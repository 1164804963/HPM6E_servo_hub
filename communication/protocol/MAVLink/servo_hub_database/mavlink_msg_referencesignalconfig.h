#pragma once
// MESSAGE ReferenceSignalConfig PACKING

#define MAVLINK_MSG_ID_ReferenceSignalConfig 30052


typedef struct __mavlink_referencesignalconfig_t {
 int64_t signal_start_pos; /*<  */
 float dt_s; /*<  */
 float amp; /*<  */
 float frq_Hz; /*<  */
 float bias; /*<  */
 uint8_t signal_type; /*<  */
 uint8_t signal_target; /*<  */
} mavlink_referencesignalconfig_t;

#define MAVLINK_MSG_ID_ReferenceSignalConfig_LEN 26
#define MAVLINK_MSG_ID_ReferenceSignalConfig_MIN_LEN 26
#define MAVLINK_MSG_ID_30052_LEN 26
#define MAVLINK_MSG_ID_30052_MIN_LEN 26

#define MAVLINK_MSG_ID_ReferenceSignalConfig_CRC 90
#define MAVLINK_MSG_ID_30052_CRC 90



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_ReferenceSignalConfig { \
    30052, \
    "ReferenceSignalConfig", \
    7, \
    {  { "dt_s", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_referencesignalconfig_t, dt_s) }, \
         { "signal_type", NULL, MAVLINK_TYPE_UINT8_T, 0, 24, offsetof(mavlink_referencesignalconfig_t, signal_type) }, \
         { "amp", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_referencesignalconfig_t, amp) }, \
         { "frq_Hz", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_referencesignalconfig_t, frq_Hz) }, \
         { "bias", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_referencesignalconfig_t, bias) }, \
         { "signal_target", NULL, MAVLINK_TYPE_UINT8_T, 0, 25, offsetof(mavlink_referencesignalconfig_t, signal_target) }, \
         { "signal_start_pos", NULL, MAVLINK_TYPE_INT64_T, 0, 0, offsetof(mavlink_referencesignalconfig_t, signal_start_pos) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_ReferenceSignalConfig { \
    "ReferenceSignalConfig", \
    7, \
    {  { "dt_s", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_referencesignalconfig_t, dt_s) }, \
         { "signal_type", NULL, MAVLINK_TYPE_UINT8_T, 0, 24, offsetof(mavlink_referencesignalconfig_t, signal_type) }, \
         { "amp", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_referencesignalconfig_t, amp) }, \
         { "frq_Hz", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_referencesignalconfig_t, frq_Hz) }, \
         { "bias", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_referencesignalconfig_t, bias) }, \
         { "signal_target", NULL, MAVLINK_TYPE_UINT8_T, 0, 25, offsetof(mavlink_referencesignalconfig_t, signal_target) }, \
         { "signal_start_pos", NULL, MAVLINK_TYPE_INT64_T, 0, 0, offsetof(mavlink_referencesignalconfig_t, signal_start_pos) }, \
         } \
}
#endif

