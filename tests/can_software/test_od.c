#include "master_cia402_callback.h"
#include "test_stubs.h"

#include <string.h>

uint32_t stub_od_value;
uint32_t stub_od_abort;
int stub_od_read_calls;
int stub_od_write_calls;
uint32_t stub_od_last_index;
uint8_t stub_od_last_subindex;
bool stub_od_last_host_entry;

uint32_t master_cia402_read_callback(uint16_t index, uint8_t subindex, void *data)
{
    stub_od_read_calls++;
    stub_od_last_index = index;
    stub_od_last_subindex = subindex;
    if (stub_od_abort != 0U)
    {
        return stub_od_abort;
    }
    *(uint32_t *)data = stub_od_value;
    return 0;
}

uint32_t master_cia402_write_callback_for(bool host_entry, uint16_t index, uint8_t subindex, void *data)
{
    stub_od_write_calls++;
    stub_od_last_host_entry = host_entry;
    stub_od_last_index = index;
    stub_od_last_subindex = subindex;
    if (stub_od_abort != 0U)
    {
        return stub_od_abort;
    }
    stub_od_value = *(uint32_t *)data;
    return 0;
}

uint32_t master_cia402_write_callback(uint16_t index, uint8_t subindex, void *data)
{
    return master_cia402_write_callback_for(false, index, subindex, data);
}
