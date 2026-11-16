#include "Cia402_ObjectDictionary_Variable.h"

/* USER CODE BEGIN AREA 0 */
#include "cia402_fsm.h"
#include "coordinate_conversion.h"
#include "data_param.h"

#include "motor_ctl_loop.h"

//64位转32位，符号位处理
INTEGER32 limit_64_to_32(int64_t val_64)
{
    int32_t val_32 = val_64;
    if(val_64 & 0x8000000000000000){
        val_32 |= 0x80000000;
    }
    else {
        val_32 &= 0x7FFFFFFF;
    }
    return val_32;
}

/* USER CODE END AREA 0 */

PDS_FSA kPDS_FSA;
Factor_group kFactor_group;
Profile_position_mode kProfile_position_mode;
Homing_mode kHoming_mode;
Position_control_function kPosition_control_function;
Interpolated_position_mode kInterpolated_position_mode;
Profile_velocity_mode kProfile_velocity_mode;
Profile_torque_mode kProfile_torque_mode;
CSP_CSV_CST kCSP_CSV_CST;
Optional_application kOptional_application;

UNS32 set_Controlword(UNS16 val){
    /* USER CODE BEGIN set_Controlword 0 */
    /* USER CODE END set_Controlword 0 */
    kPDS_FSA.Controlword = val;
    /* USER CODE BEGIN set_Controlword 1 */
#ifdef USE_CIA402
    ControlwordChange_PDAS_FSA();//cia402的控制字只影响PDS_FSA的状态机
#endif // USE_CIA402
    /* USER CODE END set_Controlword 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS16 get_Controlword(void){
    /* USER CODE BEGIN get_Controlword */
    /* USER CODE END get_Controlword */
    return kPDS_FSA.Controlword;
}

UNS32 set_Statusword(UNS16 val){
    /* USER CODE BEGIN set_Statusword 0 */
    //cia402的控制字只能由PDS_FSA的状态机修改
    /* USER CODE END set_Statusword 0 */
    kPDS_FSA.Statusword = val;
    /* USER CODE BEGIN set_Statusword 1 */
    /* USER CODE END set_Statusword 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS16 get_Statusword(void){
    /* USER CODE BEGIN get_Statusword */
    /* USER CODE END get_Statusword */
    return kPDS_FSA.Statusword;
}

UNS32 set_Error_code(UNS16 val){
    /* USER CODE BEGIN set_Error_code 0 */
    //cia402的错误码只能由PDS_FSA的状态机修改
    /* USER CODE END set_Error_code 0 */
    kPDS_FSA.Error_code = val;
    /* USER CODE BEGIN set_Error_code 1 */
    /* USER CODE END set_Error_code 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS16 get_Error_code(void){
    /* USER CODE BEGIN get_Error_code */
    /* USER CODE END get_Error_code */
    return kPDS_FSA.Error_code;
}

UNS32 set_Quick_stop_option_code(INTEGER16 val){
    /* USER CODE BEGIN set_Quick_stop_option_code 0 */
    set_app_Quick_stop_option_code(val);
    /* USER CODE END set_Quick_stop_option_code 0 */
    kPDS_FSA.Quick_stop_option_code = val;
    /* USER CODE BEGIN set_Quick_stop_option_code 1 */
    /* USER CODE END set_Quick_stop_option_code 1 */
    return ABORT_CODE_SUCCESSFUL;
}
INTEGER16 get_Quick_stop_option_code(void){
    /* USER CODE BEGIN get_Quick_stop_option_code */
    kPDS_FSA.Quick_stop_option_code = get_app_Quick_stop_option_code(); 
    /* USER CODE END get_Quick_stop_option_code */
    return kPDS_FSA.Quick_stop_option_code;
}

UNS32 set_Modes_of_operation(INTEGER8 val){
    /* USER CODE BEGIN set_Modes_of_operation 0 */
    /* USER CODE END set_Modes_of_operation 0 */
    kPDS_FSA.Modes_of_operation = val;
    /* USER CODE BEGIN set_Modes_of_operation 1 */
    //目前支持的cia402模式:PP,PV,PT,HM,CSP,CSV,CST,MIT
    switch(kPDS_FSA.Modes_of_operation){
        case kOd6060_PPM:
            set_app_Modes_of_operation(MOTOR_CTL_SM_MODE_POSITION);
            break;
        case kOd6060_PVM:
            set_app_Modes_of_operation(MOTOR_CTL_SM_MODE_SPEED);
            break;
        case kOd6060_TPM:
            set_app_Modes_of_operation(MOTOR_CTL_SM_MODE_TORQUE);
            break;
        case kOd6060_HM:
            set_app_Modes_of_operation(MOTOR_CTL_SM_MODE_HOMING);
            break;
        case kOd6060_CSP:
            set_app_Modes_of_operation(MOTOR_CTL_SM_MODE_CSP);
            break;
        case kOd6060_CSV:
            set_app_Modes_of_operation(MOTOR_CTL_SM_MODE_CSV);
            break;
        case kOd6060_CST:
            set_app_Modes_of_operation(MOTOR_CTL_SM_MODE_CST);
            break;
        case kOd6060_MIT:
            set_app_Modes_of_operation(MOTOR_CTL_SM_MODE_MIT);
            break;
        default:
            break;
    }
    /* USER CODE END set_Modes_of_operation 1 */
    return ABORT_CODE_SUCCESSFUL;
}
INTEGER8 get_Modes_of_operation(void){
    /* USER CODE BEGIN get_Modes_of_operation */
    //目前支持的cia402模式:PP,PV,PT,HM,CSP,CSV,CST,MIT
    switch(get_app_Modes_of_operation()){
        case MOTOR_CTL_SM_MODE_POSITION:
            kPDS_FSA.Modes_of_operation = kOd6060_PPM;
            break;
        case MOTOR_CTL_SM_MODE_SPEED:
            kPDS_FSA.Modes_of_operation = kOd6060_PVM;
            break;
        case MOTOR_CTL_SM_MODE_TORQUE:
            kPDS_FSA.Modes_of_operation = kOd6060_TPM;
            break;
        case MOTOR_CTL_SM_MODE_HOMING:
            kPDS_FSA.Modes_of_operation = kOd6060_HM;
            break;
        case MOTOR_CTL_SM_MODE_CSP:
            kPDS_FSA.Modes_of_operation = kOd6060_CSP;
            break;
        case MOTOR_CTL_SM_MODE_CSV:
            kPDS_FSA.Modes_of_operation = kOd6060_CSV;
            break;
        case MOTOR_CTL_SM_MODE_CST:
            kPDS_FSA.Modes_of_operation = kOd6060_CST;
            break;
        case MOTOR_CTL_SM_MODE_MIT:
            kPDS_FSA.Modes_of_operation = kOd6060_MIT;
            break;
        default:
            break;
    }
    /* USER CODE END get_Modes_of_operation */
    return kPDS_FSA.Modes_of_operation;
}

