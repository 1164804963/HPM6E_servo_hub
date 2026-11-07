#pragma once
// MESSAGE CurrentCtlConfig PACKING

#define MAVLINK_MSG_ID_CurrentCtlConfig 30026


typedef struct __mavlink_currentctlconfig_t {
 float i_noise_A; /*<  */
 float comp_du_V; /*<  */
 float bandwidth_percentage; /*<  */
 float dt_s; /*<  */
 float flux_wb; /*<  */
 float kp_ld; /*<  */
 float ki_ld; /*<  */
 float kp_lq; /*<  */
 float ki_lq; /*<  */
 float pwm_duty_cycle_max; /*<  */
 float elec_angle_compensation; /*<  */
 int8_t phase_dir; /*<  */
} mavlink_currentctlconfig_t;

#define MAVLINK_MSG_ID_CurrentCtlConfig_LEN 45
#define MAVLINK_MSG_ID_CurrentCtlConfig_MIN_LEN 45
#define MAVLINK_MSG_ID_30026_LEN 45
#define MAVLINK_MSG_ID_30026_MIN_LEN 45

#define MAVLINK_MSG_ID_CurrentCtlConfig_CRC 84
#define MAVLINK_MSG_ID_30026_CRC 84



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_CurrentCtlConfig { \
    30026, \
    "CurrentCtlConfig", \
    12, \
    {  { "i_noise_A", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_currentctlconfig_t, i_noise_A) }, \
         { "comp_du_V", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_currentctlconfig_t, comp_du_V) }, \
         { "bandwidth_percentage", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_currentctlconfig_t, bandwidth_percentage) }, \
         { "dt_s", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_currentctlconfig_t, dt_s) }, \
         { "flux_wb", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_currentctlconfig_t, flux_wb) }, \
         { "kp_ld", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_currentctlconfig_t, kp_ld) }, \
         { "ki_ld", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_currentctlconfig_t, ki_ld) }, \
         { "kp_lq", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_currentctlconfig_t, kp_lq) }, \
         { "ki_lq", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_currentctlconfig_t, ki_lq) }, \
         { "pwm_duty_cycle_max", NULL, MAVLINK_TYPE_FLOAT, 0, 36, offsetof(mavlink_currentctlconfig_t, pwm_duty_cycle_max) }, \
         { "elec_angle_compensation", NULL, MAVLINK_TYPE_FLOAT, 0, 40, offsetof(mavlink_currentctlconfig_t, elec_angle_compensation) }, \
         { "phase_dir", NULL, MAVLINK_TYPE_INT8_T, 0, 44, offsetof(mavlink_currentctlconfig_t, phase_dir) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_CurrentCtlConfig { \
    "CurrentCtlConfig", \
    12, \
    {  { "i_noise_A", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_currentctlconfig_t, i_noise_A) }, \
         { "comp_du_V", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_currentctlconfig_t, comp_du_V) }, \
         { "bandwidth_percentage", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_currentctlconfig_t, bandwidth_percentage) }, \
         { "dt_s", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_currentctlconfig_t, dt_s) }, \
         { "flux_wb", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_currentctlconfig_t, flux_wb) }, \
         { "kp_ld", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_currentctlconfig_t, kp_ld) }, \
         { "ki_ld", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_currentctlconfig_t, ki_ld) }, \
         { "kp_lq", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_currentctlconfig_t, kp_lq) }, \
         { "ki_lq", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_currentctlconfig_t, ki_lq) }, \
         { "pwm_duty_cycle_max", NULL, MAVLINK_TYPE_FLOAT, 0, 36, offsetof(mavlink_currentctlconfig_t, pwm_duty_cycle_max) }, \
         { "elec_angle_compensation", NULL, MAVLINK_TYPE_FLOAT, 0, 40, offsetof(mavlink_currentctlconfig_t, elec_angle_compensation) }, \
         { "phase_dir", NULL, MAVLINK_TYPE_INT8_T, 0, 44, offsetof(mavlink_currentctlconfig_t, phase_dir) }, \
         } \
}
#endif

