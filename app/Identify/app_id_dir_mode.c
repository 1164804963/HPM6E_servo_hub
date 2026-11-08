#include "app_id_dir_mode.h"
#include "motor_ctl_loop.h"

static Axis *const axis = &kAxis; // 引用电机对象实例化

AppResult IdDirModeInit(void)
{
    set_app_Controlword(APP_CTRL_DISABLE); //上升沿使能，初始化置0

    /* [适配补丁] 上游另外 5 个辨识 APP 都在 Init 里设了辨识电流，唯独方向辨识漏了，
     * 会沿用控制层默认的 pmsm_config.rated_current（= √2 × 电机额定 = 1.697A），
     * 连续保持 25s 会累积成驱动器过载（Error_word bit1）被强制失能。
     * 这里照其它 5 个 APP 的写法补一行：用电机额定电流。 */
    axis->direction_id_config.id_tar_max_A = get_app_Motor_rated_current();

    return APP_RET_SUCCESS;
}

AppResult IdDirModeStart(void)
{
    return APP_RET_SUCCESS;
}

AppResult IdDirModeRun(void)
{
    // 辨识运行条件: 1. 使能指令生效 2. 抱闸状态为松闸
    if (get_app_Controlword() == APP_CTRL_ENABLE && get_app_Brake_state() == BRAKE_STATE_RELEASED)
    {
        if (!get_app_Emergency_brake_requested())
        {
            if (axis->direction_id_output.state_now == IDENTIFICATION_MODE_STATE_FINISH)
            {
                // 辨识完成 会自动失能电机
                set_app_Controlword(APP_CTRL_DISABLE);
                // return APP_RET_SUCCESS;
            }
        }
        else
        {
            // 触发急停，辨识失败 会自动失能电机
            set_app_Controlword(APP_CTRL_DISABLE);
            // return APP_RET_FAIL;
        }
    }

    return APP_RET_RUNNING;
}

AppResult IdDirModeStop(void)
{
    return APP_RET_SUCCESS;
}
