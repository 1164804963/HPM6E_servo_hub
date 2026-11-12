#include "servo_debug_can.h"

#include "servo_debug_can_policy.h"

#include "board.h"
#include "can_cia402.h"
#include "hpm_interrupt.h"
#include "hpm_mcan_drv.h"
#include "hpm_mcan_soc.h"

#define SERVO_DEBUG_CAN_POLL_BUDGET (8U)
#define SERVO_DEBUG_CAN_REPLY_LEN   (8U)

/* J8 uses MCAN4. Keep its message RAM separate from bsp_can.c (MCAN7). */
static ATTR_PLACE_AT(".ahb_sram") uint32_t s_msg_buf[MCAN_MSG_BUF_SIZE_IN_WORDS];

static mcan_filter_elem_t s_filters[2];
static volatile uint32_t s_rx_irq_count;
static volatile uint32_t s_overflow_count;
static volatile uint32_t s_busoff_count;

static uint8_t s_reply[SERVO_DEBUG_CAN_REPLY_LEN];
static bool s_reply_pending;
static bool s_inited;
static bool s_ready;
static hpm_stat_t s_last_error;
static uint32_t s_rx_count;
static uint32_t s_tx_count;
static uint32_t s_invalid_count;
static uint32_t s_write_rejected_count;
static uint32_t s_abort_count;
static uint32_t s_tx_error_count;
static uint32_t s_last_abort;

SDK_DECLARE_EXT_ISR_M(IRQn_MCAN4, servo_debug_can_isr)
void servo_debug_can_isr(void)
{
    uint32_t flags = mcan_get_interrupt_flags(HPM_MCAN4);

    if ((flags & MCAN_INT_RXFIFO0_NEW_MSG) != 0U) {
        s_rx_irq_count++;
    }
    if ((flags & MCAN_INT_RXFIFO0_MSG_LOST) != 0U) {
        s_overflow_count++;
    }
    if ((flags & MCAN_INT_BUS_OFF_STATUS) != 0U) {
        s_busoff_count++;
    }
    mcan_clear_interrupt_flags(HPM_MCAN4, flags);
}

static void stop_port(void)
{
    if (s_inited) {
        intc_m_disable_irq(IRQn_MCAN4);
        mcan_deinit(HPM_MCAN4);
        s_inited = false;
    }
    s_ready = false;
    s_reply_pending = false;
}

static void send_pending(void)
{
    mcan_tx_frame_t tx;
    hpm_stat_t status;

    if (!s_ready || !s_reply_pending) {
        return;
    }

    mcan_init_tx_frame_std(&tx, SERVO_DEBUG_CAN_NODE_ID, SERVO_DEBUG_CAN_REPLY_LEN);
    for (uint32_t i = 0U; i < SERVO_DEBUG_CAN_REPLY_LEN; i++) {
        tx.data_8[i] = s_reply[i];
    }

    status = mcan_transmit_via_txbuf_nonblocking(HPM_MCAN4, 0U, &tx);
    if (status == status_success) {
        s_reply_pending = false;
        s_tx_count++;
        return;
    }
    if ((status == status_fail) || (status == status_mcan_txfifo_full) || (status == status_timeout)) {
        return; /* keep the reply for the next poll; not a TX error */
    }

    s_reply_pending = false;
    s_tx_error_count++;
    s_last_error = status;
}

