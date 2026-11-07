#pragma once
// MESSAGE ElecAngleIdConfig PACKING

#define MAVLINK_MSG_ID_ElecAngleIdConfig 30032


typedef struct __mavlink_elecangleidconfig_t {
 float id_max_A; /*<  */
 float dt_s; /*<  */
 float angle_add_rad; /*<  */
 float wait_time_s; /*<  */
 float test_angle_rad; /*<  */
 float current_slope_percentage; /*<  */
 uint8_t method; /*<  */
} mavlink_elecangleidconfig_t;

#define MAVLINK_MSG_ID_ElecAngleIdConfig_LEN 25
#define MAVLINK_MSG_ID_ElecAngleIdConfig_MIN_LEN 25
#define MAVLINK_MSG_ID_30032_LEN 25
#define MAVLINK_MSG_ID_30032_MIN_LEN 25

#define MAVLINK_MSG_ID_ElecAngleIdConfig_CRC 112
#define MAVLINK_MSG_ID_30032_CRC 112



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_ElecAngleIdConfig { \
    30032, \
    "ElecAngleIdConfig", \
    7, \
    {  { "id_max_A", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_elecangleidconfig_t, id_max_A) }, \
         { "dt_s", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_elecangleidconfig_t, dt_s) }, \
         { "method", NULL, MAVLINK_TYPE_UINT8_T, 0, 24, offsetof(mavlink_elecangleidconfig_t, method) }, \
         { "angle_add_rad", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_elecangleidconfig_t, angle_add_rad) }, \
         { "wait_time_s", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_elecangleidconfig_t, wait_time_s) }, \
         { "test_angle_rad", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_elecangleidconfig_t, test_angle_rad) }, \
         { "current_slope_percentage", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_elecangleidconfig_t, current_slope_percentage) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_ElecAngleIdConfig { \
    "ElecAngleIdConfig", \
    7, \
    {  { "id_max_A", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_elecangleidconfig_t, id_max_A) }, \
         { "dt_s", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_elecangleidconfig_t, dt_s) }, \
         { "method", NULL, MAVLINK_TYPE_UINT8_T, 0, 24, offsetof(mavlink_elecangleidconfig_t, method) }, \
         { "angle_add_rad", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_elecangleidconfig_t, angle_add_rad) }, \
         { "wait_time_s", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_elecangleidconfig_t, wait_time_s) }, \
         { "test_angle_rad", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_elecangleidconfig_t, test_angle_rad) }, \
         { "current_slope_percentage", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_elecangleidconfig_t, current_slope_percentage) }, \
         } \
}
#endif

