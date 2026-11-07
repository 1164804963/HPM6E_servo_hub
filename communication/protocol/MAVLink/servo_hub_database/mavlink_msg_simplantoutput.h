#pragma once
// MESSAGE SimPlantOutput PACKING

#define MAVLINK_MSG_ID_SimPlantOutput 30080


typedef struct __mavlink_simplantoutput_t {
 float iabc_now_A[3]; /*<  */
 uint32_t enc_counts_P; /*<  */
 float dc_bus_V; /*<  */
 uint8_t hall_state; /*<  */
} mavlink_simplantoutput_t;

#define MAVLINK_MSG_ID_SimPlantOutput_LEN 21
#define MAVLINK_MSG_ID_SimPlantOutput_MIN_LEN 21
#define MAVLINK_MSG_ID_30080_LEN 21
#define MAVLINK_MSG_ID_30080_MIN_LEN 21

#define MAVLINK_MSG_ID_SimPlantOutput_CRC 88
#define MAVLINK_MSG_ID_30080_CRC 88

#define MAVLINK_MSG_SimPlantOutput_FIELD_IABC_NOW_A_LEN 3

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_SimPlantOutput { \
    30080, \
    "SimPlantOutput", \
    4, \
    {  { "iabc_now_A", NULL, MAVLINK_TYPE_FLOAT, 3, 0, offsetof(mavlink_simplantoutput_t, iabc_now_A) }, \
         { "enc_counts_P", NULL, MAVLINK_TYPE_UINT32_T, 0, 12, offsetof(mavlink_simplantoutput_t, enc_counts_P) }, \
         { "hall_state", NULL, MAVLINK_TYPE_UINT8_T, 0, 20, offsetof(mavlink_simplantoutput_t, hall_state) }, \
         { "dc_bus_V", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_simplantoutput_t, dc_bus_V) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_SimPlantOutput { \
    "SimPlantOutput", \
    4, \
    {  { "iabc_now_A", NULL, MAVLINK_TYPE_FLOAT, 3, 0, offsetof(mavlink_simplantoutput_t, iabc_now_A) }, \
         { "enc_counts_P", NULL, MAVLINK_TYPE_UINT32_T, 0, 12, offsetof(mavlink_simplantoutput_t, enc_counts_P) }, \
         { "hall_state", NULL, MAVLINK_TYPE_UINT8_T, 0, 20, offsetof(mavlink_simplantoutput_t, hall_state) }, \
         { "dc_bus_V", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_simplantoutput_t, dc_bus_V) }, \
         } \
}
#endif

/**
 * @brief Pack a simplantoutput message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param iabc_now_A  
 * @param enc_counts_P  
 * @param hall_state  
 * @param dc_bus_V  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_simplantoutput_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               const float *iabc_now_A, uint32_t enc_counts_P, uint8_t hall_state, float dc_bus_V)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SimPlantOutput_LEN];
    _mav_put_uint32_t(buf, 12, enc_counts_P);
    _mav_put_float(buf, 16, dc_bus_V);
    _mav_put_uint8_t(buf, 20, hall_state);
    _mav_put_float_array(buf, 0, iabc_now_A, 3);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SimPlantOutput_LEN);
#else
    mavlink_simplantoutput_t packet;
    packet.enc_counts_P = enc_counts_P;
    packet.dc_bus_V = dc_bus_V;
    packet.hall_state = hall_state;
    mav_array_memcpy(packet.iabc_now_A, iabc_now_A, sizeof(float)*3);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SimPlantOutput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SimPlantOutput;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_SimPlantOutput_MIN_LEN, MAVLINK_MSG_ID_SimPlantOutput_LEN, MAVLINK_MSG_ID_SimPlantOutput_CRC);
}

/**
 * @brief Pack a simplantoutput message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param iabc_now_A  
 * @param enc_counts_P  
 * @param hall_state  
 * @param dc_bus_V  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_simplantoutput_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               const float *iabc_now_A, uint32_t enc_counts_P, uint8_t hall_state, float dc_bus_V)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SimPlantOutput_LEN];
    _mav_put_uint32_t(buf, 12, enc_counts_P);
    _mav_put_float(buf, 16, dc_bus_V);
    _mav_put_uint8_t(buf, 20, hall_state);
    _mav_put_float_array(buf, 0, iabc_now_A, 3);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SimPlantOutput_LEN);
#else
    mavlink_simplantoutput_t packet;
    packet.enc_counts_P = enc_counts_P;
    packet.dc_bus_V = dc_bus_V;
    packet.hall_state = hall_state;
    mav_array_memcpy(packet.iabc_now_A, iabc_now_A, sizeof(float)*3);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SimPlantOutput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SimPlantOutput;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_SimPlantOutput_MIN_LEN, MAVLINK_MSG_ID_SimPlantOutput_LEN, MAVLINK_MSG_ID_SimPlantOutput_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_SimPlantOutput_MIN_LEN, MAVLINK_MSG_ID_SimPlantOutput_LEN);
#endif
}

/**
 * @brief Pack a simplantoutput message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param iabc_now_A  
 * @param enc_counts_P  
 * @param hall_state  
 * @param dc_bus_V  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_simplantoutput_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   const float *iabc_now_A,uint32_t enc_counts_P,uint8_t hall_state,float dc_bus_V)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SimPlantOutput_LEN];
    _mav_put_uint32_t(buf, 12, enc_counts_P);
    _mav_put_float(buf, 16, dc_bus_V);
    _mav_put_uint8_t(buf, 20, hall_state);
    _mav_put_float_array(buf, 0, iabc_now_A, 3);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SimPlantOutput_LEN);
#else
    mavlink_simplantoutput_t packet;
    packet.enc_counts_P = enc_counts_P;
    packet.dc_bus_V = dc_bus_V;
    packet.hall_state = hall_state;
    mav_array_memcpy(packet.iabc_now_A, iabc_now_A, sizeof(float)*3);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SimPlantOutput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SimPlantOutput;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_SimPlantOutput_MIN_LEN, MAVLINK_MSG_ID_SimPlantOutput_LEN, MAVLINK_MSG_ID_SimPlantOutput_CRC);
}

/**
 * @brief Encode a simplantoutput struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param simplantoutput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_simplantoutput_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_simplantoutput_t* simplantoutput)
{
    return mavlink_msg_simplantoutput_pack(system_id, component_id, msg, simplantoutput->iabc_now_A, simplantoutput->enc_counts_P, simplantoutput->hall_state, simplantoutput->dc_bus_V);
}

/**
 * @brief Encode a simplantoutput struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param simplantoutput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_simplantoutput_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_simplantoutput_t* simplantoutput)
{
    return mavlink_msg_simplantoutput_pack_chan(system_id, component_id, chan, msg, simplantoutput->iabc_now_A, simplantoutput->enc_counts_P, simplantoutput->hall_state, simplantoutput->dc_bus_V);
}

/**
 * @brief Encode a simplantoutput struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param simplantoutput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_simplantoutput_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_simplantoutput_t* simplantoutput)
{
    return mavlink_msg_simplantoutput_pack_status(system_id, component_id, _status, msg,  simplantoutput->iabc_now_A, simplantoutput->enc_counts_P, simplantoutput->hall_state, simplantoutput->dc_bus_V);
}

/**
 * @brief Send a simplantoutput message
 * @param chan MAVLink channel to send the message
 *
 * @param iabc_now_A  
 * @param enc_counts_P  
 * @param hall_state  
 * @param dc_bus_V  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_simplantoutput_send(mavlink_channel_t chan, const float *iabc_now_A, uint32_t enc_counts_P, uint8_t hall_state, float dc_bus_V)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SimPlantOutput_LEN];
    _mav_put_uint32_t(buf, 12, enc_counts_P);
    _mav_put_float(buf, 16, dc_bus_V);
    _mav_put_uint8_t(buf, 20, hall_state);
    _mav_put_float_array(buf, 0, iabc_now_A, 3);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SimPlantOutput, buf, MAVLINK_MSG_ID_SimPlantOutput_MIN_LEN, MAVLINK_MSG_ID_SimPlantOutput_LEN, MAVLINK_MSG_ID_SimPlantOutput_CRC);
#else
    mavlink_simplantoutput_t packet;
    packet.enc_counts_P = enc_counts_P;
    packet.dc_bus_V = dc_bus_V;
    packet.hall_state = hall_state;
    mav_array_memcpy(packet.iabc_now_A, iabc_now_A, sizeof(float)*3);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SimPlantOutput, (const char *)&packet, MAVLINK_MSG_ID_SimPlantOutput_MIN_LEN, MAVLINK_MSG_ID_SimPlantOutput_LEN, MAVLINK_MSG_ID_SimPlantOutput_CRC);
#endif
}

/**
 * @brief Send a simplantoutput message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_simplantoutput_send_struct(mavlink_channel_t chan, const mavlink_simplantoutput_t* simplantoutput)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_simplantoutput_send(chan, simplantoutput->iabc_now_A, simplantoutput->enc_counts_P, simplantoutput->hall_state, simplantoutput->dc_bus_V);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SimPlantOutput, (const char *)simplantoutput, MAVLINK_MSG_ID_SimPlantOutput_MIN_LEN, MAVLINK_MSG_ID_SimPlantOutput_LEN, MAVLINK_MSG_ID_SimPlantOutput_CRC);
#endif
}

#if MAVLINK_MSG_ID_SimPlantOutput_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_simplantoutput_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  const float *iabc_now_A, uint32_t enc_counts_P, uint8_t hall_state, float dc_bus_V)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint32_t(buf, 12, enc_counts_P);
    _mav_put_float(buf, 16, dc_bus_V);
    _mav_put_uint8_t(buf, 20, hall_state);
    _mav_put_float_array(buf, 0, iabc_now_A, 3);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SimPlantOutput, buf, MAVLINK_MSG_ID_SimPlantOutput_MIN_LEN, MAVLINK_MSG_ID_SimPlantOutput_LEN, MAVLINK_MSG_ID_SimPlantOutput_CRC);
#else
    mavlink_simplantoutput_t *packet = (mavlink_simplantoutput_t *)msgbuf;
    packet->enc_counts_P = enc_counts_P;
    packet->dc_bus_V = dc_bus_V;
    packet->hall_state = hall_state;
    mav_array_memcpy(packet->iabc_now_A, iabc_now_A, sizeof(float)*3);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SimPlantOutput, (const char *)packet, MAVLINK_MSG_ID_SimPlantOutput_MIN_LEN, MAVLINK_MSG_ID_SimPlantOutput_LEN, MAVLINK_MSG_ID_SimPlantOutput_CRC);
#endif
}
#endif

#endif

// MESSAGE SimPlantOutput UNPACKING


/**
 * @brief Get field iabc_now_A from simplantoutput message
 *
 * @return  
 */
static inline uint16_t mavlink_msg_simplantoutput_get_iabc_now_A(const mavlink_message_t* msg, float *iabc_now_A)
{
    return _MAV_RETURN_float_array(msg, iabc_now_A, 3,  0);
}

/**
 * @brief Get field enc_counts_P from simplantoutput message
 *
 * @return  
 */
static inline uint32_t mavlink_msg_simplantoutput_get_enc_counts_P(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  12);
}

