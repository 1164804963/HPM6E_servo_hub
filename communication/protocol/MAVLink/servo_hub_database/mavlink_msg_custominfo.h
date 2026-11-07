#pragma once
// MESSAGE CustomInfo PACKING

#define MAVLINK_MSG_ID_CustomInfo 30076


typedef struct __mavlink_custominfo_t {
 uint64_t User_module_code; /*<  */
} mavlink_custominfo_t;

#define MAVLINK_MSG_ID_CustomInfo_LEN 8
#define MAVLINK_MSG_ID_CustomInfo_MIN_LEN 8
#define MAVLINK_MSG_ID_30076_LEN 8
#define MAVLINK_MSG_ID_30076_MIN_LEN 8

#define MAVLINK_MSG_ID_CustomInfo_CRC 1
#define MAVLINK_MSG_ID_30076_CRC 1



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_CustomInfo { \
    30076, \
    "CustomInfo", \
    1, \
    {  { "User_module_code", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_custominfo_t, User_module_code) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_CustomInfo { \
    "CustomInfo", \
    1, \
    {  { "User_module_code", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_custominfo_t, User_module_code) }, \
         } \
}
#endif

/**
 * @brief Pack a custominfo message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param User_module_code  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_custominfo_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint64_t User_module_code)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_CustomInfo_LEN];
    _mav_put_uint64_t(buf, 0, User_module_code);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_CustomInfo_LEN);
#else
    mavlink_custominfo_t packet;
    packet.User_module_code = User_module_code;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_CustomInfo_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_CustomInfo;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_CustomInfo_MIN_LEN, MAVLINK_MSG_ID_CustomInfo_LEN, MAVLINK_MSG_ID_CustomInfo_CRC);
}

/**
 * @brief Pack a custominfo message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param User_module_code  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_custominfo_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint64_t User_module_code)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_CustomInfo_LEN];
    _mav_put_uint64_t(buf, 0, User_module_code);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_CustomInfo_LEN);
#else
    mavlink_custominfo_t packet;
    packet.User_module_code = User_module_code;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_CustomInfo_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_CustomInfo;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_CustomInfo_MIN_LEN, MAVLINK_MSG_ID_CustomInfo_LEN, MAVLINK_MSG_ID_CustomInfo_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_CustomInfo_MIN_LEN, MAVLINK_MSG_ID_CustomInfo_LEN);
#endif
}

/**
 * @brief Pack a custominfo message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param User_module_code  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_custominfo_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint64_t User_module_code)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_CustomInfo_LEN];
    _mav_put_uint64_t(buf, 0, User_module_code);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_CustomInfo_LEN);
#else
    mavlink_custominfo_t packet;
    packet.User_module_code = User_module_code;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_CustomInfo_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_CustomInfo;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_CustomInfo_MIN_LEN, MAVLINK_MSG_ID_CustomInfo_LEN, MAVLINK_MSG_ID_CustomInfo_CRC);
}

/**
 * @brief Encode a custominfo struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param custominfo C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_custominfo_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_custominfo_t* custominfo)
{
    return mavlink_msg_custominfo_pack(system_id, component_id, msg, custominfo->User_module_code);
}

/**
 * @brief Encode a custominfo struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param custominfo C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_custominfo_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_custominfo_t* custominfo)
{
    return mavlink_msg_custominfo_pack_chan(system_id, component_id, chan, msg, custominfo->User_module_code);
}

/**
 * @brief Encode a custominfo struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param custominfo C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_custominfo_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_custominfo_t* custominfo)
{
    return mavlink_msg_custominfo_pack_status(system_id, component_id, _status, msg,  custominfo->User_module_code);
}

/**
 * @brief Send a custominfo message
 * @param chan MAVLink channel to send the message
 *
 * @param User_module_code  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_custominfo_send(mavlink_channel_t chan, uint64_t User_module_code)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_CustomInfo_LEN];
    _mav_put_uint64_t(buf, 0, User_module_code);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CustomInfo, buf, MAVLINK_MSG_ID_CustomInfo_MIN_LEN, MAVLINK_MSG_ID_CustomInfo_LEN, MAVLINK_MSG_ID_CustomInfo_CRC);
#else
    mavlink_custominfo_t packet;
    packet.User_module_code = User_module_code;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CustomInfo, (const char *)&packet, MAVLINK_MSG_ID_CustomInfo_MIN_LEN, MAVLINK_MSG_ID_CustomInfo_LEN, MAVLINK_MSG_ID_CustomInfo_CRC);
#endif
}

/**
 * @brief Send a custominfo message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_custominfo_send_struct(mavlink_channel_t chan, const mavlink_custominfo_t* custominfo)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_custominfo_send(chan, custominfo->User_module_code);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CustomInfo, (const char *)custominfo, MAVLINK_MSG_ID_CustomInfo_MIN_LEN, MAVLINK_MSG_ID_CustomInfo_LEN, MAVLINK_MSG_ID_CustomInfo_CRC);
#endif
}

#if MAVLINK_MSG_ID_CustomInfo_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_custominfo_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint64_t User_module_code)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint64_t(buf, 0, User_module_code);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CustomInfo, buf, MAVLINK_MSG_ID_CustomInfo_MIN_LEN, MAVLINK_MSG_ID_CustomInfo_LEN, MAVLINK_MSG_ID_CustomInfo_CRC);
#else
    mavlink_custominfo_t *packet = (mavlink_custominfo_t *)msgbuf;
    packet->User_module_code = User_module_code;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CustomInfo, (const char *)packet, MAVLINK_MSG_ID_CustomInfo_MIN_LEN, MAVLINK_MSG_ID_CustomInfo_LEN, MAVLINK_MSG_ID_CustomInfo_CRC);
#endif
}
#endif

#endif

// MESSAGE CustomInfo UNPACKING


/**
 * @brief Get field User_module_code from custominfo message
 *
 * @return  
 */
static inline uint64_t mavlink_msg_custominfo_get_User_module_code(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Decode a custominfo message into a struct
 *
 * @param msg The message to decode
 * @param custominfo C-struct to decode the message contents into
 */
static inline void mavlink_msg_custominfo_decode(const mavlink_message_t* msg, mavlink_custominfo_t* custominfo)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    custominfo->User_module_code = mavlink_msg_custominfo_get_User_module_code(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_CustomInfo_LEN? msg->len : MAVLINK_MSG_ID_CustomInfo_LEN;
        memset(custominfo, 0, MAVLINK_MSG_ID_CustomInfo_LEN);
    memcpy(custominfo, _MAV_PAYLOAD(msg), len);
#endif
}
