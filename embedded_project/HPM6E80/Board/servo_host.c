#include "servo_host.h"

#include <stdint.h>
#include <stdbool.h>

#include "board.h"              // BOARD_CONSOLE_UART_BASE / BOARD_CONSOLE_UART_IRQ
#include "hpm_uart_drv.h"
#include "hpm_interrupt.h"

#include "mavlink_callback.h"   // RegisterSendCallback / MavlinkRecvCallback
#include "motor_ctl_loop.h"     // kAxis / kAxisDw
#include "servo_board.h"        // board_get_ctrl_tick()
#include "servo_console.h"

/* ---------------------------------------------------------------------------
 * 上位机通道：UART0，中断驱动（与 Y01 原工程一致：DMA + 空闲中断 →
 * 这里用 HPM UART 的 RX 数据中断 + RX line-idle 中断与之等价）。
 *
 * 接收：RX 中断把字节推进 s_rx_rb 环形缓冲；RX-idle 中断表示“一帧收完”，
 *       在中断里按帧边界切分后调用 MavlinkRecvCallback（与 Y01 一致）。
 * 发送：MAVLink 回包不再忙等逐字节发送，而是整帧入 s_tx_rb 后由 TX 中断后台发。
 * 主循环：清空（控制全在中断，通信也全在中断）。
 * ------------------------------------------------------------------------- */

/* 上位机一帧最长 512 字节（与 MAVLINK_RECV_BUFF_SIZE 一致） */
#define HOST_FRAME_MAX      (MAVLINK_RECV_BUFF_SIZE)

/* 接收环形缓冲：一帧最多 512，留一倍余量避免 idle 边界处覆盖 */
#define HOST_RX_RB_SIZE     (1024U)
/* 发送环形缓冲：MAVLink 回包一般 <512，留 2K 足够排队几帧 */
#define HOST_TX_RB_SIZE     (2048U)

static volatile uint8_t  s_rx_rb[HOST_RX_RB_SIZE];
static volatile uint32_t s_rx_head;      /* 中断写 */
static volatile uint32_t s_rx_tail;      /* 主循环/中断消费者读 */

static volatile uint8_t  s_tx_rb[HOST_TX_RB_SIZE];
static volatile uint32_t s_tx_head;      /* 生产者写 */
static volatile uint32_t s_tx_tail;      /* TX 中断读 */

/* MAVLink 帧切分状态（在 RX-idle 中断/接收处理里维护） */
static uint8_t  s_frame[HOST_FRAME_MAX];
static uint32_t s_frame_len;
static uint32_t s_frame_total;

/* ------------------------------------------------------------------ 发送 */

/* 把一段数据塞进发送环形缓冲，然后开 TX 中断后台发。返回实际入队字节数。 */
static void host_tx_enqueue(const uint8_t *pdata, uint32_t len);

