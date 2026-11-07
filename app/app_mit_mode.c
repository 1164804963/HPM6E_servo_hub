#include "app_mit_mode.h"

static MitMode_t kMitMode =
{
    .now_Controlword = APP_CTRL_DISABLE,
    .pre_Controlword = APP_CTRL_DISABLE,
    .traj =
    {
        .kp_pos_NM_rad = 0,
        .kd_spd_NM_rad_s = 0,
        .iq_max_A = 0,
        .speed_tar_p_s = 0,
        .pos_tar_p = 0,
        .tq_set_NM = 0,
    },
    .check_status_val.all = 0,
    .emergency_brake_mode = EMERGENCY_BRAKE_MODE_DISABLED,
    .pos_tar_p_add = 0,
};

AppResult MitModeInit(void)
{
    set_app_Controlword(APP_CTRL_DISABLE); // 上升沿使能，初始化置0
    kMitMode.pre_Controlword = APP_CTRL_DISABLE;

    return APP_RET_SUCCESS;
}

AppResult MitModeStart(void)
{
    return APP_RET_SUCCESS;
}

AppResult MitModeRun(void)
{
    kMitMode.now_Controlword = (APP_CONTROL_WORD)get_app_Controlword();

    if (kMitMode.now_Controlword == APP_CTRL_ENABLE)
    {
        if (!get_app_Emergency_brake_requested())
        {
            if (kMitMode.pre_Controlword == APP_CTRL_DISABLE)
            {
                // 重新使能后初始化规划器
                kMitMode.traj.iq_max_A = get_app_MIT_max_current();
                MitTrajectoryPlanningInit(&kMitMode.traj);
            }

            // 规划速度为0的情况：1. 暂停指令生效 2. 抱闸状态不为松闸
            if (get_app_Halt_running_cmd() == true || get_app_Brake_state() != BRAKE_STATE_RELEASED)
            {
                kMitMode.traj.pos_tar_p = get_app_Motor_position_actual_value();
                kMitMode.traj.speed_tar_p_s = 0;
            }
            else
            {
                kMitMode.pos_tar_p_add = (float)(get_app_MIT_target_position() - get_app_Position_actual_value()) *
                                         get_app_Reduction_ratio() * get_app_P_load_2_motor();
                kMitMode.traj.pos_tar_p = kMitMode.pos_tar_p_add + get_app_Motor_position_actual_value();

                kMitMode.traj.speed_tar_p_s = get_app_MIT_target_velocity() * get_app_Motor_rpm_2_pps() *
                                              get_app_Reduction_ratio();
            }

            kMitMode.traj.iq_max_A = get_app_MIT_max_current();
            kMitMode.traj.tq_set_NM = get_app_MIT_feedforward_torque() * get_app_Reduction_ratio_inv(); // 负载端转矩  转化 为电机端
            kMitMode.traj.kp_pos_NM_rad = get_app_MIT_kp() * get_app_Reduction_ratio_inv();             // 转化为电机端增益
            kMitMode.traj.kd_spd_NM_rad_s = get_app_MIT_kd() * get_app_Reduction_ratio_inv();           // 转化为电机端增益
        }
        else
        {
            set_app_Controlword(APP_CTRL_EMERGENCY_BRAKE); // 强制进入紧急停车（QuickStop）状态
            kMitMode.now_Controlword = APP_CTRL_EMERGENCY_BRAKE;
        }
    }

    // 紧急停车（QuickStop）处理
    if (kMitMode.now_Controlword == APP_CTRL_EMERGENCY_BRAKE)
    {
        kMitMode.traj.pos_tar_p = get_app_Motor_position_actual_value();
        kMitMode.traj.speed_tar_p_s = 0; // 如果处于急停状态，规划速度为0

        kMitMode.emergency_brake_mode = get_app_Quick_stop_option_code();
        // 在急停后失能电机模式下，检测到零速后电机失能
        if (kMitMode.emergency_brake_mode <= EMERGENCY_BRAKE_MODE_VOLTAGE_LIMIT)
        {
            kMitMode.check_status_val = (CheckStatusVal_t)app_get_check_status_val();
            if (kMitMode.emergency_brake_mode == EMERGENCY_BRAKE_MODE_DISABLED ||
                kMitMode.check_status_val.bits.velocity_zero == true)
            {
                set_app_Controlword(APP_CTRL_DISABLE);
                kMitMode.now_Controlword = APP_CTRL_DISABLE;
            }
        }
    }

    if (kMitMode.now_Controlword != APP_CTRL_DISABLE)
    {
        MitTrajectoryPlanningHandle(&kMitMode.traj);
    }

    kMitMode.pre_Controlword = kMitMode.now_Controlword;

    return APP_RET_RUNNING;
}

AppResult MitModeStop(void)
{
    return APP_RET_SUCCESS;
}
