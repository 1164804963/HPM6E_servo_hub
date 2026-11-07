#pragma once
// MESSAGE ReciprocalMotionOutput PACKING

#define MAVLINK_MSG_ID_ReciprocalMotionOutput 30051


typedef struct __mavlink_reciprocalmotionoutput_t {
 int64_t pos_tar_p; /*<  */
 float v_tar_p_s; /*<  */
 float acc_tar_p_ss; /*<  */
 int8_t state_now; /*<  */
} mavlink_reciprocalmotionoutput_t;

#define MAVLINK_MSG_ID_ReciprocalMotionOutput_LEN 17
#define MAVLINK_MSG_ID_ReciprocalMotionOutput_MIN_LEN 17
#define MAVLINK_MSG_ID_30051_LEN 17
#define MAVLINK_MSG_ID_30051_MIN_LEN 17

#define MAVLINK_MSG_ID_ReciprocalMotionOutput_CRC 103
#define MAVLINK_MSG_ID_30051_CRC 103



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_ReciprocalMotionOutput { \
    30051, \
    "ReciprocalMotionOutput", \
    4, \
    {  { "pos_tar_p", NULL, MAVLINK_TYPE_INT64_T, 0, 0, offsetof(mavlink_reciprocalmotionoutput_t, pos_tar_p) }, \
         { "v_tar_p_s", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_reciprocalmotionoutput_t, v_tar_p_s) }, \
         { "acc_tar_p_ss", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_reciprocalmotionoutput_t, acc_tar_p_ss) }, \
         { "state_now", NULL, MAVLINK_TYPE_INT8_T, 0, 16, offsetof(mavlink_reciprocalmotionoutput_t, state_now) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_ReciprocalMotionOutput { \
    "ReciprocalMotionOutput", \
    4, \
    {  { "pos_tar_p", NULL, MAVLINK_TYPE_INT64_T, 0, 0, offsetof(mavlink_reciprocalmotionoutput_t, pos_tar_p) }, \
         { "v_tar_p_s", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_reciprocalmotionoutput_t, v_tar_p_s) }, \
         { "acc_tar_p_ss", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_reciprocalmotionoutput_t, acc_tar_p_ss) }, \
         { "state_now", NULL, MAVLINK_TYPE_INT8_T, 0, 16, offsetof(mavlink_reciprocalmotionoutput_t, state_now) }, \
         } \
}
#endif

