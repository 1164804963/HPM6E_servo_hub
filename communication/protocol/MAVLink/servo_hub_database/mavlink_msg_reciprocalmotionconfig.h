#pragma once
// MESSAGE ReciprocalMotionConfig PACKING

#define MAVLINK_MSG_ID_ReciprocalMotionConfig 30050


typedef struct __mavlink_reciprocalmotionconfig_t {
 int64_t pos_tar1_p; /*<  */
 int64_t pos_tar2_p; /*<  */
 float dwell_time_s; /*<  */
 float profile_velocity_p_s; /*<  */
 float profile_acc_p_ss; /*<  */
 float profile_dec_p_ss; /*<  */
 float dt_s; /*<  */
} mavlink_reciprocalmotionconfig_t;

#define MAVLINK_MSG_ID_ReciprocalMotionConfig_LEN 36
#define MAVLINK_MSG_ID_ReciprocalMotionConfig_MIN_LEN 36
#define MAVLINK_MSG_ID_30050_LEN 36
#define MAVLINK_MSG_ID_30050_MIN_LEN 36

#define MAVLINK_MSG_ID_ReciprocalMotionConfig_CRC 152
#define MAVLINK_MSG_ID_30050_CRC 152



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_ReciprocalMotionConfig { \
    30050, \
    "ReciprocalMotionConfig", \
    7, \
    {  { "pos_tar1_p", NULL, MAVLINK_TYPE_INT64_T, 0, 0, offsetof(mavlink_reciprocalmotionconfig_t, pos_tar1_p) }, \
         { "pos_tar2_p", NULL, MAVLINK_TYPE_INT64_T, 0, 8, offsetof(mavlink_reciprocalmotionconfig_t, pos_tar2_p) }, \
         { "dwell_time_s", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_reciprocalmotionconfig_t, dwell_time_s) }, \
         { "profile_velocity_p_s", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_reciprocalmotionconfig_t, profile_velocity_p_s) }, \
         { "profile_acc_p_ss", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_reciprocalmotionconfig_t, profile_acc_p_ss) }, \
         { "profile_dec_p_ss", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_reciprocalmotionconfig_t, profile_dec_p_ss) }, \
         { "dt_s", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_reciprocalmotionconfig_t, dt_s) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_ReciprocalMotionConfig { \
    "ReciprocalMotionConfig", \
    7, \
    {  { "pos_tar1_p", NULL, MAVLINK_TYPE_INT64_T, 0, 0, offsetof(mavlink_reciprocalmotionconfig_t, pos_tar1_p) }, \
         { "pos_tar2_p", NULL, MAVLINK_TYPE_INT64_T, 0, 8, offsetof(mavlink_reciprocalmotionconfig_t, pos_tar2_p) }, \
         { "dwell_time_s", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_reciprocalmotionconfig_t, dwell_time_s) }, \
         { "profile_velocity_p_s", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_reciprocalmotionconfig_t, profile_velocity_p_s) }, \
         { "profile_acc_p_ss", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_reciprocalmotionconfig_t, profile_acc_p_ss) }, \
         { "profile_dec_p_ss", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_reciprocalmotionconfig_t, profile_dec_p_ss) }, \
         { "dt_s", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_reciprocalmotionconfig_t, dt_s) }, \
         } \
}
#endif

