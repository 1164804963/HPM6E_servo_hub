#include "servo_can.h"

#include <string.h>

#include "bsp_api.h"
#include "bsp_can.h"
#include "data_param.h"
#include "master_cia402_callback.h"

#if defined(USE_CANOPEN)
#include "board.h"
#include "hpm_clock_drv.h"
#include "hpm_gptmr_drv.h"
#include "SlaveOD.h"
#include "states.h"
#include "timer.h"
#endif
#if defined(USE_CAN_MAVLINK_HOST)
#include "mavlink_callback.h"
#include "motor_ctl_loop.h"
#endif

#define SERVO_CAN_DEFAULT_NODE_ID (0x15U)
#define SERVO_CAN_DEFAULT_BITRATE (1000000U)

static bool s_ready;
static volatile uint32_t s_node_id = SERVO_CAN_DEFAULT_NODE_ID;
static uint32_t s_bitrate_hz = SERVO_CAN_DEFAULT_BITRATE;
static uint32_t s_active_bitrate_hz;
static hpm_stat_t s_last_error = status_success;
static volatile uint32_t s_rx_count;
static volatile uint32_t s_tx_count;
static volatile uint32_t s_tx_error_count;

#if !defined(USE_CANOPEN) && !defined(USE_ENCOS) && !defined(USE_CUSTOM)
/* Same sequence as Y01 fdcan_cia402_handle. Length is bytes, already converted from DLC. */
static void handle_cia402(const bsp_can_frame_t *rx)
{
    uint8_t is_write;
    uint16_t obj_index;
    uint8_t obj_subindex;
    uint32_t obj_data = 0U;
    uint8_t data_length;
    uint8_t tx_data[8];

    if (rx->extended || (rx->id != s_node_id))
    {
        return;
    }

    s_rx_count = (s_rx_count == 0U) ? 1U : (s_rx_count + 1U);

    if (rx->len < 5U)
    {
        return;
    }

    is_write = rx->data[0];
    obj_index = (uint16_t)((uint16_t)rx->data[1] | ((uint16_t)rx->data[2] << 8));
    obj_subindex = rx->data[3];
    data_length = (uint8_t)(rx->len - 4U);
    switch (data_length)
    {
    case 1U:
        obj_data = rx->data[4];
        break;
    case 2U:
        obj_data = (uint32_t)rx->data[4] | ((uint32_t)rx->data[5] << 8);
        break;
    case 4U:
        obj_data = (uint32_t)rx->data[4] |
                   ((uint32_t)rx->data[5] << 8) |
                   ((uint32_t)rx->data[6] << 16) |
                   ((uint32_t)rx->data[7] << 24);
        break;
    default:
        return;
    }

    if (is_write == 1U)
    {
        (void)master_cia402_write_callback(obj_index, obj_subindex, &obj_data);
    }
    else if (is_write == 0U)
    {
        (void)master_cia402_read_callback(obj_index, obj_subindex, &obj_data);
    }
    else
    {
        return;
    }

    tx_data[0] = is_write;
    tx_data[1] = (uint8_t)(obj_index & 0xFFU);
    tx_data[2] = (uint8_t)((obj_index >> 8) & 0xFFU);
    tx_data[3] = obj_subindex;
    tx_data[4] = (uint8_t)(obj_data & 0xFFU);
    tx_data[5] = (uint8_t)((obj_data >> 8) & 0xFFU);
    tx_data[6] = (uint8_t)((obj_data >> 16) & 0xFFU);
    tx_data[7] = (uint8_t)((obj_data >> 24) & 0xFFU);

    if (bsp_can_send(s_node_id, tx_data, 8U) == status_success)
    {
        s_tx_count++;
    }
    else
    {
        s_tx_error_count++;
    }
}
#endif

#if defined(USE_CANOPEN)
static void handle_canopen(const bsp_can_frame_t *rx)
{
    Message message;

    memset(&message, 0, sizeof(message));
    message.cob_id = (UNS16)rx->id;
    message.rtr = rx->remote ? 1U : 0U;
    message.len = (rx->len > 8U) ? 8U : rx->len;
    if (message.len > 0U)
    {
        memcpy(message.data, rx->data, message.len);
    }
    canDispatch(&SlaveOD_Data, &message);
    if ((message.cob_id == 0x080U) && (SlaveOD_Data.nodeState == Operational))
    {
        set_app_Target_update_state(true);
    }
}

static uint32_t s_canopen_ticks_per_us;
static TIMEVAL s_canopen_elapsed;
static TIMEVAL s_canopen_last_us;

#define CANOPEN_TMR_CH        (1U)
#define CANOPEN_TMR_PERIOD_US (1000U)

