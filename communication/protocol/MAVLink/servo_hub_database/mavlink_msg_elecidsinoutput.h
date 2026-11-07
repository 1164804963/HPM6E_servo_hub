#pragma once
// MESSAGE ElecIdSinOutput PACKING

#define MAVLINK_MSG_ID_ElecIdSinOutput 30003


typedef struct __mavlink_elecidsinoutput_t {
 float u_abc_tar_V[3]; /*<  */
 float u_alpha_now_V; /*<  */
 float i_alpha_now_A; /*<  */
 int8_t state_now; /*<  */
} mavlink_elecidsinoutput_t;

#define MAVLINK_MSG_ID_ElecIdSinOutput_LEN 21
#define MAVLINK_MSG_ID_ElecIdSinOutput_MIN_LEN 21
#define MAVLINK_MSG_ID_30003_LEN 21
#define MAVLINK_MSG_ID_30003_MIN_LEN 21

#define MAVLINK_MSG_ID_ElecIdSinOutput_CRC 180
#define MAVLINK_MSG_ID_30003_CRC 180

#define MAVLINK_MSG_ElecIdSinOutput_FIELD_U_ABC_TAR_V_LEN 3

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_ElecIdSinOutput { \
    30003, \
    "ElecIdSinOutput", \
    4, \
    {  { "state_now", NULL, MAVLINK_TYPE_INT8_T, 0, 20, offsetof(mavlink_elecidsinoutput_t, state_now) }, \
         { "u_abc_tar_V", NULL, MAVLINK_TYPE_FLOAT, 3, 0, offsetof(mavlink_elecidsinoutput_t, u_abc_tar_V) }, \
         { "u_alpha_now_V", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_elecidsinoutput_t, u_alpha_now_V) }, \
         { "i_alpha_now_A", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_elecidsinoutput_t, i_alpha_now_A) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_ElecIdSinOutput { \
    "ElecIdSinOutput", \
    4, \
    {  { "state_now", NULL, MAVLINK_TYPE_INT8_T, 0, 20, offsetof(mavlink_elecidsinoutput_t, state_now) }, \
         { "u_abc_tar_V", NULL, MAVLINK_TYPE_FLOAT, 3, 0, offsetof(mavlink_elecidsinoutput_t, u_abc_tar_V) }, \
         { "u_alpha_now_V", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_elecidsinoutput_t, u_alpha_now_V) }, \
         { "i_alpha_now_A", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_elecidsinoutput_t, i_alpha_now_A) }, \
         } \
}
#endif

