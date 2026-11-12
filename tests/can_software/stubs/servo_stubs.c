#include "bsp_api.h"
#include "data_param.h"
#include "Cia402_ObjectDictionary_Variable.h"
#include "test_stubs.h"

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
    return 0;
}

uint32_t set_Controlword(uint16_t val)
{
    stub_last_set_controlword = val;
    stub_set_controlword_calls++;
    return 0;
}

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
