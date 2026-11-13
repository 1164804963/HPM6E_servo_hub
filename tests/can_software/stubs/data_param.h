#ifndef DATA_PARAM_H
#define DATA_PARAM_H

#include <stdint.h>
#include <stdbool.h>

#define APP_CTRL_DISABLE (0U)
#define APP_CTRL_ENABLE (1U)
#define APP_CTRL_EMERGENCY_BRAKE (2U)
#define APP_CTRL_CLEAR_ERROR (3U)
#define MOTOR_CTL_SM_MOTOR_EMERGENCY_BRAKE (2U)

typedef enum
{
    EMERGENCY_BRAKE_MODE_DISABLED = 0,
    EMERGENCY_BRAKE_MODE_SLOW_DOWN_RAMP,
    EMERGENCY_BRAKE_MODE_QUICK_STOP_RAMP,
    EMERGENCY_BRAKE_MODE_CURRENT_LIMIT,
    EMERGENCY_BRAKE_MODE_VOLTAGE_LIMIT,
    EMERGENCY_BRAKE_MODE_SLOW_DOWN_RAMP_ENABLE,
    EMERGENCY_BRAKE_MODE_QUICK_STOP_RAMP_ENABLE,
    EMERGENCY_BRAKE_MODE_CURRENT_LIMIT_ENABLE,
    EMERGENCY_BRAKE_MODE_VOLTAGE_LIMIT_ENABLE,
} APP_Emergency_Brake_Mode;

uint32_t set_app_Controlword(uint16_t val);
bool get_app_Emergency_brake_requested(void);
uint16_t get_app_Quick_stop_option_code(void);
uint32_t set_app_start_upedge_state(bool val);
uint32_t set_app_Halt_running_cmd(uint8_t val);

#endif
