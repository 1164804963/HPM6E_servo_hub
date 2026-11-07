#include "servo_console.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hpm_debug_console.h"
#include "hpm_soc.h"
#include "hpm_adc16_regs.h"
#include "hpm_adc_v2.h"
#include "hpm_clock_drv.h"
#include "hpm_plic_drv.h"
#include "hpm_plic_regs.h"

#include "bsp_api.h"
#include "drv_encoder.h"
#include "motor_ctl_loop.h"
#include "servo_board.h"
#include "system_timer.h"

extern volatile uint32_t board_adc2_not_ready_count;

/* 一行最多 79 字符 + 结束符；超长时整行丢弃，避免半条命令被执行。 */
#define CONSOLE_LINE_MAX        (80U)
#define CONSOLE_ARG_MAX         (5U)
#define TWO_PI_F                (6.28318530718f)
#define RAD_S_TO_RPM            (9.549296585513721f)
/* MT6816 是 14bit，位置/速度指令都按这个分辨率换算。 */
#define ENC_CNT_PER_REV         ((float)PMSM_MOTOR_ENC_LINE_P_N)

static char s_line[CONSOLE_LINE_MAX];
static uint32_t s_line_len;
static bool s_line_overflow;
static bool s_echo;

/* 电压模式的安全上限：12V 母线，先只允许到 6V，L1 现场按需要再放开。 */
#define VOLTAGE_MODE_MAX_V      (6.0f)

static void wait_ctrl_ticks(uint32_t ticks)
{
    uint32_t start = board_get_ctrl_tick();
    uint32_t guard = 0U;

    while ((board_get_ctrl_tick() - start) < ticks)
    {
        if (++guard > 4000000U)   /* 节拍没起来时不要卡死主循环 */
        {
            printf("console: ctrl tick not running\r\n");
            return;
        }
    }
}

static bool get_float_arg(char *argv[], int argc, int index, float *value)
{
    if (argc <= index)
    {
        return false;
    }
    *value = strtof(argv[index], NULL);
    return true;
}

/* ---------------------------------------------------------------------------
 * 状态打印
 * ------------------------------------------------------------------------- */
static void print_status(void)
{
    uint16_t drift[3];
    float iabc[3];
    float rpm_now;

    sys_get_current_calibration_drift(drift);
    if (bsp_get_pwm_state())
    {
        bsp_get_phase_current(iabc);
    }
    else
    {
        iabc[0] = iabc[1] = iabc[2] = 0.0f;
    }
    rpm_now = kAxis.pos_speed_ctl_input.speed_now_rad_s * RAD_S_TO_RPM;

    printf("--- servo ---\r\n");
    printf("adc   : U=%u V=%u W=%u vbus=%u  drift=%u/%u/%u\r\n",
           (unsigned)kBspData.adc_u_raw, (unsigned)kBspData.adc_v_raw,
           (unsigned)kBspData.adc_w_raw, (unsigned)kBspData.adc_vbus_raw,
           (unsigned)drift[0], (unsigned)drift[1], (unsigned)drift[2]);
    /* 温度通道（PF8）还没进 ADC 队列，raw 恒为 0，此时读数无意义，一起打出来便于区分。 */
    printf("power : vbus=%.2fV (ctrl %.2fV) motor_temp=%.1fC (temp_raw=%u)\r\n",
           bsp_get_dc_bus_voltage(), kAxis.current_ctl_input.dc_bus_now_V,
           bsp_get_motor_temp(), (unsigned)kBspData.adc_temp_raw);
    printf("iabc  : %+.3f %+.3f %+.3f A   idq=%+.3f %+.3f A\r\n",
           iabc[0], iabc[1], iabc[2],
           kAxis.current_ctl_output.idq_now_A[0], kAxis.current_ctl_output.idq_now_A[1]);
    printf("uabc  : cmd %+.2f %+.2f %+.2f V   out %+.2f %+.2f %+.2f V\r\n",
           kAxis.current_ctl_input.uabc_tar_V[0],
           kAxis.current_ctl_input.uabc_tar_V[1],
           kAxis.current_ctl_input.uabc_tar_V[2],
           kAxis.current_ctl_output.uabc_tar_comp_V[0],
           kAxis.current_ctl_output.uabc_tar_comp_V[1],
           kAxis.current_ctl_output.uabc_tar_comp_V[2]);
    printf("enc   : cnt=%u turns=%d elec=%+.3f rad  spd=%+.1f rpm pos=%ld p\r\n",
           (unsigned)bsp_get_encoder_cnt(ENCODER_ID_MOTOR),
           (int)bsp_get_encoder_turns(ENCODER_ID_MOTOR),
           kAxis.motor_pos_sensor_output.elec_angle_now_rad,
           rpm_now,
           (long)kAxis.pos_speed_ctl_input.pos_now_p);
    printf("state : sm=%d mode=%d err=%u  cal=%d pwm=%d hw_ready=%d\r\n",
           (int)kAxis.motor_ctl_sm_output.state,
           (int)kAxis.motor_ctl_sm_output.mode_now,
           (unsigned)kAxis.motor_ctl_sm_output.error,
           (int)sys_get_current_calibration_status(),
           (int)bsp_get_pwm_state(),
           (int)kAxis.motor_ctl_sm_input.hw_ready_state);
    printf("loop  : cur=%.2fus pos=%.2fus  tick=%u\r\n",
           bsp_get_timer_duration_records_us(SYS_TIMER_RECORD_CURRENT_LOOP_TIME_INDEX),
           bsp_get_timer_duration_records_us(SYS_TIMER_RECORD_POSITION_LOOP_TIME_INDEX),
           (unsigned)board_get_ctrl_tick());
    printf("ident : elec_bias=%+.4f rad (%.1f deg)  elec_id=%d  idq_tar=%.2f/%.2f A\r\n",
           kAxis.motor_pos_sensor_config.elec_angle_bias_rad,
           kAxis.motor_pos_sensor_config.elec_angle_bias_rad * 57.29578f,
           (int)kAxis.elec_angle_id_output.state_now,
           kAxis.current_ctl_input.idq_tar_A[0], kAxis.current_ctl_input.idq_tar_A[1]);
    printf("target: iq_max=%.2fA spd=%+.0f rpm pos=%ld p\r\n",
           kAxis.pos_speed_ctl_input.iq_max_A,
           kAxis.pos_speed_ctl_input.speed_tar_p_s / ENC_CNT_PER_REV * 60.0f,
           (long)kAxis.pos_speed_ctl_input.pos_tar_p);
}

