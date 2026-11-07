#include "app_homing_mode.h"

static HomingMode_t kHmMode =
{
    .now_Controlword = APP_CTRL_DISABLE,
    .pre_Controlword = APP_CTRL_DISABLE,
    .traj =
    {
        .speed_tar_p = 0,
        .acc = 0,
        .period_s = 0,
    },
    .check_status_val.all = 0,
    .emergency_brake_mode = EMERGENCY_BRAKE_MODE_DISABLED,
    .method = HOMING_METHOD_NO_HOMING_METHOD_ASSIGNED,
    .step = HOMING_STEP_INIT,
    .speed_tar_to_switch = 0,
    .speed_tar_to_zero = 0,
    .io_status.all = 0,
    .index_state = false,
    .dt = 0,
    .timer = 0,
};

static void (*MethodRun)(HomingMode_t* const p_hm);         // 回零方法运行函数指针
static AppResult SetMethodRun(HOMING_METHOD const method);  // 回零方法运行函数指针注册
// 各回零方法运行函数实现
static void MethodRun_0(HomingMode_t* const p_hm);
// ...
static void MethodRun_7(HomingMode_t* const p_hm);
// ...
static void MethodRun_35(HomingMode_t* const p_hm);

AppResult HomingModeInit(void)
{
    AppVelocityTargetReachedStateClear();
    set_app_Controlword(APP_CTRL_DISABLE);
    kHmMode.pre_Controlword = APP_CTRL_DISABLE;

    return APP_RET_SUCCESS;
}

AppResult HomingModeStart(void)
{
    return APP_RET_SUCCESS;
}

