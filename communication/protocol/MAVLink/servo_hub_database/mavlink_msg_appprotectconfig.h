#pragma once
// MESSAGE AppProtectConfig PACKING

#define MAVLINK_MSG_ID_AppProtectConfig 30064


typedef struct __mavlink_appprotectconfig_t {
 float Bus_under_voltage_threshold; /*<  */
 float Bus_over_voltage_threshold; /*<  */
 float Drive_overload_current_duration; /*<  */
 float Drive_peak_current_duration; /*<  */
 float Drive_temperature_threshold_time; /*<  */
 float Drive_low_temperature_fault_threshold; /*<  */
 float Drive_high_temperature_fault_threshold; /*<  */
 float Overspeed_threshold; /*<  */
 float Drive_overcurrent_threshold; /*<  */
 uint32_t Protection_enable; /*<  */
 float Motor_low_temperature_fault_threshold; /*<  */
 float Motor_high_temperature_fault_threshold; /*<  */
 float Can_timeout; /*<  */
 float Motor_low_temperature_warning_threshold; /*<  */
 float Motor_high_temperature_warning_threshold; /*<  */
 float Mcu_temperature_threshold_time; /*<  */
 float Mcu_low_temperature_fault_threshold; /*<  */
 float Mcu_high_temperature_fault_threshold; /*<  */
 float Mcu_low_temperature_warning_threshold; /*<  */
 float Mcu_high_temperature_warning_threshold; /*<  */
 float Drive_low_temperature_warning_threshold; /*<  */
 float Drive_high_temperature_warning_threshold; /*<  */
} mavlink_appprotectconfig_t;

#define MAVLINK_MSG_ID_AppProtectConfig_LEN 88
#define MAVLINK_MSG_ID_AppProtectConfig_MIN_LEN 88
#define MAVLINK_MSG_ID_30064_LEN 88
#define MAVLINK_MSG_ID_30064_MIN_LEN 88

#define MAVLINK_MSG_ID_AppProtectConfig_CRC 51
#define MAVLINK_MSG_ID_30064_CRC 51



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_AppProtectConfig { \
    30064, \
    "AppProtectConfig", \
    22, \
    {  { "Bus_under_voltage_threshold", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_appprotectconfig_t, Bus_under_voltage_threshold) }, \
         { "Bus_over_voltage_threshold", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_appprotectconfig_t, Bus_over_voltage_threshold) }, \
         { "Drive_overload_current_duration", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_appprotectconfig_t, Drive_overload_current_duration) }, \
         { "Drive_peak_current_duration", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_appprotectconfig_t, Drive_peak_current_duration) }, \
         { "Drive_temperature_threshold_time", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_appprotectconfig_t, Drive_temperature_threshold_time) }, \
         { "Drive_low_temperature_fault_threshold", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_appprotectconfig_t, Drive_low_temperature_fault_threshold) }, \
         { "Drive_high_temperature_fault_threshold", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_appprotectconfig_t, Drive_high_temperature_fault_threshold) }, \
         { "Overspeed_threshold", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_appprotectconfig_t, Overspeed_threshold) }, \
         { "Drive_overcurrent_threshold", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_appprotectconfig_t, Drive_overcurrent_threshold) }, \
         { "Protection_enable", NULL, MAVLINK_TYPE_UINT32_T, 0, 36, offsetof(mavlink_appprotectconfig_t, Protection_enable) }, \
         { "Motor_low_temperature_fault_threshold", NULL, MAVLINK_TYPE_FLOAT, 0, 40, offsetof(mavlink_appprotectconfig_t, Motor_low_temperature_fault_threshold) }, \
         { "Motor_high_temperature_fault_threshold", NULL, MAVLINK_TYPE_FLOAT, 0, 44, offsetof(mavlink_appprotectconfig_t, Motor_high_temperature_fault_threshold) }, \
         { "Can_timeout", NULL, MAVLINK_TYPE_FLOAT, 0, 48, offsetof(mavlink_appprotectconfig_t, Can_timeout) }, \
         { "Motor_low_temperature_warning_threshold", NULL, MAVLINK_TYPE_FLOAT, 0, 52, offsetof(mavlink_appprotectconfig_t, Motor_low_temperature_warning_threshold) }, \
         { "Motor_high_temperature_warning_threshold", NULL, MAVLINK_TYPE_FLOAT, 0, 56, offsetof(mavlink_appprotectconfig_t, Motor_high_temperature_warning_threshold) }, \
         { "Mcu_temperature_threshold_time", NULL, MAVLINK_TYPE_FLOAT, 0, 60, offsetof(mavlink_appprotectconfig_t, Mcu_temperature_threshold_time) }, \
         { "Mcu_low_temperature_fault_threshold", NULL, MAVLINK_TYPE_FLOAT, 0, 64, offsetof(mavlink_appprotectconfig_t, Mcu_low_temperature_fault_threshold) }, \
         { "Mcu_high_temperature_fault_threshold", NULL, MAVLINK_TYPE_FLOAT, 0, 68, offsetof(mavlink_appprotectconfig_t, Mcu_high_temperature_fault_threshold) }, \
         { "Mcu_low_temperature_warning_threshold", NULL, MAVLINK_TYPE_FLOAT, 0, 72, offsetof(mavlink_appprotectconfig_t, Mcu_low_temperature_warning_threshold) }, \
         { "Mcu_high_temperature_warning_threshold", NULL, MAVLINK_TYPE_FLOAT, 0, 76, offsetof(mavlink_appprotectconfig_t, Mcu_high_temperature_warning_threshold) }, \
         { "Drive_low_temperature_warning_threshold", NULL, MAVLINK_TYPE_FLOAT, 0, 80, offsetof(mavlink_appprotectconfig_t, Drive_low_temperature_warning_threshold) }, \
         { "Drive_high_temperature_warning_threshold", NULL, MAVLINK_TYPE_FLOAT, 0, 84, offsetof(mavlink_appprotectconfig_t, Drive_high_temperature_warning_threshold) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_AppProtectConfig { \
    "AppProtectConfig", \
    22, \
    {  { "Bus_under_voltage_threshold", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_appprotectconfig_t, Bus_under_voltage_threshold) }, \
         { "Bus_over_voltage_threshold", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_appprotectconfig_t, Bus_over_voltage_threshold) }, \
         { "Drive_overload_current_duration", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_appprotectconfig_t, Drive_overload_current_duration) }, \
         { "Drive_peak_current_duration", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_appprotectconfig_t, Drive_peak_current_duration) }, \
         { "Drive_temperature_threshold_time", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_appprotectconfig_t, Drive_temperature_threshold_time) }, \
         { "Drive_low_temperature_fault_threshold", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_appprotectconfig_t, Drive_low_temperature_fault_threshold) }, \
         { "Drive_high_temperature_fault_threshold", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_appprotectconfig_t, Drive_high_temperature_fault_threshold) }, \
         { "Overspeed_threshold", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_appprotectconfig_t, Overspeed_threshold) }, \
         { "Drive_overcurrent_threshold", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_appprotectconfig_t, Drive_overcurrent_threshold) }, \
         { "Protection_enable", NULL, MAVLINK_TYPE_UINT32_T, 0, 36, offsetof(mavlink_appprotectconfig_t, Protection_enable) }, \
         { "Motor_low_temperature_fault_threshold", NULL, MAVLINK_TYPE_FLOAT, 0, 40, offsetof(mavlink_appprotectconfig_t, Motor_low_temperature_fault_threshold) }, \
         { "Motor_high_temperature_fault_threshold", NULL, MAVLINK_TYPE_FLOAT, 0, 44, offsetof(mavlink_appprotectconfig_t, Motor_high_temperature_fault_threshold) }, \
         { "Can_timeout", NULL, MAVLINK_TYPE_FLOAT, 0, 48, offsetof(mavlink_appprotectconfig_t, Can_timeout) }, \
         { "Motor_low_temperature_warning_threshold", NULL, MAVLINK_TYPE_FLOAT, 0, 52, offsetof(mavlink_appprotectconfig_t, Motor_low_temperature_warning_threshold) }, \
         { "Motor_high_temperature_warning_threshold", NULL, MAVLINK_TYPE_FLOAT, 0, 56, offsetof(mavlink_appprotectconfig_t, Motor_high_temperature_warning_threshold) }, \
         { "Mcu_temperature_threshold_time", NULL, MAVLINK_TYPE_FLOAT, 0, 60, offsetof(mavlink_appprotectconfig_t, Mcu_temperature_threshold_time) }, \
         { "Mcu_low_temperature_fault_threshold", NULL, MAVLINK_TYPE_FLOAT, 0, 64, offsetof(mavlink_appprotectconfig_t, Mcu_low_temperature_fault_threshold) }, \
         { "Mcu_high_temperature_fault_threshold", NULL, MAVLINK_TYPE_FLOAT, 0, 68, offsetof(mavlink_appprotectconfig_t, Mcu_high_temperature_fault_threshold) }, \
         { "Mcu_low_temperature_warning_threshold", NULL, MAVLINK_TYPE_FLOAT, 0, 72, offsetof(mavlink_appprotectconfig_t, Mcu_low_temperature_warning_threshold) }, \
         { "Mcu_high_temperature_warning_threshold", NULL, MAVLINK_TYPE_FLOAT, 0, 76, offsetof(mavlink_appprotectconfig_t, Mcu_high_temperature_warning_threshold) }, \
         { "Drive_low_temperature_warning_threshold", NULL, MAVLINK_TYPE_FLOAT, 0, 80, offsetof(mavlink_appprotectconfig_t, Drive_low_temperature_warning_threshold) }, \
         { "Drive_high_temperature_warning_threshold", NULL, MAVLINK_TYPE_FLOAT, 0, 84, offsetof(mavlink_appprotectconfig_t, Drive_high_temperature_warning_threshold) }, \
         } \
}
#endif

