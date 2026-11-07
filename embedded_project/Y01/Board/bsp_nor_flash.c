#include "bsp_nor_flash.h"
#include "board.h"

/* Nor Flash SPI操作函数 */
static uint8_t spi_transfer(uint8_t data);
static void spi_transfer_bulk(uint8_t *tx_data, uint8_t *rx_data, size_t size);
static int wait_for_ready(void);
static int write_enable(void);
static uint8_t read_status_register(void);
static int chip_erase(void);

/**
 * @brief 初始化GD25Q64ESIG Flash
 * @return 0-成功, -1-失败
 */
int bsp_nor_flash_init(void)
{
    uint8_t tx_buf[4] = {0};
    uint8_t rx_buf[3] = {0}; // 存储MID(1B)+Memory Type(1B)+Capacity(1B)

    /* 0. 释放其他从机片选信号（确保CS引脚为高电平） */
    DRV_SPI_CS_DISABLE();

    /* 1. 释放深度掉电模式（规格书7.29） */
    FLASH_SPI_CS_ENABLE();
    tx_buf[0] = GD25Q64_CMD_RELEASE_POWER_DOWN; // ABH命令
    HAL_SPI_Transmit(&FLASH_SPI_HANDLE, tx_buf, 1, 10);
    FLASH_SPI_CS_DISABLE();
    HAL_Delay(1); // 远大于tRES1（20μs），确保设备唤醒

    /* 2. 读取设备ID（9FH命令，规格书7.20） */
    FLASH_SPI_CS_ENABLE();
    tx_buf[0] = GD25Q64_CMD_READ_ID; // 9FH命令
    // 发送命令后，读取3字节ID（MID+Memory Type+Capacity）
    HAL_SPI_Transmit(&FLASH_SPI_HANDLE, tx_buf, 1, 10);
    HAL_SPI_Receive(&FLASH_SPI_HANDLE, rx_buf, 3, 10);
    FLASH_SPI_CS_DISABLE();

    /* 3. 验证GD25Q128设备ID（规格书Table of ID Definitions） */
    if (rx_buf[0] != 0xC8 || rx_buf[1] != 0x40 || rx_buf[2] != 0x17) {
        return -1; // 设备ID不匹配
    }

    return 0;
}

/**
 * @brief 高速读取Flash数据（用Fast Read命令0BH，支持最高133MHz）
 * @param offset 偏移地址
 * @param buf 数据缓冲区
 * @param size 读取大小
 * @return 实际读取的字节数, -1-失败
 */
int bsp_nor_flash_read(long offset, uint8_t *buf, size_t size)
{
    uint8_t tx_buf[5] = {0};

    // 参数合法性检查
    if (offset < 0 || offset + size > GD25Q64_TOTAL_SIZE || buf == NULL)
    {
        return -1;
    }

    // 等待Flash就绪（WIP位为0）
    if (wait_for_ready() != 0)
    {
        return -1;
    }

    FLASH_SPI_CS_ENABLE();

    // 发送Fast Read命令（0BH）+ 24位地址 + 1个dummy字节（规格书7.7）
    tx_buf[0] = GD25Q64_CMD_FAST_READ; // 复用原宏，实际为GD25Q128的FAST READ命令（0BH）
    tx_buf[1] = (offset >> 16) & 0xFF; // 地址高位
    tx_buf[2] = (offset >> 8) & 0xFF;  // 地址中位
    tx_buf[3] = offset & 0xFF;         // 地址低位
    tx_buf[4] = 0x00;                  // Dummy字节（高频下必须，补偿读取延迟）

    // 发送命令+地址+dummy（共5字节）
    if (HAL_SPI_Transmit(&FLASH_SPI_HANDLE, tx_buf, 5, HAL_MAX_DELAY) != HAL_OK)
    {
        FLASH_SPI_CS_DISABLE();
        return -1;
    }

    // 读取数据（高速下用HAL_SPI_Receive直接读取，效率更高）
    if (HAL_SPI_Receive(&FLASH_SPI_HANDLE, buf, size, HAL_MAX_DELAY) != HAL_OK)
    {
        FLASH_SPI_CS_DISABLE();
        return -1;
    }

    FLASH_SPI_CS_DISABLE();
    return size;
}