/**
 * @brief Pack a reciprocalmotionconfig message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param pos_tar1_p  
 * @param pos_tar2_p  
 * @param dwell_time_s  
 * @param profile_velocity_p_s  
 * @param profile_acc_p_ss  
 * @param profile_dec_p_ss  
 * @param dt_s  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_reciprocalmotionconfig_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               int64_t pos_tar1_p, int64_t pos_tar2_p, float dwell_time_s, float profile_velocity_p_s, float profile_acc_p_ss, float profile_dec_p_ss, float dt_s)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ReciprocalMotionConfig_LEN];
    _mav_put_int64_t(buf, 0, pos_tar1_p);
    _mav_put_int64_t(buf, 8, pos_tar2_p);
    _mav_put_float(buf, 16, dwell_time_s);
    _mav_put_float(buf, 20, profile_velocity_p_s);
    _mav_put_float(buf, 24, profile_acc_p_ss);
    _mav_put_float(buf, 28, profile_dec_p_ss);
    _mav_put_float(buf, 32, dt_s);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ReciprocalMotionConfig_LEN);
#else
    mavlink_reciprocalmotionconfig_t packet;
    packet.pos_tar1_p = pos_tar1_p;
    packet.pos_tar2_p = pos_tar2_p;
    packet.dwell_time_s = dwell_time_s;
    packet.profile_velocity_p_s = profile_velocity_p_s;
    packet.profile_acc_p_ss = profile_acc_p_ss;
    packet.profile_dec_p_ss = profile_dec_p_ss;
    packet.dt_s = dt_s;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ReciprocalMotionConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ReciprocalMotionConfig;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_ReciprocalMotionConfig_MIN_LEN, MAVLINK_MSG_ID_ReciprocalMotionConfig_LEN, MAVLINK_MSG_ID_ReciprocalMotionConfig_CRC);
}

/**
 * @brief Pack a reciprocalmotionconfig message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param pos_tar1_p  
 * @param pos_tar2_p  
 * @param dwell_time_s  
 * @param profile_velocity_p_s  
 * @param profile_acc_p_ss  
 * @param profile_dec_p_ss  
 * @param dt_s  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_reciprocalmotionconfig_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               int64_t pos_tar1_p, int64_t pos_tar2_p, float dwell_time_s, float profile_velocity_p_s, float profile_acc_p_ss, float profile_dec_p_ss, float dt_s)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ReciprocalMotionConfig_LEN];
    _mav_put_int64_t(buf, 0, pos_tar1_p);
    _mav_put_int64_t(buf, 8, pos_tar2_p);
    _mav_put_float(buf, 16, dwell_time_s);
    _mav_put_float(buf, 20, profile_velocity_p_s);
    _mav_put_float(buf, 24, profile_acc_p_ss);
    _mav_put_float(buf, 28, profile_dec_p_ss);
    _mav_put_float(buf, 32, dt_s);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ReciprocalMotionConfig_LEN);
#else
    mavlink_reciprocalmotionconfig_t packet;
    packet.pos_tar1_p = pos_tar1_p;
    packet.pos_tar2_p = pos_tar2_p;
    packet.dwell_time_s = dwell_time_s;
    packet.profile_velocity_p_s = profile_velocity_p_s;
    packet.profile_acc_p_ss = profile_acc_p_ss;
    packet.profile_dec_p_ss = profile_dec_p_ss;
    packet.dt_s = dt_s;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ReciprocalMotionConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ReciprocalMotionConfig;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_ReciprocalMotionConfig_MIN_LEN, MAVLINK_MSG_ID_ReciprocalMotionConfig_LEN, MAVLINK_MSG_ID_ReciprocalMotionConfig_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_ReciprocalMotionConfig_MIN_LEN, MAVLINK_MSG_ID_ReciprocalMotionConfig_LEN);
#endif
}

/**
 * @brief Pack a reciprocalmotionconfig message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param pos_tar1_p  
 * @param pos_tar2_p  
 * @param dwell_time_s  
 * @param profile_velocity_p_s  
 * @param profile_acc_p_ss  
 * @param profile_dec_p_ss  
 * @param dt_s  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_reciprocalmotionconfig_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   int64_t pos_tar1_p,int64_t pos_tar2_p,float dwell_time_s,float profile_velocity_p_s,float profile_acc_p_ss,float profile_dec_p_ss,float dt_s)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ReciprocalMotionConfig_LEN];
    _mav_put_int64_t(buf, 0, pos_tar1_p);
    _mav_put_int64_t(buf, 8, pos_tar2_p);
    _mav_put_float(buf, 16, dwell_time_s);
    _mav_put_float(buf, 20, profile_velocity_p_s);
    _mav_put_float(buf, 24, profile_acc_p_ss);
    _mav_put_float(buf, 28, profile_dec_p_ss);
    _mav_put_float(buf, 32, dt_s);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ReciprocalMotionConfig_LEN);
#else
    mavlink_reciprocalmotionconfig_t packet;
    packet.pos_tar1_p = pos_tar1_p;
    packet.pos_tar2_p = pos_tar2_p;
    packet.dwell_time_s = dwell_time_s;
    packet.profile_velocity_p_s = profile_velocity_p_s;
    packet.profile_acc_p_ss = profile_acc_p_ss;
    packet.profile_dec_p_ss = profile_dec_p_ss;
    packet.dt_s = dt_s;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ReciprocalMotionConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ReciprocalMotionConfig;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_ReciprocalMotionConfig_MIN_LEN, MAVLINK_MSG_ID_ReciprocalMotionConfig_LEN, MAVLINK_MSG_ID_ReciprocalMotionConfig_CRC);
}

/**
 * @brief Encode a reciprocalmotionconfig struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param reciprocalmotionconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_reciprocalmotionconfig_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_reciprocalmotionconfig_t* reciprocalmotionconfig)
{
    return mavlink_msg_reciprocalmotionconfig_pack(system_id, component_id, msg, reciprocalmotionconfig->pos_tar1_p, reciprocalmotionconfig->pos_tar2_p, reciprocalmotionconfig->dwell_time_s, reciprocalmotionconfig->profile_velocity_p_s, reciprocalmotionconfig->profile_acc_p_ss, reciprocalmotionconfig->profile_dec_p_ss, reciprocalmotionconfig->dt_s);
}

/**
 * @brief Encode a reciprocalmotionconfig struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param reciprocalmotionconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_reciprocalmotionconfig_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_reciprocalmotionconfig_t* reciprocalmotionconfig)
{
    return mavlink_msg_reciprocalmotionconfig_pack_chan(system_id, component_id, chan, msg, reciprocalmotionconfig->pos_tar1_p, reciprocalmotionconfig->pos_tar2_p, reciprocalmotionconfig->dwell_time_s, reciprocalmotionconfig->profile_velocity_p_s, reciprocalmotionconfig->profile_acc_p_ss, reciprocalmotionconfig->profile_dec_p_ss, reciprocalmotionconfig->dt_s);
}

/**
 * @brief Encode a reciprocalmotionconfig struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param reciprocalmotionconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_reciprocalmotionconfig_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_reciprocalmotionconfig_t* reciprocalmotionconfig)
{
    return mavlink_msg_reciprocalmotionconfig_pack_status(system_id, component_id, _status, msg,  reciprocalmotionconfig->pos_tar1_p, reciprocalmotionconfig->pos_tar2_p, reciprocalmotionconfig->dwell_time_s, reciprocalmotionconfig->profile_velocity_p_s, reciprocalmotionconfig->profile_acc_p_ss, reciprocalmotionconfig->profile_dec_p_ss, reciprocalmotionconfig->dt_s);
}

/**
 * @brief Send a reciprocalmotionconfig message
 * @param chan MAVLink channel to send the message
 *
 * @param pos_tar1_p  
 * @param pos_tar2_p  
 * @param dwell_time_s  
 * @param profile_velocity_p_s  
 * @param profile_acc_p_ss  
 * @param profile_dec_p_ss  
 * @param dt_s  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_reciprocalmotionconfig_send(mavlink_channel_t chan, int64_t pos_tar1_p, int64_t pos_tar2_p, float dwell_time_s, float profile_velocity_p_s, float profile_acc_p_ss, float profile_dec_p_ss, float dt_s)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ReciprocalMotionConfig_LEN];
    _mav_put_int64_t(buf, 0, pos_tar1_p);
    _mav_put_int64_t(buf, 8, pos_tar2_p);
    _mav_put_float(buf, 16, dwell_time_s);
    _mav_put_float(buf, 20, profile_velocity_p_s);
    _mav_put_float(buf, 24, profile_acc_p_ss);
    _mav_put_float(buf, 28, profile_dec_p_ss);
    _mav_put_float(buf, 32, dt_s);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ReciprocalMotionConfig, buf, MAVLINK_MSG_ID_ReciprocalMotionConfig_MIN_LEN, MAVLINK_MSG_ID_ReciprocalMotionConfig_LEN, MAVLINK_MSG_ID_ReciprocalMotionConfig_CRC);
#else
    mavlink_reciprocalmotionconfig_t packet;
    packet.pos_tar1_p = pos_tar1_p;
    packet.pos_tar2_p = pos_tar2_p;
    packet.dwell_time_s = dwell_time_s;
    packet.profile_velocity_p_s = profile_velocity_p_s;
    packet.profile_acc_p_ss = profile_acc_p_ss;
    packet.profile_dec_p_ss = profile_dec_p_ss;
    packet.dt_s = dt_s;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ReciprocalMotionConfig, (const char *)&packet, MAVLINK_MSG_ID_ReciprocalMotionConfig_MIN_LEN, MAVLINK_MSG_ID_ReciprocalMotionConfig_LEN, MAVLINK_MSG_ID_ReciprocalMotionConfig_CRC);
#endif
}

/**
 * @brief Send a reciprocalmotionconfig message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_reciprocalmotionconfig_send_struct(mavlink_channel_t chan, const mavlink_reciprocalmotionconfig_t* reciprocalmotionconfig)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_reciprocalmotionconfig_send(chan, reciprocalmotionconfig->pos_tar1_p, reciprocalmotionconfig->pos_tar2_p, reciprocalmotionconfig->dwell_time_s, reciprocalmotionconfig->profile_velocity_p_s, reciprocalmotionconfig->profile_acc_p_ss, reciprocalmotionconfig->profile_dec_p_ss, reciprocalmotionconfig->dt_s);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ReciprocalMotionConfig, (const char *)reciprocalmotionconfig, MAVLINK_MSG_ID_ReciprocalMotionConfig_MIN_LEN, MAVLINK_MSG_ID_ReciprocalMotionConfig_LEN, MAVLINK_MSG_ID_ReciprocalMotionConfig_CRC);
#endif
}

#if MAVLINK_MSG_ID_ReciprocalMotionConfig_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_reciprocalmotionconfig_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  int64_t pos_tar1_p, int64_t pos_tar2_p, float dwell_time_s, float profile_velocity_p_s, float profile_acc_p_ss, float profile_dec_p_ss, float dt_s)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_int64_t(buf, 0, pos_tar1_p);
    _mav_put_int64_t(buf, 8, pos_tar2_p);
    _mav_put_float(buf, 16, dwell_time_s);
    _mav_put_float(buf, 20, profile_velocity_p_s);
    _mav_put_float(buf, 24, profile_acc_p_ss);
    _mav_put_float(buf, 28, profile_dec_p_ss);
    _mav_put_float(buf, 32, dt_s);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ReciprocalMotionConfig, buf, MAVLINK_MSG_ID_ReciprocalMotionConfig_MIN_LEN, MAVLINK_MSG_ID_ReciprocalMotionConfig_LEN, MAVLINK_MSG_ID_ReciprocalMotionConfig_CRC);
#else
    mavlink_reciprocalmotionconfig_t *packet = (mavlink_reciprocalmotionconfig_t *)msgbuf;
    packet->pos_tar1_p = pos_tar1_p;
    packet->pos_tar2_p = pos_tar2_p;
    packet->dwell_time_s = dwell_time_s;
    packet->profile_velocity_p_s = profile_velocity_p_s;
    packet->profile_acc_p_ss = profile_acc_p_ss;
    packet->profile_dec_p_ss = profile_dec_p_ss;
    packet->dt_s = dt_s;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ReciprocalMotionConfig, (const char *)packet, MAVLINK_MSG_ID_ReciprocalMotionConfig_MIN_LEN, MAVLINK_MSG_ID_ReciprocalMotionConfig_LEN, MAVLINK_MSG_ID_ReciprocalMotionConfig_CRC);
#endif
}
#endif

#endif

// MESSAGE ReciprocalMotionConfig UNPACKING


/**
 * @brief Get field pos_tar1_p from reciprocalmotionconfig message
 *
 * @return  
 */
