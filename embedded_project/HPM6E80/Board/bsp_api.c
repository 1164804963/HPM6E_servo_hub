#include "bsp_api.h"

#include <math.h>
#include <stdio.h>

#include "servo_board.h"
#include "system_timer.h"
#include "drv_encoder.h"

#include "hpm_soc.h"
#include "hpm_gpio_drv.h"
#include "hpm_pwmv2_drv.h"
#include "hpm_interrupt.h"

#if defined(PORT_PATCH_CAL_DRIFT_STORE_FLASH) && (PORT_PATCH_CAL_DRIFT_STORE_FLASH)
#include "app_store_param.h"   /* [移植补丁 14] kFlashStorage */
#endif

/* ---------------------------------------------------------------------------
 * 硬件状态与校准
 * 上位机（Portable 层）只通过 bsp_api.h 看到电压/电流/温度与校准状态，
 * 这里不做任何控制逻辑。
 * ------------------------------------------------------------------------- */

#define CURRENT_CALIBRATION_TIMES   (1024U)   /* 1ms 步进，约 1.02s 采样窗口 */
/* 零点偏差上限。本板实测（L0，桥臂封锁）：U -0.29A / V -0.13A / W +0.03A，
 * 来源是 1.65V 偏置分压精度和运放失调，属于正常范围。
 * 取 0.5A：比实测留一倍余量，再大就说明采样通路（缺相、短路、分压错）真的有问题。 */
#define CURRENT_CALIBRATION_LIMIT   (0.50f)
/* 零漂采样允许的最大相电压指令：再大说明已经带载，零点采不准 */
#define CALIBRATION_ZERO_VOLTAGE_MAX_V  (0.20f)
#define BUS_UNDER_COUNT             (2000U)
#define BUS_NORMAL_COUNT            (500U)

static BspErrorCode_t s_bsp_error;
static bool s_hardware_self_test_status;

static CURRENT_CALIBRATION_STATUS s_cal_status = CURRENT_CALIBRATION_STATUS_READY;
static uint32_t s_cal_sum[3];
static uint32_t s_cal_count;
static uint16_t s_cal_drift[3];

#if defined(PORT_PATCH_CAL_DRIFT_STORE_FLASH) && (PORT_PATCH_CAL_DRIFT_STORE_FLASH)
/* 前置声明：放到 s_cal 恢复函数之前，避免定义在后面导致隐式声明冲突 */
static float bsp_raw_to_current(uint16_t raw, uint16_t drift);

/* [移植补丁 14] 电流零漂标定结果的 Flash 持久化。
 *
 * 背景（GDB 实测）：s_cal_status/s_cal_drift 只在 RAM，复位即回 READY(0)。
 * hw_ready 要求 cal==OK，所以每次上电都必须先使能一次让标定跑完 1 秒，
 * 否则电机永远不动（现象：使能了但电机纹丝不动、无报警）。
 *
 * 做法：标定成功后把三路漂移 + 魔数 + 校验和写进 kFlashStorage，走现有
 * "AllParam" 那条 FlashDB KV（SysCmd=2 存盘时一并落盘）。
 * 上电时 try_restore 校验通过就把 s_cal_drift/s_cal_status 直接置成可用。 */
#define CURRENT_CAL_DRIFT_MAGIC   (0x43414C31UL)   /* 'CAL1' */

static uint16_t cal_drift_crc16(const uint16_t *d)
{
    /* 简单校验：三个漂移值的字节异或 + 固定种子 */
    uint16_t crc = 0x5A5AU;

    for (uint32_t i = 0; i < 3U; i++)
    {
        crc = (uint16_t)(crc ^ d[i]);
        crc = (uint16_t)((crc << 3) | (crc >> 13));
    }
    return crc;
}

/* 保存到 RAM 里的 kFlashStorage（真正的落盘由 SysCmd=2 触发 flash_param_update） */
static void cal_drift_store_to_shadow(void)
{
    kFlashStorage.current_cal_drift_magic = CURRENT_CAL_DRIFT_MAGIC;
    kFlashStorage.current_cal_drift[0] = s_cal_drift[0];
    kFlashStorage.current_cal_drift[1] = s_cal_drift[1];
    kFlashStorage.current_cal_drift[2] = s_cal_drift[2];
    kFlashStorage.current_cal_drift_crc = cal_drift_crc16(s_cal_drift);
}

