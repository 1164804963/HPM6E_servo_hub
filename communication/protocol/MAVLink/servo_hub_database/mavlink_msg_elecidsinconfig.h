#pragma once
// MESSAGE ElecIdSinConfig PACKING

#define MAVLINK_MSG_ID_ElecIdSinConfig 30004


typedef struct __mavlink_elecidsinconfig_t {
 float dt_s; /*<  */
 float end_fs_Hz; /*<  */
 float i_max_A; /*<  */
 float init_fs_Hz; /*<  */
 float target_time_s; /*<  */
 float u_max_V; /*<  */
 float wait_time_s; /*<  */
} mavlink_elecidsinconfig_t;

#define MAVLINK_MSG_ID_ElecIdSinConfig_LEN 28
#define MAVLINK_MSG_ID_ElecIdSinConfig_MIN_LEN 28
#define MAVLINK_MSG_ID_30004_LEN 28
#define MAVLINK_MSG_ID_30004_MIN_LEN 28

#define MAVLINK_MSG_ID_ElecIdSinConfig_CRC 72
#define MAVLINK_MSG_ID_30004_CRC 72



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_ElecIdSinConfig { \
    30004, \
    "ElecIdSinConfig", \
    7, \
    {  { "dt_s", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_elecidsinconfig_t, dt_s) }, \
         { "end_fs_Hz", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_elecidsinconfig_t, end_fs_Hz) }, \
         { "i_max_A", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_elecidsinconfig_t, i_max_A) }, \
         { "init_fs_Hz", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_elecidsinconfig_t, init_fs_Hz) }, \
         { "target_time_s", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_elecidsinconfig_t, target_time_s) }, \
         { "u_max_V", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_elecidsinconfig_t, u_max_V) }, \
         { "wait_time_s", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_elecidsinconfig_t, wait_time_s) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_ElecIdSinConfig { \
    "ElecIdSinConfig", \
    7, \
    {  { "dt_s", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_elecidsinconfig_t, dt_s) }, \
         { "end_fs_Hz", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_elecidsinconfig_t, end_fs_Hz) }, \
         { "i_max_A", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_elecidsinconfig_t, i_max_A) }, \
         { "init_fs_Hz", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_elecidsinconfig_t, init_fs_Hz) }, \
         { "target_time_s", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_elecidsinconfig_t, target_time_s) }, \
         { "u_max_V", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_elecidsinconfig_t, u_max_V) }, \
         { "wait_time_s", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_elecidsinconfig_t, wait_time_s) }, \
         } \
}
#endif

