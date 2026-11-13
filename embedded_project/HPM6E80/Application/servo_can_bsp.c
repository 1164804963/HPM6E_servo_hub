/* Portable BSP compatibility entry points implemented by the CAN app adapter. */
#include "bsp_api.h"
#include "servo_can.h"
#include "servo_debug_can.h"
bool bsp_can_port_is_ready(bool debug_port)
{
    return debug_port ? servo_debug_can_is_ready() : servo_can_is_ready();
}
void bsp_set_can_id(uint32_t can_id)
{
    (void)servo_can_request_node_id(can_id);
}

uint32_t bsp_get_can_id(void)
{
    return servo_can_applied_node_id();
}

void bsp_set_can_baudrate(uint32_t baudrate)
{
    (void)servo_can_request_bitrate(baudrate);
}

uint32_t bsp_get_can_baudrate(void)
{
    return servo_can_applied_bitrate();
}

uint32_t bsp_get_can_mg_counts(void)
{
    return servo_can_rx_count();
}
