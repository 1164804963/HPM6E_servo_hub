#include "app_store_param.h"
#include "motor_ctl_loop.h"
/* USER CODE BEGIN AREA 0 */

/* USER CODE END AREA 0 */

FLASH_PARAM_STRUCT kFlashStorage;

void flash_param_update(void)
{
    kFlashStorage.input_shaping_config_wn_Hz = kAxis.input_shaping_config.wn_Hz;
    kFlashStorage.input_shaping_config_run_frq_Hz = kAxis.input_shaping_config.run_frq_Hz;
    kFlashStorage.pos_speed_ctl_config_aff = kAxis.pos_speed_ctl_config.aff;
    kFlashStorage.pos_speed_ctl_config_vff = kAxis.pos_speed_ctl_config.vff;
    kFlashStorage.pos_speed_ctl_config_j_kt = kAxis.pos_speed_ctl_config.j_kt;
    kFlashStorage.pos_speed_ctl_config_ki_s = kAxis.pos_speed_ctl_config.ki_s;
    kFlashStorage.pos_speed_ctl_config_kp_p = kAxis.pos_speed_ctl_config.kp_p;
    kFlashStorage.pos_speed_ctl_config_kp_s = kAxis.pos_speed_ctl_config.kp_s;
    kFlashStorage.pos_speed_ctl_config_speed_max_rad_s = kAxis.pos_speed_ctl_config.speed_max_rad_s;
    kFlashStorage.current_ctl_config_i_noise_A = kAxis.current_ctl_config.i_noise_A;
    kFlashStorage.current_ctl_config_comp_du_V = kAxis.current_ctl_config.comp_du_V;
    kFlashStorage.current_ctl_config_bandwidth_percentage = kAxis.current_ctl_config.bandwidth_percentage;
    kFlashStorage.current_ctl_config_flux_wb = kAxis.current_ctl_config.flux_wb;
    kFlashStorage.current_ctl_config_kp_ld = kAxis.current_ctl_config.kp_ld;
    kFlashStorage.current_ctl_config_ki_ld = kAxis.current_ctl_config.ki_ld;
    kFlashStorage.current_ctl_config_kp_lq = kAxis.current_ctl_config.kp_lq;
    kFlashStorage.current_ctl_config_ki_lq = kAxis.current_ctl_config.ki_lq;
    kFlashStorage.notch_filter_config_frq[0] = kAxis.notch_filter_config.frq[0];
    kFlashStorage.notch_filter_config_frq[1] = kAxis.notch_filter_config.frq[1];
    kFlashStorage.notch_filter_config_frq[2] = kAxis.notch_filter_config.frq[2];
    kFlashStorage.notch_filter_config_frq[3] = kAxis.notch_filter_config.frq[3];
    kFlashStorage.notch_filter_config_frq[4] = kAxis.notch_filter_config.frq[4];
    kFlashStorage.notch_filter_config_frq[5] = kAxis.notch_filter_config.frq[5];
    kFlashStorage.notch_filter_config_width[0] = kAxis.notch_filter_config.width[0];
    kFlashStorage.notch_filter_config_width[1] = kAxis.notch_filter_config.width[1];
    kFlashStorage.notch_filter_config_width[2] = kAxis.notch_filter_config.width[2];
    kFlashStorage.notch_filter_config_width[3] = kAxis.notch_filter_config.width[3];
    kFlashStorage.notch_filter_config_width[4] = kAxis.notch_filter_config.width[4];
    kFlashStorage.notch_filter_config_width[5] = kAxis.notch_filter_config.width[5];
    kFlashStorage.notch_filter_config_depth[0] = kAxis.notch_filter_config.depth[0];
    kFlashStorage.notch_filter_config_depth[1] = kAxis.notch_filter_config.depth[1];
    kFlashStorage.notch_filter_config_depth[2] = kAxis.notch_filter_config.depth[2];
    kFlashStorage.notch_filter_config_depth[3] = kAxis.notch_filter_config.depth[3];
    kFlashStorage.notch_filter_config_depth[4] = kAxis.notch_filter_config.depth[4];
    kFlashStorage.notch_filter_config_depth[5] = kAxis.notch_filter_config.depth[5];
    kFlashStorage.speed_obs_pll_config_wn_Hz = kAxis.speed_obs_pll_config.wn_Hz;
    kFlashStorage.motor_pos_sensor_config_elec_angle_bias_rad = kAxis.motor_pos_sensor_config.elec_angle_bias_rad;
    kFlashStorage.pos_speed_ctl_config_dob_wn_Hz = kAxis.pos_speed_ctl_config.dob_wn_Hz;
    kFlashStorage.pos_speed_ctl_config_dob_enable = kAxis.pos_speed_ctl_config.dob_enable;
    kFlashStorage.input_shaping_config_enable = kAxis.input_shaping_config.enable;
    kFlashStorage.tq_fc_id_config_iq_com_enable = kAxis.tq_fc_id_config.iq_com_enable;
    kFlashStorage.tq_fc_id_config_tq_com_enable = kAxis.tq_fc_id_config.tq_com_enable;
    kFlashStorage.tq_fc_id_config_fc_com_enable = kAxis.tq_fc_id_config.fc_com_enable;
    kFlashStorage.current_ctl_config_pwm_duty_cycle_max = kAxis.current_ctl_config.pwm_duty_cycle_max;
    kFlashStorage.app_encoder_config_Load_encoder_resolution = kAppEncoderConfig.Load_encoder_resolution;
    kFlashStorage.app_encoder_config_Motor_encoder_resolution = kAppEncoderConfig.Motor_encoder_resolution;
    kFlashStorage.app_base_config_Polarity = kAppBaseConfig.Polarity;
    kFlashStorage.app_restrict_param_Position_range_limit_Minimal_position_limit = kAppRestrictParam.Position_range_limit_Minimal_position_limit;
    kFlashStorage.app_restrict_param_Position_range_limit_Maximal_position_limit = kAppRestrictParam.Position_range_limit_Maximal_position_limit;
    kFlashStorage.app_restrict_param_Software_position_limit_Minimal_position_limit = kAppRestrictParam.Software_position_limit_Minimal_position_limit;
    kFlashStorage.app_restrict_param_Software_position_limit_Maximal_position_limit = kAppRestrictParam.Software_position_limit_Maximal_position_limit;
    kFlashStorage.app_restrict_param_Max_profile_velocity = kAppRestrictParam.Max_profile_velocity;
    kFlashStorage.app_restrict_param_Max_motor_speed = kAppRestrictParam.Max_motor_speed;
    kFlashStorage.app_motion_param_Profile_velocity = kAppMotionParam.Profile_velocity;
    kFlashStorage.app_motion_param_Profile_acceleration = kAppMotionParam.Profile_acceleration;
    kFlashStorage.app_motion_param_Profile_deceleration = kAppMotionParam.Profile_deceleration;
    kFlashStorage.app_motion_param_Quick_stop_deceleration = kAppMotionParam.Quick_stop_deceleration;
    kFlashStorage.app_motion_param_Motion_profile_type = kAppMotionParam.Motion_profile_type;
    kFlashStorage.app_restrict_param_Max_acceleration = kAppRestrictParam.Max_acceleration;
    kFlashStorage.app_restrict_param_Max_deceleration = kAppRestrictParam.Max_deceleration;
    kFlashStorage.app_motion_param_Home_offset = kAppMotionParam.Home_offset;
    kFlashStorage.app_motion_param_Homing_method = kAppMotionParam.Homing_method;
    kFlashStorage.app_window_param_Following_error_window = kAppWindowParam.Following_error_window;
    kFlashStorage.app_window_param_Following_error_time_out = kAppWindowParam.Following_error_time_out;
    kFlashStorage.app_window_param_Position_window = kAppWindowParam.Position_window;
    kFlashStorage.app_window_param_Position_window_time = kAppWindowParam.Position_window_time;
    kFlashStorage.app_window_param_Velocity_window = kAppWindowParam.Velocity_window;
    kFlashStorage.app_window_param_Velocity_window_time = kAppWindowParam.Velocity_window_time;
    kFlashStorage.app_window_param_Velocity_threshold = kAppWindowParam.Velocity_threshold;
    kFlashStorage.app_window_param_Velocity_threshold_time = kAppWindowParam.Velocity_threshold_time;
    kFlashStorage.app_restrict_param_Max_current = kAppRestrictParam.Max_current;
    kFlashStorage.app_motor_config_Motor_rated_current = kAppMotorConfig.Motor_rated_current;
    kFlashStorage.app_motor_config_Motor_rated_torque = kAppMotorConfig.Motor_rated_torque;
    kFlashStorage.app_motion_param_Torque_slope = kAppMotionParam.Torque_slope;
    kFlashStorage.pos_speed_ctl_config_dynamic_integration_enable = kAxis.pos_speed_ctl_config.dynamic_integration_enable;
    kFlashStorage.app_base_config_Home_position_offset_value = kAppBaseConfig.Home_position_offset_value;
    kFlashStorage.app_protect_config_Bus_under_voltage_threshold = kAppProtectConfig.Bus_under_voltage_threshold;
    kFlashStorage.app_protect_config_Bus_over_voltage_threshold = kAppProtectConfig.Bus_over_voltage_threshold;
    kFlashStorage.app_protect_config_Drive_overload_current_duration = kAppProtectConfig.Drive_overload_current_duration;
    kFlashStorage.app_protect_config_Drive_peak_current_duration = kAppProtectConfig.Drive_peak_current_duration;
    kFlashStorage.app_protect_config_Drive_temperature_threshold_time = kAppProtectConfig.Drive_temperature_threshold_time;
    kFlashStorage.app_protect_config_Drive_low_temperature_fault_threshold = kAppProtectConfig.Drive_low_temperature_fault_threshold;
    kFlashStorage.app_protect_config_Drive_high_temperature_fault_threshold = kAppProtectConfig.Drive_high_temperature_fault_threshold;
    kFlashStorage.app_protect_config_Overspeed_threshold = kAppProtectConfig.Overspeed_threshold;
    kFlashStorage.mit_ctl_config_kp_pos_NM_rad = kAxis.mit_ctl_config.kp_pos_NM_rad;
    kFlashStorage.mit_ctl_config_kd_spd_NM_rad_s = kAxis.mit_ctl_config.kd_spd_NM_rad_s;
    kFlashStorage.app_motor_config_Motor_peak_current = kAppMotorConfig.Motor_peak_current;
    kFlashStorage.app_motor_config_Motor_pole_pairs = kAppMotorConfig.Motor_pole_pairs;
    kFlashStorage.app_motor_config_Motor_maximum_speed = kAppMotorConfig.Motor_maximum_speed;
    kFlashStorage.current_ctl_config_elec_angle_compensation = kAxis.current_ctl_config.elec_angle_compensation;
    kFlashStorage.current_ctl_config_phase_dir = kAxis.current_ctl_config.phase_dir;
    kFlashStorage.app_motor_config_Resistance = kAppMotorConfig.Resistance;
    kFlashStorage.app_motor_config_Inductance = kAppMotorConfig.Inductance;
    kFlashStorage.app_protect_config_Drive_overcurrent_threshold = kAppProtectConfig.Drive_overcurrent_threshold;
    kFlashStorage.app_protect_config_Protection_enable = kAppProtectConfig.Protection_enable;
    kFlashStorage.app_motion_param_Encoder_calibration_speed = kAppMotionParam.Encoder_calibration_speed;
    kFlashStorage.app_motion_param_MIT_max_current = kAppMotionParam.MIT_max_current;
    kFlashStorage.app_motor_config_Reduction_ratio_num = kAppMotorConfig.Reduction_ratio_num;
    kFlashStorage.app_motor_config_Reduction_ratio_den = kAppMotorConfig.Reduction_ratio_den;
    kFlashStorage.app_base_config_Can_id = kAppBaseConfig.Can_id;
    kFlashStorage.app_base_config_Can_baudrate = kAppBaseConfig.Can_baudrate;
    kFlashStorage.app_encoder_config_Motor_encoder_type = kAppEncoderConfig.Motor_encoder_type;
    kFlashStorage.app_encoder_config_Load_encoder_type = kAppEncoderConfig.Load_encoder_type;
    kFlashStorage.app_motor_config_Torque_constant = kAppMotorConfig.Torque_constant;
    kFlashStorage.app_protect_config_Motor_low_temperature_fault_threshold = kAppProtectConfig.Motor_low_temperature_fault_threshold;
    kFlashStorage.app_protect_config_Motor_high_temperature_fault_threshold = kAppProtectConfig.Motor_high_temperature_fault_threshold;
    kFlashStorage.app_protect_config_Can_timeout = kAppProtectConfig.Can_timeout;
    kFlashStorage.app_base_config_Quick_stop_option_code = kAppBaseConfig.Quick_stop_option_code;
    kFlashStorage.app_protect_config_Motor_low_temperature_warning_threshold = kAppProtectConfig.Motor_low_temperature_warning_threshold;
    kFlashStorage.app_protect_config_Motor_high_temperature_warning_threshold = kAppProtectConfig.Motor_high_temperature_warning_threshold;
    kFlashStorage.app_base_config_Brake_engage_time = kAppBaseConfig.Brake_engage_time;
    kFlashStorage.app_base_config_Brake_release_time = kAppBaseConfig.Brake_release_time;
    kFlashStorage.app_base_config_Dynamic_brake_speed_threshold = kAppBaseConfig.Dynamic_brake_speed_threshold;
    kFlashStorage.app_base_config_Brake_release_hold_voltage = kAppBaseConfig.Brake_release_hold_voltage;
    kFlashStorage.app_protect_config_Mcu_temperature_threshold_time = kAppProtectConfig.Mcu_temperature_threshold_time;
    kFlashStorage.app_protect_config_Mcu_low_temperature_fault_threshold = kAppProtectConfig.Mcu_low_temperature_fault_threshold;
    kFlashStorage.app_protect_config_Mcu_high_temperature_fault_threshold = kAppProtectConfig.Mcu_high_temperature_fault_threshold;
    kFlashStorage.app_protect_config_Mcu_low_temperature_warning_threshold = kAppProtectConfig.Mcu_low_temperature_warning_threshold;
    kFlashStorage.app_protect_config_Mcu_high_temperature_warning_threshold = kAppProtectConfig.Mcu_high_temperature_warning_threshold;
    kFlashStorage.app_protect_config_Drive_low_temperature_warning_threshold = kAppProtectConfig.Drive_low_temperature_warning_threshold;
    kFlashStorage.app_protect_config_Drive_high_temperature_warning_threshold = kAppProtectConfig.Drive_high_temperature_warning_threshold;
    kFlashStorage.app_encoder_config_Motor_encoder_options = kAppEncoderConfig.Motor_encoder_options;
    kFlashStorage.app_motor_config_Motor_rotor_inertia = kAppMotorConfig.Motor_rotor_inertia;
    kFlashStorage.app_debug_param_Debug_float[0] = kAppDebugParam.Debug_float[0];
    kFlashStorage.app_debug_param_Debug_float[1] = kAppDebugParam.Debug_float[1];
    kFlashStorage.app_debug_param_Debug_float[2] = kAppDebugParam.Debug_float[2];
    kFlashStorage.app_debug_param_Debug_float[3] = kAppDebugParam.Debug_float[3];
    kFlashStorage.app_debug_param_Debug_float[4] = kAppDebugParam.Debug_float[4];
    kFlashStorage.app_debug_param_Debug_float[5] = kAppDebugParam.Debug_float[5];
    kFlashStorage.app_debug_param_Debug_float[6] = kAppDebugParam.Debug_float[6];
    kFlashStorage.app_debug_param_Debug_float[7] = kAppDebugParam.Debug_float[7];
    kFlashStorage.app_debug_param_Debug_float[8] = kAppDebugParam.Debug_float[8];
    kFlashStorage.app_debug_param_Debug_float[9] = kAppDebugParam.Debug_float[9];
    kFlashStorage.app_debug_param_Debug_float[10] = kAppDebugParam.Debug_float[10];
    kFlashStorage.app_debug_param_Debug_float[11] = kAppDebugParam.Debug_float[11];
    kFlashStorage.app_debug_param_Debug_float[12] = kAppDebugParam.Debug_float[12];
    kFlashStorage.app_debug_param_Debug_float[13] = kAppDebugParam.Debug_float[13];
    kFlashStorage.app_debug_param_Debug_float[14] = kAppDebugParam.Debug_float[14];
    kFlashStorage.app_debug_param_Debug_float[15] = kAppDebugParam.Debug_float[15];
    kFlashStorage.app_debug_param_Debug_uint32[0] = kAppDebugParam.Debug_uint32[0];
    kFlashStorage.app_debug_param_Debug_uint32[1] = kAppDebugParam.Debug_uint32[1];
    kFlashStorage.app_debug_param_Debug_uint32[2] = kAppDebugParam.Debug_uint32[2];
    kFlashStorage.app_debug_param_Debug_uint32[3] = kAppDebugParam.Debug_uint32[3];
    kFlashStorage.app_debug_param_Debug_uint32[4] = kAppDebugParam.Debug_uint32[4];
    kFlashStorage.app_debug_param_Debug_uint32[5] = kAppDebugParam.Debug_uint32[5];
    kFlashStorage.app_debug_param_Debug_uint32[6] = kAppDebugParam.Debug_uint32[6];
    kFlashStorage.app_debug_param_Debug_uint32[7] = kAppDebugParam.Debug_uint32[7];
    kFlashStorage.app_debug_param_Debug_uint32[8] = kAppDebugParam.Debug_uint32[8];
    kFlashStorage.app_debug_param_Debug_uint32[9] = kAppDebugParam.Debug_uint32[9];
    kFlashStorage.app_debug_param_Debug_uint32[10] = kAppDebugParam.Debug_uint32[10];
    kFlashStorage.app_debug_param_Debug_uint32[11] = kAppDebugParam.Debug_uint32[11];
    kFlashStorage.app_debug_param_Debug_uint32[12] = kAppDebugParam.Debug_uint32[12];
    kFlashStorage.app_debug_param_Debug_uint32[13] = kAppDebugParam.Debug_uint32[13];
    kFlashStorage.app_debug_param_Debug_uint32[14] = kAppDebugParam.Debug_uint32[14];
    kFlashStorage.app_debug_param_Debug_uint32[15] = kAppDebugParam.Debug_uint32[15];
    kFlashStorage.app_debug_param_Debug_int32[0] = kAppDebugParam.Debug_int32[0];
    kFlashStorage.app_debug_param_Debug_int32[1] = kAppDebugParam.Debug_int32[1];
    kFlashStorage.app_debug_param_Debug_int32[2] = kAppDebugParam.Debug_int32[2];
    kFlashStorage.app_debug_param_Debug_int32[3] = kAppDebugParam.Debug_int32[3];
    kFlashStorage.app_debug_param_Debug_int32[4] = kAppDebugParam.Debug_int32[4];
    kFlashStorage.app_debug_param_Debug_int32[5] = kAppDebugParam.Debug_int32[5];
    kFlashStorage.app_debug_param_Debug_int32[6] = kAppDebugParam.Debug_int32[6];
    kFlashStorage.app_debug_param_Debug_int32[7] = kAppDebugParam.Debug_int32[7];
    kFlashStorage.app_debug_param_Debug_int32[8] = kAppDebugParam.Debug_int32[8];
    kFlashStorage.app_debug_param_Debug_int32[9] = kAppDebugParam.Debug_int32[9];
    kFlashStorage.app_debug_param_Debug_int32[10] = kAppDebugParam.Debug_int32[10];
    kFlashStorage.app_debug_param_Debug_int32[11] = kAppDebugParam.Debug_int32[11];
    kFlashStorage.app_debug_param_Debug_int32[12] = kAppDebugParam.Debug_int32[12];
    kFlashStorage.app_debug_param_Debug_int32[13] = kAppDebugParam.Debug_int32[13];
    kFlashStorage.app_debug_param_Debug_int32[14] = kAppDebugParam.Debug_int32[14];
    kFlashStorage.app_debug_param_Debug_int32[15] = kAppDebugParam.Debug_int32[15];
    kFlashStorage.app_encoder_config_Load_control_resolution = kAppEncoderConfig.Load_control_resolution;
    kFlashStorage.app_encoder_config_Motor_control_resolution = kAppEncoderConfig.Motor_control_resolution;
    kFlashStorage.app_encoder_config_Load_encoder_options = kAppEncoderConfig.Load_encoder_options;
    kFlashStorage.app_restrict_param_Position_limit_enable = kAppRestrictParam.Position_limit_enable;
    kFlashStorage.app_base_config_Digital_io_outputs_phys = kAppBaseConfig.Digital_io_outputs_phys;
    kFlashStorage.app_base_config_Digital_io_outputs_mask = kAppBaseConfig.Digital_io_outputs_mask;
    kFlashStorage.tq_fc_id_config_fc_p_com = kAxis.tq_fc_id_config.fc_p_com;
    kFlashStorage.tq_fc_id_config_fc_n_com = kAxis.tq_fc_id_config.fc_n_com;
    kFlashStorage.app_base_config_Brake_control_mode = kAppBaseConfig.Brake_control_mode;
    kFlashStorage.app_base_config_Brake_rated_voltage = kAppBaseConfig.Brake_rated_voltage;
    kFlashStorage.app_base_config_Brake_release_action_voltage = kAppBaseConfig.Brake_release_action_voltage;
    kFlashStorage.app_base_config_Brake_release_pwm_freq = kAppBaseConfig.Brake_release_pwm_freq;
    kFlashStorage.app_base_config_Brake_engage_delay_time = kAppBaseConfig.Brake_engage_delay_time;
    kFlashStorage.app_base_config_Brake_release_delay_time = kAppBaseConfig.Brake_release_delay_time;
    kFlashStorage.app_motion_param_Interp_time_value = kAppMotionParam.Interp_time_value;
    kFlashStorage.app_motion_param_Interp_time_index = kAppMotionParam.Interp_time_index;
    kFlashStorage.app_mavlink_config_Sys_id = kAppMavlinkConfig.Sys_id;
    kFlashStorage.app_mavlink_config_Comp_id = kAppMavlinkConfig.Comp_id;
    kFlashStorage.app_motion_param_Homing_speed_search_for_switch = kAppMotionParam.Homing_speed_search_for_switch;
    kFlashStorage.app_motion_param_Homing_speed_search_for_zero = kAppMotionParam.Homing_speed_search_for_zero;
    kFlashStorage.app_motion_param_Homing_acceleration = kAppMotionParam.Homing_acceleration;
}

