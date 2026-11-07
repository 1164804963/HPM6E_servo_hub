#pragma once
// MESSAGE AppWindowParam PACKING

#define MAVLINK_MSG_ID_AppWindowParam 30062


typedef struct __mavlink_appwindowparam_t {
 int64_t Following_error_window; /*<  */
 float Following_error_time_out; /*<  */
 uint32_t Position_window; /*<  */
 float Position_window_time; /*<  */
 float Velocity_window; /*<  */
 float Velocity_window_time; /*<  */
 float Velocity_threshold; /*<  */
 float Velocity_threshold_time; /*<  */
} mavlink_appwindowparam_t;

#define MAVLINK_MSG_ID_AppWindowParam_LEN 36
#define MAVLINK_MSG_ID_AppWindowParam_MIN_LEN 36
#define MAVLINK_MSG_ID_30062_LEN 36
#define MAVLINK_MSG_ID_30062_MIN_LEN 36

#define MAVLINK_MSG_ID_AppWindowParam_CRC 162
#define MAVLINK_MSG_ID_30062_CRC 162



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_AppWindowParam { \
    30062, \
    "AppWindowParam", \
    8, \
    {  { "Following_error_window", NULL, MAVLINK_TYPE_INT64_T, 0, 0, offsetof(mavlink_appwindowparam_t, Following_error_window) }, \
         { "Following_error_time_out", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_appwindowparam_t, Following_error_time_out) }, \
         { "Position_window", NULL, MAVLINK_TYPE_UINT32_T, 0, 12, offsetof(mavlink_appwindowparam_t, Position_window) }, \
         { "Position_window_time", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_appwindowparam_t, Position_window_time) }, \
         { "Velocity_window", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_appwindowparam_t, Velocity_window) }, \
         { "Velocity_window_time", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_appwindowparam_t, Velocity_window_time) }, \
         { "Velocity_threshold", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_appwindowparam_t, Velocity_threshold) }, \
         { "Velocity_threshold_time", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_appwindowparam_t, Velocity_threshold_time) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_AppWindowParam { \
    "AppWindowParam", \
    8, \
    {  { "Following_error_window", NULL, MAVLINK_TYPE_INT64_T, 0, 0, offsetof(mavlink_appwindowparam_t, Following_error_window) }, \
         { "Following_error_time_out", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_appwindowparam_t, Following_error_time_out) }, \
         { "Position_window", NULL, MAVLINK_TYPE_UINT32_T, 0, 12, offsetof(mavlink_appwindowparam_t, Position_window) }, \
         { "Position_window_time", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_appwindowparam_t, Position_window_time) }, \
         { "Velocity_window", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_appwindowparam_t, Velocity_window) }, \
         { "Velocity_window_time", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_appwindowparam_t, Velocity_window_time) }, \
         { "Velocity_threshold", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_appwindowparam_t, Velocity_threshold) }, \
         { "Velocity_threshold_time", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_appwindowparam_t, Velocity_threshold_time) }, \
         } \
}
#endif