UNS32 set_Modes_of_operation_display(INTEGER8 val){
    /* USER CODE BEGIN set_Modes_of_operation_display 0 */
    /* USER CODE END set_Modes_of_operation_display 0 */
    kPDS_FSA.Modes_of_operation_display = val;
    /* USER CODE BEGIN set_Modes_of_operation_display 1 */
    /* USER CODE END set_Modes_of_operation_display 1 */
    return ABORT_CODE_SUCCESSFUL;
}
INTEGER8 get_Modes_of_operation_display(void){
    /* USER CODE BEGIN get_Modes_of_operation_display */
    switch(get_app_Modes_of_operation_display()){
        case MOTOR_CTL_SM_MODE_POSITION:
            kPDS_FSA.Modes_of_operation_display = kOd6060_PPM;
            break;
        case MOTOR_CTL_SM_MODE_SPEED:
            kPDS_FSA.Modes_of_operation_display = kOd6060_PVM;
            break;
        case MOTOR_CTL_SM_MODE_TORQUE:
            kPDS_FSA.Modes_of_operation_display = kOd6060_TPM;
            break;
        case MOTOR_CTL_SM_MODE_HOMING:
            kPDS_FSA.Modes_of_operation_display = kOd6060_HM;
            break;
        case MOTOR_CTL_SM_MODE_CSP:
            kPDS_FSA.Modes_of_operation_display = kOd6060_CSP;
            break;
        case MOTOR_CTL_SM_MODE_CSV:
            kPDS_FSA.Modes_of_operation_display = kOd6060_CSV;
            break;
        case MOTOR_CTL_SM_MODE_CST:
            kPDS_FSA.Modes_of_operation_display = kOd6060_CST;
            break;
        case MOTOR_CTL_SM_MODE_MIT:
            kPDS_FSA.Modes_of_operation_display = kOd6060_MIT;
            break;
        default:
            break;
    }
    /* USER CODE END get_Modes_of_operation_display */
    return kPDS_FSA.Modes_of_operation_display;
}

UNS32 set_Position_encoder_resolution(UNS8 val){
    /* USER CODE BEGIN set_Position_encoder_resolution 0 */
    /* USER CODE END set_Position_encoder_resolution 0 */
    kFactor_group.Position_encoder_resolution = val;
    /* USER CODE BEGIN set_Position_encoder_resolution 1 */
    /* USER CODE END set_Position_encoder_resolution 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS8 get_Position_encoder_resolution(void){
    /* USER CODE BEGIN get_Position_encoder_resolution */
    /* USER CODE END get_Position_encoder_resolution */
    return kFactor_group.Position_encoder_resolution;
}

UNS32 set_Position_encoder_resolution_Encoder_increments(UNS32 val){
    /* USER CODE BEGIN set_Position_encoder_resolution_Encoder_increments 0 */
    /* USER CODE END set_Position_encoder_resolution_Encoder_increments 0 */
    kFactor_group.Position_encoder_resolution_Encoder_increments = val;
    /* USER CODE BEGIN set_Position_encoder_resolution_Encoder_increments 1 */
    set_app_Load_encoder_resolution(val);   //设置负载端编码器分辨率
    /* USER CODE END set_Position_encoder_resolution_Encoder_increments 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 get_Position_encoder_resolution_Encoder_increments(void){
    /* USER CODE BEGIN get_Position_encoder_resolution_Encoder_increments */
    kFactor_group.Position_encoder_resolution_Encoder_increments = get_app_Load_encoder_resolution();
    /* USER CODE END get_Position_encoder_resolution_Encoder_increments */
    return kFactor_group.Position_encoder_resolution_Encoder_increments;
}

UNS32 set_Position_encoder_resolution_Motor_revolutions(UNS32 val){
    /* USER CODE BEGIN set_Position_encoder_resolution_Motor_revolutions 0 */
    /* USER CODE END set_Position_encoder_resolution_Motor_revolutions 0 */
    kFactor_group.Position_encoder_resolution_Motor_revolutions = val;
    /* USER CODE BEGIN set_Position_encoder_resolution_Motor_revolutions 1 */
    set_app_Motor_encoder_resolution(val);  //设置电机端编码器分辨率
    /* USER CODE END set_Position_encoder_resolution_Motor_revolutions 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 get_Position_encoder_resolution_Motor_revolutions(void){
    /* USER CODE BEGIN get_Position_encoder_resolution_Motor_revolutions */
    kFactor_group.Position_encoder_resolution_Motor_revolutions = get_app_Motor_encoder_resolution();
    /* USER CODE END get_Position_encoder_resolution_Motor_revolutions */
    return kFactor_group.Position_encoder_resolution_Motor_revolutions;
}

UNS32 set_Gear_ratio(UNS8 val){
    /* USER CODE BEGIN set_Gear_ratio 0 */
    /* USER CODE END set_Gear_ratio 0 */
    kFactor_group.Gear_ratio = val;
    /* USER CODE BEGIN set_Gear_ratio 1 */
    /* USER CODE END set_Gear_ratio 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS8 get_Gear_ratio(void){
    /* USER CODE BEGIN get_Gear_ratio */
    /* USER CODE END get_Gear_ratio */
    return kFactor_group.Gear_ratio;
}

UNS32 set_Motor_revolutions(UNS32 val){
    /* USER CODE BEGIN set_Motor_revolutions 0 */
    /* USER CODE END set_Motor_revolutions 0 */
    kFactor_group.Motor_revolutions = val;
    /* USER CODE BEGIN set_Motor_revolutions 1 */
    //电子齿轮比分母
    set_app_Reduction_ratio_den(val);
    /* USER CODE END set_Motor_revolutions 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 get_Motor_revolutions(void){
    /* USER CODE BEGIN get_Motor_revolutions */
    kFactor_group.Motor_revolutions = get_app_Reduction_ratio_den();
    /* USER CODE END get_Motor_revolutions */
    return kFactor_group.Motor_revolutions;
}

UNS32 set_Shaft_revolutions(UNS32 val){
    /* USER CODE BEGIN set_Shaft_revolutions 0 */
    /* USER CODE END set_Shaft_revolutions 0 */
    kFactor_group.Shaft_revolutions = val;
    /* USER CODE BEGIN set_Shaft_revolutions 1 */
    //电子齿轮比分子
    set_app_Reduction_ratio_num(val);
    /* USER CODE END set_Shaft_revolutions 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 get_Shaft_revolutions(void){
    /* USER CODE BEGIN get_Shaft_revolutions */
    kFactor_group.Shaft_revolutions = get_app_Reduction_ratio_num();
    /* USER CODE END get_Shaft_revolutions */
    return kFactor_group.Shaft_revolutions;
}

UNS32 set_Polarity(UNS8 val){
    /* USER CODE BEGIN set_Polarity 0 */
    /* USER CODE END set_Polarity 0 */
    kFactor_group.Polarity = val;
    /* USER CODE BEGIN set_Polarity 1 */
    set_app_Polarity(val);
    /* USER CODE END set_Polarity 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS8 get_Polarity(void){
    /* USER CODE BEGIN get_Polarity */
    kFactor_group.Polarity = get_app_Polarity();
    /* USER CODE END get_Polarity */
    return kFactor_group.Polarity;
}

UNS32 set_Target_position(INTEGER32 val){
    /* USER CODE BEGIN set_Target_position 0 */
    /* USER CODE END set_Target_position 0 */
    kProfile_position_mode.Target_position = val;
    /* USER CODE BEGIN set_Target_position 1 */
    set_app_Target_position(val);
    /* USER CODE END set_Target_position 1 */
    return ABORT_CODE_SUCCESSFUL;
}
INTEGER32 get_Target_position(void){
    /* USER CODE BEGIN get_Target_position */
    kProfile_position_mode.Target_position = get_app_Target_position();
    /* USER CODE END get_Target_position */
    return kProfile_position_mode.Target_position;
}

