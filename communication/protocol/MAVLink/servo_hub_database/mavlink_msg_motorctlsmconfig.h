#pragma once
// MESSAGE MotorCtlSmConfig PACKING

#define MAVLINK_MSG_ID_MotorCtlSmConfig 30022


typedef struct __mavlink_motorctlsmconfig_t {
 float under_voltage_protection_V; /*<  */
 float over_voltage_protection_V; /*<  */
 float over_speed_protection_rad_s; /*<  */
 float under_temperature_protection_d; /*<  */
 float over_temperature_protection_d; /*<  */
 int32_t position_following_error_protection; /*<  */
 uint32_t error_enable; /*<  */
 float over_current_protection_A; /*<  */
 int8_t mode; /*<  */
} mavlink_motorctlsmconfig_t;

#define MAVLINK_MSG_ID_MotorCtlSmConfig_LEN 33
#define MAVLINK_MSG_ID_MotorCtlSmConfig_MIN_LEN 33
#define MAVLINK_MSG_ID_30022_LEN 33
#define MAVLINK_MSG_ID_30022_MIN_LEN 33

#define MAVLINK_MSG_ID_MotorCtlSmConfig_CRC 124
#define MAVLINK_MSG_ID_30022_CRC 124



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_MotorCtlSmConfig { \
    30022, \
    "MotorCtlSmConfig", \
    9, \
    {  { "mode", NULL, MAVLINK_TYPE_INT8_T, 0, 32, offsetof(mavlink_motorctlsmconfig_t, mode) }, \
         { "under_voltage_protection_V", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_motorctlsmconfig_t, under_voltage_protection_V) }, \
         { "over_voltage_protection_V", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_motorctlsmconfig_t, over_voltage_protection_V) }, \
         { "over_speed_protection_rad_s", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_motorctlsmconfig_t, over_speed_protection_rad_s) }, \
         { "under_temperature_protection_d", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_motorctlsmconfig_t, under_temperature_protection_d) }, \
         { "over_temperature_protection_d", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_motorctlsmconfig_t, over_temperature_protection_d) }, \
         { "position_following_error_protection", NULL, MAVLINK_TYPE_INT32_T, 0, 20, offsetof(mavlink_motorctlsmconfig_t, position_following_error_protection) }, \
         { "error_enable", NULL, MAVLINK_TYPE_UINT32_T, 0, 24, offsetof(mavlink_motorctlsmconfig_t, error_enable) }, \
         { "over_current_protection_A", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_motorctlsmconfig_t, over_current_protection_A) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_MotorCtlSmConfig { \
    "MotorCtlSmConfig", \
    9, \
    {  { "mode", NULL, MAVLINK_TYPE_INT8_T, 0, 32, offsetof(mavlink_motorctlsmconfig_t, mode) }, \
         { "under_voltage_protection_V", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_motorctlsmconfig_t, under_voltage_protection_V) }, \
         { "over_voltage_protection_V", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_motorctlsmconfig_t, over_voltage_protection_V) }, \
         { "over_speed_protection_rad_s", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_motorctlsmconfig_t, over_speed_protection_rad_s) }, \
         { "under_temperature_protection_d", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_motorctlsmconfig_t, under_temperature_protection_d) }, \
         { "over_temperature_protection_d", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_motorctlsmconfig_t, over_temperature_protection_d) }, \
         { "position_following_error_protection", NULL, MAVLINK_TYPE_INT32_T, 0, 20, offsetof(mavlink_motorctlsmconfig_t, position_following_error_protection) }, \
         { "error_enable", NULL, MAVLINK_TYPE_UINT32_T, 0, 24, offsetof(mavlink_motorctlsmconfig_t, error_enable) }, \
         { "over_current_protection_A", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_motorctlsmconfig_t, over_current_protection_A) }, \
         } \
}
#endif

