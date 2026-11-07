#include "drv_upgrade.h"

/**
 * @file drv_upgrade.c
 * @brief 固件升级/备份模块实现
 * @details 实现基于状态机的固件升级与备份功能：
 *          - 升级模式：接收外部数据 -> 写入外部缓存区 -> CRC校验 -> 拷贝到升级区
 *          - 备份模式：将内部运行区固件拷贝到外部备份区
 *          - 所有Flash操作均支持重试和错误恢复
 */

/*============================== 私有宏定义 ==============================*/
#define MIN3(a,b,c)             ((a)<(b)?((a)<(c)?(a):(c)):((b)<(c)?(b):(c)))
#define BOOT_PARAMS_ADDR        BSP_FLASH_INT_BOOTUSER_ADDR
#define BOOT_PARAMS_SIZE        sizeof(BootParams_t)

/*============================== 私有全局变量 ==============================*/
static UpgradeCtx_t s_upg_ctx __attribute__((aligned(UPG_ALIGN_BYTES))) = {
    .fsm        = {0},
    .mode       = UPG_MODE_NONE,
    .state      = UPG_STATE_IDLE,
    .app_idx    = UPG_APP_IDX_INVALID,
    .fw_addr    = BSP_FLASH_EXT_APP_CACHE_ADDR,
    .fw_size    = 0,
    .flash_max_size = BSP_FLASH_INT_APP_SIZE,
    .written_size = 0,
    .buf_cnt    = 0,
    .calc_crc   = UPG_CRC32_INVALID,
};

static BootParams_t s_boot_params __attribute__((aligned(UPG_ALIGN_BYTES))) = {
    .magic      = BOOT_PARAMS_MAGIC,
    .version    = BOOT_PARAMS_VERSION,
    .boot_mode  = BOOT_MODE_NORMAL,
    .running_fw = {0},
    .backup_fw  = {0},
    .upgrade_fw = {0},
    .verify_val = UPG_CRC32_INVALID,
};

/*============================== 私有函数声明 ==============================*/
static bool is_size_valid(uint32_t size, uint32_t max_size);
static bool check_write_params(uint16_t index, uint16_t length, const void *data);
static void reset_write_ctx(void);
static UpgradeState_t init_ctx_by_mode(UpgradeMode_t mode);
static UpgradeState_t load_boot_params(void);
static UpgradeState_t save_boot_params(BootParams_t *params);
static UpgradeState_t erase_nor_flash_range(uint32_t addr, uint32_t max_size, uint32_t size);
static int8_t write_nor_flash_with_retry(uint32_t addr, const uint8_t *data, uint16_t len);
static UpgradeState_t copy_firmware(uint8_t src_part, uint32_t src_addr, uint32_t dst_addr, uint32_t size);
static bool verify_firmware_crc(uint32_t addr, uint32_t size);
static UpgradeState_t prepare_storage(UpgradeMode_t mode);
static void update_boot_params_for_upgrade(void);
static void update_boot_params_for_backup(void);
static void step_success_handler(void);
static void step_error_handler(void);
static UpgradeState_t step_init(void);
static UpgradeState_t step_prepare(void);
static UpgradeState_t step_download_cache(void);
static UpgradeState_t step_verify_cache(void);
static UpgradeState_t step_erase_upgrade(void);
static UpgradeState_t step_copy_to_upgrade(void);
static UpgradeState_t step_verify_upgrade(void);
static UpgradeState_t step_update_param(void);
static UpgradeState_t step_backup_copy(void);
static UpgradeState_t step_backup_verify(void);

/*============================== 基础辅助函数 ==============================*/
/**
 * @brief 检查文件大小是否有效(>0且不超过最大容量)
 */
static bool is_size_valid(uint32_t size, uint32_t max_size) {
    return (size > 0) && (size <= max_size);
}

/**
 * @brief 检查写入参数有效性(帧序号连续、数据合法、缓冲区不溢出)
 */
static bool check_write_params(uint16_t index, uint16_t length, const void *data) {
    if (index != s_upg_ctx.frame_idx + 1 || length == 0 || data == NULL) {
        return false;
    }
    if (s_upg_ctx.buf_cnt + length > sizeof(s_upg_ctx.buffer)) {
        return false;
    }
    return true;
}

/**
 * @brief 重置写入相关上下文(清空缓冲区、计数器等)
 */