/**
 * @brief Pack a elecidsinoutput message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param state_now  
 * @param u_abc_tar_V  
 * @param u_alpha_now_V  
 * @param i_alpha_now_A  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_elecidsinoutput_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               int8_t state_now, const float *u_abc_tar_V, float u_alpha_now_V, float i_alpha_now_A)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ElecIdSinOutput_LEN];
    _mav_put_float(buf, 12, u_alpha_now_V);
    _mav_put_float(buf, 16, i_alpha_now_A);
    _mav_put_int8_t(buf, 20, state_now);
    _mav_put_float_array(buf, 0, u_abc_tar_V, 3);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ElecIdSinOutput_LEN);
#else
    mavlink_elecidsinoutput_t packet;
    packet.u_alpha_now_V = u_alpha_now_V;
    packet.i_alpha_now_A = i_alpha_now_A;
    packet.state_now = state_now;
    mav_array_memcpy(packet.u_abc_tar_V, u_abc_tar_V, sizeof(float)*3);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ElecIdSinOutput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ElecIdSinOutput;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_ElecIdSinOutput_MIN_LEN, MAVLINK_MSG_ID_ElecIdSinOutput_LEN, MAVLINK_MSG_ID_ElecIdSinOutput_CRC);
}

/**
 * @brief Pack a elecidsinoutput message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param state_now  
 * @param u_abc_tar_V  
 * @param u_alpha_now_V  
 * @param i_alpha_now_A  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_elecidsinoutput_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               int8_t state_now, const float *u_abc_tar_V, float u_alpha_now_V, float i_alpha_now_A)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ElecIdSinOutput_LEN];
    _mav_put_float(buf, 12, u_alpha_now_V);
    _mav_put_float(buf, 16, i_alpha_now_A);
    _mav_put_int8_t(buf, 20, state_now);
    _mav_put_float_array(buf, 0, u_abc_tar_V, 3);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ElecIdSinOutput_LEN);
#else
    mavlink_elecidsinoutput_t packet;
    packet.u_alpha_now_V = u_alpha_now_V;
    packet.i_alpha_now_A = i_alpha_now_A;
    packet.state_now = state_now;
    mav_array_memcpy(packet.u_abc_tar_V, u_abc_tar_V, sizeof(float)*3);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ElecIdSinOutput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ElecIdSinOutput;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_ElecIdSinOutput_MIN_LEN, MAVLINK_MSG_ID_ElecIdSinOutput_LEN, MAVLINK_MSG_ID_ElecIdSinOutput_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_ElecIdSinOutput_MIN_LEN, MAVLINK_MSG_ID_ElecIdSinOutput_LEN);
#endif
}

/**
 * @brief Pack a elecidsinoutput message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param state_now  
 * @param u_abc_tar_V  
 * @param u_alpha_now_V  
 * @param i_alpha_now_A  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_elecidsinoutput_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   int8_t state_now,const float *u_abc_tar_V,float u_alpha_now_V,float i_alpha_now_A)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ElecIdSinOutput_LEN];
    _mav_put_float(buf, 12, u_alpha_now_V);
    _mav_put_float(buf, 16, i_alpha_now_A);
    _mav_put_int8_t(buf, 20, state_now);
    _mav_put_float_array(buf, 0, u_abc_tar_V, 3);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ElecIdSinOutput_LEN);
#else
    mavlink_elecidsinoutput_t packet;
    packet.u_alpha_now_V = u_alpha_now_V;
    packet.i_alpha_now_A = i_alpha_now_A;
    packet.state_now = state_now;
    mav_array_memcpy(packet.u_abc_tar_V, u_abc_tar_V, sizeof(float)*3);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ElecIdSinOutput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ElecIdSinOutput;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_ElecIdSinOutput_MIN_LEN, MAVLINK_MSG_ID_ElecIdSinOutput_LEN, MAVLINK_MSG_ID_ElecIdSinOutput_CRC);
}

/**
 * @brief Encode a elecidsinoutput struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param elecidsinoutput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_elecidsinoutput_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_elecidsinoutput_t* elecidsinoutput)
{
    return mavlink_msg_elecidsinoutput_pack(system_id, component_id, msg, elecidsinoutput->state_now, elecidsinoutput->u_abc_tar_V, elecidsinoutput->u_alpha_now_V, elecidsinoutput->i_alpha_now_A);
}

/**
 * @brief Encode a elecidsinoutput struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param elecidsinoutput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_elecidsinoutput_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_elecidsinoutput_t* elecidsinoutput)
{
    return mavlink_msg_elecidsinoutput_pack_chan(system_id, component_id, chan, msg, elecidsinoutput->state_now, elecidsinoutput->u_abc_tar_V, elecidsinoutput->u_alpha_now_V, elecidsinoutput->i_alpha_now_A);
}

/**
 * @brief Encode a elecidsinoutput struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param elecidsinoutput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_elecidsinoutput_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_elecidsinoutput_t* elecidsinoutput)
{
    return mavlink_msg_elecidsinoutput_pack_status(system_id, component_id, _status, msg,  elecidsinoutput->state_now, elecidsinoutput->u_abc_tar_V, elecidsinoutput->u_alpha_now_V, elecidsinoutput->i_alpha_now_A);
}

/**
 * @brief Send a elecidsinoutput message
 * @param chan MAVLink channel to send the message
 *
 * @param state_now  
 * @param u_abc_tar_V  
 * @param u_alpha_now_V  
 * @param i_alpha_now_A  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_elecidsinoutput_send(mavlink_channel_t chan, int8_t state_now, const float *u_abc_tar_V, float u_alpha_now_V, float i_alpha_now_A)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ElecIdSinOutput_LEN];
    _mav_put_float(buf, 12, u_alpha_now_V);
    _mav_put_float(buf, 16, i_alpha_now_A);
    _mav_put_int8_t(buf, 20, state_now);
    _mav_put_float_array(buf, 0, u_abc_tar_V, 3);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ElecIdSinOutput, buf, MAVLINK_MSG_ID_ElecIdSinOutput_MIN_LEN, MAVLINK_MSG_ID_ElecIdSinOutput_LEN, MAVLINK_MSG_ID_ElecIdSinOutput_CRC);
#else
    mavlink_elecidsinoutput_t packet;
    packet.u_alpha_now_V = u_alpha_now_V;
    packet.i_alpha_now_A = i_alpha_now_A;
    packet.state_now = state_now;
    mav_array_memcpy(packet.u_abc_tar_V, u_abc_tar_V, sizeof(float)*3);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ElecIdSinOutput, (const char *)&packet, MAVLINK_MSG_ID_ElecIdSinOutput_MIN_LEN, MAVLINK_MSG_ID_ElecIdSinOutput_LEN, MAVLINK_MSG_ID_ElecIdSinOutput_CRC);
#endif
}

/**
 * @brief Send a elecidsinoutput message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_elecidsinoutput_send_struct(mavlink_channel_t chan, const mavlink_elecidsinoutput_t* elecidsinoutput)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_elecidsinoutput_send(chan, elecidsinoutput->state_now, elecidsinoutput->u_abc_tar_V, elecidsinoutput->u_alpha_now_V, elecidsinoutput->i_alpha_now_A);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ElecIdSinOutput, (const char *)elecidsinoutput, MAVLINK_MSG_ID_ElecIdSinOutput_MIN_LEN, MAVLINK_MSG_ID_ElecIdSinOutput_LEN, MAVLINK_MSG_ID_ElecIdSinOutput_CRC);
#endif
}

#if MAVLINK_MSG_ID_ElecIdSinOutput_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_elecidsinoutput_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  int8_t state_now, const float *u_abc_tar_V, float u_alpha_now_V, float i_alpha_now_A)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 12, u_alpha_now_V);
    _mav_put_float(buf, 16, i_alpha_now_A);
    _mav_put_int8_t(buf, 20, state_now);
    _mav_put_float_array(buf, 0, u_abc_tar_V, 3);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ElecIdSinOutput, buf, MAVLINK_MSG_ID_ElecIdSinOutput_MIN_LEN, MAVLINK_MSG_ID_ElecIdSinOutput_LEN, MAVLINK_MSG_ID_ElecIdSinOutput_CRC);
#else
    mavlink_elecidsinoutput_t *packet = (mavlink_elecidsinoutput_t *)msgbuf;
    packet->u_alpha_now_V = u_alpha_now_V;
    packet->i_alpha_now_A = i_alpha_now_A;
    packet->state_now = state_now;
    mav_array_memcpy(packet->u_abc_tar_V, u_abc_tar_V, sizeof(float)*3);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ElecIdSinOutput, (const char *)packet, MAVLINK_MSG_ID_ElecIdSinOutput_MIN_LEN, MAVLINK_MSG_ID_ElecIdSinOutput_LEN, MAVLINK_MSG_ID_ElecIdSinOutput_CRC);
#endif
}
#endif

#endif

// MESSAGE ElecIdSinOutput UNPACKING


/**
 * @brief Get field state_now from elecidsinoutput message
 *
 * @return  
 */
