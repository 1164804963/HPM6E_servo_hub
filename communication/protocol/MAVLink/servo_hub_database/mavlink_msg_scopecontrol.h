#pragma once
// MESSAGE ScopeControl PACKING

#define MAVLINK_MSG_ID_ScopeControl 30015


typedef struct __mavlink_scopecontrol_t {
 uint32_t frame_info; /*<  */
 uint16_t control_word; /*<  */
 uint16_t frame_num[16]; /*<  */
 uint16_t status_word; /*<  */
} mavlink_scopecontrol_t;

#define MAVLINK_MSG_ID_ScopeControl_LEN 40
#define MAVLINK_MSG_ID_ScopeControl_MIN_LEN 40
#define MAVLINK_MSG_ID_30015_LEN 40
#define MAVLINK_MSG_ID_30015_MIN_LEN 40

#define MAVLINK_MSG_ID_ScopeControl_CRC 108
#define MAVLINK_MSG_ID_30015_CRC 108

#define MAVLINK_MSG_ScopeControl_FIELD_FRAME_NUM_LEN 16

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_ScopeControl { \
    30015, \
    "ScopeControl", \
    4, \
    {  { "control_word", NULL, MAVLINK_TYPE_UINT16_T, 0, 4, offsetof(mavlink_scopecontrol_t, control_word) }, \
         { "frame_info", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_scopecontrol_t, frame_info) }, \
         { "frame_num", NULL, MAVLINK_TYPE_UINT16_T, 16, 6, offsetof(mavlink_scopecontrol_t, frame_num) }, \
         { "status_word", NULL, MAVLINK_TYPE_UINT16_T, 0, 38, offsetof(mavlink_scopecontrol_t, status_word) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_ScopeControl { \
    "ScopeControl", \
    4, \
    {  { "control_word", NULL, MAVLINK_TYPE_UINT16_T, 0, 4, offsetof(mavlink_scopecontrol_t, control_word) }, \
         { "frame_info", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_scopecontrol_t, frame_info) }, \
         { "frame_num", NULL, MAVLINK_TYPE_UINT16_T, 16, 6, offsetof(mavlink_scopecontrol_t, frame_num) }, \
         { "status_word", NULL, MAVLINK_TYPE_UINT16_T, 0, 38, offsetof(mavlink_scopecontrol_t, status_word) }, \
         } \
}
#endif

/**
 * @brief Pack a scopecontrol message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param control_word  
 * @param frame_info  
 * @param frame_num  
 * @param status_word  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_scopecontrol_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint16_t control_word, uint32_t frame_info, const uint16_t *frame_num, uint16_t status_word)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ScopeControl_LEN];
    _mav_put_uint32_t(buf, 0, frame_info);
    _mav_put_uint16_t(buf, 4, control_word);
    _mav_put_uint16_t(buf, 38, status_word);
    _mav_put_uint16_t_array(buf, 6, frame_num, 16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ScopeControl_LEN);
#else
    mavlink_scopecontrol_t packet;
    packet.frame_info = frame_info;
    packet.control_word = control_word;
    packet.status_word = status_word;
    mav_array_memcpy(packet.frame_num, frame_num, sizeof(uint16_t)*16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ScopeControl_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ScopeControl;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_ScopeControl_MIN_LEN, MAVLINK_MSG_ID_ScopeControl_LEN, MAVLINK_MSG_ID_ScopeControl_CRC);
}

/**
 * @brief Pack a scopecontrol message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param control_word  
 * @param frame_info  
 * @param frame_num  
 * @param status_word  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_scopecontrol_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint16_t control_word, uint32_t frame_info, const uint16_t *frame_num, uint16_t status_word)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ScopeControl_LEN];
    _mav_put_uint32_t(buf, 0, frame_info);
    _mav_put_uint16_t(buf, 4, control_word);
    _mav_put_uint16_t(buf, 38, status_word);
    _mav_put_uint16_t_array(buf, 6, frame_num, 16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ScopeControl_LEN);
#else
    mavlink_scopecontrol_t packet;
    packet.frame_info = frame_info;
    packet.control_word = control_word;
    packet.status_word = status_word;
    mav_array_memcpy(packet.frame_num, frame_num, sizeof(uint16_t)*16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ScopeControl_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ScopeControl;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_ScopeControl_MIN_LEN, MAVLINK_MSG_ID_ScopeControl_LEN, MAVLINK_MSG_ID_ScopeControl_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_ScopeControl_MIN_LEN, MAVLINK_MSG_ID_ScopeControl_LEN);
#endif
}

/**
 * @brief Pack a scopecontrol message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param control_word  
 * @param frame_info  
 * @param frame_num  
 * @param status_word  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_scopecontrol_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint16_t control_word,uint32_t frame_info,const uint16_t *frame_num,uint16_t status_word)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ScopeControl_LEN];
    _mav_put_uint32_t(buf, 0, frame_info);
    _mav_put_uint16_t(buf, 4, control_word);
    _mav_put_uint16_t(buf, 38, status_word);
    _mav_put_uint16_t_array(buf, 6, frame_num, 16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ScopeControl_LEN);
#else
    mavlink_scopecontrol_t packet;
    packet.frame_info = frame_info;
    packet.control_word = control_word;
    packet.status_word = status_word;
    mav_array_memcpy(packet.frame_num, frame_num, sizeof(uint16_t)*16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ScopeControl_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ScopeControl;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_ScopeControl_MIN_LEN, MAVLINK_MSG_ID_ScopeControl_LEN, MAVLINK_MSG_ID_ScopeControl_CRC);
}

/**
 * @brief Encode a scopecontrol struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param scopecontrol C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_scopecontrol_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_scopecontrol_t* scopecontrol)
{
    return mavlink_msg_scopecontrol_pack(system_id, component_id, msg, scopecontrol->control_word, scopecontrol->frame_info, scopecontrol->frame_num, scopecontrol->status_word);
}

/**
 * @brief Encode a scopecontrol struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param scopecontrol C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_scopecontrol_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_scopecontrol_t* scopecontrol)
{
    return mavlink_msg_scopecontrol_pack_chan(system_id, component_id, chan, msg, scopecontrol->control_word, scopecontrol->frame_info, scopecontrol->frame_num, scopecontrol->status_word);
}

/**
 * @brief Encode a scopecontrol struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param scopecontrol C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_scopecontrol_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_scopecontrol_t* scopecontrol)
{
    return mavlink_msg_scopecontrol_pack_status(system_id, component_id, _status, msg,  scopecontrol->control_word, scopecontrol->frame_info, scopecontrol->frame_num, scopecontrol->status_word);
}

/**
 * @brief Send a scopecontrol message
 * @param chan MAVLink channel to send the message
 *
 * @param control_word  
 * @param frame_info  
 * @param frame_num  
 * @param status_word  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_scopecontrol_send(mavlink_channel_t chan, uint16_t control_word, uint32_t frame_info, const uint16_t *frame_num, uint16_t status_word)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ScopeControl_LEN];
    _mav_put_uint32_t(buf, 0, frame_info);
    _mav_put_uint16_t(buf, 4, control_word);
    _mav_put_uint16_t(buf, 38, status_word);
    _mav_put_uint16_t_array(buf, 6, frame_num, 16);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ScopeControl, buf, MAVLINK_MSG_ID_ScopeControl_MIN_LEN, MAVLINK_MSG_ID_ScopeControl_LEN, MAVLINK_MSG_ID_ScopeControl_CRC);
#else
    mavlink_scopecontrol_t packet;
    packet.frame_info = frame_info;
    packet.control_word = control_word;
    packet.status_word = status_word;
    mav_array_memcpy(packet.frame_num, frame_num, sizeof(uint16_t)*16);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ScopeControl, (const char *)&packet, MAVLINK_MSG_ID_ScopeControl_MIN_LEN, MAVLINK_MSG_ID_ScopeControl_LEN, MAVLINK_MSG_ID_ScopeControl_CRC);
#endif
}

/**
 * @brief Send a scopecontrol message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_scopecontrol_send_struct(mavlink_channel_t chan, const mavlink_scopecontrol_t* scopecontrol)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_scopecontrol_send(chan, scopecontrol->control_word, scopecontrol->frame_info, scopecontrol->frame_num, scopecontrol->status_word);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ScopeControl, (const char *)scopecontrol, MAVLINK_MSG_ID_ScopeControl_MIN_LEN, MAVLINK_MSG_ID_ScopeControl_LEN, MAVLINK_MSG_ID_ScopeControl_CRC);
#endif
}

#if MAVLINK_MSG_ID_ScopeControl_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_scopecontrol_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint16_t control_word, uint32_t frame_info, const uint16_t *frame_num, uint16_t status_word)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint32_t(buf, 0, frame_info);
    _mav_put_uint16_t(buf, 4, control_word);
    _mav_put_uint16_t(buf, 38, status_word);
    _mav_put_uint16_t_array(buf, 6, frame_num, 16);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ScopeControl, buf, MAVLINK_MSG_ID_ScopeControl_MIN_LEN, MAVLINK_MSG_ID_ScopeControl_LEN, MAVLINK_MSG_ID_ScopeControl_CRC);
#else
    mavlink_scopecontrol_t *packet = (mavlink_scopecontrol_t *)msgbuf;
    packet->frame_info = frame_info;
    packet->control_word = control_word;
    packet->status_word = status_word;
    mav_array_memcpy(packet->frame_num, frame_num, sizeof(uint16_t)*16);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ScopeControl, (const char *)packet, MAVLINK_MSG_ID_ScopeControl_MIN_LEN, MAVLINK_MSG_ID_ScopeControl_LEN, MAVLINK_MSG_ID_ScopeControl_CRC);
#endif
}
#endif

#endif

// MESSAGE ScopeControl UNPACKING


/**
 * @brief Get field control_word from scopecontrol message
 *
 * @return  
 */
static inline uint16_t mavlink_msg_scopecontrol_get_control_word(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  4);
}

