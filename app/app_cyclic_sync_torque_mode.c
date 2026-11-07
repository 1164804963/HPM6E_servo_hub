#include "app_cyclic_sync_torque_mode.h"

static CstMode_t kCstMode =
{
    .now_Controlword = APP_CTRL_DISABLE,
    .pre_Controlword = APP_CTRL_DISABLE,
    .traj = {
        .is_update_tar = false,
        .torque_tar_buff_A[0] = 0,
        .torque_tar_buff_A[1] = 0,
        .torque_tar_buff_A[2] = 0,
        .torque_tar_buff_A[3] = 0,
        .ip_dt_s = 0,
        .period_s = 0,
    },
    .check_status_val.all = 0,
    .emergency_brake_mode = EMERGENCY_BRAKE_MODE_DISABLED,
};

AppResult CstModeInit(void)
{
    AppTargetTorqueReachedStateClear();
    set_app_Target_update_state(false); // 清除目标更新状态值
    set_app_Controlword(APP_CTRL_DISABLE); // 上升沿使能，初始化置0
    kCstMode.pre_Controlword = APP_CTRL_DISABLE;

    kCstMode.traj.torque_tar_buff_A[0] = get_app_Torque_actual_value();
    kCstMode.traj.torque_tar_buff_A[1] = kCstMode.traj.torque_tar_buff_A[0];
    kCstMode.traj.torque_tar_buff_A[2] = kCstMode.traj.torque_tar_buff_A[0];
    kCstMode.traj.torque_tar_buff_A[3] = kCstMode.traj.torque_tar_buff_A[0];

    kCstMode.traj.ip_dt_s = get_app_Interp_period();
    kCstMode.traj.is_update_tar = true;

    return APP_RET_SUCCESS;
}

AppResult CstModeStart(void)
{
    return APP_RET_SUCCESS;
}

AppResult CstModeRun(void)
{
    kCstMode.now_Controlword = (APP_CONTROL_WORD)get_app_Controlword();

    if (kCstMode.now_Controlword == APP_CTRL_ENABLE)
    {
        if (!get_app_Emergency_brake_requested())
        {
            if (kCstMode.pre_Controlword == APP_CTRL_DISABLE)
            {
                // 重新使能后初始化规划器
                CstTrajectoryPlanningInit();

                kCstMode.traj.torque_tar_buff_A[0] = get_app_Torque_actual_value();
                kCstMode.traj.torque_tar_buff_A[1] = kCstMode.traj.torque_tar_buff_A[0];
                kCstMode.traj.torque_tar_buff_A[2] = kCstMode.traj.torque_tar_buff_A[0];
                kCstMode.traj.torque_tar_buff_A[3] = kCstMode.traj.torque_tar_buff_A[0];
                kCstMode.traj.ip_dt_s = get_app_Interp_period();

                kCstMode.traj.is_update_tar = true;
            }

            // 更新目标力矩条件: 1. 目标更新状态为真 2. 抱闸状态为松闸
            if ((bool)get_app_Target_update_state() == true && get_app_Brake_state() == BRAKE_STATE_RELEASED)
            {
                set_app_Target_update_state(false);

                kCstMode.traj.torque_tar_buff_A[0] = kCstMode.traj.torque_tar_buff_A[1];
                kCstMode.traj.torque_tar_buff_A[1] = kCstMode.traj.torque_tar_buff_A[2];
                kCstMode.traj.torque_tar_buff_A[2] = kCstMode.traj.torque_tar_buff_A[3];
                kCstMode.traj.torque_tar_buff_A[3] = get_app_Target_torque();

                kCstMode.traj.is_update_tar = true;
            }
        }
        else
        {
            set_app_Controlword(APP_CTRL_EMERGENCY_BRAKE); // 强制进入紧急停车（QuickStop）状态
            kCstMode.now_Controlword = APP_CTRL_EMERGENCY_BRAKE;
        }
    }

    // 紧急停车（QuickStop）处理
    if (kCstMode.now_Controlword == APP_CTRL_EMERGENCY_BRAKE)
    {
        kCstMode.emergency_brake_mode = get_app_Quick_stop_option_code();

        kCstMode.traj.torque_tar_buff_A[0] = kCstMode.traj.torque_tar_buff_A[1];
        kCstMode.traj.torque_tar_buff_A[1] = kCstMode.traj.torque_tar_buff_A[2];
        kCstMode.traj.torque_tar_buff_A[2] = kCstMode.traj.torque_tar_buff_A[3];
        kCstMode.traj.torque_tar_buff_A[3] = get_app_Target_torque();

        // 在急停后失能电机模式下，直接电机失能
        if (kCstMode.emergency_brake_mode <= EMERGENCY_BRAKE_MODE_VOLTAGE_LIMIT)
        {
            set_app_Controlword(APP_CTRL_DISABLE);
            kCstMode.now_Controlword = APP_CTRL_DISABLE;
        }
    }

    if (kCstMode.now_Controlword != APP_CTRL_DISABLE)
    {
        CstTrajectoryPlanningHandle(&kCstMode.traj);
    }

    kCstMode.pre_Controlword = kCstMode.now_Controlword;

    AppTargetTorqueReachedStateCheck();

    return APP_RET_RUNNING;
}

AppResult CstModeStop(void)
{
    return APP_RET_SUCCESS;
}
