#pragma once
// MESSAGE InputShapingConfig PACKING

#define MAVLINK_MSG_ID_InputShapingConfig 30012


typedef struct __mavlink_inputshapingconfig_t {
 float wn_Hz; /*<  */
 float run_frq_Hz; /*<  */
 uint8_t enable; /*<  */
} mavlink_inputshapingconfig_t;

#define MAVLINK_MSG_ID_InputShapingConfig_LEN 9
#define MAVLINK_MSG_ID_InputShapingConfig_MIN_LEN 9
#define MAVLINK_MSG_ID_30012_LEN 9
#define MAVLINK_MSG_ID_30012_MIN_LEN 9

#define MAVLINK_MSG_ID_InputShapingConfig_CRC 238
#define MAVLINK_MSG_ID_30012_CRC 238



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_InputShapingConfig { \
    30012, \
    "InputShapingConfig", \
    3, \
    {  { "wn_Hz", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_inputshapingconfig_t, wn_Hz) }, \
         { "run_frq_Hz", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_inputshapingconfig_t, run_frq_Hz) }, \
         { "enable", NULL, MAVLINK_TYPE_UINT8_T, 0, 8, offsetof(mavlink_inputshapingconfig_t, enable) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_InputShapingConfig { \
    "InputShapingConfig", \
    3, \
    {  { "wn_Hz", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_inputshapingconfig_t, wn_Hz) }, \
         { "run_frq_Hz", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_inputshapingconfig_t, run_frq_Hz) }, \
         { "enable", NULL, MAVLINK_TYPE_UINT8_T, 0, 8, offsetof(mavlink_inputshapingconfig_t, enable) }, \
         } \
}
#endif

