#include "bsp_flash.h"
#include "main.h"

static bool flash_offset_to_phys(long offset, uint32_t *phys_addr);
static bool flash_get_bank_sector(long offset, uint32_t *bank, uint32_t *sector);
static bool flash_check_param(long offset, size_t size);

/**
 * @brief  Flash初始化（无额外硬件步骤）
 * @retval 0=成功，-1=失败
 */
int bsp_flash_init(void)
{
    return 0;
}

/**
 * @brief  从指定逻辑偏移读取数据
 * @param  offset: 起始逻辑偏移
 * @param  buf: 接收缓冲区
 * @param  size: 读取长度
 * @retval  实际读取的字节数, -1：失败
 */
int bsp_flash_read(long offset, uint8_t *buf, size_t size)
{
    if (!flash_check_param(offset, size) || buf == NULL)
    {
        return -1;
    }

    uint32_t phys_addr;
    uint8_t *p_dst = buf;
    size_t remain = size;
    long current_offset = offset;

    if (HAL_FLASH_Unlock() != HAL_OK)
    {
        return -1;
    }

    while (remain > 0)
    {
        // 每次转换当前偏移的物理地址（自动处理跨Bank）
        if (!flash_offset_to_phys(current_offset, &phys_addr))
        {
            HAL_FLASH_Lock();
            return -1;
        }

        // 计算当前Bank内可连续读取的最大长度
        size_t chunk_size;
        if (current_offset < BSP_FLASH_BANK_SIZE)
        {
            chunk_size = BSP_FLASH_BANK_SIZE - current_offset;
        }
        else
        {
            chunk_size = BSP_FLASH_TOTAL_SIZE - current_offset;
        }
        chunk_size = (chunk_size > remain) ? remain : chunk_size;

        // 连续读取当前Bank内的数据
        for (size_t i = 0; i < chunk_size; i++)
        {
            p_dst[i] = *(uint8_t *)(phys_addr + i);
        }

        // 更新指针和偏移
        p_dst += chunk_size;
        current_offset += chunk_size;
        remain -= chunk_size;
    }
    HAL_FLASH_Lock();

    return size;
}

/**
 * @brief  擦除指定逻辑偏移区域（自动处理跨Bank）
 * @param  offset: 起始逻辑偏移
 * @param  size: 擦除长度
 * @retval 0=成功，-1=失败
 */
int bsp_flash_erase(long offset, size_t size)
{
    if (!flash_check_param(offset, size))
    {
        return -1;
    }

    FLASH_EraseInitTypeDef erase_cfg;
    uint32_t sector_error = 0;
    uint32_t bank, start_sector, end_sector;
    long current_offset = offset;
    size_t remain_size = size;

    if (HAL_FLASH_Unlock() != HAL_OK)
    {
        return -1;
    }

    // 循环处理每个Bank的擦除（支持跨Bank）
    while (remain_size > 0)
    {
        // 获取当前偏移所在的Bank和起始扇区
        if (!flash_get_bank_sector(current_offset, &bank, &start_sector))
        {
            HAL_FLASH_Lock();
            return -1;
        }

        // 计算当前Bank内需要擦除的结束扇区
        long bank_end_offset;
        if (bank == FLASH_BANK_1)
        {
            bank_end_offset = BSP_FLASH_BANK_SIZE - 1;
        }
        else
        {
            bank_end_offset = BSP_FLASH_TOTAL_SIZE - 1;
        }

        long end_offset = current_offset + remain_size - 1;
        if (end_offset > bank_end_offset)
        {
            end_offset = bank_end_offset;
        }

        if (!flash_get_bank_sector(end_offset, &bank, &end_sector))
        {
            HAL_FLASH_Lock();
            return -1;
        }

        // 配置擦除参数
        erase_cfg.TypeErase = FLASH_TYPEERASE_SECTORS;
        erase_cfg.Banks = bank;
        erase_cfg.Sector = start_sector;
        erase_cfg.NbSectors = end_sector - start_sector + 1;
        erase_cfg.VoltageRange = FLASH_VOLTAGE_RANGE_4;

        // 执行当前Bank的擦除
        if (HAL_FLASHEx_Erase(&erase_cfg, &sector_error) != HAL_OK)
        {
            HAL_FLASH_Lock();
            return -1;
        }

        // 更新剩余擦除长度和偏移
        remain_size -= (end_offset - current_offset + 1);
        current_offset = end_offset + 1;
    }
    HAL_FLASH_Lock();

    return 0;
}

/**
 * @brief  向指定逻辑偏移写入数据（自动处理32字节粒度和跨Bank）
 * @param  offset: 起始逻辑偏移
 * @param  buf: 待写入数据
 * @param  size: 写入长度
 * @retval 实际写入的字节数, -1：失败
 */
