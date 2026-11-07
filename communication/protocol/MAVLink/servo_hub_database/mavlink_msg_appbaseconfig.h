#pragma once
// MESSAGE AppBaseConfig PACKING

#define MAVLINK_MSG_ID_AppBaseConfig 30058


typedef struct __mavlink_appbaseconfig_t {
 int64_t Home_position_offset_value; /*<  */
 uint32_t Can_id; /*<  */
 uint32_t Can_baudrate; /*<  */
 float Brake_engage_time; /*<  */
 float Brake_release_time; /*<  */
 float Dynamic_brake_speed_threshold; /*<  */
 float Brake_release_hold_voltage; /*<  */
 uint32_t Digital_io_outputs_phys; /*<  */
 uint32_t Digital_io_outputs_mask; /*<  */
 float Brake_rated_voltage; /*<  */
 float Brake_release_action_voltage; /*<  */
 float Brake_engage_delay_time; /*<  */
 float Brake_release_delay_time; /*<  */
 int16_t Quick_stop_option_code; /*<  */
 uint16_t Brake_release_pwm_freq; /*<  */
 uint8_t Polarity; /*<  */
 uint8_t Brake_control_mode; /*<  */
} mavlink_appbaseconfig_t;

#define MAVLINK_MSG_ID_AppBaseConfig_LEN 62
#define MAVLINK_MSG_ID_AppBaseConfig_MIN_LEN 62
#define MAVLINK_MSG_ID_30058_LEN 62
#define MAVLINK_MSG_ID_30058_MIN_LEN 62

#define MAVLINK_MSG_ID_AppBaseConfig_CRC 81
#define MAVLINK_MSG_ID_30058_CRC 81



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_AppBaseConfig { \
    30058, \
    "AppBaseConfig", \
    17, \
    {  { "Polarity", NULL, MAVLINK_TYPE_UINT8_T, 0, 60, offsetof(mavlink_appbaseconfig_t, Polarity) }, \
         { "Home_position_offset_value", NULL, MAVLINK_TYPE_INT64_T, 0, 0, offsetof(mavlink_appbaseconfig_t, Home_position_offset_value) }, \
         { "Can_id", NULL, MAVLINK_TYPE_UINT32_T, 0, 8, offsetof(mavlink_appbaseconfig_t, Can_id) }, \
         { "Can_baudrate", NULL, MAVLINK_TYPE_UINT32_T, 0, 12, offsetof(mavlink_appbaseconfig_t, Can_baudrate) }, \
         { "Quick_stop_option_code", NULL, MAVLINK_TYPE_INT16_T, 0, 56, offsetof(mavlink_appbaseconfig_t, Quick_stop_option_code) }, \
         { "Brake_engage_time", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_appbaseconfig_t, Brake_engage_time) }, \
         { "Brake_release_time", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_appbaseconfig_t, Brake_release_time) }, \
         { "Dynamic_brake_speed_threshold", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_appbaseconfig_t, Dynamic_brake_speed_threshold) }, \
         { "Brake_release_hold_voltage", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_appbaseconfig_t, Brake_release_hold_voltage) }, \
         { "Digital_io_outputs_phys", NULL, MAVLINK_TYPE_UINT32_T, 0, 32, offsetof(mavlink_appbaseconfig_t, Digital_io_outputs_phys) }, \
         { "Digital_io_outputs_mask", NULL, MAVLINK_TYPE_UINT32_T, 0, 36, offsetof(mavlink_appbaseconfig_t, Digital_io_outputs_mask) }, \
         { "Brake_control_mode", NULL, MAVLINK_TYPE_UINT8_T, 0, 61, offsetof(mavlink_appbaseconfig_t, Brake_control_mode) }, \
         { "Brake_rated_voltage", NULL, MAVLINK_TYPE_FLOAT, 0, 40, offsetof(mavlink_appbaseconfig_t, Brake_rated_voltage) }, \
         { "Brake_release_action_voltage", NULL, MAVLINK_TYPE_FLOAT, 0, 44, offsetof(mavlink_appbaseconfig_t, Brake_release_action_voltage) }, \
         { "Brake_release_pwm_freq", NULL, MAVLINK_TYPE_UINT16_T, 0, 58, offsetof(mavlink_appbaseconfig_t, Brake_release_pwm_freq) }, \
         { "Brake_engage_delay_time", NULL, MAVLINK_TYPE_FLOAT, 0, 48, offsetof(mavlink_appbaseconfig_t, Brake_engage_delay_time) }, \
         { "Brake_release_delay_time", NULL, MAVLINK_TYPE_FLOAT, 0, 52, offsetof(mavlink_appbaseconfig_t, Brake_release_delay_time) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_AppBaseConfig { \
    "AppBaseConfig", \
    17, \
    {  { "Polarity", NULL, MAVLINK_TYPE_UINT8_T, 0, 60, offsetof(mavlink_appbaseconfig_t, Polarity) }, \
         { "Home_position_offset_value", NULL, MAVLINK_TYPE_INT64_T, 0, 0, offsetof(mavlink_appbaseconfig_t, Home_position_offset_value) }, \
         { "Can_id", NULL, MAVLINK_TYPE_UINT32_T, 0, 8, offsetof(mavlink_appbaseconfig_t, Can_id) }, \
         { "Can_baudrate", NULL, MAVLINK_TYPE_UINT32_T, 0, 12, offsetof(mavlink_appbaseconfig_t, Can_baudrate) }, \
         { "Quick_stop_option_code", NULL, MAVLINK_TYPE_INT16_T, 0, 56, offsetof(mavlink_appbaseconfig_t, Quick_stop_option_code) }, \
         { "Brake_engage_time", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_appbaseconfig_t, Brake_engage_time) }, \
         { "Brake_release_time", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_appbaseconfig_t, Brake_release_time) }, \
         { "Dynamic_brake_speed_threshold", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_appbaseconfig_t, Dynamic_brake_speed_threshold) }, \
         { "Brake_release_hold_voltage", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_appbaseconfig_t, Brake_release_hold_voltage) }, \
         { "Digital_io_outputs_phys", NULL, MAVLINK_TYPE_UINT32_T, 0, 32, offsetof(mavlink_appbaseconfig_t, Digital_io_outputs_phys) }, \
         { "Digital_io_outputs_mask", NULL, MAVLINK_TYPE_UINT32_T, 0, 36, offsetof(mavlink_appbaseconfig_t, Digital_io_outputs_mask) }, \
         { "Brake_control_mode", NULL, MAVLINK_TYPE_UINT8_T, 0, 61, offsetof(mavlink_appbaseconfig_t, Brake_control_mode) }, \
         { "Brake_rated_voltage", NULL, MAVLINK_TYPE_FLOAT, 0, 40, offsetof(mavlink_appbaseconfig_t, Brake_rated_voltage) }, \
         { "Brake_release_action_voltage", NULL, MAVLINK_TYPE_FLOAT, 0, 44, offsetof(mavlink_appbaseconfig_t, Brake_release_action_voltage) }, \
         { "Brake_release_pwm_freq", NULL, MAVLINK_TYPE_UINT16_T, 0, 58, offsetof(mavlink_appbaseconfig_t, Brake_release_pwm_freq) }, \
         { "Brake_engage_delay_time", NULL, MAVLINK_TYPE_FLOAT, 0, 48, offsetof(mavlink_appbaseconfig_t, Brake_engage_delay_time) }, \
         { "Brake_release_delay_time", NULL, MAVLINK_TYPE_FLOAT, 0, 52, offsetof(mavlink_appbaseconfig_t, Brake_release_delay_time) }, \
         } \
}
#endif