/* ---------------------------------------------------------------------------
 * 命令
 * ------------------------------------------------------------------------- */
static void cmd_help(int argc, char *argv[]);

static void cmd_status(int argc, char *argv[])
{
    (void)argc;
    (void)argv;
    print_status();
}

static void cmd_cal(int argc, char *argv[])
{
    uint16_t drift[3];
    float iabc[3];

    (void)argc;
    (void)argv;

    /* 零漂在上电自检里做（桥臂放开、相电压 0 的条件下），这里只报结果和当前的真实电流。
     * 现场想复测零点的话，用 mode 127 + en 让桥臂在 0V 下放开，再看 iabc 是否为 0。 */
    sys_get_current_calibration_drift(drift);
    bsp_get_phase_current(iabc);
    printf("cal: status=%d drift=%u/%u/%u (mid=%u)\r\n",
           (int)sys_get_current_calibration_status(),
           (unsigned)drift[0], (unsigned)drift[1], (unsigned)drift[2],
           (unsigned)UVW_CURRENT_MID_VAL);
    printf("cal: iabc now = %+.3f %+.3f %+.3f A (sum %+.3f A)\r\n",
           iabc[0], iabc[1], iabc[2], iabc[0] + iabc[1] + iabc[2]);
}

static void cmd_enable(int argc, char *argv[])
{
    (void)argc;
    (void)argv;
    if (kAxis.motor_ctl_sm_config.mode == MOTOR_CTL_SM_MODE_IDLE)
    {
        printf("en: mode is IDLE, set mode first (mode 2 / 3 / 1 / 127)\r\n");
        return;
    }
    /* 桥臂封锁时 1ms 节拍一直在续算零漂，这里等它到 OK 再使能，
     * 否则状态机走不到"放开桥臂"那一步。 */
    if (sys_get_current_calibration_status() != CURRENT_CALIBRATION_STATUS_OK)
    {
        uint32_t waited = 0U;
        while (sys_get_current_calibration_status() != CURRENT_CALIBRATION_STATUS_OK && waited < 2000U)
        {
            bsp_sys_blocking_delay_ms(1);
            waited++;
        }
        printf("en: waited %ums for current calibration\r\n", (unsigned)waited);
    }

    /* 状态机认 0->1 上升沿，先给一拍失能再给使能。 */
    kAxis.motor_ctl_sm_input.motor_enable = MOTOR_CTL_SM_MOTOR_DISABLE;
    wait_ctrl_ticks(40U);
    kAxis.motor_ctl_sm_input.motor_enable = MOTOR_CTL_SM_MOTOR_ENABLE;
    wait_ctrl_ticks(2000U);
    printf("en: mode=%d sm=%d pwm=%d cal=%d err=%u\r\n",
           (int)kAxis.motor_ctl_sm_config.mode,
           (int)kAxis.motor_ctl_sm_output.state,
           (int)bsp_get_pwm_state(),
           (int)sys_get_current_calibration_status(),
           (unsigned)kAxis.motor_ctl_sm_output.error);
}

static void cmd_disable(int argc, char *argv[])
{
    (void)argc;
    (void)argv;
    kAxis.motor_ctl_sm_input.motor_enable = MOTOR_CTL_SM_MOTOR_DISABLE;
    wait_ctrl_ticks(40U);
    printf("dis: sm=%d pwm=%d\r\n",
           (int)kAxis.motor_ctl_sm_output.state, (int)bsp_get_pwm_state());
}

static void cmd_clear(int argc, char *argv[])
{
    (void)argc;
    (void)argv;
    kAxis.motor_ctl_sm_input.motor_enable = MOTOR_CTL_SM_MOTOR_DISABLE;
    wait_ctrl_ticks(40U);
    kAxis.motor_ctl_sm_input.motor_enable = MOTOR_CTL_SM_MOTOR_CLEAR_ERROR;
    wait_ctrl_ticks(200U);
    kAxis.motor_ctl_sm_input.motor_enable = MOTOR_CTL_SM_MOTOR_DISABLE;
    printf("clr: sm=%d err=%u\r\n",
           (int)kAxis.motor_ctl_sm_output.state, (unsigned)kAxis.motor_ctl_sm_output.error);
}

static void cmd_mode(int argc, char *argv[])
{
    float mode;

    if (!get_float_arg(argv, argc, 1, &mode))
    {
        printf("mode: need a number, see help\r\n");
        return;
    }
    if (kAxis.motor_ctl_sm_output.state != MOTOR_CTL_SM_STATE_DISABLE)
    {
        printf("mode: disable motor first\r\n");
        return;
    }
    kAxis.motor_ctl_sm_config.mode = (int8_t)mode;
    printf("mode: %d\r\n", (int)kAxis.motor_ctl_sm_config.mode);
}

static void cmd_iqmax(int argc, char *argv[])
{
    float value;

    if (!get_float_arg(argv, argc, 1, &value))
    {
        printf("iqmax: need A\r\n");
        return;
    }
    kAxis.pos_speed_ctl_input.iq_max_A = value;
    printf("iqmax: %.2f A\r\n", kAxis.pos_speed_ctl_input.iq_max_A);
}

static void cmd_iq(int argc, char *argv[])
{
    float value;

    if (!get_float_arg(argv, argc, 1, &value))
    {
        printf("iq: need A\r\n");
        return;
    }
    if (fabsf(value) > kAxis.pmsm_config.peak_current)
    {
        printf("iq: %.2f A over peak %.2f A\r\n", value, kAxis.pmsm_config.peak_current);
        return;
    }
    kAxis.current_ctl_input.idq_tar_A[1] = value;
    printf("iq: %.2f A\r\n", value);
}

/* 电角度零点：把"电压矢量打在 0° 时转子停住的那个位置"的编码器角填进来。
 * L1 实测方法：mode 127 + en，vec 1 0 让转子对齐，读 elec 角即为该偏置。 */
