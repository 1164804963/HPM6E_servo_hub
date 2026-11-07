/*
 * encoder_mt6816.c — MT6816 14bit SPI 磁编码器驱动（协议移植自 STM32 参考工程）
 *
 * 与参考工程 impl_spi_encoder.c 的对应关系：
 *   spi_read_reg_internal()  → mt6816_read_reg()      （16bit 帧不变）
 *   spi_encoder_read_angle() → encoder_mt6816_read_angle()（0x03/0x04 拼接不变）
 *   HAL_SPI_TransmitReceive → HPM spi_transfer（spi_trans_write_read_together）
 *   HAL_GPIO_WritePin(CS)   → gpio_write_pin()（本驱动自带片选，见 mt6816_cs_low/high）
 *
 * 差异说明：参考工程在 CS 前后各插 100µs 延时（STM32 软件时序保守值），
 * 本移植改为 MT6816_CS_DELAY_US（现为 1us，给手册要求的百 ns 级建立/保持时间留余量），
 * 否则一次读角要 600µs，塞进 1ms 节拍太占时间。如需恢复可改回 100。
 *
 * 与 FOC 环路的接口（encoder_mt6816_sample / ..._get_cached_*）：
 *   本驱动是唯一操作 SPI7 的地方。20kHz 的 ADC 中断里调一次 sample() 完成
 *   SPI 读角并刷新缓存；FOC 的 get_theta / get_abs_theta 回调只读缓存，
 *   绝不在控制环内部再发起 SPI 传输。见 bldc_foc.c 的 isr_adc()。
 */

#include "board.h"
#include "hpm_spi_drv.h"
#include "hpm_clock_drv.h"
#include "hpm_iomux.h"
#include "hpm_gpio_drv.h"
#include "hpm_interrupt.h"
#include "encoder_mt6816.h"

/* ============================ 硬件与协议参数 ============================ */

#define MT6816_SPI_BASE             HPM_SPI7            /* PD20~PD23 那组引脚对应的 SPI */
#define MT6816_SCLK_FREQ            (4000000UL)         /* 4MHz: 24 wire bits take 6us, plus 3us CS delay; a retry repeats the read. Measure the full ISR against its 50us budget. */
#define MT6816_CS_DELAY_US          (1U)                /* Setup/hold margin for each angle burst. */

#define MT6816_PROBE_SAMPLES        (4U)                /* 自检采样次数（见 encoder_mt6816_init） */

/*
 * 计数方向：MT6816 的计数方向取决于磁铁相对转子的安装方向。
 * 电机正向旋转时，如果角度递减就把它改成 -1。标定前先确认这一项：
 * 方向错了 FOC 的 Park 变换角度会倒着走，表现为堵转/飞车，而不是简单的不转。
 */
#define MT6816_DIRECTION_SIGN       (1)

/* MT6816_COUNTS_PER_REV (=16384) 定义在 encoder_mt6816.h */
#define MT6816_TWO_PI               (6.2831853f)
#define MT6816_RAD_PER_COUNT        (MT6816_TWO_PI / (float)MT6816_COUNTS_PER_REV)

/*
 * 引脚：本驱动自带，不使用板级 init_spi7_pins*()。
 * 原因：SDK 板级文件把那组 SPI7 配在 PF26~PF29，与本板实际接线（PD20~PD23）不符，
 * 且 PF27/28/29 是相电流采样的 ADC 脚，被抢占会导致电流环失效。
 * 板级文件属 SDK 范围，不再改动，改由本驱动在初始化时直接配置 IOC。
 */
#define MT6816_PIN_SCLK             IOC_PAD_PD20
#define MT6816_PIN_CS               IOC_PAD_PD21
#define MT6816_PIN_MISO             IOC_PAD_PD22
#define MT6816_PIN_MOSI             IOC_PAD_PD23
#define MT6816_CS_GPIO_CTRL         HPM_GPIO0
#define MT6816_CS_ACTIVE_LEVEL      (0U)                /* 低有效 */

#define MT6816_REG_ANGLE_MSB        (0x03)              /* Angle[13:6] */
#define MT6816_REG_ANGLE_LSB        (0x04)              /* Angle[5:0]（高 6 位有效）+ 状态位 */
#define MT6816_READ_FLAG            (0x80)              /* Bit7=1 读 */
#define MT6816_SPI_FRAME_LEN        (2U)

