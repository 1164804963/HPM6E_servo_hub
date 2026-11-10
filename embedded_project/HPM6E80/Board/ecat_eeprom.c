/*
 * [ECAT 适配] ESC 模拟 EEPROM 的强符号定义。
 *
 * SDK port 层（samples/ethercat/port/hpm_ecat_hw.c）里有一个弱定义：
 *     ATTR_WEAK unsigned char aEepromData[ESC_EEPROM_SIZE] = {0xa5,0xa5,0xa5,0xa5};
 * hpm_ecat_e2p_emulation.c 的 ecat_flash_eeprom_init() 看到前 4 字节是 0xA5 就打印
 * "No EEPROM content in PROGRAM." 并跳过烧写，于是 ESC 的 SII 全空，主站读到
 * Vendor/Product/Mailbox 全是 0（slaveinfo 报 Invalid mailbox configuration）。
 *
 * 这里用强符号覆盖它，内容来自 Board/ecat_eeprom.h（由 yzi_dirid/gen_sii.py 按本工程
 * ESI 生成）。启动时 ecat_flash_eeprom_init() 会把这份 SII 写进 Flash 模拟 EEPROM。
 */
#include "ecat_def.h"
#include "hpm_ecat_hw.h"
#include "ecat_eeprom.h"

#if (ESC_EEPROM_SIZE != 2048)
#error "ecat_eeprom.h built for 2048-byte SII, check ESC_EEPROM_SIZE"
#endif
