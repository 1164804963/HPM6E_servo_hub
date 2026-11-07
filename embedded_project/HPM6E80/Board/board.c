#include "servo_board.h"

#include <stdio.h>

#include "hpm_soc.h"
#include "hpm_clock_drv.h"
#include "hpm_interrupt.h"
#include "hpm_pwmv2_drv.h"
#include "hpm_trgm_drv.h"
#include "hpm_gptmr_drv.h"
#include "hpm_adc16_drv.h"
#include "hpm_adc_v2.h"

#include "bsp_api.h"
#include "current_ctl_loop_task.h"
#include "motor_ctl_loop.h"
#include "servo_console.h"
#include "drv_encoder.h"
#include "system_timer.h"

/* 20kHz 控制节拍与上层位置速度环的比例：1kHz / 20kHz = 20 个电流环周期执行一次位置环。
 * 与 SIL_project/main.c 的 position_frq_div 保持一致，方便实板与离线对比。 */
#define CTRL_TICK_PER_POS_TICK   ((uint32_t)(CURRENT_FREQUENCY_HZ / POSITION_FREQUENCY_HZ))

/* 互补 PWM 死区，单位是 PWM 时钟周期。取自现有已验证固件（PWM_DEAD_AREA_TICK）。
 * 硬件侧 U9 STDRIVE101 的 DT/MODE 也限制了最小死区，软件不要再叠加补偿。 */
#define PWM_DEAD_AREA_TICK       (100U)

BspData kBspData;

/* ADC 预转换结果由 DMA 落在不可缓存区，两个通道各 2 个样本（U+W / V+VBUS）。
 * 索引：adc_buff[0] = ADC2(U,W)，adc_buff[1] = ADC3(V,VBUS)。 */
volatile ATTR_PLACE_AT_NONCACHEABLE_WITH_ALIGNMENT(ADC_SOC_DMA_ADDR_ALIGNMENT)
uint32_t adc_buff[2][BOARD_BLDC_ADC_PMT_DMA_SIZE_IN_4BYTES];

static uint32_t s_pwm_reload;

/* 20kHz 控制节拍是否已放行。
 * 上电时 PWM/ADC 已经在跑（编码器采样和零漂校准都要原始数据），但控制层还没初始化，
 * 所以中断里先只搬数据；main.c 把应用层初始化完再调 board_start_ctrl_tick() 打开逻辑。 */
static volatile bool s_ctrl_running;

/* 调试心跳开关，见 servo_board.h。 */
volatile bool board_heartbeat_on;

/* 上一拍的桥臂状态，用来在放开的第一拍清电流环积分。 */
static bool s_pwm_on_last;

/* 编码器采样分频（20kHz -> 1kHz）。 */
static uint32_t s_enc_div;

/* Read-only diagnostic: ADC3 control ticks skipped because ADC2 was not complete. */
volatile uint32_t board_adc2_not_ready_count;

static uint16_t adc_word_to_result(uint32_t word)
{
    /* ADC16 预转换 DMA 字的低 16 位是转换结果，其余位是通道/序号/触发源。 */
    return (uint16_t)(word & 0xFFFFU);
}

/*
 * PWM：三对互补通道 + 影子比较值 + ADC 触发。
 * 通道映射 PD00..PD05 -> UH/UL/VH/VL/WH/WL，比较值来源与触发点沿用现有已验证固件。
 */
