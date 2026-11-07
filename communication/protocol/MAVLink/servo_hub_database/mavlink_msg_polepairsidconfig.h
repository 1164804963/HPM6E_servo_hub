#pragma once
// MESSAGE PolePairsIdConfig PACKING

#define MAVLINK_MSG_ID_PolePairsIdConfig 30042


typedef struct __mavlink_polepairsidconfig_t {
 float elec_angle_add; /*<  */
 uint32_t enc_line_p_n; /*<  */
 float id_tar_max_A; /*<  */
 float current_slope_percentage; /*<  */
} mavlink_polepairsidconfig_t;

#define MAVLINK_MSG_ID_PolePairsIdConfig_LEN 16
#define MAVLINK_MSG_ID_PolePairsIdConfig_MIN_LEN 16
#define MAVLINK_MSG_ID_30042_LEN 16
#define MAVLINK_MSG_ID_30042_MIN_LEN 16

#define MAVLINK_MSG_ID_PolePairsIdConfig_CRC 5
#define MAVLINK_MSG_ID_30042_CRC 5



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_PolePairsIdConfig { \
    30042, \
    "PolePairsIdConfig", \
    4, \
    {  { "elec_angle_add", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_polepairsidconfig_t, elec_angle_add) }, \
         { "enc_line_p_n", NULL, MAVLINK_TYPE_UINT32_T, 0, 4, offsetof(mavlink_polepairsidconfig_t, enc_line_p_n) }, \
         { "id_tar_max_A", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_polepairsidconfig_t, id_tar_max_A) }, \
         { "current_slope_percentage", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_polepairsidconfig_t, current_slope_percentage) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_PolePairsIdConfig { \
    "PolePairsIdConfig", \
    4, \
    {  { "elec_angle_add", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_polepairsidconfig_t, elec_angle_add) }, \
         { "enc_line_p_n", NULL, MAVLINK_TYPE_UINT32_T, 0, 4, offsetof(mavlink_polepairsidconfig_t, enc_line_p_n) }, \
         { "id_tar_max_A", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_polepairsidconfig_t, id_tar_max_A) }, \
         { "current_slope_percentage", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_polepairsidconfig_t, current_slope_percentage) }, \
         } \
}
#endif

