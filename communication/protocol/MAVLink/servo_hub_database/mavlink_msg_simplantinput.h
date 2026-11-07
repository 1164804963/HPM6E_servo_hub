#pragma once
// MESSAGE SimPlantInput PACKING

#define MAVLINK_MSG_ID_SimPlantInput 30079


typedef struct __mavlink_simplantinput_t {
 float uabc_tar_V[3]; /*<  */
 float tl_Nm; /*<  */
} mavlink_simplantinput_t;

#define MAVLINK_MSG_ID_SimPlantInput_LEN 16
#define MAVLINK_MSG_ID_SimPlantInput_MIN_LEN 16
#define MAVLINK_MSG_ID_30079_LEN 16
#define MAVLINK_MSG_ID_30079_MIN_LEN 16

#define MAVLINK_MSG_ID_SimPlantInput_CRC 79
#define MAVLINK_MSG_ID_30079_CRC 79

#define MAVLINK_MSG_SimPlantInput_FIELD_UABC_TAR_V_LEN 3

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_SimPlantInput { \
    30079, \
    "SimPlantInput", \
    2, \
    {  { "uabc_tar_V", NULL, MAVLINK_TYPE_FLOAT, 3, 0, offsetof(mavlink_simplantinput_t, uabc_tar_V) }, \
         { "tl_Nm", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_simplantinput_t, tl_Nm) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_SimPlantInput { \
    "SimPlantInput", \
    2, \
    {  { "uabc_tar_V", NULL, MAVLINK_TYPE_FLOAT, 3, 0, offsetof(mavlink_simplantinput_t, uabc_tar_V) }, \
         { "tl_Nm", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_simplantinput_t, tl_Nm) }, \
         } \
}
#endif

/**
 * @brief Pack a simplantinput message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param uabc_tar_V  
 * @param tl_Nm  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_simplantinput_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               const float *uabc_tar_V, float tl_Nm)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SimPlantInput_LEN];
    _mav_put_float(buf, 12, tl_Nm);
    _mav_put_float_array(buf, 0, uabc_tar_V, 3);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SimPlantInput_LEN);
#else
    mavlink_simplantinput_t packet;
    packet.tl_Nm = tl_Nm;
    mav_array_memcpy(packet.uabc_tar_V, uabc_tar_V, sizeof(float)*3);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SimPlantInput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SimPlantInput;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_SimPlantInput_MIN_LEN, MAVLINK_MSG_ID_SimPlantInput_LEN, MAVLINK_MSG_ID_SimPlantInput_CRC);
}

/**
 * @brief Pack a simplantinput message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param uabc_tar_V  
 * @param tl_Nm  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_simplantinput_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               const float *uabc_tar_V, float tl_Nm)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SimPlantInput_LEN];
    _mav_put_float(buf, 12, tl_Nm);
    _mav_put_float_array(buf, 0, uabc_tar_V, 3);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SimPlantInput_LEN);
#else
    mavlink_simplantinput_t packet;
    packet.tl_Nm = tl_Nm;
    mav_array_memcpy(packet.uabc_tar_V, uabc_tar_V, sizeof(float)*3);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SimPlantInput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SimPlantInput;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_SimPlantInput_MIN_LEN, MAVLINK_MSG_ID_SimPlantInput_LEN, MAVLINK_MSG_ID_SimPlantInput_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_SimPlantInput_MIN_LEN, MAVLINK_MSG_ID_SimPlantInput_LEN);
#endif
}

/**
 * @brief Pack a simplantinput message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param uabc_tar_V  
 * @param tl_Nm  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_simplantinput_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   const float *uabc_tar_V,float tl_Nm)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SimPlantInput_LEN];
    _mav_put_float(buf, 12, tl_Nm);
    _mav_put_float_array(buf, 0, uabc_tar_V, 3);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SimPlantInput_LEN);
#else
    mavlink_simplantinput_t packet;
    packet.tl_Nm = tl_Nm;
    mav_array_memcpy(packet.uabc_tar_V, uabc_tar_V, sizeof(float)*3);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SimPlantInput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SimPlantInput;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_SimPlantInput_MIN_LEN, MAVLINK_MSG_ID_SimPlantInput_LEN, MAVLINK_MSG_ID_SimPlantInput_CRC);
}

/**
 * @brief Encode a simplantinput struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param simplantinput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_simplantinput_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_simplantinput_t* simplantinput)
{
    return mavlink_msg_simplantinput_pack(system_id, component_id, msg, simplantinput->uabc_tar_V, simplantinput->tl_Nm);
}

/**
 * @brief Encode a simplantinput struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param simplantinput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_simplantinput_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_simplantinput_t* simplantinput)
{
    return mavlink_msg_simplantinput_pack_chan(system_id, component_id, chan, msg, simplantinput->uabc_tar_V, simplantinput->tl_Nm);
}

/**
 * @brief Encode a simplantinput struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param simplantinput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_simplantinput_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_simplantinput_t* simplantinput)
{
    return mavlink_msg_simplantinput_pack_status(system_id, component_id, _status, msg,  simplantinput->uabc_tar_V, simplantinput->tl_Nm);
}

/**
 * @brief Send a simplantinput message
 * @param chan MAVLink channel to send the message
 *
 * @param uabc_tar_V  
 * @param tl_Nm  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_simplantinput_send(mavlink_channel_t chan, const float *uabc_tar_V, float tl_Nm)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SimPlantInput_LEN];
    _mav_put_float(buf, 12, tl_Nm);
    _mav_put_float_array(buf, 0, uabc_tar_V, 3);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SimPlantInput, buf, MAVLINK_MSG_ID_SimPlantInput_MIN_LEN, MAVLINK_MSG_ID_SimPlantInput_LEN, MAVLINK_MSG_ID_SimPlantInput_CRC);
#else
    mavlink_simplantinput_t packet;
    packet.tl_Nm = tl_Nm;
    mav_array_memcpy(packet.uabc_tar_V, uabc_tar_V, sizeof(float)*3);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SimPlantInput, (const char *)&packet, MAVLINK_MSG_ID_SimPlantInput_MIN_LEN, MAVLINK_MSG_ID_SimPlantInput_LEN, MAVLINK_MSG_ID_SimPlantInput_CRC);
#endif
}

/**
 * @brief Send a simplantinput message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_simplantinput_send_struct(mavlink_channel_t chan, const mavlink_simplantinput_t* simplantinput)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_simplantinput_send(chan, simplantinput->uabc_tar_V, simplantinput->tl_Nm);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SimPlantInput, (const char *)simplantinput, MAVLINK_MSG_ID_SimPlantInput_MIN_LEN, MAVLINK_MSG_ID_SimPlantInput_LEN, MAVLINK_MSG_ID_SimPlantInput_CRC);
#endif
}

#if MAVLINK_MSG_ID_SimPlantInput_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_simplantinput_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  const float *uabc_tar_V, float tl_Nm)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 12, tl_Nm);
    _mav_put_float_array(buf, 0, uabc_tar_V, 3);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SimPlantInput, buf, MAVLINK_MSG_ID_SimPlantInput_MIN_LEN, MAVLINK_MSG_ID_SimPlantInput_LEN, MAVLINK_MSG_ID_SimPlantInput_CRC);
#else
    mavlink_simplantinput_t *packet = (mavlink_simplantinput_t *)msgbuf;
    packet->tl_Nm = tl_Nm;
    mav_array_memcpy(packet->uabc_tar_V, uabc_tar_V, sizeof(float)*3);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SimPlantInput, (const char *)packet, MAVLINK_MSG_ID_SimPlantInput_MIN_LEN, MAVLINK_MSG_ID_SimPlantInput_LEN, MAVLINK_MSG_ID_SimPlantInput_CRC);
#endif
}
#endif

#endif

// MESSAGE SimPlantInput UNPACKING


/**
 * @brief Get field uabc_tar_V from simplantinput message
 *
 * @return  
 */
static inline uint16_t mavlink_msg_simplantinput_get_uabc_tar_V(const mavlink_message_t* msg, float *uabc_tar_V)
{
    return _MAV_RETURN_float_array(msg, uabc_tar_V, 3,  0);
}

/**
 * @brief Get field tl_Nm from simplantinput message
 *
 * @return  
 */
static inline float mavlink_msg_simplantinput_get_tl_Nm(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Decode a simplantinput message into a struct
 *
 * @param msg The message to decode
 * @param simplantinput C-struct to decode the message contents into
 */
static inline void mavlink_msg_simplantinput_decode(const mavlink_message_t* msg, mavlink_simplantinput_t* simplantinput)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_simplantinput_get_uabc_tar_V(msg, simplantinput->uabc_tar_V);
    simplantinput->tl_Nm = mavlink_msg_simplantinput_get_tl_Nm(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_SimPlantInput_LEN? msg->len : MAVLINK_MSG_ID_SimPlantInput_LEN;
        memset(simplantinput, 0, MAVLINK_MSG_ID_SimPlantInput_LEN);
    memcpy(simplantinput, _MAV_PAYLOAD(msg), len);
#endif
}