static inline int8_t mavlink_msg_elecidsinoutput_get_state_now(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int8_t(msg,  20);
}

/**
 * @brief Get field u_abc_tar_V from elecidsinoutput message
 *
 * @return  
 */
static inline uint16_t mavlink_msg_elecidsinoutput_get_u_abc_tar_V(const mavlink_message_t* msg, float *u_abc_tar_V)
{
    return _MAV_RETURN_float_array(msg, u_abc_tar_V, 3,  0);
}

/**
 * @brief Get field u_alpha_now_V from elecidsinoutput message
 *
 * @return  
 */
static inline float mavlink_msg_elecidsinoutput_get_u_alpha_now_V(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Get field i_alpha_now_A from elecidsinoutput message
 *
 * @return  
 */
static inline float mavlink_msg_elecidsinoutput_get_i_alpha_now_A(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  16);
}

/**
 * @brief Decode a elecidsinoutput message into a struct
 *
 * @param msg The message to decode
 * @param elecidsinoutput C-struct to decode the message contents into
 */
static inline void mavlink_msg_elecidsinoutput_decode(const mavlink_message_t* msg, mavlink_elecidsinoutput_t* elecidsinoutput)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_elecidsinoutput_get_u_abc_tar_V(msg, elecidsinoutput->u_abc_tar_V);
    elecidsinoutput->u_alpha_now_V = mavlink_msg_elecidsinoutput_get_u_alpha_now_V(msg);
    elecidsinoutput->i_alpha_now_A = mavlink_msg_elecidsinoutput_get_i_alpha_now_A(msg);
    elecidsinoutput->state_now = mavlink_msg_elecidsinoutput_get_state_now(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_ElecIdSinOutput_LEN? msg->len : MAVLINK_MSG_ID_ElecIdSinOutput_LEN;
        memset(elecidsinoutput, 0, MAVLINK_MSG_ID_ElecIdSinOutput_LEN);
    memcpy(elecidsinoutput, _MAV_PAYLOAD(msg), len);
#endif
}
