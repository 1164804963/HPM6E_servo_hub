#pragma once
// MESSAGE PmsmConfig PACKING

#define MAVLINK_MSG_ID_PmsmConfig 30001


typedef struct __mavlink_pmsmconfig_t {
 float b; /*<  */
 float fc; /*<  */
 float flux; /*<  */
 float j; /*<  */
 float ld; /*<  */
 float lq; /*<  */
 float peak_current; /*<  */
 float pn; /*<  */
 float r; /*<  */
 float rated_current; /*<  */
 float speed_max_rpm; /*<  */
 float tp_s; /*<  */
 float tc_s; /*<  */
 uint32_t enc_line_p_n; /*<  */
 float kt; /*<  */
} mavlink_pmsmconfig_t;

#define MAVLINK_MSG_ID_PmsmConfig_LEN 60
#define MAVLINK_MSG_ID_PmsmConfig_MIN_LEN 60
#define MAVLINK_MSG_ID_30001_LEN 60
#define MAVLINK_MSG_ID_30001_MIN_LEN 60

#define MAVLINK_MSG_ID_PmsmConfig_CRC 118
#define MAVLINK_MSG_ID_30001_CRC 118



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_PmsmConfig { \
    30001, \
    "PmsmConfig", \
    15, \
    {  { "b", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_pmsmconfig_t, b) }, \
         { "fc", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_pmsmconfig_t, fc) }, \
         { "flux", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_pmsmconfig_t, flux) }, \
         { "j", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_pmsmconfig_t, j) }, \
         { "ld", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_pmsmconfig_t, ld) }, \
         { "lq", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_pmsmconfig_t, lq) }, \
         { "peak_current", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_pmsmconfig_t, peak_current) }, \
         { "pn", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_pmsmconfig_t, pn) }, \
         { "r", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_pmsmconfig_t, r) }, \
         { "rated_current", NULL, MAVLINK_TYPE_FLOAT, 0, 36, offsetof(mavlink_pmsmconfig_t, rated_current) }, \
         { "speed_max_rpm", NULL, MAVLINK_TYPE_FLOAT, 0, 40, offsetof(mavlink_pmsmconfig_t, speed_max_rpm) }, \
         { "tp_s", NULL, MAVLINK_TYPE_FLOAT, 0, 44, offsetof(mavlink_pmsmconfig_t, tp_s) }, \
         { "tc_s", NULL, MAVLINK_TYPE_FLOAT, 0, 48, offsetof(mavlink_pmsmconfig_t, tc_s) }, \
         { "enc_line_p_n", NULL, MAVLINK_TYPE_UINT32_T, 0, 52, offsetof(mavlink_pmsmconfig_t, enc_line_p_n) }, \
         { "kt", NULL, MAVLINK_TYPE_FLOAT, 0, 56, offsetof(mavlink_pmsmconfig_t, kt) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_PmsmConfig { \
    "PmsmConfig", \
    15, \
    {  { "b", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_pmsmconfig_t, b) }, \
         { "fc", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_pmsmconfig_t, fc) }, \
         { "flux", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_pmsmconfig_t, flux) }, \
         { "j", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_pmsmconfig_t, j) }, \
         { "ld", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_pmsmconfig_t, ld) }, \
         { "lq", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_pmsmconfig_t, lq) }, \
         { "peak_current", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_pmsmconfig_t, peak_current) }, \
         { "pn", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_pmsmconfig_t, pn) }, \
         { "r", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_pmsmconfig_t, r) }, \
         { "rated_current", NULL, MAVLINK_TYPE_FLOAT, 0, 36, offsetof(mavlink_pmsmconfig_t, rated_current) }, \
         { "speed_max_rpm", NULL, MAVLINK_TYPE_FLOAT, 0, 40, offsetof(mavlink_pmsmconfig_t, speed_max_rpm) }, \
         { "tp_s", NULL, MAVLINK_TYPE_FLOAT, 0, 44, offsetof(mavlink_pmsmconfig_t, tp_s) }, \
         { "tc_s", NULL, MAVLINK_TYPE_FLOAT, 0, 48, offsetof(mavlink_pmsmconfig_t, tc_s) }, \
         { "enc_line_p_n", NULL, MAVLINK_TYPE_UINT32_T, 0, 52, offsetof(mavlink_pmsmconfig_t, enc_line_p_n) }, \
         { "kt", NULL, MAVLINK_TYPE_FLOAT, 0, 56, offsetof(mavlink_pmsmconfig_t, kt) }, \
         } \
}
#endif

