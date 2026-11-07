#pragma once
// MESSAGE AppMotionParam PACKING

#define MAVLINK_MSG_ID_AppMotionParam 30059


typedef struct __mavlink_appmotionparam_t {
 int64_t Target_position; /*<  */
 int64_t Home_offset; /*<  */
 int64_t MIT_target_position; /*<  */
 float Profile_velocity; /*<  */
 float Profile_acceleration; /*<  */
 float Profile_deceleration; /*<  */
 float Quick_stop_deceleration; /*<  */
 int32_t Motion_profile_type; /*<  */
 float Target_velocity; /*<  */
 float Target_torque; /*<  */
 float Torque_slope; /*<  */
 float Encoder_calibration_speed; /*<  */
 float MIT_feedforward_torque; /*<  */
 float MIT_max_current; /*<  */
 float MIT_target_velocity; /*<  */
 float MIT_kp; /*<  */
 float MIT_kd; /*<  */
 float Homing_speed_search_for_switch; /*<  */
 float Homing_speed_search_for_zero; /*<  */
 float Homing_acceleration; /*<  */
 int8_t Homing_method; /*<  */
 uint8_t Interp_time_value; /*<  */
 int8_t Interp_time_index; /*<  */
} mavlink_appmotionparam_t;

#define MAVLINK_MSG_ID_AppMotionParam_LEN 95
#define MAVLINK_MSG_ID_AppMotionParam_MIN_LEN 95
#define MAVLINK_MSG_ID_30059_LEN 95
#define MAVLINK_MSG_ID_30059_MIN_LEN 95

#define MAVLINK_MSG_ID_AppMotionParam_CRC 221
#define MAVLINK_MSG_ID_30059_CRC 221



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_AppMotionParam { \
    30059, \
    "AppMotionParam", \
    23, \
    {  { "Target_position", NULL, MAVLINK_TYPE_INT64_T, 0, 0, offsetof(mavlink_appmotionparam_t, Target_position) }, \
         { "Profile_velocity", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_appmotionparam_t, Profile_velocity) }, \
         { "Profile_acceleration", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_appmotionparam_t, Profile_acceleration) }, \
         { "Profile_deceleration", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_appmotionparam_t, Profile_deceleration) }, \
         { "Quick_stop_deceleration", NULL, MAVLINK_TYPE_FLOAT, 0, 36, offsetof(mavlink_appmotionparam_t, Quick_stop_deceleration) }, \
         { "Motion_profile_type", NULL, MAVLINK_TYPE_INT32_T, 0, 40, offsetof(mavlink_appmotionparam_t, Motion_profile_type) }, \
         { "Home_offset", NULL, MAVLINK_TYPE_INT64_T, 0, 8, offsetof(mavlink_appmotionparam_t, Home_offset) }, \
         { "Homing_method", NULL, MAVLINK_TYPE_INT8_T, 0, 92, offsetof(mavlink_appmotionparam_t, Homing_method) }, \
         { "Target_velocity", NULL, MAVLINK_TYPE_FLOAT, 0, 44, offsetof(mavlink_appmotionparam_t, Target_velocity) }, \
         { "Target_torque", NULL, MAVLINK_TYPE_FLOAT, 0, 48, offsetof(mavlink_appmotionparam_t, Target_torque) }, \
         { "Torque_slope", NULL, MAVLINK_TYPE_FLOAT, 0, 52, offsetof(mavlink_appmotionparam_t, Torque_slope) }, \
         { "Encoder_calibration_speed", NULL, MAVLINK_TYPE_FLOAT, 0, 56, offsetof(mavlink_appmotionparam_t, Encoder_calibration_speed) }, \
         { "MIT_feedforward_torque", NULL, MAVLINK_TYPE_FLOAT, 0, 60, offsetof(mavlink_appmotionparam_t, MIT_feedforward_torque) }, \
         { "MIT_target_position", NULL, MAVLINK_TYPE_INT64_T, 0, 16, offsetof(mavlink_appmotionparam_t, MIT_target_position) }, \
         { "MIT_max_current", NULL, MAVLINK_TYPE_FLOAT, 0, 64, offsetof(mavlink_appmotionparam_t, MIT_max_current) }, \
         { "MIT_target_velocity", NULL, MAVLINK_TYPE_FLOAT, 0, 68, offsetof(mavlink_appmotionparam_t, MIT_target_velocity) }, \
         { "MIT_kp", NULL, MAVLINK_TYPE_FLOAT, 0, 72, offsetof(mavlink_appmotionparam_t, MIT_kp) }, \
         { "MIT_kd", NULL, MAVLINK_TYPE_FLOAT, 0, 76, offsetof(mavlink_appmotionparam_t, MIT_kd) }, \
         { "Interp_time_value", NULL, MAVLINK_TYPE_UINT8_T, 0, 93, offsetof(mavlink_appmotionparam_t, Interp_time_value) }, \
         { "Interp_time_index", NULL, MAVLINK_TYPE_INT8_T, 0, 94, offsetof(mavlink_appmotionparam_t, Interp_time_index) }, \
         { "Homing_speed_search_for_switch", NULL, MAVLINK_TYPE_FLOAT, 0, 80, offsetof(mavlink_appmotionparam_t, Homing_speed_search_for_switch) }, \
         { "Homing_speed_search_for_zero", NULL, MAVLINK_TYPE_FLOAT, 0, 84, offsetof(mavlink_appmotionparam_t, Homing_speed_search_for_zero) }, \
         { "Homing_acceleration", NULL, MAVLINK_TYPE_FLOAT, 0, 88, offsetof(mavlink_appmotionparam_t, Homing_acceleration) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_AppMotionParam { \
    "AppMotionParam", \
    23, \
    {  { "Target_position", NULL, MAVLINK_TYPE_INT64_T, 0, 0, offsetof(mavlink_appmotionparam_t, Target_position) }, \
         { "Profile_velocity", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_appmotionparam_t, Profile_velocity) }, \
         { "Profile_acceleration", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_appmotionparam_t, Profile_acceleration) }, \
         { "Profile_deceleration", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_appmotionparam_t, Profile_deceleration) }, \
         { "Quick_stop_deceleration", NULL, MAVLINK_TYPE_FLOAT, 0, 36, offsetof(mavlink_appmotionparam_t, Quick_stop_deceleration) }, \
         { "Motion_profile_type", NULL, MAVLINK_TYPE_INT32_T, 0, 40, offsetof(mavlink_appmotionparam_t, Motion_profile_type) }, \
         { "Home_offset", NULL, MAVLINK_TYPE_INT64_T, 0, 8, offsetof(mavlink_appmotionparam_t, Home_offset) }, \
         { "Homing_method", NULL, MAVLINK_TYPE_INT8_T, 0, 92, offsetof(mavlink_appmotionparam_t, Homing_method) }, \
         { "Target_velocity", NULL, MAVLINK_TYPE_FLOAT, 0, 44, offsetof(mavlink_appmotionparam_t, Target_velocity) }, \
         { "Target_torque", NULL, MAVLINK_TYPE_FLOAT, 0, 48, offsetof(mavlink_appmotionparam_t, Target_torque) }, \
         { "Torque_slope", NULL, MAVLINK_TYPE_FLOAT, 0, 52, offsetof(mavlink_appmotionparam_t, Torque_slope) }, \
         { "Encoder_calibration_speed", NULL, MAVLINK_TYPE_FLOAT, 0, 56, offsetof(mavlink_appmotionparam_t, Encoder_calibration_speed) }, \
         { "MIT_feedforward_torque", NULL, MAVLINK_TYPE_FLOAT, 0, 60, offsetof(mavlink_appmotionparam_t, MIT_feedforward_torque) }, \
         { "MIT_target_position", NULL, MAVLINK_TYPE_INT64_T, 0, 16, offsetof(mavlink_appmotionparam_t, MIT_target_position) }, \
         { "MIT_max_current", NULL, MAVLINK_TYPE_FLOAT, 0, 64, offsetof(mavlink_appmotionparam_t, MIT_max_current) }, \
         { "MIT_target_velocity", NULL, MAVLINK_TYPE_FLOAT, 0, 68, offsetof(mavlink_appmotionparam_t, MIT_target_velocity) }, \
         { "MIT_kp", NULL, MAVLINK_TYPE_FLOAT, 0, 72, offsetof(mavlink_appmotionparam_t, MIT_kp) }, \
         { "MIT_kd", NULL, MAVLINK_TYPE_FLOAT, 0, 76, offsetof(mavlink_appmotionparam_t, MIT_kd) }, \
         { "Interp_time_value", NULL, MAVLINK_TYPE_UINT8_T, 0, 93, offsetof(mavlink_appmotionparam_t, Interp_time_value) }, \
         { "Interp_time_index", NULL, MAVLINK_TYPE_INT8_T, 0, 94, offsetof(mavlink_appmotionparam_t, Interp_time_index) }, \
         { "Homing_speed_search_for_switch", NULL, MAVLINK_TYPE_FLOAT, 0, 80, offsetof(mavlink_appmotionparam_t, Homing_speed_search_for_switch) }, \
         { "Homing_speed_search_for_zero", NULL, MAVLINK_TYPE_FLOAT, 0, 84, offsetof(mavlink_appmotionparam_t, Homing_speed_search_for_zero) }, \
         { "Homing_acceleration", NULL, MAVLINK_TYPE_FLOAT, 0, 88, offsetof(mavlink_appmotionparam_t, Homing_acceleration) }, \
         } \
}
#endif