void flash_param_init(void)
{
    kAxis.input_shaping_config.wn_Hz = kFlashStorage.input_shaping_config_wn_Hz;
    kAxis.input_shaping_config.run_frq_Hz = kFlashStorage.input_shaping_config_run_frq_Hz;
    kAxis.pos_speed_ctl_config.aff = kFlashStorage.pos_speed_ctl_config_aff;
    kAxis.pos_speed_ctl_config.vff = kFlashStorage.pos_speed_ctl_config_vff;
    kAxis.pos_speed_ctl_config.j_kt = kFlashStorage.pos_speed_ctl_config_j_kt;
    kAxis.pos_speed_ctl_config.ki_s = kFlashStorage.pos_speed_ctl_config_ki_s;
    kAxis.pos_speed_ctl_config.kp_p = kFlashStorage.pos_speed_ctl_config_kp_p;
    kAxis.pos_speed_ctl_config.kp_s = kFlashStorage.pos_speed_ctl_config_kp_s;
    kAxis.pos_speed_ctl_config.speed_max_rad_s = kFlashStorage.pos_speed_ctl_config_speed_max_rad_s;
    kAxis.current_ctl_config.i_noise_A = kFlashStorage.current_ctl_config_i_noise_A;
    kAxis.current_ctl_config.comp_du_V = kFlashStorage.current_ctl_config_comp_du_V;
    kAxis.current_ctl_config.bandwidth_percentage = kFlashStorage.current_ctl_config_bandwidth_percentage;
    kAxis.current_ctl_config.flux_wb = kFlashStorage.current_ctl_config_flux_wb;
    kAxis.current_ctl_config.kp_ld = kFlashStorage.current_ctl_config_kp_ld;
    kAxis.current_ctl_config.ki_ld = kFlashStorage.current_ctl_config_ki_ld;
    kAxis.current_ctl_config.kp_lq = kFlashStorage.current_ctl_config_kp_lq;
    kAxis.current_ctl_config.ki_lq = kFlashStorage.current_ctl_config_ki_lq;
    kAxis.notch_filter_config.frq[0] = kFlashStorage.notch_filter_config_frq[0];
    kAxis.notch_filter_config.frq[1] = kFlashStorage.notch_filter_config_frq[1];
    kAxis.notch_filter_config.frq[2] = kFlashStorage.notch_filter_config_frq[2];
    kAxis.notch_filter_config.frq[3] = kFlashStorage.notch_filter_config_frq[3];
    kAxis.notch_filter_config.frq[4] = kFlashStorage.notch_filter_config_frq[4];
    kAxis.notch_filter_config.frq[5] = kFlashStorage.notch_filter_config_frq[5];
    kAxis.notch_filter_config.width[0] = kFlashStorage.notch_filter_config_width[0];
    kAxis.notch_filter_config.width[1] = kFlashStorage.notch_filter_config_width[1];
    kAxis.notch_filter_config.width[2] = kFlashStorage.notch_filter_config_width[2];
    kAxis.notch_filter_config.width[3] = kFlashStorage.notch_filter_config_width[3];
    kAxis.notch_filter_config.width[4] = kFlashStorage.notch_filter_config_width[4];
    kAxis.notch_filter_config.width[5] = kFlashStorage.notch_filter_config_width[5];
    kAxis.notch_filter_config.depth[0] = kFlashStorage.notch_filter_config_depth[0];
    kAxis.notch_filter_config.depth[1] = kFlashStorage.notch_filter_config_depth[1];
    kAxis.notch_filter_config.depth[2] = kFlashStorage.notch_filter_config_depth[2];
    kAxis.notch_filter_config.depth[3] = kFlashStorage.notch_filter_config_depth[3];
    kAxis.notch_filter_config.depth[4] = kFlashStorage.notch_filter_config_depth[4];
    kAxis.notch_filter_config.depth[5] = kFlashStorage.notch_filter_config_depth[5];
    kAxis.speed_obs_pll_config.wn_Hz = kFlashStorage.speed_obs_pll_config_wn_Hz;
    kAxis.motor_pos_sensor_config.elec_angle_bias_rad = kFlashStorage.motor_pos_sensor_config_elec_angle_bias_rad;
    kAxis.pos_speed_ctl_config.dob_wn_Hz = kFlashStorage.pos_speed_ctl_config_dob_wn_Hz;
    kAxis.pos_speed_ctl_config.dob_enable = kFlashStorage.pos_speed_ctl_config_dob_enable;
    kAxis.input_shaping_config.enable = kFlashStorage.input_shaping_config_enable;
    kAxis.tq_fc_id_config.iq_com_enable = kFlashStorage.tq_fc_id_config_iq_com_enable;
    kAxis.tq_fc_id_config.tq_com_enable = kFlashStorage.tq_fc_id_config_tq_com_enable;
    kAxis.tq_fc_id_config.fc_com_enable = kFlashStorage.tq_fc_id_config_fc_com_enable;
    kAxis.current_ctl_config.pwm_duty_cycle_max = kFlashStorage.current_ctl_config_pwm_duty_cycle_max;
    kAppEncoderConfig.Load_encoder_resolution = kFlashStorage.app_encoder_config_Load_encoder_resolution;
    kAppEncoderConfig.Motor_encoder_resolution = kFlashStorage.app_encoder_config_Motor_encoder_resolution;
    kAppBaseConfig.Polarity = kFlashStorage.app_base_config_Polarity;
    kAppRestrictParam.Position_range_limit_Minimal_position_limit = kFlashStorage.app_restrict_param_Position_range_limit_Minimal_position_limit;
    kAppRestrictParam.Position_range_limit_Maximal_position_limit = kFlashStorage.app_restrict_param_Position_range_limit_Maximal_position_limit;
    kAppRestrictParam.Software_position_limit_Minimal_position_limit = kFlashStorage.app_restrict_param_Software_position_limit_Minimal_position_limit;
    kAppRestrictParam.Software_position_limit_Maximal_position_limit = kFlashStorage.app_restrict_param_Software_position_limit_Maximal_position_limit;
    kAppRestrictParam.Max_profile_velocity = kFlashStorage.app_restrict_param_Max_profile_velocity;
    kAppRestrictParam.Max_motor_speed = kFlashStorage.app_restrict_param_Max_motor_speed;
    kAppMotionParam.Profile_velocity = kFlashStorage.app_motion_param_Profile_velocity;
    kAppMotionParam.Profile_acceleration = kFlashStorage.app_motion_param_Profile_acceleration;
    kAppMotionParam.Profile_deceleration = kFlashStorage.app_motion_param_Profile_deceleration;
    kAppMotionParam.Quick_stop_deceleration = kFlashStorage.app_motion_param_Quick_stop_deceleration;
    kAppMotionParam.Motion_profile_type = kFlashStorage.app_motion_param_Motion_profile_type;
    kAppRestrictParam.Max_acceleration = kFlashStorage.app_restrict_param_Max_acceleration;
    kAppRestrictParam.Max_deceleration = kFlashStorage.app_restrict_param_Max_deceleration;
    kAppMotionParam.Home_offset = kFlashStorage.app_motion_param_Home_offset;
    kAppMotionParam.Homing_method = kFlashStorage.app_motion_param_Homing_method;
    kAppWindowParam.Following_error_window = kFlashStorage.app_window_param_Following_error_window;
    kAppWindowParam.Following_error_time_out = kFlashStorage.app_window_param_Following_error_time_out;
    kAppWindowParam.Position_window = kFlashStorage.app_window_param_Position_window;
    kAppWindowParam.Position_window_time = kFlashStorage.app_window_param_Position_window_time;
    kAppWindowParam.Velocity_window = kFlashStorage.app_window_param_Velocity_window;
    kAppWindowParam.Velocity_window_time = kFlashStorage.app_window_param_Velocity_window_time;
    kAppWindowParam.Velocity_threshold = kFlashStorage.app_window_param_Velocity_threshold;
    kAppWindowParam.Velocity_threshold_time = kFlashStorage.app_window_param_Velocity_threshold_time;
    kAppRestrictParam.Max_current = kFlashStorage.app_restrict_param_Max_current;
    kAppMotorConfig.Motor_rated_current = kFlashStorage.app_motor_config_Motor_rated_current;
    kAppMotorConfig.Motor_rated_torque = kFlashStorage.app_motor_config_Motor_rated_torque;
    kAppMotionParam.Torque_slope = kFlashStorage.app_motion_param_Torque_slope;
    kAxis.pos_speed_ctl_config.dynamic_integration_enable = kFlashStorage.pos_speed_ctl_config_dynamic_integration_enable;
    kAppBaseConfig.Home_position_offset_value = kFlashStorage.app_base_config_Home_position_offset_value;
    kAppProtectConfig.Bus_under_voltage_threshold = kFlashStorage.app_protect_config_Bus_under_voltage_threshold;
    kAppProtectConfig.Bus_over_voltage_threshold = kFlashStorage.app_protect_config_Bus_over_voltage_threshold;
    kAppProtectConfig.Drive_overload_current_duration = kFlashStorage.app_protect_config_Drive_overload_current_duration;
    kAppProtectConfig.Drive_peak_current_duration = kFlashStorage.app_protect_config_Drive_peak_current_duration;
    kAppProtectConfig.Drive_temperature_threshold_time = kFlashStorage.app_protect_config_Drive_temperature_threshold_time;
    kAppProtectConfig.Drive_low_temperature_fault_threshold = kFlashStorage.app_protect_config_Drive_low_temperature_fault_threshold;
    kAppProtectConfig.Drive_high_temperature_fault_threshold = kFlashStorage.app_protect_config_Drive_high_temperature_fault_threshold;
    kAppProtectConfig.Overspeed_threshold = kFlashStorage.app_protect_config_Overspeed_threshold;
    kAxis.mit_ctl_config.kp_pos_NM_rad = kFlashStorage.mit_ctl_config_kp_pos_NM_rad;
    kAxis.mit_ctl_config.kd_spd_NM_rad_s = kFlashStorage.mit_ctl_config_kd_spd_NM_rad_s;
    kAppMotorConfig.Motor_peak_current = kFlashStorage.app_motor_config_Motor_peak_current;
    kAppMotorConfig.Motor_pole_pairs = kFlashStorage.app_motor_config_Motor_pole_pairs;
    kAppMotorConfig.Motor_maximum_speed = kFlashStorage.app_motor_config_Motor_maximum_speed;
    kAxis.current_ctl_config.elec_angle_compensation = kFlashStorage.current_ctl_config_elec_angle_compensation;
    kAxis.current_ctl_config.phase_dir = kFlashStorage.current_ctl_config_phase_dir;
    kAppMotorConfig.Resistance = kFlashStorage.app_motor_config_Resistance;
    kAppMotorConfig.Inductance = kFlashStorage.app_motor_config_Inductance;
    kAppProtectConfig.Drive_overcurrent_threshold = kFlashStorage.app_protect_config_Drive_overcurrent_threshold;
    kAppProtectConfig.Protection_enable = kFlashStorage.app_protect_config_Protection_enable;
    kAppMotionParam.Encoder_calibration_speed = kFlashStorage.app_motion_param_Encoder_calibration_speed;
    kAppMotionParam.MIT_max_current = kFlashStorage.app_motion_param_MIT_max_current;
    kAppMotorConfig.Reduction_ratio_num = kFlashStorage.app_motor_config_Reduction_ratio_num;
    kAppMotorConfig.Reduction_ratio_den = kFlashStorage.app_motor_config_Reduction_ratio_den;
    kAppBaseConfig.Can_id = kFlashStorage.app_base_config_Can_id;
    kAppBaseConfig.Can_baudrate = kFlashStorage.app_base_config_Can_baudrate;
    kAppEncoderConfig.Motor_encoder_type = kFlashStorage.app_encoder_config_Motor_encoder_type;
    kAppEncoderConfig.Load_encoder_type = kFlashStorage.app_encoder_config_Load_encoder_type;
    kAppMotorConfig.Torque_constant = kFlashStorage.app_motor_config_Torque_constant;
    kAppProtectConfig.Motor_low_temperature_fault_threshold = kFlashStorage.app_protect_config_Motor_low_temperature_fault_threshold;
    kAppProtectConfig.Motor_high_temperature_fault_threshold = kFlashStorage.app_protect_config_Motor_high_temperature_fault_threshold;
    kAppProtectConfig.Can_timeout = kFlashStorage.app_protect_config_Can_timeout;
    kAppBaseConfig.Quick_stop_option_code = kFlashStorage.app_base_config_Quick_stop_option_code;
    kAppProtectConfig.Motor_low_temperature_warning_threshold = kFlashStorage.app_protect_config_Motor_low_temperature_warning_threshold;
    kAppProtectConfig.Motor_high_temperature_warning_threshold = kFlashStorage.app_protect_config_Motor_high_temperature_warning_threshold;
    kAppBaseConfig.Brake_engage_time = kFlashStorage.app_base_config_Brake_engage_time;
    kAppBaseConfig.Brake_release_time = kFlashStorage.app_base_config_Brake_release_time;
    kAppBaseConfig.Dynamic_brake_speed_threshold = kFlashStorage.app_base_config_Dynamic_brake_speed_threshold;
    kAppBaseConfig.Brake_release_hold_voltage = kFlashStorage.app_base_config_Brake_release_hold_voltage;
    kAppProtectConfig.Mcu_temperature_threshold_time = kFlashStorage.app_protect_config_Mcu_temperature_threshold_time;
    kAppProtectConfig.Mcu_low_temperature_fault_threshold = kFlashStorage.app_protect_config_Mcu_low_temperature_fault_threshold;
    kAppProtectConfig.Mcu_high_temperature_fault_threshold = kFlashStorage.app_protect_config_Mcu_high_temperature_fault_threshold;
    kAppProtectConfig.Mcu_low_temperature_warning_threshold = kFlashStorage.app_protect_config_Mcu_low_temperature_warning_threshold;
    kAppProtectConfig.Mcu_high_temperature_warning_threshold = kFlashStorage.app_protect_config_Mcu_high_temperature_warning_threshold;
    kAppProtectConfig.Drive_low_temperature_warning_threshold = kFlashStorage.app_protect_config_Drive_low_temperature_warning_threshold;
    kAppProtectConfig.Drive_high_temperature_warning_threshold = kFlashStorage.app_protect_config_Drive_high_temperature_warning_threshold;
    kAppEncoderConfig.Motor_encoder_options = kFlashStorage.app_encoder_config_Motor_encoder_options;
    kAppMotorConfig.Motor_rotor_inertia = kFlashStorage.app_motor_config_Motor_rotor_inertia;
    kAppDebugParam.Debug_float[0] = kFlashStorage.app_debug_param_Debug_float[0];
    kAppDebugParam.Debug_float[1] = kFlashStorage.app_debug_param_Debug_float[1];
    kAppDebugParam.Debug_float[2] = kFlashStorage.app_debug_param_Debug_float[2];
    kAppDebugParam.Debug_float[3] = kFlashStorage.app_debug_param_Debug_float[3];
    kAppDebugParam.Debug_float[4] = kFlashStorage.app_debug_param_Debug_float[4];
    kAppDebugParam.Debug_float[5] = kFlashStorage.app_debug_param_Debug_float[5];
    kAppDebugParam.Debug_float[6] = kFlashStorage.app_debug_param_Debug_float[6];
    kAppDebugParam.Debug_float[7] = kFlashStorage.app_debug_param_Debug_float[7];
    kAppDebugParam.Debug_float[8] = kFlashStorage.app_debug_param_Debug_float[8];
    kAppDebugParam.Debug_float[9] = kFlashStorage.app_debug_param_Debug_float[9];
    kAppDebugParam.Debug_float[10] = kFlashStorage.app_debug_param_Debug_float[10];
    kAppDebugParam.Debug_float[11] = kFlashStorage.app_debug_param_Debug_float[11];
    kAppDebugParam.Debug_float[12] = kFlashStorage.app_debug_param_Debug_float[12];
    kAppDebugParam.Debug_float[13] = kFlashStorage.app_debug_param_Debug_float[13];
    kAppDebugParam.Debug_float[14] = kFlashStorage.app_debug_param_Debug_float[14];
    kAppDebugParam.Debug_float[15] = kFlashStorage.app_debug_param_Debug_float[15];
    kAppDebugParam.Debug_uint32[0] = kFlashStorage.app_debug_param_Debug_uint32[0];
    kAppDebugParam.Debug_uint32[1] = kFlashStorage.app_debug_param_Debug_uint32[1];
    kAppDebugParam.Debug_uint32[2] = kFlashStorage.app_debug_param_Debug_uint32[2];
    kAppDebugParam.Debug_uint32[3] = kFlashStorage.app_debug_param_Debug_uint32[3];
    kAppDebugParam.Debug_uint32[4] = kFlashStorage.app_debug_param_Debug_uint32[4];
    kAppDebugParam.Debug_uint32[5] = kFlashStorage.app_debug_param_Debug_uint32[5];
    kAppDebugParam.Debug_uint32[6] = kFlashStorage.app_debug_param_Debug_uint32[6];
    kAppDebugParam.Debug_uint32[7] = kFlashStorage.app_debug_param_Debug_uint32[7];
    kAppDebugParam.Debug_uint32[8] = kFlashStorage.app_debug_param_Debug_uint32[8];
    kAppDebugParam.Debug_uint32[9] = kFlashStorage.app_debug_param_Debug_uint32[9];
    kAppDebugParam.Debug_uint32[10] = kFlashStorage.app_debug_param_Debug_uint32[10];
    kAppDebugParam.Debug_uint32[11] = kFlashStorage.app_debug_param_Debug_uint32[11];
    kAppDebugParam.Debug_uint32[12] = kFlashStorage.app_debug_param_Debug_uint32[12];
    kAppDebugParam.Debug_uint32[13] = kFlashStorage.app_debug_param_Debug_uint32[13];
    kAppDebugParam.Debug_uint32[14] = kFlashStorage.app_debug_param_Debug_uint32[14];
    kAppDebugParam.Debug_uint32[15] = kFlashStorage.app_debug_param_Debug_uint32[15];
    kAppDebugParam.Debug_int32[0] = kFlashStorage.app_debug_param_Debug_int32[0];
    kAppDebugParam.Debug_int32[1] = kFlashStorage.app_debug_param_Debug_int32[1];
    kAppDebugParam.Debug_int32[2] = kFlashStorage.app_debug_param_Debug_int32[2];
    kAppDebugParam.Debug_int32[3] = kFlashStorage.app_debug_param_Debug_int32[3];
    kAppDebugParam.Debug_int32[4] = kFlashStorage.app_debug_param_Debug_int32[4];
    kAppDebugParam.Debug_int32[5] = kFlashStorage.app_debug_param_Debug_int32[5];
    kAppDebugParam.Debug_int32[6] = kFlashStorage.app_debug_param_Debug_int32[6];
    kAppDebugParam.Debug_int32[7] = kFlashStorage.app_debug_param_Debug_int32[7];
    kAppDebugParam.Debug_int32[8] = kFlashStorage.app_debug_param_Debug_int32[8];
    kAppDebugParam.Debug_int32[9] = kFlashStorage.app_debug_param_Debug_int32[9];
    kAppDebugParam.Debug_int32[10] = kFlashStorage.app_debug_param_Debug_int32[10];
    kAppDebugParam.Debug_int32[11] = kFlashStorage.app_debug_param_Debug_int32[11];
    kAppDebugParam.Debug_int32[12] = kFlashStorage.app_debug_param_Debug_int32[12];
    kAppDebugParam.Debug_int32[13] = kFlashStorage.app_debug_param_Debug_int32[13];
    kAppDebugParam.Debug_int32[14] = kFlashStorage.app_debug_param_Debug_int32[14];
    kAppDebugParam.Debug_int32[15] = kFlashStorage.app_debug_param_Debug_int32[15];
    kAppEncoderConfig.Load_control_resolution = kFlashStorage.app_encoder_config_Load_control_resolution;
    kAppEncoderConfig.Motor_control_resolution = kFlashStorage.app_encoder_config_Motor_control_resolution;
    kAppEncoderConfig.Load_encoder_options = kFlashStorage.app_encoder_config_Load_encoder_options;
    kAppRestrictParam.Position_limit_enable = kFlashStorage.app_restrict_param_Position_limit_enable;
    kAppBaseConfig.Digital_io_outputs_phys = kFlashStorage.app_base_config_Digital_io_outputs_phys;
    kAppBaseConfig.Digital_io_outputs_mask = kFlashStorage.app_base_config_Digital_io_outputs_mask;
    kAxis.tq_fc_id_config.fc_p_com = kFlashStorage.tq_fc_id_config_fc_p_com;
    kAxis.tq_fc_id_config.fc_n_com = kFlashStorage.tq_fc_id_config_fc_n_com;
    kAppBaseConfig.Brake_control_mode = kFlashStorage.app_base_config_Brake_control_mode;
    kAppBaseConfig.Brake_rated_voltage = kFlashStorage.app_base_config_Brake_rated_voltage;
    kAppBaseConfig.Brake_release_action_voltage = kFlashStorage.app_base_config_Brake_release_action_voltage;
    kAppBaseConfig.Brake_release_pwm_freq = kFlashStorage.app_base_config_Brake_release_pwm_freq;
    kAppBaseConfig.Brake_engage_delay_time = kFlashStorage.app_base_config_Brake_engage_delay_time;
    kAppBaseConfig.Brake_release_delay_time = kFlashStorage.app_base_config_Brake_release_delay_time;
    kAppMotionParam.Interp_time_value = kFlashStorage.app_motion_param_Interp_time_value;
    kAppMotionParam.Interp_time_index = kFlashStorage.app_motion_param_Interp_time_index;
    kAppMavlinkConfig.Sys_id = kFlashStorage.app_mavlink_config_Sys_id;
    kAppMavlinkConfig.Comp_id = kFlashStorage.app_mavlink_config_Comp_id;
    kAppMotionParam.Homing_speed_search_for_switch = kFlashStorage.app_motion_param_Homing_speed_search_for_switch;
    kAppMotionParam.Homing_speed_search_for_zero = kFlashStorage.app_motion_param_Homing_speed_search_for_zero;
    kAppMotionParam.Homing_acceleration = kFlashStorage.app_motion_param_Homing_acceleration;
}
/* USER CODE BEGIN AREA 1 */
static HistoricalInfo kFlashHistoricalInfo;
static bool IsFlashWriteOrErase(FLASH_STORE_CMD store_cmd);
static bool IsFlashWriteGuard(FLASH_STORE_CMD store_cmd);

