#ifndef SERVO_CAN_H
#define SERVO_CAN_H

#include <stdbool.h>
#include <stdint.h>

#include "hpm_common.h"

typedef struct
{
    bool ready;
    uint16_t node_id;
    uint32_t bitrate_hz;
    uint16_t requested_node_id;
    uint32_t requested_bitrate_hz;
    hpm_stat_t last_error;
    uint32_t rx_count;
    uint32_t tx_count;
    uint32_t invalid_count;
    uint32_t abort_count;
    uint32_t tx_error_count;
    uint32_t last_abort;
    uint32_t overflow_count;
    uint32_t busoff_count;
} servo_can_status_t;

hpm_stat_t servo_can_init(uint32_t node_id, uint32_t bitrate_hz);
bool servo_can_is_ready(void);
hpm_stat_t servo_can_request_node_id(uint32_t node_id);
hpm_stat_t servo_can_request_bitrate(uint32_t bitrate_hz);
void servo_can_poll(void);
hpm_stat_t servo_can_reset(void);

void servo_can_get_status(servo_can_status_t *status);
uint16_t servo_can_applied_node_id(void);
uint32_t servo_can_applied_bitrate(void);
uint16_t servo_can_requested_node_id(void);
uint32_t servo_can_requested_bitrate(void);
uint32_t servo_can_rx_count(void);

#endif /* SERVO_CAN_H */
