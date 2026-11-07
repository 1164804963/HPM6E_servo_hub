#pragma once
// MESSAGE LoadPosSensorInput PACKING

#define MAVLINK_MSG_ID_LoadPosSensorInput 30070


typedef struct __mavlink_loadpossensorinput_t {
 uint32_t enc_counts_now_p; /*<  */
} mavlink_loadpossensorinput_t;

#define MAVLINK_MSG_ID_LoadPosSensorInput_LEN 4
#define MAVLINK_MSG_ID_LoadPosSensorInput_MIN_LEN 4
#define MAVLINK_MSG_ID_30070_LEN 4
#define MAVLINK_MSG_ID_30070_MIN_LEN 4

#define MAVLINK_MSG_ID_LoadPosSensorInput_CRC 215
#define MAVLINK_MSG_ID_30070_CRC 215



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_LoadPosSensorInput { \
    30070, \
    "LoadPosSensorInput", \
    1, \
    {  { "enc_counts_now_p", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_loadpossensorinput_t, enc_counts_now_p) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_LoadPosSensorInput { \
    "LoadPosSensorInput", \
    1, \
    {  { "enc_counts_now_p", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_loadpossensorinput_t, enc_counts_now_p) }, \
         } \
}
#endif

/**
 * @brief Pack a loadpossensorinput message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param enc_counts_now_p  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_loadpossensorinput_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint32_t enc_counts_now_p)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_LoadPosSensorInput_LEN];
    _mav_put_uint32_t(buf, 0, enc_counts_now_p);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_LoadPosSensorInput_LEN);
#else
    mavlink_loadpossensorinput_t packet;
    packet.enc_counts_now_p = enc_counts_now_p;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_LoadPosSensorInput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_LoadPosSensorInput;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_LoadPosSensorInput_MIN_LEN, MAVLINK_MSG_ID_LoadPosSensorInput_LEN, MAVLINK_MSG_ID_LoadPosSensorInput_CRC);
}

/**
 * @brief Pack a loadpossensorinput message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param enc_counts_now_p  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_loadpossensorinput_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint32_t enc_counts_now_p)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_LoadPosSensorInput_LEN];
    _mav_put_uint32_t(buf, 0, enc_counts_now_p);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_LoadPosSensorInput_LEN);
#else
    mavlink_loadpossensorinput_t packet;
    packet.enc_counts_now_p = enc_counts_now_p;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_LoadPosSensorInput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_LoadPosSensorInput;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_LoadPosSensorInput_MIN_LEN, MAVLINK_MSG_ID_LoadPosSensorInput_LEN, MAVLINK_MSG_ID_LoadPosSensorInput_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_LoadPosSensorInput_MIN_LEN, MAVLINK_MSG_ID_LoadPosSensorInput_LEN);
#endif
}

/**
 * @brief Pack a loadpossensorinput message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param enc_counts_now_p  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_loadpossensorinput_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint32_t enc_counts_now_p)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_LoadPosSensorInput_LEN];
    _mav_put_uint32_t(buf, 0, enc_counts_now_p);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_LoadPosSensorInput_LEN);
#else
    mavlink_loadpossensorinput_t packet;
    packet.enc_counts_now_p = enc_counts_now_p;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_LoadPosSensorInput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_LoadPosSensorInput;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_LoadPosSensorInput_MIN_LEN, MAVLINK_MSG_ID_LoadPosSensorInput_LEN, MAVLINK_MSG_ID_LoadPosSensorInput_CRC);
}

/**
 * @brief Encode a loadpossensorinput struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param loadpossensorinput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_loadpossensorinput_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_loadpossensorinput_t* loadpossensorinput)
{
    return mavlink_msg_loadpossensorinput_pack(system_id, component_id, msg, loadpossensorinput->enc_counts_now_p);
}

/**
 * @brief Encode a loadpossensorinput struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param loadpossensorinput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_loadpossensorinput_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_loadpossensorinput_t* loadpossensorinput)
{
    return mavlink_msg_loadpossensorinput_pack_chan(system_id, component_id, chan, msg, loadpossensorinput->enc_counts_now_p);
}

/**
 * @brief Encode a loadpossensorinput struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param loadpossensorinput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_loadpossensorinput_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_loadpossensorinput_t* loadpossensorinput)
{
    return mavlink_msg_loadpossensorinput_pack_status(system_id, component_id, _status, msg,  loadpossensorinput->enc_counts_now_p);
}

/**
 * @brief Send a loadpossensorinput message
 * @param chan MAVLink channel to send the message
 *
 * @param enc_counts_now_p  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_loadpossensorinput_send(mavlink_channel_t chan, uint32_t enc_counts_now_p)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_LoadPosSensorInput_LEN];
    _mav_put_uint32_t(buf, 0, enc_counts_now_p);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LoadPosSensorInput, buf, MAVLINK_MSG_ID_LoadPosSensorInput_MIN_LEN, MAVLINK_MSG_ID_LoadPosSensorInput_LEN, MAVLINK_MSG_ID_LoadPosSensorInput_CRC);
#else
    mavlink_loadpossensorinput_t packet;
    packet.enc_counts_now_p = enc_counts_now_p;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LoadPosSensorInput, (const char *)&packet, MAVLINK_MSG_ID_LoadPosSensorInput_MIN_LEN, MAVLINK_MSG_ID_LoadPosSensorInput_LEN, MAVLINK_MSG_ID_LoadPosSensorInput_CRC);
#endif
}

/**
 * @brief Send a loadpossensorinput message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_loadpossensorinput_send_struct(mavlink_channel_t chan, const mavlink_loadpossensorinput_t* loadpossensorinput)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_loadpossensorinput_send(chan, loadpossensorinput->enc_counts_now_p);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LoadPosSensorInput, (const char *)loadpossensorinput, MAVLINK_MSG_ID_LoadPosSensorInput_MIN_LEN, MAVLINK_MSG_ID_LoadPosSensorInput_LEN, MAVLINK_MSG_ID_LoadPosSensorInput_CRC);
#endif
}

#if MAVLINK_MSG_ID_LoadPosSensorInput_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_loadpossensorinput_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint32_t enc_counts_now_p)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint32_t(buf, 0, enc_counts_now_p);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LoadPosSensorInput, buf, MAVLINK_MSG_ID_LoadPosSensorInput_MIN_LEN, MAVLINK_MSG_ID_LoadPosSensorInput_LEN, MAVLINK_MSG_ID_LoadPosSensorInput_CRC);
#else
    mavlink_loadpossensorinput_t *packet = (mavlink_loadpossensorinput_t *)msgbuf;
    packet->enc_counts_now_p = enc_counts_now_p;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LoadPosSensorInput, (const char *)packet, MAVLINK_MSG_ID_LoadPosSensorInput_MIN_LEN, MAVLINK_MSG_ID_LoadPosSensorInput_LEN, MAVLINK_MSG_ID_LoadPosSensorInput_CRC);
#endif
}
#endif

#endif

// MESSAGE LoadPosSensorInput UNPACKING


/**
 * @brief Get field enc_counts_now_p from loadpossensorinput message
 *
 * @return  
 */
static inline uint32_t mavlink_msg_loadpossensorinput_get_enc_counts_now_p(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Decode a loadpossensorinput message into a struct
 *
 * @param msg The message to decode
 * @param loadpossensorinput C-struct to decode the message contents into
 */
static inline void mavlink_msg_loadpossensorinput_decode(const mavlink_message_t* msg, mavlink_loadpossensorinput_t* loadpossensorinput)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    loadpossensorinput->enc_counts_now_p = mavlink_msg_loadpossensorinput_get_enc_counts_now_p(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_LoadPosSensorInput_LEN? msg->len : MAVLINK_MSG_ID_LoadPosSensorInput_LEN;
        memset(loadpossensorinput, 0, MAVLINK_MSG_ID_LoadPosSensorInput_LEN);
    memcpy(loadpossensorinput, _MAV_PAYLOAD(msg), len);
#endif
}
