#pragma once
// MESSAGE PosSpeedCtlConfig PACKING

#define MAVLINK_MSG_ID_PosSpeedCtlConfig 30021


typedef struct __mavlink_posspeedctlconfig_t {
 float aff; /*<  */
 float vff; /*<  */
 float enc_line_inv_p_n; /*<  */
 float j_kt; /*<  */
 float ki_s; /*<  */
 float kp_p; /*<  */
 float kp_s; /*<  */
 float speed_max_rad_s; /*<  */
 float tp_s; /*<  */
 float mode; /*<  */
 float dob_wn_Hz; /*<  */
 uint8_t dob_enable; /*<  */
 uint8_t dynamic_integration_enable; /*<  */
} mavlink_posspeedctlconfig_t;

#define MAVLINK_MSG_ID_PosSpeedCtlConfig_LEN 46
#define MAVLINK_MSG_ID_PosSpeedCtlConfig_MIN_LEN 46
#define MAVLINK_MSG_ID_30021_LEN 46
#define MAVLINK_MSG_ID_30021_MIN_LEN 46

#define MAVLINK_MSG_ID_PosSpeedCtlConfig_CRC 109
#define MAVLINK_MSG_ID_30021_CRC 109



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_PosSpeedCtlConfig { \
    30021, \
    "PosSpeedCtlConfig", \
    13, \
    {  { "aff", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_posspeedctlconfig_t, aff) }, \
         { "vff", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_posspeedctlconfig_t, vff) }, \
         { "enc_line_inv_p_n", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_posspeedctlconfig_t, enc_line_inv_p_n) }, \
         { "j_kt", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_posspeedctlconfig_t, j_kt) }, \
         { "ki_s", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_posspeedctlconfig_t, ki_s) }, \
         { "kp_p", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_posspeedctlconfig_t, kp_p) }, \
         { "kp_s", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_posspeedctlconfig_t, kp_s) }, \
         { "speed_max_rad_s", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_posspeedctlconfig_t, speed_max_rad_s) }, \
         { "tp_s", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_posspeedctlconfig_t, tp_s) }, \
         { "mode", NULL, MAVLINK_TYPE_FLOAT, 0, 36, offsetof(mavlink_posspeedctlconfig_t, mode) }, \
         { "dob_wn_Hz", NULL, MAVLINK_TYPE_FLOAT, 0, 40, offsetof(mavlink_posspeedctlconfig_t, dob_wn_Hz) }, \
         { "dob_enable", NULL, MAVLINK_TYPE_UINT8_T, 0, 44, offsetof(mavlink_posspeedctlconfig_t, dob_enable) }, \
         { "dynamic_integration_enable", NULL, MAVLINK_TYPE_UINT8_T, 0, 45, offsetof(mavlink_posspeedctlconfig_t, dynamic_integration_enable) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_PosSpeedCtlConfig { \
    "PosSpeedCtlConfig", \
    13, \
    {  { "aff", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_posspeedctlconfig_t, aff) }, \
         { "vff", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_posspeedctlconfig_t, vff) }, \
         { "enc_line_inv_p_n", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_posspeedctlconfig_t, enc_line_inv_p_n) }, \
         { "j_kt", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_posspeedctlconfig_t, j_kt) }, \
         { "ki_s", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_posspeedctlconfig_t, ki_s) }, \
         { "kp_p", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_posspeedctlconfig_t, kp_p) }, \
         { "kp_s", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_posspeedctlconfig_t, kp_s) }, \
         { "speed_max_rad_s", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_posspeedctlconfig_t, speed_max_rad_s) }, \
         { "tp_s", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_posspeedctlconfig_t, tp_s) }, \
         { "mode", NULL, MAVLINK_TYPE_FLOAT, 0, 36, offsetof(mavlink_posspeedctlconfig_t, mode) }, \
         { "dob_wn_Hz", NULL, MAVLINK_TYPE_FLOAT, 0, 40, offsetof(mavlink_posspeedctlconfig_t, dob_wn_Hz) }, \
         { "dob_enable", NULL, MAVLINK_TYPE_UINT8_T, 0, 44, offsetof(mavlink_posspeedctlconfig_t, dob_enable) }, \
         { "dynamic_integration_enable", NULL, MAVLINK_TYPE_UINT8_T, 0, 45, offsetof(mavlink_posspeedctlconfig_t, dynamic_integration_enable) }, \
         } \
}
#endif

