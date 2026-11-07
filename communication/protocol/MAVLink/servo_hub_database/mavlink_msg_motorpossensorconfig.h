#pragma once
// MESSAGE MotorPosSensorConfig PACKING

#define MAVLINK_MSG_ID_MotorPosSensorConfig 30039


typedef struct __mavlink_motorpossensorconfig_t {
 int64_t init_pos_p; /*<  */
 uint32_t enc_line_p_n; /*<  */
 uint32_t pn; /*<  */
 float elec_angle_bias_rad; /*<  */
 int8_t dir; /*<  */
} mavlink_motorpossensorconfig_t;

#define MAVLINK_MSG_ID_MotorPosSensorConfig_LEN 21
#define MAVLINK_MSG_ID_MotorPosSensorConfig_MIN_LEN 21
#define MAVLINK_MSG_ID_30039_LEN 21
#define MAVLINK_MSG_ID_30039_MIN_LEN 21

#define MAVLINK_MSG_ID_MotorPosSensorConfig_CRC 88
#define MAVLINK_MSG_ID_30039_CRC 88



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_MotorPosSensorConfig { \
    30039, \
    "MotorPosSensorConfig", \
    5, \
    {  { "enc_line_p_n", NULL, MAVLINK_TYPE_UINT32_T, 0, 8, offsetof(mavlink_motorpossensorconfig_t, enc_line_p_n) }, \
         { "init_pos_p", NULL, MAVLINK_TYPE_INT64_T, 0, 0, offsetof(mavlink_motorpossensorconfig_t, init_pos_p) }, \
         { "pn", NULL, MAVLINK_TYPE_UINT32_T, 0, 12, offsetof(mavlink_motorpossensorconfig_t, pn) }, \
         { "elec_angle_bias_rad", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_motorpossensorconfig_t, elec_angle_bias_rad) }, \
         { "dir", NULL, MAVLINK_TYPE_INT8_T, 0, 20, offsetof(mavlink_motorpossensorconfig_t, dir) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_MotorPosSensorConfig { \
    "MotorPosSensorConfig", \
    5, \
    {  { "enc_line_p_n", NULL, MAVLINK_TYPE_UINT32_T, 0, 8, offsetof(mavlink_motorpossensorconfig_t, enc_line_p_n) }, \
         { "init_pos_p", NULL, MAVLINK_TYPE_INT64_T, 0, 0, offsetof(mavlink_motorpossensorconfig_t, init_pos_p) }, \
         { "pn", NULL, MAVLINK_TYPE_UINT32_T, 0, 12, offsetof(mavlink_motorpossensorconfig_t, pn) }, \
         { "elec_angle_bias_rad", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_motorpossensorconfig_t, elec_angle_bias_rad) }, \
         { "dir", NULL, MAVLINK_TYPE_INT8_T, 0, 20, offsetof(mavlink_motorpossensorconfig_t, dir) }, \
         } \
}
#endif

/**
 * @brief Pack a motorpossensorconfig message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param enc_line_p_n  
 * @param init_pos_p  
 * @param pn  
 * @param elec_angle_bias_rad  
 * @param dir  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_motorpossensorconfig_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint32_t enc_line_p_n, int64_t init_pos_p, uint32_t pn, float elec_angle_bias_rad, int8_t dir)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MotorPosSensorConfig_LEN];
    _mav_put_int64_t(buf, 0, init_pos_p);
    _mav_put_uint32_t(buf, 8, enc_line_p_n);
    _mav_put_uint32_t(buf, 12, pn);
    _mav_put_float(buf, 16, elec_angle_bias_rad);
    _mav_put_int8_t(buf, 20, dir);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MotorPosSensorConfig_LEN);
#else
    mavlink_motorpossensorconfig_t packet;
    packet.init_pos_p = init_pos_p;
    packet.enc_line_p_n = enc_line_p_n;
    packet.pn = pn;
    packet.elec_angle_bias_rad = elec_angle_bias_rad;
    packet.dir = dir;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MotorPosSensorConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MotorPosSensorConfig;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_MotorPosSensorConfig_MIN_LEN, MAVLINK_MSG_ID_MotorPosSensorConfig_LEN, MAVLINK_MSG_ID_MotorPosSensorConfig_CRC);
}

/**
 * @brief Pack a motorpossensorconfig message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param enc_line_p_n  
 * @param init_pos_p  
 * @param pn  
 * @param elec_angle_bias_rad  
 * @param dir  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_motorpossensorconfig_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint32_t enc_line_p_n, int64_t init_pos_p, uint32_t pn, float elec_angle_bias_rad, int8_t dir)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MotorPosSensorConfig_LEN];
    _mav_put_int64_t(buf, 0, init_pos_p);
    _mav_put_uint32_t(buf, 8, enc_line_p_n);
    _mav_put_uint32_t(buf, 12, pn);
    _mav_put_float(buf, 16, elec_angle_bias_rad);
    _mav_put_int8_t(buf, 20, dir);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MotorPosSensorConfig_LEN);
#else
    mavlink_motorpossensorconfig_t packet;
    packet.init_pos_p = init_pos_p;
    packet.enc_line_p_n = enc_line_p_n;
    packet.pn = pn;
    packet.elec_angle_bias_rad = elec_angle_bias_rad;
    packet.dir = dir;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MotorPosSensorConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MotorPosSensorConfig;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_MotorPosSensorConfig_MIN_LEN, MAVLINK_MSG_ID_MotorPosSensorConfig_LEN, MAVLINK_MSG_ID_MotorPosSensorConfig_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_MotorPosSensorConfig_MIN_LEN, MAVLINK_MSG_ID_MotorPosSensorConfig_LEN);
#endif
}

/**
 * @brief Pack a motorpossensorconfig message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param enc_line_p_n  
 * @param init_pos_p  
 * @param pn  
 * @param elec_angle_bias_rad  
 * @param dir  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_motorpossensorconfig_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint32_t enc_line_p_n,int64_t init_pos_p,uint32_t pn,float elec_angle_bias_rad,int8_t dir)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MotorPosSensorConfig_LEN];
    _mav_put_int64_t(buf, 0, init_pos_p);
    _mav_put_uint32_t(buf, 8, enc_line_p_n);
    _mav_put_uint32_t(buf, 12, pn);
    _mav_put_float(buf, 16, elec_angle_bias_rad);
    _mav_put_int8_t(buf, 20, dir);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MotorPosSensorConfig_LEN);
#else
    mavlink_motorpossensorconfig_t packet;
    packet.init_pos_p = init_pos_p;
    packet.enc_line_p_n = enc_line_p_n;
    packet.pn = pn;
    packet.elec_angle_bias_rad = elec_angle_bias_rad;
    packet.dir = dir;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MotorPosSensorConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MotorPosSensorConfig;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_MotorPosSensorConfig_MIN_LEN, MAVLINK_MSG_ID_MotorPosSensorConfig_LEN, MAVLINK_MSG_ID_MotorPosSensorConfig_CRC);
}

/**
 * @brief Encode a motorpossensorconfig struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param motorpossensorconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_motorpossensorconfig_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_motorpossensorconfig_t* motorpossensorconfig)
{
    return mavlink_msg_motorpossensorconfig_pack(system_id, component_id, msg, motorpossensorconfig->enc_line_p_n, motorpossensorconfig->init_pos_p, motorpossensorconfig->pn, motorpossensorconfig->elec_angle_bias_rad, motorpossensorconfig->dir);
}

/**
 * @brief Encode a motorpossensorconfig struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param motorpossensorconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_motorpossensorconfig_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_motorpossensorconfig_t* motorpossensorconfig)
{
    return mavlink_msg_motorpossensorconfig_pack_chan(system_id, component_id, chan, msg, motorpossensorconfig->enc_line_p_n, motorpossensorconfig->init_pos_p, motorpossensorconfig->pn, motorpossensorconfig->elec_angle_bias_rad, motorpossensorconfig->dir);
}

/**
 * @brief Encode a motorpossensorconfig struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param motorpossensorconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_motorpossensorconfig_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_motorpossensorconfig_t* motorpossensorconfig)
{
    return mavlink_msg_motorpossensorconfig_pack_status(system_id, component_id, _status, msg,  motorpossensorconfig->enc_line_p_n, motorpossensorconfig->init_pos_p, motorpossensorconfig->pn, motorpossensorconfig->elec_angle_bias_rad, motorpossensorconfig->dir);
}

/**
 * @brief Send a motorpossensorconfig message
 * @param chan MAVLink channel to send the message
 *
 * @param enc_line_p_n  
 * @param init_pos_p  
 * @param pn  
 * @param elec_angle_bias_rad  
 * @param dir  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_motorpossensorconfig_send(mavlink_channel_t chan, uint32_t enc_line_p_n, int64_t init_pos_p, uint32_t pn, float elec_angle_bias_rad, int8_t dir)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MotorPosSensorConfig_LEN];
    _mav_put_int64_t(buf, 0, init_pos_p);
    _mav_put_uint32_t(buf, 8, enc_line_p_n);
    _mav_put_uint32_t(buf, 12, pn);
    _mav_put_float(buf, 16, elec_angle_bias_rad);
    _mav_put_int8_t(buf, 20, dir);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MotorPosSensorConfig, buf, MAVLINK_MSG_ID_MotorPosSensorConfig_MIN_LEN, MAVLINK_MSG_ID_MotorPosSensorConfig_LEN, MAVLINK_MSG_ID_MotorPosSensorConfig_CRC);
#else
    mavlink_motorpossensorconfig_t packet;
    packet.init_pos_p = init_pos_p;
    packet.enc_line_p_n = enc_line_p_n;
    packet.pn = pn;
    packet.elec_angle_bias_rad = elec_angle_bias_rad;
    packet.dir = dir;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MotorPosSensorConfig, (const char *)&packet, MAVLINK_MSG_ID_MotorPosSensorConfig_MIN_LEN, MAVLINK_MSG_ID_MotorPosSensorConfig_LEN, MAVLINK_MSG_ID_MotorPosSensorConfig_CRC);
#endif
}

/**
 * @brief Send a motorpossensorconfig message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_motorpossensorconfig_send_struct(mavlink_channel_t chan, const mavlink_motorpossensorconfig_t* motorpossensorconfig)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_motorpossensorconfig_send(chan, motorpossensorconfig->enc_line_p_n, motorpossensorconfig->init_pos_p, motorpossensorconfig->pn, motorpossensorconfig->elec_angle_bias_rad, motorpossensorconfig->dir);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MotorPosSensorConfig, (const char *)motorpossensorconfig, MAVLINK_MSG_ID_MotorPosSensorConfig_MIN_LEN, MAVLINK_MSG_ID_MotorPosSensorConfig_LEN, MAVLINK_MSG_ID_MotorPosSensorConfig_CRC);
#endif
}

#if MAVLINK_MSG_ID_MotorPosSensorConfig_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_motorpossensorconfig_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint32_t enc_line_p_n, int64_t init_pos_p, uint32_t pn, float elec_angle_bias_rad, int8_t dir)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_int64_t(buf, 0, init_pos_p);
    _mav_put_uint32_t(buf, 8, enc_line_p_n);
    _mav_put_uint32_t(buf, 12, pn);
    _mav_put_float(buf, 16, elec_angle_bias_rad);
    _mav_put_int8_t(buf, 20, dir);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MotorPosSensorConfig, buf, MAVLINK_MSG_ID_MotorPosSensorConfig_MIN_LEN, MAVLINK_MSG_ID_MotorPosSensorConfig_LEN, MAVLINK_MSG_ID_MotorPosSensorConfig_CRC);
#else
    mavlink_motorpossensorconfig_t *packet = (mavlink_motorpossensorconfig_t *)msgbuf;
    packet->init_pos_p = init_pos_p;
    packet->enc_line_p_n = enc_line_p_n;
    packet->pn = pn;
    packet->elec_angle_bias_rad = elec_angle_bias_rad;
    packet->dir = dir;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MotorPosSensorConfig, (const char *)packet, MAVLINK_MSG_ID_MotorPosSensorConfig_MIN_LEN, MAVLINK_MSG_ID_MotorPosSensorConfig_LEN, MAVLINK_MSG_ID_MotorPosSensorConfig_CRC);
#endif
}
#endif

#endif

// MESSAGE MotorPosSensorConfig UNPACKING


/**
 * @brief Get field enc_line_p_n from motorpossensorconfig message
 *
 * @return  
 */
static inline uint32_t mavlink_msg_motorpossensorconfig_get_enc_line_p_n(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  8);
}