/**
 * @brief Pack a reciprocalmotionoutput message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param pos_tar_p  
 * @param v_tar_p_s  
 * @param acc_tar_p_ss  
 * @param state_now  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_reciprocalmotionoutput_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               int64_t pos_tar_p, float v_tar_p_s, float acc_tar_p_ss, int8_t state_now)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ReciprocalMotionOutput_LEN];
    _mav_put_int64_t(buf, 0, pos_tar_p);
    _mav_put_float(buf, 8, v_tar_p_s);
    _mav_put_float(buf, 12, acc_tar_p_ss);
    _mav_put_int8_t(buf, 16, state_now);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ReciprocalMotionOutput_LEN);
#else
    mavlink_reciprocalmotionoutput_t packet;
    packet.pos_tar_p = pos_tar_p;
    packet.v_tar_p_s = v_tar_p_s;
    packet.acc_tar_p_ss = acc_tar_p_ss;
    packet.state_now = state_now;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ReciprocalMotionOutput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ReciprocalMotionOutput;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_ReciprocalMotionOutput_MIN_LEN, MAVLINK_MSG_ID_ReciprocalMotionOutput_LEN, MAVLINK_MSG_ID_ReciprocalMotionOutput_CRC);
}

/**
 * @brief Pack a reciprocalmotionoutput message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param pos_tar_p  
 * @param v_tar_p_s  
 * @param acc_tar_p_ss  
 * @param state_now  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_reciprocalmotionoutput_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               int64_t pos_tar_p, float v_tar_p_s, float acc_tar_p_ss, int8_t state_now)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ReciprocalMotionOutput_LEN];
    _mav_put_int64_t(buf, 0, pos_tar_p);
    _mav_put_float(buf, 8, v_tar_p_s);
    _mav_put_float(buf, 12, acc_tar_p_ss);
    _mav_put_int8_t(buf, 16, state_now);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ReciprocalMotionOutput_LEN);
#else
    mavlink_reciprocalmotionoutput_t packet;
    packet.pos_tar_p = pos_tar_p;
    packet.v_tar_p_s = v_tar_p_s;
    packet.acc_tar_p_ss = acc_tar_p_ss;
    packet.state_now = state_now;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ReciprocalMotionOutput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ReciprocalMotionOutput;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_ReciprocalMotionOutput_MIN_LEN, MAVLINK_MSG_ID_ReciprocalMotionOutput_LEN, MAVLINK_MSG_ID_ReciprocalMotionOutput_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_ReciprocalMotionOutput_MIN_LEN, MAVLINK_MSG_ID_ReciprocalMotionOutput_LEN);
#endif
}

/**
 * @brief Pack a reciprocalmotionoutput message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param pos_tar_p  
 * @param v_tar_p_s  
 * @param acc_tar_p_ss  
 * @param state_now  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_reciprocalmotionoutput_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   int64_t pos_tar_p,float v_tar_p_s,float acc_tar_p_ss,int8_t state_now)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ReciprocalMotionOutput_LEN];
    _mav_put_int64_t(buf, 0, pos_tar_p);
    _mav_put_float(buf, 8, v_tar_p_s);
    _mav_put_float(buf, 12, acc_tar_p_ss);
    _mav_put_int8_t(buf, 16, state_now);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ReciprocalMotionOutput_LEN);
#else
    mavlink_reciprocalmotionoutput_t packet;
    packet.pos_tar_p = pos_tar_p;
    packet.v_tar_p_s = v_tar_p_s;
    packet.acc_tar_p_ss = acc_tar_p_ss;
    packet.state_now = state_now;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ReciprocalMotionOutput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ReciprocalMotionOutput;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_ReciprocalMotionOutput_MIN_LEN, MAVLINK_MSG_ID_ReciprocalMotionOutput_LEN, MAVLINK_MSG_ID_ReciprocalMotionOutput_CRC);
}

/**
 * @brief Encode a reciprocalmotionoutput struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param reciprocalmotionoutput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_reciprocalmotionoutput_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_reciprocalmotionoutput_t* reciprocalmotionoutput)
{
    return mavlink_msg_reciprocalmotionoutput_pack(system_id, component_id, msg, reciprocalmotionoutput->pos_tar_p, reciprocalmotionoutput->v_tar_p_s, reciprocalmotionoutput->acc_tar_p_ss, reciprocalmotionoutput->state_now);
}

/**
 * @brief Encode a reciprocalmotionoutput struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param reciprocalmotionoutput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_reciprocalmotionoutput_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_reciprocalmotionoutput_t* reciprocalmotionoutput)
{
    return mavlink_msg_reciprocalmotionoutput_pack_chan(system_id, component_id, chan, msg, reciprocalmotionoutput->pos_tar_p, reciprocalmotionoutput->v_tar_p_s, reciprocalmotionoutput->acc_tar_p_ss, reciprocalmotionoutput->state_now);
}

/**
 * @brief Encode a reciprocalmotionoutput struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param reciprocalmotionoutput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_reciprocalmotionoutput_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_reciprocalmotionoutput_t* reciprocalmotionoutput)
{
    return mavlink_msg_reciprocalmotionoutput_pack_status(system_id, component_id, _status, msg,  reciprocalmotionoutput->pos_tar_p, reciprocalmotionoutput->v_tar_p_s, reciprocalmotionoutput->acc_tar_p_ss, reciprocalmotionoutput->state_now);
}

/**
 * @brief Send a reciprocalmotionoutput message
 * @param chan MAVLink channel to send the message
 *
 * @param pos_tar_p  
 * @param v_tar_p_s  
 * @param acc_tar_p_ss  
 * @param state_now  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_reciprocalmotionoutput_send(mavlink_channel_t chan, int64_t pos_tar_p, float v_tar_p_s, float acc_tar_p_ss, int8_t state_now)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ReciprocalMotionOutput_LEN];
    _mav_put_int64_t(buf, 0, pos_tar_p);
    _mav_put_float(buf, 8, v_tar_p_s);
    _mav_put_float(buf, 12, acc_tar_p_ss);
    _mav_put_int8_t(buf, 16, state_now);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ReciprocalMotionOutput, buf, MAVLINK_MSG_ID_ReciprocalMotionOutput_MIN_LEN, MAVLINK_MSG_ID_ReciprocalMotionOutput_LEN, MAVLINK_MSG_ID_ReciprocalMotionOutput_CRC);
#else
    mavlink_reciprocalmotionoutput_t packet;
    packet.pos_tar_p = pos_tar_p;
    packet.v_tar_p_s = v_tar_p_s;
    packet.acc_tar_p_ss = acc_tar_p_ss;
    packet.state_now = state_now;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ReciprocalMotionOutput, (const char *)&packet, MAVLINK_MSG_ID_ReciprocalMotionOutput_MIN_LEN, MAVLINK_MSG_ID_ReciprocalMotionOutput_LEN, MAVLINK_MSG_ID_ReciprocalMotionOutput_CRC);
#endif
}

/**
 * @brief Send a reciprocalmotionoutput message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_reciprocalmotionoutput_send_struct(mavlink_channel_t chan, const mavlink_reciprocalmotionoutput_t* reciprocalmotionoutput)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_reciprocalmotionoutput_send(chan, reciprocalmotionoutput->pos_tar_p, reciprocalmotionoutput->v_tar_p_s, reciprocalmotionoutput->acc_tar_p_ss, reciprocalmotionoutput->state_now);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ReciprocalMotionOutput, (const char *)reciprocalmotionoutput, MAVLINK_MSG_ID_ReciprocalMotionOutput_MIN_LEN, MAVLINK_MSG_ID_ReciprocalMotionOutput_LEN, MAVLINK_MSG_ID_ReciprocalMotionOutput_CRC);
#endif
}

#if MAVLINK_MSG_ID_ReciprocalMotionOutput_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_reciprocalmotionoutput_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  int64_t pos_tar_p, float v_tar_p_s, float acc_tar_p_ss, int8_t state_now)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_int64_t(buf, 0, pos_tar_p);
    _mav_put_float(buf, 8, v_tar_p_s);
    _mav_put_float(buf, 12, acc_tar_p_ss);
    _mav_put_int8_t(buf, 16, state_now);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ReciprocalMotionOutput, buf, MAVLINK_MSG_ID_ReciprocalMotionOutput_MIN_LEN, MAVLINK_MSG_ID_ReciprocalMotionOutput_LEN, MAVLINK_MSG_ID_ReciprocalMotionOutput_CRC);
#else
    mavlink_reciprocalmotionoutput_t *packet = (mavlink_reciprocalmotionoutput_t *)msgbuf;
    packet->pos_tar_p = pos_tar_p;
    packet->v_tar_p_s = v_tar_p_s;
    packet->acc_tar_p_ss = acc_tar_p_ss;
    packet->state_now = state_now;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ReciprocalMotionOutput, (const char *)packet, MAVLINK_MSG_ID_ReciprocalMotionOutput_MIN_LEN, MAVLINK_MSG_ID_ReciprocalMotionOutput_LEN, MAVLINK_MSG_ID_ReciprocalMotionOutput_CRC);
#endif
}
#endif

#endif

// MESSAGE ReciprocalMotionOutput UNPACKING


/**
 * @brief Get field pos_tar_p from reciprocalmotionoutput message
 *
 * @return  
 */
