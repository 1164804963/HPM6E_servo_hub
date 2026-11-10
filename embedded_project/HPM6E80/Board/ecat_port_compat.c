/*
 * [ECAT 适配] 旧版 SSC 与 SDK HPM port 层之间的兼容层。
 *
 * 本工程用较旧版本的 ETG SSC（YuanHub 定制），而 SDK 的
 * samples/ethercat/port 是按较新 SSC 写的。差异集中在这里补齐，
 * 不改 SDK 原文件，也不动 app/ 便携层。职责共五项：
 *
 *   1) EepromReadSize：新版 SSC 的全局量，SDK 的 eeprom 模拟读函数要用；
 *   2) ESC 的 EEPROM 模拟命令响应（read/write/reload）：新版 SSC 在 PDI 中断里
 *      分发 pAPPL_EEPROM_*，旧版没有，这里补上（写 Flash 的部分留在主循环）；
 *   3) ecat_esc_start_al_events()：初始化后先把 SM2/SM3 的过程数据事件写进
 *      ESC 的 AL Event Mask(0x204)，否则第一次 PREOP->SAFEOP 收不到 PDI 中断；
 *   4) ecat_control_authority_tick()：EtherCAT 与上位机的控制权仲裁，以及
 *      主站回到 INIT 时复位协议栈与 CiA402 状态机；
 *   5) ecat_irq_follow_ssc_mode()：ESC 中断使能跟随 SSC 的工作模式；
 *   6) ecat_dc_sync0_hook()：DC/SYNC0 节拍，交给 1kHz 位置速度环消费。
 */
#include "ecat_def.h"
#include "ecatslv.h"         /* PROCESS_OUTPUT_EVENT / PROCESS_INPUT_EVENT 等 AL 事件位 */
#include "hpm_esc_drv.h"
#include "hpm_ecat_hw.h"
#include "hpm_interrupt.h"   /* intc_m_enable_irq_with_priority / HPM_PLIC_BASE */
#include "bsp_api.h"
#include "servo_board.h"   /* extern BspData kBspData */       /* kBspData.ctrl_tick：20kHz 控制节拍，用来测 SYNC0 周期 */
#include "data_param.h"      /* set_app_Comm_control_authority / COMM_CONTROL_* */
#include "coeappl.h"         /* COE_Init：INIT 时复位同步参数 */
#include "cia402_fsm.h"      /* INIT 时复位 CiA402 状态机 */

/* SDK 的 eeprom 模拟读函数用 EepromReadSize 表示"本次 ESC 请求读几个字节的 EEPROM"
 * （4 或 8）。哪一档由 ESC 寄存器 0x502 的 bit6（NUM_RD_BYTE）决定：0=4 字节，1=8 字节。
 * 新版 SSC 在 MainInit 里读一次就定死，这里每次轮询都按当前寄存器值刷新。
 * 写错这一档，主站的 SII 读会一律拿到 0（vendor/product/mailbox 全 0）。 */
UINT16 EepromReadSize = 8;




#if defined(ESC_EEPROM_EMULATION) && ESC_EEPROM_EMULATION
/* port 层提供的 EEPROM 模拟动作与 reload 响应 */
extern UINT16 ecat_eeprom_emulation_read(UINT32 wordaddr);
extern UINT16 ecat_eeprom_emulation_write(UINT32 wordaddr);
extern void   ecat_eeprom_emulation_reload_response(void);

/*
 * 轮询并响应 ESC 的 EEPROM 访问命令（等价新版 SSC 在 PDI 中断里做的分发）。
 * allow_write = false：只处理 read/reload，避免在中断上下文里写 Flash；
 * allow_write = true ：全处理，供主循环使用。
 */