/**
 * @brief Pack a appprotectconfig message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param Bus_under_voltage_threshold  
 * @param Bus_over_voltage_threshold  
 * @param Drive_overload_current_duration  
 * @param Drive_peak_current_duration  
 * @param Drive_temperature_threshold_time  
 * @param Drive_low_temperature_fault_threshold  
 * @param Drive_high_temperature_fault_threshold  
 * @param Overspeed_threshold  
 * @param Drive_overcurrent_threshold  
 * @param Protection_enable  
 * @param Motor_low_temperature_fault_threshold  
 * @param Motor_high_temperature_fault_threshold  
 * @param Can_timeout  
 * @param Motor_low_temperature_warning_threshold  
 * @param Motor_high_temperature_warning_threshold  
 * @param Mcu_temperature_threshold_time  
 * @param Mcu_low_temperature_fault_threshold  
 * @param Mcu_high_temperature_fault_threshold  
 * @param Mcu_low_temperature_warning_threshold  
 * @param Mcu_high_temperature_warning_threshold  
 * @param Drive_low_temperature_warning_threshold  
 * @param Drive_high_temperature_warning_threshold  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_appprotectconfig_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               float Bus_under_voltage_threshold, float Bus_over_voltage_threshold, float Drive_overload_current_duration, float Drive_peak_current_duration, float Drive_temperature_threshold_time, float Drive_low_temperature_fault_threshold, float Drive_high_temperature_fault_threshold, float Overspeed_threshold, float Drive_overcurrent_threshold, uint32_t Protection_enable, float Motor_low_temperature_fault_threshold, float Motor_high_temperature_fault_threshold, float Can_timeout, float Motor_low_temperature_warning_threshold, float Motor_high_temperature_warning_threshold, float Mcu_temperature_threshold_time, float Mcu_low_temperature_fault_threshold, float Mcu_high_temperature_fault_threshold, float Mcu_low_temperature_warning_threshold, float Mcu_high_temperature_warning_threshold, float Drive_low_temperature_warning_threshold, float Drive_high_temperature_warning_threshold)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_AppProtectConfig_LEN];
    _mav_put_float(buf, 0, Bus_under_voltage_threshold);
    _mav_put_float(buf, 4, Bus_over_voltage_threshold);
    _mav_put_float(buf, 8, Drive_overload_current_duration);
    _mav_put_float(buf, 12, Drive_peak_current_duration);
    _mav_put_float(buf, 16, Drive_temperature_threshold_time);
    _mav_put_float(buf, 20, Drive_low_temperature_fault_threshold);
    _mav_put_float(buf, 24, Drive_high_temperature_fault_threshold);
    _mav_put_float(buf, 28, Overspeed_threshold);
    _mav_put_float(buf, 32, Drive_overcurrent_threshold);
    _mav_put_uint32_t(buf, 36, Protection_enable);
    _mav_put_float(buf, 40, Motor_low_temperature_fault_threshold);
    _mav_put_float(buf, 44, Motor_high_temperature_fault_threshold);
    _mav_put_float(buf, 48, Can_timeout);
    _mav_put_float(buf, 52, Motor_low_temperature_warning_threshold);
    _mav_put_float(buf, 56, Motor_high_temperature_warning_threshold);
    _mav_put_float(buf, 60, Mcu_temperature_threshold_time);
    _mav_put_float(buf, 64, Mcu_low_temperature_fault_threshold);
    _mav_put_float(buf, 68, Mcu_high_temperature_fault_threshold);
    _mav_put_float(buf, 72, Mcu_low_temperature_warning_threshold);
    _mav_put_float(buf, 76, Mcu_high_temperature_warning_threshold);
    _mav_put_float(buf, 80, Drive_low_temperature_warning_threshold);
    _mav_put_float(buf, 84, Drive_high_temperature_warning_threshold);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_AppProtectConfig_LEN);
#else
    mavlink_appprotectconfig_t packet;
    packet.Bus_under_voltage_threshold = Bus_under_voltage_threshold;
    packet.Bus_over_voltage_threshold = Bus_over_voltage_threshold;
    packet.Drive_overload_current_duration = Drive_overload_current_duration;
    packet.Drive_peak_current_duration = Drive_peak_current_duration;
    packet.Drive_temperature_threshold_time = Drive_temperature_threshold_time;
    packet.Drive_low_temperature_fault_threshold = Drive_low_temperature_fault_threshold;
    packet.Drive_high_temperature_fault_threshold = Drive_high_temperature_fault_threshold;
    packet.Overspeed_threshold = Overspeed_threshold;
    packet.Drive_overcurrent_threshold = Drive_overcurrent_threshold;
    packet.Protection_enable = Protection_enable;
    packet.Motor_low_temperature_fault_threshold = Motor_low_temperature_fault_threshold;
    packet.Motor_high_temperature_fault_threshold = Motor_high_temperature_fault_threshold;
    packet.Can_timeout = Can_timeout;
    packet.Motor_low_temperature_warning_threshold = Motor_low_temperature_warning_threshold;
    packet.Motor_high_temperature_warning_threshold = Motor_high_temperature_warning_threshold;
    packet.Mcu_temperature_threshold_time = Mcu_temperature_threshold_time;
    packet.Mcu_low_temperature_fault_threshold = Mcu_low_temperature_fault_threshold;
    packet.Mcu_high_temperature_fault_threshold = Mcu_high_temperature_fault_threshold;
    packet.Mcu_low_temperature_warning_threshold = Mcu_low_temperature_warning_threshold;
    packet.Mcu_high_temperature_warning_threshold = Mcu_high_temperature_warning_threshold;
    packet.Drive_low_temperature_warning_threshold = Drive_low_temperature_warning_threshold;
    packet.Drive_high_temperature_warning_threshold = Drive_high_temperature_warning_threshold;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_AppProtectConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_AppProtectConfig;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_AppProtectConfig_MIN_LEN, MAVLINK_MSG_ID_AppProtectConfig_LEN, MAVLINK_MSG_ID_AppProtectConfig_CRC);
}

/**
 * @brief Pack a appprotectconfig message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param Bus_under_voltage_threshold  
 * @param Bus_over_voltage_threshold  
 * @param Drive_overload_current_duration  
 * @param Drive_peak_current_duration  
 * @param Drive_temperature_threshold_time  
 * @param Drive_low_temperature_fault_threshold  
 * @param Drive_high_temperature_fault_threshold  
 * @param Overspeed_threshold  
 * @param Drive_overcurrent_threshold  
 * @param Protection_enable  
 * @param Motor_low_temperature_fault_threshold  
 * @param Motor_high_temperature_fault_threshold  
 * @param Can_timeout  
 * @param Motor_low_temperature_warning_threshold  
 * @param Motor_high_temperature_warning_threshold  
 * @param Mcu_temperature_threshold_time  
 * @param Mcu_low_temperature_fault_threshold  
 * @param Mcu_high_temperature_fault_threshold  
 * @param Mcu_low_temperature_warning_threshold  
 * @param Mcu_high_temperature_warning_threshold  
 * @param Drive_low_temperature_warning_threshold  
 * @param Drive_high_temperature_warning_threshold  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_appprotectconfig_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               float Bus_under_voltage_threshold, float Bus_over_voltage_threshold, float Drive_overload_current_duration, float Drive_peak_current_duration, float Drive_temperature_threshold_time, float Drive_low_temperature_fault_threshold, float Drive_high_temperature_fault_threshold, float Overspeed_threshold, float Drive_overcurrent_threshold, uint32_t Protection_enable, float Motor_low_temperature_fault_threshold, float Motor_high_temperature_fault_threshold, float Can_timeout, float Motor_low_temperature_warning_threshold, float Motor_high_temperature_warning_threshold, float Mcu_temperature_threshold_time, float Mcu_low_temperature_fault_threshold, float Mcu_high_temperature_fault_threshold, float Mcu_low_temperature_warning_threshold, float Mcu_high_temperature_warning_threshold, float Drive_low_temperature_warning_threshold, float Drive_high_temperature_warning_threshold)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_AppProtectConfig_LEN];
    _mav_put_float(buf, 0, Bus_under_voltage_threshold);
    _mav_put_float(buf, 4, Bus_over_voltage_threshold);
    _mav_put_float(buf, 8, Drive_overload_current_duration);
    _mav_put_float(buf, 12, Drive_peak_current_duration);
    _mav_put_float(buf, 16, Drive_temperature_threshold_time);
    _mav_put_float(buf, 20, Drive_low_temperature_fault_threshold);
    _mav_put_float(buf, 24, Drive_high_temperature_fault_threshold);
    _mav_put_float(buf, 28, Overspeed_threshold);
    _mav_put_float(buf, 32, Drive_overcurrent_threshold);
    _mav_put_uint32_t(buf, 36, Protection_enable);
    _mav_put_float(buf, 40, Motor_low_temperature_fault_threshold);
    _mav_put_float(buf, 44, Motor_high_temperature_fault_threshold);
    _mav_put_float(buf, 48, Can_timeout);
    _mav_put_float(buf, 52, Motor_low_temperature_warning_threshold);
    _mav_put_float(buf, 56, Motor_high_temperature_warning_threshold);
    _mav_put_float(buf, 60, Mcu_temperature_threshold_time);
    _mav_put_float(buf, 64, Mcu_low_temperature_fault_threshold);
    _mav_put_float(buf, 68, Mcu_high_temperature_fault_threshold);
    _mav_put_float(buf, 72, Mcu_low_temperature_warning_threshold);
    _mav_put_float(buf, 76, Mcu_high_temperature_warning_threshold);
    _mav_put_float(buf, 80, Drive_low_temperature_warning_threshold);
    _mav_put_float(buf, 84, Drive_high_temperature_warning_threshold);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_AppProtectConfig_LEN);
#else
    mavlink_appprotectconfig_t packet;
    packet.Bus_under_voltage_threshold = Bus_under_voltage_threshold;
    packet.Bus_over_voltage_threshold = Bus_over_voltage_threshold;
    packet.Drive_overload_current_duration = Drive_overload_current_duration;
    packet.Drive_peak_current_duration = Drive_peak_current_duration;
    packet.Drive_temperature_threshold_time = Drive_temperature_threshold_time;
    packet.Drive_low_temperature_fault_threshold = Drive_low_temperature_fault_threshold;
    packet.Drive_high_temperature_fault_threshold = Drive_high_temperature_fault_threshold;
    packet.Overspeed_threshold = Overspeed_threshold;
    packet.Drive_overcurrent_threshold = Drive_overcurrent_threshold;
    packet.Protection_enable = Protection_enable;
    packet.Motor_low_temperature_fault_threshold = Motor_low_temperature_fault_threshold;
    packet.Motor_high_temperature_fault_threshold = Motor_high_temperature_fault_threshold;
    packet.Can_timeout = Can_timeout;
    packet.Motor_low_temperature_warning_threshold = Motor_low_temperature_warning_threshold;
    packet.Motor_high_temperature_warning_threshold = Motor_high_temperature_warning_threshold;
    packet.Mcu_temperature_threshold_time = Mcu_temperature_threshold_time;
    packet.Mcu_low_temperature_fault_threshold = Mcu_low_temperature_fault_threshold;
    packet.Mcu_high_temperature_fault_threshold = Mcu_high_temperature_fault_threshold;
    packet.Mcu_low_temperature_warning_threshold = Mcu_low_temperature_warning_threshold;
    packet.Mcu_high_temperature_warning_threshold = Mcu_high_temperature_warning_threshold;
    packet.Drive_low_temperature_warning_threshold = Drive_low_temperature_warning_threshold;
    packet.Drive_high_temperature_warning_threshold = Drive_high_temperature_warning_threshold;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_AppProtectConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_AppProtectConfig;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_AppProtectConfig_MIN_LEN, MAVLINK_MSG_ID_AppProtectConfig_LEN, MAVLINK_MSG_ID_AppProtectConfig_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_AppProtectConfig_MIN_LEN, MAVLINK_MSG_ID_AppProtectConfig_LEN);
#endif
}

/**
 * @brief Pack a appprotectconfig message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param Bus_under_voltage_threshold  
 * @param Bus_over_voltage_threshold  
 * @param Drive_overload_current_duration  
 * @param Drive_peak_current_duration  
 * @param Drive_temperature_threshold_time  
 * @param Drive_low_temperature_fault_threshold  
 * @param Drive_high_temperature_fault_threshold  
 * @param Overspeed_threshold  
 * @param Drive_overcurrent_threshold  
 * @param Protection_enable  
 * @param Motor_low_temperature_fault_threshold  
 * @param Motor_high_temperature_fault_threshold  
 * @param Can_timeout  
 * @param Motor_low_temperature_warning_threshold  
 * @param Motor_high_temperature_warning_threshold  
 * @param Mcu_temperature_threshold_time  
 * @param Mcu_low_temperature_fault_threshold  
 * @param Mcu_high_temperature_fault_threshold  
 * @param Mcu_low_temperature_warning_threshold  
 * @param Mcu_high_temperature_warning_threshold  
 * @param Drive_low_temperature_warning_threshold  
 * @param Drive_high_temperature_warning_threshold  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_appprotectconfig_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   float Bus_under_voltage_threshold,float Bus_over_voltage_threshold,float Drive_overload_current_duration,float Drive_peak_current_duration,float Drive_temperature_threshold_time,float Drive_low_temperature_fault_threshold,float Drive_high_temperature_fault_threshold,float Overspeed_threshold,float Drive_overcurrent_threshold,uint32_t Protection_enable,float Motor_low_temperature_fault_threshold,float Motor_high_temperature_fault_threshold,float Can_timeout,float Motor_low_temperature_warning_threshold,float Motor_high_temperature_warning_threshold,float Mcu_temperature_threshold_time,float Mcu_low_temperature_fault_threshold,float Mcu_high_temperature_fault_threshold,float Mcu_low_temperature_warning_threshold,float Mcu_high_temperature_warning_threshold,float Drive_low_temperature_warning_threshold,float Drive_high_temperature_warning_threshold)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_AppProtectConfig_LEN];
    _mav_put_float(buf, 0, Bus_under_voltage_threshold);
    _mav_put_float(buf, 4, Bus_over_voltage_threshold);
    _mav_put_float(buf, 8, Drive_overload_current_duration);
    _mav_put_float(buf, 12, Drive_peak_current_duration);
    _mav_put_float(buf, 16, Drive_temperature_threshold_time);
    _mav_put_float(buf, 20, Drive_low_temperature_fault_threshold);
    _mav_put_float(buf, 24, Drive_high_temperature_fault_threshold);
    _mav_put_float(buf, 28, Overspeed_threshold);
    _mav_put_float(buf, 32, Drive_overcurrent_threshold);
    _mav_put_uint32_t(buf, 36, Protection_enable);
    _mav_put_float(buf, 40, Motor_low_temperature_fault_threshold);
    _mav_put_float(buf, 44, Motor_high_temperature_fault_threshold);
    _mav_put_float(buf, 48, Can_timeout);
    _mav_put_float(buf, 52, Motor_low_temperature_warning_threshold);
    _mav_put_float(buf, 56, Motor_high_temperature_warning_threshold);
    _mav_put_float(buf, 60, Mcu_temperature_threshold_time);
    _mav_put_float(buf, 64, Mcu_low_temperature_fault_threshold);
    _mav_put_float(buf, 68, Mcu_high_temperature_fault_threshold);
    _mav_put_float(buf, 72, Mcu_low_temperature_warning_threshold);
    _mav_put_float(buf, 76, Mcu_high_temperature_warning_threshold);
    _mav_put_float(buf, 80, Drive_low_temperature_warning_threshold);
    _mav_put_float(buf, 84, Drive_high_temperature_warning_threshold);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_AppProtectConfig_LEN);
#else
    mavlink_appprotectconfig_t packet;
    packet.Bus_under_voltage_threshold = Bus_under_voltage_threshold;
    packet.Bus_over_voltage_threshold = Bus_over_voltage_threshold;
    packet.Drive_overload_current_duration = Drive_overload_current_duration;
    packet.Drive_peak_current_duration = Drive_peak_current_duration;
    packet.Drive_temperature_threshold_time = Drive_temperature_threshold_time;
    packet.Drive_low_temperature_fault_threshold = Drive_low_temperature_fault_threshold;
    packet.Drive_high_temperature_fault_threshold = Drive_high_temperature_fault_threshold;
    packet.Overspeed_threshold = Overspeed_threshold;
    packet.Drive_overcurrent_threshold = Drive_overcurrent_threshold;
    packet.Protection_enable = Protection_enable;
    packet.Motor_low_temperature_fault_threshold = Motor_low_temperature_fault_threshold;
    packet.Motor_high_temperature_fault_threshold = Motor_high_temperature_fault_threshold;
    packet.Can_timeout = Can_timeout;
    packet.Motor_low_temperature_warning_threshold = Motor_low_temperature_warning_threshold;
    packet.Motor_high_temperature_warning_threshold = Motor_high_temperature_warning_threshold;
    packet.Mcu_temperature_threshold_time = Mcu_temperature_threshold_time;
    packet.Mcu_low_temperature_fault_threshold = Mcu_low_temperature_fault_threshold;
    packet.Mcu_high_temperature_fault_threshold = Mcu_high_temperature_fault_threshold;
    packet.Mcu_low_temperature_warning_threshold = Mcu_low_temperature_warning_threshold;
    packet.Mcu_high_temperature_warning_threshold = Mcu_high_temperature_warning_threshold;
    packet.Drive_low_temperature_warning_threshold = Drive_low_temperature_warning_threshold;
    packet.Drive_high_temperature_warning_threshold = Drive_high_temperature_warning_threshold;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_AppProtectConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_AppProtectConfig;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_AppProtectConfig_MIN_LEN, MAVLINK_MSG_ID_AppProtectConfig_LEN, MAVLINK_MSG_ID_AppProtectConfig_CRC);
}

/**
 * @brief Encode a appprotectconfig struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param appprotectconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_appprotectconfig_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_appprotectconfig_t* appprotectconfig)
{
    return mavlink_msg_appprotectconfig_pack(system_id, component_id, msg, appprotectconfig->Bus_under_voltage_threshold, appprotectconfig->Bus_over_voltage_threshold, appprotectconfig->Drive_overload_current_duration, appprotectconfig->Drive_peak_current_duration, appprotectconfig->Drive_temperature_threshold_time, appprotectconfig->Drive_low_temperature_fault_threshold, appprotectconfig->Drive_high_temperature_fault_threshold, appprotectconfig->Overspeed_threshold, appprotectconfig->Drive_overcurrent_threshold, appprotectconfig->Protection_enable, appprotectconfig->Motor_low_temperature_fault_threshold, appprotectconfig->Motor_high_temperature_fault_threshold, appprotectconfig->Can_timeout, appprotectconfig->Motor_low_temperature_warning_threshold, appprotectconfig->Motor_high_temperature_warning_threshold, appprotectconfig->Mcu_temperature_threshold_time, appprotectconfig->Mcu_low_temperature_fault_threshold, appprotectconfig->Mcu_high_temperature_fault_threshold, appprotectconfig->Mcu_low_temperature_warning_threshold, appprotectconfig->Mcu_high_temperature_warning_threshold, appprotectconfig->Drive_low_temperature_warning_threshold, appprotectconfig->Drive_high_temperature_warning_threshold);
}

/**
 * @brief Encode a appprotectconfig struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param appprotectconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_appprotectconfig_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_appprotectconfig_t* appprotectconfig)
{
    return mavlink_msg_appprotectconfig_pack_chan(system_id, component_id, chan, msg, appprotectconfig->Bus_under_voltage_threshold, appprotectconfig->Bus_over_voltage_threshold, appprotectconfig->Drive_overload_current_duration, appprotectconfig->Drive_peak_current_duration, appprotectconfig->Drive_temperature_threshold_time, appprotectconfig->Drive_low_temperature_fault_threshold, appprotectconfig->Drive_high_temperature_fault_threshold, appprotectconfig->Overspeed_threshold, appprotectconfig->Drive_overcurrent_threshold, appprotectconfig->Protection_enable, appprotectconfig->Motor_low_temperature_fault_threshold, appprotectconfig->Motor_high_temperature_fault_threshold, appprotectconfig->Can_timeout, appprotectconfig->Motor_low_temperature_warning_threshold, appprotectconfig->Motor_high_temperature_warning_threshold, appprotectconfig->Mcu_temperature_threshold_time, appprotectconfig->Mcu_low_temperature_fault_threshold, appprotectconfig->Mcu_high_temperature_fault_threshold, appprotectconfig->Mcu_low_temperature_warning_threshold, appprotectconfig->Mcu_high_temperature_warning_threshold, appprotectconfig->Drive_low_temperature_warning_threshold, appprotectconfig->Drive_high_temperature_warning_threshold);
}

/**
 * @brief Encode a appprotectconfig struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param appprotectconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_appprotectconfig_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_appprotectconfig_t* appprotectconfig)
{
    return mavlink_msg_appprotectconfig_pack_status(system_id, component_id, _status, msg,  appprotectconfig->Bus_under_voltage_threshold, appprotectconfig->Bus_over_voltage_threshold, appprotectconfig->Drive_overload_current_duration, appprotectconfig->Drive_peak_current_duration, appprotectconfig->Drive_temperature_threshold_time, appprotectconfig->Drive_low_temperature_fault_threshold, appprotectconfig->Drive_high_temperature_fault_threshold, appprotectconfig->Overspeed_threshold, appprotectconfig->Drive_overcurrent_threshold, appprotectconfig->Protection_enable, appprotectconfig->Motor_low_temperature_fault_threshold, appprotectconfig->Motor_high_temperature_fault_threshold, appprotectconfig->Can_timeout, appprotectconfig->Motor_low_temperature_warning_threshold, appprotectconfig->Motor_high_temperature_warning_threshold, appprotectconfig->Mcu_temperature_threshold_time, appprotectconfig->Mcu_low_temperature_fault_threshold, appprotectconfig->Mcu_high_temperature_fault_threshold, appprotectconfig->Mcu_low_temperature_warning_threshold, appprotectconfig->Mcu_high_temperature_warning_threshold, appprotectconfig->Drive_low_temperature_warning_threshold, appprotectconfig->Drive_high_temperature_warning_threshold);
}

/**
 * @brief Send a appprotectconfig message
 * @param chan MAVLink channel to send the message
 *
 * @param Bus_under_voltage_threshold  
 * @param Bus_over_voltage_threshold  
 * @param Drive_overload_current_duration  
 * @param Drive_peak_current_duration  
 * @param Drive_temperature_threshold_time  
 * @param Drive_low_temperature_fault_threshold  
 * @param Drive_high_temperature_fault_threshold  
 * @param Overspeed_threshold  
 * @param Drive_overcurrent_threshold  
 * @param Protection_enable  
 * @param Motor_low_temperature_fault_threshold  
 * @param Motor_high_temperature_fault_threshold  
 * @param Can_timeout  
 * @param Motor_low_temperature_warning_threshold  
 * @param Motor_high_temperature_warning_threshold  
 * @param Mcu_temperature_threshold_time  
 * @param Mcu_low_temperature_fault_threshold  
 * @param Mcu_high_temperature_fault_threshold  
 * @param Mcu_low_temperature_warning_threshold  
 * @param Mcu_high_temperature_warning_threshold  
 * @param Drive_low_temperature_warning_threshold  
 * @param Drive_high_temperature_warning_threshold  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_appprotectconfig_send(mavlink_channel_t chan, float Bus_under_voltage_threshold, float Bus_over_voltage_threshold, float Drive_overload_current_duration, float Drive_peak_current_duration, float Drive_temperature_threshold_time, float Drive_low_temperature_fault_threshold, float Drive_high_temperature_fault_threshold, float Overspeed_threshold, float Drive_overcurrent_threshold, uint32_t Protection_enable, float Motor_low_temperature_fault_threshold, float Motor_high_temperature_fault_threshold, float Can_timeout, float Motor_low_temperature_warning_threshold, float Motor_high_temperature_warning_threshold, float Mcu_temperature_threshold_time, float Mcu_low_temperature_fault_threshold, float Mcu_high_temperature_fault_threshold, float Mcu_low_temperature_warning_threshold, float Mcu_high_temperature_warning_threshold, float Drive_low_temperature_warning_threshold, float Drive_high_temperature_warning_threshold)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_AppProtectConfig_LEN];
    _mav_put_float(buf, 0, Bus_under_voltage_threshold);
    _mav_put_float(buf, 4, Bus_over_voltage_threshold);
    _mav_put_float(buf, 8, Drive_overload_current_duration);
    _mav_put_float(buf, 12, Drive_peak_current_duration);
    _mav_put_float(buf, 16, Drive_temperature_threshold_time);
    _mav_put_float(buf, 20, Drive_low_temperature_fault_threshold);
    _mav_put_float(buf, 24, Drive_high_temperature_fault_threshold);
    _mav_put_float(buf, 28, Overspeed_threshold);
    _mav_put_float(buf, 32, Drive_overcurrent_threshold);
    _mav_put_uint32_t(buf, 36, Protection_enable);
    _mav_put_float(buf, 40, Motor_low_temperature_fault_threshold);
    _mav_put_float(buf, 44, Motor_high_temperature_fault_threshold);
    _mav_put_float(buf, 48, Can_timeout);
    _mav_put_float(buf, 52, Motor_low_temperature_warning_threshold);
    _mav_put_float(buf, 56, Motor_high_temperature_warning_threshold);
    _mav_put_float(buf, 60, Mcu_temperature_threshold_time);
    _mav_put_float(buf, 64, Mcu_low_temperature_fault_threshold);
    _mav_put_float(buf, 68, Mcu_high_temperature_fault_threshold);
    _mav_put_float(buf, 72, Mcu_low_temperature_warning_threshold);
    _mav_put_float(buf, 76, Mcu_high_temperature_warning_threshold);
    _mav_put_float(buf, 80, Drive_low_temperature_warning_threshold);
    _mav_put_float(buf, 84, Drive_high_temperature_warning_threshold);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppProtectConfig, buf, MAVLINK_MSG_ID_AppProtectConfig_MIN_LEN, MAVLINK_MSG_ID_AppProtectConfig_LEN, MAVLINK_MSG_ID_AppProtectConfig_CRC);
#else
    mavlink_appprotectconfig_t packet;
    packet.Bus_under_voltage_threshold = Bus_under_voltage_threshold;
    packet.Bus_over_voltage_threshold = Bus_over_voltage_threshold;
    packet.Drive_overload_current_duration = Drive_overload_current_duration;
    packet.Drive_peak_current_duration = Drive_peak_current_duration;
    packet.Drive_temperature_threshold_time = Drive_temperature_threshold_time;
    packet.Drive_low_temperature_fault_threshold = Drive_low_temperature_fault_threshold;
    packet.Drive_high_temperature_fault_threshold = Drive_high_temperature_fault_threshold;
    packet.Overspeed_threshold = Overspeed_threshold;
    packet.Drive_overcurrent_threshold = Drive_overcurrent_threshold;
    packet.Protection_enable = Protection_enable;
    packet.Motor_low_temperature_fault_threshold = Motor_low_temperature_fault_threshold;
    packet.Motor_high_temperature_fault_threshold = Motor_high_temperature_fault_threshold;
    packet.Can_timeout = Can_timeout;
    packet.Motor_low_temperature_warning_threshold = Motor_low_temperature_warning_threshold;
    packet.Motor_high_temperature_warning_threshold = Motor_high_temperature_warning_threshold;
    packet.Mcu_temperature_threshold_time = Mcu_temperature_threshold_time;
    packet.Mcu_low_temperature_fault_threshold = Mcu_low_temperature_fault_threshold;
    packet.Mcu_high_temperature_fault_threshold = Mcu_high_temperature_fault_threshold;
    packet.Mcu_low_temperature_warning_threshold = Mcu_low_temperature_warning_threshold;
    packet.Mcu_high_temperature_warning_threshold = Mcu_high_temperature_warning_threshold;
    packet.Drive_low_temperature_warning_threshold = Drive_low_temperature_warning_threshold;
    packet.Drive_high_temperature_warning_threshold = Drive_high_temperature_warning_threshold;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppProtectConfig, (const char *)&packet, MAVLINK_MSG_ID_AppProtectConfig_MIN_LEN, MAVLINK_MSG_ID_AppProtectConfig_LEN, MAVLINK_MSG_ID_AppProtectConfig_CRC);
#endif
}

/**
 * @brief Send a appprotectconfig message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_appprotectconfig_send_struct(mavlink_channel_t chan, const mavlink_appprotectconfig_t* appprotectconfig)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_appprotectconfig_send(chan, appprotectconfig->Bus_under_voltage_threshold, appprotectconfig->Bus_over_voltage_threshold, appprotectconfig->Drive_overload_current_duration, appprotectconfig->Drive_peak_current_duration, appprotectconfig->Drive_temperature_threshold_time, appprotectconfig->Drive_low_temperature_fault_threshold, appprotectconfig->Drive_high_temperature_fault_threshold, appprotectconfig->Overspeed_threshold, appprotectconfig->Drive_overcurrent_threshold, appprotectconfig->Protection_enable, appprotectconfig->Motor_low_temperature_fault_threshold, appprotectconfig->Motor_high_temperature_fault_threshold, appprotectconfig->Can_timeout, appprotectconfig->Motor_low_temperature_warning_threshold, appprotectconfig->Motor_high_temperature_warning_threshold, appprotectconfig->Mcu_temperature_threshold_time, appprotectconfig->Mcu_low_temperature_fault_threshold, appprotectconfig->Mcu_high_temperature_fault_threshold, appprotectconfig->Mcu_low_temperature_warning_threshold, appprotectconfig->Mcu_high_temperature_warning_threshold, appprotectconfig->Drive_low_temperature_warning_threshold, appprotectconfig->Drive_high_temperature_warning_threshold);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppProtectConfig, (const char *)appprotectconfig, MAVLINK_MSG_ID_AppProtectConfig_MIN_LEN, MAVLINK_MSG_ID_AppProtectConfig_LEN, MAVLINK_MSG_ID_AppProtectConfig_CRC);
#endif
}

#if MAVLINK_MSG_ID_AppProtectConfig_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_appprotectconfig_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float Bus_under_voltage_threshold, float Bus_over_voltage_threshold, float Drive_overload_current_duration, float Drive_peak_current_duration, float Drive_temperature_threshold_time, float Drive_low_temperature_fault_threshold, float Drive_high_temperature_fault_threshold, float Overspeed_threshold, float Drive_overcurrent_threshold, uint32_t Protection_enable, float Motor_low_temperature_fault_threshold, float Motor_high_temperature_fault_threshold, float Can_timeout, float Motor_low_temperature_warning_threshold, float Motor_high_temperature_warning_threshold, float Mcu_temperature_threshold_time, float Mcu_low_temperature_fault_threshold, float Mcu_high_temperature_fault_threshold, float Mcu_low_temperature_warning_threshold, float Mcu_high_temperature_warning_threshold, float Drive_low_temperature_warning_threshold, float Drive_high_temperature_warning_threshold)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, Bus_under_voltage_threshold);
    _mav_put_float(buf, 4, Bus_over_voltage_threshold);
    _mav_put_float(buf, 8, Drive_overload_current_duration);
    _mav_put_float(buf, 12, Drive_peak_current_duration);
    _mav_put_float(buf, 16, Drive_temperature_threshold_time);
    _mav_put_float(buf, 20, Drive_low_temperature_fault_threshold);
    _mav_put_float(buf, 24, Drive_high_temperature_fault_threshold);
    _mav_put_float(buf, 28, Overspeed_threshold);
    _mav_put_float(buf, 32, Drive_overcurrent_threshold);
    _mav_put_uint32_t(buf, 36, Protection_enable);
    _mav_put_float(buf, 40, Motor_low_temperature_fault_threshold);
    _mav_put_float(buf, 44, Motor_high_temperature_fault_threshold);
    _mav_put_float(buf, 48, Can_timeout);
    _mav_put_float(buf, 52, Motor_low_temperature_warning_threshold);
    _mav_put_float(buf, 56, Motor_high_temperature_warning_threshold);
    _mav_put_float(buf, 60, Mcu_temperature_threshold_time);
    _mav_put_float(buf, 64, Mcu_low_temperature_fault_threshold);
    _mav_put_float(buf, 68, Mcu_high_temperature_fault_threshold);
    _mav_put_float(buf, 72, Mcu_low_temperature_warning_threshold);
    _mav_put_float(buf, 76, Mcu_high_temperature_warning_threshold);
    _mav_put_float(buf, 80, Drive_low_temperature_warning_threshold);
    _mav_put_float(buf, 84, Drive_high_temperature_warning_threshold);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppProtectConfig, buf, MAVLINK_MSG_ID_AppProtectConfig_MIN_LEN, MAVLINK_MSG_ID_AppProtectConfig_LEN, MAVLINK_MSG_ID_AppProtectConfig_CRC);
#else
    mavlink_appprotectconfig_t *packet = (mavlink_appprotectconfig_t *)msgbuf;
    packet->Bus_under_voltage_threshold = Bus_under_voltage_threshold;
    packet->Bus_over_voltage_threshold = Bus_over_voltage_threshold;
    packet->Drive_overload_current_duration = Drive_overload_current_duration;
    packet->Drive_peak_current_duration = Drive_peak_current_duration;
    packet->Drive_temperature_threshold_time = Drive_temperature_threshold_time;
    packet->Drive_low_temperature_fault_threshold = Drive_low_temperature_fault_threshold;
    packet->Drive_high_temperature_fault_threshold = Drive_high_temperature_fault_threshold;
    packet->Overspeed_threshold = Overspeed_threshold;
    packet->Drive_overcurrent_threshold = Drive_overcurrent_threshold;
    packet->Protection_enable = Protection_enable;
    packet->Motor_low_temperature_fault_threshold = Motor_low_temperature_fault_threshold;
    packet->Motor_high_temperature_fault_threshold = Motor_high_temperature_fault_threshold;
    packet->Can_timeout = Can_timeout;
    packet->Motor_low_temperature_warning_threshold = Motor_low_temperature_warning_threshold;
    packet->Motor_high_temperature_warning_threshold = Motor_high_temperature_warning_threshold;
    packet->Mcu_temperature_threshold_time = Mcu_temperature_threshold_time;
    packet->Mcu_low_temperature_fault_threshold = Mcu_low_temperature_fault_threshold;
    packet->Mcu_high_temperature_fault_threshold = Mcu_high_temperature_fault_threshold;
    packet->Mcu_low_temperature_warning_threshold = Mcu_low_temperature_warning_threshold;
    packet->Mcu_high_temperature_warning_threshold = Mcu_high_temperature_warning_threshold;
    packet->Drive_low_temperature_warning_threshold = Drive_low_temperature_warning_threshold;
    packet->Drive_high_temperature_warning_threshold = Drive_high_temperature_warning_threshold;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppProtectConfig, (const char *)packet, MAVLINK_MSG_ID_AppProtectConfig_MIN_LEN, MAVLINK_MSG_ID_AppProtectConfig_LEN, MAVLINK_MSG_ID_AppProtectConfig_CRC);
#endif
}
#endif

#endif

// MESSAGE AppProtectConfig UNPACKING


/**
 * @brief Get field Bus_under_voltage_threshold from appprotectconfig message
 *
 * @return  
 */
