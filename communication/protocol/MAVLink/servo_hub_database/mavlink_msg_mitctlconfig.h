#pragma once
// MESSAGE MitCtlConfig PACKING

#define MAVLINK_MSG_ID_MitCtlConfig 30066


typedef struct __mavlink_mitctlconfig_t {
 float kp_pos_NM_rad; /*<  */
 float kd_spd_NM_rad_s; /*<  */
 float enc_line_inv_p_n; /*<  */
 float kt_NM_A; /*<  */
} mavlink_mitctlconfig_t;

#define MAVLINK_MSG_ID_MitCtlConfig_LEN 16
#define MAVLINK_MSG_ID_MitCtlConfig_MIN_LEN 16
#define MAVLINK_MSG_ID_30066_LEN 16
#define MAVLINK_MSG_ID_30066_MIN_LEN 16

#define MAVLINK_MSG_ID_MitCtlConfig_CRC 147
#define MAVLINK_MSG_ID_30066_CRC 147



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_MitCtlConfig { \
    30066, \
    "MitCtlConfig", \
    4, \
    {  { "kp_pos_NM_rad", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_mitctlconfig_t, kp_pos_NM_rad) }, \
         { "kd_spd_NM_rad_s", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_mitctlconfig_t, kd_spd_NM_rad_s) }, \
         { "enc_line_inv_p_n", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_mitctlconfig_t, enc_line_inv_p_n) }, \
         { "kt_NM_A", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_mitctlconfig_t, kt_NM_A) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_MitCtlConfig { \
    "MitCtlConfig", \
    4, \
    {  { "kp_pos_NM_rad", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_mitctlconfig_t, kp_pos_NM_rad) }, \
         { "kd_spd_NM_rad_s", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_mitctlconfig_t, kd_spd_NM_rad_s) }, \
         { "enc_line_inv_p_n", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_mitctlconfig_t, enc_line_inv_p_n) }, \
         { "kt_NM_A", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_mitctlconfig_t, kt_NM_A) }, \
         } \
}
#endif

