#pragma once
// MESSAGE DirectionIdOutput PACKING

#define MAVLINK_MSG_ID_DirectionIdOutput 30037


typedef struct __mavlink_directionidoutput_t {
 float elec_angle_tar_rad; /*<  */
 float id_tar_A; /*<  */
 int8_t direction; /*<  */
 int8_t state_now; /*<  */
} mavlink_directionidoutput_t;

#define MAVLINK_MSG_ID_DirectionIdOutput_LEN 10
#define MAVLINK_MSG_ID_DirectionIdOutput_MIN_LEN 10
#define MAVLINK_MSG_ID_30037_LEN 10
#define MAVLINK_MSG_ID_30037_MIN_LEN 10

#define MAVLINK_MSG_ID_DirectionIdOutput_CRC 103
#define MAVLINK_MSG_ID_30037_CRC 103



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_DirectionIdOutput { \
    30037, \
    "DirectionIdOutput", \
    4, \
    {  { "elec_angle_tar_rad", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_directionidoutput_t, elec_angle_tar_rad) }, \
         { "direction", NULL, MAVLINK_TYPE_INT8_T, 0, 8, offsetof(mavlink_directionidoutput_t, direction) }, \
         { "state_now", NULL, MAVLINK_TYPE_INT8_T, 0, 9, offsetof(mavlink_directionidoutput_t, state_now) }, \
         { "id_tar_A", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_directionidoutput_t, id_tar_A) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_DirectionIdOutput { \
    "DirectionIdOutput", \
    4, \
    {  { "elec_angle_tar_rad", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_directionidoutput_t, elec_angle_tar_rad) }, \
         { "direction", NULL, MAVLINK_TYPE_INT8_T, 0, 8, offsetof(mavlink_directionidoutput_t, direction) }, \
         { "state_now", NULL, MAVLINK_TYPE_INT8_T, 0, 9, offsetof(mavlink_directionidoutput_t, state_now) }, \
         { "id_tar_A", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_directionidoutput_t, id_tar_A) }, \
         } \
}
#endif

