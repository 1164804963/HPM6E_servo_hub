#pragma once
// MESSAGE ElecAngleIdOutput PACKING

#define MAVLINK_MSG_ID_ElecAngleIdOutput 30033


typedef struct __mavlink_elecangleidoutput_t {
 float id_tar_A; /*<  */
 float elec_bias_rad; /*<  */
 float elec_bias_buff_rad[2]; /*<  */
 int8_t state_now; /*<  */
 uint8_t step_num; /*<  */
} mavlink_elecangleidoutput_t;

#define MAVLINK_MSG_ID_ElecAngleIdOutput_LEN 18
#define MAVLINK_MSG_ID_ElecAngleIdOutput_MIN_LEN 18
#define MAVLINK_MSG_ID_30033_LEN 18
#define MAVLINK_MSG_ID_30033_MIN_LEN 18

#define MAVLINK_MSG_ID_ElecAngleIdOutput_CRC 25
#define MAVLINK_MSG_ID_30033_CRC 25

#define MAVLINK_MSG_ElecAngleIdOutput_FIELD_ELEC_BIAS_BUFF_RAD_LEN 2

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_ElecAngleIdOutput { \
    30033, \
    "ElecAngleIdOutput", \
    5, \
    {  { "id_tar_A", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_elecangleidoutput_t, id_tar_A) }, \
         { "elec_bias_rad", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_elecangleidoutput_t, elec_bias_rad) }, \
         { "state_now", NULL, MAVLINK_TYPE_INT8_T, 0, 16, offsetof(mavlink_elecangleidoutput_t, state_now) }, \
         { "elec_bias_buff_rad", NULL, MAVLINK_TYPE_FLOAT, 2, 8, offsetof(mavlink_elecangleidoutput_t, elec_bias_buff_rad) }, \
         { "step_num", NULL, MAVLINK_TYPE_UINT8_T, 0, 17, offsetof(mavlink_elecangleidoutput_t, step_num) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_ElecAngleIdOutput { \
    "ElecAngleIdOutput", \
    5, \
    {  { "id_tar_A", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_elecangleidoutput_t, id_tar_A) }, \
         { "elec_bias_rad", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_elecangleidoutput_t, elec_bias_rad) }, \
         { "state_now", NULL, MAVLINK_TYPE_INT8_T, 0, 16, offsetof(mavlink_elecangleidoutput_t, state_now) }, \
         { "elec_bias_buff_rad", NULL, MAVLINK_TYPE_FLOAT, 2, 8, offsetof(mavlink_elecangleidoutput_t, elec_bias_buff_rad) }, \
         { "step_num", NULL, MAVLINK_TYPE_UINT8_T, 0, 17, offsetof(mavlink_elecangleidoutput_t, step_num) }, \
         } \
}
#endif