/**
 * @brief Get field init_pos_p from motorpossensorconfig message
 *
 * @return  
 */
static inline int64_t mavlink_msg_motorpossensorconfig_get_init_pos_p(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int64_t(msg,  0);
}

/**
 * @brief Get field pn from motorpossensorconfig message
 *
 * @return  
 */
static inline uint32_t mavlink_msg_motorpossensorconfig_get_pn(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  12);
}

/**
 * @brief Get field elec_angle_bias_rad from motorpossensorconfig message
 *
 * @return  
 */
static inline float mavlink_msg_motorpossensorconfig_get_elec_angle_bias_rad(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  16);
}

/**
 * @brief Get field dir from motorpossensorconfig message
 *
 * @return  
 */
static inline int8_t mavlink_msg_motorpossensorconfig_get_dir(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int8_t(msg,  20);
}

/**
 * @brief Decode a motorpossensorconfig message into a struct
 *
 * @param msg The message to decode
 * @param motorpossensorconfig C-struct to decode the message contents into
 */
static inline void mavlink_msg_motorpossensorconfig_decode(const mavlink_message_t* msg, mavlink_motorpossensorconfig_t* motorpossensorconfig)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    motorpossensorconfig->init_pos_p = mavlink_msg_motorpossensorconfig_get_init_pos_p(msg);
    motorpossensorconfig->enc_line_p_n = mavlink_msg_motorpossensorconfig_get_enc_line_p_n(msg);
    motorpossensorconfig->pn = mavlink_msg_motorpossensorconfig_get_pn(msg);
    motorpossensorconfig->elec_angle_bias_rad = mavlink_msg_motorpossensorconfig_get_elec_angle_bias_rad(msg);
    motorpossensorconfig->dir = mavlink_msg_motorpossensorconfig_get_dir(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_MotorPosSensorConfig_LEN? msg->len : MAVLINK_MSG_ID_MotorPosSensorConfig_LEN;
        memset(motorpossensorconfig, 0, MAVLINK_MSG_ID_MotorPosSensorConfig_LEN);
    memcpy(motorpossensorconfig, _MAV_PAYLOAD(msg), len);
#endif
}
