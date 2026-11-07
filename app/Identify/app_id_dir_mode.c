#include "app_id_dir_mode.h"
#include "motor_ctl_loop.h"

static Axis *const axis = &kAxis; // 引用电机对象实例化

AppResult IdDirModeInit(void)
{
    set_app_Controlword(APP_CTRL_DISABLE); //上升沿使能，初始化置0

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
