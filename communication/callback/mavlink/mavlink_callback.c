#include "mavlink_callback.h"

SendCallbackRegistry registry = {
    .callback = NULL,
};

SystemConfig kSystemConfig = {
    .param_save = 0,
    .system_reset = 0,
    .current_loop_freq = (uint32_t)CURRENT_FREQUENCY_HZ,
    .position_loop_freq = (uint32_t)POSITION_FREQUENCY_HZ,
};

#ifdef HPMSOC_HAS_HPMSDK_MCHTMR
ATTR_PLACE_AT_NONCACHEABLE uint8_t mavlink_tx_buff[MAVLINK_SEND_BUFF_SIZE];
ATTR_PLACE_AT_NONCACHEABLE uint8_t mavlink_rx_buff[MAVLINK_RECV_BUFF_SIZE];
#else
__attribute__((section(".RAM_D1"))) uint8_t mavlink_tx_buff[MAVLINK_SEND_BUFF_SIZE];
__attribute__((section(".RAM_D1"))) uint8_t mavlink_rx_buff[MAVLINK_RECV_BUFF_SIZE];
#endif

mavlink_scopeconfig_t scope_config;
mavlink_scopecontrol_t scope_control;
mavlink_scopedata_t scope_data;

mavlink_read_param_t read_param;
mavlink_waveformmap_t waveform_map;
mavlink_waveformdata_t waveform_data;
mavlink_systemconfig_t system_config_t;
mavlink_tableconfig_t table_config_t;
mavlink_tabledata_t table_data_t;
mavlink_appfiletransferstream_t appfile_transfer_stream_t;

//DATABASE_CODE_START_1
mavlink_pmsmconfig_t pmsm_config_t;
mavlink_elecidsininput_t elec_id_sin_input_t;
mavlink_elecidsinoutput_t elec_id_sin_output_t;
mavlink_elecidsinconfig_t elec_id_sin_config_t;
mavlink_mecidoutput_t mec_id_output_t;
mavlink_mecidconfig_t mec_id_config_t;
mavlink_notchfilterinput_t notch_filter_input_t;
mavlink_notchfilterinternal_t notch_filter_internal_t;
mavlink_notchfilteroutput_t notch_filter_output_t;
mavlink_mecidinput_t mec_id_input_t;
mavlink_inputshapinginput_t input_shaping_input_t;
mavlink_inputshapingconfig_t input_shaping_config_t;
mavlink_inputshapingoutput_t input_shaping_output_t;
mavlink_posspeedctlinput_t pos_speed_ctl_input_t;
mavlink_posspeedctloutput_t pos_speed_ctl_output_t;
mavlink_posspeedctlconfig_t pos_speed_ctl_config_t;
mavlink_motorctlsmconfig_t motor_ctl_sm_config_t;
mavlink_motorctlsminput_t motor_ctl_sm_input_t;
mavlink_motorctlsmoutput_t motor_ctl_sm_output_t;
mavlink_currentctlinput_t current_ctl_input_t;
mavlink_currentctlconfig_t current_ctl_config_t;
mavlink_currentctloutput_t current_ctl_output_t;
mavlink_notchfilterconfig_t notch_filter_config_t;
mavlink_speedobspllinput_t speed_obs_pll_input_t;
mavlink_speedobspllconfig_t speed_obs_pll_config_t;
mavlink_speedobsplloutput_t speed_obs_pll_output_t;
mavlink_elecangleidconfig_t elec_angle_id_config_t;
mavlink_elecangleidoutput_t elec_angle_id_output_t;
mavlink_elecangleidinput_t elec_angle_id_input_t;
mavlink_directionidinput_t direction_id_input_t;
mavlink_directionidconfig_t direction_id_config_t;
mavlink_directionidoutput_t direction_id_output_t;
mavlink_motorpossensorinput_t motor_pos_sensor_input_t;
mavlink_motorpossensorconfig_t motor_pos_sensor_config_t;
mavlink_motorpossensoroutput_t motor_pos_sensor_output_t;
mavlink_polepairsidinput_t pole_pairs_id_input_t;
mavlink_polepairsidconfig_t pole_pairs_id_config_t;
mavlink_polepairsidoutput_t pole_pairs_id_output_t;
mavlink_tqfcidinput_t tq_fc_id_input_t;
mavlink_tqfcidconfig_t tq_fc_id_config_t;
mavlink_tqfcidoutput_t tq_fc_id_output_t;
mavlink_reciprocalmotionconfig_t reciprocal_motion_config_t;
mavlink_reciprocalmotionoutput_t reciprocal_motion_output_t;
mavlink_referencesignalconfig_t reference_signal_config_t;
mavlink_referencesignaloutput_t reference_signal_output_t;
mavlink_appcontrolword_t app_control_word_t;
mavlink_appstatusinfo_t app_status_info_t;
mavlink_appopmode_t app_op_mode_t;
mavlink_appencoderconfig_t app_encoder_config_t;
mavlink_appbaseconfig_t app_base_config_t;
mavlink_appmotionparam_t app_motion_param_t;
mavlink_apprestrictparam_t app_restrict_param_t;
mavlink_appmotioninfo_t app_motion_info_t;
mavlink_appwindowparam_t app_window_param_t;
mavlink_appmotorconfig_t app_motor_config_t;
mavlink_appprotectconfig_t app_protect_config_t;
mavlink_mitctlinput_t mit_ctl_input_t;
mavlink_mitctlconfig_t mit_ctl_config_t;
mavlink_mitctloutput_t mit_ctl_output_t;
mavlink_apppermissionconfig_t app_permission_config_t;
mavlink_systemcmd_t system_cmd_t;
mavlink_loadpossensorinput_t load_pos_sensor_input_t;
mavlink_loadpossensorconfig_t load_pos_sensor_config_t;
mavlink_loadpossensoroutput_t load_pos_sensor_output_t;
mavlink_systemstatus_t system_status_t;
mavlink_encodercalibrationcmd_t encoder_calibration_cmd_t;
mavlink_encodercalibrationstatus_t encoder_calibration_status_t;
mavlink_custominfo_t custom_info_t;
mavlink_heartbit_t heart_bit_t;
mavlink_historicalinfo_t historical_info_t;
mavlink_simplantinput_t sim_plant_input_t;
mavlink_simplantoutput_t sim_plant_output_t;
mavlink_simplantconfig_t sim_plant_config_t;
mavlink_appdebugparam_t app_debug_param_t;
mavlink_appmavlinkconfig_t app_mavlink_config_t;
mavlink_appfiletransferconfig_t app_file_transfer_config_t;
mavlink_appfwupgradeparam_t app_fw_upgrade_param_t;
//DATABASE_CODE_STOP_1

static mavlink_message_t msg;
static mavlink_status_t status;
static mavlink_message_t send_msg;
static uint16_t mavlink_parse_fail_cnt = 0;  // 解析失败计数器

