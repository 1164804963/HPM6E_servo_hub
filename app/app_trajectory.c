#include "app_trajectory.h"
#include "motor_ctl_loop.h"

static Axis *const axis = &kAxis;

pos_trajectory_planning_DW_f kPosTrajDw;
linear_trajectory_planning_DW_f kTorqueTrajDw;
linear_trajectory_planning_DW_f kSpeedTrajDw;

csp_planning_DW_f kCspTrajDw;
csv_planning_DW_f kCsvTrajDw;
cst_planning_DW_f kCstTrajDw;

// 轮廓位置轨迹规划器初始化
void PosTrajectoryPlanningInit(void)
{
    memset(&kPosTrajDw, 0, sizeof(kPosTrajDw));

    // 初始化当前规划器 为当前速度  当前位置
    kPosTrajDw.q0_int = axis->pos_speed_ctl_input.pos_now_p;
    kPosTrajDw.x = axis->pos_speed_ctl_input.pos_now_p;
    kPosTrajDw.q0_dec = 0;
    kPosTrajDw.dq0 = axis->pos_speed_ctl_input.speed_now_rad_s /
                     MOTOR_CTL_SM_TWO_PI * axis->pmsm_config.enc_line_p_n; // 从当前速度开始规划  p/s
}

// 轮廓位置轨迹规划器处理函数
void PosTrajectoryPlanningHandle(POS_TRAJECTORY_DATA *pos_traj_data)
{
    int8_T state_now = 0;
    pos_traj_data->period_s = axis->pmsm_config.tp_s;

    pos_trajectory_planning(&pos_traj_data->pos_tar_p,
                            &pos_traj_data->profile_speed,
                            &pos_traj_data->profile_acc,
                            &pos_traj_data->profile_dec,
                            &pos_traj_data->period_s,
                            &axis->input_shaping_input.pos_cmd_p,
                            &pos_traj_data->pos_out_dec_p,
                            &axis->pos_speed_ctl_input.speed_tar_p_s,
                            &axis->pos_speed_ctl_input.acc_tar_p_ss,
                            &state_now, &kPosTrajDw);
}

// 轮廓速度轨迹规划器初始化
void SpeedTrajectoryPlanningInit(void)
{
    memset(&kSpeedTrajDw, 0, sizeof(kSpeedTrajDw));
    kSpeedTrajDw.traj_now = axis->pos_speed_ctl_input.speed_now_rad_s /
                            MOTOR_CTL_SM_TWO_PI * axis->pmsm_config.enc_line_p_n; // 从当前速度开始规划  p/s
}

// 速度轨迹规划器处理函数
void SpeedTrajectoryPlanningHandle(SPEED_TRAJECTORY_DATA *speed_traj_data)
{
    int8_T state_now = 0;
    speed_traj_data->period_s = axis->pmsm_config.tp_s;

    linear_trajectory_planning(&speed_traj_data->speed_tar_p,
                               &speed_traj_data->acc,
                               &speed_traj_data->period_s,
                               &axis->pos_speed_ctl_input.speed_tar_p_s,
                               &state_now, &(kSpeedTrajDw));
}

// 轮廓转矩轨迹规划器初始化
void TorqueTrajectoryPlanningInit(void)
{
    memset(&kTorqueTrajDw, 0, sizeof(kTorqueTrajDw));
    // 初始化当前规划器 为当前 q轴电流
    kTorqueTrajDw.traj_now = axis->current_ctl_output.idq_now_A[1];
}

// 转矩轨迹规划器处理函数
void TorqueTrajectoryPlanningHandle(TORQUE_TRAJECTORY_DATA *torque_traj_data)
{
    int8_T state_now = 0;
    torque_traj_data->period_s = axis->pmsm_config.tp_s;

    linear_trajectory_planning(&torque_traj_data->torque_tar,
                               &torque_traj_data->slope,
                               &torque_traj_data->period_s,
                               &axis->current_ctl_input.idq_tar_A[1],
                               &state_now, &(kTorqueTrajDw));
}