static void FlashdbDatabaseInit(void)
{
    if (bsp_flashdb_key_register(FLASHDB_KEY_INDEX_ALL_PARAM, "AllParam", \
            &kFlashStorage, sizeof(kFlashStorage)) != FLASHDB_NO_ERR)
    {
        sys_set_bsp_error_state(ERROR_FLASH_STORE, ERROR_SET);
        return;
    }
    if (bsp_flashdb_key_register(FLASHDB_KEY_INDEX_ERROR_RECORD, "ErrorRecord", \
            &kFlashHistoricalInfo.Error_records_list, \
            sizeof(kFlashHistoricalInfo.Error_records_list)) != FLASHDB_NO_ERR)
    {
        sys_set_bsp_error_state(ERROR_FLASH_STORE, ERROR_SET);
        return;
    }
    if (bsp_flashdb_key_register(FLASHDB_KEY_INDEX_TQ_FC_TABLE, "TqFcTable", \
            &kAxisDw.tq_fc_id_InstanceData.rtdw, \
            sizeof(kAxisDw.tq_fc_id_InstanceData.rtdw)) != FLASHDB_NO_ERR)
    {
        sys_set_bsp_error_state(ERROR_FLASH_STORE, ERROR_SET);
        return;
    }

    if (bsp_flashdb_init() != FLASHDB_NO_ERR)
    {
        sys_set_bsp_error_state(ERROR_FLASH_STORE, ERROR_SET);
        return;
    }
}

