/** @file
 *    @brief MAVLink comm protocol testsuite generated from servo_hub_database.xml
 *    @see https://mavlink.io/en/
 */
#pragma once
#ifndef SERVO_HUB_DATABASE_TESTSUITE_H
#define SERVO_HUB_DATABASE_TESTSUITE_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef MAVLINK_TEST_ALL
#define MAVLINK_TEST_ALL

static void mavlink_test_servo_hub_database(uint8_t, uint8_t, mavlink_message_t *last_msg);

static void mavlink_test_all(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{

    mavlink_test_servo_hub_database(system_id, component_id, last_msg);
}
#endif




static void mavlink_test_command_long(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_COMMAND_LONG >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_command_long_t packet_in = {
        17.0,45.0,73.0,101.0,129.0,157.0,185.0,89,156,223,34
    };
    mavlink_command_long_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.param1 = packet_in.param1;
        packet1.param2 = packet_in.param2;
        packet1.param3 = packet_in.param3;
        packet1.param4 = packet_in.param4;
        packet1.param5 = packet_in.param5;
        packet1.param6 = packet_in.param6;
        packet1.param7 = packet_in.param7;
        packet1.target_system = packet_in.target_system;
        packet1.target_component = packet_in.target_component;
        packet1.command = packet_in.command;
        packet1.confirmation = packet_in.confirmation;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_COMMAND_LONG_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_COMMAND_LONG_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_command_long_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_command_long_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_command_long_pack(system_id, component_id, &msg , packet1.target_system , packet1.target_component , packet1.command , packet1.confirmation , packet1.param1 , packet1.param2 , packet1.param3 , packet1.param4 , packet1.param5 , packet1.param6 , packet1.param7 );
    mavlink_msg_command_long_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_command_long_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.target_system , packet1.target_component , packet1.command , packet1.confirmation , packet1.param1 , packet1.param2 , packet1.param3 , packet1.param4 , packet1.param5 , packet1.param6 , packet1.param7 );
    mavlink_msg_command_long_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_command_long_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_command_long_send(MAVLINK_COMM_1 , packet1.target_system , packet1.target_component , packet1.command , packet1.confirmation , packet1.param1 , packet1.param2 , packet1.param3 , packet1.param4 , packet1.param5 , packet1.param6 , packet1.param7 );
    mavlink_msg_command_long_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("COMMAND_LONG") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_COMMAND_LONG) != NULL);
#endif
}

static void mavlink_test_command_ack(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_COMMAND_ACK >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_command_ack_t packet_in = {
        17235,139,206,963497672,29,963497932
    };
    mavlink_command_ack_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.command = packet_in.command;
        packet1.result = packet_in.result;
        packet1.progress = packet_in.progress;
        packet1.result_param2 = packet_in.result_param2;
        packet1.target_system = packet_in.target_system;
        packet1.target_component = packet_in.target_component;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_COMMAND_ACK_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_COMMAND_ACK_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_command_ack_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_command_ack_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_command_ack_pack(system_id, component_id, &msg , packet1.command , packet1.result , packet1.progress , packet1.result_param2 , packet1.target_system , packet1.target_component );
    mavlink_msg_command_ack_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_command_ack_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.command , packet1.result , packet1.progress , packet1.result_param2 , packet1.target_system , packet1.target_component );
    mavlink_msg_command_ack_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_command_ack_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_command_ack_send(MAVLINK_COMM_1 , packet1.command , packet1.result , packet1.progress , packet1.result_param2 , packet1.target_system , packet1.target_component );
    mavlink_msg_command_ack_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("COMMAND_ACK") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_COMMAND_ACK) != NULL);
#endif
}

static void mavlink_test_read_param(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_READ_PARAM >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_read_param_t packet_in = {
        963497464
    };
    mavlink_read_param_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.struct_id = packet_in.struct_id;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_READ_PARAM_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_READ_PARAM_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_read_param_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_read_param_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_read_param_pack(system_id, component_id, &msg , packet1.struct_id );
    mavlink_msg_read_param_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_read_param_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.struct_id );
    mavlink_msg_read_param_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_read_param_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_read_param_send(MAVLINK_COMM_1 , packet1.struct_id );
    mavlink_msg_read_param_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("READ_PARAM") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_READ_PARAM) != NULL);
#endif
}

static void mavlink_test_pmsmconfig(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_PmsmConfig >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_pmsmconfig_t packet_in = {
        17.0,45.0,73.0,101.0,129.0,157.0,185.0,213.0,241.0,269.0,297.0,325.0,353.0,963500168,409.0
    };
    mavlink_pmsmconfig_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.b = packet_in.b;
        packet1.fc = packet_in.fc;
        packet1.flux = packet_in.flux;
        packet1.j = packet_in.j;
        packet1.ld = packet_in.ld;
        packet1.lq = packet_in.lq;
        packet1.peak_current = packet_in.peak_current;
        packet1.pn = packet_in.pn;
        packet1.r = packet_in.r;
        packet1.rated_current = packet_in.rated_current;
        packet1.speed_max_rpm = packet_in.speed_max_rpm;
        packet1.tp_s = packet_in.tp_s;
        packet1.tc_s = packet_in.tc_s;
        packet1.enc_line_p_n = packet_in.enc_line_p_n;
        packet1.kt = packet_in.kt;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_PmsmConfig_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_PmsmConfig_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_pmsmconfig_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_pmsmconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_pmsmconfig_pack(system_id, component_id, &msg , packet1.b , packet1.fc , packet1.flux , packet1.j , packet1.ld , packet1.lq , packet1.peak_current , packet1.pn , packet1.r , packet1.rated_current , packet1.speed_max_rpm , packet1.tp_s , packet1.tc_s , packet1.enc_line_p_n , packet1.kt );
    mavlink_msg_pmsmconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_pmsmconfig_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.b , packet1.fc , packet1.flux , packet1.j , packet1.ld , packet1.lq , packet1.peak_current , packet1.pn , packet1.r , packet1.rated_current , packet1.speed_max_rpm , packet1.tp_s , packet1.tc_s , packet1.enc_line_p_n , packet1.kt );
    mavlink_msg_pmsmconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_pmsmconfig_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_pmsmconfig_send(MAVLINK_COMM_1 , packet1.b , packet1.fc , packet1.flux , packet1.j , packet1.ld , packet1.lq , packet1.peak_current , packet1.pn , packet1.r , packet1.rated_current , packet1.speed_max_rpm , packet1.tp_s , packet1.tc_s , packet1.enc_line_p_n , packet1.kt );
    mavlink_msg_pmsmconfig_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("PmsmConfig") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_PmsmConfig) != NULL);
#endif
}

static void mavlink_test_elecidsininput(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_ElecIdSinInput >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_elecidsininput_t packet_in = {
        { 17.0, 18.0, 19.0 }
    };
    mavlink_elecidsininput_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        
        mav_array_memcpy(packet1.i_abc_now_A, packet_in.i_abc_now_A, sizeof(float)*3);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_ElecIdSinInput_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_ElecIdSinInput_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_elecidsininput_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_elecidsininput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_elecidsininput_pack(system_id, component_id, &msg , packet1.i_abc_now_A );
    mavlink_msg_elecidsininput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_elecidsininput_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.i_abc_now_A );
    mavlink_msg_elecidsininput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_elecidsininput_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_elecidsininput_send(MAVLINK_COMM_1 , packet1.i_abc_now_A );
    mavlink_msg_elecidsininput_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("ElecIdSinInput") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_ElecIdSinInput) != NULL);
#endif
}

static void mavlink_test_elecidsinoutput(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_ElecIdSinOutput >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_elecidsinoutput_t packet_in = {
        { 17.0, 18.0, 19.0 },101.0,129.0,65
    };
    mavlink_elecidsinoutput_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.u_alpha_now_V = packet_in.u_alpha_now_V;
        packet1.i_alpha_now_A = packet_in.i_alpha_now_A;
        packet1.state_now = packet_in.state_now;
        
        mav_array_memcpy(packet1.u_abc_tar_V, packet_in.u_abc_tar_V, sizeof(float)*3);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_ElecIdSinOutput_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_ElecIdSinOutput_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_elecidsinoutput_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_elecidsinoutput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_elecidsinoutput_pack(system_id, component_id, &msg , packet1.state_now , packet1.u_abc_tar_V , packet1.u_alpha_now_V , packet1.i_alpha_now_A );
    mavlink_msg_elecidsinoutput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_elecidsinoutput_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.state_now , packet1.u_abc_tar_V , packet1.u_alpha_now_V , packet1.i_alpha_now_A );
    mavlink_msg_elecidsinoutput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_elecidsinoutput_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_elecidsinoutput_send(MAVLINK_COMM_1 , packet1.state_now , packet1.u_abc_tar_V , packet1.u_alpha_now_V , packet1.i_alpha_now_A );
    mavlink_msg_elecidsinoutput_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("ElecIdSinOutput") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_ElecIdSinOutput) != NULL);
#endif
}

static void mavlink_test_elecidsinconfig(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_ElecIdSinConfig >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_elecidsinconfig_t packet_in = {
        17.0,45.0,73.0,101.0,129.0,157.0,185.0
    };
    mavlink_elecidsinconfig_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.dt_s = packet_in.dt_s;
        packet1.end_fs_Hz = packet_in.end_fs_Hz;
        packet1.i_max_A = packet_in.i_max_A;
        packet1.init_fs_Hz = packet_in.init_fs_Hz;
        packet1.target_time_s = packet_in.target_time_s;
        packet1.u_max_V = packet_in.u_max_V;
        packet1.wait_time_s = packet_in.wait_time_s;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_ElecIdSinConfig_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_ElecIdSinConfig_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_elecidsinconfig_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_elecidsinconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_elecidsinconfig_pack(system_id, component_id, &msg , packet1.dt_s , packet1.end_fs_Hz , packet1.i_max_A , packet1.init_fs_Hz , packet1.target_time_s , packet1.u_max_V , packet1.wait_time_s );
    mavlink_msg_elecidsinconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_elecidsinconfig_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.dt_s , packet1.end_fs_Hz , packet1.i_max_A , packet1.init_fs_Hz , packet1.target_time_s , packet1.u_max_V , packet1.wait_time_s );
    mavlink_msg_elecidsinconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_elecidsinconfig_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_elecidsinconfig_send(MAVLINK_COMM_1 , packet1.dt_s , packet1.end_fs_Hz , packet1.i_max_A , packet1.init_fs_Hz , packet1.target_time_s , packet1.u_max_V , packet1.wait_time_s );
    mavlink_msg_elecidsinconfig_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("ElecIdSinConfig") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_ElecIdSinConfig) != NULL);
#endif
}

static void mavlink_test_mecidoutput(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_MecIdOutput >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_mecidoutput_t packet_in = {
        17.0,17
    };
    mavlink_mecidoutput_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.iq_tar_A = packet_in.iq_tar_A;
        packet1.state_now = packet_in.state_now;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_MecIdOutput_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_MecIdOutput_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_mecidoutput_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_mecidoutput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_mecidoutput_pack(system_id, component_id, &msg , packet1.iq_tar_A , packet1.state_now );
    mavlink_msg_mecidoutput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_mecidoutput_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.iq_tar_A , packet1.state_now );
    mavlink_msg_mecidoutput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_mecidoutput_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_mecidoutput_send(MAVLINK_COMM_1 , packet1.iq_tar_A , packet1.state_now );
    mavlink_msg_mecidoutput_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("MecIdOutput") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_MecIdOutput) != NULL);
#endif
}

static void mavlink_test_mecidconfig(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_MecIdConfig >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_mecidconfig_t packet_in = {
        17.0,45.0,73.0,101.0,129.0,157.0,185.0,89
    };
    mavlink_mecidconfig_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.dt_s = packet_in.dt_s;
        packet1.end_fs_Hz = packet_in.end_fs_Hz;
        packet1.start_fs_Hz = packet_in.start_fs_Hz;
        packet1.target_time_s = packet_in.target_time_s;
        packet1.i_max_A = packet_in.i_max_A;
        packet1.search_speed_max_rad_s = packet_in.search_speed_max_rad_s;
        packet1.wait_time_s = packet_in.wait_time_s;
        packet1.signal_type = packet_in.signal_type;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_MecIdConfig_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_MecIdConfig_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_mecidconfig_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_mecidconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_mecidconfig_pack(system_id, component_id, &msg , packet1.dt_s , packet1.end_fs_Hz , packet1.start_fs_Hz , packet1.target_time_s , packet1.i_max_A , packet1.search_speed_max_rad_s , packet1.wait_time_s , packet1.signal_type );
    mavlink_msg_mecidconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_mecidconfig_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.dt_s , packet1.end_fs_Hz , packet1.start_fs_Hz , packet1.target_time_s , packet1.i_max_A , packet1.search_speed_max_rad_s , packet1.wait_time_s , packet1.signal_type );
    mavlink_msg_mecidconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_mecidconfig_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_mecidconfig_send(MAVLINK_COMM_1 , packet1.dt_s , packet1.end_fs_Hz , packet1.start_fs_Hz , packet1.target_time_s , packet1.i_max_A , packet1.search_speed_max_rad_s , packet1.wait_time_s , packet1.signal_type );
    mavlink_msg_mecidconfig_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("MecIdConfig") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_MecIdConfig) != NULL);
#endif
}

static void mavlink_test_notchfilterinput(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_NotchFilterInput >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_notchfilterinput_t packet_in = {
        17.0
    };
    mavlink_notchfilterinput_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.iq_tar_A = packet_in.iq_tar_A;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_NotchFilterInput_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_NotchFilterInput_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_notchfilterinput_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_notchfilterinput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_notchfilterinput_pack(system_id, component_id, &msg , packet1.iq_tar_A );
    mavlink_msg_notchfilterinput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_notchfilterinput_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.iq_tar_A );
    mavlink_msg_notchfilterinput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_notchfilterinput_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_notchfilterinput_send(MAVLINK_COMM_1 , packet1.iq_tar_A );
    mavlink_msg_notchfilterinput_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("NotchFilterInput") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_NotchFilterInput) != NULL);
#endif
}

static void mavlink_test_notchfilterinternal(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_NotchFilterInternal >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_notchfilterinternal_t packet_in = {
        { 17.0, 18.0, 19.0, 20.0, 21.0, 22.0 },{ 185.0, 186.0, 187.0, 188.0, 189.0, 190.0 },{ 353.0, 354.0, 355.0, 356.0, 357.0, 358.0 },{ 521.0, 522.0, 523.0, 524.0, 525.0, 526.0 },{ 689.0, 690.0, 691.0, 692.0, 693.0, 694.0 }
    };
    mavlink_notchfilterinternal_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        
        mav_array_memcpy(packet1.u0, packet_in.u0, sizeof(float)*6);
        mav_array_memcpy(packet1.u1, packet_in.u1, sizeof(float)*6);
        mav_array_memcpy(packet1.u2, packet_in.u2, sizeof(float)*6);
        mav_array_memcpy(packet1.y0, packet_in.y0, sizeof(float)*6);
        mav_array_memcpy(packet1.y1, packet_in.y1, sizeof(float)*6);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_NotchFilterInternal_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_NotchFilterInternal_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_notchfilterinternal_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_notchfilterinternal_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_notchfilterinternal_pack(system_id, component_id, &msg , packet1.u0 , packet1.u1 , packet1.u2 , packet1.y0 , packet1.y1 );
    mavlink_msg_notchfilterinternal_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_notchfilterinternal_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.u0 , packet1.u1 , packet1.u2 , packet1.y0 , packet1.y1 );
    mavlink_msg_notchfilterinternal_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_notchfilterinternal_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_notchfilterinternal_send(MAVLINK_COMM_1 , packet1.u0 , packet1.u1 , packet1.u2 , packet1.y0 , packet1.y1 );
    mavlink_msg_notchfilterinternal_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("NotchFilterInternal") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_NotchFilterInternal) != NULL);
#endif
}

static void mavlink_test_notchfilteroutput(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_NotchFilterOutput >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_notchfilteroutput_t packet_in = {
        17.0
    };
    mavlink_notchfilteroutput_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.iq_tar_filter_A = packet_in.iq_tar_filter_A;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_NotchFilterOutput_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_NotchFilterOutput_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_notchfilteroutput_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_notchfilteroutput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_notchfilteroutput_pack(system_id, component_id, &msg , packet1.iq_tar_filter_A );
    mavlink_msg_notchfilteroutput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_notchfilteroutput_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.iq_tar_filter_A );
    mavlink_msg_notchfilteroutput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_notchfilteroutput_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_notchfilteroutput_send(MAVLINK_COMM_1 , packet1.iq_tar_filter_A );
    mavlink_msg_notchfilteroutput_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("NotchFilterOutput") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_NotchFilterOutput) != NULL);
#endif
}

static void mavlink_test_mecidinput(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_MecIdInput >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_mecidinput_t packet_in = {
        17.0
    };
    mavlink_mecidinput_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.speed_now_rad_s = packet_in.speed_now_rad_s;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_MecIdInput_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_MecIdInput_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_mecidinput_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_mecidinput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_mecidinput_pack(system_id, component_id, &msg , packet1.speed_now_rad_s );
    mavlink_msg_mecidinput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_mecidinput_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.speed_now_rad_s );
    mavlink_msg_mecidinput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_mecidinput_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_mecidinput_send(MAVLINK_COMM_1 , packet1.speed_now_rad_s );
    mavlink_msg_mecidinput_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("MecIdInput") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_MecIdInput) != NULL);
#endif
}

static void mavlink_test_inputshapinginput(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_InputShapingInput >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_inputshapinginput_t packet_in = {
        93372036854775807LL,93372036854776311LL
    };
    mavlink_inputshapinginput_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.pos_cmd_p = packet_in.pos_cmd_p;
        packet1.pos_cmd_p_init = packet_in.pos_cmd_p_init;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_InputShapingInput_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_InputShapingInput_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_inputshapinginput_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_inputshapinginput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_inputshapinginput_pack(system_id, component_id, &msg , packet1.pos_cmd_p , packet1.pos_cmd_p_init );
    mavlink_msg_inputshapinginput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_inputshapinginput_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.pos_cmd_p , packet1.pos_cmd_p_init );
    mavlink_msg_inputshapinginput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_inputshapinginput_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_inputshapinginput_send(MAVLINK_COMM_1 , packet1.pos_cmd_p , packet1.pos_cmd_p_init );
    mavlink_msg_inputshapinginput_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("InputShapingInput") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_InputShapingInput) != NULL);