/* 从 kFlashStorage 尝试恢复。成功返回 true。 */
static bool cal_drift_try_restore(void)
{
    const uint16_t d[3] = {
        kFlashStorage.current_cal_drift[0],
        kFlashStorage.current_cal_drift[1],
        kFlashStorage.current_cal_drift[2],
    };

    if (kFlashStorage.current_cal_drift_magic != CURRENT_CAL_DRIFT_MAGIC)
    {
        return false;
    }
    if (kFlashStorage.current_cal_drift_crc != cal_drift_crc16(d))
    {
        return false;
    }
    /* 恢复出来的漂移还要过一遍量程检查，防止存进去的是脏数据 */
    for (uint32_t i = 0; i < 3U; i++)
    {
        float center_current = bsp_raw_to_current(d[i], (uint16_t)UVW_CURRENT_MID_VAL);

        if (center_current > CURRENT_CALIBRATION_LIMIT || center_current < -CURRENT_CALIBRATION_LIMIT)
        {
            return false;
        }
    }
    s_cal_drift[0] = d[0];
    s_cal_drift[1] = d[1];
    s_cal_drift[2] = d[2];
    s_cal_status = CURRENT_CALIBRATION_STATUS_OK;
    s_hardware_self_test_status = true;
    return true;
}

/* 公开接口：上电初始化（在 FlashDB 读完参数之后）调用一次 */
void bsp_current_calibration_restore_from_flash(void)
{
    (void)cal_drift_try_restore();
}
#endif

#if defined(PORT_PATCH_ELEC_BIAS_STORE_FLASH) && (PORT_PATCH_ELEC_BIAS_STORE_FLASH)
/* [移植补丁 16] 电角度零点标定值的 Flash 持久化。
 *
 * 背景：原程序电角度零点靠"每次上电跑一次电角度辨识"现场获得，辨识不可靠时
 * 零点会错（甚至反相 180° 导致速度环正反馈飞车）。本板先在头文件写死实测标定值
 * （PMSM_ELEC_ANGLE_BIAS_RAD）顶着，但那是编译期常量、改一次就得重刷固件。
 *
 * 做法：把标定值 + 魔数 + 校验存进 kFlashStorage（随 AllParam 那条 KV 走 SysCmd=2 落盘）。
 * 上电时若校验通过且值在合理范围，就用 Flash 里的值覆盖头文件静态值；
 * 否则保留头文件默认值。这样以后标定一次、存盘，就再也不依赖重刷固件。
 *
 * 零点合理范围：0~2π（弧度）。超出即视为脏数据（含 NaN 判断）。 */
#define CURRENT_ELEC_BIAS_MAGIC   (0x454C4231UL)   /* 'ELB1' */

static uint16_t elec_bias_crc16(float bias)
{
    union { float f; uint32_t u; } v;
    uint16_t crc = 0x3C3CU;

    v.f = bias;
    crc = (uint16_t)(crc ^ (uint16_t)(v.u & 0xFFFFU));
    crc = (uint16_t)((crc << 7) | (crc >> 9));
    crc = (uint16_t)(crc ^ (uint16_t)((v.u >> 16) & 0xFFFFU));
    crc = (uint16_t)((crc << 7) | (crc >> 9));
    return crc;
}

/* 保存电角度零点到 RAM 影子（落盘由 SysCmd=2 触发 flash_param_update） */
void bsp_elec_bias_store_to_shadow(float bias_rad)
{
    kFlashStorage.elec_angle_bias_magic = CURRENT_ELEC_BIAS_MAGIC;
    kFlashStorage.elec_angle_bias_rad = bias_rad;
    kFlashStorage.elec_angle_bias_crc = elec_bias_crc16(bias_rad);
}

