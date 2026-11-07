#pragma once
// MESSAGE AppMotorConfig PACKING

#define MAVLINK_MSG_ID_AppMotorConfig 30063


typedef struct __mavlink_appmotorconfig_t {
 float Motor_rated_current; /*<  */
 float Motor_rated_torque; /*<  */
 float Motor_peak_current; /*<  */
 float Motor_pole_pairs; /*<  */
 float Motor_maximum_speed; /*<  */
 float Resistance; /*<  */
 float Inductance; /*<  */
 uint32_t Reduction_ratio_num; /*<  */
 uint32_t Reduction_ratio_den; /*<  */
 float Torque_constant; /*<  */
 float Reduction_ratio; /*<  */
 float Reduction_ratio_inv; /*<  */
 float Motor_rotor_inertia; /*<  */
} mavlink_appmotorconfig_t;

#define MAVLINK_MSG_ID_AppMotorConfig_LEN 52
#define MAVLINK_MSG_ID_AppMotorConfig_MIN_LEN 52
#define MAVLINK_MSG_ID_30063_LEN 52
#define MAVLINK_MSG_ID_30063_MIN_LEN 52

#define MAVLINK_MSG_ID_AppMotorConfig_CRC 239
#define MAVLINK_MSG_ID_30063_CRC 239



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_AppMotorConfig { \
    30063, \
    "AppMotorConfig", \
    13, \
    {  { "Motor_rated_current", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_appmotorconfig_t, Motor_rated_current) }, \
         { "Motor_rated_torque", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_appmotorconfig_t, Motor_rated_torque) }, \
         { "Motor_peak_current", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_appmotorconfig_t, Motor_peak_current) }, \
         { "Motor_pole_pairs", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_appmotorconfig_t, Motor_pole_pairs) }, \
         { "Motor_maximum_speed", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_appmotorconfig_t, Motor_maximum_speed) }, \
         { "Resistance", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_appmotorconfig_t, Resistance) }, \
         { "Inductance", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_appmotorconfig_t, Inductance) }, \
         { "Reduction_ratio_num", NULL, MAVLINK_TYPE_UINT32_T, 0, 28, offsetof(mavlink_appmotorconfig_t, Reduction_ratio_num) }, \
         { "Reduction_ratio_den", NULL, MAVLINK_TYPE_UINT32_T, 0, 32, offsetof(mavlink_appmotorconfig_t, Reduction_ratio_den) }, \
         { "Torque_constant", NULL, MAVLINK_TYPE_FLOAT, 0, 36, offsetof(mavlink_appmotorconfig_t, Torque_constant) }, \
         { "Reduction_ratio", NULL, MAVLINK_TYPE_FLOAT, 0, 40, offsetof(mavlink_appmotorconfig_t, Reduction_ratio) }, \
         { "Reduction_ratio_inv", NULL, MAVLINK_TYPE_FLOAT, 0, 44, offsetof(mavlink_appmotorconfig_t, Reduction_ratio_inv) }, \
         { "Motor_rotor_inertia", NULL, MAVLINK_TYPE_FLOAT, 0, 48, offsetof(mavlink_appmotorconfig_t, Motor_rotor_inertia) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_AppMotorConfig { \
    "AppMotorConfig", \
    13, \
    {  { "Motor_rated_current", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_appmotorconfig_t, Motor_rated_current) }, \
         { "Motor_rated_torque", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_appmotorconfig_t, Motor_rated_torque) }, \
         { "Motor_peak_current", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_appmotorconfig_t, Motor_peak_current) }, \
         { "Motor_pole_pairs", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_appmotorconfig_t, Motor_pole_pairs) }, \
         { "Motor_maximum_speed", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_appmotorconfig_t, Motor_maximum_speed) }, \
         { "Resistance", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_appmotorconfig_t, Resistance) }, \
         { "Inductance", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_appmotorconfig_t, Inductance) }, \
         { "Reduction_ratio_num", NULL, MAVLINK_TYPE_UINT32_T, 0, 28, offsetof(mavlink_appmotorconfig_t, Reduction_ratio_num) }, \
         { "Reduction_ratio_den", NULL, MAVLINK_TYPE_UINT32_T, 0, 32, offsetof(mavlink_appmotorconfig_t, Reduction_ratio_den) }, \
         { "Torque_constant", NULL, MAVLINK_TYPE_FLOAT, 0, 36, offsetof(mavlink_appmotorconfig_t, Torque_constant) }, \
         { "Reduction_ratio", NULL, MAVLINK_TYPE_FLOAT, 0, 40, offsetof(mavlink_appmotorconfig_t, Reduction_ratio) }, \
         { "Reduction_ratio_inv", NULL, MAVLINK_TYPE_FLOAT, 0, 44, offsetof(mavlink_appmotorconfig_t, Reduction_ratio_inv) }, \
         { "Motor_rotor_inertia", NULL, MAVLINK_TYPE_FLOAT, 0, 48, offsetof(mavlink_appmotorconfig_t, Motor_rotor_inertia) }, \
         } \
}
#endif

