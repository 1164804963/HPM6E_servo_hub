#pragma once
// MESSAGE AppEncoderConfig PACKING

#define MAVLINK_MSG_ID_AppEncoderConfig 30057


typedef struct __mavlink_appencoderconfig_t {
 uint32_t Load_encoder_resolution; /*<  */
 uint32_t Motor_encoder_resolution; /*<  */
 float Load_pps_2_rpm; /*<  */
 float Load_rpm_2_pps; /*<  */
 float Motor_pps_2_rpm; /*<  */
 float Motor_rpm_2_pps; /*<  */
 float P_load_2_motor; /*<  */
 float P_motor_2_load; /*<  */
 uint32_t Load_control_resolution; /*<  */
 uint32_t Motor_control_resolution; /*<  */
 uint8_t Motor_encoder_type; /*<  */
 uint8_t Load_encoder_type; /*<  */
 uint8_t Motor_encoder_options; /*<  */
 uint8_t Load_encoder_options; /*<  */
} mavlink_appencoderconfig_t;

#define MAVLINK_MSG_ID_AppEncoderConfig_LEN 44
#define MAVLINK_MSG_ID_AppEncoderConfig_MIN_LEN 44
#define MAVLINK_MSG_ID_30057_LEN 44
#define MAVLINK_MSG_ID_30057_MIN_LEN 44

#define MAVLINK_MSG_ID_AppEncoderConfig_CRC 220
#define MAVLINK_MSG_ID_30057_CRC 220



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_AppEncoderConfig { \
    30057, \
    "AppEncoderConfig", \
    14, \
    {  { "Load_encoder_resolution", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_appencoderconfig_t, Load_encoder_resolution) }, \
         { "Motor_encoder_resolution", NULL, MAVLINK_TYPE_UINT32_T, 0, 4, offsetof(mavlink_appencoderconfig_t, Motor_encoder_resolution) }, \
         { "Motor_encoder_type", NULL, MAVLINK_TYPE_UINT8_T, 0, 40, offsetof(mavlink_appencoderconfig_t, Motor_encoder_type) }, \
         { "Load_encoder_type", NULL, MAVLINK_TYPE_UINT8_T, 0, 41, offsetof(mavlink_appencoderconfig_t, Load_encoder_type) }, \
         { "Motor_encoder_options", NULL, MAVLINK_TYPE_UINT8_T, 0, 42, offsetof(mavlink_appencoderconfig_t, Motor_encoder_options) }, \
         { "Load_pps_2_rpm", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_appencoderconfig_t, Load_pps_2_rpm) }, \
         { "Load_rpm_2_pps", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_appencoderconfig_t, Load_rpm_2_pps) }, \
         { "Motor_pps_2_rpm", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_appencoderconfig_t, Motor_pps_2_rpm) }, \
         { "Motor_rpm_2_pps", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_appencoderconfig_t, Motor_rpm_2_pps) }, \
         { "P_load_2_motor", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_appencoderconfig_t, P_load_2_motor) }, \
         { "P_motor_2_load", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_appencoderconfig_t, P_motor_2_load) }, \
         { "Load_control_resolution", NULL, MAVLINK_TYPE_UINT32_T, 0, 32, offsetof(mavlink_appencoderconfig_t, Load_control_resolution) }, \
         { "Motor_control_resolution", NULL, MAVLINK_TYPE_UINT32_T, 0, 36, offsetof(mavlink_appencoderconfig_t, Motor_control_resolution) }, \
         { "Load_encoder_options", NULL, MAVLINK_TYPE_UINT8_T, 0, 43, offsetof(mavlink_appencoderconfig_t, Load_encoder_options) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_AppEncoderConfig { \
    "AppEncoderConfig", \
    14, \
    {  { "Load_encoder_resolution", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_appencoderconfig_t, Load_encoder_resolution) }, \
         { "Motor_encoder_resolution", NULL, MAVLINK_TYPE_UINT32_T, 0, 4, offsetof(mavlink_appencoderconfig_t, Motor_encoder_resolution) }, \
         { "Motor_encoder_type", NULL, MAVLINK_TYPE_UINT8_T, 0, 40, offsetof(mavlink_appencoderconfig_t, Motor_encoder_type) }, \
         { "Load_encoder_type", NULL, MAVLINK_TYPE_UINT8_T, 0, 41, offsetof(mavlink_appencoderconfig_t, Load_encoder_type) }, \
         { "Motor_encoder_options", NULL, MAVLINK_TYPE_UINT8_T, 0, 42, offsetof(mavlink_appencoderconfig_t, Motor_encoder_options) }, \
         { "Load_pps_2_rpm", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_appencoderconfig_t, Load_pps_2_rpm) }, \
         { "Load_rpm_2_pps", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_appencoderconfig_t, Load_rpm_2_pps) }, \
         { "Motor_pps_2_rpm", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_appencoderconfig_t, Motor_pps_2_rpm) }, \
         { "Motor_rpm_2_pps", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_appencoderconfig_t, Motor_rpm_2_pps) }, \
         { "P_load_2_motor", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_appencoderconfig_t, P_load_2_motor) }, \
         { "P_motor_2_load", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_appencoderconfig_t, P_motor_2_load) }, \
         { "Load_control_resolution", NULL, MAVLINK_TYPE_UINT32_T, 0, 32, offsetof(mavlink_appencoderconfig_t, Load_control_resolution) }, \
         { "Motor_control_resolution", NULL, MAVLINK_TYPE_UINT32_T, 0, 36, offsetof(mavlink_appencoderconfig_t, Motor_control_resolution) }, \
         { "Load_encoder_options", NULL, MAVLINK_TYPE_UINT8_T, 0, 43, offsetof(mavlink_appencoderconfig_t, Load_encoder_options) }, \
         } \
}
#endif