/**
 * @brief Pack a directionidoutput message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param elec_angle_tar_rad  
 * @param direction  
 * @param state_now  
 * @param id_tar_A  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_directionidoutput_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               float elec_angle_tar_rad, int8_t direction, int8_t state_now, float id_tar_A)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_DirectionIdOutput_LEN];
    _mav_put_float(buf, 0, elec_angle_tar_rad);
    _mav_put_float(buf, 4, id_tar_A);
    _mav_put_int8_t(buf, 8, direction);
    _mav_put_int8_t(buf, 9, state_now);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_DirectionIdOutput_LEN);
#else
    mavlink_directionidoutput_t packet;
    packet.elec_angle_tar_rad = elec_angle_tar_rad;
    packet.id_tar_A = id_tar_A;
    packet.direction = direction;
    packet.state_now = state_now;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_DirectionIdOutput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_DirectionIdOutput;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_DirectionIdOutput_MIN_LEN, MAVLINK_MSG_ID_DirectionIdOutput_LEN, MAVLINK_MSG_ID_DirectionIdOutput_CRC);
}

/**
 * @brief Pack a directionidoutput message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param elec_angle_tar_rad  
 * @param direction  
 * @param state_now  
 * @param id_tar_A  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_directionidoutput_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               float elec_angle_tar_rad, int8_t direction, int8_t state_now, float id_tar_A)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_DirectionIdOutput_LEN];
    _mav_put_float(buf, 0, elec_angle_tar_rad);
    _mav_put_float(buf, 4, id_tar_A);
    _mav_put_int8_t(buf, 8, direction);
    _mav_put_int8_t(buf, 9, state_now);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_DirectionIdOutput_LEN);
#else
    mavlink_directionidoutput_t packet;
    packet.elec_angle_tar_rad = elec_angle_tar_rad;
    packet.id_tar_A = id_tar_A;
    packet.direction = direction;
    packet.state_now = state_now;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_DirectionIdOutput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_DirectionIdOutput;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_DirectionIdOutput_MIN_LEN, MAVLINK_MSG_ID_DirectionIdOutput_LEN, MAVLINK_MSG_ID_DirectionIdOutput_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_DirectionIdOutput_MIN_LEN, MAVLINK_MSG_ID_DirectionIdOutput_LEN);
#endif
}

/**
 * @brief Pack a directionidoutput message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param elec_angle_tar_rad  
 * @param direction  
 * @param state_now  
 * @param id_tar_A  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_directionidoutput_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   float elec_angle_tar_rad,int8_t direction,int8_t state_now,float id_tar_A)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_DirectionIdOutput_LEN];
    _mav_put_float(buf, 0, elec_angle_tar_rad);
    _mav_put_float(buf, 4, id_tar_A);
    _mav_put_int8_t(buf, 8, direction);
    _mav_put_int8_t(buf, 9, state_now);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_DirectionIdOutput_LEN);
#else
    mavlink_directionidoutput_t packet;
    packet.elec_angle_tar_rad = elec_angle_tar_rad;
    packet.id_tar_A = id_tar_A;
    packet.direction = direction;
    packet.state_now = state_now;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_DirectionIdOutput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_DirectionIdOutput;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_DirectionIdOutput_MIN_LEN, MAVLINK_MSG_ID_DirectionIdOutput_LEN, MAVLINK_MSG_ID_DirectionIdOutput_CRC);
}

/**
 * @brief Encode a directionidoutput struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param directionidoutput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_directionidoutput_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_directionidoutput_t* directionidoutput)
{
    return mavlink_msg_directionidoutput_pack(system_id, component_id, msg, directionidoutput->elec_angle_tar_rad, directionidoutput->direction, directionidoutput->state_now, directionidoutput->id_tar_A);
}

/**
 * @brief Encode a directionidoutput struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param directionidoutput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_directionidoutput_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_directionidoutput_t* directionidoutput)
{
    return mavlink_msg_directionidoutput_pack_chan(system_id, component_id, chan, msg, directionidoutput->elec_angle_tar_rad, directionidoutput->direction, directionidoutput->state_now, directionidoutput->id_tar_A);
}

/**
 * @brief Encode a directionidoutput struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param directionidoutput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_directionidoutput_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_directionidoutput_t* directionidoutput)
{
    return mavlink_msg_directionidoutput_pack_status(system_id, component_id, _status, msg,  directionidoutput->elec_angle_tar_rad, directionidoutput->direction, directionidoutput->state_now, directionidoutput->id_tar_A);
}

/**
 * @brief Send a directionidoutput message
 * @param chan MAVLink channel to send the message
 *
 * @param elec_angle_tar_rad  
 * @param direction  
 * @param state_now  
 * @param id_tar_A  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_directionidoutput_send(mavlink_channel_t chan, float elec_angle_tar_rad, int8_t direction, int8_t state_now, float id_tar_A)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_DirectionIdOutput_LEN];
    _mav_put_float(buf, 0, elec_angle_tar_rad);
    _mav_put_float(buf, 4, id_tar_A);
    _mav_put_int8_t(buf, 8, direction);
    _mav_put_int8_t(buf, 9, state_now);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_DirectionIdOutput, buf, MAVLINK_MSG_ID_DirectionIdOutput_MIN_LEN, MAVLINK_MSG_ID_DirectionIdOutput_LEN, MAVLINK_MSG_ID_DirectionIdOutput_CRC);
#else
    mavlink_directionidoutput_t packet;
    packet.elec_angle_tar_rad = elec_angle_tar_rad;
    packet.id_tar_A = id_tar_A;
    packet.direction = direction;
    packet.state_now = state_now;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_DirectionIdOutput, (const char *)&packet, MAVLINK_MSG_ID_DirectionIdOutput_MIN_LEN, MAVLINK_MSG_ID_DirectionIdOutput_LEN, MAVLINK_MSG_ID_DirectionIdOutput_CRC);
#endif
}

/**
 * @brief Send a directionidoutput message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_directionidoutput_send_struct(mavlink_channel_t chan, const mavlink_directionidoutput_t* directionidoutput)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_directionidoutput_send(chan, directionidoutput->elec_angle_tar_rad, directionidoutput->direction, directionidoutput->state_now, directionidoutput->id_tar_A);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_DirectionIdOutput, (const char *)directionidoutput, MAVLINK_MSG_ID_DirectionIdOutput_MIN_LEN, MAVLINK_MSG_ID_DirectionIdOutput_LEN, MAVLINK_MSG_ID_DirectionIdOutput_CRC);
#endif
}

#if MAVLINK_MSG_ID_DirectionIdOutput_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_directionidoutput_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float elec_angle_tar_rad, int8_t direction, int8_t state_now, float id_tar_A)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, elec_angle_tar_rad);
    _mav_put_float(buf, 4, id_tar_A);
    _mav_put_int8_t(buf, 8, direction);
    _mav_put_int8_t(buf, 9, state_now);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_DirectionIdOutput, buf, MAVLINK_MSG_ID_DirectionIdOutput_MIN_LEN, MAVLINK_MSG_ID_DirectionIdOutput_LEN, MAVLINK_MSG_ID_DirectionIdOutput_CRC);
#else
    mavlink_directionidoutput_t *packet = (mavlink_directionidoutput_t *)msgbuf;
    packet->elec_angle_tar_rad = elec_angle_tar_rad;
    packet->id_tar_A = id_tar_A;
    packet->direction = direction;
    packet->state_now = state_now;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_DirectionIdOutput, (const char *)packet, MAVLINK_MSG_ID_DirectionIdOutput_MIN_LEN, MAVLINK_MSG_ID_DirectionIdOutput_LEN, MAVLINK_MSG_ID_DirectionIdOutput_CRC);
#endif
}
#endif

#endif

// MESSAGE DirectionIdOutput UNPACKING


/**
 * @brief Get field elec_angle_tar_rad from directionidoutput message
 *
 * @return  
 */
