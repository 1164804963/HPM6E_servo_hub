#pragma once
// MESSAGE SpeedObsPllInput PACKING

#define MAVLINK_MSG_ID_SpeedObsPllInput 30029


typedef struct __mavlink_speedobspllinput_t {
 int64_t pos_now_p; /*<  */
} mavlink_speedobspllinput_t;

#define MAVLINK_MSG_ID_SpeedObsPllInput_LEN 8
#define MAVLINK_MSG_ID_SpeedObsPllInput_MIN_LEN 8
#define MAVLINK_MSG_ID_30029_LEN 8
#define MAVLINK_MSG_ID_30029_MIN_LEN 8

#define MAVLINK_MSG_ID_SpeedObsPllInput_CRC 30
#define MAVLINK_MSG_ID_30029_CRC 30



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_SpeedObsPllInput { \
    30029, \
    "SpeedObsPllInput", \
    1, \
    {  { "pos_now_p", NULL, MAVLINK_TYPE_INT64_T, 0, 0, offsetof(mavlink_speedobspllinput_t, pos_now_p) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_SpeedObsPllInput { \
    "SpeedObsPllInput", \
    1, \
    {  { "pos_now_p", NULL, MAVLINK_TYPE_INT64_T, 0, 0, offsetof(mavlink_speedobspllinput_t, pos_now_p) }, \
         } \
}
#endif

/**
 * @brief Pack a speedobspllinput message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param pos_now_p  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_speedobspllinput_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               int64_t pos_now_p)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SpeedObsPllInput_LEN];
    _mav_put_int64_t(buf, 0, pos_now_p);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SpeedObsPllInput_LEN);
#else
    mavlink_speedobspllinput_t packet;
    packet.pos_now_p = pos_now_p;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SpeedObsPllInput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SpeedObsPllInput;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_SpeedObsPllInput_MIN_LEN, MAVLINK_MSG_ID_SpeedObsPllInput_LEN, MAVLINK_MSG_ID_SpeedObsPllInput_CRC);
}

/**
 * @brief Pack a speedobspllinput message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param pos_now_p  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_speedobspllinput_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               int64_t pos_now_p)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SpeedObsPllInput_LEN];
    _mav_put_int64_t(buf, 0, pos_now_p);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SpeedObsPllInput_LEN);
#else
    mavlink_speedobspllinput_t packet;
    packet.pos_now_p = pos_now_p;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SpeedObsPllInput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SpeedObsPllInput;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_SpeedObsPllInput_MIN_LEN, MAVLINK_MSG_ID_SpeedObsPllInput_LEN, MAVLINK_MSG_ID_SpeedObsPllInput_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_SpeedObsPllInput_MIN_LEN, MAVLINK_MSG_ID_SpeedObsPllInput_LEN);
#endif
}

/**
 * @brief Pack a speedobspllinput message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param pos_now_p  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_speedobspllinput_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   int64_t pos_now_p)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SpeedObsPllInput_LEN];
    _mav_put_int64_t(buf, 0, pos_now_p);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SpeedObsPllInput_LEN);
#else
    mavlink_speedobspllinput_t packet;
    packet.pos_now_p = pos_now_p;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SpeedObsPllInput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SpeedObsPllInput;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_SpeedObsPllInput_MIN_LEN, MAVLINK_MSG_ID_SpeedObsPllInput_LEN, MAVLINK_MSG_ID_SpeedObsPllInput_CRC);
}

/**
 * @brief Encode a speedobspllinput struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param speedobspllinput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_speedobspllinput_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_speedobspllinput_t* speedobspllinput)
{
    return mavlink_msg_speedobspllinput_pack(system_id, component_id, msg, speedobspllinput->pos_now_p);
}

/**
 * @brief Encode a speedobspllinput struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param speedobspllinput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_speedobspllinput_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_speedobspllinput_t* speedobspllinput)
{
    return mavlink_msg_speedobspllinput_pack_chan(system_id, component_id, chan, msg, speedobspllinput->pos_now_p);
}

/**
 * @brief Encode a speedobspllinput struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param speedobspllinput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_speedobspllinput_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_speedobspllinput_t* speedobspllinput)
{
    return mavlink_msg_speedobspllinput_pack_status(system_id, component_id, _status, msg,  speedobspllinput->pos_now_p);
}

/**
 * @brief Send a speedobspllinput message
 * @param chan MAVLink channel to send the message
 *
 * @param pos_now_p  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_speedobspllinput_send(mavlink_channel_t chan, int64_t pos_now_p)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SpeedObsPllInput_LEN];
    _mav_put_int64_t(buf, 0, pos_now_p);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SpeedObsPllInput, buf, MAVLINK_MSG_ID_SpeedObsPllInput_MIN_LEN, MAVLINK_MSG_ID_SpeedObsPllInput_LEN, MAVLINK_MSG_ID_SpeedObsPllInput_CRC);
#else
    mavlink_speedobspllinput_t packet;
    packet.pos_now_p = pos_now_p;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SpeedObsPllInput, (const char *)&packet, MAVLINK_MSG_ID_SpeedObsPllInput_MIN_LEN, MAVLINK_MSG_ID_SpeedObsPllInput_LEN, MAVLINK_MSG_ID_SpeedObsPllInput_CRC);
#endif
}

/**
 * @brief Send a speedobspllinput message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_speedobspllinput_send_struct(mavlink_channel_t chan, const mavlink_speedobspllinput_t* speedobspllinput)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_speedobspllinput_send(chan, speedobspllinput->pos_now_p);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SpeedObsPllInput, (const char *)speedobspllinput, MAVLINK_MSG_ID_SpeedObsPllInput_MIN_LEN, MAVLINK_MSG_ID_SpeedObsPllInput_LEN, MAVLINK_MSG_ID_SpeedObsPllInput_CRC);
#endif
}

#if MAVLINK_MSG_ID_SpeedObsPllInput_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_speedobspllinput_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  int64_t pos_now_p)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_int64_t(buf, 0, pos_now_p);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SpeedObsPllInput, buf, MAVLINK_MSG_ID_SpeedObsPllInput_MIN_LEN, MAVLINK_MSG_ID_SpeedObsPllInput_LEN, MAVLINK_MSG_ID_SpeedObsPllInput_CRC);
#else
    mavlink_speedobspllinput_t *packet = (mavlink_speedobspllinput_t *)msgbuf;
    packet->pos_now_p = pos_now_p;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SpeedObsPllInput, (const char *)packet, MAVLINK_MSG_ID_SpeedObsPllInput_MIN_LEN, MAVLINK_MSG_ID_SpeedObsPllInput_LEN, MAVLINK_MSG_ID_SpeedObsPllInput_CRC);
#endif
}
#endif

#endif

// MESSAGE SpeedObsPllInput UNPACKING


/**
 * @brief Get field pos_now_p from speedobspllinput message
 *
 * @return  
 */
static inline int64_t mavlink_msg_speedobspllinput_get_pos_now_p(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int64_t(msg,  0);
}

/**
 * @brief Decode a speedobspllinput message into a struct
 *
 * @param msg The message to decode
 * @param speedobspllinput C-struct to decode the message contents into
 */
static inline void mavlink_msg_speedobspllinput_decode(const mavlink_message_t* msg, mavlink_speedobspllinput_t* speedobspllinput)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    speedobspllinput->pos_now_p = mavlink_msg_speedobspllinput_get_pos_now_p(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_SpeedObsPllInput_LEN? msg->len : MAVLINK_MSG_ID_SpeedObsPllInput_LEN;
        memset(speedobspllinput, 0, MAVLINK_MSG_ID_SpeedObsPllInput_LEN);
    memcpy(speedobspllinput, _MAV_PAYLOAD(msg), len);
#endif
}
