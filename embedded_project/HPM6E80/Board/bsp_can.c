#include "bsp_can.h"

#include <string.h>

#include "board.h"
#include "hpm_interrupt.h"
#include "hpm_mcan_drv.h"
#include "hpm_mcan_soc.h"
#include "version.h"

#ifndef SERVO_CANFD_DATA_BITRATE
#define SERVO_CANFD_DATA_BITRATE 0U /* 0 keeps the original nominal/data timing. */
#endif

/* HPM6E80 MCAN message RAM lives in AHB SRAM (0xF0200000..). */
static ATTR_PLACE_AT(".ahb_sram") uint32_t s_mcan_msg_buf[MCAN_MSG_BUF_SIZE_IN_WORDS];

static mcan_filter_elem_t s_std_filters[2];
#if IS_USE_CAN_PASSTHROUGH
static mcan_filter_elem_t s_ext_filters[3];
#endif
static volatile uint32_t s_overflow_count;
static volatile uint32_t s_busoff_count;
static bool s_inited;
static uint32_t s_node_id;

/* Root-cause instrumentation: one latch of the first bus-off and the max error
 * counters seen on error interrupts. Cleared only by an explicit bsp_can_init(). */
static volatile bool s_first_error_valid;
static bsp_can_error_snapshot_t s_first_error;
static volatile bool s_first_busoff_valid;
static bsp_can_error_snapshot_t s_first_busoff;
static volatile uint16_t s_max_tec;
static volatile uint16_t s_max_rec;

#if IS_USE_CAN_PASSTHROUGH
#define CANID_FLAG_GLOBAL   (2U)
#define CANID_FLAG_SYSTEM   (1U)
#define CANID_FLAG_SHIFT    (11U)
#define CANID_SYSID_SHIFT   (21U)
#define CANID_COMPID_SHIFT  (13U)
#define CANID_FLAG_MASK     (0x3U << CANID_FLAG_SHIFT)
#define CANID_SYSID_MASK    (0x1FU << CANID_SYSID_SHIFT)
#define CANID_COMPID_MASK   (0xFFU << CANID_COMPID_SHIFT)
#define CANID_SYSID_DEFAULT (0x1U)
static uint32_t s_mav_sys_id = CANID_SYSID_DEFAULT;
static uint32_t s_mav_comp_id = 0x15U;
#endif

static bool timing_for_bitrate(uint32_t bitrate_hz, mcan_bit_timing_param_t *timing)
{
    /* Same 80 MHz segments as Y01 bsp_fdcan.c. The driver writes N-1 into NBTP/DBTP. */
    if (bitrate_hz == 1000000U)
    {
        timing->prescaler = 4U;
        timing->num_seg1 = 14U;
        timing->num_seg2 = 5U;
        timing->num_sjw = 2U;
    }
    else if (bitrate_hz == 500000U)
    {
        timing->prescaler = 10U;
        timing->num_seg1 = 13U;
        timing->num_seg2 = 2U;
        timing->num_sjw = 2U;
    }
    else
    {
        return false;
    }
    timing->enable_tdc = false;
    return true;
}

/* Data timing is independent of the arbitration rate. Values are TQ counts. */
static mcan_bit_timing_param_t data_timing_for(const mcan_bit_timing_param_t *nominal)
{
    mcan_bit_timing_param_t data = *nominal;
#if SERVO_CANFD_DATA_BITRATE == 1000000
    (void)timing_for_bitrate(1000000U, &data);
#elif SERVO_CANFD_DATA_BITRATE == 2000000
    /* SDK 80 MHz CAN FD profile: 80 MHz / (2 * (1 + 14 + 5)) = 2 Mbps. */
    data.prescaler = 2U;
    data.num_seg1 = 14U;
    data.num_seg2 = 5U;
    data.num_sjw = 2U;
    data.enable_tdc = true;
#elif SERVO_CANFD_DATA_BITRATE != 0
#error Unsupported CAN FD data bitrate
#endif
    return data;
}

static uint8_t dlc_from_bytes(uint8_t len)
{
    static const uint8_t limit[16] = {
        0U, 1U, 2U, 3U, 4U, 5U, 6U, 7U, 8U, 12U, 16U, 20U, 24U, 32U, 48U, 64U
    };
    uint8_t dlc;

    for (dlc = 0U; dlc < 16U; dlc++)
    {
        if (len <= limit[dlc])
        {
            return dlc;
        }
    }
    return 15U;
}