/**
 * @brief Pack a elecangleidconfig message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param id_max_A  
 * @param dt_s  
 * @param method  
 * @param angle_add_rad  
 * @param wait_time_s  
 * @param test_angle_rad  
 * @param current_slope_percentage  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_elecangleidconfig_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               float id_max_A, float dt_s, uint8_t method, float angle_add_rad, float wait_time_s, float test_angle_rad, float current_slope_percentage)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ElecAngleIdConfig_LEN];
    _mav_put_float(buf, 0, id_max_A);
    _mav_put_float(buf, 4, dt_s);
    _mav_put_float(buf, 8, angle_add_rad);
    _mav_put_float(buf, 12, wait_time_s);
    _mav_put_float(buf, 16, test_angle_rad);
    _mav_put_float(buf, 20, current_slope_percentage);
    _mav_put_uint8_t(buf, 24, method);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ElecAngleIdConfig_LEN);
#else
    mavlink_elecangleidconfig_t packet;
    packet.id_max_A = id_max_A;
    packet.dt_s = dt_s;
    packet.angle_add_rad = angle_add_rad;
    packet.wait_time_s = wait_time_s;
    packet.test_angle_rad = test_angle_rad;
    packet.current_slope_percentage = current_slope_percentage;
    packet.method = method;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ElecAngleIdConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ElecAngleIdConfig;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_ElecAngleIdConfig_MIN_LEN, MAVLINK_MSG_ID_ElecAngleIdConfig_LEN, MAVLINK_MSG_ID_ElecAngleIdConfig_CRC);
}

/**
 * @brief Pack a elecangleidconfig message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param id_max_A  
 * @param dt_s  
 * @param method  
 * @param angle_add_rad  
 * @param wait_time_s  
 * @param test_angle_rad  
 * @param current_slope_percentage  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_elecangleidconfig_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               float id_max_A, float dt_s, uint8_t method, float angle_add_rad, float wait_time_s, float test_angle_rad, float current_slope_percentage)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ElecAngleIdConfig_LEN];
    _mav_put_float(buf, 0, id_max_A);
    _mav_put_float(buf, 4, dt_s);
    _mav_put_float(buf, 8, angle_add_rad);
    _mav_put_float(buf, 12, wait_time_s);
    _mav_put_float(buf, 16, test_angle_rad);
    _mav_put_float(buf, 20, current_slope_percentage);
    _mav_put_uint8_t(buf, 24, method);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ElecAngleIdConfig_LEN);
#else
    mavlink_elecangleidconfig_t packet;
    packet.id_max_A = id_max_A;
    packet.dt_s = dt_s;
    packet.angle_add_rad = angle_add_rad;
    packet.wait_time_s = wait_time_s;
    packet.test_angle_rad = test_angle_rad;
    packet.current_slope_percentage = current_slope_percentage;
    packet.method = method;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ElecAngleIdConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ElecAngleIdConfig;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_ElecAngleIdConfig_MIN_LEN, MAVLINK_MSG_ID_ElecAngleIdConfig_LEN, MAVLINK_MSG_ID_ElecAngleIdConfig_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_ElecAngleIdConfig_MIN_LEN, MAVLINK_MSG_ID_ElecAngleIdConfig_LEN);
#endif
}

/**
 * @brief Pack a elecangleidconfig message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param id_max_A  
 * @param dt_s  
 * @param method  
 * @param angle_add_rad  
 * @param wait_time_s  
 * @param test_angle_rad  
 * @param current_slope_percentage  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_elecangleidconfig_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   float id_max_A,float dt_s,uint8_t method,float angle_add_rad,float wait_time_s,float test_angle_rad,float current_slope_percentage)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ElecAngleIdConfig_LEN];
    _mav_put_float(buf, 0, id_max_A);
    _mav_put_float(buf, 4, dt_s);
    _mav_put_float(buf, 8, angle_add_rad);
    _mav_put_float(buf, 12, wait_time_s);
    _mav_put_float(buf, 16, test_angle_rad);
    _mav_put_float(buf, 20, current_slope_percentage);
    _mav_put_uint8_t(buf, 24, method);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ElecAngleIdConfig_LEN);
#else
    mavlink_elecangleidconfig_t packet;
    packet.id_max_A = id_max_A;
    packet.dt_s = dt_s;
    packet.angle_add_rad = angle_add_rad;
    packet.wait_time_s = wait_time_s;
    packet.test_angle_rad = test_angle_rad;
    packet.current_slope_percentage = current_slope_percentage;
    packet.method = method;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ElecAngleIdConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ElecAngleIdConfig;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_ElecAngleIdConfig_MIN_LEN, MAVLINK_MSG_ID_ElecAngleIdConfig_LEN, MAVLINK_MSG_ID_ElecAngleIdConfig_CRC);
}

/**
 * @brief Encode a elecangleidconfig struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param elecangleidconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_elecangleidconfig_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_elecangleidconfig_t* elecangleidconfig)
{
    return mavlink_msg_elecangleidconfig_pack(system_id, component_id, msg, elecangleidconfig->id_max_A, elecangleidconfig->dt_s, elecangleidconfig->method, elecangleidconfig->angle_add_rad, elecangleidconfig->wait_time_s, elecangleidconfig->test_angle_rad, elecangleidconfig->current_slope_percentage);
}

/**
 * @brief Encode a elecangleidconfig struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param elecangleidconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_elecangleidconfig_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_elecangleidconfig_t* elecangleidconfig)
{
    return mavlink_msg_elecangleidconfig_pack_chan(system_id, component_id, chan, msg, elecangleidconfig->id_max_A, elecangleidconfig->dt_s, elecangleidconfig->method, elecangleidconfig->angle_add_rad, elecangleidconfig->wait_time_s, elecangleidconfig->test_angle_rad, elecangleidconfig->current_slope_percentage);
}

/**
 * @brief Encode a elecangleidconfig struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param elecangleidconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_elecangleidconfig_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_elecangleidconfig_t* elecangleidconfig)
{
    return mavlink_msg_elecangleidconfig_pack_status(system_id, component_id, _status, msg,  elecangleidconfig->id_max_A, elecangleidconfig->dt_s, elecangleidconfig->method, elecangleidconfig->angle_add_rad, elecangleidconfig->wait_time_s, elecangleidconfig->test_angle_rad, elecangleidconfig->current_slope_percentage);
}

/**
 * @brief Send a elecangleidconfig message
 * @param chan MAVLink channel to send the message
 *
 * @param id_max_A  
 * @param dt_s  
 * @param method  
 * @param angle_add_rad  
 * @param wait_time_s  
 * @param test_angle_rad  
 * @param current_slope_percentage  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_elecangleidconfig_send(mavlink_channel_t chan, float id_max_A, float dt_s, uint8_t method, float angle_add_rad, float wait_time_s, float test_angle_rad, float current_slope_percentage)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ElecAngleIdConfig_LEN];
    _mav_put_float(buf, 0, id_max_A);
    _mav_put_float(buf, 4, dt_s);
    _mav_put_float(buf, 8, angle_add_rad);
    _mav_put_float(buf, 12, wait_time_s);
    _mav_put_float(buf, 16, test_angle_rad);
    _mav_put_float(buf, 20, current_slope_percentage);
    _mav_put_uint8_t(buf, 24, method);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ElecAngleIdConfig, buf, MAVLINK_MSG_ID_ElecAngleIdConfig_MIN_LEN, MAVLINK_MSG_ID_ElecAngleIdConfig_LEN, MAVLINK_MSG_ID_ElecAngleIdConfig_CRC);
#else
    mavlink_elecangleidconfig_t packet;
    packet.id_max_A = id_max_A;
    packet.dt_s = dt_s;
    packet.angle_add_rad = angle_add_rad;
    packet.wait_time_s = wait_time_s;
    packet.test_angle_rad = test_angle_rad;
    packet.current_slope_percentage = current_slope_percentage;
    packet.method = method;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ElecAngleIdConfig, (const char *)&packet, MAVLINK_MSG_ID_ElecAngleIdConfig_MIN_LEN, MAVLINK_MSG_ID_ElecAngleIdConfig_LEN, MAVLINK_MSG_ID_ElecAngleIdConfig_CRC);
#endif
}

/**
 * @brief Send a elecangleidconfig message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_elecangleidconfig_send_struct(mavlink_channel_t chan, const mavlink_elecangleidconfig_t* elecangleidconfig)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_elecangleidconfig_send(chan, elecangleidconfig->id_max_A, elecangleidconfig->dt_s, elecangleidconfig->method, elecangleidconfig->angle_add_rad, elecangleidconfig->wait_time_s, elecangleidconfig->test_angle_rad, elecangleidconfig->current_slope_percentage);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ElecAngleIdConfig, (const char *)elecangleidconfig, MAVLINK_MSG_ID_ElecAngleIdConfig_MIN_LEN, MAVLINK_MSG_ID_ElecAngleIdConfig_LEN, MAVLINK_MSG_ID_ElecAngleIdConfig_CRC);
#endif
}

#if MAVLINK_MSG_ID_ElecAngleIdConfig_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_elecangleidconfig_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float id_max_A, float dt_s, uint8_t method, float angle_add_rad, float wait_time_s, float test_angle_rad, float current_slope_percentage)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, id_max_A);
    _mav_put_float(buf, 4, dt_s);
    _mav_put_float(buf, 8, angle_add_rad);
    _mav_put_float(buf, 12, wait_time_s);
    _mav_put_float(buf, 16, test_angle_rad);
    _mav_put_float(buf, 20, current_slope_percentage);
    _mav_put_uint8_t(buf, 24, method);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ElecAngleIdConfig, buf, MAVLINK_MSG_ID_ElecAngleIdConfig_MIN_LEN, MAVLINK_MSG_ID_ElecAngleIdConfig_LEN, MAVLINK_MSG_ID_ElecAngleIdConfig_CRC);
#else
    mavlink_elecangleidconfig_t *packet = (mavlink_elecangleidconfig_t *)msgbuf;
    packet->id_max_A = id_max_A;
    packet->dt_s = dt_s;
    packet->angle_add_rad = angle_add_rad;
    packet->wait_time_s = wait_time_s;
    packet->test_angle_rad = test_angle_rad;
    packet->current_slope_percentage = current_slope_percentage;
    packet->method = method;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ElecAngleIdConfig, (const char *)packet, MAVLINK_MSG_ID_ElecAngleIdConfig_MIN_LEN, MAVLINK_MSG_ID_ElecAngleIdConfig_LEN, MAVLINK_MSG_ID_ElecAngleIdConfig_CRC);
#endif
}
#endif

#endif

// MESSAGE ElecAngleIdConfig UNPACKING


/**
 * @brief Get field id_max_A from elecangleidconfig message
 *
 * @return  
 */