/**
 * @brief Pack a inputshapingconfig message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param wn_Hz  
 * @param run_frq_Hz  
 * @param enable  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_inputshapingconfig_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               float wn_Hz, float run_frq_Hz, uint8_t enable)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_InputShapingConfig_LEN];
    _mav_put_float(buf, 0, wn_Hz);
    _mav_put_float(buf, 4, run_frq_Hz);
    _mav_put_uint8_t(buf, 8, enable);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_InputShapingConfig_LEN);
#else
    mavlink_inputshapingconfig_t packet;
    packet.wn_Hz = wn_Hz;
    packet.run_frq_Hz = run_frq_Hz;
    packet.enable = enable;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_InputShapingConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_InputShapingConfig;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_InputShapingConfig_MIN_LEN, MAVLINK_MSG_ID_InputShapingConfig_LEN, MAVLINK_MSG_ID_InputShapingConfig_CRC);
}

/**
 * @brief Pack a inputshapingconfig message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param wn_Hz  
 * @param run_frq_Hz  
 * @param enable  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_inputshapingconfig_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               float wn_Hz, float run_frq_Hz, uint8_t enable)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_InputShapingConfig_LEN];
    _mav_put_float(buf, 0, wn_Hz);
    _mav_put_float(buf, 4, run_frq_Hz);
    _mav_put_uint8_t(buf, 8, enable);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_InputShapingConfig_LEN);
#else
    mavlink_inputshapingconfig_t packet;
    packet.wn_Hz = wn_Hz;
    packet.run_frq_Hz = run_frq_Hz;
    packet.enable = enable;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_InputShapingConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_InputShapingConfig;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_InputShapingConfig_MIN_LEN, MAVLINK_MSG_ID_InputShapingConfig_LEN, MAVLINK_MSG_ID_InputShapingConfig_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_InputShapingConfig_MIN_LEN, MAVLINK_MSG_ID_InputShapingConfig_LEN);
#endif
}

/**
 * @brief Pack a inputshapingconfig message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param wn_Hz  
 * @param run_frq_Hz  
 * @param enable  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_inputshapingconfig_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   float wn_Hz,float run_frq_Hz,uint8_t enable)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_InputShapingConfig_LEN];
    _mav_put_float(buf, 0, wn_Hz);
    _mav_put_float(buf, 4, run_frq_Hz);
    _mav_put_uint8_t(buf, 8, enable);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_InputShapingConfig_LEN);
#else
    mavlink_inputshapingconfig_t packet;
    packet.wn_Hz = wn_Hz;
    packet.run_frq_Hz = run_frq_Hz;
    packet.enable = enable;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_InputShapingConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_InputShapingConfig;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_InputShapingConfig_MIN_LEN, MAVLINK_MSG_ID_InputShapingConfig_LEN, MAVLINK_MSG_ID_InputShapingConfig_CRC);
}

/**
 * @brief Encode a inputshapingconfig struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param inputshapingconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_inputshapingconfig_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_inputshapingconfig_t* inputshapingconfig)
{
    return mavlink_msg_inputshapingconfig_pack(system_id, component_id, msg, inputshapingconfig->wn_Hz, inputshapingconfig->run_frq_Hz, inputshapingconfig->enable);
}

/**
 * @brief Encode a inputshapingconfig struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param inputshapingconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_inputshapingconfig_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_inputshapingconfig_t* inputshapingconfig)
{
    return mavlink_msg_inputshapingconfig_pack_chan(system_id, component_id, chan, msg, inputshapingconfig->wn_Hz, inputshapingconfig->run_frq_Hz, inputshapingconfig->enable);
}

/**
 * @brief Encode a inputshapingconfig struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param inputshapingconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_inputshapingconfig_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_inputshapingconfig_t* inputshapingconfig)
{
    return mavlink_msg_inputshapingconfig_pack_status(system_id, component_id, _status, msg,  inputshapingconfig->wn_Hz, inputshapingconfig->run_frq_Hz, inputshapingconfig->enable);
}

/**
 * @brief Send a inputshapingconfig message
 * @param chan MAVLink channel to send the message
 *
 * @param wn_Hz  
 * @param run_frq_Hz  
 * @param enable  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_inputshapingconfig_send(mavlink_channel_t chan, float wn_Hz, float run_frq_Hz, uint8_t enable)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_InputShapingConfig_LEN];
    _mav_put_float(buf, 0, wn_Hz);
    _mav_put_float(buf, 4, run_frq_Hz);
    _mav_put_uint8_t(buf, 8, enable);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_InputShapingConfig, buf, MAVLINK_MSG_ID_InputShapingConfig_MIN_LEN, MAVLINK_MSG_ID_InputShapingConfig_LEN, MAVLINK_MSG_ID_InputShapingConfig_CRC);
#else
    mavlink_inputshapingconfig_t packet;
    packet.wn_Hz = wn_Hz;
    packet.run_frq_Hz = run_frq_Hz;
    packet.enable = enable;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_InputShapingConfig, (const char *)&packet, MAVLINK_MSG_ID_InputShapingConfig_MIN_LEN, MAVLINK_MSG_ID_InputShapingConfig_LEN, MAVLINK_MSG_ID_InputShapingConfig_CRC);
#endif
}

/**
 * @brief Send a inputshapingconfig message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_inputshapingconfig_send_struct(mavlink_channel_t chan, const mavlink_inputshapingconfig_t* inputshapingconfig)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_inputshapingconfig_send(chan, inputshapingconfig->wn_Hz, inputshapingconfig->run_frq_Hz, inputshapingconfig->enable);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_InputShapingConfig, (const char *)inputshapingconfig, MAVLINK_MSG_ID_InputShapingConfig_MIN_LEN, MAVLINK_MSG_ID_InputShapingConfig_LEN, MAVLINK_MSG_ID_InputShapingConfig_CRC);
#endif
}

#if MAVLINK_MSG_ID_InputShapingConfig_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_inputshapingconfig_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float wn_Hz, float run_frq_Hz, uint8_t enable)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, wn_Hz);
    _mav_put_float(buf, 4, run_frq_Hz);
    _mav_put_uint8_t(buf, 8, enable);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_InputShapingConfig, buf, MAVLINK_MSG_ID_InputShapingConfig_MIN_LEN, MAVLINK_MSG_ID_InputShapingConfig_LEN, MAVLINK_MSG_ID_InputShapingConfig_CRC);
#else
    mavlink_inputshapingconfig_t *packet = (mavlink_inputshapingconfig_t *)msgbuf;
    packet->wn_Hz = wn_Hz;
    packet->run_frq_Hz = run_frq_Hz;
    packet->enable = enable;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_InputShapingConfig, (const char *)packet, MAVLINK_MSG_ID_InputShapingConfig_MIN_LEN, MAVLINK_MSG_ID_InputShapingConfig_LEN, MAVLINK_MSG_ID_InputShapingConfig_CRC);
#endif
}
#endif

#endif

// MESSAGE InputShapingConfig UNPACKING


/**
 * @brief Get field wn_Hz from inputshapingconfig message
 *
 * @return  
 */
static inline float mavlink_msg_inputshapingconfig_get_wn_Hz(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field run_frq_Hz from inputshapingconfig message
 *
 * @return  
 */
static inline float mavlink_msg_inputshapingconfig_get_run_frq_Hz(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field enable from inputshapingconfig message
 *
 * @return  
 */
static inline uint8_t mavlink_msg_inputshapingconfig_get_enable(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  8);
}

/**
 * @brief Decode a inputshapingconfig message into a struct
 *
 * @param msg The message to decode
 * @param inputshapingconfig C-struct to decode the message contents into
 */
static inline void mavlink_msg_inputshapingconfig_decode(const mavlink_message_t* msg, mavlink_inputshapingconfig_t* inputshapingconfig)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    inputshapingconfig->wn_Hz = mavlink_msg_inputshapingconfig_get_wn_Hz(msg);
    inputshapingconfig->run_frq_Hz = mavlink_msg_inputshapingconfig_get_run_frq_Hz(msg);
    inputshapingconfig->enable = mavlink_msg_inputshapingconfig_get_enable(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_InputShapingConfig_LEN? msg->len : MAVLINK_MSG_ID_InputShapingConfig_LEN;
        memset(inputshapingconfig, 0, MAVLINK_MSG_ID_InputShapingConfig_LEN);
    memcpy(inputshapingconfig, _MAV_PAYLOAD(msg), len);
#endif
}
