#pragma once
// MESSAGE AppControlWord PACKING

#define MAVLINK_MSG_ID_AppControlWord 30054


typedef struct __mavlink_appcontrolword_t {
 uint16_t Controlword; /*<  */
 uint8_t Halt_running_cmd; /*<  */
} mavlink_appcontrolword_t;

#define MAVLINK_MSG_ID_AppControlWord_LEN 3
#define MAVLINK_MSG_ID_AppControlWord_MIN_LEN 3
#define MAVLINK_MSG_ID_30054_LEN 3
#define MAVLINK_MSG_ID_30054_MIN_LEN 3

#define MAVLINK_MSG_ID_AppControlWord_CRC 108
#define MAVLINK_MSG_ID_30054_CRC 108



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_AppControlWord { \
    30054, \
    "AppControlWord", \
    2, \
    {  { "Controlword", NULL, MAVLINK_TYPE_UINT16_T, 0, 0, offsetof(mavlink_appcontrolword_t, Controlword) }, \
         { "Halt_running_cmd", NULL, MAVLINK_TYPE_UINT8_T, 0, 2, offsetof(mavlink_appcontrolword_t, Halt_running_cmd) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_AppControlWord { \
    "AppControlWord", \
    2, \
    {  { "Controlword", NULL, MAVLINK_TYPE_UINT16_T, 0, 0, offsetof(mavlink_appcontrolword_t, Controlword) }, \
         { "Halt_running_cmd", NULL, MAVLINK_TYPE_UINT8_T, 0, 2, offsetof(mavlink_appcontrolword_t, Halt_running_cmd) }, \
         } \
}
#endif

/**
 * @brief Pack a appcontrolword message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param Controlword  
 * @param Halt_running_cmd  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_appcontrolword_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint16_t Controlword, uint8_t Halt_running_cmd)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_AppControlWord_LEN];
    _mav_put_uint16_t(buf, 0, Controlword);
    _mav_put_uint8_t(buf, 2, Halt_running_cmd);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_AppControlWord_LEN);
#else
    mavlink_appcontrolword_t packet;
    packet.Controlword = Controlword;
    packet.Halt_running_cmd = Halt_running_cmd;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_AppControlWord_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_AppControlWord;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_AppControlWord_MIN_LEN, MAVLINK_MSG_ID_AppControlWord_LEN, MAVLINK_MSG_ID_AppControlWord_CRC);
}

/**
 * @brief Pack a appcontrolword message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param Controlword  
 * @param Halt_running_cmd  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_appcontrolword_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint16_t Controlword, uint8_t Halt_running_cmd)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_AppControlWord_LEN];
    _mav_put_uint16_t(buf, 0, Controlword);
    _mav_put_uint8_t(buf, 2, Halt_running_cmd);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_AppControlWord_LEN);
#else
    mavlink_appcontrolword_t packet;
    packet.Controlword = Controlword;
    packet.Halt_running_cmd = Halt_running_cmd;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_AppControlWord_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_AppControlWord;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_AppControlWord_MIN_LEN, MAVLINK_MSG_ID_AppControlWord_LEN, MAVLINK_MSG_ID_AppControlWord_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_AppControlWord_MIN_LEN, MAVLINK_MSG_ID_AppControlWord_LEN);
#endif
}

/**
 * @brief Pack a appcontrolword message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param Controlword  
 * @param Halt_running_cmd  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_appcontrolword_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint16_t Controlword,uint8_t Halt_running_cmd)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_AppControlWord_LEN];
    _mav_put_uint16_t(buf, 0, Controlword);
    _mav_put_uint8_t(buf, 2, Halt_running_cmd);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_AppControlWord_LEN);
#else
    mavlink_appcontrolword_t packet;
    packet.Controlword = Controlword;
    packet.Halt_running_cmd = Halt_running_cmd;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_AppControlWord_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_AppControlWord;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_AppControlWord_MIN_LEN, MAVLINK_MSG_ID_AppControlWord_LEN, MAVLINK_MSG_ID_AppControlWord_CRC);
}

/**
 * @brief Encode a appcontrolword struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param appcontrolword C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_appcontrolword_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_appcontrolword_t* appcontrolword)
{
    return mavlink_msg_appcontrolword_pack(system_id, component_id, msg, appcontrolword->Controlword, appcontrolword->Halt_running_cmd);
}

/**
 * @brief Encode a appcontrolword struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param appcontrolword C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_appcontrolword_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_appcontrolword_t* appcontrolword)
{
    return mavlink_msg_appcontrolword_pack_chan(system_id, component_id, chan, msg, appcontrolword->Controlword, appcontrolword->Halt_running_cmd);
}

/**
 * @brief Encode a appcontrolword struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param appcontrolword C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_appcontrolword_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_appcontrolword_t* appcontrolword)
{
    return mavlink_msg_appcontrolword_pack_status(system_id, component_id, _status, msg,  appcontrolword->Controlword, appcontrolword->Halt_running_cmd);
}

/**
 * @brief Send a appcontrolword message
 * @param chan MAVLink channel to send the message
 *
 * @param Controlword  
 * @param Halt_running_cmd  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_appcontrolword_send(mavlink_channel_t chan, uint16_t Controlword, uint8_t Halt_running_cmd)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_AppControlWord_LEN];
    _mav_put_uint16_t(buf, 0, Controlword);
    _mav_put_uint8_t(buf, 2, Halt_running_cmd);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppControlWord, buf, MAVLINK_MSG_ID_AppControlWord_MIN_LEN, MAVLINK_MSG_ID_AppControlWord_LEN, MAVLINK_MSG_ID_AppControlWord_CRC);
#else
    mavlink_appcontrolword_t packet;
    packet.Controlword = Controlword;
    packet.Halt_running_cmd = Halt_running_cmd;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppControlWord, (const char *)&packet, MAVLINK_MSG_ID_AppControlWord_MIN_LEN, MAVLINK_MSG_ID_AppControlWord_LEN, MAVLINK_MSG_ID_AppControlWord_CRC);
#endif
}

/**
 * @brief Send a appcontrolword message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_appcontrolword_send_struct(mavlink_channel_t chan, const mavlink_appcontrolword_t* appcontrolword)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_appcontrolword_send(chan, appcontrolword->Controlword, appcontrolword->Halt_running_cmd);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppControlWord, (const char *)appcontrolword, MAVLINK_MSG_ID_AppControlWord_MIN_LEN, MAVLINK_MSG_ID_AppControlWord_LEN, MAVLINK_MSG_ID_AppControlWord_CRC);
#endif
}

#if MAVLINK_MSG_ID_AppControlWord_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_appcontrolword_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint16_t Controlword, uint8_t Halt_running_cmd)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint16_t(buf, 0, Controlword);
    _mav_put_uint8_t(buf, 2, Halt_running_cmd);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppControlWord, buf, MAVLINK_MSG_ID_AppControlWord_MIN_LEN, MAVLINK_MSG_ID_AppControlWord_LEN, MAVLINK_MSG_ID_AppControlWord_CRC);
#else
    mavlink_appcontrolword_t *packet = (mavlink_appcontrolword_t *)msgbuf;
    packet->Controlword = Controlword;
    packet->Halt_running_cmd = Halt_running_cmd;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppControlWord, (const char *)packet, MAVLINK_MSG_ID_AppControlWord_MIN_LEN, MAVLINK_MSG_ID_AppControlWord_LEN, MAVLINK_MSG_ID_AppControlWord_CRC);
#endif
}
#endif

#endif

// MESSAGE AppControlWord UNPACKING


/**
 * @brief Get field Controlword from appcontrolword message
 *
 * @return  
 */
static inline uint16_t mavlink_msg_appcontrolword_get_Controlword(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  0);
}

/**
 * @brief Get field Halt_running_cmd from appcontrolword message
 *
 * @return  
 */
static inline uint8_t mavlink_msg_appcontrolword_get_Halt_running_cmd(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  2);
}

/**
 * @brief Decode a appcontrolword message into a struct
 *
 * @param msg The message to decode
 * @param appcontrolword C-struct to decode the message contents into
 */
static inline void mavlink_msg_appcontrolword_decode(const mavlink_message_t* msg, mavlink_appcontrolword_t* appcontrolword)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    appcontrolword->Controlword = mavlink_msg_appcontrolword_get_Controlword(msg);
    appcontrolword->Halt_running_cmd = mavlink_msg_appcontrolword_get_Halt_running_cmd(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_AppControlWord_LEN? msg->len : MAVLINK_MSG_ID_AppControlWord_LEN;
        memset(appcontrolword, 0, MAVLINK_MSG_ID_AppControlWord_LEN);
    memcpy(appcontrolword, _MAV_PAYLOAD(msg), len);
#endif
}