/* 从 Flash 尝试恢复电角度零点。成功返回 true 并写入 out_bias_rad。 */
bool bsp_elec_bias_restore_from_flash(float *out_bias_rad)
{
    float bias = kFlashStorage.elec_angle_bias_rad;

    if (kFlashStorage.elec_angle_bias_magic != CURRENT_ELEC_BIAS_MAGIC)
    {
        return false;
    }
    if (kFlashStorage.elec_angle_bias_crc != elec_bias_crc16(bias))
    {
        return false;
    }
    /* 合理性检查：弧度必须落在 0~2π 且非 NaN（NaN 与自身比较恒不等） */
    if (!((bias >= 0.0f) && (bias < 6.2832f)))
    {
        return false;
    }
    *out_bias_rad = bias;
    return true;
}
#endif

static VOLTAGE_CHECK_STATUS s_bus_check_status = VOLTAGE_STATUS_UNKNOWN;
static uint32_t s_bus_under_cnt;
static uint32_t s_bus_normal_cnt;

/* 电流换算：raw - 零点 -> A。方向由 UVW_CURRENT_DIRECTION 决定，L0 阶段实测确认。 */
static float bsp_raw_to_current(uint16_t raw, uint16_t drift)
{
    return UVW_CURRENT_DIRECTION * (float)((int32_t)raw - (int32_t)drift) * UVW_CURRENT_SAMP_ADC_K;
}

void bsp_system_reset(void)
{
    /* 关全局中断后等看门狗复位，保留当前现场供调试观察。 */
    bsp_system_global_irq_disable();
    while (1)
    {
    }
}

void bsp_system_global_irq_enable(void)
{
    enable_global_irq(CSR_MSTATUS_MIE_MASK);
}

void bsp_system_global_irq_disable(void)
{
    disable_global_irq(CSR_MSTATUS_MIE_MASK);
}

void sys_set_bsp_error_state(BSP_ERROR_CODE type, BSP_ERROR_OPERATION op)
{
    if (type >= ERROR_MAX)
    {
        return;
    }
    if (op == ERROR_SET)
    {
        s_bsp_error.code |= (1UL << type);
    }
    else
    {
        s_bsp_error.code &= ~(1UL << type);
    }
}

void sys_get_bsp_error_state(BspErrorCode_t **p_bsp_error)
{
    *p_bsp_error = &s_bsp_error;
}

bool sys_get_hardware_self_test_status(void)
{
    return s_hardware_self_test_status;
}

/* 母线电压检查：连续计数去抖，避免开关瞬间误判。 */
VOLTAGE_CHECK_STATUS sys_bus_voltage_check(void)
{
    float bus_voltage = bsp_get_dc_bus_voltage();

    if (bus_voltage < UNDER_VOLTAGE_PROTECTION_V)
    {
        s_bus_normal_cnt = 0U;
        if (++s_bus_under_cnt > BUS_UNDER_COUNT)
        {
            s_bus_check_status = VOLTAGE_STATUS_ERROR;
            s_bus_under_cnt = 0U;
        }
    }
    else if (bus_voltage > OVER_VOLTAGE_PROTECTION_V)
    {
        s_bus_normal_cnt = 0U;
        s_bus_check_status = VOLTAGE_STATUS_ERROR;
    }
    else
    {
        s_bus_under_cnt = 0U;
        if (++s_bus_normal_cnt > BUS_NORMAL_COUNT)
        {
            s_bus_check_status = VOLTAGE_STATUS_NORMAL;
            s_bus_normal_cnt = 0U;
        }
    }
    return s_bus_check_status;
}

/*
 * 电流零漂校准：**必须在桥臂放开、相电压为 0 的状态下采样**。
 *
 * 原因：电流运放的零点随共模电压变化（采样电阻与低边管导通与否，共模差约 0.5V），
 * 桥臂封锁时测到的零点比运行时偏 0.1~0.2A。用封锁时的零点去算运行电流，三相之和不为零，
 * 电流环会把这个假偏置当真误差，积分很快顶到电压限幅，一使能就过流保护。
 *
 * 条件：桥臂已放开（低边管按 50% 占空比导通）且三相电压指令接近 0。
 * 上一次的错误结果不作为终点，下一次调用重新开始累计，避免一次上电失败把桥臂永久锁死。
 */