/**
 * @brief Pack a appwindowparam message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param Following_error_window  
 * @param Following_error_time_out  
 * @param Position_window  
 * @param Position_window_time  
 * @param Velocity_window  
 * @param Velocity_window_time  
 * @param Velocity_threshold  
 * @param Velocity_threshold_time  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_appwindowparam_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               int64_t Following_error_window, float Following_error_time_out, uint32_t Position_window, float Position_window_time, float Velocity_window, float Velocity_window_time, float Velocity_threshold, float Velocity_threshold_time)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_AppWindowParam_LEN];
    _mav_put_int64_t(buf, 0, Following_error_window);
    _mav_put_float(buf, 8, Following_error_time_out);
    _mav_put_uint32_t(buf, 12, Position_window);
    _mav_put_float(buf, 16, Position_window_time);
    _mav_put_float(buf, 20, Velocity_window);
    _mav_put_float(buf, 24, Velocity_window_time);
    _mav_put_float(buf, 28, Velocity_threshold);
    _mav_put_float(buf, 32, Velocity_threshold_time);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_AppWindowParam_LEN);
#else
    mavlink_appwindowparam_t packet;
    packet.Following_error_window = Following_error_window;
    packet.Following_error_time_out = Following_error_time_out;
    packet.Position_window = Position_window;
    packet.Position_window_time = Position_window_time;
    packet.Velocity_window = Velocity_window;
    packet.Velocity_window_time = Velocity_window_time;
    packet.Velocity_threshold = Velocity_threshold;
    packet.Velocity_threshold_time = Velocity_threshold_time;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_AppWindowParam_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_AppWindowParam;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_AppWindowParam_MIN_LEN, MAVLINK_MSG_ID_AppWindowParam_LEN, MAVLINK_MSG_ID_AppWindowParam_CRC);
}

/**
 * @brief Pack a appwindowparam message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param Following_error_window  
 * @param Following_error_time_out  
 * @param Position_window  
 * @param Position_window_time  
 * @param Velocity_window  
 * @param Velocity_window_time  
 * @param Velocity_threshold  
 * @param Velocity_threshold_time  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_appwindowparam_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               int64_t Following_error_window, float Following_error_time_out, uint32_t Position_window, float Position_window_time, float Velocity_window, float Velocity_window_time, float Velocity_threshold, float Velocity_threshold_time)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_AppWindowParam_LEN];
    _mav_put_int64_t(buf, 0, Following_error_window);
    _mav_put_float(buf, 8, Following_error_time_out);
    _mav_put_uint32_t(buf, 12, Position_window);
    _mav_put_float(buf, 16, Position_window_time);
    _mav_put_float(buf, 20, Velocity_window);
    _mav_put_float(buf, 24, Velocity_window_time);
    _mav_put_float(buf, 28, Velocity_threshold);
    _mav_put_float(buf, 32, Velocity_threshold_time);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_AppWindowParam_LEN);
#else
    mavlink_appwindowparam_t packet;
    packet.Following_error_window = Following_error_window;
    packet.Following_error_time_out = Following_error_time_out;
    packet.Position_window = Position_window;
    packet.Position_window_time = Position_window_time;
    packet.Velocity_window = Velocity_window;
    packet.Velocity_window_time = Velocity_window_time;
    packet.Velocity_threshold = Velocity_threshold;
    packet.Velocity_threshold_time = Velocity_threshold_time;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_AppWindowParam_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_AppWindowParam;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_AppWindowParam_MIN_LEN, MAVLINK_MSG_ID_AppWindowParam_LEN, MAVLINK_MSG_ID_AppWindowParam_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_AppWindowParam_MIN_LEN, MAVLINK_MSG_ID_AppWindowParam_LEN);
#endif
}

/**
 * @brief Pack a appwindowparam message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param Following_error_window  
 * @param Following_error_time_out  
 * @param Position_window  
 * @param Position_window_time  
 * @param Velocity_window  
 * @param Velocity_window_time  
 * @param Velocity_threshold  
 * @param Velocity_threshold_time  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_appwindowparam_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   int64_t Following_error_window,float Following_error_time_out,uint32_t Position_window,float Position_window_time,float Velocity_window,float Velocity_window_time,float Velocity_threshold,float Velocity_threshold_time)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_AppWindowParam_LEN];
    _mav_put_int64_t(buf, 0, Following_error_window);
    _mav_put_float(buf, 8, Following_error_time_out);
    _mav_put_uint32_t(buf, 12, Position_window);
    _mav_put_float(buf, 16, Position_window_time);
    _mav_put_float(buf, 20, Velocity_window);
    _mav_put_float(buf, 24, Velocity_window_time);
    _mav_put_float(buf, 28, Velocity_threshold);
    _mav_put_float(buf, 32, Velocity_threshold_time);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_AppWindowParam_LEN);
#else
    mavlink_appwindowparam_t packet;
    packet.Following_error_window = Following_error_window;
    packet.Following_error_time_out = Following_error_time_out;
    packet.Position_window = Position_window;
    packet.Position_window_time = Position_window_time;
    packet.Velocity_window = Velocity_window;
    packet.Velocity_window_time = Velocity_window_time;
    packet.Velocity_threshold = Velocity_threshold;
    packet.Velocity_threshold_time = Velocity_threshold_time;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_AppWindowParam_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_AppWindowParam;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_AppWindowParam_MIN_LEN, MAVLINK_MSG_ID_AppWindowParam_LEN, MAVLINK_MSG_ID_AppWindowParam_CRC);
}

/**
 * @brief Encode a appwindowparam struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param appwindowparam C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_appwindowparam_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_appwindowparam_t* appwindowparam)
{
    return mavlink_msg_appwindowparam_pack(system_id, component_id, msg, appwindowparam->Following_error_window, appwindowparam->Following_error_time_out, appwindowparam->Position_window, appwindowparam->Position_window_time, appwindowparam->Velocity_window, appwindowparam->Velocity_window_time, appwindowparam->Velocity_threshold, appwindowparam->Velocity_threshold_time);
}

/**
 * @brief Encode a appwindowparam struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param appwindowparam C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_appwindowparam_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_appwindowparam_t* appwindowparam)
{
    return mavlink_msg_appwindowparam_pack_chan(system_id, component_id, chan, msg, appwindowparam->Following_error_window, appwindowparam->Following_error_time_out, appwindowparam->Position_window, appwindowparam->Position_window_time, appwindowparam->Velocity_window, appwindowparam->Velocity_window_time, appwindowparam->Velocity_threshold, appwindowparam->Velocity_threshold_time);
}

/**
 * @brief Encode a appwindowparam struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param appwindowparam C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_appwindowparam_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_appwindowparam_t* appwindowparam)
{
    return mavlink_msg_appwindowparam_pack_status(system_id, component_id, _status, msg,  appwindowparam->Following_error_window, appwindowparam->Following_error_time_out, appwindowparam->Position_window, appwindowparam->Position_window_time, appwindowparam->Velocity_window, appwindowparam->Velocity_window_time, appwindowparam->Velocity_threshold, appwindowparam->Velocity_threshold_time);
}

/**
 * @brief Send a appwindowparam message
 * @param chan MAVLink channel to send the message
 *
 * @param Following_error_window  
 * @param Following_error_time_out  
 * @param Position_window  
 * @param Position_window_time  
 * @param Velocity_window  
 * @param Velocity_window_time  
 * @param Velocity_threshold  
 * @param Velocity_threshold_time  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_appwindowparam_send(mavlink_channel_t chan, int64_t Following_error_window, float Following_error_time_out, uint32_t Position_window, float Position_window_time, float Velocity_window, float Velocity_window_time, float Velocity_threshold, float Velocity_threshold_time)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_AppWindowParam_LEN];
    _mav_put_int64_t(buf, 0, Following_error_window);
    _mav_put_float(buf, 8, Following_error_time_out);
    _mav_put_uint32_t(buf, 12, Position_window);
    _mav_put_float(buf, 16, Position_window_time);
    _mav_put_float(buf, 20, Velocity_window);
    _mav_put_float(buf, 24, Velocity_window_time);
    _mav_put_float(buf, 28, Velocity_threshold);
    _mav_put_float(buf, 32, Velocity_threshold_time);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppWindowParam, buf, MAVLINK_MSG_ID_AppWindowParam_MIN_LEN, MAVLINK_MSG_ID_AppWindowParam_LEN, MAVLINK_MSG_ID_AppWindowParam_CRC);
#else
    mavlink_appwindowparam_t packet;
    packet.Following_error_window = Following_error_window;
    packet.Following_error_time_out = Following_error_time_out;
    packet.Position_window = Position_window;
    packet.Position_window_time = Position_window_time;
    packet.Velocity_window = Velocity_window;
    packet.Velocity_window_time = Velocity_window_time;
    packet.Velocity_threshold = Velocity_threshold;
    packet.Velocity_threshold_time = Velocity_threshold_time;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppWindowParam, (const char *)&packet, MAVLINK_MSG_ID_AppWindowParam_MIN_LEN, MAVLINK_MSG_ID_AppWindowParam_LEN, MAVLINK_MSG_ID_AppWindowParam_CRC);
#endif
}

/**
 * @brief Send a appwindowparam message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_appwindowparam_send_struct(mavlink_channel_t chan, const mavlink_appwindowparam_t* appwindowparam)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_appwindowparam_send(chan, appwindowparam->Following_error_window, appwindowparam->Following_error_time_out, appwindowparam->Position_window, appwindowparam->Position_window_time, appwindowparam->Velocity_window, appwindowparam->Velocity_window_time, appwindowparam->Velocity_threshold, appwindowparam->Velocity_threshold_time);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppWindowParam, (const char *)appwindowparam, MAVLINK_MSG_ID_AppWindowParam_MIN_LEN, MAVLINK_MSG_ID_AppWindowParam_LEN, MAVLINK_MSG_ID_AppWindowParam_CRC);
#endif
}

#if MAVLINK_MSG_ID_AppWindowParam_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_appwindowparam_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  int64_t Following_error_window, float Following_error_time_out, uint32_t Position_window, float Position_window_time, float Velocity_window, float Velocity_window_time, float Velocity_threshold, float Velocity_threshold_time)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_int64_t(buf, 0, Following_error_window);
    _mav_put_float(buf, 8, Following_error_time_out);
    _mav_put_uint32_t(buf, 12, Position_window);
    _mav_put_float(buf, 16, Position_window_time);
    _mav_put_float(buf, 20, Velocity_window);
    _mav_put_float(buf, 24, Velocity_window_time);
    _mav_put_float(buf, 28, Velocity_threshold);
    _mav_put_float(buf, 32, Velocity_threshold_time);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppWindowParam, buf, MAVLINK_MSG_ID_AppWindowParam_MIN_LEN, MAVLINK_MSG_ID_AppWindowParam_LEN, MAVLINK_MSG_ID_AppWindowParam_CRC);
#else
    mavlink_appwindowparam_t *packet = (mavlink_appwindowparam_t *)msgbuf;
    packet->Following_error_window = Following_error_window;
    packet->Following_error_time_out = Following_error_time_out;
    packet->Position_window = Position_window;
    packet->Position_window_time = Position_window_time;
    packet->Velocity_window = Velocity_window;
    packet->Velocity_window_time = Velocity_window_time;
    packet->Velocity_threshold = Velocity_threshold;
    packet->Velocity_threshold_time = Velocity_threshold_time;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppWindowParam, (const char *)packet, MAVLINK_MSG_ID_AppWindowParam_MIN_LEN, MAVLINK_MSG_ID_AppWindowParam_LEN, MAVLINK_MSG_ID_AppWindowParam_CRC);
#endif
}
#endif

#endif

// MESSAGE AppWindowParam UNPACKING


/**
 * @brief Get field Following_error_window from appwindowparam message
 *
 * @return  
 */
