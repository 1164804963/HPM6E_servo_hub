#ifndef MASTER_CIA402_CALLBACK_H
#define MASTER_CIA402_CALLBACK_H

#include <stdint.h>

uint32_t master_cia402_read_callback(uint16_t index, uint8_t subindex, void *data);
uint32_t master_cia402_write_callback(uint16_t index, uint8_t subindex, void *data);

#endif /* MASTER_CIA402_CALLBACK_H */