/**
 * @brief Pack a pmsmconfig message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param b  
 * @param fc  
 * @param flux  
 * @param j  
 * @param ld  
 * @param lq  
 * @param peak_current  
 * @param pn  
 * @param r  
 * @param rated_current  
 * @param speed_max_rpm  
 * @param tp_s  
 * @param tc_s  
 * @param enc_line_p_n  
 * @param kt  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_pmsmconfig_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               float b, float fc, float flux, float j, float ld, float lq, float peak_current, float pn, float r, float rated_current, float speed_max_rpm, float tp_s, float tc_s, uint32_t enc_line_p_n, float kt)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PmsmConfig_LEN];
    _mav_put_float(buf, 0, b);
    _mav_put_float(buf, 4, fc);
    _mav_put_float(buf, 8, flux);
    _mav_put_float(buf, 12, j);
    _mav_put_float(buf, 16, ld);
    _mav_put_float(buf, 20, lq);
    _mav_put_float(buf, 24, peak_current);
    _mav_put_float(buf, 28, pn);
    _mav_put_float(buf, 32, r);
    _mav_put_float(buf, 36, rated_current);
    _mav_put_float(buf, 40, speed_max_rpm);
    _mav_put_float(buf, 44, tp_s);
    _mav_put_float(buf, 48, tc_s);
    _mav_put_uint32_t(buf, 52, enc_line_p_n);
    _mav_put_float(buf, 56, kt);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_PmsmConfig_LEN);
#else
    mavlink_pmsmconfig_t packet;
    packet.b = b;
    packet.fc = fc;
    packet.flux = flux;
    packet.j = j;
    packet.ld = ld;
    packet.lq = lq;
    packet.peak_current = peak_current;
    packet.pn = pn;
    packet.r = r;
    packet.rated_current = rated_current;
    packet.speed_max_rpm = speed_max_rpm;
    packet.tp_s = tp_s;
    packet.tc_s = tc_s;
    packet.enc_line_p_n = enc_line_p_n;
    packet.kt = kt;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_PmsmConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_PmsmConfig;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_PmsmConfig_MIN_LEN, MAVLINK_MSG_ID_PmsmConfig_LEN, MAVLINK_MSG_ID_PmsmConfig_CRC);
}

/**
 * @brief Pack a pmsmconfig message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param b  
 * @param fc  
 * @param flux  
 * @param j  
 * @param ld  
 * @param lq  
 * @param peak_current  
 * @param pn  
 * @param r  
 * @param rated_current  
 * @param speed_max_rpm  
 * @param tp_s  
 * @param tc_s  
 * @param enc_line_p_n  
 * @param kt  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_pmsmconfig_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               float b, float fc, float flux, float j, float ld, float lq, float peak_current, float pn, float r, float rated_current, float speed_max_rpm, float tp_s, float tc_s, uint32_t enc_line_p_n, float kt)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PmsmConfig_LEN];
    _mav_put_float(buf, 0, b);
    _mav_put_float(buf, 4, fc);
    _mav_put_float(buf, 8, flux);
    _mav_put_float(buf, 12, j);
    _mav_put_float(buf, 16, ld);
    _mav_put_float(buf, 20, lq);
    _mav_put_float(buf, 24, peak_current);
    _mav_put_float(buf, 28, pn);
    _mav_put_float(buf, 32, r);
    _mav_put_float(buf, 36, rated_current);
    _mav_put_float(buf, 40, speed_max_rpm);
    _mav_put_float(buf, 44, tp_s);
    _mav_put_float(buf, 48, tc_s);
    _mav_put_uint32_t(buf, 52, enc_line_p_n);
    _mav_put_float(buf, 56, kt);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_PmsmConfig_LEN);
#else
    mavlink_pmsmconfig_t packet;
    packet.b = b;
    packet.fc = fc;
    packet.flux = flux;
    packet.j = j;
    packet.ld = ld;
    packet.lq = lq;
    packet.peak_current = peak_current;
    packet.pn = pn;
    packet.r = r;
    packet.rated_current = rated_current;
    packet.speed_max_rpm = speed_max_rpm;
    packet.tp_s = tp_s;
    packet.tc_s = tc_s;
    packet.enc_line_p_n = enc_line_p_n;
    packet.kt = kt;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_PmsmConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_PmsmConfig;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_PmsmConfig_MIN_LEN, MAVLINK_MSG_ID_PmsmConfig_LEN, MAVLINK_MSG_ID_PmsmConfig_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_PmsmConfig_MIN_LEN, MAVLINK_MSG_ID_PmsmConfig_LEN);
#endif
}

/**
 * @brief Pack a pmsmconfig message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param b  
 * @param fc  
 * @param flux  
 * @param j  
 * @param ld  
 * @param lq  
 * @param peak_current  
 * @param pn  
 * @param r  
 * @param rated_current  
 * @param speed_max_rpm  
 * @param tp_s  
 * @param tc_s  
 * @param enc_line_p_n  
 * @param kt  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_pmsmconfig_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   float b,float fc,float flux,float j,float ld,float lq,float peak_current,float pn,float r,float rated_current,float speed_max_rpm,float tp_s,float tc_s,uint32_t enc_line_p_n,float kt)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PmsmConfig_LEN];
    _mav_put_float(buf, 0, b);
    _mav_put_float(buf, 4, fc);
    _mav_put_float(buf, 8, flux);
    _mav_put_float(buf, 12, j);
    _mav_put_float(buf, 16, ld);
    _mav_put_float(buf, 20, lq);
    _mav_put_float(buf, 24, peak_current);
    _mav_put_float(buf, 28, pn);
    _mav_put_float(buf, 32, r);
    _mav_put_float(buf, 36, rated_current);
    _mav_put_float(buf, 40, speed_max_rpm);
    _mav_put_float(buf, 44, tp_s);
    _mav_put_float(buf, 48, tc_s);
    _mav_put_uint32_t(buf, 52, enc_line_p_n);
    _mav_put_float(buf, 56, kt);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_PmsmConfig_LEN);
#else
    mavlink_pmsmconfig_t packet;
    packet.b = b;
    packet.fc = fc;
    packet.flux = flux;
    packet.j = j;
    packet.ld = ld;
    packet.lq = lq;
    packet.peak_current = peak_current;
    packet.pn = pn;
    packet.r = r;
    packet.rated_current = rated_current;
    packet.speed_max_rpm = speed_max_rpm;
    packet.tp_s = tp_s;
    packet.tc_s = tc_s;
    packet.enc_line_p_n = enc_line_p_n;
    packet.kt = kt;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_PmsmConfig_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_PmsmConfig;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_PmsmConfig_MIN_LEN, MAVLINK_MSG_ID_PmsmConfig_LEN, MAVLINK_MSG_ID_PmsmConfig_CRC);
}

/**
 * @brief Encode a pmsmconfig struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param pmsmconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_pmsmconfig_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_pmsmconfig_t* pmsmconfig)
{
    return mavlink_msg_pmsmconfig_pack(system_id, component_id, msg, pmsmconfig->b, pmsmconfig->fc, pmsmconfig->flux, pmsmconfig->j, pmsmconfig->ld, pmsmconfig->lq, pmsmconfig->peak_current, pmsmconfig->pn, pmsmconfig->r, pmsmconfig->rated_current, pmsmconfig->speed_max_rpm, pmsmconfig->tp_s, pmsmconfig->tc_s, pmsmconfig->enc_line_p_n, pmsmconfig->kt);
}

/**
 * @brief Encode a pmsmconfig struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param pmsmconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_pmsmconfig_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_pmsmconfig_t* pmsmconfig)
{
    return mavlink_msg_pmsmconfig_pack_chan(system_id, component_id, chan, msg, pmsmconfig->b, pmsmconfig->fc, pmsmconfig->flux, pmsmconfig->j, pmsmconfig->ld, pmsmconfig->lq, pmsmconfig->peak_current, pmsmconfig->pn, pmsmconfig->r, pmsmconfig->rated_current, pmsmconfig->speed_max_rpm, pmsmconfig->tp_s, pmsmconfig->tc_s, pmsmconfig->enc_line_p_n, pmsmconfig->kt);
}

/**
 * @brief Encode a pmsmconfig struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param pmsmconfig C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_pmsmconfig_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_pmsmconfig_t* pmsmconfig)
{
    return mavlink_msg_pmsmconfig_pack_status(system_id, component_id, _status, msg,  pmsmconfig->b, pmsmconfig->fc, pmsmconfig->flux, pmsmconfig->j, pmsmconfig->ld, pmsmconfig->lq, pmsmconfig->peak_current, pmsmconfig->pn, pmsmconfig->r, pmsmconfig->rated_current, pmsmconfig->speed_max_rpm, pmsmconfig->tp_s, pmsmconfig->tc_s, pmsmconfig->enc_line_p_n, pmsmconfig->kt);
}

/**
 * @brief Send a pmsmconfig message
 * @param chan MAVLink channel to send the message
 *
 * @param b  
 * @param fc  
 * @param flux  
 * @param j  
 * @param ld  
 * @param lq  
 * @param peak_current  
 * @param pn  
 * @param r  
 * @param rated_current  
 * @param speed_max_rpm  
 * @param tp_s  
 * @param tc_s  
 * @param enc_line_p_n  
 * @param kt  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_pmsmconfig_send(mavlink_channel_t chan, float b, float fc, float flux, float j, float ld, float lq, float peak_current, float pn, float r, float rated_current, float speed_max_rpm, float tp_s, float tc_s, uint32_t enc_line_p_n, float kt)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PmsmConfig_LEN];
    _mav_put_float(buf, 0, b);
    _mav_put_float(buf, 4, fc);
    _mav_put_float(buf, 8, flux);
    _mav_put_float(buf, 12, j);
    _mav_put_float(buf, 16, ld);
    _mav_put_float(buf, 20, lq);
    _mav_put_float(buf, 24, peak_current);
    _mav_put_float(buf, 28, pn);
    _mav_put_float(buf, 32, r);
    _mav_put_float(buf, 36, rated_current);
    _mav_put_float(buf, 40, speed_max_rpm);
    _mav_put_float(buf, 44, tp_s);
    _mav_put_float(buf, 48, tc_s);
    _mav_put_uint32_t(buf, 52, enc_line_p_n);
    _mav_put_float(buf, 56, kt);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PmsmConfig, buf, MAVLINK_MSG_ID_PmsmConfig_MIN_LEN, MAVLINK_MSG_ID_PmsmConfig_LEN, MAVLINK_MSG_ID_PmsmConfig_CRC);
#else
    mavlink_pmsmconfig_t packet;
    packet.b = b;
    packet.fc = fc;
    packet.flux = flux;
    packet.j = j;
    packet.ld = ld;
    packet.lq = lq;
    packet.peak_current = peak_current;
    packet.pn = pn;
    packet.r = r;
    packet.rated_current = rated_current;
    packet.speed_max_rpm = speed_max_rpm;
    packet.tp_s = tp_s;
    packet.tc_s = tc_s;
    packet.enc_line_p_n = enc_line_p_n;
    packet.kt = kt;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PmsmConfig, (const char *)&packet, MAVLINK_MSG_ID_PmsmConfig_MIN_LEN, MAVLINK_MSG_ID_PmsmConfig_LEN, MAVLINK_MSG_ID_PmsmConfig_CRC);
#endif
}

/**
 * @brief Send a pmsmconfig message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_pmsmconfig_send_struct(mavlink_channel_t chan, const mavlink_pmsmconfig_t* pmsmconfig)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_pmsmconfig_send(chan, pmsmconfig->b, pmsmconfig->fc, pmsmconfig->flux, pmsmconfig->j, pmsmconfig->ld, pmsmconfig->lq, pmsmconfig->peak_current, pmsmconfig->pn, pmsmconfig->r, pmsmconfig->rated_current, pmsmconfig->speed_max_rpm, pmsmconfig->tp_s, pmsmconfig->tc_s, pmsmconfig->enc_line_p_n, pmsmconfig->kt);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PmsmConfig, (const char *)pmsmconfig, MAVLINK_MSG_ID_PmsmConfig_MIN_LEN, MAVLINK_MSG_ID_PmsmConfig_LEN, MAVLINK_MSG_ID_PmsmConfig_CRC);
#endif
}

#if MAVLINK_MSG_ID_PmsmConfig_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_pmsmconfig_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float b, float fc, float flux, float j, float ld, float lq, float peak_current, float pn, float r, float rated_current, float speed_max_rpm, float tp_s, float tc_s, uint32_t enc_line_p_n, float kt)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, b);
    _mav_put_float(buf, 4, fc);
    _mav_put_float(buf, 8, flux);
    _mav_put_float(buf, 12, j);
    _mav_put_float(buf, 16, ld);
    _mav_put_float(buf, 20, lq);
    _mav_put_float(buf, 24, peak_current);
    _mav_put_float(buf, 28, pn);
    _mav_put_float(buf, 32, r);
    _mav_put_float(buf, 36, rated_current);
    _mav_put_float(buf, 40, speed_max_rpm);
    _mav_put_float(buf, 44, tp_s);
    _mav_put_float(buf, 48, tc_s);
    _mav_put_uint32_t(buf, 52, enc_line_p_n);
    _mav_put_float(buf, 56, kt);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PmsmConfig, buf, MAVLINK_MSG_ID_PmsmConfig_MIN_LEN, MAVLINK_MSG_ID_PmsmConfig_LEN, MAVLINK_MSG_ID_PmsmConfig_CRC);
#else
    mavlink_pmsmconfig_t *packet = (mavlink_pmsmconfig_t *)msgbuf;
    packet->b = b;
    packet->fc = fc;
    packet->flux = flux;
    packet->j = j;
    packet->ld = ld;
    packet->lq = lq;
    packet->peak_current = peak_current;
    packet->pn = pn;
    packet->r = r;
    packet->rated_current = rated_current;
    packet->speed_max_rpm = speed_max_rpm;
    packet->tp_s = tp_s;
    packet->tc_s = tc_s;
    packet->enc_line_p_n = enc_line_p_n;
    packet->kt = kt;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PmsmConfig, (const char *)packet, MAVLINK_MSG_ID_PmsmConfig_MIN_LEN, MAVLINK_MSG_ID_PmsmConfig_LEN, MAVLINK_MSG_ID_PmsmConfig_CRC);
#endif
}
#endif

#endif

// MESSAGE PmsmConfig UNPACKING


/**
 * @brief Get field b from pmsmconfig message
 *
 * @return  
 */
