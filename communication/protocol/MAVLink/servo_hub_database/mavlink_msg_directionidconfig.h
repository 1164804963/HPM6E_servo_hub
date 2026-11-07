#pragma once
// MESSAGE DirectionIdConfig PACKING

#define MAVLINK_MSG_ID_DirectionIdConfig 30036


typedef struct __mavlink_directionidconfig_t {
 float elec_angle_add_rad; /*<  */
 float current_slope_percentage; /*<  */
 float id_tar_max_A; /*<  */
} mavlink_directionidconfig_t;

#define MAVLINK_MSG_ID_DirectionIdConfig_LEN 12
#define MAVLINK_MSG_ID_DirectionIdConfig_MIN_LEN 12
#define MAVLINK_MSG_ID_30036_LEN 12
#define MAVLINK_MSG_ID_30036_MIN_LEN 12

#define MAVLINK_MSG_ID_DirectionIdConfig_CRC 197
#define MAVLINK_MSG_ID_30036_CRC 197



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_DirectionIdConfig { \
    30036, \
    "DirectionIdConfig", \
    3, \
    {  { "elec_angle_add_rad", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_directionidconfig_t, elec_angle_add_rad) }, \
         { "current_slope_percentage", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_directionidconfig_t, current_slope_percentage) }, \
         { "id_tar_max_A", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_directionidconfig_t, id_tar_max_A) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_DirectionIdConfig { \
    "DirectionIdConfig", \
    3, \
    {  { "elec_angle_add_rad", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_directionidconfig_t, elec_angle_add_rad) }, \
         { "current_slope_percentage", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_directionidconfig_t, current_slope_percentage) }, \
         { "id_tar_max_A", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_directionidconfig_t, id_tar_max_A) }, \
         } \
}
#endif