void sys_current_calibration_step(void)
{
    uint16_t drift[3];
    float vmax = 0.0f;

    if (s_cal_status == CURRENT_CALIBRATION_STATUS_OK)
    {
        return;
    }
    for (uint32_t i = 0; i < 3U; i++)
    {
        float v = kBspData.uvw_target_voltage[i];
        if (v < 0.0f)
        {
            v = -v;
        }
        if (v > vmax)
        {
            vmax = v;
        }
    }
    if (!bsp_get_pwm_state() || vmax > CALIBRATION_ZERO_VOLTAGE_MAX_V)
    {
        /* 条件不满足：清掉半截数据，等下一次进来重新开始 */
        s_cal_status = CURRENT_CALIBRATION_STATUS_READY;
        s_cal_sum[0] = s_cal_sum[1] = s_cal_sum[2] = 0U;
        s_cal_count = 0U;
        return;
    }
    if (s_cal_status != CURRENT_CALIBRATION_STATUS_READY)
    {
        s_cal_status = CURRENT_CALIBRATION_STATUS_READY;
        s_cal_sum[0] = s_cal_sum[1] = s_cal_sum[2] = 0U;
        s_cal_count = 0U;
    }

    s_cal_sum[0] += kBspData.adc_u_raw;
    s_cal_sum[1] += kBspData.adc_v_raw;
    s_cal_sum[2] += kBspData.adc_w_raw;
    if (++s_cal_count < CURRENT_CALIBRATION_TIMES)
    {
        return;
    }
    for (uint32_t i = 0; i < 3U; i++)
    {
        drift[i] = (uint16_t)(s_cal_sum[i] / CURRENT_CALIBRATION_TIMES);
    }
    /* 三路都要在合理零点附近，单看一路会漏掉另外两路的采样故障。 */
    for (uint32_t i = 0; i < 3U; i++)
    {
        float center_current = bsp_raw_to_current(drift[i], (uint16_t)UVW_CURRENT_MID_VAL);
        if (center_current > CURRENT_CALIBRATION_LIMIT || center_current < -CURRENT_CALIBRATION_LIMIT)
        {
            s_cal_status = CURRENT_CALIBRATION_STATUS_ERR_BIG_CURRENT;
            return;
        }
    }
    s_cal_drift[0] = drift[0];
    s_cal_drift[1] = drift[1];
    s_cal_drift[2] = drift[2];
    s_cal_status = CURRENT_CALIBRATION_STATUS_OK;
    /* 自检通过：零漂可信即可参与使能判定，母线是否正常由 sys_bus_voltage_check 单独跟踪。 */
    s_hardware_self_test_status = true;
#if defined(PORT_PATCH_CAL_DRIFT_STORE_FLASH) && (PORT_PATCH_CAL_DRIFT_STORE_FLASH)
    /* [移植补丁 14] 标定成功→写入影子结构，SysCmd=2 时随 AllParam 一起落盘 */
    cal_drift_store_to_shadow();
#endif
    /* 注意：这里不能 printf。本函数会被 1ms 中断调用，而 newlib 的 printf 带 stdout 锁，
     * 主循环正在打印时被中断打断就会死等同一把锁（现场表现为串口卡死后不再响应）。
     * 校准结果由 sys_get_current_calibration_drift() 读，打印交给主循环里的调试台。 */
}

CURRENT_CALIBRATION_STATUS sys_get_current_calibration_status(void)
{
    return s_cal_status;
}

void sys_get_current_calibration_drift(uint16_t *drift)
{
    drift[0] = s_cal_drift[0];
    drift[1] = s_cal_drift[1];
    drift[2] = s_cal_drift[2];
}

