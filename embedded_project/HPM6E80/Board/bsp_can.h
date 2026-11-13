#ifndef BSP_CAN_H
#define BSP_CAN_H

#include <stdbool.h>
#include <stdint.h>

#include "hpm_common.h"

#define BSP_CAN_DATA_MAX (64U)

typedef struct
{
    uint32_t id;
    bool extended;
    bool remote;
    bool canfd;
    bool bitrate_switch;
    uint8_t len;
    uint8_t data[BSP_CAN_DATA_MAX];
} bsp_can_frame_t;

/* J8/MCAN4. 500 kbps and 1 Mbps use the Y01 segment settings.
 * node_id is the CANopen filter node; other protocols only compare it in software. */
hpm_stat_t bsp_can_init(uint32_t node_id, uint32_t bitrate_hz);

/* Classic standard data frame, 0..8 bytes, queued on the TX FIFO. */
hpm_stat_t bsp_can_send(uint32_t id, const uint8_t *data, uint8_t len);

/* Classic frame. extended selects 29-bit ID. remote sends a remote frame. */
hpm_stat_t bsp_can_send_classic(uint32_t id, bool extended, bool remote,
                                const uint8_t *data, uint8_t len);

/* CAN FD data frame, 0..64 bytes. bitrate_switch uses the same bit timing as the nominal phase. */
hpm_stat_t bsp_can_send_fd(uint32_t id, bool extended, bool bitrate_switch,
                           const uint8_t *data, uint8_t len);

/* FIFO0. Implemented by the CAN application. Called in the MCAN RX interrupt. */
void bsp_can_on_rx(const bsp_can_frame_t *frame);

/* FIFO1, used by the MAVLink passthrough. */
void bsp_can_on_rx_fifo1(const bsp_can_frame_t *frame);

uint32_t bsp_can_overflow_count(void);
uint32_t bsp_can_busoff_count(void);

#endif /* BSP_CAN_H */