static void board_init_pwm(void)
{
    pwmv2_cmp_config_t cmp_cfg[2] = {0};
    pwmv2_pair_config_t pwm_cfg = {0};

    s_pwm_reload = (clock_get_frequency(BOARD_BLDC_MOTOR_CLOCK_SOURCE) / (uint32_t)CURRENT_FREQUENCY_HZ) - 1U;

    pwmv2_get_default_config(&pwm_cfg.pwm[0]);
    pwmv2_get_default_config(&pwm_cfg.pwm[1]);

    cmp_cfg[0].cmp = s_pwm_reload;
    cmp_cfg[0].cmp_source = cmp_value_from_shadow_val;
    cmp_cfg[0].cmp_source_index = PWMV2_SHADOW_INDEX(1);
    cmp_cfg[0].update_trigger = pwm_shadow_register_update_on_reload;
    cmp_cfg[1].cmp = s_pwm_reload;
    cmp_cfg[1].cmp_source = cmp_value_from_shadow_val;
    cmp_cfg[1].cmp_source_index = PWMV2_SHADOW_INDEX(2);
    cmp_cfg[1].update_trigger = pwm_shadow_register_update_on_reload;

    for (uint32_t i = 0; i < 2; i++)
    {
        pwm_cfg.pwm[i].enable_output = true;
        pwm_cfg.pwm[i].enable_async_fault = false;
        pwm_cfg.pwm[i].enable_sync_fault = false;
        pwm_cfg.pwm[i].invert_output = false;
        pwm_cfg.pwm[i].enable_four_cmp = false;
        pwm_cfg.pwm[i].update_trigger = pwm_reload_update_on_reload;
        pwm_cfg.pwm[i].dead_zone_in_half_cycle = PWM_DEAD_AREA_TICK;
    }

    pwmv2_disable_counter(BOARD_BLDCPWM, pwm_counter_0);
    pwmv2_reset_counter(BOARD_BLDCPWM, pwm_counter_0);

    pwmv2_shadow_register_unlock(BOARD_BLDCPWM);
    pwmv2_set_shadow_val(BOARD_BLDCPWM, PWMV2_SHADOW_INDEX(0), s_pwm_reload, 0, false);
    pwmv2_set_shadow_val(BOARD_BLDCPWM, PWMV2_SHADOW_INDEX(9), 1, 0, false);
    pwmv2_shadow_register_lock(BOARD_BLDCPWM);

    pwmv2_setup_waveform_in_pair(BOARD_BLDCPWM, pwm_channel_0, &pwm_cfg, PWMV2_CMP_INDEX(0), &cmp_cfg[0], 2);
    cmp_cfg[0].cmp_source_index = PWMV2_SHADOW_INDEX(3);
    cmp_cfg[1].cmp_source_index = PWMV2_SHADOW_INDEX(4);
    pwmv2_setup_waveform_in_pair(BOARD_BLDCPWM, pwm_channel_2, &pwm_cfg, PWMV2_CMP_INDEX(4), &cmp_cfg[0], 2);
    cmp_cfg[0].cmp_source_index = PWMV2_SHADOW_INDEX(5);
    cmp_cfg[1].cmp_source_index = PWMV2_SHADOW_INDEX(6);
    pwmv2_setup_waveform_in_pair(BOARD_BLDCPWM, pwm_channel_4, &pwm_cfg, PWMV2_CMP_INDEX(8), &cmp_cfg[0], 2);

    pwmv2_counter_select_data_offset_from_shadow_value(BOARD_BLDCPWM, pwm_counter_0, PWMV2_SHADOW_INDEX(0));
    pwmv2_counter_burst_disable(BOARD_BLDCPWM, pwm_counter_0);
    pwmv2_set_reload_update_time(BOARD_BLDCPWM, pwm_counter_0, pwm_reload_update_on_reload);

    pwmv2_counter_select_data_offset_from_shadow_value(BOARD_BLDCPWM, pwm_counter_1, PWMV2_SHADOW_INDEX(0));
    pwmv2_counter_burst_disable(BOARD_BLDCPWM, pwm_counter_1);
    pwmv2_set_reload_update_time(BOARD_BLDCPWM, pwm_counter_1, pwm_reload_update_on_reload);

    pwmv2_counter_select_data_offset_from_shadow_value(BOARD_BLDCPWM, pwm_counter_2, PWMV2_SHADOW_INDEX(0));
    pwmv2_counter_burst_disable(BOARD_BLDCPWM, pwm_counter_2);
    pwmv2_set_reload_update_time(BOARD_BLDCPWM, pwm_counter_2, pwm_reload_update_on_reload);

    /* 触发点：计数器 = 1，即三角波底部（下桥臂全开），下桥臂 10mΩ 采样就在这里。 */
    pwmv2_select_cmp_source(BOARD_BLDCPWM, BOARD_BLDCPWM_CMP_TRIG_CMP, cmp_value_from_shadow_val,
                            PWMV2_SHADOW_INDEX(9));
    if (status_success != pwmv2_set_trigout_cmp_index(BOARD_BLDCPWM, BOARD_BLDC_PWM_TRIG_OUT_CHN,
                                                      BOARD_BLDCPWM_CMP_TRIG_CMP))
    {
        printf("board: PWM trigger cmp index setup FAILED\r\n");
        return;
    }
    pwmv2_cmp_select_counter(BOARD_BLDCPWM, BOARD_BLDCPWM_CMP_TRIG_CMP, pwm_counter_0);
    pwmv2_shadow_register_lock(BOARD_BLDCPWM);

    pwmv2_enable_multi_counter_sync(BOARD_BLDCPWM, 0x07);
    pwmv2_start_pwm_output_sync(BOARD_BLDCPWM, 0x07);
}

