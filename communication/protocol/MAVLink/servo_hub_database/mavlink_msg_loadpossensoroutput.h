#pragma once
// MESSAGE LoadPosSensorOutput PACKING

#define MAVLINK_MSG_ID_LoadPosSensorOutput 30072


typedef struct __mavlink_loadpossensoroutput_t {
 int64_t enc_sum_p; /*<  */
} mavlink_loadpossensoroutput_t;

#define MAVLINK_MSG_ID_LoadPosSensorOutput_LEN 8
#define MAVLINK_MSG_ID_LoadPosSensorOutput_MIN_LEN 8
#define MAVLINK_MSG_ID_30072_LEN 8
#define MAVLINK_MSG_ID_30072_MIN_LEN 8

#define MAVLINK_MSG_ID_LoadPosSensorOutput_CRC 228
#define MAVLINK_MSG_ID_30072_CRC 228



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_LoadPosSensorOutput { \
    30072, \
    "LoadPosSensorOutput", \
    1, \
    {  { "enc_sum_p", NULL, MAVLINK_TYPE_INT64_T, 0, 0, offsetof(mavlink_loadpossensoroutput_t, enc_sum_p) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_LoadPosSensorOutput { \
    "LoadPosSensorOutput", \
    1, \
    {  { "enc_sum_p", NULL, MAVLINK_TYPE_INT64_T, 0, 0, offsetof(mavlink_loadpossensoroutput_t, enc_sum_p) }, \
         } \
}
#endif

/**
 * @brief Pack a loadpossensoroutput message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param enc_sum_p  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_loadpossensoroutput_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               int64_t enc_sum_p)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_LoadPosSensorOutput_LEN];
    _mav_put_int64_t(buf, 0, enc_sum_p);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_LoadPosSensorOutput_LEN);
#else
    mavlink_loadpossensoroutput_t packet;
    packet.enc_sum_p = enc_sum_p;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_LoadPosSensorOutput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_LoadPosSensorOutput;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_LoadPosSensorOutput_MIN_LEN, MAVLINK_MSG_ID_LoadPosSensorOutput_LEN, MAVLINK_MSG_ID_LoadPosSensorOutput_CRC);
}

/**
 * @brief Pack a loadpossensoroutput message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param enc_sum_p  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_loadpossensoroutput_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               int64_t enc_sum_p)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_LoadPosSensorOutput_LEN];
    _mav_put_int64_t(buf, 0, enc_sum_p);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_LoadPosSensorOutput_LEN);
#else
    mavlink_loadpossensoroutput_t packet;
    packet.enc_sum_p = enc_sum_p;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_LoadPosSensorOutput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_LoadPosSensorOutput;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_LoadPosSensorOutput_MIN_LEN, MAVLINK_MSG_ID_LoadPosSensorOutput_LEN, MAVLINK_MSG_ID_LoadPosSensorOutput_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_LoadPosSensorOutput_MIN_LEN, MAVLINK_MSG_ID_LoadPosSensorOutput_LEN);
#endif
}

/**
 * @brief Pack a loadpossensoroutput message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param enc_sum_p  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_loadpossensoroutput_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   int64_t enc_sum_p)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_LoadPosSensorOutput_LEN];
    _mav_put_int64_t(buf, 0, enc_sum_p);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_LoadPosSensorOutput_LEN);
#else
    mavlink_loadpossensoroutput_t packet;
    packet.enc_sum_p = enc_sum_p;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_LoadPosSensorOutput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_LoadPosSensorOutput;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_LoadPosSensorOutput_MIN_LEN, MAVLINK_MSG_ID_LoadPosSensorOutput_LEN, MAVLINK_MSG_ID_LoadPosSensorOutput_CRC);
}

/**
 * @brief Encode a loadpossensoroutput struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param loadpossensoroutput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_loadpossensoroutput_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_loadpossensoroutput_t* loadpossensoroutput)
{
    return mavlink_msg_loadpossensoroutput_pack(system_id, component_id, msg, loadpossensoroutput->enc_sum_p);
}

/**
 * @brief Encode a loadpossensoroutput struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param loadpossensoroutput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_loadpossensoroutput_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_loadpossensoroutput_t* loadpossensoroutput)
{
    return mavlink_msg_loadpossensoroutput_pack_chan(system_id, component_id, chan, msg, loadpossensoroutput->enc_sum_p);
}

/**
 * @brief Encode a loadpossensoroutput struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param loadpossensoroutput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_loadpossensoroutput_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_loadpossensoroutput_t* loadpossensoroutput)
{
    return mavlink_msg_loadpossensoroutput_pack_status(system_id, component_id, _status, msg,  loadpossensoroutput->enc_sum_p);
}

/**
 * @brief Send a loadpossensoroutput message
 * @param chan MAVLink channel to send the message
 *
 * @param enc_sum_p  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_loadpossensoroutput_send(mavlink_channel_t chan, int64_t enc_sum_p)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_LoadPosSensorOutput_LEN];
    _mav_put_int64_t(buf, 0, enc_sum_p);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LoadPosSensorOutput, buf, MAVLINK_MSG_ID_LoadPosSensorOutput_MIN_LEN, MAVLINK_MSG_ID_LoadPosSensorOutput_LEN, MAVLINK_MSG_ID_LoadPosSensorOutput_CRC);
#else
    mavlink_loadpossensoroutput_t packet;
    packet.enc_sum_p = enc_sum_p;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LoadPosSensorOutput, (const char *)&packet, MAVLINK_MSG_ID_LoadPosSensorOutput_MIN_LEN, MAVLINK_MSG_ID_LoadPosSensorOutput_LEN, MAVLINK_MSG_ID_LoadPosSensorOutput_CRC);
#endif
}

/**
 * @brief Send a loadpossensoroutput message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_loadpossensoroutput_send_struct(mavlink_channel_t chan, const mavlink_loadpossensoroutput_t* loadpossensoroutput)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_loadpossensoroutput_send(chan, loadpossensoroutput->enc_sum_p);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LoadPosSensorOutput, (const char *)loadpossensoroutput, MAVLINK_MSG_ID_LoadPosSensorOutput_MIN_LEN, MAVLINK_MSG_ID_LoadPosSensorOutput_LEN, MAVLINK_MSG_ID_LoadPosSensorOutput_CRC);
#endif
}

#if MAVLINK_MSG_ID_LoadPosSensorOutput_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_loadpossensoroutput_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  int64_t enc_sum_p)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_int64_t(buf, 0, enc_sum_p);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LoadPosSensorOutput, buf, MAVLINK_MSG_ID_LoadPosSensorOutput_MIN_LEN, MAVLINK_MSG_ID_LoadPosSensorOutput_LEN, MAVLINK_MSG_ID_LoadPosSensorOutput_CRC);
#else
    mavlink_loadpossensoroutput_t *packet = (mavlink_loadpossensoroutput_t *)msgbuf;
    packet->enc_sum_p = enc_sum_p;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LoadPosSensorOutput, (const char *)packet, MAVLINK_MSG_ID_LoadPosSensorOutput_MIN_LEN, MAVLINK_MSG_ID_LoadPosSensorOutput_LEN, MAVLINK_MSG_ID_LoadPosSensorOutput_CRC);
#endif
}
#endif

#endif

// MESSAGE LoadPosSensorOutput UNPACKING


/**
 * @brief Get field enc_sum_p from loadpossensoroutput message
 *
 * @return  
 */
static inline int64_t mavlink_msg_loadpossensoroutput_get_enc_sum_p(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int64_t(msg,  0);
}

/**
 * @brief Decode a loadpossensoroutput message into a struct
 *
 * @param msg The message to decode
 * @param loadpossensoroutput C-struct to decode the message contents into
 */
static inline void mavlink_msg_loadpossensoroutput_decode(const mavlink_message_t* msg, mavlink_loadpossensoroutput_t* loadpossensoroutput)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    loadpossensoroutput->enc_sum_p = mavlink_msg_loadpossensoroutput_get_enc_sum_p(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_LoadPosSensorOutput_LEN? msg->len : MAVLINK_MSG_ID_LoadPosSensorOutput_LEN;
        memset(loadpossensoroutput, 0, MAVLINK_MSG_ID_LoadPosSensorOutput_LEN);
    memcpy(loadpossensoroutput, _MAV_PAYLOAD(msg), len);
#endif
}