/**
 * @brief Pack a appencoderconfig message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param Load_encoder_resolution  
 * @param Motor_encoder_resolution  
 * @param Motor_encoder_type  
 * @param Load_encoder_type  
 * @param Motor_encoder_options  
 * @param Load_pps_2_rpm  
 * @param Load_rpm_2_pps  
 * @param Motor_pps_2_rpm  
 * @param Motor_rpm_2_pps  
 * @param P_load_2_motor  
 * @param P_motor_2_load  
 * @param Load_control_resolution  
 * @param Motor_control_resolution  
 * @param Load_encoder_options  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_appencoderconfig_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint32_t Load_encoder_resolution, uint32_t Motor_encoder_resolution, uint8_t Motor_encoder_type, uint8_t Load_encoder_type, uint8_t Motor_encoder_options, float Load_pps_2_rpm, float Load_rpm_2_pps, float Motor_pps_2_rpm, float Motor_rpm_2_pps, float P_load_2_motor, float P_motor_2_load, uint32_t Load_control_resolution, uint32_t Motor_control_resolution, uint8_t Load_encoder_options)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_AppEncoderConfig_LEN];
    _mav_put_uint32_t(buf, 0, Load_encoder_resolution);
    _mav_put_uint32_t(buf, 4, Motor_encoder_resolution);
    _mav_put_float(buf, 8, Load_pps_2_rpm);
    _mav_put_float(buf, 12, Load_rpm_2_pps);
    _mav_put_float(buf, 16, Motor_pps_2_rpm);
    _mav_put_float(buf, 20, Motor_rpm_2_pps);
    _mav_put_float(buf, 24, P_load_2_motor);
    _mav_put_float(buf, 28, P_motor_2_load);
    _mav_put_uint32_t(buf, 32, Load_control_resolution);
    _mav_put_uint32_t(buf, 36, Motor_control_resolution);
    _mav_put_uint8_t(buf, 40, Motor_encoder_type);
    _mav_put_uint8_t(buf, 41, Load_encoder_type);
    _mav_put_uint8_t(buf, 42, Motor_encoder_options);
    _mav_put_uint8_t(buf, 43, Load_encoder_options);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_AppEncoderConfig_LEN);
#else
    mavlink_appencoderconfig_t packet;
    packet.Load_encoder_resolution = Load_encoder_resolution;
    packet.Motor_encoder_resolution = Motor_encoder_resolution;
    packet.Load_pps_2_rpm = Load_pps_2_rpm;
    packet.Load_rpm_2_pps = Load_rpm_2_pps;
    packet.Motor_pps_2_rpm = Motor_pps_2_rpm;
    packet.Motor_rpm_2_pps = Motor_rpm_2_pps;
    packet.P_load_2_motor = P_load_2_motor;
    packet.P_motor_2_load = P_motor_2_load;
    packet.Load_control_resolution = Load_control_resolution;
    packet.Motor_control_resolution = Motor_control_resolution;
    packet.Motor_encoder_type = Motor_encoder_type;
    packet.Load_encoder_type = Load_encoder_type;
    packet.Motor_encoder_options = Motor_encoder_options;
    packet.Load_encoder_options = Load_encoder_options;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_AppEncoderConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_AppEncoderConfig;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_AppEncoderConfig_MIN_LEN, MAVLINK_MSG_ID_AppEncoderConfig_LEN, MAVLINK_MSG_ID_AppEncoderConfig_CRC);
}

/**
 * @brief Pack a appencoderconfig message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param Load_encoder_resolution  
 * @param Motor_encoder_resolution  
 * @param Motor_encoder_type  
 * @param Load_encoder_type  
 * @param Motor_encoder_options  
 * @param Load_pps_2_rpm  
 * @param Load_rpm_2_pps  
 * @param Motor_pps_2_rpm  
 * @param Motor_rpm_2_pps  
 * @param P_load_2_motor  
 * @param P_motor_2_load  
 * @param Load_control_resolution  
 * @param Motor_control_resolution  
 * @param Load_encoder_options  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_appencoderconfig_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint32_t Load_encoder_resolution, uint32_t Motor_encoder_resolution, uint8_t Motor_encoder_type, uint8_t Load_encoder_type, uint8_t Motor_encoder_options, float Load_pps_2_rpm, float Load_rpm_2_pps, float Motor_pps_2_rpm, float Motor_rpm_2_pps, float P_load_2_motor, float P_motor_2_load, uint32_t Load_control_resolution, uint32_t Motor_control_resolution, uint8_t Load_encoder_options)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_AppEncoderConfig_LEN];
    _mav_put_uint32_t(buf, 0, Load_encoder_resolution);
    _mav_put_uint32_t(buf, 4, Motor_encoder_resolution);
    _mav_put_float(buf, 8, Load_pps_2_rpm);
    _mav_put_float(buf, 12, Load_rpm_2_pps);
    _mav_put_float(buf, 16, Motor_pps_2_rpm);
    _mav_put_float(buf, 20, Motor_rpm_2_pps);
    _mav_put_float(buf, 24, P_load_2_motor);
    _mav_put_float(buf, 28, P_motor_2_load);
    _mav_put_uint32_t(buf, 32, Load_control_resolution);
    _mav_put_uint32_t(buf, 36, Motor_control_resolution);
    _mav_put_uint8_t(buf, 40, Motor_encoder_type);
    _mav_put_uint8_t(buf, 41, Load_encoder_type);
    _mav_put_uint8_t(buf, 42, Motor_encoder_options);
    _mav_put_uint8_t(buf, 43, Load_encoder_options);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_AppEncoderConfig_LEN);
#else
    mavlink_appencoderconfig_t packet;
    packet.Load_encoder_resolution = Load_encoder_resolution;
    packet.Motor_encoder_resolution = Motor_encoder_resolution;
    packet.Load_pps_2_rpm = Load_pps_2_rpm;
    packet.Load_rpm_2_pps = Load_rpm_2_pps;
    packet.Motor_pps_2_rpm = Motor_pps_2_rpm;
    packet.Motor_rpm_2_pps = Motor_rpm_2_pps;
    packet.P_load_2_motor = P_load_2_motor;
    packet.P_motor_2_load = P_motor_2_load;
    packet.Load_control_resolution = Load_control_resolution;
    packet.Motor_control_resolution = Motor_control_resolution;
    packet.Motor_encoder_type = Motor_encoder_type;
    packet.Load_encoder_type = Load_encoder_type;
    packet.Motor_encoder_options = Motor_encoder_options;
    packet.Load_encoder_options = Load_encoder_options;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_AppEncoderConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_AppEncoderConfig;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_AppEncoderConfig_MIN_LEN, MAVLINK_MSG_ID_AppEncoderConfig_LEN, MAVLINK_MSG_ID_AppEncoderConfig_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_AppEncoderConfig_MIN_LEN, MAVLINK_MSG_ID_AppEncoderConfig_LEN);
#endif
}

/**
 * @brief Pack a appencoderconfig message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param Load_encoder_resolution  
 * @param Motor_encoder_resolution  
 * @param Motor_encoder_type  
 * @param Load_encoder_type  
 * @param Motor_encoder_options  
 * @param Load_pps_2_rpm  
 * @param Load_rpm_2_pps  
 * @param Motor_pps_2_rpm  
 * @param Motor_rpm_2_pps  
 * @param P_load_2_motor  
 * @param P_motor_2_load  
 * @param Load_control_resolution  
 * @param Motor_control_resolution  
 * @param Load_encoder_options  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_appencoderconfig_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint32_t Load_encoder_resolution,uint32_t Motor_encoder_resolution,uint8_t Motor_encoder_type,uint8_t Load_encoder_type,uint8_t Motor_encoder_options,float Load_pps_2_rpm,float Load_rpm_2_pps,float Motor_pps_2_rpm,float Motor_rpm_2_pps,float P_load_2_motor,float P_motor_2_load,uint32_t Load_control_resolution,uint32_t Motor_control_resolution,uint8_t Load_encoder_options)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_AppEncoderConfig_LEN];
    _mav_put_uint32_t(buf, 0, Load_encoder_resolution);
    _mav_put_uint32_t(buf, 4, Motor_encoder_resolution);
    _mav_put_float(buf, 8, Load_pps_2_rpm);
    _mav_put_float(buf, 12, Load_rpm_2_pps);
    _mav_put_float(buf, 16, Motor_pps_2_rpm);
    _mav_put_float(buf, 20, Motor_rpm_2_pps);
    _mav_put_float(buf, 24, P_load_2_motor);
    _mav_put_float(buf, 28, P_motor_2_load);
    _mav_put_uint32_t(buf, 32, Load_control_resolution);
    _mav_put_uint32_t(buf, 36, Motor_control_resolution);
    _mav_put_uint8_t(buf, 40, Motor_encoder_type);
    _mav_put_uint8_t(buf, 41, Load_encoder_type);
    _mav_put_uint8_t(buf, 42, Motor_encoder_options);
    _mav_put_uint8_t(buf, 43, Load_encoder_options);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_AppEncoderConfig_LEN);
#else
    mavlink_appencoderconfig_t packet;
    packet.Load_encoder_resolution = Load_encoder_resolution;
    packet.Motor_encoder_resolution = Motor_encoder_resolution;
    packet.Load_pps_2_rpm = Load_pps_2_rpm;
    packet.Load_rpm_2_pps = Load_rpm_2_pps;
    packet.Motor_pps_2_rpm = Motor_pps_2_rpm;
    packet.Motor_rpm_2_pps = Motor_rpm_2_pps;
    packet.P_load_2_motor = P_load_2_motor;
    packet.P_motor_2_load = P_motor_2_load;
    packet.Load_control_resolution = Load_control_resolution;
    packet.Motor_control_resolution = Motor_control_resolution;
    packet.Motor_encoder_type = Motor_encoder_type;
    packet.Load_encoder_type = Load_encoder_type;
    packet.Motor_encoder_options = Motor_encoder_options;
    packet.Load_encoder_options = Load_encoder_options;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_AppEncoderConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_AppEncoderConfig;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_AppEncoderConfig_MIN_LEN, MAVLINK_MSG_ID_AppEncoderConfig_LEN, MAVLINK_MSG_ID_AppEncoderConfig_CRC);
}

/**
 * @brief Encode a appencoderconfig struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param appencoderconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_appencoderconfig_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_appencoderconfig_t* appencoderconfig)
{
    return mavlink_msg_appencoderconfig_pack(system_id, component_id, msg, appencoderconfig->Load_encoder_resolution, appencoderconfig->Motor_encoder_resolution, appencoderconfig->Motor_encoder_type, appencoderconfig->Load_encoder_type, appencoderconfig->Motor_encoder_options, appencoderconfig->Load_pps_2_rpm, appencoderconfig->Load_rpm_2_pps, appencoderconfig->Motor_pps_2_rpm, appencoderconfig->Motor_rpm_2_pps, appencoderconfig->P_load_2_motor, appencoderconfig->P_motor_2_load, appencoderconfig->Load_control_resolution, appencoderconfig->Motor_control_resolution, appencoderconfig->Load_encoder_options);
}

/**
 * @brief Encode a appencoderconfig struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param appencoderconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_appencoderconfig_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_appencoderconfig_t* appencoderconfig)
{
    return mavlink_msg_appencoderconfig_pack_chan(system_id, component_id, chan, msg, appencoderconfig->Load_encoder_resolution, appencoderconfig->Motor_encoder_resolution, appencoderconfig->Motor_encoder_type, appencoderconfig->Load_encoder_type, appencoderconfig->Motor_encoder_options, appencoderconfig->Load_pps_2_rpm, appencoderconfig->Load_rpm_2_pps, appencoderconfig->Motor_pps_2_rpm, appencoderconfig->Motor_rpm_2_pps, appencoderconfig->P_load_2_motor, appencoderconfig->P_motor_2_load, appencoderconfig->Load_control_resolution, appencoderconfig->Motor_control_resolution, appencoderconfig->Load_encoder_options);
}

/**
 * @brief Encode a appencoderconfig struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param appencoderconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_appencoderconfig_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_appencoderconfig_t* appencoderconfig)
{
    return mavlink_msg_appencoderconfig_pack_status(system_id, component_id, _status, msg,  appencoderconfig->Load_encoder_resolution, appencoderconfig->Motor_encoder_resolution, appencoderconfig->Motor_encoder_type, appencoderconfig->Load_encoder_type, appencoderconfig->Motor_encoder_options, appencoderconfig->Load_pps_2_rpm, appencoderconfig->Load_rpm_2_pps, appencoderconfig->Motor_pps_2_rpm, appencoderconfig->Motor_rpm_2_pps, appencoderconfig->P_load_2_motor, appencoderconfig->P_motor_2_load, appencoderconfig->Load_control_resolution, appencoderconfig->Motor_control_resolution, appencoderconfig->Load_encoder_options);
}

/**
 * @brief Send a appencoderconfig message
 * @param chan MAVLink channel to send the message
 *
 * @param Load_encoder_resolution  
 * @param Motor_encoder_resolution  
 * @param Motor_encoder_type  
 * @param Load_encoder_type  
 * @param Motor_encoder_options  
 * @param Load_pps_2_rpm  
 * @param Load_rpm_2_pps  
 * @param Motor_pps_2_rpm  
 * @param Motor_rpm_2_pps  
 * @param P_load_2_motor  
 * @param P_motor_2_load  
 * @param Load_control_resolution  
 * @param Motor_control_resolution  
 * @param Load_encoder_options  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_appencoderconfig_send(mavlink_channel_t chan, uint32_t Load_encoder_resolution, uint32_t Motor_encoder_resolution, uint8_t Motor_encoder_type, uint8_t Load_encoder_type, uint8_t Motor_encoder_options, float Load_pps_2_rpm, float Load_rpm_2_pps, float Motor_pps_2_rpm, float Motor_rpm_2_pps, float P_load_2_motor, float P_motor_2_load, uint32_t Load_control_resolution, uint32_t Motor_control_resolution, uint8_t Load_encoder_options)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_AppEncoderConfig_LEN];
    _mav_put_uint32_t(buf, 0, Load_encoder_resolution);
    _mav_put_uint32_t(buf, 4, Motor_encoder_resolution);
    _mav_put_float(buf, 8, Load_pps_2_rpm);
    _mav_put_float(buf, 12, Load_rpm_2_pps);
    _mav_put_float(buf, 16, Motor_pps_2_rpm);
    _mav_put_float(buf, 20, Motor_rpm_2_pps);
    _mav_put_float(buf, 24, P_load_2_motor);
    _mav_put_float(buf, 28, P_motor_2_load);
    _mav_put_uint32_t(buf, 32, Load_control_resolution);
    _mav_put_uint32_t(buf, 36, Motor_control_resolution);
    _mav_put_uint8_t(buf, 40, Motor_encoder_type);
    _mav_put_uint8_t(buf, 41, Load_encoder_type);
    _mav_put_uint8_t(buf, 42, Motor_encoder_options);
    _mav_put_uint8_t(buf, 43, Load_encoder_options);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppEncoderConfig, buf, MAVLINK_MSG_ID_AppEncoderConfig_MIN_LEN, MAVLINK_MSG_ID_AppEncoderConfig_LEN, MAVLINK_MSG_ID_AppEncoderConfig_CRC);
#else
    mavlink_appencoderconfig_t packet;
    packet.Load_encoder_resolution = Load_encoder_resolution;
    packet.Motor_encoder_resolution = Motor_encoder_resolution;
    packet.Load_pps_2_rpm = Load_pps_2_rpm;
    packet.Load_rpm_2_pps = Load_rpm_2_pps;
    packet.Motor_pps_2_rpm = Motor_pps_2_rpm;
    packet.Motor_rpm_2_pps = Motor_rpm_2_pps;
    packet.P_load_2_motor = P_load_2_motor;
    packet.P_motor_2_load = P_motor_2_load;
    packet.Load_control_resolution = Load_control_resolution;
    packet.Motor_control_resolution = Motor_control_resolution;
    packet.Motor_encoder_type = Motor_encoder_type;
    packet.Load_encoder_type = Load_encoder_type;
    packet.Motor_encoder_options = Motor_encoder_options;
    packet.Load_encoder_options = Load_encoder_options;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppEncoderConfig, (const char *)&packet, MAVLINK_MSG_ID_AppEncoderConfig_MIN_LEN, MAVLINK_MSG_ID_AppEncoderConfig_LEN, MAVLINK_MSG_ID_AppEncoderConfig_CRC);
#endif
}

/**
 * @brief Send a appencoderconfig message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_appencoderconfig_send_struct(mavlink_channel_t chan, const mavlink_appencoderconfig_t* appencoderconfig)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_appencoderconfig_send(chan, appencoderconfig->Load_encoder_resolution, appencoderconfig->Motor_encoder_resolution, appencoderconfig->Motor_encoder_type, appencoderconfig->Load_encoder_type, appencoderconfig->Motor_encoder_options, appencoderconfig->Load_pps_2_rpm, appencoderconfig->Load_rpm_2_pps, appencoderconfig->Motor_pps_2_rpm, appencoderconfig->Motor_rpm_2_pps, appencoderconfig->P_load_2_motor, appencoderconfig->P_motor_2_load, appencoderconfig->Load_control_resolution, appencoderconfig->Motor_control_resolution, appencoderconfig->Load_encoder_options);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppEncoderConfig, (const char *)appencoderconfig, MAVLINK_MSG_ID_AppEncoderConfig_MIN_LEN, MAVLINK_MSG_ID_AppEncoderConfig_LEN, MAVLINK_MSG_ID_AppEncoderConfig_CRC);
#endif
}

#if MAVLINK_MSG_ID_AppEncoderConfig_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_appencoderconfig_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint32_t Load_encoder_resolution, uint32_t Motor_encoder_resolution, uint8_t Motor_encoder_type, uint8_t Load_encoder_type, uint8_t Motor_encoder_options, float Load_pps_2_rpm, float Load_rpm_2_pps, float Motor_pps_2_rpm, float Motor_rpm_2_pps, float P_load_2_motor, float P_motor_2_load, uint32_t Load_control_resolution, uint32_t Motor_control_resolution, uint8_t Load_encoder_options)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint32_t(buf, 0, Load_encoder_resolution);
    _mav_put_uint32_t(buf, 4, Motor_encoder_resolution);
    _mav_put_float(buf, 8, Load_pps_2_rpm);
    _mav_put_float(buf, 12, Load_rpm_2_pps);
    _mav_put_float(buf, 16, Motor_pps_2_rpm);
    _mav_put_float(buf, 20, Motor_rpm_2_pps);
    _mav_put_float(buf, 24, P_load_2_motor);
    _mav_put_float(buf, 28, P_motor_2_load);
    _mav_put_uint32_t(buf, 32, Load_control_resolution);
    _mav_put_uint32_t(buf, 36, Motor_control_resolution);
    _mav_put_uint8_t(buf, 40, Motor_encoder_type);
    _mav_put_uint8_t(buf, 41, Load_encoder_type);
    _mav_put_uint8_t(buf, 42, Motor_encoder_options);
    _mav_put_uint8_t(buf, 43, Load_encoder_options);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppEncoderConfig, buf, MAVLINK_MSG_ID_AppEncoderConfig_MIN_LEN, MAVLINK_MSG_ID_AppEncoderConfig_LEN, MAVLINK_MSG_ID_AppEncoderConfig_CRC);
#else
    mavlink_appencoderconfig_t *packet = (mavlink_appencoderconfig_t *)msgbuf;
    packet->Load_encoder_resolution = Load_encoder_resolution;
    packet->Motor_encoder_resolution = Motor_encoder_resolution;
    packet->Load_pps_2_rpm = Load_pps_2_rpm;
    packet->Load_rpm_2_pps = Load_rpm_2_pps;
    packet->Motor_pps_2_rpm = Motor_pps_2_rpm;
    packet->Motor_rpm_2_pps = Motor_rpm_2_pps;
    packet->P_load_2_motor = P_load_2_motor;
    packet->P_motor_2_load = P_motor_2_load;
    packet->Load_control_resolution = Load_control_resolution;
    packet->Motor_control_resolution = Motor_control_resolution;
    packet->Motor_encoder_type = Motor_encoder_type;
    packet->Load_encoder_type = Load_encoder_type;
    packet->Motor_encoder_options = Motor_encoder_options;
    packet->Load_encoder_options = Load_encoder_options;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppEncoderConfig, (const char *)packet, MAVLINK_MSG_ID_AppEncoderConfig_MIN_LEN, MAVLINK_MSG_ID_AppEncoderConfig_LEN, MAVLINK_MSG_ID_AppEncoderConfig_CRC);
#endif
}
#endif

#endif

// MESSAGE AppEncoderConfig UNPACKING


/**
 * @brief Get field Load_encoder_resolution from appencoderconfig message
 *
 * @return  
 */
