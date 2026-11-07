#pragma once
// MESSAGE SimPlantConfig PACKING

#define MAVLINK_MSG_ID_SimPlantConfig 30081


typedef struct __mavlink_simplantconfig_t {
 int64_t enc_line_init_pos_P; /*<  */
 float b; /*<  */
 float fc; /*<  */
 float flux; /*<  */
 float kt; /*<  */
 float j; /*<  */
 float ld; /*<  */
 float lq; /*<  */
 float peak_current_A; /*<  */
 float pn; /*<  */
 float r; /*<  */
 float rated_current_A; /*<  */
 float speed_max_rpm; /*<  */
 float dt_s; /*<  */
 uint32_t enc_line_p_n; /*<  */
 float j_inv; /*<  */
 float ld_inv; /*<  */
 float lq_inv; /*<  */
 float enc_noise; /*<  */
} mavlink_simplantconfig_t;

#define MAVLINK_MSG_ID_SimPlantConfig_LEN 80
#define MAVLINK_MSG_ID_SimPlantConfig_MIN_LEN 80
#define MAVLINK_MSG_ID_30081_LEN 80
#define MAVLINK_MSG_ID_30081_MIN_LEN 80

#define MAVLINK_MSG_ID_SimPlantConfig_CRC 135
#define MAVLINK_MSG_ID_30081_CRC 135



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_SimPlantConfig { \
    30081, \
    "SimPlantConfig", \
    19, \
    {  { "b", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_simplantconfig_t, b) }, \
         { "fc", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_simplantconfig_t, fc) }, \
         { "flux", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_simplantconfig_t, flux) }, \
         { "kt", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_simplantconfig_t, kt) }, \
         { "j", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_simplantconfig_t, j) }, \
         { "ld", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_simplantconfig_t, ld) }, \
         { "lq", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_simplantconfig_t, lq) }, \
         { "peak_current_A", NULL, MAVLINK_TYPE_FLOAT, 0, 36, offsetof(mavlink_simplantconfig_t, peak_current_A) }, \
         { "pn", NULL, MAVLINK_TYPE_FLOAT, 0, 40, offsetof(mavlink_simplantconfig_t, pn) }, \
         { "r", NULL, MAVLINK_TYPE_FLOAT, 0, 44, offsetof(mavlink_simplantconfig_t, r) }, \
         { "rated_current_A", NULL, MAVLINK_TYPE_FLOAT, 0, 48, offsetof(mavlink_simplantconfig_t, rated_current_A) }, \
         { "speed_max_rpm", NULL, MAVLINK_TYPE_FLOAT, 0, 52, offsetof(mavlink_simplantconfig_t, speed_max_rpm) }, \
         { "dt_s", NULL, MAVLINK_TYPE_FLOAT, 0, 56, offsetof(mavlink_simplantconfig_t, dt_s) }, \
         { "enc_line_p_n", NULL, MAVLINK_TYPE_UINT32_T, 0, 60, offsetof(mavlink_simplantconfig_t, enc_line_p_n) }, \
         { "j_inv", NULL, MAVLINK_TYPE_FLOAT, 0, 64, offsetof(mavlink_simplantconfig_t, j_inv) }, \
         { "ld_inv", NULL, MAVLINK_TYPE_FLOAT, 0, 68, offsetof(mavlink_simplantconfig_t, ld_inv) }, \
         { "lq_inv", NULL, MAVLINK_TYPE_FLOAT, 0, 72, offsetof(mavlink_simplantconfig_t, lq_inv) }, \
         { "enc_line_init_pos_P", NULL, MAVLINK_TYPE_INT64_T, 0, 0, offsetof(mavlink_simplantconfig_t, enc_line_init_pos_P) }, \
         { "enc_noise", NULL, MAVLINK_TYPE_FLOAT, 0, 76, offsetof(mavlink_simplantconfig_t, enc_noise) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_SimPlantConfig { \
    "SimPlantConfig", \
    19, \
    {  { "b", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_simplantconfig_t, b) }, \
         { "fc", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_simplantconfig_t, fc) }, \
         { "flux", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_simplantconfig_t, flux) }, \
         { "kt", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_simplantconfig_t, kt) }, \
         { "j", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_simplantconfig_t, j) }, \
         { "ld", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_simplantconfig_t, ld) }, \
         { "lq", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_simplantconfig_t, lq) }, \
         { "peak_current_A", NULL, MAVLINK_TYPE_FLOAT, 0, 36, offsetof(mavlink_simplantconfig_t, peak_current_A) }, \
         { "pn", NULL, MAVLINK_TYPE_FLOAT, 0, 40, offsetof(mavlink_simplantconfig_t, pn) }, \
         { "r", NULL, MAVLINK_TYPE_FLOAT, 0, 44, offsetof(mavlink_simplantconfig_t, r) }, \
         { "rated_current_A", NULL, MAVLINK_TYPE_FLOAT, 0, 48, offsetof(mavlink_simplantconfig_t, rated_current_A) }, \
         { "speed_max_rpm", NULL, MAVLINK_TYPE_FLOAT, 0, 52, offsetof(mavlink_simplantconfig_t, speed_max_rpm) }, \
         { "dt_s", NULL, MAVLINK_TYPE_FLOAT, 0, 56, offsetof(mavlink_simplantconfig_t, dt_s) }, \
         { "enc_line_p_n", NULL, MAVLINK_TYPE_UINT32_T, 0, 60, offsetof(mavlink_simplantconfig_t, enc_line_p_n) }, \
         { "j_inv", NULL, MAVLINK_TYPE_FLOAT, 0, 64, offsetof(mavlink_simplantconfig_t, j_inv) }, \
         { "ld_inv", NULL, MAVLINK_TYPE_FLOAT, 0, 68, offsetof(mavlink_simplantconfig_t, ld_inv) }, \
         { "lq_inv", NULL, MAVLINK_TYPE_FLOAT, 0, 72, offsetof(mavlink_simplantconfig_t, lq_inv) }, \
         { "enc_line_init_pos_P", NULL, MAVLINK_TYPE_INT64_T, 0, 0, offsetof(mavlink_simplantconfig_t, enc_line_init_pos_P) }, \
         { "enc_noise", NULL, MAVLINK_TYPE_FLOAT, 0, 76, offsetof(mavlink_simplantconfig_t, enc_noise) }, \
         } \
}
#endif