void MavlinkRecvCallback(Axis *axis, AxisDw *axis_dw, uint8_t rx_data[], uint32_t len)
{
    bool is_mavlink_parse_success = false;

    if (len > MAVLINK_RECV_BUFF_SIZE) {
        len = MAVLINK_RECV_BUFF_SIZE;
    }

    for (uint32_t i = 0; i < len; i++) {
        if (mavlink_parse_char(MAVLINK_COMM_0, rx_data[i], &msg, &status)) {
            mavlink_parse_fail_cnt = 0;  // 解析成功，重置失败计数器
            is_mavlink_parse_success = true;
            break;
        }
        else {
            // 解析失败，增加计数器
            mavlink_parse_fail_cnt++;
            // 超过阈值时重置状态和缓存
            if (mavlink_parse_fail_cnt >= MAVLINK_PARSE_ERROR_THRESHOLD) {
                // 重置MAVLink通道状态、清零接收缓冲区
                mavlink_reset_channel_status(MAVLINK_COMM_0);
                mavlink_message_t *rx_buffer = mavlink_get_channel_buffer(MAVLINK_COMM_0);
                memset(rx_buffer, 0, sizeof(mavlink_message_t));
                // 重置失败计数器
                mavlink_parse_fail_cnt = 0;
            }
        }
    }

    if (!is_mavlink_parse_success) {
        return;
    }

    uint8_t sys_id = get_app_Sys_id();
    uint8_t comp_id = get_app_Comp_id();

    if(msg.msgid == MAVLINK_MSG_ID_READ_PARAM){
        mavlink_msg_read_param_decode(&msg, &read_param);
        switch (read_param.struct_id){
            case MAVLINK_MSG_ID_ScopeConfig:
                mavlink_scope_config_callback(&scope_config, &kScopeObject, SCOPE_READ);
                mavlink_msg_scopeconfig_encode(sys_id, comp_id, &send_msg, &scope_config);
                break; 
            case MAVLINK_MSG_ID_ScopeControl:
                mavlink_scope_control_callback(&scope_control, &kScopeObject, SCOPE_READ);
                mavlink_msg_scopecontrol_encode(sys_id, comp_id, &send_msg, &scope_control);
                break;
            case MAVLINK_MSG_ID_ScopeData:
                mavlink_get_scope_data_callback(&scope_data, &scope_control, &kScopeObject, SCOPE_READ);
                mavlink_msg_scopedata_encode(sys_id, comp_id, &send_msg, &scope_data);
                break;
            case MAVLINK_MSG_ID_WaveformMap:
                get_waveform_map(waveform_map.waveform_map_info);
                mavlink_msg_waveformmap_encode(sys_id, comp_id, &send_msg, &waveform_map);
                break;
            case MAVLINK_MSG_ID_WaveformData:
                get_waveform_data(waveform_data.waveform_data_array);
                mavlink_msg_waveformdata_encode(sys_id, comp_id, &send_msg, &waveform_data);
                break;
            case MAVLINK_MSG_ID_SystemConfig:
                system_config_t.param_save = kSystemConfig.param_save;
                system_config_t.system_reset = kSystemConfig.system_reset;
                system_config_t.current_loop_freq = kSystemConfig.current_loop_freq;
                system_config_t.position_loop_freq = kSystemConfig.position_loop_freq;
                mavlink_msg_systemconfig_encode(sys_id, comp_id, &send_msg, (mavlink_systemconfig_t *)&system_config_t);
                break;
            case MAVLINK_MSG_ID_TableConfig:
                mavlink_msg_tableconfig_encode(sys_id, comp_id, &send_msg, (mavlink_tableconfig_t *)&table_config_t);
                break;
            case MAVLINK_MSG_ID_TableData:
                memcpy(&table_data_t.table_data, axis_dw->tq_fc_id_InstanceData.rtdw.com_table + table_config_t.table_index_offset * 20, sizeof(table_data_t.table_data));
                mavlink_msg_tabledata_encode(sys_id, comp_id, &send_msg, (mavlink_tabledata_t *)&table_data_t);
                break;
            case MAVLINK_MSG_ID_AppFileTransferStream:
                mavlink_msg_appfiletransferstream_decode(&msg, &appfile_transfer_stream_t);
                break;
//DATABASE_CODE_START_2
            case MAVLINK_MSG_ID_PmsmConfig:
                pmsm_config_t.b = axis->pmsm_config.b;
                pmsm_config_t.fc = axis->pmsm_config.fc;
                pmsm_config_t.flux = axis->pmsm_config.flux;
                pmsm_config_t.j = axis->pmsm_config.j;
                pmsm_config_t.ld = axis->pmsm_config.ld;
                pmsm_config_t.lq = axis->pmsm_config.lq;
                pmsm_config_t.peak_current = axis->pmsm_config.peak_current;
                pmsm_config_t.pn = axis->pmsm_config.pn;
                pmsm_config_t.r = axis->pmsm_config.r;
                pmsm_config_t.rated_current = axis->pmsm_config.rated_current;
                pmsm_config_t.speed_max_rpm = axis->pmsm_config.speed_max_rpm;
                pmsm_config_t.tp_s = axis->pmsm_config.tp_s;
                pmsm_config_t.tc_s = axis->pmsm_config.tc_s;
                pmsm_config_t.enc_line_p_n = axis->pmsm_config.enc_line_p_n;
                pmsm_config_t.kt = axis->pmsm_config.kt;
                mavlink_msg_pmsmconfig_encode(sys_id, comp_id, &send_msg, (mavlink_pmsmconfig_t *)&pmsm_config_t);
                break;
            case MAVLINK_MSG_ID_ElecIdSinInput:
                memcpy(&elec_id_sin_input_t.i_abc_now_A, axis->elec_id_sin_input.i_abc_now_A, sizeof(elec_id_sin_input_t.i_abc_now_A));
                mavlink_msg_elecidsininput_encode(sys_id, comp_id, &send_msg, (mavlink_elecidsininput_t *)&elec_id_sin_input_t);
                break;
            case MAVLINK_MSG_ID_ElecIdSinOutput:
                elec_id_sin_output_t.state_now = axis->elec_id_sin_output.state_now;
                memcpy(&elec_id_sin_output_t.u_abc_tar_V, axis->elec_id_sin_output.u_abc_tar_V, sizeof(elec_id_sin_output_t.u_abc_tar_V));
                elec_id_sin_output_t.u_alpha_now_V = axis->elec_id_sin_output.u_alpha_now_V;
                elec_id_sin_output_t.i_alpha_now_A = axis->elec_id_sin_output.i_alpha_now_A;
                mavlink_msg_elecidsinoutput_encode(sys_id, comp_id, &send_msg, (mavlink_elecidsinoutput_t *)&elec_id_sin_output_t);
                break;
            case MAVLINK_MSG_ID_ElecIdSinConfig:
                elec_id_sin_config_t.dt_s = axis->elec_id_sin_config.dt_s;
                elec_id_sin_config_t.end_fs_Hz = axis->elec_id_sin_config.end_fs_Hz;
                elec_id_sin_config_t.i_max_A = axis->elec_id_sin_config.i_max_A;
                elec_id_sin_config_t.init_fs_Hz = axis->elec_id_sin_config.init_fs_Hz;
                elec_id_sin_config_t.target_time_s = axis->elec_id_sin_config.target_time_s;
                elec_id_sin_config_t.u_max_V = axis->elec_id_sin_config.u_max_V;
                elec_id_sin_config_t.wait_time_s = axis->elec_id_sin_config.wait_time_s;
                mavlink_msg_elecidsinconfig_encode(sys_id, comp_id, &send_msg, (mavlink_elecidsinconfig_t *)&elec_id_sin_config_t);
                break;
            case MAVLINK_MSG_ID_MecIdOutput:
                mec_id_output_t.iq_tar_A = axis->mec_id_output.iq_tar_A;
                mec_id_output_t.state_now = axis->mec_id_output.state_now;
                mavlink_msg_mecidoutput_encode(sys_id, comp_id, &send_msg, (mavlink_mecidoutput_t *)&mec_id_output_t);
                break;
            case MAVLINK_MSG_ID_MecIdConfig:
                mec_id_config_t.dt_s = axis->mec_id_config.dt_s;
                mec_id_config_t.end_fs_Hz = axis->mec_id_config.end_fs_Hz;
                mec_id_config_t.start_fs_Hz = axis->mec_id_config.start_fs_Hz;
                mec_id_config_t.target_time_s = axis->mec_id_config.target_time_s;
                mec_id_config_t.i_max_A = axis->mec_id_config.i_max_A;
                mec_id_config_t.search_speed_max_rad_s = axis->mec_id_config.search_speed_max_rad_s;
                mec_id_config_t.wait_time_s = axis->mec_id_config.wait_time_s;
                mec_id_config_t.signal_type = axis->mec_id_config.signal_type;
                mavlink_msg_mecidconfig_encode(sys_id, comp_id, &send_msg, (mavlink_mecidconfig_t *)&mec_id_config_t);
                break;
            case MAVLINK_MSG_ID_NotchFilterInput:
                notch_filter_input_t.iq_tar_A = axis->notch_filter_input.iq_tar_A;
                mavlink_msg_notchfilterinput_encode(sys_id, comp_id, &send_msg, (mavlink_notchfilterinput_t *)&notch_filter_input_t);
                break;
            case MAVLINK_MSG_ID_NotchFilterInternal:
                memcpy(&notch_filter_internal_t.u0, axis->notch_filter_internal.u0, sizeof(notch_filter_internal_t.u0));
                memcpy(&notch_filter_internal_t.u1, axis->notch_filter_internal.u1, sizeof(notch_filter_internal_t.u1));
                memcpy(&notch_filter_internal_t.u2, axis->notch_filter_internal.u2, sizeof(notch_filter_internal_t.u2));
                memcpy(&notch_filter_internal_t.y0, axis->notch_filter_internal.y0, sizeof(notch_filter_internal_t.y0));
                memcpy(&notch_filter_internal_t.y1, axis->notch_filter_internal.y1, sizeof(notch_filter_internal_t.y1));
                mavlink_msg_notchfilterinternal_encode(sys_id, comp_id, &send_msg, (mavlink_notchfilterinternal_t *)&notch_filter_internal_t);
                break;
            case MAVLINK_MSG_ID_NotchFilterOutput:
                notch_filter_output_t.iq_tar_filter_A = axis->notch_filter_output.iq_tar_filter_A;
                mavlink_msg_notchfilteroutput_encode(sys_id, comp_id, &send_msg, (mavlink_notchfilteroutput_t *)&notch_filter_output_t);
                break;
            case MAVLINK_MSG_ID_MecIdInput:
                mec_id_input_t.speed_now_rad_s = axis->mec_id_input.speed_now_rad_s;
                mavlink_msg_mecidinput_encode(sys_id, comp_id, &send_msg, (mavlink_mecidinput_t *)&mec_id_input_t);
                break;
            case MAVLINK_MSG_ID_InputShapingInput:
                input_shaping_input_t.pos_cmd_p = axis->input_shaping_input.pos_cmd_p;
                input_shaping_input_t.pos_cmd_p_init = axis->input_shaping_input.pos_cmd_p_init;
                mavlink_msg_inputshapinginput_encode(sys_id, comp_id, &send_msg, (mavlink_inputshapinginput_t *)&input_shaping_input_t);
                break;
            case MAVLINK_MSG_ID_InputShapingConfig:
                input_shaping_config_t.wn_Hz = axis->input_shaping_config.wn_Hz;
                input_shaping_config_t.run_frq_Hz = axis->input_shaping_config.run_frq_Hz;
                input_shaping_config_t.enable = axis->input_shaping_config.enable;
                mavlink_msg_inputshapingconfig_encode(sys_id, comp_id, &send_msg, (mavlink_inputshapingconfig_t *)&input_shaping_config_t);
                break;
            case MAVLINK_MSG_ID_InputShapingOutput:
                input_shaping_output_t.pos_cmd_shaping_p = axis->input_shaping_output.pos_cmd_shaping_p;
                mavlink_msg_inputshapingoutput_encode(sys_id, comp_id, &send_msg, (mavlink_inputshapingoutput_t *)&input_shaping_output_t);
                break;
            case MAVLINK_MSG_ID_PosSpeedCtlInput:
                pos_speed_ctl_input_t.pos_tar_p = axis->pos_speed_ctl_input.pos_tar_p;
                pos_speed_ctl_input_t.pos_now_p = axis->pos_speed_ctl_input.pos_now_p;
                pos_speed_ctl_input_t.iq_max_A = axis->pos_speed_ctl_input.iq_max_A;
                pos_speed_ctl_input_t.speed_tar_p_s = axis->pos_speed_ctl_input.speed_tar_p_s;
                pos_speed_ctl_input_t.acc_tar_p_ss = axis->pos_speed_ctl_input.acc_tar_p_ss;
                pos_speed_ctl_input_t.speed_now_rad_s = axis->pos_speed_ctl_input.speed_now_rad_s;
                pos_speed_ctl_input_t.position_offset_p = axis->pos_speed_ctl_input.position_offset_p;
                pos_speed_ctl_input_t.speed_offset_p_s = axis->pos_speed_ctl_input.speed_offset_p_s;
                mavlink_msg_posspeedctlinput_encode(sys_id, comp_id, &send_msg, (mavlink_posspeedctlinput_t *)&pos_speed_ctl_input_t);
                break;
            case MAVLINK_MSG_ID_PosSpeedCtlOutput:
                pos_speed_ctl_output_t.iq_tar_A = axis->pos_speed_ctl_output.iq_tar_A;
                pos_speed_ctl_output_t.pos_ctl_error_p = axis->pos_speed_ctl_output.pos_ctl_error_p;
                pos_speed_ctl_output_t.dob_iq_com_A = axis->pos_speed_ctl_output.dob_iq_com_A;
                mavlink_msg_posspeedctloutput_encode(sys_id, comp_id, &send_msg, (mavlink_posspeedctloutput_t *)&pos_speed_ctl_output_t);
                break;
            case MAVLINK_MSG_ID_PosSpeedCtlConfig:
                pos_speed_ctl_config_t.aff = axis->pos_speed_ctl_config.aff;
                pos_speed_ctl_config_t.vff = axis->pos_speed_ctl_config.vff;
                pos_speed_ctl_config_t.enc_line_inv_p_n = axis->pos_speed_ctl_config.enc_line_inv_p_n;
                pos_speed_ctl_config_t.j_kt = axis->pos_speed_ctl_config.j_kt;
                pos_speed_ctl_config_t.ki_s = axis->pos_speed_ctl_config.ki_s;
                pos_speed_ctl_config_t.kp_p = axis->pos_speed_ctl_config.kp_p;
                pos_speed_ctl_config_t.kp_s = axis->pos_speed_ctl_config.kp_s;
                pos_speed_ctl_config_t.speed_max_rad_s = axis->pos_speed_ctl_config.speed_max_rad_s;
                pos_speed_ctl_config_t.tp_s = axis->pos_speed_ctl_config.tp_s;
                pos_speed_ctl_config_t.mode = axis->pos_speed_ctl_config.mode;
                pos_speed_ctl_config_t.dob_wn_Hz = axis->pos_speed_ctl_config.dob_wn_Hz;
                pos_speed_ctl_config_t.dob_enable = axis->pos_speed_ctl_config.dob_enable;
                pos_speed_ctl_config_t.dynamic_integration_enable = axis->pos_speed_ctl_config.dynamic_integration_enable;
                mavlink_msg_posspeedctlconfig_encode(sys_id, comp_id, &send_msg, (mavlink_posspeedctlconfig_t *)&pos_speed_ctl_config_t);
                break;
            case MAVLINK_MSG_ID_MotorCtlSmConfig:
                motor_ctl_sm_config_t.mode = axis->motor_ctl_sm_config.mode;
                motor_ctl_sm_config_t.under_voltage_protection_V = axis->motor_ctl_sm_config.under_voltage_protection_V;
                motor_ctl_sm_config_t.over_voltage_protection_V = axis->motor_ctl_sm_config.over_voltage_protection_V;
                motor_ctl_sm_config_t.over_speed_protection_rad_s = axis->motor_ctl_sm_config.over_speed_protection_rad_s;
                motor_ctl_sm_config_t.under_temperature_protection_d = axis->motor_ctl_sm_config.under_temperature_protection_d;
                motor_ctl_sm_config_t.over_temperature_protection_d = axis->motor_ctl_sm_config.over_temperature_protection_d;
                motor_ctl_sm_config_t.position_following_error_protection = axis->motor_ctl_sm_config.position_following_error_protection;
                motor_ctl_sm_config_t.error_enable = axis->motor_ctl_sm_config.error_enable;
                motor_ctl_sm_config_t.over_current_protection_A = axis->motor_ctl_sm_config.over_current_protection_A;
                mavlink_msg_motorctlsmconfig_encode(sys_id, comp_id, &send_msg, (mavlink_motorctlsmconfig_t *)&motor_ctl_sm_config_t);
                break;
            case MAVLINK_MSG_ID_MotorCtlSmInput:
                motor_ctl_sm_input_t.motor_enable = axis->motor_ctl_sm_input.motor_enable;
                motor_ctl_sm_input_t.hw_ready_state = axis->motor_ctl_sm_input.hw_ready_state;
                mavlink_msg_motorctlsminput_encode(sys_id, comp_id, &send_msg, (mavlink_motorctlsminput_t *)&motor_ctl_sm_input_t);
                break;
            case MAVLINK_MSG_ID_MotorCtlSmOutput:
                motor_ctl_sm_output_t.state = axis->motor_ctl_sm_output.state;
                motor_ctl_sm_output_t.error = axis->motor_ctl_sm_output.error;
                motor_ctl_sm_output_t.warning = axis->motor_ctl_sm_output.warning;
                motor_ctl_sm_output_t.mode_now = axis->motor_ctl_sm_output.mode_now;
                motor_ctl_sm_output_t.motor_enable_last = axis->motor_ctl_sm_output.motor_enable_last;
                motor_ctl_sm_output_t.state_last = axis->motor_ctl_sm_output.state_last;
                mavlink_msg_motorctlsmoutput_encode(sys_id, comp_id, &send_msg, (mavlink_motorctlsmoutput_t *)&motor_ctl_sm_output_t);
                break;
            case MAVLINK_MSG_ID_CurrentCtlInput:
                memcpy(&current_ctl_input_t.idq_tar_A, axis->current_ctl_input.idq_tar_A, sizeof(current_ctl_input_t.idq_tar_A));
                memcpy(&current_ctl_input_t.iabc_now_A, axis->current_ctl_input.iabc_now_A, sizeof(current_ctl_input_t.iabc_now_A));
                current_ctl_input_t.elec_theta_rad = axis->current_ctl_input.elec_theta_rad;
                current_ctl_input_t.dc_bus_now_V = axis->current_ctl_input.dc_bus_now_V;
                current_ctl_input_t.mode = axis->current_ctl_input.mode;
                memcpy(&current_ctl_input_t.uabc_tar_V, axis->current_ctl_input.uabc_tar_V, sizeof(current_ctl_input_t.uabc_tar_V));
                current_ctl_input_t.driver_temp = axis->current_ctl_input.driver_temp;
                current_ctl_input_t.elec_angle_speed_rad_s = axis->current_ctl_input.elec_angle_speed_rad_s;
                current_ctl_input_t.iq_offset_A = axis->current_ctl_input.iq_offset_A;
                mavlink_msg_currentctlinput_encode(sys_id, comp_id, &send_msg, (mavlink_currentctlinput_t *)&current_ctl_input_t);
                break;
            case MAVLINK_MSG_ID_CurrentCtlConfig:
                current_ctl_config_t.i_noise_A = axis->current_ctl_config.i_noise_A;
                current_ctl_config_t.comp_du_V = axis->current_ctl_config.comp_du_V;
                current_ctl_config_t.bandwidth_percentage = axis->current_ctl_config.bandwidth_percentage;
                current_ctl_config_t.dt_s = axis->current_ctl_config.dt_s;
                current_ctl_config_t.flux_wb = axis->current_ctl_config.flux_wb;
                current_ctl_config_t.kp_ld = axis->current_ctl_config.kp_ld;
                current_ctl_config_t.ki_ld = axis->current_ctl_config.ki_ld;
                current_ctl_config_t.kp_lq = axis->current_ctl_config.kp_lq;
                current_ctl_config_t.ki_lq = axis->current_ctl_config.ki_lq;
                current_ctl_config_t.pwm_duty_cycle_max = axis->current_ctl_config.pwm_duty_cycle_max;
                current_ctl_config_t.elec_angle_compensation = axis->current_ctl_config.elec_angle_compensation;
                current_ctl_config_t.phase_dir = axis->current_ctl_config.phase_dir;
                mavlink_msg_currentctlconfig_encode(sys_id, comp_id, &send_msg, (mavlink_currentctlconfig_t *)&current_ctl_config_t);
                break;
            case MAVLINK_MSG_ID_CurrentCtlOutput:
                memcpy(&current_ctl_output_t.uabc_tar_comp_V, axis->current_ctl_output.uabc_tar_comp_V, sizeof(current_ctl_output_t.uabc_tar_comp_V));
                memcpy(&current_ctl_output_t.idq_now_A, axis->current_ctl_output.idq_now_A, sizeof(current_ctl_output_t.idq_now_A));
                memcpy(&current_ctl_output_t.uabc_tar_org_V, axis->current_ctl_output.uabc_tar_org_V, sizeof(current_ctl_output_t.uabc_tar_org_V));
                mavlink_msg_currentctloutput_encode(sys_id, comp_id, &send_msg, (mavlink_currentctloutput_t *)&current_ctl_output_t);
                break;
            case MAVLINK_MSG_ID_NotchFilterConfig:
                memcpy(&notch_filter_config_t.frq, axis->notch_filter_config.frq, sizeof(notch_filter_config_t.frq));
                memcpy(&notch_filter_config_t.width, axis->notch_filter_config.width, sizeof(notch_filter_config_t.width));
                memcpy(&notch_filter_config_t.depth, axis->notch_filter_config.depth, sizeof(notch_filter_config_t.depth));
                mavlink_msg_notchfilterconfig_encode(sys_id, comp_id, &send_msg, (mavlink_notchfilterconfig_t *)&notch_filter_config_t);
                break;
            case MAVLINK_MSG_ID_SpeedObsPllInput:
                speed_obs_pll_input_t.pos_now_p = axis->speed_obs_pll_input.pos_now_p;
                mavlink_msg_speedobspllinput_encode(sys_id, comp_id, &send_msg, (mavlink_speedobspllinput_t *)&speed_obs_pll_input_t);
                break;
            case MAVLINK_MSG_ID_SpeedObsPllConfig:
                speed_obs_pll_config_t.tp_s = axis->speed_obs_pll_config.tp_s;
                speed_obs_pll_config_t.wn_Hz = axis->speed_obs_pll_config.wn_Hz;
                speed_obs_pll_config_t.enc_line_inv_p_n = axis->speed_obs_pll_config.enc_line_inv_p_n;
                speed_obs_pll_config_t.speed_obs_max_rad_s = axis->speed_obs_pll_config.speed_obs_max_rad_s;
                mavlink_msg_speedobspllconfig_encode(sys_id, comp_id, &send_msg, (mavlink_speedobspllconfig_t *)&speed_obs_pll_config_t);
                break;
            case MAVLINK_MSG_ID_SpeedObsPllOutput:
                speed_obs_pll_output_t.ev_rad_s = axis->speed_obs_pll_output.ev_rad_s;
                mavlink_msg_speedobsplloutput_encode(sys_id, comp_id, &send_msg, (mavlink_speedobsplloutput_t *)&speed_obs_pll_output_t);
                break;
            case MAVLINK_MSG_ID_ElecAngleIdConfig:
                elec_angle_id_config_t.id_max_A = axis->elec_angle_id_config.id_max_A;
                elec_angle_id_config_t.dt_s = axis->elec_angle_id_config.dt_s;
                elec_angle_id_config_t.method = axis->elec_angle_id_config.method;
                elec_angle_id_config_t.angle_add_rad = axis->elec_angle_id_config.angle_add_rad;
                elec_angle_id_config_t.wait_time_s = axis->elec_angle_id_config.wait_time_s;
                elec_angle_id_config_t.test_angle_rad = axis->elec_angle_id_config.test_angle_rad;
                elec_angle_id_config_t.current_slope_percentage = axis->elec_angle_id_config.current_slope_percentage;
                mavlink_msg_elecangleidconfig_encode(sys_id, comp_id, &send_msg, (mavlink_elecangleidconfig_t *)&elec_angle_id_config_t);
                break;
            case MAVLINK_MSG_ID_ElecAngleIdOutput:
                elec_angle_id_output_t.id_tar_A = axis->elec_angle_id_output.id_tar_A;
                elec_angle_id_output_t.elec_bias_rad = axis->elec_angle_id_output.elec_bias_rad;
                elec_angle_id_output_t.state_now = axis->elec_angle_id_output.state_now;
                memcpy(&elec_angle_id_output_t.elec_bias_buff_rad, axis->elec_angle_id_output.elec_bias_buff_rad, sizeof(elec_angle_id_output_t.elec_bias_buff_rad));
                elec_angle_id_output_t.step_num = axis->elec_angle_id_output.step_num;
                mavlink_msg_elecangleidoutput_encode(sys_id, comp_id, &send_msg, (mavlink_elecangleidoutput_t *)&elec_angle_id_output_t);
                break;
            case MAVLINK_MSG_ID_ElecAngleIdInput:
                elec_angle_id_input_t.pos_now_rad = axis->elec_angle_id_input.pos_now_rad;
                mavlink_msg_elecangleidinput_encode(sys_id, comp_id, &send_msg, (mavlink_elecangleidinput_t *)&elec_angle_id_input_t);
                break;
            case MAVLINK_MSG_ID_DirectionIdInput:
                direction_id_input_t.enc_counts_sum_p = axis->direction_id_input.enc_counts_sum_p;
                mavlink_msg_directionidinput_encode(sys_id, comp_id, &send_msg, (mavlink_directionidinput_t *)&direction_id_input_t);
                break;
            case MAVLINK_MSG_ID_DirectionIdConfig:
                direction_id_config_t.elec_angle_add_rad = axis->direction_id_config.elec_angle_add_rad;
                direction_id_config_t.current_slope_percentage = axis->direction_id_config.current_slope_percentage;
                direction_id_config_t.id_tar_max_A = axis->direction_id_config.id_tar_max_A;
                mavlink_msg_directionidconfig_encode(sys_id, comp_id, &send_msg, (mavlink_directionidconfig_t *)&direction_id_config_t);
                break;
            case MAVLINK_MSG_ID_DirectionIdOutput:
                direction_id_output_t.elec_angle_tar_rad = axis->direction_id_output.elec_angle_tar_rad;
                direction_id_output_t.direction = axis->direction_id_output.direction;
                direction_id_output_t.state_now = axis->direction_id_output.state_now;
                direction_id_output_t.id_tar_A = axis->direction_id_output.id_tar_A;
                mavlink_msg_directionidoutput_encode(sys_id, comp_id, &send_msg, (mavlink_directionidoutput_t *)&direction_id_output_t);
                break;
            case MAVLINK_MSG_ID_MotorPosSensorInput:
                motor_pos_sensor_input_t.enc_counts_now_p = axis->motor_pos_sensor_input.enc_counts_now_p;
                mavlink_msg_motorpossensorinput_encode(sys_id, comp_id, &send_msg, (mavlink_motorpossensorinput_t *)&motor_pos_sensor_input_t);
                break;
            case MAVLINK_MSG_ID_MotorPosSensorConfig:
                motor_pos_sensor_config_t.enc_line_p_n = axis->motor_pos_sensor_config.enc_line_p_n;
                motor_pos_sensor_config_t.init_pos_p = axis->motor_pos_sensor_config.init_pos_p;
                motor_pos_sensor_config_t.pn = axis->motor_pos_sensor_config.pn;
                motor_pos_sensor_config_t.elec_angle_bias_rad = axis->motor_pos_sensor_config.elec_angle_bias_rad;
                motor_pos_sensor_config_t.dir = axis->motor_pos_sensor_config.dir;
                mavlink_msg_motorpossensorconfig_encode(sys_id, comp_id, &send_msg, (mavlink_motorpossensorconfig_t *)&motor_pos_sensor_config_t);
                break;
            case MAVLINK_MSG_ID_MotorPosSensorOutput:
                motor_pos_sensor_output_t.enc_sum_p = axis->motor_pos_sensor_output.enc_sum_p;
                motor_pos_sensor_output_t.elec_angle_now_rad = axis->motor_pos_sensor_output.elec_angle_now_rad;
                mavlink_msg_motorpossensoroutput_encode(sys_id, comp_id, &send_msg, (mavlink_motorpossensoroutput_t *)&motor_pos_sensor_output_t);
                break;
            case MAVLINK_MSG_ID_PolePairsIdInput:
                pole_pairs_id_input_t.enc_counts_sum_p = axis->pole_pairs_id_input.enc_counts_sum_p;
                mavlink_msg_polepairsidinput_encode(sys_id, comp_id, &send_msg, (mavlink_polepairsidinput_t *)&pole_pairs_id_input_t);
                break;
            case MAVLINK_MSG_ID_PolePairsIdConfig:
                pole_pairs_id_config_t.elec_angle_add = axis->pole_pairs_id_config.elec_angle_add;
                pole_pairs_id_config_t.enc_line_p_n = axis->pole_pairs_id_config.enc_line_p_n;
                pole_pairs_id_config_t.id_tar_max_A = axis->pole_pairs_id_config.id_tar_max_A;
                pole_pairs_id_config_t.current_slope_percentage = axis->pole_pairs_id_config.current_slope_percentage;
                mavlink_msg_polepairsidconfig_encode(sys_id, comp_id, &send_msg, (mavlink_polepairsidconfig_t *)&pole_pairs_id_config_t);
                break;
            case MAVLINK_MSG_ID_PolePairsIdOutput:
                pole_pairs_id_output_t.pn_id = axis->pole_pairs_id_output.pn_id;
                pole_pairs_id_output_t.state_now = axis->pole_pairs_id_output.state_now;
                pole_pairs_id_output_t.elec_angle_tar_rad = axis->pole_pairs_id_output.elec_angle_tar_rad;
                pole_pairs_id_output_t.id_tar_A = axis->pole_pairs_id_output.id_tar_A;
                mavlink_msg_polepairsidoutput_encode(sys_id, comp_id, &send_msg, (mavlink_polepairsidoutput_t *)&pole_pairs_id_output_t);
                break;
            case MAVLINK_MSG_ID_TqFcIdInput:
                tq_fc_id_input_t.iq_com_A = axis->tq_fc_id_input.iq_com_A;
                tq_fc_id_input_t.pos_abs_p = axis->tq_fc_id_input.pos_abs_p;
                tq_fc_id_input_t.pos_init_p = axis->tq_fc_id_input.pos_init_p;
                tq_fc_id_input_t.start = axis->tq_fc_id_input.start;
                mavlink_msg_tqfcidinput_encode(sys_id, comp_id, &send_msg, (mavlink_tqfcidinput_t *)&tq_fc_id_input_t);
                break;
            case MAVLINK_MSG_ID_TqFcIdConfig:
                tq_fc_id_config_t.enc_line_p_n = axis->tq_fc_id_config.enc_line_p_n;
                tq_fc_id_config_t.iq_com_enable = axis->tq_fc_id_config.iq_com_enable;
                tq_fc_id_config_t.tq_com_enable = axis->tq_fc_id_config.tq_com_enable;
                tq_fc_id_config_t.fc_com_enable = axis->tq_fc_id_config.fc_com_enable;
                tq_fc_id_config_t.fc_p_com = axis->tq_fc_id_config.fc_p_com;
                tq_fc_id_config_t.fc_n_com = axis->tq_fc_id_config.fc_n_com;
                mavlink_msg_tqfcidconfig_encode(sys_id, comp_id, &send_msg, (mavlink_tqfcidconfig_t *)&tq_fc_id_config_t);
                break;
            case MAVLINK_MSG_ID_TqFcIdOutput:
                tq_fc_id_output_t.pos_cmd_p = axis->tq_fc_id_output.pos_cmd_p;
                tq_fc_id_output_t.state_now = axis->tq_fc_id_output.state_now;
                mavlink_msg_tqfcidoutput_encode(sys_id, comp_id, &send_msg, (mavlink_tqfcidoutput_t *)&tq_fc_id_output_t);
                break;
            case MAVLINK_MSG_ID_ReciprocalMotionConfig:
                reciprocal_motion_config_t.pos_tar1_p = axis->reciprocal_motion_config.pos_tar1_p;
                reciprocal_motion_config_t.pos_tar2_p = axis->reciprocal_motion_config.pos_tar2_p;
                reciprocal_motion_config_t.dwell_time_s = axis->reciprocal_motion_config.dwell_time_s;
                reciprocal_motion_config_t.profile_velocity_p_s = axis->reciprocal_motion_config.profile_velocity_p_s;
                reciprocal_motion_config_t.profile_acc_p_ss = axis->reciprocal_motion_config.profile_acc_p_ss;
                reciprocal_motion_config_t.profile_dec_p_ss = axis->reciprocal_motion_config.profile_dec_p_ss;
                reciprocal_motion_config_t.dt_s = axis->reciprocal_motion_config.dt_s;
                mavlink_msg_reciprocalmotionconfig_encode(sys_id, comp_id, &send_msg, (mavlink_reciprocalmotionconfig_t *)&reciprocal_motion_config_t);
                break;
            case MAVLINK_MSG_ID_ReciprocalMotionOutput:
                reciprocal_motion_output_t.pos_tar_p = axis->reciprocal_motion_output.pos_tar_p;
                reciprocal_motion_output_t.v_tar_p_s = axis->reciprocal_motion_output.v_tar_p_s;
                reciprocal_motion_output_t.acc_tar_p_ss = axis->reciprocal_motion_output.acc_tar_p_ss;
                reciprocal_motion_output_t.state_now = axis->reciprocal_motion_output.state_now;
                mavlink_msg_reciprocalmotionoutput_encode(sys_id, comp_id, &send_msg, (mavlink_reciprocalmotionoutput_t *)&reciprocal_motion_output_t);
                break;
            case MAVLINK_MSG_ID_ReferenceSignalConfig:
                reference_signal_config_t.dt_s = axis->reference_signal_config.dt_s;
                reference_signal_config_t.signal_type = axis->reference_signal_config.signal_type;
                reference_signal_config_t.amp = axis->reference_signal_config.amp;
                reference_signal_config_t.frq_Hz = axis->reference_signal_config.frq_Hz;
                reference_signal_config_t.bias = axis->reference_signal_config.bias;
                reference_signal_config_t.signal_target = axis->reference_signal_config.signal_target;
                reference_signal_config_t.signal_start_pos = axis->reference_signal_config.signal_start_pos;
                mavlink_msg_referencesignalconfig_encode(sys_id, comp_id, &send_msg, (mavlink_referencesignalconfig_t *)&reference_signal_config_t);
                break;
            case MAVLINK_MSG_ID_ReferenceSignalOutput:
                reference_signal_output_t.signal_out = axis->reference_signal_output.signal_out;
                reference_signal_output_t.signal_pos = axis->reference_signal_output.signal_pos;
                reference_signal_output_t.signal_vel = axis->reference_signal_output.signal_vel;
                reference_signal_output_t.signal_acc = axis->reference_signal_output.signal_acc;
                mavlink_msg_referencesignaloutput_encode(sys_id, comp_id, &send_msg, (mavlink_referencesignaloutput_t *)&reference_signal_output_t);
                break;
            case MAVLINK_MSG_ID_AppControlWord:
                app_control_word_t.Controlword = get_app_Controlword();
                app_control_word_t.Halt_running_cmd = get_app_Halt_running_cmd();
                mavlink_msg_appcontrolword_encode(sys_id, comp_id, &send_msg, (mavlink_appcontrolword_t *)&app_control_word_t);
                break;
            case MAVLINK_MSG_ID_AppStatusInfo:
                app_status_info_t.Statusword = get_app_Statusword();
                app_status_info_t.Error_word = get_app_Error_word();
                app_status_info_t.DC_link_circuit_voltage = get_app_DC_link_circuit_voltage();
                app_status_info_t.Drive_accumulated_heat = get_app_Drive_accumulated_heat();
                app_status_info_t.Drive_temperature = get_app_Drive_temperature();
                app_status_info_t.Alarm_word = get_app_Alarm_word();
                app_status_info_t.Modes_of_operation_display = get_app_Modes_of_operation_display();
                app_status_info_t.Version = get_app_Version();
                app_status_info_t.Motor_temperature = get_app_Motor_temperature();
                app_status_info_t.Motor_power = get_app_Motor_power();
                app_status_info_t.Mcu_temperature = get_app_Mcu_temperature();
                app_status_info_t.Digital_io_inputs_status = get_app_Digital_io_inputs_status();
                app_status_info_t.Brake_state = get_app_Brake_state();
                mavlink_msg_appstatusinfo_encode(sys_id, comp_id, &send_msg, (mavlink_appstatusinfo_t *)&app_status_info_t);
                break;
            case MAVLINK_MSG_ID_AppOpMode:
                app_op_mode_t.Modes_of_operation = get_app_Modes_of_operation();
                mavlink_msg_appopmode_encode(sys_id, comp_id, &send_msg, (mavlink_appopmode_t *)&app_op_mode_t);
                break;
            case MAVLINK_MSG_ID_AppEncoderConfig:
                app_encoder_config_t.Load_encoder_resolution = get_app_Load_encoder_resolution();
                app_encoder_config_t.Motor_encoder_resolution = get_app_Motor_encoder_resolution();
                app_encoder_config_t.Motor_encoder_type = get_app_Motor_encoder_type();
                app_encoder_config_t.Load_encoder_type = get_app_Load_encoder_type();
                app_encoder_config_t.Motor_encoder_options = get_app_Motor_encoder_options();
                app_encoder_config_t.Load_pps_2_rpm = get_app_Load_pps_2_rpm();
                app_encoder_config_t.Load_rpm_2_pps = get_app_Load_rpm_2_pps();
                app_encoder_config_t.Motor_pps_2_rpm = get_app_Motor_pps_2_rpm();
                app_encoder_config_t.Motor_rpm_2_pps = get_app_Motor_rpm_2_pps();
                app_encoder_config_t.P_load_2_motor = get_app_P_load_2_motor();
                app_encoder_config_t.P_motor_2_load = get_app_P_motor_2_load();
                app_encoder_config_t.Load_control_resolution = get_app_Load_control_resolution();
                app_encoder_config_t.Motor_control_resolution = get_app_Motor_control_resolution();
                app_encoder_config_t.Load_encoder_options = get_app_Load_encoder_options();
                mavlink_msg_appencoderconfig_encode(sys_id, comp_id, &send_msg, (mavlink_appencoderconfig_t *)&app_encoder_config_t);
                break;
            case MAVLINK_MSG_ID_AppBaseConfig:
                app_base_config_t.Polarity = get_app_Polarity();
                app_base_config_t.Home_position_offset_value = get_app_Home_position_offset_value();
                app_base_config_t.Can_id = get_app_Can_id();
                app_base_config_t.Can_baudrate = get_app_Can_baudrate();
                app_base_config_t.Quick_stop_option_code = get_app_Quick_stop_option_code();
                app_base_config_t.Brake_engage_time = get_app_Brake_engage_time();
                app_base_config_t.Brake_release_time = get_app_Brake_release_time();
                app_base_config_t.Dynamic_brake_speed_threshold = get_app_Dynamic_brake_speed_threshold();
                app_base_config_t.Brake_release_hold_voltage = get_app_Brake_release_hold_voltage();
                app_base_config_t.Digital_io_outputs_phys = get_app_Digital_io_outputs_phys();
                app_base_config_t.Digital_io_outputs_mask = get_app_Digital_io_outputs_mask();
                app_base_config_t.Brake_control_mode = get_app_Brake_control_mode();
                app_base_config_t.Brake_rated_voltage = get_app_Brake_rated_voltage();
                app_base_config_t.Brake_release_action_voltage = get_app_Brake_release_action_voltage();
                app_base_config_t.Brake_release_pwm_freq = get_app_Brake_release_pwm_freq();
                app_base_config_t.Brake_engage_delay_time = get_app_Brake_engage_delay_time();
                app_base_config_t.Brake_release_delay_time = get_app_Brake_release_delay_time();
                mavlink_msg_appbaseconfig_encode(sys_id, comp_id, &send_msg, (mavlink_appbaseconfig_t *)&app_base_config_t);
                break;
            case MAVLINK_MSG_ID_AppMotionParam:
                app_motion_param_t.Target_position = get_app_Target_position();
                app_motion_param_t.Profile_velocity = get_app_Profile_velocity();
                app_motion_param_t.Profile_acceleration = get_app_Profile_acceleration();
                app_motion_param_t.Profile_deceleration = get_app_Profile_deceleration();
                app_motion_param_t.Quick_stop_deceleration = get_app_Quick_stop_deceleration();
                app_motion_param_t.Motion_profile_type = get_app_Motion_profile_type();
                app_motion_param_t.Home_offset = get_app_Home_offset();
                app_motion_param_t.Homing_method = get_app_Homing_method();
                app_motion_param_t.Target_velocity = get_app_Target_velocity();
                app_motion_param_t.Target_torque = get_app_Target_torque();
                app_motion_param_t.Torque_slope = get_app_Torque_slope();
                app_motion_param_t.Encoder_calibration_speed = get_app_Encoder_calibration_speed();
                app_motion_param_t.MIT_feedforward_torque = get_app_MIT_feedforward_torque();
                app_motion_param_t.MIT_target_position = get_app_MIT_target_position();
                app_motion_param_t.MIT_max_current = get_app_MIT_max_current();
                app_motion_param_t.MIT_target_velocity = get_app_MIT_target_velocity();
                app_motion_param_t.MIT_kp = get_app_MIT_kp();
                app_motion_param_t.MIT_kd = get_app_MIT_kd();
                app_motion_param_t.Interp_time_value = get_app_Interp_time_value();
                app_motion_param_t.Interp_time_index = get_app_Interp_time_index();
                app_motion_param_t.Homing_speed_search_for_switch = get_app_Homing_speed_search_for_switch();
                app_motion_param_t.Homing_speed_search_for_zero = get_app_Homing_speed_search_for_zero();
                app_motion_param_t.Homing_acceleration = get_app_Homing_acceleration();
                mavlink_msg_appmotionparam_encode(sys_id, comp_id, &send_msg, (mavlink_appmotionparam_t *)&app_motion_param_t);
                break;
            case MAVLINK_MSG_ID_AppRestrictParam:
                app_restrict_param_t.Position_range_limit_Minimal_position_limit = get_app_Position_range_limit_Minimal_position_limit();
                app_restrict_param_t.Position_range_limit_Maximal_position_limit = get_app_Position_range_limit_Maximal_position_limit();
                app_restrict_param_t.Software_position_limit_Minimal_position_limit = get_app_Software_position_limit_Minimal_position_limit();
                app_restrict_param_t.Software_position_limit_Maximal_position_limit = get_app_Software_position_limit_Maximal_position_limit();
                app_restrict_param_t.Max_profile_velocity = get_app_Max_profile_velocity();
                app_restrict_param_t.Max_motor_speed = get_app_Max_motor_speed();
                app_restrict_param_t.Max_acceleration = get_app_Max_acceleration();
                app_restrict_param_t.Max_deceleration = get_app_Max_deceleration();
                app_restrict_param_t.Max_current = get_app_Max_current();
                app_restrict_param_t.Position_limit_enable = get_app_Position_limit_enable();
                mavlink_msg_apprestrictparam_encode(sys_id, comp_id, &send_msg, (mavlink_apprestrictparam_t *)&app_restrict_param_t);
                break;
            case MAVLINK_MSG_ID_AppMotionInfo:
                app_motion_info_t.Position_demand_value = get_app_Position_demand_value();
                app_motion_info_t.Position_actual_value_inc = get_app_Position_actual_value_inc();
                app_motion_info_t.Position_actual_value = get_app_Position_actual_value();
                app_motion_info_t.Following_error_actual_value = get_app_Following_error_actual_value();
                app_motion_info_t.Velocity_demand_value = get_app_Velocity_demand_value();
                app_motion_info_t.Velocity_actual_value = get_app_Velocity_actual_value();
                app_motion_info_t.Torque_demand_value = get_app_Torque_demand_value();
                app_motion_info_t.Torque_actual_value = get_app_Torque_actual_value();
                app_motion_info_t.Current_actual_value = get_app_Current_actual_value();
                app_motion_info_t.D_current_actual_value = get_app_D_current_actual_value();
                app_motion_info_t.U_current_actual_value = get_app_U_current_actual_value();
                app_motion_info_t.V_current_actual_value = get_app_V_current_actual_value();
                app_motion_info_t.W_current_actual_value = get_app_W_current_actual_value();
                app_motion_info_t.Motor_position_demand_value = get_app_Motor_position_demand_value();
                app_motion_info_t.Motor_position_actual_value = get_app_Motor_position_actual_value();
                app_motion_info_t.Motor_following_error_actual_value = get_app_Motor_following_error_actual_value();
                app_motion_info_t.Motor_velocity_demand_value = get_app_Motor_velocity_demand_value();
                app_motion_info_t.Motor_velocity_actual_value = get_app_Motor_velocity_actual_value();
                app_motion_info_t.U_adc_mid_val = get_app_U_adc_mid_val();
                app_motion_info_t.V_adc_mid_val = get_app_V_adc_mid_val();
                app_motion_info_t.W_adc_mid_val = get_app_W_adc_mid_val();
                app_motion_info_t.Current_loop_time = get_app_Current_loop_time();
                app_motion_info_t.Position_loop_time = get_app_Position_loop_time();
                app_motion_info_t.Current_loop_cycle = get_app_Current_loop_cycle();
                app_motion_info_t.Position_loop_cycle = get_app_Position_loop_cycle();
                app_motion_info_t.Interp_period = get_app_Interp_period();
                app_motion_info_t.Emergency_brake_requested = get_app_Emergency_brake_requested();
                app_motion_info_t.Target_update_state = get_app_Target_update_state();
                app_motion_info_t.Homing_step = get_app_Homing_step();
                app_motion_info_t.Encoder_zero_crossing_state = get_app_Encoder_zero_crossing_state();
                app_motion_info_t.Homing_state = get_app_Homing_state();
                mavlink_msg_appmotioninfo_encode(sys_id, comp_id, &send_msg, (mavlink_appmotioninfo_t *)&app_motion_info_t);
                break;
            case MAVLINK_MSG_ID_AppWindowParam:
                app_window_param_t.Following_error_window = get_app_Following_error_window();
                app_window_param_t.Following_error_time_out = get_app_Following_error_time_out();
                app_window_param_t.Position_window = get_app_Position_window();
                app_window_param_t.Position_window_time = get_app_Position_window_time();
                app_window_param_t.Velocity_window = get_app_Velocity_window();
                app_window_param_t.Velocity_window_time = get_app_Velocity_window_time();
                app_window_param_t.Velocity_threshold = get_app_Velocity_threshold();
                app_window_param_t.Velocity_threshold_time = get_app_Velocity_threshold_time();
                mavlink_msg_appwindowparam_encode(sys_id, comp_id, &send_msg, (mavlink_appwindowparam_t *)&app_window_param_t);
                break;
            case MAVLINK_MSG_ID_AppMotorConfig:
                app_motor_config_t.Motor_rated_current = get_app_Motor_rated_current();
                app_motor_config_t.Motor_rated_torque = get_app_Motor_rated_torque();
                app_motor_config_t.Motor_peak_current = get_app_Motor_peak_current();
                app_motor_config_t.Motor_pole_pairs = get_app_Motor_pole_pairs();
                app_motor_config_t.Motor_maximum_speed = get_app_Motor_maximum_speed();
                app_motor_config_t.Resistance = get_app_Resistance();
                app_motor_config_t.Inductance = get_app_Inductance();
                app_motor_config_t.Reduction_ratio_num = get_app_Reduction_ratio_num();
                app_motor_config_t.Reduction_ratio_den = get_app_Reduction_ratio_den();
                app_motor_config_t.Torque_constant = get_app_Torque_constant();
                app_motor_config_t.Reduction_ratio = get_app_Reduction_ratio();
                app_motor_config_t.Reduction_ratio_inv = get_app_Reduction_ratio_inv();
                app_motor_config_t.Motor_rotor_inertia = get_app_Motor_rotor_inertia();
                mavlink_msg_appmotorconfig_encode(sys_id, comp_id, &send_msg, (mavlink_appmotorconfig_t *)&app_motor_config_t);
                break;
            case MAVLINK_MSG_ID_AppProtectConfig:
                app_protect_config_t.Bus_under_voltage_threshold = get_app_Bus_under_voltage_threshold();
                app_protect_config_t.Bus_over_voltage_threshold = get_app_Bus_over_voltage_threshold();
                app_protect_config_t.Drive_overload_current_duration = get_app_Drive_overload_current_duration();
                app_protect_config_t.Drive_peak_current_duration = get_app_Drive_peak_current_duration();
                app_protect_config_t.Drive_temperature_threshold_time = get_app_Drive_temperature_threshold_time();
                app_protect_config_t.Drive_low_temperature_fault_threshold = get_app_Drive_low_temperature_fault_threshold();
                app_protect_config_t.Drive_high_temperature_fault_threshold = get_app_Drive_high_temperature_fault_threshold();
                app_protect_config_t.Overspeed_threshold = get_app_Overspeed_threshold();
                app_protect_config_t.Drive_overcurrent_threshold = get_app_Drive_overcurrent_threshold();
                app_protect_config_t.Protection_enable = get_app_Protection_enable();
                app_protect_config_t.Motor_low_temperature_fault_threshold = get_app_Motor_low_temperature_fault_threshold();
                app_protect_config_t.Motor_high_temperature_fault_threshold = get_app_Motor_high_temperature_fault_threshold();
                app_protect_config_t.Can_timeout = get_app_Can_timeout();
                app_protect_config_t.Motor_low_temperature_warning_threshold = get_app_Motor_low_temperature_warning_threshold();
                app_protect_config_t.Motor_high_temperature_warning_threshold = get_app_Motor_high_temperature_warning_threshold();
                app_protect_config_t.Mcu_temperature_threshold_time = get_app_Mcu_temperature_threshold_time();
                app_protect_config_t.Mcu_low_temperature_fault_threshold = get_app_Mcu_low_temperature_fault_threshold();
                app_protect_config_t.Mcu_high_temperature_fault_threshold = get_app_Mcu_high_temperature_fault_threshold();
                app_protect_config_t.Mcu_low_temperature_warning_threshold = get_app_Mcu_low_temperature_warning_threshold();
                app_protect_config_t.Mcu_high_temperature_warning_threshold = get_app_Mcu_high_temperature_warning_threshold();
                app_protect_config_t.Drive_low_temperature_warning_threshold = get_app_Drive_low_temperature_warning_threshold();
                app_protect_config_t.Drive_high_temperature_warning_threshold = get_app_Drive_high_temperature_warning_threshold();
                mavlink_msg_appprotectconfig_encode(sys_id, comp_id, &send_msg, (mavlink_appprotectconfig_t *)&app_protect_config_t);
                break;
            case MAVLINK_MSG_ID_MitCtlInput:
                mit_ctl_input_t.tq_set_NM = axis->mit_ctl_input.tq_set_NM;
                mit_ctl_input_t.pos_tar_p = axis->mit_ctl_input.pos_tar_p;
                mit_ctl_input_t.pos_now_p = axis->mit_ctl_input.pos_now_p;
                mit_ctl_input_t.iq_max_A = axis->mit_ctl_input.iq_max_A;
                mit_ctl_input_t.speed_tar_p_s = axis->mit_ctl_input.speed_tar_p_s;
                mit_ctl_input_t.speed_now_rad_s = axis->mit_ctl_input.speed_now_rad_s;
                mavlink_msg_mitctlinput_encode(sys_id, comp_id, &send_msg, (mavlink_mitctlinput_t *)&mit_ctl_input_t);
                break;
            case MAVLINK_MSG_ID_MitCtlConfig:
                mit_ctl_config_t.kp_pos_NM_rad = axis->mit_ctl_config.kp_pos_NM_rad;
                mit_ctl_config_t.kd_spd_NM_rad_s = axis->mit_ctl_config.kd_spd_NM_rad_s;
                mit_ctl_config_t.enc_line_inv_p_n = axis->mit_ctl_config.enc_line_inv_p_n;
                mit_ctl_config_t.kt_NM_A = axis->mit_ctl_config.kt_NM_A;
                mavlink_msg_mitctlconfig_encode(sys_id, comp_id, &send_msg, (mavlink_mitctlconfig_t *)&mit_ctl_config_t);
                break;
            case MAVLINK_MSG_ID_MitCtlOutput:
                mit_ctl_output_t.iq_tar_A = axis->mit_ctl_output.iq_tar_A;
                mavlink_msg_mitctloutput_encode(sys_id, comp_id, &send_msg, (mavlink_mitctloutput_t *)&mit_ctl_output_t);
                break;
            case MAVLINK_MSG_ID_AppPermissionConfig:
                app_permission_config_t.Comm_control_authority = get_app_Comm_control_authority();
                app_permission_config_t.Internal_control_authority = get_app_Internal_control_authority();
                mavlink_msg_apppermissionconfig_encode(sys_id, comp_id, &send_msg, (mavlink_apppermissionconfig_t *)&app_permission_config_t);
                break;
            case MAVLINK_MSG_ID_SystemCmd:
                system_cmd_t.Sys_cmd = get_app_Sys_cmd();
                mavlink_msg_systemcmd_encode(sys_id, comp_id, &send_msg, (mavlink_systemcmd_t *)&system_cmd_t);
                break;
            case MAVLINK_MSG_ID_LoadPosSensorInput:
                load_pos_sensor_input_t.enc_counts_now_p = axis->load_pos_sensor_input.enc_counts_now_p;
                mavlink_msg_loadpossensorinput_encode(sys_id, comp_id, &send_msg, (mavlink_loadpossensorinput_t *)&load_pos_sensor_input_t);
                break;
            case MAVLINK_MSG_ID_LoadPosSensorConfig:
                load_pos_sensor_config_t.enc_line_p_n = axis->load_pos_sensor_config.enc_line_p_n;
                load_pos_sensor_config_t.init_pos_p = axis->load_pos_sensor_config.init_pos_p;
                load_pos_sensor_config_t.dir = axis->load_pos_sensor_config.dir;
                mavlink_msg_loadpossensorconfig_encode(sys_id, comp_id, &send_msg, (mavlink_loadpossensorconfig_t *)&load_pos_sensor_config_t);
                break;
            case MAVLINK_MSG_ID_LoadPosSensorOutput:
                load_pos_sensor_output_t.enc_sum_p = axis->load_pos_sensor_output.enc_sum_p;
                mavlink_msg_loadpossensoroutput_encode(sys_id, comp_id, &send_msg, (mavlink_loadpossensoroutput_t *)&load_pos_sensor_output_t);
                break;
            case MAVLINK_MSG_ID_SystemStatus:
                system_status_t.Storage_status = get_app_Storage_status();
                system_status_t.Storage_cmd = get_app_Storage_cmd();
                mavlink_msg_systemstatus_encode(sys_id, comp_id, &send_msg, (mavlink_systemstatus_t *)&system_status_t);
                break;
            case MAVLINK_MSG_ID_EncoderCalibrationCmd:
                encoder_calibration_cmd_t.Calibration_cmd = get_app_Calibration_cmd();
                encoder_calibration_cmd_t.Calibration_time = get_app_Calibration_time();
                mavlink_msg_encodercalibrationcmd_encode(sys_id, comp_id, &send_msg, (mavlink_encodercalibrationcmd_t *)&encoder_calibration_cmd_t);
                break;
            case MAVLINK_MSG_ID_EncoderCalibrationStatus:
                encoder_calibration_status_t.Calibration_status = get_app_Calibration_status();
                mavlink_msg_encodercalibrationstatus_encode(sys_id, comp_id, &send_msg, (mavlink_encodercalibrationstatus_t *)&encoder_calibration_status_t);
                break;
            case MAVLINK_MSG_ID_CustomInfo:
                custom_info_t.User_module_code = get_app_User_module_code();
                mavlink_msg_custominfo_encode(sys_id, comp_id, &send_msg, (mavlink_custominfo_t *)&custom_info_t);
                break;
            case MAVLINK_MSG_ID_HeartBit:
                heart_bit_t.Sys_init_flag = get_app_Sys_init_flag();
                mavlink_msg_heartbit_encode(sys_id, comp_id, &send_msg, (mavlink_heartbit_t *)&heart_bit_t);
                break;
            case MAVLINK_MSG_ID_HistoricalInfo:
                memcpy(&historical_info_t.Error_records_list, get_app_Error_records_list_addr(), sizeof(historical_info_t.Error_records_list));
                mavlink_msg_historicalinfo_encode(sys_id, comp_id, &send_msg, (mavlink_historicalinfo_t *)&historical_info_t);
                break;
            case MAVLINK_MSG_ID_SimPlantInput:
                memcpy(&sim_plant_input_t.uabc_tar_V, axis->sim_plant_input.uabc_tar_V, sizeof(sim_plant_input_t.uabc_tar_V));
                sim_plant_input_t.tl_Nm = axis->sim_plant_input.tl_Nm;
                mavlink_msg_simplantinput_encode(sys_id, comp_id, &send_msg, (mavlink_simplantinput_t *)&sim_plant_input_t);
                break;
            case MAVLINK_MSG_ID_SimPlantOutput:
                memcpy(&sim_plant_output_t.iabc_now_A, axis->sim_plant_output.iabc_now_A, sizeof(sim_plant_output_t.iabc_now_A));
                sim_plant_output_t.enc_counts_P = axis->sim_plant_output.enc_counts_P;
                sim_plant_output_t.hall_state = axis->sim_plant_output.hall_state;
                sim_plant_output_t.dc_bus_V = axis->sim_plant_output.dc_bus_V;
                mavlink_msg_simplantoutput_encode(sys_id, comp_id, &send_msg, (mavlink_simplantoutput_t *)&sim_plant_output_t);
                break;
            case MAVLINK_MSG_ID_SimPlantConfig:
                sim_plant_config_t.b = axis->sim_plant_config.b;
                sim_plant_config_t.fc = axis->sim_plant_config.fc;
                sim_plant_config_t.flux = axis->sim_plant_config.flux;
                sim_plant_config_t.kt = axis->sim_plant_config.kt;
                sim_plant_config_t.j = axis->sim_plant_config.j;
                sim_plant_config_t.ld = axis->sim_plant_config.ld;
                sim_plant_config_t.lq = axis->sim_plant_config.lq;
                sim_plant_config_t.peak_current_A = axis->sim_plant_config.peak_current_A;
                sim_plant_config_t.pn = axis->sim_plant_config.pn;
                sim_plant_config_t.r = axis->sim_plant_config.r;
                sim_plant_config_t.rated_current_A = axis->sim_plant_config.rated_current_A;
                sim_plant_config_t.speed_max_rpm = axis->sim_plant_config.speed_max_rpm;
                sim_plant_config_t.dt_s = axis->sim_plant_config.dt_s;
                sim_plant_config_t.enc_line_p_n = axis->sim_plant_config.enc_line_p_n;
                sim_plant_config_t.j_inv = axis->sim_plant_config.j_inv;
                sim_plant_config_t.ld_inv = axis->sim_plant_config.ld_inv;
                sim_plant_config_t.lq_inv = axis->sim_plant_config.lq_inv;
                sim_plant_config_t.enc_line_init_pos_P = axis->sim_plant_config.enc_line_init_pos_P;
                sim_plant_config_t.enc_noise = axis->sim_plant_config.enc_noise;
                mavlink_msg_simplantconfig_encode(sys_id, comp_id, &send_msg, (mavlink_simplantconfig_t *)&sim_plant_config_t);
                break;
            case MAVLINK_MSG_ID_AppDebugParam:
                memcpy(&app_debug_param_t.Debug_float, get_app_Debug_float_addr(), sizeof(app_debug_param_t.Debug_float));
                memcpy(&app_debug_param_t.Debug_uint32, get_app_Debug_uint32_addr(), sizeof(app_debug_param_t.Debug_uint32));
                memcpy(&app_debug_param_t.Debug_int32, get_app_Debug_int32_addr(), sizeof(app_debug_param_t.Debug_int32));
                mavlink_msg_appdebugparam_encode(sys_id, comp_id, &send_msg, (mavlink_appdebugparam_t *)&app_debug_param_t);
                break;
            case MAVLINK_MSG_ID_AppMavlinkConfig:
                app_mavlink_config_t.Sys_id = get_app_Sys_id();
                app_mavlink_config_t.Comp_id = get_app_Comp_id();
                mavlink_msg_appmavlinkconfig_encode(sys_id, comp_id, &send_msg, (mavlink_appmavlinkconfig_t *)&app_mavlink_config_t);
                break;
            case MAVLINK_MSG_ID_AppFileTransferConfig:
                app_file_transfer_config_t.File_type = get_app_File_type();
                app_file_transfer_config_t.File_size = get_app_File_size();
                app_file_transfer_config_t.File_direction = get_app_File_direction();
                app_file_transfer_config_t.File_index_complete = get_app_File_index_complete();
                app_file_transfer_config_t.File_status = get_app_File_status();
                mavlink_msg_appfiletransferconfig_encode(sys_id, comp_id, &send_msg, (mavlink_appfiletransferconfig_t *)&app_file_transfer_config_t);
                break;
            case MAVLINK_MSG_ID_AppFwUpgradeParam:
                app_fw_upgrade_param_t.Fw_mode = get_app_Fw_mode();
                app_fw_upgrade_param_t.Fw_app_index = get_app_Fw_app_index();
                app_fw_upgrade_param_t.Fw_flash_size = get_app_Fw_flash_size();
                app_fw_upgrade_param_t.Fw_operating_steps = get_app_Fw_operating_steps();
                mavlink_msg_appfwupgradeparam_encode(sys_id, comp_id, &send_msg, (mavlink_appfwupgradeparam_t *)&app_fw_upgrade_param_t);
                break;
//DATABASE_CODE_STOP_2
            default:
                break;
        }
    }
    else{
        switch (msg.msgid){
            case MAVLINK_MSG_ID_ScopeConfig:
                mavlink_msg_scopeconfig_decode(&msg, &scope_config);
                mavlink_scope_config_callback(&scope_config, &kScopeObject, SCOPE_WRITE);
                mavlink_msg_scopeconfig_encode(sys_id, comp_id, &send_msg, &scope_config);
                break;
            case MAVLINK_MSG_ID_ScopeControl:
                mavlink_msg_scopecontrol_decode(&msg, &scope_control);
                mavlink_scope_control_callback(&scope_control, &kScopeObject, SCOPE_WRITE);
                mavlink_msg_scopecontrol_encode(sys_id, comp_id, &send_msg, &scope_control);
                break;
            case MAVLINK_MSG_ID_WaveformMap:
                mavlink_msg_waveformmap_decode(&msg, &waveform_map);
                set_waveform_map(waveform_map.waveform_map_info);
                mavlink_msg_waveformmap_encode(sys_id, comp_id, &send_msg, &waveform_map);
                break;
            case MAVLINK_MSG_ID_SystemConfig:
                mavlink_msg_systemconfig_decode(&msg, &system_config_t);
                kSystemConfig.param_save = system_config_t.param_save;
                kSystemConfig.system_reset = system_config_t.system_reset;
                kSystemConfig.current_loop_freq = system_config_t.current_loop_freq;
                kSystemConfig.position_loop_freq = system_config_t.position_loop_freq;
                mavlink_msg_systemconfig_encode(sys_id, comp_id, &send_msg, &system_config_t);
                break;
            case MAVLINK_MSG_ID_TableConfig:
                mavlink_msg_tableconfig_decode(&msg, (mavlink_tableconfig_t *)&table_config_t);
                mavlink_msg_tableconfig_encode(sys_id, comp_id, &send_msg, (mavlink_tableconfig_t *)&table_config_t);
                break;
            case MAVLINK_MSG_ID_TableData:
                mavlink_msg_tabledata_decode(&msg, (mavlink_tabledata_t *)&table_data_t);
                memcpy(axis_dw->tq_fc_id_InstanceData.rtdw.com_table + table_config_t.table_index_offset * 20, table_data_t.table_data, sizeof(table_data_t.table_data));
                mavlink_msg_tableconfig_encode(sys_id, comp_id, &send_msg, (mavlink_tableconfig_t *)&table_config_t);
                break;
            case MAVLINK_MSG_ID_AppFileTransferStream:

                mavlink_msg_appfiletransferstream_decode(&msg, (mavlink_appfiletransferstream_t *)&appfile_transfer_stream_t);

                FwUpgradeOverMavlinkCallback(appfile_transfer_stream_t.Index, appfile_transfer_stream_t.Length, (uint8_t *)appfile_transfer_stream_t.File_buffer);

                app_file_transfer_config_t.File_type = get_app_File_type();
                app_file_transfer_config_t.File_size = get_app_File_size();
                app_file_transfer_config_t.File_direction = get_app_File_direction();
                app_file_transfer_config_t.File_index_complete = get_app_File_index_complete();
                app_file_transfer_config_t.File_status = get_app_File_status();
                mavlink_msg_appfiletransferconfig_encode(sys_id, comp_id, &send_msg, (mavlink_appfiletransferconfig_t *)&app_file_transfer_config_t);
                break;
//DATABASE_CODE_START_3
            case MAVLINK_MSG_ID_PmsmConfig:
                mavlink_msg_pmsmconfig_decode(&msg, (mavlink_pmsmconfig_t *)&pmsm_config_t);
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->pmsm_config.b = pmsm_config_t.b;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->pmsm_config.fc = pmsm_config_t.fc;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->pmsm_config.flux = pmsm_config_t.flux;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->pmsm_config.j = pmsm_config_t.j;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->pmsm_config.ld = pmsm_config_t.ld;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->pmsm_config.lq = pmsm_config_t.lq;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->pmsm_config.peak_current = pmsm_config_t.peak_current;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->pmsm_config.pn = pmsm_config_t.pn;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->pmsm_config.r = pmsm_config_t.r;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->pmsm_config.rated_current = pmsm_config_t.rated_current;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->pmsm_config.speed_max_rpm = pmsm_config_t.speed_max_rpm;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->pmsm_config.tp_s = pmsm_config_t.tp_s;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->pmsm_config.tc_s = pmsm_config_t.tc_s;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->pmsm_config.enc_line_p_n = pmsm_config_t.enc_line_p_n;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->pmsm_config.kt = pmsm_config_t.kt;}
                mavlink_msg_pmsmconfig_encode(sys_id, comp_id, &send_msg, (mavlink_pmsmconfig_t *)&pmsm_config_t);
                break;
            case MAVLINK_MSG_ID_ElecIdSinInput:
                mavlink_msg_elecidsininput_decode(&msg, (mavlink_elecidsininput_t *)&elec_id_sin_input_t);
                mavlink_msg_elecidsininput_encode(sys_id, comp_id, &send_msg, (mavlink_elecidsininput_t *)&elec_id_sin_input_t);
                break;
            case MAVLINK_MSG_ID_ElecIdSinOutput:
                mavlink_msg_elecidsinoutput_decode(&msg, (mavlink_elecidsinoutput_t *)&elec_id_sin_output_t);
                mavlink_msg_elecidsinoutput_encode(sys_id, comp_id, &send_msg, (mavlink_elecidsinoutput_t *)&elec_id_sin_output_t);
                break;
            case MAVLINK_MSG_ID_ElecIdSinConfig:
                mavlink_msg_elecidsinconfig_decode(&msg, (mavlink_elecidsinconfig_t *)&elec_id_sin_config_t);
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->elec_id_sin_config.dt_s = elec_id_sin_config_t.dt_s;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->elec_id_sin_config.end_fs_Hz = elec_id_sin_config_t.end_fs_Hz;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->elec_id_sin_config.i_max_A = elec_id_sin_config_t.i_max_A;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->elec_id_sin_config.init_fs_Hz = elec_id_sin_config_t.init_fs_Hz;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->elec_id_sin_config.target_time_s = elec_id_sin_config_t.target_time_s;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->elec_id_sin_config.u_max_V = elec_id_sin_config_t.u_max_V;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->elec_id_sin_config.wait_time_s = elec_id_sin_config_t.wait_time_s;}
                mavlink_msg_elecidsinconfig_encode(sys_id, comp_id, &send_msg, (mavlink_elecidsinconfig_t *)&elec_id_sin_config_t);
                break;
            case MAVLINK_MSG_ID_MecIdOutput:
                mavlink_msg_mecidoutput_decode(&msg, (mavlink_mecidoutput_t *)&mec_id_output_t);
                mavlink_msg_mecidoutput_encode(sys_id, comp_id, &send_msg, (mavlink_mecidoutput_t *)&mec_id_output_t);
                break;
            case MAVLINK_MSG_ID_MecIdConfig:
                mavlink_msg_mecidconfig_decode(&msg, (mavlink_mecidconfig_t *)&mec_id_config_t);
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->mec_id_config.dt_s = mec_id_config_t.dt_s;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->mec_id_config.end_fs_Hz = mec_id_config_t.end_fs_Hz;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->mec_id_config.start_fs_Hz = mec_id_config_t.start_fs_Hz;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->mec_id_config.target_time_s = mec_id_config_t.target_time_s;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->mec_id_config.i_max_A = mec_id_config_t.i_max_A;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->mec_id_config.search_speed_max_rad_s = mec_id_config_t.search_speed_max_rad_s;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->mec_id_config.wait_time_s = mec_id_config_t.wait_time_s;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->mec_id_config.signal_type = mec_id_config_t.signal_type;}
                mavlink_msg_mecidconfig_encode(sys_id, comp_id, &send_msg, (mavlink_mecidconfig_t *)&mec_id_config_t);
                break;
            case MAVLINK_MSG_ID_NotchFilterInput:
                mavlink_msg_notchfilterinput_decode(&msg, (mavlink_notchfilterinput_t *)&notch_filter_input_t);
                mavlink_msg_notchfilterinput_encode(sys_id, comp_id, &send_msg, (mavlink_notchfilterinput_t *)&notch_filter_input_t);
                break;
            case MAVLINK_MSG_ID_NotchFilterInternal:
                mavlink_msg_notchfilterinternal_decode(&msg, (mavlink_notchfilterinternal_t *)&notch_filter_internal_t);
                mavlink_msg_notchfilterinternal_encode(sys_id, comp_id, &send_msg, (mavlink_notchfilterinternal_t *)&notch_filter_internal_t);
                break;
            case MAVLINK_MSG_ID_NotchFilterOutput:
                mavlink_msg_notchfilteroutput_decode(&msg, (mavlink_notchfilteroutput_t *)&notch_filter_output_t);
                mavlink_msg_notchfilteroutput_encode(sys_id, comp_id, &send_msg, (mavlink_notchfilteroutput_t *)&notch_filter_output_t);
                break;
            case MAVLINK_MSG_ID_MecIdInput:
                mavlink_msg_mecidinput_decode(&msg, (mavlink_mecidinput_t *)&mec_id_input_t);
                mavlink_msg_mecidinput_encode(sys_id, comp_id, &send_msg, (mavlink_mecidinput_t *)&mec_id_input_t);
                break;
            case MAVLINK_MSG_ID_InputShapingInput:
                mavlink_msg_inputshapinginput_decode(&msg, (mavlink_inputshapinginput_t *)&input_shaping_input_t);
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->input_shaping_input.pos_cmd_p = input_shaping_input_t.pos_cmd_p;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->input_shaping_input.pos_cmd_p_init = input_shaping_input_t.pos_cmd_p_init;}
                mavlink_msg_inputshapinginput_encode(sys_id, comp_id, &send_msg, (mavlink_inputshapinginput_t *)&input_shaping_input_t);
                break;
            case MAVLINK_MSG_ID_InputShapingConfig:
                mavlink_msg_inputshapingconfig_decode(&msg, (mavlink_inputshapingconfig_t *)&input_shaping_config_t);
                axis->input_shaping_config.wn_Hz = input_shaping_config_t.wn_Hz;
                axis->input_shaping_config.run_frq_Hz = input_shaping_config_t.run_frq_Hz;
                axis->input_shaping_config.enable = input_shaping_config_t.enable;
                mavlink_msg_inputshapingconfig_encode(sys_id, comp_id, &send_msg, (mavlink_inputshapingconfig_t *)&input_shaping_config_t);
                break;
            case MAVLINK_MSG_ID_InputShapingOutput:
                mavlink_msg_inputshapingoutput_decode(&msg, (mavlink_inputshapingoutput_t *)&input_shaping_output_t);
                mavlink_msg_inputshapingoutput_encode(sys_id, comp_id, &send_msg, (mavlink_inputshapingoutput_t *)&input_shaping_output_t);
                break;
            case MAVLINK_MSG_ID_PosSpeedCtlInput:
                mavlink_msg_posspeedctlinput_decode(&msg, (mavlink_posspeedctlinput_t *)&pos_speed_ctl_input_t);
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->pos_speed_ctl_input.pos_tar_p = pos_speed_ctl_input_t.pos_tar_p;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->pos_speed_ctl_input.iq_max_A = pos_speed_ctl_input_t.iq_max_A;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->pos_speed_ctl_input.speed_tar_p_s = pos_speed_ctl_input_t.speed_tar_p_s;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->pos_speed_ctl_input.acc_tar_p_ss = pos_speed_ctl_input_t.acc_tar_p_ss;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->pos_speed_ctl_input.position_offset_p = pos_speed_ctl_input_t.position_offset_p;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->pos_speed_ctl_input.speed_offset_p_s = pos_speed_ctl_input_t.speed_offset_p_s;}
                mavlink_msg_posspeedctlinput_encode(sys_id, comp_id, &send_msg, (mavlink_posspeedctlinput_t *)&pos_speed_ctl_input_t);
                break;
            case MAVLINK_MSG_ID_PosSpeedCtlOutput:
                mavlink_msg_posspeedctloutput_decode(&msg, (mavlink_posspeedctloutput_t *)&pos_speed_ctl_output_t);
                mavlink_msg_posspeedctloutput_encode(sys_id, comp_id, &send_msg, (mavlink_posspeedctloutput_t *)&pos_speed_ctl_output_t);
                break;
            case MAVLINK_MSG_ID_PosSpeedCtlConfig:
                mavlink_msg_posspeedctlconfig_decode(&msg, (mavlink_posspeedctlconfig_t *)&pos_speed_ctl_config_t);
                axis->pos_speed_ctl_config.aff = pos_speed_ctl_config_t.aff;
                axis->pos_speed_ctl_config.vff = pos_speed_ctl_config_t.vff;
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->pos_speed_ctl_config.enc_line_inv_p_n = pos_speed_ctl_config_t.enc_line_inv_p_n;}
                axis->pos_speed_ctl_config.j_kt = pos_speed_ctl_config_t.j_kt;
                axis->pos_speed_ctl_config.ki_s = pos_speed_ctl_config_t.ki_s;
                axis->pos_speed_ctl_config.kp_p = pos_speed_ctl_config_t.kp_p;
                axis->pos_speed_ctl_config.kp_s = pos_speed_ctl_config_t.kp_s;
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->pos_speed_ctl_config.speed_max_rad_s = pos_speed_ctl_config_t.speed_max_rad_s;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->pos_speed_ctl_config.tp_s = pos_speed_ctl_config_t.tp_s;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->pos_speed_ctl_config.mode = pos_speed_ctl_config_t.mode;}
                axis->pos_speed_ctl_config.dob_wn_Hz = pos_speed_ctl_config_t.dob_wn_Hz;
                axis->pos_speed_ctl_config.dob_enable = pos_speed_ctl_config_t.dob_enable;
                axis->pos_speed_ctl_config.dynamic_integration_enable = pos_speed_ctl_config_t.dynamic_integration_enable;
                mavlink_msg_posspeedctlconfig_encode(sys_id, comp_id, &send_msg, (mavlink_posspeedctlconfig_t *)&pos_speed_ctl_config_t);
                break;
            case MAVLINK_MSG_ID_MotorCtlSmConfig:
                mavlink_msg_motorctlsmconfig_decode(&msg, (mavlink_motorctlsmconfig_t *)&motor_ctl_sm_config_t);
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->motor_ctl_sm_config.mode = motor_ctl_sm_config_t.mode;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->motor_ctl_sm_config.under_voltage_protection_V = motor_ctl_sm_config_t.under_voltage_protection_V;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->motor_ctl_sm_config.over_voltage_protection_V = motor_ctl_sm_config_t.over_voltage_protection_V;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->motor_ctl_sm_config.over_speed_protection_rad_s = motor_ctl_sm_config_t.over_speed_protection_rad_s;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->motor_ctl_sm_config.under_temperature_protection_d = motor_ctl_sm_config_t.under_temperature_protection_d;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->motor_ctl_sm_config.over_temperature_protection_d = motor_ctl_sm_config_t.over_temperature_protection_d;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->motor_ctl_sm_config.position_following_error_protection = motor_ctl_sm_config_t.position_following_error_protection;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->motor_ctl_sm_config.error_enable = motor_ctl_sm_config_t.error_enable;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->motor_ctl_sm_config.over_current_protection_A = motor_ctl_sm_config_t.over_current_protection_A;}
                mavlink_msg_motorctlsmconfig_encode(sys_id, comp_id, &send_msg, (mavlink_motorctlsmconfig_t *)&motor_ctl_sm_config_t);
                break;
            case MAVLINK_MSG_ID_MotorCtlSmInput:
                mavlink_msg_motorctlsminput_decode(&msg, (mavlink_motorctlsminput_t *)&motor_ctl_sm_input_t);
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->motor_ctl_sm_input.motor_enable = motor_ctl_sm_input_t.motor_enable;}
                mavlink_msg_motorctlsminput_encode(sys_id, comp_id, &send_msg, (mavlink_motorctlsminput_t *)&motor_ctl_sm_input_t);
                break;
            case MAVLINK_MSG_ID_MotorCtlSmOutput:
                mavlink_msg_motorctlsmoutput_decode(&msg, (mavlink_motorctlsmoutput_t *)&motor_ctl_sm_output_t);
                mavlink_msg_motorctlsmoutput_encode(sys_id, comp_id, &send_msg, (mavlink_motorctlsmoutput_t *)&motor_ctl_sm_output_t);
                break;
            case MAVLINK_MSG_ID_CurrentCtlInput:
                mavlink_msg_currentctlinput_decode(&msg, (mavlink_currentctlinput_t *)&current_ctl_input_t);
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){memcpy(axis->current_ctl_input.idq_tar_A, current_ctl_input_t.idq_tar_A, sizeof(current_ctl_input_t.idq_tar_A));}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){memcpy(axis->current_ctl_input.uabc_tar_V, current_ctl_input_t.uabc_tar_V, sizeof(current_ctl_input_t.uabc_tar_V));}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->current_ctl_input.iq_offset_A = current_ctl_input_t.iq_offset_A;}
                mavlink_msg_currentctlinput_encode(sys_id, comp_id, &send_msg, (mavlink_currentctlinput_t *)&current_ctl_input_t);
                break;
            case MAVLINK_MSG_ID_CurrentCtlConfig:
                mavlink_msg_currentctlconfig_decode(&msg, (mavlink_currentctlconfig_t *)&current_ctl_config_t);
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->current_ctl_config.i_noise_A = current_ctl_config_t.i_noise_A;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->current_ctl_config.comp_du_V = current_ctl_config_t.comp_du_V;}
                axis->current_ctl_config.bandwidth_percentage = current_ctl_config_t.bandwidth_percentage;
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->current_ctl_config.dt_s = current_ctl_config_t.dt_s;}
                axis->current_ctl_config.flux_wb = current_ctl_config_t.flux_wb;
                axis->current_ctl_config.kp_ld = current_ctl_config_t.kp_ld;
                axis->current_ctl_config.ki_ld = current_ctl_config_t.ki_ld;
                axis->current_ctl_config.kp_lq = current_ctl_config_t.kp_lq;
                axis->current_ctl_config.ki_lq = current_ctl_config_t.ki_lq;
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->current_ctl_config.pwm_duty_cycle_max = current_ctl_config_t.pwm_duty_cycle_max;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->current_ctl_config.elec_angle_compensation = current_ctl_config_t.elec_angle_compensation;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->current_ctl_config.phase_dir = current_ctl_config_t.phase_dir;}
                mavlink_msg_currentctlconfig_encode(sys_id, comp_id, &send_msg, (mavlink_currentctlconfig_t *)&current_ctl_config_t);
                break;
            case MAVLINK_MSG_ID_CurrentCtlOutput:
                mavlink_msg_currentctloutput_decode(&msg, (mavlink_currentctloutput_t *)&current_ctl_output_t);
                mavlink_msg_currentctloutput_encode(sys_id, comp_id, &send_msg, (mavlink_currentctloutput_t *)&current_ctl_output_t);
                break;
            case MAVLINK_MSG_ID_NotchFilterConfig:
                mavlink_msg_notchfilterconfig_decode(&msg, (mavlink_notchfilterconfig_t *)&notch_filter_config_t);
                memcpy(axis->notch_filter_config.frq, notch_filter_config_t.frq, sizeof(notch_filter_config_t.frq));
                memcpy(axis->notch_filter_config.width, notch_filter_config_t.width, sizeof(notch_filter_config_t.width));
                memcpy(axis->notch_filter_config.depth, notch_filter_config_t.depth, sizeof(notch_filter_config_t.depth));
                mavlink_msg_notchfilterconfig_encode(sys_id, comp_id, &send_msg, (mavlink_notchfilterconfig_t *)&notch_filter_config_t);
                break;
            case MAVLINK_MSG_ID_SpeedObsPllInput:
                mavlink_msg_speedobspllinput_decode(&msg, (mavlink_speedobspllinput_t *)&speed_obs_pll_input_t);
                mavlink_msg_speedobspllinput_encode(sys_id, comp_id, &send_msg, (mavlink_speedobspllinput_t *)&speed_obs_pll_input_t);
                break;
            case MAVLINK_MSG_ID_SpeedObsPllConfig:
                mavlink_msg_speedobspllconfig_decode(&msg, (mavlink_speedobspllconfig_t *)&speed_obs_pll_config_t);
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->speed_obs_pll_config.tp_s = speed_obs_pll_config_t.tp_s;}
                axis->speed_obs_pll_config.wn_Hz = speed_obs_pll_config_t.wn_Hz;
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->speed_obs_pll_config.enc_line_inv_p_n = speed_obs_pll_config_t.enc_line_inv_p_n;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->speed_obs_pll_config.speed_obs_max_rad_s = speed_obs_pll_config_t.speed_obs_max_rad_s;}
                mavlink_msg_speedobspllconfig_encode(sys_id, comp_id, &send_msg, (mavlink_speedobspllconfig_t *)&speed_obs_pll_config_t);
                break;
            case MAVLINK_MSG_ID_SpeedObsPllOutput:
                mavlink_msg_speedobsplloutput_decode(&msg, (mavlink_speedobsplloutput_t *)&speed_obs_pll_output_t);
                mavlink_msg_speedobsplloutput_encode(sys_id, comp_id, &send_msg, (mavlink_speedobsplloutput_t *)&speed_obs_pll_output_t);
                break;
            case MAVLINK_MSG_ID_ElecAngleIdConfig:
                mavlink_msg_elecangleidconfig_decode(&msg, (mavlink_elecangleidconfig_t *)&elec_angle_id_config_t);
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->elec_angle_id_config.id_max_A = elec_angle_id_config_t.id_max_A;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->elec_angle_id_config.dt_s = elec_angle_id_config_t.dt_s;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->elec_angle_id_config.method = elec_angle_id_config_t.method;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->elec_angle_id_config.angle_add_rad = elec_angle_id_config_t.angle_add_rad;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->elec_angle_id_config.wait_time_s = elec_angle_id_config_t.wait_time_s;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->elec_angle_id_config.test_angle_rad = elec_angle_id_config_t.test_angle_rad;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->elec_angle_id_config.current_slope_percentage = elec_angle_id_config_t.current_slope_percentage;}
                mavlink_msg_elecangleidconfig_encode(sys_id, comp_id, &send_msg, (mavlink_elecangleidconfig_t *)&elec_angle_id_config_t);
                break;
            case MAVLINK_MSG_ID_ElecAngleIdOutput:
                mavlink_msg_elecangleidoutput_decode(&msg, (mavlink_elecangleidoutput_t *)&elec_angle_id_output_t);
                mavlink_msg_elecangleidoutput_encode(sys_id, comp_id, &send_msg, (mavlink_elecangleidoutput_t *)&elec_angle_id_output_t);
                break;
            case MAVLINK_MSG_ID_ElecAngleIdInput:
                mavlink_msg_elecangleidinput_decode(&msg, (mavlink_elecangleidinput_t *)&elec_angle_id_input_t);
                mavlink_msg_elecangleidinput_encode(sys_id, comp_id, &send_msg, (mavlink_elecangleidinput_t *)&elec_angle_id_input_t);
                break;
            case MAVLINK_MSG_ID_DirectionIdInput:
                mavlink_msg_directionidinput_decode(&msg, (mavlink_directionidinput_t *)&direction_id_input_t);
                mavlink_msg_directionidinput_encode(sys_id, comp_id, &send_msg, (mavlink_directionidinput_t *)&direction_id_input_t);
                break;
            case MAVLINK_MSG_ID_DirectionIdConfig:
                mavlink_msg_directionidconfig_decode(&msg, (mavlink_directionidconfig_t *)&direction_id_config_t);
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->direction_id_config.elec_angle_add_rad = direction_id_config_t.elec_angle_add_rad;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->direction_id_config.current_slope_percentage = direction_id_config_t.current_slope_percentage;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->direction_id_config.id_tar_max_A = direction_id_config_t.id_tar_max_A;}
                mavlink_msg_directionidconfig_encode(sys_id, comp_id, &send_msg, (mavlink_directionidconfig_t *)&direction_id_config_t);
                break;
            case MAVLINK_MSG_ID_DirectionIdOutput:
                mavlink_msg_directionidoutput_decode(&msg, (mavlink_directionidoutput_t *)&direction_id_output_t);
                mavlink_msg_directionidoutput_encode(sys_id, comp_id, &send_msg, (mavlink_directionidoutput_t *)&direction_id_output_t);
                break;
            case MAVLINK_MSG_ID_MotorPosSensorInput:
                mavlink_msg_motorpossensorinput_decode(&msg, (mavlink_motorpossensorinput_t *)&motor_pos_sensor_input_t);
                mavlink_msg_motorpossensorinput_encode(sys_id, comp_id, &send_msg, (mavlink_motorpossensorinput_t *)&motor_pos_sensor_input_t);
                break;
            case MAVLINK_MSG_ID_MotorPosSensorConfig:
                mavlink_msg_motorpossensorconfig_decode(&msg, (mavlink_motorpossensorconfig_t *)&motor_pos_sensor_config_t);
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->motor_pos_sensor_config.enc_line_p_n = motor_pos_sensor_config_t.enc_line_p_n;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->motor_pos_sensor_config.init_pos_p = motor_pos_sensor_config_t.init_pos_p;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->motor_pos_sensor_config.pn = motor_pos_sensor_config_t.pn;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->motor_pos_sensor_config.elec_angle_bias_rad = motor_pos_sensor_config_t.elec_angle_bias_rad;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->motor_pos_sensor_config.dir = motor_pos_sensor_config_t.dir;}
                mavlink_msg_motorpossensorconfig_encode(sys_id, comp_id, &send_msg, (mavlink_motorpossensorconfig_t *)&motor_pos_sensor_config_t);
                break;
            case MAVLINK_MSG_ID_MotorPosSensorOutput:
                mavlink_msg_motorpossensoroutput_decode(&msg, (mavlink_motorpossensoroutput_t *)&motor_pos_sensor_output_t);
                mavlink_msg_motorpossensoroutput_encode(sys_id, comp_id, &send_msg, (mavlink_motorpossensoroutput_t *)&motor_pos_sensor_output_t);
                break;
            case MAVLINK_MSG_ID_PolePairsIdInput:
                mavlink_msg_polepairsidinput_decode(&msg, (mavlink_polepairsidinput_t *)&pole_pairs_id_input_t);
                mavlink_msg_polepairsidinput_encode(sys_id, comp_id, &send_msg, (mavlink_polepairsidinput_t *)&pole_pairs_id_input_t);
                break;
            case MAVLINK_MSG_ID_PolePairsIdConfig:
                mavlink_msg_polepairsidconfig_decode(&msg, (mavlink_polepairsidconfig_t *)&pole_pairs_id_config_t);
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->pole_pairs_id_config.elec_angle_add = pole_pairs_id_config_t.elec_angle_add;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->pole_pairs_id_config.enc_line_p_n = pole_pairs_id_config_t.enc_line_p_n;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->pole_pairs_id_config.id_tar_max_A = pole_pairs_id_config_t.id_tar_max_A;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->pole_pairs_id_config.current_slope_percentage = pole_pairs_id_config_t.current_slope_percentage;}
                mavlink_msg_polepairsidconfig_encode(sys_id, comp_id, &send_msg, (mavlink_polepairsidconfig_t *)&pole_pairs_id_config_t);
                break;
            case MAVLINK_MSG_ID_PolePairsIdOutput:
                mavlink_msg_polepairsidoutput_decode(&msg, (mavlink_polepairsidoutput_t *)&pole_pairs_id_output_t);
                mavlink_msg_polepairsidoutput_encode(sys_id, comp_id, &send_msg, (mavlink_polepairsidoutput_t *)&pole_pairs_id_output_t);
                break;
            case MAVLINK_MSG_ID_TqFcIdInput:
                mavlink_msg_tqfcidinput_decode(&msg, (mavlink_tqfcidinput_t *)&tq_fc_id_input_t);
                mavlink_msg_tqfcidinput_encode(sys_id, comp_id, &send_msg, (mavlink_tqfcidinput_t *)&tq_fc_id_input_t);
                break;
            case MAVLINK_MSG_ID_TqFcIdConfig:
                mavlink_msg_tqfcidconfig_decode(&msg, (mavlink_tqfcidconfig_t *)&tq_fc_id_config_t);
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->tq_fc_id_config.enc_line_p_n = tq_fc_id_config_t.enc_line_p_n;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->tq_fc_id_config.iq_com_enable = tq_fc_id_config_t.iq_com_enable;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->tq_fc_id_config.tq_com_enable = tq_fc_id_config_t.tq_com_enable;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->tq_fc_id_config.fc_com_enable = tq_fc_id_config_t.fc_com_enable;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->tq_fc_id_config.fc_p_com = tq_fc_id_config_t.fc_p_com;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->tq_fc_id_config.fc_n_com = tq_fc_id_config_t.fc_n_com;}
                mavlink_msg_tqfcidconfig_encode(sys_id, comp_id, &send_msg, (mavlink_tqfcidconfig_t *)&tq_fc_id_config_t);
                break;
            case MAVLINK_MSG_ID_TqFcIdOutput:
                mavlink_msg_tqfcidoutput_decode(&msg, (mavlink_tqfcidoutput_t *)&tq_fc_id_output_t);
                mavlink_msg_tqfcidoutput_encode(sys_id, comp_id, &send_msg, (mavlink_tqfcidoutput_t *)&tq_fc_id_output_t);
                break;
            case MAVLINK_MSG_ID_ReciprocalMotionConfig:
                mavlink_msg_reciprocalmotionconfig_decode(&msg, (mavlink_reciprocalmotionconfig_t *)&reciprocal_motion_config_t);
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->reciprocal_motion_config.pos_tar1_p = reciprocal_motion_config_t.pos_tar1_p;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->reciprocal_motion_config.pos_tar2_p = reciprocal_motion_config_t.pos_tar2_p;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->reciprocal_motion_config.dwell_time_s = reciprocal_motion_config_t.dwell_time_s;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->reciprocal_motion_config.profile_velocity_p_s = reciprocal_motion_config_t.profile_velocity_p_s;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->reciprocal_motion_config.profile_acc_p_ss = reciprocal_motion_config_t.profile_acc_p_ss;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->reciprocal_motion_config.profile_dec_p_ss = reciprocal_motion_config_t.profile_dec_p_ss;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->reciprocal_motion_config.dt_s = reciprocal_motion_config_t.dt_s;}
                mavlink_msg_reciprocalmotionconfig_encode(sys_id, comp_id, &send_msg, (mavlink_reciprocalmotionconfig_t *)&reciprocal_motion_config_t);
                break;
            case MAVLINK_MSG_ID_ReciprocalMotionOutput:
                mavlink_msg_reciprocalmotionoutput_decode(&msg, (mavlink_reciprocalmotionoutput_t *)&reciprocal_motion_output_t);
                mavlink_msg_reciprocalmotionoutput_encode(sys_id, comp_id, &send_msg, (mavlink_reciprocalmotionoutput_t *)&reciprocal_motion_output_t);
                break;
            case MAVLINK_MSG_ID_ReferenceSignalConfig:
                mavlink_msg_referencesignalconfig_decode(&msg, (mavlink_referencesignalconfig_t *)&reference_signal_config_t);
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->reference_signal_config.dt_s = reference_signal_config_t.dt_s;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->reference_signal_config.signal_type = reference_signal_config_t.signal_type;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->reference_signal_config.amp = reference_signal_config_t.amp;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->reference_signal_config.frq_Hz = reference_signal_config_t.frq_Hz;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->reference_signal_config.bias = reference_signal_config_t.bias;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->reference_signal_config.signal_target = reference_signal_config_t.signal_target;}
                mavlink_msg_referencesignalconfig_encode(sys_id, comp_id, &send_msg, (mavlink_referencesignalconfig_t *)&reference_signal_config_t);
                break;
            case MAVLINK_MSG_ID_ReferenceSignalOutput:
                mavlink_msg_referencesignaloutput_decode(&msg, (mavlink_referencesignaloutput_t *)&reference_signal_output_t);
                mavlink_msg_referencesignaloutput_encode(sys_id, comp_id, &send_msg, (mavlink_referencesignaloutput_t *)&reference_signal_output_t);
                break;
            case MAVLINK_MSG_ID_AppControlWord:
                mavlink_msg_appcontrolword_decode(&msg, (mavlink_appcontrolword_t *)&app_control_word_t);
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Controlword(app_control_word_t.Controlword);}
                app_control_word_t.Controlword = get_app_Controlword();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Halt_running_cmd(app_control_word_t.Halt_running_cmd);}
                app_control_word_t.Halt_running_cmd = get_app_Halt_running_cmd();
                mavlink_msg_appcontrolword_encode(sys_id, comp_id, &send_msg, (mavlink_appcontrolword_t *)&app_control_word_t);
                break;
            case MAVLINK_MSG_ID_AppStatusInfo:
                mavlink_msg_appstatusinfo_decode(&msg, (mavlink_appstatusinfo_t *)&app_status_info_t);
                mavlink_msg_appstatusinfo_encode(sys_id, comp_id, &send_msg, (mavlink_appstatusinfo_t *)&app_status_info_t);
                break;
            case MAVLINK_MSG_ID_AppOpMode:
                mavlink_msg_appopmode_decode(&msg, (mavlink_appopmode_t *)&app_op_mode_t);
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Modes_of_operation(app_op_mode_t.Modes_of_operation);}
                app_op_mode_t.Modes_of_operation = get_app_Modes_of_operation();
                mavlink_msg_appopmode_encode(sys_id, comp_id, &send_msg, (mavlink_appopmode_t *)&app_op_mode_t);
                break;
            case MAVLINK_MSG_ID_AppEncoderConfig:
                mavlink_msg_appencoderconfig_decode(&msg, (mavlink_appencoderconfig_t *)&app_encoder_config_t);
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Load_encoder_resolution(app_encoder_config_t.Load_encoder_resolution);}
                app_encoder_config_t.Load_encoder_resolution = get_app_Load_encoder_resolution();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Motor_encoder_resolution(app_encoder_config_t.Motor_encoder_resolution);}
                app_encoder_config_t.Motor_encoder_resolution = get_app_Motor_encoder_resolution();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Motor_encoder_type(app_encoder_config_t.Motor_encoder_type);}
                app_encoder_config_t.Motor_encoder_type = get_app_Motor_encoder_type();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Load_encoder_type(app_encoder_config_t.Load_encoder_type);}
                app_encoder_config_t.Load_encoder_type = get_app_Load_encoder_type();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Motor_encoder_options(app_encoder_config_t.Motor_encoder_options);}
                app_encoder_config_t.Motor_encoder_options = get_app_Motor_encoder_options();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Load_control_resolution(app_encoder_config_t.Load_control_resolution);}
                app_encoder_config_t.Load_control_resolution = get_app_Load_control_resolution();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Motor_control_resolution(app_encoder_config_t.Motor_control_resolution);}
                app_encoder_config_t.Motor_control_resolution = get_app_Motor_control_resolution();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Load_encoder_options(app_encoder_config_t.Load_encoder_options);}
                app_encoder_config_t.Load_encoder_options = get_app_Load_encoder_options();
                mavlink_msg_appencoderconfig_encode(sys_id, comp_id, &send_msg, (mavlink_appencoderconfig_t *)&app_encoder_config_t);
                break;
            case MAVLINK_MSG_ID_AppBaseConfig:
                mavlink_msg_appbaseconfig_decode(&msg, (mavlink_appbaseconfig_t *)&app_base_config_t);
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Polarity(app_base_config_t.Polarity);}
                app_base_config_t.Polarity = get_app_Polarity();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Can_id(app_base_config_t.Can_id);}
                app_base_config_t.Can_id = get_app_Can_id();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Can_baudrate(app_base_config_t.Can_baudrate);}
                app_base_config_t.Can_baudrate = get_app_Can_baudrate();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Quick_stop_option_code(app_base_config_t.Quick_stop_option_code);}
                app_base_config_t.Quick_stop_option_code = get_app_Quick_stop_option_code();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Brake_engage_time(app_base_config_t.Brake_engage_time);}
                app_base_config_t.Brake_engage_time = get_app_Brake_engage_time();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Brake_release_time(app_base_config_t.Brake_release_time);}
                app_base_config_t.Brake_release_time = get_app_Brake_release_time();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Dynamic_brake_speed_threshold(app_base_config_t.Dynamic_brake_speed_threshold);}
                app_base_config_t.Dynamic_brake_speed_threshold = get_app_Dynamic_brake_speed_threshold();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Brake_release_hold_voltage(app_base_config_t.Brake_release_hold_voltage);}
                app_base_config_t.Brake_release_hold_voltage = get_app_Brake_release_hold_voltage();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Digital_io_outputs_phys(app_base_config_t.Digital_io_outputs_phys);}
                app_base_config_t.Digital_io_outputs_phys = get_app_Digital_io_outputs_phys();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Digital_io_outputs_mask(app_base_config_t.Digital_io_outputs_mask);}
                app_base_config_t.Digital_io_outputs_mask = get_app_Digital_io_outputs_mask();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Brake_control_mode(app_base_config_t.Brake_control_mode);}
                app_base_config_t.Brake_control_mode = get_app_Brake_control_mode();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Brake_rated_voltage(app_base_config_t.Brake_rated_voltage);}
                app_base_config_t.Brake_rated_voltage = get_app_Brake_rated_voltage();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Brake_release_action_voltage(app_base_config_t.Brake_release_action_voltage);}
                app_base_config_t.Brake_release_action_voltage = get_app_Brake_release_action_voltage();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Brake_release_pwm_freq(app_base_config_t.Brake_release_pwm_freq);}
                app_base_config_t.Brake_release_pwm_freq = get_app_Brake_release_pwm_freq();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Brake_engage_delay_time(app_base_config_t.Brake_engage_delay_time);}
                app_base_config_t.Brake_engage_delay_time = get_app_Brake_engage_delay_time();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Brake_release_delay_time(app_base_config_t.Brake_release_delay_time);}
                app_base_config_t.Brake_release_delay_time = get_app_Brake_release_delay_time();
                mavlink_msg_appbaseconfig_encode(sys_id, comp_id, &send_msg, (mavlink_appbaseconfig_t *)&app_base_config_t);
                break;
            case MAVLINK_MSG_ID_AppMotionParam:
                mavlink_msg_appmotionparam_decode(&msg, (mavlink_appmotionparam_t *)&app_motion_param_t);
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Target_position(app_motion_param_t.Target_position);}
                app_motion_param_t.Target_position = get_app_Target_position();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Profile_velocity(app_motion_param_t.Profile_velocity);}
                app_motion_param_t.Profile_velocity = get_app_Profile_velocity();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Profile_acceleration(app_motion_param_t.Profile_acceleration);}
                app_motion_param_t.Profile_acceleration = get_app_Profile_acceleration();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Profile_deceleration(app_motion_param_t.Profile_deceleration);}
                app_motion_param_t.Profile_deceleration = get_app_Profile_deceleration();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Quick_stop_deceleration(app_motion_param_t.Quick_stop_deceleration);}
                app_motion_param_t.Quick_stop_deceleration = get_app_Quick_stop_deceleration();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Motion_profile_type(app_motion_param_t.Motion_profile_type);}
                app_motion_param_t.Motion_profile_type = get_app_Motion_profile_type();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Home_offset(app_motion_param_t.Home_offset);}
                app_motion_param_t.Home_offset = get_app_Home_offset();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Homing_method(app_motion_param_t.Homing_method);}
                app_motion_param_t.Homing_method = get_app_Homing_method();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Target_velocity(app_motion_param_t.Target_velocity);}
                app_motion_param_t.Target_velocity = get_app_Target_velocity();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Target_torque(app_motion_param_t.Target_torque);}
                app_motion_param_t.Target_torque = get_app_Target_torque();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Torque_slope(app_motion_param_t.Torque_slope);}
                app_motion_param_t.Torque_slope = get_app_Torque_slope();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Encoder_calibration_speed(app_motion_param_t.Encoder_calibration_speed);}
                app_motion_param_t.Encoder_calibration_speed = get_app_Encoder_calibration_speed();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_MIT_feedforward_torque(app_motion_param_t.MIT_feedforward_torque);}
                app_motion_param_t.MIT_feedforward_torque = get_app_MIT_feedforward_torque();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_MIT_target_position(app_motion_param_t.MIT_target_position);}
                app_motion_param_t.MIT_target_position = get_app_MIT_target_position();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_MIT_max_current(app_motion_param_t.MIT_max_current);}
                app_motion_param_t.MIT_max_current = get_app_MIT_max_current();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_MIT_target_velocity(app_motion_param_t.MIT_target_velocity);}
                app_motion_param_t.MIT_target_velocity = get_app_MIT_target_velocity();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_MIT_kp(app_motion_param_t.MIT_kp);}
                app_motion_param_t.MIT_kp = get_app_MIT_kp();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_MIT_kd(app_motion_param_t.MIT_kd);}
                app_motion_param_t.MIT_kd = get_app_MIT_kd();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Interp_time_value(app_motion_param_t.Interp_time_value);}
                app_motion_param_t.Interp_time_value = get_app_Interp_time_value();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Interp_time_index(app_motion_param_t.Interp_time_index);}
                app_motion_param_t.Interp_time_index = get_app_Interp_time_index();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Homing_speed_search_for_switch(app_motion_param_t.Homing_speed_search_for_switch);}
                app_motion_param_t.Homing_speed_search_for_switch = get_app_Homing_speed_search_for_switch();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Homing_speed_search_for_zero(app_motion_param_t.Homing_speed_search_for_zero);}
                app_motion_param_t.Homing_speed_search_for_zero = get_app_Homing_speed_search_for_zero();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Homing_acceleration(app_motion_param_t.Homing_acceleration);}
                app_motion_param_t.Homing_acceleration = get_app_Homing_acceleration();
                mavlink_msg_appmotionparam_encode(sys_id, comp_id, &send_msg, (mavlink_appmotionparam_t *)&app_motion_param_t);
                break;
            case MAVLINK_MSG_ID_AppRestrictParam:
                mavlink_msg_apprestrictparam_decode(&msg, (mavlink_apprestrictparam_t *)&app_restrict_param_t);
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Position_range_limit_Minimal_position_limit(app_restrict_param_t.Position_range_limit_Minimal_position_limit);}
                app_restrict_param_t.Position_range_limit_Minimal_position_limit = get_app_Position_range_limit_Minimal_position_limit();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Position_range_limit_Maximal_position_limit(app_restrict_param_t.Position_range_limit_Maximal_position_limit);}
                app_restrict_param_t.Position_range_limit_Maximal_position_limit = get_app_Position_range_limit_Maximal_position_limit();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Software_position_limit_Minimal_position_limit(app_restrict_param_t.Software_position_limit_Minimal_position_limit);}
                app_restrict_param_t.Software_position_limit_Minimal_position_limit = get_app_Software_position_limit_Minimal_position_limit();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Software_position_limit_Maximal_position_limit(app_restrict_param_t.Software_position_limit_Maximal_position_limit);}
                app_restrict_param_t.Software_position_limit_Maximal_position_limit = get_app_Software_position_limit_Maximal_position_limit();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Max_profile_velocity(app_restrict_param_t.Max_profile_velocity);}
                app_restrict_param_t.Max_profile_velocity = get_app_Max_profile_velocity();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Max_motor_speed(app_restrict_param_t.Max_motor_speed);}
                app_restrict_param_t.Max_motor_speed = get_app_Max_motor_speed();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Max_acceleration(app_restrict_param_t.Max_acceleration);}
                app_restrict_param_t.Max_acceleration = get_app_Max_acceleration();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Max_deceleration(app_restrict_param_t.Max_deceleration);}
                app_restrict_param_t.Max_deceleration = get_app_Max_deceleration();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Max_current(app_restrict_param_t.Max_current);}
                app_restrict_param_t.Max_current = get_app_Max_current();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Position_limit_enable(app_restrict_param_t.Position_limit_enable);}
                app_restrict_param_t.Position_limit_enable = get_app_Position_limit_enable();
                mavlink_msg_apprestrictparam_encode(sys_id, comp_id, &send_msg, (mavlink_apprestrictparam_t *)&app_restrict_param_t);
                break;
            case MAVLINK_MSG_ID_AppMotionInfo:
                mavlink_msg_appmotioninfo_decode(&msg, (mavlink_appmotioninfo_t *)&app_motion_info_t);
                mavlink_msg_appmotioninfo_encode(sys_id, comp_id, &send_msg, (mavlink_appmotioninfo_t *)&app_motion_info_t);
                break;
            case MAVLINK_MSG_ID_AppWindowParam:
                mavlink_msg_appwindowparam_decode(&msg, (mavlink_appwindowparam_t *)&app_window_param_t);
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Following_error_window(app_window_param_t.Following_error_window);}
                app_window_param_t.Following_error_window = get_app_Following_error_window();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Following_error_time_out(app_window_param_t.Following_error_time_out);}
                app_window_param_t.Following_error_time_out = get_app_Following_error_time_out();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Position_window(app_window_param_t.Position_window);}
                app_window_param_t.Position_window = get_app_Position_window();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Position_window_time(app_window_param_t.Position_window_time);}
                app_window_param_t.Position_window_time = get_app_Position_window_time();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Velocity_window(app_window_param_t.Velocity_window);}
                app_window_param_t.Velocity_window = get_app_Velocity_window();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Velocity_window_time(app_window_param_t.Velocity_window_time);}
                app_window_param_t.Velocity_window_time = get_app_Velocity_window_time();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Velocity_threshold(app_window_param_t.Velocity_threshold);}
                app_window_param_t.Velocity_threshold = get_app_Velocity_threshold();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Velocity_threshold_time(app_window_param_t.Velocity_threshold_time);}
                app_window_param_t.Velocity_threshold_time = get_app_Velocity_threshold_time();
                mavlink_msg_appwindowparam_encode(sys_id, comp_id, &send_msg, (mavlink_appwindowparam_t *)&app_window_param_t);
                break;
            case MAVLINK_MSG_ID_AppMotorConfig:
                mavlink_msg_appmotorconfig_decode(&msg, (mavlink_appmotorconfig_t *)&app_motor_config_t);
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Motor_rated_current(app_motor_config_t.Motor_rated_current);}
                app_motor_config_t.Motor_rated_current = get_app_Motor_rated_current();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Motor_rated_torque(app_motor_config_t.Motor_rated_torque);}
                app_motor_config_t.Motor_rated_torque = get_app_Motor_rated_torque();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Motor_peak_current(app_motor_config_t.Motor_peak_current);}
                app_motor_config_t.Motor_peak_current = get_app_Motor_peak_current();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Motor_pole_pairs(app_motor_config_t.Motor_pole_pairs);}
                app_motor_config_t.Motor_pole_pairs = get_app_Motor_pole_pairs();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Motor_maximum_speed(app_motor_config_t.Motor_maximum_speed);}
                app_motor_config_t.Motor_maximum_speed = get_app_Motor_maximum_speed();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Resistance(app_motor_config_t.Resistance);}
                app_motor_config_t.Resistance = get_app_Resistance();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Inductance(app_motor_config_t.Inductance);}
                app_motor_config_t.Inductance = get_app_Inductance();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Reduction_ratio_num(app_motor_config_t.Reduction_ratio_num);}
                app_motor_config_t.Reduction_ratio_num = get_app_Reduction_ratio_num();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Reduction_ratio_den(app_motor_config_t.Reduction_ratio_den);}
                app_motor_config_t.Reduction_ratio_den = get_app_Reduction_ratio_den();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Torque_constant(app_motor_config_t.Torque_constant);}
                app_motor_config_t.Torque_constant = get_app_Torque_constant();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Motor_rotor_inertia(app_motor_config_t.Motor_rotor_inertia);}
                app_motor_config_t.Motor_rotor_inertia = get_app_Motor_rotor_inertia();
                mavlink_msg_appmotorconfig_encode(sys_id, comp_id, &send_msg, (mavlink_appmotorconfig_t *)&app_motor_config_t);
                break;
            case MAVLINK_MSG_ID_AppProtectConfig:
                mavlink_msg_appprotectconfig_decode(&msg, (mavlink_appprotectconfig_t *)&app_protect_config_t);
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Bus_under_voltage_threshold(app_protect_config_t.Bus_under_voltage_threshold);}
                app_protect_config_t.Bus_under_voltage_threshold = get_app_Bus_under_voltage_threshold();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Bus_over_voltage_threshold(app_protect_config_t.Bus_over_voltage_threshold);}
                app_protect_config_t.Bus_over_voltage_threshold = get_app_Bus_over_voltage_threshold();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Drive_overload_current_duration(app_protect_config_t.Drive_overload_current_duration);}
                app_protect_config_t.Drive_overload_current_duration = get_app_Drive_overload_current_duration();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Drive_peak_current_duration(app_protect_config_t.Drive_peak_current_duration);}
                app_protect_config_t.Drive_peak_current_duration = get_app_Drive_peak_current_duration();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Drive_temperature_threshold_time(app_protect_config_t.Drive_temperature_threshold_time);}
                app_protect_config_t.Drive_temperature_threshold_time = get_app_Drive_temperature_threshold_time();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Drive_low_temperature_fault_threshold(app_protect_config_t.Drive_low_temperature_fault_threshold);}
                app_protect_config_t.Drive_low_temperature_fault_threshold = get_app_Drive_low_temperature_fault_threshold();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Drive_high_temperature_fault_threshold(app_protect_config_t.Drive_high_temperature_fault_threshold);}
                app_protect_config_t.Drive_high_temperature_fault_threshold = get_app_Drive_high_temperature_fault_threshold();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Overspeed_threshold(app_protect_config_t.Overspeed_threshold);}
                app_protect_config_t.Overspeed_threshold = get_app_Overspeed_threshold();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Drive_overcurrent_threshold(app_protect_config_t.Drive_overcurrent_threshold);}
                app_protect_config_t.Drive_overcurrent_threshold = get_app_Drive_overcurrent_threshold();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Protection_enable(app_protect_config_t.Protection_enable);}
                app_protect_config_t.Protection_enable = get_app_Protection_enable();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Motor_low_temperature_fault_threshold(app_protect_config_t.Motor_low_temperature_fault_threshold);}
                app_protect_config_t.Motor_low_temperature_fault_threshold = get_app_Motor_low_temperature_fault_threshold();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Motor_high_temperature_fault_threshold(app_protect_config_t.Motor_high_temperature_fault_threshold);}
                app_protect_config_t.Motor_high_temperature_fault_threshold = get_app_Motor_high_temperature_fault_threshold();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Can_timeout(app_protect_config_t.Can_timeout);}
                app_protect_config_t.Can_timeout = get_app_Can_timeout();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Motor_low_temperature_warning_threshold(app_protect_config_t.Motor_low_temperature_warning_threshold);}
                app_protect_config_t.Motor_low_temperature_warning_threshold = get_app_Motor_low_temperature_warning_threshold();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Motor_high_temperature_warning_threshold(app_protect_config_t.Motor_high_temperature_warning_threshold);}
                app_protect_config_t.Motor_high_temperature_warning_threshold = get_app_Motor_high_temperature_warning_threshold();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Mcu_temperature_threshold_time(app_protect_config_t.Mcu_temperature_threshold_time);}
                app_protect_config_t.Mcu_temperature_threshold_time = get_app_Mcu_temperature_threshold_time();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Mcu_low_temperature_fault_threshold(app_protect_config_t.Mcu_low_temperature_fault_threshold);}
                app_protect_config_t.Mcu_low_temperature_fault_threshold = get_app_Mcu_low_temperature_fault_threshold();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Mcu_high_temperature_fault_threshold(app_protect_config_t.Mcu_high_temperature_fault_threshold);}
                app_protect_config_t.Mcu_high_temperature_fault_threshold = get_app_Mcu_high_temperature_fault_threshold();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Mcu_low_temperature_warning_threshold(app_protect_config_t.Mcu_low_temperature_warning_threshold);}
                app_protect_config_t.Mcu_low_temperature_warning_threshold = get_app_Mcu_low_temperature_warning_threshold();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Mcu_high_temperature_warning_threshold(app_protect_config_t.Mcu_high_temperature_warning_threshold);}
                app_protect_config_t.Mcu_high_temperature_warning_threshold = get_app_Mcu_high_temperature_warning_threshold();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Drive_low_temperature_warning_threshold(app_protect_config_t.Drive_low_temperature_warning_threshold);}
                app_protect_config_t.Drive_low_temperature_warning_threshold = get_app_Drive_low_temperature_warning_threshold();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Drive_high_temperature_warning_threshold(app_protect_config_t.Drive_high_temperature_warning_threshold);}
                app_protect_config_t.Drive_high_temperature_warning_threshold = get_app_Drive_high_temperature_warning_threshold();
                mavlink_msg_appprotectconfig_encode(sys_id, comp_id, &send_msg, (mavlink_appprotectconfig_t *)&app_protect_config_t);
                break;
            case MAVLINK_MSG_ID_MitCtlInput:
                mavlink_msg_mitctlinput_decode(&msg, (mavlink_mitctlinput_t *)&mit_ctl_input_t);
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->mit_ctl_input.tq_set_NM = mit_ctl_input_t.tq_set_NM;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->mit_ctl_input.pos_tar_p = mit_ctl_input_t.pos_tar_p;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->mit_ctl_input.iq_max_A = mit_ctl_input_t.iq_max_A;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->mit_ctl_input.speed_tar_p_s = mit_ctl_input_t.speed_tar_p_s;}
                mavlink_msg_mitctlinput_encode(sys_id, comp_id, &send_msg, (mavlink_mitctlinput_t *)&mit_ctl_input_t);
                break;
            case MAVLINK_MSG_ID_MitCtlConfig:
                mavlink_msg_mitctlconfig_decode(&msg, (mavlink_mitctlconfig_t *)&mit_ctl_config_t);
                axis->mit_ctl_config.kp_pos_NM_rad = mit_ctl_config_t.kp_pos_NM_rad;
                axis->mit_ctl_config.kd_spd_NM_rad_s = mit_ctl_config_t.kd_spd_NM_rad_s;
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->mit_ctl_config.enc_line_inv_p_n = mit_ctl_config_t.enc_line_inv_p_n;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->mit_ctl_config.kt_NM_A = mit_ctl_config_t.kt_NM_A;}
                mavlink_msg_mitctlconfig_encode(sys_id, comp_id, &send_msg, (mavlink_mitctlconfig_t *)&mit_ctl_config_t);
                break;
            case MAVLINK_MSG_ID_MitCtlOutput:
                mavlink_msg_mitctloutput_decode(&msg, (mavlink_mitctloutput_t *)&mit_ctl_output_t);
                mavlink_msg_mitctloutput_encode(sys_id, comp_id, &send_msg, (mavlink_mitctloutput_t *)&mit_ctl_output_t);
                break;
            case MAVLINK_MSG_ID_AppPermissionConfig:
                mavlink_msg_apppermissionconfig_decode(&msg, (mavlink_apppermissionconfig_t *)&app_permission_config_t);
                set_app_Comm_control_authority(app_permission_config_t.Comm_control_authority);
                app_permission_config_t.Comm_control_authority = get_app_Comm_control_authority();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Internal_control_authority(app_permission_config_t.Internal_control_authority);}
                app_permission_config_t.Internal_control_authority = get_app_Internal_control_authority();
                mavlink_msg_apppermissionconfig_encode(sys_id, comp_id, &send_msg, (mavlink_apppermissionconfig_t *)&app_permission_config_t);
                break;
            case MAVLINK_MSG_ID_SystemCmd:
                mavlink_msg_systemcmd_decode(&msg, (mavlink_systemcmd_t *)&system_cmd_t);
                set_app_Sys_cmd(system_cmd_t.Sys_cmd);
                system_cmd_t.Sys_cmd = get_app_Sys_cmd();
                mavlink_msg_systemcmd_encode(sys_id, comp_id, &send_msg, (mavlink_systemcmd_t *)&system_cmd_t);
                break;
            case MAVLINK_MSG_ID_LoadPosSensorInput:
                mavlink_msg_loadpossensorinput_decode(&msg, (mavlink_loadpossensorinput_t *)&load_pos_sensor_input_t);
                mavlink_msg_loadpossensorinput_encode(sys_id, comp_id, &send_msg, (mavlink_loadpossensorinput_t *)&load_pos_sensor_input_t);
                break;
            case MAVLINK_MSG_ID_LoadPosSensorConfig:
                mavlink_msg_loadpossensorconfig_decode(&msg, (mavlink_loadpossensorconfig_t *)&load_pos_sensor_config_t);
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->load_pos_sensor_config.enc_line_p_n = load_pos_sensor_config_t.enc_line_p_n;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->load_pos_sensor_config.init_pos_p = load_pos_sensor_config_t.init_pos_p;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->load_pos_sensor_config.dir = load_pos_sensor_config_t.dir;}
                mavlink_msg_loadpossensorconfig_encode(sys_id, comp_id, &send_msg, (mavlink_loadpossensorconfig_t *)&load_pos_sensor_config_t);
                break;
            case MAVLINK_MSG_ID_LoadPosSensorOutput:
                mavlink_msg_loadpossensoroutput_decode(&msg, (mavlink_loadpossensoroutput_t *)&load_pos_sensor_output_t);
                mavlink_msg_loadpossensoroutput_encode(sys_id, comp_id, &send_msg, (mavlink_loadpossensoroutput_t *)&load_pos_sensor_output_t);
                break;
            case MAVLINK_MSG_ID_SystemStatus:
                mavlink_msg_systemstatus_decode(&msg, (mavlink_systemstatus_t *)&system_status_t);
                set_app_Storage_status(system_status_t.Storage_status);
                system_status_t.Storage_status = get_app_Storage_status();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Storage_cmd(system_status_t.Storage_cmd);}
                system_status_t.Storage_cmd = get_app_Storage_cmd();
                mavlink_msg_systemstatus_encode(sys_id, comp_id, &send_msg, (mavlink_systemstatus_t *)&system_status_t);
                break;
            case MAVLINK_MSG_ID_EncoderCalibrationCmd:
                mavlink_msg_encodercalibrationcmd_decode(&msg, (mavlink_encodercalibrationcmd_t *)&encoder_calibration_cmd_t);
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Calibration_cmd(encoder_calibration_cmd_t.Calibration_cmd);}
                encoder_calibration_cmd_t.Calibration_cmd = get_app_Calibration_cmd();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Calibration_time(encoder_calibration_cmd_t.Calibration_time);}
                encoder_calibration_cmd_t.Calibration_time = get_app_Calibration_time();
                mavlink_msg_encodercalibrationcmd_encode(sys_id, comp_id, &send_msg, (mavlink_encodercalibrationcmd_t *)&encoder_calibration_cmd_t);
                break;
            case MAVLINK_MSG_ID_EncoderCalibrationStatus:
                mavlink_msg_encodercalibrationstatus_decode(&msg, (mavlink_encodercalibrationstatus_t *)&encoder_calibration_status_t);
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Calibration_status(encoder_calibration_status_t.Calibration_status);}
                encoder_calibration_status_t.Calibration_status = get_app_Calibration_status();
                mavlink_msg_encodercalibrationstatus_encode(sys_id, comp_id, &send_msg, (mavlink_encodercalibrationstatus_t *)&encoder_calibration_status_t);
                break;
            case MAVLINK_MSG_ID_CustomInfo:
                mavlink_msg_custominfo_decode(&msg, (mavlink_custominfo_t *)&custom_info_t);
                mavlink_msg_custominfo_encode(sys_id, comp_id, &send_msg, (mavlink_custominfo_t *)&custom_info_t);
                break;
            case MAVLINK_MSG_ID_HeartBit:
                mavlink_msg_heartbit_decode(&msg, (mavlink_heartbit_t *)&heart_bit_t);
                set_app_Sys_init_flag(heart_bit_t.Sys_init_flag);
                heart_bit_t.Sys_init_flag = get_app_Sys_init_flag();
                mavlink_msg_heartbit_encode(sys_id, comp_id, &send_msg, (mavlink_heartbit_t *)&heart_bit_t);
                break;
            case MAVLINK_MSG_ID_HistoricalInfo:
                mavlink_msg_historicalinfo_decode(&msg, (mavlink_historicalinfo_t *)&historical_info_t);
                mavlink_msg_historicalinfo_encode(sys_id, comp_id, &send_msg, (mavlink_historicalinfo_t *)&historical_info_t);
                break;
            case MAVLINK_MSG_ID_SimPlantInput:
                mavlink_msg_simplantinput_decode(&msg, (mavlink_simplantinput_t *)&sim_plant_input_t);
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){memcpy(axis->sim_plant_input.uabc_tar_V, sim_plant_input_t.uabc_tar_V, sizeof(sim_plant_input_t.uabc_tar_V));}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->sim_plant_input.tl_Nm = sim_plant_input_t.tl_Nm;}
                mavlink_msg_simplantinput_encode(sys_id, comp_id, &send_msg, (mavlink_simplantinput_t *)&sim_plant_input_t);
                break;
            case MAVLINK_MSG_ID_SimPlantOutput:
                mavlink_msg_simplantoutput_decode(&msg, (mavlink_simplantoutput_t *)&sim_plant_output_t);
                mavlink_msg_simplantoutput_encode(sys_id, comp_id, &send_msg, (mavlink_simplantoutput_t *)&sim_plant_output_t);
                break;
            case MAVLINK_MSG_ID_SimPlantConfig:
                mavlink_msg_simplantconfig_decode(&msg, (mavlink_simplantconfig_t *)&sim_plant_config_t);
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->sim_plant_config.b = sim_plant_config_t.b;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->sim_plant_config.fc = sim_plant_config_t.fc;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->sim_plant_config.flux = sim_plant_config_t.flux;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->sim_plant_config.kt = sim_plant_config_t.kt;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->sim_plant_config.j = sim_plant_config_t.j;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->sim_plant_config.ld = sim_plant_config_t.ld;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->sim_plant_config.lq = sim_plant_config_t.lq;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->sim_plant_config.peak_current_A = sim_plant_config_t.peak_current_A;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->sim_plant_config.pn = sim_plant_config_t.pn;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->sim_plant_config.r = sim_plant_config_t.r;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->sim_plant_config.rated_current_A = sim_plant_config_t.rated_current_A;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->sim_plant_config.speed_max_rpm = sim_plant_config_t.speed_max_rpm;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->sim_plant_config.dt_s = sim_plant_config_t.dt_s;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->sim_plant_config.enc_line_p_n = sim_plant_config_t.enc_line_p_n;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->sim_plant_config.j_inv = sim_plant_config_t.j_inv;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->sim_plant_config.ld_inv = sim_plant_config_t.ld_inv;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->sim_plant_config.lq_inv = sim_plant_config_t.lq_inv;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->sim_plant_config.enc_line_init_pos_P = sim_plant_config_t.enc_line_init_pos_P;}
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){axis->sim_plant_config.enc_noise = sim_plant_config_t.enc_noise;}
                mavlink_msg_simplantconfig_encode(sys_id, comp_id, &send_msg, (mavlink_simplantconfig_t *)&sim_plant_config_t);
                break;
            case MAVLINK_MSG_ID_AppDebugParam:
                mavlink_msg_appdebugparam_decode(&msg, (mavlink_appdebugparam_t *)&app_debug_param_t);
                memcpy(get_app_Debug_float_addr(), app_debug_param_t.Debug_float, sizeof(app_debug_param_t.Debug_float));
                memcpy(get_app_Debug_uint32_addr(), app_debug_param_t.Debug_uint32, sizeof(app_debug_param_t.Debug_uint32));
                memcpy(get_app_Debug_int32_addr(), app_debug_param_t.Debug_int32, sizeof(app_debug_param_t.Debug_int32));
                mavlink_msg_appdebugparam_encode(sys_id, comp_id, &send_msg, (mavlink_appdebugparam_t *)&app_debug_param_t);
                break;
            case MAVLINK_MSG_ID_AppMavlinkConfig:
                mavlink_msg_appmavlinkconfig_decode(&msg, (mavlink_appmavlinkconfig_t *)&app_mavlink_config_t);
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Sys_id(app_mavlink_config_t.Sys_id);}
                app_mavlink_config_t.Sys_id = get_app_Sys_id();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Comp_id(app_mavlink_config_t.Comp_id);}
                app_mavlink_config_t.Comp_id = get_app_Comp_id();
                mavlink_msg_appmavlinkconfig_encode(sys_id, comp_id, &send_msg, (mavlink_appmavlinkconfig_t *)&app_mavlink_config_t);
                break;
            case MAVLINK_MSG_ID_AppFileTransferConfig:
                mavlink_msg_appfiletransferconfig_decode(&msg, (mavlink_appfiletransferconfig_t *)&app_file_transfer_config_t);
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_File_type(app_file_transfer_config_t.File_type);}
                app_file_transfer_config_t.File_type = get_app_File_type();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_File_size(app_file_transfer_config_t.File_size);}
                app_file_transfer_config_t.File_size = get_app_File_size();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_File_direction(app_file_transfer_config_t.File_direction);}
                app_file_transfer_config_t.File_direction = get_app_File_direction();
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_File_index_complete(app_file_transfer_config_t.File_index_complete);}
                app_file_transfer_config_t.File_index_complete = get_app_File_index_complete();
                mavlink_msg_appfiletransferconfig_encode(sys_id, comp_id, &send_msg, (mavlink_appfiletransferconfig_t *)&app_file_transfer_config_t);
                break;
            case MAVLINK_MSG_ID_AppFwUpgradeParam:
                mavlink_msg_appfwupgradeparam_decode(&msg, (mavlink_appfwupgradeparam_t *)&app_fw_upgrade_param_t);
                if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){set_app_Fw_mode(app_fw_upgrade_param_t.Fw_mode);}
                app_fw_upgrade_param_t.Fw_mode = get_app_Fw_mode();
                mavlink_msg_appfwupgradeparam_encode(sys_id, comp_id, &send_msg, (mavlink_appfwupgradeparam_t *)&app_fw_upgrade_param_t);
                break;
//DATABASE_CODE_STOP_3
            default:
                break;
        }

        if (msg.msgid == MAVLINK_MSG_ID_PosSpeedCtlConfig)  //可能 j_kt 被修改，自动更新j
        {
            //同步更新应用层转子惯量
            set_app_Motor_rotor_inertia(axis->pmsm_config.kt * axis->pos_speed_ctl_config.j_kt * 1e4f);
        }

        MotorCtlParamSetUpdata(axis);
    }

    len = mavlink_msg_to_send_buffer(mavlink_tx_buff, &send_msg);
    CallSendCallback(mavlink_tx_buff, len);
}

void RegisterSendCallback(MavlinkSendCallbackFunction callback)
{
    registry.callback = callback;
}

void CallSendCallback(uint8_t *pdata, uint32_t len)
{
    if (registry.callback != NULL) {
        registry.callback(pdata, len);
    }
}

