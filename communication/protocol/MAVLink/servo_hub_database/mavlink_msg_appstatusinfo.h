#pragma once
// MESSAGE AppStatusInfo PACKING

#define MAVLINK_MSG_ID_AppStatusInfo 30055


typedef struct __mavlink_appstatusinfo_t {
 uint32_t Statusword; /*<  */
 uint32_t Error_word; /*<  */
 float DC_link_circuit_voltage; /*<  */
 float Drive_accumulated_heat; /*<  */
 float Drive_temperature; /*<  */
 uint32_t Alarm_word; /*<  */
 uint32_t Version; /*<  */
 float Motor_temperature; /*<  */
 float Motor_power; /*<  */
 float Mcu_temperature; /*<  */
 uint32_t Digital_io_inputs_status; /*<  */
 int8_t Modes_of_operation_display; /*<  */
 uint8_t Brake_state; /*<  */
} mavlink_appstatusinfo_t;

#define MAVLINK_MSG_ID_AppStatusInfo_LEN 46
#define MAVLINK_MSG_ID_AppStatusInfo_MIN_LEN 46
#define MAVLINK_MSG_ID_30055_LEN 46
#define MAVLINK_MSG_ID_30055_MIN_LEN 46

#define MAVLINK_MSG_ID_AppStatusInfo_CRC 3
#define MAVLINK_MSG_ID_30055_CRC 3



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_AppStatusInfo { \
    30055, \
    "AppStatusInfo", \
    13, \
    {  { "Statusword", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_appstatusinfo_t, Statusword) }, \
         { "Error_word", NULL, MAVLINK_TYPE_UINT32_T, 0, 4, offsetof(mavlink_appstatusinfo_t, Error_word) }, \
         { "DC_link_circuit_voltage", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_appstatusinfo_t, DC_link_circuit_voltage) }, \
         { "Drive_accumulated_heat", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_appstatusinfo_t, Drive_accumulated_heat) }, \
         { "Drive_temperature", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_appstatusinfo_t, Drive_temperature) }, \
         { "Alarm_word", NULL, MAVLINK_TYPE_UINT32_T, 0, 20, offsetof(mavlink_appstatusinfo_t, Alarm_word) }, \
         { "Modes_of_operation_display", NULL, MAVLINK_TYPE_INT8_T, 0, 44, offsetof(mavlink_appstatusinfo_t, Modes_of_operation_display) }, \
         { "Version", NULL, MAVLINK_TYPE_UINT32_T, 0, 24, offsetof(mavlink_appstatusinfo_t, Version) }, \
         { "Motor_temperature", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_appstatusinfo_t, Motor_temperature) }, \
         { "Motor_power", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_appstatusinfo_t, Motor_power) }, \
         { "Mcu_temperature", NULL, MAVLINK_TYPE_FLOAT, 0, 36, offsetof(mavlink_appstatusinfo_t, Mcu_temperature) }, \
         { "Digital_io_inputs_status", NULL, MAVLINK_TYPE_UINT32_T, 0, 40, offsetof(mavlink_appstatusinfo_t, Digital_io_inputs_status) }, \
         { "Brake_state", NULL, MAVLINK_TYPE_UINT8_T, 0, 45, offsetof(mavlink_appstatusinfo_t, Brake_state) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_AppStatusInfo { \
    "AppStatusInfo", \
    13, \
    {  { "Statusword", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_appstatusinfo_t, Statusword) }, \
         { "Error_word", NULL, MAVLINK_TYPE_UINT32_T, 0, 4, offsetof(mavlink_appstatusinfo_t, Error_word) }, \
         { "DC_link_circuit_voltage", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_appstatusinfo_t, DC_link_circuit_voltage) }, \
         { "Drive_accumulated_heat", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_appstatusinfo_t, Drive_accumulated_heat) }, \
         { "Drive_temperature", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_appstatusinfo_t, Drive_temperature) }, \
         { "Alarm_word", NULL, MAVLINK_TYPE_UINT32_T, 0, 20, offsetof(mavlink_appstatusinfo_t, Alarm_word) }, \
         { "Modes_of_operation_display", NULL, MAVLINK_TYPE_INT8_T, 0, 44, offsetof(mavlink_appstatusinfo_t, Modes_of_operation_display) }, \
         { "Version", NULL, MAVLINK_TYPE_UINT32_T, 0, 24, offsetof(mavlink_appstatusinfo_t, Version) }, \
         { "Motor_temperature", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_appstatusinfo_t, Motor_temperature) }, \
         { "Motor_power", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_appstatusinfo_t, Motor_power) }, \
         { "Mcu_temperature", NULL, MAVLINK_TYPE_FLOAT, 0, 36, offsetof(mavlink_appstatusinfo_t, Mcu_temperature) }, \
         { "Digital_io_inputs_status", NULL, MAVLINK_TYPE_UINT32_T, 0, 40, offsetof(mavlink_appstatusinfo_t, Digital_io_inputs_status) }, \
         { "Brake_state", NULL, MAVLINK_TYPE_UINT8_T, 0, 45, offsetof(mavlink_appstatusinfo_t, Brake_state) }, \
         } \
}
#endif

