#pragma once
// MESSAGE MotorPosSensorOutput PACKING

#define MAVLINK_MSG_ID_MotorPosSensorOutput 30040


typedef struct __mavlink_motorpossensoroutput_t {
 int64_t enc_sum_p; /*<  */
 float elec_angle_now_rad; /*<  */
} mavlink_motorpossensoroutput_t;

#define MAVLINK_MSG_ID_MotorPosSensorOutput_LEN 12
#define MAVLINK_MSG_ID_MotorPosSensorOutput_MIN_LEN 12
#define MAVLINK_MSG_ID_30040_LEN 12
#define MAVLINK_MSG_ID_30040_MIN_LEN 12

#define MAVLINK_MSG_ID_MotorPosSensorOutput_CRC 160
#define MAVLINK_MSG_ID_30040_CRC 160



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_MotorPosSensorOutput { \
    30040, \
    "MotorPosSensorOutput", \
    2, \
    {  { "enc_sum_p", NULL, MAVLINK_TYPE_INT64_T, 0, 0, offsetof(mavlink_motorpossensoroutput_t, enc_sum_p) }, \
         { "elec_angle_now_rad", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_motorpossensoroutput_t, elec_angle_now_rad) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_MotorPosSensorOutput { \
    "MotorPosSensorOutput", \
    2, \
    {  { "enc_sum_p", NULL, MAVLINK_TYPE_INT64_T, 0, 0, offsetof(mavlink_motorpossensoroutput_t, enc_sum_p) }, \
         { "elec_angle_now_rad", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_motorpossensoroutput_t, elec_angle_now_rad) }, \
         } \
}
#endif

/**
 * @brief Pack a motorpossensoroutput message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param enc_sum_p  
 * @param elec_angle_now_rad  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_motorpossensoroutput_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               int64_t enc_sum_p, float elec_angle_now_rad)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MotorPosSensorOutput_LEN];
    _mav_put_int64_t(buf, 0, enc_sum_p);
    _mav_put_float(buf, 8, elec_angle_now_rad);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MotorPosSensorOutput_LEN);
#else
    mavlink_motorpossensoroutput_t packet;
    packet.enc_sum_p = enc_sum_p;
    packet.elec_angle_now_rad = elec_angle_now_rad;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MotorPosSensorOutput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MotorPosSensorOutput;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_MotorPosSensorOutput_MIN_LEN, MAVLINK_MSG_ID_MotorPosSensorOutput_LEN, MAVLINK_MSG_ID_MotorPosSensorOutput_CRC);
}

/**
 * @brief Pack a motorpossensoroutput message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param enc_sum_p  
 * @param elec_angle_now_rad  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_motorpossensoroutput_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               int64_t enc_sum_p, float elec_angle_now_rad)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MotorPosSensorOutput_LEN];
    _mav_put_int64_t(buf, 0, enc_sum_p);
    _mav_put_float(buf, 8, elec_angle_now_rad);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MotorPosSensorOutput_LEN);
#else
    mavlink_motorpossensoroutput_t packet;
    packet.enc_sum_p = enc_sum_p;
    packet.elec_angle_now_rad = elec_angle_now_rad;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MotorPosSensorOutput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MotorPosSensorOutput;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_MotorPosSensorOutput_MIN_LEN, MAVLINK_MSG_ID_MotorPosSensorOutput_LEN, MAVLINK_MSG_ID_MotorPosSensorOutput_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_MotorPosSensorOutput_MIN_LEN, MAVLINK_MSG_ID_MotorPosSensorOutput_LEN);
#endif
}

/**
 * @brief Pack a motorpossensoroutput message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param enc_sum_p  
 * @param elec_angle_now_rad  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_motorpossensoroutput_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   int64_t enc_sum_p,float elec_angle_now_rad)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MotorPosSensorOutput_LEN];
    _mav_put_int64_t(buf, 0, enc_sum_p);
    _mav_put_float(buf, 8, elec_angle_now_rad);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MotorPosSensorOutput_LEN);
#else
    mavlink_motorpossensoroutput_t packet;
    packet.enc_sum_p = enc_sum_p;
    packet.elec_angle_now_rad = elec_angle_now_rad;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MotorPosSensorOutput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MotorPosSensorOutput;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_MotorPosSensorOutput_MIN_LEN, MAVLINK_MSG_ID_MotorPosSensorOutput_LEN, MAVLINK_MSG_ID_MotorPosSensorOutput_CRC);
}

/**
 * @brief Encode a motorpossensoroutput struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param motorpossensoroutput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_motorpossensoroutput_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_motorpossensoroutput_t* motorpossensoroutput)
{
    return mavlink_msg_motorpossensoroutput_pack(system_id, component_id, msg, motorpossensoroutput->enc_sum_p, motorpossensoroutput->elec_angle_now_rad);
}

/**
 * @brief Encode a motorpossensoroutput struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param motorpossensoroutput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_motorpossensoroutput_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_motorpossensoroutput_t* motorpossensoroutput)
{
    return mavlink_msg_motorpossensoroutput_pack_chan(system_id, component_id, chan, msg, motorpossensoroutput->enc_sum_p, motorpossensoroutput->elec_angle_now_rad);
}

/**
 * @brief Encode a motorpossensoroutput struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param motorpossensoroutput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_motorpossensoroutput_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_motorpossensoroutput_t* motorpossensoroutput)
{
    return mavlink_msg_motorpossensoroutput_pack_status(system_id, component_id, _status, msg,  motorpossensoroutput->enc_sum_p, motorpossensoroutput->elec_angle_now_rad);
}

/**
 * @brief Send a motorpossensoroutput message
 * @param chan MAVLink channel to send the message
 *
 * @param enc_sum_p  
 * @param elec_angle_now_rad  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_motorpossensoroutput_send(mavlink_channel_t chan, int64_t enc_sum_p, float elec_angle_now_rad)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MotorPosSensorOutput_LEN];
    _mav_put_int64_t(buf, 0, enc_sum_p);
    _mav_put_float(buf, 8, elec_angle_now_rad);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MotorPosSensorOutput, buf, MAVLINK_MSG_ID_MotorPosSensorOutput_MIN_LEN, MAVLINK_MSG_ID_MotorPosSensorOutput_LEN, MAVLINK_MSG_ID_MotorPosSensorOutput_CRC);
#else
    mavlink_motorpossensoroutput_t packet;
    packet.enc_sum_p = enc_sum_p;
    packet.elec_angle_now_rad = elec_angle_now_rad;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MotorPosSensorOutput, (const char *)&packet, MAVLINK_MSG_ID_MotorPosSensorOutput_MIN_LEN, MAVLINK_MSG_ID_MotorPosSensorOutput_LEN, MAVLINK_MSG_ID_MotorPosSensorOutput_CRC);
#endif
}

/**
 * @brief Send a motorpossensoroutput message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_motorpossensoroutput_send_struct(mavlink_channel_t chan, const mavlink_motorpossensoroutput_t* motorpossensoroutput)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_motorpossensoroutput_send(chan, motorpossensoroutput->enc_sum_p, motorpossensoroutput->elec_angle_now_rad);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MotorPosSensorOutput, (const char *)motorpossensoroutput, MAVLINK_MSG_ID_MotorPosSensorOutput_MIN_LEN, MAVLINK_MSG_ID_MotorPosSensorOutput_LEN, MAVLINK_MSG_ID_MotorPosSensorOutput_CRC);
#endif
}

#if MAVLINK_MSG_ID_MotorPosSensorOutput_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_motorpossensoroutput_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  int64_t enc_sum_p, float elec_angle_now_rad)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_int64_t(buf, 0, enc_sum_p);
    _mav_put_float(buf, 8, elec_angle_now_rad);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MotorPosSensorOutput, buf, MAVLINK_MSG_ID_MotorPosSensorOutput_MIN_LEN, MAVLINK_MSG_ID_MotorPosSensorOutput_LEN, MAVLINK_MSG_ID_MotorPosSensorOutput_CRC);
#else
    mavlink_motorpossensoroutput_t *packet = (mavlink_motorpossensoroutput_t *)msgbuf;
    packet->enc_sum_p = enc_sum_p;
    packet->elec_angle_now_rad = elec_angle_now_rad;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MotorPosSensorOutput, (const char *)packet, MAVLINK_MSG_ID_MotorPosSensorOutput_MIN_LEN, MAVLINK_MSG_ID_MotorPosSensorOutput_LEN, MAVLINK_MSG_ID_MotorPosSensorOutput_CRC);
#endif
}
#endif

#endif

// MESSAGE MotorPosSensorOutput UNPACKING


/**
 * @brief Get field enc_sum_p from motorpossensoroutput message
 *
 * @return  
 */
static inline int64_t mavlink_msg_motorpossensoroutput_get_enc_sum_p(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int64_t(msg,  0);
}

/**
 * @brief Get field elec_angle_now_rad from motorpossensoroutput message
 *
 * @return  
 */
static inline float mavlink_msg_motorpossensoroutput_get_elec_angle_now_rad(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Decode a motorpossensoroutput message into a struct
 *
 * @param msg The message to decode
 * @param motorpossensoroutput C-struct to decode the message contents into
 */
static inline void mavlink_msg_motorpossensoroutput_decode(const mavlink_message_t* msg, mavlink_motorpossensoroutput_t* motorpossensoroutput)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    motorpossensoroutput->enc_sum_p = mavlink_msg_motorpossensoroutput_get_enc_sum_p(msg);
    motorpossensoroutput->elec_angle_now_rad = mavlink_msg_motorpossensoroutput_get_elec_angle_now_rad(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_MotorPosSensorOutput_LEN? msg->len : MAVLINK_MSG_ID_MotorPosSensorOutput_LEN;
        memset(motorpossensoroutput, 0, MAVLINK_MSG_ID_MotorPosSensorOutput_LEN);
    memcpy(motorpossensoroutput, _MAV_PAYLOAD(msg), len);
#endif
}