/**
 * @brief Pack a posspeedctlconfig message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param aff  
 * @param vff  
 * @param enc_line_inv_p_n  
 * @param j_kt  
 * @param ki_s  
 * @param kp_p  
 * @param kp_s  
 * @param speed_max_rad_s  
 * @param tp_s  
 * @param mode  
 * @param dob_wn_Hz  
 * @param dob_enable  
 * @param dynamic_integration_enable  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_posspeedctlconfig_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               float aff, float vff, float enc_line_inv_p_n, float j_kt, float ki_s, float kp_p, float kp_s, float speed_max_rad_s, float tp_s, float mode, float dob_wn_Hz, uint8_t dob_enable, uint8_t dynamic_integration_enable)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PosSpeedCtlConfig_LEN];
    _mav_put_float(buf, 0, aff);
    _mav_put_float(buf, 4, vff);
    _mav_put_float(buf, 8, enc_line_inv_p_n);
    _mav_put_float(buf, 12, j_kt);
    _mav_put_float(buf, 16, ki_s);
    _mav_put_float(buf, 20, kp_p);
    _mav_put_float(buf, 24, kp_s);
    _mav_put_float(buf, 28, speed_max_rad_s);
    _mav_put_float(buf, 32, tp_s);
    _mav_put_float(buf, 36, mode);
    _mav_put_float(buf, 40, dob_wn_Hz);
    _mav_put_uint8_t(buf, 44, dob_enable);
    _mav_put_uint8_t(buf, 45, dynamic_integration_enable);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_PosSpeedCtlConfig_LEN);
#else
    mavlink_posspeedctlconfig_t packet;
    packet.aff = aff;
    packet.vff = vff;
    packet.enc_line_inv_p_n = enc_line_inv_p_n;
    packet.j_kt = j_kt;
    packet.ki_s = ki_s;
    packet.kp_p = kp_p;
    packet.kp_s = kp_s;
    packet.speed_max_rad_s = speed_max_rad_s;
    packet.tp_s = tp_s;
    packet.mode = mode;
    packet.dob_wn_Hz = dob_wn_Hz;
    packet.dob_enable = dob_enable;
    packet.dynamic_integration_enable = dynamic_integration_enable;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_PosSpeedCtlConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_PosSpeedCtlConfig;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_PosSpeedCtlConfig_MIN_LEN, MAVLINK_MSG_ID_PosSpeedCtlConfig_LEN, MAVLINK_MSG_ID_PosSpeedCtlConfig_CRC);
}

/**
 * @brief Pack a posspeedctlconfig message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param aff  
 * @param vff  
 * @param enc_line_inv_p_n  
 * @param j_kt  
 * @param ki_s  
 * @param kp_p  
 * @param kp_s  
 * @param speed_max_rad_s  
 * @param tp_s  
 * @param mode  
 * @param dob_wn_Hz  
 * @param dob_enable  
 * @param dynamic_integration_enable  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_posspeedctlconfig_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               float aff, float vff, float enc_line_inv_p_n, float j_kt, float ki_s, float kp_p, float kp_s, float speed_max_rad_s, float tp_s, float mode, float dob_wn_Hz, uint8_t dob_enable, uint8_t dynamic_integration_enable)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PosSpeedCtlConfig_LEN];
    _mav_put_float(buf, 0, aff);
    _mav_put_float(buf, 4, vff);
    _mav_put_float(buf, 8, enc_line_inv_p_n);
    _mav_put_float(buf, 12, j_kt);
    _mav_put_float(buf, 16, ki_s);
    _mav_put_float(buf, 20, kp_p);
    _mav_put_float(buf, 24, kp_s);
    _mav_put_float(buf, 28, speed_max_rad_s);
    _mav_put_float(buf, 32, tp_s);
    _mav_put_float(buf, 36, mode);
    _mav_put_float(buf, 40, dob_wn_Hz);
    _mav_put_uint8_t(buf, 44, dob_enable);
    _mav_put_uint8_t(buf, 45, dynamic_integration_enable);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_PosSpeedCtlConfig_LEN);
#else
    mavlink_posspeedctlconfig_t packet;
    packet.aff = aff;
    packet.vff = vff;
    packet.enc_line_inv_p_n = enc_line_inv_p_n;
    packet.j_kt = j_kt;
    packet.ki_s = ki_s;
    packet.kp_p = kp_p;
    packet.kp_s = kp_s;
    packet.speed_max_rad_s = speed_max_rad_s;
    packet.tp_s = tp_s;
    packet.mode = mode;
    packet.dob_wn_Hz = dob_wn_Hz;
    packet.dob_enable = dob_enable;
    packet.dynamic_integration_enable = dynamic_integration_enable;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_PosSpeedCtlConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_PosSpeedCtlConfig;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_PosSpeedCtlConfig_MIN_LEN, MAVLINK_MSG_ID_PosSpeedCtlConfig_LEN, MAVLINK_MSG_ID_PosSpeedCtlConfig_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_PosSpeedCtlConfig_MIN_LEN, MAVLINK_MSG_ID_PosSpeedCtlConfig_LEN);
#endif
}

/**
 * @brief Pack a posspeedctlconfig message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param aff  
 * @param vff  
 * @param enc_line_inv_p_n  
 * @param j_kt  
 * @param ki_s  
 * @param kp_p  
 * @param kp_s  
 * @param speed_max_rad_s  
 * @param tp_s  
 * @param mode  
 * @param dob_wn_Hz  
 * @param dob_enable  
 * @param dynamic_integration_enable  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_posspeedctlconfig_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   float aff,float vff,float enc_line_inv_p_n,float j_kt,float ki_s,float kp_p,float kp_s,float speed_max_rad_s,float tp_s,float mode,float dob_wn_Hz,uint8_t dob_enable,uint8_t dynamic_integration_enable)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PosSpeedCtlConfig_LEN];
    _mav_put_float(buf, 0, aff);
    _mav_put_float(buf, 4, vff);
    _mav_put_float(buf, 8, enc_line_inv_p_n);
    _mav_put_float(buf, 12, j_kt);
    _mav_put_float(buf, 16, ki_s);
    _mav_put_float(buf, 20, kp_p);
    _mav_put_float(buf, 24, kp_s);
    _mav_put_float(buf, 28, speed_max_rad_s);
    _mav_put_float(buf, 32, tp_s);
    _mav_put_float(buf, 36, mode);
    _mav_put_float(buf, 40, dob_wn_Hz);
    _mav_put_uint8_t(buf, 44, dob_enable);
    _mav_put_uint8_t(buf, 45, dynamic_integration_enable);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_PosSpeedCtlConfig_LEN);
#else
    mavlink_posspeedctlconfig_t packet;
    packet.aff = aff;
    packet.vff = vff;
    packet.enc_line_inv_p_n = enc_line_inv_p_n;
    packet.j_kt = j_kt;
    packet.ki_s = ki_s;
    packet.kp_p = kp_p;
    packet.kp_s = kp_s;
    packet.speed_max_rad_s = speed_max_rad_s;
    packet.tp_s = tp_s;
    packet.mode = mode;
    packet.dob_wn_Hz = dob_wn_Hz;
    packet.dob_enable = dob_enable;
    packet.dynamic_integration_enable = dynamic_integration_enable;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_PosSpeedCtlConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_PosSpeedCtlConfig;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_PosSpeedCtlConfig_MIN_LEN, MAVLINK_MSG_ID_PosSpeedCtlConfig_LEN, MAVLINK_MSG_ID_PosSpeedCtlConfig_CRC);
}

/**
 * @brief Encode a posspeedctlconfig struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param posspeedctlconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_posspeedctlconfig_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_posspeedctlconfig_t* posspeedctlconfig)
{
    return mavlink_msg_posspeedctlconfig_pack(system_id, component_id, msg, posspeedctlconfig->aff, posspeedctlconfig->vff, posspeedctlconfig->enc_line_inv_p_n, posspeedctlconfig->j_kt, posspeedctlconfig->ki_s, posspeedctlconfig->kp_p, posspeedctlconfig->kp_s, posspeedctlconfig->speed_max_rad_s, posspeedctlconfig->tp_s, posspeedctlconfig->mode, posspeedctlconfig->dob_wn_Hz, posspeedctlconfig->dob_enable, posspeedctlconfig->dynamic_integration_enable);
}

/**
 * @brief Encode a posspeedctlconfig struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param posspeedctlconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_posspeedctlconfig_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_posspeedctlconfig_t* posspeedctlconfig)
{
    return mavlink_msg_posspeedctlconfig_pack_chan(system_id, component_id, chan, msg, posspeedctlconfig->aff, posspeedctlconfig->vff, posspeedctlconfig->enc_line_inv_p_n, posspeedctlconfig->j_kt, posspeedctlconfig->ki_s, posspeedctlconfig->kp_p, posspeedctlconfig->kp_s, posspeedctlconfig->speed_max_rad_s, posspeedctlconfig->tp_s, posspeedctlconfig->mode, posspeedctlconfig->dob_wn_Hz, posspeedctlconfig->dob_enable, posspeedctlconfig->dynamic_integration_enable);
}

/**
 * @brief Encode a posspeedctlconfig struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param posspeedctlconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_posspeedctlconfig_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_posspeedctlconfig_t* posspeedctlconfig)
{
    return mavlink_msg_posspeedctlconfig_pack_status(system_id, component_id, _status, msg,  posspeedctlconfig->aff, posspeedctlconfig->vff, posspeedctlconfig->enc_line_inv_p_n, posspeedctlconfig->j_kt, posspeedctlconfig->ki_s, posspeedctlconfig->kp_p, posspeedctlconfig->kp_s, posspeedctlconfig->speed_max_rad_s, posspeedctlconfig->tp_s, posspeedctlconfig->mode, posspeedctlconfig->dob_wn_Hz, posspeedctlconfig->dob_enable, posspeedctlconfig->dynamic_integration_enable);
}

/**
 * @brief Send a posspeedctlconfig message
 * @param chan MAVLink channel to send the message
 *
 * @param aff  
 * @param vff  
 * @param enc_line_inv_p_n  
 * @param j_kt  
 * @param ki_s  
 * @param kp_p  
 * @param kp_s  
 * @param speed_max_rad_s  
 * @param tp_s  
 * @param mode  
 * @param dob_wn_Hz  
 * @param dob_enable  
 * @param dynamic_integration_enable  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_posspeedctlconfig_send(mavlink_channel_t chan, float aff, float vff, float enc_line_inv_p_n, float j_kt, float ki_s, float kp_p, float kp_s, float speed_max_rad_s, float tp_s, float mode, float dob_wn_Hz, uint8_t dob_enable, uint8_t dynamic_integration_enable)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PosSpeedCtlConfig_LEN];
    _mav_put_float(buf, 0, aff);
    _mav_put_float(buf, 4, vff);
    _mav_put_float(buf, 8, enc_line_inv_p_n);
    _mav_put_float(buf, 12, j_kt);
    _mav_put_float(buf, 16, ki_s);
    _mav_put_float(buf, 20, kp_p);
    _mav_put_float(buf, 24, kp_s);
    _mav_put_float(buf, 28, speed_max_rad_s);
    _mav_put_float(buf, 32, tp_s);
    _mav_put_float(buf, 36, mode);
    _mav_put_float(buf, 40, dob_wn_Hz);
    _mav_put_uint8_t(buf, 44, dob_enable);
    _mav_put_uint8_t(buf, 45, dynamic_integration_enable);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PosSpeedCtlConfig, buf, MAVLINK_MSG_ID_PosSpeedCtlConfig_MIN_LEN, MAVLINK_MSG_ID_PosSpeedCtlConfig_LEN, MAVLINK_MSG_ID_PosSpeedCtlConfig_CRC);
#else
    mavlink_posspeedctlconfig_t packet;
    packet.aff = aff;
    packet.vff = vff;
    packet.enc_line_inv_p_n = enc_line_inv_p_n;
    packet.j_kt = j_kt;
    packet.ki_s = ki_s;
    packet.kp_p = kp_p;
    packet.kp_s = kp_s;
    packet.speed_max_rad_s = speed_max_rad_s;
    packet.tp_s = tp_s;
    packet.mode = mode;
    packet.dob_wn_Hz = dob_wn_Hz;
    packet.dob_enable = dob_enable;
    packet.dynamic_integration_enable = dynamic_integration_enable;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PosSpeedCtlConfig, (const char *)&packet, MAVLINK_MSG_ID_PosSpeedCtlConfig_MIN_LEN, MAVLINK_MSG_ID_PosSpeedCtlConfig_LEN, MAVLINK_MSG_ID_PosSpeedCtlConfig_CRC);
#endif
}

/**
 * @brief Send a posspeedctlconfig message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_posspeedctlconfig_send_struct(mavlink_channel_t chan, const mavlink_posspeedctlconfig_t* posspeedctlconfig)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_posspeedctlconfig_send(chan, posspeedctlconfig->aff, posspeedctlconfig->vff, posspeedctlconfig->enc_line_inv_p_n, posspeedctlconfig->j_kt, posspeedctlconfig->ki_s, posspeedctlconfig->kp_p, posspeedctlconfig->kp_s, posspeedctlconfig->speed_max_rad_s, posspeedctlconfig->tp_s, posspeedctlconfig->mode, posspeedctlconfig->dob_wn_Hz, posspeedctlconfig->dob_enable, posspeedctlconfig->dynamic_integration_enable);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PosSpeedCtlConfig, (const char *)posspeedctlconfig, MAVLINK_MSG_ID_PosSpeedCtlConfig_MIN_LEN, MAVLINK_MSG_ID_PosSpeedCtlConfig_LEN, MAVLINK_MSG_ID_PosSpeedCtlConfig_CRC);
#endif
}

#if MAVLINK_MSG_ID_PosSpeedCtlConfig_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_posspeedctlconfig_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float aff, float vff, float enc_line_inv_p_n, float j_kt, float ki_s, float kp_p, float kp_s, float speed_max_rad_s, float tp_s, float mode, float dob_wn_Hz, uint8_t dob_enable, uint8_t dynamic_integration_enable)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, aff);
    _mav_put_float(buf, 4, vff);
    _mav_put_float(buf, 8, enc_line_inv_p_n);
    _mav_put_float(buf, 12, j_kt);
    _mav_put_float(buf, 16, ki_s);
    _mav_put_float(buf, 20, kp_p);
    _mav_put_float(buf, 24, kp_s);
    _mav_put_float(buf, 28, speed_max_rad_s);
    _mav_put_float(buf, 32, tp_s);
    _mav_put_float(buf, 36, mode);
    _mav_put_float(buf, 40, dob_wn_Hz);
    _mav_put_uint8_t(buf, 44, dob_enable);
    _mav_put_uint8_t(buf, 45, dynamic_integration_enable);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PosSpeedCtlConfig, buf, MAVLINK_MSG_ID_PosSpeedCtlConfig_MIN_LEN, MAVLINK_MSG_ID_PosSpeedCtlConfig_LEN, MAVLINK_MSG_ID_PosSpeedCtlConfig_CRC);
#else
    mavlink_posspeedctlconfig_t *packet = (mavlink_posspeedctlconfig_t *)msgbuf;
    packet->aff = aff;
    packet->vff = vff;
    packet->enc_line_inv_p_n = enc_line_inv_p_n;
    packet->j_kt = j_kt;
    packet->ki_s = ki_s;
    packet->kp_p = kp_p;
    packet->kp_s = kp_s;
    packet->speed_max_rad_s = speed_max_rad_s;
    packet->tp_s = tp_s;
    packet->mode = mode;
    packet->dob_wn_Hz = dob_wn_Hz;
    packet->dob_enable = dob_enable;
    packet->dynamic_integration_enable = dynamic_integration_enable;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PosSpeedCtlConfig, (const char *)packet, MAVLINK_MSG_ID_PosSpeedCtlConfig_MIN_LEN, MAVLINK_MSG_ID_PosSpeedCtlConfig_LEN, MAVLINK_MSG_ID_PosSpeedCtlConfig_CRC);
#endif
}
#endif

#endif

// MESSAGE PosSpeedCtlConfig UNPACKING


/**
 * @brief Get field aff from posspeedctlconfig message
 *
 * @return  
 */