/**
 * @brief Pack a simplantconfig message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param b  
 * @param fc  
 * @param flux  
 * @param kt  
 * @param j  
 * @param ld  
 * @param lq  
 * @param peak_current_A  
 * @param pn  
 * @param r  
 * @param rated_current_A  
 * @param speed_max_rpm  
 * @param dt_s  
 * @param enc_line_p_n  
 * @param j_inv  
 * @param ld_inv  
 * @param lq_inv  
 * @param enc_line_init_pos_P  
 * @param enc_noise  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_simplantconfig_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               float b, float fc, float flux, float kt, float j, float ld, float lq, float peak_current_A, float pn, float r, float rated_current_A, float speed_max_rpm, float dt_s, uint32_t enc_line_p_n, float j_inv, float ld_inv, float lq_inv, int64_t enc_line_init_pos_P, float enc_noise)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SimPlantConfig_LEN];
    _mav_put_int64_t(buf, 0, enc_line_init_pos_P);
    _mav_put_float(buf, 8, b);
    _mav_put_float(buf, 12, fc);
    _mav_put_float(buf, 16, flux);
    _mav_put_float(buf, 20, kt);
    _mav_put_float(buf, 24, j);
    _mav_put_float(buf, 28, ld);
    _mav_put_float(buf, 32, lq);
    _mav_put_float(buf, 36, peak_current_A);
    _mav_put_float(buf, 40, pn);
    _mav_put_float(buf, 44, r);
    _mav_put_float(buf, 48, rated_current_A);
    _mav_put_float(buf, 52, speed_max_rpm);
    _mav_put_float(buf, 56, dt_s);
    _mav_put_uint32_t(buf, 60, enc_line_p_n);
    _mav_put_float(buf, 64, j_inv);
    _mav_put_float(buf, 68, ld_inv);
    _mav_put_float(buf, 72, lq_inv);
    _mav_put_float(buf, 76, enc_noise);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SimPlantConfig_LEN);
#else
    mavlink_simplantconfig_t packet;
    packet.enc_line_init_pos_P = enc_line_init_pos_P;
    packet.b = b;
    packet.fc = fc;
    packet.flux = flux;
    packet.kt = kt;
    packet.j = j;
    packet.ld = ld;
    packet.lq = lq;
    packet.peak_current_A = peak_current_A;
    packet.pn = pn;
    packet.r = r;
    packet.rated_current_A = rated_current_A;
    packet.speed_max_rpm = speed_max_rpm;
    packet.dt_s = dt_s;
    packet.enc_line_p_n = enc_line_p_n;
    packet.j_inv = j_inv;
    packet.ld_inv = ld_inv;
    packet.lq_inv = lq_inv;
    packet.enc_noise = enc_noise;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SimPlantConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SimPlantConfig;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_SimPlantConfig_MIN_LEN, MAVLINK_MSG_ID_SimPlantConfig_LEN, MAVLINK_MSG_ID_SimPlantConfig_CRC);
}

/**
 * @brief Pack a simplantconfig message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param b  
 * @param fc  
 * @param flux  
 * @param kt  
 * @param j  
 * @param ld  
 * @param lq  
 * @param peak_current_A  
 * @param pn  
 * @param r  
 * @param rated_current_A  
 * @param speed_max_rpm  
 * @param dt_s  
 * @param enc_line_p_n  
 * @param j_inv  
 * @param ld_inv  
 * @param lq_inv  
 * @param enc_line_init_pos_P  
 * @param enc_noise  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_simplantconfig_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               float b, float fc, float flux, float kt, float j, float ld, float lq, float peak_current_A, float pn, float r, float rated_current_A, float speed_max_rpm, float dt_s, uint32_t enc_line_p_n, float j_inv, float ld_inv, float lq_inv, int64_t enc_line_init_pos_P, float enc_noise)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SimPlantConfig_LEN];
    _mav_put_int64_t(buf, 0, enc_line_init_pos_P);
    _mav_put_float(buf, 8, b);
    _mav_put_float(buf, 12, fc);
    _mav_put_float(buf, 16, flux);
    _mav_put_float(buf, 20, kt);
    _mav_put_float(buf, 24, j);
    _mav_put_float(buf, 28, ld);
    _mav_put_float(buf, 32, lq);
    _mav_put_float(buf, 36, peak_current_A);
    _mav_put_float(buf, 40, pn);
    _mav_put_float(buf, 44, r);
    _mav_put_float(buf, 48, rated_current_A);
    _mav_put_float(buf, 52, speed_max_rpm);
    _mav_put_float(buf, 56, dt_s);
    _mav_put_uint32_t(buf, 60, enc_line_p_n);
    _mav_put_float(buf, 64, j_inv);
    _mav_put_float(buf, 68, ld_inv);
    _mav_put_float(buf, 72, lq_inv);
    _mav_put_float(buf, 76, enc_noise);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SimPlantConfig_LEN);
#else
    mavlink_simplantconfig_t packet;
    packet.enc_line_init_pos_P = enc_line_init_pos_P;
    packet.b = b;
    packet.fc = fc;
    packet.flux = flux;
    packet.kt = kt;
    packet.j = j;
    packet.ld = ld;
    packet.lq = lq;
    packet.peak_current_A = peak_current_A;
    packet.pn = pn;
    packet.r = r;
    packet.rated_current_A = rated_current_A;
    packet.speed_max_rpm = speed_max_rpm;
    packet.dt_s = dt_s;
    packet.enc_line_p_n = enc_line_p_n;
    packet.j_inv = j_inv;
    packet.ld_inv = ld_inv;
    packet.lq_inv = lq_inv;
    packet.enc_noise = enc_noise;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SimPlantConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SimPlantConfig;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_SimPlantConfig_MIN_LEN, MAVLINK_MSG_ID_SimPlantConfig_LEN, MAVLINK_MSG_ID_SimPlantConfig_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_SimPlantConfig_MIN_LEN, MAVLINK_MSG_ID_SimPlantConfig_LEN);
#endif
}

/**
 * @brief Pack a simplantconfig message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param b  
 * @param fc  
 * @param flux  
 * @param kt  
 * @param j  
 * @param ld  
 * @param lq  
 * @param peak_current_A  
 * @param pn  
 * @param r  
 * @param rated_current_A  
 * @param speed_max_rpm  
 * @param dt_s  
 * @param enc_line_p_n  
 * @param j_inv  
 * @param ld_inv  
 * @param lq_inv  
 * @param enc_line_init_pos_P  
 * @param enc_noise  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_simplantconfig_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   float b,float fc,float flux,float kt,float j,float ld,float lq,float peak_current_A,float pn,float r,float rated_current_A,float speed_max_rpm,float dt_s,uint32_t enc_line_p_n,float j_inv,float ld_inv,float lq_inv,int64_t enc_line_init_pos_P,float enc_noise)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SimPlantConfig_LEN];
    _mav_put_int64_t(buf, 0, enc_line_init_pos_P);
    _mav_put_float(buf, 8, b);
    _mav_put_float(buf, 12, fc);
    _mav_put_float(buf, 16, flux);
    _mav_put_float(buf, 20, kt);
    _mav_put_float(buf, 24, j);
    _mav_put_float(buf, 28, ld);
    _mav_put_float(buf, 32, lq);
    _mav_put_float(buf, 36, peak_current_A);
    _mav_put_float(buf, 40, pn);
    _mav_put_float(buf, 44, r);
    _mav_put_float(buf, 48, rated_current_A);
    _mav_put_float(buf, 52, speed_max_rpm);
    _mav_put_float(buf, 56, dt_s);
    _mav_put_uint32_t(buf, 60, enc_line_p_n);
    _mav_put_float(buf, 64, j_inv);
    _mav_put_float(buf, 68, ld_inv);
    _mav_put_float(buf, 72, lq_inv);
    _mav_put_float(buf, 76, enc_noise);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SimPlantConfig_LEN);
#else
    mavlink_simplantconfig_t packet;
    packet.enc_line_init_pos_P = enc_line_init_pos_P;
    packet.b = b;
    packet.fc = fc;
    packet.flux = flux;
    packet.kt = kt;
    packet.j = j;
    packet.ld = ld;
    packet.lq = lq;
    packet.peak_current_A = peak_current_A;
    packet.pn = pn;
    packet.r = r;
    packet.rated_current_A = rated_current_A;
    packet.speed_max_rpm = speed_max_rpm;
    packet.dt_s = dt_s;
    packet.enc_line_p_n = enc_line_p_n;
    packet.j_inv = j_inv;
    packet.ld_inv = ld_inv;
    packet.lq_inv = lq_inv;
    packet.enc_noise = enc_noise;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SimPlantConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SimPlantConfig;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_SimPlantConfig_MIN_LEN, MAVLINK_MSG_ID_SimPlantConfig_LEN, MAVLINK_MSG_ID_SimPlantConfig_CRC);
}

/**
 * @brief Encode a simplantconfig struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param simplantconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_simplantconfig_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_simplantconfig_t* simplantconfig)
{
    return mavlink_msg_simplantconfig_pack(system_id, component_id, msg, simplantconfig->b, simplantconfig->fc, simplantconfig->flux, simplantconfig->kt, simplantconfig->j, simplantconfig->ld, simplantconfig->lq, simplantconfig->peak_current_A, simplantconfig->pn, simplantconfig->r, simplantconfig->rated_current_A, simplantconfig->speed_max_rpm, simplantconfig->dt_s, simplantconfig->enc_line_p_n, simplantconfig->j_inv, simplantconfig->ld_inv, simplantconfig->lq_inv, simplantconfig->enc_line_init_pos_P, simplantconfig->enc_noise);
}

/**
 * @brief Encode a simplantconfig struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param simplantconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_simplantconfig_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_simplantconfig_t* simplantconfig)
{
    return mavlink_msg_simplantconfig_pack_chan(system_id, component_id, chan, msg, simplantconfig->b, simplantconfig->fc, simplantconfig->flux, simplantconfig->kt, simplantconfig->j, simplantconfig->ld, simplantconfig->lq, simplantconfig->peak_current_A, simplantconfig->pn, simplantconfig->r, simplantconfig->rated_current_A, simplantconfig->speed_max_rpm, simplantconfig->dt_s, simplantconfig->enc_line_p_n, simplantconfig->j_inv, simplantconfig->ld_inv, simplantconfig->lq_inv, simplantconfig->enc_line_init_pos_P, simplantconfig->enc_noise);
}

/**
 * @brief Encode a simplantconfig struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param simplantconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_simplantconfig_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_simplantconfig_t* simplantconfig)
{
    return mavlink_msg_simplantconfig_pack_status(system_id, component_id, _status, msg,  simplantconfig->b, simplantconfig->fc, simplantconfig->flux, simplantconfig->kt, simplantconfig->j, simplantconfig->ld, simplantconfig->lq, simplantconfig->peak_current_A, simplantconfig->pn, simplantconfig->r, simplantconfig->rated_current_A, simplantconfig->speed_max_rpm, simplantconfig->dt_s, simplantconfig->enc_line_p_n, simplantconfig->j_inv, simplantconfig->ld_inv, simplantconfig->lq_inv, simplantconfig->enc_line_init_pos_P, simplantconfig->enc_noise);
}

/**
 * @brief Send a simplantconfig message
 * @param chan MAVLink channel to send the message
 *
 * @param b  
 * @param fc  
 * @param flux  
 * @param kt  
 * @param j  
 * @param ld  
 * @param lq  
 * @param peak_current_A  
 * @param pn  
 * @param r  
 * @param rated_current_A  
 * @param speed_max_rpm  
 * @param dt_s  
 * @param enc_line_p_n  
 * @param j_inv  
 * @param ld_inv  
 * @param lq_inv  
 * @param enc_line_init_pos_P  
 * @param enc_noise  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_simplantconfig_send(mavlink_channel_t chan, float b, float fc, float flux, float kt, float j, float ld, float lq, float peak_current_A, float pn, float r, float rated_current_A, float speed_max_rpm, float dt_s, uint32_t enc_line_p_n, float j_inv, float ld_inv, float lq_inv, int64_t enc_line_init_pos_P, float enc_noise)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SimPlantConfig_LEN];
    _mav_put_int64_t(buf, 0, enc_line_init_pos_P);
    _mav_put_float(buf, 8, b);
    _mav_put_float(buf, 12, fc);
    _mav_put_float(buf, 16, flux);
    _mav_put_float(buf, 20, kt);
    _mav_put_float(buf, 24, j);
    _mav_put_float(buf, 28, ld);
    _mav_put_float(buf, 32, lq);
    _mav_put_float(buf, 36, peak_current_A);
    _mav_put_float(buf, 40, pn);
    _mav_put_float(buf, 44, r);
    _mav_put_float(buf, 48, rated_current_A);
    _mav_put_float(buf, 52, speed_max_rpm);
    _mav_put_float(buf, 56, dt_s);
    _mav_put_uint32_t(buf, 60, enc_line_p_n);
    _mav_put_float(buf, 64, j_inv);
    _mav_put_float(buf, 68, ld_inv);
    _mav_put_float(buf, 72, lq_inv);
    _mav_put_float(buf, 76, enc_noise);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SimPlantConfig, buf, MAVLINK_MSG_ID_SimPlantConfig_MIN_LEN, MAVLINK_MSG_ID_SimPlantConfig_LEN, MAVLINK_MSG_ID_SimPlantConfig_CRC);
#else
    mavlink_simplantconfig_t packet;
    packet.enc_line_init_pos_P = enc_line_init_pos_P;
    packet.b = b;
    packet.fc = fc;
    packet.flux = flux;
    packet.kt = kt;
    packet.j = j;
    packet.ld = ld;
    packet.lq = lq;
    packet.peak_current_A = peak_current_A;
    packet.pn = pn;
    packet.r = r;
    packet.rated_current_A = rated_current_A;
    packet.speed_max_rpm = speed_max_rpm;
    packet.dt_s = dt_s;
    packet.enc_line_p_n = enc_line_p_n;
    packet.j_inv = j_inv;
    packet.ld_inv = ld_inv;
    packet.lq_inv = lq_inv;
    packet.enc_noise = enc_noise;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SimPlantConfig, (const char *)&packet, MAVLINK_MSG_ID_SimPlantConfig_MIN_LEN, MAVLINK_MSG_ID_SimPlantConfig_LEN, MAVLINK_MSG_ID_SimPlantConfig_CRC);
#endif
}

/**
 * @brief Send a simplantconfig message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_simplantconfig_send_struct(mavlink_channel_t chan, const mavlink_simplantconfig_t* simplantconfig)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_simplantconfig_send(chan, simplantconfig->b, simplantconfig->fc, simplantconfig->flux, simplantconfig->kt, simplantconfig->j, simplantconfig->ld, simplantconfig->lq, simplantconfig->peak_current_A, simplantconfig->pn, simplantconfig->r, simplantconfig->rated_current_A, simplantconfig->speed_max_rpm, simplantconfig->dt_s, simplantconfig->enc_line_p_n, simplantconfig->j_inv, simplantconfig->ld_inv, simplantconfig->lq_inv, simplantconfig->enc_line_init_pos_P, simplantconfig->enc_noise);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SimPlantConfig, (const char *)simplantconfig, MAVLINK_MSG_ID_SimPlantConfig_MIN_LEN, MAVLINK_MSG_ID_SimPlantConfig_LEN, MAVLINK_MSG_ID_SimPlantConfig_CRC);
#endif
}

#if MAVLINK_MSG_ID_SimPlantConfig_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_simplantconfig_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float b, float fc, float flux, float kt, float j, float ld, float lq, float peak_current_A, float pn, float r, float rated_current_A, float speed_max_rpm, float dt_s, uint32_t enc_line_p_n, float j_inv, float ld_inv, float lq_inv, int64_t enc_line_init_pos_P, float enc_noise)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_int64_t(buf, 0, enc_line_init_pos_P);
    _mav_put_float(buf, 8, b);
    _mav_put_float(buf, 12, fc);
    _mav_put_float(buf, 16, flux);
    _mav_put_float(buf, 20, kt);
    _mav_put_float(buf, 24, j);
    _mav_put_float(buf, 28, ld);
    _mav_put_float(buf, 32, lq);
    _mav_put_float(buf, 36, peak_current_A);
    _mav_put_float(buf, 40, pn);
    _mav_put_float(buf, 44, r);
    _mav_put_float(buf, 48, rated_current_A);
    _mav_put_float(buf, 52, speed_max_rpm);
    _mav_put_float(buf, 56, dt_s);
    _mav_put_uint32_t(buf, 60, enc_line_p_n);
    _mav_put_float(buf, 64, j_inv);
    _mav_put_float(buf, 68, ld_inv);
    _mav_put_float(buf, 72, lq_inv);
    _mav_put_float(buf, 76, enc_noise);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SimPlantConfig, buf, MAVLINK_MSG_ID_SimPlantConfig_MIN_LEN, MAVLINK_MSG_ID_SimPlantConfig_LEN, MAVLINK_MSG_ID_SimPlantConfig_CRC);
#else
    mavlink_simplantconfig_t *packet = (mavlink_simplantconfig_t *)msgbuf;
    packet->enc_line_init_pos_P = enc_line_init_pos_P;
    packet->b = b;
    packet->fc = fc;
    packet->flux = flux;
    packet->kt = kt;
    packet->j = j;
    packet->ld = ld;
    packet->lq = lq;
    packet->peak_current_A = peak_current_A;
    packet->pn = pn;
    packet->r = r;
    packet->rated_current_A = rated_current_A;
    packet->speed_max_rpm = speed_max_rpm;
    packet->dt_s = dt_s;
    packet->enc_line_p_n = enc_line_p_n;
    packet->j_inv = j_inv;
    packet->ld_inv = ld_inv;
    packet->lq_inv = lq_inv;
    packet->enc_noise = enc_noise;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SimPlantConfig, (const char *)packet, MAVLINK_MSG_ID_SimPlantConfig_MIN_LEN, MAVLINK_MSG_ID_SimPlantConfig_LEN, MAVLINK_MSG_ID_SimPlantConfig_CRC);
#endif
}
#endif

#endif

// MESSAGE SimPlantConfig UNPACKING


/**
 * @brief Get field b from simplantconfig message
 *
 * @return  
 */