UNS32 set_Position_range_limit(UNS8 val){
    /* USER CODE BEGIN set_Position_range_limit 0 */
    /* USER CODE END set_Position_range_limit 0 */
    kProfile_position_mode.Position_range_limit = val;
    /* USER CODE BEGIN set_Position_range_limit 1 */
    /* USER CODE END set_Position_range_limit 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS8 get_Position_range_limit(void){
    /* USER CODE BEGIN get_Position_range_limit */
    /* USER CODE END get_Position_range_limit */
    return kProfile_position_mode.Position_range_limit;
}

UNS32 set_Position_range_limit_Minimal_position_limit(INTEGER32 val){
    /* USER CODE BEGIN set_Position_range_limit_Minimal_position_limit 0 */
    /* USER CODE END set_Position_range_limit_Minimal_position_limit 0 */
    kProfile_position_mode.Position_range_limit_Minimal_position_limit = val;
    /* USER CODE BEGIN set_Position_range_limit_Minimal_position_limit 1 */
    set_app_Position_range_limit_Minimal_position_limit(val);
    /* USER CODE END set_Position_range_limit_Minimal_position_limit 1 */
    return ABORT_CODE_SUCCESSFUL;
}
INTEGER32 get_Position_range_limit_Minimal_position_limit(void){
    /* USER CODE BEGIN get_Position_range_limit_Minimal_position_limit */
    kProfile_position_mode.Position_range_limit_Minimal_position_limit = limit_64_to_32(get_app_Position_range_limit_Minimal_position_limit());
    /* USER CODE END get_Position_range_limit_Minimal_position_limit */
    return kProfile_position_mode.Position_range_limit_Minimal_position_limit;
}

UNS32 set_Position_range_limit_Maximal_position_limit(INTEGER32 val){
    /* USER CODE BEGIN set_Position_range_limit_Maximal_position_limit 0 */
    /* USER CODE END set_Position_range_limit_Maximal_position_limit 0 */
    kProfile_position_mode.Position_range_limit_Maximal_position_limit = val;
    /* USER CODE BEGIN set_Position_range_limit_Maximal_position_limit 1 */
    set_app_Position_range_limit_Maximal_position_limit(val);
    /* USER CODE END set_Position_range_limit_Maximal_position_limit 1 */
    return ABORT_CODE_SUCCESSFUL;
}
INTEGER32 get_Position_range_limit_Maximal_position_limit(void){
    /* USER CODE BEGIN get_Position_range_limit_Maximal_position_limit */
    kProfile_position_mode.Position_range_limit_Maximal_position_limit = limit_64_to_32(get_app_Position_range_limit_Maximal_position_limit());
    /* USER CODE END get_Position_range_limit_Maximal_position_limit */
    return kProfile_position_mode.Position_range_limit_Maximal_position_limit;
}

UNS32 set_Software_position_limit(UNS8 val){
    /* USER CODE BEGIN set_Software_position_limit 0 */
    /* USER CODE END set_Software_position_limit 0 */
    kProfile_position_mode.Software_position_limit = val;
    /* USER CODE BEGIN set_Software_position_limit 1 */
    /* USER CODE END set_Software_position_limit 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS8 get_Software_position_limit(void){
    /* USER CODE BEGIN get_Software_position_limit */
    /* USER CODE END get_Software_position_limit */
    return kProfile_position_mode.Software_position_limit;
}

UNS32 set_Software_position_limit_Minimal_position_limit(INTEGER32 val){
    /* USER CODE BEGIN set_Software_position_limit_Minimal_position_limit 0 */
    /* USER CODE END set_Software_position_limit_Minimal_position_limit 0 */
    kProfile_position_mode.Software_position_limit_Minimal_position_limit = val;
    /* USER CODE BEGIN set_Software_position_limit_Minimal_position_limit 1 */
    set_app_Software_position_limit_Minimal_position_limit(val);
    /* USER CODE END set_Software_position_limit_Minimal_position_limit 1 */
    return ABORT_CODE_SUCCESSFUL;
}
INTEGER32 get_Software_position_limit_Minimal_position_limit(void){
    /* USER CODE BEGIN get_Software_position_limit_Minimal_position_limit */
    kProfile_position_mode.Software_position_limit_Minimal_position_limit = limit_64_to_32(get_app_Software_position_limit_Minimal_position_limit());
    /* USER CODE END get_Software_position_limit_Minimal_position_limit */
    return kProfile_position_mode.Software_position_limit_Minimal_position_limit;
}

UNS32 set_Software_position_limit_Maximal_position_limit(INTEGER32 val){
    /* USER CODE BEGIN set_Software_position_limit_Maximal_position_limit 0 */
    /* USER CODE END set_Software_position_limit_Maximal_position_limit 0 */
    kProfile_position_mode.Software_position_limit_Maximal_position_limit = val;
    /* USER CODE BEGIN set_Software_position_limit_Maximal_position_limit 1 */
    set_app_Software_position_limit_Maximal_position_limit(val);
    /* USER CODE END set_Software_position_limit_Maximal_position_limit 1 */
    return ABORT_CODE_SUCCESSFUL;
}
INTEGER32 get_Software_position_limit_Maximal_position_limit(void){
    /* USER CODE BEGIN get_Software_position_limit_Maximal_position_limit */
    kProfile_position_mode.Software_position_limit_Maximal_position_limit = limit_64_to_32(get_app_Software_position_limit_Maximal_position_limit());
    /* USER CODE END get_Software_position_limit_Maximal_position_limit */
    return kProfile_position_mode.Software_position_limit_Maximal_position_limit;
}

UNS32 set_Max_profile_velocity(UNS32 val){
    /* USER CODE BEGIN set_Max_profile_velocity 0 */
    /* USER CODE END set_Max_profile_velocity 0 */
    kProfile_position_mode.Max_profile_velocity = val;
    /* USER CODE BEGIN set_Max_profile_velocity 1 */
    // P/s转RPM
    set_app_Max_profile_velocity((float)val * get_app_Load_pps_2_rpm());
    /* USER CODE END set_Max_profile_velocity 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 get_Max_profile_velocity(void){
    /* USER CODE BEGIN get_Max_profile_velocity */
    kProfile_position_mode.Max_profile_velocity = get_app_Max_profile_velocity() * get_app_Load_rpm_2_pps();
    /* USER CODE END get_Max_profile_velocity */
    return kProfile_position_mode.Max_profile_velocity;
}

UNS32 set_Max_motor_speed(UNS32 val){
    /* USER CODE BEGIN set_Max_motor_speed 0 */
    /* USER CODE END set_Max_motor_speed 0 */
    kProfile_position_mode.Max_motor_speed = val;
    /* USER CODE BEGIN set_Max_motor_speed 1 */
    set_app_Max_motor_speed((float)val);
    /* USER CODE END set_Max_motor_speed 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 get_Max_motor_speed(void){
    /* USER CODE BEGIN get_Max_motor_speed */
    kProfile_position_mode.Max_motor_speed = get_app_Max_motor_speed();
    /* USER CODE END get_Max_motor_speed */
    return kProfile_position_mode.Max_motor_speed;
}