/**
 * @brief Pack a referencesignalconfig message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param dt_s  
 * @param signal_type  
 * @param amp  
 * @param frq_Hz  
 * @param bias  
 * @param signal_target  
 * @param signal_start_pos  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_referencesignalconfig_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               float dt_s, uint8_t signal_type, float amp, float frq_Hz, float bias, uint8_t signal_target, int64_t signal_start_pos)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ReferenceSignalConfig_LEN];
    _mav_put_int64_t(buf, 0, signal_start_pos);
    _mav_put_float(buf, 8, dt_s);
    _mav_put_float(buf, 12, amp);
    _mav_put_float(buf, 16, frq_Hz);
    _mav_put_float(buf, 20, bias);
    _mav_put_uint8_t(buf, 24, signal_type);
    _mav_put_uint8_t(buf, 25, signal_target);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ReferenceSignalConfig_LEN);
#else
    mavlink_referencesignalconfig_t packet;
    packet.signal_start_pos = signal_start_pos;
    packet.dt_s = dt_s;
    packet.amp = amp;
    packet.frq_Hz = frq_Hz;
    packet.bias = bias;
    packet.signal_type = signal_type;
    packet.signal_target = signal_target;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ReferenceSignalConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ReferenceSignalConfig;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_ReferenceSignalConfig_MIN_LEN, MAVLINK_MSG_ID_ReferenceSignalConfig_LEN, MAVLINK_MSG_ID_ReferenceSignalConfig_CRC);
}

/**
 * @brief Pack a referencesignalconfig message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param dt_s  
 * @param signal_type  
 * @param amp  
 * @param frq_Hz  
 * @param bias  
 * @param signal_target  
 * @param signal_start_pos  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_referencesignalconfig_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               float dt_s, uint8_t signal_type, float amp, float frq_Hz, float bias, uint8_t signal_target, int64_t signal_start_pos)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ReferenceSignalConfig_LEN];
    _mav_put_int64_t(buf, 0, signal_start_pos);
    _mav_put_float(buf, 8, dt_s);
    _mav_put_float(buf, 12, amp);
    _mav_put_float(buf, 16, frq_Hz);
    _mav_put_float(buf, 20, bias);
    _mav_put_uint8_t(buf, 24, signal_type);
    _mav_put_uint8_t(buf, 25, signal_target);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ReferenceSignalConfig_LEN);
#else
    mavlink_referencesignalconfig_t packet;
    packet.signal_start_pos = signal_start_pos;
    packet.dt_s = dt_s;
    packet.amp = amp;
    packet.frq_Hz = frq_Hz;
    packet.bias = bias;
    packet.signal_type = signal_type;
    packet.signal_target = signal_target;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ReferenceSignalConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ReferenceSignalConfig;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_ReferenceSignalConfig_MIN_LEN, MAVLINK_MSG_ID_ReferenceSignalConfig_LEN, MAVLINK_MSG_ID_ReferenceSignalConfig_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_ReferenceSignalConfig_MIN_LEN, MAVLINK_MSG_ID_ReferenceSignalConfig_LEN);
#endif
}

/**
 * @brief Pack a referencesignalconfig message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param dt_s  
 * @param signal_type  
 * @param amp  
 * @param frq_Hz  
 * @param bias  
 * @param signal_target  
 * @param signal_start_pos  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_referencesignalconfig_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   float dt_s,uint8_t signal_type,float amp,float frq_Hz,float bias,uint8_t signal_target,int64_t signal_start_pos)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ReferenceSignalConfig_LEN];
    _mav_put_int64_t(buf, 0, signal_start_pos);
    _mav_put_float(buf, 8, dt_s);
    _mav_put_float(buf, 12, amp);
    _mav_put_float(buf, 16, frq_Hz);
    _mav_put_float(buf, 20, bias);
    _mav_put_uint8_t(buf, 24, signal_type);
    _mav_put_uint8_t(buf, 25, signal_target);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ReferenceSignalConfig_LEN);
#else
    mavlink_referencesignalconfig_t packet;
    packet.signal_start_pos = signal_start_pos;
    packet.dt_s = dt_s;
    packet.amp = amp;
    packet.frq_Hz = frq_Hz;
    packet.bias = bias;
    packet.signal_type = signal_type;
    packet.signal_target = signal_target;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ReferenceSignalConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ReferenceSignalConfig;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_ReferenceSignalConfig_MIN_LEN, MAVLINK_MSG_ID_ReferenceSignalConfig_LEN, MAVLINK_MSG_ID_ReferenceSignalConfig_CRC);
}

/**
 * @brief Encode a referencesignalconfig struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param referencesignalconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_referencesignalconfig_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_referencesignalconfig_t* referencesignalconfig)
{
    return mavlink_msg_referencesignalconfig_pack(system_id, component_id, msg, referencesignalconfig->dt_s, referencesignalconfig->signal_type, referencesignalconfig->amp, referencesignalconfig->frq_Hz, referencesignalconfig->bias, referencesignalconfig->signal_target, referencesignalconfig->signal_start_pos);
}

/**
 * @brief Encode a referencesignalconfig struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param referencesignalconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_referencesignalconfig_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_referencesignalconfig_t* referencesignalconfig)
{
    return mavlink_msg_referencesignalconfig_pack_chan(system_id, component_id, chan, msg, referencesignalconfig->dt_s, referencesignalconfig->signal_type, referencesignalconfig->amp, referencesignalconfig->frq_Hz, referencesignalconfig->bias, referencesignalconfig->signal_target, referencesignalconfig->signal_start_pos);
}

/**
 * @brief Encode a referencesignalconfig struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param referencesignalconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_referencesignalconfig_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_referencesignalconfig_t* referencesignalconfig)
{
    return mavlink_msg_referencesignalconfig_pack_status(system_id, component_id, _status, msg,  referencesignalconfig->dt_s, referencesignalconfig->signal_type, referencesignalconfig->amp, referencesignalconfig->frq_Hz, referencesignalconfig->bias, referencesignalconfig->signal_target, referencesignalconfig->signal_start_pos);
}

/**
 * @brief Send a referencesignalconfig message
 * @param chan MAVLink channel to send the message
 *
 * @param dt_s  
 * @param signal_type  
 * @param amp  
 * @param frq_Hz  
 * @param bias  
 * @param signal_target  
 * @param signal_start_pos  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_referencesignalconfig_send(mavlink_channel_t chan, float dt_s, uint8_t signal_type, float amp, float frq_Hz, float bias, uint8_t signal_target, int64_t signal_start_pos)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ReferenceSignalConfig_LEN];
    _mav_put_int64_t(buf, 0, signal_start_pos);
    _mav_put_float(buf, 8, dt_s);
    _mav_put_float(buf, 12, amp);
    _mav_put_float(buf, 16, frq_Hz);
    _mav_put_float(buf, 20, bias);
    _mav_put_uint8_t(buf, 24, signal_type);
    _mav_put_uint8_t(buf, 25, signal_target);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ReferenceSignalConfig, buf, MAVLINK_MSG_ID_ReferenceSignalConfig_MIN_LEN, MAVLINK_MSG_ID_ReferenceSignalConfig_LEN, MAVLINK_MSG_ID_ReferenceSignalConfig_CRC);
#else
    mavlink_referencesignalconfig_t packet;
    packet.signal_start_pos = signal_start_pos;
    packet.dt_s = dt_s;
    packet.amp = amp;
    packet.frq_Hz = frq_Hz;
    packet.bias = bias;
    packet.signal_type = signal_type;
    packet.signal_target = signal_target;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ReferenceSignalConfig, (const char *)&packet, MAVLINK_MSG_ID_ReferenceSignalConfig_MIN_LEN, MAVLINK_MSG_ID_ReferenceSignalConfig_LEN, MAVLINK_MSG_ID_ReferenceSignalConfig_CRC);
#endif
}

/**
 * @brief Send a referencesignalconfig message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_referencesignalconfig_send_struct(mavlink_channel_t chan, const mavlink_referencesignalconfig_t* referencesignalconfig)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_referencesignalconfig_send(chan, referencesignalconfig->dt_s, referencesignalconfig->signal_type, referencesignalconfig->amp, referencesignalconfig->frq_Hz, referencesignalconfig->bias, referencesignalconfig->signal_target, referencesignalconfig->signal_start_pos);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ReferenceSignalConfig, (const char *)referencesignalconfig, MAVLINK_MSG_ID_ReferenceSignalConfig_MIN_LEN, MAVLINK_MSG_ID_ReferenceSignalConfig_LEN, MAVLINK_MSG_ID_ReferenceSignalConfig_CRC);
#endif
}

#if MAVLINK_MSG_ID_ReferenceSignalConfig_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_referencesignalconfig_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float dt_s, uint8_t signal_type, float amp, float frq_Hz, float bias, uint8_t signal_target, int64_t signal_start_pos)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_int64_t(buf, 0, signal_start_pos);
    _mav_put_float(buf, 8, dt_s);
    _mav_put_float(buf, 12, amp);
    _mav_put_float(buf, 16, frq_Hz);
    _mav_put_float(buf, 20, bias);
    _mav_put_uint8_t(buf, 24, signal_type);
    _mav_put_uint8_t(buf, 25, signal_target);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ReferenceSignalConfig, buf, MAVLINK_MSG_ID_ReferenceSignalConfig_MIN_LEN, MAVLINK_MSG_ID_ReferenceSignalConfig_LEN, MAVLINK_MSG_ID_ReferenceSignalConfig_CRC);
#else
    mavlink_referencesignalconfig_t *packet = (mavlink_referencesignalconfig_t *)msgbuf;
    packet->signal_start_pos = signal_start_pos;
    packet->dt_s = dt_s;
    packet->amp = amp;
    packet->frq_Hz = frq_Hz;
    packet->bias = bias;
    packet->signal_type = signal_type;
    packet->signal_target = signal_target;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ReferenceSignalConfig, (const char *)packet, MAVLINK_MSG_ID_ReferenceSignalConfig_MIN_LEN, MAVLINK_MSG_ID_ReferenceSignalConfig_LEN, MAVLINK_MSG_ID_ReferenceSignalConfig_CRC);
#endif
}
#endif

#endif

// MESSAGE ReferenceSignalConfig UNPACKING


/**
 * @brief Get field dt_s from referencesignalconfig message
 *
 * @return  
 */