static inline float mavlink_msg_posspeedctlconfig_get_aff(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field vff from posspeedctlconfig message
 *
 * @return  
 */
static inline float mavlink_msg_posspeedctlconfig_get_vff(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field enc_line_inv_p_n from posspeedctlconfig message
 *
 * @return  
 */
static inline float mavlink_msg_posspeedctlconfig_get_enc_line_inv_p_n(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field j_kt from posspeedctlconfig message
 *
 * @return  
 */
static inline float mavlink_msg_posspeedctlconfig_get_j_kt(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Get field ki_s from posspeedctlconfig message
 *
 * @return  
 */
static inline float mavlink_msg_posspeedctlconfig_get_ki_s(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  16);
}

/**
 * @brief Get field kp_p from posspeedctlconfig message
 *
 * @return  
 */
static inline float mavlink_msg_posspeedctlconfig_get_kp_p(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  20);
}

/**
 * @brief Get field kp_s from posspeedctlconfig message
 *
 * @return  
 */
static inline float mavlink_msg_posspeedctlconfig_get_kp_s(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  24);
}

/**
 * @brief Get field speed_max_rad_s from posspeedctlconfig message
 *
 * @return  
 */
static inline float mavlink_msg_posspeedctlconfig_get_speed_max_rad_s(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  28);
}