/**
 * @brief Pack a appmotionparam message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param Target_position  
 * @param Profile_velocity  
 * @param Profile_acceleration  
 * @param Profile_deceleration  
 * @param Quick_stop_deceleration  
 * @param Motion_profile_type  
 * @param Home_offset  
 * @param Homing_method  
 * @param Target_velocity  
 * @param Target_torque  
 * @param Torque_slope  
 * @param Encoder_calibration_speed  
 * @param MIT_feedforward_torque  
 * @param MIT_target_position  
 * @param MIT_max_current  
 * @param MIT_target_velocity  
 * @param MIT_kp  
 * @param MIT_kd  
 * @param Interp_time_value  
 * @param Interp_time_index  
 * @param Homing_speed_search_for_switch  
 * @param Homing_speed_search_for_zero  
 * @param Homing_acceleration  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_appmotionparam_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               int64_t Target_position, float Profile_velocity, float Profile_acceleration, float Profile_deceleration, float Quick_stop_deceleration, int32_t Motion_profile_type, int64_t Home_offset, int8_t Homing_method, float Target_velocity, float Target_torque, float Torque_slope, float Encoder_calibration_speed, float MIT_feedforward_torque, int64_t MIT_target_position, float MIT_max_current, float MIT_target_velocity, float MIT_kp, float MIT_kd, uint8_t Interp_time_value, int8_t Interp_time_index, float Homing_speed_search_for_switch, float Homing_speed_search_for_zero, float Homing_acceleration)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_AppMotionParam_LEN];
    _mav_put_int64_t(buf, 0, Target_position);
    _mav_put_int64_t(buf, 8, Home_offset);
    _mav_put_int64_t(buf, 16, MIT_target_position);
    _mav_put_float(buf, 24, Profile_velocity);
    _mav_put_float(buf, 28, Profile_acceleration);
    _mav_put_float(buf, 32, Profile_deceleration);
    _mav_put_float(buf, 36, Quick_stop_deceleration);
    _mav_put_int32_t(buf, 40, Motion_profile_type);
    _mav_put_float(buf, 44, Target_velocity);
    _mav_put_float(buf, 48, Target_torque);
    _mav_put_float(buf, 52, Torque_slope);
    _mav_put_float(buf, 56, Encoder_calibration_speed);
    _mav_put_float(buf, 60, MIT_feedforward_torque);
    _mav_put_float(buf, 64, MIT_max_current);
    _mav_put_float(buf, 68, MIT_target_velocity);
    _mav_put_float(buf, 72, MIT_kp);
    _mav_put_float(buf, 76, MIT_kd);
    _mav_put_float(buf, 80, Homing_speed_search_for_switch);
    _mav_put_float(buf, 84, Homing_speed_search_for_zero);
    _mav_put_float(buf, 88, Homing_acceleration);
    _mav_put_int8_t(buf, 92, Homing_method);
    _mav_put_uint8_t(buf, 93, Interp_time_value);
    _mav_put_int8_t(buf, 94, Interp_time_index);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_AppMotionParam_LEN);
#else
    mavlink_appmotionparam_t packet;
    packet.Target_position = Target_position;
    packet.Home_offset = Home_offset;
    packet.MIT_target_position = MIT_target_position;
    packet.Profile_velocity = Profile_velocity;
    packet.Profile_acceleration = Profile_acceleration;
    packet.Profile_deceleration = Profile_deceleration;
    packet.Quick_stop_deceleration = Quick_stop_deceleration;
    packet.Motion_profile_type = Motion_profile_type;
    packet.Target_velocity = Target_velocity;
    packet.Target_torque = Target_torque;
    packet.Torque_slope = Torque_slope;
    packet.Encoder_calibration_speed = Encoder_calibration_speed;
    packet.MIT_feedforward_torque = MIT_feedforward_torque;
    packet.MIT_max_current = MIT_max_current;
    packet.MIT_target_velocity = MIT_target_velocity;
    packet.MIT_kp = MIT_kp;
    packet.MIT_kd = MIT_kd;
    packet.Homing_speed_search_for_switch = Homing_speed_search_for_switch;
    packet.Homing_speed_search_for_zero = Homing_speed_search_for_zero;
    packet.Homing_acceleration = Homing_acceleration;
    packet.Homing_method = Homing_method;
    packet.Interp_time_value = Interp_time_value;
    packet.Interp_time_index = Interp_time_index;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_AppMotionParam_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_AppMotionParam;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_AppMotionParam_MIN_LEN, MAVLINK_MSG_ID_AppMotionParam_LEN, MAVLINK_MSG_ID_AppMotionParam_CRC);
}

/**
 * @brief Pack a appmotionparam message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param Target_position  
 * @param Profile_velocity  
 * @param Profile_acceleration  
 * @param Profile_deceleration  
 * @param Quick_stop_deceleration  
 * @param Motion_profile_type  
 * @param Home_offset  
 * @param Homing_method  
 * @param Target_velocity  
 * @param Target_torque  
 * @param Torque_slope  
 * @param Encoder_calibration_speed  
 * @param MIT_feedforward_torque  
 * @param MIT_target_position  
 * @param MIT_max_current  
 * @param MIT_target_velocity  
 * @param MIT_kp  
 * @param MIT_kd  
 * @param Interp_time_value  
 * @param Interp_time_index  
 * @param Homing_speed_search_for_switch  
 * @param Homing_speed_search_for_zero  
 * @param Homing_acceleration  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_appmotionparam_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               int64_t Target_position, float Profile_velocity, float Profile_acceleration, float Profile_deceleration, float Quick_stop_deceleration, int32_t Motion_profile_type, int64_t Home_offset, int8_t Homing_method, float Target_velocity, float Target_torque, float Torque_slope, float Encoder_calibration_speed, float MIT_feedforward_torque, int64_t MIT_target_position, float MIT_max_current, float MIT_target_velocity, float MIT_kp, float MIT_kd, uint8_t Interp_time_value, int8_t Interp_time_index, float Homing_speed_search_for_switch, float Homing_speed_search_for_zero, float Homing_acceleration)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_AppMotionParam_LEN];
    _mav_put_int64_t(buf, 0, Target_position);
    _mav_put_int64_t(buf, 8, Home_offset);
    _mav_put_int64_t(buf, 16, MIT_target_position);
    _mav_put_float(buf, 24, Profile_velocity);
    _mav_put_float(buf, 28, Profile_acceleration);
    _mav_put_float(buf, 32, Profile_deceleration);
    _mav_put_float(buf, 36, Quick_stop_deceleration);
    _mav_put_int32_t(buf, 40, Motion_profile_type);
    _mav_put_float(buf, 44, Target_velocity);
    _mav_put_float(buf, 48, Target_torque);
    _mav_put_float(buf, 52, Torque_slope);
    _mav_put_float(buf, 56, Encoder_calibration_speed);
    _mav_put_float(buf, 60, MIT_feedforward_torque);
    _mav_put_float(buf, 64, MIT_max_current);
    _mav_put_float(buf, 68, MIT_target_velocity);
    _mav_put_float(buf, 72, MIT_kp);
    _mav_put_float(buf, 76, MIT_kd);
    _mav_put_float(buf, 80, Homing_speed_search_for_switch);
    _mav_put_float(buf, 84, Homing_speed_search_for_zero);
    _mav_put_float(buf, 88, Homing_acceleration);
    _mav_put_int8_t(buf, 92, Homing_method);
    _mav_put_uint8_t(buf, 93, Interp_time_value);
    _mav_put_int8_t(buf, 94, Interp_time_index);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_AppMotionParam_LEN);
#else
    mavlink_appmotionparam_t packet;
    packet.Target_position = Target_position;
    packet.Home_offset = Home_offset;
    packet.MIT_target_position = MIT_target_position;
    packet.Profile_velocity = Profile_velocity;
    packet.Profile_acceleration = Profile_acceleration;
    packet.Profile_deceleration = Profile_deceleration;
    packet.Quick_stop_deceleration = Quick_stop_deceleration;
    packet.Motion_profile_type = Motion_profile_type;
    packet.Target_velocity = Target_velocity;
    packet.Target_torque = Target_torque;
    packet.Torque_slope = Torque_slope;
    packet.Encoder_calibration_speed = Encoder_calibration_speed;
    packet.MIT_feedforward_torque = MIT_feedforward_torque;
    packet.MIT_max_current = MIT_max_current;
    packet.MIT_target_velocity = MIT_target_velocity;
    packet.MIT_kp = MIT_kp;
    packet.MIT_kd = MIT_kd;
    packet.Homing_speed_search_for_switch = Homing_speed_search_for_switch;
    packet.Homing_speed_search_for_zero = Homing_speed_search_for_zero;
    packet.Homing_acceleration = Homing_acceleration;
    packet.Homing_method = Homing_method;
    packet.Interp_time_value = Interp_time_value;
    packet.Interp_time_index = Interp_time_index;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_AppMotionParam_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_AppMotionParam;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_AppMotionParam_MIN_LEN, MAVLINK_MSG_ID_AppMotionParam_LEN, MAVLINK_MSG_ID_AppMotionParam_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_AppMotionParam_MIN_LEN, MAVLINK_MSG_ID_AppMotionParam_LEN);
#endif
}

/**
 * @brief Pack a appmotionparam message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param Target_position  
 * @param Profile_velocity  
 * @param Profile_acceleration  
 * @param Profile_deceleration  
 * @param Quick_stop_deceleration  
 * @param Motion_profile_type  
 * @param Home_offset  
 * @param Homing_method  
 * @param Target_velocity  
 * @param Target_torque  
 * @param Torque_slope  
 * @param Encoder_calibration_speed  
 * @param MIT_feedforward_torque  
 * @param MIT_target_position  
 * @param MIT_max_current  
 * @param MIT_target_velocity  
 * @param MIT_kp  
 * @param MIT_kd  
 * @param Interp_time_value  
 * @param Interp_time_index  
 * @param Homing_speed_search_for_switch  
 * @param Homing_speed_search_for_zero  
 * @param Homing_acceleration  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_appmotionparam_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   int64_t Target_position,float Profile_velocity,float Profile_acceleration,float Profile_deceleration,float Quick_stop_deceleration,int32_t Motion_profile_type,int64_t Home_offset,int8_t Homing_method,float Target_velocity,float Target_torque,float Torque_slope,float Encoder_calibration_speed,float MIT_feedforward_torque,int64_t MIT_target_position,float MIT_max_current,float MIT_target_velocity,float MIT_kp,float MIT_kd,uint8_t Interp_time_value,int8_t Interp_time_index,float Homing_speed_search_for_switch,float Homing_speed_search_for_zero,float Homing_acceleration)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_AppMotionParam_LEN];
    _mav_put_int64_t(buf, 0, Target_position);
    _mav_put_int64_t(buf, 8, Home_offset);
    _mav_put_int64_t(buf, 16, MIT_target_position);
    _mav_put_float(buf, 24, Profile_velocity);
    _mav_put_float(buf, 28, Profile_acceleration);
    _mav_put_float(buf, 32, Profile_deceleration);
    _mav_put_float(buf, 36, Quick_stop_deceleration);
    _mav_put_int32_t(buf, 40, Motion_profile_type);
    _mav_put_float(buf, 44, Target_velocity);
    _mav_put_float(buf, 48, Target_torque);
    _mav_put_float(buf, 52, Torque_slope);
    _mav_put_float(buf, 56, Encoder_calibration_speed);
    _mav_put_float(buf, 60, MIT_feedforward_torque);
    _mav_put_float(buf, 64, MIT_max_current);
    _mav_put_float(buf, 68, MIT_target_velocity);
    _mav_put_float(buf, 72, MIT_kp);
    _mav_put_float(buf, 76, MIT_kd);
    _mav_put_float(buf, 80, Homing_speed_search_for_switch);
    _mav_put_float(buf, 84, Homing_speed_search_for_zero);
    _mav_put_float(buf, 88, Homing_acceleration);
    _mav_put_int8_t(buf, 92, Homing_method);
    _mav_put_uint8_t(buf, 93, Interp_time_value);
    _mav_put_int8_t(buf, 94, Interp_time_index);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_AppMotionParam_LEN);
#else
    mavlink_appmotionparam_t packet;
    packet.Target_position = Target_position;
    packet.Home_offset = Home_offset;
    packet.MIT_target_position = MIT_target_position;
    packet.Profile_velocity = Profile_velocity;
    packet.Profile_acceleration = Profile_acceleration;
    packet.Profile_deceleration = Profile_deceleration;
    packet.Quick_stop_deceleration = Quick_stop_deceleration;
    packet.Motion_profile_type = Motion_profile_type;
    packet.Target_velocity = Target_velocity;
    packet.Target_torque = Target_torque;
    packet.Torque_slope = Torque_slope;
    packet.Encoder_calibration_speed = Encoder_calibration_speed;
    packet.MIT_feedforward_torque = MIT_feedforward_torque;
    packet.MIT_max_current = MIT_max_current;
    packet.MIT_target_velocity = MIT_target_velocity;
    packet.MIT_kp = MIT_kp;
    packet.MIT_kd = MIT_kd;
    packet.Homing_speed_search_for_switch = Homing_speed_search_for_switch;
    packet.Homing_speed_search_for_zero = Homing_speed_search_for_zero;
    packet.Homing_acceleration = Homing_acceleration;
    packet.Homing_method = Homing_method;
    packet.Interp_time_value = Interp_time_value;
    packet.Interp_time_index = Interp_time_index;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_AppMotionParam_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_AppMotionParam;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_AppMotionParam_MIN_LEN, MAVLINK_MSG_ID_AppMotionParam_LEN, MAVLINK_MSG_ID_AppMotionParam_CRC);
}

/**
 * @brief Encode a appmotionparam struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param appmotionparam C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_appmotionparam_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_appmotionparam_t* appmotionparam)
{
    return mavlink_msg_appmotionparam_pack(system_id, component_id, msg, appmotionparam->Target_position, appmotionparam->Profile_velocity, appmotionparam->Profile_acceleration, appmotionparam->Profile_deceleration, appmotionparam->Quick_stop_deceleration, appmotionparam->Motion_profile_type, appmotionparam->Home_offset, appmotionparam->Homing_method, appmotionparam->Target_velocity, appmotionparam->Target_torque, appmotionparam->Torque_slope, appmotionparam->Encoder_calibration_speed, appmotionparam->MIT_feedforward_torque, appmotionparam->MIT_target_position, appmotionparam->MIT_max_current, appmotionparam->MIT_target_velocity, appmotionparam->MIT_kp, appmotionparam->MIT_kd, appmotionparam->Interp_time_value, appmotionparam->Interp_time_index, appmotionparam->Homing_speed_search_for_switch, appmotionparam->Homing_speed_search_for_zero, appmotionparam->Homing_acceleration);
}

/**
 * @brief Encode a appmotionparam struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param appmotionparam C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_appmotionparam_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_appmotionparam_t* appmotionparam)
{
    return mavlink_msg_appmotionparam_pack_chan(system_id, component_id, chan, msg, appmotionparam->Target_position, appmotionparam->Profile_velocity, appmotionparam->Profile_acceleration, appmotionparam->Profile_deceleration, appmotionparam->Quick_stop_deceleration, appmotionparam->Motion_profile_type, appmotionparam->Home_offset, appmotionparam->Homing_method, appmotionparam->Target_velocity, appmotionparam->Target_torque, appmotionparam->Torque_slope, appmotionparam->Encoder_calibration_speed, appmotionparam->MIT_feedforward_torque, appmotionparam->MIT_target_position, appmotionparam->MIT_max_current, appmotionparam->MIT_target_velocity, appmotionparam->MIT_kp, appmotionparam->MIT_kd, appmotionparam->Interp_time_value, appmotionparam->Interp_time_index, appmotionparam->Homing_speed_search_for_switch, appmotionparam->Homing_speed_search_for_zero, appmotionparam->Homing_acceleration);
}

/**
 * @brief Encode a appmotionparam struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param appmotionparam C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_appmotionparam_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_appmotionparam_t* appmotionparam)
{
    return mavlink_msg_appmotionparam_pack_status(system_id, component_id, _status, msg,  appmotionparam->Target_position, appmotionparam->Profile_velocity, appmotionparam->Profile_acceleration, appmotionparam->Profile_deceleration, appmotionparam->Quick_stop_deceleration, appmotionparam->Motion_profile_type, appmotionparam->Home_offset, appmotionparam->Homing_method, appmotionparam->Target_velocity, appmotionparam->Target_torque, appmotionparam->Torque_slope, appmotionparam->Encoder_calibration_speed, appmotionparam->MIT_feedforward_torque, appmotionparam->MIT_target_position, appmotionparam->MIT_max_current, appmotionparam->MIT_target_velocity, appmotionparam->MIT_kp, appmotionparam->MIT_kd, appmotionparam->Interp_time_value, appmotionparam->Interp_time_index, appmotionparam->Homing_speed_search_for_switch, appmotionparam->Homing_speed_search_for_zero, appmotionparam->Homing_acceleration);
}

/**
 * @brief Send a appmotionparam message
 * @param chan MAVLink channel to send the message
 *
 * @param Target_position  
 * @param Profile_velocity  
 * @param Profile_acceleration  
 * @param Profile_deceleration  
 * @param Quick_stop_deceleration  
 * @param Motion_profile_type  
 * @param Home_offset  
 * @param Homing_method  
 * @param Target_velocity  
 * @param Target_torque  
 * @param Torque_slope  
 * @param Encoder_calibration_speed  
 * @param MIT_feedforward_torque  
 * @param MIT_target_position  
 * @param MIT_max_current  
 * @param MIT_target_velocity  
 * @param MIT_kp  
 * @param MIT_kd  
 * @param Interp_time_value  
 * @param Interp_time_index  
 * @param Homing_speed_search_for_switch  
 * @param Homing_speed_search_for_zero  
 * @param Homing_acceleration  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_appmotionparam_send(mavlink_channel_t chan, int64_t Target_position, float Profile_velocity, float Profile_acceleration, float Profile_deceleration, float Quick_stop_deceleration, int32_t Motion_profile_type, int64_t Home_offset, int8_t Homing_method, float Target_velocity, float Target_torque, float Torque_slope, float Encoder_calibration_speed, float MIT_feedforward_torque, int64_t MIT_target_position, float MIT_max_current, float MIT_target_velocity, float MIT_kp, float MIT_kd, uint8_t Interp_time_value, int8_t Interp_time_index, float Homing_speed_search_for_switch, float Homing_speed_search_for_zero, float Homing_acceleration)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_AppMotionParam_LEN];
    _mav_put_int64_t(buf, 0, Target_position);
    _mav_put_int64_t(buf, 8, Home_offset);
    _mav_put_int64_t(buf, 16, MIT_target_position);
    _mav_put_float(buf, 24, Profile_velocity);
    _mav_put_float(buf, 28, Profile_acceleration);
    _mav_put_float(buf, 32, Profile_deceleration);
    _mav_put_float(buf, 36, Quick_stop_deceleration);
    _mav_put_int32_t(buf, 40, Motion_profile_type);
    _mav_put_float(buf, 44, Target_velocity);
    _mav_put_float(buf, 48, Target_torque);
    _mav_put_float(buf, 52, Torque_slope);
    _mav_put_float(buf, 56, Encoder_calibration_speed);
    _mav_put_float(buf, 60, MIT_feedforward_torque);
    _mav_put_float(buf, 64, MIT_max_current);
    _mav_put_float(buf, 68, MIT_target_velocity);
    _mav_put_float(buf, 72, MIT_kp);
    _mav_put_float(buf, 76, MIT_kd);
    _mav_put_float(buf, 80, Homing_speed_search_for_switch);
    _mav_put_float(buf, 84, Homing_speed_search_for_zero);
    _mav_put_float(buf, 88, Homing_acceleration);
    _mav_put_int8_t(buf, 92, Homing_method);
    _mav_put_uint8_t(buf, 93, Interp_time_value);
    _mav_put_int8_t(buf, 94, Interp_time_index);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppMotionParam, buf, MAVLINK_MSG_ID_AppMotionParam_MIN_LEN, MAVLINK_MSG_ID_AppMotionParam_LEN, MAVLINK_MSG_ID_AppMotionParam_CRC);
#else
    mavlink_appmotionparam_t packet;
    packet.Target_position = Target_position;
    packet.Home_offset = Home_offset;
    packet.MIT_target_position = MIT_target_position;
    packet.Profile_velocity = Profile_velocity;
    packet.Profile_acceleration = Profile_acceleration;
    packet.Profile_deceleration = Profile_deceleration;
    packet.Quick_stop_deceleration = Quick_stop_deceleration;
    packet.Motion_profile_type = Motion_profile_type;
    packet.Target_velocity = Target_velocity;
    packet.Target_torque = Target_torque;
    packet.Torque_slope = Torque_slope;
    packet.Encoder_calibration_speed = Encoder_calibration_speed;
    packet.MIT_feedforward_torque = MIT_feedforward_torque;
    packet.MIT_max_current = MIT_max_current;
    packet.MIT_target_velocity = MIT_target_velocity;
    packet.MIT_kp = MIT_kp;
    packet.MIT_kd = MIT_kd;
    packet.Homing_speed_search_for_switch = Homing_speed_search_for_switch;
    packet.Homing_speed_search_for_zero = Homing_speed_search_for_zero;
    packet.Homing_acceleration = Homing_acceleration;
    packet.Homing_method = Homing_method;
    packet.Interp_time_value = Interp_time_value;
    packet.Interp_time_index = Interp_time_index;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppMotionParam, (const char *)&packet, MAVLINK_MSG_ID_AppMotionParam_MIN_LEN, MAVLINK_MSG_ID_AppMotionParam_LEN, MAVLINK_MSG_ID_AppMotionParam_CRC);
#endif
}

/**
 * @brief Send a appmotionparam message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_appmotionparam_send_struct(mavlink_channel_t chan, const mavlink_appmotionparam_t* appmotionparam)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_appmotionparam_send(chan, appmotionparam->Target_position, appmotionparam->Profile_velocity, appmotionparam->Profile_acceleration, appmotionparam->Profile_deceleration, appmotionparam->Quick_stop_deceleration, appmotionparam->Motion_profile_type, appmotionparam->Home_offset, appmotionparam->Homing_method, appmotionparam->Target_velocity, appmotionparam->Target_torque, appmotionparam->Torque_slope, appmotionparam->Encoder_calibration_speed, appmotionparam->MIT_feedforward_torque, appmotionparam->MIT_target_position, appmotionparam->MIT_max_current, appmotionparam->MIT_target_velocity, appmotionparam->MIT_kp, appmotionparam->MIT_kd, appmotionparam->Interp_time_value, appmotionparam->Interp_time_index, appmotionparam->Homing_speed_search_for_switch, appmotionparam->Homing_speed_search_for_zero, appmotionparam->Homing_acceleration);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppMotionParam, (const char *)appmotionparam, MAVLINK_MSG_ID_AppMotionParam_MIN_LEN, MAVLINK_MSG_ID_AppMotionParam_LEN, MAVLINK_MSG_ID_AppMotionParam_CRC);
#endif
}

#if MAVLINK_MSG_ID_AppMotionParam_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_appmotionparam_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  int64_t Target_position, float Profile_velocity, float Profile_acceleration, float Profile_deceleration, float Quick_stop_deceleration, int32_t Motion_profile_type, int64_t Home_offset, int8_t Homing_method, float Target_velocity, float Target_torque, float Torque_slope, float Encoder_calibration_speed, float MIT_feedforward_torque, int64_t MIT_target_position, float MIT_max_current, float MIT_target_velocity, float MIT_kp, float MIT_kd, uint8_t Interp_time_value, int8_t Interp_time_index, float Homing_speed_search_for_switch, float Homing_speed_search_for_zero, float Homing_acceleration)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_int64_t(buf, 0, Target_position);
    _mav_put_int64_t(buf, 8, Home_offset);
    _mav_put_int64_t(buf, 16, MIT_target_position);
    _mav_put_float(buf, 24, Profile_velocity);
    _mav_put_float(buf, 28, Profile_acceleration);
    _mav_put_float(buf, 32, Profile_deceleration);
    _mav_put_float(buf, 36, Quick_stop_deceleration);
    _mav_put_int32_t(buf, 40, Motion_profile_type);
    _mav_put_float(buf, 44, Target_velocity);
    _mav_put_float(buf, 48, Target_torque);
    _mav_put_float(buf, 52, Torque_slope);
    _mav_put_float(buf, 56, Encoder_calibration_speed);
    _mav_put_float(buf, 60, MIT_feedforward_torque);
    _mav_put_float(buf, 64, MIT_max_current);
    _mav_put_float(buf, 68, MIT_target_velocity);
    _mav_put_float(buf, 72, MIT_kp);
    _mav_put_float(buf, 76, MIT_kd);
    _mav_put_float(buf, 80, Homing_speed_search_for_switch);
    _mav_put_float(buf, 84, Homing_speed_search_for_zero);
    _mav_put_float(buf, 88, Homing_acceleration);
    _mav_put_int8_t(buf, 92, Homing_method);
    _mav_put_uint8_t(buf, 93, Interp_time_value);
    _mav_put_int8_t(buf, 94, Interp_time_index);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppMotionParam, buf, MAVLINK_MSG_ID_AppMotionParam_MIN_LEN, MAVLINK_MSG_ID_AppMotionParam_LEN, MAVLINK_MSG_ID_AppMotionParam_CRC);
#else
    mavlink_appmotionparam_t *packet = (mavlink_appmotionparam_t *)msgbuf;
    packet->Target_position = Target_position;
    packet->Home_offset = Home_offset;
    packet->MIT_target_position = MIT_target_position;
    packet->Profile_velocity = Profile_velocity;
    packet->Profile_acceleration = Profile_acceleration;
    packet->Profile_deceleration = Profile_deceleration;
    packet->Quick_stop_deceleration = Quick_stop_deceleration;
    packet->Motion_profile_type = Motion_profile_type;
    packet->Target_velocity = Target_velocity;
    packet->Target_torque = Target_torque;
    packet->Torque_slope = Torque_slope;
    packet->Encoder_calibration_speed = Encoder_calibration_speed;
    packet->MIT_feedforward_torque = MIT_feedforward_torque;
    packet->MIT_max_current = MIT_max_current;
    packet->MIT_target_velocity = MIT_target_velocity;
    packet->MIT_kp = MIT_kp;
    packet->MIT_kd = MIT_kd;
    packet->Homing_speed_search_for_switch = Homing_speed_search_for_switch;
    packet->Homing_speed_search_for_zero = Homing_speed_search_for_zero;
    packet->Homing_acceleration = Homing_acceleration;
    packet->Homing_method = Homing_method;
    packet->Interp_time_value = Interp_time_value;
    packet->Interp_time_index = Interp_time_index;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppMotionParam, (const char *)packet, MAVLINK_MSG_ID_AppMotionParam_MIN_LEN, MAVLINK_MSG_ID_AppMotionParam_LEN, MAVLINK_MSG_ID_AppMotionParam_CRC);
#endif
}
#endif

#endif

// MESSAGE AppMotionParam UNPACKING


/**
 * @brief Get field Target_position from appmotionparam message
 *
 * @return  
 */
