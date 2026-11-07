#pragma once
// MESSAGE SystemCmd PACKING

#define MAVLINK_MSG_ID_SystemCmd 30069


typedef struct __mavlink_systemcmd_t {
 uint8_t Sys_cmd; /*<  */
} mavlink_systemcmd_t;

#define MAVLINK_MSG_ID_SystemCmd_LEN 1
#define MAVLINK_MSG_ID_SystemCmd_MIN_LEN 1
#define MAVLINK_MSG_ID_30069_LEN 1
#define MAVLINK_MSG_ID_30069_MIN_LEN 1

#define MAVLINK_MSG_ID_SystemCmd_CRC 169
#define MAVLINK_MSG_ID_30069_CRC 169



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_SystemCmd { \
    30069, \
    "SystemCmd", \
    1, \
    {  { "Sys_cmd", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_systemcmd_t, Sys_cmd) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_SystemCmd { \
    "SystemCmd", \
    1, \
    {  { "Sys_cmd", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_systemcmd_t, Sys_cmd) }, \
         } \
}
#endif

/**
 * @brief Pack a systemcmd message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param Sys_cmd  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_systemcmd_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t Sys_cmd)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SystemCmd_LEN];
    _mav_put_uint8_t(buf, 0, Sys_cmd);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SystemCmd_LEN);
#else
    mavlink_systemcmd_t packet;
    packet.Sys_cmd = Sys_cmd;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SystemCmd_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SystemCmd;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_SystemCmd_MIN_LEN, MAVLINK_MSG_ID_SystemCmd_LEN, MAVLINK_MSG_ID_SystemCmd_CRC);
}

/**
 * @brief Pack a systemcmd message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param Sys_cmd  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_systemcmd_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint8_t Sys_cmd)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SystemCmd_LEN];
    _mav_put_uint8_t(buf, 0, Sys_cmd);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SystemCmd_LEN);
#else
    mavlink_systemcmd_t packet;
    packet.Sys_cmd = Sys_cmd;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SystemCmd_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SystemCmd;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_SystemCmd_MIN_LEN, MAVLINK_MSG_ID_SystemCmd_LEN, MAVLINK_MSG_ID_SystemCmd_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_SystemCmd_MIN_LEN, MAVLINK_MSG_ID_SystemCmd_LEN);
#endif
}

/**
 * @brief Pack a systemcmd message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param Sys_cmd  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_systemcmd_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t Sys_cmd)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SystemCmd_LEN];
    _mav_put_uint8_t(buf, 0, Sys_cmd);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SystemCmd_LEN);
#else
    mavlink_systemcmd_t packet;
    packet.Sys_cmd = Sys_cmd;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SystemCmd_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SystemCmd;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_SystemCmd_MIN_LEN, MAVLINK_MSG_ID_SystemCmd_LEN, MAVLINK_MSG_ID_SystemCmd_CRC);
}

/**
 * @brief Encode a systemcmd struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param systemcmd C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_systemcmd_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_systemcmd_t* systemcmd)
{
    return mavlink_msg_systemcmd_pack(system_id, component_id, msg, systemcmd->Sys_cmd);
}

/**
 * @brief Encode a systemcmd struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param systemcmd C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_systemcmd_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_systemcmd_t* systemcmd)
{
    return mavlink_msg_systemcmd_pack_chan(system_id, component_id, chan, msg, systemcmd->Sys_cmd);
}

/**
 * @brief Encode a systemcmd struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param systemcmd C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_systemcmd_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_systemcmd_t* systemcmd)
{
    return mavlink_msg_systemcmd_pack_status(system_id, component_id, _status, msg,  systemcmd->Sys_cmd);
}

/**
 * @brief Send a systemcmd message
 * @param chan MAVLink channel to send the message
 *
 * @param Sys_cmd  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_systemcmd_send(mavlink_channel_t chan, uint8_t Sys_cmd)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SystemCmd_LEN];
    _mav_put_uint8_t(buf, 0, Sys_cmd);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SystemCmd, buf, MAVLINK_MSG_ID_SystemCmd_MIN_LEN, MAVLINK_MSG_ID_SystemCmd_LEN, MAVLINK_MSG_ID_SystemCmd_CRC);
#else
    mavlink_systemcmd_t packet;
    packet.Sys_cmd = Sys_cmd;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SystemCmd, (const char *)&packet, MAVLINK_MSG_ID_SystemCmd_MIN_LEN, MAVLINK_MSG_ID_SystemCmd_LEN, MAVLINK_MSG_ID_SystemCmd_CRC);
#endif
}

/**
 * @brief Send a systemcmd message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_systemcmd_send_struct(mavlink_channel_t chan, const mavlink_systemcmd_t* systemcmd)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_systemcmd_send(chan, systemcmd->Sys_cmd);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SystemCmd, (const char *)systemcmd, MAVLINK_MSG_ID_SystemCmd_MIN_LEN, MAVLINK_MSG_ID_SystemCmd_LEN, MAVLINK_MSG_ID_SystemCmd_CRC);
#endif
}

#if MAVLINK_MSG_ID_SystemCmd_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_systemcmd_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t Sys_cmd)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint8_t(buf, 0, Sys_cmd);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SystemCmd, buf, MAVLINK_MSG_ID_SystemCmd_MIN_LEN, MAVLINK_MSG_ID_SystemCmd_LEN, MAVLINK_MSG_ID_SystemCmd_CRC);
#else
    mavlink_systemcmd_t *packet = (mavlink_systemcmd_t *)msgbuf;
    packet->Sys_cmd = Sys_cmd;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SystemCmd, (const char *)packet, MAVLINK_MSG_ID_SystemCmd_MIN_LEN, MAVLINK_MSG_ID_SystemCmd_LEN, MAVLINK_MSG_ID_SystemCmd_CRC);
#endif
}
#endif

#endif

// MESSAGE SystemCmd UNPACKING


/**
 * @brief Get field Sys_cmd from systemcmd message
 *
 * @return  
 */
static inline uint8_t mavlink_msg_systemcmd_get_Sys_cmd(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  0);
}

/**
 * @brief Decode a systemcmd message into a struct
 *
 * @param msg The message to decode
 * @param systemcmd C-struct to decode the message contents into
 */
static inline void mavlink_msg_systemcmd_decode(const mavlink_message_t* msg, mavlink_systemcmd_t* systemcmd)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    systemcmd->Sys_cmd = mavlink_msg_systemcmd_get_Sys_cmd(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_SystemCmd_LEN? msg->len : MAVLINK_MSG_ID_SystemCmd_LEN;
        memset(systemcmd, 0, MAVLINK_MSG_ID_SystemCmd_LEN);
    memcpy(systemcmd, _MAV_PAYLOAD(msg), len);
#endif
}