static inline float mavlink_msg_elecangleidconfig_get_id_max_A(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field dt_s from elecangleidconfig message
 *
 * @return  
 */
static inline float mavlink_msg_elecangleidconfig_get_dt_s(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field method from elecangleidconfig message
 *
 * @return  
 */
static inline uint8_t mavlink_msg_elecangleidconfig_get_method(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  24);
}

/**
 * @brief Get field angle_add_rad from elecangleidconfig message
 *
 * @return  
 */
static inline float mavlink_msg_elecangleidconfig_get_angle_add_rad(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field wait_time_s from elecangleidconfig message
 *
 * @return  
 */
static inline float mavlink_msg_elecangleidconfig_get_wait_time_s(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Get field test_angle_rad from elecangleidconfig message
 *
 * @return  
 */
static inline float mavlink_msg_elecangleidconfig_get_test_angle_rad(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  16);
}

/**
 * @brief Get field current_slope_percentage from elecangleidconfig message
 *
 * @return  
 */
static inline float mavlink_msg_elecangleidconfig_get_current_slope_percentage(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  20);
}

/**
 * @brief Decode a elecangleidconfig message into a struct
 *
 * @param msg The message to decode
 * @param elecangleidconfig C-struct to decode the message contents into
 */
static inline void mavlink_msg_elecangleidconfig_decode(const mavlink_message_t* msg, mavlink_elecangleidconfig_t* elecangleidconfig)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    elecangleidconfig->id_max_A = mavlink_msg_elecangleidconfig_get_id_max_A(msg);
    elecangleidconfig->dt_s = mavlink_msg_elecangleidconfig_get_dt_s(msg);
    elecangleidconfig->angle_add_rad = mavlink_msg_elecangleidconfig_get_angle_add_rad(msg);
    elecangleidconfig->wait_time_s = mavlink_msg_elecangleidconfig_get_wait_time_s(msg);
    elecangleidconfig->test_angle_rad = mavlink_msg_elecangleidconfig_get_test_angle_rad(msg);
    elecangleidconfig->current_slope_percentage = mavlink_msg_elecangleidconfig_get_current_slope_percentage(msg);
    elecangleidconfig->method = mavlink_msg_elecangleidconfig_get_method(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_ElecAngleIdConfig_LEN? msg->len : MAVLINK_MSG_ID_ElecAngleIdConfig_LEN;
        memset(elecangleidconfig, 0, MAVLINK_MSG_ID_ElecAngleIdConfig_LEN);
    memcpy(elecangleidconfig, _MAV_PAYLOAD(msg), len);
#endif
}