/* ============================ 内部状态 ============================ */

static spi_control_config_t s_ctrl;                     /* 传输控制配置（init 配一次反复用） */
static bool s_inited = false;

/*
 * 采样缓存：由 encoder_mt6816_sample() 独占写入（20kHz ADC 中断上下文），
 * 由 encoder_mt6816_get_cached_*() 读取（同中断上下文，以及 1kHz 主循环读来发波形）。
 *
 * 全部标 volatile：中断会抢占主循环，不加 volatile 时编译器可以把这些量缓存在
 * 寄存器里，主循环就会一直看到旧值。rv32imafc 上 32bit 的对齐读写都是单条指令，
 * 所以 volatile 之外不需要额外的互斥——读到一个"上一周期的值"是可以接受的，
 * 读到撕裂值则不可能。
 */
static volatile uint16_t s_raw14;                       /* 最近一次原始 14bit 角 */
static int32_t  s_last_raw;                             /* 上一次原始读数（未作用方向符号），用于跨零检测；仅中断内使用 */
static int32_t  s_pos_counts;                           /* 方向修正后的有符号多圈累计计数；仅中断内使用 */
static volatile float    s_theta_rad;                   /* 单圈机械角 [0, 2π) */
static volatile float    s_abs_theta_rad;               /* 多圈机械角（以重置点为原点） */
static volatile bool     s_cache_valid = false;
static volatile uint32_t s_sample_errors = 0;           /* 运行采样失败总数（传输/校验/弱磁） */
static volatile bool s_latest_sample_ok;
static volatile encoder_mt6816_errors_t s_errors;
static uint32_t s_read_error;
static uint16_t s_read_frame;

/* ============================ 内部实现 ============================ */

/*
 * 函数名   : mt6816_wrap_2pi
 * 函数说明 : 把角度折回 [0, 2π)。方向符号为负时输入落在 (-2π, 0]，加一圈即可。
 * 输入参数 : x: 待折算角度，弧度
 * 返回值   : [0, 2π) 内的角度
 */
static inline float mt6816_wrap_2pi(float x)
{
    if (x < 0.0f) {
        x += MT6816_TWO_PI;
    } else if (x >= MT6816_TWO_PI) {
        x -= MT6816_TWO_PI;
    }
    return x;
}

/*
 * 函数名   : mt6816_update_cache
 * 函数说明 : 用一次新的原始读数刷新单圈角、多圈角和原始值缓存。
 *            相邻读数跨过 0/16383 边界时按整圈修正，避免量化误差累积成假圈数。
 * 输入参数 : raw: 14bit 原始角度
 * 返回值   : 无
 */
static void mt6816_update_cache(uint16_t raw)
{
    int32_t raw_i = (int32_t)raw;

    if (s_cache_valid) {
        int32_t delta = raw_i - s_last_raw;

        if (delta > (int32_t)(MT6816_COUNTS_PER_REV / 2)) {
            delta -= (int32_t)MT6816_COUNTS_PER_REV;
        } else if (delta < -(int32_t)(MT6816_COUNTS_PER_REV / 2)) {
            delta += (int32_t)MT6816_COUNTS_PER_REV;
        }
        s_pos_counts += MT6816_DIRECTION_SIGN * delta;
    } else {
        /* 首次采样：以当前位置作为多圈原点 */
        s_pos_counts = MT6816_DIRECTION_SIGN * raw_i;
    }

    s_last_raw = raw_i;
    s_raw14 = raw;
    s_theta_rad = mt6816_wrap_2pi((float)raw_i * (float)MT6816_DIRECTION_SIGN * MT6816_RAD_PER_COUNT);
    s_abs_theta_rad = (float)s_pos_counts * MT6816_RAD_PER_COUNT;
    s_cache_valid = true;
}

