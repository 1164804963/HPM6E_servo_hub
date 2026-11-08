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

    /* 6. 应用初始化完成后才放行 20kHz 控制节拍。 */
    board_start_ctrl_tick();

    /* 7. 主循环只做非实时的事情：上位机 MAVLink 通道 + 串口调试台。控制全在中断里。
     *    两条通道共用 UART0，由 servo_host_poll() 按字节分流。 */
    servo_console_init();
    servo_host_init();
    while (1)
    {
        servo_host_poll();
        servo_console_poll();
    }
}