/**
 * @brief Pack a appstatusinfo message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param Statusword  
 * @param Error_word  
 * @param DC_link_circuit_voltage  
 * @param Drive_accumulated_heat  
 * @param Drive_temperature  
 * @param Alarm_word  
 * @param Modes_of_operation_display  
 * @param Version  
 * @param Motor_temperature  
 * @param Motor_power  
 * @param Mcu_temperature  
 * @param Digital_io_inputs_status  
 * @param Brake_state  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_appstatusinfo_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint32_t Statusword, uint32_t Error_word, float DC_link_circuit_voltage, float Drive_accumulated_heat, float Drive_temperature, uint32_t Alarm_word, int8_t Modes_of_operation_display, uint32_t Version, float Motor_temperature, float Motor_power, float Mcu_temperature, uint32_t Digital_io_inputs_status, uint8_t Brake_state)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_AppStatusInfo_LEN];
    _mav_put_uint32_t(buf, 0, Statusword);
    _mav_put_uint32_t(buf, 4, Error_word);
    _mav_put_float(buf, 8, DC_link_circuit_voltage);
    _mav_put_float(buf, 12, Drive_accumulated_heat);
    _mav_put_float(buf, 16, Drive_temperature);
    _mav_put_uint32_t(buf, 20, Alarm_word);
    _mav_put_uint32_t(buf, 24, Version);
    _mav_put_float(buf, 28, Motor_temperature);
    _mav_put_float(buf, 32, Motor_power);
    _mav_put_float(buf, 36, Mcu_temperature);
    _mav_put_uint32_t(buf, 40, Digital_io_inputs_status);
    _mav_put_int8_t(buf, 44, Modes_of_operation_display);
    _mav_put_uint8_t(buf, 45, Brake_state);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_AppStatusInfo_LEN);
#else
    mavlink_appstatusinfo_t packet;
    packet.Statusword = Statusword;
    packet.Error_word = Error_word;
    packet.DC_link_circuit_voltage = DC_link_circuit_voltage;
    packet.Drive_accumulated_heat = Drive_accumulated_heat;
    packet.Drive_temperature = Drive_temperature;
    packet.Alarm_word = Alarm_word;
    packet.Version = Version;
    packet.Motor_temperature = Motor_temperature;
    packet.Motor_power = Motor_power;
    packet.Mcu_temperature = Mcu_temperature;
    packet.Digital_io_inputs_status = Digital_io_inputs_status;
    packet.Modes_of_operation_display = Modes_of_operation_display;
    packet.Brake_state = Brake_state;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_AppStatusInfo_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_AppStatusInfo;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_AppStatusInfo_MIN_LEN, MAVLINK_MSG_ID_AppStatusInfo_LEN, MAVLINK_MSG_ID_AppStatusInfo_CRC);
}

/**
 * @brief Pack a appstatusinfo message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param Statusword  
 * @param Error_word  
 * @param DC_link_circuit_voltage  
 * @param Drive_accumulated_heat  
 * @param Drive_temperature  
 * @param Alarm_word  
 * @param Modes_of_operation_display  
 * @param Version  
 * @param Motor_temperature  
 * @param Motor_power  
 * @param Mcu_temperature  
 * @param Digital_io_inputs_status  
 * @param Brake_state  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_appstatusinfo_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint32_t Statusword, uint32_t Error_word, float DC_link_circuit_voltage, float Drive_accumulated_heat, float Drive_temperature, uint32_t Alarm_word, int8_t Modes_of_operation_display, uint32_t Version, float Motor_temperature, float Motor_power, float Mcu_temperature, uint32_t Digital_io_inputs_status, uint8_t Brake_state)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_AppStatusInfo_LEN];
    _mav_put_uint32_t(buf, 0, Statusword);
    _mav_put_uint32_t(buf, 4, Error_word);
    _mav_put_float(buf, 8, DC_link_circuit_voltage);
    _mav_put_float(buf, 12, Drive_accumulated_heat);
    _mav_put_float(buf, 16, Drive_temperature);
    _mav_put_uint32_t(buf, 20, Alarm_word);
    _mav_put_uint32_t(buf, 24, Version);
    _mav_put_float(buf, 28, Motor_temperature);
    _mav_put_float(buf, 32, Motor_power);
    _mav_put_float(buf, 36, Mcu_temperature);
    _mav_put_uint32_t(buf, 40, Digital_io_inputs_status);
    _mav_put_int8_t(buf, 44, Modes_of_operation_display);
    _mav_put_uint8_t(buf, 45, Brake_state);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_AppStatusInfo_LEN);
#else
    mavlink_appstatusinfo_t packet;
    packet.Statusword = Statusword;
    packet.Error_word = Error_word;
    packet.DC_link_circuit_voltage = DC_link_circuit_voltage;
    packet.Drive_accumulated_heat = Drive_accumulated_heat;
    packet.Drive_temperature = Drive_temperature;
    packet.Alarm_word = Alarm_word;
    packet.Version = Version;
    packet.Motor_temperature = Motor_temperature;
    packet.Motor_power = Motor_power;
    packet.Mcu_temperature = Mcu_temperature;
    packet.Digital_io_inputs_status = Digital_io_inputs_status;
    packet.Modes_of_operation_display = Modes_of_operation_display;
    packet.Brake_state = Brake_state;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_AppStatusInfo_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_AppStatusInfo;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_AppStatusInfo_MIN_LEN, MAVLINK_MSG_ID_AppStatusInfo_LEN, MAVLINK_MSG_ID_AppStatusInfo_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_AppStatusInfo_MIN_LEN, MAVLINK_MSG_ID_AppStatusInfo_LEN);
#endif
}

/**
 * @brief Pack a appstatusinfo message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param Statusword  
 * @param Error_word  
 * @param DC_link_circuit_voltage  
 * @param Drive_accumulated_heat  
 * @param Drive_temperature  
 * @param Alarm_word  
 * @param Modes_of_operation_display  
 * @param Version  
 * @param Motor_temperature  
 * @param Motor_power  
 * @param Mcu_temperature  
 * @param Digital_io_inputs_status  
 * @param Brake_state  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_appstatusinfo_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint32_t Statusword,uint32_t Error_word,float DC_link_circuit_voltage,float Drive_accumulated_heat,float Drive_temperature,uint32_t Alarm_word,int8_t Modes_of_operation_display,uint32_t Version,float Motor_temperature,float Motor_power,float Mcu_temperature,uint32_t Digital_io_inputs_status,uint8_t Brake_state)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_AppStatusInfo_LEN];
    _mav_put_uint32_t(buf, 0, Statusword);
    _mav_put_uint32_t(buf, 4, Error_word);
    _mav_put_float(buf, 8, DC_link_circuit_voltage);
    _mav_put_float(buf, 12, Drive_accumulated_heat);
    _mav_put_float(buf, 16, Drive_temperature);
    _mav_put_uint32_t(buf, 20, Alarm_word);
    _mav_put_uint32_t(buf, 24, Version);
    _mav_put_float(buf, 28, Motor_temperature);
    _mav_put_float(buf, 32, Motor_power);
    _mav_put_float(buf, 36, Mcu_temperature);
    _mav_put_uint32_t(buf, 40, Digital_io_inputs_status);
    _mav_put_int8_t(buf, 44, Modes_of_operation_display);
    _mav_put_uint8_t(buf, 45, Brake_state);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_AppStatusInfo_LEN);
#else
    mavlink_appstatusinfo_t packet;
    packet.Statusword = Statusword;
    packet.Error_word = Error_word;
    packet.DC_link_circuit_voltage = DC_link_circuit_voltage;
    packet.Drive_accumulated_heat = Drive_accumulated_heat;
    packet.Drive_temperature = Drive_temperature;
    packet.Alarm_word = Alarm_word;
    packet.Version = Version;
    packet.Motor_temperature = Motor_temperature;
    packet.Motor_power = Motor_power;
    packet.Mcu_temperature = Mcu_temperature;
    packet.Digital_io_inputs_status = Digital_io_inputs_status;
    packet.Modes_of_operation_display = Modes_of_operation_display;
    packet.Brake_state = Brake_state;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_AppStatusInfo_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_AppStatusInfo;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_AppStatusInfo_MIN_LEN, MAVLINK_MSG_ID_AppStatusInfo_LEN, MAVLINK_MSG_ID_AppStatusInfo_CRC);
}

/**
 * @brief Encode a appstatusinfo struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param appstatusinfo C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_appstatusinfo_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_appstatusinfo_t* appstatusinfo)
{
    return mavlink_msg_appstatusinfo_pack(system_id, component_id, msg, appstatusinfo->Statusword, appstatusinfo->Error_word, appstatusinfo->DC_link_circuit_voltage, appstatusinfo->Drive_accumulated_heat, appstatusinfo->Drive_temperature, appstatusinfo->Alarm_word, appstatusinfo->Modes_of_operation_display, appstatusinfo->Version, appstatusinfo->Motor_temperature, appstatusinfo->Motor_power, appstatusinfo->Mcu_temperature, appstatusinfo->Digital_io_inputs_status, appstatusinfo->Brake_state);
}

/**
 * @brief Encode a appstatusinfo struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param appstatusinfo C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_appstatusinfo_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_appstatusinfo_t* appstatusinfo)
{
    return mavlink_msg_appstatusinfo_pack_chan(system_id, component_id, chan, msg, appstatusinfo->Statusword, appstatusinfo->Error_word, appstatusinfo->DC_link_circuit_voltage, appstatusinfo->Drive_accumulated_heat, appstatusinfo->Drive_temperature, appstatusinfo->Alarm_word, appstatusinfo->Modes_of_operation_display, appstatusinfo->Version, appstatusinfo->Motor_temperature, appstatusinfo->Motor_power, appstatusinfo->Mcu_temperature, appstatusinfo->Digital_io_inputs_status, appstatusinfo->Brake_state);
}

/**
 * @brief Encode a appstatusinfo struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param appstatusinfo C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_appstatusinfo_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_appstatusinfo_t* appstatusinfo)
{
    return mavlink_msg_appstatusinfo_pack_status(system_id, component_id, _status, msg,  appstatusinfo->Statusword, appstatusinfo->Error_word, appstatusinfo->DC_link_circuit_voltage, appstatusinfo->Drive_accumulated_heat, appstatusinfo->Drive_temperature, appstatusinfo->Alarm_word, appstatusinfo->Modes_of_operation_display, appstatusinfo->Version, appstatusinfo->Motor_temperature, appstatusinfo->Motor_power, appstatusinfo->Mcu_temperature, appstatusinfo->Digital_io_inputs_status, appstatusinfo->Brake_state);
}

/**
 * @brief Send a appstatusinfo message
 * @param chan MAVLink channel to send the message
 *
 * @param Statusword  
 * @param Error_word  
 * @param DC_link_circuit_voltage  
 * @param Drive_accumulated_heat  
 * @param Drive_temperature  
 * @param Alarm_word  
 * @param Modes_of_operation_display  
 * @param Version  
 * @param Motor_temperature  
 * @param Motor_power  
 * @param Mcu_temperature  
 * @param Digital_io_inputs_status  
 * @param Brake_state  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_appstatusinfo_send(mavlink_channel_t chan, uint32_t Statusword, uint32_t Error_word, float DC_link_circuit_voltage, float Drive_accumulated_heat, float Drive_temperature, uint32_t Alarm_word, int8_t Modes_of_operation_display, uint32_t Version, float Motor_temperature, float Motor_power, float Mcu_temperature, uint32_t Digital_io_inputs_status, uint8_t Brake_state)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_AppStatusInfo_LEN];
    _mav_put_uint32_t(buf, 0, Statusword);
    _mav_put_uint32_t(buf, 4, Error_word);
    _mav_put_float(buf, 8, DC_link_circuit_voltage);
    _mav_put_float(buf, 12, Drive_accumulated_heat);
    _mav_put_float(buf, 16, Drive_temperature);
    _mav_put_uint32_t(buf, 20, Alarm_word);
    _mav_put_uint32_t(buf, 24, Version);
    _mav_put_float(buf, 28, Motor_temperature);
    _mav_put_float(buf, 32, Motor_power);
    _mav_put_float(buf, 36, Mcu_temperature);
    _mav_put_uint32_t(buf, 40, Digital_io_inputs_status);
    _mav_put_int8_t(buf, 44, Modes_of_operation_display);
    _mav_put_uint8_t(buf, 45, Brake_state);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppStatusInfo, buf, MAVLINK_MSG_ID_AppStatusInfo_MIN_LEN, MAVLINK_MSG_ID_AppStatusInfo_LEN, MAVLINK_MSG_ID_AppStatusInfo_CRC);
#else
    mavlink_appstatusinfo_t packet;
    packet.Statusword = Statusword;
    packet.Error_word = Error_word;
    packet.DC_link_circuit_voltage = DC_link_circuit_voltage;
    packet.Drive_accumulated_heat = Drive_accumulated_heat;
    packet.Drive_temperature = Drive_temperature;
    packet.Alarm_word = Alarm_word;
    packet.Version = Version;
    packet.Motor_temperature = Motor_temperature;
    packet.Motor_power = Motor_power;
    packet.Mcu_temperature = Mcu_temperature;
    packet.Digital_io_inputs_status = Digital_io_inputs_status;
    packet.Modes_of_operation_display = Modes_of_operation_display;
    packet.Brake_state = Brake_state;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppStatusInfo, (const char *)&packet, MAVLINK_MSG_ID_AppStatusInfo_MIN_LEN, MAVLINK_MSG_ID_AppStatusInfo_LEN, MAVLINK_MSG_ID_AppStatusInfo_CRC);
#endif
}

/**
 * @brief Send a appstatusinfo message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_appstatusinfo_send_struct(mavlink_channel_t chan, const mavlink_appstatusinfo_t* appstatusinfo)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_appstatusinfo_send(chan, appstatusinfo->Statusword, appstatusinfo->Error_word, appstatusinfo->DC_link_circuit_voltage, appstatusinfo->Drive_accumulated_heat, appstatusinfo->Drive_temperature, appstatusinfo->Alarm_word, appstatusinfo->Modes_of_operation_display, appstatusinfo->Version, appstatusinfo->Motor_temperature, appstatusinfo->Motor_power, appstatusinfo->Mcu_temperature, appstatusinfo->Digital_io_inputs_status, appstatusinfo->Brake_state);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppStatusInfo, (const char *)appstatusinfo, MAVLINK_MSG_ID_AppStatusInfo_MIN_LEN, MAVLINK_MSG_ID_AppStatusInfo_LEN, MAVLINK_MSG_ID_AppStatusInfo_CRC);
#endif
}

#if MAVLINK_MSG_ID_AppStatusInfo_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_appstatusinfo_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint32_t Statusword, uint32_t Error_word, float DC_link_circuit_voltage, float Drive_accumulated_heat, float Drive_temperature, uint32_t Alarm_word, int8_t Modes_of_operation_display, uint32_t Version, float Motor_temperature, float Motor_power, float Mcu_temperature, uint32_t Digital_io_inputs_status, uint8_t Brake_state)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint32_t(buf, 0, Statusword);
    _mav_put_uint32_t(buf, 4, Error_word);
    _mav_put_float(buf, 8, DC_link_circuit_voltage);
    _mav_put_float(buf, 12, Drive_accumulated_heat);
    _mav_put_float(buf, 16, Drive_temperature);
    _mav_put_uint32_t(buf, 20, Alarm_word);
    _mav_put_uint32_t(buf, 24, Version);
    _mav_put_float(buf, 28, Motor_temperature);
    _mav_put_float(buf, 32, Motor_power);
    _mav_put_float(buf, 36, Mcu_temperature);
    _mav_put_uint32_t(buf, 40, Digital_io_inputs_status);
    _mav_put_int8_t(buf, 44, Modes_of_operation_display);
    _mav_put_uint8_t(buf, 45, Brake_state);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppStatusInfo, buf, MAVLINK_MSG_ID_AppStatusInfo_MIN_LEN, MAVLINK_MSG_ID_AppStatusInfo_LEN, MAVLINK_MSG_ID_AppStatusInfo_CRC);
#else
    mavlink_appstatusinfo_t *packet = (mavlink_appstatusinfo_t *)msgbuf;
    packet->Statusword = Statusword;
    packet->Error_word = Error_word;
    packet->DC_link_circuit_voltage = DC_link_circuit_voltage;
    packet->Drive_accumulated_heat = Drive_accumulated_heat;
    packet->Drive_temperature = Drive_temperature;
    packet->Alarm_word = Alarm_word;
    packet->Version = Version;
    packet->Motor_temperature = Motor_temperature;
    packet->Motor_power = Motor_power;
    packet->Mcu_temperature = Mcu_temperature;
    packet->Digital_io_inputs_status = Digital_io_inputs_status;
    packet->Modes_of_operation_display = Modes_of_operation_display;
    packet->Brake_state = Brake_state;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_AppStatusInfo, (const char *)packet, MAVLINK_MSG_ID_AppStatusInfo_MIN_LEN, MAVLINK_MSG_ID_AppStatusInfo_LEN, MAVLINK_MSG_ID_AppStatusInfo_CRC);
#endif
}
#endif

#endif

// MESSAGE AppStatusInfo UNPACKING


/**
 * @brief Get field Statusword from appstatusinfo message
 *
 * @return  
 */
