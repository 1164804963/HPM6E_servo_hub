#pragma once
// MESSAGE ReferenceSignalOutput PACKING

#define MAVLINK_MSG_ID_ReferenceSignalOutput 30053


typedef struct __mavlink_referencesignaloutput_t {
 int64_t signal_pos; /*<  */
 float signal_out; /*<  */
 float signal_vel; /*<  */
 float signal_acc; /*<  */
} mavlink_referencesignaloutput_t;

#define MAVLINK_MSG_ID_ReferenceSignalOutput_LEN 20
#define MAVLINK_MSG_ID_ReferenceSignalOutput_MIN_LEN 20
#define MAVLINK_MSG_ID_30053_LEN 20
#define MAVLINK_MSG_ID_30053_MIN_LEN 20

#define MAVLINK_MSG_ID_ReferenceSignalOutput_CRC 154
#define MAVLINK_MSG_ID_30053_CRC 154



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_ReferenceSignalOutput { \
    30053, \
    "ReferenceSignalOutput", \
    4, \
    {  { "signal_out", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_referencesignaloutput_t, signal_out) }, \
         { "signal_pos", NULL, MAVLINK_TYPE_INT64_T, 0, 0, offsetof(mavlink_referencesignaloutput_t, signal_pos) }, \
         { "signal_vel", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_referencesignaloutput_t, signal_vel) }, \
         { "signal_acc", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_referencesignaloutput_t, signal_acc) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_ReferenceSignalOutput { \
    "ReferenceSignalOutput", \
    4, \
    {  { "signal_out", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_referencesignaloutput_t, signal_out) }, \
         { "signal_pos", NULL, MAVLINK_TYPE_INT64_T, 0, 0, offsetof(mavlink_referencesignaloutput_t, signal_pos) }, \
         { "signal_vel", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_referencesignaloutput_t, signal_vel) }, \
         { "signal_acc", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_referencesignaloutput_t, signal_acc) }, \
         } \
}
#endif

