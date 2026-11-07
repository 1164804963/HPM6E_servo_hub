#include "app_id_elec_angle_mode.h"
#include "motor_ctl_loop.h"

static Axis *const axis = &kAxis; // 引用电机对象实例化

AppResult IdElecAngleModeInit(void)
{
    set_app_Controlword(APP_CTRL_DISABLE); //上升沿使能，初始化置0

    axis->elec_angle_id_config.id_max_A = get_app_Motor_rated_current(); // 设置电角度辨识正弦波幅值，一般设置为电机额定电流

    return APP_RET_SUCCESS;
}

AppResult IdElecAngleModeStart(void)
{
    return APP_RET_SUCCESS;
}

AppResult IdElecAngleModeRun(void)
{
    // 辨识运行条件: 1. 使能指令生效 2. 抱闸状态为松闸
    if (get_app_Controlword() == APP_CTRL_ENABLE && get_app_Brake_state() == BRAKE_STATE_RELEASED)
    {
        if (!get_app_Emergency_brake_requested())
        {
            if (axis->elec_angle_id_output.state_now == IDENTIFICATION_MODE_STATE_FINISH)
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

AppResult IdElecAngleModeStop(void)
{
    return APP_RET_SUCCESS;
}