/**
 * @brief Pack a elecidsinconfig message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param dt_s  
 * @param end_fs_Hz  
 * @param i_max_A  
 * @param init_fs_Hz  
 * @param target_time_s  
 * @param u_max_V  
 * @param wait_time_s  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_elecidsinconfig_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               float dt_s, float end_fs_Hz, float i_max_A, float init_fs_Hz, float target_time_s, float u_max_V, float wait_time_s)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ElecIdSinConfig_LEN];
    _mav_put_float(buf, 0, dt_s);
    _mav_put_float(buf, 4, end_fs_Hz);
    _mav_put_float(buf, 8, i_max_A);
    _mav_put_float(buf, 12, init_fs_Hz);
    _mav_put_float(buf, 16, target_time_s);
    _mav_put_float(buf, 20, u_max_V);
    _mav_put_float(buf, 24, wait_time_s);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ElecIdSinConfig_LEN);
#else
    mavlink_elecidsinconfig_t packet;
    packet.dt_s = dt_s;
    packet.end_fs_Hz = end_fs_Hz;
    packet.i_max_A = i_max_A;
    packet.init_fs_Hz = init_fs_Hz;
    packet.target_time_s = target_time_s;
    packet.u_max_V = u_max_V;
    packet.wait_time_s = wait_time_s;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ElecIdSinConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ElecIdSinConfig;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_ElecIdSinConfig_MIN_LEN, MAVLINK_MSG_ID_ElecIdSinConfig_LEN, MAVLINK_MSG_ID_ElecIdSinConfig_CRC);
}

/**
 * @brief Pack a elecidsinconfig message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param dt_s  
 * @param end_fs_Hz  
 * @param i_max_A  
 * @param init_fs_Hz  
 * @param target_time_s  
 * @param u_max_V  
 * @param wait_time_s  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_elecidsinconfig_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               float dt_s, float end_fs_Hz, float i_max_A, float init_fs_Hz, float target_time_s, float u_max_V, float wait_time_s)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ElecIdSinConfig_LEN];
    _mav_put_float(buf, 0, dt_s);
    _mav_put_float(buf, 4, end_fs_Hz);
    _mav_put_float(buf, 8, i_max_A);
    _mav_put_float(buf, 12, init_fs_Hz);
    _mav_put_float(buf, 16, target_time_s);
    _mav_put_float(buf, 20, u_max_V);
    _mav_put_float(buf, 24, wait_time_s);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ElecIdSinConfig_LEN);
#else
    mavlink_elecidsinconfig_t packet;
    packet.dt_s = dt_s;
    packet.end_fs_Hz = end_fs_Hz;
    packet.i_max_A = i_max_A;
    packet.init_fs_Hz = init_fs_Hz;
    packet.target_time_s = target_time_s;
    packet.u_max_V = u_max_V;
    packet.wait_time_s = wait_time_s;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ElecIdSinConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ElecIdSinConfig;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_ElecIdSinConfig_MIN_LEN, MAVLINK_MSG_ID_ElecIdSinConfig_LEN, MAVLINK_MSG_ID_ElecIdSinConfig_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_ElecIdSinConfig_MIN_LEN, MAVLINK_MSG_ID_ElecIdSinConfig_LEN);
#endif
}

/**
 * @brief Pack a elecidsinconfig message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param dt_s  
 * @param end_fs_Hz  
 * @param i_max_A  
 * @param init_fs_Hz  
 * @param target_time_s  
 * @param u_max_V  
 * @param wait_time_s  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_elecidsinconfig_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   float dt_s,float end_fs_Hz,float i_max_A,float init_fs_Hz,float target_time_s,float u_max_V,float wait_time_s)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ElecIdSinConfig_LEN];
    _mav_put_float(buf, 0, dt_s);
    _mav_put_float(buf, 4, end_fs_Hz);
    _mav_put_float(buf, 8, i_max_A);
    _mav_put_float(buf, 12, init_fs_Hz);
    _mav_put_float(buf, 16, target_time_s);
    _mav_put_float(buf, 20, u_max_V);
    _mav_put_float(buf, 24, wait_time_s);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ElecIdSinConfig_LEN);
#else
    mavlink_elecidsinconfig_t packet;
    packet.dt_s = dt_s;
    packet.end_fs_Hz = end_fs_Hz;
    packet.i_max_A = i_max_A;
    packet.init_fs_Hz = init_fs_Hz;
    packet.target_time_s = target_time_s;
    packet.u_max_V = u_max_V;
    packet.wait_time_s = wait_time_s;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ElecIdSinConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ElecIdSinConfig;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_ElecIdSinConfig_MIN_LEN, MAVLINK_MSG_ID_ElecIdSinConfig_LEN, MAVLINK_MSG_ID_ElecIdSinConfig_CRC);
}

/**
 * @brief Encode a elecidsinconfig struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param elecidsinconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_elecidsinconfig_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_elecidsinconfig_t* elecidsinconfig)
{
    return mavlink_msg_elecidsinconfig_pack(system_id, component_id, msg, elecidsinconfig->dt_s, elecidsinconfig->end_fs_Hz, elecidsinconfig->i_max_A, elecidsinconfig->init_fs_Hz, elecidsinconfig->target_time_s, elecidsinconfig->u_max_V, elecidsinconfig->wait_time_s);
}

/**
 * @brief Encode a elecidsinconfig struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param elecidsinconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_elecidsinconfig_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_elecidsinconfig_t* elecidsinconfig)
{
    return mavlink_msg_elecidsinconfig_pack_chan(system_id, component_id, chan, msg, elecidsinconfig->dt_s, elecidsinconfig->end_fs_Hz, elecidsinconfig->i_max_A, elecidsinconfig->init_fs_Hz, elecidsinconfig->target_time_s, elecidsinconfig->u_max_V, elecidsinconfig->wait_time_s);
}

/**
 * @brief Encode a elecidsinconfig struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param elecidsinconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_elecidsinconfig_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_elecidsinconfig_t* elecidsinconfig)
{
    return mavlink_msg_elecidsinconfig_pack_status(system_id, component_id, _status, msg,  elecidsinconfig->dt_s, elecidsinconfig->end_fs_Hz, elecidsinconfig->i_max_A, elecidsinconfig->init_fs_Hz, elecidsinconfig->target_time_s, elecidsinconfig->u_max_V, elecidsinconfig->wait_time_s);
}

/**
 * @brief Send a elecidsinconfig message
 * @param chan MAVLink channel to send the message
 *
 * @param dt_s  
 * @param end_fs_Hz  
 * @param i_max_A  
 * @param init_fs_Hz  
 * @param target_time_s  
 * @param u_max_V  
 * @param wait_time_s  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_elecidsinconfig_send(mavlink_channel_t chan, float dt_s, float end_fs_Hz, float i_max_A, float init_fs_Hz, float target_time_s, float u_max_V, float wait_time_s)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ElecIdSinConfig_LEN];
    _mav_put_float(buf, 0, dt_s);
    _mav_put_float(buf, 4, end_fs_Hz);
    _mav_put_float(buf, 8, i_max_A);
    _mav_put_float(buf, 12, init_fs_Hz);
    _mav_put_float(buf, 16, target_time_s);
    _mav_put_float(buf, 20, u_max_V);
    _mav_put_float(buf, 24, wait_time_s);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ElecIdSinConfig, buf, MAVLINK_MSG_ID_ElecIdSinConfig_MIN_LEN, MAVLINK_MSG_ID_ElecIdSinConfig_LEN, MAVLINK_MSG_ID_ElecIdSinConfig_CRC);
#else
    mavlink_elecidsinconfig_t packet;
    packet.dt_s = dt_s;
    packet.end_fs_Hz = end_fs_Hz;
    packet.i_max_A = i_max_A;
    packet.init_fs_Hz = init_fs_Hz;
    packet.target_time_s = target_time_s;
    packet.u_max_V = u_max_V;
    packet.wait_time_s = wait_time_s;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ElecIdSinConfig, (const char *)&packet, MAVLINK_MSG_ID_ElecIdSinConfig_MIN_LEN, MAVLINK_MSG_ID_ElecIdSinConfig_LEN, MAVLINK_MSG_ID_ElecIdSinConfig_CRC);
#endif
}

/**
 * @brief Send a elecidsinconfig message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_elecidsinconfig_send_struct(mavlink_channel_t chan, const mavlink_elecidsinconfig_t* elecidsinconfig)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_elecidsinconfig_send(chan, elecidsinconfig->dt_s, elecidsinconfig->end_fs_Hz, elecidsinconfig->i_max_A, elecidsinconfig->init_fs_Hz, elecidsinconfig->target_time_s, elecidsinconfig->u_max_V, elecidsinconfig->wait_time_s);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ElecIdSinConfig, (const char *)elecidsinconfig, MAVLINK_MSG_ID_ElecIdSinConfig_MIN_LEN, MAVLINK_MSG_ID_ElecIdSinConfig_LEN, MAVLINK_MSG_ID_ElecIdSinConfig_CRC);
#endif
}

#if MAVLINK_MSG_ID_ElecIdSinConfig_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_elecidsinconfig_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float dt_s, float end_fs_Hz, float i_max_A, float init_fs_Hz, float target_time_s, float u_max_V, float wait_time_s)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, dt_s);
    _mav_put_float(buf, 4, end_fs_Hz);
    _mav_put_float(buf, 8, i_max_A);
    _mav_put_float(buf, 12, init_fs_Hz);
    _mav_put_float(buf, 16, target_time_s);
    _mav_put_float(buf, 20, u_max_V);
    _mav_put_float(buf, 24, wait_time_s);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ElecIdSinConfig, buf, MAVLINK_MSG_ID_ElecIdSinConfig_MIN_LEN, MAVLINK_MSG_ID_ElecIdSinConfig_LEN, MAVLINK_MSG_ID_ElecIdSinConfig_CRC);
#else
    mavlink_elecidsinconfig_t *packet = (mavlink_elecidsinconfig_t *)msgbuf;
    packet->dt_s = dt_s;
    packet->end_fs_Hz = end_fs_Hz;
    packet->i_max_A = i_max_A;
    packet->init_fs_Hz = init_fs_Hz;
    packet->target_time_s = target_time_s;
    packet->u_max_V = u_max_V;
    packet->wait_time_s = wait_time_s;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ElecIdSinConfig, (const char *)packet, MAVLINK_MSG_ID_ElecIdSinConfig_MIN_LEN, MAVLINK_MSG_ID_ElecIdSinConfig_LEN, MAVLINK_MSG_ID_ElecIdSinConfig_CRC);
#endif
}
#endif

#endif

// MESSAGE ElecIdSinConfig UNPACKING


/**
 * @brief Get field dt_s from elecidsinconfig message
 *
 * @return  
 */
