#include "app_id_mec_mode.h"
#include "motor_ctl_loop.h"

static Axis *const axis = &kAxis;// 引用电机对象实例化

AppResult IdMecModeInit(void)
{
    set_app_Controlword(APP_CTRL_DISABLE); //上升沿使能，初始化置0

    axis->mec_id_config.i_max_A = get_app_Motor_rated_current(); // 设置辨识最大电流，一般设置为电机额定电流
    axis->mec_id_config.signal_type = 0; // 机械特性辨识信号类型 0：chirp 一般默认 1：阶跃信号，超大惯量辨识适用

    return APP_RET_SUCCESS;
}

AppResult IdMecModeStart(void)
{
    return APP_RET_SUCCESS;
}

AppResult IdMecModeRun(void)
{
    // 辨识运行条件: 1. 使能指令生效 2. 抱闸状态为松闸
    if (get_app_Controlword() == APP_CTRL_ENABLE && get_app_Brake_state() == BRAKE_STATE_RELEASED)
    {
        if (!get_app_Emergency_brake_requested())
        {
            if (axis->mec_id_output.state_now == IDENTIFICATION_MODE_STATE_FINISH)
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

AppResult IdMecModeStop(void)
{
    return APP_RET_SUCCESS;
}
