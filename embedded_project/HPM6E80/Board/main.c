#include "board.h"            // SDK 板级包：board_init() / 控制台
#include "servo_board.h"
#include "bsp_api.h"

#include "app_scheduler.h"
#include "app_status_check.h"
#include "app_store_param.h"
#include "app_brake_control.h"
#include "app_motion_precondition.h"
#include "motor_ctl_loop.h"
#include "scope_app.h"
#include "data_param.h"

#include "servo_bringup.h"
#include "servo_console.h"
#include "servo_host.h"

/* [ECAT] EtherCAT 从站（HPM6E80 内置 ESC） */
#include "hpm_ecat_hw.h"      /* ecat_hardware_init / ecat_eeprom_emulation_* */
#include "ecatappl.h"         /* MainInit / MainLoop 的框架 */
#include "applInterface.h"    /* PROTO MainInit / MainLoop / APPL_GenerateMapping */
#include "ecatslv.h"          /* nPdInputSize / nPdOutputSize */

/* [ECAT 适配] 旧版 SSC 缺的 EEPROM 模拟命令轮询（见 Board/ecat_port_compat.c） */
extern void ecat_eeprom_cmd_poll(void);
extern bool ecat_eeprom_cmd_pending(void);
extern void ecat_esc_start_al_events(void);
extern void ecat_control_authority_tick(void);
extern void ecat_irq_follow_ssc_mode(void);
extern void ecat_dc_irq_force_enable(void);
#include "ecat_def.h"

/*
 * 初始化顺序（与 Y01 板的 HalInit() 一致，这里显式写开）：
 * 参数库 -> 控制层 -> 应用层 -> 波形/存储/抱闸。
 * 不调用 board_public/system_manage/system_init.c 的 HalInit()，原因见
 * doc/PORTING_HPM6E80.md「已知偏差」：那个文件的零漂校准直接引用板级 ADC 宏。
 */
static void servo_app_init(void)
{
    AppParamInit();
    MotorCtrlInit();
    AppInit();
    AppStatusScanInit();
    AppStoreInit();
#if defined(PORT_PATCH_CAL_DRIFT_STORE_FLASH) && (PORT_PATCH_CAL_DRIFT_STORE_FLASH)
    /* [移植补丁 14] FlashDB 参数已读完，接着从 Flash 恢复电流零漂标定结果，
     * 这样上电第一次使能就能直接跑，不需要先"使能一次做标定再使能一次"。 */
    bsp_current_calibration_restore_from_flash();
#endif
    ScopeInit();
    AppBrakeControlInit();
    AppMotionPreConditionInit();
}

