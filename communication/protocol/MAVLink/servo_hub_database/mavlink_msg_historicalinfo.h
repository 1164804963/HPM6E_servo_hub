#pragma once
// MESSAGE HistoricalInfo PACKING

#define MAVLINK_MSG_ID_HistoricalInfo 30078


typedef struct __mavlink_historicalinfo_t {
 uint32_t Error_records_list[16]; /*<  */
} mavlink_historicalinfo_t;

#define MAVLINK_MSG_ID_HistoricalInfo_LEN 64
#define MAVLINK_MSG_ID_HistoricalInfo_MIN_LEN 64
#define MAVLINK_MSG_ID_30078_LEN 64
#define MAVLINK_MSG_ID_30078_MIN_LEN 64

#define MAVLINK_MSG_ID_HistoricalInfo_CRC 158
#define MAVLINK_MSG_ID_30078_CRC 158

#define MAVLINK_MSG_HistoricalInfo_FIELD_ERROR_RECORDS_LIST_LEN 16

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_HistoricalInfo { \
    30078, \
    "HistoricalInfo", \
    1, \
    {  { "Error_records_list", NULL, MAVLINK_TYPE_UINT32_T, 16, 0, offsetof(mavlink_historicalinfo_t, Error_records_list) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_HistoricalInfo { \
    "HistoricalInfo", \
    1, \
    {  { "Error_records_list", NULL, MAVLINK_TYPE_UINT32_T, 16, 0, offsetof(mavlink_historicalinfo_t, Error_records_list) }, \
         } \
}
#endif

/**
 * @brief Pack a historicalinfo message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param Error_records_list  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_historicalinfo_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               const uint32_t *Error_records_list)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_HistoricalInfo_LEN];

    _mav_put_uint32_t_array(buf, 0, Error_records_list, 16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_HistoricalInfo_LEN);
#else
    mavlink_historicalinfo_t packet;

    mav_array_memcpy(packet.Error_records_list, Error_records_list, sizeof(uint32_t)*16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_HistoricalInfo_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_HistoricalInfo;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_HistoricalInfo_MIN_LEN, MAVLINK_MSG_ID_HistoricalInfo_LEN, MAVLINK_MSG_ID_HistoricalInfo_CRC);
}

/**
 * @brief Pack a historicalinfo message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param Error_records_list  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_historicalinfo_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               const uint32_t *Error_records_list)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_HistoricalInfo_LEN];

    _mav_put_uint32_t_array(buf, 0, Error_records_list, 16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_HistoricalInfo_LEN);
#else
    mavlink_historicalinfo_t packet;

    mav_array_memcpy(packet.Error_records_list, Error_records_list, sizeof(uint32_t)*16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_HistoricalInfo_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_HistoricalInfo;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_HistoricalInfo_MIN_LEN, MAVLINK_MSG_ID_HistoricalInfo_LEN, MAVLINK_MSG_ID_HistoricalInfo_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_HistoricalInfo_MIN_LEN, MAVLINK_MSG_ID_HistoricalInfo_LEN);
#endif
}

/**
 * @brief Pack a historicalinfo message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param Error_records_list  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_historicalinfo_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   const uint32_t *Error_records_list)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_HistoricalInfo_LEN];

    _mav_put_uint32_t_array(buf, 0, Error_records_list, 16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_HistoricalInfo_LEN);
#else
    mavlink_historicalinfo_t packet;

    mav_array_memcpy(packet.Error_records_list, Error_records_list, sizeof(uint32_t)*16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_HistoricalInfo_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_HistoricalInfo;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_HistoricalInfo_MIN_LEN, MAVLINK_MSG_ID_HistoricalInfo_LEN, MAVLINK_MSG_ID_HistoricalInfo_CRC);
}

/**
 * @brief Encode a historicalinfo struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param historicalinfo C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_historicalinfo_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_historicalinfo_t* historicalinfo)
{
    return mavlink_msg_historicalinfo_pack(system_id, component_id, msg, historicalinfo->Error_records_list);
}

/**
 * @brief Encode a historicalinfo struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param historicalinfo C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_historicalinfo_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_historicalinfo_t* historicalinfo)
{
    return mavlink_msg_historicalinfo_pack_chan(system_id, component_id, chan, msg, historicalinfo->Error_records_list);
}

/**
 * @brief Encode a historicalinfo struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param historicalinfo C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_historicalinfo_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_historicalinfo_t* historicalinfo)
{
    return mavlink_msg_historicalinfo_pack_status(system_id, component_id, _status, msg,  historicalinfo->Error_records_list);
}

/**
 * @brief Send a historicalinfo message
 * @param chan MAVLink channel to send the message
 *
 * @param Error_records_list  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_historicalinfo_send(mavlink_channel_t chan, const uint32_t *Error_records_list)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_HistoricalInfo_LEN];

    _mav_put_uint32_t_array(buf, 0, Error_records_list, 16);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HistoricalInfo, buf, MAVLINK_MSG_ID_HistoricalInfo_MIN_LEN, MAVLINK_MSG_ID_HistoricalInfo_LEN, MAVLINK_MSG_ID_HistoricalInfo_CRC);
#else
    mavlink_historicalinfo_t packet;

    mav_array_memcpy(packet.Error_records_list, Error_records_list, sizeof(uint32_t)*16);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HistoricalInfo, (const char *)&packet, MAVLINK_MSG_ID_HistoricalInfo_MIN_LEN, MAVLINK_MSG_ID_HistoricalInfo_LEN, MAVLINK_MSG_ID_HistoricalInfo_CRC);
#endif
}

/**
 * @brief Send a historicalinfo message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_historicalinfo_send_struct(mavlink_channel_t chan, const mavlink_historicalinfo_t* historicalinfo)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_historicalinfo_send(chan, historicalinfo->Error_records_list);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HistoricalInfo, (const char *)historicalinfo, MAVLINK_MSG_ID_HistoricalInfo_MIN_LEN, MAVLINK_MSG_ID_HistoricalInfo_LEN, MAVLINK_MSG_ID_HistoricalInfo_CRC);
#endif
}

#if MAVLINK_MSG_ID_HistoricalInfo_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_historicalinfo_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  const uint32_t *Error_records_list)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;

    _mav_put_uint32_t_array(buf, 0, Error_records_list, 16);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HistoricalInfo, buf, MAVLINK_MSG_ID_HistoricalInfo_MIN_LEN, MAVLINK_MSG_ID_HistoricalInfo_LEN, MAVLINK_MSG_ID_HistoricalInfo_CRC);
#else
    mavlink_historicalinfo_t *packet = (mavlink_historicalinfo_t *)msgbuf;

    mav_array_memcpy(packet->Error_records_list, Error_records_list, sizeof(uint32_t)*16);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HistoricalInfo, (const char *)packet, MAVLINK_MSG_ID_HistoricalInfo_MIN_LEN, MAVLINK_MSG_ID_HistoricalInfo_LEN, MAVLINK_MSG_ID_HistoricalInfo_CRC);
#endif
}
#endif

#endif

// MESSAGE HistoricalInfo UNPACKING


/**
 * @brief Get field Error_records_list from historicalinfo message
 *
 * @return  
 */
static inline uint16_t mavlink_msg_historicalinfo_get_Error_records_list(const mavlink_message_t* msg, uint32_t *Error_records_list)
{
    return _MAV_RETURN_uint32_t_array(msg, Error_records_list, 16,  0);
}

/**
 * @brief Decode a historicalinfo message into a struct
 *
 * @param msg The message to decode
 * @param historicalinfo C-struct to decode the message contents into
 */
static inline void mavlink_msg_historicalinfo_decode(const mavlink_message_t* msg, mavlink_historicalinfo_t* historicalinfo)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_historicalinfo_get_Error_records_list(msg, historicalinfo->Error_records_list);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_HistoricalInfo_LEN? msg->len : MAVLINK_MSG_ID_HistoricalInfo_LEN;
        memset(historicalinfo, 0, MAVLINK_MSG_ID_HistoricalInfo_LEN);
    memcpy(historicalinfo, _MAV_PAYLOAD(msg), len);
#endif
}
