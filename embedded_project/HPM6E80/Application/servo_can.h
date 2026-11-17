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
    uint32_t active_node_id;     /* 当前生效的节点号（请求 ID） */
    uint32_t bitrate_hz;         /* 已配置的波特率，重启后生效 */
    uint32_t active_bitrate_hz;
    hpm_stat_t last_error;
    uint32_t rx_count;           /* 各总线确认可处理的本地入站请求计数；不代表协议执行成功 */
    uint32_t tx_count;
    uint32_t tx_error_count;
    uint32_t overflow_count;
    uint32_t busoff_count;
    uint32_t reply_id;           /* CAN_CIA402 应答 ID；其他总线为 0 */
    bool split_reply;            /* 1: 请求节点 0..0x3FF，应答 ID = 请求 | 0x400 */
    bool legacy_same_id;         /* 1: 显式 LegacySameId，应答与请求同 ID */
    uint32_t reply_pending;      /* 软件应答队列中待发送帧数 */
    uint32_t reply_drop_count;   /* 队满导致请求未执行、应答未生成的计数 */
    uint32_t reply_highwater;    /* 队列 pending 的历史最大值 */
} servo_can_status_t;

hpm_stat_t servo_can_init(uint32_t node_id, uint32_t bitrate_hz);
void servo_can_get_status(servo_can_status_t *status);
/* 前台应答发送：普通 CAN_CIA402 每圈最多尝试 8 帧，其他总线为空实现。 */
void servo_can_poll(void);

#if defined(USE_CANOPEN)
void servo_canopen_timer_start(void);
void servo_canopen_timer_isr(void);
#endif

#if defined(USE_CAN_MAVLINK_HOST)
void servo_can_mavlink_send(uint8_t *pdata, uint32_t len);
#endif

#endif /* SERVO_CAN_H */