static inline uint32_t mavlink_msg_appencoderconfig_get_Load_encoder_resolution(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Get field Motor_encoder_resolution from appencoderconfig message
 *
 * @return  
 */
static inline uint32_t mavlink_msg_appencoderconfig_get_Motor_encoder_resolution(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  4);
}

/**
 * @brief Get field Motor_encoder_type from appencoderconfig message
 *
 * @return  
 */
static inline uint8_t mavlink_msg_appencoderconfig_get_Motor_encoder_type(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  40);
}

/**
 * @brief Get field Load_encoder_type from appencoderconfig message
 *
 * @return  
 */
static inline uint8_t mavlink_msg_appencoderconfig_get_Load_encoder_type(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  41);
}

/**
 * @brief Get field Motor_encoder_options from appencoderconfig message
 *
 * @return  
 */
static inline uint8_t mavlink_msg_appencoderconfig_get_Motor_encoder_options(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  42);
}

/**
 * @brief Get field Load_pps_2_rpm from appencoderconfig message
 *
 * @return  
 */
static inline float mavlink_msg_appencoderconfig_get_Load_pps_2_rpm(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field Load_rpm_2_pps from appencoderconfig message
 *
 * @return  
 */
static inline float mavlink_msg_appencoderconfig_get_Load_rpm_2_pps(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Get field Motor_pps_2_rpm from appencoderconfig message
 *
 * @return  
 */
static inline float mavlink_msg_appencoderconfig_get_Motor_pps_2_rpm(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  16);
}

/**
 * @brief Get field Motor_rpm_2_pps from appencoderconfig message
 *
 * @return  
 */
static inline float mavlink_msg_appencoderconfig_get_Motor_rpm_2_pps(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  20);
}