/**
 * @brief Pack a elecangleidoutput message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param id_tar_A  
 * @param elec_bias_rad  
 * @param state_now  
 * @param elec_bias_buff_rad  
 * @param step_num  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_elecangleidoutput_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               float id_tar_A, float elec_bias_rad, int8_t state_now, const float *elec_bias_buff_rad, uint8_t step_num)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ElecAngleIdOutput_LEN];
    _mav_put_float(buf, 0, id_tar_A);
    _mav_put_float(buf, 4, elec_bias_rad);
    _mav_put_int8_t(buf, 16, state_now);
    _mav_put_uint8_t(buf, 17, step_num);
    _mav_put_float_array(buf, 8, elec_bias_buff_rad, 2);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ElecAngleIdOutput_LEN);
#else
    mavlink_elecangleidoutput_t packet;
    packet.id_tar_A = id_tar_A;
    packet.elec_bias_rad = elec_bias_rad;
    packet.state_now = state_now;
    packet.step_num = step_num;
    mav_array_memcpy(packet.elec_bias_buff_rad, elec_bias_buff_rad, sizeof(float)*2);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ElecAngleIdOutput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ElecAngleIdOutput;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_ElecAngleIdOutput_MIN_LEN, MAVLINK_MSG_ID_ElecAngleIdOutput_LEN, MAVLINK_MSG_ID_ElecAngleIdOutput_CRC);
}

/**
 * @brief Pack a elecangleidoutput message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param id_tar_A  
 * @param elec_bias_rad  
 * @param state_now  
 * @param elec_bias_buff_rad  
 * @param step_num  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_elecangleidoutput_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               float id_tar_A, float elec_bias_rad, int8_t state_now, const float *elec_bias_buff_rad, uint8_t step_num)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ElecAngleIdOutput_LEN];
    _mav_put_float(buf, 0, id_tar_A);
    _mav_put_float(buf, 4, elec_bias_rad);
    _mav_put_int8_t(buf, 16, state_now);
    _mav_put_uint8_t(buf, 17, step_num);
    _mav_put_float_array(buf, 8, elec_bias_buff_rad, 2);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ElecAngleIdOutput_LEN);
#else
    mavlink_elecangleidoutput_t packet;
    packet.id_tar_A = id_tar_A;
    packet.elec_bias_rad = elec_bias_rad;
    packet.state_now = state_now;
    packet.step_num = step_num;
    mav_array_memcpy(packet.elec_bias_buff_rad, elec_bias_buff_rad, sizeof(float)*2);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ElecAngleIdOutput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ElecAngleIdOutput;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_ElecAngleIdOutput_MIN_LEN, MAVLINK_MSG_ID_ElecAngleIdOutput_LEN, MAVLINK_MSG_ID_ElecAngleIdOutput_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_ElecAngleIdOutput_MIN_LEN, MAVLINK_MSG_ID_ElecAngleIdOutput_LEN);
#endif
}

/**
 * @brief Pack a elecangleidoutput message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param id_tar_A  
 * @param elec_bias_rad  
 * @param state_now  
 * @param elec_bias_buff_rad  
 * @param step_num  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_elecangleidoutput_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   float id_tar_A,float elec_bias_rad,int8_t state_now,const float *elec_bias_buff_rad,uint8_t step_num)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ElecAngleIdOutput_LEN];
    _mav_put_float(buf, 0, id_tar_A);
    _mav_put_float(buf, 4, elec_bias_rad);
    _mav_put_int8_t(buf, 16, state_now);
    _mav_put_uint8_t(buf, 17, step_num);
    _mav_put_float_array(buf, 8, elec_bias_buff_rad, 2);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ElecAngleIdOutput_LEN);
#else
    mavlink_elecangleidoutput_t packet;
    packet.id_tar_A = id_tar_A;
    packet.elec_bias_rad = elec_bias_rad;
    packet.state_now = state_now;
    packet.step_num = step_num;
    mav_array_memcpy(packet.elec_bias_buff_rad, elec_bias_buff_rad, sizeof(float)*2);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ElecAngleIdOutput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ElecAngleIdOutput;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_ElecAngleIdOutput_MIN_LEN, MAVLINK_MSG_ID_ElecAngleIdOutput_LEN, MAVLINK_MSG_ID_ElecAngleIdOutput_CRC);
}

/**
 * @brief Encode a elecangleidoutput struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param elecangleidoutput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_elecangleidoutput_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_elecangleidoutput_t* elecangleidoutput)
{
    return mavlink_msg_elecangleidoutput_pack(system_id, component_id, msg, elecangleidoutput->id_tar_A, elecangleidoutput->elec_bias_rad, elecangleidoutput->state_now, elecangleidoutput->elec_bias_buff_rad, elecangleidoutput->step_num);
}

/**
 * @brief Encode a elecangleidoutput struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param elecangleidoutput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_elecangleidoutput_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_elecangleidoutput_t* elecangleidoutput)
{
    return mavlink_msg_elecangleidoutput_pack_chan(system_id, component_id, chan, msg, elecangleidoutput->id_tar_A, elecangleidoutput->elec_bias_rad, elecangleidoutput->state_now, elecangleidoutput->elec_bias_buff_rad, elecangleidoutput->step_num);
}

/**
 * @brief Encode a elecangleidoutput struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param elecangleidoutput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_elecangleidoutput_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_elecangleidoutput_t* elecangleidoutput)
{
    return mavlink_msg_elecangleidoutput_pack_status(system_id, component_id, _status, msg,  elecangleidoutput->id_tar_A, elecangleidoutput->elec_bias_rad, elecangleidoutput->state_now, elecangleidoutput->elec_bias_buff_rad, elecangleidoutput->step_num);
}

/**
 * @brief Send a elecangleidoutput message
 * @param chan MAVLink channel to send the message
 *
 * @param id_tar_A  
 * @param elec_bias_rad  
 * @param state_now  
 * @param elec_bias_buff_rad  
 * @param step_num  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_elecangleidoutput_send(mavlink_channel_t chan, float id_tar_A, float elec_bias_rad, int8_t state_now, const float *elec_bias_buff_rad, uint8_t step_num)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ElecAngleIdOutput_LEN];
    _mav_put_float(buf, 0, id_tar_A);
    _mav_put_float(buf, 4, elec_bias_rad);
    _mav_put_int8_t(buf, 16, state_now);
    _mav_put_uint8_t(buf, 17, step_num);
    _mav_put_float_array(buf, 8, elec_bias_buff_rad, 2);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ElecAngleIdOutput, buf, MAVLINK_MSG_ID_ElecAngleIdOutput_MIN_LEN, MAVLINK_MSG_ID_ElecAngleIdOutput_LEN, MAVLINK_MSG_ID_ElecAngleIdOutput_CRC);
#else
    mavlink_elecangleidoutput_t packet;
    packet.id_tar_A = id_tar_A;
    packet.elec_bias_rad = elec_bias_rad;
    packet.state_now = state_now;
    packet.step_num = step_num;
    mav_array_memcpy(packet.elec_bias_buff_rad, elec_bias_buff_rad, sizeof(float)*2);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ElecAngleIdOutput, (const char *)&packet, MAVLINK_MSG_ID_ElecAngleIdOutput_MIN_LEN, MAVLINK_MSG_ID_ElecAngleIdOutput_LEN, MAVLINK_MSG_ID_ElecAngleIdOutput_CRC);
#endif
}

/**
 * @brief Send a elecangleidoutput message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_elecangleidoutput_send_struct(mavlink_channel_t chan, const mavlink_elecangleidoutput_t* elecangleidoutput)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_elecangleidoutput_send(chan, elecangleidoutput->id_tar_A, elecangleidoutput->elec_bias_rad, elecangleidoutput->state_now, elecangleidoutput->elec_bias_buff_rad, elecangleidoutput->step_num);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ElecAngleIdOutput, (const char *)elecangleidoutput, MAVLINK_MSG_ID_ElecAngleIdOutput_MIN_LEN, MAVLINK_MSG_ID_ElecAngleIdOutput_LEN, MAVLINK_MSG_ID_ElecAngleIdOutput_CRC);
#endif
}

#if MAVLINK_MSG_ID_ElecAngleIdOutput_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_elecangleidoutput_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float id_tar_A, float elec_bias_rad, int8_t state_now, const float *elec_bias_buff_rad, uint8_t step_num)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, id_tar_A);
    _mav_put_float(buf, 4, elec_bias_rad);
    _mav_put_int8_t(buf, 16, state_now);
    _mav_put_uint8_t(buf, 17, step_num);
    _mav_put_float_array(buf, 8, elec_bias_buff_rad, 2);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ElecAngleIdOutput, buf, MAVLINK_MSG_ID_ElecAngleIdOutput_MIN_LEN, MAVLINK_MSG_ID_ElecAngleIdOutput_LEN, MAVLINK_MSG_ID_ElecAngleIdOutput_CRC);
#else
    mavlink_elecangleidoutput_t *packet = (mavlink_elecangleidoutput_t *)msgbuf;
    packet->id_tar_A = id_tar_A;
    packet->elec_bias_rad = elec_bias_rad;
    packet->state_now = state_now;
    packet->step_num = step_num;
    mav_array_memcpy(packet->elec_bias_buff_rad, elec_bias_buff_rad, sizeof(float)*2);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ElecAngleIdOutput, (const char *)packet, MAVLINK_MSG_ID_ElecAngleIdOutput_MIN_LEN, MAVLINK_MSG_ID_ElecAngleIdOutput_LEN, MAVLINK_MSG_ID_ElecAngleIdOutput_CRC);
#endif
}
#endif

#endif

// MESSAGE ElecAngleIdOutput UNPACKING


/**
 * @brief Get field id_tar_A from elecangleidoutput message
 *
 * @return  
 */
