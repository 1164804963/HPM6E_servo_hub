#include "servo_host.h"

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stddef.h>

#include "board.h"              // BOARD_CONSOLE_UART_BASE / BOARD_CONSOLE_UART_IRQ
#include "hpm_uart_drv.h"
#include "hpm_interrupt.h"
#include "hpm_dmav2_drv.h"
#include "hpm_dmamux_drv.h"
#include "hpm_clock_drv.h"

#include "bsp_api.h"            // bsp_irq_save/restore for short ring guards
#include "mavlink_callback.h"   // RegisterSendCallback / MavlinkRecvCallback
#include "version.h"
#if defined(USE_CAN_MAVLINK_HOST)
#include "servo_can.h"
#endif
#include "motor_ctl_loop.h"     // kAxis / kAxisDw
#include "servo_board.h"        // board_get_ctrl_tick()
#include "servo_console.h"

/* UART0: DMA receives into a non-cacheable ring. The foreground splits and
 * dispatches MAVLink/console frames; TX IRQ service never waits for the FIFO. */

/* 上位机一帧最长 512 字节（与 MAVLINK_RECV_BUFF_SIZE 一致） */
#define HOST_FRAME_MAX      (MAVLINK_RECV_BUFF_SIZE)

/* 接收环形缓冲：4KiB，吸收控制中断和前台解析期间的有限突发 */
#define HOST_RX_RB_SIZE     (4096U)
/* 发送环形缓冲：MAVLink 回包一般 <512，留 2K 足够排队几帧 */
#define HOST_TX_RB_SIZE     (2048U)

/* HDMA channel 0 is reserved for UART0 RX. ADC uses its own PMT DMA. */
#define HOST_RX_DMA_CHANNEL (0U)
#define HOST_RX_DMA_MASK (1UL << HOST_RX_DMA_CHANNEL)
static ATTR_PLACE_AT_NONCACHEABLE_BSS_WITH_ALIGNMENT(32) volatile uint8_t s_rx_rb[HOST_RX_RB_SIZE];
static volatile uint32_t s_rx_dma_wraps;
static uint32_t s_rx_read_total;
static volatile bool s_rx_dma_ready;
static volatile bool s_rx_discard_pending;
static volatile uint32_t s_rx_line_errors;
static volatile uint32_t s_rx_last_irq;
static volatile uint32_t s_rx_dma_errors;
static volatile uint32_t s_rx_overruns;

static volatile uint8_t  s_tx_rb[HOST_TX_RB_SIZE];
static volatile uint32_t s_tx_head;      /* 生产者写 */
static volatile uint32_t s_tx_tail;      /* TX 中断读 */

/* MAVLink 帧切分状态（仅前台 host_rx_byte 维护） */
static uint8_t  s_frame[HOST_FRAME_MAX];
static uint32_t s_frame_len;
static uint32_t s_frame_total;

/* The DMA runs independently of control ISR latency. No RX-idle boundary is
 * needed: the foreground reads the current producer position, as in the SDK's
 * DMAV2 circular UART example. The completion IRQ counts buffer wraps. */
static hpm_stat_t host_rx_dma_start(void)
{
    dma_handshake_config_t config;
    s_rx_dma_ready = false;
    dma_disable_channel(HPM_HDMA, HOST_RX_DMA_CHANNEL);
    dma_clear_transfer_status(HPM_HDMA, HOST_RX_DMA_CHANNEL);
    s_rx_dma_wraps = 0U;
    dma_default_handshake_config(HPM_HDMA, &config);
    config.ch_index = HOST_RX_DMA_CHANNEL;
    config.dst = core_local_mem_to_sys_address(BOARD_RUNNING_CORE, (uint32_t)s_rx_rb);
    config.dst_fixed = false;
    config.src = (uint32_t)&BOARD_CONSOLE_UART_BASE->RBR;
    config.src_fixed = true;
    config.data_width = DMA_TRANSFER_WIDTH_BYTE;
    config.size_in_byte = HOST_RX_RB_SIZE;
    config.en_infiniteloop = true;
    config.interrupt_mask = DMA_INTERRUPT_MASK_HALF_TC;
    hpm_stat_t status = dma_setup_handshake(HPM_HDMA, &config, true);
    s_rx_dma_ready = (status == status_success);
    return status;
}