UNS32 set_Profile_velocity(UNS32 val){
    /* USER CODE BEGIN set_Profile_velocity 0 */
    /* USER CODE END set_Profile_velocity 0 */
    kProfile_position_mode.Profile_velocity = val;
    /* USER CODE BEGIN set_Profile_velocity 1 */
    // P/s转RPM
    set_app_Profile_velocity((float)val * get_app_Load_pps_2_rpm());
    /* USER CODE END set_Profile_velocity 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 get_Profile_velocity(void){
    /* USER CODE BEGIN get_Profile_velocity */
    kProfile_position_mode.Profile_velocity = get_app_Profile_velocity() * get_app_Load_rpm_2_pps();
    /* USER CODE END get_Profile_velocity */
    return kProfile_position_mode.Profile_velocity;
}

UNS32 set_Profile_acceleration(UNS32 val){
    /* USER CODE BEGIN set_Profile_acceleration 0 */
    /* USER CODE END set_Profile_acceleration 0 */
    kProfile_position_mode.Profile_acceleration = val;
    /* USER CODE BEGIN set_Profile_acceleration 1 */
    // P/s/s转RPM/s
    set_app_Profile_acceleration((float)val * get_app_Load_pps_2_rpm());
    /* USER CODE END set_Profile_acceleration 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 get_Profile_acceleration(void){
    /* USER CODE BEGIN get_Profile_acceleration */
    kProfile_position_mode.Profile_acceleration = get_app_Profile_acceleration() * get_app_Load_rpm_2_pps();
    /* USER CODE END get_Profile_acceleration */
    return kProfile_position_mode.Profile_acceleration;
}

UNS32 set_Profile_deceleration(UNS32 val){
    /* USER CODE BEGIN set_Profile_deceleration 0 */
    /* USER CODE END set_Profile_deceleration 0 */
    kProfile_position_mode.Profile_deceleration = val;
    /* USER CODE BEGIN set_Profile_deceleration 1 */
    // P/s/s转RPM/s
    set_app_Profile_deceleration((float)val * get_app_Load_pps_2_rpm());
    /* USER CODE END set_Profile_deceleration 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 get_Profile_deceleration(void){
    /* USER CODE BEGIN get_Profile_deceleration */
    kProfile_position_mode.Profile_deceleration = get_app_Profile_deceleration() * get_app_Load_rpm_2_pps();
    /* USER CODE END get_Profile_deceleration */
    return kProfile_position_mode.Profile_deceleration;
}

UNS32 set_Quick_stop_deceleration(UNS32 val){
    /* USER CODE BEGIN set_Quick_stop_deceleration 0 */
    /* USER CODE END set_Quick_stop_deceleration 0 */
    kProfile_position_mode.Quick_stop_deceleration = val;
    /* USER CODE BEGIN set_Quick_stop_deceleration 1 */
    // P/s/s转RPM/s
    set_app_Quick_stop_deceleration((float)val * get_app_Load_pps_2_rpm());
    /* USER CODE END set_Quick_stop_deceleration 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 get_Quick_stop_deceleration(void){
    /* USER CODE BEGIN get_Quick_stop_deceleration */
    kProfile_position_mode.Quick_stop_deceleration = get_app_Quick_stop_deceleration() * get_app_Load_rpm_2_pps();
    /* USER CODE END get_Quick_stop_deceleration */
    return kProfile_position_mode.Quick_stop_deceleration;
}

UNS32 set_Max_acceleration(UNS32 val){
    /* USER CODE BEGIN set_Max_acceleration 0 */
    /* USER CODE END set_Max_acceleration 0 */
    kProfile_position_mode.Max_acceleration = val;
    /* USER CODE BEGIN set_Max_acceleration 1 */
    // P/s/s转RPM/s
    set_app_Max_acceleration((float)val * get_app_Load_pps_2_rpm());
    /* USER CODE END set_Max_acceleration 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 get_Max_acceleration(void){
    /* USER CODE BEGIN get_Max_acceleration */
    kProfile_position_mode.Max_acceleration = get_app_Max_acceleration() * get_app_Load_rpm_2_pps();
    /* USER CODE END get_Max_acceleration */
    return kProfile_position_mode.Max_acceleration;
}

UNS32 set_Max_deceleration(UNS32 val){
    /* USER CODE BEGIN set_Max_deceleration 0 */
    /* USER CODE END set_Max_deceleration 0 */
    kProfile_position_mode.Max_deceleration = val;
    /* USER CODE BEGIN set_Max_deceleration 1 */
    // P/s/s转RPM/s
    set_app_Max_deceleration((float)val * get_app_Load_pps_2_rpm());
    /* USER CODE END set_Max_deceleration 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 get_Max_deceleration(void){
    /* USER CODE BEGIN get_Max_deceleration */
    kProfile_position_mode.Max_deceleration = get_app_Max_deceleration() * get_app_Load_rpm_2_pps();
    /* USER CODE END get_Max_deceleration */
    return kProfile_position_mode.Max_deceleration;
}

UNS32 set_Home_offset(INTEGER32 val){
    /* USER CODE BEGIN set_Home_offset 0 */
    /* USER CODE END set_Home_offset 0 */
    kHoming_mode.Home_offset = val;
    /* USER CODE BEGIN set_Home_offset 1 */
    set_app_Home_offset(val);
    /* USER CODE END set_Home_offset 1 */
    return ABORT_CODE_SUCCESSFUL;
}
INTEGER32 get_Home_offset(void){
    /* USER CODE BEGIN get_Home_offset */
    kHoming_mode.Home_offset = get_app_Home_offset();
    /* USER CODE END get_Home_offset */
    return kHoming_mode.Home_offset;
}

UNS32 set_Homing_method(INTEGER8 val){
    /* USER CODE BEGIN set_Homing_method 0 */
    /* USER CODE END set_Homing_method 0 */
    kHoming_mode.Homing_method = val;
    /* USER CODE BEGIN set_Homing_method 1 */
    set_app_Homing_method(val);
    /* USER CODE END set_Homing_method 1 */
    return ABORT_CODE_SUCCESSFUL;
}
INTEGER8 get_Homing_method(void){
    /* USER CODE BEGIN get_Homing_method */
    kHoming_mode.Homing_method = get_app_Homing_method();
    /* USER CODE END get_Homing_method */
    return kHoming_mode.Homing_method;
}

UNS32 set_Homing_speeds(UNS8 val){
    /* USER CODE BEGIN set_Homing_speeds 0 */
    /* USER CODE END set_Homing_speeds 0 */
    kHoming_mode.Homing_speeds = val;
    /* USER CODE BEGIN set_Homing_speeds 1 */
    /* USER CODE END set_Homing_speeds 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS8 get_Homing_speeds(void){
    /* USER CODE BEGIN get_Homing_speeds */
    /* USER CODE END get_Homing_speeds */
    return kHoming_mode.Homing_speeds;
}

