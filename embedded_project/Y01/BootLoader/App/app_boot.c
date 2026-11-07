#include "app_boot.h"


/*============================== 私有全局变量 ==============================*/
static uint8_t s_boot_buf[COPY_BUF_SIZE] __attribute__((aligned(BOOT_ALIGN_BYTES)));

/*============================== 私有函数声明 ==============================*/
static int boot_verify_fw_ext(uint32_t addr, uint32_t size);
static int boot_verify_fw_int(uint32_t addr, uint32_t size);
static int boot_copy_ext_to_int(uint32_t src_addr, uint32_t dst_addr, uint32_t size);
static int boot_save_params(BootParams_t *params);
static bool boot_jump_to_app(uint32_t app_addr);

/*============================== 私有函数实现 ==============================*/

/**
 * @brief 校验外部Nor Flash中固件的CRC32
 * @param addr 固件起始地址(外部Nor Flash地址)
 * @param size 固件总大小(包含末尾CRC32, 需4字节对齐)
 * @return 0=校验通过, -1=失败
 */
static int boot_verify_fw_ext(uint32_t addr, uint32_t size)
{
    if (size <= CRC32_SIZE || (size % 4) != 0) {
        return -1;
    }

    uint32_t data_size = size - CRC32_SIZE;
    uint32_t target_crc = 0;

    if (bsp_nor_flash_read(addr + data_size, (uint8_t *)&target_crc, CRC32_SIZE) != CRC32_SIZE) {
        return -1;
    }

    __HAL_CRC_DR_RESET(&hcrc);

    uint32_t remain = data_size;
    uint32_t offset = 0;
    uint32_t calc_crc = 0;

    while (remain > 0) {
        uint32_t len = (remain > COPY_BUF_SIZE) ? COPY_BUF_SIZE : remain;
        if (bsp_nor_flash_read(addr + offset, s_boot_buf, len) != (int)len) {
            return -1;
        }
        calc_crc = HAL_CRC_Accumulate(&hcrc, (uint32_t *)s_boot_buf, len / CRC32_SIZE);
        offset += len;
        remain -= len;
    }

    return (calc_crc == target_crc) ? 0 : -1;
}

/**
 * @brief 校验内部Flash中固件的CRC32
 * @param addr 固件起始地址(内部Flash地址)
 * @param size 固件总大小(包含末尾CRC32, 需4字节对齐)
 * @return 0=校验通过, -1=失败
 */
static int boot_verify_fw_int(uint32_t addr, uint32_t size)
{
    if (size <= CRC32_SIZE || (size % 4) != 0) {
        return -1;
    }

    uint32_t data_size = size - CRC32_SIZE;
    uint32_t target_crc = 0;

    if (bsp_flash_read(addr + data_size, (uint8_t *)&target_crc, CRC32_SIZE) != CRC32_SIZE) {
        return -1;
    }

    __HAL_CRC_DR_RESET(&hcrc);

    uint32_t remain = data_size;
    uint32_t offset = 0;
    uint32_t calc_crc = 0;

    while (remain > 0) {
        uint32_t len = (remain > COPY_BUF_SIZE) ? COPY_BUF_SIZE : remain;
        if (bsp_flash_read(addr + offset, s_boot_buf, len) != (int)len) {
            return -1;
        }
        calc_crc = HAL_CRC_Accumulate(&hcrc, (uint32_t *)s_boot_buf, len / CRC32_SIZE);
        offset += len;
        remain -= len;
    }

    return (calc_crc == target_crc) ? 0 : -1;
}

/**
 * @brief 从外部Nor Flash拷贝固件到内部Flash
 * @param src_addr 源地址(外部Nor Flash地址, 需4字节对齐)
 * @param dst_addr 目标地址(内部Flash地址)
 * @param size 拷贝总大小(字节, 需32字节对齐)
 * @return 0=成功, -1=失败
 * @note  内部Flash先整体擦除, 再按32字节粒度写入(硬件要求)
 */
