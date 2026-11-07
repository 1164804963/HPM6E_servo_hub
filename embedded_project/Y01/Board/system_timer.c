#include "system_timer.h"

SysTimer_t sys_timer = {
    .sys_freq_Mhz = 0,
    .sys_freq_Mhz_inv = 0,
    .now_records = {0},
    .duration_records = {0},
};

void sys_timer_init(void)
{
    if (!((DEM_CR & DEM_CR_TRCENA) && DWT_CR & DWT_CR_CYCCNTENA))
    {
        DEM_CR |= DEM_CR_TRCENA;//第一步使能DWT外设
        DWT_LAR |= DWT_LAR_UNLOCK;
        DWT_CYCCNT = 0u;//第二步在使能DWT计数前先清零
        DWT_CR |= DWT_CR_CYCCNTENA;//第三步使能DWT计数
    }
    sys_timer.sys_freq_Mhz = HAL_RCC_GetSysClockFreq() / 1000000;
    sys_timer.sys_freq_Mhz_inv = 1.0f / (float)sys_timer.sys_freq_Mhz;
}

void set_timer_record_start(SYS_TIMER_RECORD_INDEX index)
{
    sys_timer.now_records[index] = DWT_CYCCNT;
}

void set_timer_record_stop(SYS_TIMER_RECORD_INDEX index)
{
    sys_timer.duration_records[index] = DWT_CYCCNT - sys_timer.now_records[index];
}

float get_timer_duration_records_us(SYS_TIMER_RECORD_INDEX index)
{
    return sys_timer.sys_freq_Mhz_inv * sys_timer.duration_records[index];
}

static uint32_t sys_timer_get_ticks(void)
{
    return (uint32_t)(DWT_CYCCNT);
}

void sys_blocking_delay_us(uint32_t us)
{
    if (us == 0)
    {
        return;
    }
    uint32_t tickstart = sys_timer_get_ticks();
    uint32_t wait = us * sys_timer.sys_freq_Mhz - sys_timer.sys_freq_Mhz / 2;
    if (wait < 0xFFFFFFFFU)
    {
        wait += 1;
    }
    while ((sys_timer_get_ticks() - tickstart) < wait)
    {
    }
}

void sys_blocking_delay_ms(uint32_t ms)
{
    if (ms == 0)
    {
        return;
    }

    uint32_t tickstart = sys_timer_get_ticks();
    uint32_t wait = ms * sys_timer.sys_freq_Mhz * 1000 - sys_timer.sys_freq_Mhz / 2;
    if (wait < 0xFFFFFFFFU)
    {
        wait += 1;
    }
    while ((sys_timer_get_ticks() - tickstart) < wait)
    {
    }
}