UNS32 set_Homing_speeds_Speed_for_switch_search(UNS32 val){
    /* USER CODE BEGIN set_Homing_speeds_Speed_for_switch_search 0 */
    /* USER CODE END set_Homing_speeds_Speed_for_switch_search 0 */
    kHoming_mode.Homing_speeds_Speed_for_switch_search = val;
    /* USER CODE BEGIN set_Homing_speeds_Speed_for_switch_search 1 */
    // P/s转RPM
    set_app_Homing_speed_search_for_switch((float)val * get_app_Load_pps_2_rpm());
    /* USER CODE END set_Homing_speeds_Speed_for_switch_search 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 get_Homing_speeds_Speed_for_switch_search(void){
    /* USER CODE BEGIN get_Homing_speeds_Speed_for_switch_search */
    // RPM转P/s
    kHoming_mode.Homing_speeds_Speed_for_switch_search = get_app_Homing_speed_search_for_switch() * get_app_Load_rpm_2_pps();
    /* USER CODE END get_Homing_speeds_Speed_for_switch_search */
    return kHoming_mode.Homing_speeds_Speed_for_switch_search;
}

UNS32 set_Homing_speeds_Speed_for_zero_search(UNS32 val){
    /* USER CODE BEGIN set_Homing_speeds_Speed_for_zero_search 0 */
    /* USER CODE END set_Homing_speeds_Speed_for_zero_search 0 */
    kHoming_mode.Homing_speeds_Speed_for_zero_search = val;
    /* USER CODE BEGIN set_Homing_speeds_Speed_for_zero_search 1 */
    // P/s转RPM
    set_app_Homing_speed_search_for_zero((float)val * get_app_Load_pps_2_rpm());
    /* USER CODE END set_Homing_speeds_Speed_for_zero_search 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 get_Homing_speeds_Speed_for_zero_search(void){
    /* USER CODE BEGIN get_Homing_speeds_Speed_for_zero_search */
    // RPM转P/s
    kHoming_mode.Homing_speeds_Speed_for_zero_search = get_app_Homing_speed_search_for_zero() * get_app_Load_rpm_2_pps();
    /* USER CODE END get_Homing_speeds_Speed_for_zero_search */
    return kHoming_mode.Homing_speeds_Speed_for_zero_search;
}

UNS32 set_Homing_acceleration(UNS32 val){
    /* USER CODE BEGIN set_Homing_acceleration 0 */
    /* USER CODE END set_Homing_acceleration 0 */
    kHoming_mode.Homing_acceleration = val;
    /* USER CODE BEGIN set_Homing_acceleration 1 */
    // P/s/s转RPM/s
    set_app_Homing_acceleration((float)val * get_app_Load_pps_2_rpm());
    /* USER CODE END set_Homing_acceleration 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 get_Homing_acceleration(void){
    /* USER CODE BEGIN get_Homing_acceleration */
    // RPM/s/s转P/s/s
    kHoming_mode.Homing_acceleration = get_app_Homing_acceleration() * get_app_Load_rpm_2_pps();
    /* USER CODE END get_Homing_acceleration */
    return kHoming_mode.Homing_acceleration;
}

UNS32 set_Position_demand_value(INTEGER32 val){
    /* USER CODE BEGIN set_Position_demand_value 0 */
    /* USER CODE END set_Position_demand_value 0 */
    kPosition_control_function.Position_demand_value = val;
    /* USER CODE BEGIN set_Position_demand_value 1 */
    /* USER CODE END set_Position_demand_value 1 */
    return ABORT_CODE_SUCCESSFUL;
}
INTEGER32 get_Position_demand_value(void){
    /* USER CODE BEGIN get_Position_demand_value */
    kPosition_control_function.Position_demand_value = get_app_Position_demand_value();
    /* USER CODE END get_Position_demand_value */
    return kPosition_control_function.Position_demand_value;
}

UNS32 set_Position_actual_value_inc(INTEGER32 val){
    /* USER CODE BEGIN set_Position_actual_value_inc 0 */
    /* USER CODE END set_Position_actual_value_inc 0 */
    kPosition_control_function.Position_actual_value_inc = val;
    /* USER CODE BEGIN set_Position_actual_value_inc 1 */
    /* USER CODE END set_Position_actual_value_inc 1 */
    return ABORT_CODE_SUCCESSFUL;
}
INTEGER32 get_Position_actual_value_inc(void){
    /* USER CODE BEGIN get_Position_actual_value_inc */
    kPosition_control_function.Position_actual_value_inc = get_app_Position_actual_value_inc();
    /* USER CODE END get_Position_actual_value_inc */
    return kPosition_control_function.Position_actual_value_inc;
}

UNS32 set_Position_actual_value(INTEGER32 val){
    /* USER CODE BEGIN set_Position_actual_value 0 */
    /* USER CODE END set_Position_actual_value 0 */
    kPosition_control_function.Position_actual_value = val;
    /* USER CODE BEGIN set_Position_actual_value 1 */
    /* USER CODE END set_Position_actual_value 1 */
    return ABORT_CODE_SUCCESSFUL;
}
INTEGER32 get_Position_actual_value(void){
    /* USER CODE BEGIN get_Position_actual_value */
    kPosition_control_function.Position_actual_value = get_app_Position_actual_value();
    /* USER CODE END get_Position_actual_value */
    return kPosition_control_function.Position_actual_value;
}

UNS32 set_Following_error_window(UNS32 val){
    /* USER CODE BEGIN set_Following_error_window 0 */
    set_app_Following_error_window(val);
    /* USER CODE END set_Following_error_window 0 */
    kPosition_control_function.Following_error_window = val;
    /* USER CODE BEGIN set_Following_error_window 1 */
    /* USER CODE END set_Following_error_window 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 get_Following_error_window(void){
    /* USER CODE BEGIN get_Following_error_window */
    kPosition_control_function.Following_error_window = get_app_Following_error_window();
    /* USER CODE END get_Following_error_window */
    return kPosition_control_function.Following_error_window;
}

UNS32 set_Following_error_time_out(UNS16 val){
    /* USER CODE BEGIN set_Following_error_time_out 0 */
    /* USER CODE END set_Following_error_time_out 0 */
    kPosition_control_function.Following_error_time_out = val;
    /* USER CODE BEGIN set_Following_error_time_out 1 */
    set_app_Following_error_time_out((float)val * 0.001f);
    /* USER CODE END set_Following_error_time_out 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS16 get_Following_error_time_out(void){
    /* USER CODE BEGIN get_Following_error_time_out */
    kPosition_control_function.Following_error_time_out = get_app_Following_error_time_out() * 1000;
    /* USER CODE END get_Following_error_time_out */
    return kPosition_control_function.Following_error_time_out;
}

UNS32 set_Position_window(UNS32 val){
    /* USER CODE BEGIN set_Position_window 0 */
    set_app_Position_window(val);
    /* USER CODE END set_Position_window 0 */
    kPosition_control_function.Position_window = val;
    /* USER CODE BEGIN set_Position_window 1 */
    /* USER CODE END set_Position_window 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 get_Position_window(void){
    /* USER CODE BEGIN get_Position_window */
    kPosition_control_function.Position_window = get_app_Position_window();
    /* USER CODE END get_Position_window */
    return kPosition_control_function.Position_window;
}

UNS32 set_Position_window_time(UNS16 val){
    /* USER CODE BEGIN set_Position_window_time 0 */
    set_app_Position_window_time((float)val * 0.001f);
    /* USER CODE END set_Position_window_time 0 */
    kPosition_control_function.Position_window_time = val;
    /* USER CODE BEGIN set_Position_window_time 1 */
    /* USER CODE END set_Position_window_time 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS16 get_Position_window_time(void){
    /* USER CODE BEGIN get_Position_window_time */
    kPosition_control_function.Position_window_time = get_app_Position_window_time() * 1000;
    /* USER CODE END get_Position_window_time */
    return kPosition_control_function.Position_window_time;
}

