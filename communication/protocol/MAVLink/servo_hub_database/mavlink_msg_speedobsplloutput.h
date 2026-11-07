#pragma once
// MESSAGE SpeedObsPllOutput PACKING

#define MAVLINK_MSG_ID_SpeedObsPllOutput 30031


typedef struct __mavlink_speedobsplloutput_t {
 float ev_rad_s; /*<  */
} mavlink_speedobsplloutput_t;

#define MAVLINK_MSG_ID_SpeedObsPllOutput_LEN 4
#define MAVLINK_MSG_ID_SpeedObsPllOutput_MIN_LEN 4
#define MAVLINK_MSG_ID_30031_LEN 4
#define MAVLINK_MSG_ID_30031_MIN_LEN 4

#define MAVLINK_MSG_ID_SpeedObsPllOutput_CRC 244
#define MAVLINK_MSG_ID_30031_CRC 244



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_SpeedObsPllOutput { \
    30031, \
    "SpeedObsPllOutput", \
    1, \
    {  { "ev_rad_s", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_speedobsplloutput_t, ev_rad_s) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_SpeedObsPllOutput { \
    "SpeedObsPllOutput", \
    1, \
    {  { "ev_rad_s", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_speedobsplloutput_t, ev_rad_s) }, \
         } \
}
#endif

/**
 * @brief Pack a speedobsplloutput message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param ev_rad_s  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_speedobsplloutput_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               float ev_rad_s)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SpeedObsPllOutput_LEN];
    _mav_put_float(buf, 0, ev_rad_s);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SpeedObsPllOutput_LEN);
#else
    mavlink_speedobsplloutput_t packet;
    packet.ev_rad_s = ev_rad_s;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SpeedObsPllOutput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SpeedObsPllOutput;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_SpeedObsPllOutput_MIN_LEN, MAVLINK_MSG_ID_SpeedObsPllOutput_LEN, MAVLINK_MSG_ID_SpeedObsPllOutput_CRC);
}

/**
 * @brief Pack a speedobsplloutput message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param ev_rad_s  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_speedobsplloutput_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               float ev_rad_s)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SpeedObsPllOutput_LEN];
    _mav_put_float(buf, 0, ev_rad_s);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SpeedObsPllOutput_LEN);
#else
    mavlink_speedobsplloutput_t packet;
    packet.ev_rad_s = ev_rad_s;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SpeedObsPllOutput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SpeedObsPllOutput;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_SpeedObsPllOutput_MIN_LEN, MAVLINK_MSG_ID_SpeedObsPllOutput_LEN, MAVLINK_MSG_ID_SpeedObsPllOutput_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_SpeedObsPllOutput_MIN_LEN, MAVLINK_MSG_ID_SpeedObsPllOutput_LEN);
#endif
}

/**
 * @brief Pack a speedobsplloutput message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param ev_rad_s  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_speedobsplloutput_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   float ev_rad_s)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SpeedObsPllOutput_LEN];
    _mav_put_float(buf, 0, ev_rad_s);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SpeedObsPllOutput_LEN);
#else
    mavlink_speedobsplloutput_t packet;
    packet.ev_rad_s = ev_rad_s;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SpeedObsPllOutput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SpeedObsPllOutput;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_SpeedObsPllOutput_MIN_LEN, MAVLINK_MSG_ID_SpeedObsPllOutput_LEN, MAVLINK_MSG_ID_SpeedObsPllOutput_CRC);
}

/**
 * @brief Encode a speedobsplloutput struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param speedobsplloutput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_speedobsplloutput_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_speedobsplloutput_t* speedobsplloutput)
{
    return mavlink_msg_speedobsplloutput_pack(system_id, component_id, msg, speedobsplloutput->ev_rad_s);
}

/**
 * @brief Encode a speedobsplloutput struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param speedobsplloutput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_speedobsplloutput_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_speedobsplloutput_t* speedobsplloutput)
{
    return mavlink_msg_speedobsplloutput_pack_chan(system_id, component_id, chan, msg, speedobsplloutput->ev_rad_s);
}

/**
 * @brief Encode a speedobsplloutput struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param speedobsplloutput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_speedobsplloutput_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_speedobsplloutput_t* speedobsplloutput)
{
    return mavlink_msg_speedobsplloutput_pack_status(system_id, component_id, _status, msg,  speedobsplloutput->ev_rad_s);
}

/**
 * @brief Send a speedobsplloutput message
 * @param chan MAVLink channel to send the message
 *
 * @param ev_rad_s  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_speedobsplloutput_send(mavlink_channel_t chan, float ev_rad_s)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SpeedObsPllOutput_LEN];
    _mav_put_float(buf, 0, ev_rad_s);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SpeedObsPllOutput, buf, MAVLINK_MSG_ID_SpeedObsPllOutput_MIN_LEN, MAVLINK_MSG_ID_SpeedObsPllOutput_LEN, MAVLINK_MSG_ID_SpeedObsPllOutput_CRC);
#else
    mavlink_speedobsplloutput_t packet;
    packet.ev_rad_s = ev_rad_s;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SpeedObsPllOutput, (const char *)&packet, MAVLINK_MSG_ID_SpeedObsPllOutput_MIN_LEN, MAVLINK_MSG_ID_SpeedObsPllOutput_LEN, MAVLINK_MSG_ID_SpeedObsPllOutput_CRC);
#endif
}

/**
 * @brief Send a speedobsplloutput message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_speedobsplloutput_send_struct(mavlink_channel_t chan, const mavlink_speedobsplloutput_t* speedobsplloutput)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_speedobsplloutput_send(chan, speedobsplloutput->ev_rad_s);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SpeedObsPllOutput, (const char *)speedobsplloutput, MAVLINK_MSG_ID_SpeedObsPllOutput_MIN_LEN, MAVLINK_MSG_ID_SpeedObsPllOutput_LEN, MAVLINK_MSG_ID_SpeedObsPllOutput_CRC);
#endif
}

#if MAVLINK_MSG_ID_SpeedObsPllOutput_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_speedobsplloutput_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float ev_rad_s)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, ev_rad_s);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SpeedObsPllOutput, buf, MAVLINK_MSG_ID_SpeedObsPllOutput_MIN_LEN, MAVLINK_MSG_ID_SpeedObsPllOutput_LEN, MAVLINK_MSG_ID_SpeedObsPllOutput_CRC);
#else
    mavlink_speedobsplloutput_t *packet = (mavlink_speedobsplloutput_t *)msgbuf;
    packet->ev_rad_s = ev_rad_s;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SpeedObsPllOutput, (const char *)packet, MAVLINK_MSG_ID_SpeedObsPllOutput_MIN_LEN, MAVLINK_MSG_ID_SpeedObsPllOutput_LEN, MAVLINK_MSG_ID_SpeedObsPllOutput_CRC);
#endif
}
#endif

#endif

// MESSAGE SpeedObsPllOutput UNPACKING


/**
 * @brief Get field ev_rad_s from speedobsplloutput message
 *
 * @return  
 */
static inline float mavlink_msg_speedobsplloutput_get_ev_rad_s(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Decode a speedobsplloutput message into a struct
 *
 * @param msg The message to decode
 * @param speedobsplloutput C-struct to decode the message contents into
 */
static inline void mavlink_msg_speedobsplloutput_decode(const mavlink_message_t* msg, mavlink_speedobsplloutput_t* speedobsplloutput)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    speedobsplloutput->ev_rad_s = mavlink_msg_speedobsplloutput_get_ev_rad_s(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_SpeedObsPllOutput_LEN? msg->len : MAVLINK_MSG_ID_SpeedObsPllOutput_LEN;
        memset(speedobsplloutput, 0, MAVLINK_MSG_ID_SpeedObsPllOutput_LEN);
    memcpy(speedobsplloutput, _MAV_PAYLOAD(msg), len);
#endif
}