static inline int64_t mavlink_msg_reciprocalmotionconfig_get_pos_tar1_p(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int64_t(msg,  0);
}

/**
 * @brief Get field pos_tar2_p from reciprocalmotionconfig message
 *
 * @return  
 */
static inline int64_t mavlink_msg_reciprocalmotionconfig_get_pos_tar2_p(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int64_t(msg,  8);
}

/**
 * @brief Get field dwell_time_s from reciprocalmotionconfig message
 *
 * @return  
 */
static inline float mavlink_msg_reciprocalmotionconfig_get_dwell_time_s(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  16);
}

/**
 * @brief Get field profile_velocity_p_s from reciprocalmotionconfig message
 *
 * @return  
 */
static inline float mavlink_msg_reciprocalmotionconfig_get_profile_velocity_p_s(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  20);
}

/**
 * @brief Get field profile_acc_p_ss from reciprocalmotionconfig message
 *
 * @return  
 */
static inline float mavlink_msg_reciprocalmotionconfig_get_profile_acc_p_ss(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  24);
}

/**
 * @brief Get field profile_dec_p_ss from reciprocalmotionconfig message
 *
 * @return  
 */
static inline float mavlink_msg_reciprocalmotionconfig_get_profile_dec_p_ss(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  28);
}

/**
 * @brief Get field dt_s from reciprocalmotionconfig message
 *
 * @return  
 */
