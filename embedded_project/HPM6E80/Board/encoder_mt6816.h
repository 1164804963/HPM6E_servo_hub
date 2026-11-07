/*
 * encoder_mt6816.h — MT6816 14bit SPI 磁编码器驱动（HPM SPI7 + GPIO 片选）
 *
 * 移植自 STM32 参考工程（/Users/lvyulin/Desktop/project 2.2 的
 * User_Space/Impl/Src/impl_spi_encoder.c），协议保持一致：
 *   - SPI 模式 3（CPOL=1, CPHA=2nd edge），8bit，MSB 先行
 *   - 16bit 帧：[0x80|寄存器地址, dummy]，从机在第 2 字节回数据
 *   - 角度寄存器 0x03（Angle[13:6]）/ 0x04（Angle[5:0]，高 6 位有效）
 *   - 14bit 原始角：raw = ((msb << 6) | (lsb >> 2)) & 0x3FFF，满量程 16384 = 360°
 *
 * 硬件（hpm6e00YZ 板）：SPI7 走 PD 组引脚
 *   SCLK = PD20, CS  = PD21 (GPIO 软件片选, 低有效)
 *   MISO = PD22, MOSI = PD23
 * 这组引脚的 IOC 配置由本驱动自己完成（mt6816_config_pins），
 * 不调用板级 init_spi7_pins*()——后者配的是 PF 组，与本板接线不符，
 * 且 PF27/28/29 是相电流采样 ADC 脚。
 *
 * 注意：board.h 的 BOARD_APP_SPI_BASE 指向 HPM_SPI1，与其余 SPI7 宏不一致，
 * 本文件不使用该宏，直接绑定 HPM_SPI7。
 *
 * 上板调试的两个旋钮（都在 encoder_mt6816.c 顶部）：
 *   MT6816_DIRECTION_SIGN —— 电机正转时角度递增填 +1，递减填 -1；填错会堵转/飞车。
 *   MT6816_SCLK_FREQ      —— 当前 4MHz。传输及片选延时必须留在50us控制周期以内。
 */

#ifndef ENCODER_MT6816_H
#define ENCODER_MT6816_H

#include <stdint.h>
#include <stdbool.h>

/* 14bit 满量程：每圈 16384 个计数（供 MCL 的 encoder.precision 等外部配置使用） */
#define MT6816_COUNTS_PER_REV   (16384U)

#ifdef __cplusplus
extern "C" {
#endif

/* 初始化 SPI7 外设 + 引脚 + 片选（空闲拉高）。返回 false = 外设初始化失败 */
bool encoder_mt6816_init(void);

/*
 * 采样一次（SPI 读 + 刷新缓存 + 多圈计数）。FOC 的 ADC 中断每个控制周期调一次。
 * 失败返回 false，但缓存保留上一次的有效值——中断里不要因为一次传输失败就让
 * 整个编码器进入 fail 状态。
 */
bool encoder_mt6816_sample(void);

/* 以下三个只读缓存，不做 SPI 传输。缓存尚未建立（init 后还没 sample 过）时返回 false */
bool encoder_mt6816_get_cached_raw(uint16_t *raw14);          /* 原始 14bit，0~16383 */
bool encoder_mt6816_get_cached_theta_rad(float *theta_rad);   /* 单圈机械角 [0, 2π) */
bool encoder_mt6816_get_cached_abs_theta_rad(float *theta_rad); /* 多圈机械角，以重置点为原点 */

/* 把多圈累计原点重置到当前位置（电角度零点标定完成后调用） */
void encoder_mt6816_reset_abs_origin(void);

/* 运行采样失败累计次数：包括传输、偶校验和缺磁报警。 */
uint32_t encoder_mt6816_get_error_count(void);
typedef struct {
    uint32_t transfer, parity, magnetic;
    uint32_t consecutive, max_consecutive;
    uint32_t last_reason; /* 1=transfer, 2=parity, 3=magnetic; 0=no failures. */
    uint16_t last_frame; /* 0 for incomplete SPI transfer. */
} encoder_mt6816_errors_t;
/* Read-only counters since boot; caller masks ADC interrupt for consistency. */
void encoder_mt6816_get_errors(encoder_mt6816_errors_t *errors);
bool encoder_mt6816_feedback_ok(void);

/* 读一次单圈机械角度，输出弧度 [0, 2π) */
bool encoder_mt6816_read_theta_rad(float *theta_rad);

#ifdef __cplusplus
}
#endif


#endif /* ENCODER_MT6816_H */