static void reset_write_ctx(void) {
    s_upg_ctx.written_size = 0;
    s_upg_ctx.buf_cnt = 0;
    s_upg_ctx.frame_idx = 0;
    memset(s_upg_ctx.buffer, 0, sizeof(s_upg_ctx.buffer));
}

/*============================== Flash操作封装 ==============================*/
/**
 * @brief 擦除外部Nor Flash指定范围内的64K块(地址和长度需块对齐)
 * @param addr 起始地址(必须为64K块对齐)，外部Nor Flash地址
 * @param size 需要擦除的总大小(向上取整到64K倍数)
 * @return 成功返回UPG_STATE_SUCCESS，否则返回错误码
 */
static UpgradeState_t erase_nor_flash_range(uint32_t addr, uint32_t max_size, uint32_t size) {
    if (size == 0 || (addr & (FLASH_ERASE_BLOCK_SIZE - 1)) != 0) {
        return UPG_STATE_ERR_PREPARE;
    }

    uint32_t end_addr = addr + size;
    uint32_t aligned_end = ((end_addr + FLASH_ERASE_BLOCK_SIZE - 1) / 
                           FLASH_ERASE_BLOCK_SIZE) * FLASH_ERASE_BLOCK_SIZE;

    if ((aligned_end - addr) > max_size) {
        return UPG_STATE_ERR_PREPARE;
    }
    uint32_t block_cnt = (aligned_end - addr) / FLASH_ERASE_BLOCK_SIZE;

    for (uint32_t i = 0; i < block_cnt; i++) {
        uint32_t cur_addr = addr + i * FLASH_ERASE_BLOCK_SIZE;
        if (bsp_nor_flash_erase_block_64k(cur_addr) != 0) {
            return UPG_STATE_ERR_PREPARE;
        }
    }
    return UPG_STATE_SUCCESS;
}

/**
 * @brief 带重试机制的Nor Flash写入(若写入失败且地址为扇区对齐则尝试擦除后重写)
 * @param addr 目标地址(无需对齐，但建议页对齐)，外部Nor Flash地址
 * @param data 数据指针
 * @param len 数据长度(≤页大小)
 * @return 0成功，-1失败
 */
static int8_t write_nor_flash_with_retry(uint32_t addr, const uint8_t *data, uint16_t len) {
    for (uint8_t retry = 0; retry < UPG_MAX_RETRY; retry++) {
        if (bsp_nor_flash_write(addr, data, len) == len) {
            return 0;
        }
        // 仅在扇区起始地址且首次失败时尝试擦除
        if (retry == 0 && (addr & (FLASH_ERASE_SECTOR_SIZE - 1)) == 0) {
            if (bsp_nor_flash_erase(addr, len) != 0) {
                return -1;
            }
        }
    }
    return -1;
}

/**
 * @brief 将固件从源Flash拷贝到目标Nor Flash
 * @param src_part 源Flash类型(FLASH_PART_INT / FLASH_PART_EXT)
 * @param src_addr 源起始地址
 * @param dst_addr 目标起始地址(外部Nor Flash)
 * @param size 拷贝大小(字节)
 * @return 成功返回UPG_STATE_SUCCESS，否则错误码
 */
static UpgradeState_t copy_firmware(uint8_t src_part, uint32_t src_addr, uint32_t dst_addr, uint32_t size) {
    if (size == 0) {
        return UPG_STATE_ERR_COPY;
    }

    uint32_t offset = 0;
    uint32_t remain = size;
    const uint16_t buf_size = UPG_FLASH_WRITE_SIZE;

    while (remain > 0) {
        uint32_t len = (remain > buf_size) ? buf_size : remain;

        if (src_part == FLASH_PART_INT) {
            if (bsp_flash_read(src_addr + offset, s_upg_ctx.buffer, len) != len) {
                return UPG_STATE_ERR_READ;
            }
        } else {
            if (bsp_nor_flash_read(src_addr + offset, s_upg_ctx.buffer, len) != len) {
                return UPG_STATE_ERR_READ;
            }
        }

        if (write_nor_flash_with_retry(dst_addr + offset, s_upg_ctx.buffer, len) != 0) {
            return UPG_STATE_ERR_WRITE;
        }

        offset += len;
        remain -= len;
    }
    return UPG_STATE_SUCCESS;
}

/**
 * @brief 验证固件CRC32(固件末尾4字节为存储的目标CRC)
 * @param addr 固件起始地址(外部Nor Flash)
 * @param size 固件总大小(包含CRC值)
 * @return true: 校验通过; false: 失败
 */