static void cmd_bias(int argc, char *argv[])
{
    float deg;

    if (!get_float_arg(argv, argc, 1, &deg))
    {
        printf("bias: need deg\r\n");
        return;
    }
    kAxis.motor_pos_sensor_config.elec_angle_bias_rad = deg / 57.29578f;
    printf("bias: %.1f deg (%.4f rad)\r\n", deg,
           kAxis.motor_pos_sensor_config.elec_angle_bias_rad);
}

/* d 轴电流阶跃：转子不动，是台架上最干净的电流环阶跃测试（L2）。 */static void cmd_id(int argc, char *argv[])
{
    float value;

    if (!get_float_arg(argv, argc, 1, &value))
    {
        printf("id: need A\r\n");
        return;
    }
    if (fabsf(value) > kAxis.pmsm_config.peak_current)
    {
        printf("id: %.2f A over peak %.2f A\r\n", value, kAxis.pmsm_config.peak_current);
        return;
    }
    kAxis.current_ctl_input.idq_tar_A[0] = value;
    printf("id: %.2f A\r\n", value);
}

/* 打印若干次电流环反馈，用来量阶跃后的上升时间和稳态值。 */
static void cmd_step(int argc, char *argv[])
{
    uint32_t n = 10U;

    if (argc > 1)
    {
        n = (uint32_t)atoi(argv[1]);
    }
    for (uint32_t i = 0; i < n; i++)
    {
        printf("step %2u: id=%+.3f iq=%+.3f A  vd_vq out=%+.2f/%+.2f/%+.2f V\r\n",
               (unsigned)i,
               kAxis.current_ctl_output.idq_now_A[0],
               kAxis.current_ctl_output.idq_now_A[1],
               kAxis.current_ctl_output.uabc_tar_comp_V[0],
               kAxis.current_ctl_output.uabc_tar_comp_V[1],
               kAxis.current_ctl_output.uabc_tar_comp_V[2]);
        bsp_sys_blocking_delay_ms(2);
    }
}

static void cmd_speed(int argc, char *argv[])
{
    float rpm;

    if (!get_float_arg(argv, argc, 1, &rpm))
    {
        printf("spd: need rpm\r\n");
        return;
    }
    kAxis.pos_speed_ctl_input.speed_tar_p_s = rpm / 60.0f * ENC_CNT_PER_REV;
    printf("spd: %.0f rpm = %.0f p/s\r\n", rpm, kAxis.pos_speed_ctl_input.speed_tar_p_s);
}

static void cmd_position(int argc, char *argv[])
{
    float deg;

    if (!get_float_arg(argv, argc, 1, &deg))
    {
        printf("pos: need deg\r\n");
        return;
    }
    /* 以当前角度为起点做相对转动，台架上比绝对位置好对。 */
    kAxis.input_shaping_input.pos_cmd_p =
        kAxis.pos_speed_ctl_input.pos_now_p + (int64_t)(deg / 360.0f * ENC_CNT_PER_REV);
    printf("pos: %+.1f deg -> %ld p\r\n", deg, (long)kAxis.input_shaping_input.pos_cmd_p);
}

static void cmd_uvw(int argc, char *argv[])
{
    float u, v, w;

    if (!get_float_arg(argv, argc, 1, &u) || !get_float_arg(argv, argc, 2, &v) ||
        !get_float_arg(argv, argc, 3, &w))
    {
        printf("uvw: need 3 voltages\r\n");
        return;
    }
    if (fabsf(u) > VOLTAGE_MODE_MAX_V || fabsf(v) > VOLTAGE_MODE_MAX_V || fabsf(w) > VOLTAGE_MODE_MAX_V)
    {
        printf("uvw: |V| must be <= %.1f V\r\n", VOLTAGE_MODE_MAX_V);
        return;
    }
    kAxis.motor_ctl_sm_config.mode = MOTOR_CTL_SM_MODE_VOLTAGE;
    kAxis.current_ctl_input.uabc_tar_V[0] = u;
    kAxis.current_ctl_input.uabc_tar_V[1] = v;
    kAxis.current_ctl_input.uabc_tar_V[2] = w;
    printf("uvw: %.2f %.2f %.2f V\r\n", u, v, w);
}

static void cmd_vec(int argc, char *argv[])
{
    float amp;
    float deg;
    float theta;

    if (!get_float_arg(argv, argc, 1, &amp) || !get_float_arg(argv, argc, 2, &deg))
    {
        printf("vec: need amp and electrical angle (deg)\r\n");
        return;
    }
    if (fabsf(amp) > VOLTAGE_MODE_MAX_V)
    {
        printf("vec: |amp| must be <= %.1f V\r\n", VOLTAGE_MODE_MAX_V);
        return;
    }
    theta = deg / 360.0f * TWO_PI_F;
    kAxis.motor_ctl_sm_config.mode = MOTOR_CTL_SM_MODE_VOLTAGE;
    kAxis.current_ctl_input.uabc_tar_V[0] = amp * cosf(theta);
    kAxis.current_ctl_input.uabc_tar_V[1] = amp * cosf(theta - TWO_PI_F / 3.0f);
    kAxis.current_ctl_input.uabc_tar_V[2] = amp * cosf(theta + TWO_PI_F / 3.0f);
    printf("vec: %.2f V @ %.1f deg -> %.2f %.2f %.2f V\r\n", amp, deg,
           kAxis.current_ctl_input.uabc_tar_V[0],
           kAxis.current_ctl_input.uabc_tar_V[1],
           kAxis.current_ctl_input.uabc_tar_V[2]);
}

static void cmd_timing(int argc, char *argv[])
{
    (void)argc;
    (void)argv;
    printf("timing: current loop %.2f us, position loop %.2f us, budget 50 us\r\n",
           bsp_get_timer_duration_records_us(SYS_TIMER_RECORD_CURRENT_LOOP_TIME_INDEX),
           bsp_get_timer_duration_records_us(SYS_TIMER_RECORD_POSITION_LOOP_TIME_INDEX));
}

