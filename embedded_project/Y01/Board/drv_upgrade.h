#ifndef DRV_UPGRADE_H
#define DRV_UPGRADE_H

#include "board.h"
#include "bsp_memorymap.h"

#ifdef __cplusplus
extern "C" {
#endif

/*============================== 常量定义 ==============================*/
#define UPG_TIMEOUT_MS              (120 * 1000U)   /**< 升级超时时间(ms) */
#define UPG_ALIGN_BYTES             4U              /**< 地址及数据对齐字节数 */
#define UPG_MAX_RETRY               3U              /**< Flash写入最大重试次数 */

/* 固件传输相关 */
#define UPG_FRAME_DATA_MAX_LEN      256U                /**< 单帧最大数据长度(字节) */
#define UPG_FLASH_WRITE_SIZE        GD25Q64_PAGE_SIZE   /**< Flash单次写入大小(页大小) */
#define UPG_BUFFER_SIZE             (UPG_FLASH_WRITE_SIZE + UPG_FRAME_DATA_MAX_LEN) /**< 内部缓冲区大小 */
#if (UPG_BUFFER_SIZE % UPG_ALIGN_BYTES) != 0
#error "UPG_BUFFER_SIZE must be 4-byte aligned"
#endif

#define UPG_CRC32_SIZE              sizeof(uint32_t)    /**< CRC32校验值长度 */
#define UPG_CRC32_INVALID           0xFFFFFFFFU         /**< 无效CRC32值 */

/* Flash擦除/写入配置 */
#define FLASH_PART_INT              0                       /**< 内部Flash标识 */
#define FLASH_PART_EXT              1                       /**< 外部Nor Flash标识 */
#define FLASH_ERASE_SECTOR_SIZE     GD25Q64_SECTOR_SIZE     /**< 扇区大小(4KB) */
#define FLASH_ERASE_BLOCK_SIZE      GD25Q64_BLOCK_64K_SIZE  /**< 块大小(64KB) */

/* 启动参数结构体常量 */
#define BOOT_PARAMS_MAGIC           0x5A5AA5A5
#define BOOT_PARAMS_VERSION         0x00000001

/*============================== 枚举类型 ==============================*/
/** 启动模式（Bootloader使用） */
typedef enum {
    BOOT_MODE_ERR_TO_BACKUP     = 0xE2BCE2BC,   /**< 错误模式，从备份区拷贝到运行区启动 */
    BOOT_MODE_NORMAL            = 0x00000000,   /**< 运行区直接正常启动 */
    BOOT_MODE_UPG_TO_UPGRADE    = 0xAAAAAAAA,   /**< 从升级区拷贝到运行区启动 */
    BOOT_MODE_UPG_TO_BACKUP     = 0xBCBCBCBC    /**< 从备份区拷贝到运行区启动 */
} BootMode_t;

/** 固件分区索引（用于指示当前操作的区） */
typedef enum {
    UPG_APP_IDX_INVALID = 0,
    UPG_APP_IDX_CACHE   = 1,   /**< 缓存区（外部Flash） */
    UPG_APP_IDX_UPGRADE = 2,   /**< 升级区（外部Flash） */
    UPG_APP_IDX_BACKUP  = 3,   /**< 备份区（外部Flash） */
    UPG_APP_IDX_RUNNING = 4    /**< 运行区（内部Flash） */
} UpgradeAppIdx_t;

/** 升级操作模式 */
typedef enum {
    UPG_MODE_NONE    = 0x00,
    UPG_MODE_WRITE   = 0x01,   /**< 写入固件(升级) */
    UPG_MODE_READ    = 0x02,   /**< 读取固件(暂未实现) */
    UPG_MODE_BACKUP  = 0xBC    /**< 备份固件(内部→外部备份区) */
} UpgradeMode_t;

/** 升级状态码 */
typedef enum {
    UPG_STATE_ERR_TIMEOUT    = -7,  /**< 超时失败 */
    UPG_STATE_ERR_COPY       = -6,  /**< 拷贝失败 */
    UPG_STATE_ERR_READ       = -5,  /**< 读取失败 */
    UPG_STATE_ERR_WRITE      = -4,  /**< 写入/校验失败 */
    UPG_STATE_ERR_OVERSIZE   = -3,  /**< 文件大小超限 */
    UPG_STATE_ERR_PREPARE    = -2,  /**< 空间准备失败 */
    UPG_STATE_ERR_REQUEST    = -1,  /**< 请求参数无效 */
    UPG_STATE_IDLE           = 0,   /**< 空闲 */
    UPG_STATE_WRITE_REQUEST  = 1,   /**< 等待写入请求 */
    UPG_STATE_READ_REQUEST   = 2,   /**< 等待读取请求 */
    UPG_STATE_WRITING        = 3,   /**< 正在写入 */
    UPG_STATE_READING        = 4,   /**< 正在读取 */
    UPG_STATE_VERIFYING      = 5,   /**< 正在校验 */
    UPG_STATE_COPYING        = 6,   /**< 正在拷贝 */
    UPG_STATE_SUCCESS        = 7    /**< 操作成功 */
} UpgradeState_t;

/** 状态机步骤 */
typedef enum {
    UPG_STEP_IDLE = 0,
    UPG_STEP_INIT,
    UPG_STEP_PREPARE,

    /* 升级流程步骤 */
    UPG_STEP_DOWNLOAD_CACHE,
    UPG_STEP_VERIFY_CACHE,
    UPG_STEP_ERASE_UPGRADE,
    UPG_STEP_COPY_TO_UPGRADE,
    UPG_STEP_VERIFY_UPGRADE,

    /* 备份流程步骤 */
    UPG_STEP_BACKUP_COPY,
    UPG_STEP_BACKUP_VERIFY,

    /* 更新启动参数 */
    UPG_STEP_UPDATE_PARAM,
    /* 结束步骤 */
    UPG_STEP_SUCCESS,
    UPG_STEP_ERROR
} UpgradeStep_t;

/*============================== 结构体定义 ==============================*/
/** 固件信息结构体（对齐4字节） */
typedef struct __attribute__((aligned(UPG_ALIGN_BYTES))) {
    uint32_t version;       /**< 版本号 */
    uint32_t addr;          /**< 存储地址 */
    uint32_t size;          /**< 固件大小（含末尾CRC） */
    uint32_t verify_val;    /**< CRC32校验值 */
} FwInfo_t;

/** 启动参数结构体(用于内部Flash BOOTUSER区域) ，修改需考虑兼容性，修改版本号，并同步到Bootloader */
typedef struct __attribute__((aligned(UPG_ALIGN_BYTES))) {
    uint32_t magic;         /**< 魔数，验证有效性 */
    uint32_t version;       /**< 结构体版本 */
    BootMode_t boot_mode;   /**< 启动模式 */
    FwInfo_t running_fw;    /**< 当前运行固件信息 */
    FwInfo_t backup_fw;     /**< 外部备份区固件信息 */
    FwInfo_t upgrade_fw;    /**< 外部升级区固件信息 */
    uint32_t verify_val;    /**< 整个结构体CRC32(不含本字段) */
} BootParams_t;

/** 状态机控制块 */
typedef struct {
    UpgradeStep_t curr_step;    /**< 当前步骤 */
    UpgradeStep_t prev_step;    /**< 上一步骤(保留) */
    float timer_ms;             /**< 超时计时器 */
    uint8_t retry_cnt;          /**< 重试计数器(保留) */
} UpgradeFSM_t;

/** 升级模块上下文(全局单例) */
typedef struct __attribute__((aligned(UPG_ALIGN_BYTES))) {
    UpgradeFSM_t    fsm;            /**< 状态机 */
    UpgradeMode_t   mode;           /**< 当前操作模式 */
    UpgradeState_t  state;          /**< 当前状态码 */
    UpgradeAppIdx_t app_idx;        /**< 目标APP分区索引 */
    uint32_t        fw_addr;        /**< 当前操作的固件起始地址 */
    uint32_t        fw_size;        /**< 目标固件总大小(含CRC) */
    uint32_t        flash_max_size; /**< 当前操作区域最大容量 */
    uint32_t        written_size;   /**< 已写入字节数(累计) */
    uint16_t        frame_idx;      /**< 最后处理的帧索引 */
    uint8_t         buffer[UPG_BUFFER_SIZE]; /**< 数据缓冲区(同时用于读写) */
    uint16_t        buf_cnt;        /**< 缓冲区有效字节数 */
    uint32_t        calc_crc;       /**< 计算得到的CRC值(临时) */
} UpgradeCtx_t;

/*============================== 公共接口 ==============================*/
/**
 * @brief 升级模块初始化(内部Flash初始化 + 加载启动参数，应在系统早期调用)
 * @return 0=成功, -1=失败
 */
int drv_upgrade_init(void);

/**
 * @brief 升级模块运行函数(需周期性调用，例如每1ms)
 * @note 驱动状态机，处理超时和步骤跳转
 */
void drv_upgrade_run(void);

/**
 * @brief 设置升级操作模式
 * @param mode 操作模式(UPG_MODE_xxx)
 */
void drv_upgrade_set_mode(UpgradeMode_t mode);

/**
 * @brief 设置目标固件文件大小
 * @param size 固件大小(字节，包含末尾CRC32)
 */
void drv_upgrade_set_file_size(uint32_t size);

/**
 * @brief 写入固件数据帧(外部调用，提供分包数据)
 * @param index 帧序号(需严格递增，从1开始)
 * @param length 本帧数据长度
 * @param data 数据指针
 * @note 函数内部会进行缓存、对齐检查，写满缓冲区后自动写入Flash
 */
void drv_upgrade_write_data(uint16_t index, uint16_t length, const void *data);

/**
 * @brief 获取当前已接收的最后一帧序号
 * @return 帧序号
 */
uint16_t drv_upgrade_get_frame_index(void);

/**
 * @brief 获取当前目标APP分区索引
 * @return 分区索引(UPG_APP_IDX_xxx)
 */
int8_t drv_upgrade_get_app_index(void);

/**
 * @brief 获取当前操作区域的最大容量
 * @return 最大字节数
 */
uint32_t drv_upgrade_get_max_size(void);

/**
 * @brief 获取当前升级状态码
 * @return 状态码(UPG_STATE_xxx)
 */
UpgradeState_t drv_upgrade_get_state(void);

/**
 * @brief 转换为上层APP的文件传输状态
 * @return APP_FILE_STATUS枚举值
 */
APP_FILE_STATUS drv_upgrade_convert_status(void);

#ifdef __cplusplus
}
#endif

#endif /* DRV_UPGRADE_H */