/* 由 TX 中断调用：把缓冲里的数据往 UART FIFO 灌，灌空则关 TX 中断 */
static void host_tx_service(void)
{
    UART_Type *ptr = BOARD_CONSOLE_UART_BASE;

    while (s_tx_tail != s_tx_head)
    {
        uint32_t next = (s_tx_tail + 1U) % HOST_TX_RB_SIZE;

        /* FIFO 满则等下次 TX 中断，不忙等 */
        if (status_success != uart_send_byte(ptr, s_tx_rb[s_tx_tail]))
        {
            break;
        }
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
    uint32_t i = 0U;

    while (i < len)
    {
        uint32_t next = (s_tx_head + 1U) % HOST_TX_RB_SIZE;

        if (next == s_tx_tail)
        {
            /* 缓冲满：直接把剩余字节灌给 FIFO（尽力而为，正常不会走到） */
            while (i < len)
            {
                while (status_success != uart_send_byte(ptr, pdata[i]))
                {
                }
                i++;
            }
            break;
        }
        s_tx_rb[s_tx_head] = pdata[i];
        s_tx_head = next;
        i++;
    }

    /* 打开 TX slot 中断，让中断把缓冲灌出去 */
    uart_enable_irq(ptr, uart_intr_tx_slot_avail);
}

/* ------------------------------------------------------------------ 接收 */

/*
 * MAVLink 整帧长度（含 magic 和 CRC）：
 *   v2 0xFD：10 + payload + 2
 *   v1 0xFE：6  + payload + 2
 * 收到第 2 个字节（payload 长度）就能算出来。
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

    if ((s_frame_total != 0U) && (s_frame_len >= s_frame_total))
    {
        MavlinkRecvCallback(&kAxis, &kAxisDw, s_frame, s_frame_len);
        s_frame_len = 0U;
        s_frame_total = 0U;
    }
    else if (s_frame_len >= HOST_FRAME_MAX)
    {
        s_frame_len = 0U;
        s_frame_total = 0U;
    }
}

/* 把 RX 环形缓冲里已到的字节全部消费掉 */
static void host_rx_drain(void)
{
    while (s_rx_tail != s_rx_head)
    {
        uint8_t c = s_rx_rb[s_rx_tail];
        s_rx_tail = (s_rx_tail + 1U) % HOST_RX_RB_SIZE;
        host_rx_byte(c);
    }
}

/* UART0 中断服务：接收（数据可用 / line-idle）+ 发送（slot avail） */
void servo_host_uart_isr(void)
{
    UART_Type *ptr = BOARD_CONSOLE_UART_BASE;
    uint8_t id = uart_get_irq_id(ptr);

    /* 接收数据可用（或 RX FIFO 超时） */
    if ((id == uart_intr_id_rx_data_avail) || (id == uart_intr_id_rx_timeout))
    {
        uint8_t c;
        while (uart_try_receive_byte(ptr, &c) == status_success)
        {
            uint32_t next = (s_rx_head + 1U) % HOST_RX_RB_SIZE;
            if (next != s_rx_tail)
            {
                s_rx_rb[s_rx_head] = c;
                s_rx_head = next;
            }
            /* 环形缓冲满则丢新字节（正常不会发生） */
        }
        host_rx_drain();
    }

    /* RX 线路空闲：一帧收完，再兜底 drain 一次（等价 Y01 的 IDLE 中断时机） */
    if (uart_is_rxline_idle(ptr))
    {
        uart_clear_rxline_idle_flag(ptr);
        host_rx_drain();
    }

    /* 接收线路错误（溢出/帧错/奇偶/噪声）：清 FIFO，避免坏字节把链路卡死 */
    if (uart_check_status(ptr, uart_stat_overrun_error) ||
        uart_check_status(ptr, uart_stat_framing_error) ||
        uart_check_status(ptr, uart_stat_parity_error))
    {
        uart_clear_rx_fifo(ptr);
    }

    /* 发送：有空间就继续灌 */
    if (id == uart_intr_id_tx_slot_avail)
    {
        host_tx_service();
    }
}

/* ------------------------------------------------------------------ 对外 */

void servo_host_init(void)
{
    UART_Type *ptr = BOARD_CONSOLE_UART_BASE;

    RegisterSendCallback(servo_host_send);

    s_rx_head = s_rx_tail = 0U;
    s_tx_head = s_tx_tail = 0U;
    s_frame_len = 0U;
    s_frame_total = 0U;

    /* RX 数据中断：每来字节推进缓冲并切帧（MAVLink 靠长度字段即可定界，
     * 不依赖 idle）。idle 中断作为兜底一并开，阈值 2 bit。 */
    uart_enable_irq(ptr, uart_intr_rx_data_avail_or_timeout);
    uart_disable_irq(ptr, uart_intr_tx_slot_avail);

#if defined(HPM_IP_FEATURE_UART_RX_IDLE_DETECT) && (HPM_IP_FEATURE_UART_RX_IDLE_DETECT == 1)
    {
        uart_rxline_idle_config_t idle_cfg;
        idle_cfg.detect_enable = true;
        idle_cfg.detect_irq_enable = true;
        idle_cfg.idle_cond = uart_rxline_idle_cond_rxline_logic_one;
        idle_cfg.threshold = 4U;   /* 线路高电平持续 4 bit 即判空闲（约半个字节时间） */
        (void)uart_init_rxline_idle_detection(ptr, idle_cfg);
    }
#endif
}

/*
 * 保留名以兼容 main.c：中断驱动后主循环不再需要轮询，这里做成空操作。
 * 真正的收/发都在 servo_host_uart_isr() 里完成。
 */
void servo_host_poll(void)
{
}