/* 单圈计数差值，处理 0/16384 回绕。 */
static int32_t encoder_delta(uint32_t now, uint32_t last)
{
    int32_t d = (int32_t)now - (int32_t)last;

    if (d > (int32_t)(PMSM_MOTOR_ENC_LINE_P_N / 2U))
    {
        d -= (int32_t)PMSM_MOTOR_ENC_LINE_P_N;
    }
    else if (d < -(int32_t)(PMSM_MOTOR_ENC_LINE_P_N / 2U))
    {
        d += (int32_t)PMSM_MOTOR_ENC_LINE_P_N;
    }
    return d;
}

/*
 * 编码器实测：200ms 内累计位移，折算转速。
 * L0 阶段确认编码器读数稳定、不跳变；L1 阶段看转子是否真的跟着电压矢量走。
 */
static void cmd_enc(int argc, char *argv[])
{
    uint32_t last = bsp_get_encoder_cnt(ENCODER_ID_MOTOR);
    int32_t total = 0;
    int32_t step_max = 0;
    uint32_t reversals = 0U;
    int32_t last_step = 0;

    (void)argc;
    (void)argv;

    for (uint32_t i = 0; i < 200U; i++)
    {
        uint32_t now;
        int32_t step;

        bsp_sys_blocking_delay_ms(1);
        now = bsp_get_encoder_cnt(ENCODER_ID_MOTOR);
        step = encoder_delta(now, last);
        total += step;
        if (step > step_max)
        {
            step_max = step;
        }
        if (step < -step_max)
        {
            step_max = -step;
        }
        if ((step > 0 && last_step < 0) || (step < 0 && last_step > 0))
        {
            reversals++;
        }
        if (step != 0)
        {
            last_step = step;
        }
        last = now;
    }

    printf("enc: cnt=%u turns=%d, 200ms delta=%d p = %.2f rev, %.1f rpm, max_step=%d p/ms, reversals=%u\r\n",
           (unsigned)bsp_get_encoder_cnt(ENCODER_ID_MOTOR),
           (int)bsp_get_encoder_turns(ENCODER_ID_MOTOR),
           (int)total, (double)((float)total / ENC_CNT_PER_REV),
           (double)((float)total / ENC_CNT_PER_REV * 5.0f * 60.0f),
           (int)step_max, (unsigned)reversals);
    printf("enc: elec=%+.3f rad  PLL speed=%+.1f rpm  pos_now=%ld p  spi_fail=%u\r\n",
           kAxis.motor_pos_sensor_output.elec_angle_now_rad,
           kAxis.pos_speed_ctl_input.speed_now_rad_s * RAD_S_TO_RPM,
           (long)kAxis.pos_speed_ctl_input.pos_now_p,
           (unsigned)drv_encoder_get_fail_count());
}

static void cmd_tick(int argc, char *argv[])
{
    uint32_t t0;
    uint32_t t1;

    (void)argc;
    (void)argv;
    t0 = board_get_ctrl_tick();
    bsp_sys_blocking_delay_ms(100);
    t1 = board_get_ctrl_tick();
    printf("tick: %u counts in 100 ms -> %u Hz\r\n", (unsigned)(t1 - t0), (unsigned)((t1 - t0) * 10U));
}

static void cmd_echo(int argc, char *argv[])
{
    (void)argc;
    (void)argv;
    s_echo = !s_echo;
    printf("echo: %s\r\n", s_echo ? "on" : "off");
}

static void cmd_heartbeat(int argc, char *argv[])
{
    (void)argc;
    (void)argv;
    board_heartbeat_on = !board_heartbeat_on;
    printf("heartbeat: %s\r\n", board_heartbeat_on ? "on" : "off");
}

/* ---------------------------------------------------------------------------
 * 电流环波形采集（给 L2 阶跃响应用，相当于一个 20kHz 的简易示波器）
 * ------------------------------------------------------------------------- */
#define SCOPE_MAX_POINTS    (256U)

static volatile float s_scope_id[SCOPE_MAX_POINTS];
static volatile float s_scope_iq[SCOPE_MAX_POINTS];
static volatile float s_scope_ref[SCOPE_MAX_POINTS];
static volatile uint32_t s_scope_len;
static volatile uint32_t s_scope_max;
static volatile bool s_scope_done;

/* 编码器采样序列（1kHz），用来看转起来之后角度有没有跳变。 */
static volatile uint32_t s_enc_buf[SCOPE_MAX_POINTS];
static volatile uint32_t s_enc_len;
static volatile uint32_t s_enc_max;
static volatile bool s_enc_done;

/* Raw ADC DMA snapshot. 1024 * 10 words = 40 KiB, static (no heap). */
#define ADC_CAPTURE_POINTS  (1024U)

typedef struct
{
    uint32_t raw2_u;
    uint32_t raw2_w;
    uint32_t raw3_v;
    uint32_t raw3_vbus;
    uint32_t sts2;
    uint32_t sts3;
    uint32_t seq2;
    uint32_t seq3_before;
    uint32_t seq3_after;
    uint32_t start_cycle;
} AdcCaptureSample;

static AdcCaptureSample s_adc_capture[ADC_CAPTURE_POINTS];
static volatile uint32_t s_adc_cap_len;
static volatile uint32_t s_adc_cap_max;
static volatile bool s_adc_cap_armed;
static volatile bool s_adc_cap_done;
static volatile uint32_t s_adc_cap_seq2;
static volatile uint32_t s_adc_cap_seq3;
static volatile uint32_t s_adc_cap_copy_max;
static volatile uint32_t s_adc_cap_copy_total;
static volatile uint32_t s_adc_cap_cpu_hz;

/* RISC-V mcycle low 32 bits; wraps modulo 2^32, valid for these short deltas. */
static inline uint32_t adc_capture_rdcycle(void)
{
    uint32_t v;

    __asm__ volatile ("csrr %0, mcycle" : "=r"(v) : : "memory");
    return v;
}

/* Compiler barrier only: same-core ISR/console visibility, no SMP. */
static inline void adc_capture_barrier(void)
{
    __asm__ volatile ("" ::: "memory");
}

void servo_console_isr_adc3(void)
{
    if (s_adc_cap_armed)
    {
        s_adc_cap_seq3++;
    }
}

