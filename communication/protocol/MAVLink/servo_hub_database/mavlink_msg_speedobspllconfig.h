#pragma once
// MESSAGE SpeedObsPllConfig PACKING

#define MAVLINK_MSG_ID_SpeedObsPllConfig 30030


typedef struct __mavlink_speedobspllconfig_t {
 float tp_s; /*<  */
 float wn_Hz; /*<  */
 float enc_line_inv_p_n; /*<  */
 float speed_obs_max_rad_s; /*<  */
} mavlink_speedobspllconfig_t;

#define MAVLINK_MSG_ID_SpeedObsPllConfig_LEN 16
#define MAVLINK_MSG_ID_SpeedObsPllConfig_MIN_LEN 16
#define MAVLINK_MSG_ID_30030_LEN 16
#define MAVLINK_MSG_ID_30030_MIN_LEN 16

#define MAVLINK_MSG_ID_SpeedObsPllConfig_CRC 82
#define MAVLINK_MSG_ID_30030_CRC 82



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_SpeedObsPllConfig { \
    30030, \
    "SpeedObsPllConfig", \
    4, \
    {  { "tp_s", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_speedobspllconfig_t, tp_s) }, \
         { "wn_Hz", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_speedobspllconfig_t, wn_Hz) }, \
         { "enc_line_inv_p_n", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_speedobspllconfig_t, enc_line_inv_p_n) }, \
         { "speed_obs_max_rad_s", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_speedobspllconfig_t, speed_obs_max_rad_s) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_SpeedObsPllConfig { \
    "SpeedObsPllConfig", \
    4, \
    {  { "tp_s", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_speedobspllconfig_t, tp_s) }, \
         { "wn_Hz", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_speedobspllconfig_t, wn_Hz) }, \
         { "enc_line_inv_p_n", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_speedobspllconfig_t, enc_line_inv_p_n) }, \
         { "speed_obs_max_rad_s", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_speedobspllconfig_t, speed_obs_max_rad_s) }, \
         } \
}
#endif

