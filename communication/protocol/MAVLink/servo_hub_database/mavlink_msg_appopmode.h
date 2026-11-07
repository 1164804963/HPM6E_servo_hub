#pragma once
// MESSAGE AppOpMode PACKING

#define MAVLINK_MSG_ID_AppOpMode 30056


typedef struct __mavlink_appopmode_t {
 int8_t Modes_of_operation; /*<  */
} mavlink_appopmode_t;

#define MAVLINK_MSG_ID_AppOpMode_LEN 1
#define MAVLINK_MSG_ID_AppOpMode_MIN_LEN 1
#define MAVLINK_MSG_ID_30056_LEN 1
#define MAVLINK_MSG_ID_30056_MIN_LEN 1

#define MAVLINK_MSG_ID_AppOpMode_CRC 26
#define MAVLINK_MSG_ID_30056_CRC 26



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_AppOpMode { \
    30056, \
    "AppOpMode", \
    1, \
    {  { "Modes_of_operation", NULL, MAVLINK_TYPE_INT8_T, 0, 0, offsetof(mavlink_appopmode_t, Modes_of_operation) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_AppOpMode { \
    "AppOpMode", \
    1, \
    {  { "Modes_of_operation", NULL, MAVLINK_TYPE_INT8_T, 0, 0, offsetof(mavlink_appopmode_t, Modes_of_operation) }, \
         } \
}
#endif

/**
 * @brief Pack a appopmode message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param Modes_of_operation  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_appopmode_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               int8_t Modes_of_operation)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_AppOpMode_LEN];
    _mav_put_int8_t(buf, 0, Modes_of_operation);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_AppOpMode_LEN);
#else
    mavlink_appopmode_t packet;
    packet.Modes_of_operation = Modes_of_operation;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_AppOpMode_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_AppOpMode;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_AppOpMode_MIN_LEN, MAVLINK_MSG_ID_AppOpMode_LEN, MAVLINK_MSG_ID_AppOpMode_CRC);
}

/**
 * @brief Pack a appopmode message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param Modes_of_operation  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_appopmode_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               int8_t Modes_of_operation)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_AppOpMode_LEN];
    _mav_put_int8_t(buf, 0, Modes_of_operation);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_AppOpMode_LEN);
#else
    mavlink_appopmode_t packet;
    packet.Modes_of_operation = Modes_of_operation;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_AppOpMode_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_AppOpMode;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_AppOpMode_MIN_LEN, MAVLINK_MSG_ID_AppOpMode_LEN, MAVLINK_MSG_ID_AppOpMode_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_AppOpMode_MIN_LEN, MAVLINK_MSG_ID_AppOpMode_LEN);
#endif
}

/**
 * @brief Pack a appopmode message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param Modes_of_operation  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_appopmode_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   int8_t Modes_of_operation)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_AppOpMode_LEN];
    _mav_put_int8_t(buf, 0, Modes_of_operation);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_AppOpMode_LEN);
#else
    mavlink_appopmode_t packet;
    packet.Modes_of_operation = Modes_of_operation;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_AppOpMode_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_AppOpMode;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_AppOpMode_MIN_LEN, MAVLINK_MSG_ID_AppOpMode_LEN, MAVLINK_MSG_ID_AppOpMode_CRC);
}

/**
 * @brief Encode a appopmode struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param appopmode C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_appopmode_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_appopmode_t* appopmode)
{
    return mavlink_msg_appopmode_pack(system_id, component_id, msg, appopmode->Modes_of_operation);
}

/**
 * @brief Encode a appopmode struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param appopmode C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_appopmode_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_appopmode_t* appopmode)
{
    return mavlink_msg_appopmode_pack_chan(system_id, component_id, chan, msg, appopmode->Modes_of_operation);
}

/**
 * @brief Encode a appopmode struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param appopmode C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_appopmode_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_appopmode_t* appopmode)
{
    return mavlink_msg_appopmode_pack_status(system_id, component_id, _status, msg,  appopmode->Modes_of_operation);
}

/**
 * @brief Send a appopmode message
 * @param chan MAVLink channel to send the message
 *
 * @param Modes_of_operation  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_appopmode_send(mavlink_channel_t chan, int8_t Modes_of_operation)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_AppOpMode_LEN];
    _mav_put_int8_t(buf, 0, Modes_of_operation);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppOpMode, buf, MAVLINK_MSG_ID_AppOpMode_MIN_LEN, MAVLINK_MSG_ID_AppOpMode_LEN, MAVLINK_MSG_ID_AppOpMode_CRC);
#else
    mavlink_appopmode_t packet;
    packet.Modes_of_operation = Modes_of_operation;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppOpMode, (const char *)&packet, MAVLINK_MSG_ID_AppOpMode_MIN_LEN, MAVLINK_MSG_ID_AppOpMode_LEN, MAVLINK_MSG_ID_AppOpMode_CRC);
#endif
}

/**
 * @brief Send a appopmode message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_appopmode_send_struct(mavlink_channel_t chan, const mavlink_appopmode_t* appopmode)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_appopmode_send(chan, appopmode->Modes_of_operation);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppOpMode, (const char *)appopmode, MAVLINK_MSG_ID_AppOpMode_MIN_LEN, MAVLINK_MSG_ID_AppOpMode_LEN, MAVLINK_MSG_ID_AppOpMode_CRC);
#endif
}

#if MAVLINK_MSG_ID_AppOpMode_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_appopmode_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  int8_t Modes_of_operation)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_int8_t(buf, 0, Modes_of_operation);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppOpMode, buf, MAVLINK_MSG_ID_AppOpMode_MIN_LEN, MAVLINK_MSG_ID_AppOpMode_LEN, MAVLINK_MSG_ID_AppOpMode_CRC);
#else
    mavlink_appopmode_t *packet = (mavlink_appopmode_t *)msgbuf;
    packet->Modes_of_operation = Modes_of_operation;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppOpMode, (const char *)packet, MAVLINK_MSG_ID_AppOpMode_MIN_LEN, MAVLINK_MSG_ID_AppOpMode_LEN, MAVLINK_MSG_ID_AppOpMode_CRC);
#endif
}
#endif

#endif

// MESSAGE AppOpMode UNPACKING


/**
 * @brief Get field Modes_of_operation from appopmode message
 *
 * @return  
 */
static inline int8_t mavlink_msg_appopmode_get_Modes_of_operation(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int8_t(msg,  0);
}

/**
 * @brief Decode a appopmode message into a struct
 *
 * @param msg The message to decode
 * @param appopmode C-struct to decode the message contents into
 */
static inline void mavlink_msg_appopmode_decode(const mavlink_message_t* msg, mavlink_appopmode_t* appopmode)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    appopmode->Modes_of_operation = mavlink_msg_appopmode_get_Modes_of_operation(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_AppOpMode_LEN? msg->len : MAVLINK_MSG_ID_AppOpMode_LEN;
        memset(appopmode, 0, MAVLINK_MSG_ID_AppOpMode_LEN);
    memcpy(appopmode, _MAV_PAYLOAD(msg), len);
#endif
}