ATTR_RAMFUNC
static void ecat_eeprom_cmd_service(bool allow_write)
{
    ESC_Type *esc = HPM_ESC;
    uint16_t stat;

    stat = esc->EEPROM_CTRL_STAT;

    if ((stat & ESC_EEPROM_CTRL_STAT_EE_EMU_MASK) != ESC_EEPROM_CTRL_STAT_EE_EMU_MASK)
    {
        return;
    }
    if ((stat & ESC_EEPROM_CTRL_STAT_BUSY_MASK) != ESC_EEPROM_CTRL_STAT_BUSY_MASK)
    {
        return;
    }

    /* 本次访问是 4 字节还是 8 字节：ESC 0x502 bit6 (NUM_RD_BYTE) */
    EepromReadSize = ((stat & ESC_EEPROM_CTRL_STAT_NUM_RD_BYTE_MASK) != 0U) ? 8U : 4U;

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
        if (!allow_write)
        {
            return;     /* 高频上下文里不写 Flash，留给主循环 */
        }
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

/* 主循环用：read/write/reload 全处理 */
ATTR_RAMFUNC
void ecat_eeprom_cmd_poll(void)
{
    ecat_eeprom_cmd_service(true);
}

/* DC 模式用：只处理 read/reload，不写 Flash（避免长时间关中断拖垮 SYNC0） */
ATTR_RAMFUNC
void ecat_eeprom_cmd_poll_readonly(void)
{
    ecat_eeprom_cmd_service(false);
}

/* ESC 是否挂着一条待响应的 EEPROM 命令（主循环用它决定要不要继续抽干队列） */
ATTR_RAMFUNC
bool ecat_eeprom_cmd_pending(void)
{
    ESC_Type *esc = HPM_ESC;
    uint16_t stat = esc->EEPROM_CTRL_STAT;

    if ((stat & (uint16_t)(ESC_EEPROM_CTRL_STAT_EE_EMU_MASK | ESC_EEPROM_CTRL_STAT_BUSY_MASK))
        != (uint16_t)(ESC_EEPROM_CTRL_STAT_EE_EMU_MASK | ESC_EEPROM_CTRL_STAT_BUSY_MASK))
    {
        return false;
    }

    return (esc_get_eeprom_cmd(esc) != (uint8_t)esc_eeprom_idle_cmd);
}

#else
void ecat_eeprom_cmd_poll(void) { }
void ecat_eeprom_cmd_poll_readonly(void) { }
bool ecat_eeprom_cmd_pending(void) { return false; }
#endif

/*
 * 打开 AL 事件中断（ESC 0x204 AL Event Mask）。
 *
 * 旧版 SSC 只在 PREOP->SAFEOP 的状态转换里 SetALEventMask()，而这次转换本身要靠
 * PDI 中断去处理 AL Control 请求；掩码一开始是 0 的话 PDI 中断永远不会来。
 * 所以在初始化后主动把 SM2/SM3 的过程数据事件写进掩码。
 */
void ecat_esc_start_al_events(void)
{
    extern void SetALEventMask(UINT16 intMask);

    SetALEventMask((UINT16)(PROCESS_OUTPUT_EVENT | PROCESS_INPUT_EVENT));
}

/*
 * 控制权仲裁 + INIT 复位。
 *
 * 应用层的权限模型是二选一（data_type_define.h）：
 *   COMM_CONTROL_HOST = 0  上位机（MAVLink）控制
 *   COMM_CONTROL_BUS  = 1  总线（CANopen / EtherCAT）控制
 * ecat_callback.c 里每个 Write 回调都是"上位机掌权就直接返回"，
 * 所以 EtherCAT 侧的控制权切换放在 SSC 的
 * APPL_StartOutputHandler / APPL_StopOutputHandler（进/出 OP 的确切时刻）里做；
 * 这里只负责：主站把从站写回 INIT 时复位协议栈与 CiA402 状态机。
 */
void ecat_control_authority_tick(void)
{
    extern unsigned char nAlStatus;

    static uint8_t s_last_state;

    uint8_t st = (uint8_t)(nAlStatus & STATE_MASK);

    if ((st == STATE_INIT) && (s_last_state >= STATE_PREOP))
    {
        extern void ECAT_Init(void);
        extern void COE_Init(void);
        extern Cia402State CurrentState;

        /* 总线回到 INIT = 驱动器复位：协议栈与 CiA402 状态机都回初始态，
         * 否则上一次会话残留的 FSA 状态会让下一次的使能梯子偶发上不去。 */
        ECAT_Init();
        /* CoE 同步参数复位：0x1C32/0x1C33 的同步类型与 bSyncSetByUser 回默认，
         * 否则下次进 SAFEOP 时 SSC 会沿用上一次会话的同步类型判断。 */
        COE_Init();
        CurrentState = kStart;
    }

    s_last_state = st;
}

/*
 * ESC 中断使能跟随 SSC 的工作模式。
 *
 * SSC 有两套过程数据通路：
 *   - bEscIntEnabled = FALSE（FreeRun/轮询）：事件由 MainLoop 里的
 *     HW_GetALEventRegister() 消费（读即清）；
 *   - bEscIntEnabled = TRUE（SM-Synchronous / DC）：事件由 PDI 中断消费。
 * 端口层 ENABLE_ESC_INT() 是无条件打开的，于是 PREOP 阶段（FreeRun）里
 * PDI 中断也会先读掉 0x220，把"主站请求 SAFEOP"这类 AL_CONTROL_EVENT 吃掉。
 * 这里让 IRQn_ESC 的使能跟随 bEscIntEnabled，保证两套通路只有一个消费者。
 * 优先级要高于 20kHz 电流环(6)：过程数据中断被拖住会丢 SM2 缓冲，
 * 进而触发 ESC 的 SM 看门狗(AL 0x1B)。
 */
void ecat_irq_follow_ssc_mode(void)
{
    static uint8_t s_last_enabled;
    static uint8_t s_last_dc;

    uint8_t want = (bEscIntEnabled != FALSE) ? 1U : 0U;

    if (want != s_last_enabled)
    {
        if (want != 0U)
        {
            intc_m_enable_irq_with_priority(IRQn_ESC, 8);
        }
        else
        {
            intc_m_disable_irq(IRQn_ESC);
        }

        s_last_enabled = want;
    }

    /* DC 模式：SYNC0 中断必须使能，否则 Sync0_Isr 不跑 -> bDcRunning 变 0
     * -> SSC 在 OP 里判定 SYNC 超时把从站踢回 SAFEOP（实测就是这么掉的）。 */
    {
        uint8_t dc = (bDcSyncActive != FALSE) ? 1U : 0U;

        if (dc != s_last_dc)
        {
            if (dc != 0U)
            {
                intc_m_enable_irq_with_priority(IRQn_ESC_SYNC0, 8);
            }
            else
            {
                intc_m_disable_irq(IRQn_ESC_SYNC0);
            }

            s_last_dc = dc;
        }
    }
}

/* ======================================================================== */
/* DC / SYNC0                                                               */
/* ======================================================================== */

/* SYNC0 节拍计数（应用/调试可读，1kHz 环每拍 +1） */
volatile uint32_t ecat_dc_cycle_cnt;
/* SYNC0 到 1kHz 环的交接标志 */
static volatile bool s_dc_sync0_flag;

/* SYNC0 周期统计（单位 us，来自 ESC 的 DC 系统时间 0x900） */
volatile uint32_t ecat_dc_period_us;
volatile uint32_t ecat_dc_period_min_us;
volatile uint32_t ecat_dc_period_max_us;

/*
 * 由 SSC 的 Sync0_Isr() 调用（ESC 的 SYNC0 中断 -> port 层 ecat_sync0_isr
 * -> Sync0_Isr）。这里只做两件事：
 *   1) 用 ESC 自己的 DC 系统时间统计 SYNC0 周期（不需要示波器就能看抖动）；
 *   2) 置节拍标志，让 1kHz 位置速度环在 SYNC0 之后立即执行。
 */
void ecat_dc_sync0_hook(void)
{
    static uint32_t s_last_time;
    static uint8_t  s_inited;

    /* 用 ESC 的 DC 系统时间（SYS_TIME @0x910，1ns，32 位低半部分）测 SYNC0 周期 */
    uint32_t now = HPM_ESC->SYS_TIME;

    /* 新增：只统计 DC 激活期间的间隔；离开 DC 时复位统计 */

    if (bDcSyncActive == FALSE)
    {
        s_inited = 0U;
        ecat_dc_period_min_us = 0U;
        ecat_dc_period_max_us = 0U;
        ecat_dc_cycle_cnt = 0U;
        return;
    }

    if (s_inited != 0U)
    {
        uint32_t d_us = (now - s_last_time) / 1000u;

        /* 超过 2s 视为环绕/异常，丢弃（但记一次 10ms 以上的大间隔） */
        if (d_us < 2000000u)
        {
            ecat_dc_period_us = d_us;
            if ((ecat_dc_period_min_us == 0U) || (d_us < ecat_dc_period_min_us))
            {
                ecat_dc_period_min_us = d_us;
            }
            if (d_us > ecat_dc_period_max_us)
            {
                ecat_dc_period_max_us = d_us;
            }
        }
    }
    else
    {
        s_inited = 1U;
    }

    s_last_time = now;

    ecat_dc_cycle_cnt++;
    s_dc_sync0_flag = true;
}

/* 1kHz 环取 SYNC0 节拍；DC 激活时用它代替固定分频 */
bool ecat_dc_sync0_take(void)
{
    if (s_dc_sync0_flag)
    {
        s_dc_sync0_flag = false;
        return true;
    }

    return false;
}

/* 从站当前是否运行在 DC 模式（SSC 的 bDcSyncActive） */
bool ecat_dc_is_active(void)
{
    return (bDcSyncActive != FALSE) ? true : false;
}


/*
 * [ECAT 适配] DC/SYNC0 中断强制使能。
 *
 * HPM ESC 的 SYNC0 事件有两个去向（GPR_CFG0 的 SYNC0_PDI_IRQEN 位）：
 *   - 置位：SYNC0 事件合并进 PDI 中断（IRQn_ESC）。可我们的 IRQn_ESC 在 SSC
 *     FreeRun 阶段是关闭的，DC 激活后又来不及打开 -> SYNC0 事件直接丢失；
 *   - 清零：SYNC0 用独立中断 IRQn_ESC_SYNC0。
 * SDK 默认走前者。这里明确改成"独立中断"，并在初始化时就把 IRQn_ESC_SYNC0 打开，
 * 不依赖任何状态切换。
 */
void ecat_dc_irq_force_enable(void)
{
    /* 独立 SYNC0 中断：优先级高于 20kHz 电流环，随时可抢占。
     * 注意：不依赖 esc_enable_sync_irq_to_pdi_irq()（本工程未定义
     * HPM_IP_FEATURE_ESC_SYNC_IRQ_MASK，该内联函数不可见）。
     * 独立中断和 PDI 中断两条路都开着，SYNC0 事件不会被丢。 */
    intc_m_enable_irq_with_priority(IRQn_ESC_SYNC0, 9);
}