static bool verify_firmware_crc(uint32_t addr, uint32_t size) {
    if (size < UPG_CRC32_SIZE || (size % UPG_ALIGN_BYTES) != 0) {
        return false;
    }

    uint32_t data_size = size - UPG_CRC32_SIZE;
    uint32_t target_crc = 0;

    // 读取末尾CRC值
    if (bsp_nor_flash_read(addr + data_size, (uint8_t *)&target_crc, UPG_CRC32_SIZE) != UPG_CRC32_SIZE) {
        return false;
    }

    __HAL_CRC_DR_RESET(&hcrc);

    uint32_t remain = data_size;
    uint32_t offset = 0;
    const uint16_t buf_size = UPG_FLASH_WRITE_SIZE;

    while (remain > 0) {
        uint32_t len = (remain > buf_size) ? buf_size : remain;
        if (bsp_nor_flash_read(addr + offset, s_upg_ctx.buffer, len) != len) {
            return false;
        }
        // 硬件CRC累加，按32位字计算
        s_upg_ctx.calc_crc = HAL_CRC_Accumulate(&hcrc, (uint32_t *)s_upg_ctx.buffer, len / UPG_CRC32_SIZE);
        offset += len;
        remain -= len;
    }

    return (s_upg_ctx.calc_crc == target_crc);
}

/*============================== 启动参数管理 ==============================*/
/**
 * @brief 从内部Flash加载启动参数，若无效则写入默认值
 */
static UpgradeState_t load_boot_params(void) {
    BootParams_t params = {0};
    if (bsp_flash_read(BOOT_PARAMS_ADDR, (uint8_t *)&params, BOOT_PARAMS_SIZE) != BOOT_PARAMS_SIZE) {
        return UPG_STATE_ERR_REQUEST;
    }

    // 检查魔数和版本
    if (params.magic != BOOT_PARAMS_MAGIC || params.version != BOOT_PARAMS_VERSION) {
        // 写入默认参数
        if (save_boot_params(&s_boot_params) == UPG_STATE_SUCCESS) {
            return UPG_STATE_SUCCESS;
        }
        return UPG_STATE_ERR_REQUEST;
    }

    // 校验CRC
    uint32_t crc32 = HAL_CRC_Calculate(&hcrc, (uint32_t *)&params,
                                       (BOOT_PARAMS_SIZE - UPG_CRC32_SIZE) / UPG_CRC32_SIZE);
    if (crc32 == params.verify_val) {
        memcpy(&s_boot_params, &params, BOOT_PARAMS_SIZE);
        // 判断是否已被动切换到备份固件
        if (s_boot_params.boot_mode == BOOT_MODE_ERR_TO_BACKUP) {
            // 报告警告提示，用户检查系统状态，并升级固件
        }
        return UPG_STATE_SUCCESS;
    }
    return UPG_STATE_ERR_REQUEST;
}

/**
 * @brief 保存当前启动参数到内部Flash
 */
static UpgradeState_t save_boot_params(BootParams_t *params) {
    params->verify_val = HAL_CRC_Calculate(&hcrc, (uint32_t *)params,
                                           (BOOT_PARAMS_SIZE - UPG_CRC32_SIZE) / UPG_CRC32_SIZE);
    if (bsp_flash_write(BOOT_PARAMS_ADDR, (uint8_t *)params, BOOT_PARAMS_SIZE) == BOOT_PARAMS_SIZE) {
        return UPG_STATE_SUCCESS;
    }
    return UPG_STATE_ERR_WRITE;
}

/*============================== 公共接口 ==============================*/
/**
 * @brief 升级模块初始化，将内部Flash初始化与启动参数加载提前完成
 * @return 0=成功, -1=失败
 * @note  应在系统初始化早期调用，避免每次切换模式时重复初始化
 */
int drv_upgrade_init(void) {
    if (bsp_flash_init() == 0 && \
        load_boot_params() == UPG_STATE_SUCCESS) {
        return 0;
    }
    return -1;
}

/*============================== 上下文初始化 ==============================*/
/**
 * @brief 根据操作模式初始化升级上下文
 * @param mode 操作模式
 * @return 状态码(UPG_STATE_WRITE_REQUEST 或 UPG_STATE_READ_REQUEST)
 */