static inline float mavlink_msg_appprotectconfig_get_Bus_under_voltage_threshold(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field Bus_over_voltage_threshold from appprotectconfig message
 *
 * @return  
 */
static inline float mavlink_msg_appprotectconfig_get_Bus_over_voltage_threshold(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field Drive_overload_current_duration from appprotectconfig message
 *
 * @return  
 */
static inline float mavlink_msg_appprotectconfig_get_Drive_overload_current_duration(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field Drive_peak_current_duration from appprotectconfig message
 *
 * @return  
 */
static inline float mavlink_msg_appprotectconfig_get_Drive_peak_current_duration(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Get field Drive_temperature_threshold_time from appprotectconfig message
 *
 * @return  
 */
static inline float mavlink_msg_appprotectconfig_get_Drive_temperature_threshold_time(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  16);
}

/**
 * @brief Get field Drive_low_temperature_fault_threshold from appprotectconfig message
 *
 * @return  
 */
static inline float mavlink_msg_appprotectconfig_get_Drive_low_temperature_fault_threshold(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  20);
}

/**
 * @brief Get field Drive_high_temperature_fault_threshold from appprotectconfig message
 *
 * @return  
 */
static inline float mavlink_msg_appprotectconfig_get_Drive_high_temperature_fault_threshold(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  24);
}

/**
 * @brief Get field Overspeed_threshold from appprotectconfig message
 *
 * @return  
 */
static inline float mavlink_msg_appprotectconfig_get_Overspeed_threshold(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  28);
}

