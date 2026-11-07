#pragma once
// MESSAGE SystemConfig PACKING

#define MAVLINK_MSG_ID_SystemConfig 30045


typedef struct __mavlink_systemconfig_t {
 uint32_t current_loop_freq; /*<  */
 uint32_t position_loop_freq; /*<  */
 int8_t param_save; /*<  */
 int8_t system_reset; /*<  */
} mavlink_systemconfig_t;

#define MAVLINK_MSG_ID_SystemConfig_LEN 10
#define MAVLINK_MSG_ID_SystemConfig_MIN_LEN 10
#define MAVLINK_MSG_ID_30045_LEN 10
#define MAVLINK_MSG_ID_30045_MIN_LEN 10

#define MAVLINK_MSG_ID_SystemConfig_CRC 246
#define MAVLINK_MSG_ID_30045_CRC 246



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_SystemConfig { \
    30045, \
    "SystemConfig", \
    4, \
    {  { "param_save", NULL, MAVLINK_TYPE_INT8_T, 0, 8, offsetof(mavlink_systemconfig_t, param_save) }, \
         { "system_reset", NULL, MAVLINK_TYPE_INT8_T, 0, 9, offsetof(mavlink_systemconfig_t, system_reset) }, \
         { "current_loop_freq", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_systemconfig_t, current_loop_freq) }, \
         { "position_loop_freq", NULL, MAVLINK_TYPE_UINT32_T, 0, 4, offsetof(mavlink_systemconfig_t, position_loop_freq) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_SystemConfig { \
    "SystemConfig", \
    4, \
    {  { "param_save", NULL, MAVLINK_TYPE_INT8_T, 0, 8, offsetof(mavlink_systemconfig_t, param_save) }, \
         { "system_reset", NULL, MAVLINK_TYPE_INT8_T, 0, 9, offsetof(mavlink_systemconfig_t, system_reset) }, \
         { "current_loop_freq", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_systemconfig_t, current_loop_freq) }, \
         { "position_loop_freq", NULL, MAVLINK_TYPE_UINT32_T, 0, 4, offsetof(mavlink_systemconfig_t, position_loop_freq) }, \
         } \
}
#endif

/**
 * @brief Pack a systemconfig message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param param_save  
 * @param system_reset  
 * @param current_loop_freq  
 * @param position_loop_freq  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_systemconfig_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               int8_t param_save, int8_t system_reset, uint32_t current_loop_freq, uint32_t position_loop_freq)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SystemConfig_LEN];
    _mav_put_uint32_t(buf, 0, current_loop_freq);
    _mav_put_uint32_t(buf, 4, position_loop_freq);
    _mav_put_int8_t(buf, 8, param_save);
    _mav_put_int8_t(buf, 9, system_reset);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SystemConfig_LEN);
#else
    mavlink_systemconfig_t packet;
    packet.current_loop_freq = current_loop_freq;
    packet.position_loop_freq = position_loop_freq;
    packet.param_save = param_save;
    packet.system_reset = system_reset;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SystemConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SystemConfig;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_SystemConfig_MIN_LEN, MAVLINK_MSG_ID_SystemConfig_LEN, MAVLINK_MSG_ID_SystemConfig_CRC);
}

/**
 * @brief Pack a systemconfig message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param param_save  
 * @param system_reset  
 * @param current_loop_freq  
 * @param position_loop_freq  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_systemconfig_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               int8_t param_save, int8_t system_reset, uint32_t current_loop_freq, uint32_t position_loop_freq)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SystemConfig_LEN];
    _mav_put_uint32_t(buf, 0, current_loop_freq);
    _mav_put_uint32_t(buf, 4, position_loop_freq);
    _mav_put_int8_t(buf, 8, param_save);
    _mav_put_int8_t(buf, 9, system_reset);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SystemConfig_LEN);
#else
    mavlink_systemconfig_t packet;
    packet.current_loop_freq = current_loop_freq;
    packet.position_loop_freq = position_loop_freq;
    packet.param_save = param_save;
    packet.system_reset = system_reset;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SystemConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SystemConfig;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_SystemConfig_MIN_LEN, MAVLINK_MSG_ID_SystemConfig_LEN, MAVLINK_MSG_ID_SystemConfig_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_SystemConfig_MIN_LEN, MAVLINK_MSG_ID_SystemConfig_LEN);
#endif
}

/**
 * @brief Pack a systemconfig message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param param_save  
 * @param system_reset  
 * @param current_loop_freq  
 * @param position_loop_freq  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_systemconfig_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   int8_t param_save,int8_t system_reset,uint32_t current_loop_freq,uint32_t position_loop_freq)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SystemConfig_LEN];
    _mav_put_uint32_t(buf, 0, current_loop_freq);
    _mav_put_uint32_t(buf, 4, position_loop_freq);
    _mav_put_int8_t(buf, 8, param_save);
    _mav_put_int8_t(buf, 9, system_reset);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SystemConfig_LEN);
#else
    mavlink_systemconfig_t packet;
    packet.current_loop_freq = current_loop_freq;
    packet.position_loop_freq = position_loop_freq;
    packet.param_save = param_save;
    packet.system_reset = system_reset;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SystemConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SystemConfig;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_SystemConfig_MIN_LEN, MAVLINK_MSG_ID_SystemConfig_LEN, MAVLINK_MSG_ID_SystemConfig_CRC);
}

/**
 * @brief Encode a systemconfig struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param systemconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_systemconfig_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_systemconfig_t* systemconfig)
{
    return mavlink_msg_systemconfig_pack(system_id, component_id, msg, systemconfig->param_save, systemconfig->system_reset, systemconfig->current_loop_freq, systemconfig->position_loop_freq);
}

/**
 * @brief Encode a systemconfig struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param systemconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_systemconfig_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_systemconfig_t* systemconfig)
{
    return mavlink_msg_systemconfig_pack_chan(system_id, component_id, chan, msg, systemconfig->param_save, systemconfig->system_reset, systemconfig->current_loop_freq, systemconfig->position_loop_freq);
}

/**
 * @brief Encode a systemconfig struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param systemconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_systemconfig_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_systemconfig_t* systemconfig)
{
    return mavlink_msg_systemconfig_pack_status(system_id, component_id, _status, msg,  systemconfig->param_save, systemconfig->system_reset, systemconfig->current_loop_freq, systemconfig->position_loop_freq);
}

/**
 * @brief Send a systemconfig message
 * @param chan MAVLink channel to send the message
 *
 * @param param_save  
 * @param system_reset  
 * @param current_loop_freq  
 * @param position_loop_freq  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_systemconfig_send(mavlink_channel_t chan, int8_t param_save, int8_t system_reset, uint32_t current_loop_freq, uint32_t position_loop_freq)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SystemConfig_LEN];
    _mav_put_uint32_t(buf, 0, current_loop_freq);
    _mav_put_uint32_t(buf, 4, position_loop_freq);
    _mav_put_int8_t(buf, 8, param_save);
    _mav_put_int8_t(buf, 9, system_reset);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SystemConfig, buf, MAVLINK_MSG_ID_SystemConfig_MIN_LEN, MAVLINK_MSG_ID_SystemConfig_LEN, MAVLINK_MSG_ID_SystemConfig_CRC);
#else
    mavlink_systemconfig_t packet;
    packet.current_loop_freq = current_loop_freq;
    packet.position_loop_freq = position_loop_freq;
    packet.param_save = param_save;
    packet.system_reset = system_reset;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SystemConfig, (const char *)&packet, MAVLINK_MSG_ID_SystemConfig_MIN_LEN, MAVLINK_MSG_ID_SystemConfig_LEN, MAVLINK_MSG_ID_SystemConfig_CRC);
#endif
}

/**
 * @brief Send a systemconfig message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_systemconfig_send_struct(mavlink_channel_t chan, const mavlink_systemconfig_t* systemconfig)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_systemconfig_send(chan, systemconfig->param_save, systemconfig->system_reset, systemconfig->current_loop_freq, systemconfig->position_loop_freq);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SystemConfig, (const char *)systemconfig, MAVLINK_MSG_ID_SystemConfig_MIN_LEN, MAVLINK_MSG_ID_SystemConfig_LEN, MAVLINK_MSG_ID_SystemConfig_CRC);
#endif
}

#if MAVLINK_MSG_ID_SystemConfig_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_systemconfig_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  int8_t param_save, int8_t system_reset, uint32_t current_loop_freq, uint32_t position_loop_freq)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint32_t(buf, 0, current_loop_freq);
    _mav_put_uint32_t(buf, 4, position_loop_freq);
    _mav_put_int8_t(buf, 8, param_save);
    _mav_put_int8_t(buf, 9, system_reset);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SystemConfig, buf, MAVLINK_MSG_ID_SystemConfig_MIN_LEN, MAVLINK_MSG_ID_SystemConfig_LEN, MAVLINK_MSG_ID_SystemConfig_CRC);
#else
    mavlink_systemconfig_t *packet = (mavlink_systemconfig_t *)msgbuf;
    packet->current_loop_freq = current_loop_freq;
    packet->position_loop_freq = position_loop_freq;
    packet->param_save = param_save;
    packet->system_reset = system_reset;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SystemConfig, (const char *)packet, MAVLINK_MSG_ID_SystemConfig_MIN_LEN, MAVLINK_MSG_ID_SystemConfig_LEN, MAVLINK_MSG_ID_SystemConfig_CRC);
#endif
}
#endif

#endif

// MESSAGE SystemConfig UNPACKING


/**
 * @brief Get field param_save from systemconfig message
 *
 * @return  
 */
static inline int8_t mavlink_msg_systemconfig_get_param_save(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int8_t(msg,  8);
}

/**
 * @brief Get field system_reset from systemconfig message
 *
 * @return  
 */
static inline int8_t mavlink_msg_systemconfig_get_system_reset(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int8_t(msg,  9);
}

/**
 * @brief Get field current_loop_freq from systemconfig message
 *
 * @return  
 */
static inline uint32_t mavlink_msg_systemconfig_get_current_loop_freq(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Get field position_loop_freq from systemconfig message
 *
 * @return  
 */
static inline uint32_t mavlink_msg_systemconfig_get_position_loop_freq(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  4);
}

/**
 * @brief Decode a systemconfig message into a struct
 *
 * @param msg The message to decode
 * @param systemconfig C-struct to decode the message contents into
 */
static inline void mavlink_msg_systemconfig_decode(const mavlink_message_t* msg, mavlink_systemconfig_t* systemconfig)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    systemconfig->current_loop_freq = mavlink_msg_systemconfig_get_current_loop_freq(msg);
    systemconfig->position_loop_freq = mavlink_msg_systemconfig_get_position_loop_freq(msg);
    systemconfig->param_save = mavlink_msg_systemconfig_get_param_save(msg);
    systemconfig->system_reset = mavlink_msg_systemconfig_get_system_reset(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_SystemConfig_LEN? msg->len : MAVLINK_MSG_ID_SystemConfig_LEN;
        memset(systemconfig, 0, MAVLINK_MSG_ID_SystemConfig_LEN);
    memcpy(systemconfig, _MAV_PAYLOAD(msg), len);
#endif
}
