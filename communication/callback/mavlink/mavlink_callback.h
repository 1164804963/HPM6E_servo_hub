#ifndef MAVLINK_CALLBACK_H
#define MAVLINK_CALLBACK_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "data_type_define.h"

#include "motor_ctl_loop.h"
#include "data_param.h"

#include "stdint.h"
#include "mavlink.h"
#include "mavlink_scope_interface.h"
#include "waveform_app.h"
#include "data_param.h"
#ifdef HPMSOC_HAS_HPMSDK_MCHTMR
#include "hpm_common.h"
#endif

#define MAVLINK_SEND_BUFF_SIZE          512
#define MAVLINK_RECV_BUFF_SIZE          512
#define MAVLINK_PARSE_ERROR_THRESHOLD   (MAVLINK_RECV_BUFF_SIZE + 100)  // 解析失败阈值

typedef enum
{
	CAN_HOST	= 0,
	USART_HOST,
} HOST_CONTROL;

typedef struct {
    uint8_t type;
    int8_t direction;
    uint32_t resolution;
} EncoderConfig;

typedef struct {
    int8_t param_save;
    int8_t system_reset;
    uint32_t current_loop_freq;
    uint32_t position_loop_freq;
}SystemConfig;

// 定义回调函数类型，接受一个 uint8_t 类型的参数
typedef void (*MavlinkSendCallbackFunction)(uint8_t *pdata, uint32_t len);

// 回调函数注册表结构体
typedef struct {
    MavlinkSendCallbackFunction callback;
} SendCallbackRegistry;

void RegisterSendCallback(MavlinkSendCallbackFunction callback);
void CallSendCallback(uint8_t *pdata, uint32_t len);


#ifdef HPMSOC_HAS_HPMSDK_MCHTMR
extern ATTR_PLACE_AT_NONCACHEABLE uint8_t mavlink_rx_buff[MAVLINK_RECV_BUFF_SIZE];
extern ATTR_PLACE_AT_NONCACHEABLE uint8_t mavlink_tx_buff[MAVLINK_SEND_BUFF_SIZE];
#else
extern uint8_t mavlink_rx_buff[MAVLINK_RECV_BUFF_SIZE];
extern uint8_t mavlink_tx_buff[MAVLINK_SEND_BUFF_SIZE];
#endif

void MavlinkRecvCallback(Axis *axis, AxisDw *axis_dw, uint8_t rx_data[], uint32_t len);

#ifdef __cplusplus
}
#endif

#endif // MAVLINK_CALLBACK_H