/**
 * @brief Pack a referencesignaloutput message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param signal_out  
 * @param signal_pos  
 * @param signal_vel  
 * @param signal_acc  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_referencesignaloutput_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               float signal_out, int64_t signal_pos, float signal_vel, float signal_acc)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ReferenceSignalOutput_LEN];
    _mav_put_int64_t(buf, 0, signal_pos);
    _mav_put_float(buf, 8, signal_out);
    _mav_put_float(buf, 12, signal_vel);
    _mav_put_float(buf, 16, signal_acc);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ReferenceSignalOutput_LEN);
#else
    mavlink_referencesignaloutput_t packet;
    packet.signal_pos = signal_pos;
    packet.signal_out = signal_out;
    packet.signal_vel = signal_vel;
    packet.signal_acc = signal_acc;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ReferenceSignalOutput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ReferenceSignalOutput;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_ReferenceSignalOutput_MIN_LEN, MAVLINK_MSG_ID_ReferenceSignalOutput_LEN, MAVLINK_MSG_ID_ReferenceSignalOutput_CRC);
}

/**
 * @brief Pack a referencesignaloutput message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param signal_out  
 * @param signal_pos  
 * @param signal_vel  
 * @param signal_acc  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_referencesignaloutput_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               float signal_out, int64_t signal_pos, float signal_vel, float signal_acc)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ReferenceSignalOutput_LEN];
    _mav_put_int64_t(buf, 0, signal_pos);
    _mav_put_float(buf, 8, signal_out);
    _mav_put_float(buf, 12, signal_vel);
    _mav_put_float(buf, 16, signal_acc);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ReferenceSignalOutput_LEN);
#else
    mavlink_referencesignaloutput_t packet;
    packet.signal_pos = signal_pos;
    packet.signal_out = signal_out;
    packet.signal_vel = signal_vel;
    packet.signal_acc = signal_acc;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ReferenceSignalOutput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ReferenceSignalOutput;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_ReferenceSignalOutput_MIN_LEN, MAVLINK_MSG_ID_ReferenceSignalOutput_LEN, MAVLINK_MSG_ID_ReferenceSignalOutput_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_ReferenceSignalOutput_MIN_LEN, MAVLINK_MSG_ID_ReferenceSignalOutput_LEN);
#endif
}

/**
 * @brief Pack a referencesignaloutput message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param signal_out  
 * @param signal_pos  
 * @param signal_vel  
 * @param signal_acc  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_referencesignaloutput_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   float signal_out,int64_t signal_pos,float signal_vel,float signal_acc)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ReferenceSignalOutput_LEN];
    _mav_put_int64_t(buf, 0, signal_pos);
    _mav_put_float(buf, 8, signal_out);
    _mav_put_float(buf, 12, signal_vel);
    _mav_put_float(buf, 16, signal_acc);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ReferenceSignalOutput_LEN);
#else
    mavlink_referencesignaloutput_t packet;
    packet.signal_pos = signal_pos;
    packet.signal_out = signal_out;
    packet.signal_vel = signal_vel;
    packet.signal_acc = signal_acc;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ReferenceSignalOutput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ReferenceSignalOutput;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_ReferenceSignalOutput_MIN_LEN, MAVLINK_MSG_ID_ReferenceSignalOutput_LEN, MAVLINK_MSG_ID_ReferenceSignalOutput_CRC);
}

/**
 * @brief Encode a referencesignaloutput struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param referencesignaloutput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_referencesignaloutput_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_referencesignaloutput_t* referencesignaloutput)
{
    return mavlink_msg_referencesignaloutput_pack(system_id, component_id, msg, referencesignaloutput->signal_out, referencesignaloutput->signal_pos, referencesignaloutput->signal_vel, referencesignaloutput->signal_acc);
}

/**
 * @brief Encode a referencesignaloutput struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param referencesignaloutput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_referencesignaloutput_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_referencesignaloutput_t* referencesignaloutput)
{
    return mavlink_msg_referencesignaloutput_pack_chan(system_id, component_id, chan, msg, referencesignaloutput->signal_out, referencesignaloutput->signal_pos, referencesignaloutput->signal_vel, referencesignaloutput->signal_acc);
}

/**
 * @brief Encode a referencesignaloutput struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param referencesignaloutput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_referencesignaloutput_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_referencesignaloutput_t* referencesignaloutput)
{
    return mavlink_msg_referencesignaloutput_pack_status(system_id, component_id, _status, msg,  referencesignaloutput->signal_out, referencesignaloutput->signal_pos, referencesignaloutput->signal_vel, referencesignaloutput->signal_acc);
}

/**
 * @brief Send a referencesignaloutput message
 * @param chan MAVLink channel to send the message
 *
 * @param signal_out  
 * @param signal_pos  
 * @param signal_vel  
 * @param signal_acc  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_referencesignaloutput_send(mavlink_channel_t chan, float signal_out, int64_t signal_pos, float signal_vel, float signal_acc)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ReferenceSignalOutput_LEN];
    _mav_put_int64_t(buf, 0, signal_pos);
    _mav_put_float(buf, 8, signal_out);
    _mav_put_float(buf, 12, signal_vel);
    _mav_put_float(buf, 16, signal_acc);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ReferenceSignalOutput, buf, MAVLINK_MSG_ID_ReferenceSignalOutput_MIN_LEN, MAVLINK_MSG_ID_ReferenceSignalOutput_LEN, MAVLINK_MSG_ID_ReferenceSignalOutput_CRC);
#else
    mavlink_referencesignaloutput_t packet;
    packet.signal_pos = signal_pos;
    packet.signal_out = signal_out;
    packet.signal_vel = signal_vel;
    packet.signal_acc = signal_acc;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ReferenceSignalOutput, (const char *)&packet, MAVLINK_MSG_ID_ReferenceSignalOutput_MIN_LEN, MAVLINK_MSG_ID_ReferenceSignalOutput_LEN, MAVLINK_MSG_ID_ReferenceSignalOutput_CRC);
#endif
}

/**
 * @brief Send a referencesignaloutput message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_referencesignaloutput_send_struct(mavlink_channel_t chan, const mavlink_referencesignaloutput_t* referencesignaloutput)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_referencesignaloutput_send(chan, referencesignaloutput->signal_out, referencesignaloutput->signal_pos, referencesignaloutput->signal_vel, referencesignaloutput->signal_acc);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ReferenceSignalOutput, (const char *)referencesignaloutput, MAVLINK_MSG_ID_ReferenceSignalOutput_MIN_LEN, MAVLINK_MSG_ID_ReferenceSignalOutput_LEN, MAVLINK_MSG_ID_ReferenceSignalOutput_CRC);
#endif
}

#if MAVLINK_MSG_ID_ReferenceSignalOutput_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_referencesignaloutput_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float signal_out, int64_t signal_pos, float signal_vel, float signal_acc)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_int64_t(buf, 0, signal_pos);
    _mav_put_float(buf, 8, signal_out);
    _mav_put_float(buf, 12, signal_vel);
    _mav_put_float(buf, 16, signal_acc);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ReferenceSignalOutput, buf, MAVLINK_MSG_ID_ReferenceSignalOutput_MIN_LEN, MAVLINK_MSG_ID_ReferenceSignalOutput_LEN, MAVLINK_MSG_ID_ReferenceSignalOutput_CRC);
#else
    mavlink_referencesignaloutput_t *packet = (mavlink_referencesignaloutput_t *)msgbuf;
    packet->signal_pos = signal_pos;
    packet->signal_out = signal_out;
    packet->signal_vel = signal_vel;
    packet->signal_acc = signal_acc;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ReferenceSignalOutput, (const char *)packet, MAVLINK_MSG_ID_ReferenceSignalOutput_MIN_LEN, MAVLINK_MSG_ID_ReferenceSignalOutput_LEN, MAVLINK_MSG_ID_ReferenceSignalOutput_CRC);
#endif
}
#endif

#endif

// MESSAGE ReferenceSignalOutput UNPACKING


/**
 * @brief Get field signal_out from referencesignaloutput message
 *
 * @return  
 */
