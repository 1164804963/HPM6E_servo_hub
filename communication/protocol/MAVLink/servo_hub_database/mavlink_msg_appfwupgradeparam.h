#pragma once
// MESSAGE AppFwUpgradeParam PACKING

#define MAVLINK_MSG_ID_AppFwUpgradeParam 30087


typedef struct __mavlink_appfwupgradeparam_t {
 uint32_t Fw_flash_size; /*<  */
 uint8_t Fw_mode; /*<  */
 uint8_t Fw_app_index; /*<  */
 int8_t Fw_operating_steps; /*<  */
} mavlink_appfwupgradeparam_t;

#define MAVLINK_MSG_ID_AppFwUpgradeParam_LEN 7
#define MAVLINK_MSG_ID_AppFwUpgradeParam_MIN_LEN 7
#define MAVLINK_MSG_ID_30087_LEN 7
#define MAVLINK_MSG_ID_30087_MIN_LEN 7

#define MAVLINK_MSG_ID_AppFwUpgradeParam_CRC 158
#define MAVLINK_MSG_ID_30087_CRC 158



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_AppFwUpgradeParam { \
    30087, \
    "AppFwUpgradeParam", \
    4, \
    {  { "Fw_mode", NULL, MAVLINK_TYPE_UINT8_T, 0, 4, offsetof(mavlink_appfwupgradeparam_t, Fw_mode) }, \
         { "Fw_app_index", NULL, MAVLINK_TYPE_UINT8_T, 0, 5, offsetof(mavlink_appfwupgradeparam_t, Fw_app_index) }, \
         { "Fw_flash_size", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_appfwupgradeparam_t, Fw_flash_size) }, \
         { "Fw_operating_steps", NULL, MAVLINK_TYPE_INT8_T, 0, 6, offsetof(mavlink_appfwupgradeparam_t, Fw_operating_steps) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_AppFwUpgradeParam { \
    "AppFwUpgradeParam", \
    4, \
    {  { "Fw_mode", NULL, MAVLINK_TYPE_UINT8_T, 0, 4, offsetof(mavlink_appfwupgradeparam_t, Fw_mode) }, \
         { "Fw_app_index", NULL, MAVLINK_TYPE_UINT8_T, 0, 5, offsetof(mavlink_appfwupgradeparam_t, Fw_app_index) }, \
         { "Fw_flash_size", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_appfwupgradeparam_t, Fw_flash_size) }, \
         { "Fw_operating_steps", NULL, MAVLINK_TYPE_INT8_T, 0, 6, offsetof(mavlink_appfwupgradeparam_t, Fw_operating_steps) }, \
         } \
}
#endif

/**
 * @brief Pack a appfwupgradeparam message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param Fw_mode  
 * @param Fw_app_index  
 * @param Fw_flash_size  
 * @param Fw_operating_steps  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_appfwupgradeparam_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t Fw_mode, uint8_t Fw_app_index, uint32_t Fw_flash_size, int8_t Fw_operating_steps)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_AppFwUpgradeParam_LEN];
    _mav_put_uint32_t(buf, 0, Fw_flash_size);
    _mav_put_uint8_t(buf, 4, Fw_mode);
    _mav_put_uint8_t(buf, 5, Fw_app_index);
    _mav_put_int8_t(buf, 6, Fw_operating_steps);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_AppFwUpgradeParam_LEN);
#else
    mavlink_appfwupgradeparam_t packet;
    packet.Fw_flash_size = Fw_flash_size;
    packet.Fw_mode = Fw_mode;
    packet.Fw_app_index = Fw_app_index;
    packet.Fw_operating_steps = Fw_operating_steps;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_AppFwUpgradeParam_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_AppFwUpgradeParam;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_AppFwUpgradeParam_MIN_LEN, MAVLINK_MSG_ID_AppFwUpgradeParam_LEN, MAVLINK_MSG_ID_AppFwUpgradeParam_CRC);
}

/**
 * @brief Pack a appfwupgradeparam message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param Fw_mode  
 * @param Fw_app_index  
 * @param Fw_flash_size  
 * @param Fw_operating_steps  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_appfwupgradeparam_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint8_t Fw_mode, uint8_t Fw_app_index, uint32_t Fw_flash_size, int8_t Fw_operating_steps)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_AppFwUpgradeParam_LEN];
    _mav_put_uint32_t(buf, 0, Fw_flash_size);
    _mav_put_uint8_t(buf, 4, Fw_mode);
    _mav_put_uint8_t(buf, 5, Fw_app_index);
    _mav_put_int8_t(buf, 6, Fw_operating_steps);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_AppFwUpgradeParam_LEN);
#else
    mavlink_appfwupgradeparam_t packet;
    packet.Fw_flash_size = Fw_flash_size;
    packet.Fw_mode = Fw_mode;
    packet.Fw_app_index = Fw_app_index;
    packet.Fw_operating_steps = Fw_operating_steps;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_AppFwUpgradeParam_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_AppFwUpgradeParam;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_AppFwUpgradeParam_MIN_LEN, MAVLINK_MSG_ID_AppFwUpgradeParam_LEN, MAVLINK_MSG_ID_AppFwUpgradeParam_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_AppFwUpgradeParam_MIN_LEN, MAVLINK_MSG_ID_AppFwUpgradeParam_LEN);
#endif
}

/**
 * @brief Pack a appfwupgradeparam message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param Fw_mode  
 * @param Fw_app_index  
 * @param Fw_flash_size  
 * @param Fw_operating_steps  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_appfwupgradeparam_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t Fw_mode,uint8_t Fw_app_index,uint32_t Fw_flash_size,int8_t Fw_operating_steps)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_AppFwUpgradeParam_LEN];
    _mav_put_uint32_t(buf, 0, Fw_flash_size);
    _mav_put_uint8_t(buf, 4, Fw_mode);
    _mav_put_uint8_t(buf, 5, Fw_app_index);
    _mav_put_int8_t(buf, 6, Fw_operating_steps);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_AppFwUpgradeParam_LEN);
#else
    mavlink_appfwupgradeparam_t packet;
    packet.Fw_flash_size = Fw_flash_size;
    packet.Fw_mode = Fw_mode;
    packet.Fw_app_index = Fw_app_index;
    packet.Fw_operating_steps = Fw_operating_steps;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_AppFwUpgradeParam_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_AppFwUpgradeParam;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_AppFwUpgradeParam_MIN_LEN, MAVLINK_MSG_ID_AppFwUpgradeParam_LEN, MAVLINK_MSG_ID_AppFwUpgradeParam_CRC);
}

/**
 * @brief Encode a appfwupgradeparam struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param appfwupgradeparam C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_appfwupgradeparam_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_appfwupgradeparam_t* appfwupgradeparam)
{
    return mavlink_msg_appfwupgradeparam_pack(system_id, component_id, msg, appfwupgradeparam->Fw_mode, appfwupgradeparam->Fw_app_index, appfwupgradeparam->Fw_flash_size, appfwupgradeparam->Fw_operating_steps);
}

/**
 * @brief Encode a appfwupgradeparam struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param appfwupgradeparam C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_appfwupgradeparam_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_appfwupgradeparam_t* appfwupgradeparam)
{
    return mavlink_msg_appfwupgradeparam_pack_chan(system_id, component_id, chan, msg, appfwupgradeparam->Fw_mode, appfwupgradeparam->Fw_app_index, appfwupgradeparam->Fw_flash_size, appfwupgradeparam->Fw_operating_steps);
}

/**
 * @brief Encode a appfwupgradeparam struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param appfwupgradeparam C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_appfwupgradeparam_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_appfwupgradeparam_t* appfwupgradeparam)
{
    return mavlink_msg_appfwupgradeparam_pack_status(system_id, component_id, _status, msg,  appfwupgradeparam->Fw_mode, appfwupgradeparam->Fw_app_index, appfwupgradeparam->Fw_flash_size, appfwupgradeparam->Fw_operating_steps);
}

/**
 * @brief Send a appfwupgradeparam message
 * @param chan MAVLink channel to send the message
 *
 * @param Fw_mode  
 * @param Fw_app_index  
 * @param Fw_flash_size  
 * @param Fw_operating_steps  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_appfwupgradeparam_send(mavlink_channel_t chan, uint8_t Fw_mode, uint8_t Fw_app_index, uint32_t Fw_flash_size, int8_t Fw_operating_steps)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_AppFwUpgradeParam_LEN];
    _mav_put_uint32_t(buf, 0, Fw_flash_size);
    _mav_put_uint8_t(buf, 4, Fw_mode);
    _mav_put_uint8_t(buf, 5, Fw_app_index);
    _mav_put_int8_t(buf, 6, Fw_operating_steps);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppFwUpgradeParam, buf, MAVLINK_MSG_ID_AppFwUpgradeParam_MIN_LEN, MAVLINK_MSG_ID_AppFwUpgradeParam_LEN, MAVLINK_MSG_ID_AppFwUpgradeParam_CRC);
#else
    mavlink_appfwupgradeparam_t packet;
    packet.Fw_flash_size = Fw_flash_size;
    packet.Fw_mode = Fw_mode;
    packet.Fw_app_index = Fw_app_index;
    packet.Fw_operating_steps = Fw_operating_steps;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppFwUpgradeParam, (const char *)&packet, MAVLINK_MSG_ID_AppFwUpgradeParam_MIN_LEN, MAVLINK_MSG_ID_AppFwUpgradeParam_LEN, MAVLINK_MSG_ID_AppFwUpgradeParam_CRC);
#endif
}

/**
 * @brief Send a appfwupgradeparam message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_appfwupgradeparam_send_struct(mavlink_channel_t chan, const mavlink_appfwupgradeparam_t* appfwupgradeparam)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_appfwupgradeparam_send(chan, appfwupgradeparam->Fw_mode, appfwupgradeparam->Fw_app_index, appfwupgradeparam->Fw_flash_size, appfwupgradeparam->Fw_operating_steps);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppFwUpgradeParam, (const char *)appfwupgradeparam, MAVLINK_MSG_ID_AppFwUpgradeParam_MIN_LEN, MAVLINK_MSG_ID_AppFwUpgradeParam_LEN, MAVLINK_MSG_ID_AppFwUpgradeParam_CRC);
#endif
}

#if MAVLINK_MSG_ID_AppFwUpgradeParam_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_appfwupgradeparam_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t Fw_mode, uint8_t Fw_app_index, uint32_t Fw_flash_size, int8_t Fw_operating_steps)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint32_t(buf, 0, Fw_flash_size);
    _mav_put_uint8_t(buf, 4, Fw_mode);
    _mav_put_uint8_t(buf, 5, Fw_app_index);
    _mav_put_int8_t(buf, 6, Fw_operating_steps);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppFwUpgradeParam, buf, MAVLINK_MSG_ID_AppFwUpgradeParam_MIN_LEN, MAVLINK_MSG_ID_AppFwUpgradeParam_LEN, MAVLINK_MSG_ID_AppFwUpgradeParam_CRC);
#else
    mavlink_appfwupgradeparam_t *packet = (mavlink_appfwupgradeparam_t *)msgbuf;
    packet->Fw_flash_size = Fw_flash_size;
    packet->Fw_mode = Fw_mode;
    packet->Fw_app_index = Fw_app_index;
    packet->Fw_operating_steps = Fw_operating_steps;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppFwUpgradeParam, (const char *)packet, MAVLINK_MSG_ID_AppFwUpgradeParam_MIN_LEN, MAVLINK_MSG_ID_AppFwUpgradeParam_LEN, MAVLINK_MSG_ID_AppFwUpgradeParam_CRC);
#endif
}
#endif

#endif

// MESSAGE AppFwUpgradeParam UNPACKING


/**
 * @brief Get field Fw_mode from appfwupgradeparam message
 *
 * @return  
 */
static inline uint8_t mavlink_msg_appfwupgradeparam_get_Fw_mode(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  4);
}

