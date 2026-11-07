#pragma once
// MESSAGE ScopeData PACKING

#define MAVLINK_MSG_ID_ScopeData 30016


typedef struct __mavlink_scopedata_t {
 uint8_t frame_data[128]; /*<  */
} mavlink_scopedata_t;

#define MAVLINK_MSG_ID_ScopeData_LEN 128
#define MAVLINK_MSG_ID_ScopeData_MIN_LEN 128
#define MAVLINK_MSG_ID_30016_LEN 128
#define MAVLINK_MSG_ID_30016_MIN_LEN 128

#define MAVLINK_MSG_ID_ScopeData_CRC 104
#define MAVLINK_MSG_ID_30016_CRC 104

#define MAVLINK_MSG_ScopeData_FIELD_FRAME_DATA_LEN 128

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_ScopeData { \
    30016, \
    "ScopeData", \
    1, \
    {  { "frame_data", NULL, MAVLINK_TYPE_UINT8_T, 128, 0, offsetof(mavlink_scopedata_t, frame_data) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_ScopeData { \
    "ScopeData", \
    1, \
    {  { "frame_data", NULL, MAVLINK_TYPE_UINT8_T, 128, 0, offsetof(mavlink_scopedata_t, frame_data) }, \
         } \
}
#endif

/**
 * @brief Pack a scopedata message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param frame_data  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_scopedata_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               const uint8_t *frame_data)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ScopeData_LEN];

    _mav_put_uint8_t_array(buf, 0, frame_data, 128);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ScopeData_LEN);
#else
    mavlink_scopedata_t packet;

    mav_array_memcpy(packet.frame_data, frame_data, sizeof(uint8_t)*128);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ScopeData_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ScopeData;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_ScopeData_MIN_LEN, MAVLINK_MSG_ID_ScopeData_LEN, MAVLINK_MSG_ID_ScopeData_CRC);
}

/**
 * @brief Pack a scopedata message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param frame_data  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_scopedata_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               const uint8_t *frame_data)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ScopeData_LEN];

    _mav_put_uint8_t_array(buf, 0, frame_data, 128);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ScopeData_LEN);
#else
    mavlink_scopedata_t packet;

    mav_array_memcpy(packet.frame_data, frame_data, sizeof(uint8_t)*128);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ScopeData_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ScopeData;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_ScopeData_MIN_LEN, MAVLINK_MSG_ID_ScopeData_LEN, MAVLINK_MSG_ID_ScopeData_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_ScopeData_MIN_LEN, MAVLINK_MSG_ID_ScopeData_LEN);
#endif
}

/**
 * @brief Pack a scopedata message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param frame_data  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_scopedata_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   const uint8_t *frame_data)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ScopeData_LEN];

    _mav_put_uint8_t_array(buf, 0, frame_data, 128);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ScopeData_LEN);
#else
    mavlink_scopedata_t packet;

    mav_array_memcpy(packet.frame_data, frame_data, sizeof(uint8_t)*128);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ScopeData_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ScopeData;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_ScopeData_MIN_LEN, MAVLINK_MSG_ID_ScopeData_LEN, MAVLINK_MSG_ID_ScopeData_CRC);
}

/**
 * @brief Encode a scopedata struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param scopedata C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_scopedata_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_scopedata_t* scopedata)
{
    return mavlink_msg_scopedata_pack(system_id, component_id, msg, scopedata->frame_data);
}

/**
 * @brief Encode a scopedata struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param scopedata C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_scopedata_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_scopedata_t* scopedata)
{
    return mavlink_msg_scopedata_pack_chan(system_id, component_id, chan, msg, scopedata->frame_data);
}

/**
 * @brief Encode a scopedata struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param scopedata C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_scopedata_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_scopedata_t* scopedata)
{
    return mavlink_msg_scopedata_pack_status(system_id, component_id, _status, msg,  scopedata->frame_data);
}

/**
 * @brief Send a scopedata message
 * @param chan MAVLink channel to send the message
 *
 * @param frame_data  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_scopedata_send(mavlink_channel_t chan, const uint8_t *frame_data)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ScopeData_LEN];

    _mav_put_uint8_t_array(buf, 0, frame_data, 128);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ScopeData, buf, MAVLINK_MSG_ID_ScopeData_MIN_LEN, MAVLINK_MSG_ID_ScopeData_LEN, MAVLINK_MSG_ID_ScopeData_CRC);
#else
    mavlink_scopedata_t packet;

    mav_array_memcpy(packet.frame_data, frame_data, sizeof(uint8_t)*128);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ScopeData, (const char *)&packet, MAVLINK_MSG_ID_ScopeData_MIN_LEN, MAVLINK_MSG_ID_ScopeData_LEN, MAVLINK_MSG_ID_ScopeData_CRC);
#endif
}

/**
 * @brief Send a scopedata message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_scopedata_send_struct(mavlink_channel_t chan, const mavlink_scopedata_t* scopedata)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_scopedata_send(chan, scopedata->frame_data);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ScopeData, (const char *)scopedata, MAVLINK_MSG_ID_ScopeData_MIN_LEN, MAVLINK_MSG_ID_ScopeData_LEN, MAVLINK_MSG_ID_ScopeData_CRC);
#endif
}

#if MAVLINK_MSG_ID_ScopeData_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_scopedata_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  const uint8_t *frame_data)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;

    _mav_put_uint8_t_array(buf, 0, frame_data, 128);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ScopeData, buf, MAVLINK_MSG_ID_ScopeData_MIN_LEN, MAVLINK_MSG_ID_ScopeData_LEN, MAVLINK_MSG_ID_ScopeData_CRC);
#else
    mavlink_scopedata_t *packet = (mavlink_scopedata_t *)msgbuf;

    mav_array_memcpy(packet->frame_data, frame_data, sizeof(uint8_t)*128);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ScopeData, (const char *)packet, MAVLINK_MSG_ID_ScopeData_MIN_LEN, MAVLINK_MSG_ID_ScopeData_LEN, MAVLINK_MSG_ID_ScopeData_CRC);
#endif
}
#endif

#endif

// MESSAGE ScopeData UNPACKING


/**
 * @brief Get field frame_data from scopedata message
 *
 * @return  
 */
static inline uint16_t mavlink_msg_scopedata_get_frame_data(const mavlink_message_t* msg, uint8_t *frame_data)
{
    return _MAV_RETURN_uint8_t_array(msg, frame_data, 128,  0);
}

/**
 * @brief Decode a scopedata message into a struct
 *
 * @param msg The message to decode
 * @param scopedata C-struct to decode the message contents into
 */
static inline void mavlink_msg_scopedata_decode(const mavlink_message_t* msg, mavlink_scopedata_t* scopedata)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_scopedata_get_frame_data(msg, scopedata->frame_data);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_ScopeData_LEN? msg->len : MAVLINK_MSG_ID_ScopeData_LEN;
        memset(scopedata, 0, MAVLINK_MSG_ID_ScopeData_LEN);
    memcpy(scopedata, _MAV_PAYLOAD(msg), len);
#endif
}
