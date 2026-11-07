#pragma once
// MESSAGE CurrentCtlInput PACKING

#define MAVLINK_MSG_ID_CurrentCtlInput 30025


typedef struct __mavlink_currentctlinput_t {
 float idq_tar_A[2]; /*<  */
 float iabc_now_A[3]; /*<  */
 float elec_theta_rad; /*<  */
 float dc_bus_now_V; /*<  */
 float uabc_tar_V[3]; /*<  */
 float driver_temp; /*<  */
 float elec_angle_speed_rad_s; /*<  */
 float iq_offset_A; /*<  */
 uint8_t mode; /*<  */
} mavlink_currentctlinput_t;

#define MAVLINK_MSG_ID_CurrentCtlInput_LEN 53
#define MAVLINK_MSG_ID_CurrentCtlInput_MIN_LEN 53
#define MAVLINK_MSG_ID_30025_LEN 53
#define MAVLINK_MSG_ID_30025_MIN_LEN 53

#define MAVLINK_MSG_ID_CurrentCtlInput_CRC 191
#define MAVLINK_MSG_ID_30025_CRC 191

#define MAVLINK_MSG_CurrentCtlInput_FIELD_IDQ_TAR_A_LEN 2
#define MAVLINK_MSG_CurrentCtlInput_FIELD_IABC_NOW_A_LEN 3
#define MAVLINK_MSG_CurrentCtlInput_FIELD_UABC_TAR_V_LEN 3

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_CurrentCtlInput { \
    30025, \
    "CurrentCtlInput", \
    9, \
    {  { "idq_tar_A", NULL, MAVLINK_TYPE_FLOAT, 2, 0, offsetof(mavlink_currentctlinput_t, idq_tar_A) }, \
         { "iabc_now_A", NULL, MAVLINK_TYPE_FLOAT, 3, 8, offsetof(mavlink_currentctlinput_t, iabc_now_A) }, \
         { "elec_theta_rad", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_currentctlinput_t, elec_theta_rad) }, \
         { "dc_bus_now_V", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_currentctlinput_t, dc_bus_now_V) }, \
         { "mode", NULL, MAVLINK_TYPE_UINT8_T, 0, 52, offsetof(mavlink_currentctlinput_t, mode) }, \
         { "uabc_tar_V", NULL, MAVLINK_TYPE_FLOAT, 3, 28, offsetof(mavlink_currentctlinput_t, uabc_tar_V) }, \
         { "driver_temp", NULL, MAVLINK_TYPE_FLOAT, 0, 40, offsetof(mavlink_currentctlinput_t, driver_temp) }, \
         { "elec_angle_speed_rad_s", NULL, MAVLINK_TYPE_FLOAT, 0, 44, offsetof(mavlink_currentctlinput_t, elec_angle_speed_rad_s) }, \
         { "iq_offset_A", NULL, MAVLINK_TYPE_FLOAT, 0, 48, offsetof(mavlink_currentctlinput_t, iq_offset_A) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_CurrentCtlInput { \
    "CurrentCtlInput", \
    9, \
    {  { "idq_tar_A", NULL, MAVLINK_TYPE_FLOAT, 2, 0, offsetof(mavlink_currentctlinput_t, idq_tar_A) }, \
         { "iabc_now_A", NULL, MAVLINK_TYPE_FLOAT, 3, 8, offsetof(mavlink_currentctlinput_t, iabc_now_A) }, \
         { "elec_theta_rad", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_currentctlinput_t, elec_theta_rad) }, \
         { "dc_bus_now_V", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_currentctlinput_t, dc_bus_now_V) }, \
         { "mode", NULL, MAVLINK_TYPE_UINT8_T, 0, 52, offsetof(mavlink_currentctlinput_t, mode) }, \
         { "uabc_tar_V", NULL, MAVLINK_TYPE_FLOAT, 3, 28, offsetof(mavlink_currentctlinput_t, uabc_tar_V) }, \
         { "driver_temp", NULL, MAVLINK_TYPE_FLOAT, 0, 40, offsetof(mavlink_currentctlinput_t, driver_temp) }, \
         { "elec_angle_speed_rad_s", NULL, MAVLINK_TYPE_FLOAT, 0, 44, offsetof(mavlink_currentctlinput_t, elec_angle_speed_rad_s) }, \
         { "iq_offset_A", NULL, MAVLINK_TYPE_FLOAT, 0, 48, offsetof(mavlink_currentctlinput_t, iq_offset_A) }, \
         } \
}
#endif

