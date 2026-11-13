#ifndef SERVO_FAL_CFG_H
#define SERVO_FAL_CFG_H
/* Offsets from XPI0 base. 2MiB SII + 64KiB; historic records at 0x210000
 * are preserved. Only 0x240000..0x27ffff belongs to this KV database. */
#define SERVO_KV_OFFSET 0x240000U
#define SERVO_KV_SIZE   0x40000U
#define SERVO_FLASH_SECTOR 0x1000U
#define FAL_PART_HAS_TABLE_CFG
#define FAL_DEBUG 0
#define FAL_PRINTF(...) ((void)0)
extern struct fal_flash_dev servo_nor;
#define FAL_FLASH_DEV_TABLE { &servo_nor }
#define FAL_PART_TABLE { {FAL_PART_MAGIC_WORD, "servo_kv", "servo_nor", 0, SERVO_KV_SIZE, 0} }
#endif
