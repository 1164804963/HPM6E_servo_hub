#pragma once
// MESSAGE EncoderCalibrationStatus PACKING

#define MAVLINK_MSG_ID_EncoderCalibrationStatus 30075


typedef struct __mavlink_encodercalibrationstatus_t {
 uint16_t Calibration_status; /*<  */
} mavlink_encodercalibrationstatus_t;

#define MAVLINK_MSG_ID_EncoderCalibrationStatus_LEN 2
#define MAVLINK_MSG_ID_EncoderCalibrationStatus_MIN_LEN 2
#define MAVLINK_MSG_ID_30075_LEN 2
#define MAVLINK_MSG_ID_30075_MIN_LEN 2

#define MAVLINK_MSG_ID_EncoderCalibrationStatus_CRC 207
#define MAVLINK_MSG_ID_30075_CRC 207



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_EncoderCalibrationStatus { \
    30075, \
    "EncoderCalibrationStatus", \
    1, \
    {  { "Calibration_status", NULL, MAVLINK_TYPE_UINT16_T, 0, 0, offsetof(mavlink_encodercalibrationstatus_t, Calibration_status) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_EncoderCalibrationStatus { \
    "EncoderCalibrationStatus", \
    1, \
    {  { "Calibration_status", NULL, MAVLINK_TYPE_UINT16_T, 0, 0, offsetof(mavlink_encodercalibrationstatus_t, Calibration_status) }, \
         } \
}
#endif

/**
 * @brief Pack a encodercalibrationstatus message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param Calibration_status  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_encodercalibrationstatus_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint16_t Calibration_status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_EncoderCalibrationStatus_LEN];
    _mav_put_uint16_t(buf, 0, Calibration_status);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_EncoderCalibrationStatus_LEN);
#else
    mavlink_encodercalibrationstatus_t packet;
    packet.Calibration_status = Calibration_status;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_EncoderCalibrationStatus_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_EncoderCalibrationStatus;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_EncoderCalibrationStatus_MIN_LEN, MAVLINK_MSG_ID_EncoderCalibrationStatus_LEN, MAVLINK_MSG_ID_EncoderCalibrationStatus_CRC);
}

/**
 * @brief Pack a encodercalibrationstatus message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param Calibration_status  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_encodercalibrationstatus_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint16_t Calibration_status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_EncoderCalibrationStatus_LEN];
    _mav_put_uint16_t(buf, 0, Calibration_status);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_EncoderCalibrationStatus_LEN);
#else
    mavlink_encodercalibrationstatus_t packet;
    packet.Calibration_status = Calibration_status;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_EncoderCalibrationStatus_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_EncoderCalibrationStatus;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_EncoderCalibrationStatus_MIN_LEN, MAVLINK_MSG_ID_EncoderCalibrationStatus_LEN, MAVLINK_MSG_ID_EncoderCalibrationStatus_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_EncoderCalibrationStatus_MIN_LEN, MAVLINK_MSG_ID_EncoderCalibrationStatus_LEN);
#endif
}

/**
 * @brief Pack a encodercalibrationstatus message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param Calibration_status  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_encodercalibrationstatus_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint16_t Calibration_status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_EncoderCalibrationStatus_LEN];
    _mav_put_uint16_t(buf, 0, Calibration_status);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_EncoderCalibrationStatus_LEN);
#else
    mavlink_encodercalibrationstatus_t packet;
    packet.Calibration_status = Calibration_status;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_EncoderCalibrationStatus_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_EncoderCalibrationStatus;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_EncoderCalibrationStatus_MIN_LEN, MAVLINK_MSG_ID_EncoderCalibrationStatus_LEN, MAVLINK_MSG_ID_EncoderCalibrationStatus_CRC);
}

/**
 * @brief Encode a encodercalibrationstatus struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param encodercalibrationstatus C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_encodercalibrationstatus_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_encodercalibrationstatus_t* encodercalibrationstatus)
{
    return mavlink_msg_encodercalibrationstatus_pack(system_id, component_id, msg, encodercalibrationstatus->Calibration_status);
}

/**
 * @brief Encode a encodercalibrationstatus struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param encodercalibrationstatus C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_encodercalibrationstatus_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_encodercalibrationstatus_t* encodercalibrationstatus)
{
    return mavlink_msg_encodercalibrationstatus_pack_chan(system_id, component_id, chan, msg, encodercalibrationstatus->Calibration_status);
}

/**
 * @brief Encode a encodercalibrationstatus struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param encodercalibrationstatus C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_encodercalibrationstatus_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_encodercalibrationstatus_t* encodercalibrationstatus)
{
    return mavlink_msg_encodercalibrationstatus_pack_status(system_id, component_id, _status, msg,  encodercalibrationstatus->Calibration_status);
}

/**
 * @brief Send a encodercalibrationstatus message
 * @param chan MAVLink channel to send the message
 *
 * @param Calibration_status  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_encodercalibrationstatus_send(mavlink_channel_t chan, uint16_t Calibration_status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_EncoderCalibrationStatus_LEN];
    _mav_put_uint16_t(buf, 0, Calibration_status);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_EncoderCalibrationStatus, buf, MAVLINK_MSG_ID_EncoderCalibrationStatus_MIN_LEN, MAVLINK_MSG_ID_EncoderCalibrationStatus_LEN, MAVLINK_MSG_ID_EncoderCalibrationStatus_CRC);
#else
    mavlink_encodercalibrationstatus_t packet;
    packet.Calibration_status = Calibration_status;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_EncoderCalibrationStatus, (const char *)&packet, MAVLINK_MSG_ID_EncoderCalibrationStatus_MIN_LEN, MAVLINK_MSG_ID_EncoderCalibrationStatus_LEN, MAVLINK_MSG_ID_EncoderCalibrationStatus_CRC);
#endif
}

/**
 * @brief Send a encodercalibrationstatus message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_encodercalibrationstatus_send_struct(mavlink_channel_t chan, const mavlink_encodercalibrationstatus_t* encodercalibrationstatus)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_encodercalibrationstatus_send(chan, encodercalibrationstatus->Calibration_status);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_EncoderCalibrationStatus, (const char *)encodercalibrationstatus, MAVLINK_MSG_ID_EncoderCalibrationStatus_MIN_LEN, MAVLINK_MSG_ID_EncoderCalibrationStatus_LEN, MAVLINK_MSG_ID_EncoderCalibrationStatus_CRC);
#endif
}

#if MAVLINK_MSG_ID_EncoderCalibrationStatus_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_encodercalibrationstatus_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint16_t Calibration_status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint16_t(buf, 0, Calibration_status);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_EncoderCalibrationStatus, buf, MAVLINK_MSG_ID_EncoderCalibrationStatus_MIN_LEN, MAVLINK_MSG_ID_EncoderCalibrationStatus_LEN, MAVLINK_MSG_ID_EncoderCalibrationStatus_CRC);
#else
    mavlink_encodercalibrationstatus_t *packet = (mavlink_encodercalibrationstatus_t *)msgbuf;
    packet->Calibration_status = Calibration_status;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_EncoderCalibrationStatus, (const char *)packet, MAVLINK_MSG_ID_EncoderCalibrationStatus_MIN_LEN, MAVLINK_MSG_ID_EncoderCalibrationStatus_LEN, MAVLINK_MSG_ID_EncoderCalibrationStatus_CRC);
#endif
}
#endif

#endif

// MESSAGE EncoderCalibrationStatus UNPACKING


/**
 * @brief Get field Calibration_status from encodercalibrationstatus message
 *
 * @return  
 */
static inline uint16_t mavlink_msg_encodercalibrationstatus_get_Calibration_status(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  0);
}

/**
 * @brief Decode a encodercalibrationstatus message into a struct
 *
 * @param msg The message to decode
 * @param encodercalibrationstatus C-struct to decode the message contents into
 */
static inline void mavlink_msg_encodercalibrationstatus_decode(const mavlink_message_t* msg, mavlink_encodercalibrationstatus_t* encodercalibrationstatus)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    encodercalibrationstatus->Calibration_status = mavlink_msg_encodercalibrationstatus_get_Calibration_status(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_EncoderCalibrationStatus_LEN? msg->len : MAVLINK_MSG_ID_EncoderCalibrationStatus_LEN;
        memset(encodercalibrationstatus, 0, MAVLINK_MSG_ID_EncoderCalibrationStatus_LEN);
    memcpy(encodercalibrationstatus, _MAV_PAYLOAD(msg), len);
#endif
}
