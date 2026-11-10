#include "servo_console.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hpm_debug_console.h"

#include "bsp_api.h"
#include "drv_encoder.h"
#include "motor_ctl_loop.h"
#include "servo_board.h"
#include "system_timer.h"

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
#if defined(PORT_PATCH_ENABLE_ECAT) && (PORT_PATCH_ENABLE_ECAT)
    /* EtherCAT 从站状态（精简版）：AL 状态/错误码、过程数据长度、链路状态、DC 节拍 */
    {
        extern unsigned char nAlStatus;
        extern bool ecat_dc_is_active(void);
        extern volatile uint32_t ecat_dc_cycle_cnt;
        extern volatile uint32_t ecat_dc_period_us;
        extern volatile uint32_t ecat_dc_period_min_us;
        extern volatile uint32_t ecat_dc_period_max_us;

        printf("ecat  : nAl=0x%02X code=0x%04X PDO=%u/%u DL=0x%04X WDG=0x%04X\r\n",
               (unsigned)nAlStatus,
               (unsigned)(HPM_ESC->AL_STAT_CODE),
               (unsigned)(HPM_ESC->SYNCM[2].LENGTH),
               (unsigned)(HPM_ESC->SYNCM[3].LENGTH),
               (unsigned)(HPM_ESC->ESC_DL_STAT),
               (unsigned)(HPM_ESC->WDG_STAT_PDAT));

        printf("ecat  : DC=%u cyc=%lu period=%lu/%lu/%lu us (now/min/max)\r\n",
               (unsigned)(ecat_dc_is_active() ? 1U : 0U),
               (unsigned long)ecat_dc_cycle_cnt,
               (unsigned long)ecat_dc_period_us,
               (unsigned long)ecat_dc_period_min_us,
               (unsigned long)ecat_dc_period_max_us);
    }
#endif
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

/* 连续打印 N 个字符，用来看串口通道到底能吐出多少字节。 */static void cmd_burst(int argc, char *argv[])
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
