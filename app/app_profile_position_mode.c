#include "app_profile_position_mode.h"

static PpMode_t kPpMode =
{
    .now_Controlword = APP_CTRL_DISABLE,
    .pre_Controlword = APP_CTRL_DISABLE,
    .traj = {
        .pos_tar_p = 0,
        .profile_speed = 0,
        .profile_acc = 0,
        .profile_dec = 0,
        .period_s = 0,
        .pos_out_dec_p = 0,
    },
    .check_status_val.all = 0,
    .emergency_brake_mode = EMERGENCY_BRAKE_MODE_DISABLED,
    .start_upedge_latch = false,
    .start_upedge_state = false,
    .position_target_last = 0,
    .pos_tar_p_add = 0,
};

AppResult PpModeInit(void)
{
    AppPositionTargetReachedStateClear();  // 清除目标到达标志
    set_app_Controlword(APP_CTRL_DISABLE); // 上升沿使能，初始化置0
    kPpMode.pre_Controlword = APP_CTRL_DISABLE;
    kPpMode.start_upedge_latch = false;
    kPpMode.start_upedge_state = false;
    kPpMode.position_target_last = get_app_Position_actual_value();

    return APP_RET_SUCCESS;
}

AppResult PpModeStart(void)
{
    return APP_RET_SUCCESS;
}