/*
 * 函数名   : mt6816_config_pins
 * 函数说明 : 直接配置 MT6816 使用的 SPI7 引脚：PD20=SCLK，PD21=GPIO 软件片选，
 *            PD22=MISO，PD23=MOSI。板级文件把这组 SPI 配在 PF26~PF29，与本板接线不符，
 *            且会抢占电流采样脚，所以由驱动自己配置。
 * 输入参数 : 无
 * 返回值   : 无
 */
static void mt6816_config_pins(void)
{
    /* PD21：片选，配成 GPIO 输出（初始电平在 gpio_set_pin_output_with_initial 里给高） */
    HPM_IOC->PAD[MT6816_PIN_CS].FUNC_CTL = IOC_PD21_FUNC_CTL_GPIO_D_21;
    HPM_IOC->PAD[MT6816_PIN_CS].PAD_CTL = IOC_PAD_PAD_CTL_SR_SET(1) | IOC_PAD_PAD_CTL_SPD_SET(3) |
                                          IOC_PAD_PAD_CTL_PE_SET(1) | IOC_PAD_PAD_CTL_PS_SET(1) |
                                          IOC_PAD_PAD_CTL_PRS_SET(1);

    /* PD20：SCLK */
    HPM_IOC->PAD[MT6816_PIN_SCLK].FUNC_CTL = IOC_PD20_FUNC_CTL_SPI7_SCLK | IOC_PAD_FUNC_CTL_LOOP_BACK_MASK;
    HPM_IOC->PAD[MT6816_PIN_SCLK].PAD_CTL = IOC_PAD_PAD_CTL_SR_SET(1) | IOC_PAD_PAD_CTL_SPD_SET(3);

    /* PD22：MISO */
    HPM_IOC->PAD[MT6816_PIN_MISO].FUNC_CTL = IOC_PD22_FUNC_CTL_SPI7_MISO;
    HPM_IOC->PAD[MT6816_PIN_MISO].PAD_CTL = IOC_PAD_PAD_CTL_SR_SET(1) | IOC_PAD_PAD_CTL_SPD_SET(3);

    /* PD23：MOSI */
    HPM_IOC->PAD[MT6816_PIN_MOSI].FUNC_CTL = IOC_PD23_FUNC_CTL_SPI7_MOSI;
    HPM_IOC->PAD[MT6816_PIN_MOSI].PAD_CTL = IOC_PAD_PAD_CTL_SR_SET(1) | IOC_PAD_PAD_CTL_SPD_SET(3);

    gpio_set_pin_output_with_initial(MT6816_CS_GPIO_CTRL,
                                     GPIO_GET_PORT_INDEX(MT6816_PIN_CS),
                                     GPIO_GET_PIN_INDEX(MT6816_PIN_CS),
                                     !MT6816_CS_ACTIVE_LEVEL);
}

/*
 * 函数名   : mt6816_cs_low
 * 函数说明 : 拉低片选，选中 MT6816。
 * 输入参数 : 无
 * 返回值   : 无
 */
static inline void mt6816_cs_low(void)
{
    gpio_write_pin(MT6816_CS_GPIO_CTRL, GPIO_GET_PORT_INDEX(MT6816_PIN_CS),
                   GPIO_GET_PIN_INDEX(MT6816_PIN_CS), MT6816_CS_ACTIVE_LEVEL);
}

/*
 * 函数名   : mt6816_cs_high
 * 函数说明 : 拉高片选，释放 MT6816。
 * 输入参数 : 无
 * 返回值   : 无
 */
static inline void mt6816_cs_high(void)
{
    gpio_write_pin(MT6816_CS_GPIO_CTRL, GPIO_GET_PORT_INDEX(MT6816_PIN_CS),
                   GPIO_GET_PIN_INDEX(MT6816_PIN_CS), !MT6816_CS_ACTIVE_LEVEL);
}

/*
 * 函数名   : mt6816_read_angle_burst
 * 函数说明 : 一次片选内发 [0x83, dummy, dummy]，连续读出 0x03、0x04（地址自动递增，见手册图19）。
 *            比两次单独读少一轮片选延时，中断里读角更短。
 * 输入参数 : msb: 0x03 的值；lsb: 0x04 的值
 * 返回值   : true: 传输成功；false: SPI 传输失败
 */