static inline int64_t mavlink_msg_appwindowparam_get_Following_error_window(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int64_t(msg,  0);
}

/**
 * @brief Get field Following_error_time_out from appwindowparam message
 *
 * @return  
 */
static inline float mavlink_msg_appwindowparam_get_Following_error_time_out(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field Position_window from appwindowparam message
 *
 * @return  
 */
static inline uint32_t mavlink_msg_appwindowparam_get_Position_window(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  12);
}

/**
 * @brief Get field Position_window_time from appwindowparam message
 *
 * @return  
 */
static inline float mavlink_msg_appwindowparam_get_Position_window_time(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  16);
}

/**
 * @brief Get field Velocity_window from appwindowparam message
 *
 * @return  
 */
static inline float mavlink_msg_appwindowparam_get_Velocity_window(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  20);
}

/**
 * @brief Get field Velocity_window_time from appwindowparam message
 *
 * @return  
 */
static inline float mavlink_msg_appwindowparam_get_Velocity_window_time(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  24);
}

/**
 * @brief Get field Velocity_threshold from appwindowparam message
 *
 * @return  
 */
static inline float mavlink_msg_appwindowparam_get_Velocity_threshold(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  28);
}

/**
 * @brief Get field Velocity_threshold_time from appwindowparam message
 *
 * @return  
 */