/**
 * @brief Pack a polepairsidconfig message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param elec_angle_add  
 * @param enc_line_p_n  
 * @param id_tar_max_A  
 * @param current_slope_percentage  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_polepairsidconfig_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               float elec_angle_add, uint32_t enc_line_p_n, float id_tar_max_A, float current_slope_percentage)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PolePairsIdConfig_LEN];
    _mav_put_float(buf, 0, elec_angle_add);
    _mav_put_uint32_t(buf, 4, enc_line_p_n);
    _mav_put_float(buf, 8, id_tar_max_A);
    _mav_put_float(buf, 12, current_slope_percentage);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_PolePairsIdConfig_LEN);
#else
    mavlink_polepairsidconfig_t packet;
    packet.elec_angle_add = elec_angle_add;
    packet.enc_line_p_n = enc_line_p_n;
    packet.id_tar_max_A = id_tar_max_A;
    packet.current_slope_percentage = current_slope_percentage;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_PolePairsIdConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_PolePairsIdConfig;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_PolePairsIdConfig_MIN_LEN, MAVLINK_MSG_ID_PolePairsIdConfig_LEN, MAVLINK_MSG_ID_PolePairsIdConfig_CRC);
}

/**
 * @brief Pack a polepairsidconfig message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param elec_angle_add  
 * @param enc_line_p_n  
 * @param id_tar_max_A  
 * @param current_slope_percentage  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_polepairsidconfig_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               float elec_angle_add, uint32_t enc_line_p_n, float id_tar_max_A, float current_slope_percentage)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PolePairsIdConfig_LEN];
    _mav_put_float(buf, 0, elec_angle_add);
    _mav_put_uint32_t(buf, 4, enc_line_p_n);
    _mav_put_float(buf, 8, id_tar_max_A);
    _mav_put_float(buf, 12, current_slope_percentage);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_PolePairsIdConfig_LEN);
#else
    mavlink_polepairsidconfig_t packet;
    packet.elec_angle_add = elec_angle_add;
    packet.enc_line_p_n = enc_line_p_n;
    packet.id_tar_max_A = id_tar_max_A;
    packet.current_slope_percentage = current_slope_percentage;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_PolePairsIdConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_PolePairsIdConfig;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_PolePairsIdConfig_MIN_LEN, MAVLINK_MSG_ID_PolePairsIdConfig_LEN, MAVLINK_MSG_ID_PolePairsIdConfig_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_PolePairsIdConfig_MIN_LEN, MAVLINK_MSG_ID_PolePairsIdConfig_LEN);
#endif
}

/**
 * @brief Pack a polepairsidconfig message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param elec_angle_add  
 * @param enc_line_p_n  
 * @param id_tar_max_A  
 * @param current_slope_percentage  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_polepairsidconfig_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   float elec_angle_add,uint32_t enc_line_p_n,float id_tar_max_A,float current_slope_percentage)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PolePairsIdConfig_LEN];
    _mav_put_float(buf, 0, elec_angle_add);
    _mav_put_uint32_t(buf, 4, enc_line_p_n);
    _mav_put_float(buf, 8, id_tar_max_A);
    _mav_put_float(buf, 12, current_slope_percentage);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_PolePairsIdConfig_LEN);
#else
    mavlink_polepairsidconfig_t packet;
    packet.elec_angle_add = elec_angle_add;
    packet.enc_line_p_n = enc_line_p_n;
    packet.id_tar_max_A = id_tar_max_A;
    packet.current_slope_percentage = current_slope_percentage;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_PolePairsIdConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_PolePairsIdConfig;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_PolePairsIdConfig_MIN_LEN, MAVLINK_MSG_ID_PolePairsIdConfig_LEN, MAVLINK_MSG_ID_PolePairsIdConfig_CRC);
}

/**
 * @brief Encode a polepairsidconfig struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param polepairsidconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_polepairsidconfig_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_polepairsidconfig_t* polepairsidconfig)
{
    return mavlink_msg_polepairsidconfig_pack(system_id, component_id, msg, polepairsidconfig->elec_angle_add, polepairsidconfig->enc_line_p_n, polepairsidconfig->id_tar_max_A, polepairsidconfig->current_slope_percentage);
}

/**
 * @brief Encode a polepairsidconfig struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param polepairsidconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_polepairsidconfig_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_polepairsidconfig_t* polepairsidconfig)
{
    return mavlink_msg_polepairsidconfig_pack_chan(system_id, component_id, chan, msg, polepairsidconfig->elec_angle_add, polepairsidconfig->enc_line_p_n, polepairsidconfig->id_tar_max_A, polepairsidconfig->current_slope_percentage);
}

/**
 * @brief Encode a polepairsidconfig struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param polepairsidconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_polepairsidconfig_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_polepairsidconfig_t* polepairsidconfig)
{
    return mavlink_msg_polepairsidconfig_pack_status(system_id, component_id, _status, msg,  polepairsidconfig->elec_angle_add, polepairsidconfig->enc_line_p_n, polepairsidconfig->id_tar_max_A, polepairsidconfig->current_slope_percentage);
}

/**
 * @brief Send a polepairsidconfig message
 * @param chan MAVLink channel to send the message
 *
 * @param elec_angle_add  
 * @param enc_line_p_n  
 * @param id_tar_max_A  
 * @param current_slope_percentage  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_polepairsidconfig_send(mavlink_channel_t chan, float elec_angle_add, uint32_t enc_line_p_n, float id_tar_max_A, float current_slope_percentage)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PolePairsIdConfig_LEN];
    _mav_put_float(buf, 0, elec_angle_add);
    _mav_put_uint32_t(buf, 4, enc_line_p_n);
    _mav_put_float(buf, 8, id_tar_max_A);
    _mav_put_float(buf, 12, current_slope_percentage);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PolePairsIdConfig, buf, MAVLINK_MSG_ID_PolePairsIdConfig_MIN_LEN, MAVLINK_MSG_ID_PolePairsIdConfig_LEN, MAVLINK_MSG_ID_PolePairsIdConfig_CRC);
#else
    mavlink_polepairsidconfig_t packet;
    packet.elec_angle_add = elec_angle_add;
    packet.enc_line_p_n = enc_line_p_n;
    packet.id_tar_max_A = id_tar_max_A;
    packet.current_slope_percentage = current_slope_percentage;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PolePairsIdConfig, (const char *)&packet, MAVLINK_MSG_ID_PolePairsIdConfig_MIN_LEN, MAVLINK_MSG_ID_PolePairsIdConfig_LEN, MAVLINK_MSG_ID_PolePairsIdConfig_CRC);
#endif
}

/**
 * @brief Send a polepairsidconfig message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_polepairsidconfig_send_struct(mavlink_channel_t chan, const mavlink_polepairsidconfig_t* polepairsidconfig)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_polepairsidconfig_send(chan, polepairsidconfig->elec_angle_add, polepairsidconfig->enc_line_p_n, polepairsidconfig->id_tar_max_A, polepairsidconfig->current_slope_percentage);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PolePairsIdConfig, (const char *)polepairsidconfig, MAVLINK_MSG_ID_PolePairsIdConfig_MIN_LEN, MAVLINK_MSG_ID_PolePairsIdConfig_LEN, MAVLINK_MSG_ID_PolePairsIdConfig_CRC);
#endif
}

#if MAVLINK_MSG_ID_PolePairsIdConfig_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_polepairsidconfig_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float elec_angle_add, uint32_t enc_line_p_n, float id_tar_max_A, float current_slope_percentage)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, elec_angle_add);
    _mav_put_uint32_t(buf, 4, enc_line_p_n);
    _mav_put_float(buf, 8, id_tar_max_A);
    _mav_put_float(buf, 12, current_slope_percentage);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PolePairsIdConfig, buf, MAVLINK_MSG_ID_PolePairsIdConfig_MIN_LEN, MAVLINK_MSG_ID_PolePairsIdConfig_LEN, MAVLINK_MSG_ID_PolePairsIdConfig_CRC);
#else
    mavlink_polepairsidconfig_t *packet = (mavlink_polepairsidconfig_t *)msgbuf;
    packet->elec_angle_add = elec_angle_add;
    packet->enc_line_p_n = enc_line_p_n;
    packet->id_tar_max_A = id_tar_max_A;
    packet->current_slope_percentage = current_slope_percentage;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PolePairsIdConfig, (const char *)packet, MAVLINK_MSG_ID_PolePairsIdConfig_MIN_LEN, MAVLINK_MSG_ID_PolePairsIdConfig_LEN, MAVLINK_MSG_ID_PolePairsIdConfig_CRC);
#endif
}
#endif

#endif

// MESSAGE PolePairsIdConfig UNPACKING


/**
 * @brief Get field elec_angle_add from polepairsidconfig message
 *
 * @return  
 */