/**
 * @brief 向Flash写入数据
 * @param offset 偏移地址
 * @param buf 数据缓冲区
 * @param size 写入大小
 * @return 实际写入的字节数, -1-失败
 */
int bsp_nor_flash_write(long offset, const uint8_t *buf, size_t size)
{
    int bytes_written = 0;
    size_t page_remaining;
    size_t write_size;

    if (offset < 0 || offset + size > GD25Q64_TOTAL_SIZE || buf == NULL) {
        return -1;
    }

    while (size > 0) {
        /* 计算当前页剩余空间 */
        page_remaining = GD25Q64_PAGE_SIZE - (offset % GD25Q64_PAGE_SIZE);
        write_size = (size < page_remaining) ? size : page_remaining;

        /* 写使能 */
        if (write_enable() != 0) {
            return -1;
        }

        /* 等待Flash就绪 */
        if (wait_for_ready() != 0) {
            return -1;
        }

        FLASH_SPI_CS_ENABLE();

        /* 发送页编程命令和地址 */
        uint8_t tx_cmd[4] = {
            GD25Q64_CMD_PAGE_PROGRAM,
            (offset >> 16) & 0xFF,
            (offset >> 8) & 0xFF,
            offset & 0xFF
        };

        spi_transfer_bulk(tx_cmd, NULL, 4);

        /* 写入数据 */
        spi_transfer_bulk((uint8_t*)buf, NULL, write_size);

        FLASH_SPI_CS_DISABLE();

        /* 等待写入完成 */
        if (wait_for_ready() != 0) {
            return -1;
        }

        offset += write_size;
        buf += write_size;
        size -= write_size;
        bytes_written += write_size;
    }

    return bytes_written;
}

/**
 * @brief 擦除Flash区域
 * @param offset 偏移地址
 * @param size 擦除大小
 * @return 0-成功, -1-失败
 */
int bsp_nor_flash_erase(long offset, size_t size)
{
    if (offset < 0 || offset + size > GD25Q64_TOTAL_SIZE) {
        return -1;
    }

    /* 对齐到扇区边界 */
    long sector_start = offset & ~(GD25Q64_SECTOR_SIZE - 1);
    long sector_end = (offset + size + GD25Q64_SECTOR_SIZE - 1) & ~(GD25Q64_SECTOR_SIZE - 1);
    size_t erase_size = sector_end - sector_start;

    /* 检查是否需要整片擦除 */
    if (erase_size == GD25Q64_TOTAL_SIZE) {
        return chip_erase();
    }

    /* 按扇区擦除 */
    while (erase_size > 0) {
        /* 写使能 */
        if (write_enable() != 0) {
            return -1;
        }

        /* 等待Flash就绪 */
        if (wait_for_ready() != 0) {
            return -1;
        }

        FLASH_SPI_CS_ENABLE();

        /* 发送扇区擦除命令和地址 */
        uint8_t tx_cmd[4] = {
            GD25Q64_CMD_SECTOR_ERASE,
            (sector_start >> 16) & 0xFF,
            (sector_start >> 8) & 0xFF,
            sector_start & 0xFF
        };

        spi_transfer_bulk(tx_cmd, NULL, 4);

        FLASH_SPI_CS_DISABLE();

        /* 等待擦除完成 */
        if (wait_for_ready() != 0) {
            return -1;
        }

        sector_start += GD25Q64_SECTOR_SIZE;
        erase_size -= GD25Q64_SECTOR_SIZE;
    }

    return 0;
}

/**
 * @brief 擦除Flash区域（按64KB块擦除）
 * @param offset 偏移地址
 * @param size 擦除大小
 * @return 0-成功, -1-失败
 */