/**
 * @brief Get field Drive_overcurrent_threshold from appprotectconfig message
 *
 * @return  
 */
static inline float mavlink_msg_appprotectconfig_get_Drive_overcurrent_threshold(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  32);
}

/**
 * @brief Get field Protection_enable from appprotectconfig message
 *
 * @return  
 */
static inline uint32_t mavlink_msg_appprotectconfig_get_Protection_enable(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  36);
}

/**
 * @brief Get field Motor_low_temperature_fault_threshold from appprotectconfig message
 *
 * @return  
 */
static inline float mavlink_msg_appprotectconfig_get_Motor_low_temperature_fault_threshold(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  40);
}

/**
 * @brief Get field Motor_high_temperature_fault_threshold from appprotectconfig message
 *
 * @return  
 */
static inline float mavlink_msg_appprotectconfig_get_Motor_high_temperature_fault_threshold(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  44);
}

/**
 * @brief Get field Can_timeout from appprotectconfig message
 *
 * @return  
 */
static inline float mavlink_msg_appprotectconfig_get_Can_timeout(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  48);
}

/**
 * @brief Get field Motor_low_temperature_warning_threshold from appprotectconfig message
 *
 * @return  
 */
static inline float mavlink_msg_appprotectconfig_get_Motor_low_temperature_warning_threshold(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  52);
}

