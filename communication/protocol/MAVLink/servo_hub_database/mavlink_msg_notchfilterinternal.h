#pragma once
// MESSAGE NotchFilterInternal PACKING

#define MAVLINK_MSG_ID_NotchFilterInternal 30008


typedef struct __mavlink_notchfilterinternal_t {
 float u0[6]; /*<  */
 float u1[6]; /*<  */
 float u2[6]; /*<  */
 float y0[6]; /*<  */
 float y1[6]; /*<  */
} mavlink_notchfilterinternal_t;

#define MAVLINK_MSG_ID_NotchFilterInternal_LEN 120
#define MAVLINK_MSG_ID_NotchFilterInternal_MIN_LEN 120
#define MAVLINK_MSG_ID_30008_LEN 120
#define MAVLINK_MSG_ID_30008_MIN_LEN 120

#define MAVLINK_MSG_ID_NotchFilterInternal_CRC 3
#define MAVLINK_MSG_ID_30008_CRC 3

#define MAVLINK_MSG_NotchFilterInternal_FIELD_U0_LEN 6
#define MAVLINK_MSG_NotchFilterInternal_FIELD_U1_LEN 6
#define MAVLINK_MSG_NotchFilterInternal_FIELD_U2_LEN 6
#define MAVLINK_MSG_NotchFilterInternal_FIELD_Y0_LEN 6
#define MAVLINK_MSG_NotchFilterInternal_FIELD_Y1_LEN 6

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_NotchFilterInternal { \
    30008, \
    "NotchFilterInternal", \
    5, \
    {  { "u0", NULL, MAVLINK_TYPE_FLOAT, 6, 0, offsetof(mavlink_notchfilterinternal_t, u0) }, \
         { "u1", NULL, MAVLINK_TYPE_FLOAT, 6, 24, offsetof(mavlink_notchfilterinternal_t, u1) }, \
         { "u2", NULL, MAVLINK_TYPE_FLOAT, 6, 48, offsetof(mavlink_notchfilterinternal_t, u2) }, \
         { "y0", NULL, MAVLINK_TYPE_FLOAT, 6, 72, offsetof(mavlink_notchfilterinternal_t, y0) }, \
         { "y1", NULL, MAVLINK_TYPE_FLOAT, 6, 96, offsetof(mavlink_notchfilterinternal_t, y1) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_NotchFilterInternal { \
    "NotchFilterInternal", \
    5, \
    {  { "u0", NULL, MAVLINK_TYPE_FLOAT, 6, 0, offsetof(mavlink_notchfilterinternal_t, u0) }, \
         { "u1", NULL, MAVLINK_TYPE_FLOAT, 6, 24, offsetof(mavlink_notchfilterinternal_t, u1) }, \
         { "u2", NULL, MAVLINK_TYPE_FLOAT, 6, 48, offsetof(mavlink_notchfilterinternal_t, u2) }, \
         { "y0", NULL, MAVLINK_TYPE_FLOAT, 6, 72, offsetof(mavlink_notchfilterinternal_t, y0) }, \
         { "y1", NULL, MAVLINK_TYPE_FLOAT, 6, 96, offsetof(mavlink_notchfilterinternal_t, y1) }, \
         } \
}
#endif

/**
 * @brief Pack a notchfilterinternal message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param u0  
 * @param u1  
 * @param u2  
 * @param y0  
 * @param y1  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_notchfilterinternal_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               const float *u0, const float *u1, const float *u2, const float *y0, const float *y1)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_NotchFilterInternal_LEN];

    _mav_put_float_array(buf, 0, u0, 6);
    _mav_put_float_array(buf, 24, u1, 6);
    _mav_put_float_array(buf, 48, u2, 6);
    _mav_put_float_array(buf, 72, y0, 6);
    _mav_put_float_array(buf, 96, y1, 6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_NotchFilterInternal_LEN);
#else
    mavlink_notchfilterinternal_t packet;

    mav_array_memcpy(packet.u0, u0, sizeof(float)*6);
    mav_array_memcpy(packet.u1, u1, sizeof(float)*6);
    mav_array_memcpy(packet.u2, u2, sizeof(float)*6);
    mav_array_memcpy(packet.y0, y0, sizeof(float)*6);
    mav_array_memcpy(packet.y1, y1, sizeof(float)*6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_NotchFilterInternal_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_NotchFilterInternal;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_NotchFilterInternal_MIN_LEN, MAVLINK_MSG_ID_NotchFilterInternal_LEN, MAVLINK_MSG_ID_NotchFilterInternal_CRC);
}

/**
 * @brief Pack a notchfilterinternal message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param u0  
 * @param u1  
 * @param u2  
 * @param y0  
 * @param y1  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_notchfilterinternal_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               const float *u0, const float *u1, const float *u2, const float *y0, const float *y1)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_NotchFilterInternal_LEN];

    _mav_put_float_array(buf, 0, u0, 6);
    _mav_put_float_array(buf, 24, u1, 6);
    _mav_put_float_array(buf, 48, u2, 6);
    _mav_put_float_array(buf, 72, y0, 6);
    _mav_put_float_array(buf, 96, y1, 6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_NotchFilterInternal_LEN);
#else
    mavlink_notchfilterinternal_t packet;

    mav_array_memcpy(packet.u0, u0, sizeof(float)*6);
    mav_array_memcpy(packet.u1, u1, sizeof(float)*6);
    mav_array_memcpy(packet.u2, u2, sizeof(float)*6);
    mav_array_memcpy(packet.y0, y0, sizeof(float)*6);
    mav_array_memcpy(packet.y1, y1, sizeof(float)*6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_NotchFilterInternal_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_NotchFilterInternal;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_NotchFilterInternal_MIN_LEN, MAVLINK_MSG_ID_NotchFilterInternal_LEN, MAVLINK_MSG_ID_NotchFilterInternal_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_NotchFilterInternal_MIN_LEN, MAVLINK_MSG_ID_NotchFilterInternal_LEN);
#endif
}

/**
 * @brief Pack a notchfilterinternal message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param u0  
 * @param u1  
 * @param u2  
 * @param y0  
 * @param y1  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_notchfilterinternal_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   const float *u0,const float *u1,const float *u2,const float *y0,const float *y1)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_NotchFilterInternal_LEN];

    _mav_put_float_array(buf, 0, u0, 6);
    _mav_put_float_array(buf, 24, u1, 6);
    _mav_put_float_array(buf, 48, u2, 6);
    _mav_put_float_array(buf, 72, y0, 6);
    _mav_put_float_array(buf, 96, y1, 6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_NotchFilterInternal_LEN);
#else
    mavlink_notchfilterinternal_t packet;

    mav_array_memcpy(packet.u0, u0, sizeof(float)*6);
    mav_array_memcpy(packet.u1, u1, sizeof(float)*6);
    mav_array_memcpy(packet.u2, u2, sizeof(float)*6);
    mav_array_memcpy(packet.y0, y0, sizeof(float)*6);
    mav_array_memcpy(packet.y1, y1, sizeof(float)*6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_NotchFilterInternal_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_NotchFilterInternal;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_NotchFilterInternal_MIN_LEN, MAVLINK_MSG_ID_NotchFilterInternal_LEN, MAVLINK_MSG_ID_NotchFilterInternal_CRC);
}

/**
 * @brief Encode a notchfilterinternal struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param notchfilterinternal C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_notchfilterinternal_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_notchfilterinternal_t* notchfilterinternal)
{
    return mavlink_msg_notchfilterinternal_pack(system_id, component_id, msg, notchfilterinternal->u0, notchfilterinternal->u1, notchfilterinternal->u2, notchfilterinternal->y0, notchfilterinternal->y1);
}

/**
 * @brief Encode a notchfilterinternal struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param notchfilterinternal C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_notchfilterinternal_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_notchfilterinternal_t* notchfilterinternal)
{
    return mavlink_msg_notchfilterinternal_pack_chan(system_id, component_id, chan, msg, notchfilterinternal->u0, notchfilterinternal->u1, notchfilterinternal->u2, notchfilterinternal->y0, notchfilterinternal->y1);
}

/**
 * @brief Encode a notchfilterinternal struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param notchfilterinternal C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_notchfilterinternal_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_notchfilterinternal_t* notchfilterinternal)
{
    return mavlink_msg_notchfilterinternal_pack_status(system_id, component_id, _status, msg,  notchfilterinternal->u0, notchfilterinternal->u1, notchfilterinternal->u2, notchfilterinternal->y0, notchfilterinternal->y1);
}

/**
 * @brief Send a notchfilterinternal message
 * @param chan MAVLink channel to send the message
 *
 * @param u0  
 * @param u1  
 * @param u2  
 * @param y0  
 * @param y1  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_notchfilterinternal_send(mavlink_channel_t chan, const float *u0, const float *u1, const float *u2, const float *y0, const float *y1)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_NotchFilterInternal_LEN];

    _mav_put_float_array(buf, 0, u0, 6);
    _mav_put_float_array(buf, 24, u1, 6);
    _mav_put_float_array(buf, 48, u2, 6);
    _mav_put_float_array(buf, 72, y0, 6);
    _mav_put_float_array(buf, 96, y1, 6);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_NotchFilterInternal, buf, MAVLINK_MSG_ID_NotchFilterInternal_MIN_LEN, MAVLINK_MSG_ID_NotchFilterInternal_LEN, MAVLINK_MSG_ID_NotchFilterInternal_CRC);
#else
    mavlink_notchfilterinternal_t packet;

    mav_array_memcpy(packet.u0, u0, sizeof(float)*6);
    mav_array_memcpy(packet.u1, u1, sizeof(float)*6);
    mav_array_memcpy(packet.u2, u2, sizeof(float)*6);
    mav_array_memcpy(packet.y0, y0, sizeof(float)*6);
    mav_array_memcpy(packet.y1, y1, sizeof(float)*6);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_NotchFilterInternal, (const char *)&packet, MAVLINK_MSG_ID_NotchFilterInternal_MIN_LEN, MAVLINK_MSG_ID_NotchFilterInternal_LEN, MAVLINK_MSG_ID_NotchFilterInternal_CRC);
#endif
}

/**
 * @brief Send a notchfilterinternal message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_notchfilterinternal_send_struct(mavlink_channel_t chan, const mavlink_notchfilterinternal_t* notchfilterinternal)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_notchfilterinternal_send(chan, notchfilterinternal->u0, notchfilterinternal->u1, notchfilterinternal->u2, notchfilterinternal->y0, notchfilterinternal->y1);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_NotchFilterInternal, (const char *)notchfilterinternal, MAVLINK_MSG_ID_NotchFilterInternal_MIN_LEN, MAVLINK_MSG_ID_NotchFilterInternal_LEN, MAVLINK_MSG_ID_NotchFilterInternal_CRC);
#endif
}

#if MAVLINK_MSG_ID_NotchFilterInternal_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_notchfilterinternal_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  const float *u0, const float *u1, const float *u2, const float *y0, const float *y1)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;

    _mav_put_float_array(buf, 0, u0, 6);
    _mav_put_float_array(buf, 24, u1, 6);
    _mav_put_float_array(buf, 48, u2, 6);
    _mav_put_float_array(buf, 72, y0, 6);
    _mav_put_float_array(buf, 96, y1, 6);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_NotchFilterInternal, buf, MAVLINK_MSG_ID_NotchFilterInternal_MIN_LEN, MAVLINK_MSG_ID_NotchFilterInternal_LEN, MAVLINK_MSG_ID_NotchFilterInternal_CRC);
#else
    mavlink_notchfilterinternal_t *packet = (mavlink_notchfilterinternal_t *)msgbuf;

    mav_array_memcpy(packet->u0, u0, sizeof(float)*6);
    mav_array_memcpy(packet->u1, u1, sizeof(float)*6);
    mav_array_memcpy(packet->u2, u2, sizeof(float)*6);
    mav_array_memcpy(packet->y0, y0, sizeof(float)*6);
    mav_array_memcpy(packet->y1, y1, sizeof(float)*6);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_NotchFilterInternal, (const char *)packet, MAVLINK_MSG_ID_NotchFilterInternal_MIN_LEN, MAVLINK_MSG_ID_NotchFilterInternal_LEN, MAVLINK_MSG_ID_NotchFilterInternal_CRC);
#endif
}
#endif

#endif

// MESSAGE NotchFilterInternal UNPACKING


/**
 * @brief Get field u0 from notchfilterinternal message
 *
 * @return  
 */
static inline uint16_t mavlink_msg_notchfilterinternal_get_u0(const mavlink_message_t* msg, float *u0)
{
    return _MAV_RETURN_float_array(msg, u0, 6,  0);
}

/**
 * @brief Get field u1 from notchfilterinternal message
 *
 * @return  
 */
static inline uint16_t mavlink_msg_notchfilterinternal_get_u1(const mavlink_message_t* msg, float *u1)
{
    return _MAV_RETURN_float_array(msg, u1, 6,  24);
}

/**
 * @brief Get field u2 from notchfilterinternal message
 *
 * @return  
 */
static inline uint16_t mavlink_msg_notchfilterinternal_get_u2(const mavlink_message_t* msg, float *u2)
{
    return _MAV_RETURN_float_array(msg, u2, 6,  48);
}

/**
 * @brief Get field y0 from notchfilterinternal message
 *
 * @return  
 */
static inline uint16_t mavlink_msg_notchfilterinternal_get_y0(const mavlink_message_t* msg, float *y0)
{
    return _MAV_RETURN_float_array(msg, y0, 6,  72);
}

/**
 * @brief Get field y1 from notchfilterinternal message
 *
 * @return  
 */
static inline uint16_t mavlink_msg_notchfilterinternal_get_y1(const mavlink_message_t* msg, float *y1)
{
    return _MAV_RETURN_float_array(msg, y1, 6,  96);
}

/**
 * @brief Decode a notchfilterinternal message into a struct
 *
 * @param msg The message to decode
 * @param notchfilterinternal C-struct to decode the message contents into
 */
static inline void mavlink_msg_notchfilterinternal_decode(const mavlink_message_t* msg, mavlink_notchfilterinternal_t* notchfilterinternal)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_notchfilterinternal_get_u0(msg, notchfilterinternal->u0);
    mavlink_msg_notchfilterinternal_get_u1(msg, notchfilterinternal->u1);
    mavlink_msg_notchfilterinternal_get_u2(msg, notchfilterinternal->u2);
    mavlink_msg_notchfilterinternal_get_y0(msg, notchfilterinternal->y0);
    mavlink_msg_notchfilterinternal_get_y1(msg, notchfilterinternal->y1);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_NotchFilterInternal_LEN? msg->len : MAVLINK_MSG_ID_NotchFilterInternal_LEN;
        memset(notchfilterinternal, 0, MAVLINK_MSG_ID_NotchFilterInternal_LEN);
    memcpy(notchfilterinternal, _MAV_PAYLOAD(msg), len);
#endif
}