AppResult PpModeRun(void)
{
    kPpMode.now_Controlword = (APP_CONTROL_WORD)get_app_Controlword();

    uint8_t load_enc_type = bsp_get_encoder_type(ENCODER_ID_LOAD);  //获取负载端编码器类型
    int64_t home_offset = get_app_Home_position_offset_value();     //获取存储的回零内部偏移值

    if (kPpMode.now_Controlword == APP_CTRL_ENABLE)
    {
        if (!get_app_Emergency_brake_requested())
        {
            if (kPpMode.pre_Controlword == APP_CTRL_DISABLE)
            {
                // 重新使能后初始化规划器
                PosTrajectoryPlanningInit();
                kPpMode.position_target_last = get_app_Position_actual_value(); // 目标位置 等于 当前位置
                kPpMode.traj.pos_tar_p = get_app_Motor_position_actual_value();
            }

            // 总线控制时pp模式下检测控制字bit4上升沿事件，或，非总线控制时bit4上升沿事件一直有效更新目标位置
            if (kPpMode.start_upedge_state == true ||
                (APP_COMM_CONTROL_AUTHORITY)get_app_Comm_control_authority() == COMM_CONTROL_HOST)
            {
                kPpMode.start_upedge_latch = true;
                kPpMode.start_upedge_state = false;
            }

            // 规划速度为0的情况：1. 暂停指令生效 2. 抱闸状态不为松闸
            if (get_app_Halt_running_cmd() == true || get_app_Brake_state() != BRAKE_STATE_RELEASED)
            {
                kPpMode.start_upedge_latch = false; // 暂停后重新使能
                kPpMode.traj.profile_speed = 0;     // 如果处于暂停状态，规划速度为0
            }
            else
            {
                kPpMode.traj.profile_speed = get_app_Profile_velocity() * get_app_Motor_rpm_2_pps() *
                                             get_app_Reduction_ratio();
            }

            // 设置规划器参数
            // 计算目标位置和当前位置差值
            if (true == kPpMode.start_upedge_latch)
            {
                kPpMode.start_upedge_latch = false;
                kPpMode.position_target_last = get_app_Target_position(); // 上升沿更新目标位置
            }

            kPpMode.pos_tar_p_add = (float)(kPpMode.position_target_last - get_app_Position_actual_value()) *
                                    get_app_Reduction_ratio() * get_app_P_load_2_motor();

#ifdef GEAR_BACKLASH_MOTOR_PULSE // 定义了齿轮间隙参数才会对间隙进行处理
            if (kPpMode.pos_tar_p_add < GEAR_BACKLASH_MOTOR_PULSE && kPpMode.pos_tar_p_add > -GEAR_BACKLASH_MOTOR_PULSE)
            {
                // 处理齿轮间隙
                kPpMode.traj.pos_tar_p = get_app_Motor_position_actual_value(); // 急停在当前位置 避免定位振动
                kPpMode.traj.profile_speed = 0;
                kPpMode.traj.profile_acc = 2e9f;
                kPpMode.traj.profile_dec = 2e9f;
            }
            else
            {
                kPpMode.traj.pos_tar_p = kPpMode.pos_tar_p_add + get_app_Motor_position_actual_value(); //  转化到内环目标位置

                kPpMode.traj.profile_acc = get_app_Profile_acceleration() * get_app_Motor_rpm_2_pps() *
                                           get_app_Reduction_ratio();
                kPpMode.traj.profile_dec = get_app_Profile_deceleration() * get_app_Motor_rpm_2_pps() *
                                           get_app_Reduction_ratio();
            }
#else
            if(load_enc_type == 0x00) //负载端无编码器 目标位置进行绝对位置控制
            {
                if (get_app_Reduction_ratio_num() == 1) //减速比1:1  直接以电机端编码器位置为反馈
                {
                    kPpMode.traj.pos_tar_p = kPpMode.position_target_last + home_offset;
                }
                else //减速比大于1  以负载端位置为参考进行绝对位置控制
                {
                    kPpMode.traj.pos_tar_p = PosUnitLoadToMotor(kPpMode.position_target_last + home_offset);;
                }
            }
            else  //负载端有编码器 目标位置进行相对位置控制
            {
                kPpMode.traj.pos_tar_p = kPpMode.pos_tar_p_add + get_app_Motor_position_actual_value(); //  转化到内环目标位置
            }

            kPpMode.traj.profile_acc = get_app_Profile_acceleration() * get_app_Motor_rpm_2_pps() *
                                       get_app_Reduction_ratio();
            kPpMode.traj.profile_dec = get_app_Profile_deceleration() * get_app_Motor_rpm_2_pps() *
                                       get_app_Reduction_ratio();

#endif
        }
        else
        {
            set_app_Controlword(APP_CTRL_EMERGENCY_BRAKE); // 强制进入紧急停车（QuickStop）状态
            kPpMode.now_Controlword = APP_CTRL_EMERGENCY_BRAKE;
        }
    }

    // 紧急停车（QuickStop）处理
    if (kPpMode.now_Controlword == APP_CTRL_EMERGENCY_BRAKE)
    {
        kPpMode.traj.profile_speed = 0; // 如果处于急停状态，规划速度为0

        kPpMode.emergency_brake_mode = get_app_Quick_stop_option_code();
        if (kPpMode.emergency_brake_mode == EMERGENCY_BRAKE_MODE_QUICK_STOP_RAMP ||
            kPpMode.emergency_brake_mode == EMERGENCY_BRAKE_MODE_QUICK_STOP_RAMP_ENABLE ||
            kPpMode.emergency_brake_mode == EMERGENCY_BRAKE_MODE_CURRENT_LIMIT ||
            kPpMode.emergency_brake_mode == EMERGENCY_BRAKE_MODE_CURRENT_LIMIT_ENABLE)
        {
            kPpMode.traj.profile_acc = get_app_Quick_stop_deceleration() * get_app_Motor_rpm_2_pps() *
                                       get_app_Reduction_ratio();
            kPpMode.traj.profile_dec = kPpMode.traj.profile_acc;
        }
        else if (kPpMode.emergency_brake_mode != EMERGENCY_BRAKE_MODE_DISABLED)
        {
            // TODO: 电压限制急停先不实现按正常减速斜率停机
            kPpMode.traj.profile_acc = get_app_Profile_acceleration() * get_app_Motor_rpm_2_pps() *
                                       get_app_Reduction_ratio();
            kPpMode.traj.profile_dec = get_app_Profile_deceleration() * get_app_Motor_rpm_2_pps() *
                                       get_app_Reduction_ratio();
        }
        // 在急停后失能电机模式下，检测到零速后电机失能
        if (kPpMode.emergency_brake_mode <= EMERGENCY_BRAKE_MODE_VOLTAGE_LIMIT)
        {
            kPpMode.check_status_val = (CheckStatusVal_t)app_get_check_status_val();
            if (kPpMode.emergency_brake_mode == EMERGENCY_BRAKE_MODE_DISABLED ||
                kPpMode.check_status_val.bits.velocity_zero == true)
            {
                set_app_Controlword(APP_CTRL_DISABLE);
                kPpMode.now_Controlword = APP_CTRL_DISABLE;
            }
        }
    }

    if (kPpMode.now_Controlword != APP_CTRL_DISABLE)
    {
        PosTrajectoryPlanningHandle(&kPpMode.traj);
    }

    kPpMode.pre_Controlword = kPpMode.now_Controlword;

    AppPositionTargetReachedStateCheck();

    return APP_RET_RUNNING;
}

AppResult PpModeStop(void)
{
    kPpMode.start_upedge_state = false;
    kPpMode.start_upedge_latch = false;

    return APP_RET_SUCCESS;
}

void set_app_start_upedge_state(bool state)
{
    kPpMode.start_upedge_state = state;
}