static inline float mavlink_msg_referencesignalconfig_get_dt_s(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field signal_type from referencesignalconfig message
 *
 * @return  
 */
static inline uint8_t mavlink_msg_referencesignalconfig_get_signal_type(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  24);
}

/**
 * @brief Get field amp from referencesignalconfig message
 *
 * @return  
 */
static inline float mavlink_msg_referencesignalconfig_get_amp(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Get field frq_Hz from referencesignalconfig message
 *
 * @return  
 */
static inline float mavlink_msg_referencesignalconfig_get_frq_Hz(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  16);
}

/**
 * @brief Get field bias from referencesignalconfig message
 *
 * @return  
 */
static inline float mavlink_msg_referencesignalconfig_get_bias(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  20);
}

/**
 * @brief Get field signal_target from referencesignalconfig message
 *
 * @return  
 */
static inline uint8_t mavlink_msg_referencesignalconfig_get_signal_target(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  25);
}

/**
 * @brief Get field signal_start_pos from referencesignalconfig message
 *
 * @return  
 */
static inline int64_t mavlink_msg_referencesignalconfig_get_signal_start_pos(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int64_t(msg,  0);
}

/**
 * @brief Decode a referencesignalconfig message into a struct
 *
 * @param msg The message to decode
 * @param referencesignalconfig C-struct to decode the message contents into
 */
static inline void mavlink_msg_referencesignalconfig_decode(const mavlink_message_t* msg, mavlink_referencesignalconfig_t* referencesignalconfig)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    referencesignalconfig->signal_start_pos = mavlink_msg_referencesignalconfig_get_signal_start_pos(msg);
    referencesignalconfig->dt_s = mavlink_msg_referencesignalconfig_get_dt_s(msg);
    referencesignalconfig->amp = mavlink_msg_referencesignalconfig_get_amp(msg);
    referencesignalconfig->frq_Hz = mavlink_msg_referencesignalconfig_get_frq_Hz(msg);
    referencesignalconfig->bias = mavlink_msg_referencesignalconfig_get_bias(msg);
    referencesignalconfig->signal_type = mavlink_msg_referencesignalconfig_get_signal_type(msg);
    referencesignalconfig->signal_target = mavlink_msg_referencesignalconfig_get_signal_target(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_ReferenceSignalConfig_LEN? msg->len : MAVLINK_MSG_ID_ReferenceSignalConfig_LEN;
        memset(referencesignalconfig, 0, MAVLINK_MSG_ID_ReferenceSignalConfig_LEN);
    memcpy(referencesignalconfig, _MAV_PAYLOAD(msg), len);
#endif
}
