#ifndef SERVO_CAN_H
#define SERVO_CAN_H

#include <stdbool.h>
#include <stdint.h>

#include "hpm_common.h"
#include "version.h"

typedef struct
{
    bool ready;
    uint32_t node_id;
    uint32_t bitrate_hz;
    uint32_t active_bitrate_hz;
    hpm_stat_t last_error;
    uint32_t rx_count;
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
