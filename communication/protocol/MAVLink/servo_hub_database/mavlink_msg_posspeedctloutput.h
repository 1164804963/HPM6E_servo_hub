#pragma once
// MESSAGE PosSpeedCtlOutput PACKING

#define MAVLINK_MSG_ID_PosSpeedCtlOutput 30020


typedef struct __mavlink_posspeedctloutput_t {
 float iq_tar_A; /*<  */
 int32_t pos_ctl_error_p; /*<  */
 float dob_iq_com_A; /*<  */
} mavlink_posspeedctloutput_t;

#define MAVLINK_MSG_ID_PosSpeedCtlOutput_LEN 12
#define MAVLINK_MSG_ID_PosSpeedCtlOutput_MIN_LEN 12
#define MAVLINK_MSG_ID_30020_LEN 12
#define MAVLINK_MSG_ID_30020_MIN_LEN 12

#define MAVLINK_MSG_ID_PosSpeedCtlOutput_CRC 51
#define MAVLINK_MSG_ID_30020_CRC 51



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_PosSpeedCtlOutput { \
    30020, \
    "PosSpeedCtlOutput", \
    3, \
    {  { "iq_tar_A", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_posspeedctloutput_t, iq_tar_A) }, \
         { "pos_ctl_error_p", NULL, MAVLINK_TYPE_INT32_T, 0, 4, offsetof(mavlink_posspeedctloutput_t, pos_ctl_error_p) }, \
         { "dob_iq_com_A", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_posspeedctloutput_t, dob_iq_com_A) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_PosSpeedCtlOutput { \
    "PosSpeedCtlOutput", \
    3, \
    {  { "iq_tar_A", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_posspeedctloutput_t, iq_tar_A) }, \
         { "pos_ctl_error_p", NULL, MAVLINK_TYPE_INT32_T, 0, 4, offsetof(mavlink_posspeedctloutput_t, pos_ctl_error_p) }, \
         { "dob_iq_com_A", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_posspeedctloutput_t, dob_iq_com_A) }, \
         } \
}
#endif