/**
 * @brief Pack a currentctlinput message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param idq_tar_A  
 * @param iabc_now_A  
 * @param elec_theta_rad  
 * @param dc_bus_now_V  
 * @param mode  
 * @param uabc_tar_V  
 * @param driver_temp  
 * @param elec_angle_speed_rad_s  
 * @param iq_offset_A  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_currentctlinput_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               const float *idq_tar_A, const float *iabc_now_A, float elec_theta_rad, float dc_bus_now_V, uint8_t mode, const float *uabc_tar_V, float driver_temp, float elec_angle_speed_rad_s, float iq_offset_A)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_CurrentCtlInput_LEN];
    _mav_put_float(buf, 20, elec_theta_rad);
    _mav_put_float(buf, 24, dc_bus_now_V);
    _mav_put_float(buf, 40, driver_temp);
    _mav_put_float(buf, 44, elec_angle_speed_rad_s);
    _mav_put_float(buf, 48, iq_offset_A);
    _mav_put_uint8_t(buf, 52, mode);
    _mav_put_float_array(buf, 0, idq_tar_A, 2);
    _mav_put_float_array(buf, 8, iabc_now_A, 3);
    _mav_put_float_array(buf, 28, uabc_tar_V, 3);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_CurrentCtlInput_LEN);
#else
    mavlink_currentctlinput_t packet;
    packet.elec_theta_rad = elec_theta_rad;
    packet.dc_bus_now_V = dc_bus_now_V;
    packet.driver_temp = driver_temp;
    packet.elec_angle_speed_rad_s = elec_angle_speed_rad_s;
    packet.iq_offset_A = iq_offset_A;
    packet.mode = mode;
    mav_array_memcpy(packet.idq_tar_A, idq_tar_A, sizeof(float)*2);
    mav_array_memcpy(packet.iabc_now_A, iabc_now_A, sizeof(float)*3);
    mav_array_memcpy(packet.uabc_tar_V, uabc_tar_V, sizeof(float)*3);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_CurrentCtlInput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_CurrentCtlInput;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_CurrentCtlInput_MIN_LEN, MAVLINK_MSG_ID_CurrentCtlInput_LEN, MAVLINK_MSG_ID_CurrentCtlInput_CRC);
}

/**
 * @brief Pack a currentctlinput message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param idq_tar_A  
 * @param iabc_now_A  
 * @param elec_theta_rad  
 * @param dc_bus_now_V  
 * @param mode  
 * @param uabc_tar_V  
 * @param driver_temp  
 * @param elec_angle_speed_rad_s  
 * @param iq_offset_A  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_currentctlinput_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               const float *idq_tar_A, const float *iabc_now_A, float elec_theta_rad, float dc_bus_now_V, uint8_t mode, const float *uabc_tar_V, float driver_temp, float elec_angle_speed_rad_s, float iq_offset_A)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_CurrentCtlInput_LEN];
    _mav_put_float(buf, 20, elec_theta_rad);
    _mav_put_float(buf, 24, dc_bus_now_V);
    _mav_put_float(buf, 40, driver_temp);
    _mav_put_float(buf, 44, elec_angle_speed_rad_s);
    _mav_put_float(buf, 48, iq_offset_A);
    _mav_put_uint8_t(buf, 52, mode);
    _mav_put_float_array(buf, 0, idq_tar_A, 2);
    _mav_put_float_array(buf, 8, iabc_now_A, 3);
    _mav_put_float_array(buf, 28, uabc_tar_V, 3);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_CurrentCtlInput_LEN);
#else
    mavlink_currentctlinput_t packet;
    packet.elec_theta_rad = elec_theta_rad;
    packet.dc_bus_now_V = dc_bus_now_V;
    packet.driver_temp = driver_temp;
    packet.elec_angle_speed_rad_s = elec_angle_speed_rad_s;
    packet.iq_offset_A = iq_offset_A;
    packet.mode = mode;
    mav_array_memcpy(packet.idq_tar_A, idq_tar_A, sizeof(float)*2);
    mav_array_memcpy(packet.iabc_now_A, iabc_now_A, sizeof(float)*3);
    mav_array_memcpy(packet.uabc_tar_V, uabc_tar_V, sizeof(float)*3);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_CurrentCtlInput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_CurrentCtlInput;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_CurrentCtlInput_MIN_LEN, MAVLINK_MSG_ID_CurrentCtlInput_LEN, MAVLINK_MSG_ID_CurrentCtlInput_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_CurrentCtlInput_MIN_LEN, MAVLINK_MSG_ID_CurrentCtlInput_LEN);
#endif
}

/**
 * @brief Pack a currentctlinput message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param idq_tar_A  
 * @param iabc_now_A  
 * @param elec_theta_rad  
 * @param dc_bus_now_V  
 * @param mode  
 * @param uabc_tar_V  
 * @param driver_temp  
 * @param elec_angle_speed_rad_s  
 * @param iq_offset_A  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_currentctlinput_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   const float *idq_tar_A,const float *iabc_now_A,float elec_theta_rad,float dc_bus_now_V,uint8_t mode,const float *uabc_tar_V,float driver_temp,float elec_angle_speed_rad_s,float iq_offset_A)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_CurrentCtlInput_LEN];
    _mav_put_float(buf, 20, elec_theta_rad);
    _mav_put_float(buf, 24, dc_bus_now_V);
    _mav_put_float(buf, 40, driver_temp);
    _mav_put_float(buf, 44, elec_angle_speed_rad_s);
    _mav_put_float(buf, 48, iq_offset_A);
    _mav_put_uint8_t(buf, 52, mode);
    _mav_put_float_array(buf, 0, idq_tar_A, 2);
    _mav_put_float_array(buf, 8, iabc_now_A, 3);
    _mav_put_float_array(buf, 28, uabc_tar_V, 3);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_CurrentCtlInput_LEN);
#else
    mavlink_currentctlinput_t packet;
    packet.elec_theta_rad = elec_theta_rad;
    packet.dc_bus_now_V = dc_bus_now_V;
    packet.driver_temp = driver_temp;
    packet.elec_angle_speed_rad_s = elec_angle_speed_rad_s;
    packet.iq_offset_A = iq_offset_A;
    packet.mode = mode;
    mav_array_memcpy(packet.idq_tar_A, idq_tar_A, sizeof(float)*2);
    mav_array_memcpy(packet.iabc_now_A, iabc_now_A, sizeof(float)*3);
    mav_array_memcpy(packet.uabc_tar_V, uabc_tar_V, sizeof(float)*3);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_CurrentCtlInput_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_CurrentCtlInput;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_CurrentCtlInput_MIN_LEN, MAVLINK_MSG_ID_CurrentCtlInput_LEN, MAVLINK_MSG_ID_CurrentCtlInput_CRC);
}

/**
 * @brief Encode a currentctlinput struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param currentctlinput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_currentctlinput_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_currentctlinput_t* currentctlinput)
{
    return mavlink_msg_currentctlinput_pack(system_id, component_id, msg, currentctlinput->idq_tar_A, currentctlinput->iabc_now_A, currentctlinput->elec_theta_rad, currentctlinput->dc_bus_now_V, currentctlinput->mode, currentctlinput->uabc_tar_V, currentctlinput->driver_temp, currentctlinput->elec_angle_speed_rad_s, currentctlinput->iq_offset_A);
}

/**
 * @brief Encode a currentctlinput struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param currentctlinput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_currentctlinput_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_currentctlinput_t* currentctlinput)
{
    return mavlink_msg_currentctlinput_pack_chan(system_id, component_id, chan, msg, currentctlinput->idq_tar_A, currentctlinput->iabc_now_A, currentctlinput->elec_theta_rad, currentctlinput->dc_bus_now_V, currentctlinput->mode, currentctlinput->uabc_tar_V, currentctlinput->driver_temp, currentctlinput->elec_angle_speed_rad_s, currentctlinput->iq_offset_A);
}

/**
 * @brief Encode a currentctlinput struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param currentctlinput C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_currentctlinput_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_currentctlinput_t* currentctlinput)
{
    return mavlink_msg_currentctlinput_pack_status(system_id, component_id, _status, msg,  currentctlinput->idq_tar_A, currentctlinput->iabc_now_A, currentctlinput->elec_theta_rad, currentctlinput->dc_bus_now_V, currentctlinput->mode, currentctlinput->uabc_tar_V, currentctlinput->driver_temp, currentctlinput->elec_angle_speed_rad_s, currentctlinput->iq_offset_A);
}

/**
 * @brief Send a currentctlinput message
 * @param chan MAVLink channel to send the message
 *
 * @param idq_tar_A  
 * @param iabc_now_A  
 * @param elec_theta_rad  
 * @param dc_bus_now_V  
 * @param mode  
 * @param uabc_tar_V  
 * @param driver_temp  
 * @param elec_angle_speed_rad_s  
 * @param iq_offset_A  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_currentctlinput_send(mavlink_channel_t chan, const float *idq_tar_A, const float *iabc_now_A, float elec_theta_rad, float dc_bus_now_V, uint8_t mode, const float *uabc_tar_V, float driver_temp, float elec_angle_speed_rad_s, float iq_offset_A)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_CurrentCtlInput_LEN];
    _mav_put_float(buf, 20, elec_theta_rad);
    _mav_put_float(buf, 24, dc_bus_now_V);
    _mav_put_float(buf, 40, driver_temp);
    _mav_put_float(buf, 44, elec_angle_speed_rad_s);
    _mav_put_float(buf, 48, iq_offset_A);
    _mav_put_uint8_t(buf, 52, mode);
    _mav_put_float_array(buf, 0, idq_tar_A, 2);
    _mav_put_float_array(buf, 8, iabc_now_A, 3);
    _mav_put_float_array(buf, 28, uabc_tar_V, 3);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CurrentCtlInput, buf, MAVLINK_MSG_ID_CurrentCtlInput_MIN_LEN, MAVLINK_MSG_ID_CurrentCtlInput_LEN, MAVLINK_MSG_ID_CurrentCtlInput_CRC);
#else
    mavlink_currentctlinput_t packet;
    packet.elec_theta_rad = elec_theta_rad;
    packet.dc_bus_now_V = dc_bus_now_V;
    packet.driver_temp = driver_temp;
    packet.elec_angle_speed_rad_s = elec_angle_speed_rad_s;
    packet.iq_offset_A = iq_offset_A;
    packet.mode = mode;
    mav_array_memcpy(packet.idq_tar_A, idq_tar_A, sizeof(float)*2);
    mav_array_memcpy(packet.iabc_now_A, iabc_now_A, sizeof(float)*3);
    mav_array_memcpy(packet.uabc_tar_V, uabc_tar_V, sizeof(float)*3);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CurrentCtlInput, (const char *)&packet, MAVLINK_MSG_ID_CurrentCtlInput_MIN_LEN, MAVLINK_MSG_ID_CurrentCtlInput_LEN, MAVLINK_MSG_ID_CurrentCtlInput_CRC);
#endif
}

/**
 * @brief Send a currentctlinput message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_currentctlinput_send_struct(mavlink_channel_t chan, const mavlink_currentctlinput_t* currentctlinput)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_currentctlinput_send(chan, currentctlinput->idq_tar_A, currentctlinput->iabc_now_A, currentctlinput->elec_theta_rad, currentctlinput->dc_bus_now_V, currentctlinput->mode, currentctlinput->uabc_tar_V, currentctlinput->driver_temp, currentctlinput->elec_angle_speed_rad_s, currentctlinput->iq_offset_A);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CurrentCtlInput, (const char *)currentctlinput, MAVLINK_MSG_ID_CurrentCtlInput_MIN_LEN, MAVLINK_MSG_ID_CurrentCtlInput_LEN, MAVLINK_MSG_ID_CurrentCtlInput_CRC);
#endif
}

#if MAVLINK_MSG_ID_CurrentCtlInput_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_currentctlinput_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  const float *idq_tar_A, const float *iabc_now_A, float elec_theta_rad, float dc_bus_now_V, uint8_t mode, const float *uabc_tar_V, float driver_temp, float elec_angle_speed_rad_s, float iq_offset_A)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 20, elec_theta_rad);
    _mav_put_float(buf, 24, dc_bus_now_V);
    _mav_put_float(buf, 40, driver_temp);
    _mav_put_float(buf, 44, elec_angle_speed_rad_s);
    _mav_put_float(buf, 48, iq_offset_A);
    _mav_put_uint8_t(buf, 52, mode);
    _mav_put_float_array(buf, 0, idq_tar_A, 2);
    _mav_put_float_array(buf, 8, iabc_now_A, 3);
    _mav_put_float_array(buf, 28, uabc_tar_V, 3);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CurrentCtlInput, buf, MAVLINK_MSG_ID_CurrentCtlInput_MIN_LEN, MAVLINK_MSG_ID_CurrentCtlInput_LEN, MAVLINK_MSG_ID_CurrentCtlInput_CRC);
#else
    mavlink_currentctlinput_t *packet = (mavlink_currentctlinput_t *)msgbuf;
    packet->elec_theta_rad = elec_theta_rad;
    packet->dc_bus_now_V = dc_bus_now_V;
    packet->driver_temp = driver_temp;
    packet->elec_angle_speed_rad_s = elec_angle_speed_rad_s;
    packet->iq_offset_A = iq_offset_A;
    packet->mode = mode;
    mav_array_memcpy(packet->idq_tar_A, idq_tar_A, sizeof(float)*2);
    mav_array_memcpy(packet->iabc_now_A, iabc_now_A, sizeof(float)*3);
    mav_array_memcpy(packet->uabc_tar_V, uabc_tar_V, sizeof(float)*3);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CurrentCtlInput, (const char *)packet, MAVLINK_MSG_ID_CurrentCtlInput_MIN_LEN, MAVLINK_MSG_ID_CurrentCtlInput_LEN, MAVLINK_MSG_ID_CurrentCtlInput_CRC);
#endif
}
#endif

#endif

// MESSAGE CurrentCtlInput UNPACKING


/**
 * @brief Get field idq_tar_A from currentctlinput message
 *
 * @return  
 */