/**
 * @brief Get field tp_s from posspeedctlconfig message
 *
 * @return  
 */
static inline float mavlink_msg_posspeedctlconfig_get_tp_s(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  32);
}

/**
 * @brief Get field mode from posspeedctlconfig message
 *
 * @return  
 */
static inline float mavlink_msg_posspeedctlconfig_get_mode(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  36);
}

/**
 * @brief Get field dob_wn_Hz from posspeedctlconfig message
 *
 * @return  
 */
static inline float mavlink_msg_posspeedctlconfig_get_dob_wn_Hz(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  40);
}

/**
 * @brief Get field dob_enable from posspeedctlconfig message
 *
 * @return  
 */
static inline uint8_t mavlink_msg_posspeedctlconfig_get_dob_enable(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  44);
}

/**
 * @brief Get field dynamic_integration_enable from posspeedctlconfig message
 *
 * @return  
 */
static inline uint8_t mavlink_msg_posspeedctlconfig_get_dynamic_integration_enable(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  45);
}

/**
 * @brief Decode a posspeedctlconfig message into a struct
 *
 * @param msg The message to decode
 * @param posspeedctlconfig C-struct to decode the message contents into
 */
static inline void mavlink_msg_posspeedctlconfig_decode(const mavlink_message_t* msg, mavlink_posspeedctlconfig_t* posspeedctlconfig)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    posspeedctlconfig->aff = mavlink_msg_posspeedctlconfig_get_aff(msg);
    posspeedctlconfig->vff = mavlink_msg_posspeedctlconfig_get_vff(msg);
    posspeedctlconfig->enc_line_inv_p_n = mavlink_msg_posspeedctlconfig_get_enc_line_inv_p_n(msg);
    posspeedctlconfig->j_kt = mavlink_msg_posspeedctlconfig_get_j_kt(msg);
    posspeedctlconfig->ki_s = mavlink_msg_posspeedctlconfig_get_ki_s(msg);
    posspeedctlconfig->kp_p = mavlink_msg_posspeedctlconfig_get_kp_p(msg);
    posspeedctlconfig->kp_s = mavlink_msg_posspeedctlconfig_get_kp_s(msg);
    posspeedctlconfig->speed_max_rad_s = mavlink_msg_posspeedctlconfig_get_speed_max_rad_s(msg);
    posspeedctlconfig->tp_s = mavlink_msg_posspeedctlconfig_get_tp_s(msg);
    posspeedctlconfig->mode = mavlink_msg_posspeedctlconfig_get_mode(msg);
    posspeedctlconfig->dob_wn_Hz = mavlink_msg_posspeedctlconfig_get_dob_wn_Hz(msg);
    posspeedctlconfig->dob_enable = mavlink_msg_posspeedctlconfig_get_dob_enable(msg);
    posspeedctlconfig->dynamic_integration_enable = mavlink_msg_posspeedctlconfig_get_dynamic_integration_enable(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_PosSpeedCtlConfig_LEN? msg->len : MAVLINK_MSG_ID_PosSpeedCtlConfig_LEN;
        memset(posspeedctlconfig, 0, MAVLINK_MSG_ID_PosSpeedCtlConfig_LEN);
    memcpy(posspeedctlconfig, _MAV_PAYLOAD(msg), len);
#endif
}