static inline uint32_t mavlink_msg_appstatusinfo_get_Statusword(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Get field Error_word from appstatusinfo message
 *
 * @return  
 */
static inline uint32_t mavlink_msg_appstatusinfo_get_Error_word(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  4);
}

/**
 * @brief Get field DC_link_circuit_voltage from appstatusinfo message
 *
 * @return  
 */
static inline float mavlink_msg_appstatusinfo_get_DC_link_circuit_voltage(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field Drive_accumulated_heat from appstatusinfo message
 *
 * @return  
 */
static inline float mavlink_msg_appstatusinfo_get_Drive_accumulated_heat(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Get field Drive_temperature from appstatusinfo message
 *
 * @return  
 */
static inline float mavlink_msg_appstatusinfo_get_Drive_temperature(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  16);
}

/**
 * @brief Get field Alarm_word from appstatusinfo message
 *
 * @return  
 */
static inline uint32_t mavlink_msg_appstatusinfo_get_Alarm_word(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  20);
}

/**
 * @brief Get field Modes_of_operation_display from appstatusinfo message
 *
 * @return  
 */
static inline int8_t mavlink_msg_appstatusinfo_get_Modes_of_operation_display(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int8_t(msg,  44);
}

/**
 * @brief Get field Version from appstatusinfo message
 *
 * @return  
 */
