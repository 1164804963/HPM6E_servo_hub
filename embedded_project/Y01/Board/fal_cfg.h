/*
 * Copyright (c) 2020, Armink, <armink.ztl@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _FAL_CFG_H_
#define _FAL_CFG_H_

#include "bsp_memorymap.h"

#define FAL_DEBUG 0
#define FAL_PART_HAS_TABLE_CFG

/* ===================== Flash device Configuration ========================= */
extern struct fal_flash_dev nor_flash0;

/* the flash write granularity, unit: bit
 * only support 1(nor flash)/ 8(stm32f2/f4)/ 32(stm32f1)/ 64(stm32f7)/ 128(stm32h5) */
#define FDB_WRITE_GRAN        1        /* @note you must define it for a value */

/* flash device table */
#define FAL_FLASH_DEV_TABLE     \
{                               \
    &nor_flash0,                \
}

/* ====================== Partition Configuration ========================== */
#ifdef FAL_PART_HAS_TABLE_CFG
/* partition table */
#define FAL_PART_TABLE                                                                                              \
{                                                                                                                   \
    {FAL_PART_MAGIC_WORD,  "app_backup",  "norflash0",  BSP_FLASH_EXT_APP_BACKUP_ADDR,    BSP_FLASH_EXT_APP_BACKUP_SIZE,  0}, \
    {FAL_PART_MAGIC_WORD, "app_upgrade",  "norflash0",  BSP_FLASH_EXT_APP_UPGRADE_ADDR,   BSP_FLASH_EXT_APP_UPGRADE_SIZE, 0}, \
    {FAL_PART_MAGIC_WORD,  "app_buffer",  "norflash0",  BSP_FLASH_EXT_APP_CACHE_ADDR,     BSP_FLASH_EXT_APP_CACHE_SIZE,   0}, \
    {FAL_PART_MAGIC_WORD,    "app_user",  "norflash0",  BSP_FLASH_EXT_APP_USER_ADDR,      BSP_FLASH_EXT_APP_USER_SIZE,    0}, \
    {FAL_PART_MAGIC_WORD,   "reserved0",  "norflash0",  BSP_FLASH_EXT_RESERVED0_ADDR,     BSP_FLASH_EXT_RESERVED0_SIZE,   0}, \
    {FAL_PART_MAGIC_WORD,  "flashdb_kv",  "norflash0",  BSP_FLASH_EXT_FLASHDB_KV_ADDR,    BSP_FLASH_EXT_FLASHDB_KV_SIZE,  0}, \
    {FAL_PART_MAGIC_WORD,   "reserved1",  "norflash0",  BSP_FLASH_EXT_RESERVED1_ADDR,     BSP_FLASH_EXT_RESERVED1_SIZE,   0}, \
}
#endif /* FAL_PART_HAS_TABLE_CFG */

/* PRINTF NOT USED */
#define FAL_PRINTF(...)              /* nothing */

#endif /* _FAL_CFG_H_ */