static inline int64_t mavlink_msg_appmotionparam_get_Target_position(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int64_t(msg,  0);
}

/**
 * @brief Get field Profile_velocity from appmotionparam message
 *
 * @return  
 */
static inline float mavlink_msg_appmotionparam_get_Profile_velocity(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  24);
}

/**
 * @brief Get field Profile_acceleration from appmotionparam message
 *
 * @return  
 */
static inline float mavlink_msg_appmotionparam_get_Profile_acceleration(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  28);
}

/**
 * @brief Get field Profile_deceleration from appmotionparam message
 *
 * @return  
 */
static inline float mavlink_msg_appmotionparam_get_Profile_deceleration(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  32);
}

/**
 * @brief Get field Quick_stop_deceleration from appmotionparam message
 *
 * @return  
 */
static inline float mavlink_msg_appmotionparam_get_Quick_stop_deceleration(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  36);
}

/**
 * @brief Get field Motion_profile_type from appmotionparam message
 *
 * @return  
 */
static inline int32_t mavlink_msg_appmotionparam_get_Motion_profile_type(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  40);
}

/**
 * @brief Get field Home_offset from appmotionparam message
 *
 * @return  
 */
static inline int64_t mavlink_msg_appmotionparam_get_Home_offset(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int64_t(msg,  8);
}

