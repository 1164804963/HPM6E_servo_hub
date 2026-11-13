#ifndef TEST_STUBS_H
#define TEST_STUBS_H

#include <stdbool.h>
#include <stdint.h>

typedef struct
{
    uint32_t id;
    bool extended;
    uint8_t len;
    uint8_t data[8];
} stub_frame_t;

extern int stub_init_status;
extern int stub_init_calls;
extern int stub_stop_calls;
extern int stub_tx_busy;
extern bool stub_auto_complete;
extern bool stub_tx_pending_hw;
extern int stub_tx_calls;
extern uint32_t stub_last_init_bitrate;
extern stub_frame_t stub_last_tx;
extern uint16_t stub_last_set_controlword;

extern uint32_t stub_od_value;
extern uint32_t stub_od_abort;
extern int stub_od_read_calls;
extern int stub_od_write_calls;
extern uint32_t stub_od_last_index;
extern uint8_t stub_od_last_subindex;
extern bool stub_od_last_host_entry;

extern int stub_error_set_calls;
extern int stub_error_clear_calls;
extern int stub_app_controlword_calls;
extern uint16_t stub_last_app_controlword;
extern int stub_set_controlword_calls;
extern bool stub_emergency_brake_requested;
extern uint16_t stub_error_code;
extern bool stub_physical_fault;


void stub_reset(void);
void stub_queue_rx(uint32_t id, bool extended, const uint8_t *data, uint8_t len);
void stub_set_tx_complete(void);
void stub_set_init_hook(void (*hook)(void));

#endif