// MIT模式轨迹规划器初始化
void MitTrajectoryPlanningInit(MIT_TRAJECTORY_DATA *mit_traj_data)
{
    axis->mit_ctl_input.iq_max_A = mit_traj_data->iq_max_A;
}

// MIT模式轨迹规划器处理函数
void MitTrajectoryPlanningHandle(MIT_TRAJECTORY_DATA *mit_traj_data)
{
    axis->mit_ctl_input.pos_tar_p = mit_traj_data->pos_tar_p;
    axis->mit_ctl_input.speed_tar_p_s = mit_traj_data->speed_tar_p_s;
    axis->mit_ctl_input.tq_set_NM = mit_traj_data->tq_set_NM;
    axis->mit_ctl_input.iq_max_A = mit_traj_data->iq_max_A;

    axis->mit_ctl_config.kp_pos_NM_rad = mit_traj_data->kp_pos_NM_rad;
    axis->mit_ctl_config.kd_spd_NM_rad_s = mit_traj_data->kd_spd_NM_rad_s;
}

// 周期同步位置模式轨迹规划器初始化
void CspTrajectoryPlanningInit(void)
{
    memset(&kCspTrajDw, 0, sizeof(kCspTrajDw));

    csp_planning_Init(&kCspTrajDw); // 初始化规划器
}

// 周期同步位置模式轨迹规划器处理函数
void CspTrajectoryPlanningHandle(CSP_TRAJECTORY_DATA *csp_traj_data)
{
    csp_traj_data->period_s = axis->pmsm_config.tp_s;

    if (csp_traj_data->is_update_tar)
    {
        csp_traj_data->is_update_tar = false;
        kCspTrajDw.x0_sum = 0.0f; // 从0时刻开始规划
    }

    csp_planning(csp_traj_data->pos_tar_buff_p,
                 &csp_traj_data->ip_dt_s,
                 &csp_traj_data->period_s,
                 &axis->input_shaping_input.pos_cmd_p,
                 &axis->pos_speed_ctl_input.speed_tar_p_s,
                 &axis->pos_speed_ctl_input.acc_tar_p_ss,
                 &kCspTrajDw);
}

// 周期同步速度模式轨迹规划器初始化
void CsvTrajectoryPlanningInit(void)
{
    memset(&kCsvTrajDw, 0, sizeof(kCsvTrajDw));

    csv_planning_Init(&kCsvTrajDw); // 初始化规划器
}

// 周期同步速度模式轨迹规划器处理函数
void CsvTrajectoryPlanningHandle(CSV_TRAJECTORY_DATA *csv_traj_data)
{
    csv_traj_data->period_s = axis->pmsm_config.tp_s;

    if (csv_traj_data->is_update_tar)
    {
        csv_traj_data->is_update_tar = false;
        kCsvTrajDw.x0_sum = 0.0f; // 从0时刻开始规划
    }

    csv_planning(csv_traj_data->speed_tar_buff_p_s,
                 &csv_traj_data->ip_dt_s,
                 &csv_traj_data->period_s,
                 &axis->pos_speed_ctl_input.speed_tar_p_s,
                 &axis->pos_speed_ctl_input.acc_tar_p_ss,
                 &kCsvTrajDw);
}

// 周期同步转矩模式轨迹规划器初始化
void CstTrajectoryPlanningInit(void)
{
    memset(&kCstTrajDw, 0, sizeof(kCstTrajDw));

    cst_planning_Init(&kCstTrajDw); // 初始化规划器
}

// 周期同步转矩模式轨迹规划器处理函数
void CstTrajectoryPlanningHandle(CST_TRAJECTORY_DATA *cst_traj_data)
{
    cst_traj_data->period_s = axis->pmsm_config.tp_s;

    if (cst_traj_data->is_update_tar)
    {
        cst_traj_data->is_update_tar = false;
        kCstTrajDw.x0_sum = 0.0f; // 从0时刻开始规划
    }

    cst_planning(cst_traj_data->torque_tar_buff_A,
                 &cst_traj_data->ip_dt_s,
                 &cst_traj_data->period_s,
                 &axis->current_ctl_input.idq_tar_A[1],
                 &kCstTrajDw);
}
