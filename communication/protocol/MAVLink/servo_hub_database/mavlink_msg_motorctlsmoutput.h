#pragma once
// MESSAGE MotorCtlSmOutput PACKING

#define MAVLINK_MSG_ID_MotorCtlSmOutput 30024


typedef struct __mavlink_motorctlsmoutput_t {
 uint32_t error; /*<  */
 uint32_t warning; /*<  */
 int8_t state; /*<  */
 int8_t mode_now; /*<  */
 uint8_t motor_enable_last; /*<  */
 int8_t state_last; /*<  */
} mavlink_motorctlsmoutput_t;

#define MAVLINK_MSG_ID_MotorCtlSmOutput_LEN 12
#define MAVLINK_MSG_ID_MotorCtlSmOutput_MIN_LEN 12
#define MAVLINK_MSG_ID_30024_LEN 12
#define MAVLINK_MSG_ID_30024_MIN_LEN 12

#define MAVLINK_MSG_ID_MotorCtlSmOutput_CRC 38
#define MAVLINK_MSG_ID_30024_CRC 38



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_MotorCtlSmOutput { \
    30024, \
    "MotorCtlSmOutput", \
    6, \
    {  { "state", NULL, MAVLINK_TYPE_INT8_T, 0, 8, offsetof(mavlink_motorctlsmoutput_t, state) }, \
         { "error", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_motorctlsmoutput_t, error) }, \
         { "warning", NULL, MAVLINK_TYPE_UINT32_T, 0, 4, offsetof(mavlink_motorctlsmoutput_t, warning) }, \
         { "mode_now", NULL, MAVLINK_TYPE_INT8_T, 0, 9, offsetof(mavlink_motorctlsmoutput_t, mode_now) }, \
         { "motor_enable_last", NULL, MAVLINK_TYPE_UINT8_T, 0, 10, offsetof(mavlink_motorctlsmoutput_t, motor_enable_last) }, \
         { "state_last", NULL, MAVLINK_TYPE_INT8_T, 0, 11, offsetof(mavlink_motorctlsmoutput_t, state_last) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_MotorCtlSmOutput { \
    "MotorCtlSmOutput", \
    6, \
    {  { "state", NULL, MAVLINK_TYPE_INT8_T, 0, 8, offsetof(mavlink_motorctlsmoutput_t, state) }, \
         { "error", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_motorctlsmoutput_t, error) }, \
         { "warning", NULL, MAVLINK_TYPE_UINT32_T, 0, 4, offsetof(mavlink_motorctlsmoutput_t, warning) }, \
         { "mode_now", NULL, MAVLINK_TYPE_INT8_T, 0, 9, offsetof(mavlink_motorctlsmoutput_t, mode_now) }, \
         { "motor_enable_last", NULL, MAVLINK_TYPE_UINT8_T, 0, 10, offsetof(mavlink_motorctlsmoutput_t, motor_enable_last) }, \
         { "state_last", NULL, MAVLINK_TYPE_INT8_T, 0, 11, offsetof(mavlink_motorctlsmoutput_t, state_last) }, \
         } \
}
#endif

/**
 * @brief Pack a motorctlsmoutput message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param state  
 * @param error  
 * @param warning  
 * @param mode_now  
 * @param motor_enable_last  
 * @param state_last  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_motorctlsmoutput_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               int8_t state, uint32_t error, uint32_t warning, int8_t mode_now, uint8_t motor_enable_last, int8_t state_last)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MotorCtlSmOutput_LEN];
    _mav_put_uint32_t(buf, 0, error);
    _mav_put_uint32_t(buf, 4, warning);
    _mav_put_int8_t(buf, 8, state);
    _mav_put_int8_t(buf, 9, mode_now);
    _mav_put_uint8_t(buf, 10, motor_enable_last);
    _mav_put_int8_t(buf, 11, state_last);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MotorCtlSmOutput_LEN);
#else
    mavlink_motorctlsmoutput_t packet;
    packet.error = error;
    packet.warning = warning;
    packet.state = state;
    packet.mode_now = mode_now;
    packet.motor_enable_last = motor_enable_last;
    packet.state_last = state_last;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MotorCtlSmOutput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MotorCtlSmOutput;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_MotorCtlSmOutput_MIN_LEN, MAVLINK_MSG_ID_MotorCtlSmOutput_LEN, MAVLINK_MSG_ID_MotorCtlSmOutput_CRC);
}

/**
 * @brief Pack a motorctlsmoutput message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param state  
 * @param error  
 * @param warning  
 * @param mode_now  
 * @param motor_enable_last  
 * @param state_last  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_motorctlsmoutput_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               int8_t state, uint32_t error, uint32_t warning, int8_t mode_now, uint8_t motor_enable_last, int8_t state_last)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MotorCtlSmOutput_LEN];
    _mav_put_uint32_t(buf, 0, error);
    _mav_put_uint32_t(buf, 4, warning);
    _mav_put_int8_t(buf, 8, state);
    _mav_put_int8_t(buf, 9, mode_now);
    _mav_put_uint8_t(buf, 10, motor_enable_last);
    _mav_put_int8_t(buf, 11, state_last);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MotorCtlSmOutput_LEN);
#else
    mavlink_motorctlsmoutput_t packet;
    packet.error = error;
    packet.warning = warning;
    packet.state = state;
    packet.mode_now = mode_now;
    packet.motor_enable_last = motor_enable_last;
    packet.state_last = state_last;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MotorCtlSmOutput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MotorCtlSmOutput;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_MotorCtlSmOutput_MIN_LEN, MAVLINK_MSG_ID_MotorCtlSmOutput_LEN, MAVLINK_MSG_ID_MotorCtlSmOutput_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_MotorCtlSmOutput_MIN_LEN, MAVLINK_MSG_ID_MotorCtlSmOutput_LEN);
#endif
}

/**
 * @brief Pack a motorctlsmoutput message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param state  
 * @param error  
 * @param warning  
 * @param mode_now  
 * @param motor_enable_last  
 * @param state_last  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_motorctlsmoutput_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   int8_t state,uint32_t error,uint32_t warning,int8_t mode_now,uint8_t motor_enable_last,int8_t state_last)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MotorCtlSmOutput_LEN];
    _mav_put_uint32_t(buf, 0, error);
    _mav_put_uint32_t(buf, 4, warning);
    _mav_put_int8_t(buf, 8, state);
    _mav_put_int8_t(buf, 9, mode_now);
    _mav_put_uint8_t(buf, 10, motor_enable_last);
    _mav_put_int8_t(buf, 11, state_last);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MotorCtlSmOutput_LEN);
#else
    mavlink_motorctlsmoutput_t packet;
    packet.error = error;
    packet.warning = warning;
    packet.state = state;
    packet.mode_now = mode_now;
    packet.motor_enable_last = motor_enable_last;
    packet.state_last = state_last;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MotorCtlSmOutput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MotorCtlSmOutput;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_MotorCtlSmOutput_MIN_LEN, MAVLINK_MSG_ID_MotorCtlSmOutput_LEN, MAVLINK_MSG_ID_MotorCtlSmOutput_CRC);
}

/**
 * @brief Encode a motorctlsmoutput struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param motorctlsmoutput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_motorctlsmoutput_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_motorctlsmoutput_t* motorctlsmoutput)
{
    return mavlink_msg_motorctlsmoutput_pack(system_id, component_id, msg, motorctlsmoutput->state, motorctlsmoutput->error, motorctlsmoutput->warning, motorctlsmoutput->mode_now, motorctlsmoutput->motor_enable_last, motorctlsmoutput->state_last);
}

/**
 * @brief Encode a motorctlsmoutput struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param motorctlsmoutput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_motorctlsmoutput_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_motorctlsmoutput_t* motorctlsmoutput)
{
    return mavlink_msg_motorctlsmoutput_pack_chan(system_id, component_id, chan, msg, motorctlsmoutput->state, motorctlsmoutput->error, motorctlsmoutput->warning, motorctlsmoutput->mode_now, motorctlsmoutput->motor_enable_last, motorctlsmoutput->state_last);
}

/**
 * @brief Encode a motorctlsmoutput struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param motorctlsmoutput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_motorctlsmoutput_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_motorctlsmoutput_t* motorctlsmoutput)
{
    return mavlink_msg_motorctlsmoutput_pack_status(system_id, component_id, _status, msg,  motorctlsmoutput->state, motorctlsmoutput->error, motorctlsmoutput->warning, motorctlsmoutput->mode_now, motorctlsmoutput->motor_enable_last, motorctlsmoutput->state_last);
}

/**
 * @brief Send a motorctlsmoutput message
 * @param chan MAVLink channel to send the message
 *
 * @param state  
 * @param error  
 * @param warning  
 * @param mode_now  
 * @param motor_enable_last  
 * @param state_last  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_motorctlsmoutput_send(mavlink_channel_t chan, int8_t state, uint32_t error, uint32_t warning, int8_t mode_now, uint8_t motor_enable_last, int8_t state_last)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MotorCtlSmOutput_LEN];
    _mav_put_uint32_t(buf, 0, error);
    _mav_put_uint32_t(buf, 4, warning);
    _mav_put_int8_t(buf, 8, state);
    _mav_put_int8_t(buf, 9, mode_now);
    _mav_put_uint8_t(buf, 10, motor_enable_last);
    _mav_put_int8_t(buf, 11, state_last);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MotorCtlSmOutput, buf, MAVLINK_MSG_ID_MotorCtlSmOutput_MIN_LEN, MAVLINK_MSG_ID_MotorCtlSmOutput_LEN, MAVLINK_MSG_ID_MotorCtlSmOutput_CRC);
#else
    mavlink_motorctlsmoutput_t packet;
    packet.error = error;
    packet.warning = warning;
    packet.state = state;
    packet.mode_now = mode_now;
    packet.motor_enable_last = motor_enable_last;
    packet.state_last = state_last;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MotorCtlSmOutput, (const char *)&packet, MAVLINK_MSG_ID_MotorCtlSmOutput_MIN_LEN, MAVLINK_MSG_ID_MotorCtlSmOutput_LEN, MAVLINK_MSG_ID_MotorCtlSmOutput_CRC);
#endif
}

/**
 * @brief Send a motorctlsmoutput message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_motorctlsmoutput_send_struct(mavlink_channel_t chan, const mavlink_motorctlsmoutput_t* motorctlsmoutput)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_motorctlsmoutput_send(chan, motorctlsmoutput->state, motorctlsmoutput->error, motorctlsmoutput->warning, motorctlsmoutput->mode_now, motorctlsmoutput->motor_enable_last, motorctlsmoutput->state_last);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MotorCtlSmOutput, (const char *)motorctlsmoutput, MAVLINK_MSG_ID_MotorCtlSmOutput_MIN_LEN, MAVLINK_MSG_ID_MotorCtlSmOutput_LEN, MAVLINK_MSG_ID_MotorCtlSmOutput_CRC);
#endif
}

#if MAVLINK_MSG_ID_MotorCtlSmOutput_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_motorctlsmoutput_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  int8_t state, uint32_t error, uint32_t warning, int8_t mode_now, uint8_t motor_enable_last, int8_t state_last)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint32_t(buf, 0, error);
    _mav_put_uint32_t(buf, 4, warning);
    _mav_put_int8_t(buf, 8, state);
    _mav_put_int8_t(buf, 9, mode_now);
    _mav_put_uint8_t(buf, 10, motor_enable_last);
    _mav_put_int8_t(buf, 11, state_last);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MotorCtlSmOutput, buf, MAVLINK_MSG_ID_MotorCtlSmOutput_MIN_LEN, MAVLINK_MSG_ID_MotorCtlSmOutput_LEN, MAVLINK_MSG_ID_MotorCtlSmOutput_CRC);
#else
    mavlink_motorctlsmoutput_t *packet = (mavlink_motorctlsmoutput_t *)msgbuf;
    packet->error = error;
    packet->warning = warning;
    packet->state = state;
    packet->mode_now = mode_now;
    packet->motor_enable_last = motor_enable_last;
    packet->state_last = state_last;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MotorCtlSmOutput, (const char *)packet, MAVLINK_MSG_ID_MotorCtlSmOutput_MIN_LEN, MAVLINK_MSG_ID_MotorCtlSmOutput_LEN, MAVLINK_MSG_ID_MotorCtlSmOutput_CRC);
#endif
}
#endif

#endif

// MESSAGE MotorCtlSmOutput UNPACKING


/**
 * @brief Get field state from motorctlsmoutput message
 *
 * @return  
 */
static inline int8_t mavlink_msg_motorctlsmoutput_get_state(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int8_t(msg,  8);
}

/**
 * @brief Get field error from motorctlsmoutput message
 *
 * @return  
 */
static inline uint32_t mavlink_msg_motorctlsmoutput_get_error(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Get field warning from motorctlsmoutput message
 *
 * @return  
 */
static inline uint32_t mavlink_msg_motorctlsmoutput_get_warning(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  4);
}

/**
 * @brief Get field mode_now from motorctlsmoutput message
 *
 * @return  
 */
static inline int8_t mavlink_msg_motorctlsmoutput_get_mode_now(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int8_t(msg,  9);
}

/**
 * @brief Get field motor_enable_last from motorctlsmoutput message
 *
 * @return  
 */
static inline uint8_t mavlink_msg_motorctlsmoutput_get_motor_enable_last(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  10);
}