UNS32 set_Following_error_actual_value(INTEGER32 val){
    /* USER CODE BEGIN set_Following_error_actual_value 0 */
    /* USER CODE END set_Following_error_actual_value 0 */
    kPosition_control_function.Following_error_actual_value = val;
    /* USER CODE BEGIN set_Following_error_actual_value 1 */
    /* USER CODE END set_Following_error_actual_value 1 */
    return ABORT_CODE_SUCCESSFUL;
}
INTEGER32 get_Following_error_actual_value(void){
    /* USER CODE BEGIN get_Following_error_actual_value */
    kPosition_control_function.Following_error_actual_value = get_app_Following_error_actual_value();
    /* USER CODE END get_Following_error_actual_value */
    return kPosition_control_function.Following_error_actual_value;
}

UNS32 set_Interpolation_time_period(UNS8 val){
    /* USER CODE BEGIN set_Interpolation_time_period 0 */
    /* USER CODE END set_Interpolation_time_period 0 */
    kInterpolated_position_mode.Interpolation_time_period = val;
    /* USER CODE BEGIN set_Interpolation_time_period 1 */
    /* USER CODE END set_Interpolation_time_period 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS8 get_Interpolation_time_period(void){
    /* USER CODE BEGIN get_Interpolation_time_period */
    /* USER CODE END get_Interpolation_time_period */
    return kInterpolated_position_mode.Interpolation_time_period;
}

UNS32 set_Interpolation_time_period_Ip_time_units(UNS8 val){
    /* USER CODE BEGIN set_Interpolation_time_period_Ip_time_units 0 */
    /* USER CODE END set_Interpolation_time_period_Ip_time_units 0 */
    kInterpolated_position_mode.Interpolation_time_period_Ip_time_units = val;
    /* USER CODE BEGIN set_Interpolation_time_period_Ip_time_units 1 */
    set_app_Interp_time_value(val);
    /* USER CODE END set_Interpolation_time_period_Ip_time_units 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS8 get_Interpolation_time_period_Ip_time_units(void){
    /* USER CODE BEGIN get_Interpolation_time_period_Ip_time_units */
    /* USER CODE END get_Interpolation_time_period_Ip_time_units */
    return kInterpolated_position_mode.Interpolation_time_period_Ip_time_units;
}

UNS32 set_Interpolation_time_period_Ip_time_index(INTEGER8 val){
    /* USER CODE BEGIN set_Interpolation_time_period_Ip_time_index 0 */
    /* USER CODE END set_Interpolation_time_period_Ip_time_index 0 */
    kInterpolated_position_mode.Interpolation_time_period_Ip_time_index = val;
    /* USER CODE BEGIN set_Interpolation_time_period_Ip_time_index 1 */
    set_app_Interp_time_index(val);
    /* USER CODE END set_Interpolation_time_period_Ip_time_index 1 */
    return ABORT_CODE_SUCCESSFUL;
}
INTEGER8 get_Interpolation_time_period_Ip_time_index(void){
    /* USER CODE BEGIN get_Interpolation_time_period_Ip_time_index */
    /* USER CODE END get_Interpolation_time_period_Ip_time_index */
    return kInterpolated_position_mode.Interpolation_time_period_Ip_time_index;
}

UNS32 set_Velocity_demand_value(INTEGER32 val){
    /* USER CODE BEGIN set_Velocity_demand_value 0 */
    /* USER CODE END set_Velocity_demand_value 0 */
    kProfile_velocity_mode.Velocity_demand_value = val;
    /* USER CODE BEGIN set_Velocity_demand_value 1 */
    /* USER CODE END set_Velocity_demand_value 1 */
    return ABORT_CODE_SUCCESSFUL;
}
INTEGER32 get_Velocity_demand_value(void){
    /* USER CODE BEGIN get_Velocity_demand_value */
    // RPM 转 P/s
    kProfile_velocity_mode.Velocity_demand_value = get_app_Velocity_demand_value() * get_app_Load_rpm_2_pps();
    /* USER CODE END get_Velocity_demand_value */
    return kProfile_velocity_mode.Velocity_demand_value;
}

UNS32 set_Velocity_actual_value(INTEGER32 val){
    /* USER CODE BEGIN set_Velocity_actual_value 0 */
    /* USER CODE END set_Velocity_actual_value 0 */
    kProfile_velocity_mode.Velocity_actual_value = val;
    /* USER CODE BEGIN set_Velocity_actual_value 1 */
    /* USER CODE END set_Velocity_actual_value 1 */
    return ABORT_CODE_SUCCESSFUL;
}
INTEGER32 get_Velocity_actual_value(void){
    /* USER CODE BEGIN get_Velocity_actual_value */
    // P/s 转 RPM
    kProfile_velocity_mode.Velocity_actual_value = get_app_Velocity_actual_value() * get_app_Load_rpm_2_pps();
    /* USER CODE END get_Velocity_actual_value */
    return kProfile_velocity_mode.Velocity_actual_value;
}

UNS32 set_Velocity_window(UNS16 val){
    /* USER CODE BEGIN set_Velocity_window 0 */
    // P/s转RPM
    set_app_Velocity_window((float)val * get_app_Load_pps_2_rpm());
    /* USER CODE END set_Velocity_window 0 */
    kProfile_velocity_mode.Velocity_window = val;
    /* USER CODE BEGIN set_Velocity_window 1 */
    /* USER CODE END set_Velocity_window 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS16 get_Velocity_window(void){
    /* USER CODE BEGIN get_Velocity_window */
    kProfile_velocity_mode.Velocity_window = get_app_Velocity_window() * get_app_Load_rpm_2_pps();
    /* USER CODE END get_Velocity_window */
    return kProfile_velocity_mode.Velocity_window;
}

UNS32 set_Velocity_window_time(UNS16 val){
    /* USER CODE BEGIN set_Velocity_window_time 0 */
    set_app_Velocity_window_time((float)val * 0.001f);
    /* USER CODE END set_Velocity_window_time 0 */
    kProfile_velocity_mode.Velocity_window_time = val;
    /* USER CODE BEGIN set_Velocity_window_time 1 */
    /* USER CODE END set_Velocity_window_time 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS16 get_Velocity_window_time(void){
    /* USER CODE BEGIN get_Velocity_window_time */
    kProfile_velocity_mode.Velocity_window_time = get_app_Velocity_window_time() * 1000;
    /* USER CODE END get_Velocity_window_time */
    return kProfile_velocity_mode.Velocity_window_time;
}

UNS32 set_Velocity_threshold(UNS16 val){
    /* USER CODE BEGIN set_Velocity_threshold 0 */
    // P/s转RPM
    set_app_Velocity_threshold((float)val * get_app_Load_pps_2_rpm());
    /* USER CODE END set_Velocity_threshold 0 */
    kProfile_velocity_mode.Velocity_threshold = val;
    /* USER CODE BEGIN set_Velocity_threshold 1 */
    /* USER CODE END set_Velocity_threshold 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS16 get_Velocity_threshold(void){
    /* USER CODE BEGIN get_Velocity_threshold */
    kProfile_velocity_mode.Velocity_threshold = get_app_Velocity_threshold() * get_app_Load_rpm_2_pps();
    /* USER CODE END get_Velocity_threshold */
    return kProfile_velocity_mode.Velocity_threshold;
}

