#include "board.h"
#include "bsp_can.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

static bool wait_frame(bsp_can_frame_t *frame)
{
    for (uint32_t i = 0U; i < 500U; i++) /* 5 ms at 10 us */
    {
        if (bsp_can_try_receive(frame) == status_success)
        {
            return true;
        }
        board_delay_us(10U);
    }
    return false;
}

static bool run_case(uint32_t id, bool extended, uint8_t len, uint8_t seed)
{
    uint8_t data[BSP_CAN_DATA_MAX] = {0};
    bsp_can_frame_t rx;
    hpm_stat_t status;

    for (uint32_t i = 0U; i < len; i++)
    {
        data[i] = (uint8_t)(seed + i);
    }

    status = bsp_can_send(id, extended, data, len);
    if (status != status_success)
    {
        printf("send failed: id=0x%lX ext=%u len=%u status=%d\r\n",
               (unsigned long)id, (unsigned)extended, (unsigned)len, (int)status);
        return false;
    }

    if (!wait_frame(&rx))
    {
        printf("receive timeout: id=0x%lX ext=%u len=%u\r\n",
               (unsigned long)id, (unsigned)extended, (unsigned)len);
        return false;
    }

    if ((rx.id != id) || (rx.extended != extended) || (rx.len != len) ||
        ((len > 0U) && (memcmp(rx.data, data, len) != 0)))
    {
        printf("mismatch: tx id=0x%lX ext=%u len=%u, rx id=0x%lX ext=%u len=%u\r\n",
               (unsigned long)id, (unsigned)extended, (unsigned)len,
               (unsigned long)rx.id, (unsigned)rx.extended, (unsigned)rx.len);
        return false;
    }

    return true;
}

int main(void)
{
    bool ok = true;
    uint32_t irq_before;
    uint32_t irq_after;

    board_init();

    if (bsp_can_init(1000000U, true) != status_success)
    {
        printf("CAN_LOOPBACK FAIL: init\r\n");
        while (1)
        {
            board_delay_ms(1000U);
        }
    }

    irq_before = bsp_can_rx_irq_count();

    ok = run_case(0x123U, false, 8U, 0x10U) && ok;
    ok = run_case(0x1ABCDEU, true, 8U, 0x20U) && ok;
    ok = run_case(0x7FFU, false, 0U, 0x00U) && ok;
    ok = run_case(0x1FFFFFFFU, true, 8U, 0x30U) && ok;

    irq_after = bsp_can_rx_irq_count();
    if (irq_after <= irq_before)
    {
        printf("CAN_LOOPBACK FAIL: no RX IRQ\r\n");
        ok = false;
    }
    if ((bsp_can_overflow_count() != 0U) || (bsp_can_busoff_count() != 0U))
    {
        printf("CAN_LOOPBACK FAIL: errors ovf=%lu boff=%lu\r\n",
               (unsigned long)bsp_can_overflow_count(),
               (unsigned long)bsp_can_busoff_count());
        ok = false;
    }

    printf("CAN_LOOPBACK %s: rx_irq=%lu\r\n", ok ? "PASS" : "FAIL",
           (unsigned long)irq_after);

    while (1)
    {
        board_delay_ms(1000U);
    }
}
