#ifndef SYSTEM_TIMER_H
#define SYSTEM_TIMER_H

#include <stdint.h>
#include <stdbool.h>
#include "servo_system_cfg.h"
#include "data_type_define.h"

#ifdef __cplusplus
extern "C" {
#endif

// 用 RISC-V 的 rdcycle 做周期计数：HPM6E80 上无需额外外设，分辨率即 CPU 周期（600MHz）。
#define SYS_TIMER_RECORD_SLOTS   (16U)   // 环形记录槽位，覆盖 data_type_define.h 里全部枚举值

typedef struct
{
    uint32_t sys_freq_Mhz;
    float sys_freq_Mhz_inv;
    uint32_t now_records[SYS_TIMER_RECORD_SLOTS];
    uint32_t duration_records[SYS_TIMER_RECORD_SLOTS];
} SysTimer_t;

extern SysTimer_t sys_timer;

void sys_timer_init(void);
void set_timer_record_start(SYS_TIMER_RECORD_INDEX index);
void set_timer_record_stop(SYS_TIMER_RECORD_INDEX index);
float get_timer_duration_records_us(SYS_TIMER_RECORD_INDEX index);
void sys_blocking_delay_us(uint32_t us);
void sys_blocking_delay_ms(uint32_t ms);

#ifdef __cplusplus
}
#endif

#endif // SYSTEM_TIMER_H