/* TRGM：把 PWM0 触发输出直连到 ADC 预转换触发输入。 */
static void board_init_trigger_mux(void)
{
    trgm_output_t cfg;

    cfg.invert = false;
    cfg.type = trgm_output_same_as_input;
    cfg.input = BOARD_BLDC_PWM_TRG_ADC;
    trgm_output_config(BOARD_BLDCPWM_TRGM, BOARD_BLDC_TRG_ADC, &cfg);
}

/*
 * ADC：两路预转换队列 + DMA。
 *   ADC2: U(ch5) -> W(ch6); completion is polled by the ADC3 control tick.
 *   ADC3: V(ch4) -> VBUS(ch7); the later queue completion drives the 20kHz control tick.
 * 采样时刻由 PWM 触发点决定，不要在软件里改。
 */
static void board_init_adc(void)
{
    adc_v2_config_t cfg;
    adc_v2_channel_config_t ch_cfg;
    adc_v2_handle_t adc_u = HPM_ADC_V2_HANDLE(BOARD_BLDC_ADC_U_BASE);
    adc_v2_handle_t adc_v = HPM_ADC_V2_HANDLE(BOARD_BLDC_ADC_V_BASE);

    hpm_adc_v2_get_default_config(adc_u, &cfg);
    board_init_adc_clock((void *)BOARD_BLDC_ADC_U_BASE, true);
    board_init_adc_clock((void *)BOARD_BLDC_ADC_V_BASE, true);
    cfg.resolution_bits = BOARD_BLDC_ADC_RES_BITS;
    cfg.conv_mode = adc_v2_conv_mode_preemption;
    cfg.signal_mode = adc_v2_signal_mode_single_ended;
    cfg.clock_div = BOARD_BLDC_ADC_CLOCK_DIV;
    cfg.sel_sync_ahb = false;
    hpm_adc_v2_init(adc_u, &cfg);
    hpm_adc_v2_init(adc_v, &cfg);

    hpm_adc_v2_get_channel_default_config(adc_u, &ch_cfg);
    ch_cfg.signal_mode = adc_v2_signal_mode_single_ended;
    ch_cfg.sample_cycle = BOARD_BLDC_ADC_CHANNEL_SAMPLE_CYCLE;

    ch_cfg.ch = BOARD_BLDC_ADC_CH_U;
    hpm_adc_v2_init_channel(adc_u, &ch_cfg);
    ch_cfg.ch = BOARD_BLDC_ADC_CH_W;
    hpm_adc_v2_init_channel(adc_u, &ch_cfg);

    ch_cfg.ch = BOARD_BLDC_ADC_CH_V;
    hpm_adc_v2_init_channel(adc_v, &ch_cfg);
    /* 母线 200K/10K 分压源阻抗高，采样窗口单独放宽 */
    ch_cfg.ch = BOARD_BLDC_ADC_VBUS_CH;
    ch_cfg.sample_cycle = 160U;
    hpm_adc_v2_init_channel(adc_v, &ch_cfg);

    HPM_IOC->PAD[IOC_PAD_PF31].FUNC_CTL = IOC_PAD_FUNC_CTL_ANALOG_MASK;
    HPM_IOC->PAD[IOC_PAD_PF08].FUNC_CTL = IOC_PAD_FUNC_CTL_ANALOG_MASK;   /* NTC1 */

    board_init_trigger_mux();

    adc_v2_preempt_config_t pmt_cfg = {0};
    pmt_cfg.trig_ch = BOARD_BLDC_ADC_TRG;
    pmt_cfg.trig_len = 2U;
    pmt_cfg.adc_ch[0] = BOARD_BLDC_ADC_CH_U;
    pmt_cfg.adc_ch[1] = BOARD_BLDC_ADC_CH_W;
    pmt_cfg.inten[0] = false;
    pmt_cfg.inten[1] = true;                  /* W 完成后进控制环 */
    hpm_adc_v2_set_preempt_config(adc_u, &pmt_cfg);

    pmt_cfg.adc_ch[0] = BOARD_BLDC_ADC_CH_V;
    pmt_cfg.adc_ch[1] = BOARD_BLDC_ADC_VBUS_CH;
    pmt_cfg.inten[0] = false;
    pmt_cfg.inten[1] = true;                  /* VBUS 完成后进母线中断 */
    hpm_adc_v2_set_preempt_config(adc_v, &pmt_cfg);

    hpm_adc_v2_enable_pmt_queue(adc_u, BOARD_BLDC_ADC_TRG);
    hpm_adc_v2_enable_pmt_queue(adc_v, BOARD_BLDC_ADC_TRG);
    hpm_adc_v2_init_pmt_dma(adc_u, core_local_mem_to_sys_address(BOARD_RUNNING_CORE, (uint32_t)adc_buff[0]));
    hpm_adc_v2_init_pmt_dma(adc_v, core_local_mem_to_sys_address(BOARD_RUNNING_CORE, (uint32_t)adc_buff[1]));
}

