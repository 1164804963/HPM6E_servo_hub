#pragma once
// MESSAGE MotorCtlSmInput PACKING

#define MAVLINK_MSG_ID_MotorCtlSmInput 30023


typedef struct __mavlink_motorctlsminput_t {
 uint8_t motor_enable; /*<  */
 uint8_t hw_ready_state; /*<  */
} mavlink_motorctlsminput_t;

#define MAVLINK_MSG_ID_MotorCtlSmInput_LEN 2
#define MAVLINK_MSG_ID_MotorCtlSmInput_MIN_LEN 2
#define MAVLINK_MSG_ID_30023_LEN 2
#define MAVLINK_MSG_ID_30023_MIN_LEN 2

#define MAVLINK_MSG_ID_MotorCtlSmInput_CRC 152
#define MAVLINK_MSG_ID_30023_CRC 152



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_MotorCtlSmInput { \
    30023, \
    "MotorCtlSmInput", \
    2, \
    {  { "motor_enable", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_motorctlsminput_t, motor_enable) }, \
         { "hw_ready_state", NULL, MAVLINK_TYPE_UINT8_T, 0, 1, offsetof(mavlink_motorctlsminput_t, hw_ready_state) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_MotorCtlSmInput { \
    "MotorCtlSmInput", \
    2, \
    {  { "motor_enable", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_motorctlsminput_t, motor_enable) }, \
         { "hw_ready_state", NULL, MAVLINK_TYPE_UINT8_T, 0, 1, offsetof(mavlink_motorctlsminput_t, hw_ready_state) }, \
         } \
}
#endif

/**
 * @brief Pack a motorctlsminput message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param motor_enable  
 * @param hw_ready_state  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_motorctlsminput_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t motor_enable, uint8_t hw_ready_state)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MotorCtlSmInput_LEN];
    _mav_put_uint8_t(buf, 0, motor_enable);
    _mav_put_uint8_t(buf, 1, hw_ready_state);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MotorCtlSmInput_LEN);
#else
    mavlink_motorctlsminput_t packet;
    packet.motor_enable = motor_enable;
    packet.hw_ready_state = hw_ready_state;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MotorCtlSmInput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MotorCtlSmInput;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_MotorCtlSmInput_MIN_LEN, MAVLINK_MSG_ID_MotorCtlSmInput_LEN, MAVLINK_MSG_ID_MotorCtlSmInput_CRC);
}

/**
 * @brief Pack a motorctlsminput message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param motor_enable  
 * @param hw_ready_state  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_motorctlsminput_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint8_t motor_enable, uint8_t hw_ready_state)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MotorCtlSmInput_LEN];
    _mav_put_uint8_t(buf, 0, motor_enable);
    _mav_put_uint8_t(buf, 1, hw_ready_state);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MotorCtlSmInput_LEN);
#else
    mavlink_motorctlsminput_t packet;
    packet.motor_enable = motor_enable;
    packet.hw_ready_state = hw_ready_state;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MotorCtlSmInput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MotorCtlSmInput;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_MotorCtlSmInput_MIN_LEN, MAVLINK_MSG_ID_MotorCtlSmInput_LEN, MAVLINK_MSG_ID_MotorCtlSmInput_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_MotorCtlSmInput_MIN_LEN, MAVLINK_MSG_ID_MotorCtlSmInput_LEN);
#endif
}

/**
 * @brief Pack a motorctlsminput message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param motor_enable  
 * @param hw_ready_state  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_motorctlsminput_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t motor_enable,uint8_t hw_ready_state)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MotorCtlSmInput_LEN];
    _mav_put_uint8_t(buf, 0, motor_enable);
    _mav_put_uint8_t(buf, 1, hw_ready_state);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MotorCtlSmInput_LEN);
#else
    mavlink_motorctlsminput_t packet;
    packet.motor_enable = motor_enable;
    packet.hw_ready_state = hw_ready_state;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MotorCtlSmInput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MotorCtlSmInput;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_MotorCtlSmInput_MIN_LEN, MAVLINK_MSG_ID_MotorCtlSmInput_LEN, MAVLINK_MSG_ID_MotorCtlSmInput_CRC);
}

/**
 * @brief Encode a motorctlsminput struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param motorctlsminput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_motorctlsminput_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_motorctlsminput_t* motorctlsminput)
{
    return mavlink_msg_motorctlsminput_pack(system_id, component_id, msg, motorctlsminput->motor_enable, motorctlsminput->hw_ready_state);
}

/**
 * @brief Encode a motorctlsminput struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param motorctlsminput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_motorctlsminput_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_motorctlsminput_t* motorctlsminput)
{
    return mavlink_msg_motorctlsminput_pack_chan(system_id, component_id, chan, msg, motorctlsminput->motor_enable, motorctlsminput->hw_ready_state);
}

/**
 * @brief Encode a motorctlsminput struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param motorctlsminput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_motorctlsminput_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_motorctlsminput_t* motorctlsminput)
{
    return mavlink_msg_motorctlsminput_pack_status(system_id, component_id, _status, msg,  motorctlsminput->motor_enable, motorctlsminput->hw_ready_state);
}

/**
 * @brief Send a motorctlsminput message
 * @param chan MAVLink channel to send the message
 *
 * @param motor_enable  
 * @param hw_ready_state  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_motorctlsminput_send(mavlink_channel_t chan, uint8_t motor_enable, uint8_t hw_ready_state)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MotorCtlSmInput_LEN];
    _mav_put_uint8_t(buf, 0, motor_enable);
    _mav_put_uint8_t(buf, 1, hw_ready_state);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MotorCtlSmInput, buf, MAVLINK_MSG_ID_MotorCtlSmInput_MIN_LEN, MAVLINK_MSG_ID_MotorCtlSmInput_LEN, MAVLINK_MSG_ID_MotorCtlSmInput_CRC);
#else
    mavlink_motorctlsminput_t packet;
    packet.motor_enable = motor_enable;
    packet.hw_ready_state = hw_ready_state;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MotorCtlSmInput, (const char *)&packet, MAVLINK_MSG_ID_MotorCtlSmInput_MIN_LEN, MAVLINK_MSG_ID_MotorCtlSmInput_LEN, MAVLINK_MSG_ID_MotorCtlSmInput_CRC);
#endif
}

/**
 * @brief Send a motorctlsminput message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_motorctlsminput_send_struct(mavlink_channel_t chan, const mavlink_motorctlsminput_t* motorctlsminput)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_motorctlsminput_send(chan, motorctlsminput->motor_enable, motorctlsminput->hw_ready_state);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MotorCtlSmInput, (const char *)motorctlsminput, MAVLINK_MSG_ID_MotorCtlSmInput_MIN_LEN, MAVLINK_MSG_ID_MotorCtlSmInput_LEN, MAVLINK_MSG_ID_MotorCtlSmInput_CRC);
#endif
}

#if MAVLINK_MSG_ID_MotorCtlSmInput_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_motorctlsminput_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t motor_enable, uint8_t hw_ready_state)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint8_t(buf, 0, motor_enable);
    _mav_put_uint8_t(buf, 1, hw_ready_state);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MotorCtlSmInput, buf, MAVLINK_MSG_ID_MotorCtlSmInput_MIN_LEN, MAVLINK_MSG_ID_MotorCtlSmInput_LEN, MAVLINK_MSG_ID_MotorCtlSmInput_CRC);
#else
    mavlink_motorctlsminput_t *packet = (mavlink_motorctlsminput_t *)msgbuf;
    packet->motor_enable = motor_enable;
    packet->hw_ready_state = hw_ready_state;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MotorCtlSmInput, (const char *)packet, MAVLINK_MSG_ID_MotorCtlSmInput_MIN_LEN, MAVLINK_MSG_ID_MotorCtlSmInput_LEN, MAVLINK_MSG_ID_MotorCtlSmInput_CRC);
#endif
}
#endif

#endif

// MESSAGE MotorCtlSmInput UNPACKING


/**
 * @brief Get field motor_enable from motorctlsminput message
 *
 * @return  
 */
static inline uint8_t mavlink_msg_motorctlsminput_get_motor_enable(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  0);
}

/**
 * @brief Get field hw_ready_state from motorctlsminput message
 *
 * @return  
 */
static inline uint8_t mavlink_msg_motorctlsminput_get_hw_ready_state(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  1);
}

/**
 * @brief Decode a motorctlsminput message into a struct
 *
 * @param msg The message to decode
 * @param motorctlsminput C-struct to decode the message contents into
 */
static inline void mavlink_msg_motorctlsminput_decode(const mavlink_message_t* msg, mavlink_motorctlsminput_t* motorctlsminput)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    motorctlsminput->motor_enable = mavlink_msg_motorctlsminput_get_motor_enable(msg);
    motorctlsminput->hw_ready_state = mavlink_msg_motorctlsminput_get_hw_ready_state(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_MotorCtlSmInput_LEN? msg->len : MAVLINK_MSG_ID_MotorCtlSmInput_LEN;
        memset(motorctlsminput, 0, MAVLINK_MSG_ID_MotorCtlSmInput_LEN);
    memcpy(motorctlsminput, _MAV_PAYLOAD(msg), len);
#endif
}
