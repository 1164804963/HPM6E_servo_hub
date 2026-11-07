#pragma once
// MESSAGE READ_PARAM PACKING

#define MAVLINK_MSG_ID_READ_PARAM 30000


typedef struct __mavlink_read_param_t {
 uint32_t struct_id; /*<  */
} mavlink_read_param_t;

#define MAVLINK_MSG_ID_READ_PARAM_LEN 4
#define MAVLINK_MSG_ID_READ_PARAM_MIN_LEN 4
#define MAVLINK_MSG_ID_30000_LEN 4
#define MAVLINK_MSG_ID_30000_MIN_LEN 4

#define MAVLINK_MSG_ID_READ_PARAM_CRC 43
#define MAVLINK_MSG_ID_30000_CRC 43



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_READ_PARAM { \
    30000, \
    "READ_PARAM", \
    1, \
    {  { "struct_id", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_read_param_t, struct_id) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_READ_PARAM { \
    "READ_PARAM", \
    1, \
    {  { "struct_id", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_read_param_t, struct_id) }, \
         } \
}
#endif

/**
 * @brief Pack a read_param message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param struct_id  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_read_param_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint32_t struct_id)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_READ_PARAM_LEN];
    _mav_put_uint32_t(buf, 0, struct_id);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_READ_PARAM_LEN);
#else
    mavlink_read_param_t packet;
    packet.struct_id = struct_id;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_READ_PARAM_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_READ_PARAM;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_READ_PARAM_MIN_LEN, MAVLINK_MSG_ID_READ_PARAM_LEN, MAVLINK_MSG_ID_READ_PARAM_CRC);
}

/**
 * @brief Pack a read_param message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param struct_id  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_read_param_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint32_t struct_id)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_READ_PARAM_LEN];
    _mav_put_uint32_t(buf, 0, struct_id);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_READ_PARAM_LEN);
#else
    mavlink_read_param_t packet;
    packet.struct_id = struct_id;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_READ_PARAM_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_READ_PARAM;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_READ_PARAM_MIN_LEN, MAVLINK_MSG_ID_READ_PARAM_LEN, MAVLINK_MSG_ID_READ_PARAM_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_READ_PARAM_MIN_LEN, MAVLINK_MSG_ID_READ_PARAM_LEN);
#endif
}

/**
 * @brief Pack a read_param message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param struct_id  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_read_param_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint32_t struct_id)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_READ_PARAM_LEN];
    _mav_put_uint32_t(buf, 0, struct_id);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_READ_PARAM_LEN);
#else
    mavlink_read_param_t packet;
    packet.struct_id = struct_id;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_READ_PARAM_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_READ_PARAM;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_READ_PARAM_MIN_LEN, MAVLINK_MSG_ID_READ_PARAM_LEN, MAVLINK_MSG_ID_READ_PARAM_CRC);
}

/**
 * @brief Encode a read_param struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param read_param C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_read_param_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_read_param_t* read_param)
{
    return mavlink_msg_read_param_pack(system_id, component_id, msg, read_param->struct_id);
}

/**
 * @brief Encode a read_param struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param read_param C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_read_param_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_read_param_t* read_param)
{
    return mavlink_msg_read_param_pack_chan(system_id, component_id, chan, msg, read_param->struct_id);
}

/**
 * @brief Encode a read_param struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param read_param C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_read_param_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_read_param_t* read_param)
{
    return mavlink_msg_read_param_pack_status(system_id, component_id, _status, msg,  read_param->struct_id);
}

/**
 * @brief Send a read_param message
 * @param chan MAVLink channel to send the message
 *
 * @param struct_id  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_read_param_send(mavlink_channel_t chan, uint32_t struct_id)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_READ_PARAM_LEN];
    _mav_put_uint32_t(buf, 0, struct_id);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_READ_PARAM, buf, MAVLINK_MSG_ID_READ_PARAM_MIN_LEN, MAVLINK_MSG_ID_READ_PARAM_LEN, MAVLINK_MSG_ID_READ_PARAM_CRC);
#else
    mavlink_read_param_t packet;
    packet.struct_id = struct_id;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_READ_PARAM, (const char *)&packet, MAVLINK_MSG_ID_READ_PARAM_MIN_LEN, MAVLINK_MSG_ID_READ_PARAM_LEN, MAVLINK_MSG_ID_READ_PARAM_CRC);
#endif
}

/**
 * @brief Send a read_param message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_read_param_send_struct(mavlink_channel_t chan, const mavlink_read_param_t* read_param)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_read_param_send(chan, read_param->struct_id);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_READ_PARAM, (const char *)read_param, MAVLINK_MSG_ID_READ_PARAM_MIN_LEN, MAVLINK_MSG_ID_READ_PARAM_LEN, MAVLINK_MSG_ID_READ_PARAM_CRC);
#endif
}

#if MAVLINK_MSG_ID_READ_PARAM_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_read_param_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint32_t struct_id)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint32_t(buf, 0, struct_id);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_READ_PARAM, buf, MAVLINK_MSG_ID_READ_PARAM_MIN_LEN, MAVLINK_MSG_ID_READ_PARAM_LEN, MAVLINK_MSG_ID_READ_PARAM_CRC);
#else
    mavlink_read_param_t *packet = (mavlink_read_param_t *)msgbuf;
    packet->struct_id = struct_id;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_READ_PARAM, (const char *)packet, MAVLINK_MSG_ID_READ_PARAM_MIN_LEN, MAVLINK_MSG_ID_READ_PARAM_LEN, MAVLINK_MSG_ID_READ_PARAM_CRC);
#endif
}
#endif

#endif

// MESSAGE READ_PARAM UNPACKING


/**
 * @brief Get field struct_id from read_param message
 *
 * @return  
 */
static inline uint32_t mavlink_msg_read_param_get_struct_id(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Decode a read_param message into a struct
 *
 * @param msg The message to decode
 * @param read_param C-struct to decode the message contents into
 */
static inline void mavlink_msg_read_param_decode(const mavlink_message_t* msg, mavlink_read_param_t* read_param)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    read_param->struct_id = mavlink_msg_read_param_get_struct_id(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_READ_PARAM_LEN? msg->len : MAVLINK_MSG_ID_READ_PARAM_LEN;
        memset(read_param, 0, MAVLINK_MSG_ID_READ_PARAM_LEN);
    memcpy(read_param, _MAV_PAYLOAD(msg), len);
#endif
}
