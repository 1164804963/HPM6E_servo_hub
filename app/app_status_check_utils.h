#ifndef APP_STATUS_CHECK_UTILS_H
#define APP_STATUS_CHECK_UTILS_H

#include <stdbool.h>
#include <stdint.h>

/* Persistent BSP faults must not be bypassed by a normal Fault Reset. */
static inline bool app_error_clear_allowed(bool bus_voltage,
                                           bool nfault,
                                           bool comms_init)
{
    return !(bus_voltage || nfault || comms_init);
}

typedef struct
{
    bool active;
    uint32_t last_count;
    float elapsed_s;
} AppCanMonitorState;

/* 只在活动源为 BUS 且 J9 就绪时累计；切换/离开 BUS 时重建基线。 */
static inline bool app_can_monitor_step(AppCanMonitorState *state,
                                        bool active,
                                        uint32_t count,
                                        float dt_s,
                                        float timeout_s)
{
    if (!active)
    {
        state->active = false;
        state->last_count = count;
        state->elapsed_s = 0.0f;
        return false;
    }

    if (count == 0U && state->last_count == 0U)
    {
        state->active = true;
        state->elapsed_s = 0.0f;
        return false; /* No first frame since this monitor baseline. */
    }

    if (!state->active)
    {
        state->active = true;
        state->last_count = count;
        state->elapsed_s = 0.0f;
        if (count == 0U)
        {
            return false; /* 保留原语义：收到第一帧后才开始掉线计时 */
        }
    }

    if (count == state->last_count)
    {
        state->elapsed_s += dt_s;
        if (state->elapsed_s >= timeout_s)
        {
            state->elapsed_s = timeout_s;
            return true;
        }
    }
    else
    {
        state->elapsed_s = 0.0f;
        state->last_count = count;
    }
    return false;
}

/* 当前活动源：HOST 要求 J8，BUS 要求 J9。 */
static inline bool app_comm_source_ready(bool host_authority,
                                         bool j8_ready,
                                         bool j9_ready)
{
    return host_authority ? j8_ready : j9_ready;
}

#endif /* APP_STATUS_CHECK_UTILS_H */
