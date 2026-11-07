#pragma once
// MESSAGE ScopeConfig PACKING

#define MAVLINK_MSG_ID_ScopeConfig 30014


typedef struct __mavlink_scopeconfig_t {
 uint32_t channel_map[16]; /*<  */
 uint32_t sample_points; /*<  */
 uint32_t trigger_source; /*<  */
 int32_t trigger_threshold; /*<  */
 uint16_t channel_switch; /*<  */
 uint8_t sample_interval; /*<  */
 uint8_t trigger_delay; /*<  */
 uint8_t trigger_mode; /*<  */
} mavlink_scopeconfig_t;

#define MAVLINK_MSG_ID_ScopeConfig_LEN 81
#define MAVLINK_MSG_ID_ScopeConfig_MIN_LEN 81
#define MAVLINK_MSG_ID_30014_LEN 81
#define MAVLINK_MSG_ID_30014_MIN_LEN 81

#define MAVLINK_MSG_ID_ScopeConfig_CRC 199
#define MAVLINK_MSG_ID_30014_CRC 199

#define MAVLINK_MSG_ScopeConfig_FIELD_CHANNEL_MAP_LEN 16

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_ScopeConfig { \
    30014, \
    "ScopeConfig", \
    8, \
    {  { "channel_map", NULL, MAVLINK_TYPE_UINT32_T, 16, 0, offsetof(mavlink_scopeconfig_t, channel_map) }, \
         { "channel_switch", NULL, MAVLINK_TYPE_UINT16_T, 0, 76, offsetof(mavlink_scopeconfig_t, channel_switch) }, \
         { "sample_interval", NULL, MAVLINK_TYPE_UINT8_T, 0, 78, offsetof(mavlink_scopeconfig_t, sample_interval) }, \
         { "sample_points", NULL, MAVLINK_TYPE_UINT32_T, 0, 64, offsetof(mavlink_scopeconfig_t, sample_points) }, \
         { "trigger_delay", NULL, MAVLINK_TYPE_UINT8_T, 0, 79, offsetof(mavlink_scopeconfig_t, trigger_delay) }, \
         { "trigger_mode", NULL, MAVLINK_TYPE_UINT8_T, 0, 80, offsetof(mavlink_scopeconfig_t, trigger_mode) }, \
         { "trigger_source", NULL, MAVLINK_TYPE_UINT32_T, 0, 68, offsetof(mavlink_scopeconfig_t, trigger_source) }, \
         { "trigger_threshold", NULL, MAVLINK_TYPE_INT32_T, 0, 72, offsetof(mavlink_scopeconfig_t, trigger_threshold) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_ScopeConfig { \
    "ScopeConfig", \
    8, \
    {  { "channel_map", NULL, MAVLINK_TYPE_UINT32_T, 16, 0, offsetof(mavlink_scopeconfig_t, channel_map) }, \
         { "channel_switch", NULL, MAVLINK_TYPE_UINT16_T, 0, 76, offsetof(mavlink_scopeconfig_t, channel_switch) }, \
         { "sample_interval", NULL, MAVLINK_TYPE_UINT8_T, 0, 78, offsetof(mavlink_scopeconfig_t, sample_interval) }, \
         { "sample_points", NULL, MAVLINK_TYPE_UINT32_T, 0, 64, offsetof(mavlink_scopeconfig_t, sample_points) }, \
         { "trigger_delay", NULL, MAVLINK_TYPE_UINT8_T, 0, 79, offsetof(mavlink_scopeconfig_t, trigger_delay) }, \
         { "trigger_mode", NULL, MAVLINK_TYPE_UINT8_T, 0, 80, offsetof(mavlink_scopeconfig_t, trigger_mode) }, \
         { "trigger_source", NULL, MAVLINK_TYPE_UINT32_T, 0, 68, offsetof(mavlink_scopeconfig_t, trigger_source) }, \
         { "trigger_threshold", NULL, MAVLINK_TYPE_INT32_T, 0, 72, offsetof(mavlink_scopeconfig_t, trigger_threshold) }, \
         } \
}
#endif

/**
 * @brief Pack a scopeconfig message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param channel_map  
 * @param channel_switch  
 * @param sample_interval  
 * @param sample_points  
 * @param trigger_delay  
 * @param trigger_mode  
 * @param trigger_source  
 * @param trigger_threshold  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_scopeconfig_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               const uint32_t *channel_map, uint16_t channel_switch, uint8_t sample_interval, uint32_t sample_points, uint8_t trigger_delay, uint8_t trigger_mode, uint32_t trigger_source, int32_t trigger_threshold)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ScopeConfig_LEN];
    _mav_put_uint32_t(buf, 64, sample_points);
    _mav_put_uint32_t(buf, 68, trigger_source);
    _mav_put_int32_t(buf, 72, trigger_threshold);
    _mav_put_uint16_t(buf, 76, channel_switch);
    _mav_put_uint8_t(buf, 78, sample_interval);
    _mav_put_uint8_t(buf, 79, trigger_delay);
    _mav_put_uint8_t(buf, 80, trigger_mode);
    _mav_put_uint32_t_array(buf, 0, channel_map, 16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ScopeConfig_LEN);
#else
    mavlink_scopeconfig_t packet;
    packet.sample_points = sample_points;
    packet.trigger_source = trigger_source;
    packet.trigger_threshold = trigger_threshold;
    packet.channel_switch = channel_switch;
    packet.sample_interval = sample_interval;
    packet.trigger_delay = trigger_delay;
    packet.trigger_mode = trigger_mode;
    mav_array_memcpy(packet.channel_map, channel_map, sizeof(uint32_t)*16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ScopeConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ScopeConfig;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_ScopeConfig_MIN_LEN, MAVLINK_MSG_ID_ScopeConfig_LEN, MAVLINK_MSG_ID_ScopeConfig_CRC);
}

/**
 * @brief Pack a scopeconfig message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param channel_map  
 * @param channel_switch  
 * @param sample_interval  
 * @param sample_points  
 * @param trigger_delay  
 * @param trigger_mode  
 * @param trigger_source  
 * @param trigger_threshold  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_scopeconfig_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               const uint32_t *channel_map, uint16_t channel_switch, uint8_t sample_interval, uint32_t sample_points, uint8_t trigger_delay, uint8_t trigger_mode, uint32_t trigger_source, int32_t trigger_threshold)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ScopeConfig_LEN];
    _mav_put_uint32_t(buf, 64, sample_points);
    _mav_put_uint32_t(buf, 68, trigger_source);
    _mav_put_int32_t(buf, 72, trigger_threshold);
    _mav_put_uint16_t(buf, 76, channel_switch);
    _mav_put_uint8_t(buf, 78, sample_interval);
    _mav_put_uint8_t(buf, 79, trigger_delay);
    _mav_put_uint8_t(buf, 80, trigger_mode);
    _mav_put_uint32_t_array(buf, 0, channel_map, 16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ScopeConfig_LEN);
#else
    mavlink_scopeconfig_t packet;
    packet.sample_points = sample_points;
    packet.trigger_source = trigger_source;
    packet.trigger_threshold = trigger_threshold;
    packet.channel_switch = channel_switch;
    packet.sample_interval = sample_interval;
    packet.trigger_delay = trigger_delay;
    packet.trigger_mode = trigger_mode;
    mav_array_memcpy(packet.channel_map, channel_map, sizeof(uint32_t)*16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ScopeConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ScopeConfig;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_ScopeConfig_MIN_LEN, MAVLINK_MSG_ID_ScopeConfig_LEN, MAVLINK_MSG_ID_ScopeConfig_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_ScopeConfig_MIN_LEN, MAVLINK_MSG_ID_ScopeConfig_LEN);
#endif
}

/**
 * @brief Pack a scopeconfig message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param channel_map  
 * @param channel_switch  
 * @param sample_interval  
 * @param sample_points  
 * @param trigger_delay  
 * @param trigger_mode  
 * @param trigger_source  
 * @param trigger_threshold  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_scopeconfig_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   const uint32_t *channel_map,uint16_t channel_switch,uint8_t sample_interval,uint32_t sample_points,uint8_t trigger_delay,uint8_t trigger_mode,uint32_t trigger_source,int32_t trigger_threshold)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ScopeConfig_LEN];
    _mav_put_uint32_t(buf, 64, sample_points);
    _mav_put_uint32_t(buf, 68, trigger_source);
    _mav_put_int32_t(buf, 72, trigger_threshold);
    _mav_put_uint16_t(buf, 76, channel_switch);
    _mav_put_uint8_t(buf, 78, sample_interval);
    _mav_put_uint8_t(buf, 79, trigger_delay);
    _mav_put_uint8_t(buf, 80, trigger_mode);
    _mav_put_uint32_t_array(buf, 0, channel_map, 16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ScopeConfig_LEN);
#else
    mavlink_scopeconfig_t packet;
    packet.sample_points = sample_points;
    packet.trigger_source = trigger_source;
    packet.trigger_threshold = trigger_threshold;
    packet.channel_switch = channel_switch;
    packet.sample_interval = sample_interval;
    packet.trigger_delay = trigger_delay;
    packet.trigger_mode = trigger_mode;
    mav_array_memcpy(packet.channel_map, channel_map, sizeof(uint32_t)*16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ScopeConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ScopeConfig;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_ScopeConfig_MIN_LEN, MAVLINK_MSG_ID_ScopeConfig_LEN, MAVLINK_MSG_ID_ScopeConfig_CRC);
}

/**
 * @brief Encode a scopeconfig struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param scopeconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_scopeconfig_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_scopeconfig_t* scopeconfig)
{
    return mavlink_msg_scopeconfig_pack(system_id, component_id, msg, scopeconfig->channel_map, scopeconfig->channel_switch, scopeconfig->sample_interval, scopeconfig->sample_points, scopeconfig->trigger_delay, scopeconfig->trigger_mode, scopeconfig->trigger_source, scopeconfig->trigger_threshold);
}

/**
 * @brief Encode a scopeconfig struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param scopeconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_scopeconfig_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_scopeconfig_t* scopeconfig)
{
    return mavlink_msg_scopeconfig_pack_chan(system_id, component_id, chan, msg, scopeconfig->channel_map, scopeconfig->channel_switch, scopeconfig->sample_interval, scopeconfig->sample_points, scopeconfig->trigger_delay, scopeconfig->trigger_mode, scopeconfig->trigger_source, scopeconfig->trigger_threshold);
}

/**
 * @brief Encode a scopeconfig struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param scopeconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_scopeconfig_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_scopeconfig_t* scopeconfig)
{
    return mavlink_msg_scopeconfig_pack_status(system_id, component_id, _status, msg,  scopeconfig->channel_map, scopeconfig->channel_switch, scopeconfig->sample_interval, scopeconfig->sample_points, scopeconfig->trigger_delay, scopeconfig->trigger_mode, scopeconfig->trigger_source, scopeconfig->trigger_threshold);
}

/**
 * @brief Send a scopeconfig message
 * @param chan MAVLink channel to send the message
 *
 * @param channel_map  
 * @param channel_switch  
 * @param sample_interval  
 * @param sample_points  
 * @param trigger_delay  
 * @param trigger_mode  
 * @param trigger_source  
 * @param trigger_threshold  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_scopeconfig_send(mavlink_channel_t chan, const uint32_t *channel_map, uint16_t channel_switch, uint8_t sample_interval, uint32_t sample_points, uint8_t trigger_delay, uint8_t trigger_mode, uint32_t trigger_source, int32_t trigger_threshold)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ScopeConfig_LEN];
    _mav_put_uint32_t(buf, 64, sample_points);
    _mav_put_uint32_t(buf, 68, trigger_source);
    _mav_put_int32_t(buf, 72, trigger_threshold);
    _mav_put_uint16_t(buf, 76, channel_switch);
    _mav_put_uint8_t(buf, 78, sample_interval);
    _mav_put_uint8_t(buf, 79, trigger_delay);
    _mav_put_uint8_t(buf, 80, trigger_mode);
    _mav_put_uint32_t_array(buf, 0, channel_map, 16);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ScopeConfig, buf, MAVLINK_MSG_ID_ScopeConfig_MIN_LEN, MAVLINK_MSG_ID_ScopeConfig_LEN, MAVLINK_MSG_ID_ScopeConfig_CRC);
#else
    mavlink_scopeconfig_t packet;
    packet.sample_points = sample_points;
    packet.trigger_source = trigger_source;
    packet.trigger_threshold = trigger_threshold;
    packet.channel_switch = channel_switch;
    packet.sample_interval = sample_interval;
    packet.trigger_delay = trigger_delay;
    packet.trigger_mode = trigger_mode;
    mav_array_memcpy(packet.channel_map, channel_map, sizeof(uint32_t)*16);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ScopeConfig, (const char *)&packet, MAVLINK_MSG_ID_ScopeConfig_MIN_LEN, MAVLINK_MSG_ID_ScopeConfig_LEN, MAVLINK_MSG_ID_ScopeConfig_CRC);
#endif
}

/**
 * @brief Send a scopeconfig message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_scopeconfig_send_struct(mavlink_channel_t chan, const mavlink_scopeconfig_t* scopeconfig)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_scopeconfig_send(chan, scopeconfig->channel_map, scopeconfig->channel_switch, scopeconfig->sample_interval, scopeconfig->sample_points, scopeconfig->trigger_delay, scopeconfig->trigger_mode, scopeconfig->trigger_source, scopeconfig->trigger_threshold);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ScopeConfig, (const char *)scopeconfig, MAVLINK_MSG_ID_ScopeConfig_MIN_LEN, MAVLINK_MSG_ID_ScopeConfig_LEN, MAVLINK_MSG_ID_ScopeConfig_CRC);
#endif
}

#if MAVLINK_MSG_ID_ScopeConfig_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_scopeconfig_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  const uint32_t *channel_map, uint16_t channel_switch, uint8_t sample_interval, uint32_t sample_points, uint8_t trigger_delay, uint8_t trigger_mode, uint32_t trigger_source, int32_t trigger_threshold)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint32_t(buf, 64, sample_points);
    _mav_put_uint32_t(buf, 68, trigger_source);
    _mav_put_int32_t(buf, 72, trigger_threshold);
    _mav_put_uint16_t(buf, 76, channel_switch);
    _mav_put_uint8_t(buf, 78, sample_interval);
    _mav_put_uint8_t(buf, 79, trigger_delay);
    _mav_put_uint8_t(buf, 80, trigger_mode);
    _mav_put_uint32_t_array(buf, 0, channel_map, 16);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ScopeConfig, buf, MAVLINK_MSG_ID_ScopeConfig_MIN_LEN, MAVLINK_MSG_ID_ScopeConfig_LEN, MAVLINK_MSG_ID_ScopeConfig_CRC);
#else
    mavlink_scopeconfig_t *packet = (mavlink_scopeconfig_t *)msgbuf;
    packet->sample_points = sample_points;
    packet->trigger_source = trigger_source;
    packet->trigger_threshold = trigger_threshold;
    packet->channel_switch = channel_switch;
    packet->sample_interval = sample_interval;
    packet->trigger_delay = trigger_delay;
    packet->trigger_mode = trigger_mode;
    mav_array_memcpy(packet->channel_map, channel_map, sizeof(uint32_t)*16);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ScopeConfig, (const char *)packet, MAVLINK_MSG_ID_ScopeConfig_MIN_LEN, MAVLINK_MSG_ID_ScopeConfig_LEN, MAVLINK_MSG_ID_ScopeConfig_CRC);
#endif
}
#endif

#endif

// MESSAGE ScopeConfig UNPACKING


/**
 * @brief Get field channel_map from scopeconfig message
 *
 * @return  
 */
static inline uint16_t mavlink_msg_scopeconfig_get_channel_map(const mavlink_message_t* msg, uint32_t *channel_map)
{
    return _MAV_RETURN_uint32_t_array(msg, channel_map, 16,  0);
}

/**
 * @brief Get field channel_switch from scopeconfig message
 *
 * @return  
 */
static inline uint16_t mavlink_msg_scopeconfig_get_channel_switch(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  76);
}

/**
 * @brief Get field sample_interval from scopeconfig message
 *
 * @return  
 */
static inline uint8_t mavlink_msg_scopeconfig_get_sample_interval(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  78);
}

/**
 * @brief Get field sample_points from scopeconfig message
 *
 * @return  
 */
static inline uint32_t mavlink_msg_scopeconfig_get_sample_points(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  64);
}