int main(void)
{
    /* 1. SDK 板级：时钟、PMP、控制台。之后 printf 可用。 */
    board_init();

    /* 2. 本板外设：PWM/ADC/编码器/1ms，采样中断先跑起来，控制节拍还没放行。 */
    board_init_servo();

    /* 3. 应用层回调注册，与 Y01 板保持同一顺序。 */
    RegisterSetAppCallback(set_app);
    RegisterCheckErrorCallback(app_get_check_error_val);
    RegisterCheckWarningCallback(app_get_check_warning_val);
    RegisterCheckStatusCallback(app_get_check_status_val);
    RegisterCheckIoInputsStatusCallback(app_get_check_di_io_val);

    /* 4. 参数/控制/应用初始化。 */
    servo_app_init();

    /* 4.1 控制权交给上位机（与 Y01 一致）：Comm=HOST、Internal=APP。
     *     上位机不会主动来"要权限"，它默认设备就归它控制，所以这里必须给对，
     *     否则点使能没反应（日志里能看到 APPCONTROLWORD 发下去了，但 motor_enable
     *     一直是 0，因为 set_app_Controlword 在 CTRL 权限下只读）。
     *     代价：串口调试台的 en/dis/mode 会被应用层每 1ms 覆盖掉，
     *     接上位机时用它上面的按钮，串口只做观察。 */
    set_app_Comm_control_authority(COMM_CONTROL_HOST);
    set_app_Internal_control_authority(INTERNAL_CONTROL_APP);

    /* 5. 上电自检：编码器就绪 -> 初始化控制层位置状态 -> 三相电流零漂校准。
     *    这一步必须在放行控制节拍之前做完，否则速度环会从 0 位置起跳。 */
    if (!servo_bringup_self_test())
    {
        printf("main: self test FAILED, motor stays disabled\r\n");
    }
    servo_bringup_print_l0();

#if defined(PORT_PATCH_ENABLE_ECAT) && (PORT_PATCH_ENABLE_ECAT)
    /* 5.1 EtherCAT 从站初始化（HPM6E80 内置 ESC + Flash 模拟 EEPROM）。
     *     顺序对齐 SDK ecat_cia402 例程：board_init_ethercat 已在 board_init_servo
     *     里做过 ESC 时钟/PHY 复位；这里做 ESC 外设+PHY+EEPROM 初始化、
     *     SSC 协议栈初始化、EEPROM 模拟回调挂接、生成 PDO 映射。 */
    {
        hpm_stat_t ecat_stat;

        board_init_ethercat(HPM_ESC);       /* 幂等：ESC 引脚/时钟/PHY 复位 */
        ecat_stat = ecat_hardware_init(HPM_ESC);
        if (ecat_stat != status_success)
        {
            printf("main: ethercat hardware init FAILED (%d)\r\n", (int)ecat_stat);
        }
        else
        {
            /* Flash 模拟 EEPROM 的读写回调（新版 SSC 的 pAPPL_EEPROM_* 机制）。
             * 旧版 SSC 无此机制，靠 PDI 中断里 ecat_eeprom_cmd_poll 主动轮询响应，
             * 见 Board/ecat_port_compat.c，所以这里不需要挂 pAPPL_EEPROM_*。 */
            MainInit();                     /* SSC 协议栈初始化 */
            APPL_GenerateMapping(&nPdInputSize, &nPdOutputSize);
            ecat_esc_start_al_events();     /* 打开 AL 事件中断（ESC 0x204 掩码） */
            ecat_dc_irq_force_enable();     /* SYNC0 独立中断使能（DC 模式用） */
            printf("main: ethercat slave init done, ESC link ready\r\n");
        }
    }
#endif

    /* 6. 应用初始化完成后才放行 20kHz 控制节拍。 */
    board_start_ctrl_tick();

    /* 7. 主循环：控制全在 20kHz/1kHz 中断里；EtherCAT 协议栈在主循环轮询
     *    MainLoop() 驱动（与 Y01/EtherCAT 例程一致）。MAVLink 收发在 UART0 中断。 */
    servo_console_init();
    servo_host_init();
    while (1)
    {
#if defined(PORT_PATCH_ENABLE_ECAT) && (PORT_PATCH_ENABLE_ECAT)
        /* [ECAT 适配] ESC 的 EEPROM 模拟命令（主站读 SII/ESI）有很紧的响应窗口，
         * 超时后 ESC 就返回 0 —— 主站会看到 Man/ID 全 00000000，接着 PDO 映射
         * 算错、SAFEOP 被拒（StatusCode 1e）。所以放在 MainLoop() 之前，并且一次
         * 把队列抽干（BUSY 期间连续响应），别让一次长耗时把窗口拖过去。 */
        {
            /* DC 模式下不能在主循环里写 Flash：会长时间关中断，SYNC0 被拖过看门狗。
             * 此时只处理读命令（SII 读），写命令留到非 DC 再处理。 */
            extern bool ecat_dc_is_active(void);
            extern void ecat_eeprom_cmd_poll_readonly(void);

            if (ecat_dc_is_active())
            {
                uint32_t ecat_drain;

                for (ecat_drain = 0U; ecat_drain < 32U; ecat_drain++)
                {
                    if (!ecat_eeprom_cmd_pending())
                    {
                        break;
                    }
                    ecat_eeprom_cmd_poll_readonly();
                }
            }
            else
            {
                uint32_t ecat_drain;

                for (ecat_drain = 0U; ecat_drain < 32U; ecat_drain++)
                {
                    if (!ecat_eeprom_cmd_pending())
                    {
                        break;
                    }
                    ecat_eeprom_cmd_poll();
                }
            }
        }
        MainLoop();                      /* EtherCAT 从站协议栈主循环 */
        /* PDI 中断不可靠时用它把 SSC 切到轮询做 PDO；实测和 3-buffer SM 组合
         * 会让从站卡在 PREOP，先关掉，见 doc 里"待办"。 */
        ecat_irq_follow_ssc_mode();     /* [ECAT 适配] ESC 中断使能跟随 SSC 模式 */
        ecat_control_authority_tick();  /* [ECAT 适配] 进 OP 把控制权交给总线 */
#endif
        servo_console_poll();
    }
}