void servo_canopen_timer_start(void)
{
    gptmr_channel_config_t config;
    uint32_t hz = clock_get_frequency(BOARD_BLDC_TMR_CLOCK);
    uint32_t period_ticks;

    s_canopen_ticks_per_us = hz / 1000000U;
    if (s_canopen_ticks_per_us == 0U)
    {
        return;
    }
    period_ticks = s_canopen_ticks_per_us * CANOPEN_TMR_PERIOD_US;
    gptmr_channel_get_default_config(BOARD_BLDC_TMR_1MS, &config);
    config.cmp[0] = period_ticks;
    config.debug_mode = 0;
    config.reload = period_ticks + 1U;
    gptmr_enable_irq(BOARD_BLDC_TMR_1MS, GPTMR_CH_CMP_IRQ_MASK(CANOPEN_TMR_CH, 0));
    gptmr_channel_config(BOARD_BLDC_TMR_1MS, CANOPEN_TMR_CH, &config, true);
}

void servo_canopen_timer_isr(void)
{
    if (!gptmr_check_status(BOARD_BLDC_TMR_1MS, GPTMR_CH_CMP_IRQ_MASK(CANOPEN_TMR_CH, 0)))
    {
        return;
    }
    gptmr_clear_status(BOARD_BLDC_TMR_1MS, GPTMR_CH_CMP_IRQ_MASK(CANOPEN_TMR_CH, 0));
    s_canopen_last_us = 0U;
    s_canopen_elapsed = 0U;
    TimeDispatch();
}

void setTimer(TIMEVAL value)
{
    TIMEVAL now;
    TIMEVAL last;
    uint32_t ticks;

    if (s_canopen_ticks_per_us == 0U)
    {
        return;
    }
    now = gptmr_channel_get_counter(BOARD_BLDC_TMR_1MS, CANOPEN_TMR_CH, gptmr_counter_type_normal) /
          s_canopen_ticks_per_us;
    s_canopen_elapsed += now - s_canopen_last_us;
    last = (value >= (CANOPEN_TMR_PERIOD_US - 1U)) ? 0U : ((CANOPEN_TMR_PERIOD_US - 1U) - value);
    s_canopen_last_us = last;
    ticks = (uint32_t)last * s_canopen_ticks_per_us;
    gptmr_channel_update_count(BOARD_BLDC_TMR_1MS, CANOPEN_TMR_CH, ticks);
}

TIMEVAL getElapsedTime(void)
{
    TIMEVAL now;

    if (s_canopen_ticks_per_us == 0U)
    {
        return s_canopen_elapsed;
    }
    now = gptmr_channel_get_counter(BOARD_BLDC_TMR_1MS, CANOPEN_TMR_CH, gptmr_counter_type_normal) /
          s_canopen_ticks_per_us;
    if (now < s_canopen_last_us)
    {
        now += (CANOPEN_TMR_PERIOD_US - 1U);
    }
    return s_canopen_elapsed + (now - s_canopen_last_us);
}

unsigned char canSend(CAN_PORT notused, Message *message)
{
    (void)notused;
    if (message == NULL)
    {
        return 0U;
    }
    if (bsp_can_send_classic(message->cob_id, false, message->rtr != 0U,
                             message->data, message->len) != status_success)
    {
        return 0U;
    }
    return 1U;
}
#elif defined(USE_ENCOS)
/* Y01 fdcan_encos_handle is an empty placeholder. */
static void handle_encos(const bsp_can_frame_t *rx)
{
    (void)rx;
}
#elif defined(USE_CUSTOM)
static void handle_custom(const bsp_can_frame_t *rx)
{
    if (rx->canfd)
    {
        (void)bsp_can_send_fd(s_node_id, rx->extended, rx->bitrate_switch, rx->data, rx->len);
    }
    else
    {
        (void)bsp_can_send_classic(s_node_id, rx->extended, false, rx->data, rx->len);
    }
}
#endif

void bsp_can_on_rx(const bsp_can_frame_t *frame)
{
    if (frame == 0)
    {
        return;
    }
#if defined(USE_CANOPEN)
    handle_canopen(frame);
#elif defined(USE_ENCOS)
    handle_encos(frame);
#elif defined(USE_CUSTOM)
    handle_custom(frame);
#else
    handle_cia402(frame);
#endif
}