/**
 * @brief Pack a motorctlsmconfig message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param mode  
 * @param under_voltage_protection_V  
 * @param over_voltage_protection_V  
 * @param over_speed_protection_rad_s  
 * @param under_temperature_protection_d  
 * @param over_temperature_protection_d  
 * @param position_following_error_protection  
 * @param error_enable  
 * @param over_current_protection_A  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_motorctlsmconfig_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               int8_t mode, float under_voltage_protection_V, float over_voltage_protection_V, float over_speed_protection_rad_s, float under_temperature_protection_d, float over_temperature_protection_d, int32_t position_following_error_protection, uint32_t error_enable, float over_current_protection_A)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MotorCtlSmConfig_LEN];
    _mav_put_float(buf, 0, under_voltage_protection_V);
    _mav_put_float(buf, 4, over_voltage_protection_V);
    _mav_put_float(buf, 8, over_speed_protection_rad_s);
    _mav_put_float(buf, 12, under_temperature_protection_d);
    _mav_put_float(buf, 16, over_temperature_protection_d);
    _mav_put_int32_t(buf, 20, position_following_error_protection);
    _mav_put_uint32_t(buf, 24, error_enable);
    _mav_put_float(buf, 28, over_current_protection_A);
    _mav_put_int8_t(buf, 32, mode);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MotorCtlSmConfig_LEN);
#else
    mavlink_motorctlsmconfig_t packet;
    packet.under_voltage_protection_V = under_voltage_protection_V;
    packet.over_voltage_protection_V = over_voltage_protection_V;
    packet.over_speed_protection_rad_s = over_speed_protection_rad_s;
    packet.under_temperature_protection_d = under_temperature_protection_d;
    packet.over_temperature_protection_d = over_temperature_protection_d;
    packet.position_following_error_protection = position_following_error_protection;
    packet.error_enable = error_enable;
    packet.over_current_protection_A = over_current_protection_A;
    packet.mode = mode;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MotorCtlSmConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MotorCtlSmConfig;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_MotorCtlSmConfig_MIN_LEN, MAVLINK_MSG_ID_MotorCtlSmConfig_LEN, MAVLINK_MSG_ID_MotorCtlSmConfig_CRC);
}

/**
 * @brief Pack a motorctlsmconfig message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param mode  
 * @param under_voltage_protection_V  
 * @param over_voltage_protection_V  
 * @param over_speed_protection_rad_s  
 * @param under_temperature_protection_d  
 * @param over_temperature_protection_d  
 * @param position_following_error_protection  
 * @param error_enable  
 * @param over_current_protection_A  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_motorctlsmconfig_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               int8_t mode, float under_voltage_protection_V, float over_voltage_protection_V, float over_speed_protection_rad_s, float under_temperature_protection_d, float over_temperature_protection_d, int32_t position_following_error_protection, uint32_t error_enable, float over_current_protection_A)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MotorCtlSmConfig_LEN];
    _mav_put_float(buf, 0, under_voltage_protection_V);
    _mav_put_float(buf, 4, over_voltage_protection_V);
    _mav_put_float(buf, 8, over_speed_protection_rad_s);
    _mav_put_float(buf, 12, under_temperature_protection_d);
    _mav_put_float(buf, 16, over_temperature_protection_d);
    _mav_put_int32_t(buf, 20, position_following_error_protection);
    _mav_put_uint32_t(buf, 24, error_enable);
    _mav_put_float(buf, 28, over_current_protection_A);
    _mav_put_int8_t(buf, 32, mode);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MotorCtlSmConfig_LEN);
#else
    mavlink_motorctlsmconfig_t packet;
    packet.under_voltage_protection_V = under_voltage_protection_V;
    packet.over_voltage_protection_V = over_voltage_protection_V;
    packet.over_speed_protection_rad_s = over_speed_protection_rad_s;
    packet.under_temperature_protection_d = under_temperature_protection_d;
    packet.over_temperature_protection_d = over_temperature_protection_d;
    packet.position_following_error_protection = position_following_error_protection;
    packet.error_enable = error_enable;
    packet.over_current_protection_A = over_current_protection_A;
    packet.mode = mode;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MotorCtlSmConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MotorCtlSmConfig;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_MotorCtlSmConfig_MIN_LEN, MAVLINK_MSG_ID_MotorCtlSmConfig_LEN, MAVLINK_MSG_ID_MotorCtlSmConfig_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_MotorCtlSmConfig_MIN_LEN, MAVLINK_MSG_ID_MotorCtlSmConfig_LEN);
#endif
}

/**
 * @brief Pack a motorctlsmconfig message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param mode  
 * @param under_voltage_protection_V  
 * @param over_voltage_protection_V  
 * @param over_speed_protection_rad_s  
 * @param under_temperature_protection_d  
 * @param over_temperature_protection_d  
 * @param position_following_error_protection  
 * @param error_enable  
 * @param over_current_protection_A  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_motorctlsmconfig_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   int8_t mode,float under_voltage_protection_V,float over_voltage_protection_V,float over_speed_protection_rad_s,float under_temperature_protection_d,float over_temperature_protection_d,int32_t position_following_error_protection,uint32_t error_enable,float over_current_protection_A)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MotorCtlSmConfig_LEN];
    _mav_put_float(buf, 0, under_voltage_protection_V);
    _mav_put_float(buf, 4, over_voltage_protection_V);
    _mav_put_float(buf, 8, over_speed_protection_rad_s);
    _mav_put_float(buf, 12, under_temperature_protection_d);
    _mav_put_float(buf, 16, over_temperature_protection_d);
    _mav_put_int32_t(buf, 20, position_following_error_protection);
    _mav_put_uint32_t(buf, 24, error_enable);
    _mav_put_float(buf, 28, over_current_protection_A);
    _mav_put_int8_t(buf, 32, mode);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MotorCtlSmConfig_LEN);
#else
    mavlink_motorctlsmconfig_t packet;
    packet.under_voltage_protection_V = under_voltage_protection_V;
    packet.over_voltage_protection_V = over_voltage_protection_V;
    packet.over_speed_protection_rad_s = over_speed_protection_rad_s;
    packet.under_temperature_protection_d = under_temperature_protection_d;
    packet.over_temperature_protection_d = over_temperature_protection_d;
    packet.position_following_error_protection = position_following_error_protection;
    packet.error_enable = error_enable;
    packet.over_current_protection_A = over_current_protection_A;
    packet.mode = mode;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MotorCtlSmConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MotorCtlSmConfig;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_MotorCtlSmConfig_MIN_LEN, MAVLINK_MSG_ID_MotorCtlSmConfig_LEN, MAVLINK_MSG_ID_MotorCtlSmConfig_CRC);
}

/**
 * @brief Encode a motorctlsmconfig struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param motorctlsmconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_motorctlsmconfig_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_motorctlsmconfig_t* motorctlsmconfig)
{
    return mavlink_msg_motorctlsmconfig_pack(system_id, component_id, msg, motorctlsmconfig->mode, motorctlsmconfig->under_voltage_protection_V, motorctlsmconfig->over_voltage_protection_V, motorctlsmconfig->over_speed_protection_rad_s, motorctlsmconfig->under_temperature_protection_d, motorctlsmconfig->over_temperature_protection_d, motorctlsmconfig->position_following_error_protection, motorctlsmconfig->error_enable, motorctlsmconfig->over_current_protection_A);
}

/**
 * @brief Encode a motorctlsmconfig struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param motorctlsmconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_motorctlsmconfig_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_motorctlsmconfig_t* motorctlsmconfig)
{
    return mavlink_msg_motorctlsmconfig_pack_chan(system_id, component_id, chan, msg, motorctlsmconfig->mode, motorctlsmconfig->under_voltage_protection_V, motorctlsmconfig->over_voltage_protection_V, motorctlsmconfig->over_speed_protection_rad_s, motorctlsmconfig->under_temperature_protection_d, motorctlsmconfig->over_temperature_protection_d, motorctlsmconfig->position_following_error_protection, motorctlsmconfig->error_enable, motorctlsmconfig->over_current_protection_A);
}

/**
 * @brief Encode a motorctlsmconfig struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param motorctlsmconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_motorctlsmconfig_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_motorctlsmconfig_t* motorctlsmconfig)
{
    return mavlink_msg_motorctlsmconfig_pack_status(system_id, component_id, _status, msg,  motorctlsmconfig->mode, motorctlsmconfig->under_voltage_protection_V, motorctlsmconfig->over_voltage_protection_V, motorctlsmconfig->over_speed_protection_rad_s, motorctlsmconfig->under_temperature_protection_d, motorctlsmconfig->over_temperature_protection_d, motorctlsmconfig->position_following_error_protection, motorctlsmconfig->error_enable, motorctlsmconfig->over_current_protection_A);
}

/**
 * @brief Send a motorctlsmconfig message
 * @param chan MAVLink channel to send the message
 *
 * @param mode  
 * @param under_voltage_protection_V  
 * @param over_voltage_protection_V  
 * @param over_speed_protection_rad_s  
 * @param under_temperature_protection_d  
 * @param over_temperature_protection_d  
 * @param position_following_error_protection  
 * @param error_enable  
 * @param over_current_protection_A  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_motorctlsmconfig_send(mavlink_channel_t chan, int8_t mode, float under_voltage_protection_V, float over_voltage_protection_V, float over_speed_protection_rad_s, float under_temperature_protection_d, float over_temperature_protection_d, int32_t position_following_error_protection, uint32_t error_enable, float over_current_protection_A)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MotorCtlSmConfig_LEN];
    _mav_put_float(buf, 0, under_voltage_protection_V);
    _mav_put_float(buf, 4, over_voltage_protection_V);
    _mav_put_float(buf, 8, over_speed_protection_rad_s);
    _mav_put_float(buf, 12, under_temperature_protection_d);
    _mav_put_float(buf, 16, over_temperature_protection_d);
    _mav_put_int32_t(buf, 20, position_following_error_protection);
    _mav_put_uint32_t(buf, 24, error_enable);
    _mav_put_float(buf, 28, over_current_protection_A);
    _mav_put_int8_t(buf, 32, mode);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MotorCtlSmConfig, buf, MAVLINK_MSG_ID_MotorCtlSmConfig_MIN_LEN, MAVLINK_MSG_ID_MotorCtlSmConfig_LEN, MAVLINK_MSG_ID_MotorCtlSmConfig_CRC);
#else
    mavlink_motorctlsmconfig_t packet;
    packet.under_voltage_protection_V = under_voltage_protection_V;
    packet.over_voltage_protection_V = over_voltage_protection_V;
    packet.over_speed_protection_rad_s = over_speed_protection_rad_s;
    packet.under_temperature_protection_d = under_temperature_protection_d;
    packet.over_temperature_protection_d = over_temperature_protection_d;
    packet.position_following_error_protection = position_following_error_protection;
    packet.error_enable = error_enable;
    packet.over_current_protection_A = over_current_protection_A;
    packet.mode = mode;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MotorCtlSmConfig, (const char *)&packet, MAVLINK_MSG_ID_MotorCtlSmConfig_MIN_LEN, MAVLINK_MSG_ID_MotorCtlSmConfig_LEN, MAVLINK_MSG_ID_MotorCtlSmConfig_CRC);
#endif
}

/**
 * @brief Send a motorctlsmconfig message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_motorctlsmconfig_send_struct(mavlink_channel_t chan, const mavlink_motorctlsmconfig_t* motorctlsmconfig)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_motorctlsmconfig_send(chan, motorctlsmconfig->mode, motorctlsmconfig->under_voltage_protection_V, motorctlsmconfig->over_voltage_protection_V, motorctlsmconfig->over_speed_protection_rad_s, motorctlsmconfig->under_temperature_protection_d, motorctlsmconfig->over_temperature_protection_d, motorctlsmconfig->position_following_error_protection, motorctlsmconfig->error_enable, motorctlsmconfig->over_current_protection_A);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MotorCtlSmConfig, (const char *)motorctlsmconfig, MAVLINK_MSG_ID_MotorCtlSmConfig_MIN_LEN, MAVLINK_MSG_ID_MotorCtlSmConfig_LEN, MAVLINK_MSG_ID_MotorCtlSmConfig_CRC);
#endif
}

#if MAVLINK_MSG_ID_MotorCtlSmConfig_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_motorctlsmconfig_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  int8_t mode, float under_voltage_protection_V, float over_voltage_protection_V, float over_speed_protection_rad_s, float under_temperature_protection_d, float over_temperature_protection_d, int32_t position_following_error_protection, uint32_t error_enable, float over_current_protection_A)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, under_voltage_protection_V);
    _mav_put_float(buf, 4, over_voltage_protection_V);
    _mav_put_float(buf, 8, over_speed_protection_rad_s);
    _mav_put_float(buf, 12, under_temperature_protection_d);
    _mav_put_float(buf, 16, over_temperature_protection_d);
    _mav_put_int32_t(buf, 20, position_following_error_protection);
    _mav_put_uint32_t(buf, 24, error_enable);
    _mav_put_float(buf, 28, over_current_protection_A);
    _mav_put_int8_t(buf, 32, mode);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MotorCtlSmConfig, buf, MAVLINK_MSG_ID_MotorCtlSmConfig_MIN_LEN, MAVLINK_MSG_ID_MotorCtlSmConfig_LEN, MAVLINK_MSG_ID_MotorCtlSmConfig_CRC);
#else
    mavlink_motorctlsmconfig_t *packet = (mavlink_motorctlsmconfig_t *)msgbuf;
    packet->under_voltage_protection_V = under_voltage_protection_V;
    packet->over_voltage_protection_V = over_voltage_protection_V;
    packet->over_speed_protection_rad_s = over_speed_protection_rad_s;
    packet->under_temperature_protection_d = under_temperature_protection_d;
    packet->over_temperature_protection_d = over_temperature_protection_d;
    packet->position_following_error_protection = position_following_error_protection;
    packet->error_enable = error_enable;
    packet->over_current_protection_A = over_current_protection_A;
    packet->mode = mode;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MotorCtlSmConfig, (const char *)packet, MAVLINK_MSG_ID_MotorCtlSmConfig_MIN_LEN, MAVLINK_MSG_ID_MotorCtlSmConfig_LEN, MAVLINK_MSG_ID_MotorCtlSmConfig_CRC);
#endif
}
#endif

#endif

// MESSAGE MotorCtlSmConfig UNPACKING


/**
 * @brief Get field mode from motorctlsmconfig message
 *
 * @return  
 */