SDK_DECLARE_EXT_ISR_M(IRQn_HDMA, isr_host_rx_dma)
void isr_host_rx_dma(void)
{
    uint32_t status = dma_check_transfer_status(HPM_HDMA, HOST_RX_DMA_CHANNEL);
    if ((status & (DMA_CHANNEL_STATUS_ERROR | DMA_CHANNEL_STATUS_ABORT)) != 0U)
    {
        ++s_rx_dma_errors;
        s_rx_discard_pending = true;
        (void)host_rx_dma_start();
    }
    else if ((status & DMA_CHANNEL_STATUS_TC) != 0U)
    {
        ++s_rx_dma_wraps;
    }
}

/* Called with CPU IRQs masked. DMA itself keeps receiving; retry a snapshot
 * if a completion appeared between the status and remaining-count reads. */
static uint32_t host_rx_produced(void)
{
    uint32_t pending_before, pending_after, remaining;
    do
    {
        pending_before = HPM_HDMA->INTTCSTS & HOST_RX_DMA_MASK;
        remaining = dma_get_remaining_transfer_size(HPM_HDMA, HOST_RX_DMA_CHANNEL);
        pending_after = HPM_HDMA->INTTCSTS & HOST_RX_DMA_MASK;
    } while (pending_before != pending_after);
    uint32_t wraps = s_rx_dma_wraps + (pending_after != 0U ? 1U : 0U);
    uint32_t position = (HOST_RX_RB_SIZE - remaining) & (HOST_RX_RB_SIZE - 1U);
    __asm__ volatile ("fence iorw, iorw" ::: "memory");
    return wraps * HOST_RX_RB_SIZE + position;
}

/* ------------------------------------------------------------------ 发送 */

/* 整帧入发送环形缓冲；空间不足则整帧丢弃，不阻塞、不插入部分帧。 */
static void host_tx_enqueue(const uint8_t *pdata, uint32_t len);

/* 由 TX 中断调用：把缓冲里的数据往 UART FIFO 灌，灌空则关 TX 中断 */
static void host_tx_service(void)
{
    UART_Type *ptr = BOARD_CONSOLE_UART_BASE;

    while (s_tx_tail != s_tx_head)
    {
        uint32_t next = (s_tx_tail + 1U) % HOST_TX_RB_SIZE;

        /* FIFO 满则等下次 TX 中断，不忙等 */
        if (!uart_check_status(ptr, uart_stat_tx_slot_avail))
        {
            break;
        }
        uart_write_byte(ptr, s_tx_rb[s_tx_tail]);
        s_tx_tail = next;
    }

    if (s_tx_tail == s_tx_head)
    {
        /* 全部发完：关 TX slot 中断，避免空转 */
        uart_disable_irq(ptr, uart_intr_tx_slot_avail);
    }
}

/* RegisterSendCallback 注册的就是这个：MAVLink 一帧整包进来 → 入队 → 后台发 */
static void servo_host_send(uint8_t *pdata, uint32_t len)
{
    host_tx_enqueue(pdata, len);
}

