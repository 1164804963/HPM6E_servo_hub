#include "servo_host.h"

#include <stdint.h>

#include "board.h"              // BOARD_CONSOLE_UART_BASE
#include "hpm_uart_drv.h"

#include "mavlink_callback.h"   // RegisterSendCallback / MavlinkRecvCallback
#include "motor_ctl_loop.h"     // kAxis / kAxisDw
#include "servo_board.h"        // board_get_ctrl_tick()
#include "servo_console.h"

/* 上位机一帧最长 512 字节（与 MAVLINK_RECV_BUFF_SIZE 一致） */
#define HOST_FRAME_MAX      (MAVLINK_RECV_BUFF_SIZE)

/* 半截帧超时：921600 下一帧最多 5.5ms，正常请求都不到 1ms，
 * 超过 100 个 20kHz tick（5ms）还没收完就丢掉重来。 */
#define HOST_FRAME_TIMEOUT_TICK  (100U)

static uint8_t s_frame[HOST_FRAME_MAX];
static uint32_t s_frame_len;
static uint32_t s_frame_total;
static uint32_t s_frame_start_tick;

/* 上位机回包：直接写控制台那一路 UART，和 printf 共用同一条线。 */
static void servo_host_send(uint8_t *pdata, uint32_t len)
{
    for (uint32_t i = 0; i < len; i++)
    {
        while (status_success != uart_send_byte(BOARD_CONSOLE_UART_BASE, pdata[i]))
        {
        }
    }
}

void servo_host_init(void)
{
    RegisterSendCallback(servo_host_send);
}

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

/*
 * 主循环里轮询：把 UART 收到的字节分给 MAVLink 或调试台。
 * 这里直接读 UART 寄存器而不是 console_try_receive_byte()，
 * 因为后者用 0 表示"没数据"，会和 MAVLink 载荷里的 0x00 混淆。
 */
void servo_host_poll(void)
{
    /* 半截帧超时：坏字节（比如长度字段被噪声改过）不处理的话，
     * 会把后面正常帧的字节全当成本帧的载荷吃掉，整条链路就哑了。 */
    if ((s_frame_len != 0U) && ((board_get_ctrl_tick() - s_frame_start_tick) > HOST_FRAME_TIMEOUT_TICK))
    {
        s_frame_len = 0U;
        s_frame_total = 0U;
    }

    while (uart_check_status(BOARD_CONSOLE_UART_BASE, uart_stat_data_ready))
    {
        uint8_t c = 0U;

        (void)uart_receive_byte(BOARD_CONSOLE_UART_BASE, &c);

        if (s_frame_len == 0U)
        {
            if ((c == 0xFD) || (c == 0xFE))
            {
                s_frame[0] = c;
                s_frame_len = 1U;
                s_frame_total = 0U;
                s_frame_start_tick = board_get_ctrl_tick();
            }
            else
            {
                servo_console_feed(c);
            }
            continue;
        }

        s_frame[s_frame_len++] = c;

        if (s_frame_len == 2U)
        {
            s_frame_total = frame_total_len(s_frame[0], c);
            if (s_frame_total > HOST_FRAME_MAX)
            {
                /* 长度不合理，当噪声丢掉 */
                s_frame_len = 0U;
                s_frame_total = 0U;
                continue;
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
}
