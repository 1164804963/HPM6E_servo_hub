#pragma once
// MESSAGE NotchFilterInput PACKING

#define MAVLINK_MSG_ID_NotchFilterInput 30007


typedef struct __mavlink_notchfilterinput_t {
 float iq_tar_A; /*<  */
} mavlink_notchfilterinput_t;

#define MAVLINK_MSG_ID_NotchFilterInput_LEN 4
#define MAVLINK_MSG_ID_NotchFilterInput_MIN_LEN 4
#define MAVLINK_MSG_ID_30007_LEN 4
#define MAVLINK_MSG_ID_30007_MIN_LEN 4

#define MAVLINK_MSG_ID_NotchFilterInput_CRC 247
#define MAVLINK_MSG_ID_30007_CRC 247



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_NotchFilterInput { \
    30007, \
    "NotchFilterInput", \
    1, \
    {  { "iq_tar_A", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_notchfilterinput_t, iq_tar_A) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_NotchFilterInput { \
    "NotchFilterInput", \
    1, \
    {  { "iq_tar_A", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_notchfilterinput_t, iq_tar_A) }, \
         } \
}
#endif

/**
 * @brief Pack a notchfilterinput message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param iq_tar_A  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_notchfilterinput_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               float iq_tar_A)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_NotchFilterInput_LEN];
    _mav_put_float(buf, 0, iq_tar_A);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_NotchFilterInput_LEN);
#else
    mavlink_notchfilterinput_t packet;
    packet.iq_tar_A = iq_tar_A;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_NotchFilterInput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_NotchFilterInput;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_NotchFilterInput_MIN_LEN, MAVLINK_MSG_ID_NotchFilterInput_LEN, MAVLINK_MSG_ID_NotchFilterInput_CRC);
}

/**
 * @brief Pack a notchfilterinput message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param iq_tar_A  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_notchfilterinput_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               float iq_tar_A)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_NotchFilterInput_LEN];
    _mav_put_float(buf, 0, iq_tar_A);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_NotchFilterInput_LEN);
#else
    mavlink_notchfilterinput_t packet;
    packet.iq_tar_A = iq_tar_A;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_NotchFilterInput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_NotchFilterInput;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_NotchFilterInput_MIN_LEN, MAVLINK_MSG_ID_NotchFilterInput_LEN, MAVLINK_MSG_ID_NotchFilterInput_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_NotchFilterInput_MIN_LEN, MAVLINK_MSG_ID_NotchFilterInput_LEN);
#endif
}

/**
 * @brief Pack a notchfilterinput message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param iq_tar_A  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_notchfilterinput_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   float iq_tar_A)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_NotchFilterInput_LEN];
    _mav_put_float(buf, 0, iq_tar_A);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_NotchFilterInput_LEN);
#else
    mavlink_notchfilterinput_t packet;
    packet.iq_tar_A = iq_tar_A;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_NotchFilterInput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_NotchFilterInput;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_NotchFilterInput_MIN_LEN, MAVLINK_MSG_ID_NotchFilterInput_LEN, MAVLINK_MSG_ID_NotchFilterInput_CRC);
}

/**
 * @brief Encode a notchfilterinput struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param notchfilterinput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_notchfilterinput_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_notchfilterinput_t* notchfilterinput)
{
    return mavlink_msg_notchfilterinput_pack(system_id, component_id, msg, notchfilterinput->iq_tar_A);
}

/**
 * @brief Encode a notchfilterinput struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param notchfilterinput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_notchfilterinput_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_notchfilterinput_t* notchfilterinput)
{
    return mavlink_msg_notchfilterinput_pack_chan(system_id, component_id, chan, msg, notchfilterinput->iq_tar_A);
}

/**
 * @brief Encode a notchfilterinput struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param notchfilterinput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_notchfilterinput_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_notchfilterinput_t* notchfilterinput)
{
    return mavlink_msg_notchfilterinput_pack_status(system_id, component_id, _status, msg,  notchfilterinput->iq_tar_A);
}

/**
 * @brief Send a notchfilterinput message
 * @param chan MAVLink channel to send the message
 *
 * @param iq_tar_A  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_notchfilterinput_send(mavlink_channel_t chan, float iq_tar_A)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_NotchFilterInput_LEN];
    _mav_put_float(buf, 0, iq_tar_A);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_NotchFilterInput, buf, MAVLINK_MSG_ID_NotchFilterInput_MIN_LEN, MAVLINK_MSG_ID_NotchFilterInput_LEN, MAVLINK_MSG_ID_NotchFilterInput_CRC);
#else
    mavlink_notchfilterinput_t packet;
    packet.iq_tar_A = iq_tar_A;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_NotchFilterInput, (const char *)&packet, MAVLINK_MSG_ID_NotchFilterInput_MIN_LEN, MAVLINK_MSG_ID_NotchFilterInput_LEN, MAVLINK_MSG_ID_NotchFilterInput_CRC);
#endif
}

/**
 * @brief Send a notchfilterinput message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_notchfilterinput_send_struct(mavlink_channel_t chan, const mavlink_notchfilterinput_t* notchfilterinput)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_notchfilterinput_send(chan, notchfilterinput->iq_tar_A);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_NotchFilterInput, (const char *)notchfilterinput, MAVLINK_MSG_ID_NotchFilterInput_MIN_LEN, MAVLINK_MSG_ID_NotchFilterInput_LEN, MAVLINK_MSG_ID_NotchFilterInput_CRC);
#endif
}

#if MAVLINK_MSG_ID_NotchFilterInput_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_notchfilterinput_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float iq_tar_A)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, iq_tar_A);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_NotchFilterInput, buf, MAVLINK_MSG_ID_NotchFilterInput_MIN_LEN, MAVLINK_MSG_ID_NotchFilterInput_LEN, MAVLINK_MSG_ID_NotchFilterInput_CRC);
#else
    mavlink_notchfilterinput_t *packet = (mavlink_notchfilterinput_t *)msgbuf;
    packet->iq_tar_A = iq_tar_A;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_NotchFilterInput, (const char *)packet, MAVLINK_MSG_ID_NotchFilterInput_MIN_LEN, MAVLINK_MSG_ID_NotchFilterInput_LEN, MAVLINK_MSG_ID_NotchFilterInput_CRC);
#endif
}
#endif

#endif

// MESSAGE NotchFilterInput UNPACKING


/**
 * @brief Get field iq_tar_A from notchfilterinput message
 *
 * @return  
 */
static inline float mavlink_msg_notchfilterinput_get_iq_tar_A(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Decode a notchfilterinput message into a struct
 *
 * @param msg The message to decode
 * @param notchfilterinput C-struct to decode the message contents into
 */
static inline void mavlink_msg_notchfilterinput_decode(const mavlink_message_t* msg, mavlink_notchfilterinput_t* notchfilterinput)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    notchfilterinput->iq_tar_A = mavlink_msg_notchfilterinput_get_iq_tar_A(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_NotchFilterInput_LEN? msg->len : MAVLINK_MSG_ID_NotchFilterInput_LEN;
        memset(notchfilterinput, 0, MAVLINK_MSG_ID_NotchFilterInput_LEN);
    memcpy(notchfilterinput, _MAV_PAYLOAD(msg), len);
#endif
}