/**
 * @brief Get field P_load_2_motor from appencoderconfig message
 *
 * @return  
 */
static inline float mavlink_msg_appencoderconfig_get_P_load_2_motor(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  24);
}

/**
 * @brief Get field P_motor_2_load from appencoderconfig message
 *
 * @return  
 */
static inline float mavlink_msg_appencoderconfig_get_P_motor_2_load(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  28);
}

/**
 * @brief Get field Load_control_resolution from appencoderconfig message
 *
 * @return  
 */
static inline uint32_t mavlink_msg_appencoderconfig_get_Load_control_resolution(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  32);
}

/**
 * @brief Get field Motor_control_resolution from appencoderconfig message
 *
 * @return  
 */
static inline uint32_t mavlink_msg_appencoderconfig_get_Motor_control_resolution(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  36);
}

/**
 * @brief Get field Load_encoder_options from appencoderconfig message
 *
 * @return  
 */
static inline uint8_t mavlink_msg_appencoderconfig_get_Load_encoder_options(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  43);
}

/**
 * @brief Decode a appencoderconfig message into a struct
 *
 * @param msg The message to decode
 * @param appencoderconfig C-struct to decode the message contents into
 */
static inline void mavlink_msg_appencoderconfig_decode(const mavlink_message_t* msg, mavlink_appencoderconfig_t* appencoderconfig)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    appencoderconfig->Load_encoder_resolution = mavlink_msg_appencoderconfig_get_Load_encoder_resolution(msg);
    appencoderconfig->Motor_encoder_resolution = mavlink_msg_appencoderconfig_get_Motor_encoder_resolution(msg);
    appencoderconfig->Load_pps_2_rpm = mavlink_msg_appencoderconfig_get_Load_pps_2_rpm(msg);
    appencoderconfig->Load_rpm_2_pps = mavlink_msg_appencoderconfig_get_Load_rpm_2_pps(msg);
    appencoderconfig->Motor_pps_2_rpm = mavlink_msg_appencoderconfig_get_Motor_pps_2_rpm(msg);
    appencoderconfig->Motor_rpm_2_pps = mavlink_msg_appencoderconfig_get_Motor_rpm_2_pps(msg);
    appencoderconfig->P_load_2_motor = mavlink_msg_appencoderconfig_get_P_load_2_motor(msg);
    appencoderconfig->P_motor_2_load = mavlink_msg_appencoderconfig_get_P_motor_2_load(msg);
    appencoderconfig->Load_control_resolution = mavlink_msg_appencoderconfig_get_Load_control_resolution(msg);
    appencoderconfig->Motor_control_resolution = mavlink_msg_appencoderconfig_get_Motor_control_resolution(msg);
    appencoderconfig->Motor_encoder_type = mavlink_msg_appencoderconfig_get_Motor_encoder_type(msg);
    appencoderconfig->Load_encoder_type = mavlink_msg_appencoderconfig_get_Load_encoder_type(msg);
    appencoderconfig->Motor_encoder_options = mavlink_msg_appencoderconfig_get_Motor_encoder_options(msg);
    appencoderconfig->Load_encoder_options = mavlink_msg_appencoderconfig_get_Load_encoder_options(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_AppEncoderConfig_LEN? msg->len : MAVLINK_MSG_ID_AppEncoderConfig_LEN;
        memset(appencoderconfig, 0, MAVLINK_MSG_ID_AppEncoderConfig_LEN);
    memcpy(appencoderconfig, _MAV_PAYLOAD(msg), len);
#endif
}