static hpm_stat_t read_fifo(uint32_t fifo, bsp_can_frame_t *frame)
{
    mcan_rx_message_t rx;
    hpm_stat_t status;
    uint8_t len;

    status = mcan_read_rxfifo(BOARD_APP_CAN_BASE, fifo, &rx);
    if (status != status_success)
    {
        return status;
    }

    len = mcan_get_message_size_from_dlc(rx.dlc);
    frame->extended = (rx.use_ext_id != 0U);
    frame->remote = (rx.rtr != 0U);
    frame->canfd = (rx.canfd_frame != 0U);
    frame->bitrate_switch = (rx.bitrate_switch != 0U);
    frame->id = frame->extended ? rx.ext_id : rx.std_id;
    frame->len = len;
    if (len > BSP_CAN_DATA_MAX)
    {
        len = BSP_CAN_DATA_MAX;
    }
    for (uint32_t i = 0U; i < len; i++)
    {
        frame->data[i] = rx.data_8[i];
    }
    return status_success;
}

static hpm_stat_t transmit(mcan_tx_frame_t *tx)
{
    uint32_t fifo_index;

    return mcan_transmit_via_txfifo_nonblocking(BOARD_APP_CAN_BASE, tx, &fifo_index);
}

/*
 * Read-only MCAN snapshot. PSR is read once and decoded from that value: reading
 * PSR resets LEC/DLEC to "no change" in the hardware, so a second read would lose
 * the error code we are trying to record.
 */
static void can_capture_snapshot(bsp_can_error_snapshot_t *s)
{
    uint32_t psr = BOARD_APP_CAN_BASE->PSR;
    uint32_t ecr = BOARD_APP_CAN_BASE->ECR;
    mcan_protocol_status_t ps;

    s->psr = psr;
    s->ecr = ecr;
    s->tx_fqs = BOARD_APP_CAN_BASE->TXFQS;
    s->rx0_s = BOARD_APP_CAN_BASE->RXF0S;
    s->rx1_s = BOARD_APP_CAN_BASE->RXF1S;
    s->ir = mcan_get_interrupt_flags(BOARD_APP_CAN_BASE);

    s->lec = (uint8_t)MCAN_PSR_LEC_GET(psr);
    s->dlec = (uint8_t)MCAN_PSR_DLEC_GET(psr);
    s->tec = (uint16_t)MCAN_ECR_TEC_GET(ecr);
    s->rec = (uint16_t)MCAN_ECR_REC_GET(ecr);
    s->error_passive = (MCAN_ECR_RP_GET(ecr) != 0U);

    if (mcan_parse_protocol_status(psr, &ps) == status_success)
    {
        s->bus_off = ps.in_bus_off_state;
        s->error_passive = s->error_passive || ps.in_error_passive_state;
        s->error_warning = ps.in_warning_state;
    }

    s->rxfifo0_fill = mcan_get_rxfifo_fill_level(BOARD_APP_CAN_BASE, 0U);
    s->rxfifo1_fill = mcan_get_rxfifo_fill_level(BOARD_APP_CAN_BASE, 1U);
    s->rxfifo0_full = mcan_is_rxfifo_full(BOARD_APP_CAN_BASE, 0U);
    s->rxfifo1_full = mcan_is_rxfifo_full(BOARD_APP_CAN_BASE, 1U);
    s->txfifo_full = mcan_is_txfifo_full(BOARD_APP_CAN_BASE);
}