/**
 * @brief Pack a appbaseconfig message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param Polarity  
 * @param Home_position_offset_value  
 * @param Can_id  
 * @param Can_baudrate  
 * @param Quick_stop_option_code  
 * @param Brake_engage_time  
 * @param Brake_release_time  
 * @param Dynamic_brake_speed_threshold  
 * @param Brake_release_hold_voltage  
 * @param Digital_io_outputs_phys  
 * @param Digital_io_outputs_mask  
 * @param Brake_control_mode  
 * @param Brake_rated_voltage  
 * @param Brake_release_action_voltage  
 * @param Brake_release_pwm_freq  
 * @param Brake_engage_delay_time  
 * @param Brake_release_delay_time  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_appbaseconfig_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t Polarity, int64_t Home_position_offset_value, uint32_t Can_id, uint32_t Can_baudrate, int16_t Quick_stop_option_code, float Brake_engage_time, float Brake_release_time, float Dynamic_brake_speed_threshold, float Brake_release_hold_voltage, uint32_t Digital_io_outputs_phys, uint32_t Digital_io_outputs_mask, uint8_t Brake_control_mode, float Brake_rated_voltage, float Brake_release_action_voltage, uint16_t Brake_release_pwm_freq, float Brake_engage_delay_time, float Brake_release_delay_time)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_AppBaseConfig_LEN];
    _mav_put_int64_t(buf, 0, Home_position_offset_value);
    _mav_put_uint32_t(buf, 8, Can_id);
    _mav_put_uint32_t(buf, 12, Can_baudrate);
    _mav_put_float(buf, 16, Brake_engage_time);
    _mav_put_float(buf, 20, Brake_release_time);
    _mav_put_float(buf, 24, Dynamic_brake_speed_threshold);
    _mav_put_float(buf, 28, Brake_release_hold_voltage);
    _mav_put_uint32_t(buf, 32, Digital_io_outputs_phys);
    _mav_put_uint32_t(buf, 36, Digital_io_outputs_mask);
    _mav_put_float(buf, 40, Brake_rated_voltage);
    _mav_put_float(buf, 44, Brake_release_action_voltage);
    _mav_put_float(buf, 48, Brake_engage_delay_time);
    _mav_put_float(buf, 52, Brake_release_delay_time);
    _mav_put_int16_t(buf, 56, Quick_stop_option_code);
    _mav_put_uint16_t(buf, 58, Brake_release_pwm_freq);
    _mav_put_uint8_t(buf, 60, Polarity);
    _mav_put_uint8_t(buf, 61, Brake_control_mode);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_AppBaseConfig_LEN);
#else
    mavlink_appbaseconfig_t packet;
    packet.Home_position_offset_value = Home_position_offset_value;
    packet.Can_id = Can_id;
    packet.Can_baudrate = Can_baudrate;
    packet.Brake_engage_time = Brake_engage_time;
    packet.Brake_release_time = Brake_release_time;
    packet.Dynamic_brake_speed_threshold = Dynamic_brake_speed_threshold;
    packet.Brake_release_hold_voltage = Brake_release_hold_voltage;
    packet.Digital_io_outputs_phys = Digital_io_outputs_phys;
    packet.Digital_io_outputs_mask = Digital_io_outputs_mask;
    packet.Brake_rated_voltage = Brake_rated_voltage;
    packet.Brake_release_action_voltage = Brake_release_action_voltage;
    packet.Brake_engage_delay_time = Brake_engage_delay_time;
    packet.Brake_release_delay_time = Brake_release_delay_time;
    packet.Quick_stop_option_code = Quick_stop_option_code;
    packet.Brake_release_pwm_freq = Brake_release_pwm_freq;
    packet.Polarity = Polarity;
    packet.Brake_control_mode = Brake_control_mode;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_AppBaseConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_AppBaseConfig;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_AppBaseConfig_MIN_LEN, MAVLINK_MSG_ID_AppBaseConfig_LEN, MAVLINK_MSG_ID_AppBaseConfig_CRC);
}

/**
 * @brief Pack a appbaseconfig message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param Polarity  
 * @param Home_position_offset_value  
 * @param Can_id  
 * @param Can_baudrate  
 * @param Quick_stop_option_code  
 * @param Brake_engage_time  
 * @param Brake_release_time  
 * @param Dynamic_brake_speed_threshold  
 * @param Brake_release_hold_voltage  
 * @param Digital_io_outputs_phys  
 * @param Digital_io_outputs_mask  
 * @param Brake_control_mode  
 * @param Brake_rated_voltage  
 * @param Brake_release_action_voltage  
 * @param Brake_release_pwm_freq  
 * @param Brake_engage_delay_time  
 * @param Brake_release_delay_time  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_appbaseconfig_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint8_t Polarity, int64_t Home_position_offset_value, uint32_t Can_id, uint32_t Can_baudrate, int16_t Quick_stop_option_code, float Brake_engage_time, float Brake_release_time, float Dynamic_brake_speed_threshold, float Brake_release_hold_voltage, uint32_t Digital_io_outputs_phys, uint32_t Digital_io_outputs_mask, uint8_t Brake_control_mode, float Brake_rated_voltage, float Brake_release_action_voltage, uint16_t Brake_release_pwm_freq, float Brake_engage_delay_time, float Brake_release_delay_time)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_AppBaseConfig_LEN];
    _mav_put_int64_t(buf, 0, Home_position_offset_value);
    _mav_put_uint32_t(buf, 8, Can_id);
    _mav_put_uint32_t(buf, 12, Can_baudrate);
    _mav_put_float(buf, 16, Brake_engage_time);
    _mav_put_float(buf, 20, Brake_release_time);
    _mav_put_float(buf, 24, Dynamic_brake_speed_threshold);
    _mav_put_float(buf, 28, Brake_release_hold_voltage);
    _mav_put_uint32_t(buf, 32, Digital_io_outputs_phys);
    _mav_put_uint32_t(buf, 36, Digital_io_outputs_mask);
    _mav_put_float(buf, 40, Brake_rated_voltage);
    _mav_put_float(buf, 44, Brake_release_action_voltage);
    _mav_put_float(buf, 48, Brake_engage_delay_time);
    _mav_put_float(buf, 52, Brake_release_delay_time);
    _mav_put_int16_t(buf, 56, Quick_stop_option_code);
    _mav_put_uint16_t(buf, 58, Brake_release_pwm_freq);
    _mav_put_uint8_t(buf, 60, Polarity);
    _mav_put_uint8_t(buf, 61, Brake_control_mode);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_AppBaseConfig_LEN);
#else
    mavlink_appbaseconfig_t packet;
    packet.Home_position_offset_value = Home_position_offset_value;
    packet.Can_id = Can_id;
    packet.Can_baudrate = Can_baudrate;
    packet.Brake_engage_time = Brake_engage_time;
    packet.Brake_release_time = Brake_release_time;
    packet.Dynamic_brake_speed_threshold = Dynamic_brake_speed_threshold;
    packet.Brake_release_hold_voltage = Brake_release_hold_voltage;
    packet.Digital_io_outputs_phys = Digital_io_outputs_phys;
    packet.Digital_io_outputs_mask = Digital_io_outputs_mask;
    packet.Brake_rated_voltage = Brake_rated_voltage;
    packet.Brake_release_action_voltage = Brake_release_action_voltage;
    packet.Brake_engage_delay_time = Brake_engage_delay_time;
    packet.Brake_release_delay_time = Brake_release_delay_time;
    packet.Quick_stop_option_code = Quick_stop_option_code;
    packet.Brake_release_pwm_freq = Brake_release_pwm_freq;
    packet.Polarity = Polarity;
    packet.Brake_control_mode = Brake_control_mode;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_AppBaseConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_AppBaseConfig;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_AppBaseConfig_MIN_LEN, MAVLINK_MSG_ID_AppBaseConfig_LEN, MAVLINK_MSG_ID_AppBaseConfig_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_AppBaseConfig_MIN_LEN, MAVLINK_MSG_ID_AppBaseConfig_LEN);
#endif
}

/**
 * @brief Pack a appbaseconfig message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param Polarity  
 * @param Home_position_offset_value  
 * @param Can_id  
 * @param Can_baudrate  
 * @param Quick_stop_option_code  
 * @param Brake_engage_time  
 * @param Brake_release_time  
 * @param Dynamic_brake_speed_threshold  
 * @param Brake_release_hold_voltage  
 * @param Digital_io_outputs_phys  
 * @param Digital_io_outputs_mask  
 * @param Brake_control_mode  
 * @param Brake_rated_voltage  
 * @param Brake_release_action_voltage  
 * @param Brake_release_pwm_freq  
 * @param Brake_engage_delay_time  
 * @param Brake_release_delay_time  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_appbaseconfig_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t Polarity,int64_t Home_position_offset_value,uint32_t Can_id,uint32_t Can_baudrate,int16_t Quick_stop_option_code,float Brake_engage_time,float Brake_release_time,float Dynamic_brake_speed_threshold,float Brake_release_hold_voltage,uint32_t Digital_io_outputs_phys,uint32_t Digital_io_outputs_mask,uint8_t Brake_control_mode,float Brake_rated_voltage,float Brake_release_action_voltage,uint16_t Brake_release_pwm_freq,float Brake_engage_delay_time,float Brake_release_delay_time)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_AppBaseConfig_LEN];
    _mav_put_int64_t(buf, 0, Home_position_offset_value);
    _mav_put_uint32_t(buf, 8, Can_id);
    _mav_put_uint32_t(buf, 12, Can_baudrate);
    _mav_put_float(buf, 16, Brake_engage_time);
    _mav_put_float(buf, 20, Brake_release_time);
    _mav_put_float(buf, 24, Dynamic_brake_speed_threshold);
    _mav_put_float(buf, 28, Brake_release_hold_voltage);
    _mav_put_uint32_t(buf, 32, Digital_io_outputs_phys);
    _mav_put_uint32_t(buf, 36, Digital_io_outputs_mask);
    _mav_put_float(buf, 40, Brake_rated_voltage);
    _mav_put_float(buf, 44, Brake_release_action_voltage);
    _mav_put_float(buf, 48, Brake_engage_delay_time);
    _mav_put_float(buf, 52, Brake_release_delay_time);
    _mav_put_int16_t(buf, 56, Quick_stop_option_code);
    _mav_put_uint16_t(buf, 58, Brake_release_pwm_freq);
    _mav_put_uint8_t(buf, 60, Polarity);
    _mav_put_uint8_t(buf, 61, Brake_control_mode);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_AppBaseConfig_LEN);
#else
    mavlink_appbaseconfig_t packet;
    packet.Home_position_offset_value = Home_position_offset_value;
    packet.Can_id = Can_id;
    packet.Can_baudrate = Can_baudrate;
    packet.Brake_engage_time = Brake_engage_time;
    packet.Brake_release_time = Brake_release_time;
    packet.Dynamic_brake_speed_threshold = Dynamic_brake_speed_threshold;
    packet.Brake_release_hold_voltage = Brake_release_hold_voltage;
    packet.Digital_io_outputs_phys = Digital_io_outputs_phys;
    packet.Digital_io_outputs_mask = Digital_io_outputs_mask;
    packet.Brake_rated_voltage = Brake_rated_voltage;
    packet.Brake_release_action_voltage = Brake_release_action_voltage;
    packet.Brake_engage_delay_time = Brake_engage_delay_time;
    packet.Brake_release_delay_time = Brake_release_delay_time;
    packet.Quick_stop_option_code = Quick_stop_option_code;
    packet.Brake_release_pwm_freq = Brake_release_pwm_freq;
    packet.Polarity = Polarity;
    packet.Brake_control_mode = Brake_control_mode;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_AppBaseConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_AppBaseConfig;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_AppBaseConfig_MIN_LEN, MAVLINK_MSG_ID_AppBaseConfig_LEN, MAVLINK_MSG_ID_AppBaseConfig_CRC);
}

/**
 * @brief Encode a appbaseconfig struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param appbaseconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_appbaseconfig_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_appbaseconfig_t* appbaseconfig)
{
    return mavlink_msg_appbaseconfig_pack(system_id, component_id, msg, appbaseconfig->Polarity, appbaseconfig->Home_position_offset_value, appbaseconfig->Can_id, appbaseconfig->Can_baudrate, appbaseconfig->Quick_stop_option_code, appbaseconfig->Brake_engage_time, appbaseconfig->Brake_release_time, appbaseconfig->Dynamic_brake_speed_threshold, appbaseconfig->Brake_release_hold_voltage, appbaseconfig->Digital_io_outputs_phys, appbaseconfig->Digital_io_outputs_mask, appbaseconfig->Brake_control_mode, appbaseconfig->Brake_rated_voltage, appbaseconfig->Brake_release_action_voltage, appbaseconfig->Brake_release_pwm_freq, appbaseconfig->Brake_engage_delay_time, appbaseconfig->Brake_release_delay_time);
}

/**
 * @brief Encode a appbaseconfig struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param appbaseconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_appbaseconfig_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_appbaseconfig_t* appbaseconfig)
{
    return mavlink_msg_appbaseconfig_pack_chan(system_id, component_id, chan, msg, appbaseconfig->Polarity, appbaseconfig->Home_position_offset_value, appbaseconfig->Can_id, appbaseconfig->Can_baudrate, appbaseconfig->Quick_stop_option_code, appbaseconfig->Brake_engage_time, appbaseconfig->Brake_release_time, appbaseconfig->Dynamic_brake_speed_threshold, appbaseconfig->Brake_release_hold_voltage, appbaseconfig->Digital_io_outputs_phys, appbaseconfig->Digital_io_outputs_mask, appbaseconfig->Brake_control_mode, appbaseconfig->Brake_rated_voltage, appbaseconfig->Brake_release_action_voltage, appbaseconfig->Brake_release_pwm_freq, appbaseconfig->Brake_engage_delay_time, appbaseconfig->Brake_release_delay_time);
}

/**
 * @brief Encode a appbaseconfig struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param appbaseconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_appbaseconfig_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_appbaseconfig_t* appbaseconfig)
{
    return mavlink_msg_appbaseconfig_pack_status(system_id, component_id, _status, msg,  appbaseconfig->Polarity, appbaseconfig->Home_position_offset_value, appbaseconfig->Can_id, appbaseconfig->Can_baudrate, appbaseconfig->Quick_stop_option_code, appbaseconfig->Brake_engage_time, appbaseconfig->Brake_release_time, appbaseconfig->Dynamic_brake_speed_threshold, appbaseconfig->Brake_release_hold_voltage, appbaseconfig->Digital_io_outputs_phys, appbaseconfig->Digital_io_outputs_mask, appbaseconfig->Brake_control_mode, appbaseconfig->Brake_rated_voltage, appbaseconfig->Brake_release_action_voltage, appbaseconfig->Brake_release_pwm_freq, appbaseconfig->Brake_engage_delay_time, appbaseconfig->Brake_release_delay_time);
}

/**
 * @brief Send a appbaseconfig message
 * @param chan MAVLink channel to send the message
 *
 * @param Polarity  
 * @param Home_position_offset_value  
 * @param Can_id  
 * @param Can_baudrate  
 * @param Quick_stop_option_code  
 * @param Brake_engage_time  
 * @param Brake_release_time  
 * @param Dynamic_brake_speed_threshold  
 * @param Brake_release_hold_voltage  
 * @param Digital_io_outputs_phys  
 * @param Digital_io_outputs_mask  
 * @param Brake_control_mode  
 * @param Brake_rated_voltage  
 * @param Brake_release_action_voltage  
 * @param Brake_release_pwm_freq  
 * @param Brake_engage_delay_time  
 * @param Brake_release_delay_time  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_appbaseconfig_send(mavlink_channel_t chan, uint8_t Polarity, int64_t Home_position_offset_value, uint32_t Can_id, uint32_t Can_baudrate, int16_t Quick_stop_option_code, float Brake_engage_time, float Brake_release_time, float Dynamic_brake_speed_threshold, float Brake_release_hold_voltage, uint32_t Digital_io_outputs_phys, uint32_t Digital_io_outputs_mask, uint8_t Brake_control_mode, float Brake_rated_voltage, float Brake_release_action_voltage, uint16_t Brake_release_pwm_freq, float Brake_engage_delay_time, float Brake_release_delay_time)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_AppBaseConfig_LEN];
    _mav_put_int64_t(buf, 0, Home_position_offset_value);
    _mav_put_uint32_t(buf, 8, Can_id);
    _mav_put_uint32_t(buf, 12, Can_baudrate);
    _mav_put_float(buf, 16, Brake_engage_time);
    _mav_put_float(buf, 20, Brake_release_time);
    _mav_put_float(buf, 24, Dynamic_brake_speed_threshold);
    _mav_put_float(buf, 28, Brake_release_hold_voltage);
    _mav_put_uint32_t(buf, 32, Digital_io_outputs_phys);
    _mav_put_uint32_t(buf, 36, Digital_io_outputs_mask);
    _mav_put_float(buf, 40, Brake_rated_voltage);
    _mav_put_float(buf, 44, Brake_release_action_voltage);
    _mav_put_float(buf, 48, Brake_engage_delay_time);
    _mav_put_float(buf, 52, Brake_release_delay_time);
    _mav_put_int16_t(buf, 56, Quick_stop_option_code);
    _mav_put_uint16_t(buf, 58, Brake_release_pwm_freq);
    _mav_put_uint8_t(buf, 60, Polarity);
    _mav_put_uint8_t(buf, 61, Brake_control_mode);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppBaseConfig, buf, MAVLINK_MSG_ID_AppBaseConfig_MIN_LEN, MAVLINK_MSG_ID_AppBaseConfig_LEN, MAVLINK_MSG_ID_AppBaseConfig_CRC);
#else
    mavlink_appbaseconfig_t packet;
    packet.Home_position_offset_value = Home_position_offset_value;
    packet.Can_id = Can_id;
    packet.Can_baudrate = Can_baudrate;
    packet.Brake_engage_time = Brake_engage_time;
    packet.Brake_release_time = Brake_release_time;
    packet.Dynamic_brake_speed_threshold = Dynamic_brake_speed_threshold;
    packet.Brake_release_hold_voltage = Brake_release_hold_voltage;
    packet.Digital_io_outputs_phys = Digital_io_outputs_phys;
    packet.Digital_io_outputs_mask = Digital_io_outputs_mask;
    packet.Brake_rated_voltage = Brake_rated_voltage;
    packet.Brake_release_action_voltage = Brake_release_action_voltage;
    packet.Brake_engage_delay_time = Brake_engage_delay_time;
    packet.Brake_release_delay_time = Brake_release_delay_time;
    packet.Quick_stop_option_code = Quick_stop_option_code;
    packet.Brake_release_pwm_freq = Brake_release_pwm_freq;
    packet.Polarity = Polarity;
    packet.Brake_control_mode = Brake_control_mode;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppBaseConfig, (const char *)&packet, MAVLINK_MSG_ID_AppBaseConfig_MIN_LEN, MAVLINK_MSG_ID_AppBaseConfig_LEN, MAVLINK_MSG_ID_AppBaseConfig_CRC);
#endif
}

/**
 * @brief Send a appbaseconfig message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_appbaseconfig_send_struct(mavlink_channel_t chan, const mavlink_appbaseconfig_t* appbaseconfig)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_appbaseconfig_send(chan, appbaseconfig->Polarity, appbaseconfig->Home_position_offset_value, appbaseconfig->Can_id, appbaseconfig->Can_baudrate, appbaseconfig->Quick_stop_option_code, appbaseconfig->Brake_engage_time, appbaseconfig->Brake_release_time, appbaseconfig->Dynamic_brake_speed_threshold, appbaseconfig->Brake_release_hold_voltage, appbaseconfig->Digital_io_outputs_phys, appbaseconfig->Digital_io_outputs_mask, appbaseconfig->Brake_control_mode, appbaseconfig->Brake_rated_voltage, appbaseconfig->Brake_release_action_voltage, appbaseconfig->Brake_release_pwm_freq, appbaseconfig->Brake_engage_delay_time, appbaseconfig->Brake_release_delay_time);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppBaseConfig, (const char *)appbaseconfig, MAVLINK_MSG_ID_AppBaseConfig_MIN_LEN, MAVLINK_MSG_ID_AppBaseConfig_LEN, MAVLINK_MSG_ID_AppBaseConfig_CRC);
#endif
}

#if MAVLINK_MSG_ID_AppBaseConfig_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_appbaseconfig_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t Polarity, int64_t Home_position_offset_value, uint32_t Can_id, uint32_t Can_baudrate, int16_t Quick_stop_option_code, float Brake_engage_time, float Brake_release_time, float Dynamic_brake_speed_threshold, float Brake_release_hold_voltage, uint32_t Digital_io_outputs_phys, uint32_t Digital_io_outputs_mask, uint8_t Brake_control_mode, float Brake_rated_voltage, float Brake_release_action_voltage, uint16_t Brake_release_pwm_freq, float Brake_engage_delay_time, float Brake_release_delay_time)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_int64_t(buf, 0, Home_position_offset_value);
    _mav_put_uint32_t(buf, 8, Can_id);
    _mav_put_uint32_t(buf, 12, Can_baudrate);
    _mav_put_float(buf, 16, Brake_engage_time);
    _mav_put_float(buf, 20, Brake_release_time);
    _mav_put_float(buf, 24, Dynamic_brake_speed_threshold);
    _mav_put_float(buf, 28, Brake_release_hold_voltage);
    _mav_put_uint32_t(buf, 32, Digital_io_outputs_phys);
    _mav_put_uint32_t(buf, 36, Digital_io_outputs_mask);
    _mav_put_float(buf, 40, Brake_rated_voltage);
    _mav_put_float(buf, 44, Brake_release_action_voltage);
    _mav_put_float(buf, 48, Brake_engage_delay_time);
    _mav_put_float(buf, 52, Brake_release_delay_time);
    _mav_put_int16_t(buf, 56, Quick_stop_option_code);
    _mav_put_uint16_t(buf, 58, Brake_release_pwm_freq);
    _mav_put_uint8_t(buf, 60, Polarity);
    _mav_put_uint8_t(buf, 61, Brake_control_mode);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppBaseConfig, buf, MAVLINK_MSG_ID_AppBaseConfig_MIN_LEN, MAVLINK_MSG_ID_AppBaseConfig_LEN, MAVLINK_MSG_ID_AppBaseConfig_CRC);
#else
    mavlink_appbaseconfig_t *packet = (mavlink_appbaseconfig_t *)msgbuf;
    packet->Home_position_offset_value = Home_position_offset_value;
    packet->Can_id = Can_id;
    packet->Can_baudrate = Can_baudrate;
    packet->Brake_engage_time = Brake_engage_time;
    packet->Brake_release_time = Brake_release_time;
    packet->Dynamic_brake_speed_threshold = Dynamic_brake_speed_threshold;
    packet->Brake_release_hold_voltage = Brake_release_hold_voltage;
    packet->Digital_io_outputs_phys = Digital_io_outputs_phys;
    packet->Digital_io_outputs_mask = Digital_io_outputs_mask;
    packet->Brake_rated_voltage = Brake_rated_voltage;
    packet->Brake_release_action_voltage = Brake_release_action_voltage;
    packet->Brake_engage_delay_time = Brake_engage_delay_time;
    packet->Brake_release_delay_time = Brake_release_delay_time;
    packet->Quick_stop_option_code = Quick_stop_option_code;
    packet->Brake_release_pwm_freq = Brake_release_pwm_freq;
    packet->Polarity = Polarity;
    packet->Brake_control_mode = Brake_control_mode;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppBaseConfig, (const char *)packet, MAVLINK_MSG_ID_AppBaseConfig_MIN_LEN, MAVLINK_MSG_ID_AppBaseConfig_LEN, MAVLINK_MSG_ID_AppBaseConfig_CRC);
#endif
}
#endif

#endif

// MESSAGE AppBaseConfig UNPACKING


/**
 * @brief Get field Polarity from appbaseconfig message
 *
 * @return  
 */
