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

#if defined(CONFIG_SERVO_ETHERCAT) && (CONFIG_SERVO_ETHERCAT)
/* [ECAT] EtherCAT 从站（HPM6E80 内置 ESC） */
#include "hpm_ecat_hw.h"      /* ecat_hardware_init / ecat_eeprom_emulation_* */
#include "ecatappl.h"         /* MainInit / MainLoop 的框架 */
#include "applInterface.h"    /* PROTO MainInit / MainLoop / APPL_GenerateMapping */
#include "ecatslv.h"          /* nPdInputSize / nPdOutputSize */
#endif

#if defined(CONFIG_SERVO_CAN) && (CONFIG_SERVO_CAN)
#include "servo_can.h"
#include "servo_debug_can.h"
#endif

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

#if defined(CONFIG_SERVO_CAN) && (CONFIG_SERVO_CAN)
    /* 5.1 CAN CiA402：应用参数初始化后启动 MCAN7；失败明确报错并保持失能。 */
    {
        hpm_stat_t can_stat = servo_can_init(kAppBaseConfig.Can_id, kAppBaseConfig.Can_baudrate);

        if (can_stat != status_success)
        {
            sys_set_bsp_error_state(ERROR_COMMS_INIT, ERROR_SET);
            (void)set_app_Controlword((uint16_t)APP_CTRL_DISABLE);
            board_set_pwm_enable(false);
            printf("main: CAN init FAILED (%d), motor stays disabled\r\n", (int)can_stat);
        }
        else
        {
            (void)set_app_Comm_control_authority((uint8_t)COMM_CONTROL_BUS);
            (void)set_app_Internal_control_authority((uint8_t)INTERNAL_CONTROL_APP);
            printf("main: J9 CAN7 CiA402 motion ready\r\n");
        }
    }

    /* J8/CAN4 independent read-only debug port. Failure here must not touch J9. */
    {
        hpm_stat_t dbg_stat = servo_debug_can_init();

        if (dbg_stat != status_success)
        {
            printf("main: J8 debug CAN init FAILED (%d), J9 unchanged\r\n", (int)dbg_stat);
        }
        else
        {
            printf("main: J8 debug CAN ready (CAN4 1Mbps id=0x015 read-only)\r\n");
        }
    }
#endif

#if defined(CONFIG_SERVO_ETHERCAT) && (CONFIG_SERVO_ETHERCAT)
    /* 5.2 EtherCAT 从站初始化（HPM6E80 内置 ESC + Flash 模拟 EEPROM）。
     *     顺序对齐 SDK ecat_cia402 例程：这里完成 ESC 引脚、时钟和 PHY 复位，
     *     再做 ESC 外设、PHY 与 EEPROM 初始化、
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
            /* Flash 模拟 EEPROM 的 SSC 回调；命令由 SSC 的 EEPROM_CommandHandler 处理。 */
            MainInit();                     /* SSC 协议栈初始化 */
            pAPPL_EEPROM_Read = ecat_eeprom_emulation_read;
            pAPPL_EEPROM_Write = ecat_eeprom_emulation_write;
            pAPPL_EEPROM_Reload = ecat_eeprom_emulation_reload;
            pAPPL_EEPROM_Store = ecat_eeprom_emulation_store;
            APPL_GenerateMapping(&nPdInputSize, &nPdOutputSize);
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
#if defined(CONFIG_SERVO_CAN) && (CONFIG_SERVO_CAN)
        servo_can_poll();
        servo_debug_can_poll();
#endif
#if defined(CONFIG_SERVO_ETHERCAT) && (CONFIG_SERVO_ETHERCAT)
        MainLoop();                      /* EtherCAT 从站协议栈主循环 */
#endif
        servo_console_poll();
    }
}