#endif
}

static void mavlink_test_inputshapingconfig(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_InputShapingConfig >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_inputshapingconfig_t packet_in = {
        17.0,45.0,29
    };
    mavlink_inputshapingconfig_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.wn_Hz = packet_in.wn_Hz;
        packet1.run_frq_Hz = packet_in.run_frq_Hz;
        packet1.enable = packet_in.enable;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_InputShapingConfig_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_InputShapingConfig_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_inputshapingconfig_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_inputshapingconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_inputshapingconfig_pack(system_id, component_id, &msg , packet1.wn_Hz , packet1.run_frq_Hz , packet1.enable );
    mavlink_msg_inputshapingconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_inputshapingconfig_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.wn_Hz , packet1.run_frq_Hz , packet1.enable );
    mavlink_msg_inputshapingconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_inputshapingconfig_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_inputshapingconfig_send(MAVLINK_COMM_1 , packet1.wn_Hz , packet1.run_frq_Hz , packet1.enable );
    mavlink_msg_inputshapingconfig_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("InputShapingConfig") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_InputShapingConfig) != NULL);
#endif
}

static void mavlink_test_inputshapingoutput(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_InputShapingOutput >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_inputshapingoutput_t packet_in = {
        93372036854775807LL
    };
    mavlink_inputshapingoutput_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.pos_cmd_shaping_p = packet_in.pos_cmd_shaping_p;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_InputShapingOutput_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_InputShapingOutput_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_inputshapingoutput_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_inputshapingoutput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_inputshapingoutput_pack(system_id, component_id, &msg , packet1.pos_cmd_shaping_p );
    mavlink_msg_inputshapingoutput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_inputshapingoutput_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.pos_cmd_shaping_p );
    mavlink_msg_inputshapingoutput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_inputshapingoutput_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_inputshapingoutput_send(MAVLINK_COMM_1 , packet1.pos_cmd_shaping_p );
    mavlink_msg_inputshapingoutput_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("InputShapingOutput") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_InputShapingOutput) != NULL);
#endif
}

static void mavlink_test_scopeconfig(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_ScopeConfig >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_scopeconfig_t packet_in = {
        { 963497464, 963497465, 963497466, 963497467, 963497468, 963497469, 963497470, 963497471, 963497472, 963497473, 963497474, 963497475, 963497476, 963497477, 963497478, 963497479 },963500792,963501000,963501208,21187,111,178,245
    };
    mavlink_scopeconfig_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.sample_points = packet_in.sample_points;
        packet1.trigger_source = packet_in.trigger_source;
        packet1.trigger_threshold = packet_in.trigger_threshold;
        packet1.channel_switch = packet_in.channel_switch;
        packet1.sample_interval = packet_in.sample_interval;
        packet1.trigger_delay = packet_in.trigger_delay;
        packet1.trigger_mode = packet_in.trigger_mode;
        
        mav_array_memcpy(packet1.channel_map, packet_in.channel_map, sizeof(uint32_t)*16);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_ScopeConfig_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_ScopeConfig_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_scopeconfig_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_scopeconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_scopeconfig_pack(system_id, component_id, &msg , packet1.channel_map , packet1.channel_switch , packet1.sample_interval , packet1.sample_points , packet1.trigger_delay , packet1.trigger_mode , packet1.trigger_source , packet1.trigger_threshold );
    mavlink_msg_scopeconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_scopeconfig_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.channel_map , packet1.channel_switch , packet1.sample_interval , packet1.sample_points , packet1.trigger_delay , packet1.trigger_mode , packet1.trigger_source , packet1.trigger_threshold );
    mavlink_msg_scopeconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_scopeconfig_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_scopeconfig_send(MAVLINK_COMM_1 , packet1.channel_map , packet1.channel_switch , packet1.sample_interval , packet1.sample_points , packet1.trigger_delay , packet1.trigger_mode , packet1.trigger_source , packet1.trigger_threshold );
    mavlink_msg_scopeconfig_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("ScopeConfig") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_ScopeConfig) != NULL);
#endif
}

static void mavlink_test_scopecontrol(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_ScopeControl >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_scopecontrol_t packet_in = {
        963497464,17443,{ 17547, 17548, 17549, 17550, 17551, 17552, 17553, 17554, 17555, 17556, 17557, 17558, 17559, 17560, 17561, 17562 },19211
    };
    mavlink_scopecontrol_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.frame_info = packet_in.frame_info;
        packet1.control_word = packet_in.control_word;
        packet1.status_word = packet_in.status_word;
        
        mav_array_memcpy(packet1.frame_num, packet_in.frame_num, sizeof(uint16_t)*16);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_ScopeControl_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_ScopeControl_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_scopecontrol_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_scopecontrol_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_scopecontrol_pack(system_id, component_id, &msg , packet1.control_word , packet1.frame_info , packet1.frame_num , packet1.status_word );
    mavlink_msg_scopecontrol_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_scopecontrol_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.control_word , packet1.frame_info , packet1.frame_num , packet1.status_word );
    mavlink_msg_scopecontrol_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_scopecontrol_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_scopecontrol_send(MAVLINK_COMM_1 , packet1.control_word , packet1.frame_info , packet1.frame_num , packet1.status_word );
    mavlink_msg_scopecontrol_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("ScopeControl") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_ScopeControl) != NULL);
#endif
}

static void mavlink_test_scopedata(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_ScopeData >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_scopedata_t packet_in = {
        { 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132 }
    };
    mavlink_scopedata_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        
        mav_array_memcpy(packet1.frame_data, packet_in.frame_data, sizeof(uint8_t)*128);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_ScopeData_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_ScopeData_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_scopedata_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_scopedata_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_scopedata_pack(system_id, component_id, &msg , packet1.frame_data );
    mavlink_msg_scopedata_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_scopedata_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.frame_data );
    mavlink_msg_scopedata_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_scopedata_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_scopedata_send(MAVLINK_COMM_1 , packet1.frame_data );
    mavlink_msg_scopedata_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("ScopeData") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_ScopeData) != NULL);
#endif
}

static void mavlink_test_waveformdata(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_WaveformData >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_waveformdata_t packet_in = {
        { 93372036854775807, 93372036854775808, 93372036854775809, 93372036854775810, 93372036854775811, 93372036854775812 }
    };
    mavlink_waveformdata_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        
        mav_array_memcpy(packet1.waveform_data_array, packet_in.waveform_data_array, sizeof(int64_t)*6);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_WaveformData_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_WaveformData_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_waveformdata_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_waveformdata_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_waveformdata_pack(system_id, component_id, &msg , packet1.waveform_data_array );
    mavlink_msg_waveformdata_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_waveformdata_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.waveform_data_array );
    mavlink_msg_waveformdata_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_waveformdata_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_waveformdata_send(MAVLINK_COMM_1 , packet1.waveform_data_array );
    mavlink_msg_waveformdata_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("WaveformData") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_WaveformData) != NULL);
#endif
}

static void mavlink_test_waveformmap(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_WaveformMap >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_waveformmap_t packet_in = {
        { 963497464, 963497465, 963497466, 963497467, 963497468, 963497469 }
    };
    mavlink_waveformmap_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        
        mav_array_memcpy(packet1.waveform_map_info, packet_in.waveform_map_info, sizeof(int32_t)*6);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_WaveformMap_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_WaveformMap_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_waveformmap_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_waveformmap_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_waveformmap_pack(system_id, component_id, &msg , packet1.waveform_map_info );
    mavlink_msg_waveformmap_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_waveformmap_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.waveform_map_info );
    mavlink_msg_waveformmap_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_waveformmap_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_waveformmap_send(MAVLINK_COMM_1 , packet1.waveform_map_info );
    mavlink_msg_waveformmap_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("WaveformMap") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_WaveformMap) != NULL);
#endif
}

static void mavlink_test_posspeedctlinput(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_PosSpeedCtlInput >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_posspeedctlinput_t packet_in = {
        93372036854775807LL,93372036854776311LL,93372036854776815LL,185.0,213.0,241.0,269.0,297.0
    };
    mavlink_posspeedctlinput_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.pos_tar_p = packet_in.pos_tar_p;
        packet1.pos_now_p = packet_in.pos_now_p;
        packet1.position_offset_p = packet_in.position_offset_p;
        packet1.iq_max_A = packet_in.iq_max_A;
        packet1.speed_tar_p_s = packet_in.speed_tar_p_s;
        packet1.acc_tar_p_ss = packet_in.acc_tar_p_ss;
        packet1.speed_now_rad_s = packet_in.speed_now_rad_s;
        packet1.speed_offset_p_s = packet_in.speed_offset_p_s;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_PosSpeedCtlInput_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_PosSpeedCtlInput_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_posspeedctlinput_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_posspeedctlinput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_posspeedctlinput_pack(system_id, component_id, &msg , packet1.pos_tar_p , packet1.pos_now_p , packet1.iq_max_A , packet1.speed_tar_p_s , packet1.acc_tar_p_ss , packet1.speed_now_rad_s , packet1.position_offset_p , packet1.speed_offset_p_s );
    mavlink_msg_posspeedctlinput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_posspeedctlinput_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.pos_tar_p , packet1.pos_now_p , packet1.iq_max_A , packet1.speed_tar_p_s , packet1.acc_tar_p_ss , packet1.speed_now_rad_s , packet1.position_offset_p , packet1.speed_offset_p_s );
    mavlink_msg_posspeedctlinput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_posspeedctlinput_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_posspeedctlinput_send(MAVLINK_COMM_1 , packet1.pos_tar_p , packet1.pos_now_p , packet1.iq_max_A , packet1.speed_tar_p_s , packet1.acc_tar_p_ss , packet1.speed_now_rad_s , packet1.position_offset_p , packet1.speed_offset_p_s );
    mavlink_msg_posspeedctlinput_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("PosSpeedCtlInput") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_PosSpeedCtlInput) != NULL);
#endif
}

static void mavlink_test_posspeedctloutput(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_PosSpeedCtlOutput >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_posspeedctloutput_t packet_in = {
        17.0,963497672,73.0
    };
    mavlink_posspeedctloutput_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.iq_tar_A = packet_in.iq_tar_A;
        packet1.pos_ctl_error_p = packet_in.pos_ctl_error_p;
        packet1.dob_iq_com_A = packet_in.dob_iq_com_A;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_PosSpeedCtlOutput_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_PosSpeedCtlOutput_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_posspeedctloutput_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_posspeedctloutput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_posspeedctloutput_pack(system_id, component_id, &msg , packet1.iq_tar_A , packet1.pos_ctl_error_p , packet1.dob_iq_com_A );
    mavlink_msg_posspeedctloutput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_posspeedctloutput_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.iq_tar_A , packet1.pos_ctl_error_p , packet1.dob_iq_com_A );
    mavlink_msg_posspeedctloutput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_posspeedctloutput_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_posspeedctloutput_send(MAVLINK_COMM_1 , packet1.iq_tar_A , packet1.pos_ctl_error_p , packet1.dob_iq_com_A );
    mavlink_msg_posspeedctloutput_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("PosSpeedCtlOutput") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_PosSpeedCtlOutput) != NULL);
#endif
}

static void mavlink_test_posspeedctlconfig(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_PosSpeedCtlConfig >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_posspeedctlconfig_t packet_in = {
        17.0,45.0,73.0,101.0,129.0,157.0,185.0,213.0,241.0,269.0,297.0,137,204
    };
    mavlink_posspeedctlconfig_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.aff = packet_in.aff;
        packet1.vff = packet_in.vff;
        packet1.enc_line_inv_p_n = packet_in.enc_line_inv_p_n;
        packet1.j_kt = packet_in.j_kt;
        packet1.ki_s = packet_in.ki_s;
        packet1.kp_p = packet_in.kp_p;
        packet1.kp_s = packet_in.kp_s;
        packet1.speed_max_rad_s = packet_in.speed_max_rad_s;
        packet1.tp_s = packet_in.tp_s;
        packet1.mode = packet_in.mode;
        packet1.dob_wn_Hz = packet_in.dob_wn_Hz;
        packet1.dob_enable = packet_in.dob_enable;
        packet1.dynamic_integration_enable = packet_in.dynamic_integration_enable;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_PosSpeedCtlConfig_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_PosSpeedCtlConfig_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_posspeedctlconfig_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_posspeedctlconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_posspeedctlconfig_pack(system_id, component_id, &msg , packet1.aff , packet1.vff , packet1.enc_line_inv_p_n , packet1.j_kt , packet1.ki_s , packet1.kp_p , packet1.kp_s , packet1.speed_max_rad_s , packet1.tp_s , packet1.mode , packet1.dob_wn_Hz , packet1.dob_enable , packet1.dynamic_integration_enable );
    mavlink_msg_posspeedctlconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_posspeedctlconfig_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.aff , packet1.vff , packet1.enc_line_inv_p_n , packet1.j_kt , packet1.ki_s , packet1.kp_p , packet1.kp_s , packet1.speed_max_rad_s , packet1.tp_s , packet1.mode , packet1.dob_wn_Hz , packet1.dob_enable , packet1.dynamic_integration_enable );
    mavlink_msg_posspeedctlconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_posspeedctlconfig_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_posspeedctlconfig_send(MAVLINK_COMM_1 , packet1.aff , packet1.vff , packet1.enc_line_inv_p_n , packet1.j_kt , packet1.ki_s , packet1.kp_p , packet1.kp_s , packet1.speed_max_rad_s , packet1.tp_s , packet1.mode , packet1.dob_wn_Hz , packet1.dob_enable , packet1.dynamic_integration_enable );
    mavlink_msg_posspeedctlconfig_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("PosSpeedCtlConfig") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_PosSpeedCtlConfig) != NULL);
#endif
}

static void mavlink_test_motorctlsmconfig(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_MotorCtlSmConfig >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_motorctlsmconfig_t packet_in = {
        17.0,45.0,73.0,101.0,129.0,963498504,963498712,213.0,101
    };
    mavlink_motorctlsmconfig_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.under_voltage_protection_V = packet_in.under_voltage_protection_V;
        packet1.over_voltage_protection_V = packet_in.over_voltage_protection_V;
        packet1.over_speed_protection_rad_s = packet_in.over_speed_protection_rad_s;
        packet1.under_temperature_protection_d = packet_in.under_temperature_protection_d;
        packet1.over_temperature_protection_d = packet_in.over_temperature_protection_d;
        packet1.position_following_error_protection = packet_in.position_following_error_protection;
        packet1.error_enable = packet_in.error_enable;
        packet1.over_current_protection_A = packet_in.over_current_protection_A;
        packet1.mode = packet_in.mode;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_MotorCtlSmConfig_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_MotorCtlSmConfig_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_motorctlsmconfig_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_motorctlsmconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_motorctlsmconfig_pack(system_id, component_id, &msg , packet1.mode , packet1.under_voltage_protection_V , packet1.over_voltage_protection_V , packet1.over_speed_protection_rad_s , packet1.under_temperature_protection_d , packet1.over_temperature_protection_d , packet1.position_following_error_protection , packet1.error_enable , packet1.over_current_protection_A );
    mavlink_msg_motorctlsmconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_motorctlsmconfig_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.mode , packet1.under_voltage_protection_V , packet1.over_voltage_protection_V , packet1.over_speed_protection_rad_s , packet1.under_temperature_protection_d , packet1.over_temperature_protection_d , packet1.position_following_error_protection , packet1.error_enable , packet1.over_current_protection_A );
    mavlink_msg_motorctlsmconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_motorctlsmconfig_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_motorctlsmconfig_send(MAVLINK_COMM_1 , packet1.mode , packet1.under_voltage_protection_V , packet1.over_voltage_protection_V , packet1.over_speed_protection_rad_s , packet1.under_temperature_protection_d , packet1.over_temperature_protection_d , packet1.position_following_error_protection , packet1.error_enable , packet1.over_current_protection_A );
    mavlink_msg_motorctlsmconfig_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("MotorCtlSmConfig") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_MotorCtlSmConfig) != NULL);
#endif
}

static void mavlink_test_motorctlsminput(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_MotorCtlSmInput >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_motorctlsminput_t packet_in = {
        5,72
    };
    mavlink_motorctlsminput_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.motor_enable = packet_in.motor_enable;
        packet1.hw_ready_state = packet_in.hw_ready_state;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_MotorCtlSmInput_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_MotorCtlSmInput_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_motorctlsminput_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_motorctlsminput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_motorctlsminput_pack(system_id, component_id, &msg , packet1.motor_enable , packet1.hw_ready_state );
    mavlink_msg_motorctlsminput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_motorctlsminput_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.motor_enable , packet1.hw_ready_state );
    mavlink_msg_motorctlsminput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_motorctlsminput_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_motorctlsminput_send(MAVLINK_COMM_1 , packet1.motor_enable , packet1.hw_ready_state );
    mavlink_msg_motorctlsminput_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("MotorCtlSmInput") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_MotorCtlSmInput) != NULL);
#endif
}

static void mavlink_test_motorctlsmoutput(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_MotorCtlSmOutput >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_motorctlsmoutput_t packet_in = {
        963497464,963497672,29,96,163,230
    };
    mavlink_motorctlsmoutput_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.error = packet_in.error;
        packet1.warning = packet_in.warning;
        packet1.state = packet_in.state;
        packet1.mode_now = packet_in.mode_now;
        packet1.motor_enable_last = packet_in.motor_enable_last;
        packet1.state_last = packet_in.state_last;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_MotorCtlSmOutput_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_MotorCtlSmOutput_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_motorctlsmoutput_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_motorctlsmoutput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_motorctlsmoutput_pack(system_id, component_id, &msg , packet1.state , packet1.error , packet1.warning , packet1.mode_now , packet1.motor_enable_last , packet1.state_last );
    mavlink_msg_motorctlsmoutput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_motorctlsmoutput_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.state , packet1.error , packet1.warning , packet1.mode_now , packet1.motor_enable_last , packet1.state_last );
    mavlink_msg_motorctlsmoutput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_motorctlsmoutput_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_motorctlsmoutput_send(MAVLINK_COMM_1 , packet1.state , packet1.error , packet1.warning , packet1.mode_now , packet1.motor_enable_last , packet1.state_last );
    mavlink_msg_motorctlsmoutput_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("MotorCtlSmOutput") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_MotorCtlSmOutput) != NULL);