/**
 * @brief Pack a currentctlconfig message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param i_noise_A  
 * @param comp_du_V  
 * @param bandwidth_percentage  
 * @param dt_s  
 * @param flux_wb  
 * @param kp_ld  
 * @param ki_ld  
 * @param kp_lq  
 * @param ki_lq  
 * @param pwm_duty_cycle_max  
 * @param elec_angle_compensation  
 * @param phase_dir  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_currentctlconfig_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               float i_noise_A, float comp_du_V, float bandwidth_percentage, float dt_s, float flux_wb, float kp_ld, float ki_ld, float kp_lq, float ki_lq, float pwm_duty_cycle_max, float elec_angle_compensation, int8_t phase_dir)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_CurrentCtlConfig_LEN];
    _mav_put_float(buf, 0, i_noise_A);
    _mav_put_float(buf, 4, comp_du_V);
    _mav_put_float(buf, 8, bandwidth_percentage);
    _mav_put_float(buf, 12, dt_s);
    _mav_put_float(buf, 16, flux_wb);
    _mav_put_float(buf, 20, kp_ld);
    _mav_put_float(buf, 24, ki_ld);
    _mav_put_float(buf, 28, kp_lq);
    _mav_put_float(buf, 32, ki_lq);
    _mav_put_float(buf, 36, pwm_duty_cycle_max);
    _mav_put_float(buf, 40, elec_angle_compensation);
    _mav_put_int8_t(buf, 44, phase_dir);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_CurrentCtlConfig_LEN);
#else
    mavlink_currentctlconfig_t packet;
    packet.i_noise_A = i_noise_A;
    packet.comp_du_V = comp_du_V;
    packet.bandwidth_percentage = bandwidth_percentage;
    packet.dt_s = dt_s;
    packet.flux_wb = flux_wb;
    packet.kp_ld = kp_ld;
    packet.ki_ld = ki_ld;
    packet.kp_lq = kp_lq;
    packet.ki_lq = ki_lq;
    packet.pwm_duty_cycle_max = pwm_duty_cycle_max;
    packet.elec_angle_compensation = elec_angle_compensation;
    packet.phase_dir = phase_dir;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_CurrentCtlConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_CurrentCtlConfig;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_CurrentCtlConfig_MIN_LEN, MAVLINK_MSG_ID_CurrentCtlConfig_LEN, MAVLINK_MSG_ID_CurrentCtlConfig_CRC);
}

/**
 * @brief Pack a currentctlconfig message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param i_noise_A  
 * @param comp_du_V  
 * @param bandwidth_percentage  
 * @param dt_s  
 * @param flux_wb  
 * @param kp_ld  
 * @param ki_ld  
 * @param kp_lq  
 * @param ki_lq  
 * @param pwm_duty_cycle_max  
 * @param elec_angle_compensation  
 * @param phase_dir  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_currentctlconfig_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               float i_noise_A, float comp_du_V, float bandwidth_percentage, float dt_s, float flux_wb, float kp_ld, float ki_ld, float kp_lq, float ki_lq, float pwm_duty_cycle_max, float elec_angle_compensation, int8_t phase_dir)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_CurrentCtlConfig_LEN];
    _mav_put_float(buf, 0, i_noise_A);
    _mav_put_float(buf, 4, comp_du_V);
    _mav_put_float(buf, 8, bandwidth_percentage);
    _mav_put_float(buf, 12, dt_s);
    _mav_put_float(buf, 16, flux_wb);
    _mav_put_float(buf, 20, kp_ld);
    _mav_put_float(buf, 24, ki_ld);
    _mav_put_float(buf, 28, kp_lq);
    _mav_put_float(buf, 32, ki_lq);
    _mav_put_float(buf, 36, pwm_duty_cycle_max);
    _mav_put_float(buf, 40, elec_angle_compensation);
    _mav_put_int8_t(buf, 44, phase_dir);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_CurrentCtlConfig_LEN);
#else
    mavlink_currentctlconfig_t packet;
    packet.i_noise_A = i_noise_A;
    packet.comp_du_V = comp_du_V;
    packet.bandwidth_percentage = bandwidth_percentage;
    packet.dt_s = dt_s;
    packet.flux_wb = flux_wb;
    packet.kp_ld = kp_ld;
    packet.ki_ld = ki_ld;
    packet.kp_lq = kp_lq;
    packet.ki_lq = ki_lq;
    packet.pwm_duty_cycle_max = pwm_duty_cycle_max;
    packet.elec_angle_compensation = elec_angle_compensation;
    packet.phase_dir = phase_dir;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_CurrentCtlConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_CurrentCtlConfig;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_CurrentCtlConfig_MIN_LEN, MAVLINK_MSG_ID_CurrentCtlConfig_LEN, MAVLINK_MSG_ID_CurrentCtlConfig_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_CurrentCtlConfig_MIN_LEN, MAVLINK_MSG_ID_CurrentCtlConfig_LEN);
#endif
}

/**
 * @brief Pack a currentctlconfig message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param i_noise_A  
 * @param comp_du_V  
 * @param bandwidth_percentage  
 * @param dt_s  
 * @param flux_wb  
 * @param kp_ld  
 * @param ki_ld  
 * @param kp_lq  
 * @param ki_lq  
 * @param pwm_duty_cycle_max  
 * @param elec_angle_compensation  
 * @param phase_dir  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_currentctlconfig_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   float i_noise_A,float comp_du_V,float bandwidth_percentage,float dt_s,float flux_wb,float kp_ld,float ki_ld,float kp_lq,float ki_lq,float pwm_duty_cycle_max,float elec_angle_compensation,int8_t phase_dir)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_CurrentCtlConfig_LEN];
    _mav_put_float(buf, 0, i_noise_A);
    _mav_put_float(buf, 4, comp_du_V);
    _mav_put_float(buf, 8, bandwidth_percentage);
    _mav_put_float(buf, 12, dt_s);
    _mav_put_float(buf, 16, flux_wb);
    _mav_put_float(buf, 20, kp_ld);
    _mav_put_float(buf, 24, ki_ld);
    _mav_put_float(buf, 28, kp_lq);
    _mav_put_float(buf, 32, ki_lq);
    _mav_put_float(buf, 36, pwm_duty_cycle_max);
    _mav_put_float(buf, 40, elec_angle_compensation);
    _mav_put_int8_t(buf, 44, phase_dir);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_CurrentCtlConfig_LEN);
#else
    mavlink_currentctlconfig_t packet;
    packet.i_noise_A = i_noise_A;
    packet.comp_du_V = comp_du_V;
    packet.bandwidth_percentage = bandwidth_percentage;
    packet.dt_s = dt_s;
    packet.flux_wb = flux_wb;
    packet.kp_ld = kp_ld;
    packet.ki_ld = ki_ld;
    packet.kp_lq = kp_lq;
    packet.ki_lq = ki_lq;
    packet.pwm_duty_cycle_max = pwm_duty_cycle_max;
    packet.elec_angle_compensation = elec_angle_compensation;
    packet.phase_dir = phase_dir;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_CurrentCtlConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_CurrentCtlConfig;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_CurrentCtlConfig_MIN_LEN, MAVLINK_MSG_ID_CurrentCtlConfig_LEN, MAVLINK_MSG_ID_CurrentCtlConfig_CRC);
}

/**
 * @brief Encode a currentctlconfig struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param currentctlconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_currentctlconfig_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_currentctlconfig_t* currentctlconfig)
{
    return mavlink_msg_currentctlconfig_pack(system_id, component_id, msg, currentctlconfig->i_noise_A, currentctlconfig->comp_du_V, currentctlconfig->bandwidth_percentage, currentctlconfig->dt_s, currentctlconfig->flux_wb, currentctlconfig->kp_ld, currentctlconfig->ki_ld, currentctlconfig->kp_lq, currentctlconfig->ki_lq, currentctlconfig->pwm_duty_cycle_max, currentctlconfig->elec_angle_compensation, currentctlconfig->phase_dir);
}

/**
 * @brief Encode a currentctlconfig struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param currentctlconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_currentctlconfig_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_currentctlconfig_t* currentctlconfig)
{
    return mavlink_msg_currentctlconfig_pack_chan(system_id, component_id, chan, msg, currentctlconfig->i_noise_A, currentctlconfig->comp_du_V, currentctlconfig->bandwidth_percentage, currentctlconfig->dt_s, currentctlconfig->flux_wb, currentctlconfig->kp_ld, currentctlconfig->ki_ld, currentctlconfig->kp_lq, currentctlconfig->ki_lq, currentctlconfig->pwm_duty_cycle_max, currentctlconfig->elec_angle_compensation, currentctlconfig->phase_dir);
}

/**
 * @brief Encode a currentctlconfig struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param currentctlconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_currentctlconfig_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_currentctlconfig_t* currentctlconfig)
{
    return mavlink_msg_currentctlconfig_pack_status(system_id, component_id, _status, msg,  currentctlconfig->i_noise_A, currentctlconfig->comp_du_V, currentctlconfig->bandwidth_percentage, currentctlconfig->dt_s, currentctlconfig->flux_wb, currentctlconfig->kp_ld, currentctlconfig->ki_ld, currentctlconfig->kp_lq, currentctlconfig->ki_lq, currentctlconfig->pwm_duty_cycle_max, currentctlconfig->elec_angle_compensation, currentctlconfig->phase_dir);
}

/**
 * @brief Send a currentctlconfig message
 * @param chan MAVLink channel to send the message
 *
 * @param i_noise_A  
 * @param comp_du_V  
 * @param bandwidth_percentage  
 * @param dt_s  
 * @param flux_wb  
 * @param kp_ld  
 * @param ki_ld  
 * @param kp_lq  
 * @param ki_lq  
 * @param pwm_duty_cycle_max  
 * @param elec_angle_compensation  
 * @param phase_dir  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_currentctlconfig_send(mavlink_channel_t chan, float i_noise_A, float comp_du_V, float bandwidth_percentage, float dt_s, float flux_wb, float kp_ld, float ki_ld, float kp_lq, float ki_lq, float pwm_duty_cycle_max, float elec_angle_compensation, int8_t phase_dir)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_CurrentCtlConfig_LEN];
    _mav_put_float(buf, 0, i_noise_A);
    _mav_put_float(buf, 4, comp_du_V);
    _mav_put_float(buf, 8, bandwidth_percentage);
    _mav_put_float(buf, 12, dt_s);
    _mav_put_float(buf, 16, flux_wb);
    _mav_put_float(buf, 20, kp_ld);
    _mav_put_float(buf, 24, ki_ld);
    _mav_put_float(buf, 28, kp_lq);
    _mav_put_float(buf, 32, ki_lq);
    _mav_put_float(buf, 36, pwm_duty_cycle_max);
    _mav_put_float(buf, 40, elec_angle_compensation);
    _mav_put_int8_t(buf, 44, phase_dir);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CurrentCtlConfig, buf, MAVLINK_MSG_ID_CurrentCtlConfig_MIN_LEN, MAVLINK_MSG_ID_CurrentCtlConfig_LEN, MAVLINK_MSG_ID_CurrentCtlConfig_CRC);
#else
    mavlink_currentctlconfig_t packet;
    packet.i_noise_A = i_noise_A;
    packet.comp_du_V = comp_du_V;
    packet.bandwidth_percentage = bandwidth_percentage;
    packet.dt_s = dt_s;
    packet.flux_wb = flux_wb;
    packet.kp_ld = kp_ld;
    packet.ki_ld = ki_ld;
    packet.kp_lq = kp_lq;
    packet.ki_lq = ki_lq;
    packet.pwm_duty_cycle_max = pwm_duty_cycle_max;
    packet.elec_angle_compensation = elec_angle_compensation;
    packet.phase_dir = phase_dir;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CurrentCtlConfig, (const char *)&packet, MAVLINK_MSG_ID_CurrentCtlConfig_MIN_LEN, MAVLINK_MSG_ID_CurrentCtlConfig_LEN, MAVLINK_MSG_ID_CurrentCtlConfig_CRC);
#endif
}

/**
 * @brief Send a currentctlconfig message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_currentctlconfig_send_struct(mavlink_channel_t chan, const mavlink_currentctlconfig_t* currentctlconfig)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_currentctlconfig_send(chan, currentctlconfig->i_noise_A, currentctlconfig->comp_du_V, currentctlconfig->bandwidth_percentage, currentctlconfig->dt_s, currentctlconfig->flux_wb, currentctlconfig->kp_ld, currentctlconfig->ki_ld, currentctlconfig->kp_lq, currentctlconfig->ki_lq, currentctlconfig->pwm_duty_cycle_max, currentctlconfig->elec_angle_compensation, currentctlconfig->phase_dir);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CurrentCtlConfig, (const char *)currentctlconfig, MAVLINK_MSG_ID_CurrentCtlConfig_MIN_LEN, MAVLINK_MSG_ID_CurrentCtlConfig_LEN, MAVLINK_MSG_ID_CurrentCtlConfig_CRC);
#endif
}

#if MAVLINK_MSG_ID_CurrentCtlConfig_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_currentctlconfig_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float i_noise_A, float comp_du_V, float bandwidth_percentage, float dt_s, float flux_wb, float kp_ld, float ki_ld, float kp_lq, float ki_lq, float pwm_duty_cycle_max, float elec_angle_compensation, int8_t phase_dir)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, i_noise_A);
    _mav_put_float(buf, 4, comp_du_V);
    _mav_put_float(buf, 8, bandwidth_percentage);
    _mav_put_float(buf, 12, dt_s);
    _mav_put_float(buf, 16, flux_wb);
    _mav_put_float(buf, 20, kp_ld);
    _mav_put_float(buf, 24, ki_ld);
    _mav_put_float(buf, 28, kp_lq);
    _mav_put_float(buf, 32, ki_lq);
    _mav_put_float(buf, 36, pwm_duty_cycle_max);
    _mav_put_float(buf, 40, elec_angle_compensation);
    _mav_put_int8_t(buf, 44, phase_dir);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CurrentCtlConfig, buf, MAVLINK_MSG_ID_CurrentCtlConfig_MIN_LEN, MAVLINK_MSG_ID_CurrentCtlConfig_LEN, MAVLINK_MSG_ID_CurrentCtlConfig_CRC);
#else
    mavlink_currentctlconfig_t *packet = (mavlink_currentctlconfig_t *)msgbuf;
    packet->i_noise_A = i_noise_A;
    packet->comp_du_V = comp_du_V;
    packet->bandwidth_percentage = bandwidth_percentage;
    packet->dt_s = dt_s;
    packet->flux_wb = flux_wb;
    packet->kp_ld = kp_ld;
    packet->ki_ld = ki_ld;
    packet->kp_lq = kp_lq;
    packet->ki_lq = ki_lq;
    packet->pwm_duty_cycle_max = pwm_duty_cycle_max;
    packet->elec_angle_compensation = elec_angle_compensation;
    packet->phase_dir = phase_dir;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CurrentCtlConfig, (const char *)packet, MAVLINK_MSG_ID_CurrentCtlConfig_MIN_LEN, MAVLINK_MSG_ID_CurrentCtlConfig_LEN, MAVLINK_MSG_ID_CurrentCtlConfig_CRC);
#endif
}
#endif

#endif

// MESSAGE CurrentCtlConfig UNPACKING


/**
 * @brief Get field i_noise_A from currentctlconfig message
 *
 * @return  
 */