static void board_init_1ms_timer(void)
{
    gptmr_channel_config_t config;

    clock_add_to_group(BOARD_BLDC_TMR_CLOCK, 0);
    gptmr_channel_get_default_config(BOARD_BLDC_TMR_1MS, &config);
    config.cmp[0] = BOARD_BLDC_TMR_RELOAD;
    config.debug_mode = 0;
    config.reload = BOARD_BLDC_TMR_RELOAD + 1;
    gptmr_enable_irq(BOARD_BLDC_TMR_1MS, GPTMR_CH_CMP_IRQ_MASK(BOARD_BLDC_TMR_CH, BOARD_BLDC_TMR_CMP));
    gptmr_channel_config(BOARD_BLDC_TMR_1MS, BOARD_BLDC_TMR_CH, &config, true);
}

/* 1ms 硬件节拍：非实时任务 + 故障扫描。与 20kHz 控制节拍互不依赖。
 * 中断里不打印：newlib 的 printf 带锁，被中断打断会死等主循环持有的那把锁。 */
SDK_DECLARE_EXT_ISR_M(BOARD_BLDC_TMR_IRQ, isr_gptmr)
void isr_gptmr(void)
{
    if (gptmr_check_status(BOARD_BLDC_TMR_1MS, GPTMR_CH_CMP_IRQ_MASK(BOARD_BLDC_TMR_CH, BOARD_BLDC_TMR_CMP)))
    {
        gptmr_clear_status(BOARD_BLDC_TMR_1MS, GPTMR_CH_CMP_IRQ_MASK(BOARD_BLDC_TMR_CH, BOARD_BLDC_TMR_CMP));
        UnrealTimeBase1ms();
    }
}

