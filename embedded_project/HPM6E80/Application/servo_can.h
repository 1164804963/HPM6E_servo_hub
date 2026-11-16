#ifndef SERVO_CAN_H
#define SERVO_CAN_H

#include <stdbool.h>
#include <stdint.h>

#include "hpm_common.h"
#include "version.h"

typedef struct
{
    bool ready;
    uint32_t node_id;            /* 已配置的节点号（请求 ID） */
    uint32_t active_node_id;     /* 当前生效的节点号（请求/应答 ID） */
    uint32_t bitrate_hz;         /* 已配置的波特率，重启后生效 */
    uint32_t active_bitrate_hz;
    hpm_stat_t last_error;
    uint32_t rx_count;           /* CAN_CIA402 寻址命中计数（长度/opcode 不参与） */
    uint32_t tx_count;
    uint32_t tx_error_count;
    uint32_t overflow_count;
    uint32_t busoff_count;
} servo_can_status_t;

hpm_stat_t servo_can_init(uint32_t node_id, uint32_t bitrate_hz);
void servo_can_get_status(servo_can_status_t *status);

#if defined(USE_CANOPEN)
void servo_canopen_timer_start(void);
void servo_canopen_timer_isr(void);
#endif

#if defined(USE_CAN_MAVLINK_HOST)
void servo_can_mavlink_send(uint8_t *pdata, uint32_t len);
#endif

#endif /* SERVO_CAN_H */