static inline float mavlink_msg_simplantconfig_get_b(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field fc from simplantconfig message
 *
 * @return  
 */
static inline float mavlink_msg_simplantconfig_get_fc(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Get field flux from simplantconfig message
 *
 * @return  
 */
static inline float mavlink_msg_simplantconfig_get_flux(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  16);
}

/**
 * @brief Get field kt from simplantconfig message
 *
 * @return  
 */
static inline float mavlink_msg_simplantconfig_get_kt(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  20);
}

/**
 * @brief Get field j from simplantconfig message
 *
 * @return  
 */
static inline float mavlink_msg_simplantconfig_get_j(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  24);
}

/**
 * @brief Get field ld from simplantconfig message
 *
 * @return  
 */
static inline float mavlink_msg_simplantconfig_get_ld(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  28);
}

/**
 * @brief Get field lq from simplantconfig message
 *
 * @return  
 */
static inline float mavlink_msg_simplantconfig_get_lq(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  32);
}

/**
 * @brief Get field peak_current_A from simplantconfig message
 *
 * @return  
 */
static inline float mavlink_msg_simplantconfig_get_peak_current_A(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  36);
}

/**
 * @brief Get field pn from simplantconfig message
 *
 * @return  
 */
static inline float mavlink_msg_simplantconfig_get_pn(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  40);
}