#endif
}

static void mavlink_test_currentctlinput(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_CurrentCtlInput >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_currentctlinput_t packet_in = {
        { 17.0, 18.0 },{ 73.0, 74.0, 75.0 },157.0,185.0,{ 213.0, 214.0, 215.0 },297.0,325.0,353.0,161
    };
    mavlink_currentctlinput_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.elec_theta_rad = packet_in.elec_theta_rad;
        packet1.dc_bus_now_V = packet_in.dc_bus_now_V;
        packet1.driver_temp = packet_in.driver_temp;
        packet1.elec_angle_speed_rad_s = packet_in.elec_angle_speed_rad_s;
        packet1.iq_offset_A = packet_in.iq_offset_A;
        packet1.mode = packet_in.mode;
        
        mav_array_memcpy(packet1.idq_tar_A, packet_in.idq_tar_A, sizeof(float)*2);
        mav_array_memcpy(packet1.iabc_now_A, packet_in.iabc_now_A, sizeof(float)*3);
        mav_array_memcpy(packet1.uabc_tar_V, packet_in.uabc_tar_V, sizeof(float)*3);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_CurrentCtlInput_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_CurrentCtlInput_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_currentctlinput_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_currentctlinput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_currentctlinput_pack(system_id, component_id, &msg , packet1.idq_tar_A , packet1.iabc_now_A , packet1.elec_theta_rad , packet1.dc_bus_now_V , packet1.mode , packet1.uabc_tar_V , packet1.driver_temp , packet1.elec_angle_speed_rad_s , packet1.iq_offset_A );
    mavlink_msg_currentctlinput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_currentctlinput_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.idq_tar_A , packet1.iabc_now_A , packet1.elec_theta_rad , packet1.dc_bus_now_V , packet1.mode , packet1.uabc_tar_V , packet1.driver_temp , packet1.elec_angle_speed_rad_s , packet1.iq_offset_A );
    mavlink_msg_currentctlinput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_currentctlinput_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_currentctlinput_send(MAVLINK_COMM_1 , packet1.idq_tar_A , packet1.iabc_now_A , packet1.elec_theta_rad , packet1.dc_bus_now_V , packet1.mode , packet1.uabc_tar_V , packet1.driver_temp , packet1.elec_angle_speed_rad_s , packet1.iq_offset_A );
    mavlink_msg_currentctlinput_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("CurrentCtlInput") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_CurrentCtlInput) != NULL);
#endif
}

static void mavlink_test_currentctlconfig(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_CurrentCtlConfig >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_currentctlconfig_t packet_in = {
        17.0,45.0,73.0,101.0,129.0,157.0,185.0,213.0,241.0,269.0,297.0,137
    };
    mavlink_currentctlconfig_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.i_noise_A = packet_in.i_noise_A;
        packet1.comp_du_V = packet_in.comp_du_V;
        packet1.bandwidth_percentage = packet_in.bandwidth_percentage;
        packet1.dt_s = packet_in.dt_s;
        packet1.flux_wb = packet_in.flux_wb;
        packet1.kp_ld = packet_in.kp_ld;
        packet1.ki_ld = packet_in.ki_ld;
        packet1.kp_lq = packet_in.kp_lq;
        packet1.ki_lq = packet_in.ki_lq;
        packet1.pwm_duty_cycle_max = packet_in.pwm_duty_cycle_max;
        packet1.elec_angle_compensation = packet_in.elec_angle_compensation;
        packet1.phase_dir = packet_in.phase_dir;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_CurrentCtlConfig_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_CurrentCtlConfig_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_currentctlconfig_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_currentctlconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_currentctlconfig_pack(system_id, component_id, &msg , packet1.i_noise_A , packet1.comp_du_V , packet1.bandwidth_percentage , packet1.dt_s , packet1.flux_wb , packet1.kp_ld , packet1.ki_ld , packet1.kp_lq , packet1.ki_lq , packet1.pwm_duty_cycle_max , packet1.elec_angle_compensation , packet1.phase_dir );
    mavlink_msg_currentctlconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_currentctlconfig_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.i_noise_A , packet1.comp_du_V , packet1.bandwidth_percentage , packet1.dt_s , packet1.flux_wb , packet1.kp_ld , packet1.ki_ld , packet1.kp_lq , packet1.ki_lq , packet1.pwm_duty_cycle_max , packet1.elec_angle_compensation , packet1.phase_dir );
    mavlink_msg_currentctlconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_currentctlconfig_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_currentctlconfig_send(MAVLINK_COMM_1 , packet1.i_noise_A , packet1.comp_du_V , packet1.bandwidth_percentage , packet1.dt_s , packet1.flux_wb , packet1.kp_ld , packet1.ki_ld , packet1.kp_lq , packet1.ki_lq , packet1.pwm_duty_cycle_max , packet1.elec_angle_compensation , packet1.phase_dir );
    mavlink_msg_currentctlconfig_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("CurrentCtlConfig") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_CurrentCtlConfig) != NULL);
#endif
}

static void mavlink_test_currentctloutput(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_CurrentCtlOutput >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_currentctloutput_t packet_in = {
        { 17.0, 18.0, 19.0 },{ 101.0, 102.0 },{ 157.0, 158.0, 159.0 }
    };
    mavlink_currentctloutput_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        
        mav_array_memcpy(packet1.uabc_tar_comp_V, packet_in.uabc_tar_comp_V, sizeof(float)*3);
        mav_array_memcpy(packet1.idq_now_A, packet_in.idq_now_A, sizeof(float)*2);
        mav_array_memcpy(packet1.uabc_tar_org_V, packet_in.uabc_tar_org_V, sizeof(float)*3);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_CurrentCtlOutput_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_CurrentCtlOutput_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_currentctloutput_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_currentctloutput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_currentctloutput_pack(system_id, component_id, &msg , packet1.uabc_tar_comp_V , packet1.idq_now_A , packet1.uabc_tar_org_V );
    mavlink_msg_currentctloutput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_currentctloutput_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.uabc_tar_comp_V , packet1.idq_now_A , packet1.uabc_tar_org_V );
    mavlink_msg_currentctloutput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_currentctloutput_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_currentctloutput_send(MAVLINK_COMM_1 , packet1.uabc_tar_comp_V , packet1.idq_now_A , packet1.uabc_tar_org_V );
    mavlink_msg_currentctloutput_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("CurrentCtlOutput") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_CurrentCtlOutput) != NULL);
#endif
}

static void mavlink_test_notchfilterconfig(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_NotchFilterConfig >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_notchfilterconfig_t packet_in = {
        { 17.0, 18.0, 19.0, 20.0, 21.0, 22.0 },{ 185.0, 186.0, 187.0, 188.0, 189.0, 190.0 },{ 353.0, 354.0, 355.0, 356.0, 357.0, 358.0 }
    };
    mavlink_notchfilterconfig_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        
        mav_array_memcpy(packet1.frq, packet_in.frq, sizeof(float)*6);
        mav_array_memcpy(packet1.width, packet_in.width, sizeof(float)*6);
        mav_array_memcpy(packet1.depth, packet_in.depth, sizeof(float)*6);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_NotchFilterConfig_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_NotchFilterConfig_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_notchfilterconfig_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_notchfilterconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_notchfilterconfig_pack(system_id, component_id, &msg , packet1.frq , packet1.width , packet1.depth );
    mavlink_msg_notchfilterconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_notchfilterconfig_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.frq , packet1.width , packet1.depth );
    mavlink_msg_notchfilterconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_notchfilterconfig_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_notchfilterconfig_send(MAVLINK_COMM_1 , packet1.frq , packet1.width , packet1.depth );
    mavlink_msg_notchfilterconfig_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("NotchFilterConfig") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_NotchFilterConfig) != NULL);
#endif
}

static void mavlink_test_speedobspllinput(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_SpeedObsPllInput >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_speedobspllinput_t packet_in = {
        93372036854775807LL
    };
    mavlink_speedobspllinput_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.pos_now_p = packet_in.pos_now_p;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_SpeedObsPllInput_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_SpeedObsPllInput_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_speedobspllinput_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_speedobspllinput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_speedobspllinput_pack(system_id, component_id, &msg , packet1.pos_now_p );
    mavlink_msg_speedobspllinput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_speedobspllinput_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.pos_now_p );
    mavlink_msg_speedobspllinput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_speedobspllinput_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_speedobspllinput_send(MAVLINK_COMM_1 , packet1.pos_now_p );
    mavlink_msg_speedobspllinput_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("SpeedObsPllInput") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_SpeedObsPllInput) != NULL);
#endif
}

static void mavlink_test_speedobspllconfig(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_SpeedObsPllConfig >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_speedobspllconfig_t packet_in = {
        17.0,45.0,73.0,101.0
    };
    mavlink_speedobspllconfig_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.tp_s = packet_in.tp_s;
        packet1.wn_Hz = packet_in.wn_Hz;
        packet1.enc_line_inv_p_n = packet_in.enc_line_inv_p_n;
        packet1.speed_obs_max_rad_s = packet_in.speed_obs_max_rad_s;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_SpeedObsPllConfig_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_SpeedObsPllConfig_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_speedobspllconfig_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_speedobspllconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_speedobspllconfig_pack(system_id, component_id, &msg , packet1.tp_s , packet1.wn_Hz , packet1.enc_line_inv_p_n , packet1.speed_obs_max_rad_s );
    mavlink_msg_speedobspllconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_speedobspllconfig_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.tp_s , packet1.wn_Hz , packet1.enc_line_inv_p_n , packet1.speed_obs_max_rad_s );
    mavlink_msg_speedobspllconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_speedobspllconfig_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_speedobspllconfig_send(MAVLINK_COMM_1 , packet1.tp_s , packet1.wn_Hz , packet1.enc_line_inv_p_n , packet1.speed_obs_max_rad_s );
    mavlink_msg_speedobspllconfig_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("SpeedObsPllConfig") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_SpeedObsPllConfig) != NULL);
#endif
}

static void mavlink_test_speedobsplloutput(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_SpeedObsPllOutput >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_speedobsplloutput_t packet_in = {
        17.0
    };
    mavlink_speedobsplloutput_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.ev_rad_s = packet_in.ev_rad_s;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_SpeedObsPllOutput_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_SpeedObsPllOutput_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_speedobsplloutput_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_speedobsplloutput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_speedobsplloutput_pack(system_id, component_id, &msg , packet1.ev_rad_s );
    mavlink_msg_speedobsplloutput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_speedobsplloutput_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.ev_rad_s );
    mavlink_msg_speedobsplloutput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_speedobsplloutput_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_speedobsplloutput_send(MAVLINK_COMM_1 , packet1.ev_rad_s );
    mavlink_msg_speedobsplloutput_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("SpeedObsPllOutput") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_SpeedObsPllOutput) != NULL);
#endif
}

static void mavlink_test_elecangleidconfig(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_ElecAngleIdConfig >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_elecangleidconfig_t packet_in = {
        17.0,45.0,73.0,101.0,129.0,157.0,77
    };
    mavlink_elecangleidconfig_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.id_max_A = packet_in.id_max_A;
        packet1.dt_s = packet_in.dt_s;
        packet1.angle_add_rad = packet_in.angle_add_rad;
        packet1.wait_time_s = packet_in.wait_time_s;
        packet1.test_angle_rad = packet_in.test_angle_rad;
        packet1.current_slope_percentage = packet_in.current_slope_percentage;
        packet1.method = packet_in.method;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_ElecAngleIdConfig_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_ElecAngleIdConfig_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_elecangleidconfig_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_elecangleidconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_elecangleidconfig_pack(system_id, component_id, &msg , packet1.id_max_A , packet1.dt_s , packet1.method , packet1.angle_add_rad , packet1.wait_time_s , packet1.test_angle_rad , packet1.current_slope_percentage );
    mavlink_msg_elecangleidconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_elecangleidconfig_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.id_max_A , packet1.dt_s , packet1.method , packet1.angle_add_rad , packet1.wait_time_s , packet1.test_angle_rad , packet1.current_slope_percentage );
    mavlink_msg_elecangleidconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_elecangleidconfig_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_elecangleidconfig_send(MAVLINK_COMM_1 , packet1.id_max_A , packet1.dt_s , packet1.method , packet1.angle_add_rad , packet1.wait_time_s , packet1.test_angle_rad , packet1.current_slope_percentage );
    mavlink_msg_elecangleidconfig_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("ElecAngleIdConfig") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_ElecAngleIdConfig) != NULL);
#endif
}

static void mavlink_test_elecangleidoutput(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_ElecAngleIdOutput >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_elecangleidoutput_t packet_in = {
        17.0,45.0,{ 73.0, 74.0 },53,120
    };
    mavlink_elecangleidoutput_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.id_tar_A = packet_in.id_tar_A;
        packet1.elec_bias_rad = packet_in.elec_bias_rad;
        packet1.state_now = packet_in.state_now;
        packet1.step_num = packet_in.step_num;
        
        mav_array_memcpy(packet1.elec_bias_buff_rad, packet_in.elec_bias_buff_rad, sizeof(float)*2);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_ElecAngleIdOutput_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_ElecAngleIdOutput_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_elecangleidoutput_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_elecangleidoutput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_elecangleidoutput_pack(system_id, component_id, &msg , packet1.id_tar_A , packet1.elec_bias_rad , packet1.state_now , packet1.elec_bias_buff_rad , packet1.step_num );
    mavlink_msg_elecangleidoutput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_elecangleidoutput_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.id_tar_A , packet1.elec_bias_rad , packet1.state_now , packet1.elec_bias_buff_rad , packet1.step_num );
    mavlink_msg_elecangleidoutput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_elecangleidoutput_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_elecangleidoutput_send(MAVLINK_COMM_1 , packet1.id_tar_A , packet1.elec_bias_rad , packet1.state_now , packet1.elec_bias_buff_rad , packet1.step_num );
    mavlink_msg_elecangleidoutput_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("ElecAngleIdOutput") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_ElecAngleIdOutput) != NULL);
#endif
}

static void mavlink_test_elecangleidinput(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_ElecAngleIdInput >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_elecangleidinput_t packet_in = {
        17.0
    };
    mavlink_elecangleidinput_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.pos_now_rad = packet_in.pos_now_rad;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_ElecAngleIdInput_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_ElecAngleIdInput_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_elecangleidinput_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_elecangleidinput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_elecangleidinput_pack(system_id, component_id, &msg , packet1.pos_now_rad );
    mavlink_msg_elecangleidinput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_elecangleidinput_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.pos_now_rad );
    mavlink_msg_elecangleidinput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_elecangleidinput_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_elecangleidinput_send(MAVLINK_COMM_1 , packet1.pos_now_rad );
    mavlink_msg_elecangleidinput_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("ElecAngleIdInput") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_ElecAngleIdInput) != NULL);
#endif
}

static void mavlink_test_directionidinput(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_DirectionIdInput >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_directionidinput_t packet_in = {
        93372036854775807LL
    };
    mavlink_directionidinput_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.enc_counts_sum_p = packet_in.enc_counts_sum_p;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_DirectionIdInput_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_DirectionIdInput_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_directionidinput_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_directionidinput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_directionidinput_pack(system_id, component_id, &msg , packet1.enc_counts_sum_p );
    mavlink_msg_directionidinput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_directionidinput_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.enc_counts_sum_p );
    mavlink_msg_directionidinput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_directionidinput_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_directionidinput_send(MAVLINK_COMM_1 , packet1.enc_counts_sum_p );
    mavlink_msg_directionidinput_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("DirectionIdInput") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_DirectionIdInput) != NULL);
#endif
}

static void mavlink_test_directionidconfig(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_DirectionIdConfig >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_directionidconfig_t packet_in = {
        17.0,45.0,73.0
    };
    mavlink_directionidconfig_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.elec_angle_add_rad = packet_in.elec_angle_add_rad;
        packet1.current_slope_percentage = packet_in.current_slope_percentage;
        packet1.id_tar_max_A = packet_in.id_tar_max_A;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_DirectionIdConfig_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_DirectionIdConfig_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_directionidconfig_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_directionidconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_directionidconfig_pack(system_id, component_id, &msg , packet1.elec_angle_add_rad , packet1.current_slope_percentage , packet1.id_tar_max_A );
    mavlink_msg_directionidconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_directionidconfig_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.elec_angle_add_rad , packet1.current_slope_percentage , packet1.id_tar_max_A );
    mavlink_msg_directionidconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_directionidconfig_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_directionidconfig_send(MAVLINK_COMM_1 , packet1.elec_angle_add_rad , packet1.current_slope_percentage , packet1.id_tar_max_A );
    mavlink_msg_directionidconfig_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("DirectionIdConfig") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_DirectionIdConfig) != NULL);
#endif
}

static void mavlink_test_directionidoutput(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_DirectionIdOutput >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_directionidoutput_t packet_in = {
        17.0,45.0,29,96
    };
    mavlink_directionidoutput_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.elec_angle_tar_rad = packet_in.elec_angle_tar_rad;
        packet1.id_tar_A = packet_in.id_tar_A;
        packet1.direction = packet_in.direction;
        packet1.state_now = packet_in.state_now;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_DirectionIdOutput_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_DirectionIdOutput_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_directionidoutput_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_directionidoutput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_directionidoutput_pack(system_id, component_id, &msg , packet1.elec_angle_tar_rad , packet1.direction , packet1.state_now , packet1.id_tar_A );
    mavlink_msg_directionidoutput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_directionidoutput_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.elec_angle_tar_rad , packet1.direction , packet1.state_now , packet1.id_tar_A );
    mavlink_msg_directionidoutput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_directionidoutput_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_directionidoutput_send(MAVLINK_COMM_1 , packet1.elec_angle_tar_rad , packet1.direction , packet1.state_now , packet1.id_tar_A );
    mavlink_msg_directionidoutput_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("DirectionIdOutput") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_DirectionIdOutput) != NULL);