static inline uint8_t mavlink_msg_appbaseconfig_get_Polarity(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  60);
}

/**
 * @brief Get field Home_position_offset_value from appbaseconfig message
 *
 * @return  
 */
static inline int64_t mavlink_msg_appbaseconfig_get_Home_position_offset_value(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int64_t(msg,  0);
}

/**
 * @brief Get field Can_id from appbaseconfig message
 *
 * @return  
 */
static inline uint32_t mavlink_msg_appbaseconfig_get_Can_id(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  8);
}

/**
 * @brief Get field Can_baudrate from appbaseconfig message
 *
 * @return  
 */
static inline uint32_t mavlink_msg_appbaseconfig_get_Can_baudrate(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  12);
}

/**
 * @brief Get field Quick_stop_option_code from appbaseconfig message
 *
 * @return  
 */
static inline int16_t mavlink_msg_appbaseconfig_get_Quick_stop_option_code(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  56);
}

/**
 * @brief Get field Brake_engage_time from appbaseconfig message
 *
 * @return  
 */
static inline float mavlink_msg_appbaseconfig_get_Brake_engage_time(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  16);
}

/**
 * @brief Get field Brake_release_time from appbaseconfig message
 *
 * @return  
 */
static inline float mavlink_msg_appbaseconfig_get_Brake_release_time(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  20);
}