static inline float mavlink_msg_referencesignaloutput_get_signal_out(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field signal_pos from referencesignaloutput message
 *
 * @return  
 */
static inline int64_t mavlink_msg_referencesignaloutput_get_signal_pos(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int64_t(msg,  0);
}

/**
 * @brief Get field signal_vel from referencesignaloutput message
 *
 * @return  
 */
static inline float mavlink_msg_referencesignaloutput_get_signal_vel(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Get field signal_acc from referencesignaloutput message
 *
 * @return  
 */
static inline float mavlink_msg_referencesignaloutput_get_signal_acc(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  16);
}

/**
 * @brief Decode a referencesignaloutput message into a struct
 *
 * @param msg The message to decode
 * @param referencesignaloutput C-struct to decode the message contents into
 */
static inline void mavlink_msg_referencesignaloutput_decode(const mavlink_message_t* msg, mavlink_referencesignaloutput_t* referencesignaloutput)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    referencesignaloutput->signal_pos = mavlink_msg_referencesignaloutput_get_signal_pos(msg);
    referencesignaloutput->signal_out = mavlink_msg_referencesignaloutput_get_signal_out(msg);
    referencesignaloutput->signal_vel = mavlink_msg_referencesignaloutput_get_signal_vel(msg);
    referencesignaloutput->signal_acc = mavlink_msg_referencesignaloutput_get_signal_acc(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_ReferenceSignalOutput_LEN? msg->len : MAVLINK_MSG_ID_ReferenceSignalOutput_LEN;
        memset(referencesignaloutput, 0, MAVLINK_MSG_ID_ReferenceSignalOutput_LEN);
    memcpy(referencesignaloutput, _MAV_PAYLOAD(msg), len);
#endif
}
