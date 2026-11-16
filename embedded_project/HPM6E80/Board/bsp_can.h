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

/* Read-only MCAN error telemetry. Every field is a raw register value or an
 * SDK-decoded field captured at one instant; nothing here feeds the control path. */
typedef struct
{
    uint32_t psr;            /* PSR raw (LEC/DLEC are reset by the hardware on read) */
    uint32_t ecr;            /* ECR raw: TEC/REC/RP/CEL */
    uint32_t tx_fqs;         /* TXFQS raw: TFQF / TFQPI / TFFL */
    uint32_t rx0_s;          /* RXF0S raw: RF0L / F0F / F0GI */
    uint32_t rx1_s;          /* RXF1S raw: RF1L / F1F / F1GI */
    uint32_t ir;             /* IR raw at capture time */
    uint16_t tec;            /* PSR/ECR.TEC 0..255 */
    uint16_t rec;            /* ECR.REC 0..255 */
    uint8_t lec;             /* PSR.LEC: 0=no error,1=stuff,2=form,3=ack,4=bit1,5=bit0,6=crc,7=no change */
    uint8_t dlec;            /* PSR.DLEC (CAN FD data phase; unused in classic CAN) */
    bool bus_off;
    bool error_passive;      /* ECR.RP or PSR.EP */
    bool error_warning;      /* PSR.EW */
    uint32_t rxfifo0_fill;
    uint32_t rxfifo1_fill;
    bool rxfifo0_full;
    bool rxfifo1_full;
    bool txfifo_full;
} bsp_can_error_snapshot_t;

typedef struct
{
    bool inited;
    bool first_error_valid;
    bsp_can_error_snapshot_t first_error;
    bool first_busoff_valid;           /* first_busoff 是否已锁存 */
    bsp_can_error_snapshot_t now;      /* 调用时刻的实时快照 */
    bsp_can_error_snapshot_t first_busoff; /* 首次进入 bus-off 时、清标志前的快照 */
    uint16_t max_tec;                  /* bus-off 前见过的最大 TEC/REC */
    uint16_t max_rec;
} bsp_can_diag_t;

/* J8/MCAN4. 500 kbps and 1 Mbps use the Y01 segment settings.
 * node_id is the CANopen filter node; other protocols only compare it in software. */
hpm_stat_t bsp_can_init(uint32_t node_id, uint32_t bitrate_hz);

/* Classic standard data frame, 0..8 bytes, queued on the TX FIFO. */
hpm_stat_t bsp_can_send(uint32_t id, const uint8_t *data, uint8_t len);

/* Classic frame. extended selects 29-bit ID. remote sends a remote frame. */
hpm_stat_t bsp_can_send_classic(uint32_t id, bool extended, bool remote,
                                const uint8_t *data, uint8_t len);

/* CAN FD data frame, 0..64 bytes. bitrate_switch uses the separately configured data-phase timing. */
hpm_stat_t bsp_can_send_fd(uint32_t id, bool extended, bool bitrate_switch,
                           const uint8_t *data, uint8_t len);

/* FIFO0. Implemented by the CAN application. Called in the MCAN RX interrupt. */
void bsp_can_on_rx(const bsp_can_frame_t *frame);

/* FIFO1, used by the MAVLink passthrough. */
void bsp_can_on_rx_fifo1(const bsp_can_frame_t *frame);

/* Read-only instrument snapshot: current state, first bus-off capture and max
 * TEC/REC seen on error interrupts. Never changes controller state. */
void bsp_can_get_diag(bsp_can_diag_t *diag);

uint32_t bsp_can_overflow_count(void);
uint32_t bsp_can_busoff_count(void);

#endif /* BSP_CAN_H */
