#pragma once
// MESSAGE InputShapingInput PACKING

#define MAVLINK_MSG_ID_InputShapingInput 30011


typedef struct __mavlink_inputshapinginput_t {
 int64_t pos_cmd_p; /*<  */
 int64_t pos_cmd_p_init; /*<  */
} mavlink_inputshapinginput_t;

#define MAVLINK_MSG_ID_InputShapingInput_LEN 16
#define MAVLINK_MSG_ID_InputShapingInput_MIN_LEN 16
#define MAVLINK_MSG_ID_30011_LEN 16
#define MAVLINK_MSG_ID_30011_MIN_LEN 16

#define MAVLINK_MSG_ID_InputShapingInput_CRC 152
#define MAVLINK_MSG_ID_30011_CRC 152



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_InputShapingInput { \
    30011, \
    "InputShapingInput", \
    2, \
    {  { "pos_cmd_p", NULL, MAVLINK_TYPE_INT64_T, 0, 0, offsetof(mavlink_inputshapinginput_t, pos_cmd_p) }, \
         { "pos_cmd_p_init", NULL, MAVLINK_TYPE_INT64_T, 0, 8, offsetof(mavlink_inputshapinginput_t, pos_cmd_p_init) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_InputShapingInput { \
    "InputShapingInput", \
    2, \
    {  { "pos_cmd_p", NULL, MAVLINK_TYPE_INT64_T, 0, 0, offsetof(mavlink_inputshapinginput_t, pos_cmd_p) }, \
         { "pos_cmd_p_init", NULL, MAVLINK_TYPE_INT64_T, 0, 8, offsetof(mavlink_inputshapinginput_t, pos_cmd_p_init) }, \
         } \
}
#endif

/**
 * @brief Pack a inputshapinginput message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param pos_cmd_p  
 * @param pos_cmd_p_init  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_inputshapinginput_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               int64_t pos_cmd_p, int64_t pos_cmd_p_init)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_InputShapingInput_LEN];
    _mav_put_int64_t(buf, 0, pos_cmd_p);
    _mav_put_int64_t(buf, 8, pos_cmd_p_init);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_InputShapingInput_LEN);
#else
    mavlink_inputshapinginput_t packet;
    packet.pos_cmd_p = pos_cmd_p;
    packet.pos_cmd_p_init = pos_cmd_p_init;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_InputShapingInput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_InputShapingInput;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_InputShapingInput_MIN_LEN, MAVLINK_MSG_ID_InputShapingInput_LEN, MAVLINK_MSG_ID_InputShapingInput_CRC);
}

/**
 * @brief Pack a inputshapinginput message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param pos_cmd_p  
 * @param pos_cmd_p_init  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_inputshapinginput_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               int64_t pos_cmd_p, int64_t pos_cmd_p_init)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_InputShapingInput_LEN];
    _mav_put_int64_t(buf, 0, pos_cmd_p);
    _mav_put_int64_t(buf, 8, pos_cmd_p_init);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_InputShapingInput_LEN);
#else
    mavlink_inputshapinginput_t packet;
    packet.pos_cmd_p = pos_cmd_p;
    packet.pos_cmd_p_init = pos_cmd_p_init;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_InputShapingInput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_InputShapingInput;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_InputShapingInput_MIN_LEN, MAVLINK_MSG_ID_InputShapingInput_LEN, MAVLINK_MSG_ID_InputShapingInput_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_InputShapingInput_MIN_LEN, MAVLINK_MSG_ID_InputShapingInput_LEN);
#endif
}

/**
 * @brief Pack a inputshapinginput message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param pos_cmd_p  
 * @param pos_cmd_p_init  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_inputshapinginput_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   int64_t pos_cmd_p,int64_t pos_cmd_p_init)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_InputShapingInput_LEN];
    _mav_put_int64_t(buf, 0, pos_cmd_p);
    _mav_put_int64_t(buf, 8, pos_cmd_p_init);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_InputShapingInput_LEN);
#else
    mavlink_inputshapinginput_t packet;
    packet.pos_cmd_p = pos_cmd_p;
    packet.pos_cmd_p_init = pos_cmd_p_init;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_InputShapingInput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_InputShapingInput;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_InputShapingInput_MIN_LEN, MAVLINK_MSG_ID_InputShapingInput_LEN, MAVLINK_MSG_ID_InputShapingInput_CRC);
}

/**
 * @brief Encode a inputshapinginput struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param inputshapinginput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_inputshapinginput_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_inputshapinginput_t* inputshapinginput)
{
    return mavlink_msg_inputshapinginput_pack(system_id, component_id, msg, inputshapinginput->pos_cmd_p, inputshapinginput->pos_cmd_p_init);
}

/**
 * @brief Encode a inputshapinginput struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param inputshapinginput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_inputshapinginput_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_inputshapinginput_t* inputshapinginput)
{
    return mavlink_msg_inputshapinginput_pack_chan(system_id, component_id, chan, msg, inputshapinginput->pos_cmd_p, inputshapinginput->pos_cmd_p_init);
}

/**
 * @brief Encode a inputshapinginput struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param inputshapinginput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_inputshapinginput_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_inputshapinginput_t* inputshapinginput)
{
    return mavlink_msg_inputshapinginput_pack_status(system_id, component_id, _status, msg,  inputshapinginput->pos_cmd_p, inputshapinginput->pos_cmd_p_init);
}

/**
 * @brief Send a inputshapinginput message
 * @param chan MAVLink channel to send the message
 *
 * @param pos_cmd_p  
 * @param pos_cmd_p_init  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_inputshapinginput_send(mavlink_channel_t chan, int64_t pos_cmd_p, int64_t pos_cmd_p_init)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_InputShapingInput_LEN];
    _mav_put_int64_t(buf, 0, pos_cmd_p);
    _mav_put_int64_t(buf, 8, pos_cmd_p_init);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_InputShapingInput, buf, MAVLINK_MSG_ID_InputShapingInput_MIN_LEN, MAVLINK_MSG_ID_InputShapingInput_LEN, MAVLINK_MSG_ID_InputShapingInput_CRC);
#else
    mavlink_inputshapinginput_t packet;
    packet.pos_cmd_p = pos_cmd_p;
    packet.pos_cmd_p_init = pos_cmd_p_init;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_InputShapingInput, (const char *)&packet, MAVLINK_MSG_ID_InputShapingInput_MIN_LEN, MAVLINK_MSG_ID_InputShapingInput_LEN, MAVLINK_MSG_ID_InputShapingInput_CRC);
#endif
}

/**
 * @brief Send a inputshapinginput message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_inputshapinginput_send_struct(mavlink_channel_t chan, const mavlink_inputshapinginput_t* inputshapinginput)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_inputshapinginput_send(chan, inputshapinginput->pos_cmd_p, inputshapinginput->pos_cmd_p_init);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_InputShapingInput, (const char *)inputshapinginput, MAVLINK_MSG_ID_InputShapingInput_MIN_LEN, MAVLINK_MSG_ID_InputShapingInput_LEN, MAVLINK_MSG_ID_InputShapingInput_CRC);
#endif
}

#if MAVLINK_MSG_ID_InputShapingInput_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_inputshapinginput_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  int64_t pos_cmd_p, int64_t pos_cmd_p_init)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_int64_t(buf, 0, pos_cmd_p);
    _mav_put_int64_t(buf, 8, pos_cmd_p_init);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_InputShapingInput, buf, MAVLINK_MSG_ID_InputShapingInput_MIN_LEN, MAVLINK_MSG_ID_InputShapingInput_LEN, MAVLINK_MSG_ID_InputShapingInput_CRC);
#else
    mavlink_inputshapinginput_t *packet = (mavlink_inputshapinginput_t *)msgbuf;
    packet->pos_cmd_p = pos_cmd_p;
    packet->pos_cmd_p_init = pos_cmd_p_init;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_InputShapingInput, (const char *)packet, MAVLINK_MSG_ID_InputShapingInput_MIN_LEN, MAVLINK_MSG_ID_InputShapingInput_LEN, MAVLINK_MSG_ID_InputShapingInput_CRC);
#endif
}
#endif

#endif

// MESSAGE InputShapingInput UNPACKING


/**
 * @brief Get field pos_cmd_p from inputshapinginput message
 *
 * @return  
 */
static inline int64_t mavlink_msg_inputshapinginput_get_pos_cmd_p(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int64_t(msg,  0);
}

/**
 * @brief Get field pos_cmd_p_init from inputshapinginput message
 *
 * @return  
 */
static inline int64_t mavlink_msg_inputshapinginput_get_pos_cmd_p_init(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int64_t(msg,  8);
}

/**
 * @brief Decode a inputshapinginput message into a struct
 *
 * @param msg The message to decode
 * @param inputshapinginput C-struct to decode the message contents into
 */
static inline void mavlink_msg_inputshapinginput_decode(const mavlink_message_t* msg, mavlink_inputshapinginput_t* inputshapinginput)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    inputshapinginput->pos_cmd_p = mavlink_msg_inputshapinginput_get_pos_cmd_p(msg);
    inputshapinginput->pos_cmd_p_init = mavlink_msg_inputshapinginput_get_pos_cmd_p_init(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_InputShapingInput_LEN? msg->len : MAVLINK_MSG_ID_InputShapingInput_LEN;
        memset(inputshapinginput, 0, MAVLINK_MSG_ID_InputShapingInput_LEN);
    memcpy(inputshapinginput, _MAV_PAYLOAD(msg), len);
#endif
}