/**
 * @brief Pack a speedobspllconfig message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param tp_s  
 * @param wn_Hz  
 * @param enc_line_inv_p_n  
 * @param speed_obs_max_rad_s  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_speedobspllconfig_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               float tp_s, float wn_Hz, float enc_line_inv_p_n, float speed_obs_max_rad_s)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SpeedObsPllConfig_LEN];
    _mav_put_float(buf, 0, tp_s);
    _mav_put_float(buf, 4, wn_Hz);
    _mav_put_float(buf, 8, enc_line_inv_p_n);
    _mav_put_float(buf, 12, speed_obs_max_rad_s);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SpeedObsPllConfig_LEN);
#else
    mavlink_speedobspllconfig_t packet;
    packet.tp_s = tp_s;
    packet.wn_Hz = wn_Hz;
    packet.enc_line_inv_p_n = enc_line_inv_p_n;
    packet.speed_obs_max_rad_s = speed_obs_max_rad_s;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SpeedObsPllConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SpeedObsPllConfig;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_SpeedObsPllConfig_MIN_LEN, MAVLINK_MSG_ID_SpeedObsPllConfig_LEN, MAVLINK_MSG_ID_SpeedObsPllConfig_CRC);
}

/**
 * @brief Pack a speedobspllconfig message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param tp_s  
 * @param wn_Hz  
 * @param enc_line_inv_p_n  
 * @param speed_obs_max_rad_s  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_speedobspllconfig_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               float tp_s, float wn_Hz, float enc_line_inv_p_n, float speed_obs_max_rad_s)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SpeedObsPllConfig_LEN];
    _mav_put_float(buf, 0, tp_s);
    _mav_put_float(buf, 4, wn_Hz);
    _mav_put_float(buf, 8, enc_line_inv_p_n);
    _mav_put_float(buf, 12, speed_obs_max_rad_s);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SpeedObsPllConfig_LEN);
#else
    mavlink_speedobspllconfig_t packet;
    packet.tp_s = tp_s;
    packet.wn_Hz = wn_Hz;
    packet.enc_line_inv_p_n = enc_line_inv_p_n;
    packet.speed_obs_max_rad_s = speed_obs_max_rad_s;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SpeedObsPllConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SpeedObsPllConfig;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_SpeedObsPllConfig_MIN_LEN, MAVLINK_MSG_ID_SpeedObsPllConfig_LEN, MAVLINK_MSG_ID_SpeedObsPllConfig_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_SpeedObsPllConfig_MIN_LEN, MAVLINK_MSG_ID_SpeedObsPllConfig_LEN);
#endif
}

/**
 * @brief Pack a speedobspllconfig message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param tp_s  
 * @param wn_Hz  
 * @param enc_line_inv_p_n  
 * @param speed_obs_max_rad_s  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_speedobspllconfig_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   float tp_s,float wn_Hz,float enc_line_inv_p_n,float speed_obs_max_rad_s)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SpeedObsPllConfig_LEN];
    _mav_put_float(buf, 0, tp_s);
    _mav_put_float(buf, 4, wn_Hz);
    _mav_put_float(buf, 8, enc_line_inv_p_n);
    _mav_put_float(buf, 12, speed_obs_max_rad_s);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SpeedObsPllConfig_LEN);
#else
    mavlink_speedobspllconfig_t packet;
    packet.tp_s = tp_s;
    packet.wn_Hz = wn_Hz;
    packet.enc_line_inv_p_n = enc_line_inv_p_n;
    packet.speed_obs_max_rad_s = speed_obs_max_rad_s;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SpeedObsPllConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SpeedObsPllConfig;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_SpeedObsPllConfig_MIN_LEN, MAVLINK_MSG_ID_SpeedObsPllConfig_LEN, MAVLINK_MSG_ID_SpeedObsPllConfig_CRC);
}

/**
 * @brief Encode a speedobspllconfig struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param speedobspllconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_speedobspllconfig_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_speedobspllconfig_t* speedobspllconfig)
{
    return mavlink_msg_speedobspllconfig_pack(system_id, component_id, msg, speedobspllconfig->tp_s, speedobspllconfig->wn_Hz, speedobspllconfig->enc_line_inv_p_n, speedobspllconfig->speed_obs_max_rad_s);
}

/**
 * @brief Encode a speedobspllconfig struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param speedobspllconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_speedobspllconfig_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_speedobspllconfig_t* speedobspllconfig)
{
    return mavlink_msg_speedobspllconfig_pack_chan(system_id, component_id, chan, msg, speedobspllconfig->tp_s, speedobspllconfig->wn_Hz, speedobspllconfig->enc_line_inv_p_n, speedobspllconfig->speed_obs_max_rad_s);
}

/**
 * @brief Encode a speedobspllconfig struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param speedobspllconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_speedobspllconfig_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_speedobspllconfig_t* speedobspllconfig)
{
    return mavlink_msg_speedobspllconfig_pack_status(system_id, component_id, _status, msg,  speedobspllconfig->tp_s, speedobspllconfig->wn_Hz, speedobspllconfig->enc_line_inv_p_n, speedobspllconfig->speed_obs_max_rad_s);
}

/**
 * @brief Send a speedobspllconfig message
 * @param chan MAVLink channel to send the message
 *
 * @param tp_s  
 * @param wn_Hz  
 * @param enc_line_inv_p_n  
 * @param speed_obs_max_rad_s  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_speedobspllconfig_send(mavlink_channel_t chan, float tp_s, float wn_Hz, float enc_line_inv_p_n, float speed_obs_max_rad_s)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SpeedObsPllConfig_LEN];
    _mav_put_float(buf, 0, tp_s);
    _mav_put_float(buf, 4, wn_Hz);
    _mav_put_float(buf, 8, enc_line_inv_p_n);
    _mav_put_float(buf, 12, speed_obs_max_rad_s);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SpeedObsPllConfig, buf, MAVLINK_MSG_ID_SpeedObsPllConfig_MIN_LEN, MAVLINK_MSG_ID_SpeedObsPllConfig_LEN, MAVLINK_MSG_ID_SpeedObsPllConfig_CRC);
#else
    mavlink_speedobspllconfig_t packet;
    packet.tp_s = tp_s;
    packet.wn_Hz = wn_Hz;
    packet.enc_line_inv_p_n = enc_line_inv_p_n;
    packet.speed_obs_max_rad_s = speed_obs_max_rad_s;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SpeedObsPllConfig, (const char *)&packet, MAVLINK_MSG_ID_SpeedObsPllConfig_MIN_LEN, MAVLINK_MSG_ID_SpeedObsPllConfig_LEN, MAVLINK_MSG_ID_SpeedObsPllConfig_CRC);
#endif
}

/**
 * @brief Send a speedobspllconfig message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_speedobspllconfig_send_struct(mavlink_channel_t chan, const mavlink_speedobspllconfig_t* speedobspllconfig)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_speedobspllconfig_send(chan, speedobspllconfig->tp_s, speedobspllconfig->wn_Hz, speedobspllconfig->enc_line_inv_p_n, speedobspllconfig->speed_obs_max_rad_s);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SpeedObsPllConfig, (const char *)speedobspllconfig, MAVLINK_MSG_ID_SpeedObsPllConfig_MIN_LEN, MAVLINK_MSG_ID_SpeedObsPllConfig_LEN, MAVLINK_MSG_ID_SpeedObsPllConfig_CRC);
#endif
}

#if MAVLINK_MSG_ID_SpeedObsPllConfig_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_speedobspllconfig_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float tp_s, float wn_Hz, float enc_line_inv_p_n, float speed_obs_max_rad_s)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, tp_s);
    _mav_put_float(buf, 4, wn_Hz);
    _mav_put_float(buf, 8, enc_line_inv_p_n);
    _mav_put_float(buf, 12, speed_obs_max_rad_s);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SpeedObsPllConfig, buf, MAVLINK_MSG_ID_SpeedObsPllConfig_MIN_LEN, MAVLINK_MSG_ID_SpeedObsPllConfig_LEN, MAVLINK_MSG_ID_SpeedObsPllConfig_CRC);
#else
    mavlink_speedobspllconfig_t *packet = (mavlink_speedobspllconfig_t *)msgbuf;
    packet->tp_s = tp_s;
    packet->wn_Hz = wn_Hz;
    packet->enc_line_inv_p_n = enc_line_inv_p_n;
    packet->speed_obs_max_rad_s = speed_obs_max_rad_s;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SpeedObsPllConfig, (const char *)packet, MAVLINK_MSG_ID_SpeedObsPllConfig_MIN_LEN, MAVLINK_MSG_ID_SpeedObsPllConfig_LEN, MAVLINK_MSG_ID_SpeedObsPllConfig_CRC);
#endif
}
#endif

#endif

// MESSAGE SpeedObsPllConfig UNPACKING


/**
 * @brief Get field tp_s from speedobspllconfig message
 *
 * @return  
 */