#endif
}

static void mavlink_test_motorpossensorinput(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_MotorPosSensorInput >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_motorpossensorinput_t packet_in = {
        963497464
    };
    mavlink_motorpossensorinput_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.enc_counts_now_p = packet_in.enc_counts_now_p;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_MotorPosSensorInput_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_MotorPosSensorInput_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_motorpossensorinput_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_motorpossensorinput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_motorpossensorinput_pack(system_id, component_id, &msg , packet1.enc_counts_now_p );
    mavlink_msg_motorpossensorinput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_motorpossensorinput_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.enc_counts_now_p );
    mavlink_msg_motorpossensorinput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_motorpossensorinput_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_motorpossensorinput_send(MAVLINK_COMM_1 , packet1.enc_counts_now_p );
    mavlink_msg_motorpossensorinput_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("MotorPosSensorInput") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_MotorPosSensorInput) != NULL);
#endif
}

static void mavlink_test_motorpossensorconfig(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_MotorPosSensorConfig >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_motorpossensorconfig_t packet_in = {
        93372036854775807LL,963497880,963498088,129.0,65
    };
    mavlink_motorpossensorconfig_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.init_pos_p = packet_in.init_pos_p;
        packet1.enc_line_p_n = packet_in.enc_line_p_n;
        packet1.pn = packet_in.pn;
        packet1.elec_angle_bias_rad = packet_in.elec_angle_bias_rad;
        packet1.dir = packet_in.dir;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_MotorPosSensorConfig_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_MotorPosSensorConfig_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_motorpossensorconfig_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_motorpossensorconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_motorpossensorconfig_pack(system_id, component_id, &msg , packet1.enc_line_p_n , packet1.init_pos_p , packet1.pn , packet1.elec_angle_bias_rad , packet1.dir );
    mavlink_msg_motorpossensorconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_motorpossensorconfig_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.enc_line_p_n , packet1.init_pos_p , packet1.pn , packet1.elec_angle_bias_rad , packet1.dir );
    mavlink_msg_motorpossensorconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_motorpossensorconfig_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_motorpossensorconfig_send(MAVLINK_COMM_1 , packet1.enc_line_p_n , packet1.init_pos_p , packet1.pn , packet1.elec_angle_bias_rad , packet1.dir );
    mavlink_msg_motorpossensorconfig_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("MotorPosSensorConfig") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_MotorPosSensorConfig) != NULL);
#endif
}

static void mavlink_test_motorpossensoroutput(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_MotorPosSensorOutput >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_motorpossensoroutput_t packet_in = {
        93372036854775807LL,73.0
    };
    mavlink_motorpossensoroutput_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.enc_sum_p = packet_in.enc_sum_p;
        packet1.elec_angle_now_rad = packet_in.elec_angle_now_rad;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_MotorPosSensorOutput_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_MotorPosSensorOutput_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_motorpossensoroutput_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_motorpossensoroutput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_motorpossensoroutput_pack(system_id, component_id, &msg , packet1.enc_sum_p , packet1.elec_angle_now_rad );
    mavlink_msg_motorpossensoroutput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_motorpossensoroutput_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.enc_sum_p , packet1.elec_angle_now_rad );
    mavlink_msg_motorpossensoroutput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_motorpossensoroutput_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_motorpossensoroutput_send(MAVLINK_COMM_1 , packet1.enc_sum_p , packet1.elec_angle_now_rad );
    mavlink_msg_motorpossensoroutput_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("MotorPosSensorOutput") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_MotorPosSensorOutput) != NULL);
#endif
}

static void mavlink_test_polepairsidinput(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_PolePairsIdInput >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_polepairsidinput_t packet_in = {
        93372036854775807LL
    };
    mavlink_polepairsidinput_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.enc_counts_sum_p = packet_in.enc_counts_sum_p;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_PolePairsIdInput_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_PolePairsIdInput_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_polepairsidinput_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_polepairsidinput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_polepairsidinput_pack(system_id, component_id, &msg , packet1.enc_counts_sum_p );
    mavlink_msg_polepairsidinput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_polepairsidinput_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.enc_counts_sum_p );
    mavlink_msg_polepairsidinput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_polepairsidinput_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_polepairsidinput_send(MAVLINK_COMM_1 , packet1.enc_counts_sum_p );
    mavlink_msg_polepairsidinput_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("PolePairsIdInput") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_PolePairsIdInput) != NULL);
#endif
}

static void mavlink_test_polepairsidconfig(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_PolePairsIdConfig >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_polepairsidconfig_t packet_in = {
        17.0,963497672,73.0,101.0
    };
    mavlink_polepairsidconfig_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.elec_angle_add = packet_in.elec_angle_add;
        packet1.enc_line_p_n = packet_in.enc_line_p_n;
        packet1.id_tar_max_A = packet_in.id_tar_max_A;
        packet1.current_slope_percentage = packet_in.current_slope_percentage;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_PolePairsIdConfig_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_PolePairsIdConfig_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_polepairsidconfig_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_polepairsidconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_polepairsidconfig_pack(system_id, component_id, &msg , packet1.elec_angle_add , packet1.enc_line_p_n , packet1.id_tar_max_A , packet1.current_slope_percentage );
    mavlink_msg_polepairsidconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_polepairsidconfig_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.elec_angle_add , packet1.enc_line_p_n , packet1.id_tar_max_A , packet1.current_slope_percentage );
    mavlink_msg_polepairsidconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_polepairsidconfig_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_polepairsidconfig_send(MAVLINK_COMM_1 , packet1.elec_angle_add , packet1.enc_line_p_n , packet1.id_tar_max_A , packet1.current_slope_percentage );
    mavlink_msg_polepairsidconfig_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("PolePairsIdConfig") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_PolePairsIdConfig) != NULL);
#endif
}

static void mavlink_test_polepairsidoutput(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_PolePairsIdOutput >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_polepairsidoutput_t packet_in = {
        963497464,45.0,73.0,41
    };
    mavlink_polepairsidoutput_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.pn_id = packet_in.pn_id;
        packet1.elec_angle_tar_rad = packet_in.elec_angle_tar_rad;
        packet1.id_tar_A = packet_in.id_tar_A;
        packet1.state_now = packet_in.state_now;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_PolePairsIdOutput_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_PolePairsIdOutput_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_polepairsidoutput_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_polepairsidoutput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_polepairsidoutput_pack(system_id, component_id, &msg , packet1.pn_id , packet1.state_now , packet1.elec_angle_tar_rad , packet1.id_tar_A );
    mavlink_msg_polepairsidoutput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_polepairsidoutput_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.pn_id , packet1.state_now , packet1.elec_angle_tar_rad , packet1.id_tar_A );
    mavlink_msg_polepairsidoutput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_polepairsidoutput_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_polepairsidoutput_send(MAVLINK_COMM_1 , packet1.pn_id , packet1.state_now , packet1.elec_angle_tar_rad , packet1.id_tar_A );
    mavlink_msg_polepairsidoutput_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("PolePairsIdOutput") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_PolePairsIdOutput) != NULL);
#endif
}

static void mavlink_test_nonvolatileparam(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_NonVolatileParam >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_nonvolatileparam_t packet_in = {
        963497464,45.0
    };
    mavlink_nonvolatileparam_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.encoder_res = packet_in.encoder_res;
        packet1.rated_current = packet_in.rated_current;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_NonVolatileParam_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_NonVolatileParam_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_nonvolatileparam_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_nonvolatileparam_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_nonvolatileparam_pack(system_id, component_id, &msg , packet1.encoder_res , packet1.rated_current );
    mavlink_msg_nonvolatileparam_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_nonvolatileparam_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.encoder_res , packet1.rated_current );
    mavlink_msg_nonvolatileparam_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_nonvolatileparam_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_nonvolatileparam_send(MAVLINK_COMM_1 , packet1.encoder_res , packet1.rated_current );
    mavlink_msg_nonvolatileparam_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("NonVolatileParam") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_NonVolatileParam) != NULL);
#endif
}

static void mavlink_test_systemconfig(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_SystemConfig >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_systemconfig_t packet_in = {
        963497464,963497672,29,96
    };
    mavlink_systemconfig_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.current_loop_freq = packet_in.current_loop_freq;
        packet1.position_loop_freq = packet_in.position_loop_freq;
        packet1.param_save = packet_in.param_save;
        packet1.system_reset = packet_in.system_reset;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_SystemConfig_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_SystemConfig_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_systemconfig_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_systemconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_systemconfig_pack(system_id, component_id, &msg , packet1.param_save , packet1.system_reset , packet1.current_loop_freq , packet1.position_loop_freq );
    mavlink_msg_systemconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_systemconfig_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.param_save , packet1.system_reset , packet1.current_loop_freq , packet1.position_loop_freq );
    mavlink_msg_systemconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_systemconfig_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_systemconfig_send(MAVLINK_COMM_1 , packet1.param_save , packet1.system_reset , packet1.current_loop_freq , packet1.position_loop_freq );
    mavlink_msg_systemconfig_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("SystemConfig") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_SystemConfig) != NULL);
#endif
}

static void mavlink_test_tqfcidinput(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_TqFcIdInput >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_tqfcidinput_t packet_in = {
        93372036854775807LL,73.0,963498088,53
    };
    mavlink_tqfcidinput_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.pos_init_p = packet_in.pos_init_p;
        packet1.iq_com_A = packet_in.iq_com_A;
        packet1.pos_abs_p = packet_in.pos_abs_p;
        packet1.start = packet_in.start;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_TqFcIdInput_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_TqFcIdInput_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_tqfcidinput_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_tqfcidinput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_tqfcidinput_pack(system_id, component_id, &msg , packet1.iq_com_A , packet1.pos_abs_p , packet1.pos_init_p , packet1.start );
    mavlink_msg_tqfcidinput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_tqfcidinput_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.iq_com_A , packet1.pos_abs_p , packet1.pos_init_p , packet1.start );
    mavlink_msg_tqfcidinput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_tqfcidinput_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_tqfcidinput_send(MAVLINK_COMM_1 , packet1.iq_com_A , packet1.pos_abs_p , packet1.pos_init_p , packet1.start );
    mavlink_msg_tqfcidinput_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("TqFcIdInput") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_TqFcIdInput) != NULL);
#endif
}

static void mavlink_test_tqfcidconfig(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_TqFcIdConfig >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_tqfcidconfig_t packet_in = {
        963497464,45.0,73.0,41,108,175
    };
    mavlink_tqfcidconfig_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.enc_line_p_n = packet_in.enc_line_p_n;
        packet1.fc_p_com = packet_in.fc_p_com;
        packet1.fc_n_com = packet_in.fc_n_com;
        packet1.iq_com_enable = packet_in.iq_com_enable;
        packet1.tq_com_enable = packet_in.tq_com_enable;
        packet1.fc_com_enable = packet_in.fc_com_enable;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_TqFcIdConfig_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_TqFcIdConfig_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_tqfcidconfig_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_tqfcidconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_tqfcidconfig_pack(system_id, component_id, &msg , packet1.enc_line_p_n , packet1.iq_com_enable , packet1.tq_com_enable , packet1.fc_com_enable , packet1.fc_p_com , packet1.fc_n_com );
    mavlink_msg_tqfcidconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_tqfcidconfig_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.enc_line_p_n , packet1.iq_com_enable , packet1.tq_com_enable , packet1.fc_com_enable , packet1.fc_p_com , packet1.fc_n_com );
    mavlink_msg_tqfcidconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_tqfcidconfig_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_tqfcidconfig_send(MAVLINK_COMM_1 , packet1.enc_line_p_n , packet1.iq_com_enable , packet1.tq_com_enable , packet1.fc_com_enable , packet1.fc_p_com , packet1.fc_n_com );
    mavlink_msg_tqfcidconfig_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("TqFcIdConfig") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_TqFcIdConfig) != NULL);
#endif
}

static void mavlink_test_tqfcidoutput(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_TqFcIdOutput >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_tqfcidoutput_t packet_in = {
        93372036854775807LL,29
    };
    mavlink_tqfcidoutput_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.pos_cmd_p = packet_in.pos_cmd_p;
        packet1.state_now = packet_in.state_now;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_TqFcIdOutput_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_TqFcIdOutput_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_tqfcidoutput_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_tqfcidoutput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_tqfcidoutput_pack(system_id, component_id, &msg , packet1.pos_cmd_p , packet1.state_now );
    mavlink_msg_tqfcidoutput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_tqfcidoutput_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.pos_cmd_p , packet1.state_now );
    mavlink_msg_tqfcidoutput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_tqfcidoutput_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_tqfcidoutput_send(MAVLINK_COMM_1 , packet1.pos_cmd_p , packet1.state_now );
    mavlink_msg_tqfcidoutput_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("TqFcIdOutput") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_TqFcIdOutput) != NULL);
#endif
}

static void mavlink_test_objectdictionary(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_ObjectDictionary >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_objectdictionary_t packet_in = {
        963497464,17443,151,218
    };
    mavlink_objectdictionary_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.data = packet_in.data;
        packet1.index = packet_in.index;
        packet1.sub_index = packet_in.sub_index;
        packet1.rw = packet_in.rw;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_ObjectDictionary_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_ObjectDictionary_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_objectdictionary_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_objectdictionary_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_objectdictionary_pack(system_id, component_id, &msg , packet1.index , packet1.sub_index , packet1.data , packet1.rw );
    mavlink_msg_objectdictionary_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_objectdictionary_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.index , packet1.sub_index , packet1.data , packet1.rw );
    mavlink_msg_objectdictionary_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_objectdictionary_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_objectdictionary_send(MAVLINK_COMM_1 , packet1.index , packet1.sub_index , packet1.data , packet1.rw );
    mavlink_msg_objectdictionary_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("ObjectDictionary") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_ObjectDictionary) != NULL);
#endif
}

static void mavlink_test_reciprocalmotionconfig(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_ReciprocalMotionConfig >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_reciprocalmotionconfig_t packet_in = {
        93372036854775807LL,93372036854776311LL,129.0,157.0,185.0,213.0,241.0
    };
    mavlink_reciprocalmotionconfig_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.pos_tar1_p = packet_in.pos_tar1_p;
        packet1.pos_tar2_p = packet_in.pos_tar2_p;
        packet1.dwell_time_s = packet_in.dwell_time_s;
        packet1.profile_velocity_p_s = packet_in.profile_velocity_p_s;
        packet1.profile_acc_p_ss = packet_in.profile_acc_p_ss;
        packet1.profile_dec_p_ss = packet_in.profile_dec_p_ss;
        packet1.dt_s = packet_in.dt_s;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_ReciprocalMotionConfig_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_ReciprocalMotionConfig_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_reciprocalmotionconfig_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_reciprocalmotionconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_reciprocalmotionconfig_pack(system_id, component_id, &msg , packet1.pos_tar1_p , packet1.pos_tar2_p , packet1.dwell_time_s , packet1.profile_velocity_p_s , packet1.profile_acc_p_ss , packet1.profile_dec_p_ss , packet1.dt_s );
    mavlink_msg_reciprocalmotionconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_reciprocalmotionconfig_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.pos_tar1_p , packet1.pos_tar2_p , packet1.dwell_time_s , packet1.profile_velocity_p_s , packet1.profile_acc_p_ss , packet1.profile_dec_p_ss , packet1.dt_s );
    mavlink_msg_reciprocalmotionconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_reciprocalmotionconfig_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_reciprocalmotionconfig_send(MAVLINK_COMM_1 , packet1.pos_tar1_p , packet1.pos_tar2_p , packet1.dwell_time_s , packet1.profile_velocity_p_s , packet1.profile_acc_p_ss , packet1.profile_dec_p_ss , packet1.dt_s );
    mavlink_msg_reciprocalmotionconfig_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("ReciprocalMotionConfig") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_ReciprocalMotionConfig) != NULL);
#endif
}

static void mavlink_test_reciprocalmotionoutput(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_ReciprocalMotionOutput >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_reciprocalmotionoutput_t packet_in = {
        93372036854775807LL,73.0,101.0,53
    };
    mavlink_reciprocalmotionoutput_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.pos_tar_p = packet_in.pos_tar_p;
        packet1.v_tar_p_s = packet_in.v_tar_p_s;
        packet1.acc_tar_p_ss = packet_in.acc_tar_p_ss;
        packet1.state_now = packet_in.state_now;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_ReciprocalMotionOutput_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_ReciprocalMotionOutput_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_reciprocalmotionoutput_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_reciprocalmotionoutput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_reciprocalmotionoutput_pack(system_id, component_id, &msg , packet1.pos_tar_p , packet1.v_tar_p_s , packet1.acc_tar_p_ss , packet1.state_now );
    mavlink_msg_reciprocalmotionoutput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_reciprocalmotionoutput_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.pos_tar_p , packet1.v_tar_p_s , packet1.acc_tar_p_ss , packet1.state_now );
    mavlink_msg_reciprocalmotionoutput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_reciprocalmotionoutput_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_reciprocalmotionoutput_send(MAVLINK_COMM_1 , packet1.pos_tar_p , packet1.v_tar_p_s , packet1.acc_tar_p_ss , packet1.state_now );
    mavlink_msg_reciprocalmotionoutput_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("ReciprocalMotionOutput") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_ReciprocalMotionOutput) != NULL);
#endif
}

