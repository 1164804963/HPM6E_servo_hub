#pragma once
// MESSAGE WaveformMap PACKING

#define MAVLINK_MSG_ID_WaveformMap 30018


typedef struct __mavlink_waveformmap_t {
 int32_t waveform_map_info[6]; /*<  */
} mavlink_waveformmap_t;

#define MAVLINK_MSG_ID_WaveformMap_LEN 24
#define MAVLINK_MSG_ID_WaveformMap_MIN_LEN 24
#define MAVLINK_MSG_ID_30018_LEN 24
#define MAVLINK_MSG_ID_30018_MIN_LEN 24

#define MAVLINK_MSG_ID_WaveformMap_CRC 96
#define MAVLINK_MSG_ID_30018_CRC 96

#define MAVLINK_MSG_WaveformMap_FIELD_WAVEFORM_MAP_INFO_LEN 6

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_WaveformMap { \
    30018, \
    "WaveformMap", \
    1, \
    {  { "waveform_map_info", NULL, MAVLINK_TYPE_INT32_T, 6, 0, offsetof(mavlink_waveformmap_t, waveform_map_info) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_WaveformMap { \
    "WaveformMap", \
    1, \
    {  { "waveform_map_info", NULL, MAVLINK_TYPE_INT32_T, 6, 0, offsetof(mavlink_waveformmap_t, waveform_map_info) }, \
         } \
}
#endif

/**
 * @brief Pack a waveformmap message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param waveform_map_info  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_waveformmap_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               const int32_t *waveform_map_info)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_WaveformMap_LEN];

    _mav_put_int32_t_array(buf, 0, waveform_map_info, 6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_WaveformMap_LEN);
#else
    mavlink_waveformmap_t packet;

    mav_array_memcpy(packet.waveform_map_info, waveform_map_info, sizeof(int32_t)*6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_WaveformMap_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_WaveformMap;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_WaveformMap_MIN_LEN, MAVLINK_MSG_ID_WaveformMap_LEN, MAVLINK_MSG_ID_WaveformMap_CRC);
}

/**
 * @brief Pack a waveformmap message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param waveform_map_info  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_waveformmap_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               const int32_t *waveform_map_info)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_WaveformMap_LEN];

    _mav_put_int32_t_array(buf, 0, waveform_map_info, 6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_WaveformMap_LEN);
#else
    mavlink_waveformmap_t packet;

    mav_array_memcpy(packet.waveform_map_info, waveform_map_info, sizeof(int32_t)*6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_WaveformMap_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_WaveformMap;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_WaveformMap_MIN_LEN, MAVLINK_MSG_ID_WaveformMap_LEN, MAVLINK_MSG_ID_WaveformMap_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_WaveformMap_MIN_LEN, MAVLINK_MSG_ID_WaveformMap_LEN);
#endif
}

/**
 * @brief Pack a waveformmap message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param waveform_map_info  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_waveformmap_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   const int32_t *waveform_map_info)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_WaveformMap_LEN];

    _mav_put_int32_t_array(buf, 0, waveform_map_info, 6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_WaveformMap_LEN);
#else
    mavlink_waveformmap_t packet;

    mav_array_memcpy(packet.waveform_map_info, waveform_map_info, sizeof(int32_t)*6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_WaveformMap_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_WaveformMap;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_WaveformMap_MIN_LEN, MAVLINK_MSG_ID_WaveformMap_LEN, MAVLINK_MSG_ID_WaveformMap_CRC);
}

/**
 * @brief Encode a waveformmap struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param waveformmap C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_waveformmap_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_waveformmap_t* waveformmap)
{
    return mavlink_msg_waveformmap_pack(system_id, component_id, msg, waveformmap->waveform_map_info);
}

/**
 * @brief Encode a waveformmap struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param waveformmap C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_waveformmap_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_waveformmap_t* waveformmap)
{
    return mavlink_msg_waveformmap_pack_chan(system_id, component_id, chan, msg, waveformmap->waveform_map_info);
}

/**
 * @brief Encode a waveformmap struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param waveformmap C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_waveformmap_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_waveformmap_t* waveformmap)
{
    return mavlink_msg_waveformmap_pack_status(system_id, component_id, _status, msg,  waveformmap->waveform_map_info);
}

/**
 * @brief Send a waveformmap message
 * @param chan MAVLink channel to send the message
 *
 * @param waveform_map_info  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_waveformmap_send(mavlink_channel_t chan, const int32_t *waveform_map_info)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_WaveformMap_LEN];

    _mav_put_int32_t_array(buf, 0, waveform_map_info, 6);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_WaveformMap, buf, MAVLINK_MSG_ID_WaveformMap_MIN_LEN, MAVLINK_MSG_ID_WaveformMap_LEN, MAVLINK_MSG_ID_WaveformMap_CRC);
#else
    mavlink_waveformmap_t packet;

    mav_array_memcpy(packet.waveform_map_info, waveform_map_info, sizeof(int32_t)*6);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_WaveformMap, (const char *)&packet, MAVLINK_MSG_ID_WaveformMap_MIN_LEN, MAVLINK_MSG_ID_WaveformMap_LEN, MAVLINK_MSG_ID_WaveformMap_CRC);
#endif
}

/**
 * @brief Send a waveformmap message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_waveformmap_send_struct(mavlink_channel_t chan, const mavlink_waveformmap_t* waveformmap)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_waveformmap_send(chan, waveformmap->waveform_map_info);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_WaveformMap, (const char *)waveformmap, MAVLINK_MSG_ID_WaveformMap_MIN_LEN, MAVLINK_MSG_ID_WaveformMap_LEN, MAVLINK_MSG_ID_WaveformMap_CRC);
#endif
}

#if MAVLINK_MSG_ID_WaveformMap_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_waveformmap_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  const int32_t *waveform_map_info)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;

    _mav_put_int32_t_array(buf, 0, waveform_map_info, 6);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_WaveformMap, buf, MAVLINK_MSG_ID_WaveformMap_MIN_LEN, MAVLINK_MSG_ID_WaveformMap_LEN, MAVLINK_MSG_ID_WaveformMap_CRC);
#else
    mavlink_waveformmap_t *packet = (mavlink_waveformmap_t *)msgbuf;

    mav_array_memcpy(packet->waveform_map_info, waveform_map_info, sizeof(int32_t)*6);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_WaveformMap, (const char *)packet, MAVLINK_MSG_ID_WaveformMap_MIN_LEN, MAVLINK_MSG_ID_WaveformMap_LEN, MAVLINK_MSG_ID_WaveformMap_CRC);
#endif
}
#endif

#endif

// MESSAGE WaveformMap UNPACKING


/**
 * @brief Get field waveform_map_info from waveformmap message
 *
 * @return  
 */
static inline uint16_t mavlink_msg_waveformmap_get_waveform_map_info(const mavlink_message_t* msg, int32_t *waveform_map_info)
{
    return _MAV_RETURN_int32_t_array(msg, waveform_map_info, 6,  0);
}

/**
 * @brief Decode a waveformmap message into a struct
 *
 * @param msg The message to decode
 * @param waveformmap C-struct to decode the message contents into
 */
static inline void mavlink_msg_waveformmap_decode(const mavlink_message_t* msg, mavlink_waveformmap_t* waveformmap)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_waveformmap_get_waveform_map_info(msg, waveformmap->waveform_map_info);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_WaveformMap_LEN? msg->len : MAVLINK_MSG_ID_WaveformMap_LEN;
        memset(waveformmap, 0, MAVLINK_MSG_ID_WaveformMap_LEN);
    memcpy(waveformmap, _MAV_PAYLOAD(msg), len);
#endif
}
