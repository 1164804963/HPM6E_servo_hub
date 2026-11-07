
#ifndef BSP_MEMORYMAP_H
#define BSP_MEMORYMAP_H

#include "bsp_flash.h"
#include "bsp_nor_flash.h"

#ifdef __cplusplus
extern "C" {
#endif


/************ Memory 分区 定义 ************/
// 片上 On Chip Flash 分区 定义
/************ BANK 1 ************/
// / ---------------- /
// /    BOOTLOADER    / 128K 0x20000    BOOT加载器区域，引导加载器固件
// /------------------/
// /    BOOTUSER      / 128K 0x20000    BOOT用户区域，固件信息、升级参数
// /------------------/
// /    RESERVED      / 256K 0x40000    保留区域，用于未来扩展
// /------------------/
/************ BANK 2 ************/
// / ---------------- /
// /       APP        / 512K 0x80000    应用运行区域，应用固件
// /------------------/
#define BSP_FLASH_INT_TOTAL_SIZE            (BSP_FLASH_TOTAL_SIZE)
#define BSP_FLASH_INT_BANK_SIZE             (BSP_FLASH_INT_TOTAL_SIZE >> 1)
#define BSP_FLASH_INT_SECTOR_SIZE           (BSP_FLASH_SECTOR_SIZE)

#define BSP_FLASH_INT_BASE_ADDR             (0x00000000)                // Flash 应用地址
#define BSP_FLASH_INT_BANK1_ADDR            (BSP_FLASH_INT_BASE_ADDR)   // BANK 1 应用地址
#define BSP_FLASH_INT_BANK2_ADDR            (BSP_FLASH_INT_BANK1_ADDR + \
                                             BSP_FLASH_INT_BANK_SIZE)   // BANK 2 应用地址（映射为连续地址）
// BANK 1 区域定义
#define BSP_FLASH_INT_BOOTLOADER_ADDR       (BSP_FLASH_INT_BANK1_ADDR)  // BOOT加载器区域地址
#define BSP_FLASH_INT_BOOTLOADER_SIZE       (0x20000)                   // BOOT加载器区域大小 128K
#define BSP_FLASH_INT_BOOTUSER_ADDR         (BSP_FLASH_INT_BOOTLOADER_ADDR + BSP_FLASH_INT_BOOTLOADER_SIZE) // BOOT用户区域地址
#define BSP_FLASH_INT_BOOTUSER_SIZE         (0x20000)                   // BOOT用户区域大小 128K
#define BSP_FLASH_INT_RESERVED_ADDR         (BSP_FLASH_INT_BOOTUSER_ADDR + BSP_FLASH_INT_BOOTUSER_SIZE) // 保留区域地址
#define BSP_FLASH_INT_RESERVED_SIZE         (0x40000)                   // 保留区域大小 256K
#if (BSP_FLASH_INT_RESERVED_ADDR - BSP_FLASH_INT_BOOTLOADER_ADDR + BSP_FLASH_INT_RESERVED_SIZE > BSP_FLASH_INT_BANK_SIZE)
#error ("on chip flash bank 1 map error!\r\n")
#endif
// BANK 2 区域定义
#define BSP_FLASH_INT_APP_ADDR              (BSP_FLASH_INT_BANK2_ADDR)  // 应用区域地址
#define BSP_FLASH_INT_APP_SIZE              (0x80000)                   // 应用区域大小 512K
#if (BSP_FLASH_INT_APP_SIZE > BSP_FLASH_INT_BANK_SIZE)
#error ("on chip flash bank 2 map error!\r\n")
#endif