static UpgradeState_t init_ctx_by_mode(UpgradeMode_t mode) {
    // 基础检查
    if (load_boot_params() != UPG_STATE_SUCCESS) {
        return UPG_STATE_ERR_REQUEST;
    }

    // 根据模式配置地址、大小等
    switch (mode) {
    case UPG_MODE_WRITE:
        s_upg_ctx.frame_idx = 0;
        s_upg_ctx.app_idx = UPG_APP_IDX_CACHE;
        s_upg_ctx.flash_max_size = MIN3(BSP_FLASH_EXT_APP_CACHE_SIZE,
                                        BSP_FLASH_EXT_APP_UPGRADE_SIZE,
                                        BSP_FLASH_INT_APP_SIZE);
        s_upg_ctx.fw_addr = BSP_FLASH_EXT_APP_CACHE_ADDR;
        break;

    case UPG_MODE_READ:
        s_upg_ctx.app_idx = UPG_APP_IDX_RUNNING;
        s_upg_ctx.flash_max_size = BSP_FLASH_INT_APP_SIZE;
        s_upg_ctx.fw_addr = BSP_FLASH_INT_APP_ADDR;
        s_upg_ctx.fw_size = s_boot_params.running_fw.size;
        break;

    case UPG_MODE_BACKUP:
        s_upg_ctx.app_idx = UPG_APP_IDX_BACKUP;
        s_upg_ctx.flash_max_size = BSP_FLASH_EXT_APP_BACKUP_SIZE;
        s_upg_ctx.fw_addr = BSP_FLASH_EXT_APP_BACKUP_ADDR;
        s_upg_ctx.fw_size = s_boot_params.running_fw.size;
        break;

    default:
        return UPG_STATE_ERR_REQUEST;
    }

    // 检查大小合法性(写入/备份模式)
    if ((mode == UPG_MODE_WRITE || mode == UPG_MODE_BACKUP) &&
        !is_size_valid(s_upg_ctx.fw_size, s_upg_ctx.flash_max_size)) {
        return UPG_STATE_ERR_OVERSIZE;
    }

    reset_write_ctx();
    return (mode == UPG_MODE_READ) ? UPG_STATE_READ_REQUEST : UPG_STATE_WRITE_REQUEST;
}

/**
 * @brief 准备存储空间(擦除目标区域)
 */
static UpgradeState_t prepare_storage(UpgradeMode_t mode) {
    if (mode != UPG_MODE_WRITE && mode != UPG_MODE_BACKUP) {
        return UPG_STATE_ERR_PREPARE;
    }
    // 确保地址是64K块对齐的
    if ((s_upg_ctx.fw_addr & (FLASH_ERASE_BLOCK_SIZE - 1)) != 0) {
        return UPG_STATE_ERR_PREPARE;
    }
    return erase_nor_flash_range(s_upg_ctx.fw_addr, s_upg_ctx.flash_max_size, s_upg_ctx.fw_size);
}

/*============================== 状态机步骤处理函数 ==============================*/
static void step_success_handler(void) {
    s_upg_ctx.mode = UPG_MODE_NONE;
    s_upg_ctx.state = UPG_STATE_SUCCESS;
    s_upg_ctx.fsm.curr_step = UPG_STEP_IDLE;   // 回到空闲
}

static void step_error_handler(void) {
    // 错误时保持当前状态，可由外部查询错误码后重新开始
    // 状态机停止计时，不再继续
}

static UpgradeState_t step_init(void) {
    UpgradeState_t state = init_ctx_by_mode(s_upg_ctx.mode);
    s_upg_ctx.state = state;
    if (state == UPG_STATE_WRITE_REQUEST) {
        s_upg_ctx.fsm.curr_step = UPG_STEP_PREPARE;
    } else if (state == UPG_STATE_READ_REQUEST) {
        // 读取模式暂未实现，直接错误
        s_upg_ctx.state = UPG_STATE_ERR_REQUEST;
        s_upg_ctx.fsm.curr_step = UPG_STEP_ERROR;
    } else {
        s_upg_ctx.state = UPG_STATE_ERR_REQUEST;
        s_upg_ctx.fsm.curr_step = UPG_STEP_ERROR;
    }
    return state;
}

