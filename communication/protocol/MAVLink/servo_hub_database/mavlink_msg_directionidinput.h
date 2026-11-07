#pragma once
// MESSAGE DirectionIdInput PACKING

#define MAVLINK_MSG_ID_DirectionIdInput 30035


typedef struct __mavlink_directionidinput_t {
 int64_t enc_counts_sum_p; /*<  */
} mavlink_directionidinput_t;

#define MAVLINK_MSG_ID_DirectionIdInput_LEN 8
#define MAVLINK_MSG_ID_DirectionIdInput_MIN_LEN 8
#define MAVLINK_MSG_ID_30035_LEN 8
#define MAVLINK_MSG_ID_30035_MIN_LEN 8

#define MAVLINK_MSG_ID_DirectionIdInput_CRC 232
#define MAVLINK_MSG_ID_30035_CRC 232



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_DirectionIdInput { \
    30035, \
    "DirectionIdInput", \
    1, \
    {  { "enc_counts_sum_p", NULL, MAVLINK_TYPE_INT64_T, 0, 0, offsetof(mavlink_directionidinput_t, enc_counts_sum_p) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_DirectionIdInput { \
    "DirectionIdInput", \
    1, \
    {  { "enc_counts_sum_p", NULL, MAVLINK_TYPE_INT64_T, 0, 0, offsetof(mavlink_directionidinput_t, enc_counts_sum_p) }, \
         } \
}
#endif

/**
 * @brief Pack a directionidinput message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param enc_counts_sum_p  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_directionidinput_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               int64_t enc_counts_sum_p)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_DirectionIdInput_LEN];
    _mav_put_int64_t(buf, 0, enc_counts_sum_p);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_DirectionIdInput_LEN);
#else
    mavlink_directionidinput_t packet;
    packet.enc_counts_sum_p = enc_counts_sum_p;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_DirectionIdInput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_DirectionIdInput;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_DirectionIdInput_MIN_LEN, MAVLINK_MSG_ID_DirectionIdInput_LEN, MAVLINK_MSG_ID_DirectionIdInput_CRC);
}

/**
 * @brief Pack a directionidinput message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param enc_counts_sum_p  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_directionidinput_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               int64_t enc_counts_sum_p)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_DirectionIdInput_LEN];
    _mav_put_int64_t(buf, 0, enc_counts_sum_p);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_DirectionIdInput_LEN);
#else
    mavlink_directionidinput_t packet;
    packet.enc_counts_sum_p = enc_counts_sum_p;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_DirectionIdInput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_DirectionIdInput;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_DirectionIdInput_MIN_LEN, MAVLINK_MSG_ID_DirectionIdInput_LEN, MAVLINK_MSG_ID_DirectionIdInput_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_DirectionIdInput_MIN_LEN, MAVLINK_MSG_ID_DirectionIdInput_LEN);
#endif
}

/**
 * @brief Pack a directionidinput message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param enc_counts_sum_p  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_directionidinput_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   int64_t enc_counts_sum_p)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_DirectionIdInput_LEN];
    _mav_put_int64_t(buf, 0, enc_counts_sum_p);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_DirectionIdInput_LEN);
#else
    mavlink_directionidinput_t packet;
    packet.enc_counts_sum_p = enc_counts_sum_p;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_DirectionIdInput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_DirectionIdInput;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_DirectionIdInput_MIN_LEN, MAVLINK_MSG_ID_DirectionIdInput_LEN, MAVLINK_MSG_ID_DirectionIdInput_CRC);
}

/**
 * @brief Encode a directionidinput struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param directionidinput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_directionidinput_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_directionidinput_t* directionidinput)
{
    return mavlink_msg_directionidinput_pack(system_id, component_id, msg, directionidinput->enc_counts_sum_p);
}

/**
 * @brief Encode a directionidinput struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param directionidinput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_directionidinput_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_directionidinput_t* directionidinput)
{
    return mavlink_msg_directionidinput_pack_chan(system_id, component_id, chan, msg, directionidinput->enc_counts_sum_p);
}

/**
 * @brief Encode a directionidinput struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param directionidinput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_directionidinput_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_directionidinput_t* directionidinput)
{
    return mavlink_msg_directionidinput_pack_status(system_id, component_id, _status, msg,  directionidinput->enc_counts_sum_p);
}

/**
 * @brief Send a directionidinput message
 * @param chan MAVLink channel to send the message
 *
 * @param enc_counts_sum_p  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_directionidinput_send(mavlink_channel_t chan, int64_t enc_counts_sum_p)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_DirectionIdInput_LEN];
    _mav_put_int64_t(buf, 0, enc_counts_sum_p);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_DirectionIdInput, buf, MAVLINK_MSG_ID_DirectionIdInput_MIN_LEN, MAVLINK_MSG_ID_DirectionIdInput_LEN, MAVLINK_MSG_ID_DirectionIdInput_CRC);
#else
    mavlink_directionidinput_t packet;
    packet.enc_counts_sum_p = enc_counts_sum_p;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_DirectionIdInput, (const char *)&packet, MAVLINK_MSG_ID_DirectionIdInput_MIN_LEN, MAVLINK_MSG_ID_DirectionIdInput_LEN, MAVLINK_MSG_ID_DirectionIdInput_CRC);
#endif
}

/**
 * @brief Send a directionidinput message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_directionidinput_send_struct(mavlink_channel_t chan, const mavlink_directionidinput_t* directionidinput)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_directionidinput_send(chan, directionidinput->enc_counts_sum_p);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_DirectionIdInput, (const char *)directionidinput, MAVLINK_MSG_ID_DirectionIdInput_MIN_LEN, MAVLINK_MSG_ID_DirectionIdInput_LEN, MAVLINK_MSG_ID_DirectionIdInput_CRC);
#endif
}

#if MAVLINK_MSG_ID_DirectionIdInput_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_directionidinput_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  int64_t enc_counts_sum_p)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_int64_t(buf, 0, enc_counts_sum_p);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_DirectionIdInput, buf, MAVLINK_MSG_ID_DirectionIdInput_MIN_LEN, MAVLINK_MSG_ID_DirectionIdInput_LEN, MAVLINK_MSG_ID_DirectionIdInput_CRC);
#else
    mavlink_directionidinput_t *packet = (mavlink_directionidinput_t *)msgbuf;
    packet->enc_counts_sum_p = enc_counts_sum_p;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_DirectionIdInput, (const char *)packet, MAVLINK_MSG_ID_DirectionIdInput_MIN_LEN, MAVLINK_MSG_ID_DirectionIdInput_LEN, MAVLINK_MSG_ID_DirectionIdInput_CRC);
#endif
}
#endif

#endif

// MESSAGE DirectionIdInput UNPACKING


/**
 * @brief Get field enc_counts_sum_p from directionidinput message
 *
 * @return  
 */
static inline int64_t mavlink_msg_directionidinput_get_enc_counts_sum_p(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int64_t(msg,  0);
}

/**
 * @brief Decode a directionidinput message into a struct
 *
 * @param msg The message to decode
 * @param directionidinput C-struct to decode the message contents into
 */
static inline void mavlink_msg_directionidinput_decode(const mavlink_message_t* msg, mavlink_directionidinput_t* directionidinput)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    directionidinput->enc_counts_sum_p = mavlink_msg_directionidinput_get_enc_counts_sum_p(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_DirectionIdInput_LEN? msg->len : MAVLINK_MSG_ID_DirectionIdInput_LEN;
        memset(directionidinput, 0, MAVLINK_MSG_ID_DirectionIdInput_LEN);
    memcpy(directionidinput, _MAV_PAYLOAD(msg), len);
#endif
}