static inline int8_t mavlink_msg_motorctlsmconfig_get_mode(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int8_t(msg,  32);
}

/**
 * @brief Get field under_voltage_protection_V from motorctlsmconfig message
 *
 * @return  
 */
static inline float mavlink_msg_motorctlsmconfig_get_under_voltage_protection_V(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field over_voltage_protection_V from motorctlsmconfig message
 *
 * @return  
 */
static inline float mavlink_msg_motorctlsmconfig_get_over_voltage_protection_V(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field over_speed_protection_rad_s from motorctlsmconfig message
 *
 * @return  
 */
static inline float mavlink_msg_motorctlsmconfig_get_over_speed_protection_rad_s(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field under_temperature_protection_d from motorctlsmconfig message
 *
 * @return  
 */
static inline float mavlink_msg_motorctlsmconfig_get_under_temperature_protection_d(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Get field over_temperature_protection_d from motorctlsmconfig message
 *
 * @return  
 */
static inline float mavlink_msg_motorctlsmconfig_get_over_temperature_protection_d(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  16);
}

/**
 * @brief Get field position_following_error_protection from motorctlsmconfig message
 *
 * @return  
 */
static inline int32_t mavlink_msg_motorctlsmconfig_get_position_following_error_protection(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  20);
}

/**
 * @brief Get field error_enable from motorctlsmconfig message
 *
 * @return  
 */
static inline uint32_t mavlink_msg_motorctlsmconfig_get_error_enable(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  24);
}

/**
 * @brief Get field over_current_protection_A from motorctlsmconfig message
 *
 * @return  
 */
static inline float mavlink_msg_motorctlsmconfig_get_over_current_protection_A(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  28);
}

