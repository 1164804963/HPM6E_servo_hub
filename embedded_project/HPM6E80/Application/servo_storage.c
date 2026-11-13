#include "servo_storage.h"

#include "board.h"

#include "app_store_param.h"
#include "bsp_api.h"
#include "data_param.h"
#include "motor_ctl_loop.h"
#include "system_timer.h"

/* 前台查看存储命令。到点才处理；桥臂或使能还在时丢掉本次命令。
 * 间隔用 CPU 周期计数，主循环被堵住时不会按严格 1 ms 触发。 */
void servo_storage_poll(void)
{
    static uint32_t store_last_cycle;
    uint32_t now = read_csr(CSR_MCYCLE);

    if ((uint32_t)(now - store_last_cycle) < sys_timer.sys_freq_Mhz * 1000U)
        return;

    store_last_cycle = now;
    uint32_t irq = bsp_irq_save();
    if (get_app_Storage_cmd() != FLASH_STORE_CMD_NULL &&
        (bsp_get_pwm_state() || get_app_Controlword() != APP_CTRL_DISABLE ||
         kAxis.motor_ctl_sm_input.motor_enable != 0))
    {
        set_app_Storage_status(FLASH_STORE_STATUS_WARNING);
        set_app_Storage_cmd(FLASH_STORE_CMD_NULL);
    }
    else
        AppStoreUpdata1ms();
    bsp_irq_restore(irq);
}