/**
 * @brief Get field trigger_delay from scopeconfig message
 *
 * @return  
 */
static inline uint8_t mavlink_msg_scopeconfig_get_trigger_delay(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  79);
}

/**
 * @brief Get field trigger_mode from scopeconfig message
 *
 * @return  
 */
static inline uint8_t mavlink_msg_scopeconfig_get_trigger_mode(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  80);
}

/**
 * @brief Get field trigger_source from scopeconfig message
 *
 * @return  
 */
static inline uint32_t mavlink_msg_scopeconfig_get_trigger_source(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  68);
}

/**
 * @brief Get field trigger_threshold from scopeconfig message
 *
 * @return  
 */
static inline int32_t mavlink_msg_scopeconfig_get_trigger_threshold(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  72);
}

/**
 * @brief Decode a scopeconfig message into a struct
 *
 * @param msg The message to decode
 * @param scopeconfig C-struct to decode the message contents into
 */
static inline void mavlink_msg_scopeconfig_decode(const mavlink_message_t* msg, mavlink_scopeconfig_t* scopeconfig)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_scopeconfig_get_channel_map(msg, scopeconfig->channel_map);
    scopeconfig->sample_points = mavlink_msg_scopeconfig_get_sample_points(msg);
    scopeconfig->trigger_source = mavlink_msg_scopeconfig_get_trigger_source(msg);
    scopeconfig->trigger_threshold = mavlink_msg_scopeconfig_get_trigger_threshold(msg);
    scopeconfig->channel_switch = mavlink_msg_scopeconfig_get_channel_switch(msg);
    scopeconfig->sample_interval = mavlink_msg_scopeconfig_get_sample_interval(msg);
    scopeconfig->trigger_delay = mavlink_msg_scopeconfig_get_trigger_delay(msg);
    scopeconfig->trigger_mode = mavlink_msg_scopeconfig_get_trigger_mode(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_ScopeConfig_LEN? msg->len : MAVLINK_MSG_ID_ScopeConfig_LEN;
        memset(scopeconfig, 0, MAVLINK_MSG_ID_ScopeConfig_LEN);
    memcpy(scopeconfig, _MAV_PAYLOAD(msg), len);
#endif
}