/**
 * @brief Pack a appmotorconfig message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param Motor_rated_current  
 * @param Motor_rated_torque  
 * @param Motor_peak_current  
 * @param Motor_pole_pairs  
 * @param Motor_maximum_speed  
 * @param Resistance  
 * @param Inductance  
 * @param Reduction_ratio_num  
 * @param Reduction_ratio_den  
 * @param Torque_constant  
 * @param Reduction_ratio  
 * @param Reduction_ratio_inv  
 * @param Motor_rotor_inertia  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_appmotorconfig_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               float Motor_rated_current, float Motor_rated_torque, float Motor_peak_current, float Motor_pole_pairs, float Motor_maximum_speed, float Resistance, float Inductance, uint32_t Reduction_ratio_num, uint32_t Reduction_ratio_den, float Torque_constant, float Reduction_ratio, float Reduction_ratio_inv, float Motor_rotor_inertia)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_AppMotorConfig_LEN];
    _mav_put_float(buf, 0, Motor_rated_current);
    _mav_put_float(buf, 4, Motor_rated_torque);
    _mav_put_float(buf, 8, Motor_peak_current);
    _mav_put_float(buf, 12, Motor_pole_pairs);
    _mav_put_float(buf, 16, Motor_maximum_speed);
    _mav_put_float(buf, 20, Resistance);
    _mav_put_float(buf, 24, Inductance);
    _mav_put_uint32_t(buf, 28, Reduction_ratio_num);
    _mav_put_uint32_t(buf, 32, Reduction_ratio_den);
    _mav_put_float(buf, 36, Torque_constant);
    _mav_put_float(buf, 40, Reduction_ratio);
    _mav_put_float(buf, 44, Reduction_ratio_inv);
    _mav_put_float(buf, 48, Motor_rotor_inertia);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_AppMotorConfig_LEN);
#else
    mavlink_appmotorconfig_t packet;
    packet.Motor_rated_current = Motor_rated_current;
    packet.Motor_rated_torque = Motor_rated_torque;
    packet.Motor_peak_current = Motor_peak_current;
    packet.Motor_pole_pairs = Motor_pole_pairs;
    packet.Motor_maximum_speed = Motor_maximum_speed;
    packet.Resistance = Resistance;
    packet.Inductance = Inductance;
    packet.Reduction_ratio_num = Reduction_ratio_num;
    packet.Reduction_ratio_den = Reduction_ratio_den;
    packet.Torque_constant = Torque_constant;
    packet.Reduction_ratio = Reduction_ratio;
    packet.Reduction_ratio_inv = Reduction_ratio_inv;
    packet.Motor_rotor_inertia = Motor_rotor_inertia;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_AppMotorConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_AppMotorConfig;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_AppMotorConfig_MIN_LEN, MAVLINK_MSG_ID_AppMotorConfig_LEN, MAVLINK_MSG_ID_AppMotorConfig_CRC);
}

/**
 * @brief Pack a appmotorconfig message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param Motor_rated_current  
 * @param Motor_rated_torque  
 * @param Motor_peak_current  
 * @param Motor_pole_pairs  
 * @param Motor_maximum_speed  
 * @param Resistance  
 * @param Inductance  
 * @param Reduction_ratio_num  
 * @param Reduction_ratio_den  
 * @param Torque_constant  
 * @param Reduction_ratio  
 * @param Reduction_ratio_inv  
 * @param Motor_rotor_inertia  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_appmotorconfig_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               float Motor_rated_current, float Motor_rated_torque, float Motor_peak_current, float Motor_pole_pairs, float Motor_maximum_speed, float Resistance, float Inductance, uint32_t Reduction_ratio_num, uint32_t Reduction_ratio_den, float Torque_constant, float Reduction_ratio, float Reduction_ratio_inv, float Motor_rotor_inertia)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_AppMotorConfig_LEN];
    _mav_put_float(buf, 0, Motor_rated_current);
    _mav_put_float(buf, 4, Motor_rated_torque);
    _mav_put_float(buf, 8, Motor_peak_current);
    _mav_put_float(buf, 12, Motor_pole_pairs);
    _mav_put_float(buf, 16, Motor_maximum_speed);
    _mav_put_float(buf, 20, Resistance);
    _mav_put_float(buf, 24, Inductance);
    _mav_put_uint32_t(buf, 28, Reduction_ratio_num);
    _mav_put_uint32_t(buf, 32, Reduction_ratio_den);
    _mav_put_float(buf, 36, Torque_constant);
    _mav_put_float(buf, 40, Reduction_ratio);
    _mav_put_float(buf, 44, Reduction_ratio_inv);
    _mav_put_float(buf, 48, Motor_rotor_inertia);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_AppMotorConfig_LEN);
#else
    mavlink_appmotorconfig_t packet;
    packet.Motor_rated_current = Motor_rated_current;
    packet.Motor_rated_torque = Motor_rated_torque;
    packet.Motor_peak_current = Motor_peak_current;
    packet.Motor_pole_pairs = Motor_pole_pairs;
    packet.Motor_maximum_speed = Motor_maximum_speed;
    packet.Resistance = Resistance;
    packet.Inductance = Inductance;
    packet.Reduction_ratio_num = Reduction_ratio_num;
    packet.Reduction_ratio_den = Reduction_ratio_den;
    packet.Torque_constant = Torque_constant;
    packet.Reduction_ratio = Reduction_ratio;
    packet.Reduction_ratio_inv = Reduction_ratio_inv;
    packet.Motor_rotor_inertia = Motor_rotor_inertia;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_AppMotorConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_AppMotorConfig;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_AppMotorConfig_MIN_LEN, MAVLINK_MSG_ID_AppMotorConfig_LEN, MAVLINK_MSG_ID_AppMotorConfig_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_AppMotorConfig_MIN_LEN, MAVLINK_MSG_ID_AppMotorConfig_LEN);
#endif
}

/**
 * @brief Pack a appmotorconfig message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param Motor_rated_current  
 * @param Motor_rated_torque  
 * @param Motor_peak_current  
 * @param Motor_pole_pairs  
 * @param Motor_maximum_speed  
 * @param Resistance  
 * @param Inductance  
 * @param Reduction_ratio_num  
 * @param Reduction_ratio_den  
 * @param Torque_constant  
 * @param Reduction_ratio  
 * @param Reduction_ratio_inv  
 * @param Motor_rotor_inertia  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_appmotorconfig_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   float Motor_rated_current,float Motor_rated_torque,float Motor_peak_current,float Motor_pole_pairs,float Motor_maximum_speed,float Resistance,float Inductance,uint32_t Reduction_ratio_num,uint32_t Reduction_ratio_den,float Torque_constant,float Reduction_ratio,float Reduction_ratio_inv,float Motor_rotor_inertia)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_AppMotorConfig_LEN];
    _mav_put_float(buf, 0, Motor_rated_current);
    _mav_put_float(buf, 4, Motor_rated_torque);
    _mav_put_float(buf, 8, Motor_peak_current);
    _mav_put_float(buf, 12, Motor_pole_pairs);
    _mav_put_float(buf, 16, Motor_maximum_speed);
    _mav_put_float(buf, 20, Resistance);
    _mav_put_float(buf, 24, Inductance);
    _mav_put_uint32_t(buf, 28, Reduction_ratio_num);
    _mav_put_uint32_t(buf, 32, Reduction_ratio_den);
    _mav_put_float(buf, 36, Torque_constant);
    _mav_put_float(buf, 40, Reduction_ratio);
    _mav_put_float(buf, 44, Reduction_ratio_inv);
    _mav_put_float(buf, 48, Motor_rotor_inertia);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_AppMotorConfig_LEN);
#else
    mavlink_appmotorconfig_t packet;
    packet.Motor_rated_current = Motor_rated_current;
    packet.Motor_rated_torque = Motor_rated_torque;
    packet.Motor_peak_current = Motor_peak_current;
    packet.Motor_pole_pairs = Motor_pole_pairs;
    packet.Motor_maximum_speed = Motor_maximum_speed;
    packet.Resistance = Resistance;
    packet.Inductance = Inductance;
    packet.Reduction_ratio_num = Reduction_ratio_num;
    packet.Reduction_ratio_den = Reduction_ratio_den;
    packet.Torque_constant = Torque_constant;
    packet.Reduction_ratio = Reduction_ratio;
    packet.Reduction_ratio_inv = Reduction_ratio_inv;
    packet.Motor_rotor_inertia = Motor_rotor_inertia;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_AppMotorConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_AppMotorConfig;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_AppMotorConfig_MIN_LEN, MAVLINK_MSG_ID_AppMotorConfig_LEN, MAVLINK_MSG_ID_AppMotorConfig_CRC);
}

/**
 * @brief Encode a appmotorconfig struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param appmotorconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_appmotorconfig_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_appmotorconfig_t* appmotorconfig)
{
    return mavlink_msg_appmotorconfig_pack(system_id, component_id, msg, appmotorconfig->Motor_rated_current, appmotorconfig->Motor_rated_torque, appmotorconfig->Motor_peak_current, appmotorconfig->Motor_pole_pairs, appmotorconfig->Motor_maximum_speed, appmotorconfig->Resistance, appmotorconfig->Inductance, appmotorconfig->Reduction_ratio_num, appmotorconfig->Reduction_ratio_den, appmotorconfig->Torque_constant, appmotorconfig->Reduction_ratio, appmotorconfig->Reduction_ratio_inv, appmotorconfig->Motor_rotor_inertia);
}

/**
 * @brief Encode a appmotorconfig struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param appmotorconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_appmotorconfig_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_appmotorconfig_t* appmotorconfig)
{
    return mavlink_msg_appmotorconfig_pack_chan(system_id, component_id, chan, msg, appmotorconfig->Motor_rated_current, appmotorconfig->Motor_rated_torque, appmotorconfig->Motor_peak_current, appmotorconfig->Motor_pole_pairs, appmotorconfig->Motor_maximum_speed, appmotorconfig->Resistance, appmotorconfig->Inductance, appmotorconfig->Reduction_ratio_num, appmotorconfig->Reduction_ratio_den, appmotorconfig->Torque_constant, appmotorconfig->Reduction_ratio, appmotorconfig->Reduction_ratio_inv, appmotorconfig->Motor_rotor_inertia);
}

/**
 * @brief Encode a appmotorconfig struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param appmotorconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_appmotorconfig_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_appmotorconfig_t* appmotorconfig)
{
    return mavlink_msg_appmotorconfig_pack_status(system_id, component_id, _status, msg,  appmotorconfig->Motor_rated_current, appmotorconfig->Motor_rated_torque, appmotorconfig->Motor_peak_current, appmotorconfig->Motor_pole_pairs, appmotorconfig->Motor_maximum_speed, appmotorconfig->Resistance, appmotorconfig->Inductance, appmotorconfig->Reduction_ratio_num, appmotorconfig->Reduction_ratio_den, appmotorconfig->Torque_constant, appmotorconfig->Reduction_ratio, appmotorconfig->Reduction_ratio_inv, appmotorconfig->Motor_rotor_inertia);
}

/**
 * @brief Send a appmotorconfig message
 * @param chan MAVLink channel to send the message
 *
 * @param Motor_rated_current  
 * @param Motor_rated_torque  
 * @param Motor_peak_current  
 * @param Motor_pole_pairs  
 * @param Motor_maximum_speed  
 * @param Resistance  
 * @param Inductance  
 * @param Reduction_ratio_num  
 * @param Reduction_ratio_den  
 * @param Torque_constant  
 * @param Reduction_ratio  
 * @param Reduction_ratio_inv  
 * @param Motor_rotor_inertia  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_appmotorconfig_send(mavlink_channel_t chan, float Motor_rated_current, float Motor_rated_torque, float Motor_peak_current, float Motor_pole_pairs, float Motor_maximum_speed, float Resistance, float Inductance, uint32_t Reduction_ratio_num, uint32_t Reduction_ratio_den, float Torque_constant, float Reduction_ratio, float Reduction_ratio_inv, float Motor_rotor_inertia)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_AppMotorConfig_LEN];
    _mav_put_float(buf, 0, Motor_rated_current);
    _mav_put_float(buf, 4, Motor_rated_torque);
    _mav_put_float(buf, 8, Motor_peak_current);
    _mav_put_float(buf, 12, Motor_pole_pairs);
    _mav_put_float(buf, 16, Motor_maximum_speed);
    _mav_put_float(buf, 20, Resistance);
    _mav_put_float(buf, 24, Inductance);
    _mav_put_uint32_t(buf, 28, Reduction_ratio_num);
    _mav_put_uint32_t(buf, 32, Reduction_ratio_den);
    _mav_put_float(buf, 36, Torque_constant);
    _mav_put_float(buf, 40, Reduction_ratio);
    _mav_put_float(buf, 44, Reduction_ratio_inv);
    _mav_put_float(buf, 48, Motor_rotor_inertia);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppMotorConfig, buf, MAVLINK_MSG_ID_AppMotorConfig_MIN_LEN, MAVLINK_MSG_ID_AppMotorConfig_LEN, MAVLINK_MSG_ID_AppMotorConfig_CRC);
#else
    mavlink_appmotorconfig_t packet;
    packet.Motor_rated_current = Motor_rated_current;
    packet.Motor_rated_torque = Motor_rated_torque;
    packet.Motor_peak_current = Motor_peak_current;
    packet.Motor_pole_pairs = Motor_pole_pairs;
    packet.Motor_maximum_speed = Motor_maximum_speed;
    packet.Resistance = Resistance;
    packet.Inductance = Inductance;
    packet.Reduction_ratio_num = Reduction_ratio_num;
    packet.Reduction_ratio_den = Reduction_ratio_den;
    packet.Torque_constant = Torque_constant;
    packet.Reduction_ratio = Reduction_ratio;
    packet.Reduction_ratio_inv = Reduction_ratio_inv;
    packet.Motor_rotor_inertia = Motor_rotor_inertia;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppMotorConfig, (const char *)&packet, MAVLINK_MSG_ID_AppMotorConfig_MIN_LEN, MAVLINK_MSG_ID_AppMotorConfig_LEN, MAVLINK_MSG_ID_AppMotorConfig_CRC);
#endif
}

/**
 * @brief Send a appmotorconfig message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_appmotorconfig_send_struct(mavlink_channel_t chan, const mavlink_appmotorconfig_t* appmotorconfig)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_appmotorconfig_send(chan, appmotorconfig->Motor_rated_current, appmotorconfig->Motor_rated_torque, appmotorconfig->Motor_peak_current, appmotorconfig->Motor_pole_pairs, appmotorconfig->Motor_maximum_speed, appmotorconfig->Resistance, appmotorconfig->Inductance, appmotorconfig->Reduction_ratio_num, appmotorconfig->Reduction_ratio_den, appmotorconfig->Torque_constant, appmotorconfig->Reduction_ratio, appmotorconfig->Reduction_ratio_inv, appmotorconfig->Motor_rotor_inertia);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppMotorConfig, (const char *)appmotorconfig, MAVLINK_MSG_ID_AppMotorConfig_MIN_LEN, MAVLINK_MSG_ID_AppMotorConfig_LEN, MAVLINK_MSG_ID_AppMotorConfig_CRC);
#endif
}

#if MAVLINK_MSG_ID_AppMotorConfig_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_appmotorconfig_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float Motor_rated_current, float Motor_rated_torque, float Motor_peak_current, float Motor_pole_pairs, float Motor_maximum_speed, float Resistance, float Inductance, uint32_t Reduction_ratio_num, uint32_t Reduction_ratio_den, float Torque_constant, float Reduction_ratio, float Reduction_ratio_inv, float Motor_rotor_inertia)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, Motor_rated_current);
    _mav_put_float(buf, 4, Motor_rated_torque);
    _mav_put_float(buf, 8, Motor_peak_current);
    _mav_put_float(buf, 12, Motor_pole_pairs);
    _mav_put_float(buf, 16, Motor_maximum_speed);
    _mav_put_float(buf, 20, Resistance);
    _mav_put_float(buf, 24, Inductance);
    _mav_put_uint32_t(buf, 28, Reduction_ratio_num);
    _mav_put_uint32_t(buf, 32, Reduction_ratio_den);
    _mav_put_float(buf, 36, Torque_constant);
    _mav_put_float(buf, 40, Reduction_ratio);
    _mav_put_float(buf, 44, Reduction_ratio_inv);
    _mav_put_float(buf, 48, Motor_rotor_inertia);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppMotorConfig, buf, MAVLINK_MSG_ID_AppMotorConfig_MIN_LEN, MAVLINK_MSG_ID_AppMotorConfig_LEN, MAVLINK_MSG_ID_AppMotorConfig_CRC);
#else
    mavlink_appmotorconfig_t *packet = (mavlink_appmotorconfig_t *)msgbuf;
    packet->Motor_rated_current = Motor_rated_current;
    packet->Motor_rated_torque = Motor_rated_torque;
    packet->Motor_peak_current = Motor_peak_current;
    packet->Motor_pole_pairs = Motor_pole_pairs;
    packet->Motor_maximum_speed = Motor_maximum_speed;
    packet->Resistance = Resistance;
    packet->Inductance = Inductance;
    packet->Reduction_ratio_num = Reduction_ratio_num;
    packet->Reduction_ratio_den = Reduction_ratio_den;
    packet->Torque_constant = Torque_constant;
    packet->Reduction_ratio = Reduction_ratio;
    packet->Reduction_ratio_inv = Reduction_ratio_inv;
    packet->Motor_rotor_inertia = Motor_rotor_inertia;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppMotorConfig, (const char *)packet, MAVLINK_MSG_ID_AppMotorConfig_MIN_LEN, MAVLINK_MSG_ID_AppMotorConfig_LEN, MAVLINK_MSG_ID_AppMotorConfig_CRC);
#endif
}
#endif

#endif

// MESSAGE AppMotorConfig UNPACKING


/**
 * @brief Get field Motor_rated_current from appmotorconfig message
 *
 * @return  
 */