void AppStoreInit(void)
{
    flash_param_update(); // 在初次存储KV还未被创建时，将参数默认值更新到kFlashStorage后写入flash
    FlashdbDatabaseInit();

    set_app_Storage_status(FLASH_STORE_STATUS_IDLE);

    set_app_Storage_cmd(FLASH_STORE_CMD_READ_PARAM);
    AppStoreUpdata1ms();
    set_app_Storage_cmd(FLASH_STORE_CMD_READ_ERROR);
    AppStoreUpdata1ms();
    set_app_Storage_cmd(FLASH_STORE_CMD_READ_TQ_FC);
    AppStoreUpdata1ms();
}

void AppStoreUpdata1ms(void)
{
    FLASHDB_STATUS flashdb_status = FLASHDB_NO_ERR;

    FLASH_STORE_CMD store_cmd = get_app_Storage_cmd();
    FLASH_STORE_STATUS store_status = get_app_Storage_status();

    // 窗口检查擦写频率，是否保护Flash不被频繁擦写
    if (IsFlashWriteGuard(store_cmd))
    {
        // flashdb_status = FLASHDB_PROTECT_ERR;
        set_app_Storage_status(FLASH_STORE_STATUS_PROTECT);
        sys_set_bsp_error_state(ERROR_FLASH_STORE, ERROR_SET);
        set_app_Storage_cmd(FLASH_STORE_CMD_NULL);
        return;
    }

    if (store_cmd != FLASH_STORE_CMD_NULL &&
        store_status != FLASH_STORE_STATUS_BUSY)
    {
        // 实测参数存储耗时
        //set_timer_record_start(9);
        uint32_t *p_AppErrorRecordsList = get_app_Error_records_list_addr();

        set_app_Storage_status(FLASH_STORE_STATUS_BUSY);
        switch (store_cmd)
        {
            // 数据库参数存储相关
            case FLASH_STORE_CMD_READ_PARAM:
                flashdb_status = bsp_flashdb_read(FLASHDB_KEY_INDEX_ALL_PARAM);

                if (flashdb_status == FLASHDB_NO_ERR)
                {
                    // flash参数赋值到内部变量
                    flash_param_init();
                    app_param_update();
                }
                break;
            case FLASH_STORE_CMD_WRITE_PARAM:
                flash_param_update();

                flashdb_status = bsp_flashdb_write(FLASHDB_KEY_INDEX_ALL_PARAM);
                break;
            case FLASH_STORE_CMD_ERASE_PARAM:
                // 先恢复出厂再写入flash，成功后系统复位
                bsp_system_global_irq_disable(); // 禁用全局中断，防止参数初始化过程中运行任务异常
                AppParamInit();     //应用层数据库初始化
                MotorCtrlInit();    //控制层数据库初始化
                flash_param_update();

                bsp_flashdb_key_delete(FLASHDB_KEY_INDEX_TQ_FC_TABLE);
                flashdb_status = bsp_flashdb_write(FLASHDB_KEY_INDEX_ALL_PARAM);

                if (flashdb_status == FLASHDB_NO_ERR)
                {
                    bsp_system_reset();
                }
                bsp_system_global_irq_enable(); // 恢复失败，使能全局中断，允许其他任务执行
                break;
            // 错误记录相关
            case FLASH_STORE_CMD_READ_ERROR:
                flashdb_status = bsp_flashdb_read(FLASHDB_KEY_INDEX_ERROR_RECORD);

                if (flashdb_status == FLASHDB_NO_ERR)
                {
                    for (uint16_t i = 0; i < ERROR_RECORD_NUM; i++)
                    {
                        p_AppErrorRecordsList[i] = kFlashHistoricalInfo.Error_records_list[i];
                    }
                }
                break;
            case FLASH_STORE_CMD_WRITE_ERROR:
                for (uint16_t i = 0; i < ERROR_RECORD_NUM; i++)
                {
                    kFlashHistoricalInfo.Error_records_list[i] = p_AppErrorRecordsList[i];
                }

                flashdb_status = bsp_flashdb_write(FLASHDB_KEY_INDEX_ERROR_RECORD);
                break;
            case FLASH_STORE_CMD_ERASE_ERROR:
                for (uint16_t i = 0; i < ERROR_RECORD_NUM; i++)
                {
                    p_AppErrorRecordsList[i] = 0;
                    kFlashHistoricalInfo.Error_records_list[i] = p_AppErrorRecordsList[i];
                }

                flashdb_status = bsp_flashdb_write(FLASHDB_KEY_INDEX_ERROR_RECORD);
                break;
            // 转矩摩擦补偿表相关
            case FLASH_STORE_CMD_READ_TQ_FC:
                flashdb_status = bsp_flashdb_read(FLASHDB_KEY_INDEX_TQ_FC_TABLE);
                break;
            case FLASH_STORE_CMD_WRITE_TQ_FC:
                flashdb_status = bsp_flashdb_write(FLASHDB_KEY_INDEX_TQ_FC_TABLE);
                break;
            case FLASH_STORE_CMD_ERASE_TQ_FC:
                flashdb_status = bsp_flashdb_key_delete(FLASHDB_KEY_INDEX_TQ_FC_TABLE);
                break;
            default:
                flashdb_status = FLASHDB_PART_NOT_FOUND;
                break;
        }

        if (flashdb_status != FLASHDB_NO_ERR)
        {
            set_app_Storage_status(FLASH_STORE_STATUS_ERROR);
            sys_set_bsp_error_state(ERROR_FLASH_STORE, ERROR_SET);
        }
        else
        {
            set_app_Storage_status(FLASH_STORE_STATUS_SUCCESS);
        }

        set_app_Storage_cmd(FLASH_STORE_CMD_NULL);

        //set_time_record_stop(9);
    }
}