/**
 * @brief Get field Dynamic_brake_speed_threshold from appbaseconfig message
 *
 * @return  
 */
static inline float mavlink_msg_appbaseconfig_get_Dynamic_brake_speed_threshold(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  24);
}

/**
 * @brief Get field Brake_release_hold_voltage from appbaseconfig message
 *
 * @return  
 */
static inline float mavlink_msg_appbaseconfig_get_Brake_release_hold_voltage(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  28);
}

/**
 * @brief Get field Digital_io_outputs_phys from appbaseconfig message
 *
 * @return  
 */
static inline uint32_t mavlink_msg_appbaseconfig_get_Digital_io_outputs_phys(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  32);
}

/**
 * @brief Get field Digital_io_outputs_mask from appbaseconfig message
 *
 * @return  
 */
static inline uint32_t mavlink_msg_appbaseconfig_get_Digital_io_outputs_mask(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  36);
}

/**
 * @brief Get field Brake_control_mode from appbaseconfig message
 *
 * @return  
 */
static inline uint8_t mavlink_msg_appbaseconfig_get_Brake_control_mode(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  61);
}

/**
 * @brief Get field Brake_rated_voltage from appbaseconfig message
 *
 * @return  
 */
static inline float mavlink_msg_appbaseconfig_get_Brake_rated_voltage(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  40);
}