static inline float mavlink_msg_appmotorconfig_get_Motor_rated_current(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field Motor_rated_torque from appmotorconfig message
 *
 * @return  
 */
static inline float mavlink_msg_appmotorconfig_get_Motor_rated_torque(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field Motor_peak_current from appmotorconfig message
 *
 * @return  
 */
static inline float mavlink_msg_appmotorconfig_get_Motor_peak_current(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field Motor_pole_pairs from appmotorconfig message
 *
 * @return  
 */
static inline float mavlink_msg_appmotorconfig_get_Motor_pole_pairs(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Get field Motor_maximum_speed from appmotorconfig message
 *
 * @return  
 */
static inline float mavlink_msg_appmotorconfig_get_Motor_maximum_speed(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  16);
}

/**
 * @brief Get field Resistance from appmotorconfig message
 *
 * @return  
 */
static inline float mavlink_msg_appmotorconfig_get_Resistance(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  20);
}

/**
 * @brief Get field Inductance from appmotorconfig message
 *
 * @return  
 */
static inline float mavlink_msg_appmotorconfig_get_Inductance(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  24);
}

/**
 * @brief Get field Reduction_ratio_num from appmotorconfig message
 *
 * @return  
 */
static inline uint32_t mavlink_msg_appmotorconfig_get_Reduction_ratio_num(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  28);
}

