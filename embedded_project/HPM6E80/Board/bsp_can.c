#include "bsp_can.h"

#include "board.h"
#include "hpm_interrupt.h"
#include "hpm_mcan_drv.h"
#include "hpm_mcan_soc.h"

/* HPM6E80 MCAN message RAM lives in AHB SRAM (0xF0200000..). */
static ATTR_PLACE_AT(".ahb_sram") uint32_t s_mcan_msg_buf[MCAN_MSG_BUF_SIZE_IN_WORDS];

static mcan_filter_elem_t s_filters[2];
static volatile uint32_t s_rx_irq_count;
static volatile uint32_t s_overflow_count;
static volatile uint32_t s_busoff_count;
static bool s_inited;

SDK_DECLARE_EXT_ISR_M(BOARD_APP_CAN_IRQn, bsp_can_isr)
void bsp_can_isr(void)
{
    uint32_t flags = mcan_get_interrupt_flags(BOARD_APP_CAN_BASE);

    if ((flags & MCAN_INT_RXFIFO0_NEW_MSG) != 0U)
    {
        s_rx_irq_count++;
    }
    if ((flags & MCAN_INT_RXFIFO0_MSG_LOST) != 0U)
    {
        s_overflow_count++;
    }
    if ((flags & MCAN_INT_BUS_OFF_STATUS) != 0U)
    {
        s_busoff_count++;
    }

    mcan_clear_interrupt_flags(BOARD_APP_CAN_BASE, flags);
}

void bsp_can_stop(void)
{
    if (s_inited)
    {
        intc_m_disable_irq(BOARD_APP_CAN_IRQn);
        mcan_deinit(BOARD_APP_CAN_BASE);
        s_inited = false;
    }
}

bool bsp_can_tx_pending(void)
{
    if (!s_inited)
    {
        return false;
    }
    return mcan_is_transmit_request_pending(BOARD_APP_CAN_BASE, 0U);
}

hpm_stat_t bsp_can_init(uint32_t bitrate_hz, bool internal_loopback)
{
    mcan_config_t can_config;
    mcan_msg_buf_attr_t ram_attr;
    uint32_t src_clk_hz;
    hpm_stat_t status;

    if (s_inited)
    {
        bsp_can_stop();
    }
    s_inited = false;
    s_rx_irq_count = 0U;
    s_overflow_count = 0U;
    s_busoff_count = 0U;

    ram_attr.ram_base = (uint32_t)s_mcan_msg_buf;
    ram_attr.ram_size = sizeof(s_mcan_msg_buf);
    status = mcan_set_msg_buf_attr(BOARD_APP_CAN_BASE, &ram_attr);
    if (status != status_success)
    {
        return status;
    }

    s_filters[0].filter_type = MCAN_FILTER_TYPE_RANGE_FILTER;
    s_filters[0].filter_config = MCAN_FILTER_ELEM_CFG_STORE_IN_RX_FIFO0_IF_MATCH;
    s_filters[0].can_id_type = MCAN_CAN_ID_TYPE_STANDARD;
    s_filters[0].sync_message = 0U;
    s_filters[0].start_id = 0U;
    s_filters[0].end_id = 0x7FFU;

    s_filters[1].filter_type = MCAN_FILTER_TYPE_RANGE_FILTER;
    s_filters[1].filter_config = MCAN_FILTER_ELEM_CFG_STORE_IN_RX_FIFO0_IF_MATCH;
    s_filters[1].can_id_type = MCAN_CAN_ID_TYPE_EXTENDED;
    s_filters[1].sync_message = 0U;
    s_filters[1].start_id = 0U;
    s_filters[1].end_id = 0x1FFFFFFFU;

    mcan_get_default_config(BOARD_APP_CAN_BASE, &can_config);
    can_config.baudrate = bitrate_hz;
    can_config.enable_canfd = false;
    can_config.mode = internal_loopback ? mcan_mode_loopback_internal : mcan_mode_normal;
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

    src_clk_hz = board_init_can_clock(BOARD_APP_CAN_BASE);
    if (src_clk_hz == 0U)
    {
        return status_fail;
    }

    if (!internal_loopback)
    {
        board_init_can(BOARD_APP_CAN_BASE);
        board_can_transceiver_phy_set(BOARD_APP_CAN_BASE, true);
    }

    status = mcan_init(BOARD_APP_CAN_BASE, &can_config, src_clk_hz);
    if (status != status_success)
    {
        return status;
    }

    s_inited = true;
    intc_m_enable_irq_with_priority(BOARD_APP_CAN_IRQn, 5); /* lower than 20kHz current loop (6) */

    return status_success;
}

hpm_stat_t bsp_can_send(uint32_t id, bool extended, const uint8_t *data, uint8_t len)
{
    mcan_tx_frame_t tx;
    uint32_t index = 0U;

    if (!s_inited)
    {
        return status_fail;
    }
    if ((len > BSP_CAN_DATA_MAX) || (extended ? (id > 0x1FFFFFFFU) : (id > 0x7FFU)))
    {
        return status_invalid_argument;
    }
    if ((len > 0U) && (data == NULL))
    {
        return status_invalid_argument;
    }

    if (extended)
    {
        mcan_init_tx_frame_ext(&tx, id, len);
    }
    else
    {
        mcan_init_tx_frame_std(&tx, (uint16_t)id, len);
    }
    for (uint32_t i = 0U; i < len; i++)
    {
        tx.data_8[i] = data[i];
    }

    /* Dedicated TX buffer 0 is non-blocking; a busy slot returns an error. */
    return mcan_transmit_via_txbuf_nonblocking(BOARD_APP_CAN_BASE, index, &tx);
}

hpm_stat_t bsp_can_try_receive(bsp_can_frame_t *frame)
{
    mcan_rx_message_t rx;
    hpm_stat_t status;
    uint8_t len;

    if (!s_inited || (frame == NULL))
    {
        return status_invalid_argument;
    }

    status = mcan_read_rxfifo(BOARD_APP_CAN_BASE, 0U, &rx);
    if (status != status_success)
    {
        return status;
    }

    len = mcan_get_message_size_from_dlc(rx.dlc);
    if (len > BSP_CAN_DATA_MAX)
    {
        return status_invalid_argument;
    }

    frame->extended = (rx.use_ext_id != 0U);
    frame->id = frame->extended ? rx.ext_id : rx.std_id;
    frame->len = len;
    for (uint32_t i = 0U; i < len; i++)
    {
        frame->data[i] = rx.data_8[i];
    }

    return status_success;
}

uint32_t bsp_can_rx_irq_count(void)
{
    return s_rx_irq_count;
}

uint32_t bsp_can_overflow_count(void)
{
    return s_overflow_count;
}

uint32_t bsp_can_busoff_count(void)
{
    return s_busoff_count;
}
