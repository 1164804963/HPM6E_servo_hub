#pragma once
// MESSAGE NonVolatileParam PACKING

#define MAVLINK_MSG_ID_NonVolatileParam 30044


typedef struct __mavlink_nonvolatileparam_t {
 uint32_t encoder_res; /*<  */
 float rated_current; /*<  */
} mavlink_nonvolatileparam_t;

#define MAVLINK_MSG_ID_NonVolatileParam_LEN 8
#define MAVLINK_MSG_ID_NonVolatileParam_MIN_LEN 8
#define MAVLINK_MSG_ID_30044_LEN 8
#define MAVLINK_MSG_ID_30044_MIN_LEN 8

#define MAVLINK_MSG_ID_NonVolatileParam_CRC 152
#define MAVLINK_MSG_ID_30044_CRC 152



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_NonVolatileParam { \
    30044, \
    "NonVolatileParam", \
    2, \
    {  { "encoder_res", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_nonvolatileparam_t, encoder_res) }, \
         { "rated_current", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_nonvolatileparam_t, rated_current) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_NonVolatileParam { \
    "NonVolatileParam", \
    2, \
    {  { "encoder_res", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_nonvolatileparam_t, encoder_res) }, \
         { "rated_current", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_nonvolatileparam_t, rated_current) }, \
         } \
}
#endif