AppResult HomingModeRun(void)
{
    kHmMode.now_Controlword = (APP_CONTROL_WORD)get_app_Controlword();

    if (kHmMode.now_Controlword == APP_CTRL_ENABLE)
    {
        if (!get_app_Emergency_brake_requested())
        {
            if (kHmMode.pre_Controlword == APP_CTRL_DISABLE)
            {
                // 使能前更新一次回零参数
                kHmMode.method = (HOMING_METHOD)get_app_Homing_method();
                if (SetMethodRun(kHmMode.method) == APP_RET_SUCCESS)
                {
                    kHmMode.step = HOMING_STEP_START;
                }
                else
                {
                    kHmMode.step = HOMING_STEP_FAIL;
                    set_app_Controlword(APP_CTRL_DISABLE); // 手动禁用使能位
                    return APP_RET_FAIL;
                }
                kHmMode.speed_tar_to_switch = get_app_Homing_speed_search_for_switch() * \
                                              get_app_Motor_rpm_2_pps() * get_app_Reduction_ratio();
                kHmMode.speed_tar_to_zero = get_app_Homing_speed_search_for_zero() * \
                                            get_app_Motor_rpm_2_pps() * get_app_Reduction_ratio();
                kHmMode.traj.acc = get_app_Homing_acceleration() * \
                                   get_app_Motor_rpm_2_pps() * get_app_Reduction_ratio();
                set_app_Encoder_zero_crossing_state(0); // 清除Index信号状态
                set_app_Homing_state(HOMING_STATE_IDLE);

                // 重新使能后初始化规划器
                SpeedTrajectoryPlanningInit();
            }

            // 规划速度为0的情况：1. 暂停指令生效 2. 抱闸状态不为松闸
            if (get_app_Halt_running_cmd() == true || get_app_Brake_state() != BRAKE_STATE_RELEASED)
            {
                kHmMode.traj.speed_tar_p = 0;
            }
            else if (kHmMode.step != HOMING_STEP_COMPLETE)
            {
                // 开关及Index信号等状态更新
                kHmMode.io_status.all = get_app_Digital_io_inputs_status();
                kHmMode.index_state = get_app_Encoder_zero_crossing_state();
                set_app_Encoder_zero_crossing_state(0); // 使用完清除Index信号状态
                kHmMode.check_status_val = (CheckStatusVal_t)app_get_check_status_val();
                // 运行回零方法
                MethodRun(&kHmMode);
                set_app_Homing_step(kHmMode.step);
            }

            // 回零成功后仅执行一次更新回零偏移值
            if (kHmMode.step == HOMING_STEP_COMPLETE && get_app_Homing_state() != HOMING_STATE_SUCCEED)
            {
                set_app_Homing_state(HOMING_STATE_SUCCEED);
                set_app_Home_position_offset_value(get_app_Position_actual_value_inc() + \
                                                   get_app_Home_offset());
                // TODO: 根据实际应用场景，可添加自动保存回零偏移值，但同时会将其它参数保存，注意不要重复保存
                // return APP_RET_SUCCESS; // 设置成功将停止此模式，无法重复运行
            }
            // 回零失败后状态置为失败
            else if (kHmMode.step == HOMING_STEP_FAIL)
            {
                set_app_Homing_state(HOMING_STATE_FAIL);
            }
            else
            {
                // TODO：根据实际应用场景，可在此进行超时时间累计及处理
            }
        }
        else
        {
            kHmMode.now_Controlword = APP_CTRL_DISABLE;
            set_app_Controlword(APP_CTRL_DISABLE); // 手动禁用使能位
        }
    }

    // 紧急停车（QuickStop）处理
    if (kHmMode.now_Controlword == APP_CTRL_EMERGENCY_BRAKE)
    {
        kHmMode.step = HOMING_STEP_FAIL;
        set_app_Homing_step(kHmMode.step);

        kHmMode.traj.speed_tar_p = 0; // 如果处于急停状态，规划速度为0
        kHmMode.emergency_brake_mode = get_app_Quick_stop_option_code();
        if (kHmMode.emergency_brake_mode == EMERGENCY_BRAKE_MODE_QUICK_STOP_RAMP ||\
            kHmMode.emergency_brake_mode == EMERGENCY_BRAKE_MODE_QUICK_STOP_RAMP_ENABLE ||\
            kHmMode.emergency_brake_mode == EMERGENCY_BRAKE_MODE_CURRENT_LIMIT ||\
            kHmMode.emergency_brake_mode == EMERGENCY_BRAKE_MODE_CURRENT_LIMIT_ENABLE)
        {
            kHmMode.traj.acc = get_app_Quick_stop_deceleration() * get_app_Motor_rpm_2_pps() * \
                               get_app_Reduction_ratio();
        }
        else if (kHmMode.emergency_brake_mode != EMERGENCY_BRAKE_MODE_DISABLED)
        {
            //TODO: 电压限制急停先不实现按正常减速斜率停机
            kHmMode.traj.acc = get_app_Profile_deceleration() * get_app_Motor_rpm_2_pps() * \
                               get_app_Reduction_ratio();
        }
        // 在急停后失能电机模式下，检测到零速后电机失能
        if (kHmMode.emergency_brake_mode <= EMERGENCY_BRAKE_MODE_VOLTAGE_LIMIT)
        {
            kHmMode.check_status_val = (CheckStatusVal_t)app_get_check_status_val();
            if (kHmMode.emergency_brake_mode == EMERGENCY_BRAKE_MODE_DISABLED ||\
                kHmMode.check_status_val.bits.velocity_zero == true)
            {
                set_app_Controlword(APP_CTRL_DISABLE);
                kHmMode.now_Controlword = APP_CTRL_DISABLE;
            }
        }
    }

    if (kHmMode.now_Controlword != APP_CTRL_DISABLE)
    {
        SpeedTrajectoryPlanningHandle(&kHmMode.traj);
    }

    kHmMode.pre_Controlword = kHmMode.now_Controlword;

    AppHomingAttainedStateCheck();

    return APP_RET_RUNNING;
}

AppResult HomingModeStop(void)
{
    return APP_RET_SUCCESS;
}

// 回零方法实现如下：
static AppResult SetMethodRun(HOMING_METHOD const method)
{
    switch (method)
    {
    case HOMING_METHOD_NO_HOMING_METHOD_ASSIGNED:
        MethodRun = MethodRun_0;
        break;
    case HOMING_METHOD_7:
        MethodRun = MethodRun_7;
        break;
    case HOMING_METHOD_35:
        MethodRun = MethodRun_35;
        break;
    default:
        MethodRun = MethodRun_0;
        return APP_RET_FAIL;
    }
    return APP_RET_SUCCESS;
}

static void MethodRun_0(HomingMode_t* const p_hm)
{
    p_hm->step = HOMING_STEP_FAIL;
}