/**
 * @brief Get field Motor_high_temperature_warning_threshold from appprotectconfig message
 *
 * @return  
 */
static inline float mavlink_msg_appprotectconfig_get_Motor_high_temperature_warning_threshold(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  56);
}

/**
 * @brief Get field Mcu_temperature_threshold_time from appprotectconfig message
 *
 * @return  
 */
static inline float mavlink_msg_appprotectconfig_get_Mcu_temperature_threshold_time(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  60);
}

/**
 * @brief Get field Mcu_low_temperature_fault_threshold from appprotectconfig message
 *
 * @return  
 */
static inline float mavlink_msg_appprotectconfig_get_Mcu_low_temperature_fault_threshold(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  64);
}

/**
 * @brief Get field Mcu_high_temperature_fault_threshold from appprotectconfig message
 *
 * @return  
 */
static inline float mavlink_msg_appprotectconfig_get_Mcu_high_temperature_fault_threshold(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  68);
}

/**
 * @brief Get field Mcu_low_temperature_warning_threshold from appprotectconfig message
 *
 * @return  
 */
static inline float mavlink_msg_appprotectconfig_get_Mcu_low_temperature_warning_threshold(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  72);
}

/**
 * @brief Get field Mcu_high_temperature_warning_threshold from appprotectconfig message
 *
 * @return  
 */