static inline float mavlink_msg_pmsmconfig_get_b(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field fc from pmsmconfig message
 *
 * @return  
 */
static inline float mavlink_msg_pmsmconfig_get_fc(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field flux from pmsmconfig message
 *
 * @return  
 */
static inline float mavlink_msg_pmsmconfig_get_flux(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field j from pmsmconfig message
 *
 * @return  
 */
static inline float mavlink_msg_pmsmconfig_get_j(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Get field ld from pmsmconfig message
 *
 * @return  
 */
static inline float mavlink_msg_pmsmconfig_get_ld(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  16);
}

/**
 * @brief Get field lq from pmsmconfig message
 *
 * @return  
 */
static inline float mavlink_msg_pmsmconfig_get_lq(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  20);
}

/**
 * @brief Get field peak_current from pmsmconfig message
 *
 * @return  
 */
static inline float mavlink_msg_pmsmconfig_get_peak_current(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  24);
}

/**
 * @brief Get field pn from pmsmconfig message
 *
 * @return  
 */
static inline float mavlink_msg_pmsmconfig_get_pn(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  28);
}

/**
 * @brief Get field r from pmsmconfig message
 *
 * @return  
 */
static inline float mavlink_msg_pmsmconfig_get_r(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  32);
}

/**
 * @brief Get field rated_current from pmsmconfig message
 *
 * @return  
 */
