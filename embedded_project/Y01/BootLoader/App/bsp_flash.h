#ifndef BSP_FLASH_H
#define BSP_FLASH_H

#include "main.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

/* STM32H743VGT6 Flash 配置 */
// #define BSP_FLASH_TOTAL_SIZE            (FLASH_SIZE)
#define BSP_FLASH_TOTAL_SIZE            (1 * 1024 * 1024)
// #define BSP_FLASH_BANK_SIZE             (FLASH_BANK_SIZE)
#define BSP_FLASH_BANK_SIZE             (BSP_FLASH_TOTAL_SIZE >> 1)
#define BSP_FLASH_SECTOR_SIZE           (FLASH_SECTOR_SIZE)

#define BSP_FLASH_BASE_ADDR             (FLASH_BASE)        // Flash 基地址
#define BSP_FLASH_BANK1_ADDR            (FLASH_BANK1_BASE)  // BANK 1 基地址
#define BSP_FLASH_BANK2_ADDR            (FLASH_BANK2_BASE)  // BANK 2 基地址

#define BSP_FLASH_PROG_GRANULARITY      32U    // 编程粒度32字节
#define BSP_FLASH_ADDR_ALIGNMENT        4U     // 地址4字节对齐

bool flash_offset_to_phys(long offset, uint32_t *phys_addr);

int bsp_flash_init(void);
int bsp_flash_read(long offset, uint8_t *buf, size_t size);
int bsp_flash_write(long offset, const uint8_t *buf, size_t size);
int bsp_flash_erase(long offset, size_t size);

#ifdef __cplusplus
}
#endif

#endif /* BSP_FLASH_H */