static inline float mavlink_msg_speedobspllconfig_get_tp_s(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field wn_Hz from speedobspllconfig message
 *
 * @return  
 */
static inline float mavlink_msg_speedobspllconfig_get_wn_Hz(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field enc_line_inv_p_n from speedobspllconfig message
 *
 * @return  
 */
static inline float mavlink_msg_speedobspllconfig_get_enc_line_inv_p_n(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field speed_obs_max_rad_s from speedobspllconfig message
 *
 * @return  
 */
static inline float mavlink_msg_speedobspllconfig_get_speed_obs_max_rad_s(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Decode a speedobspllconfig message into a struct
 *
 * @param msg The message to decode
 * @param speedobspllconfig C-struct to decode the message contents into
 */
static inline void mavlink_msg_speedobspllconfig_decode(const mavlink_message_t* msg, mavlink_speedobspllconfig_t* speedobspllconfig)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    speedobspllconfig->tp_s = mavlink_msg_speedobspllconfig_get_tp_s(msg);
    speedobspllconfig->wn_Hz = mavlink_msg_speedobspllconfig_get_wn_Hz(msg);
    speedobspllconfig->enc_line_inv_p_n = mavlink_msg_speedobspllconfig_get_enc_line_inv_p_n(msg);
    speedobspllconfig->speed_obs_max_rad_s = mavlink_msg_speedobspllconfig_get_speed_obs_max_rad_s(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_SpeedObsPllConfig_LEN? msg->len : MAVLINK_MSG_ID_SpeedObsPllConfig_LEN;
        memset(speedobspllconfig, 0, MAVLINK_MSG_ID_SpeedObsPllConfig_LEN);
    memcpy(speedobspllconfig, _MAV_PAYLOAD(msg), len);
#endif
}