/**
 * @brief Pack a posspeedctloutput message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param iq_tar_A  
 * @param pos_ctl_error_p  
 * @param dob_iq_com_A  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_posspeedctloutput_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               float iq_tar_A, int32_t pos_ctl_error_p, float dob_iq_com_A)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PosSpeedCtlOutput_LEN];
    _mav_put_float(buf, 0, iq_tar_A);
    _mav_put_int32_t(buf, 4, pos_ctl_error_p);
    _mav_put_float(buf, 8, dob_iq_com_A);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_PosSpeedCtlOutput_LEN);
#else
    mavlink_posspeedctloutput_t packet;
    packet.iq_tar_A = iq_tar_A;
    packet.pos_ctl_error_p = pos_ctl_error_p;
    packet.dob_iq_com_A = dob_iq_com_A;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_PosSpeedCtlOutput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_PosSpeedCtlOutput;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_PosSpeedCtlOutput_MIN_LEN, MAVLINK_MSG_ID_PosSpeedCtlOutput_LEN, MAVLINK_MSG_ID_PosSpeedCtlOutput_CRC);
}

/**
 * @brief Pack a posspeedctloutput message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param iq_tar_A  
 * @param pos_ctl_error_p  
 * @param dob_iq_com_A  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_posspeedctloutput_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               float iq_tar_A, int32_t pos_ctl_error_p, float dob_iq_com_A)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PosSpeedCtlOutput_LEN];
    _mav_put_float(buf, 0, iq_tar_A);
    _mav_put_int32_t(buf, 4, pos_ctl_error_p);
    _mav_put_float(buf, 8, dob_iq_com_A);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_PosSpeedCtlOutput_LEN);
#else
    mavlink_posspeedctloutput_t packet;
    packet.iq_tar_A = iq_tar_A;
    packet.pos_ctl_error_p = pos_ctl_error_p;
    packet.dob_iq_com_A = dob_iq_com_A;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_PosSpeedCtlOutput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_PosSpeedCtlOutput;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_PosSpeedCtlOutput_MIN_LEN, MAVLINK_MSG_ID_PosSpeedCtlOutput_LEN, MAVLINK_MSG_ID_PosSpeedCtlOutput_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_PosSpeedCtlOutput_MIN_LEN, MAVLINK_MSG_ID_PosSpeedCtlOutput_LEN);
#endif
}

/**
 * @brief Pack a posspeedctloutput message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param iq_tar_A  
 * @param pos_ctl_error_p  
 * @param dob_iq_com_A  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_posspeedctloutput_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   float iq_tar_A,int32_t pos_ctl_error_p,float dob_iq_com_A)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PosSpeedCtlOutput_LEN];
    _mav_put_float(buf, 0, iq_tar_A);
    _mav_put_int32_t(buf, 4, pos_ctl_error_p);
    _mav_put_float(buf, 8, dob_iq_com_A);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_PosSpeedCtlOutput_LEN);
#else
    mavlink_posspeedctloutput_t packet;
    packet.iq_tar_A = iq_tar_A;
    packet.pos_ctl_error_p = pos_ctl_error_p;
    packet.dob_iq_com_A = dob_iq_com_A;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_PosSpeedCtlOutput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_PosSpeedCtlOutput;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_PosSpeedCtlOutput_MIN_LEN, MAVLINK_MSG_ID_PosSpeedCtlOutput_LEN, MAVLINK_MSG_ID_PosSpeedCtlOutput_CRC);
}

/**
 * @brief Encode a posspeedctloutput struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param posspeedctloutput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_posspeedctloutput_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_posspeedctloutput_t* posspeedctloutput)
{
    return mavlink_msg_posspeedctloutput_pack(system_id, component_id, msg, posspeedctloutput->iq_tar_A, posspeedctloutput->pos_ctl_error_p, posspeedctloutput->dob_iq_com_A);
}

/**
 * @brief Encode a posspeedctloutput struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param posspeedctloutput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_posspeedctloutput_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_posspeedctloutput_t* posspeedctloutput)
{
    return mavlink_msg_posspeedctloutput_pack_chan(system_id, component_id, chan, msg, posspeedctloutput->iq_tar_A, posspeedctloutput->pos_ctl_error_p, posspeedctloutput->dob_iq_com_A);
}

/**
 * @brief Encode a posspeedctloutput struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param posspeedctloutput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_posspeedctloutput_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_posspeedctloutput_t* posspeedctloutput)
{
    return mavlink_msg_posspeedctloutput_pack_status(system_id, component_id, _status, msg,  posspeedctloutput->iq_tar_A, posspeedctloutput->pos_ctl_error_p, posspeedctloutput->dob_iq_com_A);
}

/**
 * @brief Send a posspeedctloutput message
 * @param chan MAVLink channel to send the message
 *
 * @param iq_tar_A  
 * @param pos_ctl_error_p  
 * @param dob_iq_com_A  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_posspeedctloutput_send(mavlink_channel_t chan, float iq_tar_A, int32_t pos_ctl_error_p, float dob_iq_com_A)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PosSpeedCtlOutput_LEN];
    _mav_put_float(buf, 0, iq_tar_A);
    _mav_put_int32_t(buf, 4, pos_ctl_error_p);
    _mav_put_float(buf, 8, dob_iq_com_A);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PosSpeedCtlOutput, buf, MAVLINK_MSG_ID_PosSpeedCtlOutput_MIN_LEN, MAVLINK_MSG_ID_PosSpeedCtlOutput_LEN, MAVLINK_MSG_ID_PosSpeedCtlOutput_CRC);
#else
    mavlink_posspeedctloutput_t packet;
    packet.iq_tar_A = iq_tar_A;
    packet.pos_ctl_error_p = pos_ctl_error_p;
    packet.dob_iq_com_A = dob_iq_com_A;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PosSpeedCtlOutput, (const char *)&packet, MAVLINK_MSG_ID_PosSpeedCtlOutput_MIN_LEN, MAVLINK_MSG_ID_PosSpeedCtlOutput_LEN, MAVLINK_MSG_ID_PosSpeedCtlOutput_CRC);
#endif
}

/**
 * @brief Send a posspeedctloutput message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_posspeedctloutput_send_struct(mavlink_channel_t chan, const mavlink_posspeedctloutput_t* posspeedctloutput)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_posspeedctloutput_send(chan, posspeedctloutput->iq_tar_A, posspeedctloutput->pos_ctl_error_p, posspeedctloutput->dob_iq_com_A);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PosSpeedCtlOutput, (const char *)posspeedctloutput, MAVLINK_MSG_ID_PosSpeedCtlOutput_MIN_LEN, MAVLINK_MSG_ID_PosSpeedCtlOutput_LEN, MAVLINK_MSG_ID_PosSpeedCtlOutput_CRC);
#endif
}

#if MAVLINK_MSG_ID_PosSpeedCtlOutput_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_posspeedctloutput_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float iq_tar_A, int32_t pos_ctl_error_p, float dob_iq_com_A)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, iq_tar_A);
    _mav_put_int32_t(buf, 4, pos_ctl_error_p);
    _mav_put_float(buf, 8, dob_iq_com_A);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PosSpeedCtlOutput, buf, MAVLINK_MSG_ID_PosSpeedCtlOutput_MIN_LEN, MAVLINK_MSG_ID_PosSpeedCtlOutput_LEN, MAVLINK_MSG_ID_PosSpeedCtlOutput_CRC);
#else
    mavlink_posspeedctloutput_t *packet = (mavlink_posspeedctloutput_t *)msgbuf;
    packet->iq_tar_A = iq_tar_A;
    packet->pos_ctl_error_p = pos_ctl_error_p;
    packet->dob_iq_com_A = dob_iq_com_A;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PosSpeedCtlOutput, (const char *)packet, MAVLINK_MSG_ID_PosSpeedCtlOutput_MIN_LEN, MAVLINK_MSG_ID_PosSpeedCtlOutput_LEN, MAVLINK_MSG_ID_PosSpeedCtlOutput_CRC);
#endif
}
#endif

#endif

// MESSAGE PosSpeedCtlOutput UNPACKING


/**
 * @brief Get field iq_tar_A from posspeedctloutput message
 *
 * @return  
 */