static inline float mavlink_msg_appwindowparam_get_Velocity_threshold_time(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  32);
}

/**
 * @brief Decode a appwindowparam message into a struct
 *
 * @param msg The message to decode
 * @param appwindowparam C-struct to decode the message contents into
 */
static inline void mavlink_msg_appwindowparam_decode(const mavlink_message_t* msg, mavlink_appwindowparam_t* appwindowparam)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    appwindowparam->Following_error_window = mavlink_msg_appwindowparam_get_Following_error_window(msg);
    appwindowparam->Following_error_time_out = mavlink_msg_appwindowparam_get_Following_error_time_out(msg);
    appwindowparam->Position_window = mavlink_msg_appwindowparam_get_Position_window(msg);
    appwindowparam->Position_window_time = mavlink_msg_appwindowparam_get_Position_window_time(msg);
    appwindowparam->Velocity_window = mavlink_msg_appwindowparam_get_Velocity_window(msg);
    appwindowparam->Velocity_window_time = mavlink_msg_appwindowparam_get_Velocity_window_time(msg);
    appwindowparam->Velocity_threshold = mavlink_msg_appwindowparam_get_Velocity_threshold(msg);
    appwindowparam->Velocity_threshold_time = mavlink_msg_appwindowparam_get_Velocity_threshold_time(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_AppWindowParam_LEN? msg->len : MAVLINK_MSG_ID_AppWindowParam_LEN;
        memset(appwindowparam, 0, MAVLINK_MSG_ID_AppWindowParam_LEN);
    memcpy(appwindowparam, _MAV_PAYLOAD(msg), len);
#endif
}