static inline float mavlink_msg_appprotectconfig_get_Mcu_high_temperature_warning_threshold(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  76);
}

/**
 * @brief Get field Drive_low_temperature_warning_threshold from appprotectconfig message
 *
 * @return  
 */
static inline float mavlink_msg_appprotectconfig_get_Drive_low_temperature_warning_threshold(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  80);
}

/**
 * @brief Get field Drive_high_temperature_warning_threshold from appprotectconfig message
 *
 * @return  
 */
static inline float mavlink_msg_appprotectconfig_get_Drive_high_temperature_warning_threshold(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  84);
}

/**
 * @brief Decode a appprotectconfig message into a struct
 *
 * @param msg The message to decode
 * @param appprotectconfig C-struct to decode the message contents into
 */
static inline void mavlink_msg_appprotectconfig_decode(const mavlink_message_t* msg, mavlink_appprotectconfig_t* appprotectconfig)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    appprotectconfig->Bus_under_voltage_threshold = mavlink_msg_appprotectconfig_get_Bus_under_voltage_threshold(msg);
    appprotectconfig->Bus_over_voltage_threshold = mavlink_msg_appprotectconfig_get_Bus_over_voltage_threshold(msg);
    appprotectconfig->Drive_overload_current_duration = mavlink_msg_appprotectconfig_get_Drive_overload_current_duration(msg);
    appprotectconfig->Drive_peak_current_duration = mavlink_msg_appprotectconfig_get_Drive_peak_current_duration(msg);
    appprotectconfig->Drive_temperature_threshold_time = mavlink_msg_appprotectconfig_get_Drive_temperature_threshold_time(msg);
    appprotectconfig->Drive_low_temperature_fault_threshold = mavlink_msg_appprotectconfig_get_Drive_low_temperature_fault_threshold(msg);
    appprotectconfig->Drive_high_temperature_fault_threshold = mavlink_msg_appprotectconfig_get_Drive_high_temperature_fault_threshold(msg);
    appprotectconfig->Overspeed_threshold = mavlink_msg_appprotectconfig_get_Overspeed_threshold(msg);
    appprotectconfig->Drive_overcurrent_threshold = mavlink_msg_appprotectconfig_get_Drive_overcurrent_threshold(msg);
    appprotectconfig->Protection_enable = mavlink_msg_appprotectconfig_get_Protection_enable(msg);
    appprotectconfig->Motor_low_temperature_fault_threshold = mavlink_msg_appprotectconfig_get_Motor_low_temperature_fault_threshold(msg);
    appprotectconfig->Motor_high_temperature_fault_threshold = mavlink_msg_appprotectconfig_get_Motor_high_temperature_fault_threshold(msg);
    appprotectconfig->Can_timeout = mavlink_msg_appprotectconfig_get_Can_timeout(msg);
    appprotectconfig->Motor_low_temperature_warning_threshold = mavlink_msg_appprotectconfig_get_Motor_low_temperature_warning_threshold(msg);
    appprotectconfig->Motor_high_temperature_warning_threshold = mavlink_msg_appprotectconfig_get_Motor_high_temperature_warning_threshold(msg);
    appprotectconfig->Mcu_temperature_threshold_time = mavlink_msg_appprotectconfig_get_Mcu_temperature_threshold_time(msg);
    appprotectconfig->Mcu_low_temperature_fault_threshold = mavlink_msg_appprotectconfig_get_Mcu_low_temperature_fault_threshold(msg);
    appprotectconfig->Mcu_high_temperature_fault_threshold = mavlink_msg_appprotectconfig_get_Mcu_high_temperature_fault_threshold(msg);
    appprotectconfig->Mcu_low_temperature_warning_threshold = mavlink_msg_appprotectconfig_get_Mcu_low_temperature_warning_threshold(msg);
    appprotectconfig->Mcu_high_temperature_warning_threshold = mavlink_msg_appprotectconfig_get_Mcu_high_temperature_warning_threshold(msg);
    appprotectconfig->Drive_low_temperature_warning_threshold = mavlink_msg_appprotectconfig_get_Drive_low_temperature_warning_threshold(msg);
    appprotectconfig->Drive_high_temperature_warning_threshold = mavlink_msg_appprotectconfig_get_Drive_high_temperature_warning_threshold(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_AppProtectConfig_LEN? msg->len : MAVLINK_MSG_ID_AppProtectConfig_LEN;
        memset(appprotectconfig, 0, MAVLINK_MSG_ID_AppProtectConfig_LEN);
    memcpy(appprotectconfig, _MAV_PAYLOAD(msg), len);
#endif
}
