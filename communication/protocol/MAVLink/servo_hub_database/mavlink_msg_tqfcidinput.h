#pragma once
// MESSAGE TqFcIdInput PACKING

#define MAVLINK_MSG_ID_TqFcIdInput 30046


typedef struct __mavlink_tqfcidinput_t {
 int64_t pos_init_p; /*<  */
 float iq_com_A; /*<  */
 uint32_t pos_abs_p; /*<  */
 uint8_t start; /*<  */
} mavlink_tqfcidinput_t;

#define MAVLINK_MSG_ID_TqFcIdInput_LEN 17
#define MAVLINK_MSG_ID_TqFcIdInput_MIN_LEN 17
#define MAVLINK_MSG_ID_30046_LEN 17
#define MAVLINK_MSG_ID_30046_MIN_LEN 17

#define MAVLINK_MSG_ID_TqFcIdInput_CRC 37
#define MAVLINK_MSG_ID_30046_CRC 37



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_TqFcIdInput { \
    30046, \
    "TqFcIdInput", \
    4, \
    {  { "iq_com_A", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_tqfcidinput_t, iq_com_A) }, \
         { "pos_abs_p", NULL, MAVLINK_TYPE_UINT32_T, 0, 12, offsetof(mavlink_tqfcidinput_t, pos_abs_p) }, \
         { "pos_init_p", NULL, MAVLINK_TYPE_INT64_T, 0, 0, offsetof(mavlink_tqfcidinput_t, pos_init_p) }, \
         { "start", NULL, MAVLINK_TYPE_UINT8_T, 0, 16, offsetof(mavlink_tqfcidinput_t, start) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_TqFcIdInput { \
    "TqFcIdInput", \
    4, \
    {  { "iq_com_A", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_tqfcidinput_t, iq_com_A) }, \
         { "pos_abs_p", NULL, MAVLINK_TYPE_UINT32_T, 0, 12, offsetof(mavlink_tqfcidinput_t, pos_abs_p) }, \
         { "pos_init_p", NULL, MAVLINK_TYPE_INT64_T, 0, 0, offsetof(mavlink_tqfcidinput_t, pos_init_p) }, \
         { "start", NULL, MAVLINK_TYPE_UINT8_T, 0, 16, offsetof(mavlink_tqfcidinput_t, start) }, \
         } \
}
#endif

/**
 * @brief Pack a tqfcidinput message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param iq_com_A  
 * @param pos_abs_p  
 * @param pos_init_p  
 * @param start  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_tqfcidinput_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               float iq_com_A, uint32_t pos_abs_p, int64_t pos_init_p, uint8_t start)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TqFcIdInput_LEN];
    _mav_put_int64_t(buf, 0, pos_init_p);
    _mav_put_float(buf, 8, iq_com_A);
    _mav_put_uint32_t(buf, 12, pos_abs_p);
    _mav_put_uint8_t(buf, 16, start);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_TqFcIdInput_LEN);
#else
    mavlink_tqfcidinput_t packet;
    packet.pos_init_p = pos_init_p;
    packet.iq_com_A = iq_com_A;
    packet.pos_abs_p = pos_abs_p;
    packet.start = start;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_TqFcIdInput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_TqFcIdInput;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_TqFcIdInput_MIN_LEN, MAVLINK_MSG_ID_TqFcIdInput_LEN, MAVLINK_MSG_ID_TqFcIdInput_CRC);
}

/**
 * @brief Pack a tqfcidinput message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param iq_com_A  
 * @param pos_abs_p  
 * @param pos_init_p  
 * @param start  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_tqfcidinput_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               float iq_com_A, uint32_t pos_abs_p, int64_t pos_init_p, uint8_t start)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TqFcIdInput_LEN];
    _mav_put_int64_t(buf, 0, pos_init_p);
    _mav_put_float(buf, 8, iq_com_A);
    _mav_put_uint32_t(buf, 12, pos_abs_p);
    _mav_put_uint8_t(buf, 16, start);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_TqFcIdInput_LEN);
#else
    mavlink_tqfcidinput_t packet;
    packet.pos_init_p = pos_init_p;
    packet.iq_com_A = iq_com_A;
    packet.pos_abs_p = pos_abs_p;
    packet.start = start;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_TqFcIdInput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_TqFcIdInput;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_TqFcIdInput_MIN_LEN, MAVLINK_MSG_ID_TqFcIdInput_LEN, MAVLINK_MSG_ID_TqFcIdInput_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_TqFcIdInput_MIN_LEN, MAVLINK_MSG_ID_TqFcIdInput_LEN);
#endif
}

/**
 * @brief Pack a tqfcidinput message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param iq_com_A  
 * @param pos_abs_p  
 * @param pos_init_p  
 * @param start  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_tqfcidinput_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   float iq_com_A,uint32_t pos_abs_p,int64_t pos_init_p,uint8_t start)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TqFcIdInput_LEN];
    _mav_put_int64_t(buf, 0, pos_init_p);
    _mav_put_float(buf, 8, iq_com_A);
    _mav_put_uint32_t(buf, 12, pos_abs_p);
    _mav_put_uint8_t(buf, 16, start);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_TqFcIdInput_LEN);
#else
    mavlink_tqfcidinput_t packet;
    packet.pos_init_p = pos_init_p;
    packet.iq_com_A = iq_com_A;
    packet.pos_abs_p = pos_abs_p;
    packet.start = start;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_TqFcIdInput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_TqFcIdInput;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_TqFcIdInput_MIN_LEN, MAVLINK_MSG_ID_TqFcIdInput_LEN, MAVLINK_MSG_ID_TqFcIdInput_CRC);
}

/**
 * @brief Encode a tqfcidinput struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param tqfcidinput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_tqfcidinput_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_tqfcidinput_t* tqfcidinput)
{
    return mavlink_msg_tqfcidinput_pack(system_id, component_id, msg, tqfcidinput->iq_com_A, tqfcidinput->pos_abs_p, tqfcidinput->pos_init_p, tqfcidinput->start);
}

/**
 * @brief Encode a tqfcidinput struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param tqfcidinput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_tqfcidinput_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_tqfcidinput_t* tqfcidinput)
{
    return mavlink_msg_tqfcidinput_pack_chan(system_id, component_id, chan, msg, tqfcidinput->iq_com_A, tqfcidinput->pos_abs_p, tqfcidinput->pos_init_p, tqfcidinput->start);
}

/**
 * @brief Encode a tqfcidinput struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param tqfcidinput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_tqfcidinput_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_tqfcidinput_t* tqfcidinput)
{
    return mavlink_msg_tqfcidinput_pack_status(system_id, component_id, _status, msg,  tqfcidinput->iq_com_A, tqfcidinput->pos_abs_p, tqfcidinput->pos_init_p, tqfcidinput->start);
}

/**
 * @brief Send a tqfcidinput message
 * @param chan MAVLink channel to send the message
 *
 * @param iq_com_A  
 * @param pos_abs_p  
 * @param pos_init_p  
 * @param start  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_tqfcidinput_send(mavlink_channel_t chan, float iq_com_A, uint32_t pos_abs_p, int64_t pos_init_p, uint8_t start)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TqFcIdInput_LEN];
    _mav_put_int64_t(buf, 0, pos_init_p);
    _mav_put_float(buf, 8, iq_com_A);
    _mav_put_uint32_t(buf, 12, pos_abs_p);
    _mav_put_uint8_t(buf, 16, start);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TqFcIdInput, buf, MAVLINK_MSG_ID_TqFcIdInput_MIN_LEN, MAVLINK_MSG_ID_TqFcIdInput_LEN, MAVLINK_MSG_ID_TqFcIdInput_CRC);
#else
    mavlink_tqfcidinput_t packet;
    packet.pos_init_p = pos_init_p;
    packet.iq_com_A = iq_com_A;
    packet.pos_abs_p = pos_abs_p;
    packet.start = start;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TqFcIdInput, (const char *)&packet, MAVLINK_MSG_ID_TqFcIdInput_MIN_LEN, MAVLINK_MSG_ID_TqFcIdInput_LEN, MAVLINK_MSG_ID_TqFcIdInput_CRC);
#endif
}

/**
 * @brief Send a tqfcidinput message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_tqfcidinput_send_struct(mavlink_channel_t chan, const mavlink_tqfcidinput_t* tqfcidinput)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_tqfcidinput_send(chan, tqfcidinput->iq_com_A, tqfcidinput->pos_abs_p, tqfcidinput->pos_init_p, tqfcidinput->start);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TqFcIdInput, (const char *)tqfcidinput, MAVLINK_MSG_ID_TqFcIdInput_MIN_LEN, MAVLINK_MSG_ID_TqFcIdInput_LEN, MAVLINK_MSG_ID_TqFcIdInput_CRC);
#endif
}

#if MAVLINK_MSG_ID_TqFcIdInput_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_tqfcidinput_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float iq_com_A, uint32_t pos_abs_p, int64_t pos_init_p, uint8_t start)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_int64_t(buf, 0, pos_init_p);
    _mav_put_float(buf, 8, iq_com_A);
    _mav_put_uint32_t(buf, 12, pos_abs_p);
    _mav_put_uint8_t(buf, 16, start);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TqFcIdInput, buf, MAVLINK_MSG_ID_TqFcIdInput_MIN_LEN, MAVLINK_MSG_ID_TqFcIdInput_LEN, MAVLINK_MSG_ID_TqFcIdInput_CRC);
#else
    mavlink_tqfcidinput_t *packet = (mavlink_tqfcidinput_t *)msgbuf;
    packet->pos_init_p = pos_init_p;
    packet->iq_com_A = iq_com_A;
    packet->pos_abs_p = pos_abs_p;
    packet->start = start;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TqFcIdInput, (const char *)packet, MAVLINK_MSG_ID_TqFcIdInput_MIN_LEN, MAVLINK_MSG_ID_TqFcIdInput_LEN, MAVLINK_MSG_ID_TqFcIdInput_CRC);
#endif
}
#endif

#endif

// MESSAGE TqFcIdInput UNPACKING


/**
 * @brief Get field iq_com_A from tqfcidinput message
 *
 * @return  
 */
static inline float mavlink_msg_tqfcidinput_get_iq_com_A(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field pos_abs_p from tqfcidinput message
 *
 * @return  
 */
static inline uint32_t mavlink_msg_tqfcidinput_get_pos_abs_p(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  12);
}

/**
 * @brief Get field pos_init_p from tqfcidinput message
 *
 * @return  
 */
static inline int64_t mavlink_msg_tqfcidinput_get_pos_init_p(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int64_t(msg,  0);
}

/**
 * @brief Get field start from tqfcidinput message
 *
 * @return  
 */
static inline uint8_t mavlink_msg_tqfcidinput_get_start(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  16);
}

/**
 * @brief Decode a tqfcidinput message into a struct
 *
 * @param msg The message to decode
 * @param tqfcidinput C-struct to decode the message contents into
 */
static inline void mavlink_msg_tqfcidinput_decode(const mavlink_message_t* msg, mavlink_tqfcidinput_t* tqfcidinput)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    tqfcidinput->pos_init_p = mavlink_msg_tqfcidinput_get_pos_init_p(msg);
    tqfcidinput->iq_com_A = mavlink_msg_tqfcidinput_get_iq_com_A(msg);
    tqfcidinput->pos_abs_p = mavlink_msg_tqfcidinput_get_pos_abs_p(msg);
    tqfcidinput->start = mavlink_msg_tqfcidinput_get_start(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_TqFcIdInput_LEN? msg->len : MAVLINK_MSG_ID_TqFcIdInput_LEN;
        memset(tqfcidinput, 0, MAVLINK_MSG_ID_TqFcIdInput_LEN);
    memcpy(tqfcidinput, _MAV_PAYLOAD(msg), len);
#endif
}