int bsp_nor_flash_erase_block_64k(long offset)
{
    if (offset < 0 || offset + GD25Q64_BLOCK_64K_SIZE > GD25Q64_TOTAL_SIZE) {
        return -1;
    }

    /* 对齐到64KB块边界 */
    long block_start = offset & ~(GD25Q64_BLOCK_64K_SIZE - 1);

    /* 按64KB块擦除 */
    /* 写使能 */
    if (write_enable() != 0) {
        return -1;
    }

    /* 等待Flash就绪 */
    if (wait_for_ready() != 0) {
        return -1;
    }

    FLASH_SPI_CS_ENABLE();

    /* 发送64KB块擦除命令和地址 */
    uint8_t tx_cmd[4] = {
        GD25Q64_CMD_BLOCK_ERASE_64K,
        (block_start >> 16) & 0xFF,
        (block_start >> 8) & 0xFF,
        block_start & 0xFF
    };

    spi_transfer_bulk(tx_cmd, NULL, 4);

    FLASH_SPI_CS_DISABLE();

    /* 等待擦除完成 */
    if (wait_for_ready() != 0) {
        return -1;
    }

    return 0;
}

/**
 * @brief SPI单字节传输（高频下减少函数调用开销）
 * @param data 发送数据
 * @return 接收数据
 */
static uint8_t spi_transfer(uint8_t data)
{
    uint8_t rx_data;

    HAL_SPI_TransmitReceive(&FLASH_SPI_HANDLE, &data, &rx_data, 1, 10);

    return rx_data;
}
/**
 * @brief SPI批量传输（优化高频下效率，减少分支判断）
 * @param tx_data 发送缓冲区（NULL表示仅接收）
 * @param rx_data 接收缓冲区（NULL表示仅发送）
 * @param size 传输字节数
 */
static void spi_transfer_bulk(uint8_t *tx_data, uint8_t *rx_data, size_t size)
{
    if (size == 0) return;

    // 全双工传输（TX+RX）
    if (tx_data != NULL && rx_data != NULL)
    {
        HAL_SPI_TransmitReceive(&FLASH_SPI_HANDLE, tx_data, rx_data, size, 100); // 超时100ms，避免死等
    }
    // 仅发送
    else if (tx_data != NULL)
    {
        HAL_SPI_Transmit(&FLASH_SPI_HANDLE, tx_data, size, 100);
    }
    // 仅接收
    else if (rx_data != NULL)
    {
        HAL_SPI_Receive(&FLASH_SPI_HANDLE, rx_data, size, 100);
    }
}

/**
 * @brief 等待Flash就绪
 * @return 0-就绪, -1-超时
 */
static int wait_for_ready(void)
{
    uint32_t timeout = 1000000; // 超时计数器

    while (timeout--) {
        uint8_t status = read_status_register();
        if ((status & 0x01) == 0) { // 检查WIP位
            return 0; // 就绪
        }
    }

    return -1; // 超时
}

/**
 * @brief 写使能
 * @return 0-成功, -1-失败
 */
static int write_enable(void)
{
    uint32_t retry = 3; // 重试3次，避免高频下偶发失败
    const uint32_t short_delay = 100; // 短延时循环次数，根据实际情况调整
    while (retry--)
    {
        FLASH_SPI_CS_ENABLE();
        spi_transfer(GD25Q64_CMD_WRITE_ENABLE); // 06H命令
        FLASH_SPI_CS_DISABLE();

        // 读取状态寄存器，检查WEL位（S1位）是否置1（规格书6.1）
        uint8_t status = read_status_register();
        if ((status & 0x02) != 0)
        {
            return 0; // WEL位已置1
        }
        for (volatile uint32_t i = 0; i < short_delay; i++)
        {
            __NOP(); // 空操作，仅占用CPU周期
        }
    }
    return -1; // 多次重试失败
}

/**
 * @brief 读取状态寄存器
 * @return 状态寄存器值
 */
static uint8_t read_status_register(void)
{
    uint8_t status;

    FLASH_SPI_CS_ENABLE();
    spi_transfer(GD25Q64_CMD_READ_STATUS_REG1);
    status = spi_transfer(0xFF);
    FLASH_SPI_CS_DISABLE();

    return status;
}

/**
 * @brief 整片擦除（可选功能）
 * @return 0-成功, -1-失败
 */
static int chip_erase(void)
{
    /* 写使能 */
    if (write_enable() != 0) {
        return -1;
    }

    /* 等待Flash就绪 */
    if (wait_for_ready() != 0) {
        return -1;
    }

    FLASH_SPI_CS_ENABLE();
    spi_transfer(GD25Q64_CMD_CHIP_ERASE);
    FLASH_SPI_CS_DISABLE();

    /* 等待擦除完成 */
    return wait_for_ready();
}