static void MethodRun_7(HomingMode_t* const p_hm)
{
    switch (p_hm->step)
    {
        case HOMING_STEP_INIT:
            break;
        case HOMING_STEP_START:
            // 根据初始状态选择回零路径
            // 碰到正极限位，负向运行
            if (p_hm->io_status.bits.positive_limit_switch && !p_hm->io_status.bits.home_switch)
            {
                p_hm->traj.speed_tar_p = -p_hm->speed_tar_to_switch;
                p_hm->step = HOMING_STEP_SEARCH_HOME_SWITCH;
            }
            // 碰到回零开关，负向运行
            else if (p_hm->io_status.bits.home_switch)
            {
                p_hm->traj.speed_tar_p = -p_hm->speed_tar_to_switch;
                p_hm->step = HOMING_STEP_RETRACT_FROM_HOME_SWITCH;
            }
            // 其他状态，正向运行
            else
            {
                p_hm->traj.speed_tar_p = p_hm->speed_tar_to_switch;
                p_hm->step = HOMING_STEP_SEARCH_SWITCH;
            }
            break;
        case HOMING_STEP_SEARCH_SWITCH:
            // 正向搜索开关
            if (p_hm->io_status.bits.home_switch)
            {
                // 碰到回零开关，负向退出回零开关
                p_hm->traj.speed_tar_p = -p_hm->speed_tar_to_switch;
                p_hm->step = HOMING_STEP_RETRACT_FROM_HOME_SWITCH;
            }
            else if (p_hm->io_status.bits.positive_limit_switch)
            {
                // 碰到正极限位，负向搜索回零开关
                p_hm->traj.speed_tar_p = -p_hm->speed_tar_to_switch;
                p_hm->step = HOMING_STEP_SEARCH_HOME_SWITCH;
            }
            else if (p_hm->io_status.bits.negative_limit_switch)
            {
                // 碰到负极限位，为异常情况，传感器安装位置不对
                p_hm->traj.speed_tar_p = 0;
                p_hm->step = HOMING_STEP_FAIL;
            }
            break;
        case HOMING_STEP_SEARCH_HOME_SWITCH:
            // 负向搜索回零开关
            if (p_hm->io_status.bits.home_switch)
            {
                // 碰到回零开关，负向退出回零开关
                p_hm->traj.speed_tar_p = -p_hm->speed_tar_to_switch;
                p_hm->step = HOMING_STEP_RETRACT_FROM_HOME_SWITCH;
            }
            else if (p_hm->io_status.bits.negative_limit_switch)
            {
                // 碰到负极限位，为异常情况，传感器安装位置不对
                p_hm->traj.speed_tar_p = 0;
                p_hm->step = HOMING_STEP_FAIL;
            }
            break;
        case HOMING_STEP_RETRACT_FROM_HOME_SWITCH:
            if (!p_hm->io_status.bits.home_switch)
            {
                // 退出回零开关后，负向搜索Index信号
                p_hm->index_state = false;
                p_hm->traj.speed_tar_p = -p_hm->speed_tar_to_zero;
                p_hm->step = HOMING_STEP_SEARCH_INDEX;
            }
            break;
        case HOMING_STEP_SEARCH_INDEX:
            // 负向搜索Index信号
            if (p_hm->index_state)
            {
                // 找到Index信号，立即减速
                p_hm->traj.speed_tar_p = 0;
                p_hm->step = HOMING_STEP_DECELERATE;
            }
            break;
        case HOMING_STEP_DECELERATE:
            // 回零完成减速中
            if (p_hm->check_status_val.bits.velocity_zero)
            {
                // 速度减到零速，回零完成
                p_hm->traj.speed_tar_p = 0;
                p_hm->step = HOMING_STEP_COMPLETE;
            }
            break;
        case HOMING_STEP_COMPLETE:
            // 回零完成
            p_hm->traj.speed_tar_p = 0;
            break;
        default:
            p_hm->traj.speed_tar_p = 0;
            p_hm->step = HOMING_STEP_FAIL;
            break;
    }
}

static void MethodRun_35(HomingMode_t* const p_hm)
{
    p_hm->traj.speed_tar_p = 0;
    p_hm->step = HOMING_STEP_COMPLETE;
}