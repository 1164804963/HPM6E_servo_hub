#ifndef HPM_COMMON_H
#define HPM_COMMON_H

#include <stdbool.h>
#include <stdint.h>

typedef enum
{
    status_success = 0,
    status_fail = -1,
    status_invalid_argument = -2,
    status_timeout = -3,
    status_mcan_txfifo_full = -4,
} hpm_stat_t;

#endif
