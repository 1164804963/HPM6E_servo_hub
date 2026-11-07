#pragma once
// MESSAGE ElecAngleIdInput PACKING

#define MAVLINK_MSG_ID_ElecAngleIdInput 30034


typedef struct __mavlink_elecangleidinput_t {
 float pos_now_rad; /*<  */
} mavlink_elecangleidinput_t;

#define MAVLINK_MSG_ID_ElecAngleIdInput_LEN 4
#define MAVLINK_MSG_ID_ElecAngleIdInput_MIN_LEN 4
#define MAVLINK_MSG_ID_30034_LEN 4
#define MAVLINK_MSG_ID_30034_MIN_LEN 4

#define MAVLINK_MSG_ID_ElecAngleIdInput_CRC 156
#define MAVLINK_MSG_ID_30034_CRC 156



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_ElecAngleIdInput { \
    30034, \
    "ElecAngleIdInput", \
    1, \
    {  { "pos_now_rad", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_elecangleidinput_t, pos_now_rad) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_ElecAngleIdInput { \
    "ElecAngleIdInput", \
    1, \
    {  { "pos_now_rad", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_elecangleidinput_t, pos_now_rad) }, \
         } \
}
#endif

/**
 * @brief Pack a elecangleidinput message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param pos_now_rad  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_elecangleidinput_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               float pos_now_rad)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ElecAngleIdInput_LEN];
    _mav_put_float(buf, 0, pos_now_rad);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ElecAngleIdInput_LEN);
#else
    mavlink_elecangleidinput_t packet;
    packet.pos_now_rad = pos_now_rad;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ElecAngleIdInput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ElecAngleIdInput;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_ElecAngleIdInput_MIN_LEN, MAVLINK_MSG_ID_ElecAngleIdInput_LEN, MAVLINK_MSG_ID_ElecAngleIdInput_CRC);
}

/**
 * @brief Pack a elecangleidinput message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param pos_now_rad  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_elecangleidinput_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               float pos_now_rad)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ElecAngleIdInput_LEN];
    _mav_put_float(buf, 0, pos_now_rad);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ElecAngleIdInput_LEN);
#else
    mavlink_elecangleidinput_t packet;
    packet.pos_now_rad = pos_now_rad;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ElecAngleIdInput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ElecAngleIdInput;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_ElecAngleIdInput_MIN_LEN, MAVLINK_MSG_ID_ElecAngleIdInput_LEN, MAVLINK_MSG_ID_ElecAngleIdInput_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_ElecAngleIdInput_MIN_LEN, MAVLINK_MSG_ID_ElecAngleIdInput_LEN);
#endif
}

/**
 * @brief Pack a elecangleidinput message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param pos_now_rad  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_elecangleidinput_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   float pos_now_rad)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ElecAngleIdInput_LEN];
    _mav_put_float(buf, 0, pos_now_rad);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ElecAngleIdInput_LEN);
#else
    mavlink_elecangleidinput_t packet;
    packet.pos_now_rad = pos_now_rad;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ElecAngleIdInput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ElecAngleIdInput;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_ElecAngleIdInput_MIN_LEN, MAVLINK_MSG_ID_ElecAngleIdInput_LEN, MAVLINK_MSG_ID_ElecAngleIdInput_CRC);
}

/**
 * @brief Encode a elecangleidinput struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param elecangleidinput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_elecangleidinput_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_elecangleidinput_t* elecangleidinput)
{
    return mavlink_msg_elecangleidinput_pack(system_id, component_id, msg, elecangleidinput->pos_now_rad);
}

/**
 * @brief Encode a elecangleidinput struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param elecangleidinput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_elecangleidinput_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_elecangleidinput_t* elecangleidinput)
{
    return mavlink_msg_elecangleidinput_pack_chan(system_id, component_id, chan, msg, elecangleidinput->pos_now_rad);
}

/**
 * @brief Encode a elecangleidinput struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param elecangleidinput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_elecangleidinput_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_elecangleidinput_t* elecangleidinput)
{
    return mavlink_msg_elecangleidinput_pack_status(system_id, component_id, _status, msg,  elecangleidinput->pos_now_rad);
}

/**
 * @brief Send a elecangleidinput message
 * @param chan MAVLink channel to send the message
 *
 * @param pos_now_rad  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_elecangleidinput_send(mavlink_channel_t chan, float pos_now_rad)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ElecAngleIdInput_LEN];
    _mav_put_float(buf, 0, pos_now_rad);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ElecAngleIdInput, buf, MAVLINK_MSG_ID_ElecAngleIdInput_MIN_LEN, MAVLINK_MSG_ID_ElecAngleIdInput_LEN, MAVLINK_MSG_ID_ElecAngleIdInput_CRC);
#else
    mavlink_elecangleidinput_t packet;
    packet.pos_now_rad = pos_now_rad;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ElecAngleIdInput, (const char *)&packet, MAVLINK_MSG_ID_ElecAngleIdInput_MIN_LEN, MAVLINK_MSG_ID_ElecAngleIdInput_LEN, MAVLINK_MSG_ID_ElecAngleIdInput_CRC);
#endif
}

/**
 * @brief Send a elecangleidinput message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_elecangleidinput_send_struct(mavlink_channel_t chan, const mavlink_elecangleidinput_t* elecangleidinput)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_elecangleidinput_send(chan, elecangleidinput->pos_now_rad);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ElecAngleIdInput, (const char *)elecangleidinput, MAVLINK_MSG_ID_ElecAngleIdInput_MIN_LEN, MAVLINK_MSG_ID_ElecAngleIdInput_LEN, MAVLINK_MSG_ID_ElecAngleIdInput_CRC);
#endif
}

#if MAVLINK_MSG_ID_ElecAngleIdInput_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_elecangleidinput_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float pos_now_rad)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, pos_now_rad);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ElecAngleIdInput, buf, MAVLINK_MSG_ID_ElecAngleIdInput_MIN_LEN, MAVLINK_MSG_ID_ElecAngleIdInput_LEN, MAVLINK_MSG_ID_ElecAngleIdInput_CRC);
#else
    mavlink_elecangleidinput_t *packet = (mavlink_elecangleidinput_t *)msgbuf;
    packet->pos_now_rad = pos_now_rad;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ElecAngleIdInput, (const char *)packet, MAVLINK_MSG_ID_ElecAngleIdInput_MIN_LEN, MAVLINK_MSG_ID_ElecAngleIdInput_LEN, MAVLINK_MSG_ID_ElecAngleIdInput_CRC);
#endif
}
#endif

#endif

// MESSAGE ElecAngleIdInput UNPACKING


/**
 * @brief Get field pos_now_rad from elecangleidinput message
 *
 * @return  
 */
static inline float mavlink_msg_elecangleidinput_get_pos_now_rad(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Decode a elecangleidinput message into a struct
 *
 * @param msg The message to decode
 * @param elecangleidinput C-struct to decode the message contents into
 */
static inline void mavlink_msg_elecangleidinput_decode(const mavlink_message_t* msg, mavlink_elecangleidinput_t* elecangleidinput)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    elecangleidinput->pos_now_rad = mavlink_msg_elecangleidinput_get_pos_now_rad(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_ElecAngleIdInput_LEN? msg->len : MAVLINK_MSG_ID_ElecAngleIdInput_LEN;
        memset(elecangleidinput, 0, MAVLINK_MSG_ID_ElecAngleIdInput_LEN);
    memcpy(elecangleidinput, _MAV_PAYLOAD(msg), len);
#endif
}
