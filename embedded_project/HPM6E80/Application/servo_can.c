#include "servo_can.h"

#include "bsp_api.h"
#include "bsp_can.h"
#include "can_cia402.h"
#include "hpm_mcan_drv.h"
#include "Cia402_ObjectDictionary_Variable.h"
#include "cia402_fsm.h"
#include "data_param.h"

#define SERVO_CAN_DEFAULT_NODE_ID (0x15U)
#define SERVO_CAN_DEFAULT_BITRATE (1000000U)
#define SERVO_CAN_POLL_BUDGET     (8U)

static bool s_ready;
static uint16_t s_node_id = SERVO_CAN_DEFAULT_NODE_ID;
static uint32_t s_bitrate_hz = SERVO_CAN_DEFAULT_BITRATE;
static volatile uint16_t s_requested_node_id = SERVO_CAN_DEFAULT_NODE_ID;
static volatile uint32_t s_requested_bitrate_hz = SERVO_CAN_DEFAULT_BITRATE;
static hpm_stat_t s_last_error = status_success;

static bool s_reply_pending;
static uint8_t s_reply[8];
static uint32_t s_reply_id;

static uint32_t s_rx_count;
static uint32_t s_tx_count;
static uint32_t s_invalid_count;
static uint32_t s_abort_count;
static uint32_t s_tx_error_count;
static uint32_t s_last_abort;

static bool valid_node_id(uint32_t node_id)
{
    return node_id <= 0x7FFU;
}

static bool valid_bitrate(uint32_t bitrate_hz)
{
    return (bitrate_hz == 500000U) || (bitrate_hz == 1000000U);
}

static void send_pending(void)
{
    hpm_stat_t status = bsp_can_send(s_reply_id, false, s_reply, 8U);

    if (status == status_success)
    {
        s_reply_pending = false;
        s_tx_count++;
        return;
    }
    if ((status == status_fail) || (status == status_mcan_txfifo_full) || (status == status_timeout))
    {
        return; /* keep the reply for the next poll */
    }

    s_reply_pending = false;
    s_tx_error_count++;
    s_last_error = status;
}

static hpm_stat_t apply_config(bool force)
{
    uint16_t node = s_requested_node_id;
    uint32_t baudrate = s_requested_bitrate_hz;
    hpm_stat_t status;

    if (!force && (node == s_node_id) && (baudrate == s_bitrate_hz) && s_ready)
    {
        return status_success;
    }
    if (!force && (s_reply_pending || bsp_can_tx_pending()))
    {
        return status_success; /* hardware still owns the previous reply */
    }

    /* Reinit is only allowed after the normal CiA402 disable path; Fault is not cleared. */
    Cia402FsmRequestSafeStop();
    (void)set_app_Controlword((uint16_t)APP_CTRL_DISABLE);
    s_reply_pending = false;
    bsp_can_stop();

    status = bsp_can_init(baudrate, false);
    s_last_error = status;
    if (status == status_success)
    {
        s_node_id = node;
        s_bitrate_hz = baudrate;
        s_ready = true;
    }
    else
    {
        s_ready = false;
    }
    return status;
}

bool servo_can_is_ready(void)
{
    return s_ready;
}

hpm_stat_t servo_can_init(uint32_t node_id, uint32_t bitrate_hz)
{
    if (!valid_node_id(node_id) || !valid_bitrate(bitrate_hz))
    {
        s_last_error = status_invalid_argument;
        return status_invalid_argument;
    }

    s_requested_node_id = node_id;
    s_requested_bitrate_hz = bitrate_hz;
    s_rx_count = 0U;
    s_tx_count = 0U;
    s_invalid_count = 0U;
    s_abort_count = 0U;
    s_tx_error_count = 0U;
    s_last_abort = 0U;
    s_reply_pending = false;

    return apply_config(true);
}

hpm_stat_t servo_can_request_node_id(uint32_t node_id)
{
    if (!valid_node_id(node_id))
    {
        s_last_error = status_invalid_argument;
        return status_invalid_argument;
    }
    s_requested_node_id = node_id;
    return status_success;
}

hpm_stat_t servo_can_request_bitrate(uint32_t bitrate_hz)
{
    if (!valid_bitrate(bitrate_hz))
    {
        s_last_error = status_invalid_argument;
        return status_invalid_argument;
    }
    s_requested_bitrate_hz = bitrate_hz;
    return status_success;
}

void servo_can_poll(void)
{
    uint8_t budget = SERVO_CAN_POLL_BUDGET;

    if (!s_ready)
    {
        return;
    }

    if (s_reply_pending)
    {
        send_pending();
        if (s_reply_pending)
        {
            return;
        }
    }

    if ((s_requested_node_id != s_node_id) || (s_requested_bitrate_hz != s_bitrate_hz))
    {
        (void)apply_config(false);
        if (!s_ready)
        {
            return;
        }
    }

    while ((budget > 0U) && !s_reply_pending)
    {
        bsp_can_frame_t rx;
        uint8_t reply[8];
        uint32_t abort_code = 0U;
        can_cia402_result_t result;

        budget--;
        if (bsp_can_try_receive(&rx) != status_success)
        {
            break;
        }
        if (rx.extended || (rx.id != (uint32_t)s_node_id))
        {
            s_invalid_count++;
            continue;
        }

        s_rx_count++;
        result = can_cia402_handle_request(rx.data, rx.len, reply, &abort_code);
        if (result == CAN_CIA402_OK)
        {
            for (uint32_t i = 0U; i < 8U; i++)
            {
                s_reply[i] = reply[i];
            }
            s_reply_id = (uint32_t)s_node_id;
            s_reply_pending = true;
            send_pending();
        }
        else if (result == CAN_CIA402_ABORT)
        {
            s_abort_count++;
            s_last_abort = abort_code;
        }
        else
        {
            s_invalid_count++;
        }
    }
}

hpm_stat_t servo_can_reset(void)
{
    return apply_config(true);
}

void servo_can_get_status(servo_can_status_t *status)
{
    if (status == 0)
    {
        return;
    }

    status->ready = s_ready;
    status->node_id = s_node_id;
    status->bitrate_hz = s_bitrate_hz;
    status->requested_node_id = s_requested_node_id;
    status->requested_bitrate_hz = s_requested_bitrate_hz;
    status->last_error = s_last_error;
    status->rx_count = s_rx_count;
    status->tx_count = s_tx_count;
    status->invalid_count = s_invalid_count;
    status->abort_count = s_abort_count;
    status->tx_error_count = s_tx_error_count;
    status->last_abort = s_last_abort;
    status->overflow_count = bsp_can_overflow_count();
    status->busoff_count = bsp_can_busoff_count();
}

uint16_t servo_can_requested_node_id(void)
{
    return s_requested_node_id;
}

uint32_t servo_can_requested_bitrate(void)
{
    return s_requested_bitrate_hz;
}

uint16_t servo_can_applied_node_id(void)
{
    return s_node_id;
}

uint32_t servo_can_applied_bitrate(void)
{
    return s_bitrate_hz;
}

uint32_t servo_can_rx_count(void)
{
    return s_rx_count;
}