int bsp_flash_write(long offset, const uint8_t *buf, size_t size)
{
    if (!flash_check_param(offset, size) || buf == NULL)
    {
        return -1;
    }

    // 第一步：先擦除目标区域
    if (bsp_flash_erase(offset, size) != 0)
    {
        return -1;
    }

    uint32_t phys_addr;
    const uint8_t *p_src = buf;
    size_t remain = size;
    size_t written = 0;
    long current_offset = offset;
    uint8_t temp_buf[BSP_FLASH_PROG_GRANULARITY] __attribute__((aligned(32))) = {0};

    if (HAL_FLASH_Unlock() != HAL_OK)
    {
        return -1;
    }

    while (remain > 0)
    {
        // 转换当前偏移的物理地址
        if (!flash_offset_to_phys(current_offset, &phys_addr))
        {
            HAL_FLASH_Lock();
            return -1;
        }

        // 计算本次可写入的长度（不超过32字节，且不跨Bank）
        size_t write_len = (remain >= BSP_FLASH_PROG_GRANULARITY) ? BSP_FLASH_PROG_GRANULARITY : remain;

        // 检查是否跨Bank边界，若跨则截断到Bank末尾
        long bank_end_offset;
        if (current_offset < BSP_FLASH_BANK_SIZE)
        {
            bank_end_offset = BSP_FLASH_BANK_SIZE - 1;
        }
        else
        {
            bank_end_offset = BSP_FLASH_TOTAL_SIZE - 1;
        }

        if ((current_offset + write_len - 1) > bank_end_offset)
        {
            write_len = bank_end_offset - current_offset + 1;
        }

        // 填充临时缓冲区（不足32字节补0）
        memset(temp_buf, 0, BSP_FLASH_PROG_GRANULARITY);
        memcpy(temp_buf, p_src, write_len);

        // 执行32字节编程
        if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_FLASHWORD, phys_addr, (uint32_t)temp_buf) != HAL_OK)
        {
            HAL_FLASH_Lock();
            return -1;
        }

        // 校验写入数据
        for (size_t i = 0; i < write_len; i++)
        {
            if (*(uint8_t *)(phys_addr + i) != temp_buf[i])
            {
                HAL_FLASH_Lock();
                return -1;
            }
        }

        // 更新指针和偏移
        p_src += write_len;
        current_offset += write_len;
        remain -= write_len;
        written += write_len;
    }
    HAL_FLASH_Lock();

    return written;
}

/**
 * @brief  逻辑偏移转换为物理地址（核心：处理双Bank不连续映射）
 * @param  offset: 逻辑偏移（0~1048575）
 * @param  phys_addr: 输出转换后的物理地址
 * @retval true=转换成功，false=偏移非法
 */
static bool flash_offset_to_phys(long offset, uint32_t *phys_addr)
{
    if (offset < 0 || offset >= BSP_FLASH_TOTAL_SIZE)
    {
        return false;
    }

    if (offset < BSP_FLASH_BANK_SIZE)
    {
        // 0~511KB → Bank1
        *phys_addr = BSP_FLASH_BANK1_ADDR + (uint32_t)offset;
    }
    else
    {
        // 512KB~1023KB → Bank2（跳过中间512KB保留区）
        *phys_addr = BSP_FLASH_BANK2_ADDR + (uint32_t)(offset - BSP_FLASH_BANK_SIZE);
    }

    return true;
}

/**
 * @brief  获取逻辑偏移所在的Bank编号和Bank内扇区编号
 * @param  offset: 逻辑偏移
 * @param  bank: 输出Bank编号（FLASH_BANK_1/FLASH_BANK_2）
 * @param  sector: 输出Bank内扇区编号（0~3）
 * @retval true=成功，false=偏移非法
 */
static bool flash_get_bank_sector(long offset, uint32_t *bank, uint32_t *sector)
{
    if (offset < 0 || offset >= BSP_FLASH_TOTAL_SIZE)
    {
        return false;
    }

    if (offset < BSP_FLASH_BANK_SIZE)
    {
        *bank = FLASH_BANK_1;
        *sector = (uint32_t)offset / BSP_FLASH_SECTOR_SIZE;
    }
    else
    {
        *bank = FLASH_BANK_2;
        *sector = (uint32_t)(offset - BSP_FLASH_BANK_SIZE) / BSP_FLASH_SECTOR_SIZE;
    }

    return true;
}

/**
 * @brief  校验Flash操作参数合法性（含地址连续性检查）
 * @param  offset: 起始逻辑偏移
 * @param  size: 操作长度
 * @retval true=合法，false=非法
 */
static bool flash_check_param(long offset, size_t size)
{
    if (offset < 0 || size == 0 || (offset + size) > BSP_FLASH_TOTAL_SIZE)
    {
        return false;
    }

    // 额外验证：转换后的物理地址必须在有效Bank范围内
    uint32_t start_phys, end_phys;
    if (!flash_offset_to_phys(offset, &start_phys) || \
        !flash_offset_to_phys(offset + size - 1, &end_phys))
    {
        return false;
    }

    return true;
}