/**
 * @brief Get field hall_state from simplantoutput message
 *
 * @return  
 */
static inline uint8_t mavlink_msg_simplantoutput_get_hall_state(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  20);
}

/**
 * @brief Get field dc_bus_V from simplantoutput message
 *
 * @return  
 */
static inline float mavlink_msg_simplantoutput_get_dc_bus_V(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  16);
}

/**
 * @brief Decode a simplantoutput message into a struct
 *
 * @param msg The message to decode
 * @param simplantoutput C-struct to decode the message contents into
 */
static inline void mavlink_msg_simplantoutput_decode(const mavlink_message_t* msg, mavlink_simplantoutput_t* simplantoutput)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_simplantoutput_get_iabc_now_A(msg, simplantoutput->iabc_now_A);
    simplantoutput->enc_counts_P = mavlink_msg_simplantoutput_get_enc_counts_P(msg);
    simplantoutput->dc_bus_V = mavlink_msg_simplantoutput_get_dc_bus_V(msg);
    simplantoutput->hall_state = mavlink_msg_simplantoutput_get_hall_state(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_SimPlantOutput_LEN? msg->len : MAVLINK_MSG_ID_SimPlantOutput_LEN;
        memset(simplantoutput, 0, MAVLINK_MSG_ID_SimPlantOutput_LEN);
    memcpy(simplantoutput, _MAV_PAYLOAD(msg), len);
#endif
}