/**
 * @brief Get field state_last from motorctlsmoutput message
 *
 * @return  
 */
static inline int8_t mavlink_msg_motorctlsmoutput_get_state_last(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int8_t(msg,  11);
}

/**
 * @brief Decode a motorctlsmoutput message into a struct
 *
 * @param msg The message to decode
 * @param motorctlsmoutput C-struct to decode the message contents into
 */
static inline void mavlink_msg_motorctlsmoutput_decode(const mavlink_message_t* msg, mavlink_motorctlsmoutput_t* motorctlsmoutput)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    motorctlsmoutput->error = mavlink_msg_motorctlsmoutput_get_error(msg);
    motorctlsmoutput->warning = mavlink_msg_motorctlsmoutput_get_warning(msg);
    motorctlsmoutput->state = mavlink_msg_motorctlsmoutput_get_state(msg);
    motorctlsmoutput->mode_now = mavlink_msg_motorctlsmoutput_get_mode_now(msg);
    motorctlsmoutput->motor_enable_last = mavlink_msg_motorctlsmoutput_get_motor_enable_last(msg);
    motorctlsmoutput->state_last = mavlink_msg_motorctlsmoutput_get_state_last(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_MotorCtlSmOutput_LEN? msg->len : MAVLINK_MSG_ID_MotorCtlSmOutput_LEN;
        memset(motorctlsmoutput, 0, MAVLINK_MSG_ID_MotorCtlSmOutput_LEN);
    memcpy(motorctlsmoutput, _MAV_PAYLOAD(msg), len);
#endif
}