void bsp_set_pwm_state(bool state)
{
    if (state)
    {
        /* 开波这一层不再做"零漂未校准就不许开波"的门禁。
         *
         * 原因：零漂标定本身要求桥臂已放开、相电压为 0 才能采到运行时零点
         * （见 sys_current_calibration_step 的说明），如果开波反过来又要求校准已完成，
         * 就形成互锁：标定等开波、开波等标定。一旦上电自检那次标定没成功，
         * 之后永远开不了波；而调用方（motor_ctl_loop）又只在失能->使能的单个上升沿
         * 请求一次开波，于是状态机停在 ENABLE、hw_ready_state 恒 0、ModeRun 永不执行，
         * 表现为"辨识一直卡在辨识中"。
         *
         * "能不能跑模式"的判据保留在 hw_ready_state（= PWM 已开 && 校准 OK）里，
         * 由控制层自己决定是否执行模式运算，不需要在这里挡。
         */
        board_set_pwm_enable(true);
    }
    else
    {
        /* 封锁桥臂不作废零漂：零点标定的是采样通路本身，与桥臂开关无关
         * （上电时就是在桥臂放开、电压为零的条件下标定的，见 sys_current_calibration_step）。 */
        board_set_pwm_enable(false);
    }
}

bool bsp_get_pwm_state(void)
{
    return board_get_pwm_state();
}

void bsp_pwm_ready_state_updata(void)
{
    if (kBspData.pwm_en_state)
    {
        kBspData.pwm_state_cnt++;
        kBspData.pwm_ready_state = (kBspData.pwm_state_cnt > DRIVER_PWM_READY_TIME);
    }
    else
    {
        kBspData.pwm_state_cnt = 0U;
        kBspData.pwm_ready_state = false;
    }
}

/*
 * 三相电压 -> 占空比 -> PWMv2 影子比较值。
 * 逐相 SPWM：duty = 0.5 + V/Vbus，与 servo_hub 算法层输出 abc 电压的约定一致。
 * 比较值写法沿用现有已验证固件的中心对齐方案（三对通道，每对两个比较值）。
 */
void bsp_set_phase_voltage(const float voltage[3])
{
    static const uint32_t cmp_index[3] = {
        BOARD_BLDCPWM_CMP_INDEX_0, BOARD_BLDCPWM_CMP_INDEX_2, BOARD_BLDCPWM_CMP_INDEX_4,
    };
    float vbus = kBspData.dc_bus_voltage_val;

    if (vbus < 8.0f)
    {
        return;
    }
    kBspData.uvw_target_voltage[0] = voltage[0];
    kBspData.uvw_target_voltage[1] = voltage[1];
    kBspData.uvw_target_voltage[2] = voltage[2];

    uint32_t reload = board_get_pwm_reload();
    uint32_t cmp_full = (uint32_t)((float)reload * 0.98f);
    uint32_t reload_half = reload >> 1U;

    pwmv2_shadow_register_unlock(BOARD_BLDCPWM);
    for (uint32_t i = 0; i < 3U; i++)
    {
        float duty = 0.5f + voltage[i] / vbus;

        /* NaN/Inf 保护：电流环内部一旦出现 0/0，占空比会变成 NaN，
         * 而 NaN 与任何数比较都返回假，下面的限幅拦不住它，
         * 转成 uint32_t 时又是未定义行为。这里直接回中性占空比。 */
        if (!isfinite(duty))
        {
            duty = 0.5f;
            kBspData.uvw_target_voltage[i] = 0.0f;
        }
        if (duty > CURRENT_CTL_CONFIG_PWM_DUTY_CYCLE_MAX)
        {
            duty = CURRENT_CTL_CONFIG_PWM_DUTY_CYCLE_MAX;
        }
        if (duty < (1.0f - CURRENT_CTL_CONFIG_PWM_DUTY_CYCLE_MAX))
        {
            duty = 1.0f - CURRENT_CTL_CONFIG_PWM_DUTY_CYCLE_MAX;
        }
        uint32_t cmp_half = (uint32_t)(duty * (float)cmp_full) >> 1U;
        pwmv2_set_shadow_val(BOARD_BLDCPWM, cmp_index[i] + 1U, reload_half - cmp_half, 0, false);
        pwmv2_set_shadow_val(BOARD_BLDCPWM, cmp_index[i] + 2U, reload_half + cmp_half, 0, false);
    }
    pwmv2_shadow_register_lock(BOARD_BLDCPWM);
}