static bool mt6816_read_angle_burst(uint8_t *msb, uint8_t *lsb)
{
    uint8_t tx[3] = {(uint8_t)(MT6816_READ_FLAG | MT6816_REG_ANGLE_MSB), 0x00, 0x00};
    uint8_t rx[3] = {0};
    mt6816_cs_low();
    board_delay_us(MT6816_CS_DELAY_US);
    hpm_stat_t stat = spi_transfer(MT6816_SPI_BASE, &s_ctrl, NULL, NULL, tx, 3, rx, 3);
    board_delay_us(MT6816_CS_DELAY_US);
    mt6816_cs_high();
    board_delay_us(MT6816_CS_DELAY_US);
    if (stat != status_success) return false;
    *msb = rx[1];
    *lsb = rx[2];
    return true;
}

/*
 * 函数名   : mt6816_check_frame
 * 函数说明 : 检查 16bit 返回帧：偶数校验位（全 16bit）和 Reg 0x04 bit1 的弱磁警告位。
 *            校验错时不再解释状态位，避免把坏帧当成有效数据。
 * 输入参数 : frame: 由 0x03/0x04 拼成的 16bit 帧
 * 返回值   : 0: 正常；1: 校验错；2: 弱磁警告
 */
static unsigned mt6816_check_frame(uint16_t frame)
{
    uint16_t parity = frame;
    parity ^= parity >> 8;
    parity ^= parity >> 4;
    parity ^= parity >> 2;
    parity ^= parity >> 1;
    if (parity & 1U) return 1U; /* Do not interpret status bits in a corrupt frame. */
    return (frame & 2U) ? 2U : 0U;
}

/*
 * 函数名   : mt6816_read_raw_once
 * 函数说明 : 按参考工程顺序先读 0x03 再读 0x04，拼成 16bit 帧并检查校验与状态位，
 *            成功后取出 14bit 角度。初始化自检和正常运行共用。
 * 输入参数 : raw: 输出 14bit 原始角度
 * 返回值   : true: 读到有效角度；false: 传输失败、校验错或弱磁
 */
static bool mt6816_read_raw_once(uint16_t *raw)
{
    uint8_t msb = 0, lsb = 0;
    s_read_error = 0;
    s_read_frame = 0;

    if (!mt6816_read_angle_burst(&msb, &lsb)) {
        s_read_error = 1; /* SPI transfer failed; no complete frame. */
        s_latest_sample_ok = false;
        return false;
    }

    uint16_t frame = ((uint16_t)msb << 8) | lsb;
    s_read_frame = frame;
    unsigned check = mt6816_check_frame(frame);
    s_read_error = check == 1U ? 2U : (check == 2U ? 3U : 0U);
    s_latest_sample_ok = check == 0U;
    if (!s_latest_sample_ok) return false;

    *raw = frame >> 2;
    return true;
}

/* ============================ 公开 API ============================ */

/*
 * 函数名   : encoder_mt6816_init
 * 函数说明 : 初始化 SPI7 时钟、PD20~PD23 引脚和帧格式，再连采几次角度做通信自检。
 *            自检看数据是否退化成 0x0000/0x3FFF，因为从机不在时 SPI 传输仍返回成功。
 * 输入参数 : 无
 * 返回值   : true: 编码器可用；false: 初始化或自检失败
 */
