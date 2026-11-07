#pragma once
// MESSAGE MecIdConfig PACKING

#define MAVLINK_MSG_ID_MecIdConfig 30006


typedef struct __mavlink_mecidconfig_t {
 float dt_s; /*<  */
 float end_fs_Hz; /*<  */
 float start_fs_Hz; /*<  */
 float target_time_s; /*<  */
 float i_max_A; /*<  */
 float search_speed_max_rad_s; /*<  */
 float wait_time_s; /*<  */
 uint8_t signal_type; /*<  */
} mavlink_mecidconfig_t;

#define MAVLINK_MSG_ID_MecIdConfig_LEN 29
#define MAVLINK_MSG_ID_MecIdConfig_MIN_LEN 29
#define MAVLINK_MSG_ID_30006_LEN 29
#define MAVLINK_MSG_ID_30006_MIN_LEN 29

#define MAVLINK_MSG_ID_MecIdConfig_CRC 65
#define MAVLINK_MSG_ID_30006_CRC 65



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_MecIdConfig { \
    30006, \
    "MecIdConfig", \
    8, \
    {  { "dt_s", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_mecidconfig_t, dt_s) }, \
         { "end_fs_Hz", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_mecidconfig_t, end_fs_Hz) }, \
         { "start_fs_Hz", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_mecidconfig_t, start_fs_Hz) }, \
         { "target_time_s", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_mecidconfig_t, target_time_s) }, \
         { "i_max_A", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_mecidconfig_t, i_max_A) }, \
         { "search_speed_max_rad_s", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_mecidconfig_t, search_speed_max_rad_s) }, \
         { "wait_time_s", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_mecidconfig_t, wait_time_s) }, \
         { "signal_type", NULL, MAVLINK_TYPE_UINT8_T, 0, 28, offsetof(mavlink_mecidconfig_t, signal_type) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_MecIdConfig { \
    "MecIdConfig", \
    8, \
    {  { "dt_s", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_mecidconfig_t, dt_s) }, \
         { "end_fs_Hz", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_mecidconfig_t, end_fs_Hz) }, \
         { "start_fs_Hz", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_mecidconfig_t, start_fs_Hz) }, \
         { "target_time_s", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_mecidconfig_t, target_time_s) }, \
         { "i_max_A", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_mecidconfig_t, i_max_A) }, \
         { "search_speed_max_rad_s", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_mecidconfig_t, search_speed_max_rad_s) }, \
         { "wait_time_s", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_mecidconfig_t, wait_time_s) }, \
         { "signal_type", NULL, MAVLINK_TYPE_UINT8_T, 0, 28, offsetof(mavlink_mecidconfig_t, signal_type) }, \
         } \
}
#endif