static UpgradeState_t step_prepare(void) {
    UpgradeState_t state = prepare_storage(s_upg_ctx.mode);
    if (state == UPG_STATE_SUCCESS) {
        s_upg_ctx.state = UPG_STATE_WRITING;
        if (s_upg_ctx.mode == UPG_MODE_WRITE) {
            s_upg_ctx.fsm.curr_step = UPG_STEP_DOWNLOAD_CACHE;
        } else if (s_upg_ctx.mode == UPG_MODE_BACKUP) {
            s_upg_ctx.fsm.curr_step = UPG_STEP_BACKUP_COPY;
        }
    } else {
        s_upg_ctx.state = state;
        s_upg_ctx.fsm.curr_step = UPG_STEP_ERROR;
    }
    return state;
}

static UpgradeState_t step_download_cache(void) {
    // 此步骤依赖外部调用 drv_upgrade_write_data 填充数据
    // 当写入完成后，外部会设置 state 为 UPG_STATE_VERIFYING
    if (s_upg_ctx.state == UPG_STATE_VERIFYING) {
        s_upg_ctx.fsm.curr_step = UPG_STEP_VERIFY_CACHE;
    }
    return UPG_STATE_WRITING;  // 仍在等待
}

static UpgradeState_t step_verify_cache(void) {
    if (verify_firmware_crc(s_upg_ctx.fw_addr, s_upg_ctx.fw_size)) {
        s_upg_ctx.app_idx = UPG_APP_IDX_UPGRADE;
        s_upg_ctx.flash_max_size = BSP_FLASH_EXT_APP_UPGRADE_SIZE;
        s_upg_ctx.fw_addr = BSP_FLASH_EXT_APP_UPGRADE_ADDR;
        s_upg_ctx.state = UPG_STATE_COPYING;
        s_upg_ctx.fsm.curr_step = UPG_STEP_ERASE_UPGRADE;
    } else {
        s_upg_ctx.state = UPG_STATE_ERR_WRITE;
        s_upg_ctx.fsm.curr_step = UPG_STEP_ERROR;
    }
    return UPG_STATE_VERIFYING;
}

static UpgradeState_t step_erase_upgrade(void) {
    UpgradeState_t state = erase_nor_flash_range(s_upg_ctx.fw_addr, s_upg_ctx.flash_max_size, s_upg_ctx.fw_size);
    if (state == UPG_STATE_SUCCESS) {
        reset_write_ctx();
        s_upg_ctx.state = UPG_STATE_COPYING;
        s_upg_ctx.fsm.curr_step = UPG_STEP_COPY_TO_UPGRADE;
    } else {
        s_upg_ctx.state = UPG_STATE_ERR_COPY;
        s_upg_ctx.fsm.curr_step = UPG_STEP_ERROR;
    }
    return state;
}

static UpgradeState_t step_copy_to_upgrade(void) {
    UpgradeState_t state = copy_firmware(FLASH_PART_EXT, BSP_FLASH_EXT_APP_CACHE_ADDR,
                                         s_upg_ctx.fw_addr, s_upg_ctx.fw_size);
    if (state == UPG_STATE_SUCCESS) {
        s_upg_ctx.state = UPG_STATE_COPYING;
        s_upg_ctx.fsm.curr_step = UPG_STEP_VERIFY_UPGRADE;
    } else {
        s_upg_ctx.state = UPG_STATE_ERR_COPY;
        s_upg_ctx.fsm.curr_step = UPG_STEP_ERROR;
    }
    return state;
}

static UpgradeState_t step_verify_upgrade(void) {
    if (verify_firmware_crc(s_upg_ctx.fw_addr, s_upg_ctx.fw_size)) {
        s_upg_ctx.state = UPG_STATE_COPYING;
        s_upg_ctx.fsm.curr_step = UPG_STEP_UPDATE_PARAM;
    } else {
        s_upg_ctx.state = UPG_STATE_ERR_COPY;
        s_upg_ctx.fsm.curr_step = UPG_STEP_ERROR;
    }
    return UPG_STATE_VERIFYING;
}

static void update_boot_params_for_upgrade(void) {
    s_boot_params.boot_mode = BOOT_MODE_UPG_TO_UPGRADE;
    s_boot_params.upgrade_fw.version = 0;
    s_boot_params.upgrade_fw.addr = s_upg_ctx.fw_addr;
    s_boot_params.upgrade_fw.size = s_upg_ctx.fw_size;
    s_boot_params.upgrade_fw.verify_val = s_upg_ctx.calc_crc;  // 最后一次校验的计算值
}