hpm_stat_t servo_debug_can_init(void)
{
    mcan_config_t can_config;
    mcan_msg_buf_attr_t ram_attr;
    uint32_t src_clk_hz;
    hpm_stat_t status;

    stop_port();
    s_rx_count = 0U;
    s_tx_count = 0U;
    s_invalid_count = 0U;
    s_write_rejected_count = 0U;
    s_abort_count = 0U;
    s_tx_error_count = 0U;
    s_last_abort = 0U;
    s_rx_irq_count = 0U;
    s_overflow_count = 0U;
    s_busoff_count = 0U;

    ram_attr.ram_base = (uint32_t)s_msg_buf;
    ram_attr.ram_size = sizeof(s_msg_buf);
    status = mcan_set_msg_buf_attr(HPM_MCAN4, &ram_attr);
    if (status != status_success) {
        s_last_error = status;
        return status;
    }

    s_filters[0].filter_type = MCAN_FILTER_TYPE_RANGE_FILTER;
    s_filters[0].filter_config = MCAN_FILTER_ELEM_CFG_STORE_IN_RX_FIFO0_IF_MATCH;
    s_filters[0].can_id_type = MCAN_CAN_ID_TYPE_STANDARD;
    s_filters[0].sync_message = 0U;
    s_filters[0].start_id = SERVO_DEBUG_CAN_NODE_ID;
    s_filters[0].end_id = SERVO_DEBUG_CAN_NODE_ID;

    s_filters[1].filter_type = MCAN_FILTER_TYPE_RANGE_FILTER;
    s_filters[1].filter_config = MCAN_FILTER_ELEM_CFG_STORE_IN_RX_FIFO0_IF_MATCH;
    s_filters[1].can_id_type = MCAN_CAN_ID_TYPE_EXTENDED;
    s_filters[1].sync_message = 0U;
    s_filters[1].start_id = SERVO_DEBUG_CAN_NODE_ID;
    s_filters[1].end_id = SERVO_DEBUG_CAN_NODE_ID;

    mcan_get_default_config(HPM_MCAN4, &can_config);
    can_config.baudrate = SERVO_DEBUG_CAN_BITRATE_HZ;
    can_config.enable_canfd = false;
    can_config.mode = mcan_mode_normal;
    can_config.all_filters_config.std_id_filter_list.filter_elem_list = &s_filters[0];
    can_config.all_filters_config.std_id_filter_list.mcan_filter_elem_count = 1U;
    can_config.all_filters_config.ext_id_filter_list.filter_elem_list = &s_filters[1];
    can_config.all_filters_config.ext_id_filter_list.mcan_filter_elem_count = 1U;
    can_config.all_filters_config.global_filter_config.accept_non_matching_std_frame_option =
        MCAN_ACCEPT_NON_MATCHING_FRAME_OPTION_REJECT;
    can_config.all_filters_config.global_filter_config.accept_non_matching_ext_frame_option =
        MCAN_ACCEPT_NON_MATCHING_FRAME_OPTION_REJECT;
    can_config.all_filters_config.global_filter_config.reject_remote_std_frame = true;
    can_config.all_filters_config.global_filter_config.reject_remote_ext_frame = true;
    can_config.interrupt_mask = MCAN_EVENT_RECEIVE | MCAN_INT_RXFIFO0_MSG_LOST | MCAN_EVENT_ERROR;
    can_config.txbuf_trans_interrupt_mask = 0U;

    src_clk_hz = board_init_can_clock(HPM_MCAN4);
    if (src_clk_hz == 0U) {
        s_last_error = status_fail;
        return status_fail;
    }

    board_init_can(HPM_MCAN4);
    board_can_transceiver_phy_set(HPM_MCAN4, true);

    status = mcan_init(HPM_MCAN4, &can_config, src_clk_hz);
    s_last_error = status;
    if (status != status_success) {
        return status;
    }

    s_inited = true;
    s_ready = true;
    intc_m_enable_irq_with_priority(IRQn_MCAN4, 5);
    return status_success;
}

void servo_debug_can_poll(void)
{
    uint8_t budget = SERVO_DEBUG_CAN_POLL_BUDGET;

    if (!s_ready) {
        return;
    }

    if (s_reply_pending) {
        send_pending();
        if (s_reply_pending) {
            return;
        }
    }

    while (budget-- > 0U) {
        mcan_rx_message_t rx;
        uint8_t len;
        bool extended;
        uint32_t id;
        uint8_t reply[SERVO_DEBUG_CAN_REPLY_LEN];
        uint32_t abort_code = 0U;
        can_cia402_result_t result;

        if (mcan_read_rxfifo(HPM_MCAN4, 0U, &rx) != status_success) {
            break;
        }

        len = mcan_get_message_size_from_dlc(rx.dlc);
        extended = (rx.use_ext_id != 0U);
        id = extended ? rx.ext_id : rx.std_id;

        /* Reject extensions/wrong IDs/DLCs before touching codec or OD. */
        if (extended || (id != SERVO_DEBUG_CAN_NODE_ID) ||
            ((len != 5U) && (len != 6U) && (len != 8U))) {
            s_invalid_count++;
            continue;
        }

        s_rx_count++;
        if (rx.data_8[0] != 0U) {
            s_write_rejected_count++;
            continue; /* op != 0: no callback, no reply */
        }

        if (!servo_debug_can_is_read_only_request(extended, id, len, rx.data_8)) {
            s_invalid_count++;
            continue;
        }

        result = can_cia402_handle_request(rx.data_8, len, reply, &abort_code);
        if (result == CAN_CIA402_OK) {
            for (uint32_t i = 0U; i < SERVO_DEBUG_CAN_REPLY_LEN; i++) {
                s_reply[i] = reply[i];
            }
            s_reply_pending = true;
            send_pending();
            if (s_reply_pending) {
                break; /* TX busy: next poll sends this reply before any new RX */
            }
        } else if (result == CAN_CIA402_ABORT) {
            s_abort_count++;
            s_last_abort = abort_code;
        } else {
            s_invalid_count++;
        }
    }
}

void servo_debug_can_get_status(servo_debug_can_status_t *status)
{
    if (status == NULL) {
        return;
    }

    status->ready = s_ready;
    status->node_id = SERVO_DEBUG_CAN_NODE_ID;
    status->bitrate_hz = SERVO_DEBUG_CAN_BITRATE_HZ;
    status->last_error = s_last_error;
    status->rx_count = s_rx_count;
    status->tx_count = s_tx_count;
    status->invalid_count = s_invalid_count;
    status->write_rejected_count = s_write_rejected_count;
    status->abort_count = s_abort_count;
    status->tx_error_count = s_tx_error_count;
    status->last_abort = s_last_abort;
    status->overflow_count = s_overflow_count;
    status->busoff_count = s_busoff_count;
}