/**
 * @brief Pack a nonvolatileparam message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param encoder_res  
 * @param rated_current  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_nonvolatileparam_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint32_t encoder_res, float rated_current)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_NonVolatileParam_LEN];
    _mav_put_uint32_t(buf, 0, encoder_res);
    _mav_put_float(buf, 4, rated_current);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_NonVolatileParam_LEN);
#else
    mavlink_nonvolatileparam_t packet;
    packet.encoder_res = encoder_res;
    packet.rated_current = rated_current;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_NonVolatileParam_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_NonVolatileParam;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_NonVolatileParam_MIN_LEN, MAVLINK_MSG_ID_NonVolatileParam_LEN, MAVLINK_MSG_ID_NonVolatileParam_CRC);
}

/**
 * @brief Pack a nonvolatileparam message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param encoder_res  
 * @param rated_current  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_nonvolatileparam_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint32_t encoder_res, float rated_current)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_NonVolatileParam_LEN];
    _mav_put_uint32_t(buf, 0, encoder_res);
    _mav_put_float(buf, 4, rated_current);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_NonVolatileParam_LEN);
#else
    mavlink_nonvolatileparam_t packet;
    packet.encoder_res = encoder_res;
    packet.rated_current = rated_current;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_NonVolatileParam_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_NonVolatileParam;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_NonVolatileParam_MIN_LEN, MAVLINK_MSG_ID_NonVolatileParam_LEN, MAVLINK_MSG_ID_NonVolatileParam_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_NonVolatileParam_MIN_LEN, MAVLINK_MSG_ID_NonVolatileParam_LEN);
#endif
}

/**
 * @brief Pack a nonvolatileparam message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param encoder_res  
 * @param rated_current  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_nonvolatileparam_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint32_t encoder_res,float rated_current)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_NonVolatileParam_LEN];
    _mav_put_uint32_t(buf, 0, encoder_res);
    _mav_put_float(buf, 4, rated_current);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_NonVolatileParam_LEN);
#else
    mavlink_nonvolatileparam_t packet;
    packet.encoder_res = encoder_res;
    packet.rated_current = rated_current;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_NonVolatileParam_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_NonVolatileParam;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_NonVolatileParam_MIN_LEN, MAVLINK_MSG_ID_NonVolatileParam_LEN, MAVLINK_MSG_ID_NonVolatileParam_CRC);
}

/**
 * @brief Encode a nonvolatileparam struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param nonvolatileparam C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_nonvolatileparam_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_nonvolatileparam_t* nonvolatileparam)
{
    return mavlink_msg_nonvolatileparam_pack(system_id, component_id, msg, nonvolatileparam->encoder_res, nonvolatileparam->rated_current);
}

/**
 * @brief Encode a nonvolatileparam struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param nonvolatileparam C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_nonvolatileparam_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_nonvolatileparam_t* nonvolatileparam)
{
    return mavlink_msg_nonvolatileparam_pack_chan(system_id, component_id, chan, msg, nonvolatileparam->encoder_res, nonvolatileparam->rated_current);
}

/**
 * @brief Encode a nonvolatileparam struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param nonvolatileparam C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_nonvolatileparam_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_nonvolatileparam_t* nonvolatileparam)
{
    return mavlink_msg_nonvolatileparam_pack_status(system_id, component_id, _status, msg,  nonvolatileparam->encoder_res, nonvolatileparam->rated_current);
}

/**
 * @brief Send a nonvolatileparam message
 * @param chan MAVLink channel to send the message
 *
 * @param encoder_res  
 * @param rated_current  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_nonvolatileparam_send(mavlink_channel_t chan, uint32_t encoder_res, float rated_current)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_NonVolatileParam_LEN];
    _mav_put_uint32_t(buf, 0, encoder_res);
    _mav_put_float(buf, 4, rated_current);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_NonVolatileParam, buf, MAVLINK_MSG_ID_NonVolatileParam_MIN_LEN, MAVLINK_MSG_ID_NonVolatileParam_LEN, MAVLINK_MSG_ID_NonVolatileParam_CRC);
#else
    mavlink_nonvolatileparam_t packet;
    packet.encoder_res = encoder_res;
    packet.rated_current = rated_current;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_NonVolatileParam, (const char *)&packet, MAVLINK_MSG_ID_NonVolatileParam_MIN_LEN, MAVLINK_MSG_ID_NonVolatileParam_LEN, MAVLINK_MSG_ID_NonVolatileParam_CRC);
#endif
}

/**
 * @brief Send a nonvolatileparam message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_nonvolatileparam_send_struct(mavlink_channel_t chan, const mavlink_nonvolatileparam_t* nonvolatileparam)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_nonvolatileparam_send(chan, nonvolatileparam->encoder_res, nonvolatileparam->rated_current);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_NonVolatileParam, (const char *)nonvolatileparam, MAVLINK_MSG_ID_NonVolatileParam_MIN_LEN, MAVLINK_MSG_ID_NonVolatileParam_LEN, MAVLINK_MSG_ID_NonVolatileParam_CRC);
#endif
}

#if MAVLINK_MSG_ID_NonVolatileParam_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_nonvolatileparam_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint32_t encoder_res, float rated_current)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint32_t(buf, 0, encoder_res);
    _mav_put_float(buf, 4, rated_current);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_NonVolatileParam, buf, MAVLINK_MSG_ID_NonVolatileParam_MIN_LEN, MAVLINK_MSG_ID_NonVolatileParam_LEN, MAVLINK_MSG_ID_NonVolatileParam_CRC);
#else
    mavlink_nonvolatileparam_t *packet = (mavlink_nonvolatileparam_t *)msgbuf;
    packet->encoder_res = encoder_res;
    packet->rated_current = rated_current;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_NonVolatileParam, (const char *)packet, MAVLINK_MSG_ID_NonVolatileParam_MIN_LEN, MAVLINK_MSG_ID_NonVolatileParam_LEN, MAVLINK_MSG_ID_NonVolatileParam_CRC);
#endif
}
#endif

#endif

// MESSAGE NonVolatileParam UNPACKING


/**
 * @brief Get field encoder_res from nonvolatileparam message
 *
 * @return  
 */
static inline uint32_t mavlink_msg_nonvolatileparam_get_encoder_res(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Get field rated_current from nonvolatileparam message
 *
 * @return  
 */
static inline float mavlink_msg_nonvolatileparam_get_rated_current(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Decode a nonvolatileparam message into a struct
 *
 * @param msg The message to decode
 * @param nonvolatileparam C-struct to decode the message contents into
 */
static inline void mavlink_msg_nonvolatileparam_decode(const mavlink_message_t* msg, mavlink_nonvolatileparam_t* nonvolatileparam)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    nonvolatileparam->encoder_res = mavlink_msg_nonvolatileparam_get_encoder_res(msg);
    nonvolatileparam->rated_current = mavlink_msg_nonvolatileparam_get_rated_current(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_NonVolatileParam_LEN? msg->len : MAVLINK_MSG_ID_NonVolatileParam_LEN;
        memset(nonvolatileparam, 0, MAVLINK_MSG_ID_NonVolatileParam_LEN);
    memcpy(nonvolatileparam, _MAV_PAYLOAD(msg), len);
#endif
}