static void update_boot_params_for_backup(void) {
    s_boot_params.backup_fw.version = 0;
    s_boot_params.backup_fw.addr = s_upg_ctx.fw_addr;
    s_boot_params.backup_fw.size = s_upg_ctx.fw_size;
    s_boot_params.backup_fw.verify_val = s_upg_ctx.calc_crc;
}

static UpgradeState_t step_update_param(void) {
    if (s_upg_ctx.mode == UPG_MODE_WRITE) {
        update_boot_params_for_upgrade();
    } else if (s_upg_ctx.mode == UPG_MODE_BACKUP) {
        update_boot_params_for_backup();
    } else {
        s_upg_ctx.state = UPG_STATE_ERR_REQUEST;
        s_upg_ctx.fsm.curr_step = UPG_STEP_ERROR;
        return UPG_STATE_ERR_REQUEST;
    }

    UpgradeState_t state = save_boot_params(&s_boot_params);
    if (state == UPG_STATE_SUCCESS) {
        s_upg_ctx.state = UPG_STATE_SUCCESS;
        s_upg_ctx.fsm.curr_step = UPG_STEP_SUCCESS;
    } else {
        s_upg_ctx.state = UPG_STATE_ERR_COPY;
        s_upg_ctx.fsm.curr_step = UPG_STEP_ERROR;
    }
    return state;
}

static UpgradeState_t step_backup_copy(void) {
    UpgradeState_t state = copy_firmware(FLASH_PART_INT, BSP_FLASH_INT_APP_ADDR,
                                         s_upg_ctx.fw_addr, s_upg_ctx.fw_size);
    if (state == UPG_STATE_SUCCESS) {
        s_upg_ctx.state = UPG_STATE_COPYING;
        s_upg_ctx.fsm.curr_step = UPG_STEP_BACKUP_VERIFY;
    } else {
        s_upg_ctx.state = UPG_STATE_ERR_COPY;
        s_upg_ctx.fsm.curr_step = UPG_STEP_ERROR;
    }
    return state;
}

static UpgradeState_t step_backup_verify(void) {
    if (verify_firmware_crc(s_upg_ctx.fw_addr, s_upg_ctx.fw_size)) {
        s_upg_ctx.state = UPG_STATE_COPYING;
        s_upg_ctx.fsm.curr_step = UPG_STEP_UPDATE_PARAM;  // 复用更新参数步骤
    } else {
        s_upg_ctx.state = UPG_STATE_ERR_COPY;
        s_upg_ctx.fsm.curr_step = UPG_STEP_ERROR;
    }
    return UPG_STATE_VERIFYING;
}

/*============================== 状态机调度器 ==============================*/
static void fsm_step_switch(UpgradeStep_t new_step) {
    s_upg_ctx.fsm.prev_step = s_upg_ctx.fsm.curr_step;
    s_upg_ctx.fsm.curr_step = new_step;
    s_upg_ctx.fsm.timer_ms = 0;
}

/**
 * @brief 状态机主调度函数(需周期性调用)
 */
static void fsm_scheduler(void) {
    // 超时检测(全局)，大都为阻塞式任务检测没有意义
    if (s_upg_ctx.fsm.timer_ms > UPG_TIMEOUT_MS) {
        s_upg_ctx.state = UPG_STATE_ERR_TIMEOUT;
        s_upg_ctx.fsm.curr_step = UPG_STEP_ERROR;
    }

    switch (s_upg_ctx.fsm.curr_step) {
    case UPG_STEP_IDLE:
        s_upg_ctx.fsm.timer_ms = 0;
        if (s_upg_ctx.mode != UPG_MODE_NONE) {
            fsm_step_switch(UPG_STEP_INIT);
        }
        break;
    case UPG_STEP_INIT:
        (void)step_init();
        break;
    case UPG_STEP_PREPARE:
        (void)step_prepare();
        break;
    case UPG_STEP_DOWNLOAD_CACHE:
        (void)step_download_cache();
        break;
    case UPG_STEP_VERIFY_CACHE:
        (void)step_verify_cache();
        break;
    case UPG_STEP_ERASE_UPGRADE:
        (void)step_erase_upgrade();
        break;
    case UPG_STEP_COPY_TO_UPGRADE:
        (void)step_copy_to_upgrade();
        break;
    case UPG_STEP_VERIFY_UPGRADE:
        (void)step_verify_upgrade();
        break;
    case UPG_STEP_UPDATE_PARAM:
        (void)step_update_param();
        break;
    case UPG_STEP_BACKUP_COPY:
        (void)step_backup_copy();
        break;
    case UPG_STEP_BACKUP_VERIFY:
        (void)step_backup_verify();
        break;
    case UPG_STEP_SUCCESS:
        step_success_handler();
        break;
    case UPG_STEP_ERROR:
        step_error_handler();
        break;
    default:
        break;
    }

    s_upg_ctx.fsm.timer_ms += 1;  // 假定调用间隔1ms
    set_app_Fw_operating_steps(s_upg_ctx.state);  // 外部通知
}