/*
 * ADC3 V/VBUS ISR is the single control tick; ADC2 U/W is consumed here.
 * ADC3 priority 6; no ADC2 external IRQ is enabled.
 */
static void board_control_tick(void);

SDK_DECLARE_EXT_ISR_M(IRQn_ADC3, isr_adc_bus)
void isr_adc_bus(void)
{
    adc_v2_handle_t adc = HPM_ADC_V2_HANDLE(BOARD_BLDC_ADC_V_BASE);

    if ((hpm_adc_v2_get_status_flags(adc) & HPM_ADC_V2_EVENT_TRIG_COMPLETE) == 0U)
    {
        return;
    }
    hpm_adc_v2_clear_status_flags(adc, HPM_ADC_V2_EVENT_TRIG_COMPLETE);
    servo_console_isr_adc3();

    __asm__ volatile ("fence iorw, iorw" ::: "memory");
    kBspData.adc_v_raw = adc_word_to_result(adc_buff[1][BOARD_BLDC_ADC_TRG * 4U]);
    kBspData.adc_vbus_raw = adc_word_to_result(adc_buff[1][BOARD_BLDC_ADC_TRG * 4U + 1U]);

    /* ADC3 tick is the single control frame; it consumes the earlier ADC2 U/W frame. */
    board_control_tick();
}

/*
 * 逐周期过流兜底。
 * 控制层的过流保护在 1kHz 位置环里查，最坏要 1ms 才发现；电流环一旦因为
 * 电角度或电流采样异常算出大电压，1ms 足够把桥臂电流推到几安培。
 * 这里每个电流环周期都看一次实测相电流，超过驱动器限值立刻封锁桥臂并置错误位。
 */
static void board_check_over_current(void)
{
    float iabc[3];

    bsp_get_phase_current(iabc);
    if ((iabc[0] > DRIVER_OVERCURRENT_LIMIT_A) || (iabc[0] < -DRIVER_OVERCURRENT_LIMIT_A) ||
        (iabc[1] > DRIVER_OVERCURRENT_LIMIT_A) || (iabc[1] < -DRIVER_OVERCURRENT_LIMIT_A) ||
        (iabc[2] > DRIVER_OVERCURRENT_LIMIT_A) || (iabc[2] < -DRIVER_OVERCURRENT_LIMIT_A))
    {
        board_set_pwm_enable(false);
        sys_set_bsp_error_state(ERROR_BUS_CURRENT_OC, ERROR_SET);
    }
}

/*
 * One control frame per ADC3 tick. ADC2 completion is checked below;
 * no ADC2 IRQ/busy wait. All existing 20kHz/1kHz work remains here.
 */