static inline float mavlink_msg_directionidoutput_get_elec_angle_tar_rad(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field direction from directionidoutput message
 *
 * @return  
 */
static inline int8_t mavlink_msg_directionidoutput_get_direction(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int8_t(msg,  8);
}

/**
 * @brief Get field state_now from directionidoutput message
 *
 * @return  
 */
static inline int8_t mavlink_msg_directionidoutput_get_state_now(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int8_t(msg,  9);
}

/**
 * @brief Get field id_tar_A from directionidoutput message
 *
 * @return  
 */
static inline float mavlink_msg_directionidoutput_get_id_tar_A(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Decode a directionidoutput message into a struct
 *
 * @param msg The message to decode
 * @param directionidoutput C-struct to decode the message contents into
 */
static inline void mavlink_msg_directionidoutput_decode(const mavlink_message_t* msg, mavlink_directionidoutput_t* directionidoutput)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    directionidoutput->elec_angle_tar_rad = mavlink_msg_directionidoutput_get_elec_angle_tar_rad(msg);
    directionidoutput->id_tar_A = mavlink_msg_directionidoutput_get_id_tar_A(msg);
    directionidoutput->direction = mavlink_msg_directionidoutput_get_direction(msg);
    directionidoutput->state_now = mavlink_msg_directionidoutput_get_state_now(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_DirectionIdOutput_LEN? msg->len : MAVLINK_MSG_ID_DirectionIdOutput_LEN;
        memset(directionidoutput, 0, MAVLINK_MSG_ID_DirectionIdOutput_LEN);
    memcpy(directionidoutput, _MAV_PAYLOAD(msg), len);
#endif
}