bool encoder_mt6816_init(void)
{
    if (s_inited) {
        return true;
    }

    /* 时钟 + 引脚（PD20/22/23 复用为 SPI7，PD21 配为 GPIO 输出并拉高做软件片选） */
    (void)board_init_spi_clock(MT6816_SPI_BASE);
    mt6816_config_pins();

    /* 时序配置：SCLK 频率 */
    spi_timing_config_t timing_config = {0};
    spi_master_get_default_timing_config(&timing_config);
    timing_config.master_config.clk_src_freq_in_hz = board_init_spi_clock(MT6816_SPI_BASE);
    timing_config.master_config.sclk_freq_in_hz = MT6816_SCLK_FREQ;
    if (status_success != spi_master_timing_init(MT6816_SPI_BASE, &timing_config)) {
        printf("mt6816: spi timing init failed\n");
        return false;
    }

    /* 帧格式：模式 3（CPOL=1 + 偶数边沿采样），8bit，MSB 先行 —— 与参考工程一致 */
    spi_format_config_t format_config = {0};
    spi_master_get_default_format_config(&format_config);
    format_config.common_config.data_len_in_bits = 8;
    format_config.common_config.mode = spi_master_mode;
    format_config.common_config.cpol = spi_sclk_high_idle;              /* CPOL=1 */
    format_config.common_config.cpha = spi_sclk_sampling_even_clk_edges; /* CPHA=2nd edge */
    spi_format_init(MT6816_SPI_BASE, &format_config);

    /* 传输控制：无命令/地址相位，全双工同发同收（等价 HAL_SPI_TransmitReceive） */
    spi_master_get_default_control_config(&s_ctrl);
    s_ctrl.master_config.cmd_enable = false;
    s_ctrl.master_config.addr_enable = false;
    s_ctrl.common_config.trans_mode = spi_trans_write_read_together;

    mt6816_cs_high();   /* 空闲高，未选中状态 */

    /*
     * 通信自检：采 MT6816_PROBE_SAMPLES 次角度，只要有一次不是 0x0000/0x3FFF 就算通。
     * 判据说明：SPI 主机在从机不存在时依然返回 status_success（MISO 读到空闲电平），
     * 所以只判 spi_transfer 的返回码会误报成功。总线断开时拼出的 raw 恒为 0 或满量程；
     * 真实器件连续 N 次全落在同一端点值的概率为 (1/16384)^N，可忽略。取"任一非端点"
     * 是为了避免恰好停在 0° 时误判。
     */
    bool got_valid = false;
    uint16_t raw = 0;

    for (uint32_t i = 0; i < MT6816_PROBE_SAMPLES; i++) {
        if (!mt6816_read_raw_once(&raw)) {
            printf("mt6816: probe transfer failed (check wiring/power)\n");
            return false;
        }
        if ((raw != 0x0000U) && (raw != 0x3FFFU)) {
            got_valid = true;
            break;
        }
    }
    if (!got_valid) {
        printf("mt6816: probe all %u samples degenerate (raw=0x%04X), no encoder responding\n",
               (unsigned)MT6816_PROBE_SAMPLES, (unsigned)raw);
        return false;
    }

    s_inited = true;
    printf("mt6816: init ok (spi7 PD20-23 @%uHz, raw=0x%04X)\n", (unsigned)MT6816_SCLK_FREQ, (unsigned)raw);
    return true;
}

/*
 * 函数名   : encoder_mt6816_sample
 * 函数说明 : 采一次角并刷新全部缓存，控制环每周期调用一次。
 *            失败时保留上一次的有效角度，避免中断里返回错误导致 MCL 把编码器判为失效。
 * 输入参数 : 无
 * 返回值   : true: 本次采样有效；false: 采样失败
 */
bool encoder_mt6816_sample(void)
{
    uint16_t raw = 0;

    if (!s_inited) {
        return false;
    }
    /*
     * Parity failures only appear while the rotor turns and the bad frames sit within 1-2 counts of
     * the true angle (low bits or PC flipped), i.e. the chip updated its angle while latching the
     * frame. A second read gets a fresh latch; costs one more 24-bit frame (~9us) only on failure.
     */
    if (!mt6816_read_raw_once(&raw) && (s_read_error != 2U || !mt6816_read_raw_once(&raw))) {
        s_sample_errors++;
        if (s_read_error == 1U) s_errors.transfer++;
        else if (s_read_error == 2U) s_errors.parity++;
        else s_errors.magnetic++;
        s_errors.consecutive++;
        if (s_errors.consecutive > s_errors.max_consecutive)
            s_errors.max_consecutive = s_errors.consecutive;
        s_errors.last_reason = s_read_error;
        s_errors.last_frame = s_read_frame;
        return false;
    }

    s_errors.consecutive = 0;
    mt6816_update_cache(raw);
    return true;
}

/*
 * 函数名   : encoder_mt6816_get_cached_raw
 * 函数说明 : 取缓存的 14bit 原始角度，不发起 SPI 传输。
 * 输入参数 : raw14: 输出原始角度，可为 NULL
 * 返回值   : true: 缓存有效；false: 还没有成功采样过
 */