void bsp_get_phase_current(float piabc[3])
{
    uint16_t drift[3];

    if (!bsp_get_pwm_state())
    {
        piabc[0] = 0.0f;
        piabc[1] = 0.0f;
        piabc[2] = 0.0f;
        return;
    }
    sys_get_current_calibration_drift(drift);
    kBspData.uvw_current[0] = bsp_raw_to_current(kBspData.adc_u_raw, drift[0]);
    kBspData.uvw_current[1] = bsp_raw_to_current(kBspData.adc_v_raw, drift[1]);
    kBspData.uvw_current[2] = bsp_raw_to_current(kBspData.adc_w_raw, drift[2]);
    piabc[0] = kBspData.uvw_current[0];
    piabc[1] = kBspData.uvw_current[1];
    piabc[2] = kBspData.uvw_current[2];
}

float bsp_get_dc_bus_voltage(void)
{
    kBspData.dc_bus_voltage_val = (float)kBspData.adc_vbus_raw * DC_BUS_ADC_VOLTAGE_K + DC_BUS_ADC_VOLTAGE_BIAS;
    return kBspData.dc_bus_voltage_val;
}

float bsp_get_dc_bus_current(void)
{
    /* 本板没有独立的母线电流采样电阻：用三相电流重构功率 / 母线电压。
     * 首版返回 0，需要母线电流保护时再接 CP(PF9) 通道。 */
    return 0.0f;
}

float bsp_get_motor_temp(void)
{
    /* 温度通道还没接：PF08 在 HPM6E80 上只有数字复用（UART/I2C/SPI/MCAN/PWM…），
     * 没有 ADC 通道，说明原理图上标的 NTC1 不是这个脚。真实引脚未确证前这里返回
     * 常温，让应用层的过温/欠温检查通过；否则 motor_temp 恒 -50℃，会命中
     * AppTooLowTemperatureMotorErrorCheck，应用层每 1ms 下发一次失能，
     * 上位机永远使不了能。找到实际 NTC 引脚后改回 ADC 换算。 */
    kBspData.motor_temp_val = 25.0f;
    return kBspData.motor_temp_val;
}

float bsp_get_mos_temperature(void)
{
    /* 本板只有 NTC1 一个温度节点（MCP9700），MOS/MCU 无独立传感器。
     * 返回 0℃ 落在保护区间内，不会误触发。 */
    return 0.0f;
}

float bsp_get_mcu_temperature(void)
{
    return 0.0f;
}

uint16_t bsp_get_user_adc1_val(void)
{
    return 0U;
}

void bsp_calc_brake_pwm_timer_param(bool is_pwm_adjust, float pwm_freq, float rated_voltage,
                                   float release_action_voltage, float release_hold_voltage)
{
    (void)is_pwm_adjust;
    (void)pwm_freq;
    (void)rated_voltage;
    (void)release_action_voltage;
    (void)release_hold_voltage;
}

void bsp_set_brake_pwm_timer_config(APP_BRAKE_STATE brake_state)
{
    /* 原理图中 BRAKE 网络到 Q12 栅极的连接未确证（见 PORTING_HPM6E80.md），首版空实现。 */
    (void)brake_state;
}

/* ---------------------------------------------------------------------------
 * 编码器
 * ------------------------------------------------------------------------- */

void bsp_set_encoder_config(ENCODER_ID const enc_id, uint16_t const type, uint8_t const options,
                            uint32_t const a_single_res, uint32_t const a_single_res_real, uint32_t const a_multi_res,
                            uint32_t const b_single_res, uint32_t const b_single_res_real, uint32_t const b_multi_res)
{
    (void)enc_id;
    (void)type;
    (void)options;
    (void)a_single_res;
    (void)a_single_res_real;
    (void)a_multi_res;
    (void)b_single_res;
    (void)b_single_res_real;
    (void)b_multi_res;
    /* MT6816 是固定 14bit，不需要运行期配置；接口保留以匹配 bsp_api.h。 */
}

bool bsp_get_encoder_state(ENCODER_ID const enc_id)
{
    return drv_encoder_get_state(enc_id);
}

