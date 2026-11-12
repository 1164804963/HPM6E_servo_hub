#include "bsp_can.h"
#include "test_stubs.h"

#include <string.h>

#define STUB_RX_MAX (32)

static stub_frame_t s_rx[STUB_RX_MAX];
static int s_rx_head;
static int s_rx_tail;
static void (*s_init_hook)(void);

int stub_init_status = status_success;
int stub_init_calls;
int stub_stop_calls;
int stub_tx_busy;
bool stub_auto_complete;
bool stub_tx_pending_hw;
int stub_tx_calls;
uint32_t stub_last_init_bitrate;
stub_frame_t stub_last_tx;

void stub_reset(void)
{
    s_rx_head = 0;
    s_rx_tail = 0;
    s_init_hook = 0;
    stub_init_status = status_success;
    stub_init_calls = 0;
    stub_stop_calls = 0;
    stub_tx_busy = 0;
    stub_auto_complete = true;
    stub_tx_pending_hw = false;
    stub_tx_calls = 0;
    stub_last_init_bitrate = 0U;
    memset(&stub_last_tx, 0, sizeof(stub_last_tx));
}

void stub_queue_rx(uint32_t id, bool extended, const uint8_t *data, uint8_t len)
{
    if ((s_rx_tail - s_rx_head) >= STUB_RX_MAX)
    {
        return;
    }
    stub_frame_t *f = &s_rx[s_rx_tail % STUB_RX_MAX];
    f->id = id;
    f->extended = extended;
    f->len = len;
    memset(f->data, 0, sizeof(f->data));
    if (data != 0)
    {
        memcpy(f->data, data, len);
    }
    s_rx_tail++;
}

void stub_set_tx_complete(void)
{
    stub_tx_pending_hw = false;
}

void stub_set_init_hook(void (*hook)(void))
{
    s_init_hook = hook;
}

hpm_stat_t bsp_can_init(uint32_t bitrate_hz, bool internal_loopback)
{
    (void)internal_loopback;
    stub_init_calls++;
    stub_last_init_bitrate = bitrate_hz;
    stub_tx_pending_hw = false;
    if (s_init_hook != 0)
    {
        s_init_hook();
    }
    return (hpm_stat_t)stub_init_status;
}

void bsp_can_stop(void)
{
    stub_stop_calls++;
    stub_tx_pending_hw = false;
}

bool bsp_can_tx_pending(void)
{
    return stub_tx_pending_hw;
}

hpm_stat_t bsp_can_send(uint32_t id, bool extended, const uint8_t *data, uint8_t len)
{
    stub_tx_calls++;
    if ((stub_tx_busy != 0) || ((!stub_auto_complete) && stub_tx_pending_hw))
    {
        return status_fail;
    }

    stub_last_tx.id = id;
    stub_last_tx.extended = extended;
    stub_last_tx.len = len;
    memset(stub_last_tx.data, 0, sizeof(stub_last_tx.data));
    if ((data != 0) && (len <= sizeof(stub_last_tx.data)))
    {
        memcpy(stub_last_tx.data, data, len);
    }
    if (!stub_auto_complete)
    {
        stub_tx_pending_hw = true;
    }
    return status_success;
}

hpm_stat_t bsp_can_try_receive(bsp_can_frame_t *frame)
{
    if (s_rx_head >= s_rx_tail)
    {
        return status_fail;
    }
    stub_frame_t *f = &s_rx[s_rx_head % STUB_RX_MAX];
    s_rx_head++;
    frame->id = f->id;
    frame->extended = f->extended;
    frame->len = f->len;
    memcpy(frame->data, f->data, sizeof(frame->data));
    return status_success;
}

uint32_t bsp_can_rx_irq_count(void)
{
    return 0;
}

uint32_t bsp_can_overflow_count(void)
{
    return 0;
}

uint32_t bsp_can_busoff_count(void)
{
    return 0;
}