/**
 * @brief Pack a mecidconfig message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param dt_s  
 * @param end_fs_Hz  
 * @param start_fs_Hz  
 * @param target_time_s  
 * @param i_max_A  
 * @param search_speed_max_rad_s  
 * @param wait_time_s  
 * @param signal_type  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_mecidconfig_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               float dt_s, float end_fs_Hz, float start_fs_Hz, float target_time_s, float i_max_A, float search_speed_max_rad_s, float wait_time_s, uint8_t signal_type)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MecIdConfig_LEN];
    _mav_put_float(buf, 0, dt_s);
    _mav_put_float(buf, 4, end_fs_Hz);
    _mav_put_float(buf, 8, start_fs_Hz);
    _mav_put_float(buf, 12, target_time_s);
    _mav_put_float(buf, 16, i_max_A);
    _mav_put_float(buf, 20, search_speed_max_rad_s);
    _mav_put_float(buf, 24, wait_time_s);
    _mav_put_uint8_t(buf, 28, signal_type);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MecIdConfig_LEN);
#else
    mavlink_mecidconfig_t packet;
    packet.dt_s = dt_s;
    packet.end_fs_Hz = end_fs_Hz;
    packet.start_fs_Hz = start_fs_Hz;
    packet.target_time_s = target_time_s;
    packet.i_max_A = i_max_A;
    packet.search_speed_max_rad_s = search_speed_max_rad_s;
    packet.wait_time_s = wait_time_s;
    packet.signal_type = signal_type;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MecIdConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MecIdConfig;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_MecIdConfig_MIN_LEN, MAVLINK_MSG_ID_MecIdConfig_LEN, MAVLINK_MSG_ID_MecIdConfig_CRC);
}

/**
 * @brief Pack a mecidconfig message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param dt_s  
 * @param end_fs_Hz  
 * @param start_fs_Hz  
 * @param target_time_s  
 * @param i_max_A  
 * @param search_speed_max_rad_s  
 * @param wait_time_s  
 * @param signal_type  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_mecidconfig_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               float dt_s, float end_fs_Hz, float start_fs_Hz, float target_time_s, float i_max_A, float search_speed_max_rad_s, float wait_time_s, uint8_t signal_type)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MecIdConfig_LEN];
    _mav_put_float(buf, 0, dt_s);
    _mav_put_float(buf, 4, end_fs_Hz);
    _mav_put_float(buf, 8, start_fs_Hz);
    _mav_put_float(buf, 12, target_time_s);
    _mav_put_float(buf, 16, i_max_A);
    _mav_put_float(buf, 20, search_speed_max_rad_s);
    _mav_put_float(buf, 24, wait_time_s);
    _mav_put_uint8_t(buf, 28, signal_type);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MecIdConfig_LEN);
#else
    mavlink_mecidconfig_t packet;
    packet.dt_s = dt_s;
    packet.end_fs_Hz = end_fs_Hz;
    packet.start_fs_Hz = start_fs_Hz;
    packet.target_time_s = target_time_s;
    packet.i_max_A = i_max_A;
    packet.search_speed_max_rad_s = search_speed_max_rad_s;
    packet.wait_time_s = wait_time_s;
    packet.signal_type = signal_type;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MecIdConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MecIdConfig;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_MecIdConfig_MIN_LEN, MAVLINK_MSG_ID_MecIdConfig_LEN, MAVLINK_MSG_ID_MecIdConfig_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_MecIdConfig_MIN_LEN, MAVLINK_MSG_ID_MecIdConfig_LEN);
#endif
}

/**
 * @brief Pack a mecidconfig message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param dt_s  
 * @param end_fs_Hz  
 * @param start_fs_Hz  
 * @param target_time_s  
 * @param i_max_A  
 * @param search_speed_max_rad_s  
 * @param wait_time_s  
 * @param signal_type  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_mecidconfig_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   float dt_s,float end_fs_Hz,float start_fs_Hz,float target_time_s,float i_max_A,float search_speed_max_rad_s,float wait_time_s,uint8_t signal_type)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MecIdConfig_LEN];
    _mav_put_float(buf, 0, dt_s);
    _mav_put_float(buf, 4, end_fs_Hz);
    _mav_put_float(buf, 8, start_fs_Hz);
    _mav_put_float(buf, 12, target_time_s);
    _mav_put_float(buf, 16, i_max_A);
    _mav_put_float(buf, 20, search_speed_max_rad_s);
    _mav_put_float(buf, 24, wait_time_s);
    _mav_put_uint8_t(buf, 28, signal_type);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MecIdConfig_LEN);
#else
    mavlink_mecidconfig_t packet;
    packet.dt_s = dt_s;
    packet.end_fs_Hz = end_fs_Hz;
    packet.start_fs_Hz = start_fs_Hz;
    packet.target_time_s = target_time_s;
    packet.i_max_A = i_max_A;
    packet.search_speed_max_rad_s = search_speed_max_rad_s;
    packet.wait_time_s = wait_time_s;
    packet.signal_type = signal_type;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MecIdConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MecIdConfig;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_MecIdConfig_MIN_LEN, MAVLINK_MSG_ID_MecIdConfig_LEN, MAVLINK_MSG_ID_MecIdConfig_CRC);
}

/**
 * @brief Encode a mecidconfig struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param mecidconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_mecidconfig_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_mecidconfig_t* mecidconfig)
{
    return mavlink_msg_mecidconfig_pack(system_id, component_id, msg, mecidconfig->dt_s, mecidconfig->end_fs_Hz, mecidconfig->start_fs_Hz, mecidconfig->target_time_s, mecidconfig->i_max_A, mecidconfig->search_speed_max_rad_s, mecidconfig->wait_time_s, mecidconfig->signal_type);
}

/**
 * @brief Encode a mecidconfig struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param mecidconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_mecidconfig_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_mecidconfig_t* mecidconfig)
{
    return mavlink_msg_mecidconfig_pack_chan(system_id, component_id, chan, msg, mecidconfig->dt_s, mecidconfig->end_fs_Hz, mecidconfig->start_fs_Hz, mecidconfig->target_time_s, mecidconfig->i_max_A, mecidconfig->search_speed_max_rad_s, mecidconfig->wait_time_s, mecidconfig->signal_type);
}

/**
 * @brief Encode a mecidconfig struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param mecidconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_mecidconfig_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_mecidconfig_t* mecidconfig)
{
    return mavlink_msg_mecidconfig_pack_status(system_id, component_id, _status, msg,  mecidconfig->dt_s, mecidconfig->end_fs_Hz, mecidconfig->start_fs_Hz, mecidconfig->target_time_s, mecidconfig->i_max_A, mecidconfig->search_speed_max_rad_s, mecidconfig->wait_time_s, mecidconfig->signal_type);
}

/**
 * @brief Send a mecidconfig message
 * @param chan MAVLink channel to send the message
 *
 * @param dt_s  
 * @param end_fs_Hz  
 * @param start_fs_Hz  
 * @param target_time_s  
 * @param i_max_A  
 * @param search_speed_max_rad_s  
 * @param wait_time_s  
 * @param signal_type  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_mecidconfig_send(mavlink_channel_t chan, float dt_s, float end_fs_Hz, float start_fs_Hz, float target_time_s, float i_max_A, float search_speed_max_rad_s, float wait_time_s, uint8_t signal_type)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MecIdConfig_LEN];
    _mav_put_float(buf, 0, dt_s);
    _mav_put_float(buf, 4, end_fs_Hz);
    _mav_put_float(buf, 8, start_fs_Hz);
    _mav_put_float(buf, 12, target_time_s);
    _mav_put_float(buf, 16, i_max_A);
    _mav_put_float(buf, 20, search_speed_max_rad_s);
    _mav_put_float(buf, 24, wait_time_s);
    _mav_put_uint8_t(buf, 28, signal_type);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MecIdConfig, buf, MAVLINK_MSG_ID_MecIdConfig_MIN_LEN, MAVLINK_MSG_ID_MecIdConfig_LEN, MAVLINK_MSG_ID_MecIdConfig_CRC);
#else
    mavlink_mecidconfig_t packet;
    packet.dt_s = dt_s;
    packet.end_fs_Hz = end_fs_Hz;
    packet.start_fs_Hz = start_fs_Hz;
    packet.target_time_s = target_time_s;
    packet.i_max_A = i_max_A;
    packet.search_speed_max_rad_s = search_speed_max_rad_s;
    packet.wait_time_s = wait_time_s;
    packet.signal_type = signal_type;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MecIdConfig, (const char *)&packet, MAVLINK_MSG_ID_MecIdConfig_MIN_LEN, MAVLINK_MSG_ID_MecIdConfig_LEN, MAVLINK_MSG_ID_MecIdConfig_CRC);
#endif
}

/**
 * @brief Send a mecidconfig message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_mecidconfig_send_struct(mavlink_channel_t chan, const mavlink_mecidconfig_t* mecidconfig)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_mecidconfig_send(chan, mecidconfig->dt_s, mecidconfig->end_fs_Hz, mecidconfig->start_fs_Hz, mecidconfig->target_time_s, mecidconfig->i_max_A, mecidconfig->search_speed_max_rad_s, mecidconfig->wait_time_s, mecidconfig->signal_type);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MecIdConfig, (const char *)mecidconfig, MAVLINK_MSG_ID_MecIdConfig_MIN_LEN, MAVLINK_MSG_ID_MecIdConfig_LEN, MAVLINK_MSG_ID_MecIdConfig_CRC);
#endif
}

#if MAVLINK_MSG_ID_MecIdConfig_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_mecidconfig_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float dt_s, float end_fs_Hz, float start_fs_Hz, float target_time_s, float i_max_A, float search_speed_max_rad_s, float wait_time_s, uint8_t signal_type)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, dt_s);
    _mav_put_float(buf, 4, end_fs_Hz);
    _mav_put_float(buf, 8, start_fs_Hz);
    _mav_put_float(buf, 12, target_time_s);
    _mav_put_float(buf, 16, i_max_A);
    _mav_put_float(buf, 20, search_speed_max_rad_s);
    _mav_put_float(buf, 24, wait_time_s);
    _mav_put_uint8_t(buf, 28, signal_type);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MecIdConfig, buf, MAVLINK_MSG_ID_MecIdConfig_MIN_LEN, MAVLINK_MSG_ID_MecIdConfig_LEN, MAVLINK_MSG_ID_MecIdConfig_CRC);
#else
    mavlink_mecidconfig_t *packet = (mavlink_mecidconfig_t *)msgbuf;
    packet->dt_s = dt_s;
    packet->end_fs_Hz = end_fs_Hz;
    packet->start_fs_Hz = start_fs_Hz;
    packet->target_time_s = target_time_s;
    packet->i_max_A = i_max_A;
    packet->search_speed_max_rad_s = search_speed_max_rad_s;
    packet->wait_time_s = wait_time_s;
    packet->signal_type = signal_type;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MecIdConfig, (const char *)packet, MAVLINK_MSG_ID_MecIdConfig_MIN_LEN, MAVLINK_MSG_ID_MecIdConfig_LEN, MAVLINK_MSG_ID_MecIdConfig_CRC);
#endif
}
#endif

#endif

// MESSAGE MecIdConfig UNPACKING


/**
 * @brief Get field dt_s from mecidconfig message
 *
 * @return  
 */