static inline float mavlink_msg_elecidsinconfig_get_dt_s(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field end_fs_Hz from elecidsinconfig message
 *
 * @return  
 */
static inline float mavlink_msg_elecidsinconfig_get_end_fs_Hz(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field i_max_A from elecidsinconfig message
 *
 * @return  
 */
static inline float mavlink_msg_elecidsinconfig_get_i_max_A(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field init_fs_Hz from elecidsinconfig message
 *
 * @return  
 */
static inline float mavlink_msg_elecidsinconfig_get_init_fs_Hz(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Get field target_time_s from elecidsinconfig message
 *
 * @return  
 */
static inline float mavlink_msg_elecidsinconfig_get_target_time_s(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  16);
}

/**
 * @brief Get field u_max_V from elecidsinconfig message
 *
 * @return  
 */
static inline float mavlink_msg_elecidsinconfig_get_u_max_V(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  20);
}

/**
 * @brief Get field wait_time_s from elecidsinconfig message
 *
 * @return  
 */
static inline float mavlink_msg_elecidsinconfig_get_wait_time_s(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  24);
}

/**
 * @brief Decode a elecidsinconfig message into a struct
 *
 * @param msg The message to decode
 * @param elecidsinconfig C-struct to decode the message contents into
 */
static inline void mavlink_msg_elecidsinconfig_decode(const mavlink_message_t* msg, mavlink_elecidsinconfig_t* elecidsinconfig)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    elecidsinconfig->dt_s = mavlink_msg_elecidsinconfig_get_dt_s(msg);
    elecidsinconfig->end_fs_Hz = mavlink_msg_elecidsinconfig_get_end_fs_Hz(msg);
    elecidsinconfig->i_max_A = mavlink_msg_elecidsinconfig_get_i_max_A(msg);
    elecidsinconfig->init_fs_Hz = mavlink_msg_elecidsinconfig_get_init_fs_Hz(msg);
    elecidsinconfig->target_time_s = mavlink_msg_elecidsinconfig_get_target_time_s(msg);
    elecidsinconfig->u_max_V = mavlink_msg_elecidsinconfig_get_u_max_V(msg);
    elecidsinconfig->wait_time_s = mavlink_msg_elecidsinconfig_get_wait_time_s(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_ElecIdSinConfig_LEN? msg->len : MAVLINK_MSG_ID_ElecIdSinConfig_LEN;
        memset(elecidsinconfig, 0, MAVLINK_MSG_ID_ElecIdSinConfig_LEN);
    memcpy(elecidsinconfig, _MAV_PAYLOAD(msg), len);
#endif
}