static void board_control_tick(void)
{
    static uint32_t pos_div;

    adc_v2_handle_t adc = HPM_ADC_V2_HANDLE(BOARD_BLDC_ADC_U_BASE);

    if ((hpm_adc_v2_get_status_flags(adc) & HPM_ADC_V2_EVENT_TRIG_COMPLETE) == 0U)
    {
        board_adc2_not_ready_count++;
        return;
    }
    hpm_adc_v2_clear_status_flags(adc, HPM_ADC_V2_EVENT_TRIG_COMPLETE);

    __asm__ volatile ("fence iorw, iorw" ::: "memory");
    kBspData.adc_u_raw = adc_word_to_result(adc_buff[0][BOARD_BLDC_ADC_TRG * 4U]);
    kBspData.adc_w_raw = adc_word_to_result(adc_buff[0][BOARD_BLDC_ADC_TRG * 4U + 1U]);

    /* Raw copy only while adccap is armed; status registers are read inside that branch. */
    servo_console_isr_adc_capture(&adc_buff[0][BOARD_BLDC_ADC_TRG * 4U],
                                  &adc_buff[1][BOARD_BLDC_ADC_TRG * 4U]);

    kBspData.ctrl_tick++;

    /* 编码器按 1kHz 采样（不跟 20kHz 电流环走）：控制层用到的电角度和位置都是
     * 位置环周期更新的，20kHz 读 SPI 只是白占 ISR 时间，还更容易把开关噪声采进位置。
     * drv_encoder 内部有 3 点中值滤波，压掉偶发的跳变帧。
     * 放在 s_ctrl_running 判断之前：上电自检也要读编码器。 */
    if (++s_enc_div >= CTRL_TICK_PER_POS_TICK)
    {
        s_enc_div = 0U;
        drv_encoder_sample();
        servo_console_isr_encoder((uint32_t)drv_encoder_get_cnt(ENCODER_ID_MOTOR));
    }

    if (!s_ctrl_running)
    {
        return;
    }

    set_timer_record_start(SYS_TIMER_RECORD_CURRENT_LOOP_TIME_INDEX);

    /* 桥臂刚放开的第一拍先清电流环积分：封锁期间（以及电压模式做 L1 时）
     * 电流环一直在算，误差会把 id/iq 积分顶到限幅；带着这个积分进入电流模式，
     * 使能瞬间就会输出几伏电压，实测会把相电流冲到 3A 以上。
     * 速度观测器也要一起复位：PLL 每拍最大只能表示 1.0rad/T 的速度（1ms 环约 9550rpm），
     * 高速段被饱和过以后状态会卡在极限环里，速度环再也拿不到正确反馈。 */
    if (board_get_pwm_state() && !s_pwm_on_last)
    {
        current_ctl_loop_task_Init(&kAxisDw.current_ctl_loop_task_InstanceData.rtdw);

        speed_obs_pll_Init(&kAxisDw.speed_obs_pll_InstanceData.rtdw);
        /* Init 会把上一次位置清 0，直接喂第一帧会得到一个巨大的位置差，这里补上当前值 */
        kAxisDw.speed_obs_pll_InstanceData.rtdw.pos_now_p_last = kAxis.pos_speed_ctl_input.pos_now_p;
    }
    s_pwm_on_last = board_get_pwm_state();

    CurrentLoopCtrl();
    set_timer_record_stop(SYS_TIMER_RECORD_CURRENT_LOOP_TIME_INDEX);

    servo_console_isr_sample();
    board_check_over_current();

    if (++pos_div >= CTRL_TICK_PER_POS_TICK)
    {
        pos_div = 0U;
        set_timer_record_start(SYS_TIMER_RECORD_POSITION_LOOP_TIME_INDEX);
        PosSpeedLoopCtrl();
        set_timer_record_stop(SYS_TIMER_RECORD_POSITION_LOOP_TIME_INDEX);
    }
}

/* 放开/封锁六路输出。
 * 封锁：CFG1.SW_FORCE_EN + GLB_CTRL.SW_FORCE_SET 都要置位，输出才被强制到固定电平；
 * 放开：两处都要清。只清 CFG1 的话 GLB 里的 SW_FORCE 还在，
 * 实测就是"状态机说 pwm=1、比较值也对，但相电流恒为 0"。
 * （SDK 的 bldc_foc 例程里放开只调了 pwmv2_disable_software_force，这里两处都清更保险） */
void board_set_pwm_enable(bool enable)
{
    static const uint8_t pins[6] = {
        BOARD_BLDC_UH_PWM_OUTPIN, BOARD_BLDC_UL_PWM_OUTPIN,
        BOARD_BLDC_VH_PWM_OUTPIN, BOARD_BLDC_VL_PWM_OUTPIN,
        BOARD_BLDC_WH_PWM_OUTPIN, BOARD_BLDC_WL_PWM_OUTPIN,
    };

    pwmv2_shadow_register_unlock(BOARD_BLDCPWM);
    for (uint32_t i = 0; i < 6U; i++)
    {
        if (enable)
        {
            pwmv2_disable_software_force(BOARD_BLDCPWM, pins[i]);
            pwmv2_disable_force_by_software(BOARD_BLDCPWM, pins[i]);
        }
        else
        {
            pwmv2_set_force_update_time(BOARD_BLDCPWM, pins[i], pwm_force_immediately);
            pwmv2_force_update_time_by_shadow(BOARD_BLDCPWM, pins[i], pwm_force_update_shadow_immediately);
            pwmv2_enable_force_by_software(BOARD_BLDCPWM, pins[i]);
            pwmv2_enable_software_force(BOARD_BLDCPWM, pins[i]);
            pwmv2_force_output(BOARD_BLDCPWM, pins[i], pwm_force_output_1, false);
        }
    }
    pwmv2_shadow_register_lock(BOARD_BLDCPWM);

    kBspData.pwm_en_state = enable;
    kBspData.pwm_state_cnt = 0;
}

