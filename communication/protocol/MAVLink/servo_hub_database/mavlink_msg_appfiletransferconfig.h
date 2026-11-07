#pragma once
// MESSAGE AppFileTransferConfig PACKING

#define MAVLINK_MSG_ID_AppFileTransferConfig 30086


typedef struct __mavlink_appfiletransferconfig_t {
 uint32_t File_size; /*<  */
 uint32_t File_index_complete; /*<  */
 uint8_t File_type; /*<  */
 uint8_t File_direction; /*<  */
 int8_t File_status; /*<  */
} mavlink_appfiletransferconfig_t;

#define MAVLINK_MSG_ID_AppFileTransferConfig_LEN 11
#define MAVLINK_MSG_ID_AppFileTransferConfig_MIN_LEN 11
#define MAVLINK_MSG_ID_30086_LEN 11
#define MAVLINK_MSG_ID_30086_MIN_LEN 11

#define MAVLINK_MSG_ID_AppFileTransferConfig_CRC 77
#define MAVLINK_MSG_ID_30086_CRC 77



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_AppFileTransferConfig { \
    30086, \
    "AppFileTransferConfig", \
    5, \
    {  { "File_type", NULL, MAVLINK_TYPE_UINT8_T, 0, 8, offsetof(mavlink_appfiletransferconfig_t, File_type) }, \
         { "File_size", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_appfiletransferconfig_t, File_size) }, \
         { "File_direction", NULL, MAVLINK_TYPE_UINT8_T, 0, 9, offsetof(mavlink_appfiletransferconfig_t, File_direction) }, \
         { "File_index_complete", NULL, MAVLINK_TYPE_UINT32_T, 0, 4, offsetof(mavlink_appfiletransferconfig_t, File_index_complete) }, \
         { "File_status", NULL, MAVLINK_TYPE_INT8_T, 0, 10, offsetof(mavlink_appfiletransferconfig_t, File_status) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_AppFileTransferConfig { \
    "AppFileTransferConfig", \
    5, \
    {  { "File_type", NULL, MAVLINK_TYPE_UINT8_T, 0, 8, offsetof(mavlink_appfiletransferconfig_t, File_type) }, \
         { "File_size", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_appfiletransferconfig_t, File_size) }, \
         { "File_direction", NULL, MAVLINK_TYPE_UINT8_T, 0, 9, offsetof(mavlink_appfiletransferconfig_t, File_direction) }, \
         { "File_index_complete", NULL, MAVLINK_TYPE_UINT32_T, 0, 4, offsetof(mavlink_appfiletransferconfig_t, File_index_complete) }, \
         { "File_status", NULL, MAVLINK_TYPE_INT8_T, 0, 10, offsetof(mavlink_appfiletransferconfig_t, File_status) }, \
         } \
}
#endif

/**
 * @brief Pack a appfiletransferconfig message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param File_type  
 * @param File_size  
 * @param File_direction  
 * @param File_index_complete  
 * @param File_status  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_appfiletransferconfig_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t File_type, uint32_t File_size, uint8_t File_direction, uint32_t File_index_complete, int8_t File_status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_AppFileTransferConfig_LEN];
    _mav_put_uint32_t(buf, 0, File_size);
    _mav_put_uint32_t(buf, 4, File_index_complete);
    _mav_put_uint8_t(buf, 8, File_type);
    _mav_put_uint8_t(buf, 9, File_direction);
    _mav_put_int8_t(buf, 10, File_status);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_AppFileTransferConfig_LEN);
#else
    mavlink_appfiletransferconfig_t packet;
    packet.File_size = File_size;
    packet.File_index_complete = File_index_complete;
    packet.File_type = File_type;
    packet.File_direction = File_direction;
    packet.File_status = File_status;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_AppFileTransferConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_AppFileTransferConfig;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_AppFileTransferConfig_MIN_LEN, MAVLINK_MSG_ID_AppFileTransferConfig_LEN, MAVLINK_MSG_ID_AppFileTransferConfig_CRC);
}

/**
 * @brief Pack a appfiletransferconfig message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param File_type  
 * @param File_size  
 * @param File_direction  
 * @param File_index_complete  
 * @param File_status  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_appfiletransferconfig_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint8_t File_type, uint32_t File_size, uint8_t File_direction, uint32_t File_index_complete, int8_t File_status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_AppFileTransferConfig_LEN];
    _mav_put_uint32_t(buf, 0, File_size);
    _mav_put_uint32_t(buf, 4, File_index_complete);
    _mav_put_uint8_t(buf, 8, File_type);
    _mav_put_uint8_t(buf, 9, File_direction);
    _mav_put_int8_t(buf, 10, File_status);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_AppFileTransferConfig_LEN);
#else
    mavlink_appfiletransferconfig_t packet;
    packet.File_size = File_size;
    packet.File_index_complete = File_index_complete;
    packet.File_type = File_type;
    packet.File_direction = File_direction;
    packet.File_status = File_status;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_AppFileTransferConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_AppFileTransferConfig;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_AppFileTransferConfig_MIN_LEN, MAVLINK_MSG_ID_AppFileTransferConfig_LEN, MAVLINK_MSG_ID_AppFileTransferConfig_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_AppFileTransferConfig_MIN_LEN, MAVLINK_MSG_ID_AppFileTransferConfig_LEN);
#endif
}

/**
 * @brief Pack a appfiletransferconfig message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param File_type  
 * @param File_size  
 * @param File_direction  
 * @param File_index_complete  
 * @param File_status  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_appfiletransferconfig_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t File_type,uint32_t File_size,uint8_t File_direction,uint32_t File_index_complete,int8_t File_status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_AppFileTransferConfig_LEN];
    _mav_put_uint32_t(buf, 0, File_size);
    _mav_put_uint32_t(buf, 4, File_index_complete);
    _mav_put_uint8_t(buf, 8, File_type);
    _mav_put_uint8_t(buf, 9, File_direction);
    _mav_put_int8_t(buf, 10, File_status);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_AppFileTransferConfig_LEN);
#else
    mavlink_appfiletransferconfig_t packet;
    packet.File_size = File_size;
    packet.File_index_complete = File_index_complete;
    packet.File_type = File_type;
    packet.File_direction = File_direction;
    packet.File_status = File_status;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_AppFileTransferConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_AppFileTransferConfig;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_AppFileTransferConfig_MIN_LEN, MAVLINK_MSG_ID_AppFileTransferConfig_LEN, MAVLINK_MSG_ID_AppFileTransferConfig_CRC);
}

/**
 * @brief Encode a appfiletransferconfig struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param appfiletransferconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_appfiletransferconfig_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_appfiletransferconfig_t* appfiletransferconfig)
{
    return mavlink_msg_appfiletransferconfig_pack(system_id, component_id, msg, appfiletransferconfig->File_type, appfiletransferconfig->File_size, appfiletransferconfig->File_direction, appfiletransferconfig->File_index_complete, appfiletransferconfig->File_status);
}

/**
 * @brief Encode a appfiletransferconfig struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param appfiletransferconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_appfiletransferconfig_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_appfiletransferconfig_t* appfiletransferconfig)
{
    return mavlink_msg_appfiletransferconfig_pack_chan(system_id, component_id, chan, msg, appfiletransferconfig->File_type, appfiletransferconfig->File_size, appfiletransferconfig->File_direction, appfiletransferconfig->File_index_complete, appfiletransferconfig->File_status);
}

/**
 * @brief Encode a appfiletransferconfig struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param appfiletransferconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_appfiletransferconfig_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_appfiletransferconfig_t* appfiletransferconfig)
{
    return mavlink_msg_appfiletransferconfig_pack_status(system_id, component_id, _status, msg,  appfiletransferconfig->File_type, appfiletransferconfig->File_size, appfiletransferconfig->File_direction, appfiletransferconfig->File_index_complete, appfiletransferconfig->File_status);
}

/**
 * @brief Send a appfiletransferconfig message
 * @param chan MAVLink channel to send the message
 *
 * @param File_type  
 * @param File_size  
 * @param File_direction  
 * @param File_index_complete  
 * @param File_status  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_appfiletransferconfig_send(mavlink_channel_t chan, uint8_t File_type, uint32_t File_size, uint8_t File_direction, uint32_t File_index_complete, int8_t File_status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_AppFileTransferConfig_LEN];
    _mav_put_uint32_t(buf, 0, File_size);
    _mav_put_uint32_t(buf, 4, File_index_complete);
    _mav_put_uint8_t(buf, 8, File_type);
    _mav_put_uint8_t(buf, 9, File_direction);
    _mav_put_int8_t(buf, 10, File_status);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppFileTransferConfig, buf, MAVLINK_MSG_ID_AppFileTransferConfig_MIN_LEN, MAVLINK_MSG_ID_AppFileTransferConfig_LEN, MAVLINK_MSG_ID_AppFileTransferConfig_CRC);
#else
    mavlink_appfiletransferconfig_t packet;
    packet.File_size = File_size;
    packet.File_index_complete = File_index_complete;
    packet.File_type = File_type;
    packet.File_direction = File_direction;
    packet.File_status = File_status;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppFileTransferConfig, (const char *)&packet, MAVLINK_MSG_ID_AppFileTransferConfig_MIN_LEN, MAVLINK_MSG_ID_AppFileTransferConfig_LEN, MAVLINK_MSG_ID_AppFileTransferConfig_CRC);
#endif
}

/**
 * @brief Send a appfiletransferconfig message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_appfiletransferconfig_send_struct(mavlink_channel_t chan, const mavlink_appfiletransferconfig_t* appfiletransferconfig)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_appfiletransferconfig_send(chan, appfiletransferconfig->File_type, appfiletransferconfig->File_size, appfiletransferconfig->File_direction, appfiletransferconfig->File_index_complete, appfiletransferconfig->File_status);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppFileTransferConfig, (const char *)appfiletransferconfig, MAVLINK_MSG_ID_AppFileTransferConfig_MIN_LEN, MAVLINK_MSG_ID_AppFileTransferConfig_LEN, MAVLINK_MSG_ID_AppFileTransferConfig_CRC);
#endif
}

#if MAVLINK_MSG_ID_AppFileTransferConfig_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_appfiletransferconfig_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t File_type, uint32_t File_size, uint8_t File_direction, uint32_t File_index_complete, int8_t File_status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint32_t(buf, 0, File_size);
    _mav_put_uint32_t(buf, 4, File_index_complete);
    _mav_put_uint8_t(buf, 8, File_type);
    _mav_put_uint8_t(buf, 9, File_direction);
    _mav_put_int8_t(buf, 10, File_status);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppFileTransferConfig, buf, MAVLINK_MSG_ID_AppFileTransferConfig_MIN_LEN, MAVLINK_MSG_ID_AppFileTransferConfig_LEN, MAVLINK_MSG_ID_AppFileTransferConfig_CRC);
#else
    mavlink_appfiletransferconfig_t *packet = (mavlink_appfiletransferconfig_t *)msgbuf;
    packet->File_size = File_size;
    packet->File_index_complete = File_index_complete;
    packet->File_type = File_type;
    packet->File_direction = File_direction;
    packet->File_status = File_status;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppFileTransferConfig, (const char *)packet, MAVLINK_MSG_ID_AppFileTransferConfig_MIN_LEN, MAVLINK_MSG_ID_AppFileTransferConfig_LEN, MAVLINK_MSG_ID_AppFileTransferConfig_CRC);
#endif
}
#endif

#endif

// MESSAGE AppFileTransferConfig UNPACKING


/**
 * @brief Get field File_type from appfiletransferconfig message
 *
 * @return  
 */
static inline uint8_t mavlink_msg_appfiletransferconfig_get_File_type(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  8);
}

