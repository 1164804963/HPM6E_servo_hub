#pragma once
// MESSAGE MecIdOutput PACKING

#define MAVLINK_MSG_ID_MecIdOutput 30005


typedef struct __mavlink_mecidoutput_t {
 float iq_tar_A; /*<  */
 int8_t state_now; /*<  */
} mavlink_mecidoutput_t;

#define MAVLINK_MSG_ID_MecIdOutput_LEN 5
#define MAVLINK_MSG_ID_MecIdOutput_MIN_LEN 5
#define MAVLINK_MSG_ID_30005_LEN 5
#define MAVLINK_MSG_ID_30005_MIN_LEN 5

#define MAVLINK_MSG_ID_MecIdOutput_CRC 99
#define MAVLINK_MSG_ID_30005_CRC 99



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_MecIdOutput { \
    30005, \
    "MecIdOutput", \
    2, \
    {  { "iq_tar_A", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_mecidoutput_t, iq_tar_A) }, \
         { "state_now", NULL, MAVLINK_TYPE_INT8_T, 0, 4, offsetof(mavlink_mecidoutput_t, state_now) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_MecIdOutput { \
    "MecIdOutput", \
    2, \
    {  { "iq_tar_A", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_mecidoutput_t, iq_tar_A) }, \
         { "state_now", NULL, MAVLINK_TYPE_INT8_T, 0, 4, offsetof(mavlink_mecidoutput_t, state_now) }, \
         } \
}
#endif

/**
 * @brief Pack a mecidoutput message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param iq_tar_A  
 * @param state_now  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_mecidoutput_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               float iq_tar_A, int8_t state_now)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MecIdOutput_LEN];
    _mav_put_float(buf, 0, iq_tar_A);
    _mav_put_int8_t(buf, 4, state_now);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MecIdOutput_LEN);
#else
    mavlink_mecidoutput_t packet;
    packet.iq_tar_A = iq_tar_A;
    packet.state_now = state_now;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MecIdOutput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MecIdOutput;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_MecIdOutput_MIN_LEN, MAVLINK_MSG_ID_MecIdOutput_LEN, MAVLINK_MSG_ID_MecIdOutput_CRC);
}

/**
 * @brief Pack a mecidoutput message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param iq_tar_A  
 * @param state_now  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_mecidoutput_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               float iq_tar_A, int8_t state_now)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MecIdOutput_LEN];
    _mav_put_float(buf, 0, iq_tar_A);
    _mav_put_int8_t(buf, 4, state_now);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MecIdOutput_LEN);
#else
    mavlink_mecidoutput_t packet;
    packet.iq_tar_A = iq_tar_A;
    packet.state_now = state_now;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MecIdOutput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MecIdOutput;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_MecIdOutput_MIN_LEN, MAVLINK_MSG_ID_MecIdOutput_LEN, MAVLINK_MSG_ID_MecIdOutput_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_MecIdOutput_MIN_LEN, MAVLINK_MSG_ID_MecIdOutput_LEN);
#endif
}

/**
 * @brief Pack a mecidoutput message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param iq_tar_A  
 * @param state_now  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_mecidoutput_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   float iq_tar_A,int8_t state_now)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MecIdOutput_LEN];
    _mav_put_float(buf, 0, iq_tar_A);
    _mav_put_int8_t(buf, 4, state_now);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MecIdOutput_LEN);
#else
    mavlink_mecidoutput_t packet;
    packet.iq_tar_A = iq_tar_A;
    packet.state_now = state_now;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MecIdOutput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MecIdOutput;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_MecIdOutput_MIN_LEN, MAVLINK_MSG_ID_MecIdOutput_LEN, MAVLINK_MSG_ID_MecIdOutput_CRC);
}

/**
 * @brief Encode a mecidoutput struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param mecidoutput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_mecidoutput_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_mecidoutput_t* mecidoutput)
{
    return mavlink_msg_mecidoutput_pack(system_id, component_id, msg, mecidoutput->iq_tar_A, mecidoutput->state_now);
}

/**
 * @brief Encode a mecidoutput struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param mecidoutput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_mecidoutput_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_mecidoutput_t* mecidoutput)
{
    return mavlink_msg_mecidoutput_pack_chan(system_id, component_id, chan, msg, mecidoutput->iq_tar_A, mecidoutput->state_now);
}

/**
 * @brief Encode a mecidoutput struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param mecidoutput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_mecidoutput_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_mecidoutput_t* mecidoutput)
{
    return mavlink_msg_mecidoutput_pack_status(system_id, component_id, _status, msg,  mecidoutput->iq_tar_A, mecidoutput->state_now);
}

/**
 * @brief Send a mecidoutput message
 * @param chan MAVLink channel to send the message
 *
 * @param iq_tar_A  
 * @param state_now  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_mecidoutput_send(mavlink_channel_t chan, float iq_tar_A, int8_t state_now)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MecIdOutput_LEN];
    _mav_put_float(buf, 0, iq_tar_A);
    _mav_put_int8_t(buf, 4, state_now);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MecIdOutput, buf, MAVLINK_MSG_ID_MecIdOutput_MIN_LEN, MAVLINK_MSG_ID_MecIdOutput_LEN, MAVLINK_MSG_ID_MecIdOutput_CRC);
#else
    mavlink_mecidoutput_t packet;
    packet.iq_tar_A = iq_tar_A;
    packet.state_now = state_now;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MecIdOutput, (const char *)&packet, MAVLINK_MSG_ID_MecIdOutput_MIN_LEN, MAVLINK_MSG_ID_MecIdOutput_LEN, MAVLINK_MSG_ID_MecIdOutput_CRC);
#endif
}

/**
 * @brief Send a mecidoutput message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_mecidoutput_send_struct(mavlink_channel_t chan, const mavlink_mecidoutput_t* mecidoutput)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_mecidoutput_send(chan, mecidoutput->iq_tar_A, mecidoutput->state_now);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MecIdOutput, (const char *)mecidoutput, MAVLINK_MSG_ID_MecIdOutput_MIN_LEN, MAVLINK_MSG_ID_MecIdOutput_LEN, MAVLINK_MSG_ID_MecIdOutput_CRC);
#endif
}

#if MAVLINK_MSG_ID_MecIdOutput_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_mecidoutput_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float iq_tar_A, int8_t state_now)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, iq_tar_A);
    _mav_put_int8_t(buf, 4, state_now);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MecIdOutput, buf, MAVLINK_MSG_ID_MecIdOutput_MIN_LEN, MAVLINK_MSG_ID_MecIdOutput_LEN, MAVLINK_MSG_ID_MecIdOutput_CRC);
#else
    mavlink_mecidoutput_t *packet = (mavlink_mecidoutput_t *)msgbuf;
    packet->iq_tar_A = iq_tar_A;
    packet->state_now = state_now;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MecIdOutput, (const char *)packet, MAVLINK_MSG_ID_MecIdOutput_MIN_LEN, MAVLINK_MSG_ID_MecIdOutput_LEN, MAVLINK_MSG_ID_MecIdOutput_CRC);
#endif
}
#endif

#endif

// MESSAGE MecIdOutput UNPACKING


/**
 * @brief Get field iq_tar_A from mecidoutput message
 *
 * @return  
 */
static inline float mavlink_msg_mecidoutput_get_iq_tar_A(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field state_now from mecidoutput message
 *
 * @return  
 */
static inline int8_t mavlink_msg_mecidoutput_get_state_now(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int8_t(msg,  4);
}

/**
 * @brief Decode a mecidoutput message into a struct
 *
 * @param msg The message to decode
 * @param mecidoutput C-struct to decode the message contents into
 */
static inline void mavlink_msg_mecidoutput_decode(const mavlink_message_t* msg, mavlink_mecidoutput_t* mecidoutput)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mecidoutput->iq_tar_A = mavlink_msg_mecidoutput_get_iq_tar_A(msg);
    mecidoutput->state_now = mavlink_msg_mecidoutput_get_state_now(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_MecIdOutput_LEN? msg->len : MAVLINK_MSG_ID_MecIdOutput_LEN;
        memset(mecidoutput, 0, MAVLINK_MSG_ID_MecIdOutput_LEN);
    memcpy(mecidoutput, _MAV_PAYLOAD(msg), len);
#endif
}