static void host_tx_enqueue(const uint8_t *pdata, uint32_t len)
{
    UART_Type *ptr = BOARD_CONSOLE_UART_BASE;
    uint32_t irq_state;
    uint32_t head;
    uint32_t tail;
    uint32_t free_count;
    uint32_t i;

    if ((pdata == NULL) || (len == 0U) || (len > (HOST_TX_RB_SIZE - 1U)))
    {
        return;
    }

    /* The MAVLink callback runs in the foreground, but CAN/scope may also
     * enqueue from an ISR. Reserve the whole frame under a short IRQ guard;
     * never wait on the UART here. */
    irq_state = bsp_irq_save();
    head = s_tx_head;
    tail = s_tx_tail;
    free_count = (tail + HOST_TX_RB_SIZE - head - 1U) % HOST_TX_RB_SIZE;
    if (len > free_count)
    {
        bsp_irq_restore(irq_state);
        return;   /* drop the whole frame, keep the queued frames in order */
    }

    for (i = 0U; i < len; i++)
    {
        s_tx_rb[head] = pdata[i];
        head = (head + 1U) % HOST_TX_RB_SIZE;
    }
    s_tx_head = head;
    bsp_irq_restore(irq_state);

    uart_enable_irq(ptr, uart_intr_tx_slot_avail);
}

/* ------------------------------------------------------------------ 接收 */

/*
 * MAVLink 整帧长度（含 magic 和 CRC）：
 *   v2 0xFD：10 + payload + 2（signed时另加13字节尾部）
 *   v1 0xFE：6  + payload + 2
 * 第2字节给出基本长度，第3字节决定v2签名尾部。
 */
static uint32_t frame_total_len(uint8_t magic, uint8_t payload_len)
{
    if (magic == 0xFD)
    {
        return (uint32_t)(10U + payload_len + 2U);
    }
    return (uint32_t)(6U + payload_len + 2U);
}

/* 处理一个收到的字节：要么喂调试台，要么攒进 MAVLink 帧；整帧收齐即回调。 */
static void host_rx_byte(uint8_t c)
{
    if (s_frame_len == 0U)
    {
        if ((c == 0xFD) || (c == 0xFE))
        {
            s_frame[0] = c;
            s_frame_len = 1U;
            s_frame_total = 0U;
        }
        else
        {
            servo_console_feed(c);
        }
        return;
    }

    s_frame[s_frame_len++] = c;

    if (s_frame_len == 2U)
    {
        s_frame_total = frame_total_len(s_frame[0], c);
        if (s_frame_total > HOST_FRAME_MAX)
        {
            s_frame_len = 0U;
            s_frame_total = 0U;
            return;
        }
    }

    /* MAVLink2's signed flag adds a binary 13-byte trailer. */
    if ((s_frame_len == 3U) && (s_frame[0] == 0xFD) &&
        ((s_frame[2] & MAVLINK_IFLAG_SIGNED) != 0U))
    {
        s_frame_total += MAVLINK_SIGNATURE_BLOCK_LEN;
    }

    if ((s_frame_total != 0U) && (s_frame_len >= s_frame_total))
    {
#if !defined(USE_CAN_MAVLINK_HOST)
        MavlinkRecvCallback(&kAxis, &kAxisDw, s_frame, s_frame_len);
#endif
        /* In CAN-host mode consume the UART frame without dispatching it. Binary
         * MAVLink bytes must not fall through into console commands. */
        s_frame_len = 0U;
        s_frame_total = 0U;
    }
    else if (s_frame_len >= HOST_FRAME_MAX)
    {
        s_frame_len = 0U;
        s_frame_total = 0U;
    }
}

/* Snapshot the DMA producer and take one byte under a short IRQ guard. */
static void host_rx_drain(void)
{
    for (;;)
    {
        uint32_t irq_state = bsp_irq_save();
        if (!s_rx_dma_ready)
        {
            bsp_irq_restore(irq_state);
            return;
        }
        uint32_t produced = host_rx_produced();
        uint32_t available = produced - s_rx_read_total;
        if (s_rx_discard_pending || (available >= HOST_RX_RB_SIZE && available < 0x80000000U))
        {
            if (available >= HOST_RX_RB_SIZE && available < 0x80000000U) ++s_rx_overruns;
            s_rx_discard_pending = false;
            s_rx_read_total = produced;
            s_frame_len = 0U;
            s_frame_total = 0U;
            available = 0U;
        }
        /* At the hardware reload boundary, zero remaining can precede the TC
         * flag by a bus cycle. Retry in the next foreground poll. */
        if (available == 0U || available >= 0x80000000U)
        {
            bsp_irq_restore(irq_state);
            break;
        }
        uint8_t c = s_rx_rb[s_rx_read_total & (HOST_RX_RB_SIZE - 1U)];
        ++s_rx_read_total;
        bsp_irq_restore(irq_state);
        host_rx_byte(c);
    }
}