static inline float mavlink_msg_currentctlconfig_get_i_noise_A(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field comp_du_V from currentctlconfig message
 *
 * @return  
 */
static inline float mavlink_msg_currentctlconfig_get_comp_du_V(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field bandwidth_percentage from currentctlconfig message
 *
 * @return  
 */
static inline float mavlink_msg_currentctlconfig_get_bandwidth_percentage(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field dt_s from currentctlconfig message
 *
 * @return  
 */
static inline float mavlink_msg_currentctlconfig_get_dt_s(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Get field flux_wb from currentctlconfig message
 *
 * @return  
 */
static inline float mavlink_msg_currentctlconfig_get_flux_wb(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  16);
}

/**
 * @brief Get field kp_ld from currentctlconfig message
 *
 * @return  
 */
static inline float mavlink_msg_currentctlconfig_get_kp_ld(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  20);
}

/**
 * @brief Get field ki_ld from currentctlconfig message
 *
 * @return  
 */
static inline float mavlink_msg_currentctlconfig_get_ki_ld(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  24);
}

/**
 * @brief Get field kp_lq from currentctlconfig message
 *
 * @return  
 */
static inline float mavlink_msg_currentctlconfig_get_kp_lq(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  28);
}

/**
 * @brief Get field ki_lq from currentctlconfig message
 *
 * @return  
 */