/**
 * @brief Pack a mitctlconfig message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param kp_pos_NM_rad  
 * @param kd_spd_NM_rad_s  
 * @param enc_line_inv_p_n  
 * @param kt_NM_A  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_mitctlconfig_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               float kp_pos_NM_rad, float kd_spd_NM_rad_s, float enc_line_inv_p_n, float kt_NM_A)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MitCtlConfig_LEN];
    _mav_put_float(buf, 0, kp_pos_NM_rad);
    _mav_put_float(buf, 4, kd_spd_NM_rad_s);
    _mav_put_float(buf, 8, enc_line_inv_p_n);
    _mav_put_float(buf, 12, kt_NM_A);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MitCtlConfig_LEN);
#else
    mavlink_mitctlconfig_t packet;
    packet.kp_pos_NM_rad = kp_pos_NM_rad;
    packet.kd_spd_NM_rad_s = kd_spd_NM_rad_s;
    packet.enc_line_inv_p_n = enc_line_inv_p_n;
    packet.kt_NM_A = kt_NM_A;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MitCtlConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MitCtlConfig;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_MitCtlConfig_MIN_LEN, MAVLINK_MSG_ID_MitCtlConfig_LEN, MAVLINK_MSG_ID_MitCtlConfig_CRC);
}

/**
 * @brief Pack a mitctlconfig message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param kp_pos_NM_rad  
 * @param kd_spd_NM_rad_s  
 * @param enc_line_inv_p_n  
 * @param kt_NM_A  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_mitctlconfig_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               float kp_pos_NM_rad, float kd_spd_NM_rad_s, float enc_line_inv_p_n, float kt_NM_A)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MitCtlConfig_LEN];
    _mav_put_float(buf, 0, kp_pos_NM_rad);
    _mav_put_float(buf, 4, kd_spd_NM_rad_s);
    _mav_put_float(buf, 8, enc_line_inv_p_n);
    _mav_put_float(buf, 12, kt_NM_A);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MitCtlConfig_LEN);
#else
    mavlink_mitctlconfig_t packet;
    packet.kp_pos_NM_rad = kp_pos_NM_rad;
    packet.kd_spd_NM_rad_s = kd_spd_NM_rad_s;
    packet.enc_line_inv_p_n = enc_line_inv_p_n;
    packet.kt_NM_A = kt_NM_A;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MitCtlConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MitCtlConfig;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_MitCtlConfig_MIN_LEN, MAVLINK_MSG_ID_MitCtlConfig_LEN, MAVLINK_MSG_ID_MitCtlConfig_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_MitCtlConfig_MIN_LEN, MAVLINK_MSG_ID_MitCtlConfig_LEN);
#endif
}

/**
 * @brief Pack a mitctlconfig message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param kp_pos_NM_rad  
 * @param kd_spd_NM_rad_s  
 * @param enc_line_inv_p_n  
 * @param kt_NM_A  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_mitctlconfig_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   float kp_pos_NM_rad,float kd_spd_NM_rad_s,float enc_line_inv_p_n,float kt_NM_A)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MitCtlConfig_LEN];
    _mav_put_float(buf, 0, kp_pos_NM_rad);
    _mav_put_float(buf, 4, kd_spd_NM_rad_s);
    _mav_put_float(buf, 8, enc_line_inv_p_n);
    _mav_put_float(buf, 12, kt_NM_A);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MitCtlConfig_LEN);
#else
    mavlink_mitctlconfig_t packet;
    packet.kp_pos_NM_rad = kp_pos_NM_rad;
    packet.kd_spd_NM_rad_s = kd_spd_NM_rad_s;
    packet.enc_line_inv_p_n = enc_line_inv_p_n;
    packet.kt_NM_A = kt_NM_A;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MitCtlConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MitCtlConfig;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_MitCtlConfig_MIN_LEN, MAVLINK_MSG_ID_MitCtlConfig_LEN, MAVLINK_MSG_ID_MitCtlConfig_CRC);
}

/**
 * @brief Encode a mitctlconfig struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param mitctlconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_mitctlconfig_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_mitctlconfig_t* mitctlconfig)
{
    return mavlink_msg_mitctlconfig_pack(system_id, component_id, msg, mitctlconfig->kp_pos_NM_rad, mitctlconfig->kd_spd_NM_rad_s, mitctlconfig->enc_line_inv_p_n, mitctlconfig->kt_NM_A);
}

/**
 * @brief Encode a mitctlconfig struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param mitctlconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_mitctlconfig_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_mitctlconfig_t* mitctlconfig)
{
    return mavlink_msg_mitctlconfig_pack_chan(system_id, component_id, chan, msg, mitctlconfig->kp_pos_NM_rad, mitctlconfig->kd_spd_NM_rad_s, mitctlconfig->enc_line_inv_p_n, mitctlconfig->kt_NM_A);
}

/**
 * @brief Encode a mitctlconfig struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param mitctlconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_mitctlconfig_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_mitctlconfig_t* mitctlconfig)
{
    return mavlink_msg_mitctlconfig_pack_status(system_id, component_id, _status, msg,  mitctlconfig->kp_pos_NM_rad, mitctlconfig->kd_spd_NM_rad_s, mitctlconfig->enc_line_inv_p_n, mitctlconfig->kt_NM_A);
}

/**
 * @brief Send a mitctlconfig message
 * @param chan MAVLink channel to send the message
 *
 * @param kp_pos_NM_rad  
 * @param kd_spd_NM_rad_s  
 * @param enc_line_inv_p_n  
 * @param kt_NM_A  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_mitctlconfig_send(mavlink_channel_t chan, float kp_pos_NM_rad, float kd_spd_NM_rad_s, float enc_line_inv_p_n, float kt_NM_A)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MitCtlConfig_LEN];
    _mav_put_float(buf, 0, kp_pos_NM_rad);
    _mav_put_float(buf, 4, kd_spd_NM_rad_s);
    _mav_put_float(buf, 8, enc_line_inv_p_n);
    _mav_put_float(buf, 12, kt_NM_A);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MitCtlConfig, buf, MAVLINK_MSG_ID_MitCtlConfig_MIN_LEN, MAVLINK_MSG_ID_MitCtlConfig_LEN, MAVLINK_MSG_ID_MitCtlConfig_CRC);
#else
    mavlink_mitctlconfig_t packet;
    packet.kp_pos_NM_rad = kp_pos_NM_rad;
    packet.kd_spd_NM_rad_s = kd_spd_NM_rad_s;
    packet.enc_line_inv_p_n = enc_line_inv_p_n;
    packet.kt_NM_A = kt_NM_A;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MitCtlConfig, (const char *)&packet, MAVLINK_MSG_ID_MitCtlConfig_MIN_LEN, MAVLINK_MSG_ID_MitCtlConfig_LEN, MAVLINK_MSG_ID_MitCtlConfig_CRC);
#endif
}

/**
 * @brief Send a mitctlconfig message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_mitctlconfig_send_struct(mavlink_channel_t chan, const mavlink_mitctlconfig_t* mitctlconfig)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_mitctlconfig_send(chan, mitctlconfig->kp_pos_NM_rad, mitctlconfig->kd_spd_NM_rad_s, mitctlconfig->enc_line_inv_p_n, mitctlconfig->kt_NM_A);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MitCtlConfig, (const char *)mitctlconfig, MAVLINK_MSG_ID_MitCtlConfig_MIN_LEN, MAVLINK_MSG_ID_MitCtlConfig_LEN, MAVLINK_MSG_ID_MitCtlConfig_CRC);
#endif
}

#if MAVLINK_MSG_ID_MitCtlConfig_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_mitctlconfig_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float kp_pos_NM_rad, float kd_spd_NM_rad_s, float enc_line_inv_p_n, float kt_NM_A)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, kp_pos_NM_rad);
    _mav_put_float(buf, 4, kd_spd_NM_rad_s);
    _mav_put_float(buf, 8, enc_line_inv_p_n);
    _mav_put_float(buf, 12, kt_NM_A);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MitCtlConfig, buf, MAVLINK_MSG_ID_MitCtlConfig_MIN_LEN, MAVLINK_MSG_ID_MitCtlConfig_LEN, MAVLINK_MSG_ID_MitCtlConfig_CRC);
#else
    mavlink_mitctlconfig_t *packet = (mavlink_mitctlconfig_t *)msgbuf;
    packet->kp_pos_NM_rad = kp_pos_NM_rad;
    packet->kd_spd_NM_rad_s = kd_spd_NM_rad_s;
    packet->enc_line_inv_p_n = enc_line_inv_p_n;
    packet->kt_NM_A = kt_NM_A;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MitCtlConfig, (const char *)packet, MAVLINK_MSG_ID_MitCtlConfig_MIN_LEN, MAVLINK_MSG_ID_MitCtlConfig_LEN, MAVLINK_MSG_ID_MitCtlConfig_CRC);
#endif
}
#endif

#endif

// MESSAGE MitCtlConfig UNPACKING


/**
 * @brief Get field kp_pos_NM_rad from mitctlconfig message
 *
 * @return  
 */