/**
 * @brief Get field Fw_app_index from appfwupgradeparam message
 *
 * @return  
 */
static inline uint8_t mavlink_msg_appfwupgradeparam_get_Fw_app_index(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  5);
}

/**
 * @brief Get field Fw_flash_size from appfwupgradeparam message
 *
 * @return  
 */
static inline uint32_t mavlink_msg_appfwupgradeparam_get_Fw_flash_size(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Get field Fw_operating_steps from appfwupgradeparam message
 *
 * @return  
 */
static inline int8_t mavlink_msg_appfwupgradeparam_get_Fw_operating_steps(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int8_t(msg,  6);
}

/**
 * @brief Decode a appfwupgradeparam message into a struct
 *
 * @param msg The message to decode
 * @param appfwupgradeparam C-struct to decode the message contents into
 */
static inline void mavlink_msg_appfwupgradeparam_decode(const mavlink_message_t* msg, mavlink_appfwupgradeparam_t* appfwupgradeparam)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    appfwupgradeparam->Fw_flash_size = mavlink_msg_appfwupgradeparam_get_Fw_flash_size(msg);
    appfwupgradeparam->Fw_mode = mavlink_msg_appfwupgradeparam_get_Fw_mode(msg);
    appfwupgradeparam->Fw_app_index = mavlink_msg_appfwupgradeparam_get_Fw_app_index(msg);
    appfwupgradeparam->Fw_operating_steps = mavlink_msg_appfwupgradeparam_get_Fw_operating_steps(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_AppFwUpgradeParam_LEN? msg->len : MAVLINK_MSG_ID_AppFwUpgradeParam_LEN;
        memset(appfwupgradeparam, 0, MAVLINK_MSG_ID_AppFwUpgradeParam_LEN);
    memcpy(appfwupgradeparam, _MAV_PAYLOAD(msg), len);
#endif
}