// 片外 Nor Flash 分区 定义
// / ---------------- /
// /    APP_BACKUP    / 512K 0x80000    应用固件备份区域
// /------------------/
// /    APP_UPGRADE   / 512K 0x80000    应用固件升级区域
// /------------------/
// /    APP_CACHE    / 512K 0x80000    应用固件缓存区域，差分包缓存、临时数据
// /------------------/
// /    APP_USER      / 128K 0x20000    应用固件数据区域
// /------------------/
// /    RESERVED0     / 1536K 0x180000  保留区域0，用于未来扩展
// /------------------/
// /    FLASHDB_KV    / 2048K 0x200000  用户数据库区域
// /------------------/
// /    RESERVED1     / 2944K 0x2E0000  保留区域1，用于未来扩展
// / ---------------- /
#define BSP_FLASH_EXT_TOTAL_SIZE            (GD25Q64_TOTAL_SIZE)
#define BSP_FLASH_EXT_BLOCK_SIZE            (GD25Q64_BLOCK_64K_SIZE)
#define BSP_FLASH_EXT_SECTOR_SIZE           (GD25Q64_SECTOR_SIZE)
#define BSP_FLASH_EXT_PAGE_SIZE             (GD25Q64_PAGE_SIZE)

#define BSP_FLASH_EXT_BASE_ADDR             (GD25Q64_BASE_ADDR)

#define BSP_FLASH_EXT_APP_BACKUP_ADDR       (BSP_FLASH_EXT_BASE_ADDR)       // 应用固件备份区域地址
#define BSP_FLASH_EXT_APP_BACKUP_SIZE       (0x80000)                       // 应用固件备份区域大小 512K
#define BSP_FLASH_EXT_APP_UPGRADE_ADDR      (BSP_FLASH_EXT_APP_BACKUP_ADDR + BSP_FLASH_EXT_APP_BACKUP_SIZE) // 应用固件升级区域地址
#define BSP_FLASH_EXT_APP_UPGRADE_SIZE      (0x80000)                       // 应用固件升级区域大小 512K
#define BSP_FLASH_EXT_APP_CACHE_ADDR        (BSP_FLASH_EXT_APP_UPGRADE_ADDR + BSP_FLASH_EXT_APP_UPGRADE_SIZE) // 应用固件缓存区域地址
#define BSP_FLASH_EXT_APP_CACHE_SIZE        (0x80000)                       // 应用固件缓存区域大小 512K
#define BSP_FLASH_EXT_APP_USER_ADDR         (BSP_FLASH_EXT_APP_CACHE_ADDR + BSP_FLASH_EXT_APP_CACHE_SIZE) // 应用固件数据区域地址
#define BSP_FLASH_EXT_APP_USER_SIZE         (0x20000)                       // 应用固件数据区域大小 128K
#define BSP_FLASH_EXT_RESERVED0_ADDR        (BSP_FLASH_EXT_APP_USER_ADDR + BSP_FLASH_EXT_APP_USER_SIZE) // 保留区域0地址
#define BSP_FLASH_EXT_RESERVED0_SIZE        (0x180000)                      // 保留区域0大小 1536K
#define BSP_FLASH_EXT_FLASHDB_KV_ADDR       (BSP_FLASH_EXT_RESERVED0_ADDR + BSP_FLASH_EXT_RESERVED0_SIZE) // 用户数据库区域地址
#define BSP_FLASH_EXT_FLASHDB_KV_SIZE       (0x200000)                      // 用户数据库区域大小 2048K
#define BSP_FLASH_EXT_RESERVED1_ADDR        (BSP_FLASH_EXT_FLASHDB_KV_ADDR + BSP_FLASH_EXT_FLASHDB_KV_SIZE) // 保留区域1地址
#define BSP_FLASH_EXT_RESERVED1_SIZE        (0x2E0000)                      // 保留区域1大小 2944K
#if (BSP_FLASH_EXT_RESERVED1_ADDR - BSP_FLASH_EXT_BASE_ADDR + BSP_FLASH_EXT_RESERVED1_SIZE > BSP_FLASH_EXT_TOTAL_SIZE)
#error ("nor flash map error!\r\n")
#endif

#ifdef __cplusplus
}
#endif

#endif // BSP_MEMORYMAP_H
