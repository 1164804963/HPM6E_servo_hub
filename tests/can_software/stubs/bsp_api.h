#ifndef BSP_API_H
#define BSP_API_H

#include <stdint.h>
uint32_t bsp_irq_save(void);
void bsp_irq_restore(uint32_t state);

typedef enum
{
    ERROR_CLEAR = 0,
    ERROR_SET = 1
} BSP_ERROR_OPERATION;

typedef enum
{
    ERROR_COMMS_INIT = 0
} BSP_ERROR_CODE;

void sys_set_bsp_error_state(BSP_ERROR_CODE type, BSP_ERROR_OPERATION op);

#endif
