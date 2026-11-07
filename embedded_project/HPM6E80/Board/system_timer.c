#include "system_timer.h"

#include "hpm_clock_drv.h"
#include "hpm_common.h"

SysTimer_t sys_timer = {
    .sys_freq_Mhz = 0,
    .sys_freq_Mhz_inv = 0,
    .now_records = {0},
    .duration_records = {0},
};

// HPM6E80 是 RISC-V 核，rdcycle 直接读 64/32 位周期计数器。
// 这里只取低 32 位，与 STM32 版 DWT_CYCCNT 的用法保持一致（差值运算天然回绕）。
static inline uint32_t sys_timer_get_ticks(void)
{
    uint32_t value;
    __asm__ volatile ("rdcycle %0" : "=r"(value));
    return value;
}

void sys_timer_init(void)
{
    sys_timer.sys_freq_Mhz = clock_get_frequency(clock_cpu0) / 1000000U;
    sys_timer.sys_freq_Mhz_inv = 1.0f / (float)sys_timer.sys_freq_Mhz;
}

void set_timer_record_start(SYS_TIMER_RECORD_INDEX index)
{
    sys_timer.now_records[index] = sys_timer_get_ticks();
}

void set_timer_record_stop(SYS_TIMER_RECORD_INDEX index)
{
    sys_timer.duration_records[index] = sys_timer_get_ticks() - sys_timer.now_records[index];
}

float get_timer_duration_records_us(SYS_TIMER_RECORD_INDEX index)
{
    return sys_timer.sys_freq_Mhz_inv * sys_timer.duration_records[index];
}

void sys_blocking_delay_us(uint32_t us)
{
    if (us == 0U)
    {
        return;
    }
    uint32_t tickstart = sys_timer_get_ticks();
    uint32_t wait = us * sys_timer.sys_freq_Mhz - sys_timer.sys_freq_Mhz / 2U;
    wait += 1U;
    while ((sys_timer_get_ticks() - tickstart) < wait)
    {
    }
}

void sys_blocking_delay_ms(uint32_t ms)
{
    if (ms == 0U)
    {
        return;
    }
    uint32_t tickstart = sys_timer_get_ticks();
    uint32_t wait = ms * sys_timer.sys_freq_Mhz * 1000U - sys_timer.sys_freq_Mhz / 2U;
    wait += 1U;
    while ((sys_timer_get_ticks() - tickstart) < wait)
    {
    }
}
