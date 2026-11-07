#pragma once
// MESSAGE LoadPosSensorConfig PACKING

#define MAVLINK_MSG_ID_LoadPosSensorConfig 30071


typedef struct __mavlink_loadpossensorconfig_t {
 int64_t init_pos_p; /*<  */
 uint32_t enc_line_p_n; /*<  */
 int8_t dir; /*<  */
} mavlink_loadpossensorconfig_t;

#define MAVLINK_MSG_ID_LoadPosSensorConfig_LEN 13
#define MAVLINK_MSG_ID_LoadPosSensorConfig_MIN_LEN 13
#define MAVLINK_MSG_ID_30071_LEN 13
#define MAVLINK_MSG_ID_30071_MIN_LEN 13

#define MAVLINK_MSG_ID_LoadPosSensorConfig_CRC 27
#define MAVLINK_MSG_ID_30071_CRC 27



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_LoadPosSensorConfig { \
    30071, \
    "LoadPosSensorConfig", \
    3, \
    {  { "enc_line_p_n", NULL, MAVLINK_TYPE_UINT32_T, 0, 8, offsetof(mavlink_loadpossensorconfig_t, enc_line_p_n) }, \
         { "init_pos_p", NULL, MAVLINK_TYPE_INT64_T, 0, 0, offsetof(mavlink_loadpossensorconfig_t, init_pos_p) }, \
         { "dir", NULL, MAVLINK_TYPE_INT8_T, 0, 12, offsetof(mavlink_loadpossensorconfig_t, dir) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_LoadPosSensorConfig { \
    "LoadPosSensorConfig", \
    3, \
    {  { "enc_line_p_n", NULL, MAVLINK_TYPE_UINT32_T, 0, 8, offsetof(mavlink_loadpossensorconfig_t, enc_line_p_n) }, \
         { "init_pos_p", NULL, MAVLINK_TYPE_INT64_T, 0, 0, offsetof(mavlink_loadpossensorconfig_t, init_pos_p) }, \
         { "dir", NULL, MAVLINK_TYPE_INT8_T, 0, 12, offsetof(mavlink_loadpossensorconfig_t, dir) }, \
         } \
}
#endif

/**
 * @brief Pack a loadpossensorconfig message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param enc_line_p_n  
 * @param init_pos_p  
 * @param dir  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_loadpossensorconfig_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint32_t enc_line_p_n, int64_t init_pos_p, int8_t dir)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_LoadPosSensorConfig_LEN];
    _mav_put_int64_t(buf, 0, init_pos_p);
    _mav_put_uint32_t(buf, 8, enc_line_p_n);
    _mav_put_int8_t(buf, 12, dir);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_LoadPosSensorConfig_LEN);
#else
    mavlink_loadpossensorconfig_t packet;
    packet.init_pos_p = init_pos_p;
    packet.enc_line_p_n = enc_line_p_n;
    packet.dir = dir;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_LoadPosSensorConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_LoadPosSensorConfig;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_LoadPosSensorConfig_MIN_LEN, MAVLINK_MSG_ID_LoadPosSensorConfig_LEN, MAVLINK_MSG_ID_LoadPosSensorConfig_CRC);
}

/**
 * @brief Pack a loadpossensorconfig message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param enc_line_p_n  
 * @param init_pos_p  
 * @param dir  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_loadpossensorconfig_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint32_t enc_line_p_n, int64_t init_pos_p, int8_t dir)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_LoadPosSensorConfig_LEN];
    _mav_put_int64_t(buf, 0, init_pos_p);
    _mav_put_uint32_t(buf, 8, enc_line_p_n);
    _mav_put_int8_t(buf, 12, dir);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_LoadPosSensorConfig_LEN);
#else
    mavlink_loadpossensorconfig_t packet;
    packet.init_pos_p = init_pos_p;
    packet.enc_line_p_n = enc_line_p_n;
    packet.dir = dir;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_LoadPosSensorConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_LoadPosSensorConfig;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_LoadPosSensorConfig_MIN_LEN, MAVLINK_MSG_ID_LoadPosSensorConfig_LEN, MAVLINK_MSG_ID_LoadPosSensorConfig_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_LoadPosSensorConfig_MIN_LEN, MAVLINK_MSG_ID_LoadPosSensorConfig_LEN);
#endif
}

/**
 * @brief Pack a loadpossensorconfig message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param enc_line_p_n  
 * @param init_pos_p  
 * @param dir  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_loadpossensorconfig_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint32_t enc_line_p_n,int64_t init_pos_p,int8_t dir)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_LoadPosSensorConfig_LEN];
    _mav_put_int64_t(buf, 0, init_pos_p);
    _mav_put_uint32_t(buf, 8, enc_line_p_n);
    _mav_put_int8_t(buf, 12, dir);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_LoadPosSensorConfig_LEN);
#else
    mavlink_loadpossensorconfig_t packet;
    packet.init_pos_p = init_pos_p;
    packet.enc_line_p_n = enc_line_p_n;
    packet.dir = dir;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_LoadPosSensorConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_LoadPosSensorConfig;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_LoadPosSensorConfig_MIN_LEN, MAVLINK_MSG_ID_LoadPosSensorConfig_LEN, MAVLINK_MSG_ID_LoadPosSensorConfig_CRC);
}

/**
 * @brief Encode a loadpossensorconfig struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param loadpossensorconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_loadpossensorconfig_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_loadpossensorconfig_t* loadpossensorconfig)
{
    return mavlink_msg_loadpossensorconfig_pack(system_id, component_id, msg, loadpossensorconfig->enc_line_p_n, loadpossensorconfig->init_pos_p, loadpossensorconfig->dir);
}

/**
 * @brief Encode a loadpossensorconfig struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param loadpossensorconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_loadpossensorconfig_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_loadpossensorconfig_t* loadpossensorconfig)
{
    return mavlink_msg_loadpossensorconfig_pack_chan(system_id, component_id, chan, msg, loadpossensorconfig->enc_line_p_n, loadpossensorconfig->init_pos_p, loadpossensorconfig->dir);
}

/**
 * @brief Encode a loadpossensorconfig struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param loadpossensorconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_loadpossensorconfig_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_loadpossensorconfig_t* loadpossensorconfig)
{
    return mavlink_msg_loadpossensorconfig_pack_status(system_id, component_id, _status, msg,  loadpossensorconfig->enc_line_p_n, loadpossensorconfig->init_pos_p, loadpossensorconfig->dir);
}

/**
 * @brief Send a loadpossensorconfig message
 * @param chan MAVLink channel to send the message
 *
 * @param enc_line_p_n  
 * @param init_pos_p  
 * @param dir  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_loadpossensorconfig_send(mavlink_channel_t chan, uint32_t enc_line_p_n, int64_t init_pos_p, int8_t dir)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_LoadPosSensorConfig_LEN];
    _mav_put_int64_t(buf, 0, init_pos_p);
    _mav_put_uint32_t(buf, 8, enc_line_p_n);
    _mav_put_int8_t(buf, 12, dir);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LoadPosSensorConfig, buf, MAVLINK_MSG_ID_LoadPosSensorConfig_MIN_LEN, MAVLINK_MSG_ID_LoadPosSensorConfig_LEN, MAVLINK_MSG_ID_LoadPosSensorConfig_CRC);
#else
    mavlink_loadpossensorconfig_t packet;
    packet.init_pos_p = init_pos_p;
    packet.enc_line_p_n = enc_line_p_n;
    packet.dir = dir;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LoadPosSensorConfig, (const char *)&packet, MAVLINK_MSG_ID_LoadPosSensorConfig_MIN_LEN, MAVLINK_MSG_ID_LoadPosSensorConfig_LEN, MAVLINK_MSG_ID_LoadPosSensorConfig_CRC);
#endif
}

/**
 * @brief Send a loadpossensorconfig message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_loadpossensorconfig_send_struct(mavlink_channel_t chan, const mavlink_loadpossensorconfig_t* loadpossensorconfig)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_loadpossensorconfig_send(chan, loadpossensorconfig->enc_line_p_n, loadpossensorconfig->init_pos_p, loadpossensorconfig->dir);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LoadPosSensorConfig, (const char *)loadpossensorconfig, MAVLINK_MSG_ID_LoadPosSensorConfig_MIN_LEN, MAVLINK_MSG_ID_LoadPosSensorConfig_LEN, MAVLINK_MSG_ID_LoadPosSensorConfig_CRC);
#endif
}

#if MAVLINK_MSG_ID_LoadPosSensorConfig_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_loadpossensorconfig_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint32_t enc_line_p_n, int64_t init_pos_p, int8_t dir)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_int64_t(buf, 0, init_pos_p);
    _mav_put_uint32_t(buf, 8, enc_line_p_n);
    _mav_put_int8_t(buf, 12, dir);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LoadPosSensorConfig, buf, MAVLINK_MSG_ID_LoadPosSensorConfig_MIN_LEN, MAVLINK_MSG_ID_LoadPosSensorConfig_LEN, MAVLINK_MSG_ID_LoadPosSensorConfig_CRC);
#else
    mavlink_loadpossensorconfig_t *packet = (mavlink_loadpossensorconfig_t *)msgbuf;
    packet->init_pos_p = init_pos_p;
    packet->enc_line_p_n = enc_line_p_n;
    packet->dir = dir;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LoadPosSensorConfig, (const char *)packet, MAVLINK_MSG_ID_LoadPosSensorConfig_MIN_LEN, MAVLINK_MSG_ID_LoadPosSensorConfig_LEN, MAVLINK_MSG_ID_LoadPosSensorConfig_CRC);
#endif
}
#endif

#endif

// MESSAGE LoadPosSensorConfig UNPACKING


/**
 * @brief Get field enc_line_p_n from loadpossensorconfig message
 *
 * @return  
 */
static inline uint32_t mavlink_msg_loadpossensorconfig_get_enc_line_p_n(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  8);
}

/**
 * @brief Get field init_pos_p from loadpossensorconfig message
 *
 * @return  
 */
static inline int64_t mavlink_msg_loadpossensorconfig_get_init_pos_p(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int64_t(msg,  0);
}

/**
 * @brief Get field dir from loadpossensorconfig message
 *
 * @return  
 */
static inline int8_t mavlink_msg_loadpossensorconfig_get_dir(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int8_t(msg,  12);
}

/**
 * @brief Decode a loadpossensorconfig message into a struct
 *
 * @param msg The message to decode
 * @param loadpossensorconfig C-struct to decode the message contents into
 */
static inline void mavlink_msg_loadpossensorconfig_decode(const mavlink_message_t* msg, mavlink_loadpossensorconfig_t* loadpossensorconfig)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    loadpossensorconfig->init_pos_p = mavlink_msg_loadpossensorconfig_get_init_pos_p(msg);
    loadpossensorconfig->enc_line_p_n = mavlink_msg_loadpossensorconfig_get_enc_line_p_n(msg);
    loadpossensorconfig->dir = mavlink_msg_loadpossensorconfig_get_dir(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_LoadPosSensorConfig_LEN? msg->len : MAVLINK_MSG_ID_LoadPosSensorConfig_LEN;
        memset(loadpossensorconfig, 0, MAVLINK_MSG_ID_LoadPosSensorConfig_LEN);
    memcpy(loadpossensorconfig, _MAV_PAYLOAD(msg), len);
#endif
}