void servo_console_isr_adc_capture(const volatile uint32_t raw2[2],
                                   const volatile uint32_t raw3[2])
{
    uint32_t n = s_adc_cap_len;
    uint32_t copy_start;
    uint32_t copy_cycles;
    AdcCaptureSample *s;

    if (!s_adc_cap_armed || (n >= s_adc_cap_max))
    {
        return;
    }

    s = &s_adc_capture[n];
    copy_start = adc_capture_rdcycle();
    s->start_cycle = copy_start;
    s->seq2 = s_adc_cap_seq2 + 1U;
    s_adc_cap_seq2 = s->seq2;
    s->seq3_before = s_adc_cap_seq3;

    /* ADC3 is the control source; seq3_before/after exposes unexpected reentry. */
    s->raw2_u = raw2[0];
    s->raw2_w = raw2[1];
    s->raw3_v = raw3[0];
    s->raw3_vbus = raw3[1];
    s->sts2 = HPM_ADC2->INT_STS;
    s->sts3 = HPM_ADC3->INT_STS;
    s->seq3_after = s_adc_cap_seq3;

    /* mcycle delta is wall time; ADC3 is the control source. */
    copy_cycles = adc_capture_rdcycle() - copy_start;
    s_adc_cap_copy_total += copy_cycles;
    if (copy_cycles > s_adc_cap_copy_max)
    {
        s_adc_cap_copy_max = copy_cycles;
    }

    s_adc_cap_len = n + 1U;
    if (s_adc_cap_len >= s_adc_cap_max)
    {
        s_adc_cap_armed = false;
        adc_capture_barrier();
        s_adc_cap_done = true;
    }
}

void servo_console_isr_encoder(uint32_t cnt)
{
    uint32_t n = s_enc_len;

    if ((s_enc_max == 0U) || (n >= s_enc_max))
    {
        return;
    }
    s_enc_buf[n] = cnt;
    s_enc_len = n + 1U;
    if (s_enc_len >= s_enc_max)
    {
        s_enc_done = true;
    }
}

/* escope <点数>：抓 1kHz 的编码器单圈计数，打印逐点差值。 */
static void cmd_escope(int argc, char *argv[])
{
    uint32_t n = 100U;
    uint32_t waited = 0U;
    uint32_t max_step = 0U;
    uint32_t big = 0U;

    if (argc > 1)
    {
        n = (uint32_t)atoi(argv[1]);
    }
    if (n > SCOPE_MAX_POINTS)
    {
        n = SCOPE_MAX_POINTS;
    }
    if (n < 4U)
    {
        n = 4U;
    }

    s_enc_max = 0U;
    s_enc_len = 0U;
    s_enc_done = false;
    s_enc_max = n;

    while (!s_enc_done && waited < 400U)
    {
        bsp_sys_blocking_delay_ms(1);
        waited++;
    }
    s_enc_max = 0U;

    printf("escope: %u pts @1kHz, %s\r\n", (unsigned)s_enc_len, s_enc_done ? "done" : "TIMEOUT");
    printf("#  t_ms  cnt   d_cnt\r\n");
    for (uint32_t i = 1U; i < s_enc_len; i++)
    {
        int32_t d = encoder_delta(s_enc_buf[i], s_enc_buf[i - 1U]);
        uint32_t ad = (uint32_t)((d < 0) ? -d : d);

        if (ad > max_step)
        {
            max_step = ad;
        }
        if (ad > 300U)
        {
            big++;
        }
        printf("%5u %5u %6d\r\n", (unsigned)i, (unsigned)s_enc_buf[i], (int)d);
    }
    printf("escope: max_step=%u, frames with |d|>300: %u/%u\r\n",
           (unsigned)max_step, (unsigned)big, (unsigned)(s_enc_len - 1U));
}

void servo_console_isr_sample(void)
{
    uint32_t n = s_scope_len;

    if ((s_scope_max == 0U) || (n >= s_scope_max))
    {
        return;
    }
    s_scope_id[n] = kAxis.current_ctl_output.idq_now_A[0];
    s_scope_iq[n] = kAxis.current_ctl_output.idq_now_A[1];
    s_scope_ref[n] = kAxis.current_ctl_input.idq_tar_A[0];
    s_scope_len = n + 1U;
    if (s_scope_len >= s_scope_max)
    {
        s_scope_done = true;
    }
}

/* scope <点数> [d轴阶跃 A]：抓一段 20kHz 电流环波形，单位 mA。
 * 带上第二个参数时，先把 d 轴目标设过去再开始采集，看到的波形就是阶跃响应。 */
static void cmd_scope(int argc, char *argv[])
{
    uint32_t n = 80U;
    uint32_t waited = 0U;

    if (argc > 1)
    {
        n = (uint32_t)atoi(argv[1]);
    }
    if (n > SCOPE_MAX_POINTS)
    {
        n = SCOPE_MAX_POINTS;
    }
    if (n < 4U)
    {
        n = 4U;
    }

    s_scope_max = 0U;          /* 先停采集，避免清缓冲时被中断写脏 */
    s_scope_len = 0U;
    s_scope_done = false;

    if (argc > 2)
    {
        float step = strtof(argv[2], NULL);

        kAxis.current_ctl_input.idq_tar_A[0] = step;
        printf("scope: id step -> %.3f A\r\n", step);
    }

    s_scope_max = n;

    while (!s_scope_done && waited < 200U)
    {
        bsp_sys_blocking_delay_ms(1);
        waited++;
    }
    s_scope_max = 0U;

    printf("scope: %u pts @20kHz, %s\r\n", (unsigned)s_scope_len, s_scope_done ? "done" : "TIMEOUT");
    printf("#  t_us  id_mA  iq_mA  ref_mA\r\n");
    for (uint32_t i = 0U; i < s_scope_len; i++)
    {
        printf("%5u %7d %7d %7d\r\n",
               (unsigned)(i * 50U),
               (int)(s_scope_id[i] * 1000.0f),
               (int)(s_scope_iq[i] * 1000.0f),
               (int)(s_scope_ref[i] * 1000.0f));
    }
}