UNS32 set_Velocity_threshold_time(UNS16 val){
    /* USER CODE BEGIN set_Velocity_threshold_time 0 */
    set_app_Velocity_threshold_time((float)val * 0.001f);
    /* USER CODE END set_Velocity_threshold_time 0 */
    kProfile_velocity_mode.Velocity_threshold_time = val;
    /* USER CODE BEGIN set_Velocity_threshold_time 1 */
    /* USER CODE END set_Velocity_threshold_time 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS16 get_Velocity_threshold_time(void){
    /* USER CODE BEGIN get_Velocity_threshold_time */
    kProfile_velocity_mode.Velocity_threshold_time = get_app_Velocity_threshold_time() * 1000;
    /* USER CODE END get_Velocity_threshold_time */
    return kProfile_velocity_mode.Velocity_threshold_time;
}

UNS32 set_Target_velocity(INTEGER32 val){
    /* USER CODE BEGIN set_Target_velocity 0 */
    /* USER CODE END set_Target_velocity 0 */
    kProfile_velocity_mode.Target_velocity = val;
    /* USER CODE BEGIN set_Target_velocity 1 */
    // P/s 转 RPM
    set_app_Target_velocity((float)val * get_app_Load_pps_2_rpm());
    /* USER CODE END set_Target_velocity 1 */
    return ABORT_CODE_SUCCESSFUL;
}
INTEGER32 get_Target_velocity(void){
    /* USER CODE BEGIN get_Target_velocity */
    // RPM 转 P/s
    kProfile_velocity_mode.Target_velocity = get_app_Target_velocity() * get_app_Load_rpm_2_pps();
    /* USER CODE END get_Target_velocity */
    return kProfile_velocity_mode.Target_velocity;
}

UNS32 set_Target_torque(INTEGER16 val){
    /* USER CODE BEGIN set_Target_torque 0 */
    /* USER CODE END set_Target_torque 0 */
    kProfile_torque_mode.Target_torque = val;
    /* USER CODE BEGIN set_Target_torque 1 */
    // 额定电流千分比转实际电流
    set_app_Target_torque((float)val * get_app_Motor_rated_current() * MATH_ARMS2APEAK * 0.001f);
    /* USER CODE END set_Target_torque 1 */
    return ABORT_CODE_SUCCESSFUL;
}
INTEGER16 get_Target_torque(void){
    /* USER CODE BEGIN get_Target_torque */
    kProfile_torque_mode.Target_torque = get_app_Target_torque() * 1000 / (get_app_Motor_rated_current() * MATH_ARMS2APEAK);
    /* USER CODE END get_Target_torque */
    return kProfile_torque_mode.Target_torque;
}

UNS32 set_Max_torque(UNS16 val){
    /* USER CODE BEGIN set_Max_torque 0 */
    /* USER CODE END set_Max_torque 0 */
    kProfile_torque_mode.Max_torque = val;
    /* USER CODE BEGIN set_Max_torque 1 */
    // 额定电流千分比转实际电流
    set_app_Max_current((float)val * get_app_Motor_rated_current() * MATH_ARMS2APEAK * 0.001f);
    /* USER CODE END set_Max_torque 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS16 get_Max_torque(void){
    /* USER CODE BEGIN get_Max_torque */
    kProfile_torque_mode.Max_torque = get_app_Max_current() * 1000 / (get_app_Motor_rated_current() * MATH_ARMS2APEAK);
    /* USER CODE END get_Max_torque */
    return kProfile_torque_mode.Max_torque;
}

UNS32 set_Max_current(UNS16 val){
    /* USER CODE BEGIN set_Max_current 0 */
    /* USER CODE END set_Max_current 0 */
    kProfile_torque_mode.Max_current = val;
    /* USER CODE BEGIN set_Max_current 1 */
    set_app_Max_current((float)val * get_app_Motor_rated_current() * MATH_ARMS2APEAK * 0.001f);
    /* USER CODE END set_Max_current 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS16 get_Max_current(void){
    /* USER CODE BEGIN get_Max_current */
    kProfile_torque_mode.Max_current = get_app_Max_current() * 1000 / (get_app_Motor_rated_current() * MATH_ARMS2APEAK);
    /* USER CODE END get_Max_current */
    return kProfile_torque_mode.Max_current;
}

UNS32 set_Torque_demand_value(INTEGER16 val){
    /* USER CODE BEGIN set_Torque_demand_value 0 */
    /* USER CODE END set_Torque_demand_value 0 */
    kProfile_torque_mode.Torque_demand_value = val;
    /* USER CODE BEGIN set_Torque_demand_value 1 */
    /* USER CODE END set_Torque_demand_value 1 */
    return ABORT_CODE_SUCCESSFUL;
}
INTEGER16 get_Torque_demand_value(void){
    /* USER CODE BEGIN get_Torque_demand_value */
    kProfile_torque_mode.Torque_demand_value = get_app_Torque_demand_value() * 1000 / (get_app_Motor_rated_current() * MATH_ARMS2APEAK);
    /* USER CODE END get_Torque_demand_value */
    return kProfile_torque_mode.Torque_demand_value;
}

UNS32 set_Motor_rated_current(UNS32 val){
    /* USER CODE BEGIN set_Motor_rated_current 0 */
    /* USER CODE END set_Motor_rated_current 0 */
    kProfile_torque_mode.Motor_rated_current = val;
    /* USER CODE BEGIN set_Motor_rated_current 1 */
    set_app_Motor_rated_current((float)val * 0.001f);
    /* USER CODE END set_Motor_rated_current 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 get_Motor_rated_current(void){
    /* USER CODE BEGIN get_Motor_rated_current */
    kProfile_torque_mode.Motor_rated_current = get_app_Motor_rated_current() * 1000;
    /* USER CODE END get_Motor_rated_current */
    return kProfile_torque_mode.Motor_rated_current;
}

UNS32 set_Motor_rated_torque(UNS32 val){
    /* USER CODE BEGIN set_Motor_rated_torque 0 */
    /* USER CODE END set_Motor_rated_torque 0 */
    kProfile_torque_mode.Motor_rated_torque = val;
    /* USER CODE BEGIN set_Motor_rated_torque 1 */
    // mNm 转 Nm
    set_app_Motor_rated_torque((float)val * 0.001f);
    /* USER CODE END set_Motor_rated_torque 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 get_Motor_rated_torque(void){
    /* USER CODE BEGIN get_Motor_rated_torque */
    kProfile_torque_mode.Motor_rated_torque = get_app_Motor_rated_torque() * 1000;
    /* USER CODE END get_Motor_rated_torque */
    return kProfile_torque_mode.Motor_rated_torque;
}

UNS32 set_Torque_actual_value(INTEGER16 val){
    /* USER CODE BEGIN set_Torque_actual_value 0 */
    /* USER CODE END set_Torque_actual_value 0 */
    kProfile_torque_mode.Torque_actual_value = val;
    /* USER CODE BEGIN set_Torque_actual_value 1 */
    /* USER CODE END set_Torque_actual_value 1 */
    return ABORT_CODE_SUCCESSFUL;
}
INTEGER16 get_Torque_actual_value(void){
    /* USER CODE BEGIN get_Torque_actual_value */
    // 实际力矩转为额定力矩千分比
    kProfile_torque_mode.Torque_actual_value = get_app_Current_actual_value() * 1000 \
                                                / (get_app_Motor_rated_current() * MATH_ARMS2APEAK);
    /* USER CODE END get_Torque_actual_value */
    return kProfile_torque_mode.Torque_actual_value;
}