bool board_get_pwm_state(void)
{
    return kBspData.pwm_en_state;
}

uint32_t board_get_ctrl_tick(void)
{
    return kBspData.ctrl_tick;
}

uint32_t board_get_pwm_reload(void)
{
    return s_pwm_reload;
}

/*
 * 板级初始化：时钟/引脚由 SDK 板级包完成，这里只补伺服部分。
 * 顺序：编码器 -> PWM -> ADC -> 1ms -> 封锁输出 -> 放开采样中断。
 * 20kHz 的“控制”逻辑由 board_start_ctrl_tick() 在应用层初始化完成后单独放行。
 */
void board_init_servo(void)
{
    sys_timer_init();

    /* 六路 PWM 引脚：PD00..PD05 复用成 PWM0_P_0..5（-> IN_UH/UL/VH/VL/WH/WL）。
     * SDK 板级包的 board_init() 里没有这一步（官方例程是在应用自己的 pwm_init 里调），
     * 漏掉的话 IOC 里这几个 pad 停在 GPIO（FUNC_CTL=0），门驱输入全低、相电流恒为 0，
     * 而状态机会以为桥臂已经放开。 */
    init_pwm_pins(BOARD_BLDCPWM);

    if (!drv_encoder_init())
    {
        /* 失败时控制环不会报错，现象只是电机不转，必须显式打印。 */
        printf("board: MT6816 encoder init FAILED (check SPI7 PD20-23 wiring)\r\n");
    }

    board_init_pwm();
    board_init_adc();
    board_init_1ms_timer();

    /* 上电默认封锁输出，由 CiA402 状态机后续放开 */
    board_set_pwm_enable(false);
    kBspData.pwm_ready_state = false;

    /* 采样中断先放开：上电自检（编码器就绪、零漂校准）要原始数据。 */
    hpm_adc_v2_clear_status_flags(HPM_ADC_V2_HANDLE(BOARD_BLDC_ADC_V_BASE), HPM_ADC_V2_EVENT_TRIG_COMPLETE);
    hpm_adc_v2_enable_interrupts(HPM_ADC_V2_HANDLE(BOARD_BLDC_ADC_V_BASE), HPM_ADC_V2_EVENT_TRIG_COMPLETE);
    intc_m_enable_irq_with_priority(IRQn_ADC3, 6);   /* Sole ADC control interrupt. */

    hpm_adc_v2_clear_status_flags(HPM_ADC_V2_HANDLE(BOARD_BLDC_ADC_U_BASE), HPM_ADC_V2_EVENT_TRIG_COMPLETE);
    hpm_adc_v2_enable_interrupts(HPM_ADC_V2_HANDLE(BOARD_BLDC_ADC_U_BASE), HPM_ADC_V2_EVENT_TRIG_COMPLETE);
    /* ADC2 completion is polled in board_control_tick(); no ADC2 external IRQ. */
}

/* 启动 20kHz 控制节拍与 1ms 节拍。必须在 MotorCtrlInit()/AppInit() 之后调用。 */
void board_start_ctrl_tick(void)
{
    s_ctrl_running = true;
    intc_m_enable_irq_with_priority(BOARD_BLDC_TMR_IRQ, 6);
}