SDK_DECLARE_EXT_ISR_M(BOARD_APP_CAN_IRQn, bsp_can_isr)
void bsp_can_isr(void)
{
    uint32_t flags = mcan_get_interrupt_flags(BOARD_APP_CAN_BASE);

    if ((flags & MCAN_EVENT_ERROR) != 0U)
    {
        /* Bounded sampling: only when an error interrupt actually fires, never per
         * received frame. ECR is read once and used for both counters. */
        uint32_t ecr = BOARD_APP_CAN_BASE->ECR;
        uint16_t tec = (uint16_t)MCAN_ECR_TEC_GET(ecr);
        uint16_t rec = (uint16_t)MCAN_ECR_REC_GET(ecr);

        if (!s_first_error_valid && ((tec != 0U) || (rec != 0U)))
        {
            can_capture_snapshot(&s_first_error);
            s_first_error_valid = true;
        }
        if (tec > s_max_tec)
        {
            s_max_tec = tec;
        }
        if (rec > s_max_rec)
        {
            s_max_rec = rec;
        }
    }
    if ((flags & MCAN_INT_BUS_OFF_STATUS) != 0U)
    {
        bsp_can_error_snapshot_t snapshot = {0};
        can_capture_snapshot(&snapshot);
        /* BO interrupt reports both entry and recovery. Count only entry. */
        if (snapshot.bus_off)
        {
            if (!s_first_busoff_valid)
            {
                /* Capture before draining RX FIFO or clearing interrupt flags. */
                s_first_busoff = snapshot;
                s_first_busoff_valid = true;
            }
            s_busoff_count++;
        }
    }

    if ((flags & MCAN_INT_RXFIFO0_NEW_MSG) != 0U)
    {
        bsp_can_frame_t frame;

        while (read_fifo(0U, &frame) == status_success)
        {
            bsp_can_on_rx(&frame);
        }
    }
#if IS_USE_CAN_PASSTHROUGH
    if ((flags & MCAN_INT_RXFIFO1_NEW_MSG) != 0U)
    {
        bsp_can_frame_t frame;

        while (read_fifo(1U, &frame) == status_success)
        {
            bsp_can_on_rx_fifo1(&frame);
        }
    }
#endif
    if ((flags & MCAN_INT_RXFIFO0_MSG_LOST) != 0U)
    {
        s_overflow_count++;
    }

    mcan_clear_interrupt_flags(BOARD_APP_CAN_BASE, flags);
}

static void setup_filters(mcan_config_t *can_config)
{
#if defined(USE_CANOPEN)
    /* NMT 0x000 and SYNC 0x080, plus any function code addressed to this node. */
    s_std_filters[0].filter_type = MCAN_FILTER_TYPE_SPECIFIED_ID_FILTER;
    s_std_filters[0].filter_config = MCAN_FILTER_ELEM_CFG_STORE_IN_RX_FIFO0_IF_MATCH;
    s_std_filters[0].can_id_type = MCAN_CAN_ID_TYPE_STANDARD;
    s_std_filters[0].sync_message = 0U;
    s_std_filters[0].id1 = 0x000U;
    s_std_filters[0].id2 = 0x080U;

    s_std_filters[1].filter_type = MCAN_FILTER_TYPE_CLASSIC_FILTER;
    s_std_filters[1].filter_config = MCAN_FILTER_ELEM_CFG_STORE_IN_RX_FIFO0_IF_MATCH;
    s_std_filters[1].can_id_type = MCAN_CAN_ID_TYPE_STANDARD;
    s_std_filters[1].sync_message = 0U;
    s_std_filters[1].filter_id = s_node_id;
    s_std_filters[1].filter_mask = 0x7FU;
    can_config->all_filters_config.std_id_filter_list.mcan_filter_elem_count = 2U;
#else
    /* Accept every standard ID. The application compares the node ID, as Y01 does. */
    s_std_filters[0].filter_type = MCAN_FILTER_TYPE_RANGE_FILTER;
    s_std_filters[0].filter_config = MCAN_FILTER_ELEM_CFG_STORE_IN_RX_FIFO0_IF_MATCH;
    s_std_filters[0].can_id_type = MCAN_CAN_ID_TYPE_STANDARD;
    s_std_filters[0].sync_message = 0U;
    s_std_filters[0].start_id = 0U;
    s_std_filters[0].end_id = 0x7FFU;
    can_config->all_filters_config.std_id_filter_list.mcan_filter_elem_count = 1U;
#endif
    can_config->all_filters_config.std_id_filter_list.filter_elem_list = s_std_filters;

#if IS_USE_CAN_PASSTHROUGH
    for (uint32_t i = 0U; i < 3U; i++)
    {
        s_ext_filters[i].filter_type = MCAN_FILTER_TYPE_CLASSIC_FILTER;
        s_ext_filters[i].filter_config = MCAN_FILTER_ELEM_CFG_STORE_IN_RX_FIFO1_IF_MATCH;
        s_ext_filters[i].can_id_type = MCAN_CAN_ID_TYPE_EXTENDED;
        s_ext_filters[i].sync_message = 0U;
    }
    s_ext_filters[0].filter_id = (CANID_FLAG_GLOBAL << CANID_FLAG_SHIFT);
    s_ext_filters[0].filter_mask = CANID_FLAG_MASK;
    s_ext_filters[1].filter_id = (CANID_FLAG_SYSTEM << CANID_FLAG_SHIFT) |
                                 (s_mav_sys_id << CANID_SYSID_SHIFT);
    s_ext_filters[1].filter_mask = CANID_FLAG_MASK | CANID_SYSID_MASK;
    s_ext_filters[2].filter_id = (s_mav_comp_id << CANID_COMPID_SHIFT) |
                                 (s_mav_sys_id << CANID_SYSID_SHIFT);
    s_ext_filters[2].filter_mask = CANID_COMPID_MASK | CANID_SYSID_MASK;
    can_config->all_filters_config.ext_id_filter_list.filter_elem_list = s_ext_filters;
    can_config->all_filters_config.ext_id_filter_list.mcan_filter_elem_count = 3U;
#else
    can_config->all_filters_config.ext_id_filter_list.filter_elem_list = NULL;
    can_config->all_filters_config.ext_id_filter_list.mcan_filter_elem_count = 0U;
#endif
}