static inline float mavlink_msg_pmsmconfig_get_rated_current(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  36);
}

/**
 * @brief Get field speed_max_rpm from pmsmconfig message
 *
 * @return  
 */
static inline float mavlink_msg_pmsmconfig_get_speed_max_rpm(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  40);
}

/**
 * @brief Get field tp_s from pmsmconfig message
 *
 * @return  
 */
static inline float mavlink_msg_pmsmconfig_get_tp_s(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  44);
}

/**
 * @brief Get field tc_s from pmsmconfig message
 *
 * @return  
 */
static inline float mavlink_msg_pmsmconfig_get_tc_s(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  48);
}

/**
 * @brief Get field enc_line_p_n from pmsmconfig message
 *
 * @return  
 */
static inline uint32_t mavlink_msg_pmsmconfig_get_enc_line_p_n(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  52);
}

/**
 * @brief Get field kt from pmsmconfig message
 *
 * @return  
 */
static inline float mavlink_msg_pmsmconfig_get_kt(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  56);
}

/**
 * @brief Decode a pmsmconfig message into a struct
 *
 * @param msg The message to decode
 * @param pmsmconfig C-struct to decode the message contents into
 */
static inline void mavlink_msg_pmsmconfig_decode(const mavlink_message_t* msg, mavlink_pmsmconfig_t* pmsmconfig)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    pmsmconfig->b = mavlink_msg_pmsmconfig_get_b(msg);
    pmsmconfig->fc = mavlink_msg_pmsmconfig_get_fc(msg);
    pmsmconfig->flux = mavlink_msg_pmsmconfig_get_flux(msg);
    pmsmconfig->j = mavlink_msg_pmsmconfig_get_j(msg);
    pmsmconfig->ld = mavlink_msg_pmsmconfig_get_ld(msg);
    pmsmconfig->lq = mavlink_msg_pmsmconfig_get_lq(msg);
    pmsmconfig->peak_current = mavlink_msg_pmsmconfig_get_peak_current(msg);
    pmsmconfig->pn = mavlink_msg_pmsmconfig_get_pn(msg);
    pmsmconfig->r = mavlink_msg_pmsmconfig_get_r(msg);
    pmsmconfig->rated_current = mavlink_msg_pmsmconfig_get_rated_current(msg);
    pmsmconfig->speed_max_rpm = mavlink_msg_pmsmconfig_get_speed_max_rpm(msg);
    pmsmconfig->tp_s = mavlink_msg_pmsmconfig_get_tp_s(msg);
    pmsmconfig->tc_s = mavlink_msg_pmsmconfig_get_tc_s(msg);
    pmsmconfig->enc_line_p_n = mavlink_msg_pmsmconfig_get_enc_line_p_n(msg);
    pmsmconfig->kt = mavlink_msg_pmsmconfig_get_kt(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_PmsmConfig_LEN? msg->len : MAVLINK_MSG_ID_PmsmConfig_LEN;
        memset(pmsmconfig, 0, MAVLINK_MSG_ID_PmsmConfig_LEN);
    memcpy(pmsmconfig, _MAV_PAYLOAD(msg), len);
#endif
}