/**
 * @brief Get field Brake_release_action_voltage from appbaseconfig message
 *
 * @return  
 */
static inline float mavlink_msg_appbaseconfig_get_Brake_release_action_voltage(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  44);
}

/**
 * @brief Get field Brake_release_pwm_freq from appbaseconfig message
 *
 * @return  
 */
static inline uint16_t mavlink_msg_appbaseconfig_get_Brake_release_pwm_freq(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  58);
}

/**
 * @brief Get field Brake_engage_delay_time from appbaseconfig message
 *
 * @return  
 */
static inline float mavlink_msg_appbaseconfig_get_Brake_engage_delay_time(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  48);
}

/**
 * @brief Get field Brake_release_delay_time from appbaseconfig message
 *
 * @return  
 */
static inline float mavlink_msg_appbaseconfig_get_Brake_release_delay_time(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  52);
}

/**
 * @brief Decode a appbaseconfig message into a struct
 *
 * @param msg The message to decode
 * @param appbaseconfig C-struct to decode the message contents into
 */
static inline void mavlink_msg_appbaseconfig_decode(const mavlink_message_t* msg, mavlink_appbaseconfig_t* appbaseconfig)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    appbaseconfig->Home_position_offset_value = mavlink_msg_appbaseconfig_get_Home_position_offset_value(msg);
    appbaseconfig->Can_id = mavlink_msg_appbaseconfig_get_Can_id(msg);
    appbaseconfig->Can_baudrate = mavlink_msg_appbaseconfig_get_Can_baudrate(msg);
    appbaseconfig->Brake_engage_time = mavlink_msg_appbaseconfig_get_Brake_engage_time(msg);
    appbaseconfig->Brake_release_time = mavlink_msg_appbaseconfig_get_Brake_release_time(msg);
    appbaseconfig->Dynamic_brake_speed_threshold = mavlink_msg_appbaseconfig_get_Dynamic_brake_speed_threshold(msg);
    appbaseconfig->Brake_release_hold_voltage = mavlink_msg_appbaseconfig_get_Brake_release_hold_voltage(msg);
    appbaseconfig->Digital_io_outputs_phys = mavlink_msg_appbaseconfig_get_Digital_io_outputs_phys(msg);
    appbaseconfig->Digital_io_outputs_mask = mavlink_msg_appbaseconfig_get_Digital_io_outputs_mask(msg);
    appbaseconfig->Brake_rated_voltage = mavlink_msg_appbaseconfig_get_Brake_rated_voltage(msg);
    appbaseconfig->Brake_release_action_voltage = mavlink_msg_appbaseconfig_get_Brake_release_action_voltage(msg);
    appbaseconfig->Brake_engage_delay_time = mavlink_msg_appbaseconfig_get_Brake_engage_delay_time(msg);
    appbaseconfig->Brake_release_delay_time = mavlink_msg_appbaseconfig_get_Brake_release_delay_time(msg);
    appbaseconfig->Quick_stop_option_code = mavlink_msg_appbaseconfig_get_Quick_stop_option_code(msg);
    appbaseconfig->Brake_release_pwm_freq = mavlink_msg_appbaseconfig_get_Brake_release_pwm_freq(msg);
    appbaseconfig->Polarity = mavlink_msg_appbaseconfig_get_Polarity(msg);
    appbaseconfig->Brake_control_mode = mavlink_msg_appbaseconfig_get_Brake_control_mode(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_AppBaseConfig_LEN? msg->len : MAVLINK_MSG_ID_AppBaseConfig_LEN;
        memset(appbaseconfig, 0, MAVLINK_MSG_ID_AppBaseConfig_LEN);
    memcpy(appbaseconfig, _MAV_PAYLOAD(msg), len);
#endif
}