static void mavlink_test_referencesignalconfig(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_ReferenceSignalConfig >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_referencesignalconfig_t packet_in = {
        93372036854775807LL,73.0,101.0,129.0,157.0,77,144
    };
    mavlink_referencesignalconfig_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.signal_start_pos = packet_in.signal_start_pos;
        packet1.dt_s = packet_in.dt_s;
        packet1.amp = packet_in.amp;
        packet1.frq_Hz = packet_in.frq_Hz;
        packet1.bias = packet_in.bias;
        packet1.signal_type = packet_in.signal_type;
        packet1.signal_target = packet_in.signal_target;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_ReferenceSignalConfig_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_ReferenceSignalConfig_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_referencesignalconfig_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_referencesignalconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_referencesignalconfig_pack(system_id, component_id, &msg , packet1.dt_s , packet1.signal_type , packet1.amp , packet1.frq_Hz , packet1.bias , packet1.signal_target , packet1.signal_start_pos );
    mavlink_msg_referencesignalconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_referencesignalconfig_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.dt_s , packet1.signal_type , packet1.amp , packet1.frq_Hz , packet1.bias , packet1.signal_target , packet1.signal_start_pos );
    mavlink_msg_referencesignalconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_referencesignalconfig_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_referencesignalconfig_send(MAVLINK_COMM_1 , packet1.dt_s , packet1.signal_type , packet1.amp , packet1.frq_Hz , packet1.bias , packet1.signal_target , packet1.signal_start_pos );
    mavlink_msg_referencesignalconfig_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("ReferenceSignalConfig") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_ReferenceSignalConfig) != NULL);
#endif
}

static void mavlink_test_referencesignaloutput(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_ReferenceSignalOutput >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_referencesignaloutput_t packet_in = {
        93372036854775807LL,73.0,101.0,129.0
    };
    mavlink_referencesignaloutput_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.signal_pos = packet_in.signal_pos;
        packet1.signal_out = packet_in.signal_out;
        packet1.signal_vel = packet_in.signal_vel;
        packet1.signal_acc = packet_in.signal_acc;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_ReferenceSignalOutput_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_ReferenceSignalOutput_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_referencesignaloutput_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_referencesignaloutput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_referencesignaloutput_pack(system_id, component_id, &msg , packet1.signal_out , packet1.signal_pos , packet1.signal_vel , packet1.signal_acc );
    mavlink_msg_referencesignaloutput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_referencesignaloutput_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.signal_out , packet1.signal_pos , packet1.signal_vel , packet1.signal_acc );
    mavlink_msg_referencesignaloutput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_referencesignaloutput_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_referencesignaloutput_send(MAVLINK_COMM_1 , packet1.signal_out , packet1.signal_pos , packet1.signal_vel , packet1.signal_acc );
    mavlink_msg_referencesignaloutput_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("ReferenceSignalOutput") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_ReferenceSignalOutput) != NULL);
#endif
}

static void mavlink_test_appcontrolword(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_AppControlWord >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_appcontrolword_t packet_in = {
        17235,139
    };
    mavlink_appcontrolword_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.Controlword = packet_in.Controlword;
        packet1.Halt_running_cmd = packet_in.Halt_running_cmd;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_AppControlWord_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_AppControlWord_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_appcontrolword_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_appcontrolword_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_appcontrolword_pack(system_id, component_id, &msg , packet1.Controlword , packet1.Halt_running_cmd );
    mavlink_msg_appcontrolword_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_appcontrolword_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.Controlword , packet1.Halt_running_cmd );
    mavlink_msg_appcontrolword_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_appcontrolword_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_appcontrolword_send(MAVLINK_COMM_1 , packet1.Controlword , packet1.Halt_running_cmd );
    mavlink_msg_appcontrolword_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("AppControlWord") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_AppControlWord) != NULL);
#endif
}

static void mavlink_test_appstatusinfo(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_AppStatusInfo >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_appstatusinfo_t packet_in = {
        963497464,963497672,73.0,101.0,129.0,963498504,963498712,213.0,241.0,269.0,963499544,137,204
    };
    mavlink_appstatusinfo_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.Statusword = packet_in.Statusword;
        packet1.Error_word = packet_in.Error_word;
        packet1.DC_link_circuit_voltage = packet_in.DC_link_circuit_voltage;
        packet1.Drive_accumulated_heat = packet_in.Drive_accumulated_heat;
        packet1.Drive_temperature = packet_in.Drive_temperature;
        packet1.Alarm_word = packet_in.Alarm_word;
        packet1.Version = packet_in.Version;
        packet1.Motor_temperature = packet_in.Motor_temperature;
        packet1.Motor_power = packet_in.Motor_power;
        packet1.Mcu_temperature = packet_in.Mcu_temperature;
        packet1.Digital_io_inputs_status = packet_in.Digital_io_inputs_status;
        packet1.Modes_of_operation_display = packet_in.Modes_of_operation_display;
        packet1.Brake_state = packet_in.Brake_state;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_AppStatusInfo_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_AppStatusInfo_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_appstatusinfo_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_appstatusinfo_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_appstatusinfo_pack(system_id, component_id, &msg , packet1.Statusword , packet1.Error_word , packet1.DC_link_circuit_voltage , packet1.Drive_accumulated_heat , packet1.Drive_temperature , packet1.Alarm_word , packet1.Modes_of_operation_display , packet1.Version , packet1.Motor_temperature , packet1.Motor_power , packet1.Mcu_temperature , packet1.Digital_io_inputs_status , packet1.Brake_state );
    mavlink_msg_appstatusinfo_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_appstatusinfo_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.Statusword , packet1.Error_word , packet1.DC_link_circuit_voltage , packet1.Drive_accumulated_heat , packet1.Drive_temperature , packet1.Alarm_word , packet1.Modes_of_operation_display , packet1.Version , packet1.Motor_temperature , packet1.Motor_power , packet1.Mcu_temperature , packet1.Digital_io_inputs_status , packet1.Brake_state );
    mavlink_msg_appstatusinfo_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_appstatusinfo_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_appstatusinfo_send(MAVLINK_COMM_1 , packet1.Statusword , packet1.Error_word , packet1.DC_link_circuit_voltage , packet1.Drive_accumulated_heat , packet1.Drive_temperature , packet1.Alarm_word , packet1.Modes_of_operation_display , packet1.Version , packet1.Motor_temperature , packet1.Motor_power , packet1.Mcu_temperature , packet1.Digital_io_inputs_status , packet1.Brake_state );
    mavlink_msg_appstatusinfo_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("AppStatusInfo") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_AppStatusInfo) != NULL);
#endif
}

static void mavlink_test_appopmode(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_AppOpMode >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_appopmode_t packet_in = {
        5
    };
    mavlink_appopmode_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.Modes_of_operation = packet_in.Modes_of_operation;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_AppOpMode_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_AppOpMode_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_appopmode_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_appopmode_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_appopmode_pack(system_id, component_id, &msg , packet1.Modes_of_operation );
    mavlink_msg_appopmode_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_appopmode_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.Modes_of_operation );
    mavlink_msg_appopmode_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_appopmode_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_appopmode_send(MAVLINK_COMM_1 , packet1.Modes_of_operation );
    mavlink_msg_appopmode_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("AppOpMode") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_AppOpMode) != NULL);
#endif
}

static void mavlink_test_appencoderconfig(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_AppEncoderConfig >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_appencoderconfig_t packet_in = {
        963497464,963497672,73.0,101.0,129.0,157.0,185.0,213.0,963499128,963499336,125,192,3,70
    };
    mavlink_appencoderconfig_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.Load_encoder_resolution = packet_in.Load_encoder_resolution;
        packet1.Motor_encoder_resolution = packet_in.Motor_encoder_resolution;
        packet1.Load_pps_2_rpm = packet_in.Load_pps_2_rpm;
        packet1.Load_rpm_2_pps = packet_in.Load_rpm_2_pps;
        packet1.Motor_pps_2_rpm = packet_in.Motor_pps_2_rpm;
        packet1.Motor_rpm_2_pps = packet_in.Motor_rpm_2_pps;
        packet1.P_load_2_motor = packet_in.P_load_2_motor;
        packet1.P_motor_2_load = packet_in.P_motor_2_load;
        packet1.Load_control_resolution = packet_in.Load_control_resolution;
        packet1.Motor_control_resolution = packet_in.Motor_control_resolution;
        packet1.Motor_encoder_type = packet_in.Motor_encoder_type;
        packet1.Load_encoder_type = packet_in.Load_encoder_type;
        packet1.Motor_encoder_options = packet_in.Motor_encoder_options;
        packet1.Load_encoder_options = packet_in.Load_encoder_options;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_AppEncoderConfig_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_AppEncoderConfig_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_appencoderconfig_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_appencoderconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_appencoderconfig_pack(system_id, component_id, &msg , packet1.Load_encoder_resolution , packet1.Motor_encoder_resolution , packet1.Motor_encoder_type , packet1.Load_encoder_type , packet1.Motor_encoder_options , packet1.Load_pps_2_rpm , packet1.Load_rpm_2_pps , packet1.Motor_pps_2_rpm , packet1.Motor_rpm_2_pps , packet1.P_load_2_motor , packet1.P_motor_2_load , packet1.Load_control_resolution , packet1.Motor_control_resolution , packet1.Load_encoder_options );
    mavlink_msg_appencoderconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_appencoderconfig_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.Load_encoder_resolution , packet1.Motor_encoder_resolution , packet1.Motor_encoder_type , packet1.Load_encoder_type , packet1.Motor_encoder_options , packet1.Load_pps_2_rpm , packet1.Load_rpm_2_pps , packet1.Motor_pps_2_rpm , packet1.Motor_rpm_2_pps , packet1.P_load_2_motor , packet1.P_motor_2_load , packet1.Load_control_resolution , packet1.Motor_control_resolution , packet1.Load_encoder_options );
    mavlink_msg_appencoderconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_appencoderconfig_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_appencoderconfig_send(MAVLINK_COMM_1 , packet1.Load_encoder_resolution , packet1.Motor_encoder_resolution , packet1.Motor_encoder_type , packet1.Load_encoder_type , packet1.Motor_encoder_options , packet1.Load_pps_2_rpm , packet1.Load_rpm_2_pps , packet1.Motor_pps_2_rpm , packet1.Motor_rpm_2_pps , packet1.P_load_2_motor , packet1.P_motor_2_load , packet1.Load_control_resolution , packet1.Motor_control_resolution , packet1.Load_encoder_options );
    mavlink_msg_appencoderconfig_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("AppEncoderConfig") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_AppEncoderConfig) != NULL);
#endif
}

static void mavlink_test_appbaseconfig(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_AppBaseConfig >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_appbaseconfig_t packet_in = {
        93372036854775807LL,963497880,963498088,129.0,157.0,185.0,213.0,963499128,963499336,297.0,325.0,353.0,381.0,20147,20251,185,252
    };
    mavlink_appbaseconfig_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.Home_position_offset_value = packet_in.Home_position_offset_value;
        packet1.Can_id = packet_in.Can_id;
        packet1.Can_baudrate = packet_in.Can_baudrate;
        packet1.Brake_engage_time = packet_in.Brake_engage_time;
        packet1.Brake_release_time = packet_in.Brake_release_time;
        packet1.Dynamic_brake_speed_threshold = packet_in.Dynamic_brake_speed_threshold;
        packet1.Brake_release_hold_voltage = packet_in.Brake_release_hold_voltage;
        packet1.Digital_io_outputs_phys = packet_in.Digital_io_outputs_phys;
        packet1.Digital_io_outputs_mask = packet_in.Digital_io_outputs_mask;
        packet1.Brake_rated_voltage = packet_in.Brake_rated_voltage;
        packet1.Brake_release_action_voltage = packet_in.Brake_release_action_voltage;
        packet1.Brake_engage_delay_time = packet_in.Brake_engage_delay_time;
        packet1.Brake_release_delay_time = packet_in.Brake_release_delay_time;
        packet1.Quick_stop_option_code = packet_in.Quick_stop_option_code;
        packet1.Brake_release_pwm_freq = packet_in.Brake_release_pwm_freq;
        packet1.Polarity = packet_in.Polarity;
        packet1.Brake_control_mode = packet_in.Brake_control_mode;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_AppBaseConfig_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_AppBaseConfig_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_appbaseconfig_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_appbaseconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_appbaseconfig_pack(system_id, component_id, &msg , packet1.Polarity , packet1.Home_position_offset_value , packet1.Can_id , packet1.Can_baudrate , packet1.Quick_stop_option_code , packet1.Brake_engage_time , packet1.Brake_release_time , packet1.Dynamic_brake_speed_threshold , packet1.Brake_release_hold_voltage , packet1.Digital_io_outputs_phys , packet1.Digital_io_outputs_mask , packet1.Brake_control_mode , packet1.Brake_rated_voltage , packet1.Brake_release_action_voltage , packet1.Brake_release_pwm_freq , packet1.Brake_engage_delay_time , packet1.Brake_release_delay_time );
    mavlink_msg_appbaseconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_appbaseconfig_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.Polarity , packet1.Home_position_offset_value , packet1.Can_id , packet1.Can_baudrate , packet1.Quick_stop_option_code , packet1.Brake_engage_time , packet1.Brake_release_time , packet1.Dynamic_brake_speed_threshold , packet1.Brake_release_hold_voltage , packet1.Digital_io_outputs_phys , packet1.Digital_io_outputs_mask , packet1.Brake_control_mode , packet1.Brake_rated_voltage , packet1.Brake_release_action_voltage , packet1.Brake_release_pwm_freq , packet1.Brake_engage_delay_time , packet1.Brake_release_delay_time );
    mavlink_msg_appbaseconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_appbaseconfig_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_appbaseconfig_send(MAVLINK_COMM_1 , packet1.Polarity , packet1.Home_position_offset_value , packet1.Can_id , packet1.Can_baudrate , packet1.Quick_stop_option_code , packet1.Brake_engage_time , packet1.Brake_release_time , packet1.Dynamic_brake_speed_threshold , packet1.Brake_release_hold_voltage , packet1.Digital_io_outputs_phys , packet1.Digital_io_outputs_mask , packet1.Brake_control_mode , packet1.Brake_rated_voltage , packet1.Brake_release_action_voltage , packet1.Brake_release_pwm_freq , packet1.Brake_engage_delay_time , packet1.Brake_release_delay_time );
    mavlink_msg_appbaseconfig_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("AppBaseConfig") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_AppBaseConfig) != NULL);
#endif
}

static void mavlink_test_appmotionparam(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_AppMotionParam >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_appmotionparam_t packet_in = {
        93372036854775807LL,93372036854776311LL,93372036854776815LL,185.0,213.0,241.0,269.0,963499544,325.0,353.0,381.0,409.0,437.0,465.0,493.0,521.0,549.0,577.0,605.0,633.0,25,92,159
    };
    mavlink_appmotionparam_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.Target_position = packet_in.Target_position;
        packet1.Home_offset = packet_in.Home_offset;
        packet1.MIT_target_position = packet_in.MIT_target_position;
        packet1.Profile_velocity = packet_in.Profile_velocity;
        packet1.Profile_acceleration = packet_in.Profile_acceleration;
        packet1.Profile_deceleration = packet_in.Profile_deceleration;
        packet1.Quick_stop_deceleration = packet_in.Quick_stop_deceleration;
        packet1.Motion_profile_type = packet_in.Motion_profile_type;
        packet1.Target_velocity = packet_in.Target_velocity;
        packet1.Target_torque = packet_in.Target_torque;
        packet1.Torque_slope = packet_in.Torque_slope;
        packet1.Encoder_calibration_speed = packet_in.Encoder_calibration_speed;
        packet1.MIT_feedforward_torque = packet_in.MIT_feedforward_torque;
        packet1.MIT_max_current = packet_in.MIT_max_current;
        packet1.MIT_target_velocity = packet_in.MIT_target_velocity;
        packet1.MIT_kp = packet_in.MIT_kp;
        packet1.MIT_kd = packet_in.MIT_kd;
        packet1.Homing_speed_search_for_switch = packet_in.Homing_speed_search_for_switch;
        packet1.Homing_speed_search_for_zero = packet_in.Homing_speed_search_for_zero;
        packet1.Homing_acceleration = packet_in.Homing_acceleration;
        packet1.Homing_method = packet_in.Homing_method;
        packet1.Interp_time_value = packet_in.Interp_time_value;
        packet1.Interp_time_index = packet_in.Interp_time_index;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_AppMotionParam_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_AppMotionParam_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_appmotionparam_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_appmotionparam_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_appmotionparam_pack(system_id, component_id, &msg , packet1.Target_position , packet1.Profile_velocity , packet1.Profile_acceleration , packet1.Profile_deceleration , packet1.Quick_stop_deceleration , packet1.Motion_profile_type , packet1.Home_offset , packet1.Homing_method , packet1.Target_velocity , packet1.Target_torque , packet1.Torque_slope , packet1.Encoder_calibration_speed , packet1.MIT_feedforward_torque , packet1.MIT_target_position , packet1.MIT_max_current , packet1.MIT_target_velocity , packet1.MIT_kp , packet1.MIT_kd , packet1.Interp_time_value , packet1.Interp_time_index , packet1.Homing_speed_search_for_switch , packet1.Homing_speed_search_for_zero , packet1.Homing_acceleration );
    mavlink_msg_appmotionparam_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_appmotionparam_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.Target_position , packet1.Profile_velocity , packet1.Profile_acceleration , packet1.Profile_deceleration , packet1.Quick_stop_deceleration , packet1.Motion_profile_type , packet1.Home_offset , packet1.Homing_method , packet1.Target_velocity , packet1.Target_torque , packet1.Torque_slope , packet1.Encoder_calibration_speed , packet1.MIT_feedforward_torque , packet1.MIT_target_position , packet1.MIT_max_current , packet1.MIT_target_velocity , packet1.MIT_kp , packet1.MIT_kd , packet1.Interp_time_value , packet1.Interp_time_index , packet1.Homing_speed_search_for_switch , packet1.Homing_speed_search_for_zero , packet1.Homing_acceleration );
    mavlink_msg_appmotionparam_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_appmotionparam_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_appmotionparam_send(MAVLINK_COMM_1 , packet1.Target_position , packet1.Profile_velocity , packet1.Profile_acceleration , packet1.Profile_deceleration , packet1.Quick_stop_deceleration , packet1.Motion_profile_type , packet1.Home_offset , packet1.Homing_method , packet1.Target_velocity , packet1.Target_torque , packet1.Torque_slope , packet1.Encoder_calibration_speed , packet1.MIT_feedforward_torque , packet1.MIT_target_position , packet1.MIT_max_current , packet1.MIT_target_velocity , packet1.MIT_kp , packet1.MIT_kd , packet1.Interp_time_value , packet1.Interp_time_index , packet1.Homing_speed_search_for_switch , packet1.Homing_speed_search_for_zero , packet1.Homing_acceleration );
    mavlink_msg_appmotionparam_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("AppMotionParam") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_AppMotionParam) != NULL);
