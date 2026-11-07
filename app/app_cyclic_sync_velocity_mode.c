#include "app_cyclic_sync_velocity_mode.h"

static CsvMode_t kCsvMode =
{
    .now_Controlword = APP_CTRL_DISABLE,
    .pre_Controlword = APP_CTRL_DISABLE,
    .traj = {
        .is_update_tar = false,
        .speed_tar_buff_p_s[0] = 0,
        .speed_tar_buff_p_s[1] = 0,
        .speed_tar_buff_p_s[2] = 0,
        .speed_tar_buff_p_s[3] = 0,
        .ip_dt_s = 0,
        .period_s = 0,
    },
    .check_status_val.all = 0,
    .emergency_brake_mode = EMERGENCY_BRAKE_MODE_DISABLED,
    .velocity_target = 0,
};

AppResult CsvModeInit(void)
{
    AppVelocityTargetReachedStateClear();
    set_app_Target_update_state(false); // 清除目标更新状态值
    set_app_Controlword(APP_CTRL_DISABLE); // 上升沿使能，初始化置0
    kCsvMode.pre_Controlword = APP_CTRL_DISABLE;
    kCsvMode.velocity_target = get_app_Motor_velocity_actual_value() * \
                               get_app_Motor_rpm_2_pps();

    kCsvMode.traj.speed_tar_buff_p_s[0] = kCsvMode.velocity_target;
    kCsvMode.traj.speed_tar_buff_p_s[1] = kCsvMode.traj.speed_tar_buff_p_s[0];
    kCsvMode.traj.speed_tar_buff_p_s[2] = kCsvMode.traj.speed_tar_buff_p_s[0];
    kCsvMode.traj.speed_tar_buff_p_s[3] = kCsvMode.traj.speed_tar_buff_p_s[0];

    kCsvMode.traj.ip_dt_s = get_app_Interp_period();
    kCsvMode.traj.is_update_tar = true;

    return APP_RET_SUCCESS;
}

AppResult CsvModeStart(void)
{
    return APP_RET_SUCCESS;
}

AppResult CsvModeRun(void)
{
    kCsvMode.now_Controlword = (APP_CONTROL_WORD)get_app_Controlword();

    if (kCsvMode.now_Controlword == APP_CTRL_ENABLE)
    {
        if (!get_app_Emergency_brake_requested())
        {
            if (kCsvMode.pre_Controlword == APP_CTRL_DISABLE)
            {
                // 重新使能后初始化规划器
                CsvTrajectoryPlanningInit();

                kCsvMode.velocity_target = get_app_Motor_velocity_actual_value() * \
                                           get_app_Motor_rpm_2_pps();

                kCsvMode.traj.speed_tar_buff_p_s[0] = kCsvMode.velocity_target;
                kCsvMode.traj.speed_tar_buff_p_s[1] = kCsvMode.traj.speed_tar_buff_p_s[0];
                kCsvMode.traj.speed_tar_buff_p_s[2] = kCsvMode.traj.speed_tar_buff_p_s[0];
                kCsvMode.traj.speed_tar_buff_p_s[3] = kCsvMode.traj.speed_tar_buff_p_s[0];
                kCsvMode.traj.ip_dt_s = get_app_Interp_period();

                kCsvMode.traj.is_update_tar = true;
            }

            // 更新目标速度条件: 1. 目标更新状态为真 2. 抱闸状态为松闸
            if ((bool)get_app_Target_update_state() == true && get_app_Brake_state() == BRAKE_STATE_RELEASED)
            {
                set_app_Target_update_state(false);

                kCsvMode.velocity_target = get_app_Target_velocity() * get_app_Motor_rpm_2_pps() * \
                                           get_app_Reduction_ratio();

                kCsvMode.traj.speed_tar_buff_p_s[0] = kCsvMode.traj.speed_tar_buff_p_s[1];
                kCsvMode.traj.speed_tar_buff_p_s[1] = kCsvMode.traj.speed_tar_buff_p_s[2];
                kCsvMode.traj.speed_tar_buff_p_s[2] = kCsvMode.traj.speed_tar_buff_p_s[3];
                kCsvMode.traj.speed_tar_buff_p_s[3] = kCsvMode.velocity_target;

                kCsvMode.traj.is_update_tar = true;
            }
        }
        else
        {
            set_app_Controlword(APP_CTRL_EMERGENCY_BRAKE); // 强制进入紧急停车（QuickStop）状态
            kCsvMode.now_Controlword = APP_CTRL_EMERGENCY_BRAKE;
        }
    }

    // 紧急停车（QuickStop）处理
    if (kCsvMode.now_Controlword == APP_CTRL_EMERGENCY_BRAKE)
    {
        kCsvMode.emergency_brake_mode = get_app_Quick_stop_option_code();

        kCsvMode.velocity_target = 0;
        kCsvMode.traj.speed_tar_buff_p_s[0] = kCsvMode.traj.speed_tar_buff_p_s[1];
        kCsvMode.traj.speed_tar_buff_p_s[1] = kCsvMode.traj.speed_tar_buff_p_s[2];
        kCsvMode.traj.speed_tar_buff_p_s[2] = kCsvMode.traj.speed_tar_buff_p_s[3];
        kCsvMode.traj.speed_tar_buff_p_s[3] = kCsvMode.velocity_target;

        // 在急停后失能电机模式下，检测到零速后电机失能
        if (kCsvMode.emergency_brake_mode <= EMERGENCY_BRAKE_MODE_VOLTAGE_LIMIT)
        {
            kCsvMode.check_status_val = (CheckStatusVal_t)app_get_check_status_val();
            if (kCsvMode.emergency_brake_mode == EMERGENCY_BRAKE_MODE_DISABLED ||\
                kCsvMode.check_status_val.bits.velocity_zero == true)
            {
                set_app_Controlword(APP_CTRL_DISABLE);
                kCsvMode.now_Controlword = APP_CTRL_DISABLE;
            }
        }
    }

    if (kCsvMode.now_Controlword != APP_CTRL_DISABLE)
    {
        CsvTrajectoryPlanningHandle(&kCsvMode.traj);
    }

    kCsvMode.pre_Controlword = kCsvMode.now_Controlword;

    AppVelocityTargetReachedStateCheck();

    return APP_RET_RUNNING;
}

AppResult CsvModeStop(void)
{
    return APP_RET_SUCCESS;
}