/**
 * @brief Get field Homing_method from appmotionparam message
 *
 * @return  
 */
static inline int8_t mavlink_msg_appmotionparam_get_Homing_method(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int8_t(msg,  92);
}

/**
 * @brief Get field Target_velocity from appmotionparam message
 *
 * @return  
 */
static inline float mavlink_msg_appmotionparam_get_Target_velocity(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  44);
}

/**
 * @brief Get field Target_torque from appmotionparam message
 *
 * @return  
 */
static inline float mavlink_msg_appmotionparam_get_Target_torque(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  48);
}

/**
 * @brief Get field Torque_slope from appmotionparam message
 *
 * @return  
 */
static inline float mavlink_msg_appmotionparam_get_Torque_slope(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  52);
}

/**
 * @brief Get field Encoder_calibration_speed from appmotionparam message
 *
 * @return  
 */
static inline float mavlink_msg_appmotionparam_get_Encoder_calibration_speed(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  56);
}

/**
 * @brief Get field MIT_feedforward_torque from appmotionparam message
 *
 * @return  
 */
static inline float mavlink_msg_appmotionparam_get_MIT_feedforward_torque(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  60);
}

/**
 * @brief Get field MIT_target_position from appmotionparam message
 *
 * @return  
 */
static inline int64_t mavlink_msg_appmotionparam_get_MIT_target_position(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int64_t(msg,  16);
}

