#include "Cia402_ObjectDictionary_Callback.h"

extern UNS32 master_cia402_read_callback(uint16_t index, uint8_t subindex, void *data);
extern UNS32 master_cia402_write_callback(uint16_t index, uint8_t subindex, void *data);

UNS32 SlaveOD_Read_Callback(uint16_t index, uint8_t subindex, void *data)
{
    return master_cia402_read_callback(index, subindex, data);
}

UNS32 SlaveOD_Write_Callback(uint16_t index, uint8_t subindex, void *data)
{
    return master_cia402_write_callback(index, subindex, data);
}