uint32_t bsp_get_encoder_cnt(ENCODER_ID const enc_id)
{
    return drv_encoder_get_cnt(enc_id);
}

int64_t bsp_get_encoder_turns(ENCODER_ID const enc_id)
{
    return drv_encoder_get_turns(enc_id);
}

uint8_t bsp_get_encoder_type(ENCODER_ID enc_id)
{
    return drv_encoder_get_type(enc_id);
}

bool bsp_get_encoder_zero_crossing_state(ENCODER_ID const enc_id)
{
    (void)enc_id;
    return false;
}

/* ---------------------------------------------------------------------------
 * 通信：首版只保留接口，CAN 收发在 EtherCAT/CAN 阶段接入
 * ------------------------------------------------------------------------- */

static uint32_t s_can_id;
static uint32_t s_can_baudrate;
static uint32_t s_can_mg_counts;
static uint8_t s_can_mav_sys_id;
static uint8_t s_can_mav_comp_id;

void bsp_set_can_id(uint32_t can_id)
{
    s_can_id = can_id;
}

uint32_t bsp_get_can_id(void)
{
    return s_can_id;
}

void bsp_set_can_baudrate(uint32_t baudrate)
{
    s_can_baudrate = baudrate;
}

uint32_t bsp_get_can_baudrate(void)
{
    return s_can_baudrate;
}

uint32_t bsp_get_can_mg_counts(void)
{
    return s_can_mg_counts;
}

void bsp_set_can_mav_id(uint8_t sys_id, uint8_t comp_id)
{
    s_can_mav_sys_id = sys_id;
    s_can_mav_comp_id = comp_id;
}

void bsp_get_can_mav_id(uint8_t *sys_id, uint8_t *comp_id)
{
    *sys_id = s_can_mav_sys_id;
    *comp_id = s_can_mav_comp_id;
}

/* ---------------------------------------------------------------------------
 * 参数存储：本板还没有 flash 分区，先做成"内存版"——注册的缓冲区本身就是存储，
 * read/write 是空操作，掉电丢参数。
 *
 * 为什么不能直接返回错误：应用层的错误检查表里有 AppFlashStoreErrorCheck
 * （app_status_check.c 的 CheckTable），一旦存储返回错误，AppStatusCheck 每 1ms
 * 就会调一次 set_app_Controlword(APP_CTRL_DISABLE)，上位机永远使能不了电机。
 *
 * 接真 FlashDB 的路径见移植文档第 6 节：board_public/flash_db 的源码是齐的，
 * 缺的是 fal_flash 端口（HPM XPI NOR 分区），以及"从 NOR 上执行时擦写同一片 NOR"
 * 的处理（要走 ROM API 把算法搬到 ILM 执行）。
 * ------------------------------------------------------------------------- */
#define BSP_STORE_MAX_KEYS  (4U)

typedef struct
{
    const char *key;
    void *value;
    size_t value_len;
    bool registered;
} bsp_store_item_t;

static bsp_store_item_t s_store[BSP_STORE_MAX_KEYS];

FLASHDB_STATUS bsp_flashdb_init(void)
{
    return FLASHDB_NO_ERR;
}

FLASHDB_STATUS bsp_flashdb_read(FLASHDB_KEY_INDEX const index)
{
    /* 值一直就在注册时给的那块内存里，不需要搬 */
    if (((uint32_t)index >= BSP_STORE_MAX_KEYS) || !s_store[index].registered)
    {
        return FLASHDB_READ_ERR;
    }
    return FLASHDB_NO_ERR;
}

FLASHDB_STATUS bsp_flashdb_write(FLASHDB_KEY_INDEX const index)
{
    if (((uint32_t)index >= BSP_STORE_MAX_KEYS) || !s_store[index].registered)
    {
        return FLASHDB_WRITE_ERR;
    }
    return FLASHDB_NO_ERR;
}

