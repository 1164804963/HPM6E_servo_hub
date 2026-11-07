#pragma once
// MESSAGE PolePairsIdOutput PACKING

#define MAVLINK_MSG_ID_PolePairsIdOutput 30043


typedef struct __mavlink_polepairsidoutput_t {
 uint32_t pn_id; /*<  */
 float elec_angle_tar_rad; /*<  */
 float id_tar_A; /*<  */
 int8_t state_now; /*<  */
} mavlink_polepairsidoutput_t;

#define MAVLINK_MSG_ID_PolePairsIdOutput_LEN 13
#define MAVLINK_MSG_ID_PolePairsIdOutput_MIN_LEN 13
#define MAVLINK_MSG_ID_30043_LEN 13
#define MAVLINK_MSG_ID_30043_MIN_LEN 13

#define MAVLINK_MSG_ID_PolePairsIdOutput_CRC 20
#define MAVLINK_MSG_ID_30043_CRC 20



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_PolePairsIdOutput { \
    30043, \
    "PolePairsIdOutput", \
    4, \
    {  { "pn_id", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_polepairsidoutput_t, pn_id) }, \
         { "state_now", NULL, MAVLINK_TYPE_INT8_T, 0, 12, offsetof(mavlink_polepairsidoutput_t, state_now) }, \
         { "elec_angle_tar_rad", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_polepairsidoutput_t, elec_angle_tar_rad) }, \
         { "id_tar_A", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_polepairsidoutput_t, id_tar_A) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_PolePairsIdOutput { \
    "PolePairsIdOutput", \
    4, \
    {  { "pn_id", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_polepairsidoutput_t, pn_id) }, \
         { "state_now", NULL, MAVLINK_TYPE_INT8_T, 0, 12, offsetof(mavlink_polepairsidoutput_t, state_now) }, \
         { "elec_angle_tar_rad", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_polepairsidoutput_t, elec_angle_tar_rad) }, \
         { "id_tar_A", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_polepairsidoutput_t, id_tar_A) }, \
         } \
}
#endif

