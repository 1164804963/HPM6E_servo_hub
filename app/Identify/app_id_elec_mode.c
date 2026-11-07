#include "app_id_elec_mode.h"
#include "motor_ctl_loop.h"

static Axis *const axis = &kAxis;// 引用电机对象实例化

AppResult IdElecModeInit(void)
{
    set_app_Controlword(APP_CTRL_DISABLE); //上升沿使能，初始化置0

    axis->elec_id_sin_config.i_max_A = get_app_Motor_rated_current(); // 设置辨识最大电流，一般设置为电机额定电流
    axis->elec_id_sin_config.u_max_V = get_app_DC_link_circuit_voltage() * 0.5f * 0.9f; // 设置最大电压 如母线电压 48V  该参数应当设置为 48.0f*0.5f*0.9f

    return APP_RET_SUCCESS;
}

AppResult IdElecModeStart(void)
{
    return APP_RET_SUCCESS;
}

AppResult IdElecModeRun(void)
{
    // 辨识运行条件: 1. 使能指令生效 2. 抱闸状态为松闸
    if (get_app_Controlword() == APP_CTRL_ENABLE && get_app_Brake_state() == BRAKE_STATE_RELEASED)
    {
        if (!get_app_Emergency_brake_requested())
        {
            if (axis->elec_id_sin_output.state_now == IDENTIFICATION_MODE_STATE_FINISH)
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

AppResult IdElecModeStop(void)
{
    return APP_RET_SUCCESS;
}