static inline float mavlink_msg_posspeedctloutput_get_iq_tar_A(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field pos_ctl_error_p from posspeedctloutput message
 *
 * @return  
 */
static inline int32_t mavlink_msg_posspeedctloutput_get_pos_ctl_error_p(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  4);
}

/**
 * @brief Get field dob_iq_com_A from posspeedctloutput message
 *
 * @return  
 */
static inline float mavlink_msg_posspeedctloutput_get_dob_iq_com_A(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Decode a posspeedctloutput message into a struct
 *
 * @param msg The message to decode
 * @param posspeedctloutput C-struct to decode the message contents into
 */
static inline void mavlink_msg_posspeedctloutput_decode(const mavlink_message_t* msg, mavlink_posspeedctloutput_t* posspeedctloutput)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    posspeedctloutput->iq_tar_A = mavlink_msg_posspeedctloutput_get_iq_tar_A(msg);
    posspeedctloutput->pos_ctl_error_p = mavlink_msg_posspeedctloutput_get_pos_ctl_error_p(msg);
    posspeedctloutput->dob_iq_com_A = mavlink_msg_posspeedctloutput_get_dob_iq_com_A(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_PosSpeedCtlOutput_LEN? msg->len : MAVLINK_MSG_ID_PosSpeedCtlOutput_LEN;
        memset(posspeedctloutput, 0, MAVLINK_MSG_ID_PosSpeedCtlOutput_LEN);
    memcpy(posspeedctloutput, _MAV_PAYLOAD(msg), len);
#endif
}