/**
 * @brief Pack a polepairsidoutput message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param pn_id  
 * @param state_now  
 * @param elec_angle_tar_rad  
 * @param id_tar_A  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_polepairsidoutput_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint32_t pn_id, int8_t state_now, float elec_angle_tar_rad, float id_tar_A)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PolePairsIdOutput_LEN];
    _mav_put_uint32_t(buf, 0, pn_id);
    _mav_put_float(buf, 4, elec_angle_tar_rad);
    _mav_put_float(buf, 8, id_tar_A);
    _mav_put_int8_t(buf, 12, state_now);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_PolePairsIdOutput_LEN);
#else
    mavlink_polepairsidoutput_t packet;
    packet.pn_id = pn_id;
    packet.elec_angle_tar_rad = elec_angle_tar_rad;
    packet.id_tar_A = id_tar_A;
    packet.state_now = state_now;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_PolePairsIdOutput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_PolePairsIdOutput;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_PolePairsIdOutput_MIN_LEN, MAVLINK_MSG_ID_PolePairsIdOutput_LEN, MAVLINK_MSG_ID_PolePairsIdOutput_CRC);
}

/**
 * @brief Pack a polepairsidoutput message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param pn_id  
 * @param state_now  
 * @param elec_angle_tar_rad  
 * @param id_tar_A  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_polepairsidoutput_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint32_t pn_id, int8_t state_now, float elec_angle_tar_rad, float id_tar_A)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PolePairsIdOutput_LEN];
    _mav_put_uint32_t(buf, 0, pn_id);
    _mav_put_float(buf, 4, elec_angle_tar_rad);
    _mav_put_float(buf, 8, id_tar_A);
    _mav_put_int8_t(buf, 12, state_now);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_PolePairsIdOutput_LEN);
#else
    mavlink_polepairsidoutput_t packet;
    packet.pn_id = pn_id;
    packet.elec_angle_tar_rad = elec_angle_tar_rad;
    packet.id_tar_A = id_tar_A;
    packet.state_now = state_now;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_PolePairsIdOutput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_PolePairsIdOutput;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_PolePairsIdOutput_MIN_LEN, MAVLINK_MSG_ID_PolePairsIdOutput_LEN, MAVLINK_MSG_ID_PolePairsIdOutput_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_PolePairsIdOutput_MIN_LEN, MAVLINK_MSG_ID_PolePairsIdOutput_LEN);
#endif
}

/**
 * @brief Pack a polepairsidoutput message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param pn_id  
 * @param state_now  
 * @param elec_angle_tar_rad  
 * @param id_tar_A  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_polepairsidoutput_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint32_t pn_id,int8_t state_now,float elec_angle_tar_rad,float id_tar_A)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PolePairsIdOutput_LEN];
    _mav_put_uint32_t(buf, 0, pn_id);
    _mav_put_float(buf, 4, elec_angle_tar_rad);
    _mav_put_float(buf, 8, id_tar_A);
    _mav_put_int8_t(buf, 12, state_now);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_PolePairsIdOutput_LEN);
#else
    mavlink_polepairsidoutput_t packet;
    packet.pn_id = pn_id;
    packet.elec_angle_tar_rad = elec_angle_tar_rad;
    packet.id_tar_A = id_tar_A;
    packet.state_now = state_now;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_PolePairsIdOutput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_PolePairsIdOutput;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_PolePairsIdOutput_MIN_LEN, MAVLINK_MSG_ID_PolePairsIdOutput_LEN, MAVLINK_MSG_ID_PolePairsIdOutput_CRC);
}

/**
 * @brief Encode a polepairsidoutput struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param polepairsidoutput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_polepairsidoutput_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_polepairsidoutput_t* polepairsidoutput)
{
    return mavlink_msg_polepairsidoutput_pack(system_id, component_id, msg, polepairsidoutput->pn_id, polepairsidoutput->state_now, polepairsidoutput->elec_angle_tar_rad, polepairsidoutput->id_tar_A);
}

/**
 * @brief Encode a polepairsidoutput struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param polepairsidoutput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_polepairsidoutput_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_polepairsidoutput_t* polepairsidoutput)
{
    return mavlink_msg_polepairsidoutput_pack_chan(system_id, component_id, chan, msg, polepairsidoutput->pn_id, polepairsidoutput->state_now, polepairsidoutput->elec_angle_tar_rad, polepairsidoutput->id_tar_A);
}

/**
 * @brief Encode a polepairsidoutput struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param polepairsidoutput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_polepairsidoutput_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_polepairsidoutput_t* polepairsidoutput)
{
    return mavlink_msg_polepairsidoutput_pack_status(system_id, component_id, _status, msg,  polepairsidoutput->pn_id, polepairsidoutput->state_now, polepairsidoutput->elec_angle_tar_rad, polepairsidoutput->id_tar_A);
}

/**
 * @brief Send a polepairsidoutput message
 * @param chan MAVLink channel to send the message
 *
 * @param pn_id  
 * @param state_now  
 * @param elec_angle_tar_rad  
 * @param id_tar_A  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_polepairsidoutput_send(mavlink_channel_t chan, uint32_t pn_id, int8_t state_now, float elec_angle_tar_rad, float id_tar_A)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PolePairsIdOutput_LEN];
    _mav_put_uint32_t(buf, 0, pn_id);
    _mav_put_float(buf, 4, elec_angle_tar_rad);
    _mav_put_float(buf, 8, id_tar_A);
    _mav_put_int8_t(buf, 12, state_now);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PolePairsIdOutput, buf, MAVLINK_MSG_ID_PolePairsIdOutput_MIN_LEN, MAVLINK_MSG_ID_PolePairsIdOutput_LEN, MAVLINK_MSG_ID_PolePairsIdOutput_CRC);
#else
    mavlink_polepairsidoutput_t packet;
    packet.pn_id = pn_id;
    packet.elec_angle_tar_rad = elec_angle_tar_rad;
    packet.id_tar_A = id_tar_A;
    packet.state_now = state_now;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PolePairsIdOutput, (const char *)&packet, MAVLINK_MSG_ID_PolePairsIdOutput_MIN_LEN, MAVLINK_MSG_ID_PolePairsIdOutput_LEN, MAVLINK_MSG_ID_PolePairsIdOutput_CRC);
#endif
}

/**
 * @brief Send a polepairsidoutput message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_polepairsidoutput_send_struct(mavlink_channel_t chan, const mavlink_polepairsidoutput_t* polepairsidoutput)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_polepairsidoutput_send(chan, polepairsidoutput->pn_id, polepairsidoutput->state_now, polepairsidoutput->elec_angle_tar_rad, polepairsidoutput->id_tar_A);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PolePairsIdOutput, (const char *)polepairsidoutput, MAVLINK_MSG_ID_PolePairsIdOutput_MIN_LEN, MAVLINK_MSG_ID_PolePairsIdOutput_LEN, MAVLINK_MSG_ID_PolePairsIdOutput_CRC);
#endif
}

#if MAVLINK_MSG_ID_PolePairsIdOutput_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_polepairsidoutput_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint32_t pn_id, int8_t state_now, float elec_angle_tar_rad, float id_tar_A)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint32_t(buf, 0, pn_id);
    _mav_put_float(buf, 4, elec_angle_tar_rad);
    _mav_put_float(buf, 8, id_tar_A);
    _mav_put_int8_t(buf, 12, state_now);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PolePairsIdOutput, buf, MAVLINK_MSG_ID_PolePairsIdOutput_MIN_LEN, MAVLINK_MSG_ID_PolePairsIdOutput_LEN, MAVLINK_MSG_ID_PolePairsIdOutput_CRC);
#else
    mavlink_polepairsidoutput_t *packet = (mavlink_polepairsidoutput_t *)msgbuf;
    packet->pn_id = pn_id;
    packet->elec_angle_tar_rad = elec_angle_tar_rad;
    packet->id_tar_A = id_tar_A;
    packet->state_now = state_now;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PolePairsIdOutput, (const char *)packet, MAVLINK_MSG_ID_PolePairsIdOutput_MIN_LEN, MAVLINK_MSG_ID_PolePairsIdOutput_LEN, MAVLINK_MSG_ID_PolePairsIdOutput_CRC);
#endif
}
#endif

#endif

// MESSAGE PolePairsIdOutput UNPACKING


/**
 * @brief Get field pn_id from polepairsidoutput message
 *
 * @return  
 */