FLASHDB_STATUS bsp_flashdb_key_register(FLASHDB_KEY_INDEX const index, char *key, void *value, size_t value_len)
{
    if (((uint32_t)index >= BSP_STORE_MAX_KEYS) || (value == NULL))
    {
        return FLASHDB_READ_ERR;
    }

    s_store[index].key = key;
    s_store[index].value = value;
    s_store[index].value_len = value_len;
    s_store[index].registered = true;
    return FLASHDB_NO_ERR;
}

FLASHDB_STATUS bsp_flashdb_key_delete(FLASHDB_KEY_INDEX const index)
{
    if ((uint32_t)index >= BSP_STORE_MAX_KEYS)
    {
        return FLASHDB_ERASE_ERR;
    }

    s_store[index].registered = false;
    return FLASHDB_NO_ERR;
}

/* ---------------------------------------------------------------------------
 * 其它
 * ------------------------------------------------------------------------- */

static bool s_gpio_ready;

static void bsp_gpio_init_once(void)
{
    if (s_gpio_ready)
    {
        return;
    }
    /* 本板无独立 DI/DO 接口板：限位/原点/互锁暂按未接线处理（读回 false）。
     * 按键 KEYA/KEYB/KEYC = PC14/PC15/PC19，按下为低，需要时在这里配输入。 */
    s_gpio_ready = true;
}

bool bsp_get_digital_input_state(DIGITAL_INPUTS_IO_BIT const io)
{
    (void)io;
    bsp_gpio_init_once();
    return false;
}

void bsp_set_digital_output_state(DIGITAL_OUTPUTS_IO_BIT const io, bool state)
{
    (void)io;
    (void)state;
    bsp_gpio_init_once();
}

void bsp_sys_blocking_delay_us(uint32_t us)
{
    sys_blocking_delay_us(us);
}

void bsp_sys_blocking_delay_ms(uint32_t ms)
{
    sys_blocking_delay_ms(ms);
}

void bsp_set_timer_record_start(SYS_TIMER_RECORD_INDEX index)
{
    set_timer_record_start(index);
}

void bsp_set_timer_record_stop(SYS_TIMER_RECORD_INDEX index)
{
    set_timer_record_stop(index);
}

float bsp_get_timer_duration_records_us(SYS_TIMER_RECORD_INDEX index)
{
    return get_timer_duration_records_us(index);
}

/* LED：LED_G=PB24，LED_R=PB25，经 2N7002 低边驱动，高电平点亮。 */
static void bsp_led_write(uint32_t pad, uint32_t pin, bool on)
{
    HPM_IOC->PAD[pad].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(0);
    gpio_set_pin_output_with_initial(HPM_GPIO0, GPIO_DI_GPIOB, pin, on ? 1U : 0U);
}

void bsp_set_run_led_state(uint8_t state)
{
    bsp_led_write(IOC_PAD_PB24, 24U, state != 0U);
}

static bool s_run_led_on;

void bsp_set_run_led_toggle(void)
{
    s_run_led_on = !s_run_led_on;
    bsp_set_run_led_state(s_run_led_on ? 1U : 0U);
}

void bsp_set_error_led_state(uint8_t state)
{
    bsp_led_write(IOC_PAD_PB25, 25U, state != 0U);
}

static bool s_error_led_on;

void bsp_set_error_led_toggle(void)
{
    s_error_led_on = !s_error_led_on;
    bsp_set_error_led_state(s_error_led_on ? 1U : 0U);
}

void bsp_set_file_transfer_config(uint8_t file_type, uint32_t file_size, uint8_t file_dir)
{
    (void)file_type;
    (void)file_size;
    (void)file_dir;
}

void bsp_set_fw_upgrade_config(uint8_t fw_mode)
{
    (void)fw_mode;
}

void bsp_set_fw_upgrade_write(uint16_t const index, uint16_t const length, void const *data)
{
    (void)index;
    (void)length;
    (void)data;
}

uint32_t bsp_get_fw_file_index_complete(void)
{
    return 0U;
}

APP_FILE_STATUS bsp_get_fw_file_status(void)
{
    return APP_FILE_STATUS_IDLE;
}

int8_t bsp_get_fw_operating_steps(void)
{
    return 0;
}

void bsp_run_fw_upgrade(void)
{
}