/**
 * @brief Get field MIT_max_current from appmotionparam message
 *
 * @return  
 */
static inline float mavlink_msg_appmotionparam_get_MIT_max_current(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  64);
}

/**
 * @brief Get field MIT_target_velocity from appmotionparam message
 *
 * @return  
 */
static inline float mavlink_msg_appmotionparam_get_MIT_target_velocity(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  68);
}

/**
 * @brief Get field MIT_kp from appmotionparam message
 *
 * @return  
 */
static inline float mavlink_msg_appmotionparam_get_MIT_kp(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  72);
}

/**
 * @brief Get field MIT_kd from appmotionparam message
 *
 * @return  
 */
static inline float mavlink_msg_appmotionparam_get_MIT_kd(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  76);
}

/**
 * @brief Get field Interp_time_value from appmotionparam message
 *
 * @return  
 */
static inline uint8_t mavlink_msg_appmotionparam_get_Interp_time_value(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  93);
}

/**
 * @brief Get field Interp_time_index from appmotionparam message
 *
 * @return  
 */
static inline int8_t mavlink_msg_appmotionparam_get_Interp_time_index(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int8_t(msg,  94);
}

/**
 * @brief Get field Homing_speed_search_for_switch from appmotionparam message
 *
 * @return  
 */
static inline float mavlink_msg_appmotionparam_get_Homing_speed_search_for_switch(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  80);
}

