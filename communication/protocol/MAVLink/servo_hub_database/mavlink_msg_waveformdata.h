#pragma once
// MESSAGE WaveformData PACKING

#define MAVLINK_MSG_ID_WaveformData 30017


typedef struct __mavlink_waveformdata_t {
 int64_t waveform_data_array[6]; /*<  */
} mavlink_waveformdata_t;

#define MAVLINK_MSG_ID_WaveformData_LEN 48
#define MAVLINK_MSG_ID_WaveformData_MIN_LEN 48
#define MAVLINK_MSG_ID_30017_LEN 48
#define MAVLINK_MSG_ID_30017_MIN_LEN 48

#define MAVLINK_MSG_ID_WaveformData_CRC 78
#define MAVLINK_MSG_ID_30017_CRC 78

#define MAVLINK_MSG_WaveformData_FIELD_WAVEFORM_DATA_ARRAY_LEN 6

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_WaveformData { \
    30017, \
    "WaveformData", \
    1, \
    {  { "waveform_data_array", NULL, MAVLINK_TYPE_INT64_T, 6, 0, offsetof(mavlink_waveformdata_t, waveform_data_array) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_WaveformData { \
    "WaveformData", \
    1, \
    {  { "waveform_data_array", NULL, MAVLINK_TYPE_INT64_T, 6, 0, offsetof(mavlink_waveformdata_t, waveform_data_array) }, \
         } \
}
#endif

/**
 * @brief Pack a waveformdata message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param waveform_data_array  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_waveformdata_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               const int64_t *waveform_data_array)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_WaveformData_LEN];

    _mav_put_int64_t_array(buf, 0, waveform_data_array, 6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_WaveformData_LEN);
#else
    mavlink_waveformdata_t packet;

    mav_array_memcpy(packet.waveform_data_array, waveform_data_array, sizeof(int64_t)*6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_WaveformData_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_WaveformData;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_WaveformData_MIN_LEN, MAVLINK_MSG_ID_WaveformData_LEN, MAVLINK_MSG_ID_WaveformData_CRC);
}

/**
 * @brief Pack a waveformdata message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param waveform_data_array  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_waveformdata_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               const int64_t *waveform_data_array)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_WaveformData_LEN];

    _mav_put_int64_t_array(buf, 0, waveform_data_array, 6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_WaveformData_LEN);
#else
    mavlink_waveformdata_t packet;

    mav_array_memcpy(packet.waveform_data_array, waveform_data_array, sizeof(int64_t)*6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_WaveformData_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_WaveformData;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_WaveformData_MIN_LEN, MAVLINK_MSG_ID_WaveformData_LEN, MAVLINK_MSG_ID_WaveformData_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_WaveformData_MIN_LEN, MAVLINK_MSG_ID_WaveformData_LEN);
#endif
}

/**
 * @brief Pack a waveformdata message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param waveform_data_array  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_waveformdata_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   const int64_t *waveform_data_array)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_WaveformData_LEN];

    _mav_put_int64_t_array(buf, 0, waveform_data_array, 6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_WaveformData_LEN);
#else
    mavlink_waveformdata_t packet;

    mav_array_memcpy(packet.waveform_data_array, waveform_data_array, sizeof(int64_t)*6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_WaveformData_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_WaveformData;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_WaveformData_MIN_LEN, MAVLINK_MSG_ID_WaveformData_LEN, MAVLINK_MSG_ID_WaveformData_CRC);
}

/**
 * @brief Encode a waveformdata struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param waveformdata C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_waveformdata_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_waveformdata_t* waveformdata)
{
    return mavlink_msg_waveformdata_pack(system_id, component_id, msg, waveformdata->waveform_data_array);
}

/**
 * @brief Encode a waveformdata struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param waveformdata C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_waveformdata_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_waveformdata_t* waveformdata)
{
    return mavlink_msg_waveformdata_pack_chan(system_id, component_id, chan, msg, waveformdata->waveform_data_array);
}

/**
 * @brief Encode a waveformdata struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param waveformdata C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_waveformdata_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_waveformdata_t* waveformdata)
{
    return mavlink_msg_waveformdata_pack_status(system_id, component_id, _status, msg,  waveformdata->waveform_data_array);
}

/**
 * @brief Send a waveformdata message
 * @param chan MAVLink channel to send the message
 *
 * @param waveform_data_array  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_waveformdata_send(mavlink_channel_t chan, const int64_t *waveform_data_array)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_WaveformData_LEN];

    _mav_put_int64_t_array(buf, 0, waveform_data_array, 6);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_WaveformData, buf, MAVLINK_MSG_ID_WaveformData_MIN_LEN, MAVLINK_MSG_ID_WaveformData_LEN, MAVLINK_MSG_ID_WaveformData_CRC);
#else
    mavlink_waveformdata_t packet;

    mav_array_memcpy(packet.waveform_data_array, waveform_data_array, sizeof(int64_t)*6);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_WaveformData, (const char *)&packet, MAVLINK_MSG_ID_WaveformData_MIN_LEN, MAVLINK_MSG_ID_WaveformData_LEN, MAVLINK_MSG_ID_WaveformData_CRC);
#endif
}

/**
 * @brief Send a waveformdata message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_waveformdata_send_struct(mavlink_channel_t chan, const mavlink_waveformdata_t* waveformdata)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_waveformdata_send(chan, waveformdata->waveform_data_array);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_WaveformData, (const char *)waveformdata, MAVLINK_MSG_ID_WaveformData_MIN_LEN, MAVLINK_MSG_ID_WaveformData_LEN, MAVLINK_MSG_ID_WaveformData_CRC);
#endif
}

#if MAVLINK_MSG_ID_WaveformData_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_waveformdata_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  const int64_t *waveform_data_array)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;

    _mav_put_int64_t_array(buf, 0, waveform_data_array, 6);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_WaveformData, buf, MAVLINK_MSG_ID_WaveformData_MIN_LEN, MAVLINK_MSG_ID_WaveformData_LEN, MAVLINK_MSG_ID_WaveformData_CRC);
#else
    mavlink_waveformdata_t *packet = (mavlink_waveformdata_t *)msgbuf;

    mav_array_memcpy(packet->waveform_data_array, waveform_data_array, sizeof(int64_t)*6);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_WaveformData, (const char *)packet, MAVLINK_MSG_ID_WaveformData_MIN_LEN, MAVLINK_MSG_ID_WaveformData_LEN, MAVLINK_MSG_ID_WaveformData_CRC);
#endif
}
#endif

#endif

// MESSAGE WaveformData UNPACKING


/**
 * @brief Get field waveform_data_array from waveformdata message
 *
 * @return  
 */
static inline uint16_t mavlink_msg_waveformdata_get_waveform_data_array(const mavlink_message_t* msg, int64_t *waveform_data_array)
{
    return _MAV_RETURN_int64_t_array(msg, waveform_data_array, 6,  0);
}

/**
 * @brief Decode a waveformdata message into a struct
 *
 * @param msg The message to decode
 * @param waveformdata C-struct to decode the message contents into
 */
static inline void mavlink_msg_waveformdata_decode(const mavlink_message_t* msg, mavlink_waveformdata_t* waveformdata)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_waveformdata_get_waveform_data_array(msg, waveformdata->waveform_data_array);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_WaveformData_LEN? msg->len : MAVLINK_MSG_ID_WaveformData_LEN;
        memset(waveformdata, 0, MAVLINK_MSG_ID_WaveformData_LEN);
    memcpy(waveformdata, _MAV_PAYLOAD(msg), len);
#endif
}