hpm_stat_t servo_can_init(uint32_t node_id, uint32_t bitrate_hz)
{
    hpm_stat_t status;

    s_node_id = node_id;
    s_bitrate_hz = bitrate_hz;
    s_rx_count = 0U;
    s_tx_count = 0U;
    s_tx_error_count = 0U;
    s_active_bitrate_hz = 0U;

    status = bsp_can_init(node_id, bitrate_hz);
#if defined(USE_CANOPEN)
    if (status == status_success)
    {
        servo_canopen_timer_start();
        setNodeId(&SlaveOD_Data, (UNS8)s_node_id);
        setState(&SlaveOD_Data, Initialisation);
        setState(&SlaveOD_Data, Operational);
    }
#endif
    s_last_error = status;
    s_ready = (status == status_success);
    if (s_ready)
    {
        s_active_bitrate_hz = bitrate_hz;
    }
    return status;
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
    status->active_bitrate_hz = s_active_bitrate_hz;
    status->last_error = s_last_error;
    status->rx_count = s_rx_count;
    status->tx_count = s_tx_count;
    status->tx_error_count = s_tx_error_count;
    status->overflow_count = bsp_can_overflow_count();
    status->busoff_count = bsp_can_busoff_count();
}

/* Node ID is used on the next frame. Baudrate is stored until the next init. */
bool bsp_can_port_is_ready(bool debug_port)
{
    (void)debug_port;
    return s_ready;
}

void bsp_set_can_id(uint32_t can_id)
{
    s_node_id = can_id;
}

uint32_t bsp_get_can_id(void)
{
    return s_node_id;
}

void bsp_set_can_baudrate(uint32_t baudrate)
{
    s_bitrate_hz = baudrate;
}

uint32_t bsp_get_can_baudrate(void)
{
    return s_bitrate_hz;
}

uint32_t bsp_get_can_mg_counts(void)
{
    return s_rx_count;
}

#if IS_USE_CAN_PASSTHROUGH
#define CAN_POS_PRIORITY  26
#define CAN_POS_SYSID     21
#define CAN_POS_COMPID    13
#define CAN_POS_FLAG_CAST 11
#define CAN_POS_TRANS_SEQ 6
#define CAN_POS_CNT_OF_TX 3
#define CAN_POS_FLAG_END  2
#define CAN_POS_VERSION   0
#define CANFD_MESSAGE     1U
#define CANFD_DEBUG       2U

static uint8_t s_mav_seq;
static uint8_t s_mav_sys_id = 1U;
static uint8_t s_mav_comp_id = 0x15U;

void bsp_can_on_rx_fifo1(const bsp_can_frame_t *frame)
{
    if ((frame == 0) || frame->bitrate_switch)
    {
        return;
    }
    MavlinkRecvCallback(&kAxis, &kAxisDw, (uint8_t *)frame->data, frame->len);
}

static uint8_t mav_send_packet(uint8_t *data, uint16_t len, uint8_t sys_id, uint8_t comp_id,
                               uint8_t priority, uint8_t channel)
{
    uint32_t id_base = 0U;
    uint16_t sent = 0U;
    uint8_t count = 0U;

    id_base |= ((uint32_t)priority & 0x07U) << CAN_POS_PRIORITY;
    id_base |= ((uint32_t)sys_id & 0x1FU) << CAN_POS_SYSID;
    id_base |= ((uint32_t)comp_id & 0xFFU) << CAN_POS_COMPID;
    id_base |= (0U << CAN_POS_FLAG_CAST);

    while (sent < len)
    {
        uint8_t chunk = (uint8_t)((len - sent) > 64U ? 64U : (len - sent));
        uint8_t flag_end = ((uint16_t)(sent + chunk) < len) ? 1U : 0U;
        uint32_t id = id_base;
        bool brs = (channel != CANFD_DEBUG);

        id |= ((uint32_t)s_mav_seq & 0x1FU) << CAN_POS_TRANS_SEQ;
        id |= ((uint32_t)count & 0x07U) << CAN_POS_CNT_OF_TX;
        id |= ((uint32_t)flag_end & 0x01U) << CAN_POS_FLAG_END;
        if (bsp_can_send_fd(id, true, brs, data + sent, chunk) != status_success)
        {
            return 1U;
        }
        sent = (uint16_t)(sent + chunk);
        count++;
        if (count > 7U)
        {
            break;
        }
    }
    s_mav_seq = (uint8_t)((s_mav_seq + 1U) & 0x1FU);
    return 0U;
}

void servo_can_mavlink_send(uint8_t *pdata, uint32_t len)
{
    if ((pdata == 0) || (len > 0xFFFFU))
    {
        return;
    }
    (void)mav_send_packet(pdata, (uint16_t)len, get_app_Sys_id(), get_app_Comp_id(), 1U, CANFD_MESSAGE);
}

/* Y01 maps the CAN node to the MAVLink component id and ignores a direct mav-id write. */
void bsp_set_can_mav_id(uint8_t sys_id, uint8_t comp_id)
{
    (void)sys_id;
    (void)comp_id;
}

void bsp_get_can_mav_id(uint8_t *sys_id, uint8_t *comp_id)
{
    if (sys_id != 0)
    {
        *sys_id = s_mav_sys_id;
    }
    if (comp_id != 0)
    {
        *comp_id = s_mav_comp_id;
    }
}
#endif
