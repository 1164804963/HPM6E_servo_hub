#ifndef SYSTEM_TIMER_H
#define SYSTEM_TIMER_H

#include "stm32h7xx_hal.h"
#include "board.h"

#ifdef __cplusplus
extern "C"
{
}
#endif

#define DWT_LAR_UNLOCK (uint32_t)0xC5ACCE55
#define DWT_LAR (*(volatile uint32_t *)0xE0000FB0)

#define DWT_CR (*(volatile uint32_t *)0xE0001000)
#define DWT_CYCCNT (*(volatile uint32_t *)0xE0001004)
#define DEM_CR (*(volatile uint32_t *)0xE000EDFC)
#define DEM_CR_TRCENA (1 << 24)
#define DWT_CR_CYCCNTENA (1 << 0)

#define SYS_TIMER_RECORD_MAX_INDEX      10
typedef struct
{
    uint32_t now_records[SYS_TIMER_RECORD_MAX_INDEX];
    uint32_t duration_records[SYS_TIMER_RECORD_MAX_INDEX];
    uint32_t sys_freq_Mhz;
    float sys_freq_Mhz_inv;
} SysTimer_t;

void sys_timer_init(void);
void set_timer_record_start(SYS_TIMER_RECORD_INDEX index);
void set_timer_record_stop(SYS_TIMER_RECORD_INDEX index);
float get_timer_duration_records_us(SYS_TIMER_RECORD_INDEX index);
void sys_blocking_delay_us(uint32_t us);
void sys_blocking_delay_ms(uint32_t ms);

#ifdef __cplusplus
}
#endif

#endif