static inline float mavlink_msg_elecangleidoutput_get_id_tar_A(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field elec_bias_rad from elecangleidoutput message
 *
 * @return  
 */
static inline float mavlink_msg_elecangleidoutput_get_elec_bias_rad(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field state_now from elecangleidoutput message
 *
 * @return  
 */
static inline int8_t mavlink_msg_elecangleidoutput_get_state_now(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int8_t(msg,  16);
}

/**
 * @brief Get field elec_bias_buff_rad from elecangleidoutput message
 *
 * @return  
 */
static inline uint16_t mavlink_msg_elecangleidoutput_get_elec_bias_buff_rad(const mavlink_message_t* msg, float *elec_bias_buff_rad)
{
    return _MAV_RETURN_float_array(msg, elec_bias_buff_rad, 2,  8);
}

/**
 * @brief Get field step_num from elecangleidoutput message
 *
 * @return  
 */
static inline uint8_t mavlink_msg_elecangleidoutput_get_step_num(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  17);
}

/**
 * @brief Decode a elecangleidoutput message into a struct
 *
 * @param msg The message to decode
 * @param elecangleidoutput C-struct to decode the message contents into
 */
static inline void mavlink_msg_elecangleidoutput_decode(const mavlink_message_t* msg, mavlink_elecangleidoutput_t* elecangleidoutput)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    elecangleidoutput->id_tar_A = mavlink_msg_elecangleidoutput_get_id_tar_A(msg);
    elecangleidoutput->elec_bias_rad = mavlink_msg_elecangleidoutput_get_elec_bias_rad(msg);
    mavlink_msg_elecangleidoutput_get_elec_bias_buff_rad(msg, elecangleidoutput->elec_bias_buff_rad);
    elecangleidoutput->state_now = mavlink_msg_elecangleidoutput_get_state_now(msg);
    elecangleidoutput->step_num = mavlink_msg_elecangleidoutput_get_step_num(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_ElecAngleIdOutput_LEN? msg->len : MAVLINK_MSG_ID_ElecAngleIdOutput_LEN;
        memset(elecangleidoutput, 0, MAVLINK_MSG_ID_ElecAngleIdOutput_LEN);
    memcpy(elecangleidoutput, _MAV_PAYLOAD(msg), len);
#endif
}