static inline uint16_t mavlink_msg_currentctlinput_get_idq_tar_A(const mavlink_message_t* msg, float *idq_tar_A)
{
    return _MAV_RETURN_float_array(msg, idq_tar_A, 2,  0);
}

/**
 * @brief Get field iabc_now_A from currentctlinput message
 *
 * @return  
 */
static inline uint16_t mavlink_msg_currentctlinput_get_iabc_now_A(const mavlink_message_t* msg, float *iabc_now_A)
{
    return _MAV_RETURN_float_array(msg, iabc_now_A, 3,  8);
}

/**
 * @brief Get field elec_theta_rad from currentctlinput message
 *
 * @return  
 */
static inline float mavlink_msg_currentctlinput_get_elec_theta_rad(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  20);
}

/**
 * @brief Get field dc_bus_now_V from currentctlinput message
 *
 * @return  
 */
static inline float mavlink_msg_currentctlinput_get_dc_bus_now_V(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  24);
}

/**
 * @brief Get field mode from currentctlinput message
 *
 * @return  
 */
static inline uint8_t mavlink_msg_currentctlinput_get_mode(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  52);
}

/**
 * @brief Get field uabc_tar_V from currentctlinput message
 *
 * @return  
 */
static inline uint16_t mavlink_msg_currentctlinput_get_uabc_tar_V(const mavlink_message_t* msg, float *uabc_tar_V)
{
    return _MAV_RETURN_float_array(msg, uabc_tar_V, 3,  28);
}