/* Read-only ADC clock/divider/sample-cycle snapshot. No status write/clear. */
static void adcinfo_sample(const char *name, ADC16_Type *adc, uint32_t ch)
{
    uint32_t cfg = adc->SAMPLE_CFG[ch];

    printf("adcinfo: %s ch=%lu SAMPLE_CFG=0x%08lX sample_cycle=%lu shift=%lu\r\n",
           name, (unsigned long)ch, (unsigned long)cfg,
           (unsigned long)ADC16_SAMPLE_CFG_SAMPLE_CLOCK_NUMBER_GET(cfg),
           (unsigned long)ADC16_SAMPLE_CFG_SAMPLE_CLOCK_NUMBER_SHIFT_GET(cfg));
}

static void cmd_adcinfo(int argc, char *argv[])
{
    uint32_t conv2 = HPM_ADC2->CONV_CFG1;
    uint32_t conv3 = HPM_ADC3->CONV_CFG1;
    uint32_t cfg2 = HPM_ADC2->ADC_CFG0;
    uint32_t cfg3 = HPM_ADC3->ADC_CFG0;
    uint32_t cov2 = HPM_ADC2->ADC16_CONFIG1;
    uint32_t cov3 = HPM_ADC3->ADC16_CONFIG1;
    uint32_t buf2 = HPM_ADC2->BUF_CFG0;
    uint32_t buf3 = HPM_ADC3->BUF_CFG0;

    (void)argc;
    (void)argv;
    printf("adcinfo: cpu_clk=%lu Hz adc2_clk=%lu Hz adc3_clk=%lu Hz ahb0_clk=%lu Hz\r\n",
           (unsigned long)clock_get_frequency(clock_cpu0),
           (unsigned long)clock_get_frequency(clock_adc2),
           (unsigned long)clock_get_frequency(clock_adc3),
           (unsigned long)clock_get_frequency(clock_ahb0));
    printf("adcinfo: PLIC feature=0x%08lX preempt=%lu threshold=%lu ADC2_pri=%lu ADC3_pri=%lu\r\n",
           (unsigned long)HPM_PLIC->FEATURE,
           (unsigned long)PLIC_FEATURE_PREEMPT_GET(HPM_PLIC->FEATURE),
           (unsigned long)HPM_PLIC->TARGETCONFIG[HPM_PLIC_TARGET_M_MODE].THRESHOLD,
           (unsigned long)HPM_PLIC->PRIORITY[IRQn_ADC2 - 1U],
           (unsigned long)HPM_PLIC->PRIORITY[IRQn_ADC3 - 1U]);
    printf("adcinfo: ADC2_tick_not_ready=%lu\r\n",
           (unsigned long)board_adc2_not_ready_count);
    printf("adcinfo: ADC2 CONV_CFG1=0x%08lX divider_field=%lu divider=%lu conv_clk=%lu ADC_CFG0=0x%08lX sync_ahb=%lu ahb_en=%lu COV_END=%lu wait_dis=%lu\r\n",
           (unsigned long)conv2,
           (unsigned long)ADC16_CONV_CFG1_CLOCK_DIVIDER_GET(conv2),
           (unsigned long)(ADC16_CONV_CFG1_CLOCK_DIVIDER_GET(conv2) + 1U),
           (unsigned long)ADC16_CONV_CFG1_CONVERT_CLOCK_NUMBER_GET(conv2),
           (unsigned long)cfg2,
           (unsigned long)ADC16_ADC_CFG0_SEL_SYNC_AHB_GET(cfg2),
           (unsigned long)ADC16_ADC_CFG0_ADC_AHB_EN_GET(cfg2),
           (unsigned long)ADC16_ADC16_CONFIG1_COV_END_CNT_GET(cov2),
           (unsigned long)ADC16_BUF_CFG0_WAIT_DIS_GET(buf2));
    printf("adcinfo: ADC3 CONV_CFG1=0x%08lX divider_field=%lu divider=%lu conv_clk=%lu ADC_CFG0=0x%08lX sync_ahb=%lu ahb_en=%lu COV_END=%lu wait_dis=%lu\r\n",
           (unsigned long)conv3,
           (unsigned long)ADC16_CONV_CFG1_CLOCK_DIVIDER_GET(conv3),
           (unsigned long)(ADC16_CONV_CFG1_CLOCK_DIVIDER_GET(conv3) + 1U),
           (unsigned long)ADC16_CONV_CFG1_CONVERT_CLOCK_NUMBER_GET(conv3),
           (unsigned long)cfg3,
           (unsigned long)ADC16_ADC_CFG0_SEL_SYNC_AHB_GET(cfg3),
           (unsigned long)ADC16_ADC_CFG0_ADC_AHB_EN_GET(cfg3),
           (unsigned long)ADC16_ADC16_CONFIG1_COV_END_CNT_GET(cov3),
           (unsigned long)ADC16_BUF_CFG0_WAIT_DIS_GET(buf3));
    adcinfo_sample("ADC2", HPM_ADC2, BOARD_BLDC_ADC_CH_U);
    adcinfo_sample("ADC2", HPM_ADC2, BOARD_BLDC_ADC_CH_W);
    adcinfo_sample("ADC3", HPM_ADC3, BOARD_BLDC_ADC_CH_V);
    adcinfo_sample("ADC3", HPM_ADC3, BOARD_BLDC_ADC_VBUS_CH);
}

static void cmd_adccap(int argc, char *argv[])
{
    (void)argc;
    (void)argv;
    s_adc_cap_armed = false;
    s_adc_cap_len = 0U;
    s_adc_cap_done = false;
    s_adc_cap_seq2 = 0U;
    s_adc_cap_seq3 = 0U;
    s_adc_cap_copy_max = 0U;
    s_adc_cap_copy_total = 0U;
    s_adc_cap_cpu_hz = clock_get_frequency(clock_cpu0);
    s_adc_cap_max = ADC_CAPTURE_POINTS;
    adc_capture_barrier();
    s_adc_cap_armed = true;
    printf("adccap: armed %lu points; adcdump after capture completes\r\n",
           (unsigned long)ADC_CAPTURE_POINTS);
}

