#ifndef DRV_NOR_FLASH_H
#define DRV_NOR_FLASH_H

#include <flashdb.h>
#include "board.h"

#ifdef __cplusplus
extern "C" {
#endif

FLASHDB_STATUS flashdb_init(void);
FLASHDB_STATUS flashdb_read(FLASHDB_KEY_INDEX const index);
FLASHDB_STATUS flashdb_write(FLASHDB_KEY_INDEX const index);
FLASHDB_STATUS flashdb_key_register(FLASHDB_KEY_INDEX const index, char *key, void *value, size_t value_len);
FLASHDB_STATUS flashdb_key_delete(FLASHDB_KEY_INDEX const index);

#ifdef __cplusplus
}
#endif

#endif /* DRV_NOR_FLASH_H */