/**
 * @brief Get field File_size from appfiletransferconfig message
 *
 * @return  
 */
static inline uint32_t mavlink_msg_appfiletransferconfig_get_File_size(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Get field File_direction from appfiletransferconfig message
 *
 * @return  
 */
static inline uint8_t mavlink_msg_appfiletransferconfig_get_File_direction(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  9);
}

/**
 * @brief Get field File_index_complete from appfiletransferconfig message
 *
 * @return  
 */
static inline uint32_t mavlink_msg_appfiletransferconfig_get_File_index_complete(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  4);
}

/**
 * @brief Get field File_status from appfiletransferconfig message
 *
 * @return  
 */
static inline int8_t mavlink_msg_appfiletransferconfig_get_File_status(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int8_t(msg,  10);
}

/**
 * @brief Decode a appfiletransferconfig message into a struct
 *
 * @param msg The message to decode
 * @param appfiletransferconfig C-struct to decode the message contents into
 */
static inline void mavlink_msg_appfiletransferconfig_decode(const mavlink_message_t* msg, mavlink_appfiletransferconfig_t* appfiletransferconfig)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    appfiletransferconfig->File_size = mavlink_msg_appfiletransferconfig_get_File_size(msg);
    appfiletransferconfig->File_index_complete = mavlink_msg_appfiletransferconfig_get_File_index_complete(msg);
    appfiletransferconfig->File_type = mavlink_msg_appfiletransferconfig_get_File_type(msg);
    appfiletransferconfig->File_direction = mavlink_msg_appfiletransferconfig_get_File_direction(msg);
    appfiletransferconfig->File_status = mavlink_msg_appfiletransferconfig_get_File_status(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_AppFileTransferConfig_LEN? msg->len : MAVLINK_MSG_ID_AppFileTransferConfig_LEN;
        memset(appfiletransferconfig, 0, MAVLINK_MSG_ID_AppFileTransferConfig_LEN);
    memcpy(appfiletransferconfig, _MAV_PAYLOAD(msg), len);
#endif
}
