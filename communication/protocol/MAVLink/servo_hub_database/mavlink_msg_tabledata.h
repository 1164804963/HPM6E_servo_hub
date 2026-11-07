#pragma once
// MESSAGE TableData PACKING

#define MAVLINK_MSG_ID_TableData 30083


typedef struct __mavlink_tabledata_t {
 float table_data[20]; /*<  */
} mavlink_tabledata_t;

#define MAVLINK_MSG_ID_TableData_LEN 80
#define MAVLINK_MSG_ID_TableData_MIN_LEN 80
#define MAVLINK_MSG_ID_30083_LEN 80
#define MAVLINK_MSG_ID_30083_MIN_LEN 80

#define MAVLINK_MSG_ID_TableData_CRC 166
#define MAVLINK_MSG_ID_30083_CRC 166

#define MAVLINK_MSG_TableData_FIELD_TABLE_DATA_LEN 20

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_TableData { \
    30083, \
    "TableData", \
    1, \
    {  { "table_data", NULL, MAVLINK_TYPE_FLOAT, 20, 0, offsetof(mavlink_tabledata_t, table_data) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_TableData { \
    "TableData", \
    1, \
    {  { "table_data", NULL, MAVLINK_TYPE_FLOAT, 20, 0, offsetof(mavlink_tabledata_t, table_data) }, \
         } \
}
#endif

/**
 * @brief Pack a tabledata message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param table_data  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_tabledata_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               const float *table_data)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TableData_LEN];

    _mav_put_float_array(buf, 0, table_data, 20);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_TableData_LEN);
#else
    mavlink_tabledata_t packet;

    mav_array_memcpy(packet.table_data, table_data, sizeof(float)*20);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_TableData_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_TableData;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_TableData_MIN_LEN, MAVLINK_MSG_ID_TableData_LEN, MAVLINK_MSG_ID_TableData_CRC);
}

/**
 * @brief Pack a tabledata message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param table_data  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_tabledata_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               const float *table_data)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TableData_LEN];

    _mav_put_float_array(buf, 0, table_data, 20);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_TableData_LEN);
#else
    mavlink_tabledata_t packet;

    mav_array_memcpy(packet.table_data, table_data, sizeof(float)*20);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_TableData_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_TableData;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_TableData_MIN_LEN, MAVLINK_MSG_ID_TableData_LEN, MAVLINK_MSG_ID_TableData_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_TableData_MIN_LEN, MAVLINK_MSG_ID_TableData_LEN);
#endif
}

/**
 * @brief Pack a tabledata message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param table_data  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_tabledata_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   const float *table_data)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TableData_LEN];

    _mav_put_float_array(buf, 0, table_data, 20);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_TableData_LEN);
#else
    mavlink_tabledata_t packet;

    mav_array_memcpy(packet.table_data, table_data, sizeof(float)*20);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_TableData_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_TableData;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_TableData_MIN_LEN, MAVLINK_MSG_ID_TableData_LEN, MAVLINK_MSG_ID_TableData_CRC);
}

/**
 * @brief Encode a tabledata struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param tabledata C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_tabledata_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_tabledata_t* tabledata)
{
    return mavlink_msg_tabledata_pack(system_id, component_id, msg, tabledata->table_data);
}

/**
 * @brief Encode a tabledata struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param tabledata C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_tabledata_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_tabledata_t* tabledata)
{
    return mavlink_msg_tabledata_pack_chan(system_id, component_id, chan, msg, tabledata->table_data);
}

/**
 * @brief Encode a tabledata struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param tabledata C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_tabledata_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_tabledata_t* tabledata)
{
    return mavlink_msg_tabledata_pack_status(system_id, component_id, _status, msg,  tabledata->table_data);
}

/**
 * @brief Send a tabledata message
 * @param chan MAVLink channel to send the message
 *
 * @param table_data  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_tabledata_send(mavlink_channel_t chan, const float *table_data)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TableData_LEN];

    _mav_put_float_array(buf, 0, table_data, 20);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TableData, buf, MAVLINK_MSG_ID_TableData_MIN_LEN, MAVLINK_MSG_ID_TableData_LEN, MAVLINK_MSG_ID_TableData_CRC);
#else
    mavlink_tabledata_t packet;

    mav_array_memcpy(packet.table_data, table_data, sizeof(float)*20);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TableData, (const char *)&packet, MAVLINK_MSG_ID_TableData_MIN_LEN, MAVLINK_MSG_ID_TableData_LEN, MAVLINK_MSG_ID_TableData_CRC);
#endif
}

/**
 * @brief Send a tabledata message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_tabledata_send_struct(mavlink_channel_t chan, const mavlink_tabledata_t* tabledata)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_tabledata_send(chan, tabledata->table_data);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TableData, (const char *)tabledata, MAVLINK_MSG_ID_TableData_MIN_LEN, MAVLINK_MSG_ID_TableData_LEN, MAVLINK_MSG_ID_TableData_CRC);
#endif
}

#if MAVLINK_MSG_ID_TableData_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_tabledata_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  const float *table_data)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;

    _mav_put_float_array(buf, 0, table_data, 20);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TableData, buf, MAVLINK_MSG_ID_TableData_MIN_LEN, MAVLINK_MSG_ID_TableData_LEN, MAVLINK_MSG_ID_TableData_CRC);
#else
    mavlink_tabledata_t *packet = (mavlink_tabledata_t *)msgbuf;

    mav_array_memcpy(packet->table_data, table_data, sizeof(float)*20);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TableData, (const char *)packet, MAVLINK_MSG_ID_TableData_MIN_LEN, MAVLINK_MSG_ID_TableData_LEN, MAVLINK_MSG_ID_TableData_CRC);
#endif
}
#endif

#endif

// MESSAGE TableData UNPACKING


/**
 * @brief Get field table_data from tabledata message
 *
 * @return  
 */
static inline uint16_t mavlink_msg_tabledata_get_table_data(const mavlink_message_t* msg, float *table_data)
{
    return _MAV_RETURN_float_array(msg, table_data, 20,  0);
}

/**
 * @brief Decode a tabledata message into a struct
 *
 * @param msg The message to decode
 * @param tabledata C-struct to decode the message contents into
 */
static inline void mavlink_msg_tabledata_decode(const mavlink_message_t* msg, mavlink_tabledata_t* tabledata)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_tabledata_get_table_data(msg, tabledata->table_data);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_TableData_LEN? msg->len : MAVLINK_MSG_ID_TableData_LEN;
        memset(tabledata, 0, MAVLINK_MSG_ID_TableData_LEN);
    memcpy(tabledata, _MAV_PAYLOAD(msg), len);
#endif
}
