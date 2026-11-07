#pragma once
// MESSAGE AppMavlinkConfig PACKING

#define MAVLINK_MSG_ID_AppMavlinkConfig 30085


typedef struct __mavlink_appmavlinkconfig_t {
 uint8_t Sys_id; /*<  */
 uint8_t Comp_id; /*<  */
} mavlink_appmavlinkconfig_t;

#define MAVLINK_MSG_ID_AppMavlinkConfig_LEN 2
#define MAVLINK_MSG_ID_AppMavlinkConfig_MIN_LEN 2
#define MAVLINK_MSG_ID_30085_LEN 2
#define MAVLINK_MSG_ID_30085_MIN_LEN 2

#define MAVLINK_MSG_ID_AppMavlinkConfig_CRC 213
#define MAVLINK_MSG_ID_30085_CRC 213



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_AppMavlinkConfig { \
    30085, \
    "AppMavlinkConfig", \
    2, \
    {  { "Sys_id", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_appmavlinkconfig_t, Sys_id) }, \
         { "Comp_id", NULL, MAVLINK_TYPE_UINT8_T, 0, 1, offsetof(mavlink_appmavlinkconfig_t, Comp_id) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_AppMavlinkConfig { \
    "AppMavlinkConfig", \
    2, \
    {  { "Sys_id", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_appmavlinkconfig_t, Sys_id) }, \
         { "Comp_id", NULL, MAVLINK_TYPE_UINT8_T, 0, 1, offsetof(mavlink_appmavlinkconfig_t, Comp_id) }, \
         } \
}
#endif

/**
 * @brief Pack a appmavlinkconfig message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param Sys_id  
 * @param Comp_id  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_appmavlinkconfig_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t Sys_id, uint8_t Comp_id)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_AppMavlinkConfig_LEN];
    _mav_put_uint8_t(buf, 0, Sys_id);
    _mav_put_uint8_t(buf, 1, Comp_id);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_AppMavlinkConfig_LEN);
#else
    mavlink_appmavlinkconfig_t packet;
    packet.Sys_id = Sys_id;
    packet.Comp_id = Comp_id;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_AppMavlinkConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_AppMavlinkConfig;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_AppMavlinkConfig_MIN_LEN, MAVLINK_MSG_ID_AppMavlinkConfig_LEN, MAVLINK_MSG_ID_AppMavlinkConfig_CRC);
}

/**
 * @brief Pack a appmavlinkconfig message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param Sys_id  
 * @param Comp_id  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_appmavlinkconfig_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint8_t Sys_id, uint8_t Comp_id)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_AppMavlinkConfig_LEN];
    _mav_put_uint8_t(buf, 0, Sys_id);
    _mav_put_uint8_t(buf, 1, Comp_id);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_AppMavlinkConfig_LEN);
#else
    mavlink_appmavlinkconfig_t packet;
    packet.Sys_id = Sys_id;
    packet.Comp_id = Comp_id;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_AppMavlinkConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_AppMavlinkConfig;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_AppMavlinkConfig_MIN_LEN, MAVLINK_MSG_ID_AppMavlinkConfig_LEN, MAVLINK_MSG_ID_AppMavlinkConfig_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_AppMavlinkConfig_MIN_LEN, MAVLINK_MSG_ID_AppMavlinkConfig_LEN);
#endif
}

/**
 * @brief Pack a appmavlinkconfig message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param Sys_id  
 * @param Comp_id  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_appmavlinkconfig_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t Sys_id,uint8_t Comp_id)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_AppMavlinkConfig_LEN];
    _mav_put_uint8_t(buf, 0, Sys_id);
    _mav_put_uint8_t(buf, 1, Comp_id);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_AppMavlinkConfig_LEN);
#else
    mavlink_appmavlinkconfig_t packet;
    packet.Sys_id = Sys_id;
    packet.Comp_id = Comp_id;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_AppMavlinkConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_AppMavlinkConfig;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_AppMavlinkConfig_MIN_LEN, MAVLINK_MSG_ID_AppMavlinkConfig_LEN, MAVLINK_MSG_ID_AppMavlinkConfig_CRC);
}

/**
 * @brief Encode a appmavlinkconfig struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param appmavlinkconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_appmavlinkconfig_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_appmavlinkconfig_t* appmavlinkconfig)
{
    return mavlink_msg_appmavlinkconfig_pack(system_id, component_id, msg, appmavlinkconfig->Sys_id, appmavlinkconfig->Comp_id);
}

/**
 * @brief Encode a appmavlinkconfig struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param appmavlinkconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_appmavlinkconfig_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_appmavlinkconfig_t* appmavlinkconfig)
{
    return mavlink_msg_appmavlinkconfig_pack_chan(system_id, component_id, chan, msg, appmavlinkconfig->Sys_id, appmavlinkconfig->Comp_id);
}

/**
 * @brief Encode a appmavlinkconfig struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param appmavlinkconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_appmavlinkconfig_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_appmavlinkconfig_t* appmavlinkconfig)
{
    return mavlink_msg_appmavlinkconfig_pack_status(system_id, component_id, _status, msg,  appmavlinkconfig->Sys_id, appmavlinkconfig->Comp_id);
}

/**
 * @brief Send a appmavlinkconfig message
 * @param chan MAVLink channel to send the message
 *
 * @param Sys_id  
 * @param Comp_id  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_appmavlinkconfig_send(mavlink_channel_t chan, uint8_t Sys_id, uint8_t Comp_id)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_AppMavlinkConfig_LEN];
    _mav_put_uint8_t(buf, 0, Sys_id);
    _mav_put_uint8_t(buf, 1, Comp_id);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppMavlinkConfig, buf, MAVLINK_MSG_ID_AppMavlinkConfig_MIN_LEN, MAVLINK_MSG_ID_AppMavlinkConfig_LEN, MAVLINK_MSG_ID_AppMavlinkConfig_CRC);
#else
    mavlink_appmavlinkconfig_t packet;
    packet.Sys_id = Sys_id;
    packet.Comp_id = Comp_id;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppMavlinkConfig, (const char *)&packet, MAVLINK_MSG_ID_AppMavlinkConfig_MIN_LEN, MAVLINK_MSG_ID_AppMavlinkConfig_LEN, MAVLINK_MSG_ID_AppMavlinkConfig_CRC);
#endif
}

/**
 * @brief Send a appmavlinkconfig message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_appmavlinkconfig_send_struct(mavlink_channel_t chan, const mavlink_appmavlinkconfig_t* appmavlinkconfig)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_appmavlinkconfig_send(chan, appmavlinkconfig->Sys_id, appmavlinkconfig->Comp_id);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppMavlinkConfig, (const char *)appmavlinkconfig, MAVLINK_MSG_ID_AppMavlinkConfig_MIN_LEN, MAVLINK_MSG_ID_AppMavlinkConfig_LEN, MAVLINK_MSG_ID_AppMavlinkConfig_CRC);
#endif
}

#if MAVLINK_MSG_ID_AppMavlinkConfig_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_appmavlinkconfig_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t Sys_id, uint8_t Comp_id)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint8_t(buf, 0, Sys_id);
    _mav_put_uint8_t(buf, 1, Comp_id);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppMavlinkConfig, buf, MAVLINK_MSG_ID_AppMavlinkConfig_MIN_LEN, MAVLINK_MSG_ID_AppMavlinkConfig_LEN, MAVLINK_MSG_ID_AppMavlinkConfig_CRC);
#else
    mavlink_appmavlinkconfig_t *packet = (mavlink_appmavlinkconfig_t *)msgbuf;
    packet->Sys_id = Sys_id;
    packet->Comp_id = Comp_id;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppMavlinkConfig, (const char *)packet, MAVLINK_MSG_ID_AppMavlinkConfig_MIN_LEN, MAVLINK_MSG_ID_AppMavlinkConfig_LEN, MAVLINK_MSG_ID_AppMavlinkConfig_CRC);
#endif
}
#endif

#endif

// MESSAGE AppMavlinkConfig UNPACKING


/**
 * @brief Get field Sys_id from appmavlinkconfig message
 *
 * @return  
 */
static inline uint8_t mavlink_msg_appmavlinkconfig_get_Sys_id(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  0);
}

/**
 * @brief Get field Comp_id from appmavlinkconfig message
 *
 * @return  
 */
static inline uint8_t mavlink_msg_appmavlinkconfig_get_Comp_id(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  1);
}

/**
 * @brief Decode a appmavlinkconfig message into a struct
 *
 * @param msg The message to decode
 * @param appmavlinkconfig C-struct to decode the message contents into
 */
static inline void mavlink_msg_appmavlinkconfig_decode(const mavlink_message_t* msg, mavlink_appmavlinkconfig_t* appmavlinkconfig)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    appmavlinkconfig->Sys_id = mavlink_msg_appmavlinkconfig_get_Sys_id(msg);
    appmavlinkconfig->Comp_id = mavlink_msg_appmavlinkconfig_get_Comp_id(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_AppMavlinkConfig_LEN? msg->len : MAVLINK_MSG_ID_AppMavlinkConfig_LEN;
        memset(appmavlinkconfig, 0, MAVLINK_MSG_ID_AppMavlinkConfig_LEN);
    memcpy(appmavlinkconfig, _MAV_PAYLOAD(msg), len);
#endif
}