hpm_stat_t bsp_can_init(uint32_t node_id, uint32_t bitrate_hz)
{
    mcan_config_t can_config;
    mcan_msg_buf_attr_t ram_attr;
    mcan_bit_timing_param_t timing;
    uint32_t src_clk_hz;
    hpm_stat_t status;

#if defined(USE_CANOPEN)
    if (node_id > 0x7FU)
    {
        return status_fail;
    }
#endif
    if (!timing_for_bitrate(bitrate_hz, &timing))
    {
        return status_fail;
    }

    s_inited = false;
    s_node_id = node_id;
#if IS_USE_CAN_PASSTHROUGH
    s_mav_comp_id = node_id;
#endif
    s_overflow_count = 0U;
    s_busoff_count = 0U;
    /* Instrumentation state is reset only by an explicit (re)initialisation. */
    s_first_error_valid = false;
    memset(&s_first_error, 0, sizeof(s_first_error));
    s_first_busoff_valid = false;
    s_max_tec = 0U;
    s_max_rec = 0U;
    memset(&s_first_busoff, 0, sizeof(s_first_busoff));

    ram_attr.ram_base = (uint32_t)s_mcan_msg_buf;
    ram_attr.ram_size = sizeof(s_mcan_msg_buf);
    status = mcan_set_msg_buf_attr(BOARD_APP_CAN_BASE, &ram_attr);
    if (status != status_success)
    {
        return status;
    }

    mcan_get_default_config(BOARD_APP_CAN_BASE, &can_config);
    can_config.use_lowlevel_timing_setting = true;
#if SERVO_CANFD_DATA_BITRATE == 2000000
    if (bitrate_hz == 1000000U)
    {
        /* Match the adapter arbitration sample point during BRS transitions. */
        timing.prescaler = 1U;
        timing.num_seg1 = 69U;
        timing.num_seg2 = 10U;
        timing.num_sjw = 8U;
    }
#endif
    can_config.can_timing = timing;
    can_config.canfd_timing = data_timing_for(&timing);
    can_config.enable_canfd = true;
    can_config.enable_tdc = can_config.canfd_timing.enable_tdc;
    if (can_config.enable_tdc)
    {
        /* Let the SDK derive SSP offset and measurement filter together. */
        can_config.tdc_config.ssp_offset = 0U;
        can_config.tdc_config.filter_window_length = 0U;
    }
    can_config.enable_transmit_pause = true;
    can_config.disable_auto_retransmission = false;
    can_config.disable_protocol_exception_handling = true;
    can_config.mode = mcan_mode_normal;
    mcan_get_default_ram_config(BOARD_APP_CAN_BASE, &can_config.ram_config, true);
    setup_filters(&can_config);
    can_config.all_filters_config.global_filter_config.accept_non_matching_std_frame_option =
        MCAN_ACCEPT_NON_MATCHING_FRAME_OPTION_REJECT;
    can_config.all_filters_config.global_filter_config.accept_non_matching_ext_frame_option =
        MCAN_ACCEPT_NON_MATCHING_FRAME_OPTION_REJECT;
    /* Y01 uses FDCAN_FILTER_REMOTE: matching remote frames reach the application.
     * CANopen node guarding needs this path. */
    can_config.all_filters_config.global_filter_config.reject_remote_std_frame = false;
    can_config.all_filters_config.global_filter_config.reject_remote_ext_frame = false;
    can_config.interrupt_mask = MCAN_EVENT_RECEIVE | MCAN_INT_RXFIFO0_MSG_LOST | MCAN_EVENT_ERROR;
    can_config.txbuf_trans_interrupt_mask = 0U;

    src_clk_hz = board_init_can_clock(BOARD_APP_CAN_BASE);
    if (src_clk_hz == 0U)
    {
        return status_fail;
    }

    board_init_can(BOARD_APP_CAN_BASE);
    board_can_transceiver_phy_set(BOARD_APP_CAN_BASE, true);

    status = mcan_init(BOARD_APP_CAN_BASE, &can_config, src_clk_hz);
    if (status != status_success)
    {
        return status;
    }

    /* CiA402 keeps bitrate switch off. Custom FD and the MAVLink passthrough send BRS frames. */
#if !defined(USE_CUSTOM) && !IS_USE_CAN_PASSTHROUGH
    status = mcan_begin_reconfig(BOARD_APP_CAN_BASE);
    if (status != status_success)
    {
        return status;
    }
    mcan_disable_bitrate_switch(BOARD_APP_CAN_BASE);
    status = mcan_end_reconfig(BOARD_APP_CAN_BASE);
    if (status != status_success)
    {
        return status;
    }
#endif

    s_inited = true;
    intc_m_enable_irq_with_priority(BOARD_APP_CAN_IRQn, 5); /* lower than 20kHz current loop (6) */
    return status_success;
}

