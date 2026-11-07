#include "servo_bringup.h"

#include <stdio.h>

#include "bsp_api.h"
#include "drv_encoder.h"
#include "motor_ctl_loop.h"
#include "servo_board.h"
#include "system_timer.h"

/* 编码器上电就绪的等待上限：MT6816 在控制中断里每 50us 采一帧，几十毫秒足够。 */
#define ENCODER_READY_TIMEOUT_MS    (200U)
/* ADC 第一次出数的等待上限：PWM 触发 20kHz，正常情况下几毫秒内就有值。 */
#define ADC_READY_TIMEOUT_MS        (200U)
/* 零漂校准 1024 步，1ms 一步。留一倍余量等第一次采样对齐 PWM 触发。 */
#define CALIBRATION_TIMEOUT_MS      (1500U)

static bool s_self_test_ok;

bool servo_bringup_self_test(void)
{
    uint32_t waited_ms = 0U;

    s_self_test_ok = false;

    /* 1. 编码器等第一帧有效数据，再用它的值初始化控制层位置状态。
     *    MotorCtlSmStateInit 会一次性刷新位置传感器、负载传感器和速度观测器，
     *    少了这一步位置/速度反馈的初值就是 0，后面速度环会当成一个大阶跃。 */
    while (!bsp_get_encoder_state(ENCODER_ID_MOTOR) && waited_ms < ENCODER_READY_TIMEOUT_MS)
    {
        bsp_sys_blocking_delay_ms(1);
        waited_ms++;
    }

    if (!bsp_get_encoder_state(ENCODER_ID_MOTOR))
    {
        printf("bringup: motor encoder NOT ready after %ums\r\n", (unsigned)ENCODER_READY_TIMEOUT_MS);
        sys_set_bsp_error_state(ERROR_ENCODER_MOTOR, ERROR_SET);
        return false;
    }

    MotorCtlSmStateInit(&kAxis, &kAxisDw,
                        bsp_get_encoder_turns(ENCODER_ID_MOTOR),
                        bsp_get_encoder_cnt(ENCODER_ID_MOTOR),
                        0, 0);

    /* 电角度零点：L1 标定值写在 board_public 的电机参数头里，掉电保存做好之前先在这里补上。
     * 填错 180° 时电流环仍然是"稳"的（dq 两轴一起反），但 q 轴出力方向反过来，
     * 速度环会变成正反馈，现象是电机飞转、iq 一直顶在限幅。 */
    kAxis.motor_pos_sensor_config.elec_angle_bias_rad = PMSM_ELEC_ANGLE_BIAS_RAD;

    printf("bringup: encoder ready, cnt=%u turns=%d, elec bias=%.1f deg\r\n",
           (unsigned)bsp_get_encoder_cnt(ENCODER_ID_MOTOR),
           (int)bsp_get_encoder_turns(ENCODER_ID_MOTOR),
           PMSM_ELEC_ANGLE_BIAS_DEG);

    /* 2. 三相电流零漂校准。
     *    条件：桥臂放开（低边管按 50% 占空比导通）、三相电压指令为 0。
     *    先把比较值设成 50%，再放开桥臂，此时三相电位相同、电流为 0，
     *    采到的才是"运行时"的放大器零点（原因见 bsp_api.c 里 sys_current_calibration_step 的说明）。
     *    ADC 由 PWM 触发，刚上电的前几拍可能还是 0，先等采样通道出数。 */
    waited_ms = 0U;
    while ((kBspData.adc_u_raw == 0U || kBspData.adc_v_raw == 0U || kBspData.adc_w_raw == 0U) &&
           waited_ms < ADC_READY_TIMEOUT_MS)
    {
        bsp_sys_blocking_delay_ms(1);
        waited_ms++;
    }
    printf("bringup: adc ready after %ums, raw U=%u V=%u W=%u\r\n", (unsigned)waited_ms,
           (unsigned)kBspData.adc_u_raw, (unsigned)kBspData.adc_v_raw, (unsigned)kBspData.adc_w_raw);

    {
        const float zero_voltage[3] = {0.0f, 0.0f, 0.0f};

        (void)bsp_get_dc_bus_voltage();        /* 刷新 kVbus，占空比换算要用 */
        bsp_set_phase_voltage(zero_voltage);   /* 三个比较值落到 50% 占空比 */
        board_set_pwm_enable(true);            /* 放开桥臂，此时相电压仍为 0 */
        bsp_sys_blocking_delay_ms(2);          /* 等 PWM 和 ADC 对齐 */

        waited_ms = 0U;
        while (sys_get_current_calibration_status() != CURRENT_CALIBRATION_STATUS_OK &&
               waited_ms < CALIBRATION_TIMEOUT_MS)
        {
            sys_current_calibration_step();
            bsp_sys_blocking_delay_ms(1);
            waited_ms++;
        }

        board_set_pwm_enable(false);           /* 校准完立刻封锁，等状态机使能 */
    }

    if (sys_get_current_calibration_status() != CURRENT_CALIBRATION_STATUS_OK)
    {
        printf("bringup: current calibration FAILED, status=%d\r\n",
               (int)sys_get_current_calibration_status());
        return false;
    }

    /* 母线电压：bsp_set_phase_voltage 在 8V 以下不输出，必须确认采样通路是对的。 */
    printf("bringup: zero drift done, vbus=%d mV\r\n", (int)(bsp_get_dc_bus_voltage() * 1000.0f));

    /* 控制层的欠压保护在第一个位置环周期就会检查 dc_bus_now_V（1ms 任务里的滤波值）。
     * 上电先给实测值，否则第一拍读到的 0V 会让状态机直接进欠压错误。 */
    kAxis.current_ctl_input.dc_bus_now_V = bsp_get_dc_bus_voltage();
    kAxis.current_ctl_input.driver_temp = bsp_get_mos_temperature();

    /* 速度环开启动态积分（抗积分饱和）：生成代码里这个开关 >0 时会把积分器
     * 限制在 iq_max 附近，默认 0（不限制）。速度环启动阶段 iq 长时间顶限幅，
     * 不限制的话积分会冲到很远，退饱和时反向过冲，实测表现为 65Hz 的来回荡。 */
    kAxis.pos_speed_ctl_config.dynamic_integration_enable = 1;

    s_self_test_ok = true;
    return true;
}

void servo_bringup_print_l0(void)
{
    uint16_t drift[3];

    sys_get_current_calibration_drift(drift);

    printf("L0 adc raw : U=%u V=%u W=%u vbus=%u\r\n",
           (unsigned)kBspData.adc_u_raw, (unsigned)kBspData.adc_v_raw,
           (unsigned)kBspData.adc_w_raw, (unsigned)kBspData.adc_vbus_raw);
    printf("L0 mid     : drift=%u %u %u (expect near %u)  cal=%d selftest=%d\r\n",
           (unsigned)drift[0], (unsigned)drift[1], (unsigned)drift[2],
           (unsigned)UVW_CURRENT_MID_VAL,
           (int)sys_get_current_calibration_status(),
           (int)s_self_test_ok);
    printf("L0 bus     : %d mV  (K=%.6f V/count)\r\n",
           (int)(bsp_get_dc_bus_voltage() * 1000.0f), (double)DC_BUS_ADC_VOLTAGE_K);
}