/**
 * @brief Get field r from simplantconfig message
 *
 * @return  
 */
static inline float mavlink_msg_simplantconfig_get_r(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  44);
}

/**
 * @brief Get field rated_current_A from simplantconfig message
 *
 * @return  
 */
static inline float mavlink_msg_simplantconfig_get_rated_current_A(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  48);
}

/**
 * @brief Get field speed_max_rpm from simplantconfig message
 *
 * @return  
 */
static inline float mavlink_msg_simplantconfig_get_speed_max_rpm(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  52);
}

/**
 * @brief Get field dt_s from simplantconfig message
 *
 * @return  
 */
static inline float mavlink_msg_simplantconfig_get_dt_s(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  56);
}

/**
 * @brief Get field enc_line_p_n from simplantconfig message
 *
 * @return  
 */
static inline uint32_t mavlink_msg_simplantconfig_get_enc_line_p_n(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  60);
}

/**
 * @brief Get field j_inv from simplantconfig message
 *
 * @return  
 */
static inline float mavlink_msg_simplantconfig_get_j_inv(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  64);
}

/**
 * @brief Get field ld_inv from simplantconfig message
 *
 * @return  
 */
static inline float mavlink_msg_simplantconfig_get_ld_inv(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  68);
}

/**
 * @brief Get field lq_inv from simplantconfig message
 *
 * @return  
 */