static inline float mavlink_msg_mecidconfig_get_dt_s(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field end_fs_Hz from mecidconfig message
 *
 * @return  
 */
static inline float mavlink_msg_mecidconfig_get_end_fs_Hz(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field start_fs_Hz from mecidconfig message
 *
 * @return  
 */
static inline float mavlink_msg_mecidconfig_get_start_fs_Hz(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field target_time_s from mecidconfig message
 *
 * @return  
 */
static inline float mavlink_msg_mecidconfig_get_target_time_s(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Get field i_max_A from mecidconfig message
 *
 * @return  
 */
static inline float mavlink_msg_mecidconfig_get_i_max_A(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  16);
}

/**
 * @brief Get field search_speed_max_rad_s from mecidconfig message
 *
 * @return  
 */
static inline float mavlink_msg_mecidconfig_get_search_speed_max_rad_s(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  20);
}

/**
 * @brief Get field wait_time_s from mecidconfig message
 *
 * @return  
 */
static inline float mavlink_msg_mecidconfig_get_wait_time_s(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  24);
}

/**
 * @brief Get field signal_type from mecidconfig message
 *
 * @return  
 */
static inline uint8_t mavlink_msg_mecidconfig_get_signal_type(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  28);
}

/**
 * @brief Decode a mecidconfig message into a struct
 *
 * @param msg The message to decode
 * @param mecidconfig C-struct to decode the message contents into
 */