static inline int64_t mavlink_msg_reciprocalmotionoutput_get_pos_tar_p(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int64_t(msg,  0);
}

/**
 * @brief Get field v_tar_p_s from reciprocalmotionoutput message
 *
 * @return  
 */
static inline float mavlink_msg_reciprocalmotionoutput_get_v_tar_p_s(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field acc_tar_p_ss from reciprocalmotionoutput message
 *
 * @return  
 */
static inline float mavlink_msg_reciprocalmotionoutput_get_acc_tar_p_ss(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Get field state_now from reciprocalmotionoutput message
 *
 * @return  
 */
static inline int8_t mavlink_msg_reciprocalmotionoutput_get_state_now(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int8_t(msg,  16);
}

/**
 * @brief Decode a reciprocalmotionoutput message into a struct
 *
 * @param msg The message to decode
 * @param reciprocalmotionoutput C-struct to decode the message contents into
 */
static inline void mavlink_msg_reciprocalmotionoutput_decode(const mavlink_message_t* msg, mavlink_reciprocalmotionoutput_t* reciprocalmotionoutput)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    reciprocalmotionoutput->pos_tar_p = mavlink_msg_reciprocalmotionoutput_get_pos_tar_p(msg);
    reciprocalmotionoutput->v_tar_p_s = mavlink_msg_reciprocalmotionoutput_get_v_tar_p_s(msg);
    reciprocalmotionoutput->acc_tar_p_ss = mavlink_msg_reciprocalmotionoutput_get_acc_tar_p_ss(msg);
    reciprocalmotionoutput->state_now = mavlink_msg_reciprocalmotionoutput_get_state_now(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_ReciprocalMotionOutput_LEN? msg->len : MAVLINK_MSG_ID_ReciprocalMotionOutput_LEN;
        memset(reciprocalmotionoutput, 0, MAVLINK_MSG_ID_ReciprocalMotionOutput_LEN);
    memcpy(reciprocalmotionoutput, _MAV_PAYLOAD(msg), len);
#endif
}