/**
 * @brief Get field frame_info from scopecontrol message
 *
 * @return  
 */
static inline uint32_t mavlink_msg_scopecontrol_get_frame_info(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Get field frame_num from scopecontrol message
 *
 * @return  
 */
static inline uint16_t mavlink_msg_scopecontrol_get_frame_num(const mavlink_message_t* msg, uint16_t *frame_num)
{
    return _MAV_RETURN_uint16_t_array(msg, frame_num, 16,  6);
}

/**
 * @brief Get field status_word from scopecontrol message
 *
 * @return  
 */
static inline uint16_t mavlink_msg_scopecontrol_get_status_word(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  38);
}

/**
 * @brief Decode a scopecontrol message into a struct
 *
 * @param msg The message to decode
 * @param scopecontrol C-struct to decode the message contents into
 */
static inline void mavlink_msg_scopecontrol_decode(const mavlink_message_t* msg, mavlink_scopecontrol_t* scopecontrol)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    scopecontrol->frame_info = mavlink_msg_scopecontrol_get_frame_info(msg);
    scopecontrol->control_word = mavlink_msg_scopecontrol_get_control_word(msg);
    mavlink_msg_scopecontrol_get_frame_num(msg, scopecontrol->frame_num);
    scopecontrol->status_word = mavlink_msg_scopecontrol_get_status_word(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_ScopeControl_LEN? msg->len : MAVLINK_MSG_ID_ScopeControl_LEN;
        memset(scopecontrol, 0, MAVLINK_MSG_ID_ScopeControl_LEN);
    memcpy(scopecontrol, _MAV_PAYLOAD(msg), len);
#endif
}
