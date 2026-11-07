#include "app_profile_velocity_mode.h"

static PvMode_t kPvMode =
{
    .now_Controlword = APP_CTRL_DISABLE,
    .pre_Controlword = APP_CTRL_DISABLE,
    .traj = {
        .speed_tar_p = 0,
        .acc = 0,
        .period_s = 0,
    },
    .check_status_val.all = 0,
    .emergency_brake_mode = EMERGENCY_BRAKE_MODE_DISABLED,
    .velocity_target = 0,
};

AppResult PvModeInit(void)
{
    AppVelocityTargetReachedStateClear();
    set_app_Controlword(APP_CTRL_DISABLE); // 上升沿使能，初始化置0
    kPvMode.pre_Controlword = APP_CTRL_DISABLE;

    return APP_RET_SUCCESS;
}

AppResult PvModeStart(void)
{
    return APP_RET_SUCCESS;
}

AppResult PvModeRun(void)
{
    kPvMode.now_Controlword = (APP_CONTROL_WORD)get_app_Controlword();

    if (kPvMode.now_Controlword == APP_CTRL_ENABLE)
    {
        if (!get_app_Emergency_brake_requested())
        {
            if (kPvMode.pre_Controlword == APP_CTRL_DISABLE)
            {
                // 重新使能后初始化规划器
                SpeedTrajectoryPlanningInit();
            }

            kPvMode.velocity_target = get_app_Target_velocity();

            // 规划速度为0的情况：1. 暂停指令生效 2. 抱闸状态不为松闸
            if (get_app_Halt_running_cmd() == true || get_app_Brake_state() != BRAKE_STATE_RELEASED)
            {
                kPvMode.traj.speed_tar_p = 0;
            }
            else
            {
                kPvMode.traj.speed_tar_p = kPvMode.velocity_target * get_app_Motor_rpm_2_pps() * \
                                           get_app_Reduction_ratio();
            }

            // 轮廓加速度减速度切换 目标速度绝对值 大于 当前规划速度绝对值加速 否则则加速
            if (MATH_ABS(kPvMode.velocity_target) > MATH_ABS(get_app_Velocity_demand_value()))
            {
                kPvMode.traj.acc = get_app_Profile_acceleration() * get_app_Motor_rpm_2_pps() * \
                                   get_app_Reduction_ratio();
            }
            else
            {
                kPvMode.traj.acc = get_app_Profile_deceleration() * get_app_Motor_rpm_2_pps() * \
                                   get_app_Reduction_ratio();
            }
        }
        else
        {
            set_app_Controlword(APP_CTRL_EMERGENCY_BRAKE); // 强制进入紧急停车（QuickStop）状态
            kPvMode.now_Controlword = APP_CTRL_EMERGENCY_BRAKE;
        }
    }

    // 紧急停车（QuickStop）处理
    if (kPvMode.now_Controlword == APP_CTRL_EMERGENCY_BRAKE)
    {
        kPvMode.traj.speed_tar_p = 0; // 如果处于急停状态，规划速度为0
        kPvMode.emergency_brake_mode = get_app_Quick_stop_option_code();
        if (kPvMode.emergency_brake_mode == EMERGENCY_BRAKE_MODE_QUICK_STOP_RAMP ||\
            kPvMode.emergency_brake_mode == EMERGENCY_BRAKE_MODE_QUICK_STOP_RAMP_ENABLE ||\
            kPvMode.emergency_brake_mode == EMERGENCY_BRAKE_MODE_CURRENT_LIMIT ||\
            kPvMode.emergency_brake_mode == EMERGENCY_BRAKE_MODE_CURRENT_LIMIT_ENABLE)
        {
            kPvMode.traj.acc = get_app_Quick_stop_deceleration() * get_app_Motor_rpm_2_pps() * \
                               get_app_Reduction_ratio();
        }
        else if (kPvMode.emergency_brake_mode != EMERGENCY_BRAKE_MODE_DISABLED)
        {
            //TODO: 电压限制急停先不实现按正常减速斜率停机
            kPvMode.traj.acc = get_app_Profile_deceleration() * get_app_Motor_rpm_2_pps() * \
                               get_app_Reduction_ratio();
        }
        // 在急停后失能电机模式下，检测到零速后电机失能
        if (kPvMode.emergency_brake_mode <= EMERGENCY_BRAKE_MODE_VOLTAGE_LIMIT)
        {
            kPvMode.check_status_val = (CheckStatusVal_t)app_get_check_status_val();
            if (kPvMode.emergency_brake_mode == EMERGENCY_BRAKE_MODE_DISABLED ||\
                kPvMode.check_status_val.bits.velocity_zero == true)
            {
                set_app_Controlword(APP_CTRL_DISABLE);
                kPvMode.now_Controlword = APP_CTRL_DISABLE;
            }
        }
    }

    if (kPvMode.now_Controlword != APP_CTRL_DISABLE)
    {
        SpeedTrajectoryPlanningHandle(&kPvMode.traj);
    }

    kPvMode.pre_Controlword = kPvMode.now_Controlword;

    AppVelocityTargetReachedStateCheck();

    return APP_RET_RUNNING;
}

AppResult PvModeStop(void)
{
    return APP_RET_SUCCESS;
}