UNS32 set_Current_actual_value(INTEGER16 val){
    /* USER CODE BEGIN set_Current_actual_value 0 */
    /* USER CODE END set_Current_actual_value 0 */
    kProfile_torque_mode.Current_actual_value = val;
    /* USER CODE BEGIN set_Current_actual_value 1 */
    /* USER CODE END set_Current_actual_value 1 */
    return ABORT_CODE_SUCCESSFUL;
}
INTEGER16 get_Current_actual_value(void){
    /* USER CODE BEGIN get_Current_actual_value */
    kProfile_torque_mode.Current_actual_value = get_app_Current_actual_value() * 1000 \
                                                / (get_app_Motor_rated_current() * MATH_ARMS2APEAK);
    /* USER CODE END get_Current_actual_value */
    return kProfile_torque_mode.Current_actual_value;
}

UNS32 set_DC_link_circuit_voltage(UNS32 val){
    /* USER CODE BEGIN set_DC_link_circuit_voltage 0 */
    /* USER CODE END set_DC_link_circuit_voltage 0 */
    kProfile_torque_mode.DC_link_circuit_voltage = val;
    /* USER CODE BEGIN set_DC_link_circuit_voltage 1 */
    /* USER CODE END set_DC_link_circuit_voltage 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 get_DC_link_circuit_voltage(void){
    /* USER CODE BEGIN get_DC_link_circuit_voltage */
    kProfile_torque_mode.DC_link_circuit_voltage = get_app_DC_link_circuit_voltage() * 1000;
    /* USER CODE END get_DC_link_circuit_voltage */
    return kProfile_torque_mode.DC_link_circuit_voltage;
}

UNS32 set_Torque_slope(UNS32 val){
    /* USER CODE BEGIN set_Torque_slope 0 */
    /* USER CODE END set_Torque_slope 0 */
    kProfile_torque_mode.Torque_slope = val;
    /* USER CODE BEGIN set_Torque_slope 1 */
    // 千分比转电流
    set_app_Torque_slope((float)val * get_app_Motor_rated_current() * MATH_ARMS2APEAK * 0.001f);
    /* USER CODE END set_Torque_slope 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 get_Torque_slope(void){
    /* USER CODE BEGIN get_Torque_slope */
    kProfile_torque_mode.Torque_slope = get_app_Torque_slope() * 1000 / (get_app_Motor_rated_current() * MATH_ARMS2APEAK);
    /* USER CODE END get_Torque_slope */
    return kProfile_torque_mode.Torque_slope;
}

UNS32 set_Position_offset(INTEGER32 val){
    /* USER CODE BEGIN set_Position_offset 0 */
    /* USER CODE END set_Position_offset 0 */
    kCSP_CSV_CST.Position_offset = val;
    /* USER CODE BEGIN set_Position_offset 1 */
    /* USER CODE END set_Position_offset 1 */
    return ABORT_CODE_SUCCESSFUL;
}
INTEGER32 get_Position_offset(void){
    /* USER CODE BEGIN get_Position_offset */
    /* USER CODE END get_Position_offset */
    return kCSP_CSV_CST.Position_offset;
}

UNS32 set_Velocity_offset(INTEGER32 val){
    /* USER CODE BEGIN set_Velocity_offset 0 */
    /* USER CODE END set_Velocity_offset 0 */
    kCSP_CSV_CST.Velocity_offset = val;
    /* USER CODE BEGIN set_Velocity_offset 1 */
    /* USER CODE END set_Velocity_offset 1 */
    return ABORT_CODE_SUCCESSFUL;
}
INTEGER32 get_Velocity_offset(void){
    /* USER CODE BEGIN get_Velocity_offset */
    /* USER CODE END get_Velocity_offset */
    return kCSP_CSV_CST.Velocity_offset;
}

UNS32 set_Torque_offset(INTEGER16 val){
    /* USER CODE BEGIN set_Torque_offset 0 */
    /* USER CODE END set_Torque_offset 0 */
    kCSP_CSV_CST.Torque_offset = val;
    /* USER CODE BEGIN set_Torque_offset 1 */
    /* USER CODE END set_Torque_offset 1 */
    return ABORT_CODE_SUCCESSFUL;
}
INTEGER16 get_Torque_offset(void){
    /* USER CODE BEGIN get_Torque_offset */
    /* USER CODE END get_Torque_offset */
    return kCSP_CSV_CST.Torque_offset;
}

UNS32 set_Digital_inputs(UNS32 val){
    /* USER CODE BEGIN set_Digital_inputs 0 */
    /* USER CODE END set_Digital_inputs 0 */
    kOptional_application.Digital_inputs = val;
    /* USER CODE BEGIN set_Digital_inputs 1 */
    /* USER CODE END set_Digital_inputs 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 get_Digital_inputs(void){
    /* USER CODE BEGIN get_Digital_inputs */
    kOptional_application.Digital_inputs = get_app_Digital_io_inputs_status();
    /* USER CODE END get_Digital_inputs */
    return kOptional_application.Digital_inputs;
}

UNS32 set_Digital_outputs(UNS8 val){
    /* USER CODE BEGIN set_Digital_outputs 0 */
    /* USER CODE END set_Digital_outputs 0 */
    kOptional_application.Digital_outputs = val;
    /* USER CODE BEGIN set_Digital_outputs 1 */
    /* USER CODE END set_Digital_outputs 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS8 get_Digital_outputs(void){
    /* USER CODE BEGIN get_Digital_outputs */
    /* USER CODE END get_Digital_outputs */
    return kOptional_application.Digital_outputs;
}

UNS32 set_Digital_outputs_Physical_outputs(UNS32 val){
    /* USER CODE BEGIN set_Digital_outputs_Physical_outputs 0 */
    /* USER CODE END set_Digital_outputs_Physical_outputs 0 */
    kOptional_application.Digital_outputs_Physical_outputs = val;
    /* USER CODE BEGIN set_Digital_outputs_Physical_outputs 1 */
    set_app_Digital_io_outputs_phys(val);
    /* USER CODE END set_Digital_outputs_Physical_outputs 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 get_Digital_outputs_Physical_outputs(void){
    /* USER CODE BEGIN get_Digital_outputs_Physical_outputs */
    /* USER CODE END get_Digital_outputs_Physical_outputs */
    return kOptional_application.Digital_outputs_Physical_outputs;
}

UNS32 set_Digital_outputs_Bit_mask(UNS32 val){
    /* USER CODE BEGIN set_Digital_outputs_Bit_mask 0 */
    /* USER CODE END set_Digital_outputs_Bit_mask 0 */
    kOptional_application.Digital_outputs_Bit_mask = val;
    /* USER CODE BEGIN set_Digital_outputs_Bit_mask 1 */
    set_app_Digital_io_outputs_mask(val);
    /* USER CODE END set_Digital_outputs_Bit_mask 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 get_Digital_outputs_Bit_mask(void){
    /* USER CODE BEGIN get_Digital_outputs_Bit_mask */
    /* USER CODE END get_Digital_outputs_Bit_mask */
    return kOptional_application.Digital_outputs_Bit_mask;
}