static int boot_copy_ext_to_int(uint32_t src_addr, uint32_t dst_addr, uint32_t size)
{
    if (size == 0 || (size % 4) != 0) {
        return -1;
    }

    /* 第一步: 擦除内部Flash目标区域 */
    if (bsp_flash_erase((long)dst_addr, size) != 0) {
        return -1;
    }

    /* 第二步: 分块读取Nor Flash并写入内部Flash */
    if (HAL_FLASH_Unlock() != HAL_OK) {
        return -1;
    }

    uint32_t src_off = 0;
    uint32_t dst_off = 0;
    uint32_t remain  = size;

    while (remain > 0) {
        uint32_t chunk = (remain > COPY_BUF_SIZE) ? COPY_BUF_SIZE : remain;

        if (bsp_nor_flash_read(src_addr + src_off, s_boot_buf, chunk) != (int)chunk) {
            HAL_FLASH_Lock();
            return -1;
        }

        /* 按32字节(FlashWord)粒度写入内部Flash */
        for (uint32_t i = 0; i < chunk; i += BSP_FLASH_PROG_GRANULARITY) {
            uint8_t prog_buf[BSP_FLASH_PROG_GRANULARITY];
            memset(prog_buf, 0, BSP_FLASH_PROG_GRANULARITY);
            memcpy(prog_buf, s_boot_buf + i,
                   (i + BSP_FLASH_PROG_GRANULARITY <= chunk)
                       ? BSP_FLASH_PROG_GRANULARITY
                       : (chunk - i));

            uint32_t phys_addr;
            if (dst_addr < BSP_FLASH_BANK_SIZE) {
                phys_addr = BSP_FLASH_BANK1_ADDR + dst_addr + dst_off + i;
            } else {
                phys_addr = BSP_FLASH_BANK2_ADDR + (dst_addr + dst_off + i - BSP_FLASH_BANK_SIZE);
            }

            if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_FLASHWORD,
                                  phys_addr, (uint32_t)(uintptr_t)prog_buf) != HAL_OK) {
                HAL_FLASH_Lock();
                return -1;
            }

            /* 写入校验 */
            for (uint32_t j = 0; j < BSP_FLASH_PROG_GRANULARITY; j++) {
                if (*(uint8_t *)(phys_addr + j) != prog_buf[j]) {
                    HAL_FLASH_Lock();
                    return -1;
                }
            }
        }

        src_off += chunk;
        dst_off += chunk;
        remain  -= chunk;
    }

    HAL_FLASH_Lock();
    return 0;
}

/**
 * @brief 保存启动参数到内部Flash(BOOTUSER区域)
 * @param params 待保存的参数指针
 * @return 0=成功, -1=失败
 */
static int boot_save_params(BootParams_t *params)
{
    params->verify_val = HAL_CRC_Calculate(&hcrc, (uint32_t *)params,
                                           (BOOT_PARAMS_SIZE - CRC32_SIZE) / CRC32_SIZE);
    if (bsp_flash_write(BOOT_PARAMS_ADDR, (uint8_t *)params, BOOT_PARAMS_SIZE) == BOOT_PARAMS_SIZE) {
        return 0;
    }
    return -1;
}

/**
 * @brief 跳转到应用程序
 * @param app_addr 应用程序起始地址(内部Flash)
 * @return true=成功, false=失败
 */
static bool boot_jump_to_app(uint32_t app_addr)
{
    uint32_t phys_app_addr;
    if (!flash_offset_to_phys(app_addr, &phys_app_addr)) {
        return false;
    }
    uint32_t sp = *(uint32_t *)phys_app_addr;
    uint32_t reset_handler = *(uint32_t *)(phys_app_addr + 4);

    /* 校验栈指针合法性(应在RAM区域内: 0x20000000 ~ 0x20020000) */
    if ((sp & 0x2FFE0000) != 0x20000000) {
        return false;
    }

    /* 禁用所有涉及到外设的中断 */
    SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;  // 关闭SysTick中断
    SysTick->CTRL = 0;
    SysTick->LOAD = 0;
    SysTick->VAL = 0;                            // 清当前值
    SCB->ICSR |= SCB_ICSR_PENDSTCLR_Msk;         // 清挂起标志

    /* 反初始化使用过的外设，交给APP重新初始化 */
    HAL_CRC_DeInit(&hcrc);
    FLASH_SPI_CS_DISABLE();          // 片选拉高，释放Flash
    HAL_SPI_DeInit(&AF_SPI_HANDLE);
    HAL_DeInit();

    /* 设置向量表偏移 */
    SCB->VTOR = app_addr;

    /* 设置栈指针 */
    __set_MSP(sp);
    __set_CONTROL(0);  /* 确保在特权模式下运行 */

    /* 跳转到复位处理函数 */
    ((void (*)(void))reset_handler)();

    return true;
}

/*============================== 公共接口实现 ==============================*/

/**
 * @brief Bootloader主逻辑入口
 * @note  上电后由main()调用, 根据启动参数决定启动路径
 */
