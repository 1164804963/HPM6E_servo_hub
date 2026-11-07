#pragma once
// MESSAGE MotorPosSensorInput PACKING

#define MAVLINK_MSG_ID_MotorPosSensorInput 30038


typedef struct __mavlink_motorpossensorinput_t {
 uint32_t enc_counts_now_p; /*<  */
} mavlink_motorpossensorinput_t;

#define MAVLINK_MSG_ID_MotorPosSensorInput_LEN 4
#define MAVLINK_MSG_ID_MotorPosSensorInput_MIN_LEN 4
#define MAVLINK_MSG_ID_30038_LEN 4
#define MAVLINK_MSG_ID_30038_MIN_LEN 4

#define MAVLINK_MSG_ID_MotorPosSensorInput_CRC 107
#define MAVLINK_MSG_ID_30038_CRC 107



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_MotorPosSensorInput { \
    30038, \
    "MotorPosSensorInput", \
    1, \
    {  { "enc_counts_now_p", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_motorpossensorinput_t, enc_counts_now_p) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_MotorPosSensorInput { \
    "MotorPosSensorInput", \
    1, \
    {  { "enc_counts_now_p", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_motorpossensorinput_t, enc_counts_now_p) }, \
         } \
}
#endif

/**
 * @brief Pack a motorpossensorinput message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param enc_counts_now_p  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_motorpossensorinput_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint32_t enc_counts_now_p)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MotorPosSensorInput_LEN];
    _mav_put_uint32_t(buf, 0, enc_counts_now_p);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MotorPosSensorInput_LEN);
#else
    mavlink_motorpossensorinput_t packet;
    packet.enc_counts_now_p = enc_counts_now_p;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MotorPosSensorInput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MotorPosSensorInput;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_MotorPosSensorInput_MIN_LEN, MAVLINK_MSG_ID_MotorPosSensorInput_LEN, MAVLINK_MSG_ID_MotorPosSensorInput_CRC);
}

/**
 * @brief Pack a motorpossensorinput message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param enc_counts_now_p  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_motorpossensorinput_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint32_t enc_counts_now_p)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MotorPosSensorInput_LEN];
    _mav_put_uint32_t(buf, 0, enc_counts_now_p);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MotorPosSensorInput_LEN);
#else
    mavlink_motorpossensorinput_t packet;
    packet.enc_counts_now_p = enc_counts_now_p;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MotorPosSensorInput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MotorPosSensorInput;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_MotorPosSensorInput_MIN_LEN, MAVLINK_MSG_ID_MotorPosSensorInput_LEN, MAVLINK_MSG_ID_MotorPosSensorInput_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_MotorPosSensorInput_MIN_LEN, MAVLINK_MSG_ID_MotorPosSensorInput_LEN);
#endif
}

/**
 * @brief Pack a motorpossensorinput message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param enc_counts_now_p  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_motorpossensorinput_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint32_t enc_counts_now_p)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MotorPosSensorInput_LEN];
    _mav_put_uint32_t(buf, 0, enc_counts_now_p);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MotorPosSensorInput_LEN);
#else
    mavlink_motorpossensorinput_t packet;
    packet.enc_counts_now_p = enc_counts_now_p;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MotorPosSensorInput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MotorPosSensorInput;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_MotorPosSensorInput_MIN_LEN, MAVLINK_MSG_ID_MotorPosSensorInput_LEN, MAVLINK_MSG_ID_MotorPosSensorInput_CRC);
}

/**
 * @brief Encode a motorpossensorinput struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param motorpossensorinput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_motorpossensorinput_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_motorpossensorinput_t* motorpossensorinput)
{
    return mavlink_msg_motorpossensorinput_pack(system_id, component_id, msg, motorpossensorinput->enc_counts_now_p);
}

/**
 * @brief Encode a motorpossensorinput struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param motorpossensorinput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_motorpossensorinput_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_motorpossensorinput_t* motorpossensorinput)
{
    return mavlink_msg_motorpossensorinput_pack_chan(system_id, component_id, chan, msg, motorpossensorinput->enc_counts_now_p);
}

/**
 * @brief Encode a motorpossensorinput struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param motorpossensorinput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_motorpossensorinput_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_motorpossensorinput_t* motorpossensorinput)
{
    return mavlink_msg_motorpossensorinput_pack_status(system_id, component_id, _status, msg,  motorpossensorinput->enc_counts_now_p);
}

/**
 * @brief Send a motorpossensorinput message
 * @param chan MAVLink channel to send the message
 *
 * @param enc_counts_now_p  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_motorpossensorinput_send(mavlink_channel_t chan, uint32_t enc_counts_now_p)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MotorPosSensorInput_LEN];
    _mav_put_uint32_t(buf, 0, enc_counts_now_p);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MotorPosSensorInput, buf, MAVLINK_MSG_ID_MotorPosSensorInput_MIN_LEN, MAVLINK_MSG_ID_MotorPosSensorInput_LEN, MAVLINK_MSG_ID_MotorPosSensorInput_CRC);
#else
    mavlink_motorpossensorinput_t packet;
    packet.enc_counts_now_p = enc_counts_now_p;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MotorPosSensorInput, (const char *)&packet, MAVLINK_MSG_ID_MotorPosSensorInput_MIN_LEN, MAVLINK_MSG_ID_MotorPosSensorInput_LEN, MAVLINK_MSG_ID_MotorPosSensorInput_CRC);
#endif
}

/**
 * @brief Send a motorpossensorinput message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_motorpossensorinput_send_struct(mavlink_channel_t chan, const mavlink_motorpossensorinput_t* motorpossensorinput)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_motorpossensorinput_send(chan, motorpossensorinput->enc_counts_now_p);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MotorPosSensorInput, (const char *)motorpossensorinput, MAVLINK_MSG_ID_MotorPosSensorInput_MIN_LEN, MAVLINK_MSG_ID_MotorPosSensorInput_LEN, MAVLINK_MSG_ID_MotorPosSensorInput_CRC);
#endif
}

#if MAVLINK_MSG_ID_MotorPosSensorInput_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_motorpossensorinput_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint32_t enc_counts_now_p)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint32_t(buf, 0, enc_counts_now_p);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MotorPosSensorInput, buf, MAVLINK_MSG_ID_MotorPosSensorInput_MIN_LEN, MAVLINK_MSG_ID_MotorPosSensorInput_LEN, MAVLINK_MSG_ID_MotorPosSensorInput_CRC);
#else
    mavlink_motorpossensorinput_t *packet = (mavlink_motorpossensorinput_t *)msgbuf;
    packet->enc_counts_now_p = enc_counts_now_p;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MotorPosSensorInput, (const char *)packet, MAVLINK_MSG_ID_MotorPosSensorInput_MIN_LEN, MAVLINK_MSG_ID_MotorPosSensorInput_LEN, MAVLINK_MSG_ID_MotorPosSensorInput_CRC);
#endif
}
#endif

#endif

// MESSAGE MotorPosSensorInput UNPACKING


/**
 * @brief Get field enc_counts_now_p from motorpossensorinput message
 *
 * @return  
 */
static inline uint32_t mavlink_msg_motorpossensorinput_get_enc_counts_now_p(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Decode a motorpossensorinput message into a struct
 *
 * @param msg The message to decode
 * @param motorpossensorinput C-struct to decode the message contents into
 */
static inline void mavlink_msg_motorpossensorinput_decode(const mavlink_message_t* msg, mavlink_motorpossensorinput_t* motorpossensorinput)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    motorpossensorinput->enc_counts_now_p = mavlink_msg_motorpossensorinput_get_enc_counts_now_p(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_MotorPosSensorInput_LEN? msg->len : MAVLINK_MSG_ID_MotorPosSensorInput_LEN;
        memset(motorpossensorinput, 0, MAVLINK_MSG_ID_MotorPosSensorInput_LEN);
    memcpy(motorpossensorinput, _MAV_PAYLOAD(msg), len);
#endif
}
