#pragma once
// MESSAGE AppFileTransferStream PACKING

#define MAVLINK_MSG_ID_AppFileTransferStream 30088


typedef struct __mavlink_appfiletransferstream_t {
 uint16_t Index; /*<  */
 uint8_t Length; /*<  */
 uint8_t File_buffer[252]; /*<  */
} mavlink_appfiletransferstream_t;

#define MAVLINK_MSG_ID_AppFileTransferStream_LEN 255
#define MAVLINK_MSG_ID_AppFileTransferStream_MIN_LEN 255
#define MAVLINK_MSG_ID_30088_LEN 255
#define MAVLINK_MSG_ID_30088_MIN_LEN 255

#define MAVLINK_MSG_ID_AppFileTransferStream_CRC 118
#define MAVLINK_MSG_ID_30088_CRC 118

#define MAVLINK_MSG_AppFileTransferStream_FIELD_FILE_BUFFER_LEN 252

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_AppFileTransferStream { \
    30088, \
    "AppFileTransferStream", \
    3, \
    {  { "Index", NULL, MAVLINK_TYPE_UINT16_T, 0, 0, offsetof(mavlink_appfiletransferstream_t, Index) }, \
         { "Length", NULL, MAVLINK_TYPE_UINT8_T, 0, 2, offsetof(mavlink_appfiletransferstream_t, Length) }, \
         { "File_buffer", NULL, MAVLINK_TYPE_UINT8_T, 252, 3, offsetof(mavlink_appfiletransferstream_t, File_buffer) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_AppFileTransferStream { \
    "AppFileTransferStream", \
    3, \
    {  { "Index", NULL, MAVLINK_TYPE_UINT16_T, 0, 0, offsetof(mavlink_appfiletransferstream_t, Index) }, \
         { "Length", NULL, MAVLINK_TYPE_UINT8_T, 0, 2, offsetof(mavlink_appfiletransferstream_t, Length) }, \
         { "File_buffer", NULL, MAVLINK_TYPE_UINT8_T, 252, 3, offsetof(mavlink_appfiletransferstream_t, File_buffer) }, \
         } \
}
#endif

/**
 * @brief Pack a appfiletransferstream message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param Index  
 * @param Length  
 * @param File_buffer  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_appfiletransferstream_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint16_t Index, uint8_t Length, const uint8_t *File_buffer)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_AppFileTransferStream_LEN];
    _mav_put_uint16_t(buf, 0, Index);
    _mav_put_uint8_t(buf, 2, Length);
    _mav_put_uint8_t_array(buf, 3, File_buffer, 252);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_AppFileTransferStream_LEN);
#else
    mavlink_appfiletransferstream_t packet;
    packet.Index = Index;
    packet.Length = Length;
    mav_array_memcpy(packet.File_buffer, File_buffer, sizeof(uint8_t)*252);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_AppFileTransferStream_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_AppFileTransferStream;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_AppFileTransferStream_MIN_LEN, MAVLINK_MSG_ID_AppFileTransferStream_LEN, MAVLINK_MSG_ID_AppFileTransferStream_CRC);
}

/**
 * @brief Pack a appfiletransferstream message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param Index  
 * @param Length  
 * @param File_buffer  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_appfiletransferstream_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint16_t Index, uint8_t Length, const uint8_t *File_buffer)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_AppFileTransferStream_LEN];
    _mav_put_uint16_t(buf, 0, Index);
    _mav_put_uint8_t(buf, 2, Length);
    _mav_put_uint8_t_array(buf, 3, File_buffer, 252);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_AppFileTransferStream_LEN);
#else
    mavlink_appfiletransferstream_t packet;
    packet.Index = Index;
    packet.Length = Length;
    mav_array_memcpy(packet.File_buffer, File_buffer, sizeof(uint8_t)*252);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_AppFileTransferStream_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_AppFileTransferStream;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_AppFileTransferStream_MIN_LEN, MAVLINK_MSG_ID_AppFileTransferStream_LEN, MAVLINK_MSG_ID_AppFileTransferStream_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_AppFileTransferStream_MIN_LEN, MAVLINK_MSG_ID_AppFileTransferStream_LEN);
#endif
}

/**
 * @brief Pack a appfiletransferstream message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param Index  
 * @param Length  
 * @param File_buffer  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_appfiletransferstream_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint16_t Index,uint8_t Length,const uint8_t *File_buffer)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_AppFileTransferStream_LEN];
    _mav_put_uint16_t(buf, 0, Index);
    _mav_put_uint8_t(buf, 2, Length);
    _mav_put_uint8_t_array(buf, 3, File_buffer, 252);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_AppFileTransferStream_LEN);
#else
    mavlink_appfiletransferstream_t packet;
    packet.Index = Index;
    packet.Length = Length;
    mav_array_memcpy(packet.File_buffer, File_buffer, sizeof(uint8_t)*252);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_AppFileTransferStream_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_AppFileTransferStream;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_AppFileTransferStream_MIN_LEN, MAVLINK_MSG_ID_AppFileTransferStream_LEN, MAVLINK_MSG_ID_AppFileTransferStream_CRC);
}

/**
 * @brief Encode a appfiletransferstream struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param appfiletransferstream C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_appfiletransferstream_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_appfiletransferstream_t* appfiletransferstream)
{
    return mavlink_msg_appfiletransferstream_pack(system_id, component_id, msg, appfiletransferstream->Index, appfiletransferstream->Length, appfiletransferstream->File_buffer);
}

/**
 * @brief Encode a appfiletransferstream struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param appfiletransferstream C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_appfiletransferstream_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_appfiletransferstream_t* appfiletransferstream)
{
    return mavlink_msg_appfiletransferstream_pack_chan(system_id, component_id, chan, msg, appfiletransferstream->Index, appfiletransferstream->Length, appfiletransferstream->File_buffer);
}

/**
 * @brief Encode a appfiletransferstream struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param appfiletransferstream C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_appfiletransferstream_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_appfiletransferstream_t* appfiletransferstream)
{
    return mavlink_msg_appfiletransferstream_pack_status(system_id, component_id, _status, msg,  appfiletransferstream->Index, appfiletransferstream->Length, appfiletransferstream->File_buffer);
}

/**
 * @brief Send a appfiletransferstream message
 * @param chan MAVLink channel to send the message
 *
 * @param Index  
 * @param Length  
 * @param File_buffer  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_appfiletransferstream_send(mavlink_channel_t chan, uint16_t Index, uint8_t Length, const uint8_t *File_buffer)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_AppFileTransferStream_LEN];
    _mav_put_uint16_t(buf, 0, Index);
    _mav_put_uint8_t(buf, 2, Length);
    _mav_put_uint8_t_array(buf, 3, File_buffer, 252);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppFileTransferStream, buf, MAVLINK_MSG_ID_AppFileTransferStream_MIN_LEN, MAVLINK_MSG_ID_AppFileTransferStream_LEN, MAVLINK_MSG_ID_AppFileTransferStream_CRC);
#else
    mavlink_appfiletransferstream_t packet;
    packet.Index = Index;
    packet.Length = Length;
    mav_array_memcpy(packet.File_buffer, File_buffer, sizeof(uint8_t)*252);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppFileTransferStream, (const char *)&packet, MAVLINK_MSG_ID_AppFileTransferStream_MIN_LEN, MAVLINK_MSG_ID_AppFileTransferStream_LEN, MAVLINK_MSG_ID_AppFileTransferStream_CRC);
#endif
}

/**
 * @brief Send a appfiletransferstream message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_appfiletransferstream_send_struct(mavlink_channel_t chan, const mavlink_appfiletransferstream_t* appfiletransferstream)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_appfiletransferstream_send(chan, appfiletransferstream->Index, appfiletransferstream->Length, appfiletransferstream->File_buffer);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppFileTransferStream, (const char *)appfiletransferstream, MAVLINK_MSG_ID_AppFileTransferStream_MIN_LEN, MAVLINK_MSG_ID_AppFileTransferStream_LEN, MAVLINK_MSG_ID_AppFileTransferStream_CRC);
#endif
}

#if MAVLINK_MSG_ID_AppFileTransferStream_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_appfiletransferstream_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint16_t Index, uint8_t Length, const uint8_t *File_buffer)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint16_t(buf, 0, Index);
    _mav_put_uint8_t(buf, 2, Length);
    _mav_put_uint8_t_array(buf, 3, File_buffer, 252);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppFileTransferStream, buf, MAVLINK_MSG_ID_AppFileTransferStream_MIN_LEN, MAVLINK_MSG_ID_AppFileTransferStream_LEN, MAVLINK_MSG_ID_AppFileTransferStream_CRC);
#else
    mavlink_appfiletransferstream_t *packet = (mavlink_appfiletransferstream_t *)msgbuf;
    packet->Index = Index;
    packet->Length = Length;
    mav_array_memcpy(packet->File_buffer, File_buffer, sizeof(uint8_t)*252);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppFileTransferStream, (const char *)packet, MAVLINK_MSG_ID_AppFileTransferStream_MIN_LEN, MAVLINK_MSG_ID_AppFileTransferStream_LEN, MAVLINK_MSG_ID_AppFileTransferStream_CRC);
#endif
}
#endif

#endif

// MESSAGE AppFileTransferStream UNPACKING


/**
 * @brief Get field Index from appfiletransferstream message
 *
 * @return  
 */
static inline uint16_t mavlink_msg_appfiletransferstream_get_Index(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  0);
}

/**
 * @brief Get field Length from appfiletransferstream message
 *
 * @return  
 */
static inline uint8_t mavlink_msg_appfiletransferstream_get_Length(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  2);
}

/**
 * @brief Get field File_buffer from appfiletransferstream message
 *
 * @return  
 */
static inline uint16_t mavlink_msg_appfiletransferstream_get_File_buffer(const mavlink_message_t* msg, uint8_t *File_buffer)
{
    return _MAV_RETURN_uint8_t_array(msg, File_buffer, 252,  3);
}

/**
 * @brief Decode a appfiletransferstream message into a struct
 *
 * @param msg The message to decode
 * @param appfiletransferstream C-struct to decode the message contents into
 */
static inline void mavlink_msg_appfiletransferstream_decode(const mavlink_message_t* msg, mavlink_appfiletransferstream_t* appfiletransferstream)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    appfiletransferstream->Index = mavlink_msg_appfiletransferstream_get_Index(msg);
    appfiletransferstream->Length = mavlink_msg_appfiletransferstream_get_Length(msg);
    mavlink_msg_appfiletransferstream_get_File_buffer(msg, appfiletransferstream->File_buffer);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_AppFileTransferStream_LEN? msg->len : MAVLINK_MSG_ID_AppFileTransferStream_LEN;
        memset(appfiletransferstream, 0, MAVLINK_MSG_ID_AppFileTransferStream_LEN);
    memcpy(appfiletransferstream, _MAV_PAYLOAD(msg), len);
#endif
}
