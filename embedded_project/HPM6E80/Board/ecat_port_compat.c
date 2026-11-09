/*
 * [ECAT 适配] 旧版 SSC 与 SDK HPM port 层的兼容补齐。
 *
 * 本工程用的是较旧版本的 ETG SSC（YuanHub 定制），而 SDK
 * samples/ethercat/port 的 HPM 内置 ESC 适配层是按较新 SSC 写的。两者差异集中
 * 在这里补齐，避免改动 SDK 原文件或大改 SSC 源：
 *   1) 新版 SSC 的全局量 EepromReadSize；
 *   2) HPM ESC 的 EEPROM 模拟命令响应（read/write/reload）——新版 SSC 在 PDI
 *      中断里轮询 ESC 的 EEPROM 命令并回调，旧版 SSC 没有这段，这里补上。
 */
#include "ecat_def.h"
#include "hpm_esc_drv.h"
#include "hpm_ecat_hw.h"

/* SDK hpm_ecat_hw.c 的 eeprom 模拟读函数用 EepromReadSize 表示“本次 ESC 请求
 * 读几个字节的 EEPROM”（值 4 或 8）。HPM ESC 的 EEPROM 模拟按 8 字节读组织
 * （EEPROM_WRITE_SIZE=2，8/2=4 个字），这里固定为 8。 */
UINT16 EepromReadSize = 8;

#if defined(ESC_EEPROM_EMULATION) && ESC_EEPROM_EMULATION
/* port 层提供的 EEPROM 模拟动作与 reload 响应 */
extern UINT16 ecat_eeprom_emulation_read(UINT32 wordaddr);
extern UINT16 ecat_eeprom_emulation_write(UINT32 wordaddr);
extern void   ecat_eeprom_emulation_reload_response(void);

/*
 * [ECAT 适配] 轮询并响应 ESC 的 EEPROM 访问命令（等价新版 SSC 在 PDI 中断里
 * 做的 pAPPL_EEPROM_Read/Write/Reload 分发）。放在 PDI_Isr 末尾调用：
 * 主站读写 ESI/EEPROM 时，ESC 会产生 EEPROM 命令并触发 PDI 中断，这里及时响应，
 * 否则主站读不到 EEPROM/设备无法识别。
 */
ATTR_RAMFUNC
void ecat_eeprom_cmd_poll(void)
{
    ESC_Type *esc = HPM_ESC;

    /* 只有 EEPROM 模拟使能、且 ESC 处于忙碌(有新命令)时才处理 */
    if ((esc->EEPROM_CTRL_STAT & ESC_EEPROM_CTRL_STAT_EE_EMU_MASK) != ESC_EEPROM_CTRL_STAT_EE_EMU_MASK)
    {
        return;
    }
    if ((esc->EEPROM_CTRL_STAT & ESC_EEPROM_CTRL_STAT_BUSY_MASK) != ESC_EEPROM_CTRL_STAT_BUSY_MASK)
    {
        return;
    }

    switch (esc_get_eeprom_cmd(esc))
    {
    case esc_eeprom_read_cmd:
        if (ecat_eeprom_emulation_read(esc_get_eeprom_word_address(esc)) == ESC_EEPROM_EMULATION_SUCCESS)
        {
            esc_eeprom_emulation_ack(esc, esc_eeprom_read_cmd, false, false);
        }
        else
        {
            esc_eeprom_emulation_ack(esc, esc_eeprom_read_cmd, true, false);
        }
        break;

    case esc_eeprom_write_cmd:
        if (ecat_eeprom_emulation_write(esc_get_eeprom_word_address(esc)) == ESC_EEPROM_EMULATION_SUCCESS)
        {
            esc_eeprom_emulation_ack(esc, esc_eeprom_write_cmd, false, false);
        }
        else
        {
            esc_eeprom_emulation_ack(esc, esc_eeprom_write_cmd, true, false);
        }
        break;

    case esc_eeprom_reload_cmd:
        ecat_eeprom_emulation_reload_response();
        break;

    default:
        break;
    }
}
#else
void ecat_eeprom_cmd_poll(void) { }
#endif