static inline float mavlink_msg_polepairsidconfig_get_elec_angle_add(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field enc_line_p_n from polepairsidconfig message
 *
 * @return  
 */
static inline uint32_t mavlink_msg_polepairsidconfig_get_enc_line_p_n(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  4);
}

/**
 * @brief Get field id_tar_max_A from polepairsidconfig message
 *
 * @return  
 */
static inline float mavlink_msg_polepairsidconfig_get_id_tar_max_A(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field current_slope_percentage from polepairsidconfig message
 *
 * @return  
 */
static inline float mavlink_msg_polepairsidconfig_get_current_slope_percentage(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Decode a polepairsidconfig message into a struct
 *
 * @param msg The message to decode
 * @param polepairsidconfig C-struct to decode the message contents into
 */
static inline void mavlink_msg_polepairsidconfig_decode(const mavlink_message_t* msg, mavlink_polepairsidconfig_t* polepairsidconfig)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    polepairsidconfig->elec_angle_add = mavlink_msg_polepairsidconfig_get_elec_angle_add(msg);
    polepairsidconfig->enc_line_p_n = mavlink_msg_polepairsidconfig_get_enc_line_p_n(msg);
    polepairsidconfig->id_tar_max_A = mavlink_msg_polepairsidconfig_get_id_tar_max_A(msg);
    polepairsidconfig->current_slope_percentage = mavlink_msg_polepairsidconfig_get_current_slope_percentage(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_PolePairsIdConfig_LEN? msg->len : MAVLINK_MSG_ID_PolePairsIdConfig_LEN;
        memset(polepairsidconfig, 0, MAVLINK_MSG_ID_PolePairsIdConfig_LEN);
    memcpy(polepairsidconfig, _MAV_PAYLOAD(msg), len);
#endif
}
