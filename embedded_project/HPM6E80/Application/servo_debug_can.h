#ifndef SERVO_DEBUG_CAN_H
#define SERVO_DEBUG_CAN_H

#include <stdbool.h>
#include <stdint.h>

#include "hpm_common.h"

typedef struct
{
    bool ready;
    uint16_t node_id;
    uint32_t bitrate_hz;
    hpm_stat_t last_error;
    uint32_t rx_count;
    uint32_t tx_count;
    uint32_t invalid_count;
    uint32_t write_count;
    uint32_t write_rejected_count;
    uint32_t abort_count;
    uint32_t tx_error_count;
    uint32_t last_abort;
    uint32_t overflow_count;
    uint32_t busoff_count;
} servo_debug_can_status_t;

hpm_stat_t servo_debug_can_init(void);
bool servo_debug_can_is_ready(void);
void servo_debug_can_poll(void);
void servo_debug_can_get_status(servo_debug_can_status_t *status);

#endif /* SERVO_DEBUG_CAN_H */