static inline float mavlink_msg_currentctlconfig_get_ki_lq(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  32);
}

/**
 * @brief Get field pwm_duty_cycle_max from currentctlconfig message
 *
 * @return  
 */
static inline float mavlink_msg_currentctlconfig_get_pwm_duty_cycle_max(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  36);
}

/**
 * @brief Get field elec_angle_compensation from currentctlconfig message
 *
 * @return  
 */
static inline float mavlink_msg_currentctlconfig_get_elec_angle_compensation(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  40);
}

/**
 * @brief Get field phase_dir from currentctlconfig message
 *
 * @return  
 */
static inline int8_t mavlink_msg_currentctlconfig_get_phase_dir(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int8_t(msg,  44);
}

/**
 * @brief Decode a currentctlconfig message into a struct
 *
 * @param msg The message to decode
 * @param currentctlconfig C-struct to decode the message contents into
 */
static inline void mavlink_msg_currentctlconfig_decode(const mavlink_message_t* msg, mavlink_currentctlconfig_t* currentctlconfig)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    currentctlconfig->i_noise_A = mavlink_msg_currentctlconfig_get_i_noise_A(msg);
    currentctlconfig->comp_du_V = mavlink_msg_currentctlconfig_get_comp_du_V(msg);
    currentctlconfig->bandwidth_percentage = mavlink_msg_currentctlconfig_get_bandwidth_percentage(msg);
    currentctlconfig->dt_s = mavlink_msg_currentctlconfig_get_dt_s(msg);
    currentctlconfig->flux_wb = mavlink_msg_currentctlconfig_get_flux_wb(msg);
    currentctlconfig->kp_ld = mavlink_msg_currentctlconfig_get_kp_ld(msg);
    currentctlconfig->ki_ld = mavlink_msg_currentctlconfig_get_ki_ld(msg);
    currentctlconfig->kp_lq = mavlink_msg_currentctlconfig_get_kp_lq(msg);
    currentctlconfig->ki_lq = mavlink_msg_currentctlconfig_get_ki_lq(msg);
    currentctlconfig->pwm_duty_cycle_max = mavlink_msg_currentctlconfig_get_pwm_duty_cycle_max(msg);
    currentctlconfig->elec_angle_compensation = mavlink_msg_currentctlconfig_get_elec_angle_compensation(msg);
    currentctlconfig->phase_dir = mavlink_msg_currentctlconfig_get_phase_dir(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_CurrentCtlConfig_LEN? msg->len : MAVLINK_MSG_ID_CurrentCtlConfig_LEN;
        memset(currentctlconfig, 0, MAVLINK_MSG_ID_CurrentCtlConfig_LEN);
    memcpy(currentctlconfig, _MAV_PAYLOAD(msg), len);
#endif
}