static inline uint32_t mavlink_msg_polepairsidoutput_get_pn_id(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Get field state_now from polepairsidoutput message
 *
 * @return  
 */
static inline int8_t mavlink_msg_polepairsidoutput_get_state_now(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int8_t(msg,  12);
}

/**
 * @brief Get field elec_angle_tar_rad from polepairsidoutput message
 *
 * @return  
 */
static inline float mavlink_msg_polepairsidoutput_get_elec_angle_tar_rad(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field id_tar_A from polepairsidoutput message
 *
 * @return  
 */
static inline float mavlink_msg_polepairsidoutput_get_id_tar_A(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Decode a polepairsidoutput message into a struct
 *
 * @param msg The message to decode
 * @param polepairsidoutput C-struct to decode the message contents into
 */
static inline void mavlink_msg_polepairsidoutput_decode(const mavlink_message_t* msg, mavlink_polepairsidoutput_t* polepairsidoutput)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    polepairsidoutput->pn_id = mavlink_msg_polepairsidoutput_get_pn_id(msg);
    polepairsidoutput->elec_angle_tar_rad = mavlink_msg_polepairsidoutput_get_elec_angle_tar_rad(msg);
    polepairsidoutput->id_tar_A = mavlink_msg_polepairsidoutput_get_id_tar_A(msg);
    polepairsidoutput->state_now = mavlink_msg_polepairsidoutput_get_state_now(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_PolePairsIdOutput_LEN? msg->len : MAVLINK_MSG_ID_PolePairsIdOutput_LEN;
        memset(polepairsidoutput, 0, MAVLINK_MSG_ID_PolePairsIdOutput_LEN);
    memcpy(polepairsidoutput, _MAV_PAYLOAD(msg), len);
#endif
}