static inline void mavlink_msg_mecidconfig_decode(const mavlink_message_t* msg, mavlink_mecidconfig_t* mecidconfig)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mecidconfig->dt_s = mavlink_msg_mecidconfig_get_dt_s(msg);
    mecidconfig->end_fs_Hz = mavlink_msg_mecidconfig_get_end_fs_Hz(msg);
    mecidconfig->start_fs_Hz = mavlink_msg_mecidconfig_get_start_fs_Hz(msg);
    mecidconfig->target_time_s = mavlink_msg_mecidconfig_get_target_time_s(msg);
    mecidconfig->i_max_A = mavlink_msg_mecidconfig_get_i_max_A(msg);
    mecidconfig->search_speed_max_rad_s = mavlink_msg_mecidconfig_get_search_speed_max_rad_s(msg);
    mecidconfig->wait_time_s = mavlink_msg_mecidconfig_get_wait_time_s(msg);
    mecidconfig->signal_type = mavlink_msg_mecidconfig_get_signal_type(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_MecIdConfig_LEN? msg->len : MAVLINK_MSG_ID_MecIdConfig_LEN;
        memset(mecidconfig, 0, MAVLINK_MSG_ID_MecIdConfig_LEN);
    memcpy(mecidconfig, _MAV_PAYLOAD(msg), len);
#endif
}