/* Full raw rows, no statistics-only replacement. Incomplete dump never waits. */
static void cmd_adcdump(int argc, char *argv[])
{
    adc_v2_handle_t adc2 = HPM_ADC_V2_HANDLE(BOARD_BLDC_ADC_U_BASE);
    adc_v2_handle_t adc3 = HPM_ADC_V2_HANDLE(BOARD_BLDC_ADC_V_BASE);

    (void)argc;
    (void)argv;
    if (!s_adc_cap_done || (s_adc_cap_len != s_adc_cap_max) || (s_adc_cap_max == 0U))
    {
        printf("adcdump: NOT READY n=%lu/%lu armed=%u done=%u\r\n",
               (unsigned long)s_adc_cap_len, (unsigned long)s_adc_cap_max,
               (unsigned)s_adc_cap_armed, (unsigned)s_adc_cap_done);
        return;
    }

    printf("# ADC raw capture: %lu points; seq2=control tick count; seq3b/a=ADC3 ISR count before/after raw copy\r\n",
           (unsigned long)s_adc_cap_len);
    printf("# copy mcycle low32: max=%lu mean=%lu cycles @ cpu=%lu Hz; ADC3 is the control source\r\n",
           (unsigned long)s_adc_cap_copy_max,
           (unsigned long)(s_adc_cap_copy_total / s_adc_cap_len),
           (unsigned long)s_adc_cap_cpu_hz);
    printf("# ADC2 slots: u=raw2[0], w=raw2[1]; ADC3 slots: v=raw3[0], vbus=raw3[1]\r\n");
    printf("# DMA word (ADC_SOC_IP_VERSION=3): [15:0]=result [19:16]=reserved [24:20]=adc_ch [28:25]=trig_ch [30:29]=seq_num [31]=cycle_bit; PMT DMA word has no valid bit\r\n");
    printf("# sts: b31 TRIG_CMPT b30 TRIG_SW_CFLCT b29 TRIG_HW_CFLCT b28 READ_CFLCT b22 DMA_FIFO_FULL b21 AHB_ERR; RW1C read snapshot, b31 cleared by ISR before capture\r\n");
    printf("# idx cyc seq2 seq3b seq3a u_raw w_raw v_raw vbus_raw u_ch w_ch v_ch vbus_ch u_tr w_tr v_tr vbus_tr sts2 sts3\r\n");
    for (uint32_t i = 0U; i < s_adc_cap_len; i++)
    {
        const AdcCaptureSample *s = &s_adc_capture[i];
        adc_v2_dma_sample_t u, w, v, vbus;

        hpm_adc_v2_parse_pmt_dma_word(adc2, s->raw2_u, &u);
        hpm_adc_v2_parse_pmt_dma_word(adc2, s->raw2_w, &w);
        hpm_adc_v2_parse_pmt_dma_word(adc3, s->raw3_v, &v);
        hpm_adc_v2_parse_pmt_dma_word(adc3, s->raw3_vbus, &vbus);
        printf("%4lu %10lu %5lu %5lu %5lu 0x%08lX 0x%08lX 0x%08lX 0x%08lX %2lu %2lu %2lu %2lu %2lu %2lu %2lu %2lu 0x%08lX 0x%08lX\r\n",
               (unsigned long)i, (unsigned long)s->start_cycle,
               (unsigned long)s->seq2, (unsigned long)s->seq3_before,
               (unsigned long)s->seq3_after,
               (unsigned long)s->raw2_u, (unsigned long)s->raw2_w,
               (unsigned long)s->raw3_v, (unsigned long)s->raw3_vbus,
               (unsigned long)u.adc_ch, (unsigned long)w.adc_ch,
               (unsigned long)v.adc_ch, (unsigned long)vbus.adc_ch,
               (unsigned long)u.trig_ch, (unsigned long)w.trig_ch,
               (unsigned long)v.trig_ch, (unsigned long)vbus.trig_ch,
               (unsigned long)s->sts2, (unsigned long)s->sts3);
    }
}

/* 连续打印 N 个字符，用来看串口通道到底能吐出多少字节。 */
static void cmd_burst(int argc, char *argv[])
{
    uint32_t n = 1000U;

    if (argc > 1)
    {
        n = (uint32_t)atoi(argv[1]);
    }
    for (uint32_t i = 0; i < n; i++)
    {
        printf("%c", (i % 60U == 59U) ? '\n' : (char)('0' + (i % 10U)));
    }
    printf("\r\nburst end %u\r\n", (unsigned)n);
}

/*
 * 每秒一行心跳，只在主循环里打印。
 * 不能在中断里调用 printf：newlib 的 stdout 有锁，中断打断主循环的打印后会死等这把锁。
 */
static void console_heartbeat(void)
{
    static uint32_t last_tick;
    uint32_t now;

    if (!board_heartbeat_on)
    {
        return;
    }
    now = board_get_ctrl_tick();
    if ((now - last_tick) < 20000U)
    {
        return;
    }
    last_tick = now;
    printf("[hb] tick=%u cur=%.1fus pos=%.1fus spd=%+.1frpm sm=%d pwm=%d idq=%+.2f\r\n",
           (unsigned)now,
           (double)bsp_get_timer_duration_records_us(SYS_TIMER_RECORD_CURRENT_LOOP_TIME_INDEX),
           (double)bsp_get_timer_duration_records_us(SYS_TIMER_RECORD_POSITION_LOOP_TIME_INDEX),
           (double)(kAxis.pos_speed_ctl_input.speed_now_rad_s * RAD_S_TO_RPM),
           (int)kAxis.motor_ctl_sm_output.state,
           (int)bsp_get_pwm_state(),
           (double)kAxis.current_ctl_output.idq_now_A[1]);
}

typedef struct
{
    const char *name;
    void (*run)(int argc, char *argv[]);
    const char *help;
} ConsoleCommand;

/*
 * 位置环内部量。位置模式一使能就报 err=6（位置跟随误差过大）时要看这几项：
 *   pos_tar/pos_now/offset 三者相加就是 pos_ctl_error（见 pos_speed_ctl_pip.c 的 Add1）
 *   follow_limit 是 MotorCtlSmConfig.position_following_error_protection（默认 1638 count）
 *   error_enable 的 bit5 关掉可以临时屏蔽这条保护，用来确认是不是它导致的
 */
