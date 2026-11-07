#ifndef APP_BOOT_H
#define APP_BOOT_H

#include "bsp_memorymap.h"

#ifdef __cplusplus
extern "C" {
#endif

/*============================== 私有宏定义 ==============================*/
#define BOOT_ALIGN_BYTES            4U              /**< 地址及数据对齐字节数 */
#define BOOT_PARAMS_MAGIC           0x5A5AA5A5
#define BOOT_PARAMS_VERSION         0x00000001
#define BOOT_PARAMS_ADDR            BSP_FLASH_INT_BOOTUSER_ADDR
#define BOOT_PARAMS_SIZE            sizeof(BootParams_t)
#define CRC32_SIZE                  sizeof(uint32_t)
#define COPY_BUF_SIZE               GD25Q64_PAGE_SIZE  /* 256字节, 需4字节对齐 */

/** 启动模式（Bootloader使用） */
typedef enum {
    BOOT_MODE_ERR_TO_BACKUP     = 0xE2BCE2BC,   /**< 错误模式，从备份区拷贝到运行区启动 */
    BOOT_MODE_NORMAL            = 0x00000000,   /**< 运行区直接正常启动 */
    BOOT_MODE_UPG_TO_UPGRADE    = 0xAAAAAAAA,   /**< 从升级区拷贝到运行区启动 */
    BOOT_MODE_UPG_TO_BACKUP     = 0xBCBCBCBC    /**< 从备份区拷贝到运行区启动 */
} BootMode_t;

/** 固件信息结构体（对齐4字节） */
typedef struct __attribute__((aligned(BOOT_ALIGN_BYTES))) {
    uint32_t version;       /**< 版本号 */
    uint32_t addr;          /**< 存储地址 */
    uint32_t size;          /**< 固件大小（含末尾CRC） */
    uint32_t verify_val;    /**< CRC32校验值 */
} FwInfo_t;

/** 启动参数结构体(用于内部Flash BOOTUSER区域) ，修改需考虑兼容性，修改版本号，并同步到Bootloader */
typedef struct __attribute__((aligned(BOOT_ALIGN_BYTES))) {
    uint32_t magic;         /**< 魔数，验证有效性 */
    uint32_t version;       /**< 结构体版本 */
    BootMode_t boot_mode;   /**< 启动模式 */
    FwInfo_t running_fw;    /**< 当前运行固件信息 */
    FwInfo_t backup_fw;     /**< 外部备份区固件信息 */
    FwInfo_t upgrade_fw;    /**< 外部升级区固件信息 */
    uint32_t verify_val;    /**< 整个结构体CRC32(不含本字段) */
} BootParams_t;

/** LED控制宏定义 */
#define LED_ON_GPIO_LEVEL           (GPIO_PIN_RESET)
#define LED_OFF_GPIO_LEVEL          (!LED_ON_GPIO_LEVEL)

#define LED_RED_ON()                (HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, LED_ON_GPIO_LEVEL))
#define LED_RED_OFF()               (HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, LED_OFF_GPIO_LEVEL))
#define LED_RED_TOGGLE()            (HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin))
#define LED_BLUE_ON()               (HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, LED_ON_GPIO_LEVEL))
#define LED_BLUE_OFF()              (HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, LED_OFF_GPIO_LEVEL))
#define LED_BLUE_TOGGLE()           (HAL_GPIO_TogglePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin))

/*============================== 公共接口 ==============================*/
void boot_run(void);

#ifdef __cplusplus
}
#endif

#endif /* APP_BOOT_H */