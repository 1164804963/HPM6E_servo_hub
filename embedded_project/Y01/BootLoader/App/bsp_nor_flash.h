#ifndef BSP_NOR_FLASH_H
#define BSP_NOR_FLASH_H

#include "main.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#define AF_SPI_HANDLE               (hspi3)
#define FLASH_SPI_HANDLE            (AF_SPI_HANDLE)
#define FLASH_SPI_CS_ENABLE()       (HAL_GPIO_WritePin(FLASH_AF_SPI_NSS_GPIO_Port, FLASH_AF_SPI_NSS_Pin, GPIO_PIN_RESET))
#define FLASH_SPI_CS_DISABLE()      (HAL_GPIO_WritePin(FLASH_AF_SPI_NSS_GPIO_Port, FLASH_AF_SPI_NSS_Pin, GPIO_PIN_SET))

#ifndef FAL_USING_NOR_FLASH_DEV_NAME
#define FAL_USING_NOR_FLASH_DEV_NAME    "norflash0"
#endif

/* Nor Flash GD25Q64ESIG 命令定义 */
#define GD25Q64_CMD_WRITE_ENABLE        0x06
#define GD25Q64_CMD_WRITE_DISABLE       0x04
#define GD25Q64_CMD_READ_STATUS_REG1    0x05
#define GD25Q64_CMD_READ_STATUS_REG2    0x35
#define GD25Q64_CMD_WRITE_STATUS_REG    0x01
#define GD25Q64_CMD_PAGE_PROGRAM        0x02
#define GD25Q64_CMD_QUAD_PAGE_PROGRAM   0x32
#define GD25Q64_CMD_READ_DATA           0x03
#define GD25Q64_CMD_FAST_READ           0x0B
#define GD25Q64_CMD_SECTOR_ERASE        0x20
#define GD25Q64_CMD_BLOCK_ERASE_32K     0x52
#define GD25Q64_CMD_BLOCK_ERASE_64K     0xD8
#define GD25Q64_CMD_CHIP_ERASE          0xC7
#define GD25Q64_CMD_POWER_DOWN          0xB9
#define GD25Q64_CMD_RELEASE_POWER_DOWN  0xAB
#define GD25Q64_CMD_READ_ID             0x9F

/* Nor Flash GD25Q64ESIG 参数 */
#define GD25Q64_PAGE_SIZE               256
#define GD25Q64_SECTOR_SIZE             4096
#define GD25Q64_BLOCK_32K_SIZE          (32 * 1024)
#define GD25Q64_BLOCK_64K_SIZE          (64 * 1024)
#define GD25Q64_TOTAL_SIZE              (8 * 1024 * 1024)

#define GD25Q64_BASE_ADDR               (0x00000000)

/* FlashDB 标准接口 */
int bsp_nor_flash_init(void);
int bsp_nor_flash_read(long offset, uint8_t *buf, size_t size);
int bsp_nor_flash_write(long offset, const uint8_t *buf, size_t size);
int bsp_nor_flash_erase(long offset, size_t size);
int bsp_nor_flash_erase_block_64k(long offset);

#ifdef __cplusplus
}
#endif

#endif /* BSP_NOR_FLASH_H */
