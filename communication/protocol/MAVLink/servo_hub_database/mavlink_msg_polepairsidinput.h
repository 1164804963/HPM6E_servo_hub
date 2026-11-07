#pragma once
// MESSAGE PolePairsIdInput PACKING

#define MAVLINK_MSG_ID_PolePairsIdInput 30041


typedef struct __mavlink_polepairsidinput_t {
 int64_t enc_counts_sum_p; /*<  */
} mavlink_polepairsidinput_t;

#define MAVLINK_MSG_ID_PolePairsIdInput_LEN 8
#define MAVLINK_MSG_ID_PolePairsIdInput_MIN_LEN 8
#define MAVLINK_MSG_ID_30041_LEN 8
#define MAVLINK_MSG_ID_30041_MIN_LEN 8

#define MAVLINK_MSG_ID_PolePairsIdInput_CRC 88
#define MAVLINK_MSG_ID_30041_CRC 88



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_PolePairsIdInput { \
    30041, \
    "PolePairsIdInput", \
    1, \
    {  { "enc_counts_sum_p", NULL, MAVLINK_TYPE_INT64_T, 0, 0, offsetof(mavlink_polepairsidinput_t, enc_counts_sum_p) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_PolePairsIdInput { \
    "PolePairsIdInput", \
    1, \
    {  { "enc_counts_sum_p", NULL, MAVLINK_TYPE_INT64_T, 0, 0, offsetof(mavlink_polepairsidinput_t, enc_counts_sum_p) }, \
         } \
}
#endif

/**
 * @brief Pack a polepairsidinput message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param enc_counts_sum_p  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_polepairsidinput_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               int64_t enc_counts_sum_p)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PolePairsIdInput_LEN];
    _mav_put_int64_t(buf, 0, enc_counts_sum_p);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_PolePairsIdInput_LEN);
#else
    mavlink_polepairsidinput_t packet;
    packet.enc_counts_sum_p = enc_counts_sum_p;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_PolePairsIdInput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_PolePairsIdInput;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_PolePairsIdInput_MIN_LEN, MAVLINK_MSG_ID_PolePairsIdInput_LEN, MAVLINK_MSG_ID_PolePairsIdInput_CRC);
}

/**
 * @brief Pack a polepairsidinput message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param enc_counts_sum_p  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_polepairsidinput_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               int64_t enc_counts_sum_p)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PolePairsIdInput_LEN];
    _mav_put_int64_t(buf, 0, enc_counts_sum_p);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_PolePairsIdInput_LEN);
#else
    mavlink_polepairsidinput_t packet;
    packet.enc_counts_sum_p = enc_counts_sum_p;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_PolePairsIdInput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_PolePairsIdInput;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_PolePairsIdInput_MIN_LEN, MAVLINK_MSG_ID_PolePairsIdInput_LEN, MAVLINK_MSG_ID_PolePairsIdInput_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_PolePairsIdInput_MIN_LEN, MAVLINK_MSG_ID_PolePairsIdInput_LEN);
#endif
}

/**
 * @brief Pack a polepairsidinput message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param enc_counts_sum_p  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_polepairsidinput_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   int64_t enc_counts_sum_p)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PolePairsIdInput_LEN];
    _mav_put_int64_t(buf, 0, enc_counts_sum_p);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_PolePairsIdInput_LEN);
#else
    mavlink_polepairsidinput_t packet;
    packet.enc_counts_sum_p = enc_counts_sum_p;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_PolePairsIdInput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_PolePairsIdInput;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_PolePairsIdInput_MIN_LEN, MAVLINK_MSG_ID_PolePairsIdInput_LEN, MAVLINK_MSG_ID_PolePairsIdInput_CRC);
}

/**
 * @brief Encode a polepairsidinput struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param polepairsidinput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_polepairsidinput_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_polepairsidinput_t* polepairsidinput)
{
    return mavlink_msg_polepairsidinput_pack(system_id, component_id, msg, polepairsidinput->enc_counts_sum_p);
}

/**
 * @brief Encode a polepairsidinput struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param polepairsidinput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_polepairsidinput_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_polepairsidinput_t* polepairsidinput)
{
    return mavlink_msg_polepairsidinput_pack_chan(system_id, component_id, chan, msg, polepairsidinput->enc_counts_sum_p);
}

/**
 * @brief Encode a polepairsidinput struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param polepairsidinput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_polepairsidinput_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_polepairsidinput_t* polepairsidinput)
{
    return mavlink_msg_polepairsidinput_pack_status(system_id, component_id, _status, msg,  polepairsidinput->enc_counts_sum_p);
}

/**
 * @brief Send a polepairsidinput message
 * @param chan MAVLink channel to send the message
 *
 * @param enc_counts_sum_p  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_polepairsidinput_send(mavlink_channel_t chan, int64_t enc_counts_sum_p)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PolePairsIdInput_LEN];
    _mav_put_int64_t(buf, 0, enc_counts_sum_p);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PolePairsIdInput, buf, MAVLINK_MSG_ID_PolePairsIdInput_MIN_LEN, MAVLINK_MSG_ID_PolePairsIdInput_LEN, MAVLINK_MSG_ID_PolePairsIdInput_CRC);
#else
    mavlink_polepairsidinput_t packet;
    packet.enc_counts_sum_p = enc_counts_sum_p;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PolePairsIdInput, (const char *)&packet, MAVLINK_MSG_ID_PolePairsIdInput_MIN_LEN, MAVLINK_MSG_ID_PolePairsIdInput_LEN, MAVLINK_MSG_ID_PolePairsIdInput_CRC);
#endif
}

/**
 * @brief Send a polepairsidinput message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_polepairsidinput_send_struct(mavlink_channel_t chan, const mavlink_polepairsidinput_t* polepairsidinput)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_polepairsidinput_send(chan, polepairsidinput->enc_counts_sum_p);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PolePairsIdInput, (const char *)polepairsidinput, MAVLINK_MSG_ID_PolePairsIdInput_MIN_LEN, MAVLINK_MSG_ID_PolePairsIdInput_LEN, MAVLINK_MSG_ID_PolePairsIdInput_CRC);
#endif
}

#if MAVLINK_MSG_ID_PolePairsIdInput_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_polepairsidinput_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  int64_t enc_counts_sum_p)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_int64_t(buf, 0, enc_counts_sum_p);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PolePairsIdInput, buf, MAVLINK_MSG_ID_PolePairsIdInput_MIN_LEN, MAVLINK_MSG_ID_PolePairsIdInput_LEN, MAVLINK_MSG_ID_PolePairsIdInput_CRC);
#else
    mavlink_polepairsidinput_t *packet = (mavlink_polepairsidinput_t *)msgbuf;
    packet->enc_counts_sum_p = enc_counts_sum_p;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PolePairsIdInput, (const char *)packet, MAVLINK_MSG_ID_PolePairsIdInput_MIN_LEN, MAVLINK_MSG_ID_PolePairsIdInput_LEN, MAVLINK_MSG_ID_PolePairsIdInput_CRC);
#endif
}
#endif

#endif

// MESSAGE PolePairsIdInput UNPACKING


/**
 * @brief Get field enc_counts_sum_p from polepairsidinput message
 *
 * @return  
 */
static inline int64_t mavlink_msg_polepairsidinput_get_enc_counts_sum_p(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int64_t(msg,  0);
}

/**
 * @brief Decode a polepairsidinput message into a struct
 *
 * @param msg The message to decode
 * @param polepairsidinput C-struct to decode the message contents into
 */
static inline void mavlink_msg_polepairsidinput_decode(const mavlink_message_t* msg, mavlink_polepairsidinput_t* polepairsidinput)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    polepairsidinput->enc_counts_sum_p = mavlink_msg_polepairsidinput_get_enc_counts_sum_p(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_PolePairsIdInput_LEN? msg->len : MAVLINK_MSG_ID_PolePairsIdInput_LEN;
        memset(polepairsidinput, 0, MAVLINK_MSG_ID_PolePairsIdInput_LEN);
    memcpy(polepairsidinput, _MAV_PAYLOAD(msg), len);
#endif
}