hpm_stat_t bsp_can_send(uint32_t id, const uint8_t *data, uint8_t len)
{
    return bsp_can_send_classic(id, false, false, data, len);
}

hpm_stat_t bsp_can_send_classic(uint32_t id, bool extended, bool remote,
                                const uint8_t *data, uint8_t len)
{
    mcan_tx_frame_t tx;

    if (!s_inited || (len > 8U))
    {
        return status_fail;
    }
    if (extended ? (id > 0x1FFFFFFFU) : (id > 0x7FFU))
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
    tx.rtr = remote ? 1U : 0U;
    for (uint32_t i = 0U; i < len; i++)
    {
        tx.data_8[i] = data[i];
    }
    return transmit(&tx);
}

hpm_stat_t bsp_can_send_fd(uint32_t id, bool extended, bool bitrate_switch,
                           const uint8_t *data, uint8_t len)
{
    mcan_tx_frame_t tx;

    if (!s_inited || (len > BSP_CAN_DATA_MAX))
    {
        return status_fail;
    }
    if (extended ? (id > 0x1FFFFFFFU) : (id > 0x7FFU))
    {
        return status_invalid_argument;
    }
    if ((len > 0U) && (data == NULL))
    {
        return status_invalid_argument;
    }

    memset(&tx, 0, sizeof(tx));
    tx.canfd_frame = 1U;
    tx.bitrate_switch = bitrate_switch ? 1U : 0U;
    tx.dlc = dlc_from_bytes(len);
    if (extended)
    {
        tx.use_ext_id = 1U;
        tx.ext_id = id;
    }
    else
    {
        tx.std_id = (uint16_t)id;
    }
    for (uint32_t i = 0U; i < len; i++)
    {
        tx.data_8[i] = data[i];
    }
    return transmit(&tx);
}

uint32_t bsp_can_overflow_count(void)
{
    return s_overflow_count;
}

uint32_t bsp_can_busoff_count(void)
{
    return s_busoff_count;
}

void bsp_can_get_diag(bsp_can_diag_t *diag)
{
    uint32_t irq_state;

    if (diag == NULL)
    {
        return;
    }
    memset(diag, 0, sizeof(*diag));
    diag->inited = s_inited;
    if (!s_inited)
    {
        return;
    }

    can_capture_snapshot(&diag->now);

    /* The first-bus-off latch and the max counters are written from the RX ISR;
     * copy them as one consistent set. */
    irq_state = disable_global_irq(CSR_MSTATUS_MIE_MASK);
    diag->first_error_valid = s_first_error_valid;
    diag->first_error = s_first_error;
    diag->first_busoff_valid = s_first_busoff_valid;
    diag->first_busoff = s_first_busoff;
    diag->max_tec = s_max_tec;
    diag->max_rec = s_max_rec;
    if ((irq_state & CSR_MSTATUS_MIE_MASK) != 0U)
    {
        enable_global_irq(CSR_MSTATUS_MIE_MASK);
    }
}
