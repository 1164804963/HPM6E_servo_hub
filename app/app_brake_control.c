#include "app_brake_control.h"

static BrakeControl_t brake_ctrl;

void AppBrakeControlInit(void)
{
    // 初始化抱闸状态
    brake_ctrl.now_release_enable = false;
    brake_ctrl.pre_release_enable = false;
    brake_ctrl.do_req = BRAKE_NULL;
    brake_ctrl.dt = NRT_TASK_PERIOD_S;
    brake_ctrl.timer = 0.0f;

    brake_ctrl.state = BRAKE_STATE_ENGAGED;
    brake_ctrl.mode = get_app_Brake_control_mode();

    // 计算抱闸PWM定时器配置参数，上电初始化计算一次，相关参数均为修改保存后重启生效
    bool is_pwm_adjust = (brake_ctrl.mode == BRAKE_CONTROL_MODE_PWM_AUTO ||
                          brake_ctrl.mode == BRAKE_CONTROL_MODE_PWM_MANUAL) ? true : false;
    bsp_calc_brake_pwm_timer_param(is_pwm_adjust,
                                   get_app_Brake_release_pwm_freq(),
                                   get_app_Brake_rated_voltage(),
                                   get_app_Brake_release_action_voltage(),
                                   get_app_Brake_release_hold_voltage());
}

void AppBrakeControlRun(void)
{
    if (brake_ctrl.mode == BRAKE_CONTROL_MODE_IO_AUTO || \
        brake_ctrl.mode == BRAKE_CONTROL_MODE_PWM_AUTO)
    {
        // 自动模式下，通过判断伺服当前状态进行设置抱闸/松闸请求
        brake_ctrl.do_req = BRAKE_NULL;
        APP_CONTROL_WORD now_Controlword = (APP_CONTROL_WORD)get_app_Controlword();
        // 伺服使能或紧急制动时设置为松闸请求，其他状态时一律设置为抱闸请求
        brake_ctrl.now_release_enable = (now_Controlword == APP_CTRL_ENABLE || \
                                        now_Controlword == APP_CTRL_EMERGENCY_BRAKE) ? \
                                        true : false;
    }
    else
    {
        // 手动模式下，根据外部控制的DO_IO_SET_BRAKE位判断抱闸/松闸请求
        uint32_t u32_temp = ((uint32_t)1 << DO_IO_SET_BRAKE) & \
                   get_app_Digital_io_outputs_phys() & \
                   get_app_Digital_io_outputs_mask();
        brake_ctrl.do_req = (u32_temp != 0) ? BRAKE_RELEASE : BRAKE_ENGAGE;
        brake_ctrl.now_release_enable = (brake_ctrl.do_req == BRAKE_RELEASE) ? true : false;
    }

    switch (brake_ctrl.state)
    {
        // 抱闸完成
        case BRAKE_STATE_ENGAGED:
            if (brake_ctrl.now_release_enable)
            {
                // 有 松闸请求
                // 手动模式下直接松闸，自动模式下满足松闸延迟时间
                brake_ctrl.timer += brake_ctrl.dt;
                if (brake_ctrl.do_req == BRAKE_RELEASE || \
                    brake_ctrl.timer >= get_app_Brake_release_delay_time())
                {
                    // 切换到松闸进行中状态
                    brake_ctrl.timer = 0.0f;
                    brake_ctrl.state = BRAKE_STATE_RELEASING;
                }
            }
            else
            {
                // 无/取消 松闸请求
                brake_ctrl.timer = 0.0f;
            }
            break;
        // 松闸进行中
        case BRAKE_STATE_RELEASING:
            if (brake_ctrl.now_release_enable)
            {
                // 松闸过程中，松闸机械动作时间
                brake_ctrl.timer += brake_ctrl.dt;
                if (brake_ctrl.timer >= get_app_Brake_release_time())
                {
                    // 松闸完成
                    brake_ctrl.timer = 0.0f;
                    brake_ctrl.state = BRAKE_STATE_RELEASED;
                }
            }
            else
            {
                // 松闸过程中，抱闸
                brake_ctrl.timer = 0.0f;
                brake_ctrl.state = BRAKE_STATE_ENGAGING;
            }
            break;
        // 松闸完成
        case BRAKE_STATE_RELEASED:
            if (!brake_ctrl.now_release_enable)
            {
                // 有 抱闸请求
                // 手动模式下无需延时，自动模式下满足抱闸延迟时间或抱闸制动速度阈值
                brake_ctrl.timer += brake_ctrl.dt;
                if (brake_ctrl.do_req == BRAKE_ENGAGE || \
                    brake_ctrl.timer >= get_app_Brake_engage_delay_time() || \
                    MATH_ABS(get_app_Motor_velocity_actual_value()) <= get_app_Dynamic_brake_speed_threshold())
                {
                    // 切换到抱闸进行中状态
                    brake_ctrl.timer = 0.0f;
                    brake_ctrl.state = BRAKE_STATE_ENGAGING;
                }
            }
            else
            {
                // 无/取消 抱闸请求
                brake_ctrl.timer = 0.0f;
            }
            break;
        // 抱闸过程中
        case BRAKE_STATE_ENGAGING:
            if (!brake_ctrl.now_release_enable)
            {
                // 抱闸过程中
                brake_ctrl.timer += brake_ctrl.dt;
                if (brake_ctrl.timer >= get_app_Brake_engage_time())
                {
                    // 抱闸完成
                    brake_ctrl.timer = 0.0f;
                    brake_ctrl.state = BRAKE_STATE_ENGAGED;
                }
            }
            else
            {
                // 抱闸过程中，松闸
                brake_ctrl.timer = 0.0f;
                brake_ctrl.state = BRAKE_STATE_RELEASING;
            }
            break;
        default:
            break;
    }

    // 更新抱闸PWM定时器配置参数及当前抱闸输出状态
    bsp_set_brake_pwm_timer_config(brake_ctrl.state);
    set_app_Brake_state((uint8_t)brake_ctrl.state);
}