/**
 * @brief Get field Reduction_ratio_den from appmotorconfig message
 *
 * @return  
 */
static inline uint32_t mavlink_msg_appmotorconfig_get_Reduction_ratio_den(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  32);
}

/**
 * @brief Get field Torque_constant from appmotorconfig message
 *
 * @return  
 */
static inline float mavlink_msg_appmotorconfig_get_Torque_constant(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  36);
}

/**
 * @brief Get field Reduction_ratio from appmotorconfig message
 *
 * @return  
 */
static inline float mavlink_msg_appmotorconfig_get_Reduction_ratio(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  40);
}

/**
 * @brief Get field Reduction_ratio_inv from appmotorconfig message
 *
 * @return  
 */
static inline float mavlink_msg_appmotorconfig_get_Reduction_ratio_inv(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  44);
}

/**
 * @brief Get field Motor_rotor_inertia from appmotorconfig message
 *
 * @return  
 */
static inline float mavlink_msg_appmotorconfig_get_Motor_rotor_inertia(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  48);
}

/**
 * @brief Decode a appmotorconfig message into a struct
 *
 * @param msg The message to decode
 * @param appmotorconfig C-struct to decode the message contents into
 */
static inline void mavlink_msg_appmotorconfig_decode(const mavlink_message_t* msg, mavlink_appmotorconfig_t* appmotorconfig)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    appmotorconfig->Motor_rated_current = mavlink_msg_appmotorconfig_get_Motor_rated_current(msg);
    appmotorconfig->Motor_rated_torque = mavlink_msg_appmotorconfig_get_Motor_rated_torque(msg);
    appmotorconfig->Motor_peak_current = mavlink_msg_appmotorconfig_get_Motor_peak_current(msg);
    appmotorconfig->Motor_pole_pairs = mavlink_msg_appmotorconfig_get_Motor_pole_pairs(msg);
    appmotorconfig->Motor_maximum_speed = mavlink_msg_appmotorconfig_get_Motor_maximum_speed(msg);
    appmotorconfig->Resistance = mavlink_msg_appmotorconfig_get_Resistance(msg);
    appmotorconfig->Inductance = mavlink_msg_appmotorconfig_get_Inductance(msg);
    appmotorconfig->Reduction_ratio_num = mavlink_msg_appmotorconfig_get_Reduction_ratio_num(msg);
    appmotorconfig->Reduction_ratio_den = mavlink_msg_appmotorconfig_get_Reduction_ratio_den(msg);
    appmotorconfig->Torque_constant = mavlink_msg_appmotorconfig_get_Torque_constant(msg);
    appmotorconfig->Reduction_ratio = mavlink_msg_appmotorconfig_get_Reduction_ratio(msg);
    appmotorconfig->Reduction_ratio_inv = mavlink_msg_appmotorconfig_get_Reduction_ratio_inv(msg);
    appmotorconfig->Motor_rotor_inertia = mavlink_msg_appmotorconfig_get_Motor_rotor_inertia(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_AppMotorConfig_LEN? msg->len : MAVLINK_MSG_ID_AppMotorConfig_LEN;
        memset(appmotorconfig, 0, MAVLINK_MSG_ID_AppMotorConfig_LEN);
    memcpy(appmotorconfig, _MAV_PAYLOAD(msg), len);
#endif
}