/**
 * @brief Get field Homing_speed_search_for_zero from appmotionparam message
 *
 * @return  
 */
static inline float mavlink_msg_appmotionparam_get_Homing_speed_search_for_zero(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  84);
}

/**
 * @brief Get field Homing_acceleration from appmotionparam message
 *
 * @return  
 */
static inline float mavlink_msg_appmotionparam_get_Homing_acceleration(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  88);
}

/**
 * @brief Decode a appmotionparam message into a struct
 *
 * @param msg The message to decode
 * @param appmotionparam C-struct to decode the message contents into
 */
static inline void mavlink_msg_appmotionparam_decode(const mavlink_message_t* msg, mavlink_appmotionparam_t* appmotionparam)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    appmotionparam->Target_position = mavlink_msg_appmotionparam_get_Target_position(msg);
    appmotionparam->Home_offset = mavlink_msg_appmotionparam_get_Home_offset(msg);
    appmotionparam->MIT_target_position = mavlink_msg_appmotionparam_get_MIT_target_position(msg);
    appmotionparam->Profile_velocity = mavlink_msg_appmotionparam_get_Profile_velocity(msg);
    appmotionparam->Profile_acceleration = mavlink_msg_appmotionparam_get_Profile_acceleration(msg);
    appmotionparam->Profile_deceleration = mavlink_msg_appmotionparam_get_Profile_deceleration(msg);
    appmotionparam->Quick_stop_deceleration = mavlink_msg_appmotionparam_get_Quick_stop_deceleration(msg);
    appmotionparam->Motion_profile_type = mavlink_msg_appmotionparam_get_Motion_profile_type(msg);
    appmotionparam->Target_velocity = mavlink_msg_appmotionparam_get_Target_velocity(msg);
    appmotionparam->Target_torque = mavlink_msg_appmotionparam_get_Target_torque(msg);
    appmotionparam->Torque_slope = mavlink_msg_appmotionparam_get_Torque_slope(msg);
    appmotionparam->Encoder_calibration_speed = mavlink_msg_appmotionparam_get_Encoder_calibration_speed(msg);
    appmotionparam->MIT_feedforward_torque = mavlink_msg_appmotionparam_get_MIT_feedforward_torque(msg);
    appmotionparam->MIT_max_current = mavlink_msg_appmotionparam_get_MIT_max_current(msg);
    appmotionparam->MIT_target_velocity = mavlink_msg_appmotionparam_get_MIT_target_velocity(msg);
    appmotionparam->MIT_kp = mavlink_msg_appmotionparam_get_MIT_kp(msg);
    appmotionparam->MIT_kd = mavlink_msg_appmotionparam_get_MIT_kd(msg);
    appmotionparam->Homing_speed_search_for_switch = mavlink_msg_appmotionparam_get_Homing_speed_search_for_switch(msg);
    appmotionparam->Homing_speed_search_for_zero = mavlink_msg_appmotionparam_get_Homing_speed_search_for_zero(msg);
    appmotionparam->Homing_acceleration = mavlink_msg_appmotionparam_get_Homing_acceleration(msg);
    appmotionparam->Homing_method = mavlink_msg_appmotionparam_get_Homing_method(msg);
    appmotionparam->Interp_time_value = mavlink_msg_appmotionparam_get_Interp_time_value(msg);
    appmotionparam->Interp_time_index = mavlink_msg_appmotionparam_get_Interp_time_index(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_AppMotionParam_LEN? msg->len : MAVLINK_MSG_ID_AppMotionParam_LEN;
        memset(appmotionparam, 0, MAVLINK_MSG_ID_AppMotionParam_LEN);
    memcpy(appmotionparam, _MAV_PAYLOAD(msg), len);
#endif
}