/**
 * @brief Pack a directionidconfig message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param elec_angle_add_rad  
 * @param current_slope_percentage  
 * @param id_tar_max_A  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_directionidconfig_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               float elec_angle_add_rad, float current_slope_percentage, float id_tar_max_A)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_DirectionIdConfig_LEN];
    _mav_put_float(buf, 0, elec_angle_add_rad);
    _mav_put_float(buf, 4, current_slope_percentage);
    _mav_put_float(buf, 8, id_tar_max_A);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_DirectionIdConfig_LEN);
#else
    mavlink_directionidconfig_t packet;
    packet.elec_angle_add_rad = elec_angle_add_rad;
    packet.current_slope_percentage = current_slope_percentage;
    packet.id_tar_max_A = id_tar_max_A;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_DirectionIdConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_DirectionIdConfig;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_DirectionIdConfig_MIN_LEN, MAVLINK_MSG_ID_DirectionIdConfig_LEN, MAVLINK_MSG_ID_DirectionIdConfig_CRC);
}

/**
 * @brief Pack a directionidconfig message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param elec_angle_add_rad  
 * @param current_slope_percentage  
 * @param id_tar_max_A  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_directionidconfig_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               float elec_angle_add_rad, float current_slope_percentage, float id_tar_max_A)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_DirectionIdConfig_LEN];
    _mav_put_float(buf, 0, elec_angle_add_rad);
    _mav_put_float(buf, 4, current_slope_percentage);
    _mav_put_float(buf, 8, id_tar_max_A);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_DirectionIdConfig_LEN);
#else
    mavlink_directionidconfig_t packet;
    packet.elec_angle_add_rad = elec_angle_add_rad;
    packet.current_slope_percentage = current_slope_percentage;
    packet.id_tar_max_A = id_tar_max_A;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_DirectionIdConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_DirectionIdConfig;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_DirectionIdConfig_MIN_LEN, MAVLINK_MSG_ID_DirectionIdConfig_LEN, MAVLINK_MSG_ID_DirectionIdConfig_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_DirectionIdConfig_MIN_LEN, MAVLINK_MSG_ID_DirectionIdConfig_LEN);
#endif
}

/**
 * @brief Pack a directionidconfig message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param elec_angle_add_rad  
 * @param current_slope_percentage  
 * @param id_tar_max_A  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_directionidconfig_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   float elec_angle_add_rad,float current_slope_percentage,float id_tar_max_A)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_DirectionIdConfig_LEN];
    _mav_put_float(buf, 0, elec_angle_add_rad);
    _mav_put_float(buf, 4, current_slope_percentage);
    _mav_put_float(buf, 8, id_tar_max_A);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_DirectionIdConfig_LEN);
#else
    mavlink_directionidconfig_t packet;
    packet.elec_angle_add_rad = elec_angle_add_rad;
    packet.current_slope_percentage = current_slope_percentage;
    packet.id_tar_max_A = id_tar_max_A;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_DirectionIdConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_DirectionIdConfig;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_DirectionIdConfig_MIN_LEN, MAVLINK_MSG_ID_DirectionIdConfig_LEN, MAVLINK_MSG_ID_DirectionIdConfig_CRC);
}

/**
 * @brief Encode a directionidconfig struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param directionidconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_directionidconfig_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_directionidconfig_t* directionidconfig)
{
    return mavlink_msg_directionidconfig_pack(system_id, component_id, msg, directionidconfig->elec_angle_add_rad, directionidconfig->current_slope_percentage, directionidconfig->id_tar_max_A);
}

/**
 * @brief Encode a directionidconfig struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param directionidconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_directionidconfig_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_directionidconfig_t* directionidconfig)
{
    return mavlink_msg_directionidconfig_pack_chan(system_id, component_id, chan, msg, directionidconfig->elec_angle_add_rad, directionidconfig->current_slope_percentage, directionidconfig->id_tar_max_A);
}

/**
 * @brief Encode a directionidconfig struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param directionidconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_directionidconfig_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_directionidconfig_t* directionidconfig)
{
    return mavlink_msg_directionidconfig_pack_status(system_id, component_id, _status, msg,  directionidconfig->elec_angle_add_rad, directionidconfig->current_slope_percentage, directionidconfig->id_tar_max_A);
}

/**
 * @brief Send a directionidconfig message
 * @param chan MAVLink channel to send the message
 *
 * @param elec_angle_add_rad  
 * @param current_slope_percentage  
 * @param id_tar_max_A  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_directionidconfig_send(mavlink_channel_t chan, float elec_angle_add_rad, float current_slope_percentage, float id_tar_max_A)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_DirectionIdConfig_LEN];
    _mav_put_float(buf, 0, elec_angle_add_rad);
    _mav_put_float(buf, 4, current_slope_percentage);
    _mav_put_float(buf, 8, id_tar_max_A);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_DirectionIdConfig, buf, MAVLINK_MSG_ID_DirectionIdConfig_MIN_LEN, MAVLINK_MSG_ID_DirectionIdConfig_LEN, MAVLINK_MSG_ID_DirectionIdConfig_CRC);
#else
    mavlink_directionidconfig_t packet;
    packet.elec_angle_add_rad = elec_angle_add_rad;
    packet.current_slope_percentage = current_slope_percentage;
    packet.id_tar_max_A = id_tar_max_A;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_DirectionIdConfig, (const char *)&packet, MAVLINK_MSG_ID_DirectionIdConfig_MIN_LEN, MAVLINK_MSG_ID_DirectionIdConfig_LEN, MAVLINK_MSG_ID_DirectionIdConfig_CRC);
#endif
}

/**
 * @brief Send a directionidconfig message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_directionidconfig_send_struct(mavlink_channel_t chan, const mavlink_directionidconfig_t* directionidconfig)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_directionidconfig_send(chan, directionidconfig->elec_angle_add_rad, directionidconfig->current_slope_percentage, directionidconfig->id_tar_max_A);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_DirectionIdConfig, (const char *)directionidconfig, MAVLINK_MSG_ID_DirectionIdConfig_MIN_LEN, MAVLINK_MSG_ID_DirectionIdConfig_LEN, MAVLINK_MSG_ID_DirectionIdConfig_CRC);
#endif
}

#if MAVLINK_MSG_ID_DirectionIdConfig_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_directionidconfig_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float elec_angle_add_rad, float current_slope_percentage, float id_tar_max_A)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, elec_angle_add_rad);
    _mav_put_float(buf, 4, current_slope_percentage);
    _mav_put_float(buf, 8, id_tar_max_A);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_DirectionIdConfig, buf, MAVLINK_MSG_ID_DirectionIdConfig_MIN_LEN, MAVLINK_MSG_ID_DirectionIdConfig_LEN, MAVLINK_MSG_ID_DirectionIdConfig_CRC);
#else
    mavlink_directionidconfig_t *packet = (mavlink_directionidconfig_t *)msgbuf;
    packet->elec_angle_add_rad = elec_angle_add_rad;
    packet->current_slope_percentage = current_slope_percentage;
    packet->id_tar_max_A = id_tar_max_A;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_DirectionIdConfig, (const char *)packet, MAVLINK_MSG_ID_DirectionIdConfig_MIN_LEN, MAVLINK_MSG_ID_DirectionIdConfig_LEN, MAVLINK_MSG_ID_DirectionIdConfig_CRC);
#endif
}
#endif

#endif

// MESSAGE DirectionIdConfig UNPACKING


/**
 * @brief Get field elec_angle_add_rad from directionidconfig message
 *
 * @return  
 */
static inline float mavlink_msg_directionidconfig_get_elec_angle_add_rad(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field current_slope_percentage from directionidconfig message
 *
 * @return  
 */
static inline float mavlink_msg_directionidconfig_get_current_slope_percentage(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field id_tar_max_A from directionidconfig message
 *
 * @return  
 */
static inline float mavlink_msg_directionidconfig_get_id_tar_max_A(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Decode a directionidconfig message into a struct
 *
 * @param msg The message to decode
 * @param directionidconfig C-struct to decode the message contents into
 */
static inline void mavlink_msg_directionidconfig_decode(const mavlink_message_t* msg, mavlink_directionidconfig_t* directionidconfig)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    directionidconfig->elec_angle_add_rad = mavlink_msg_directionidconfig_get_elec_angle_add_rad(msg);
    directionidconfig->current_slope_percentage = mavlink_msg_directionidconfig_get_current_slope_percentage(msg);
    directionidconfig->id_tar_max_A = mavlink_msg_directionidconfig_get_id_tar_max_A(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_DirectionIdConfig_LEN? msg->len : MAVLINK_MSG_ID_DirectionIdConfig_LEN;
        memset(directionidconfig, 0, MAVLINK_MSG_ID_DirectionIdConfig_LEN);
    memcpy(directionidconfig, _MAV_PAYLOAD(msg), len);
#endif
}
