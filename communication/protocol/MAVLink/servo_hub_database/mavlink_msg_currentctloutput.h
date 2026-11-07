#pragma once
// MESSAGE CurrentCtlOutput PACKING

#define MAVLINK_MSG_ID_CurrentCtlOutput 30027


typedef struct __mavlink_currentctloutput_t {
 float uabc_tar_comp_V[3]; /*<  */
 float idq_now_A[2]; /*<  */
 float uabc_tar_org_V[3]; /*<  */
} mavlink_currentctloutput_t;

#define MAVLINK_MSG_ID_CurrentCtlOutput_LEN 32
#define MAVLINK_MSG_ID_CurrentCtlOutput_MIN_LEN 32
#define MAVLINK_MSG_ID_30027_LEN 32
#define MAVLINK_MSG_ID_30027_MIN_LEN 32

#define MAVLINK_MSG_ID_CurrentCtlOutput_CRC 58
#define MAVLINK_MSG_ID_30027_CRC 58

#define MAVLINK_MSG_CurrentCtlOutput_FIELD_UABC_TAR_COMP_V_LEN 3
#define MAVLINK_MSG_CurrentCtlOutput_FIELD_IDQ_NOW_A_LEN 2
#define MAVLINK_MSG_CurrentCtlOutput_FIELD_UABC_TAR_ORG_V_LEN 3

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_CurrentCtlOutput { \
    30027, \
    "CurrentCtlOutput", \
    3, \
    {  { "uabc_tar_comp_V", NULL, MAVLINK_TYPE_FLOAT, 3, 0, offsetof(mavlink_currentctloutput_t, uabc_tar_comp_V) }, \
         { "idq_now_A", NULL, MAVLINK_TYPE_FLOAT, 2, 12, offsetof(mavlink_currentctloutput_t, idq_now_A) }, \
         { "uabc_tar_org_V", NULL, MAVLINK_TYPE_FLOAT, 3, 20, offsetof(mavlink_currentctloutput_t, uabc_tar_org_V) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_CurrentCtlOutput { \
    "CurrentCtlOutput", \
    3, \
    {  { "uabc_tar_comp_V", NULL, MAVLINK_TYPE_FLOAT, 3, 0, offsetof(mavlink_currentctloutput_t, uabc_tar_comp_V) }, \
         { "idq_now_A", NULL, MAVLINK_TYPE_FLOAT, 2, 12, offsetof(mavlink_currentctloutput_t, idq_now_A) }, \
         { "uabc_tar_org_V", NULL, MAVLINK_TYPE_FLOAT, 3, 20, offsetof(mavlink_currentctloutput_t, uabc_tar_org_V) }, \
         } \
}
#endif

/**
 * @brief Pack a currentctloutput message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param uabc_tar_comp_V  
 * @param idq_now_A  
 * @param uabc_tar_org_V  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_currentctloutput_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               const float *uabc_tar_comp_V, const float *idq_now_A, const float *uabc_tar_org_V)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_CurrentCtlOutput_LEN];

    _mav_put_float_array(buf, 0, uabc_tar_comp_V, 3);
    _mav_put_float_array(buf, 12, idq_now_A, 2);
    _mav_put_float_array(buf, 20, uabc_tar_org_V, 3);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_CurrentCtlOutput_LEN);
#else
    mavlink_currentctloutput_t packet;

    mav_array_memcpy(packet.uabc_tar_comp_V, uabc_tar_comp_V, sizeof(float)*3);
    mav_array_memcpy(packet.idq_now_A, idq_now_A, sizeof(float)*2);
    mav_array_memcpy(packet.uabc_tar_org_V, uabc_tar_org_V, sizeof(float)*3);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_CurrentCtlOutput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_CurrentCtlOutput;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_CurrentCtlOutput_MIN_LEN, MAVLINK_MSG_ID_CurrentCtlOutput_LEN, MAVLINK_MSG_ID_CurrentCtlOutput_CRC);
}

/**
 * @brief Pack a currentctloutput message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param uabc_tar_comp_V  
 * @param idq_now_A  
 * @param uabc_tar_org_V  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_currentctloutput_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               const float *uabc_tar_comp_V, const float *idq_now_A, const float *uabc_tar_org_V)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_CurrentCtlOutput_LEN];

    _mav_put_float_array(buf, 0, uabc_tar_comp_V, 3);
    _mav_put_float_array(buf, 12, idq_now_A, 2);
    _mav_put_float_array(buf, 20, uabc_tar_org_V, 3);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_CurrentCtlOutput_LEN);
#else
    mavlink_currentctloutput_t packet;

    mav_array_memcpy(packet.uabc_tar_comp_V, uabc_tar_comp_V, sizeof(float)*3);
    mav_array_memcpy(packet.idq_now_A, idq_now_A, sizeof(float)*2);
    mav_array_memcpy(packet.uabc_tar_org_V, uabc_tar_org_V, sizeof(float)*3);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_CurrentCtlOutput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_CurrentCtlOutput;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_CurrentCtlOutput_MIN_LEN, MAVLINK_MSG_ID_CurrentCtlOutput_LEN, MAVLINK_MSG_ID_CurrentCtlOutput_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_CurrentCtlOutput_MIN_LEN, MAVLINK_MSG_ID_CurrentCtlOutput_LEN);
#endif
}

/**
 * @brief Pack a currentctloutput message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param uabc_tar_comp_V  
 * @param idq_now_A  
 * @param uabc_tar_org_V  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_currentctloutput_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   const float *uabc_tar_comp_V,const float *idq_now_A,const float *uabc_tar_org_V)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_CurrentCtlOutput_LEN];

    _mav_put_float_array(buf, 0, uabc_tar_comp_V, 3);
    _mav_put_float_array(buf, 12, idq_now_A, 2);
    _mav_put_float_array(buf, 20, uabc_tar_org_V, 3);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_CurrentCtlOutput_LEN);
#else
    mavlink_currentctloutput_t packet;

    mav_array_memcpy(packet.uabc_tar_comp_V, uabc_tar_comp_V, sizeof(float)*3);
    mav_array_memcpy(packet.idq_now_A, idq_now_A, sizeof(float)*2);
    mav_array_memcpy(packet.uabc_tar_org_V, uabc_tar_org_V, sizeof(float)*3);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_CurrentCtlOutput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_CurrentCtlOutput;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_CurrentCtlOutput_MIN_LEN, MAVLINK_MSG_ID_CurrentCtlOutput_LEN, MAVLINK_MSG_ID_CurrentCtlOutput_CRC);
}

/**
 * @brief Encode a currentctloutput struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param currentctloutput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_currentctloutput_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_currentctloutput_t* currentctloutput)
{
    return mavlink_msg_currentctloutput_pack(system_id, component_id, msg, currentctloutput->uabc_tar_comp_V, currentctloutput->idq_now_A, currentctloutput->uabc_tar_org_V);
}

/**
 * @brief Encode a currentctloutput struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param currentctloutput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_currentctloutput_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_currentctloutput_t* currentctloutput)
{
    return mavlink_msg_currentctloutput_pack_chan(system_id, component_id, chan, msg, currentctloutput->uabc_tar_comp_V, currentctloutput->idq_now_A, currentctloutput->uabc_tar_org_V);
}

/**
 * @brief Encode a currentctloutput struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param currentctloutput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_currentctloutput_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_currentctloutput_t* currentctloutput)
{
    return mavlink_msg_currentctloutput_pack_status(system_id, component_id, _status, msg,  currentctloutput->uabc_tar_comp_V, currentctloutput->idq_now_A, currentctloutput->uabc_tar_org_V);
}

/**
 * @brief Send a currentctloutput message
 * @param chan MAVLink channel to send the message
 *
 * @param uabc_tar_comp_V  
 * @param idq_now_A  
 * @param uabc_tar_org_V  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_currentctloutput_send(mavlink_channel_t chan, const float *uabc_tar_comp_V, const float *idq_now_A, const float *uabc_tar_org_V)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_CurrentCtlOutput_LEN];

    _mav_put_float_array(buf, 0, uabc_tar_comp_V, 3);
    _mav_put_float_array(buf, 12, idq_now_A, 2);
    _mav_put_float_array(buf, 20, uabc_tar_org_V, 3);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CurrentCtlOutput, buf, MAVLINK_MSG_ID_CurrentCtlOutput_MIN_LEN, MAVLINK_MSG_ID_CurrentCtlOutput_LEN, MAVLINK_MSG_ID_CurrentCtlOutput_CRC);
#else
    mavlink_currentctloutput_t packet;

    mav_array_memcpy(packet.uabc_tar_comp_V, uabc_tar_comp_V, sizeof(float)*3);
    mav_array_memcpy(packet.idq_now_A, idq_now_A, sizeof(float)*2);
    mav_array_memcpy(packet.uabc_tar_org_V, uabc_tar_org_V, sizeof(float)*3);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CurrentCtlOutput, (const char *)&packet, MAVLINK_MSG_ID_CurrentCtlOutput_MIN_LEN, MAVLINK_MSG_ID_CurrentCtlOutput_LEN, MAVLINK_MSG_ID_CurrentCtlOutput_CRC);
#endif
}

/**
 * @brief Send a currentctloutput message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_currentctloutput_send_struct(mavlink_channel_t chan, const mavlink_currentctloutput_t* currentctloutput)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_currentctloutput_send(chan, currentctloutput->uabc_tar_comp_V, currentctloutput->idq_now_A, currentctloutput->uabc_tar_org_V);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CurrentCtlOutput, (const char *)currentctloutput, MAVLINK_MSG_ID_CurrentCtlOutput_MIN_LEN, MAVLINK_MSG_ID_CurrentCtlOutput_LEN, MAVLINK_MSG_ID_CurrentCtlOutput_CRC);
#endif
}

#if MAVLINK_MSG_ID_CurrentCtlOutput_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_currentctloutput_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  const float *uabc_tar_comp_V, const float *idq_now_A, const float *uabc_tar_org_V)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;

    _mav_put_float_array(buf, 0, uabc_tar_comp_V, 3);
    _mav_put_float_array(buf, 12, idq_now_A, 2);
    _mav_put_float_array(buf, 20, uabc_tar_org_V, 3);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CurrentCtlOutput, buf, MAVLINK_MSG_ID_CurrentCtlOutput_MIN_LEN, MAVLINK_MSG_ID_CurrentCtlOutput_LEN, MAVLINK_MSG_ID_CurrentCtlOutput_CRC);
#else
    mavlink_currentctloutput_t *packet = (mavlink_currentctloutput_t *)msgbuf;

    mav_array_memcpy(packet->uabc_tar_comp_V, uabc_tar_comp_V, sizeof(float)*3);
    mav_array_memcpy(packet->idq_now_A, idq_now_A, sizeof(float)*2);
    mav_array_memcpy(packet->uabc_tar_org_V, uabc_tar_org_V, sizeof(float)*3);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CurrentCtlOutput, (const char *)packet, MAVLINK_MSG_ID_CurrentCtlOutput_MIN_LEN, MAVLINK_MSG_ID_CurrentCtlOutput_LEN, MAVLINK_MSG_ID_CurrentCtlOutput_CRC);
#endif
}
#endif

#endif

// MESSAGE CurrentCtlOutput UNPACKING


/**
 * @brief Get field uabc_tar_comp_V from currentctloutput message
 *
 * @return  
 */
static inline uint16_t mavlink_msg_currentctloutput_get_uabc_tar_comp_V(const mavlink_message_t* msg, float *uabc_tar_comp_V)
{
    return _MAV_RETURN_float_array(msg, uabc_tar_comp_V, 3,  0);
}

/**
 * @brief Get field idq_now_A from currentctloutput message
 *
 * @return  
 */
static inline uint16_t mavlink_msg_currentctloutput_get_idq_now_A(const mavlink_message_t* msg, float *idq_now_A)
{
    return _MAV_RETURN_float_array(msg, idq_now_A, 2,  12);
}

/**
 * @brief Get field uabc_tar_org_V from currentctloutput message
 *
 * @return  
 */
static inline uint16_t mavlink_msg_currentctloutput_get_uabc_tar_org_V(const mavlink_message_t* msg, float *uabc_tar_org_V)
{
    return _MAV_RETURN_float_array(msg, uabc_tar_org_V, 3,  20);
}

/**
 * @brief Decode a currentctloutput message into a struct
 *
 * @param msg The message to decode
 * @param currentctloutput C-struct to decode the message contents into
 */
static inline void mavlink_msg_currentctloutput_decode(const mavlink_message_t* msg, mavlink_currentctloutput_t* currentctloutput)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_currentctloutput_get_uabc_tar_comp_V(msg, currentctloutput->uabc_tar_comp_V);
    mavlink_msg_currentctloutput_get_idq_now_A(msg, currentctloutput->idq_now_A);
    mavlink_msg_currentctloutput_get_uabc_tar_org_V(msg, currentctloutput->uabc_tar_org_V);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_CurrentCtlOutput_LEN? msg->len : MAVLINK_MSG_ID_CurrentCtlOutput_LEN;
        memset(currentctloutput, 0, MAVLINK_MSG_ID_CurrentCtlOutput_LEN);
    memcpy(currentctloutput, _MAV_PAYLOAD(msg), len);
#endif
}
