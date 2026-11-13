#include "bsp_api.h"
#include "data_param.h"
#include "Cia402_ObjectDictionary_Variable.h"
#include "test_stubs.h"

bool stub_physical_fault;
uint16_t stub_error_code;
int stub_error_set_calls;
int stub_error_clear_calls;
int stub_app_controlword_calls;
uint16_t stub_last_app_controlword;
int stub_set_controlword_calls;
uint16_t stub_last_set_controlword;

uint32_t set_app_Controlword(uint16_t val)
{
    stub_app_controlword_calls++;
    stub_last_app_controlword = val;
    if (val == APP_CTRL_CLEAR_ERROR && !stub_physical_fault) { stub_error_code = 0U; }
    return 0;
}

uint32_t set_Controlword(uint16_t val)
{
    stub_last_set_controlword = val;
    stub_set_controlword_calls++;
    return 0;
}

uint32_t bsp_irq_save(void) { return 0U; }
void bsp_irq_restore(uint32_t state) { (void)state; }
PDS_FSA kPDS_FSA;
bool stub_emergency_brake_requested;

uint16_t get_Controlword(void) { return kPDS_FSA.Controlword; }
uint16_t get_Statusword(void) { return kPDS_FSA.Statusword; }
uint32_t set_Statusword(uint16_t val) { kPDS_FSA.Statusword = val; return 0; }
uint16_t get_Error_code(void) { return stub_error_code; }
uint32_t set_Error_code(uint16_t val) { stub_error_code = val; return 0; }
int16_t get_Quick_stop_option_code(void) { return 0; }

bool get_app_Emergency_brake_requested(void) { return stub_emergency_brake_requested; }
uint32_t set_app_start_upedge_state(bool val) { (void)val; return 0; }
uint32_t set_app_Halt_running_cmd(uint8_t val) { (void)val; return 0; }
bool get_velocity_zero_state(void) { return false; }

void sys_set_bsp_error_state(BSP_ERROR_CODE type, BSP_ERROR_OPERATION op)
{
    (void)type;
    if (op == ERROR_SET)
    {
        stub_error_set_calls++;
    }
    else
    {
        stub_error_clear_calls++;
    }
}
