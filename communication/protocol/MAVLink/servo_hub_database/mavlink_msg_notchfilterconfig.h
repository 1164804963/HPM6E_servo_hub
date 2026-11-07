#pragma once
// MESSAGE NotchFilterConfig PACKING

#define MAVLINK_MSG_ID_NotchFilterConfig 30028


typedef struct __mavlink_notchfilterconfig_t {
 float frq[6]; /*<  */
 float width[6]; /*<  */
 float depth[6]; /*<  */
} mavlink_notchfilterconfig_t;

#define MAVLINK_MSG_ID_NotchFilterConfig_LEN 72
#define MAVLINK_MSG_ID_NotchFilterConfig_MIN_LEN 72
#define MAVLINK_MSG_ID_30028_LEN 72
#define MAVLINK_MSG_ID_30028_MIN_LEN 72

#define MAVLINK_MSG_ID_NotchFilterConfig_CRC 125
#define MAVLINK_MSG_ID_30028_CRC 125

#define MAVLINK_MSG_NotchFilterConfig_FIELD_FRQ_LEN 6
#define MAVLINK_MSG_NotchFilterConfig_FIELD_WIDTH_LEN 6
#define MAVLINK_MSG_NotchFilterConfig_FIELD_DEPTH_LEN 6

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_NotchFilterConfig { \
    30028, \
    "NotchFilterConfig", \
    3, \
    {  { "frq", NULL, MAVLINK_TYPE_FLOAT, 6, 0, offsetof(mavlink_notchfilterconfig_t, frq) }, \
         { "width", NULL, MAVLINK_TYPE_FLOAT, 6, 24, offsetof(mavlink_notchfilterconfig_t, width) }, \
         { "depth", NULL, MAVLINK_TYPE_FLOAT, 6, 48, offsetof(mavlink_notchfilterconfig_t, depth) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_NotchFilterConfig { \
    "NotchFilterConfig", \
    3, \
    {  { "frq", NULL, MAVLINK_TYPE_FLOAT, 6, 0, offsetof(mavlink_notchfilterconfig_t, frq) }, \
         { "width", NULL, MAVLINK_TYPE_FLOAT, 6, 24, offsetof(mavlink_notchfilterconfig_t, width) }, \
         { "depth", NULL, MAVLINK_TYPE_FLOAT, 6, 48, offsetof(mavlink_notchfilterconfig_t, depth) }, \
         } \
}
#endif

/**
 * @brief Pack a notchfilterconfig message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param frq  
 * @param width  
 * @param depth  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_notchfilterconfig_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               const float *frq, const float *width, const float *depth)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_NotchFilterConfig_LEN];

    _mav_put_float_array(buf, 0, frq, 6);
    _mav_put_float_array(buf, 24, width, 6);
    _mav_put_float_array(buf, 48, depth, 6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_NotchFilterConfig_LEN);
#else
    mavlink_notchfilterconfig_t packet;

    mav_array_memcpy(packet.frq, frq, sizeof(float)*6);
    mav_array_memcpy(packet.width, width, sizeof(float)*6);
    mav_array_memcpy(packet.depth, depth, sizeof(float)*6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_NotchFilterConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_NotchFilterConfig;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_NotchFilterConfig_MIN_LEN, MAVLINK_MSG_ID_NotchFilterConfig_LEN, MAVLINK_MSG_ID_NotchFilterConfig_CRC);
}

/**
 * @brief Pack a notchfilterconfig message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param frq  
 * @param width  
 * @param depth  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_notchfilterconfig_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               const float *frq, const float *width, const float *depth)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_NotchFilterConfig_LEN];

    _mav_put_float_array(buf, 0, frq, 6);
    _mav_put_float_array(buf, 24, width, 6);
    _mav_put_float_array(buf, 48, depth, 6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_NotchFilterConfig_LEN);
#else
    mavlink_notchfilterconfig_t packet;

    mav_array_memcpy(packet.frq, frq, sizeof(float)*6);
    mav_array_memcpy(packet.width, width, sizeof(float)*6);
    mav_array_memcpy(packet.depth, depth, sizeof(float)*6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_NotchFilterConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_NotchFilterConfig;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_NotchFilterConfig_MIN_LEN, MAVLINK_MSG_ID_NotchFilterConfig_LEN, MAVLINK_MSG_ID_NotchFilterConfig_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_NotchFilterConfig_MIN_LEN, MAVLINK_MSG_ID_NotchFilterConfig_LEN);
#endif
}

/**
 * @brief Pack a notchfilterconfig message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param frq  
 * @param width  
 * @param depth  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_notchfilterconfig_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   const float *frq,const float *width,const float *depth)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_NotchFilterConfig_LEN];

    _mav_put_float_array(buf, 0, frq, 6);
    _mav_put_float_array(buf, 24, width, 6);
    _mav_put_float_array(buf, 48, depth, 6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_NotchFilterConfig_LEN);
#else
    mavlink_notchfilterconfig_t packet;

    mav_array_memcpy(packet.frq, frq, sizeof(float)*6);
    mav_array_memcpy(packet.width, width, sizeof(float)*6);
    mav_array_memcpy(packet.depth, depth, sizeof(float)*6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_NotchFilterConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_NotchFilterConfig;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_NotchFilterConfig_MIN_LEN, MAVLINK_MSG_ID_NotchFilterConfig_LEN, MAVLINK_MSG_ID_NotchFilterConfig_CRC);
}

/**
 * @brief Encode a notchfilterconfig struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param notchfilterconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_notchfilterconfig_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_notchfilterconfig_t* notchfilterconfig)
{
    return mavlink_msg_notchfilterconfig_pack(system_id, component_id, msg, notchfilterconfig->frq, notchfilterconfig->width, notchfilterconfig->depth);
}

/**
 * @brief Encode a notchfilterconfig struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param notchfilterconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_notchfilterconfig_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_notchfilterconfig_t* notchfilterconfig)
{
    return mavlink_msg_notchfilterconfig_pack_chan(system_id, component_id, chan, msg, notchfilterconfig->frq, notchfilterconfig->width, notchfilterconfig->depth);
}

/**
 * @brief Encode a notchfilterconfig struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param notchfilterconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_notchfilterconfig_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_notchfilterconfig_t* notchfilterconfig)
{
    return mavlink_msg_notchfilterconfig_pack_status(system_id, component_id, _status, msg,  notchfilterconfig->frq, notchfilterconfig->width, notchfilterconfig->depth);
}

/**
 * @brief Send a notchfilterconfig message
 * @param chan MAVLink channel to send the message
 *
 * @param frq  
 * @param width  
 * @param depth  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_notchfilterconfig_send(mavlink_channel_t chan, const float *frq, const float *width, const float *depth)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_NotchFilterConfig_LEN];

    _mav_put_float_array(buf, 0, frq, 6);
    _mav_put_float_array(buf, 24, width, 6);
    _mav_put_float_array(buf, 48, depth, 6);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_NotchFilterConfig, buf, MAVLINK_MSG_ID_NotchFilterConfig_MIN_LEN, MAVLINK_MSG_ID_NotchFilterConfig_LEN, MAVLINK_MSG_ID_NotchFilterConfig_CRC);
#else
    mavlink_notchfilterconfig_t packet;

    mav_array_memcpy(packet.frq, frq, sizeof(float)*6);
    mav_array_memcpy(packet.width, width, sizeof(float)*6);
    mav_array_memcpy(packet.depth, depth, sizeof(float)*6);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_NotchFilterConfig, (const char *)&packet, MAVLINK_MSG_ID_NotchFilterConfig_MIN_LEN, MAVLINK_MSG_ID_NotchFilterConfig_LEN, MAVLINK_MSG_ID_NotchFilterConfig_CRC);
#endif
}

/**
 * @brief Send a notchfilterconfig message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_notchfilterconfig_send_struct(mavlink_channel_t chan, const mavlink_notchfilterconfig_t* notchfilterconfig)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_notchfilterconfig_send(chan, notchfilterconfig->frq, notchfilterconfig->width, notchfilterconfig->depth);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_NotchFilterConfig, (const char *)notchfilterconfig, MAVLINK_MSG_ID_NotchFilterConfig_MIN_LEN, MAVLINK_MSG_ID_NotchFilterConfig_LEN, MAVLINK_MSG_ID_NotchFilterConfig_CRC);
#endif
}

#if MAVLINK_MSG_ID_NotchFilterConfig_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_notchfilterconfig_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  const float *frq, const float *width, const float *depth)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;

    _mav_put_float_array(buf, 0, frq, 6);
    _mav_put_float_array(buf, 24, width, 6);
    _mav_put_float_array(buf, 48, depth, 6);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_NotchFilterConfig, buf, MAVLINK_MSG_ID_NotchFilterConfig_MIN_LEN, MAVLINK_MSG_ID_NotchFilterConfig_LEN, MAVLINK_MSG_ID_NotchFilterConfig_CRC);
#else
    mavlink_notchfilterconfig_t *packet = (mavlink_notchfilterconfig_t *)msgbuf;

    mav_array_memcpy(packet->frq, frq, sizeof(float)*6);
    mav_array_memcpy(packet->width, width, sizeof(float)*6);
    mav_array_memcpy(packet->depth, depth, sizeof(float)*6);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_NotchFilterConfig, (const char *)packet, MAVLINK_MSG_ID_NotchFilterConfig_MIN_LEN, MAVLINK_MSG_ID_NotchFilterConfig_LEN, MAVLINK_MSG_ID_NotchFilterConfig_CRC);
#endif
}
#endif

#endif

// MESSAGE NotchFilterConfig UNPACKING


/**
 * @brief Get field frq from notchfilterconfig message
 *
 * @return  
 */
static inline uint16_t mavlink_msg_notchfilterconfig_get_frq(const mavlink_message_t* msg, float *frq)
{
    return _MAV_RETURN_float_array(msg, frq, 6,  0);
}

/**
 * @brief Get field width from notchfilterconfig message
 *
 * @return  
 */
static inline uint16_t mavlink_msg_notchfilterconfig_get_width(const mavlink_message_t* msg, float *width)
{
    return _MAV_RETURN_float_array(msg, width, 6,  24);
}

/**
 * @brief Get field depth from notchfilterconfig message
 *
 * @return  
 */
static inline uint16_t mavlink_msg_notchfilterconfig_get_depth(const mavlink_message_t* msg, float *depth)
{
    return _MAV_RETURN_float_array(msg, depth, 6,  48);
}

/**
 * @brief Decode a notchfilterconfig message into a struct
 *
 * @param msg The message to decode
 * @param notchfilterconfig C-struct to decode the message contents into
 */
static inline void mavlink_msg_notchfilterconfig_decode(const mavlink_message_t* msg, mavlink_notchfilterconfig_t* notchfilterconfig)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_notchfilterconfig_get_frq(msg, notchfilterconfig->frq);
    mavlink_msg_notchfilterconfig_get_width(msg, notchfilterconfig->width);
    mavlink_msg_notchfilterconfig_get_depth(msg, notchfilterconfig->depth);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_NotchFilterConfig_LEN? msg->len : MAVLINK_MSG_ID_NotchFilterConfig_LEN;
        memset(notchfilterconfig, 0, MAVLINK_MSG_ID_NotchFilterConfig_LEN);
    memcpy(notchfilterconfig, _MAV_PAYLOAD(msg), len);
#endif
}
