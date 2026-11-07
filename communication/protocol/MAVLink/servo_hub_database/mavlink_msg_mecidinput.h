#pragma once
// MESSAGE MecIdInput PACKING

#define MAVLINK_MSG_ID_MecIdInput 30010


typedef struct __mavlink_mecidinput_t {
 float speed_now_rad_s; /*<  */
} mavlink_mecidinput_t;

#define MAVLINK_MSG_ID_MecIdInput_LEN 4
#define MAVLINK_MSG_ID_MecIdInput_MIN_LEN 4
#define MAVLINK_MSG_ID_30010_LEN 4
#define MAVLINK_MSG_ID_30010_MIN_LEN 4

#define MAVLINK_MSG_ID_MecIdInput_CRC 37
#define MAVLINK_MSG_ID_30010_CRC 37



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_MecIdInput { \
    30010, \
    "MecIdInput", \
    1, \
    {  { "speed_now_rad_s", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_mecidinput_t, speed_now_rad_s) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_MecIdInput { \
    "MecIdInput", \
    1, \
    {  { "speed_now_rad_s", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_mecidinput_t, speed_now_rad_s) }, \
         } \
}
#endif

/**
 * @brief Pack a mecidinput message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param speed_now_rad_s  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_mecidinput_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               float speed_now_rad_s)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MecIdInput_LEN];
    _mav_put_float(buf, 0, speed_now_rad_s);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MecIdInput_LEN);
#else
    mavlink_mecidinput_t packet;
    packet.speed_now_rad_s = speed_now_rad_s;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MecIdInput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MecIdInput;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_MecIdInput_MIN_LEN, MAVLINK_MSG_ID_MecIdInput_LEN, MAVLINK_MSG_ID_MecIdInput_CRC);
}

/**
 * @brief Pack a mecidinput message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param speed_now_rad_s  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_mecidinput_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               float speed_now_rad_s)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MecIdInput_LEN];
    _mav_put_float(buf, 0, speed_now_rad_s);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MecIdInput_LEN);
#else
    mavlink_mecidinput_t packet;
    packet.speed_now_rad_s = speed_now_rad_s;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MecIdInput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MecIdInput;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_MecIdInput_MIN_LEN, MAVLINK_MSG_ID_MecIdInput_LEN, MAVLINK_MSG_ID_MecIdInput_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_MecIdInput_MIN_LEN, MAVLINK_MSG_ID_MecIdInput_LEN);
#endif
}

/**
 * @brief Pack a mecidinput message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param speed_now_rad_s  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_mecidinput_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   float speed_now_rad_s)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MecIdInput_LEN];
    _mav_put_float(buf, 0, speed_now_rad_s);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MecIdInput_LEN);
#else
    mavlink_mecidinput_t packet;
    packet.speed_now_rad_s = speed_now_rad_s;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MecIdInput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MecIdInput;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_MecIdInput_MIN_LEN, MAVLINK_MSG_ID_MecIdInput_LEN, MAVLINK_MSG_ID_MecIdInput_CRC);
}

/**
 * @brief Encode a mecidinput struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param mecidinput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_mecidinput_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_mecidinput_t* mecidinput)
{
    return mavlink_msg_mecidinput_pack(system_id, component_id, msg, mecidinput->speed_now_rad_s);
}

/**
 * @brief Encode a mecidinput struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param mecidinput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_mecidinput_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_mecidinput_t* mecidinput)
{
    return mavlink_msg_mecidinput_pack_chan(system_id, component_id, chan, msg, mecidinput->speed_now_rad_s);
}

/**
 * @brief Encode a mecidinput struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param mecidinput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_mecidinput_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_mecidinput_t* mecidinput)
{
    return mavlink_msg_mecidinput_pack_status(system_id, component_id, _status, msg,  mecidinput->speed_now_rad_s);
}

/**
 * @brief Send a mecidinput message
 * @param chan MAVLink channel to send the message
 *
 * @param speed_now_rad_s  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_mecidinput_send(mavlink_channel_t chan, float speed_now_rad_s)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MecIdInput_LEN];
    _mav_put_float(buf, 0, speed_now_rad_s);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MecIdInput, buf, MAVLINK_MSG_ID_MecIdInput_MIN_LEN, MAVLINK_MSG_ID_MecIdInput_LEN, MAVLINK_MSG_ID_MecIdInput_CRC);
#else
    mavlink_mecidinput_t packet;
    packet.speed_now_rad_s = speed_now_rad_s;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MecIdInput, (const char *)&packet, MAVLINK_MSG_ID_MecIdInput_MIN_LEN, MAVLINK_MSG_ID_MecIdInput_LEN, MAVLINK_MSG_ID_MecIdInput_CRC);
#endif
}

/**
 * @brief Send a mecidinput message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_mecidinput_send_struct(mavlink_channel_t chan, const mavlink_mecidinput_t* mecidinput)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_mecidinput_send(chan, mecidinput->speed_now_rad_s);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MecIdInput, (const char *)mecidinput, MAVLINK_MSG_ID_MecIdInput_MIN_LEN, MAVLINK_MSG_ID_MecIdInput_LEN, MAVLINK_MSG_ID_MecIdInput_CRC);
#endif
}

#if MAVLINK_MSG_ID_MecIdInput_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_mecidinput_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float speed_now_rad_s)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, speed_now_rad_s);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MecIdInput, buf, MAVLINK_MSG_ID_MecIdInput_MIN_LEN, MAVLINK_MSG_ID_MecIdInput_LEN, MAVLINK_MSG_ID_MecIdInput_CRC);
#else
    mavlink_mecidinput_t *packet = (mavlink_mecidinput_t *)msgbuf;
    packet->speed_now_rad_s = speed_now_rad_s;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MecIdInput, (const char *)packet, MAVLINK_MSG_ID_MecIdInput_MIN_LEN, MAVLINK_MSG_ID_MecIdInput_LEN, MAVLINK_MSG_ID_MecIdInput_CRC);
#endif
}
#endif

#endif

// MESSAGE MecIdInput UNPACKING


/**
 * @brief Get field speed_now_rad_s from mecidinput message
 *
 * @return  
 */
static inline float mavlink_msg_mecidinput_get_speed_now_rad_s(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Decode a mecidinput message into a struct
 *
 * @param msg The message to decode
 * @param mecidinput C-struct to decode the message contents into
 */
static inline void mavlink_msg_mecidinput_decode(const mavlink_message_t* msg, mavlink_mecidinput_t* mecidinput)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mecidinput->speed_now_rad_s = mavlink_msg_mecidinput_get_speed_now_rad_s(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_MecIdInput_LEN? msg->len : MAVLINK_MSG_ID_MecIdInput_LEN;
        memset(mecidinput, 0, MAVLINK_MSG_ID_MecIdInput_LEN);
    memcpy(mecidinput, _MAV_PAYLOAD(msg), len);
#endif
}