/**
 * @brief 判断是否为写入或擦除操作
 * @param store_cmd 存储命令
 * @return true 为写入或擦除操作 false 不为写入或擦除操作
*/
static bool IsFlashWriteOrErase(FLASH_STORE_CMD store_cmd)
{
    if (store_cmd == FLASH_STORE_CMD_WRITE_PARAM || \
        store_cmd == FLASH_STORE_CMD_WRITE_ERROR || \
        store_cmd == FLASH_STORE_CMD_WRITE_TQ_FC || \
        store_cmd == FLASH_STORE_CMD_ERASE_PARAM || \
        store_cmd == FLASH_STORE_CMD_ERASE_ERROR || \
        store_cmd == FLASH_STORE_CMD_ERASE_TQ_FC)
    {
        return true;
    }
    return false;
}

/**
 * @brief 窗口检查擦写频率，是否超过最大允许次数，以保护Flash不被频繁擦写
 * @param store_cmd 存储命令
 * @return true 保护已锁定，禁止擦写 false 允许擦写
*/
static bool IsFlashWriteGuard(FLASH_STORE_CMD store_cmd)
{
    static bool is_protected_locked = false;
    static uint16_t write_count = 0;
    static uint16_t window_timer = 0;

    if (IsFlashWriteOrErase(store_cmd))
    {
        // 若Flash擦写保护已锁定，重启驱动器才自动解锁
        if (is_protected_locked)
        {
            return is_protected_locked;
        }

        if (write_count == 0)
        {
            window_timer = 0; // 窗口时间重置，开始计时
        }
        write_count++;
    }

    // 擦写动作触发窗口及次数检查
    if (write_count > 0)
    {
        window_timer++; // 窗口时间增加1ms
        if (window_timer >= STORE_WINDOW_TIME_SECONDS) // 窗口时间到，重置
        {
            window_timer = 0;
            write_count = 0;
        }
        else if (write_count >= STORE_MAX_WRITES_IN_WINDOW)
        {
            is_protected_locked = true; // 窗口内次数超限禁止擦写，并上锁
        }
    }

    return is_protected_locked;
}

/* USER CODE END AREA 1 */