/* RX bytes are moved by DMA, even while a higher-priority ISR is running. */
void servo_host_uart_isr(void)
{
    UART_Type *ptr = BOARD_CONSOLE_UART_BASE;
    uint8_t id = uart_get_irq_id(ptr);
    uint32_t line_status = ptr->LSR;
    s_rx_last_irq = id;
    /* DMA can pop an erroneous FIFO entry before this handler runs. The PLIC
     * retains the interrupt, while IIR can already report 1 (no pending cause). */
    if ((id == uart_intr_id_rx_line_stat) || (id == 1U) || ((line_status & (UART_LSR_OE_MASK | UART_LSR_FE_MASK | UART_LSR_PE_MASK |
                        UART_LSR_LBREAK_MASK | UART_LSR_ERRF_MASK)) != 0U))
    {
        ++s_rx_line_errors;
        uart_clear_rx_fifo(ptr);
        s_rx_discard_pending = true;
    }
    if (id == uart_intr_id_tx_slot_avail)
    {
        host_tx_service();
    }
    /* Complete the TX IRQ mask write before the PLIC completion. */
    __asm__ volatile ("fence iorw, iorw" ::: "memory");
}

/* ------------------------------------------------------------------ 对外 */

void servo_host_init(void)
{
    UART_Type *ptr = BOARD_CONSOLE_UART_BASE;

#if defined(USE_CAN_MAVLINK_HOST)
    RegisterSendCallback(servo_can_mavlink_send);
#else
    RegisterSendCallback(servo_host_send);
#endif

    s_rx_read_total = 0U;
    s_rx_dma_wraps = 0U;
    s_rx_line_errors = s_rx_dma_errors = s_rx_overruns = 0U;
    s_tx_head = s_tx_tail = 0U;
    s_rx_discard_pending = false;
    s_frame_len = 0U;
    s_frame_total = 0U;

    uart_disable_irq(ptr, uart_intr_rx_data_avail_or_timeout | uart_intr_tx_slot_avail);
#if defined(HPM_IP_FEATURE_UART_RX_IDLE_DETECT) && HPM_IP_FEATURE_UART_RX_IDLE_DETECT
    uart_disable_irq(ptr, uart_intr_rx_line_idle);
    uart_disable_rxline_idle_detection(ptr);
#endif
    uart_fifo_ctrl_t fifo = {0};
    fifo.fifo_enable = true;
    fifo.dma_enable = true;
    fifo.rx_fifo_level = uart_rx_fifo_trg_not_empty;
    fifo.tx_fifo_level = uart_tx_fifo_trg_not_full;
    uart_config_fifo_ctrl(ptr, &fifo);
    clock_add_to_group(clock_hdma, 0);
    dmamux_config(HPM_DMAMUX, DMA_SOC_CHN_TO_DMAMUX_CHN(HPM_HDMA, HOST_RX_DMA_CHANNEL),
                  BOARD_CONSOLE_UART_RX_DMA_REQ, true);
    intc_m_enable_irq_with_priority(IRQn_HDMA, 5);
    if (host_rx_dma_start() != status_success)
    {
        sys_set_bsp_error_state(ERROR_COMMS_INIT, ERROR_SET);
        printf("host: RX DMA initialization failed\r\n");
    }
    uart_enable_irq(ptr, uart_intr_rx_line_stat);
}

/*
 * 前台接收解析：DMA持续收字节，MAVLink/console 在这里执行。
 * 由 main while 在 servo_console_poll() 之前调用。
 */
void servo_host_poll(void)
{
    host_rx_drain();
}