static inline float mavlink_msg_reciprocalmotionconfig_get_dt_s(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  32);
}

/**
 * @brief Decode a reciprocalmotionconfig message into a struct
 *
 * @param msg The message to decode
 * @param reciprocalmotionconfig C-struct to decode the message contents into
 */
static inline void mavlink_msg_reciprocalmotionconfig_decode(const mavlink_message_t* msg, mavlink_reciprocalmotionconfig_t* reciprocalmotionconfig)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    reciprocalmotionconfig->pos_tar1_p = mavlink_msg_reciprocalmotionconfig_get_pos_tar1_p(msg);
    reciprocalmotionconfig->pos_tar2_p = mavlink_msg_reciprocalmotionconfig_get_pos_tar2_p(msg);
    reciprocalmotionconfig->dwell_time_s = mavlink_msg_reciprocalmotionconfig_get_dwell_time_s(msg);
    reciprocalmotionconfig->profile_velocity_p_s = mavlink_msg_reciprocalmotionconfig_get_profile_velocity_p_s(msg);
    reciprocalmotionconfig->profile_acc_p_ss = mavlink_msg_reciprocalmotionconfig_get_profile_acc_p_ss(msg);
    reciprocalmotionconfig->profile_dec_p_ss = mavlink_msg_reciprocalmotionconfig_get_profile_dec_p_ss(msg);
    reciprocalmotionconfig->dt_s = mavlink_msg_reciprocalmotionconfig_get_dt_s(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_ReciprocalMotionConfig_LEN? msg->len : MAVLINK_MSG_ID_ReciprocalMotionConfig_LEN;
        memset(reciprocalmotionconfig, 0, MAVLINK_MSG_ID_ReciprocalMotionConfig_LEN);
    memcpy(reciprocalmotionconfig, _MAV_PAYLOAD(msg), len);
#endif
}