/**
 * @brief Decode a motorctlsmconfig message into a struct
 *
 * @param msg The message to decode
 * @param motorctlsmconfig C-struct to decode the message contents into
 */
static inline void mavlink_msg_motorctlsmconfig_decode(const mavlink_message_t* msg, mavlink_motorctlsmconfig_t* motorctlsmconfig)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    motorctlsmconfig->under_voltage_protection_V = mavlink_msg_motorctlsmconfig_get_under_voltage_protection_V(msg);
    motorctlsmconfig->over_voltage_protection_V = mavlink_msg_motorctlsmconfig_get_over_voltage_protection_V(msg);
    motorctlsmconfig->over_speed_protection_rad_s = mavlink_msg_motorctlsmconfig_get_over_speed_protection_rad_s(msg);
    motorctlsmconfig->under_temperature_protection_d = mavlink_msg_motorctlsmconfig_get_under_temperature_protection_d(msg);
    motorctlsmconfig->over_temperature_protection_d = mavlink_msg_motorctlsmconfig_get_over_temperature_protection_d(msg);
    motorctlsmconfig->position_following_error_protection = mavlink_msg_motorctlsmconfig_get_position_following_error_protection(msg);
    motorctlsmconfig->error_enable = mavlink_msg_motorctlsmconfig_get_error_enable(msg);
    motorctlsmconfig->over_current_protection_A = mavlink_msg_motorctlsmconfig_get_over_current_protection_A(msg);
    motorctlsmconfig->mode = mavlink_msg_motorctlsmconfig_get_mode(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_MotorCtlSmConfig_LEN? msg->len : MAVLINK_MSG_ID_MotorCtlSmConfig_LEN;
        memset(motorctlsmconfig, 0, MAVLINK_MSG_ID_MotorCtlSmConfig_LEN);
    memcpy(motorctlsmconfig, _MAV_PAYLOAD(msg), len);
#endif
}
