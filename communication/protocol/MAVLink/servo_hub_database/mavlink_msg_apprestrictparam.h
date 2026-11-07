#pragma once
// MESSAGE AppRestrictParam PACKING

#define MAVLINK_MSG_ID_AppRestrictParam 30060


typedef struct __mavlink_apprestrictparam_t {
 int64_t Position_range_limit_Minimal_position_limit; /*<  */
 int64_t Position_range_limit_Maximal_position_limit; /*<  */
 int64_t Software_position_limit_Minimal_position_limit; /*<  */
 int64_t Software_position_limit_Maximal_position_limit; /*<  */
 float Max_profile_velocity; /*<  */
 float Max_motor_speed; /*<  */
 float Max_acceleration; /*<  */
 float Max_deceleration; /*<  */
 float Max_current; /*<  */
 uint8_t Position_limit_enable; /*<  */
} mavlink_apprestrictparam_t;

#define MAVLINK_MSG_ID_AppRestrictParam_LEN 53
#define MAVLINK_MSG_ID_AppRestrictParam_MIN_LEN 53
#define MAVLINK_MSG_ID_30060_LEN 53
#define MAVLINK_MSG_ID_30060_MIN_LEN 53

#define MAVLINK_MSG_ID_AppRestrictParam_CRC 34
#define MAVLINK_MSG_ID_30060_CRC 34



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_AppRestrictParam { \
    30060, \
    "AppRestrictParam", \
    10, \
    {  { "Position_range_limit_Minimal_position_limit", NULL, MAVLINK_TYPE_INT64_T, 0, 0, offsetof(mavlink_apprestrictparam_t, Position_range_limit_Minimal_position_limit) }, \
         { "Position_range_limit_Maximal_position_limit", NULL, MAVLINK_TYPE_INT64_T, 0, 8, offsetof(mavlink_apprestrictparam_t, Position_range_limit_Maximal_position_limit) }, \
         { "Software_position_limit_Minimal_position_limit", NULL, MAVLINK_TYPE_INT64_T, 0, 16, offsetof(mavlink_apprestrictparam_t, Software_position_limit_Minimal_position_limit) }, \
         { "Software_position_limit_Maximal_position_limit", NULL, MAVLINK_TYPE_INT64_T, 0, 24, offsetof(mavlink_apprestrictparam_t, Software_position_limit_Maximal_position_limit) }, \
         { "Max_profile_velocity", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_apprestrictparam_t, Max_profile_velocity) }, \
         { "Max_motor_speed", NULL, MAVLINK_TYPE_FLOAT, 0, 36, offsetof(mavlink_apprestrictparam_t, Max_motor_speed) }, \
         { "Max_acceleration", NULL, MAVLINK_TYPE_FLOAT, 0, 40, offsetof(mavlink_apprestrictparam_t, Max_acceleration) }, \
         { "Max_deceleration", NULL, MAVLINK_TYPE_FLOAT, 0, 44, offsetof(mavlink_apprestrictparam_t, Max_deceleration) }, \
         { "Max_current", NULL, MAVLINK_TYPE_FLOAT, 0, 48, offsetof(mavlink_apprestrictparam_t, Max_current) }, \
         { "Position_limit_enable", NULL, MAVLINK_TYPE_UINT8_T, 0, 52, offsetof(mavlink_apprestrictparam_t, Position_limit_enable) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_AppRestrictParam { \
    "AppRestrictParam", \
    10, \
    {  { "Position_range_limit_Minimal_position_limit", NULL, MAVLINK_TYPE_INT64_T, 0, 0, offsetof(mavlink_apprestrictparam_t, Position_range_limit_Minimal_position_limit) }, \
         { "Position_range_limit_Maximal_position_limit", NULL, MAVLINK_TYPE_INT64_T, 0, 8, offsetof(mavlink_apprestrictparam_t, Position_range_limit_Maximal_position_limit) }, \
         { "Software_position_limit_Minimal_position_limit", NULL, MAVLINK_TYPE_INT64_T, 0, 16, offsetof(mavlink_apprestrictparam_t, Software_position_limit_Minimal_position_limit) }, \
         { "Software_position_limit_Maximal_position_limit", NULL, MAVLINK_TYPE_INT64_T, 0, 24, offsetof(mavlink_apprestrictparam_t, Software_position_limit_Maximal_position_limit) }, \
         { "Max_profile_velocity", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_apprestrictparam_t, Max_profile_velocity) }, \
         { "Max_motor_speed", NULL, MAVLINK_TYPE_FLOAT, 0, 36, offsetof(mavlink_apprestrictparam_t, Max_motor_speed) }, \
         { "Max_acceleration", NULL, MAVLINK_TYPE_FLOAT, 0, 40, offsetof(mavlink_apprestrictparam_t, Max_acceleration) }, \
         { "Max_deceleration", NULL, MAVLINK_TYPE_FLOAT, 0, 44, offsetof(mavlink_apprestrictparam_t, Max_deceleration) }, \
         { "Max_current", NULL, MAVLINK_TYPE_FLOAT, 0, 48, offsetof(mavlink_apprestrictparam_t, Max_current) }, \
         { "Position_limit_enable", NULL, MAVLINK_TYPE_UINT8_T, 0, 52, offsetof(mavlink_apprestrictparam_t, Position_limit_enable) }, \
         } \
}
#endif

/**
 * @brief Pack a apprestrictparam message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param Position_range_limit_Minimal_position_limit  
 * @param Position_range_limit_Maximal_position_limit  
 * @param Software_position_limit_Minimal_position_limit  
 * @param Software_position_limit_Maximal_position_limit  
 * @param Max_profile_velocity  
 * @param Max_motor_speed  
 * @param Max_acceleration  
 * @param Max_deceleration  
 * @param Max_current  
 * @param Position_limit_enable  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_apprestrictparam_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               int64_t Position_range_limit_Minimal_position_limit, int64_t Position_range_limit_Maximal_position_limit, int64_t Software_position_limit_Minimal_position_limit, int64_t Software_position_limit_Maximal_position_limit, float Max_profile_velocity, float Max_motor_speed, float Max_acceleration, float Max_deceleration, float Max_current, uint8_t Position_limit_enable)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_AppRestrictParam_LEN];
    _mav_put_int64_t(buf, 0, Position_range_limit_Minimal_position_limit);
    _mav_put_int64_t(buf, 8, Position_range_limit_Maximal_position_limit);
    _mav_put_int64_t(buf, 16, Software_position_limit_Minimal_position_limit);
    _mav_put_int64_t(buf, 24, Software_position_limit_Maximal_position_limit);
    _mav_put_float(buf, 32, Max_profile_velocity);
    _mav_put_float(buf, 36, Max_motor_speed);
    _mav_put_float(buf, 40, Max_acceleration);
    _mav_put_float(buf, 44, Max_deceleration);
    _mav_put_float(buf, 48, Max_current);
    _mav_put_uint8_t(buf, 52, Position_limit_enable);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_AppRestrictParam_LEN);
#else
    mavlink_apprestrictparam_t packet;
    packet.Position_range_limit_Minimal_position_limit = Position_range_limit_Minimal_position_limit;
    packet.Position_range_limit_Maximal_position_limit = Position_range_limit_Maximal_position_limit;
    packet.Software_position_limit_Minimal_position_limit = Software_position_limit_Minimal_position_limit;
    packet.Software_position_limit_Maximal_position_limit = Software_position_limit_Maximal_position_limit;
    packet.Max_profile_velocity = Max_profile_velocity;
    packet.Max_motor_speed = Max_motor_speed;
    packet.Max_acceleration = Max_acceleration;
    packet.Max_deceleration = Max_deceleration;
    packet.Max_current = Max_current;
    packet.Position_limit_enable = Position_limit_enable;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_AppRestrictParam_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_AppRestrictParam;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_AppRestrictParam_MIN_LEN, MAVLINK_MSG_ID_AppRestrictParam_LEN, MAVLINK_MSG_ID_AppRestrictParam_CRC);
}

/**
 * @brief Pack a apprestrictparam message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param Position_range_limit_Minimal_position_limit  
 * @param Position_range_limit_Maximal_position_limit  
 * @param Software_position_limit_Minimal_position_limit  
 * @param Software_position_limit_Maximal_position_limit  
 * @param Max_profile_velocity  
 * @param Max_motor_speed  
 * @param Max_acceleration  
 * @param Max_deceleration  
 * @param Max_current  
 * @param Position_limit_enable  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_apprestrictparam_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               int64_t Position_range_limit_Minimal_position_limit, int64_t Position_range_limit_Maximal_position_limit, int64_t Software_position_limit_Minimal_position_limit, int64_t Software_position_limit_Maximal_position_limit, float Max_profile_velocity, float Max_motor_speed, float Max_acceleration, float Max_deceleration, float Max_current, uint8_t Position_limit_enable)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_AppRestrictParam_LEN];
    _mav_put_int64_t(buf, 0, Position_range_limit_Minimal_position_limit);
    _mav_put_int64_t(buf, 8, Position_range_limit_Maximal_position_limit);
    _mav_put_int64_t(buf, 16, Software_position_limit_Minimal_position_limit);
    _mav_put_int64_t(buf, 24, Software_position_limit_Maximal_position_limit);
    _mav_put_float(buf, 32, Max_profile_velocity);
    _mav_put_float(buf, 36, Max_motor_speed);
    _mav_put_float(buf, 40, Max_acceleration);
    _mav_put_float(buf, 44, Max_deceleration);
    _mav_put_float(buf, 48, Max_current);
    _mav_put_uint8_t(buf, 52, Position_limit_enable);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_AppRestrictParam_LEN);
#else
    mavlink_apprestrictparam_t packet;
    packet.Position_range_limit_Minimal_position_limit = Position_range_limit_Minimal_position_limit;
    packet.Position_range_limit_Maximal_position_limit = Position_range_limit_Maximal_position_limit;
    packet.Software_position_limit_Minimal_position_limit = Software_position_limit_Minimal_position_limit;
    packet.Software_position_limit_Maximal_position_limit = Software_position_limit_Maximal_position_limit;
    packet.Max_profile_velocity = Max_profile_velocity;
    packet.Max_motor_speed = Max_motor_speed;
    packet.Max_acceleration = Max_acceleration;
    packet.Max_deceleration = Max_deceleration;
    packet.Max_current = Max_current;
    packet.Position_limit_enable = Position_limit_enable;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_AppRestrictParam_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_AppRestrictParam;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_AppRestrictParam_MIN_LEN, MAVLINK_MSG_ID_AppRestrictParam_LEN, MAVLINK_MSG_ID_AppRestrictParam_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_AppRestrictParam_MIN_LEN, MAVLINK_MSG_ID_AppRestrictParam_LEN);
#endif
}

/**
 * @brief Pack a apprestrictparam message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param Position_range_limit_Minimal_position_limit  
 * @param Position_range_limit_Maximal_position_limit  
 * @param Software_position_limit_Minimal_position_limit  
 * @param Software_position_limit_Maximal_position_limit  
 * @param Max_profile_velocity  
 * @param Max_motor_speed  
 * @param Max_acceleration  
 * @param Max_deceleration  
 * @param Max_current  
 * @param Position_limit_enable  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_apprestrictparam_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   int64_t Position_range_limit_Minimal_position_limit,int64_t Position_range_limit_Maximal_position_limit,int64_t Software_position_limit_Minimal_position_limit,int64_t Software_position_limit_Maximal_position_limit,float Max_profile_velocity,float Max_motor_speed,float Max_acceleration,float Max_deceleration,float Max_current,uint8_t Position_limit_enable)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_AppRestrictParam_LEN];
    _mav_put_int64_t(buf, 0, Position_range_limit_Minimal_position_limit);
    _mav_put_int64_t(buf, 8, Position_range_limit_Maximal_position_limit);
    _mav_put_int64_t(buf, 16, Software_position_limit_Minimal_position_limit);
    _mav_put_int64_t(buf, 24, Software_position_limit_Maximal_position_limit);
    _mav_put_float(buf, 32, Max_profile_velocity);
    _mav_put_float(buf, 36, Max_motor_speed);
    _mav_put_float(buf, 40, Max_acceleration);
    _mav_put_float(buf, 44, Max_deceleration);
    _mav_put_float(buf, 48, Max_current);
    _mav_put_uint8_t(buf, 52, Position_limit_enable);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_AppRestrictParam_LEN);
#else
    mavlink_apprestrictparam_t packet;
    packet.Position_range_limit_Minimal_position_limit = Position_range_limit_Minimal_position_limit;
    packet.Position_range_limit_Maximal_position_limit = Position_range_limit_Maximal_position_limit;
    packet.Software_position_limit_Minimal_position_limit = Software_position_limit_Minimal_position_limit;
    packet.Software_position_limit_Maximal_position_limit = Software_position_limit_Maximal_position_limit;
    packet.Max_profile_velocity = Max_profile_velocity;
    packet.Max_motor_speed = Max_motor_speed;
    packet.Max_acceleration = Max_acceleration;
    packet.Max_deceleration = Max_deceleration;
    packet.Max_current = Max_current;
    packet.Position_limit_enable = Position_limit_enable;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_AppRestrictParam_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_AppRestrictParam;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_AppRestrictParam_MIN_LEN, MAVLINK_MSG_ID_AppRestrictParam_LEN, MAVLINK_MSG_ID_AppRestrictParam_CRC);
}

/**
 * @brief Encode a apprestrictparam struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param apprestrictparam C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_apprestrictparam_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_apprestrictparam_t* apprestrictparam)
{
    return mavlink_msg_apprestrictparam_pack(system_id, component_id, msg, apprestrictparam->Position_range_limit_Minimal_position_limit, apprestrictparam->Position_range_limit_Maximal_position_limit, apprestrictparam->Software_position_limit_Minimal_position_limit, apprestrictparam->Software_position_limit_Maximal_position_limit, apprestrictparam->Max_profile_velocity, apprestrictparam->Max_motor_speed, apprestrictparam->Max_acceleration, apprestrictparam->Max_deceleration, apprestrictparam->Max_current, apprestrictparam->Position_limit_enable);
}

/**
 * @brief Encode a apprestrictparam struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param apprestrictparam C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_apprestrictparam_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_apprestrictparam_t* apprestrictparam)
{
    return mavlink_msg_apprestrictparam_pack_chan(system_id, component_id, chan, msg, apprestrictparam->Position_range_limit_Minimal_position_limit, apprestrictparam->Position_range_limit_Maximal_position_limit, apprestrictparam->Software_position_limit_Minimal_position_limit, apprestrictparam->Software_position_limit_Maximal_position_limit, apprestrictparam->Max_profile_velocity, apprestrictparam->Max_motor_speed, apprestrictparam->Max_acceleration, apprestrictparam->Max_deceleration, apprestrictparam->Max_current, apprestrictparam->Position_limit_enable);
}

/**
 * @brief Encode a apprestrictparam struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param apprestrictparam C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_apprestrictparam_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_apprestrictparam_t* apprestrictparam)
{
    return mavlink_msg_apprestrictparam_pack_status(system_id, component_id, _status, msg,  apprestrictparam->Position_range_limit_Minimal_position_limit, apprestrictparam->Position_range_limit_Maximal_position_limit, apprestrictparam->Software_position_limit_Minimal_position_limit, apprestrictparam->Software_position_limit_Maximal_position_limit, apprestrictparam->Max_profile_velocity, apprestrictparam->Max_motor_speed, apprestrictparam->Max_acceleration, apprestrictparam->Max_deceleration, apprestrictparam->Max_current, apprestrictparam->Position_limit_enable);
}

/**
 * @brief Send a apprestrictparam message
 * @param chan MAVLink channel to send the message
 *
 * @param Position_range_limit_Minimal_position_limit  
 * @param Position_range_limit_Maximal_position_limit  
 * @param Software_position_limit_Minimal_position_limit  
 * @param Software_position_limit_Maximal_position_limit  
 * @param Max_profile_velocity  
 * @param Max_motor_speed  
 * @param Max_acceleration  
 * @param Max_deceleration  
 * @param Max_current  
 * @param Position_limit_enable  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_apprestrictparam_send(mavlink_channel_t chan, int64_t Position_range_limit_Minimal_position_limit, int64_t Position_range_limit_Maximal_position_limit, int64_t Software_position_limit_Minimal_position_limit, int64_t Software_position_limit_Maximal_position_limit, float Max_profile_velocity, float Max_motor_speed, float Max_acceleration, float Max_deceleration, float Max_current, uint8_t Position_limit_enable)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_AppRestrictParam_LEN];
    _mav_put_int64_t(buf, 0, Position_range_limit_Minimal_position_limit);
    _mav_put_int64_t(buf, 8, Position_range_limit_Maximal_position_limit);
    _mav_put_int64_t(buf, 16, Software_position_limit_Minimal_position_limit);
    _mav_put_int64_t(buf, 24, Software_position_limit_Maximal_position_limit);
    _mav_put_float(buf, 32, Max_profile_velocity);
    _mav_put_float(buf, 36, Max_motor_speed);
    _mav_put_float(buf, 40, Max_acceleration);
    _mav_put_float(buf, 44, Max_deceleration);
    _mav_put_float(buf, 48, Max_current);
    _mav_put_uint8_t(buf, 52, Position_limit_enable);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppRestrictParam, buf, MAVLINK_MSG_ID_AppRestrictParam_MIN_LEN, MAVLINK_MSG_ID_AppRestrictParam_LEN, MAVLINK_MSG_ID_AppRestrictParam_CRC);
#else
    mavlink_apprestrictparam_t packet;
    packet.Position_range_limit_Minimal_position_limit = Position_range_limit_Minimal_position_limit;
    packet.Position_range_limit_Maximal_position_limit = Position_range_limit_Maximal_position_limit;
    packet.Software_position_limit_Minimal_position_limit = Software_position_limit_Minimal_position_limit;
    packet.Software_position_limit_Maximal_position_limit = Software_position_limit_Maximal_position_limit;
    packet.Max_profile_velocity = Max_profile_velocity;
    packet.Max_motor_speed = Max_motor_speed;
    packet.Max_acceleration = Max_acceleration;
    packet.Max_deceleration = Max_deceleration;
    packet.Max_current = Max_current;
    packet.Position_limit_enable = Position_limit_enable;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppRestrictParam, (const char *)&packet, MAVLINK_MSG_ID_AppRestrictParam_MIN_LEN, MAVLINK_MSG_ID_AppRestrictParam_LEN, MAVLINK_MSG_ID_AppRestrictParam_CRC);
#endif
}

/**
 * @brief Send a apprestrictparam message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_apprestrictparam_send_struct(mavlink_channel_t chan, const mavlink_apprestrictparam_t* apprestrictparam)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_apprestrictparam_send(chan, apprestrictparam->Position_range_limit_Minimal_position_limit, apprestrictparam->Position_range_limit_Maximal_position_limit, apprestrictparam->Software_position_limit_Minimal_position_limit, apprestrictparam->Software_position_limit_Maximal_position_limit, apprestrictparam->Max_profile_velocity, apprestrictparam->Max_motor_speed, apprestrictparam->Max_acceleration, apprestrictparam->Max_deceleration, apprestrictparam->Max_current, apprestrictparam->Position_limit_enable);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppRestrictParam, (const char *)apprestrictparam, MAVLINK_MSG_ID_AppRestrictParam_MIN_LEN, MAVLINK_MSG_ID_AppRestrictParam_LEN, MAVLINK_MSG_ID_AppRestrictParam_CRC);
#endif
}

#if MAVLINK_MSG_ID_AppRestrictParam_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_apprestrictparam_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  int64_t Position_range_limit_Minimal_position_limit, int64_t Position_range_limit_Maximal_position_limit, int64_t Software_position_limit_Minimal_position_limit, int64_t Software_position_limit_Maximal_position_limit, float Max_profile_velocity, float Max_motor_speed, float Max_acceleration, float Max_deceleration, float Max_current, uint8_t Position_limit_enable)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_int64_t(buf, 0, Position_range_limit_Minimal_position_limit);
    _mav_put_int64_t(buf, 8, Position_range_limit_Maximal_position_limit);
    _mav_put_int64_t(buf, 16, Software_position_limit_Minimal_position_limit);
    _mav_put_int64_t(buf, 24, Software_position_limit_Maximal_position_limit);
    _mav_put_float(buf, 32, Max_profile_velocity);
    _mav_put_float(buf, 36, Max_motor_speed);
    _mav_put_float(buf, 40, Max_acceleration);
    _mav_put_float(buf, 44, Max_deceleration);
    _mav_put_float(buf, 48, Max_current);
    _mav_put_uint8_t(buf, 52, Position_limit_enable);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppRestrictParam, buf, MAVLINK_MSG_ID_AppRestrictParam_MIN_LEN, MAVLINK_MSG_ID_AppRestrictParam_LEN, MAVLINK_MSG_ID_AppRestrictParam_CRC);
#else
    mavlink_apprestrictparam_t *packet = (mavlink_apprestrictparam_t *)msgbuf;
    packet->Position_range_limit_Minimal_position_limit = Position_range_limit_Minimal_position_limit;
    packet->Position_range_limit_Maximal_position_limit = Position_range_limit_Maximal_position_limit;
    packet->Software_position_limit_Minimal_position_limit = Software_position_limit_Minimal_position_limit;
    packet->Software_position_limit_Maximal_position_limit = Software_position_limit_Maximal_position_limit;
    packet->Max_profile_velocity = Max_profile_velocity;
    packet->Max_motor_speed = Max_motor_speed;
    packet->Max_acceleration = Max_acceleration;
    packet->Max_deceleration = Max_deceleration;
    packet->Max_current = Max_current;
    packet->Position_limit_enable = Position_limit_enable;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppRestrictParam, (const char *)packet, MAVLINK_MSG_ID_AppRestrictParam_MIN_LEN, MAVLINK_MSG_ID_AppRestrictParam_LEN, MAVLINK_MSG_ID_AppRestrictParam_CRC);
#endif
}
#endif

#endif

// MESSAGE AppRestrictParam UNPACKING


/**
 * @brief Get field Position_range_limit_Minimal_position_limit from apprestrictparam message
 *
 * @return  
 */
static inline int64_t mavlink_msg_apprestrictparam_get_Position_range_limit_Minimal_position_limit(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int64_t(msg,  0);
}

/**
 * @brief Get field Position_range_limit_Maximal_position_limit from apprestrictparam message
 *
 * @return  
 */
static inline int64_t mavlink_msg_apprestrictparam_get_Position_range_limit_Maximal_position_limit(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int64_t(msg,  8);
}

/**
 * @brief Get field Software_position_limit_Minimal_position_limit from apprestrictparam message
 *
 * @return  
 */
static inline int64_t mavlink_msg_apprestrictparam_get_Software_position_limit_Minimal_position_limit(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int64_t(msg,  16);
}

/**
 * @brief Get field Software_position_limit_Maximal_position_limit from apprestrictparam message
 *
 * @return  
 */
static inline int64_t mavlink_msg_apprestrictparam_get_Software_position_limit_Maximal_position_limit(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int64_t(msg,  24);
}

/**
 * @brief Get field Max_profile_velocity from apprestrictparam message
 *
 * @return  
 */
static inline float mavlink_msg_apprestrictparam_get_Max_profile_velocity(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  32);
}