#endif
}

static void mavlink_test_apprestrictparam(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_AppRestrictParam >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_apprestrictparam_t packet_in = {
        93372036854775807LL,93372036854776311LL,93372036854776815LL,93372036854777319LL,241.0,269.0,297.0,325.0,353.0,161
    };
    mavlink_apprestrictparam_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.Position_range_limit_Minimal_position_limit = packet_in.Position_range_limit_Minimal_position_limit;
        packet1.Position_range_limit_Maximal_position_limit = packet_in.Position_range_limit_Maximal_position_limit;
        packet1.Software_position_limit_Minimal_position_limit = packet_in.Software_position_limit_Minimal_position_limit;
        packet1.Software_position_limit_Maximal_position_limit = packet_in.Software_position_limit_Maximal_position_limit;
        packet1.Max_profile_velocity = packet_in.Max_profile_velocity;
        packet1.Max_motor_speed = packet_in.Max_motor_speed;
        packet1.Max_acceleration = packet_in.Max_acceleration;
        packet1.Max_deceleration = packet_in.Max_deceleration;
        packet1.Max_current = packet_in.Max_current;
        packet1.Position_limit_enable = packet_in.Position_limit_enable;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_AppRestrictParam_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_AppRestrictParam_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_apprestrictparam_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_apprestrictparam_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_apprestrictparam_pack(system_id, component_id, &msg , packet1.Position_range_limit_Minimal_position_limit , packet1.Position_range_limit_Maximal_position_limit , packet1.Software_position_limit_Minimal_position_limit , packet1.Software_position_limit_Maximal_position_limit , packet1.Max_profile_velocity , packet1.Max_motor_speed , packet1.Max_acceleration , packet1.Max_deceleration , packet1.Max_current , packet1.Position_limit_enable );
    mavlink_msg_apprestrictparam_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_apprestrictparam_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.Position_range_limit_Minimal_position_limit , packet1.Position_range_limit_Maximal_position_limit , packet1.Software_position_limit_Minimal_position_limit , packet1.Software_position_limit_Maximal_position_limit , packet1.Max_profile_velocity , packet1.Max_motor_speed , packet1.Max_acceleration , packet1.Max_deceleration , packet1.Max_current , packet1.Position_limit_enable );
    mavlink_msg_apprestrictparam_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_apprestrictparam_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_apprestrictparam_send(MAVLINK_COMM_1 , packet1.Position_range_limit_Minimal_position_limit , packet1.Position_range_limit_Maximal_position_limit , packet1.Software_position_limit_Minimal_position_limit , packet1.Software_position_limit_Maximal_position_limit , packet1.Max_profile_velocity , packet1.Max_motor_speed , packet1.Max_acceleration , packet1.Max_deceleration , packet1.Max_current , packet1.Position_limit_enable );
    mavlink_msg_apprestrictparam_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("AppRestrictParam") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_AppRestrictParam) != NULL);
#endif
}

static void mavlink_test_appmotioninfo(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_AppMotionInfo >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_appmotioninfo_t packet_in = {
        93372036854775807LL,93372036854776311LL,93372036854776815LL,93372036854777319LL,93372036854777823LL,93372036854778327LL,93372036854778831LL,409.0,437.0,465.0,493.0,521.0,549.0,577.0,605.0,633.0,661.0,689.0,717.0,745.0,773.0,801.0,829.0,23475,23579,23683,255,66,133,200,11
    };
    mavlink_appmotioninfo_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.Position_demand_value = packet_in.Position_demand_value;
        packet1.Position_actual_value_inc = packet_in.Position_actual_value_inc;
        packet1.Position_actual_value = packet_in.Position_actual_value;
        packet1.Following_error_actual_value = packet_in.Following_error_actual_value;
        packet1.Motor_position_demand_value = packet_in.Motor_position_demand_value;
        packet1.Motor_position_actual_value = packet_in.Motor_position_actual_value;
        packet1.Motor_following_error_actual_value = packet_in.Motor_following_error_actual_value;
        packet1.Velocity_demand_value = packet_in.Velocity_demand_value;
        packet1.Velocity_actual_value = packet_in.Velocity_actual_value;
        packet1.Torque_demand_value = packet_in.Torque_demand_value;
        packet1.Torque_actual_value = packet_in.Torque_actual_value;
        packet1.Current_actual_value = packet_in.Current_actual_value;
        packet1.D_current_actual_value = packet_in.D_current_actual_value;
        packet1.U_current_actual_value = packet_in.U_current_actual_value;
        packet1.V_current_actual_value = packet_in.V_current_actual_value;
        packet1.W_current_actual_value = packet_in.W_current_actual_value;
        packet1.Motor_velocity_demand_value = packet_in.Motor_velocity_demand_value;
        packet1.Motor_velocity_actual_value = packet_in.Motor_velocity_actual_value;
        packet1.Current_loop_time = packet_in.Current_loop_time;
        packet1.Position_loop_time = packet_in.Position_loop_time;
        packet1.Current_loop_cycle = packet_in.Current_loop_cycle;
        packet1.Position_loop_cycle = packet_in.Position_loop_cycle;
        packet1.Interp_period = packet_in.Interp_period;
        packet1.U_adc_mid_val = packet_in.U_adc_mid_val;
        packet1.V_adc_mid_val = packet_in.V_adc_mid_val;
        packet1.W_adc_mid_val = packet_in.W_adc_mid_val;
        packet1.Emergency_brake_requested = packet_in.Emergency_brake_requested;
        packet1.Target_update_state = packet_in.Target_update_state;
        packet1.Homing_step = packet_in.Homing_step;
        packet1.Encoder_zero_crossing_state = packet_in.Encoder_zero_crossing_state;
        packet1.Homing_state = packet_in.Homing_state;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_AppMotionInfo_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_AppMotionInfo_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_appmotioninfo_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_appmotioninfo_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_appmotioninfo_pack(system_id, component_id, &msg , packet1.Position_demand_value , packet1.Position_actual_value_inc , packet1.Position_actual_value , packet1.Following_error_actual_value , packet1.Velocity_demand_value , packet1.Velocity_actual_value , packet1.Torque_demand_value , packet1.Torque_actual_value , packet1.Current_actual_value , packet1.D_current_actual_value , packet1.U_current_actual_value , packet1.V_current_actual_value , packet1.W_current_actual_value , packet1.Motor_position_demand_value , packet1.Motor_position_actual_value , packet1.Motor_following_error_actual_value , packet1.Motor_velocity_demand_value , packet1.Motor_velocity_actual_value , packet1.U_adc_mid_val , packet1.V_adc_mid_val , packet1.W_adc_mid_val , packet1.Current_loop_time , packet1.Position_loop_time , packet1.Current_loop_cycle , packet1.Position_loop_cycle , packet1.Interp_period , packet1.Emergency_brake_requested , packet1.Target_update_state , packet1.Homing_step , packet1.Encoder_zero_crossing_state , packet1.Homing_state );
    mavlink_msg_appmotioninfo_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_appmotioninfo_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.Position_demand_value , packet1.Position_actual_value_inc , packet1.Position_actual_value , packet1.Following_error_actual_value , packet1.Velocity_demand_value , packet1.Velocity_actual_value , packet1.Torque_demand_value , packet1.Torque_actual_value , packet1.Current_actual_value , packet1.D_current_actual_value , packet1.U_current_actual_value , packet1.V_current_actual_value , packet1.W_current_actual_value , packet1.Motor_position_demand_value , packet1.Motor_position_actual_value , packet1.Motor_following_error_actual_value , packet1.Motor_velocity_demand_value , packet1.Motor_velocity_actual_value , packet1.U_adc_mid_val , packet1.V_adc_mid_val , packet1.W_adc_mid_val , packet1.Current_loop_time , packet1.Position_loop_time , packet1.Current_loop_cycle , packet1.Position_loop_cycle , packet1.Interp_period , packet1.Emergency_brake_requested , packet1.Target_update_state , packet1.Homing_step , packet1.Encoder_zero_crossing_state , packet1.Homing_state );
    mavlink_msg_appmotioninfo_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_appmotioninfo_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_appmotioninfo_send(MAVLINK_COMM_1 , packet1.Position_demand_value , packet1.Position_actual_value_inc , packet1.Position_actual_value , packet1.Following_error_actual_value , packet1.Velocity_demand_value , packet1.Velocity_actual_value , packet1.Torque_demand_value , packet1.Torque_actual_value , packet1.Current_actual_value , packet1.D_current_actual_value , packet1.U_current_actual_value , packet1.V_current_actual_value , packet1.W_current_actual_value , packet1.Motor_position_demand_value , packet1.Motor_position_actual_value , packet1.Motor_following_error_actual_value , packet1.Motor_velocity_demand_value , packet1.Motor_velocity_actual_value , packet1.U_adc_mid_val , packet1.V_adc_mid_val , packet1.W_adc_mid_val , packet1.Current_loop_time , packet1.Position_loop_time , packet1.Current_loop_cycle , packet1.Position_loop_cycle , packet1.Interp_period , packet1.Emergency_brake_requested , packet1.Target_update_state , packet1.Homing_step , packet1.Encoder_zero_crossing_state , packet1.Homing_state );
    mavlink_msg_appmotioninfo_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("AppMotionInfo") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_AppMotionInfo) != NULL);
#endif
}

static void mavlink_test_appwindowparam(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_AppWindowParam >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_appwindowparam_t packet_in = {
        93372036854775807LL,73.0,963498088,129.0,157.0,185.0,213.0,241.0
    };
    mavlink_appwindowparam_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.Following_error_window = packet_in.Following_error_window;
        packet1.Following_error_time_out = packet_in.Following_error_time_out;
        packet1.Position_window = packet_in.Position_window;
        packet1.Position_window_time = packet_in.Position_window_time;
        packet1.Velocity_window = packet_in.Velocity_window;
        packet1.Velocity_window_time = packet_in.Velocity_window_time;
        packet1.Velocity_threshold = packet_in.Velocity_threshold;
        packet1.Velocity_threshold_time = packet_in.Velocity_threshold_time;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_AppWindowParam_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_AppWindowParam_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_appwindowparam_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_appwindowparam_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_appwindowparam_pack(system_id, component_id, &msg , packet1.Following_error_window , packet1.Following_error_time_out , packet1.Position_window , packet1.Position_window_time , packet1.Velocity_window , packet1.Velocity_window_time , packet1.Velocity_threshold , packet1.Velocity_threshold_time );
    mavlink_msg_appwindowparam_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_appwindowparam_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.Following_error_window , packet1.Following_error_time_out , packet1.Position_window , packet1.Position_window_time , packet1.Velocity_window , packet1.Velocity_window_time , packet1.Velocity_threshold , packet1.Velocity_threshold_time );
    mavlink_msg_appwindowparam_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_appwindowparam_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_appwindowparam_send(MAVLINK_COMM_1 , packet1.Following_error_window , packet1.Following_error_time_out , packet1.Position_window , packet1.Position_window_time , packet1.Velocity_window , packet1.Velocity_window_time , packet1.Velocity_threshold , packet1.Velocity_threshold_time );
    mavlink_msg_appwindowparam_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("AppWindowParam") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_AppWindowParam) != NULL);
#endif
}

static void mavlink_test_appmotorconfig(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_AppMotorConfig >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_appmotorconfig_t packet_in = {
        17.0,45.0,73.0,101.0,129.0,157.0,185.0,963498920,963499128,269.0,297.0,325.0,353.0
    };
    mavlink_appmotorconfig_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.Motor_rated_current = packet_in.Motor_rated_current;
        packet1.Motor_rated_torque = packet_in.Motor_rated_torque;
        packet1.Motor_peak_current = packet_in.Motor_peak_current;
        packet1.Motor_pole_pairs = packet_in.Motor_pole_pairs;
        packet1.Motor_maximum_speed = packet_in.Motor_maximum_speed;
        packet1.Resistance = packet_in.Resistance;
        packet1.Inductance = packet_in.Inductance;
        packet1.Reduction_ratio_num = packet_in.Reduction_ratio_num;
        packet1.Reduction_ratio_den = packet_in.Reduction_ratio_den;
        packet1.Torque_constant = packet_in.Torque_constant;
        packet1.Reduction_ratio = packet_in.Reduction_ratio;
        packet1.Reduction_ratio_inv = packet_in.Reduction_ratio_inv;
        packet1.Motor_rotor_inertia = packet_in.Motor_rotor_inertia;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_AppMotorConfig_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_AppMotorConfig_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_appmotorconfig_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_appmotorconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_appmotorconfig_pack(system_id, component_id, &msg , packet1.Motor_rated_current , packet1.Motor_rated_torque , packet1.Motor_peak_current , packet1.Motor_pole_pairs , packet1.Motor_maximum_speed , packet1.Resistance , packet1.Inductance , packet1.Reduction_ratio_num , packet1.Reduction_ratio_den , packet1.Torque_constant , packet1.Reduction_ratio , packet1.Reduction_ratio_inv , packet1.Motor_rotor_inertia );
    mavlink_msg_appmotorconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_appmotorconfig_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.Motor_rated_current , packet1.Motor_rated_torque , packet1.Motor_peak_current , packet1.Motor_pole_pairs , packet1.Motor_maximum_speed , packet1.Resistance , packet1.Inductance , packet1.Reduction_ratio_num , packet1.Reduction_ratio_den , packet1.Torque_constant , packet1.Reduction_ratio , packet1.Reduction_ratio_inv , packet1.Motor_rotor_inertia );
    mavlink_msg_appmotorconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_appmotorconfig_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_appmotorconfig_send(MAVLINK_COMM_1 , packet1.Motor_rated_current , packet1.Motor_rated_torque , packet1.Motor_peak_current , packet1.Motor_pole_pairs , packet1.Motor_maximum_speed , packet1.Resistance , packet1.Inductance , packet1.Reduction_ratio_num , packet1.Reduction_ratio_den , packet1.Torque_constant , packet1.Reduction_ratio , packet1.Reduction_ratio_inv , packet1.Motor_rotor_inertia );
    mavlink_msg_appmotorconfig_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("AppMotorConfig") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_AppMotorConfig) != NULL);
#endif
}

static void mavlink_test_appprotectconfig(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_AppProtectConfig >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_appprotectconfig_t packet_in = {
        17.0,45.0,73.0,101.0,129.0,157.0,185.0,213.0,241.0,963499336,297.0,325.0,353.0,381.0,409.0,437.0,465.0,493.0,521.0,549.0,577.0,605.0
    };
    mavlink_appprotectconfig_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.Bus_under_voltage_threshold = packet_in.Bus_under_voltage_threshold;
        packet1.Bus_over_voltage_threshold = packet_in.Bus_over_voltage_threshold;
        packet1.Drive_overload_current_duration = packet_in.Drive_overload_current_duration;
        packet1.Drive_peak_current_duration = packet_in.Drive_peak_current_duration;
        packet1.Drive_temperature_threshold_time = packet_in.Drive_temperature_threshold_time;
        packet1.Drive_low_temperature_fault_threshold = packet_in.Drive_low_temperature_fault_threshold;
        packet1.Drive_high_temperature_fault_threshold = packet_in.Drive_high_temperature_fault_threshold;
        packet1.Overspeed_threshold = packet_in.Overspeed_threshold;
        packet1.Drive_overcurrent_threshold = packet_in.Drive_overcurrent_threshold;
        packet1.Protection_enable = packet_in.Protection_enable;
        packet1.Motor_low_temperature_fault_threshold = packet_in.Motor_low_temperature_fault_threshold;
        packet1.Motor_high_temperature_fault_threshold = packet_in.Motor_high_temperature_fault_threshold;
        packet1.Can_timeout = packet_in.Can_timeout;
        packet1.Motor_low_temperature_warning_threshold = packet_in.Motor_low_temperature_warning_threshold;
        packet1.Motor_high_temperature_warning_threshold = packet_in.Motor_high_temperature_warning_threshold;
        packet1.Mcu_temperature_threshold_time = packet_in.Mcu_temperature_threshold_time;
        packet1.Mcu_low_temperature_fault_threshold = packet_in.Mcu_low_temperature_fault_threshold;
        packet1.Mcu_high_temperature_fault_threshold = packet_in.Mcu_high_temperature_fault_threshold;
        packet1.Mcu_low_temperature_warning_threshold = packet_in.Mcu_low_temperature_warning_threshold;
        packet1.Mcu_high_temperature_warning_threshold = packet_in.Mcu_high_temperature_warning_threshold;
        packet1.Drive_low_temperature_warning_threshold = packet_in.Drive_low_temperature_warning_threshold;
        packet1.Drive_high_temperature_warning_threshold = packet_in.Drive_high_temperature_warning_threshold;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_AppProtectConfig_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_AppProtectConfig_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_appprotectconfig_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_appprotectconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_appprotectconfig_pack(system_id, component_id, &msg , packet1.Bus_under_voltage_threshold , packet1.Bus_over_voltage_threshold , packet1.Drive_overload_current_duration , packet1.Drive_peak_current_duration , packet1.Drive_temperature_threshold_time , packet1.Drive_low_temperature_fault_threshold , packet1.Drive_high_temperature_fault_threshold , packet1.Overspeed_threshold , packet1.Drive_overcurrent_threshold , packet1.Protection_enable , packet1.Motor_low_temperature_fault_threshold , packet1.Motor_high_temperature_fault_threshold , packet1.Can_timeout , packet1.Motor_low_temperature_warning_threshold , packet1.Motor_high_temperature_warning_threshold , packet1.Mcu_temperature_threshold_time , packet1.Mcu_low_temperature_fault_threshold , packet1.Mcu_high_temperature_fault_threshold , packet1.Mcu_low_temperature_warning_threshold , packet1.Mcu_high_temperature_warning_threshold , packet1.Drive_low_temperature_warning_threshold , packet1.Drive_high_temperature_warning_threshold );
    mavlink_msg_appprotectconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_appprotectconfig_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.Bus_under_voltage_threshold , packet1.Bus_over_voltage_threshold , packet1.Drive_overload_current_duration , packet1.Drive_peak_current_duration , packet1.Drive_temperature_threshold_time , packet1.Drive_low_temperature_fault_threshold , packet1.Drive_high_temperature_fault_threshold , packet1.Overspeed_threshold , packet1.Drive_overcurrent_threshold , packet1.Protection_enable , packet1.Motor_low_temperature_fault_threshold , packet1.Motor_high_temperature_fault_threshold , packet1.Can_timeout , packet1.Motor_low_temperature_warning_threshold , packet1.Motor_high_temperature_warning_threshold , packet1.Mcu_temperature_threshold_time , packet1.Mcu_low_temperature_fault_threshold , packet1.Mcu_high_temperature_fault_threshold , packet1.Mcu_low_temperature_warning_threshold , packet1.Mcu_high_temperature_warning_threshold , packet1.Drive_low_temperature_warning_threshold , packet1.Drive_high_temperature_warning_threshold );
    mavlink_msg_appprotectconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_appprotectconfig_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_appprotectconfig_send(MAVLINK_COMM_1 , packet1.Bus_under_voltage_threshold , packet1.Bus_over_voltage_threshold , packet1.Drive_overload_current_duration , packet1.Drive_peak_current_duration , packet1.Drive_temperature_threshold_time , packet1.Drive_low_temperature_fault_threshold , packet1.Drive_high_temperature_fault_threshold , packet1.Overspeed_threshold , packet1.Drive_overcurrent_threshold , packet1.Protection_enable , packet1.Motor_low_temperature_fault_threshold , packet1.Motor_high_temperature_fault_threshold , packet1.Can_timeout , packet1.Motor_low_temperature_warning_threshold , packet1.Motor_high_temperature_warning_threshold , packet1.Mcu_temperature_threshold_time , packet1.Mcu_low_temperature_fault_threshold , packet1.Mcu_high_temperature_fault_threshold , packet1.Mcu_low_temperature_warning_threshold , packet1.Mcu_high_temperature_warning_threshold , packet1.Drive_low_temperature_warning_threshold , packet1.Drive_high_temperature_warning_threshold );
    mavlink_msg_appprotectconfig_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("AppProtectConfig") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_AppProtectConfig) != NULL);
