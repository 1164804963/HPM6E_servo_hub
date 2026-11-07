#pragma once
// MESSAGE AppPermissionConfig PACKING

#define MAVLINK_MSG_ID_AppPermissionConfig 30068


typedef struct __mavlink_apppermissionconfig_t {
 uint8_t Comm_control_authority; /*<  */
 uint8_t Internal_control_authority; /*<  */
} mavlink_apppermissionconfig_t;

#define MAVLINK_MSG_ID_AppPermissionConfig_LEN 2
#define MAVLINK_MSG_ID_AppPermissionConfig_MIN_LEN 2
#define MAVLINK_MSG_ID_30068_LEN 2
#define MAVLINK_MSG_ID_30068_MIN_LEN 2

#define MAVLINK_MSG_ID_AppPermissionConfig_CRC 134
#define MAVLINK_MSG_ID_30068_CRC 134



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_AppPermissionConfig { \
    30068, \
    "AppPermissionConfig", \
    2, \
    {  { "Comm_control_authority", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_apppermissionconfig_t, Comm_control_authority) }, \
         { "Internal_control_authority", NULL, MAVLINK_TYPE_UINT8_T, 0, 1, offsetof(mavlink_apppermissionconfig_t, Internal_control_authority) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_AppPermissionConfig { \
    "AppPermissionConfig", \
    2, \
    {  { "Comm_control_authority", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_apppermissionconfig_t, Comm_control_authority) }, \
         { "Internal_control_authority", NULL, MAVLINK_TYPE_UINT8_T, 0, 1, offsetof(mavlink_apppermissionconfig_t, Internal_control_authority) }, \
         } \
}
#endif

/**
 * @brief Pack a apppermissionconfig message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param Comm_control_authority  
 * @param Internal_control_authority  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_apppermissionconfig_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t Comm_control_authority, uint8_t Internal_control_authority)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_AppPermissionConfig_LEN];
    _mav_put_uint8_t(buf, 0, Comm_control_authority);
    _mav_put_uint8_t(buf, 1, Internal_control_authority);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_AppPermissionConfig_LEN);
#else
    mavlink_apppermissionconfig_t packet;
    packet.Comm_control_authority = Comm_control_authority;
    packet.Internal_control_authority = Internal_control_authority;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_AppPermissionConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_AppPermissionConfig;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_AppPermissionConfig_MIN_LEN, MAVLINK_MSG_ID_AppPermissionConfig_LEN, MAVLINK_MSG_ID_AppPermissionConfig_CRC);
}

/**
 * @brief Pack a apppermissionconfig message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param Comm_control_authority  
 * @param Internal_control_authority  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_apppermissionconfig_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint8_t Comm_control_authority, uint8_t Internal_control_authority)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_AppPermissionConfig_LEN];
    _mav_put_uint8_t(buf, 0, Comm_control_authority);
    _mav_put_uint8_t(buf, 1, Internal_control_authority);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_AppPermissionConfig_LEN);
#else
    mavlink_apppermissionconfig_t packet;
    packet.Comm_control_authority = Comm_control_authority;
    packet.Internal_control_authority = Internal_control_authority;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_AppPermissionConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_AppPermissionConfig;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_AppPermissionConfig_MIN_LEN, MAVLINK_MSG_ID_AppPermissionConfig_LEN, MAVLINK_MSG_ID_AppPermissionConfig_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_AppPermissionConfig_MIN_LEN, MAVLINK_MSG_ID_AppPermissionConfig_LEN);
#endif
}

/**
 * @brief Pack a apppermissionconfig message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param Comm_control_authority  
 * @param Internal_control_authority  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_apppermissionconfig_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t Comm_control_authority,uint8_t Internal_control_authority)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_AppPermissionConfig_LEN];
    _mav_put_uint8_t(buf, 0, Comm_control_authority);
    _mav_put_uint8_t(buf, 1, Internal_control_authority);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_AppPermissionConfig_LEN);
#else
    mavlink_apppermissionconfig_t packet;
    packet.Comm_control_authority = Comm_control_authority;
    packet.Internal_control_authority = Internal_control_authority;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_AppPermissionConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_AppPermissionConfig;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_AppPermissionConfig_MIN_LEN, MAVLINK_MSG_ID_AppPermissionConfig_LEN, MAVLINK_MSG_ID_AppPermissionConfig_CRC);
}

/**
 * @brief Encode a apppermissionconfig struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param apppermissionconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_apppermissionconfig_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_apppermissionconfig_t* apppermissionconfig)
{
    return mavlink_msg_apppermissionconfig_pack(system_id, component_id, msg, apppermissionconfig->Comm_control_authority, apppermissionconfig->Internal_control_authority);
}

/**
 * @brief Encode a apppermissionconfig struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param apppermissionconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_apppermissionconfig_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_apppermissionconfig_t* apppermissionconfig)
{
    return mavlink_msg_apppermissionconfig_pack_chan(system_id, component_id, chan, msg, apppermissionconfig->Comm_control_authority, apppermissionconfig->Internal_control_authority);
}

/**
 * @brief Encode a apppermissionconfig struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param apppermissionconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_apppermissionconfig_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_apppermissionconfig_t* apppermissionconfig)
{
    return mavlink_msg_apppermissionconfig_pack_status(system_id, component_id, _status, msg,  apppermissionconfig->Comm_control_authority, apppermissionconfig->Internal_control_authority);
}

/**
 * @brief Send a apppermissionconfig message
 * @param chan MAVLink channel to send the message
 *
 * @param Comm_control_authority  
 * @param Internal_control_authority  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_apppermissionconfig_send(mavlink_channel_t chan, uint8_t Comm_control_authority, uint8_t Internal_control_authority)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_AppPermissionConfig_LEN];
    _mav_put_uint8_t(buf, 0, Comm_control_authority);
    _mav_put_uint8_t(buf, 1, Internal_control_authority);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppPermissionConfig, buf, MAVLINK_MSG_ID_AppPermissionConfig_MIN_LEN, MAVLINK_MSG_ID_AppPermissionConfig_LEN, MAVLINK_MSG_ID_AppPermissionConfig_CRC);
#else
    mavlink_apppermissionconfig_t packet;
    packet.Comm_control_authority = Comm_control_authority;
    packet.Internal_control_authority = Internal_control_authority;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppPermissionConfig, (const char *)&packet, MAVLINK_MSG_ID_AppPermissionConfig_MIN_LEN, MAVLINK_MSG_ID_AppPermissionConfig_LEN, MAVLINK_MSG_ID_AppPermissionConfig_CRC);
#endif
}

/**
 * @brief Send a apppermissionconfig message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_apppermissionconfig_send_struct(mavlink_channel_t chan, const mavlink_apppermissionconfig_t* apppermissionconfig)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_apppermissionconfig_send(chan, apppermissionconfig->Comm_control_authority, apppermissionconfig->Internal_control_authority);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppPermissionConfig, (const char *)apppermissionconfig, MAVLINK_MSG_ID_AppPermissionConfig_MIN_LEN, MAVLINK_MSG_ID_AppPermissionConfig_LEN, MAVLINK_MSG_ID_AppPermissionConfig_CRC);
#endif
}

#if MAVLINK_MSG_ID_AppPermissionConfig_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_apppermissionconfig_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t Comm_control_authority, uint8_t Internal_control_authority)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint8_t(buf, 0, Comm_control_authority);
    _mav_put_uint8_t(buf, 1, Internal_control_authority);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppPermissionConfig, buf, MAVLINK_MSG_ID_AppPermissionConfig_MIN_LEN, MAVLINK_MSG_ID_AppPermissionConfig_LEN, MAVLINK_MSG_ID_AppPermissionConfig_CRC);
#else
    mavlink_apppermissionconfig_t *packet = (mavlink_apppermissionconfig_t *)msgbuf;
    packet->Comm_control_authority = Comm_control_authority;
    packet->Internal_control_authority = Internal_control_authority;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppPermissionConfig, (const char *)packet, MAVLINK_MSG_ID_AppPermissionConfig_MIN_LEN, MAVLINK_MSG_ID_AppPermissionConfig_LEN, MAVLINK_MSG_ID_AppPermissionConfig_CRC);
#endif
}
#endif

#endif

// MESSAGE AppPermissionConfig UNPACKING


/**
 * @brief Get field Comm_control_authority from apppermissionconfig message
 *
 * @return  
 */
static inline uint8_t mavlink_msg_apppermissionconfig_get_Comm_control_authority(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  0);
}

/**
 * @brief Get field Internal_control_authority from apppermissionconfig message
 *
 * @return  
 */
static inline uint8_t mavlink_msg_apppermissionconfig_get_Internal_control_authority(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  1);
}

/**
 * @brief Decode a apppermissionconfig message into a struct
 *
 * @param msg The message to decode
 * @param apppermissionconfig C-struct to decode the message contents into
 */
static inline void mavlink_msg_apppermissionconfig_decode(const mavlink_message_t* msg, mavlink_apppermissionconfig_t* apppermissionconfig)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    apppermissionconfig->Comm_control_authority = mavlink_msg_apppermissionconfig_get_Comm_control_authority(msg);
    apppermissionconfig->Internal_control_authority = mavlink_msg_apppermissionconfig_get_Internal_control_authority(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_AppPermissionConfig_LEN? msg->len : MAVLINK_MSG_ID_AppPermissionConfig_LEN;
        memset(apppermissionconfig, 0, MAVLINK_MSG_ID_AppPermissionConfig_LEN);
    memcpy(apppermissionconfig, _MAV_PAYLOAD(msg), len);
#endif
}