static inline float mavlink_msg_simplantconfig_get_lq_inv(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  72);
}

/**
 * @brief Get field enc_line_init_pos_P from simplantconfig message
 *
 * @return  
 */
static inline int64_t mavlink_msg_simplantconfig_get_enc_line_init_pos_P(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int64_t(msg,  0);
}

/**
 * @brief Get field enc_noise from simplantconfig message
 *
 * @return  
 */
static inline float mavlink_msg_simplantconfig_get_enc_noise(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  76);
}

/**
 * @brief Decode a simplantconfig message into a struct
 *
 * @param msg The message to decode
 * @param simplantconfig C-struct to decode the message contents into
 */
static inline void mavlink_msg_simplantconfig_decode(const mavlink_message_t* msg, mavlink_simplantconfig_t* simplantconfig)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    simplantconfig->enc_line_init_pos_P = mavlink_msg_simplantconfig_get_enc_line_init_pos_P(msg);
    simplantconfig->b = mavlink_msg_simplantconfig_get_b(msg);
    simplantconfig->fc = mavlink_msg_simplantconfig_get_fc(msg);
    simplantconfig->flux = mavlink_msg_simplantconfig_get_flux(msg);
    simplantconfig->kt = mavlink_msg_simplantconfig_get_kt(msg);
    simplantconfig->j = mavlink_msg_simplantconfig_get_j(msg);
    simplantconfig->ld = mavlink_msg_simplantconfig_get_ld(msg);
    simplantconfig->lq = mavlink_msg_simplantconfig_get_lq(msg);
    simplantconfig->peak_current_A = mavlink_msg_simplantconfig_get_peak_current_A(msg);
    simplantconfig->pn = mavlink_msg_simplantconfig_get_pn(msg);
    simplantconfig->r = mavlink_msg_simplantconfig_get_r(msg);
    simplantconfig->rated_current_A = mavlink_msg_simplantconfig_get_rated_current_A(msg);
    simplantconfig->speed_max_rpm = mavlink_msg_simplantconfig_get_speed_max_rpm(msg);
    simplantconfig->dt_s = mavlink_msg_simplantconfig_get_dt_s(msg);
    simplantconfig->enc_line_p_n = mavlink_msg_simplantconfig_get_enc_line_p_n(msg);
    simplantconfig->j_inv = mavlink_msg_simplantconfig_get_j_inv(msg);
    simplantconfig->ld_inv = mavlink_msg_simplantconfig_get_ld_inv(msg);
    simplantconfig->lq_inv = mavlink_msg_simplantconfig_get_lq_inv(msg);
    simplantconfig->enc_noise = mavlink_msg_simplantconfig_get_enc_noise(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_SimPlantConfig_LEN? msg->len : MAVLINK_MSG_ID_SimPlantConfig_LEN;
        memset(simplantconfig, 0, MAVLINK_MSG_ID_SimPlantConfig_LEN);
    memcpy(simplantconfig, _MAV_PAYLOAD(msg), len);
#endif
}