bool encoder_mt6816_get_cached_raw(uint16_t *raw14)
{
    if (!s_cache_valid) {
        return false;
    }
    if (raw14 != NULL) {
        *raw14 = s_raw14;
    }
    return true;
}

/*
 * 函数名   : encoder_mt6816_get_cached_theta_rad
 * 函数说明 : 取缓存的单圈机械角，不发起 SPI 传输。
 * 输入参数 : theta_rad: 输出角度，弧度 [0, 2π)，可为 NULL
 * 返回值   : true: 缓存有效；false: 还没有成功采样过
 */
bool encoder_mt6816_get_cached_theta_rad(float *theta_rad)
{
    if (!s_cache_valid) {
        return false;
    }
    if (theta_rad != NULL) {
        *theta_rad = s_theta_rad;
    }
    return true;
}

/*
 * 函数名   : encoder_mt6816_get_cached_abs_theta_rad
 * 函数说明 : 取缓存的多圈机械角，不发起 SPI 传输。
 * 输入参数 : theta_rad: 输出角度，弧度，可超出 2π，可为 NULL
 * 返回值   : true: 缓存有效；false: 还没有成功采样过
 */
bool encoder_mt6816_get_cached_abs_theta_rad(float *theta_rad)
{
    if (!s_cache_valid) {
        return false;
    }
    if (theta_rad != NULL) {
        *theta_rad = s_abs_theta_rad;
    }
    return true;
}

/*
 * 函数名   : encoder_mt6816_reset_abs_origin
 * 函数说明 : 把多圈累计位置清零，使多圈角从当前位置重新起算。
 *            只清累计量，不动上次读数和单圈角，否则下次跨零检测会算出假 delta。
 * 输入参数 : 无
 * 返回值   : 无
 */
void encoder_mt6816_reset_abs_origin(void)
{
    /* 只清多圈累计（和它的派生量），不动 s_last_raw / s_theta_rad，
     * 否则下一次跨零检测会算出一个假 delta。 */
    s_pos_counts = 0;
    s_abs_theta_rad = 0.0f;
}

/*
 * 函数名   : encoder_mt6816_get_errors
 * 函数说明 : 拷出分类错误统计和最近一帧内容。调用者需关中断，保证快照一致。
 * 输入参数 : errors: 输出错误统计
 * 返回值   : 无
 */
void encoder_mt6816_get_errors(encoder_mt6816_errors_t *errors)
{
    errors->transfer = s_errors.transfer;
    errors->parity = s_errors.parity;
    errors->magnetic = s_errors.magnetic;
    errors->consecutive = s_errors.consecutive;
    errors->max_consecutive = s_errors.max_consecutive;
    errors->last_reason = s_errors.last_reason;
    errors->last_frame = s_errors.last_frame;
}

/*
 * 函数名   : encoder_mt6816_get_error_count
 * 函数说明 : 返回上电以来采样失败的总次数，供看门狗判断编码器是否持续失效。
 * 输入参数 : 无
 * 返回值   : 失败次数
 */
uint32_t encoder_mt6816_get_error_count(void)
{
    return s_sample_errors;
}

/*
 * 函数名   : encoder_mt6816_feedback_ok
 * 函数说明 : 判断反馈是否可用：缓存已建立，且最近一次采样成功。
 * 输入参数 : 无
 * 返回值   : true: 反馈正常；false: 尚未采样或最近一次失败
 */
bool encoder_mt6816_feedback_ok(void)
{
    return s_cache_valid && s_latest_sample_ok;
}

/*
 * 函数名   : encoder_mt6816_read_theta_rad
 * 函数说明 : 立刻发起一次 SPI 读角并返回单圈机械角，供初始化阶段使用；
 *            正常运行应走 sample + get_cached 接口，避免在控制环里等 SPI。
 * 输入参数 : theta_rad: 输出角度，弧度，可为 NULL
 * 返回值   : true: 读取成功；false: 采样失败
 */
bool encoder_mt6816_read_theta_rad(float *theta_rad)
{
    if (!encoder_mt6816_sample()) {
        return false;
    }
    if (theta_rad != NULL) {
        *theta_rad = s_theta_rad;
    }
    return true;
}
