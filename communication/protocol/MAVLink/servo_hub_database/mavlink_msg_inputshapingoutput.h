#pragma once
// MESSAGE InputShapingOutput PACKING

#define MAVLINK_MSG_ID_InputShapingOutput 30013


typedef struct __mavlink_inputshapingoutput_t {
 int64_t pos_cmd_shaping_p; /*<  */
} mavlink_inputshapingoutput_t;

#define MAVLINK_MSG_ID_InputShapingOutput_LEN 8
#define MAVLINK_MSG_ID_InputShapingOutput_MIN_LEN 8
#define MAVLINK_MSG_ID_30013_LEN 8
#define MAVLINK_MSG_ID_30013_MIN_LEN 8

#define MAVLINK_MSG_ID_InputShapingOutput_CRC 107
#define MAVLINK_MSG_ID_30013_CRC 107



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_InputShapingOutput { \
    30013, \
    "InputShapingOutput", \
    1, \
    {  { "pos_cmd_shaping_p", NULL, MAVLINK_TYPE_INT64_T, 0, 0, offsetof(mavlink_inputshapingoutput_t, pos_cmd_shaping_p) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_InputShapingOutput { \
    "InputShapingOutput", \
    1, \
    {  { "pos_cmd_shaping_p", NULL, MAVLINK_TYPE_INT64_T, 0, 0, offsetof(mavlink_inputshapingoutput_t, pos_cmd_shaping_p) }, \
         } \
}
#endif

/**
 * @brief Pack a inputshapingoutput message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param pos_cmd_shaping_p  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_inputshapingoutput_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               int64_t pos_cmd_shaping_p)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_InputShapingOutput_LEN];
    _mav_put_int64_t(buf, 0, pos_cmd_shaping_p);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_InputShapingOutput_LEN);
#else
    mavlink_inputshapingoutput_t packet;
    packet.pos_cmd_shaping_p = pos_cmd_shaping_p;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_InputShapingOutput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_InputShapingOutput;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_InputShapingOutput_MIN_LEN, MAVLINK_MSG_ID_InputShapingOutput_LEN, MAVLINK_MSG_ID_InputShapingOutput_CRC);
}

/**
 * @brief Pack a inputshapingoutput message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param pos_cmd_shaping_p  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_inputshapingoutput_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               int64_t pos_cmd_shaping_p)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_InputShapingOutput_LEN];
    _mav_put_int64_t(buf, 0, pos_cmd_shaping_p);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_InputShapingOutput_LEN);
#else
    mavlink_inputshapingoutput_t packet;
    packet.pos_cmd_shaping_p = pos_cmd_shaping_p;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_InputShapingOutput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_InputShapingOutput;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_InputShapingOutput_MIN_LEN, MAVLINK_MSG_ID_InputShapingOutput_LEN, MAVLINK_MSG_ID_InputShapingOutput_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_InputShapingOutput_MIN_LEN, MAVLINK_MSG_ID_InputShapingOutput_LEN);
#endif
}

/**
 * @brief Pack a inputshapingoutput message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param pos_cmd_shaping_p  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_inputshapingoutput_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   int64_t pos_cmd_shaping_p)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_InputShapingOutput_LEN];
    _mav_put_int64_t(buf, 0, pos_cmd_shaping_p);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_InputShapingOutput_LEN);
#else
    mavlink_inputshapingoutput_t packet;
    packet.pos_cmd_shaping_p = pos_cmd_shaping_p;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_InputShapingOutput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_InputShapingOutput;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_InputShapingOutput_MIN_LEN, MAVLINK_MSG_ID_InputShapingOutput_LEN, MAVLINK_MSG_ID_InputShapingOutput_CRC);
}

/**
 * @brief Encode a inputshapingoutput struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param inputshapingoutput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_inputshapingoutput_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_inputshapingoutput_t* inputshapingoutput)
{
    return mavlink_msg_inputshapingoutput_pack(system_id, component_id, msg, inputshapingoutput->pos_cmd_shaping_p);
}

/**
 * @brief Encode a inputshapingoutput struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param inputshapingoutput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_inputshapingoutput_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_inputshapingoutput_t* inputshapingoutput)
{
    return mavlink_msg_inputshapingoutput_pack_chan(system_id, component_id, chan, msg, inputshapingoutput->pos_cmd_shaping_p);
}

/**
 * @brief Encode a inputshapingoutput struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param inputshapingoutput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_inputshapingoutput_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_inputshapingoutput_t* inputshapingoutput)
{
    return mavlink_msg_inputshapingoutput_pack_status(system_id, component_id, _status, msg,  inputshapingoutput->pos_cmd_shaping_p);
}

/**
 * @brief Send a inputshapingoutput message
 * @param chan MAVLink channel to send the message
 *
 * @param pos_cmd_shaping_p  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_inputshapingoutput_send(mavlink_channel_t chan, int64_t pos_cmd_shaping_p)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_InputShapingOutput_LEN];
    _mav_put_int64_t(buf, 0, pos_cmd_shaping_p);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_InputShapingOutput, buf, MAVLINK_MSG_ID_InputShapingOutput_MIN_LEN, MAVLINK_MSG_ID_InputShapingOutput_LEN, MAVLINK_MSG_ID_InputShapingOutput_CRC);
#else
    mavlink_inputshapingoutput_t packet;
    packet.pos_cmd_shaping_p = pos_cmd_shaping_p;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_InputShapingOutput, (const char *)&packet, MAVLINK_MSG_ID_InputShapingOutput_MIN_LEN, MAVLINK_MSG_ID_InputShapingOutput_LEN, MAVLINK_MSG_ID_InputShapingOutput_CRC);
#endif
}

/**
 * @brief Send a inputshapingoutput message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_inputshapingoutput_send_struct(mavlink_channel_t chan, const mavlink_inputshapingoutput_t* inputshapingoutput)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_inputshapingoutput_send(chan, inputshapingoutput->pos_cmd_shaping_p);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_InputShapingOutput, (const char *)inputshapingoutput, MAVLINK_MSG_ID_InputShapingOutput_MIN_LEN, MAVLINK_MSG_ID_InputShapingOutput_LEN, MAVLINK_MSG_ID_InputShapingOutput_CRC);
#endif
}

#if MAVLINK_MSG_ID_InputShapingOutput_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_inputshapingoutput_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  int64_t pos_cmd_shaping_p)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_int64_t(buf, 0, pos_cmd_shaping_p);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_InputShapingOutput, buf, MAVLINK_MSG_ID_InputShapingOutput_MIN_LEN, MAVLINK_MSG_ID_InputShapingOutput_LEN, MAVLINK_MSG_ID_InputShapingOutput_CRC);
#else
    mavlink_inputshapingoutput_t *packet = (mavlink_inputshapingoutput_t *)msgbuf;
    packet->pos_cmd_shaping_p = pos_cmd_shaping_p;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_InputShapingOutput, (const char *)packet, MAVLINK_MSG_ID_InputShapingOutput_MIN_LEN, MAVLINK_MSG_ID_InputShapingOutput_LEN, MAVLINK_MSG_ID_InputShapingOutput_CRC);
#endif
}
#endif

#endif

// MESSAGE InputShapingOutput UNPACKING


/**
 * @brief Get field pos_cmd_shaping_p from inputshapingoutput message
 *
 * @return  
 */
static inline int64_t mavlink_msg_inputshapingoutput_get_pos_cmd_shaping_p(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int64_t(msg,  0);
}

/**
 * @brief Decode a inputshapingoutput message into a struct
 *
 * @param msg The message to decode
 * @param inputshapingoutput C-struct to decode the message contents into
 */
static inline void mavlink_msg_inputshapingoutput_decode(const mavlink_message_t* msg, mavlink_inputshapingoutput_t* inputshapingoutput)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    inputshapingoutput->pos_cmd_shaping_p = mavlink_msg_inputshapingoutput_get_pos_cmd_shaping_p(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_InputShapingOutput_LEN? msg->len : MAVLINK_MSG_ID_InputShapingOutput_LEN;
        memset(inputshapingoutput, 0, MAVLINK_MSG_ID_InputShapingOutput_LEN);
    memcpy(inputshapingoutput, _MAV_PAYLOAD(msg), len);
#endif
}