static void cmd_pl(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    printf("pl    : pos_tar=%ld pos_now=%ld offset=%ld\r\n",
           (long)kAxis.pos_speed_ctl_input.pos_tar_p,
           (long)kAxis.pos_speed_ctl_input.pos_now_p,
           (long)kAxis.pos_speed_ctl_input.position_offset_p);
    printf("pl    : pos_ctl_error=%ld  follow_limit=%ld  error_enable=0x%04X\r\n",
           (long)kAxis.pos_speed_ctl_output.pos_ctl_error_p,
           (long)kAxis.motor_ctl_sm_config.position_following_error_protection,
           (unsigned)kAxis.motor_ctl_sm_config.error_enable);
    printf("pl    : ctl_mode=%.0f  sm_state=%d  sm_error=%u\r\n",
           (double)kAxis.pos_speed_ctl_config.mode,
           (int)kAxis.motor_ctl_sm_output.state,
           (unsigned)kAxis.motor_ctl_sm_output.error);
}

static const ConsoleCommand s_commands[] = {
    {"adcinfo", cmd_adcinfo, "print ADC clock/divider/sample registers"},
    {"adccap",  cmd_adccap,  "arm 1024 raw ADC DMA samples (non-blocking)"},
    {"adcdump", cmd_adcdump, "dump 1024 raw ADC DMA samples after adccap"},
    {"help",  cmd_help,     "打印命令表"},
    {"st",    cmd_status,   "打印运行状态"},
    {"pl",    cmd_pl,       "打印位置环内部量（pos_tar/pos_now/跟随误差/阈值）"},
    {"cal",   cmd_cal,      "打印电流零漂校准结果与当前三相电流"},
    {"en",    cmd_enable,   "使能电机（走控制层状态机）"},
    {"dis",   cmd_disable,  "失能电机"},
    {"clr",   cmd_clear,    "清除控制层错误"},
    {"mode",  cmd_mode,     "运行模式 1力矩 2速度 3位置 127电压 -4电角度辨识 -3方向辨识 -2极对数辨识"},
    {"iqmax", cmd_iqmax,    "速度/位置模式最大 q 轴电流 A"},
    {"iq",    cmd_iq,       "力矩模式目标 q 轴电流 A"},
    {"id",    cmd_id,       "力矩模式目标 d 轴电流 A（转子不动，做电流环阶跃）"},
    {"bias",  cmd_bias,     "设置电角度零点偏置（单位度，L1 对齐实测值）"},
    {"step",  cmd_step,     "连续打印 N 次 idq 反馈（默认 10 次，每次 2ms）"},
    {"spd",   cmd_speed,    "速度模式目标转速 rpm"},
    {"pos",   cmd_position, "位置模式相对当前角度转动 deg"},
    {"uvw",   cmd_uvw,      "电压模式直接给三相电压 u v w（单位 V）"},
    {"vec",   cmd_vec,      "电压模式给三相电压矢量 amp deg（电角度）"},
    {"enc",   cmd_enc,      "200ms 编码器实测：位移、折算转速、跳变"},
    {"tm",    cmd_timing,   "打印电流环/位置环耗时"},
    {"tick",  cmd_tick,     "测 20kHz 节拍实际频率"},
    {"hb",    cmd_heartbeat,"1ms/20kHz 中断心跳打印开关"},
    {"burst", cmd_burst,    "连续打印 N 个字符（默认 1000），测串口吞吐"},
    {"scope", cmd_scope,    "抓一段 20kHz 电流环 idq 波形（点数默认 128，最多 256）"},
    {"escope", cmd_escope,  "抓 1kHz 编码器计数序列，看角度有没有跳变"},
    {"echo",  cmd_echo,     "切换命令回显"},
};

static void cmd_help(int argc, char *argv[])
{
    uint32_t i;

    (void)argc;
    (void)argv;
    printf("commands:\r\n");
    for (i = 0U; i < sizeof(s_commands) / sizeof(s_commands[0]); i++)
    {
        printf("  %-6s %s\r\n", s_commands[i].name, s_commands[i].help);
    }
}

static void run_line(char *line)
{
    char *argv[CONSOLE_ARG_MAX];
    int argc = 0;
    char *p = line;
    uint32_t i;

    while (*p != '\0' && argc < (int)CONSOLE_ARG_MAX)
    {
        while (*p == ' ' || *p == '\t')
        {
            *p = '\0';
            p++;
        }
        if (*p == '\0')
        {
            break;
        }
        argv[argc++] = p;
        while (*p != '\0' && *p != ' ' && *p != '\t')
        {
            p++;
        }
    }
    if (argc == 0)
    {
        return;
    }

    for (i = 0U; i < sizeof(s_commands) / sizeof(s_commands[0]); i++)
    {
        if (strcmp(argv[0], s_commands[i].name) == 0)
        {
            s_commands[i].run(argc, argv);
            return;
        }
    }
    printf("unknown command: %s, try help\r\n", argv[0]);
}

void servo_console_init(void)
{
    s_line_len = 0U;
    s_line_overflow = false;
    s_echo = false;
    printf("\r\nservo_hub HPM6EMotorV20 console ready, type help\r\n");
    printf("servo> ");
}

/*
 * 处理一个收到的字节。串口读取由 servo_host_poll() 负责：
 * MAVLink 帧交给上位机协议，其余字节进这里当命令。
 */
void servo_console_feed(uint8_t c)
{
    if (c == '\r' || c == '\n')
    {
        printf("\r\n");
        if (!s_line_overflow)
        {
            s_line[s_line_len] = '\0';
            run_line(s_line);
        }
        s_line_len = 0U;
        s_line_overflow = false;
        printf("servo> ");
        return;
    }

    if (c == 8U || c == 127U)   /* 退格 */
    {
        if (s_line_len > 0U)
        {
            s_line_len--;
            printf("\b \b");
        }
        return;
    }

    if (s_line_len < (CONSOLE_LINE_MAX - 1U))
    {
        s_line[s_line_len++] = (char)c;
        if (s_echo)
        {
            printf("%c", c);
        }
    }
    else
    {
        s_line_overflow = true;
    }
}

/* 主循环里每圈调一次：只管心跳，收字节交给 servo_host_poll()。 */
void servo_console_poll(void)
{
    console_heartbeat();
}