#endif
}

static void mavlink_test_mitctlinput(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_MitCtlInput >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_mitctlinput_t packet_in = {
        93372036854775807LL,93372036854776311LL,129.0,157.0,185.0,213.0
    };
    mavlink_mitctlinput_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.pos_tar_p = packet_in.pos_tar_p;
        packet1.pos_now_p = packet_in.pos_now_p;
        packet1.tq_set_NM = packet_in.tq_set_NM;
        packet1.iq_max_A = packet_in.iq_max_A;
        packet1.speed_tar_p_s = packet_in.speed_tar_p_s;
        packet1.speed_now_rad_s = packet_in.speed_now_rad_s;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_MitCtlInput_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_MitCtlInput_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_mitctlinput_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_mitctlinput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_mitctlinput_pack(system_id, component_id, &msg , packet1.tq_set_NM , packet1.pos_tar_p , packet1.pos_now_p , packet1.iq_max_A , packet1.speed_tar_p_s , packet1.speed_now_rad_s );
    mavlink_msg_mitctlinput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_mitctlinput_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.tq_set_NM , packet1.pos_tar_p , packet1.pos_now_p , packet1.iq_max_A , packet1.speed_tar_p_s , packet1.speed_now_rad_s );
    mavlink_msg_mitctlinput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_mitctlinput_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_mitctlinput_send(MAVLINK_COMM_1 , packet1.tq_set_NM , packet1.pos_tar_p , packet1.pos_now_p , packet1.iq_max_A , packet1.speed_tar_p_s , packet1.speed_now_rad_s );
    mavlink_msg_mitctlinput_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("MitCtlInput") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_MitCtlInput) != NULL);
#endif
}

static void mavlink_test_mitctlconfig(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_MitCtlConfig >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_mitctlconfig_t packet_in = {
        17.0,45.0,73.0,101.0
    };
    mavlink_mitctlconfig_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.kp_pos_NM_rad = packet_in.kp_pos_NM_rad;
        packet1.kd_spd_NM_rad_s = packet_in.kd_spd_NM_rad_s;
        packet1.enc_line_inv_p_n = packet_in.enc_line_inv_p_n;
        packet1.kt_NM_A = packet_in.kt_NM_A;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_MitCtlConfig_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_MitCtlConfig_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_mitctlconfig_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_mitctlconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_mitctlconfig_pack(system_id, component_id, &msg , packet1.kp_pos_NM_rad , packet1.kd_spd_NM_rad_s , packet1.enc_line_inv_p_n , packet1.kt_NM_A );
    mavlink_msg_mitctlconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_mitctlconfig_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.kp_pos_NM_rad , packet1.kd_spd_NM_rad_s , packet1.enc_line_inv_p_n , packet1.kt_NM_A );
    mavlink_msg_mitctlconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_mitctlconfig_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_mitctlconfig_send(MAVLINK_COMM_1 , packet1.kp_pos_NM_rad , packet1.kd_spd_NM_rad_s , packet1.enc_line_inv_p_n , packet1.kt_NM_A );
    mavlink_msg_mitctlconfig_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("MitCtlConfig") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_MitCtlConfig) != NULL);
#endif
}

static void mavlink_test_mitctloutput(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_MitCtlOutput >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_mitctloutput_t packet_in = {
        17.0
    };
    mavlink_mitctloutput_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.iq_tar_A = packet_in.iq_tar_A;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_MitCtlOutput_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_MitCtlOutput_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_mitctloutput_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_mitctloutput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_mitctloutput_pack(system_id, component_id, &msg , packet1.iq_tar_A );
    mavlink_msg_mitctloutput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_mitctloutput_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.iq_tar_A );
    mavlink_msg_mitctloutput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_mitctloutput_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_mitctloutput_send(MAVLINK_COMM_1 , packet1.iq_tar_A );
    mavlink_msg_mitctloutput_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("MitCtlOutput") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_MitCtlOutput) != NULL);
#endif
}

static void mavlink_test_apppermissionconfig(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_AppPermissionConfig >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_apppermissionconfig_t packet_in = {
        5,72
    };
    mavlink_apppermissionconfig_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.Comm_control_authority = packet_in.Comm_control_authority;
        packet1.Internal_control_authority = packet_in.Internal_control_authority;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_AppPermissionConfig_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_AppPermissionConfig_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_apppermissionconfig_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_apppermissionconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_apppermissionconfig_pack(system_id, component_id, &msg , packet1.Comm_control_authority , packet1.Internal_control_authority );
    mavlink_msg_apppermissionconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_apppermissionconfig_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.Comm_control_authority , packet1.Internal_control_authority );
    mavlink_msg_apppermissionconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_apppermissionconfig_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_apppermissionconfig_send(MAVLINK_COMM_1 , packet1.Comm_control_authority , packet1.Internal_control_authority );
    mavlink_msg_apppermissionconfig_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("AppPermissionConfig") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_AppPermissionConfig) != NULL);
#endif
}

static void mavlink_test_systemcmd(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_SystemCmd >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_systemcmd_t packet_in = {
        5
    };
    mavlink_systemcmd_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.Sys_cmd = packet_in.Sys_cmd;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_SystemCmd_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_SystemCmd_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_systemcmd_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_systemcmd_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_systemcmd_pack(system_id, component_id, &msg , packet1.Sys_cmd );
    mavlink_msg_systemcmd_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_systemcmd_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.Sys_cmd );
    mavlink_msg_systemcmd_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_systemcmd_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_systemcmd_send(MAVLINK_COMM_1 , packet1.Sys_cmd );
    mavlink_msg_systemcmd_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("SystemCmd") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_SystemCmd) != NULL);
#endif
}

static void mavlink_test_loadpossensorinput(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_LoadPosSensorInput >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_loadpossensorinput_t packet_in = {
        963497464
    };
    mavlink_loadpossensorinput_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.enc_counts_now_p = packet_in.enc_counts_now_p;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_LoadPosSensorInput_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_LoadPosSensorInput_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_loadpossensorinput_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_loadpossensorinput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_loadpossensorinput_pack(system_id, component_id, &msg , packet1.enc_counts_now_p );
    mavlink_msg_loadpossensorinput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_loadpossensorinput_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.enc_counts_now_p );
    mavlink_msg_loadpossensorinput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_loadpossensorinput_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_loadpossensorinput_send(MAVLINK_COMM_1 , packet1.enc_counts_now_p );
    mavlink_msg_loadpossensorinput_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("LoadPosSensorInput") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_LoadPosSensorInput) != NULL);
#endif
}

static void mavlink_test_loadpossensorconfig(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_LoadPosSensorConfig >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_loadpossensorconfig_t packet_in = {
        93372036854775807LL,963497880,41
    };
    mavlink_loadpossensorconfig_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.init_pos_p = packet_in.init_pos_p;
        packet1.enc_line_p_n = packet_in.enc_line_p_n;
        packet1.dir = packet_in.dir;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_LoadPosSensorConfig_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_LoadPosSensorConfig_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_loadpossensorconfig_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_loadpossensorconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_loadpossensorconfig_pack(system_id, component_id, &msg , packet1.enc_line_p_n , packet1.init_pos_p , packet1.dir );
    mavlink_msg_loadpossensorconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_loadpossensorconfig_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.enc_line_p_n , packet1.init_pos_p , packet1.dir );
    mavlink_msg_loadpossensorconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_loadpossensorconfig_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_loadpossensorconfig_send(MAVLINK_COMM_1 , packet1.enc_line_p_n , packet1.init_pos_p , packet1.dir );
    mavlink_msg_loadpossensorconfig_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("LoadPosSensorConfig") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_LoadPosSensorConfig) != NULL);
#endif
}

static void mavlink_test_loadpossensoroutput(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_LoadPosSensorOutput >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_loadpossensoroutput_t packet_in = {
        93372036854775807LL
    };
    mavlink_loadpossensoroutput_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.enc_sum_p = packet_in.enc_sum_p;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_LoadPosSensorOutput_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_LoadPosSensorOutput_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_loadpossensoroutput_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_loadpossensoroutput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_loadpossensoroutput_pack(system_id, component_id, &msg , packet1.enc_sum_p );
    mavlink_msg_loadpossensoroutput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_loadpossensoroutput_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.enc_sum_p );
    mavlink_msg_loadpossensoroutput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_loadpossensoroutput_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_loadpossensoroutput_send(MAVLINK_COMM_1 , packet1.enc_sum_p );
    mavlink_msg_loadpossensoroutput_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("LoadPosSensorOutput") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_LoadPosSensorOutput) != NULL);
#endif
}

static void mavlink_test_systemstatus(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_SystemStatus >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_systemstatus_t packet_in = {
        5,72
    };
    mavlink_systemstatus_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.Storage_status = packet_in.Storage_status;
        packet1.Storage_cmd = packet_in.Storage_cmd;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_SystemStatus_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_SystemStatus_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_systemstatus_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_systemstatus_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_systemstatus_pack(system_id, component_id, &msg , packet1.Storage_status , packet1.Storage_cmd );
    mavlink_msg_systemstatus_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_systemstatus_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.Storage_status , packet1.Storage_cmd );
    mavlink_msg_systemstatus_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_systemstatus_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_systemstatus_send(MAVLINK_COMM_1 , packet1.Storage_status , packet1.Storage_cmd );
    mavlink_msg_systemstatus_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("SystemStatus") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_SystemStatus) != NULL);
#endif
}

static void mavlink_test_encodercalibrationcmd(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_EncoderCalibrationCmd >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_encodercalibrationcmd_t packet_in = {
        17235,17339
    };
    mavlink_encodercalibrationcmd_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.Calibration_cmd = packet_in.Calibration_cmd;
        packet1.Calibration_time = packet_in.Calibration_time;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_EncoderCalibrationCmd_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_EncoderCalibrationCmd_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_encodercalibrationcmd_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_encodercalibrationcmd_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_encodercalibrationcmd_pack(system_id, component_id, &msg , packet1.Calibration_cmd , packet1.Calibration_time );
    mavlink_msg_encodercalibrationcmd_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_encodercalibrationcmd_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.Calibration_cmd , packet1.Calibration_time );
    mavlink_msg_encodercalibrationcmd_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_encodercalibrationcmd_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_encodercalibrationcmd_send(MAVLINK_COMM_1 , packet1.Calibration_cmd , packet1.Calibration_time );
    mavlink_msg_encodercalibrationcmd_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("EncoderCalibrationCmd") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_EncoderCalibrationCmd) != NULL);
#endif
}

static void mavlink_test_encodercalibrationstatus(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_EncoderCalibrationStatus >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_encodercalibrationstatus_t packet_in = {
        17235
    };
    mavlink_encodercalibrationstatus_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.Calibration_status = packet_in.Calibration_status;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_EncoderCalibrationStatus_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_EncoderCalibrationStatus_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_encodercalibrationstatus_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_encodercalibrationstatus_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_encodercalibrationstatus_pack(system_id, component_id, &msg , packet1.Calibration_status );
    mavlink_msg_encodercalibrationstatus_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_encodercalibrationstatus_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.Calibration_status );
    mavlink_msg_encodercalibrationstatus_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_encodercalibrationstatus_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_encodercalibrationstatus_send(MAVLINK_COMM_1 , packet1.Calibration_status );
    mavlink_msg_encodercalibrationstatus_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("EncoderCalibrationStatus") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_EncoderCalibrationStatus) != NULL);
#endif
}

static void mavlink_test_custominfo(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_CustomInfo >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_custominfo_t packet_in = {
        93372036854775807ULL
    };
    mavlink_custominfo_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.User_module_code = packet_in.User_module_code;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_CustomInfo_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_CustomInfo_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_custominfo_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_custominfo_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_custominfo_pack(system_id, component_id, &msg , packet1.User_module_code );
    mavlink_msg_custominfo_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_custominfo_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.User_module_code );
    mavlink_msg_custominfo_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_custominfo_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_custominfo_send(MAVLINK_COMM_1 , packet1.User_module_code );
    mavlink_msg_custominfo_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("CustomInfo") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_CustomInfo) != NULL);
#endif
}

static void mavlink_test_heartbit(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_HeartBit >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_heartbit_t packet_in = {
        5
    };
    mavlink_heartbit_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.Sys_init_flag = packet_in.Sys_init_flag;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_HeartBit_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_HeartBit_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_heartbit_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_heartbit_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_heartbit_pack(system_id, component_id, &msg , packet1.Sys_init_flag );
    mavlink_msg_heartbit_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_heartbit_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.Sys_init_flag );
    mavlink_msg_heartbit_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_heartbit_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_heartbit_send(MAVLINK_COMM_1 , packet1.Sys_init_flag );
    mavlink_msg_heartbit_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("HeartBit") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_HeartBit) != NULL);
#endif
}

static void mavlink_test_historicalinfo(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_HistoricalInfo >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_historicalinfo_t packet_in = {
        { 963497464, 963497465, 963497466, 963497467, 963497468, 963497469, 963497470, 963497471, 963497472, 963497473, 963497474, 963497475, 963497476, 963497477, 963497478, 963497479 }
    };
    mavlink_historicalinfo_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        
        mav_array_memcpy(packet1.Error_records_list, packet_in.Error_records_list, sizeof(uint32_t)*16);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_HistoricalInfo_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_HistoricalInfo_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_historicalinfo_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_historicalinfo_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_historicalinfo_pack(system_id, component_id, &msg , packet1.Error_records_list );
    mavlink_msg_historicalinfo_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_historicalinfo_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.Error_records_list );
    mavlink_msg_historicalinfo_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_historicalinfo_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_historicalinfo_send(MAVLINK_COMM_1 , packet1.Error_records_list );
    mavlink_msg_historicalinfo_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("HistoricalInfo") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_HistoricalInfo) != NULL);
#endif
}

static void mavlink_test_simplantinput(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_SimPlantInput >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_simplantinput_t packet_in = {
        { 17.0, 18.0, 19.0 },101.0
    };
    mavlink_simplantinput_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.tl_Nm = packet_in.tl_Nm;
        
        mav_array_memcpy(packet1.uabc_tar_V, packet_in.uabc_tar_V, sizeof(float)*3);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_SimPlantInput_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_SimPlantInput_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_simplantinput_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_simplantinput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_simplantinput_pack(system_id, component_id, &msg , packet1.uabc_tar_V , packet1.tl_Nm );
    mavlink_msg_simplantinput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_simplantinput_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.uabc_tar_V , packet1.tl_Nm );
    mavlink_msg_simplantinput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_simplantinput_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_simplantinput_send(MAVLINK_COMM_1 , packet1.uabc_tar_V , packet1.tl_Nm );
    mavlink_msg_simplantinput_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("SimPlantInput") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_SimPlantInput) != NULL);
#endif
}

static void mavlink_test_simplantoutput(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_SimPlantOutput >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_simplantoutput_t packet_in = {
        { 17.0, 18.0, 19.0 },963498088,129.0,65
    };
    mavlink_simplantoutput_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.enc_counts_P = packet_in.enc_counts_P;
        packet1.dc_bus_V = packet_in.dc_bus_V;
        packet1.hall_state = packet_in.hall_state;
        
        mav_array_memcpy(packet1.iabc_now_A, packet_in.iabc_now_A, sizeof(float)*3);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_SimPlantOutput_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_SimPlantOutput_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_simplantoutput_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_simplantoutput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_simplantoutput_pack(system_id, component_id, &msg , packet1.iabc_now_A , packet1.enc_counts_P , packet1.hall_state , packet1.dc_bus_V );
    mavlink_msg_simplantoutput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_simplantoutput_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.iabc_now_A , packet1.enc_counts_P , packet1.hall_state , packet1.dc_bus_V );
    mavlink_msg_simplantoutput_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_simplantoutput_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_simplantoutput_send(MAVLINK_COMM_1 , packet1.iabc_now_A , packet1.enc_counts_P , packet1.hall_state , packet1.dc_bus_V );
    mavlink_msg_simplantoutput_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("SimPlantOutput") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_SimPlantOutput) != NULL);