static inline float mavlink_msg_mitctlconfig_get_kp_pos_NM_rad(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field kd_spd_NM_rad_s from mitctlconfig message
 *
 * @return  
 */
static inline float mavlink_msg_mitctlconfig_get_kd_spd_NM_rad_s(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field enc_line_inv_p_n from mitctlconfig message
 *
 * @return  
 */
static inline float mavlink_msg_mitctlconfig_get_enc_line_inv_p_n(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field kt_NM_A from mitctlconfig message
 *
 * @return  
 */
static inline float mavlink_msg_mitctlconfig_get_kt_NM_A(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Decode a mitctlconfig message into a struct
 *
 * @param msg The message to decode
 * @param mitctlconfig C-struct to decode the message contents into
 */
static inline void mavlink_msg_mitctlconfig_decode(const mavlink_message_t* msg, mavlink_mitctlconfig_t* mitctlconfig)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mitctlconfig->kp_pos_NM_rad = mavlink_msg_mitctlconfig_get_kp_pos_NM_rad(msg);
    mitctlconfig->kd_spd_NM_rad_s = mavlink_msg_mitctlconfig_get_kd_spd_NM_rad_s(msg);
    mitctlconfig->enc_line_inv_p_n = mavlink_msg_mitctlconfig_get_enc_line_inv_p_n(msg);
    mitctlconfig->kt_NM_A = mavlink_msg_mitctlconfig_get_kt_NM_A(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_MitCtlConfig_LEN? msg->len : MAVLINK_MSG_ID_MitCtlConfig_LEN;
        memset(mitctlconfig, 0, MAVLINK_MSG_ID_MitCtlConfig_LEN);
    memcpy(mitctlconfig, _MAV_PAYLOAD(msg), len);
#endif
}
