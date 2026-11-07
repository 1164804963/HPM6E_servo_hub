#pragma once
// MESSAGE AppDebugParam PACKING

#define MAVLINK_MSG_ID_AppDebugParam 30082


typedef struct __mavlink_appdebugparam_t {
 float Debug_float[16]; /*<  */
 uint32_t Debug_uint32[16]; /*<  */
 int32_t Debug_int32[16]; /*<  */
} mavlink_appdebugparam_t;

#define MAVLINK_MSG_ID_AppDebugParam_LEN 192
#define MAVLINK_MSG_ID_AppDebugParam_MIN_LEN 192
#define MAVLINK_MSG_ID_30082_LEN 192
#define MAVLINK_MSG_ID_30082_MIN_LEN 192

#define MAVLINK_MSG_ID_AppDebugParam_CRC 218
#define MAVLINK_MSG_ID_30082_CRC 218

#define MAVLINK_MSG_AppDebugParam_FIELD_DEBUG_FLOAT_LEN 16
#define MAVLINK_MSG_AppDebugParam_FIELD_DEBUG_UINT32_LEN 16
#define MAVLINK_MSG_AppDebugParam_FIELD_DEBUG_INT32_LEN 16

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_AppDebugParam { \
    30082, \
    "AppDebugParam", \
    3, \
    {  { "Debug_float", NULL, MAVLINK_TYPE_FLOAT, 16, 0, offsetof(mavlink_appdebugparam_t, Debug_float) }, \
         { "Debug_uint32", NULL, MAVLINK_TYPE_UINT32_T, 16, 64, offsetof(mavlink_appdebugparam_t, Debug_uint32) }, \
         { "Debug_int32", NULL, MAVLINK_TYPE_INT32_T, 16, 128, offsetof(mavlink_appdebugparam_t, Debug_int32) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_AppDebugParam { \
    "AppDebugParam", \
    3, \
    {  { "Debug_float", NULL, MAVLINK_TYPE_FLOAT, 16, 0, offsetof(mavlink_appdebugparam_t, Debug_float) }, \
         { "Debug_uint32", NULL, MAVLINK_TYPE_UINT32_T, 16, 64, offsetof(mavlink_appdebugparam_t, Debug_uint32) }, \
         { "Debug_int32", NULL, MAVLINK_TYPE_INT32_T, 16, 128, offsetof(mavlink_appdebugparam_t, Debug_int32) }, \
         } \
}
#endif

/**
 * @brief Pack a appdebugparam message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param Debug_float  
 * @param Debug_uint32  
 * @param Debug_int32  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_appdebugparam_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               const float *Debug_float, const uint32_t *Debug_uint32, const int32_t *Debug_int32)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_AppDebugParam_LEN];

    _mav_put_float_array(buf, 0, Debug_float, 16);
    _mav_put_uint32_t_array(buf, 64, Debug_uint32, 16);
    _mav_put_int32_t_array(buf, 128, Debug_int32, 16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_AppDebugParam_LEN);
#else
    mavlink_appdebugparam_t packet;

    mav_array_memcpy(packet.Debug_float, Debug_float, sizeof(float)*16);
    mav_array_memcpy(packet.Debug_uint32, Debug_uint32, sizeof(uint32_t)*16);
    mav_array_memcpy(packet.Debug_int32, Debug_int32, sizeof(int32_t)*16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_AppDebugParam_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_AppDebugParam;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_AppDebugParam_MIN_LEN, MAVLINK_MSG_ID_AppDebugParam_LEN, MAVLINK_MSG_ID_AppDebugParam_CRC);
}

/**
 * @brief Pack a appdebugparam message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param Debug_float  
 * @param Debug_uint32  
 * @param Debug_int32  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_appdebugparam_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               const float *Debug_float, const uint32_t *Debug_uint32, const int32_t *Debug_int32)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_AppDebugParam_LEN];

    _mav_put_float_array(buf, 0, Debug_float, 16);
    _mav_put_uint32_t_array(buf, 64, Debug_uint32, 16);
    _mav_put_int32_t_array(buf, 128, Debug_int32, 16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_AppDebugParam_LEN);
#else
    mavlink_appdebugparam_t packet;

    mav_array_memcpy(packet.Debug_float, Debug_float, sizeof(float)*16);
    mav_array_memcpy(packet.Debug_uint32, Debug_uint32, sizeof(uint32_t)*16);
    mav_array_memcpy(packet.Debug_int32, Debug_int32, sizeof(int32_t)*16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_AppDebugParam_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_AppDebugParam;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_AppDebugParam_MIN_LEN, MAVLINK_MSG_ID_AppDebugParam_LEN, MAVLINK_MSG_ID_AppDebugParam_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_AppDebugParam_MIN_LEN, MAVLINK_MSG_ID_AppDebugParam_LEN);
#endif
}

/**
 * @brief Pack a appdebugparam message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param Debug_float  
 * @param Debug_uint32  
 * @param Debug_int32  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_appdebugparam_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   const float *Debug_float,const uint32_t *Debug_uint32,const int32_t *Debug_int32)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_AppDebugParam_LEN];

    _mav_put_float_array(buf, 0, Debug_float, 16);
    _mav_put_uint32_t_array(buf, 64, Debug_uint32, 16);
    _mav_put_int32_t_array(buf, 128, Debug_int32, 16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_AppDebugParam_LEN);
#else
    mavlink_appdebugparam_t packet;

    mav_array_memcpy(packet.Debug_float, Debug_float, sizeof(float)*16);
    mav_array_memcpy(packet.Debug_uint32, Debug_uint32, sizeof(uint32_t)*16);
    mav_array_memcpy(packet.Debug_int32, Debug_int32, sizeof(int32_t)*16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_AppDebugParam_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_AppDebugParam;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_AppDebugParam_MIN_LEN, MAVLINK_MSG_ID_AppDebugParam_LEN, MAVLINK_MSG_ID_AppDebugParam_CRC);
}

/**
 * @brief Encode a appdebugparam struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param appdebugparam C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_appdebugparam_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_appdebugparam_t* appdebugparam)
{
    return mavlink_msg_appdebugparam_pack(system_id, component_id, msg, appdebugparam->Debug_float, appdebugparam->Debug_uint32, appdebugparam->Debug_int32);
}

/**
 * @brief Encode a appdebugparam struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param appdebugparam C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_appdebugparam_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_appdebugparam_t* appdebugparam)
{
    return mavlink_msg_appdebugparam_pack_chan(system_id, component_id, chan, msg, appdebugparam->Debug_float, appdebugparam->Debug_uint32, appdebugparam->Debug_int32);
}

/**
 * @brief Encode a appdebugparam struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param appdebugparam C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_appdebugparam_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_appdebugparam_t* appdebugparam)
{
    return mavlink_msg_appdebugparam_pack_status(system_id, component_id, _status, msg,  appdebugparam->Debug_float, appdebugparam->Debug_uint32, appdebugparam->Debug_int32);
}

/**
 * @brief Send a appdebugparam message
 * @param chan MAVLink channel to send the message
 *
 * @param Debug_float  
 * @param Debug_uint32  
 * @param Debug_int32  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_appdebugparam_send(mavlink_channel_t chan, const float *Debug_float, const uint32_t *Debug_uint32, const int32_t *Debug_int32)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_AppDebugParam_LEN];

    _mav_put_float_array(buf, 0, Debug_float, 16);
    _mav_put_uint32_t_array(buf, 64, Debug_uint32, 16);
    _mav_put_int32_t_array(buf, 128, Debug_int32, 16);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppDebugParam, buf, MAVLINK_MSG_ID_AppDebugParam_MIN_LEN, MAVLINK_MSG_ID_AppDebugParam_LEN, MAVLINK_MSG_ID_AppDebugParam_CRC);
#else
    mavlink_appdebugparam_t packet;

    mav_array_memcpy(packet.Debug_float, Debug_float, sizeof(float)*16);
    mav_array_memcpy(packet.Debug_uint32, Debug_uint32, sizeof(uint32_t)*16);
    mav_array_memcpy(packet.Debug_int32, Debug_int32, sizeof(int32_t)*16);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppDebugParam, (const char *)&packet, MAVLINK_MSG_ID_AppDebugParam_MIN_LEN, MAVLINK_MSG_ID_AppDebugParam_LEN, MAVLINK_MSG_ID_AppDebugParam_CRC);
#endif
}

/**
 * @brief Send a appdebugparam message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_appdebugparam_send_struct(mavlink_channel_t chan, const mavlink_appdebugparam_t* appdebugparam)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_appdebugparam_send(chan, appdebugparam->Debug_float, appdebugparam->Debug_uint32, appdebugparam->Debug_int32);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppDebugParam, (const char *)appdebugparam, MAVLINK_MSG_ID_AppDebugParam_MIN_LEN, MAVLINK_MSG_ID_AppDebugParam_LEN, MAVLINK_MSG_ID_AppDebugParam_CRC);
#endif
}

#if MAVLINK_MSG_ID_AppDebugParam_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_appdebugparam_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  const float *Debug_float, const uint32_t *Debug_uint32, const int32_t *Debug_int32)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;

    _mav_put_float_array(buf, 0, Debug_float, 16);
    _mav_put_uint32_t_array(buf, 64, Debug_uint32, 16);
    _mav_put_int32_t_array(buf, 128, Debug_int32, 16);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppDebugParam, buf, MAVLINK_MSG_ID_AppDebugParam_MIN_LEN, MAVLINK_MSG_ID_AppDebugParam_LEN, MAVLINK_MSG_ID_AppDebugParam_CRC);
#else
    mavlink_appdebugparam_t *packet = (mavlink_appdebugparam_t *)msgbuf;

    mav_array_memcpy(packet->Debug_float, Debug_float, sizeof(float)*16);
    mav_array_memcpy(packet->Debug_uint32, Debug_uint32, sizeof(uint32_t)*16);
    mav_array_memcpy(packet->Debug_int32, Debug_int32, sizeof(int32_t)*16);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppDebugParam, (const char *)packet, MAVLINK_MSG_ID_AppDebugParam_MIN_LEN, MAVLINK_MSG_ID_AppDebugParam_LEN, MAVLINK_MSG_ID_AppDebugParam_CRC);
#endif
}
#endif

#endif

// MESSAGE AppDebugParam UNPACKING


/**
 * @brief Get field Debug_float from appdebugparam message
 *
 * @return  
 */
static inline uint16_t mavlink_msg_appdebugparam_get_Debug_float(const mavlink_message_t* msg, float *Debug_float)
{
    return _MAV_RETURN_float_array(msg, Debug_float, 16,  0);
}

/**
 * @brief Get field Debug_uint32 from appdebugparam message
 *
 * @return  
 */
static inline uint16_t mavlink_msg_appdebugparam_get_Debug_uint32(const mavlink_message_t* msg, uint32_t *Debug_uint32)
{
    return _MAV_RETURN_uint32_t_array(msg, Debug_uint32, 16,  64);
}

/**
 * @brief Get field Debug_int32 from appdebugparam message
 *
 * @return  
 */
static inline uint16_t mavlink_msg_appdebugparam_get_Debug_int32(const mavlink_message_t* msg, int32_t *Debug_int32)
{
    return _MAV_RETURN_int32_t_array(msg, Debug_int32, 16,  128);
}

/**
 * @brief Decode a appdebugparam message into a struct
 *
 * @param msg The message to decode
 * @param appdebugparam C-struct to decode the message contents into
 */
static inline void mavlink_msg_appdebugparam_decode(const mavlink_message_t* msg, mavlink_appdebugparam_t* appdebugparam)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_appdebugparam_get_Debug_float(msg, appdebugparam->Debug_float);
    mavlink_msg_appdebugparam_get_Debug_uint32(msg, appdebugparam->Debug_uint32);
    mavlink_msg_appdebugparam_get_Debug_int32(msg, appdebugparam->Debug_int32);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_AppDebugParam_LEN? msg->len : MAVLINK_MSG_ID_AppDebugParam_LEN;
        memset(appdebugparam, 0, MAVLINK_MSG_ID_AppDebugParam_LEN);
    memcpy(appdebugparam, _MAV_PAYLOAD(msg), len);
#endif
}