static inline uint32_t mavlink_msg_appstatusinfo_get_Version(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  24);
}

/**
 * @brief Get field Motor_temperature from appstatusinfo message
 *
 * @return  
 */
static inline float mavlink_msg_appstatusinfo_get_Motor_temperature(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  28);
}

/**
 * @brief Get field Motor_power from appstatusinfo message
 *
 * @return  
 */
static inline float mavlink_msg_appstatusinfo_get_Motor_power(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  32);
}

/**
 * @brief Get field Mcu_temperature from appstatusinfo message
 *
 * @return  
 */
static inline float mavlink_msg_appstatusinfo_get_Mcu_temperature(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  36);
}

/**
 * @brief Get field Digital_io_inputs_status from appstatusinfo message
 *
 * @return  
 */
static inline uint32_t mavlink_msg_appstatusinfo_get_Digital_io_inputs_status(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  40);
}

/**
 * @brief Get field Brake_state from appstatusinfo message
 *
 * @return  
 */
static inline uint8_t mavlink_msg_appstatusinfo_get_Brake_state(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  45);
}

/**
 * @brief Decode a appstatusinfo message into a struct
 *
 * @param msg The message to decode
 * @param appstatusinfo C-struct to decode the message contents into
 */
static inline void mavlink_msg_appstatusinfo_decode(const mavlink_message_t* msg, mavlink_appstatusinfo_t* appstatusinfo)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    appstatusinfo->Statusword = mavlink_msg_appstatusinfo_get_Statusword(msg);
    appstatusinfo->Error_word = mavlink_msg_appstatusinfo_get_Error_word(msg);
    appstatusinfo->DC_link_circuit_voltage = mavlink_msg_appstatusinfo_get_DC_link_circuit_voltage(msg);
    appstatusinfo->Drive_accumulated_heat = mavlink_msg_appstatusinfo_get_Drive_accumulated_heat(msg);
    appstatusinfo->Drive_temperature = mavlink_msg_appstatusinfo_get_Drive_temperature(msg);
    appstatusinfo->Alarm_word = mavlink_msg_appstatusinfo_get_Alarm_word(msg);
    appstatusinfo->Version = mavlink_msg_appstatusinfo_get_Version(msg);
    appstatusinfo->Motor_temperature = mavlink_msg_appstatusinfo_get_Motor_temperature(msg);
    appstatusinfo->Motor_power = mavlink_msg_appstatusinfo_get_Motor_power(msg);
    appstatusinfo->Mcu_temperature = mavlink_msg_appstatusinfo_get_Mcu_temperature(msg);
    appstatusinfo->Digital_io_inputs_status = mavlink_msg_appstatusinfo_get_Digital_io_inputs_status(msg);
    appstatusinfo->Modes_of_operation_display = mavlink_msg_appstatusinfo_get_Modes_of_operation_display(msg);
    appstatusinfo->Brake_state = mavlink_msg_appstatusinfo_get_Brake_state(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_AppStatusInfo_LEN? msg->len : MAVLINK_MSG_ID_AppStatusInfo_LEN;
        memset(appstatusinfo, 0, MAVLINK_MSG_ID_AppStatusInfo_LEN);
    memcpy(appstatusinfo, _MAV_PAYLOAD(msg), len);
#endif
}