void boot_run(void)
{
    BootParams_t params;

    /* 0. 初始化LED */
    LED_RED_OFF();
    LED_BLUE_ON();

    /* 1. 初始化Flash驱动 */
    bsp_flash_init();
    if (bsp_nor_flash_init() != 0) {
        /* Nor Flash初始化失败, 直接跳转运行区 */
        goto jump_to_app;
    }

    /* 2. 读取启动参数 */
    if (bsp_flash_read(BOOT_PARAMS_ADDR, (uint8_t *)&params, BOOT_PARAMS_SIZE) != BOOT_PARAMS_SIZE) {
        goto jump_to_app;
    }

    /* 3. 参数无效 → 直接跳转运行区 */
    if (params.magic != BOOT_PARAMS_MAGIC || params.version != BOOT_PARAMS_VERSION) {
        goto jump_to_app;
    }

    uint32_t crc = HAL_CRC_Calculate(&hcrc, (uint32_t *)&params,
                                     (BOOT_PARAMS_SIZE - CRC32_SIZE) / CRC32_SIZE);
    if (crc != params.verify_val) {
        goto jump_to_app;
    }

    /* 4~7. 根据启动模式执行不同路径 */
    switch (params.boot_mode) {

    /*-----------------------------------------------------------------*/
    /* 4. 升级模式: 外部升级区 → 内部运行区 */
    /*-----------------------------------------------------------------*/
    case BOOT_MODE_UPG_TO_UPGRADE:
        if (boot_verify_fw_ext(params.upgrade_fw.addr, params.upgrade_fw.size) == 0 &&
            boot_copy_ext_to_int(params.upgrade_fw.addr,
                                 BSP_FLASH_INT_APP_ADDR,
                                 params.upgrade_fw.size) == 0 &&
            boot_verify_fw_int(BSP_FLASH_INT_APP_ADDR, params.upgrade_fw.size) == 0) {

            params.running_fw = params.upgrade_fw;
            params.running_fw.addr = BSP_FLASH_INT_APP_ADDR;
            params.boot_mode = BOOT_MODE_NORMAL;
            boot_save_params(&params);
            goto jump_to_app;
        }
        /* 升级失败, 进入兜底路径(步骤7) */
        params.boot_mode = BOOT_MODE_ERR_TO_BACKUP;
        break;

    /*-----------------------------------------------------------------*/
    /* 5. 备份恢复模式: 外部备份区 → 内部运行区 */
    /*-----------------------------------------------------------------*/
    case BOOT_MODE_UPG_TO_BACKUP:
        // 7. 使用外部备份区固件恢复运行区
        params.boot_mode = BOOT_MODE_NORMAL;
        break;

    /*-----------------------------------------------------------------*/
    /* 6. 正常启动: 校验运行区固件, 通过则跳转 */
    /*-----------------------------------------------------------------*/
    case BOOT_MODE_NORMAL:
    default:
        if (boot_verify_fw_int(params.running_fw.addr, params.running_fw.size) == 0) {
            goto jump_to_app;
        }
        /* 运行区校验失败, 进入兜底路径(步骤7) */
        params.boot_mode = BOOT_MODE_ERR_TO_BACKUP;
        break;
    }

    /*================================================================-*/
    /* 7. 使用外部备份区固件恢复运行区 */
    /* TODO：在APP运行中报看门狗或其他固件异常时, 自动复位可直接进入此兜底路径 */
    /*================================================================-*/
    if (boot_verify_fw_ext(params.backup_fw.addr, params.backup_fw.size) == 0 &&
        boot_copy_ext_to_int(params.backup_fw.addr,
                             BSP_FLASH_INT_APP_ADDR,
                             params.backup_fw.size) == 0 &&
        boot_verify_fw_int(BSP_FLASH_INT_APP_ADDR, params.backup_fw.size) == 0) {

        params.running_fw = params.backup_fw;
        params.running_fw.addr = BSP_FLASH_INT_APP_ADDR;
        // params.boot_mode 由上述case设置
        boot_save_params(&params);
        if (!boot_jump_to_app(BSP_FLASH_INT_APP_ADDR)) {
            goto jump_to_app;
        }
    }

jump_to_app:
    // 所有路径均失败, 直接跳转运行区(变砖风险)
    boot_jump_to_app(BSP_FLASH_INT_APP_ADDR);
    /* 跳转失败后, 无法启动 提示错误 */
    while (1) {
        // ERR: 无法启动
        LED_BLUE_TOGGLE();
        LED_RED_TOGGLE();
        HAL_Delay(200);
    }
}
