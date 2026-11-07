#include "app_cyclic_sync_position_mode.h"

static CspMode_t kCspMode =
{
    .now_Controlword = APP_CTRL_DISABLE,
    .pre_Controlword = APP_CTRL_DISABLE,
    .traj = {
        .is_update_tar = false,
        .pos_tar_buff_p[0] = 0,
        .pos_tar_buff_p[1] = 0,
        .pos_tar_buff_p[2] = 0,
        .pos_tar_buff_p[3] = 0,
        .ip_dt_s = 0,
        .period_s = 0,
    },
    .check_status_val.all = 0,
    .emergency_brake_mode = EMERGENCY_BRAKE_MODE_DISABLED,
    .pos_tar_last_p = 0,
    .pos_tar_add_p = 0,
    .pos_tar_p = 0,
};

AppResult CspModeInit(void)
{
    AppPositionTargetReachedStateClear(); // 清除目标到达标志
    set_app_Target_update_state(false); // 清除目标更新状态值
    set_app_Controlword(APP_CTRL_DISABLE); // 上升沿使能，初始化置0
    kCspMode.pre_Controlword = APP_CTRL_DISABLE;
    kCspMode.pos_tar_last_p = get_app_Position_actual_value();

    kCspMode.pos_tar_p = get_app_Motor_position_actual_value();
    kCspMode.traj.pos_tar_buff_p[0] = kCspMode.pos_tar_p;
    kCspMode.traj.pos_tar_buff_p[1] = kCspMode.traj.pos_tar_buff_p[0];
    kCspMode.traj.pos_tar_buff_p[2] = kCspMode.traj.pos_tar_buff_p[0];
    kCspMode.traj.pos_tar_buff_p[3] = kCspMode.traj.pos_tar_buff_p[0];

    kCspMode.traj.ip_dt_s = get_app_Interp_period();
    kCspMode.traj.is_update_tar = true;

    return APP_RET_SUCCESS;
}

AppResult CspModeStart(void)
{
    return APP_RET_SUCCESS;
}

AppResult CspModeRun(void)
{
    kCspMode.now_Controlword = (APP_CONTROL_WORD)get_app_Controlword();

    uint8_t load_enc_type = bsp_get_encoder_type(ENCODER_ID_LOAD);  //获取负载端编码器类型
    int64_t home_offset = get_app_Home_position_offset_value();     //获取存储的回零内部偏移值

    if (kCspMode.now_Controlword == APP_CTRL_ENABLE)
    {
        if (!get_app_Emergency_brake_requested())
        {
            if (kCspMode.pre_Controlword == APP_CTRL_DISABLE)
            {
                // 重新使能后初始化规划器
                CspTrajectoryPlanningInit();

                kCspMode.pos_tar_last_p = get_app_Position_actual_value(); // 目标位置 等于 当前位置
                kCspMode.pos_tar_p = get_app_Motor_position_actual_value();

                kCspMode.traj.pos_tar_buff_p[0] = kCspMode.pos_tar_p;
                kCspMode.traj.pos_tar_buff_p[1] = kCspMode.traj.pos_tar_buff_p[0];
                kCspMode.traj.pos_tar_buff_p[2] = kCspMode.traj.pos_tar_buff_p[0];
                kCspMode.traj.pos_tar_buff_p[3] = kCspMode.traj.pos_tar_buff_p[0];
                kCspMode.traj.ip_dt_s = get_app_Interp_period();

                kCspMode.traj.is_update_tar = true;
            }

            // 更新目标位置条件: 1. 目标更新状态为真 2. 抱闸状态为松闸
            if ((bool)get_app_Target_update_state() == true && get_app_Brake_state() == BRAKE_STATE_RELEASED)
            {
                set_app_Target_update_state(false);

                kCspMode.pos_tar_last_p = get_app_Target_position();

                kCspMode.pos_tar_add_p = (float)(kCspMode.pos_tar_last_p - get_app_Position_actual_value()) * \
                                         get_app_Reduction_ratio() * get_app_P_load_2_motor();

                if(load_enc_type == 0x00) //负载端无编码器 目标位置进行绝对位置控制
                {
                    if (get_app_Reduction_ratio_num() == 1) //减速比1:1  直接以电机端编码器位置为反馈
                    {
                        kCspMode.pos_tar_p = kCspMode.pos_tar_last_p + home_offset;
                    }
                    else //减速比大于1  以负载端位置为参考进行绝对位置控制
                    {
                        kCspMode.pos_tar_p = PosUnitLoadToMotor(kCspMode.pos_tar_last_p + home_offset);
                    }
                }
                else  //负载端有编码器 目标位置进行相对位置控制
                {
                    kCspMode.pos_tar_p = kCspMode.pos_tar_add_p + get_app_Motor_position_actual_value(); //  转化到内环目标位置
                }


                kCspMode.traj.pos_tar_buff_p[0] = kCspMode.traj.pos_tar_buff_p[1];
                kCspMode.traj.pos_tar_buff_p[1] = kCspMode.traj.pos_tar_buff_p[2];
                kCspMode.traj.pos_tar_buff_p[2] = kCspMode.traj.pos_tar_buff_p[3];
                kCspMode.traj.pos_tar_buff_p[3] = kCspMode.pos_tar_p;

                kCspMode.traj.is_update_tar = true;
            }
        }
        else
        {
            set_app_Controlword(APP_CTRL_EMERGENCY_BRAKE); // 强制进入紧急停车（QuickStop）状态
            kCspMode.now_Controlword = APP_CTRL_EMERGENCY_BRAKE;
        }
    }

    // 紧急停车（QuickStop）处理
    if (kCspMode.now_Controlword == APP_CTRL_EMERGENCY_BRAKE)
    {
        kCspMode.emergency_brake_mode = get_app_Quick_stop_option_code();

        kCspMode.traj.pos_tar_buff_p[0] = kCspMode.traj.pos_tar_buff_p[1];
        kCspMode.traj.pos_tar_buff_p[1] = kCspMode.traj.pos_tar_buff_p[2];
        kCspMode.traj.pos_tar_buff_p[2] = kCspMode.traj.pos_tar_buff_p[3];
        kCspMode.traj.pos_tar_buff_p[3] = kCspMode.pos_tar_p;

        // 在急停后失能电机模式下，检测到零速后电机失能
        if (kCspMode.emergency_brake_mode <= EMERGENCY_BRAKE_MODE_VOLTAGE_LIMIT)
        {
            kCspMode.check_status_val = (CheckStatusVal_t)app_get_check_status_val();
            if (kCspMode.emergency_brake_mode == EMERGENCY_BRAKE_MODE_DISABLED ||\
                kCspMode.check_status_val.bits.velocity_zero == true)
            {
                set_app_Controlword(APP_CTRL_DISABLE);
                kCspMode.now_Controlword = APP_CTRL_DISABLE;
            }
        }
    }

    if (kCspMode.now_Controlword != APP_CTRL_DISABLE)
    {
        CspTrajectoryPlanningHandle(&kCspMode.traj);
    }

    kCspMode.pre_Controlword = kCspMode.now_Controlword;

    AppPositionTargetReachedStateCheck();

    return APP_RET_RUNNING;
}

AppResult CspModeStop(void)
{
    return APP_RET_SUCCESS;
}
