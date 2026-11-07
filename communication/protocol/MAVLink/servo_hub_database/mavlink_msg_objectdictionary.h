#pragma once
// MESSAGE ObjectDictionary PACKING

#define MAVLINK_MSG_ID_ObjectDictionary 30049


typedef struct __mavlink_objectdictionary_t {
 uint32_t data; /*<  */
 uint16_t index; /*<  */
 uint8_t sub_index; /*<  */
 uint8_t rw; /*<  */
} mavlink_objectdictionary_t;

#define MAVLINK_MSG_ID_ObjectDictionary_LEN 8
#define MAVLINK_MSG_ID_ObjectDictionary_MIN_LEN 8
#define MAVLINK_MSG_ID_30049_LEN 8
#define MAVLINK_MSG_ID_30049_MIN_LEN 8

#define MAVLINK_MSG_ID_ObjectDictionary_CRC 34
#define MAVLINK_MSG_ID_30049_CRC 34



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_ObjectDictionary { \
    30049, \
    "ObjectDictionary", \
    4, \
    {  { "index", NULL, MAVLINK_TYPE_UINT16_T, 0, 4, offsetof(mavlink_objectdictionary_t, index) }, \
         { "sub_index", NULL, MAVLINK_TYPE_UINT8_T, 0, 6, offsetof(mavlink_objectdictionary_t, sub_index) }, \
         { "data", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_objectdictionary_t, data) }, \
         { "rw", NULL, MAVLINK_TYPE_UINT8_T, 0, 7, offsetof(mavlink_objectdictionary_t, rw) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_ObjectDictionary { \
    "ObjectDictionary", \
    4, \
    {  { "index", NULL, MAVLINK_TYPE_UINT16_T, 0, 4, offsetof(mavlink_objectdictionary_t, index) }, \
         { "sub_index", NULL, MAVLINK_TYPE_UINT8_T, 0, 6, offsetof(mavlink_objectdictionary_t, sub_index) }, \
         { "data", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_objectdictionary_t, data) }, \
         { "rw", NULL, MAVLINK_TYPE_UINT8_T, 0, 7, offsetof(mavlink_objectdictionary_t, rw) }, \
         } \
}
#endif

/**
 * @brief Pack a objectdictionary message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param index  
 * @param sub_index  
 * @param data  
 * @param rw  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_objectdictionary_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint16_t index, uint8_t sub_index, uint32_t data, uint8_t rw)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ObjectDictionary_LEN];
    _mav_put_uint32_t(buf, 0, data);
    _mav_put_uint16_t(buf, 4, index);
    _mav_put_uint8_t(buf, 6, sub_index);
    _mav_put_uint8_t(buf, 7, rw);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ObjectDictionary_LEN);
#else
    mavlink_objectdictionary_t packet;
    packet.data = data;
    packet.index = index;
    packet.sub_index = sub_index;
    packet.rw = rw;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ObjectDictionary_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ObjectDictionary;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_ObjectDictionary_MIN_LEN, MAVLINK_MSG_ID_ObjectDictionary_LEN, MAVLINK_MSG_ID_ObjectDictionary_CRC);
}

/**
 * @brief Pack a objectdictionary message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param index  
 * @param sub_index  
 * @param data  
 * @param rw  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_objectdictionary_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint16_t index, uint8_t sub_index, uint32_t data, uint8_t rw)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ObjectDictionary_LEN];
    _mav_put_uint32_t(buf, 0, data);
    _mav_put_uint16_t(buf, 4, index);
    _mav_put_uint8_t(buf, 6, sub_index);
    _mav_put_uint8_t(buf, 7, rw);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ObjectDictionary_LEN);
#else
    mavlink_objectdictionary_t packet;
    packet.data = data;
    packet.index = index;
    packet.sub_index = sub_index;
    packet.rw = rw;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ObjectDictionary_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ObjectDictionary;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_ObjectDictionary_MIN_LEN, MAVLINK_MSG_ID_ObjectDictionary_LEN, MAVLINK_MSG_ID_ObjectDictionary_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_ObjectDictionary_MIN_LEN, MAVLINK_MSG_ID_ObjectDictionary_LEN);
#endif
}

/**
 * @brief Pack a objectdictionary message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param index  
 * @param sub_index  
 * @param data  
 * @param rw  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_objectdictionary_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint16_t index,uint8_t sub_index,uint32_t data,uint8_t rw)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ObjectDictionary_LEN];
    _mav_put_uint32_t(buf, 0, data);
    _mav_put_uint16_t(buf, 4, index);
    _mav_put_uint8_t(buf, 6, sub_index);
    _mav_put_uint8_t(buf, 7, rw);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ObjectDictionary_LEN);
#else
    mavlink_objectdictionary_t packet;
    packet.data = data;
    packet.index = index;
    packet.sub_index = sub_index;
    packet.rw = rw;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ObjectDictionary_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ObjectDictionary;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_ObjectDictionary_MIN_LEN, MAVLINK_MSG_ID_ObjectDictionary_LEN, MAVLINK_MSG_ID_ObjectDictionary_CRC);
}

/**
 * @brief Encode a objectdictionary struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param objectdictionary C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_objectdictionary_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_objectdictionary_t* objectdictionary)
{
    return mavlink_msg_objectdictionary_pack(system_id, component_id, msg, objectdictionary->index, objectdictionary->sub_index, objectdictionary->data, objectdictionary->rw);
}

/**
 * @brief Encode a objectdictionary struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param objectdictionary C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_objectdictionary_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_objectdictionary_t* objectdictionary)
{
    return mavlink_msg_objectdictionary_pack_chan(system_id, component_id, chan, msg, objectdictionary->index, objectdictionary->sub_index, objectdictionary->data, objectdictionary->rw);
}

/**
 * @brief Encode a objectdictionary struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param objectdictionary C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_objectdictionary_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_objectdictionary_t* objectdictionary)
{
    return mavlink_msg_objectdictionary_pack_status(system_id, component_id, _status, msg,  objectdictionary->index, objectdictionary->sub_index, objectdictionary->data, objectdictionary->rw);
}

/**
 * @brief Send a objectdictionary message
 * @param chan MAVLink channel to send the message
 *
 * @param index  
 * @param sub_index  
 * @param data  
 * @param rw  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_objectdictionary_send(mavlink_channel_t chan, uint16_t index, uint8_t sub_index, uint32_t data, uint8_t rw)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ObjectDictionary_LEN];
    _mav_put_uint32_t(buf, 0, data);
    _mav_put_uint16_t(buf, 4, index);
    _mav_put_uint8_t(buf, 6, sub_index);
    _mav_put_uint8_t(buf, 7, rw);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ObjectDictionary, buf, MAVLINK_MSG_ID_ObjectDictionary_MIN_LEN, MAVLINK_MSG_ID_ObjectDictionary_LEN, MAVLINK_MSG_ID_ObjectDictionary_CRC);
#else
    mavlink_objectdictionary_t packet;
    packet.data = data;
    packet.index = index;
    packet.sub_index = sub_index;
    packet.rw = rw;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ObjectDictionary, (const char *)&packet, MAVLINK_MSG_ID_ObjectDictionary_MIN_LEN, MAVLINK_MSG_ID_ObjectDictionary_LEN, MAVLINK_MSG_ID_ObjectDictionary_CRC);
#endif
}

/**
 * @brief Send a objectdictionary message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_objectdictionary_send_struct(mavlink_channel_t chan, const mavlink_objectdictionary_t* objectdictionary)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_objectdictionary_send(chan, objectdictionary->index, objectdictionary->sub_index, objectdictionary->data, objectdictionary->rw);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ObjectDictionary, (const char *)objectdictionary, MAVLINK_MSG_ID_ObjectDictionary_MIN_LEN, MAVLINK_MSG_ID_ObjectDictionary_LEN, MAVLINK_MSG_ID_ObjectDictionary_CRC);
#endif
}

#if MAVLINK_MSG_ID_ObjectDictionary_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_objectdictionary_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint16_t index, uint8_t sub_index, uint32_t data, uint8_t rw)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint32_t(buf, 0, data);
    _mav_put_uint16_t(buf, 4, index);
    _mav_put_uint8_t(buf, 6, sub_index);
    _mav_put_uint8_t(buf, 7, rw);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ObjectDictionary, buf, MAVLINK_MSG_ID_ObjectDictionary_MIN_LEN, MAVLINK_MSG_ID_ObjectDictionary_LEN, MAVLINK_MSG_ID_ObjectDictionary_CRC);
#else
    mavlink_objectdictionary_t *packet = (mavlink_objectdictionary_t *)msgbuf;
    packet->data = data;
    packet->index = index;
    packet->sub_index = sub_index;
    packet->rw = rw;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ObjectDictionary, (const char *)packet, MAVLINK_MSG_ID_ObjectDictionary_MIN_LEN, MAVLINK_MSG_ID_ObjectDictionary_LEN, MAVLINK_MSG_ID_ObjectDictionary_CRC);
#endif
}
#endif

#endif

// MESSAGE ObjectDictionary UNPACKING


/**
 * @brief Get field index from objectdictionary message
 *
 * @return  
 */
static inline uint16_t mavlink_msg_objectdictionary_get_index(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  4);
}

