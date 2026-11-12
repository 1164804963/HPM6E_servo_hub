#ifndef BSP_CAN_H
#define BSP_CAN_H

#include <stdbool.h>
#include <stdint.h>

#include "hpm_common.h"

#define BSP_CAN_DATA_MAX (8U)

typedef struct
{
    uint32_t id;
    bool extended;
    uint8_t len;
    uint8_t data[BSP_CAN_DATA_MAX];
} bsp_can_frame_t;

/* MCAN7 classic CAN. internal_loopback=true does not touch J9 pins/transceiver. */
hpm_stat_t bsp_can_init(uint32_t bitrate_hz, bool internal_loopback);
void bsp_can_stop(void);
bool bsp_can_tx_pending(void);

/* Non-blocking classic CAN transmit; busy propagates the SDK status (status_fail/timeout). */
hpm_stat_t bsp_can_send(uint32_t id, bool extended, const uint8_t *data, uint8_t len);

/* Non-blocking RX FIFO0 read; status_mcan_rxfifo_empty when no frame is ready. */
hpm_stat_t bsp_can_try_receive(bsp_can_frame_t *frame);

uint32_t bsp_can_rx_irq_count(void);
uint32_t bsp_can_overflow_count(void);
uint32_t bsp_can_busoff_count(void);

#endif /* BSP_CAN_H */