/*============================== 公共接口实现 ==============================*/
void drv_upgrade_run(void) {
    fsm_scheduler();
}

void drv_upgrade_set_mode(UpgradeMode_t mode) {
    if (mode != s_upg_ctx.mode) {
        s_upg_ctx.mode = mode;
        fsm_step_switch(UPG_STEP_INIT);
    }
}

void drv_upgrade_set_file_size(uint32_t size) {
    s_upg_ctx.fw_size = size;
}

void drv_upgrade_write_data(uint16_t index, uint16_t length, const void *data) {
    if (s_upg_ctx.state != UPG_STATE_WRITING) {
        s_upg_ctx.state = UPG_STATE_ERR_WRITE;
        return;
    }

    if (!check_write_params(index, length, data)) {
        s_upg_ctx.state = UPG_STATE_ERR_WRITE;
        return;
    }

    // 缓存数据
    memcpy(&s_upg_ctx.buffer[s_upg_ctx.buf_cnt], data, length);
    s_upg_ctx.buf_cnt += length;

    // 确定本次写入Flash的数据长度
    uint16_t write_remain = 0;

    // 最后一包数据，需检查对齐
    if (s_upg_ctx.written_size + s_upg_ctx.buf_cnt >= s_upg_ctx.fw_size) {
        if (s_upg_ctx.buf_cnt % UPG_ALIGN_BYTES != 0) {
            s_upg_ctx.state = UPG_STATE_ERR_WRITE;
            return;
        }
        write_remain = s_upg_ctx.buf_cnt;
    }
    else if (s_upg_ctx.buf_cnt >= UPG_FLASH_WRITE_SIZE) {
        write_remain = UPG_FLASH_WRITE_SIZE;
    }

    while (write_remain) {
        uint16_t write_len = write_remain;
        if (write_len > UPG_FLASH_WRITE_SIZE) {
            write_len = UPG_FLASH_WRITE_SIZE;
            write_remain -= write_len;
        }
        else {
            write_remain = 0;
        }
        s_upg_ctx.buf_cnt -= write_len;

        uint32_t write_addr = s_upg_ctx.fw_addr + s_upg_ctx.written_size;
        if (write_nor_flash_with_retry(write_addr, s_upg_ctx.buffer, write_len) != 0) {
            s_upg_ctx.state = UPG_STATE_ERR_WRITE;
            return;
        }
        s_upg_ctx.written_size += write_len;
        if (s_upg_ctx.buf_cnt > 0) {
            memmove(s_upg_ctx.buffer, &s_upg_ctx.buffer[write_len], s_upg_ctx.buf_cnt);
        }
    }

    // 完成全部写入时切换到校验状态
    if (s_upg_ctx.written_size >= s_upg_ctx.fw_size) {
        s_upg_ctx.state = UPG_STATE_VERIFYING;
    }

    s_upg_ctx.frame_idx = index;
}

uint16_t drv_upgrade_get_frame_index(void) {
    return s_upg_ctx.frame_idx;
}

int8_t drv_upgrade_get_app_index(void) {
    return s_upg_ctx.app_idx;
}

uint32_t drv_upgrade_get_max_size(void) {
    return s_upg_ctx.flash_max_size;
}

UpgradeState_t drv_upgrade_get_state(void) {
    return s_upg_ctx.state;
}

APP_FILE_STATUS drv_upgrade_convert_status(void) {
    if (s_upg_ctx.state < UPG_STATE_IDLE) {
        return APP_FILE_STATUS_TRANSFER_ERR;
    } else if (s_upg_ctx.state <= UPG_STATE_READ_REQUEST) {
        return APP_FILE_STATUS_IDLE;
    } else if (s_upg_ctx.state == UPG_STATE_SUCCESS) {
        return APP_FILE_STATUS_SUCCESS;
    }
    return APP_FILE_STATUS_BUSY;
}