#endif
}

static void mavlink_test_simplantconfig(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_SimPlantConfig >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_simplantconfig_t packet_in = {
        93372036854775807LL,73.0,101.0,129.0,157.0,185.0,213.0,241.0,269.0,297.0,325.0,353.0,381.0,409.0,963500584,465.0,493.0,521.0,549.0
    };
    mavlink_simplantconfig_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.enc_line_init_pos_P = packet_in.enc_line_init_pos_P;
        packet1.b = packet_in.b;
        packet1.fc = packet_in.fc;
        packet1.flux = packet_in.flux;
        packet1.kt = packet_in.kt;
        packet1.j = packet_in.j;
        packet1.ld = packet_in.ld;
        packet1.lq = packet_in.lq;
        packet1.peak_current_A = packet_in.peak_current_A;
        packet1.pn = packet_in.pn;
        packet1.r = packet_in.r;
        packet1.rated_current_A = packet_in.rated_current_A;
        packet1.speed_max_rpm = packet_in.speed_max_rpm;
        packet1.dt_s = packet_in.dt_s;
        packet1.enc_line_p_n = packet_in.enc_line_p_n;
        packet1.j_inv = packet_in.j_inv;
        packet1.ld_inv = packet_in.ld_inv;
        packet1.lq_inv = packet_in.lq_inv;
        packet1.enc_noise = packet_in.enc_noise;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_SimPlantConfig_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_SimPlantConfig_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_simplantconfig_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_simplantconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_simplantconfig_pack(system_id, component_id, &msg , packet1.b , packet1.fc , packet1.flux , packet1.kt , packet1.j , packet1.ld , packet1.lq , packet1.peak_current_A , packet1.pn , packet1.r , packet1.rated_current_A , packet1.speed_max_rpm , packet1.dt_s , packet1.enc_line_p_n , packet1.j_inv , packet1.ld_inv , packet1.lq_inv , packet1.enc_line_init_pos_P , packet1.enc_noise );
    mavlink_msg_simplantconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_simplantconfig_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.b , packet1.fc , packet1.flux , packet1.kt , packet1.j , packet1.ld , packet1.lq , packet1.peak_current_A , packet1.pn , packet1.r , packet1.rated_current_A , packet1.speed_max_rpm , packet1.dt_s , packet1.enc_line_p_n , packet1.j_inv , packet1.ld_inv , packet1.lq_inv , packet1.enc_line_init_pos_P , packet1.enc_noise );
    mavlink_msg_simplantconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_simplantconfig_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_simplantconfig_send(MAVLINK_COMM_1 , packet1.b , packet1.fc , packet1.flux , packet1.kt , packet1.j , packet1.ld , packet1.lq , packet1.peak_current_A , packet1.pn , packet1.r , packet1.rated_current_A , packet1.speed_max_rpm , packet1.dt_s , packet1.enc_line_p_n , packet1.j_inv , packet1.ld_inv , packet1.lq_inv , packet1.enc_line_init_pos_P , packet1.enc_noise );
    mavlink_msg_simplantconfig_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("SimPlantConfig") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_SimPlantConfig) != NULL);
#endif
}

static void mavlink_test_appdebugparam(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_AppDebugParam >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_appdebugparam_t packet_in = {
        { 17.0, 18.0, 19.0, 20.0, 21.0, 22.0, 23.0, 24.0, 25.0, 26.0, 27.0, 28.0, 29.0, 30.0, 31.0, 32.0 },{ 963500792, 963500793, 963500794, 963500795, 963500796, 963500797, 963500798, 963500799, 963500800, 963500801, 963500802, 963500803, 963500804, 963500805, 963500806, 963500807 },{ 963504120, 963504121, 963504122, 963504123, 963504124, 963504125, 963504126, 963504127, 963504128, 963504129, 963504130, 963504131, 963504132, 963504133, 963504134, 963504135 }
    };
    mavlink_appdebugparam_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        
        mav_array_memcpy(packet1.Debug_float, packet_in.Debug_float, sizeof(float)*16);
        mav_array_memcpy(packet1.Debug_uint32, packet_in.Debug_uint32, sizeof(uint32_t)*16);
        mav_array_memcpy(packet1.Debug_int32, packet_in.Debug_int32, sizeof(int32_t)*16);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_AppDebugParam_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_AppDebugParam_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_appdebugparam_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_appdebugparam_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_appdebugparam_pack(system_id, component_id, &msg , packet1.Debug_float , packet1.Debug_uint32 , packet1.Debug_int32 );
    mavlink_msg_appdebugparam_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_appdebugparam_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.Debug_float , packet1.Debug_uint32 , packet1.Debug_int32 );
    mavlink_msg_appdebugparam_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_appdebugparam_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_appdebugparam_send(MAVLINK_COMM_1 , packet1.Debug_float , packet1.Debug_uint32 , packet1.Debug_int32 );
    mavlink_msg_appdebugparam_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("AppDebugParam") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_AppDebugParam) != NULL);
#endif
}

static void mavlink_test_tabledata(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_TableData >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_tabledata_t packet_in = {
        { 17.0, 18.0, 19.0, 20.0, 21.0, 22.0, 23.0, 24.0, 25.0, 26.0, 27.0, 28.0, 29.0, 30.0, 31.0, 32.0, 33.0, 34.0, 35.0, 36.0 }
    };
    mavlink_tabledata_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        
        mav_array_memcpy(packet1.table_data, packet_in.table_data, sizeof(float)*20);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_TableData_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_TableData_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_tabledata_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_tabledata_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_tabledata_pack(system_id, component_id, &msg , packet1.table_data );
    mavlink_msg_tabledata_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_tabledata_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.table_data );
    mavlink_msg_tabledata_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_tabledata_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_tabledata_send(MAVLINK_COMM_1 , packet1.table_data );
    mavlink_msg_tabledata_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("TableData") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_TableData) != NULL);
#endif
}

static void mavlink_test_tableconfig(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_TableConfig >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_tableconfig_t packet_in = {
        5,72
    };
    mavlink_tableconfig_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.table_id = packet_in.table_id;
        packet1.table_index_offset = packet_in.table_index_offset;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_TableConfig_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_TableConfig_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_tableconfig_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_tableconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_tableconfig_pack(system_id, component_id, &msg , packet1.table_id , packet1.table_index_offset );
    mavlink_msg_tableconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_tableconfig_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.table_id , packet1.table_index_offset );
    mavlink_msg_tableconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_tableconfig_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_tableconfig_send(MAVLINK_COMM_1 , packet1.table_id , packet1.table_index_offset );
    mavlink_msg_tableconfig_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("TableConfig") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_TableConfig) != NULL);
#endif
}

static void mavlink_test_appmavlinkconfig(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_AppMavlinkConfig >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_appmavlinkconfig_t packet_in = {
        5,72
    };
    mavlink_appmavlinkconfig_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.Sys_id = packet_in.Sys_id;
        packet1.Comp_id = packet_in.Comp_id;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_AppMavlinkConfig_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_AppMavlinkConfig_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_appmavlinkconfig_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_appmavlinkconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_appmavlinkconfig_pack(system_id, component_id, &msg , packet1.Sys_id , packet1.Comp_id );
    mavlink_msg_appmavlinkconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_appmavlinkconfig_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.Sys_id , packet1.Comp_id );
    mavlink_msg_appmavlinkconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_appmavlinkconfig_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_appmavlinkconfig_send(MAVLINK_COMM_1 , packet1.Sys_id , packet1.Comp_id );
    mavlink_msg_appmavlinkconfig_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("AppMavlinkConfig") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_AppMavlinkConfig) != NULL);
#endif
}

static void mavlink_test_appfiletransferconfig(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_AppFileTransferConfig >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_appfiletransferconfig_t packet_in = {
        963497464,963497672,29,96,163
    };
    mavlink_appfiletransferconfig_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.File_size = packet_in.File_size;
        packet1.File_index_complete = packet_in.File_index_complete;
        packet1.File_type = packet_in.File_type;
        packet1.File_direction = packet_in.File_direction;
        packet1.File_status = packet_in.File_status;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_AppFileTransferConfig_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_AppFileTransferConfig_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_appfiletransferconfig_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_appfiletransferconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_appfiletransferconfig_pack(system_id, component_id, &msg , packet1.File_type , packet1.File_size , packet1.File_direction , packet1.File_index_complete , packet1.File_status );
    mavlink_msg_appfiletransferconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_appfiletransferconfig_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.File_type , packet1.File_size , packet1.File_direction , packet1.File_index_complete , packet1.File_status );
    mavlink_msg_appfiletransferconfig_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_appfiletransferconfig_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_appfiletransferconfig_send(MAVLINK_COMM_1 , packet1.File_type , packet1.File_size , packet1.File_direction , packet1.File_index_complete , packet1.File_status );
    mavlink_msg_appfiletransferconfig_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("AppFileTransferConfig") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_AppFileTransferConfig) != NULL);
#endif
}

static void mavlink_test_appfwupgradeparam(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_AppFwUpgradeParam >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_appfwupgradeparam_t packet_in = {
        963497464,17,84,151
    };
    mavlink_appfwupgradeparam_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.Fw_flash_size = packet_in.Fw_flash_size;
        packet1.Fw_mode = packet_in.Fw_mode;
        packet1.Fw_app_index = packet_in.Fw_app_index;
        packet1.Fw_operating_steps = packet_in.Fw_operating_steps;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_AppFwUpgradeParam_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_AppFwUpgradeParam_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_appfwupgradeparam_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_appfwupgradeparam_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_appfwupgradeparam_pack(system_id, component_id, &msg , packet1.Fw_mode , packet1.Fw_app_index , packet1.Fw_flash_size , packet1.Fw_operating_steps );
    mavlink_msg_appfwupgradeparam_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_appfwupgradeparam_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.Fw_mode , packet1.Fw_app_index , packet1.Fw_flash_size , packet1.Fw_operating_steps );
    mavlink_msg_appfwupgradeparam_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_appfwupgradeparam_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_appfwupgradeparam_send(MAVLINK_COMM_1 , packet1.Fw_mode , packet1.Fw_app_index , packet1.Fw_flash_size , packet1.Fw_operating_steps );
    mavlink_msg_appfwupgradeparam_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("AppFwUpgradeParam") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_AppFwUpgradeParam) != NULL);
#endif
}

static void mavlink_test_appfiletransferstream(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_AppFileTransferStream >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_appfiletransferstream_t packet_in = {
        17235,139,{ 206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200, 201 }
    };
    mavlink_appfiletransferstream_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.Index = packet_in.Index;
        packet1.Length = packet_in.Length;
        
        mav_array_memcpy(packet1.File_buffer, packet_in.File_buffer, sizeof(uint8_t)*252);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_AppFileTransferStream_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_AppFileTransferStream_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_appfiletransferstream_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_appfiletransferstream_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_appfiletransferstream_pack(system_id, component_id, &msg , packet1.Index , packet1.Length , packet1.File_buffer );
    mavlink_msg_appfiletransferstream_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_appfiletransferstream_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.Index , packet1.Length , packet1.File_buffer );
    mavlink_msg_appfiletransferstream_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_appfiletransferstream_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_appfiletransferstream_send(MAVLINK_COMM_1 , packet1.Index , packet1.Length , packet1.File_buffer );
    mavlink_msg_appfiletransferstream_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("AppFileTransferStream") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_AppFileTransferStream) != NULL);
#endif
}

static void mavlink_test_servo_hub_database(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
    mavlink_test_command_long(system_id, component_id, last_msg);
    mavlink_test_command_ack(system_id, component_id, last_msg);
    mavlink_test_read_param(system_id, component_id, last_msg);
    mavlink_test_pmsmconfig(system_id, component_id, last_msg);
    mavlink_test_elecidsininput(system_id, component_id, last_msg);
    mavlink_test_elecidsinoutput(system_id, component_id, last_msg);
    mavlink_test_elecidsinconfig(system_id, component_id, last_msg);
    mavlink_test_mecidoutput(system_id, component_id, last_msg);
    mavlink_test_mecidconfig(system_id, component_id, last_msg);
    mavlink_test_notchfilterinput(system_id, component_id, last_msg);
    mavlink_test_notchfilterinternal(system_id, component_id, last_msg);
    mavlink_test_notchfilteroutput(system_id, component_id, last_msg);
    mavlink_test_mecidinput(system_id, component_id, last_msg);
    mavlink_test_inputshapinginput(system_id, component_id, last_msg);
    mavlink_test_inputshapingconfig(system_id, component_id, last_msg);
    mavlink_test_inputshapingoutput(system_id, component_id, last_msg);
    mavlink_test_scopeconfig(system_id, component_id, last_msg);
    mavlink_test_scopecontrol(system_id, component_id, last_msg);
    mavlink_test_scopedata(system_id, component_id, last_msg);
    mavlink_test_waveformdata(system_id, component_id, last_msg);
    mavlink_test_waveformmap(system_id, component_id, last_msg);
    mavlink_test_posspeedctlinput(system_id, component_id, last_msg);
    mavlink_test_posspeedctloutput(system_id, component_id, last_msg);
    mavlink_test_posspeedctlconfig(system_id, component_id, last_msg);
    mavlink_test_motorctlsmconfig(system_id, component_id, last_msg);
    mavlink_test_motorctlsminput(system_id, component_id, last_msg);
    mavlink_test_motorctlsmoutput(system_id, component_id, last_msg);
    mavlink_test_currentctlinput(system_id, component_id, last_msg);
    mavlink_test_currentctlconfig(system_id, component_id, last_msg);
    mavlink_test_currentctloutput(system_id, component_id, last_msg);
    mavlink_test_notchfilterconfig(system_id, component_id, last_msg);
    mavlink_test_speedobspllinput(system_id, component_id, last_msg);
    mavlink_test_speedobspllconfig(system_id, component_id, last_msg);
    mavlink_test_speedobsplloutput(system_id, component_id, last_msg);
    mavlink_test_elecangleidconfig(system_id, component_id, last_msg);
    mavlink_test_elecangleidoutput(system_id, component_id, last_msg);
    mavlink_test_elecangleidinput(system_id, component_id, last_msg);
    mavlink_test_directionidinput(system_id, component_id, last_msg);
    mavlink_test_directionidconfig(system_id, component_id, last_msg);
    mavlink_test_directionidoutput(system_id, component_id, last_msg);
    mavlink_test_motorpossensorinput(system_id, component_id, last_msg);
    mavlink_test_motorpossensorconfig(system_id, component_id, last_msg);
    mavlink_test_motorpossensoroutput(system_id, component_id, last_msg);
    mavlink_test_polepairsidinput(system_id, component_id, last_msg);
    mavlink_test_polepairsidconfig(system_id, component_id, last_msg);
    mavlink_test_polepairsidoutput(system_id, component_id, last_msg);
    mavlink_test_nonvolatileparam(system_id, component_id, last_msg);
    mavlink_test_systemconfig(system_id, component_id, last_msg);
    mavlink_test_tqfcidinput(system_id, component_id, last_msg);
    mavlink_test_tqfcidconfig(system_id, component_id, last_msg);
    mavlink_test_tqfcidoutput(system_id, component_id, last_msg);
    mavlink_test_objectdictionary(system_id, component_id, last_msg);
    mavlink_test_reciprocalmotionconfig(system_id, component_id, last_msg);
    mavlink_test_reciprocalmotionoutput(system_id, component_id, last_msg);
    mavlink_test_referencesignalconfig(system_id, component_id, last_msg);
    mavlink_test_referencesignaloutput(system_id, component_id, last_msg);
    mavlink_test_appcontrolword(system_id, component_id, last_msg);
    mavlink_test_appstatusinfo(system_id, component_id, last_msg);
    mavlink_test_appopmode(system_id, component_id, last_msg);
    mavlink_test_appencoderconfig(system_id, component_id, last_msg);
    mavlink_test_appbaseconfig(system_id, component_id, last_msg);
    mavlink_test_appmotionparam(system_id, component_id, last_msg);
    mavlink_test_apprestrictparam(system_id, component_id, last_msg);
    mavlink_test_appmotioninfo(system_id, component_id, last_msg);
    mavlink_test_appwindowparam(system_id, component_id, last_msg);
    mavlink_test_appmotorconfig(system_id, component_id, last_msg);
    mavlink_test_appprotectconfig(system_id, component_id, last_msg);
    mavlink_test_mitctlinput(system_id, component_id, last_msg);
    mavlink_test_mitctlconfig(system_id, component_id, last_msg);
    mavlink_test_mitctloutput(system_id, component_id, last_msg);
    mavlink_test_apppermissionconfig(system_id, component_id, last_msg);
    mavlink_test_systemcmd(system_id, component_id, last_msg);
    mavlink_test_loadpossensorinput(system_id, component_id, last_msg);
    mavlink_test_loadpossensorconfig(system_id, component_id, last_msg);
    mavlink_test_loadpossensoroutput(system_id, component_id, last_msg);
    mavlink_test_systemstatus(system_id, component_id, last_msg);
    mavlink_test_encodercalibrationcmd(system_id, component_id, last_msg);
    mavlink_test_encodercalibrationstatus(system_id, component_id, last_msg);
    mavlink_test_custominfo(system_id, component_id, last_msg);
    mavlink_test_heartbit(system_id, component_id, last_msg);
    mavlink_test_historicalinfo(system_id, component_id, last_msg);
    mavlink_test_simplantinput(system_id, component_id, last_msg);
    mavlink_test_simplantoutput(system_id, component_id, last_msg);
    mavlink_test_simplantconfig(system_id, component_id, last_msg);
    mavlink_test_appdebugparam(system_id, component_id, last_msg);
    mavlink_test_tabledata(system_id, component_id, last_msg);
    mavlink_test_tableconfig(system_id, component_id, last_msg);
    mavlink_test_appmavlinkconfig(system_id, component_id, last_msg);
    mavlink_test_appfiletransferconfig(system_id, component_id, last_msg);
    mavlink_test_appfwupgradeparam(system_id, component_id, last_msg);
    mavlink_test_appfiletransferstream(system_id, component_id, last_msg);
}

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // SERVO_HUB_DATABASE_TESTSUITE_H