/**
 * @brief Get field Max_motor_speed from apprestrictparam message
 *
 * @return  
 */
static inline float mavlink_msg_apprestrictparam_get_Max_motor_speed(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  36);
}

/**
 * @brief Get field Max_acceleration from apprestrictparam message
 *
 * @return  
 */
static inline float mavlink_msg_apprestrictparam_get_Max_acceleration(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  40);
}

/**
 * @brief Get field Max_deceleration from apprestrictparam message
 *
 * @return  
 */
static inline float mavlink_msg_apprestrictparam_get_Max_deceleration(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  44);
}

/**
 * @brief Get field Max_current from apprestrictparam message
 *
 * @return  
 */
static inline float mavlink_msg_apprestrictparam_get_Max_current(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  48);
}

/**
 * @brief Get field Position_limit_enable from apprestrictparam message
 *
 * @return  
 */
static inline uint8_t mavlink_msg_apprestrictparam_get_Position_limit_enable(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  52);
}

/**
 * @brief Decode a apprestrictparam message into a struct
 *
 * @param msg The message to decode
 * @param apprestrictparam C-struct to decode the message contents into
 */
static inline void mavlink_msg_apprestrictparam_decode(const mavlink_message_t* msg, mavlink_apprestrictparam_t* apprestrictparam)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    apprestrictparam->Position_range_limit_Minimal_position_limit = mavlink_msg_apprestrictparam_get_Position_range_limit_Minimal_position_limit(msg);
    apprestrictparam->Position_range_limit_Maximal_position_limit = mavlink_msg_apprestrictparam_get_Position_range_limit_Maximal_position_limit(msg);
    apprestrictparam->Software_position_limit_Minimal_position_limit = mavlink_msg_apprestrictparam_get_Software_position_limit_Minimal_position_limit(msg);
    apprestrictparam->Software_position_limit_Maximal_position_limit = mavlink_msg_apprestrictparam_get_Software_position_limit_Maximal_position_limit(msg);
    apprestrictparam->Max_profile_velocity = mavlink_msg_apprestrictparam_get_Max_profile_velocity(msg);
    apprestrictparam->Max_motor_speed = mavlink_msg_apprestrictparam_get_Max_motor_speed(msg);
    apprestrictparam->Max_acceleration = mavlink_msg_apprestrictparam_get_Max_acceleration(msg);
    apprestrictparam->Max_deceleration = mavlink_msg_apprestrictparam_get_Max_deceleration(msg);
    apprestrictparam->Max_current = mavlink_msg_apprestrictparam_get_Max_current(msg);
    apprestrictparam->Position_limit_enable = mavlink_msg_apprestrictparam_get_Position_limit_enable(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_AppRestrictParam_LEN? msg->len : MAVLINK_MSG_ID_AppRestrictParam_LEN;
        memset(apprestrictparam, 0, MAVLINK_MSG_ID_AppRestrictParam_LEN);
    memcpy(apprestrictparam, _MAV_PAYLOAD(msg), len);
#endif
}