/**
 * @brief Get field driver_temp from currentctlinput message
 *
 * @return  
 */
static inline float mavlink_msg_currentctlinput_get_driver_temp(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  40);
}

/**
 * @brief Get field elec_angle_speed_rad_s from currentctlinput message
 *
 * @return  
 */
static inline float mavlink_msg_currentctlinput_get_elec_angle_speed_rad_s(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  44);
}

/**
 * @brief Get field iq_offset_A from currentctlinput message
 *
 * @return  
 */
static inline float mavlink_msg_currentctlinput_get_iq_offset_A(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  48);
}

/**
 * @brief Decode a currentctlinput message into a struct
 *
 * @param msg The message to decode
 * @param currentctlinput C-struct to decode the message contents into
 */
static inline void mavlink_msg_currentctlinput_decode(const mavlink_message_t* msg, mavlink_currentctlinput_t* currentctlinput)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_currentctlinput_get_idq_tar_A(msg, currentctlinput->idq_tar_A);
    mavlink_msg_currentctlinput_get_iabc_now_A(msg, currentctlinput->iabc_now_A);
    currentctlinput->elec_theta_rad = mavlink_msg_currentctlinput_get_elec_theta_rad(msg);
    currentctlinput->dc_bus_now_V = mavlink_msg_currentctlinput_get_dc_bus_now_V(msg);
    mavlink_msg_currentctlinput_get_uabc_tar_V(msg, currentctlinput->uabc_tar_V);
    currentctlinput->driver_temp = mavlink_msg_currentctlinput_get_driver_temp(msg);
    currentctlinput->elec_angle_speed_rad_s = mavlink_msg_currentctlinput_get_elec_angle_speed_rad_s(msg);
    currentctlinput->iq_offset_A = mavlink_msg_currentctlinput_get_iq_offset_A(msg);
    currentctlinput->mode = mavlink_msg_currentctlinput_get_mode(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_CurrentCtlInput_LEN? msg->len : MAVLINK_MSG_ID_CurrentCtlInput_LEN;
        memset(currentctlinput, 0, MAVLINK_MSG_ID_CurrentCtlInput_LEN);
    memcpy(currentctlinput, _MAV_PAYLOAD(msg), len);
#endif
}
