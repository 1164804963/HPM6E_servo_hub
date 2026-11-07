#pragma once
// MESSAGE MitCtlOutput PACKING

#define MAVLINK_MSG_ID_MitCtlOutput 30067


typedef struct __mavlink_mitctloutput_t {
 float iq_tar_A; /*<  */
} mavlink_mitctloutput_t;

#define MAVLINK_MSG_ID_MitCtlOutput_LEN 4
#define MAVLINK_MSG_ID_MitCtlOutput_MIN_LEN 4
#define MAVLINK_MSG_ID_30067_LEN 4
#define MAVLINK_MSG_ID_30067_MIN_LEN 4

#define MAVLINK_MSG_ID_MitCtlOutput_CRC 53
#define MAVLINK_MSG_ID_30067_CRC 53



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_MitCtlOutput { \
    30067, \
    "MitCtlOutput", \
    1, \
    {  { "iq_tar_A", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_mitctloutput_t, iq_tar_A) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_MitCtlOutput { \
    "MitCtlOutput", \
    1, \
    {  { "iq_tar_A", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_mitctloutput_t, iq_tar_A) }, \
         } \
}
#endif

/**
 * @brief Pack a mitctloutput message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param iq_tar_A  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_mitctloutput_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               float iq_tar_A)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MitCtlOutput_LEN];
    _mav_put_float(buf, 0, iq_tar_A);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MitCtlOutput_LEN);
#else
    mavlink_mitctloutput_t packet;
    packet.iq_tar_A = iq_tar_A;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MitCtlOutput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MitCtlOutput;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_MitCtlOutput_MIN_LEN, MAVLINK_MSG_ID_MitCtlOutput_LEN, MAVLINK_MSG_ID_MitCtlOutput_CRC);
}

/**
 * @brief Pack a mitctloutput message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param iq_tar_A  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_mitctloutput_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               float iq_tar_A)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MitCtlOutput_LEN];
    _mav_put_float(buf, 0, iq_tar_A);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MitCtlOutput_LEN);
#else
    mavlink_mitctloutput_t packet;
    packet.iq_tar_A = iq_tar_A;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MitCtlOutput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MitCtlOutput;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_MitCtlOutput_MIN_LEN, MAVLINK_MSG_ID_MitCtlOutput_LEN, MAVLINK_MSG_ID_MitCtlOutput_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_MitCtlOutput_MIN_LEN, MAVLINK_MSG_ID_MitCtlOutput_LEN);
#endif
}

/**
 * @brief Pack a mitctloutput message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param iq_tar_A  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_mitctloutput_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   float iq_tar_A)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MitCtlOutput_LEN];
    _mav_put_float(buf, 0, iq_tar_A);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MitCtlOutput_LEN);
#else
    mavlink_mitctloutput_t packet;
    packet.iq_tar_A = iq_tar_A;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MitCtlOutput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MitCtlOutput;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_MitCtlOutput_MIN_LEN, MAVLINK_MSG_ID_MitCtlOutput_LEN, MAVLINK_MSG_ID_MitCtlOutput_CRC);
}

/**
 * @brief Encode a mitctloutput struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param mitctloutput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_mitctloutput_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_mitctloutput_t* mitctloutput)
{
    return mavlink_msg_mitctloutput_pack(system_id, component_id, msg, mitctloutput->iq_tar_A);
}

/**
 * @brief Encode a mitctloutput struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param mitctloutput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_mitctloutput_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_mitctloutput_t* mitctloutput)
{
    return mavlink_msg_mitctloutput_pack_chan(system_id, component_id, chan, msg, mitctloutput->iq_tar_A);
}

/**
 * @brief Encode a mitctloutput struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param mitctloutput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_mitctloutput_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_mitctloutput_t* mitctloutput)
{
    return mavlink_msg_mitctloutput_pack_status(system_id, component_id, _status, msg,  mitctloutput->iq_tar_A);
}

/**
 * @brief Send a mitctloutput message
 * @param chan MAVLink channel to send the message
 *
 * @param iq_tar_A  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_mitctloutput_send(mavlink_channel_t chan, float iq_tar_A)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MitCtlOutput_LEN];
    _mav_put_float(buf, 0, iq_tar_A);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MitCtlOutput, buf, MAVLINK_MSG_ID_MitCtlOutput_MIN_LEN, MAVLINK_MSG_ID_MitCtlOutput_LEN, MAVLINK_MSG_ID_MitCtlOutput_CRC);
#else
    mavlink_mitctloutput_t packet;
    packet.iq_tar_A = iq_tar_A;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MitCtlOutput, (const char *)&packet, MAVLINK_MSG_ID_MitCtlOutput_MIN_LEN, MAVLINK_MSG_ID_MitCtlOutput_LEN, MAVLINK_MSG_ID_MitCtlOutput_CRC);
#endif
}

/**
 * @brief Send a mitctloutput message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_mitctloutput_send_struct(mavlink_channel_t chan, const mavlink_mitctloutput_t* mitctloutput)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_mitctloutput_send(chan, mitctloutput->iq_tar_A);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MitCtlOutput, (const char *)mitctloutput, MAVLINK_MSG_ID_MitCtlOutput_MIN_LEN, MAVLINK_MSG_ID_MitCtlOutput_LEN, MAVLINK_MSG_ID_MitCtlOutput_CRC);
#endif
}

#if MAVLINK_MSG_ID_MitCtlOutput_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_mitctloutput_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float iq_tar_A)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, iq_tar_A);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MitCtlOutput, buf, MAVLINK_MSG_ID_MitCtlOutput_MIN_LEN, MAVLINK_MSG_ID_MitCtlOutput_LEN, MAVLINK_MSG_ID_MitCtlOutput_CRC);
#else
    mavlink_mitctloutput_t *packet = (mavlink_mitctloutput_t *)msgbuf;
    packet->iq_tar_A = iq_tar_A;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MitCtlOutput, (const char *)packet, MAVLINK_MSG_ID_MitCtlOutput_MIN_LEN, MAVLINK_MSG_ID_MitCtlOutput_LEN, MAVLINK_MSG_ID_MitCtlOutput_CRC);
#endif
}
#endif

#endif

// MESSAGE MitCtlOutput UNPACKING


/**
 * @brief Get field iq_tar_A from mitctloutput message
 *
 * @return  
 */
static inline float mavlink_msg_mitctloutput_get_iq_tar_A(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Decode a mitctloutput message into a struct
 *
 * @param msg The message to decode
 * @param mitctloutput C-struct to decode the message contents into
 */
static inline void mavlink_msg_mitctloutput_decode(const mavlink_message_t* msg, mavlink_mitctloutput_t* mitctloutput)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mitctloutput->iq_tar_A = mavlink_msg_mitctloutput_get_iq_tar_A(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_MitCtlOutput_LEN? msg->len : MAVLINK_MSG_ID_MitCtlOutput_LEN;
        memset(mitctloutput, 0, MAVLINK_MSG_ID_MitCtlOutput_LEN);
    memcpy(mitctloutput, _MAV_PAYLOAD(msg), len);
#endif
}
