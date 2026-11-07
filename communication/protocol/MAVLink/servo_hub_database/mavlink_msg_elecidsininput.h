#pragma once
// MESSAGE ElecIdSinInput PACKING

#define MAVLINK_MSG_ID_ElecIdSinInput 30002


typedef struct __mavlink_elecidsininput_t {
 float i_abc_now_A[3]; /*<  */
} mavlink_elecidsininput_t;

#define MAVLINK_MSG_ID_ElecIdSinInput_LEN 12
#define MAVLINK_MSG_ID_ElecIdSinInput_MIN_LEN 12
#define MAVLINK_MSG_ID_30002_LEN 12
#define MAVLINK_MSG_ID_30002_MIN_LEN 12

#define MAVLINK_MSG_ID_ElecIdSinInput_CRC 47
#define MAVLINK_MSG_ID_30002_CRC 47

#define MAVLINK_MSG_ElecIdSinInput_FIELD_I_ABC_NOW_A_LEN 3

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_ElecIdSinInput { \
    30002, \
    "ElecIdSinInput", \
    1, \
    {  { "i_abc_now_A", NULL, MAVLINK_TYPE_FLOAT, 3, 0, offsetof(mavlink_elecidsininput_t, i_abc_now_A) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_ElecIdSinInput { \
    "ElecIdSinInput", \
    1, \
    {  { "i_abc_now_A", NULL, MAVLINK_TYPE_FLOAT, 3, 0, offsetof(mavlink_elecidsininput_t, i_abc_now_A) }, \
         } \
}
#endif

/**
 * @brief Pack a elecidsininput message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param i_abc_now_A  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_elecidsininput_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               const float *i_abc_now_A)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ElecIdSinInput_LEN];

    _mav_put_float_array(buf, 0, i_abc_now_A, 3);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ElecIdSinInput_LEN);
#else
    mavlink_elecidsininput_t packet;

    mav_array_memcpy(packet.i_abc_now_A, i_abc_now_A, sizeof(float)*3);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ElecIdSinInput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ElecIdSinInput;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_ElecIdSinInput_MIN_LEN, MAVLINK_MSG_ID_ElecIdSinInput_LEN, MAVLINK_MSG_ID_ElecIdSinInput_CRC);
}

/**
 * @brief Pack a elecidsininput message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param i_abc_now_A  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_elecidsininput_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               const float *i_abc_now_A)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ElecIdSinInput_LEN];

    _mav_put_float_array(buf, 0, i_abc_now_A, 3);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ElecIdSinInput_LEN);
#else
    mavlink_elecidsininput_t packet;

    mav_array_memcpy(packet.i_abc_now_A, i_abc_now_A, sizeof(float)*3);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ElecIdSinInput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ElecIdSinInput;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_ElecIdSinInput_MIN_LEN, MAVLINK_MSG_ID_ElecIdSinInput_LEN, MAVLINK_MSG_ID_ElecIdSinInput_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_ElecIdSinInput_MIN_LEN, MAVLINK_MSG_ID_ElecIdSinInput_LEN);
#endif
}

/**
 * @brief Pack a elecidsininput message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param i_abc_now_A  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_elecidsininput_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   const float *i_abc_now_A)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ElecIdSinInput_LEN];

    _mav_put_float_array(buf, 0, i_abc_now_A, 3);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ElecIdSinInput_LEN);
#else
    mavlink_elecidsininput_t packet;

    mav_array_memcpy(packet.i_abc_now_A, i_abc_now_A, sizeof(float)*3);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ElecIdSinInput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ElecIdSinInput;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_ElecIdSinInput_MIN_LEN, MAVLINK_MSG_ID_ElecIdSinInput_LEN, MAVLINK_MSG_ID_ElecIdSinInput_CRC);
}

/**
 * @brief Encode a elecidsininput struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param elecidsininput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_elecidsininput_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_elecidsininput_t* elecidsininput)
{
    return mavlink_msg_elecidsininput_pack(system_id, component_id, msg, elecidsininput->i_abc_now_A);
}

/**
 * @brief Encode a elecidsininput struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param elecidsininput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_elecidsininput_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_elecidsininput_t* elecidsininput)
{
    return mavlink_msg_elecidsininput_pack_chan(system_id, component_id, chan, msg, elecidsininput->i_abc_now_A);
}

/**
 * @brief Encode a elecidsininput struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param elecidsininput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_elecidsininput_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_elecidsininput_t* elecidsininput)
{
    return mavlink_msg_elecidsininput_pack_status(system_id, component_id, _status, msg,  elecidsininput->i_abc_now_A);
}

/**
 * @brief Send a elecidsininput message
 * @param chan MAVLink channel to send the message
 *
 * @param i_abc_now_A  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_elecidsininput_send(mavlink_channel_t chan, const float *i_abc_now_A)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ElecIdSinInput_LEN];

    _mav_put_float_array(buf, 0, i_abc_now_A, 3);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ElecIdSinInput, buf, MAVLINK_MSG_ID_ElecIdSinInput_MIN_LEN, MAVLINK_MSG_ID_ElecIdSinInput_LEN, MAVLINK_MSG_ID_ElecIdSinInput_CRC);
#else
    mavlink_elecidsininput_t packet;

    mav_array_memcpy(packet.i_abc_now_A, i_abc_now_A, sizeof(float)*3);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ElecIdSinInput, (const char *)&packet, MAVLINK_MSG_ID_ElecIdSinInput_MIN_LEN, MAVLINK_MSG_ID_ElecIdSinInput_LEN, MAVLINK_MSG_ID_ElecIdSinInput_CRC);
#endif
}

/**
 * @brief Send a elecidsininput message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_elecidsininput_send_struct(mavlink_channel_t chan, const mavlink_elecidsininput_t* elecidsininput)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_elecidsininput_send(chan, elecidsininput->i_abc_now_A);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ElecIdSinInput, (const char *)elecidsininput, MAVLINK_MSG_ID_ElecIdSinInput_MIN_LEN, MAVLINK_MSG_ID_ElecIdSinInput_LEN, MAVLINK_MSG_ID_ElecIdSinInput_CRC);
#endif
}

#if MAVLINK_MSG_ID_ElecIdSinInput_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_elecidsininput_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  const float *i_abc_now_A)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;

    _mav_put_float_array(buf, 0, i_abc_now_A, 3);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ElecIdSinInput, buf, MAVLINK_MSG_ID_ElecIdSinInput_MIN_LEN, MAVLINK_MSG_ID_ElecIdSinInput_LEN, MAVLINK_MSG_ID_ElecIdSinInput_CRC);
#else
    mavlink_elecidsininput_t *packet = (mavlink_elecidsininput_t *)msgbuf;

    mav_array_memcpy(packet->i_abc_now_A, i_abc_now_A, sizeof(float)*3);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ElecIdSinInput, (const char *)packet, MAVLINK_MSG_ID_ElecIdSinInput_MIN_LEN, MAVLINK_MSG_ID_ElecIdSinInput_LEN, MAVLINK_MSG_ID_ElecIdSinInput_CRC);
#endif
}
#endif

#endif

// MESSAGE ElecIdSinInput UNPACKING


/**
 * @brief Get field i_abc_now_A from elecidsininput message
 *
 * @return  
 */
static inline uint16_t mavlink_msg_elecidsininput_get_i_abc_now_A(const mavlink_message_t* msg, float *i_abc_now_A)
{
    return _MAV_RETURN_float_array(msg, i_abc_now_A, 3,  0);
}

/**
 * @brief Decode a elecidsininput message into a struct
 *
 * @param msg The message to decode
 * @param elecidsininput C-struct to decode the message contents into
 */
static inline void mavlink_msg_elecidsininput_decode(const mavlink_message_t* msg, mavlink_elecidsininput_t* elecidsininput)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_elecidsininput_get_i_abc_now_A(msg, elecidsininput->i_abc_now_A);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_ElecIdSinInput_LEN? msg->len : MAVLINK_MSG_ID_ElecIdSinInput_LEN;
        memset(elecidsininput, 0, MAVLINK_MSG_ID_ElecIdSinInput_LEN);
    memcpy(elecidsininput, _MAV_PAYLOAD(msg), len);
#endif
}