/**
 * @brief Get field sub_index from objectdictionary message
 *
 * @return  
 */
static inline uint8_t mavlink_msg_objectdictionary_get_sub_index(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  6);
}

/**
 * @brief Get field data from objectdictionary message
 *
 * @return  
 */
static inline uint32_t mavlink_msg_objectdictionary_get_data(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Get field rw from objectdictionary message
 *
 * @return  
 */
static inline uint8_t mavlink_msg_objectdictionary_get_rw(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  7);
}

/**
 * @brief Decode a objectdictionary message into a struct
 *
 * @param msg The message to decode
 * @param objectdictionary C-struct to decode the message contents into
 */
static inline void mavlink_msg_objectdictionary_decode(const mavlink_message_t* msg, mavlink_objectdictionary_t* objectdictionary)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    objectdictionary->data = mavlink_msg_objectdictionary_get_data(msg);
    objectdictionary->index = mavlink_msg_objectdictionary_get_index(msg);
    objectdictionary->sub_index = mavlink_msg_objectdictionary_get_sub_index(msg);
    objectdictionary->rw = mavlink_msg_objectdictionary_get_rw(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_ObjectDictionary_LEN? msg->len : MAVLINK_MSG_ID_ObjectDictionary_LEN;
        memset(objectdictionary, 0, MAVLINK_MSG_ID_ObjectDictionary_LEN);
    memcpy(objectdictionary, _MAV_PAYLOAD(msg), len);
#endif
}
