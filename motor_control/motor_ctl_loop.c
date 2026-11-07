#include "motor_ctl_loop.h"

// 关联底层接口
#include "bsp_api.h"

// 关联应用层接口
#include "app_brake_control.h"
#include "app_motion_precondition.h"
#include "app_scheduler.h"
#include "app_store_param.h"
#include "app_status_check.h"
#include "scope_app.h"

#ifdef USE_CIA402
#include "cia402_fsm.h"
#include "cia402_statusword.h"
#include "cia402_error_code.h"
#endif

#ifdef MOTOR_CTL_TEST // 控制层示例测试代码
static void motor_ctl_test(void);
#endif

// 用户定义实例化多轴
Axis kAxis;
AxisDw kAxisDw;

// 用户接口注册函数接口
// 初始化
void MotorCtrlInit(void)
{
    // 对控制层进行初始化
    MotorCtlSmInit(&kAxis, &kAxisDw);

    // 初始化硬件默认参数配置
    // 电机参数
    kAxis.pmsm_config.tc_s = 1.0f / CURRENT_FREQUENCY_HZ;  // 电流环周期
    kAxis.pmsm_config.tp_s = 1.0f / POSITION_FREQUENCY_HZ; // 位置速度环周期
    kAxis.pmsm_config.j = PMSM_J;
    kAxis.pmsm_config.b = 0.0001f;
    kAxis.pmsm_config.fc = 0.001f;
    kAxis.pmsm_config.ld = PMSM_Lp2p * 0.5f;
    kAxis.pmsm_config.lq = PMSM_Lp2p * 0.5f;
    kAxis.pmsm_config.peak_current = PMSM_PEAK_CURRENT;
    kAxis.pmsm_config.pn = PMSM_PN;
    kAxis.pmsm_config.r = PMSM_Rp2p * 0.5f;
    kAxis.pmsm_config.rated_current = PMSM_RATED_CURRENT;
    kAxis.pmsm_config.speed_max_rpm = PMSM_SPEED_MAX_RPM;
    kAxis.pmsm_config.enc_line_p_n = PMSM_MOTOR_ENC_LINE_P_N;
    kAxis.pmsm_config.kt = PMSM_TORQUE_CONSTANT_MNM_A * 0.001f;

    // 编码器参数
    kAxis.motor_pos_sensor_config.elec_angle_bias_rad = 0.0f;           // 电角度偏移值
    kAxis.load_pos_sensor_config.enc_line_p_n = PMSM_LOAD_ENC_LINE_P_N; // 负载端编码器分辨率
    kAxis.load_pos_sensor_config.init_pos_p = 0;                        // 负载端初始位置
    kAxis.load_pos_sensor_config.dir = 1;                               // 负载端编码器方向

    // 保护参数
    kAxis.motor_ctl_sm_config.under_voltage_protection_V = UNDER_VOLTAGE_PROTECTION_V;
    kAxis.motor_ctl_sm_config.over_voltage_protection_V = OVER_VOLTAGE_PROTECTION_V;
    kAxis.motor_ctl_sm_config.over_temperature_protection_d = OVER_TEMP_PROTECTION_C;
    kAxis.motor_ctl_sm_config.under_temperature_protection_d = UNDER_TEMP_PROTECTION_C;
    kAxis.motor_ctl_sm_config.position_following_error_protection = PMSM_MOTOR_ENC_LINE_P_N / 10;
    kAxis.motor_ctl_sm_config.over_speed_protection_rad_s = kAxis.pmsm_config.speed_max_rpm * MOTOR_CTL_SM_TWO_PI / 60.0f * 1.2f;

    // 电流环参数
    kAxis.current_ctl_config.comp_du_V = VOLTAGE_COMPENSATION_V;
    kAxis.current_ctl_config.i_noise_A = CURRENT_SAMP_NOISE_A;
    kAxis.current_ctl_config.kp_ld = CURRENT_CTL_CONFIG_KP_LD;
    kAxis.current_ctl_config.ki_ld = CURRENT_CTL_CONFIG_KI_LD;
    kAxis.current_ctl_config.kp_lq = CURRENT_CTL_CONFIG_KP_LQ;
    kAxis.current_ctl_config.ki_lq = CURRENT_CTL_CONFIG_KI_LQ;
    kAxis.current_ctl_config.pwm_duty_cycle_max = CURRENT_CTL_CONFIG_PWM_DUTY_CYCLE_MAX;
    kAxis.current_ctl_config.elec_angle_compensation = CURRENT_CTL_CONFIG_ELEC_ANGLE_COMPENSATION; // 电角度补偿值
    kAxis.current_ctl_config.phase_dir = CURRENT_CTL_CONFIG_PHASE_DIR;                             // 电机相序

    // 位置速度环参数
    kAxis.pos_speed_ctl_config.aff = POS_SPEED_CTL_CONFIG_AFF;
    kAxis.pos_speed_ctl_config.vff = POS_SPEED_CTL_CONFIG_VFF;
    kAxis.pos_speed_ctl_config.j_kt = POS_SPEED_CTL_CONFIG_J_KT;
    kAxis.pos_speed_ctl_config.ki_s = POS_SPEED_CTL_CONFIG_KI_S;
    kAxis.pos_speed_ctl_config.kp_p = POS_SPEED_CTL_CONFIG_KP_P;
    kAxis.pos_speed_ctl_config.kp_s = POS_SPEED_CTL_CONFIG_KP_S;

    // 负载扰动观测器
    kAxis.pos_speed_ctl_config.dob_wn_Hz = POS_SPEED_CTL_CONFIG_DOB_WN_HZ;
    kAxis.pos_speed_ctl_config.dob_enable = POS_SPEED_CTL_CONFIG_DOB_ENABLE;

    // 速度观测器
    kAxis.speed_obs_pll_config.wn_Hz = SPEED_OBS_PLL_WN_HZ;

    // 关联更新控制层其他参数
    MotorCtlParamSetUpdata(&kAxis);

    // 更新虚拟被控对象参数
    kAxis.sim_plant_config.dt_s = kAxis.pmsm_config.tc_s;
    kAxis.sim_plant_config.j = kAxis.pmsm_config.j;
    kAxis.sim_plant_config.j_inv = 1.0f / kAxis.pmsm_config.j;
    kAxis.sim_plant_config.b = kAxis.pmsm_config.b;
    kAxis.sim_plant_config.fc = kAxis.pmsm_config.fc;
    kAxis.sim_plant_config.flux = kAxis.pmsm_config.flux;
    kAxis.sim_plant_config.kt = kAxis.pmsm_config.kt;
    kAxis.sim_plant_config.pn = kAxis.pmsm_config.pn;
    kAxis.sim_plant_config.r = kAxis.pmsm_config.r;
    kAxis.sim_plant_config.ld = kAxis.pmsm_config.ld;
    kAxis.sim_plant_config.lq = kAxis.pmsm_config.lq;
    kAxis.sim_plant_config.ld_inv = 1.0f / kAxis.pmsm_config.ld;
    kAxis.sim_plant_config.lq_inv = 1.0f / kAxis.pmsm_config.lq;
    kAxis.sim_plant_config.enc_line_p_n = kAxis.pmsm_config.enc_line_p_n;
    kAxis.sim_plant_config.enc_line_init_pos_P = 0;
    kAxis.sim_plant_config.enc_noise = 1;
}

/**
 * @brief 非实时任务1ms循环
 */
void UnrealTimeBase1ms(void)
{
    float data_org = 0.0f;
    float data_org_p = 0.0f;
    float lpf_k = K_LPF_TEMP; // 滤波系数  100HZ  1ms周期

    // 1. 读取母线电压
    data_org = bsp_get_dc_bus_voltage();

    math_lib_first_order_lpf_iir(&data_org, &lpf_k,
                                 &kAxis.current_ctl_input.dc_bus_now_V,
                                 &kAxis.current_ctl_input.dc_bus_now_V);

    // 2. 读取驱动器温度
    data_org = bsp_get_mos_temperature();

    math_lib_first_order_lpf_iir(&data_org, &lpf_k,
                                 &kAxis.current_ctl_input.driver_temp,
                                 &kAxis.current_ctl_input.driver_temp);

    // 3. 读取MCU温度
    data_org_p = bsp_get_mcu_temperature();

    math_lib_first_order_lpf_iir(&data_org_p, &lpf_k,
                                 &kAppStatusInfo.Mcu_temperature,
                                 &kAppStatusInfo.Mcu_temperature);

    // 4. 读取电机温度
    data_org = bsp_get_motor_temp();

    math_lib_first_order_lpf_iir(&data_org, &lpf_k,
                                 &kAppStatusInfo.Motor_temperature,
                                 &kAppStatusInfo.Motor_temperature);

    // 5. 更新母线电流
    bsp_get_dc_bus_current();

    // 6. 状态扫描
    AppStatusScanSlow();

    // 7. 更新抱闸控制
    AppBrakeControlRun();

    // 8. 更新LED状态
    AppLedStateUpdata1ms();

    // 9. flash参数存储
    AppStoreUpdata1ms();

    // 10. 固件升级运行主函数
#ifdef YH_RELEASE
    bsp_run_fw_upgrade();
#endif // YH_RELEASE

#ifdef MOTOR_CTL_TEST // 控制层示例测试代码
    motor_ctl_test();
#endif
}

/**
 * @brief 电流环中断循环
 */
void CurrentLoopCtrl(void)
{
    // 电流环系统输入
    // 1. 读取当前实际三相电流
    bsp_get_phase_current(kAxis.current_ctl_input.iabc_now_A);

    // 2. 执行电流环控制算法
    CurrentCtlLoopTask(&kAxis, &kAxisDw);

    // 3. 输出电机控制电压
    bsp_set_phase_voltage(kAxis.current_ctl_output.uabc_tar_comp_V);
}

/**
 * @brief 位置速度环中断循环
 */
void PosSpeedLoopCtrl(void)
{
    // 位置速度环系统输入
    // 1. 读取当前实际位置  编码器当前单圈位置
    kAxis.motor_pos_sensor_input.enc_counts_now_p = bsp_get_encoder_cnt(ENCODER_ID_MOTOR);
    kAxis.load_pos_sensor_input.enc_counts_now_p = bsp_get_encoder_cnt(ENCODER_ID_LOAD);

    if (get_app_Internal_control_authority() == INTERNAL_CONTROL_APP)
    {
        AppStatusCheck();
        AppStatusScanFast();
        AppMotionPreConditionRun();
#ifdef USE_CIA402
        Cia402ErrorCodeScan();
        PDS_FSA_Run();
#endif // USE_CIA402
        AppRun(kAxis.motor_ctl_sm_input.hw_ready_state);
#ifdef USE_CIA402
        UpdateStatusword();
#endif // USE_CIA402
    }

    // 2. 执行位置速度环控制算法
    PosSpeedCtlLoopTask(&kAxis, &kAxisDw);

    // 3. 输出电机控制电压  失能状态到使能状态 上升沿使能电机
    if (kAxis.motor_ctl_sm_output.state == MOTOR_CTL_SM_STATE_ENABLE)
    {
        if (sys_get_current_calibration_status() == CURRENT_CALIBRATION_STATUS_OK)
        {
            if (kAxis.motor_ctl_sm_output.state_last == MOTOR_CTL_SM_STATE_DISABLE)
            {
                bsp_set_pwm_state(PWM_ENABLE);
            }
        }
        else
        {
            sys_current_calibration_step();
        }
    }
    else // 失能状态    其他状态都失能电机  包括错误状态
    {
        bsp_set_pwm_state(PWM_DISABLE);
    }

    // 4. 更新硬件准备状态
    if (bsp_get_pwm_state() == true &&\
        sys_get_current_calibration_status() == CURRENT_CALIBRATION_STATUS_OK)
    {
        kAxis.motor_ctl_sm_input.hw_ready_state = 1;
    }
    else
    {
        kAxis.motor_ctl_sm_input.hw_ready_state = 0;
    }
    // 记录上一次控制层状态机状态
    kAxis.motor_ctl_sm_output.state_last = kAxis.motor_ctl_sm_output.state;


    // 同步控制层变量到应用层,实现波形动态刷新和离线波形采集
    AppParamSyncUser();

    // 运行离线波形采样
    ScopeIsrHandle();
}

/**
 * @brief 虚拟被控对象模型运行  默认运行频率 20KHZ 与电流环同频
 */
void SimPlantStep(void)
{
    // 运行虚拟电机模型,在电流环中断中调用,一个电流环执行1次虚拟模型计算
    for (uint8_t i = 0; i < 1; i++)
    {
        sim_plant(&kAxis.sim_plant_input, &kAxis.sim_plant_config,
                  &kAxis.sim_plant_output, &(kAxisDw.sim_plant_InstanceData.rtdw));
    }
}

#ifdef MOTOR_CTL_TEST // 控制层示例测试代码
volatile uint8_T kMotorCtlTestMode = 0;

static void motor_ctl_test_param_updata(void)
{
    kAxis.motor_ctl_sm_input.motor_enable = MOTOR_CTL_SM_MOTOR_DISABLE; // 失能电机

    // 电机参数
    kAxis.pmsm_config.tc_s = 1.0f / CURRENT_FREQUENCY_HZ;  // 电流环周期
    kAxis.pmsm_config.tp_s = 1.0f / POSITION_FREQUENCY_HZ; // 位置速度环周期
    kAxis.pmsm_config.j = PMSM_J;
    kAxis.pmsm_config.ld = PMSM_Lp2p * 0.5f;
    kAxis.pmsm_config.lq = PMSM_Lp2p * 0.5f;
    kAxis.pmsm_config.peak_current = PMSM_PEAK_CURRENT;
    kAxis.pmsm_config.pn = PMSM_PN;
    kAxis.pmsm_config.r = PMSM_Rp2p * 0.5f;
    kAxis.pmsm_config.rated_current = PMSM_RATED_CURRENT;
    kAxis.pmsm_config.speed_max_rpm = PMSM_SPEED_MAX_RPM;
    kAxis.pmsm_config.enc_line_p_n = PMSM_MOTOR_ENC_LINE_P_N;

    // 编码器参数
    kAxis.motor_pos_sensor_config.elec_angle_bias_rad = 0.0f; // 电角度偏移值

    // 电流环参数
    kAxis.current_ctl_config.comp_du_V = VOLTAGE_COMPENSATION_V;
    kAxis.current_ctl_config.i_noise_A = CURRENT_SAMP_NOISE_A;
    kAxis.current_ctl_config.kp_ld = CURRENT_CTL_CONFIG_KP_LD;
    kAxis.current_ctl_config.ki_ld = CURRENT_CTL_CONFIG_KI_LD;
    kAxis.current_ctl_config.kp_lq = CURRENT_CTL_CONFIG_KP_LQ;
    kAxis.current_ctl_config.ki_lq = CURRENT_CTL_CONFIG_KI_LQ;
    kAxis.current_ctl_config.pwm_duty_cycle_max = CURRENT_CTL_CONFIG_PWM_DUTY_CYCLE_MAX;
    kAxis.current_ctl_config.elec_angle_compensation = CURRENT_CTL_CONFIG_ELEC_ANGLE_COMPENSATION; // 电角度补偿值
    kAxis.current_ctl_config.phase_dir = CURRENT_CTL_CONFIG_PHASE_DIR;                             // 电机相序

    // 位置速度环参数
    kAxis.pos_speed_ctl_config.aff = POS_SPEED_CTL_CONFIG_AFF;
    kAxis.pos_speed_ctl_config.vff = POS_SPEED_CTL_CONFIG_VFF;
    kAxis.pos_speed_ctl_config.j_kt = POS_SPEED_CTL_CONFIG_J_KT;
    kAxis.pos_speed_ctl_config.ki_s = POS_SPEED_CTL_CONFIG_KI_S;
    kAxis.pos_speed_ctl_config.kp_p = POS_SPEED_CTL_CONFIG_KP_P;
    kAxis.pos_speed_ctl_config.kp_s = POS_SPEED_CTL_CONFIG_KP_S;

    // 陷波滤波器参数设置
    // 设置陷波滤波器0抑制频率 Hz,如果设置为0 则不生效滤波器
    kAxis.notch_filter_config.frq[0] = 0.0f;
    kAxis.notch_filter_config.width[0] = 20.0f;
    kAxis.notch_filter_config.depth[0] = 0.01f;

    // 负载扰动观测器
    kAxis.pos_speed_ctl_config.dob_wn_Hz = POS_SPEED_CTL_CONFIG_DOB_WN_HZ;
    kAxis.pos_speed_ctl_config.dob_enable = POS_SPEED_CTL_CONFIG_DOB_ENABLE;

    // 速度观测器
    kAxis.speed_obs_pll_config.wn_Hz = SPEED_OBS_PLL_WN_HZ;

    MotorCtlParamSetUpdata(&kAxis);
    kMotorCtlTestMode = 0; // 只执行一次
}

static void motor_ctl_test_security(void)
{
    // 失能电机
    kAxis.motor_ctl_sm_input.motor_enable = MOTOR_CTL_SM_MOTOR_DISABLE;

    // 安全保护参数设置
    kAxis.motor_ctl_sm_config.error_enable = 0xffff; // 使能所有保护

    kAxis.motor_ctl_sm_config.under_voltage_protection_V = UNDER_VOLTAGE_PROTECTION_V;
    kAxis.motor_ctl_sm_config.over_voltage_protection_V = OVER_VOLTAGE_PROTECTION_V;
    kAxis.motor_ctl_sm_config.over_temperature_protection_d = OVER_TEMP_PROTECTION_C;
    kAxis.motor_ctl_sm_config.under_temperature_protection_d = UNDER_TEMP_PROTECTION_C;
    kMotorCtlTestMode = 0; // 只执行一次
}

static void motor_ctl_test_motor_ctl_sm(void)
{
    static uint32_t time_conunt = 0;
    static uint8_t first_run = 0;
    time_conunt++;

    // 发生错误自动清除错误
    if (kAxis.motor_ctl_sm_output.state == MOTOR_CTL_SM_STATE_ERROR && first_run == 0)
    {
        first_run = 1;                                                      // 只执行一次
        kAxis.motor_ctl_sm_input.motor_enable = MOTOR_CTL_SM_MOTOR_DISABLE; // 失能电机   0->3 上升沿清除
    }
    else if (kAxis.motor_ctl_sm_output.state == MOTOR_CTL_SM_STATE_ERROR && first_run == 1)
    {
        first_run = 0;                                                          // 只执行一次
        kAxis.motor_ctl_sm_input.motor_enable = MOTOR_CTL_SM_MOTOR_CLEAR_ERROR; // 3：清除错误
    }

    // 使能电机
    if (kAxis.motor_ctl_sm_output.state == MOTOR_CTL_SM_STATE_DISABLE &&
        kAxis.motor_ctl_sm_input.motor_enable != MOTOR_CTL_SM_MOTOR_DISABLE)
    {
        // 先失能  再使能电机   0->1 上升沿使能电机
        kAxis.motor_ctl_sm_input.motor_enable = MOTOR_CTL_SM_MOTOR_DISABLE; // 失能电机
    }
    else if (kAxis.motor_ctl_sm_output.state == MOTOR_CTL_SM_STATE_DISABLE &&
             kAxis.motor_ctl_sm_input.motor_enable == MOTOR_CTL_SM_MOTOR_DISABLE)
    {
        kAxis.motor_ctl_sm_config.mode = MOTOR_CTL_SM_MODE_SPEED;          // 速度模式
        kAxis.pos_speed_ctl_input.iq_max_A = 5.0f;                         // 设置最大q轴电流
        kAxis.pos_speed_ctl_input.acc_tar_p_ss = 1e6f;                     // 设置目标加速度
        kAxis.pos_speed_ctl_input.speed_tar_p_s = 1e6f;                    // 设置目标速度
        kAxis.motor_ctl_sm_input.motor_enable = MOTOR_CTL_SM_MOTOR_ENABLE; // 使能电机  0->1 上升沿使能电机
        time_conunt = 0;                                                   // 重置计数
    }

    // 失能电机  5s后自动失能
    if (kAxis.motor_ctl_sm_output.state == MOTOR_CTL_SM_STATE_ENABLE && time_conunt >= 5000)
    {
        kAxis.motor_ctl_sm_input.motor_enable = MOTOR_CTL_SM_MOTOR_DISABLE; // 使能电机
        time_conunt = 0;                                                    // 重置计数
        kMotorCtlTestMode = 0;                                              // 只执行一次
    }
}
static void motor_ctl_test_elec_id_mode(void) // kMotorCtlTestMode = 4
{
    // 使能电机
    if (kAxis.motor_ctl_sm_output.state == MOTOR_CTL_SM_STATE_DISABLE &&
        kAxis.motor_ctl_sm_input.motor_enable != MOTOR_CTL_SM_MOTOR_DISABLE)
    {
        // 先失能  再使能电机   0->1 上升沿使能电机
        kAxis.motor_ctl_sm_input.motor_enable = MOTOR_CTL_SM_MOTOR_DISABLE; // 失能电机
    }
    else if (kAxis.motor_ctl_sm_output.state == MOTOR_CTL_SM_STATE_DISABLE &&
             kAxis.motor_ctl_sm_input.motor_enable == MOTOR_CTL_SM_MOTOR_DISABLE)
    {
        kAxis.motor_ctl_sm_config.mode = MOTOR_CTL_SM_MODE_ELECTRIC_IDENTIFICATION;            // 电气辨识模式
        kAxis.elec_id_sin_config.i_max_A = kAxis.pmsm_config.rated_current;                    // 设置辨识最大电流，一般设置为电机额定电流
        kAxis.elec_id_sin_config.u_max_V = kAxis.current_ctl_input.dc_bus_now_V * 0.5f * 0.9f; // 设置最大电压 如母线电压 48V  该参数应当设置为 48.0f*0.5f*0.9f

        kAxis.elec_id_sin_output.state_now = IDENTIFICATION_MODE_STATE_IDLE; // 重置辨识状态

        kAxis.motor_ctl_sm_input.motor_enable = MOTOR_CTL_SM_MOTOR_ENABLE; // 使能电机  0->1 上升沿使能电机
    }

    // kAxis.elec_id_sin_output.state_now == IDENTIFICATION_MODE_STATE_STABLE_INCENTIVE; // 稳定激励阶段采集离线波形

    if (kAxis.elec_id_sin_output.state_now == IDENTIFICATION_MODE_STATE_FINISH) // 辨识完成 会自动失能电机
    {
        kAxis.motor_ctl_sm_input.motor_enable = MOTOR_CTL_SM_MOTOR_DISABLE; // 失能电机  辨识结束
        kMotorCtlTestMode = 0;                                              // 只执行一次
    }
}

static void motor_ctl_test_dir_id_mode(void)
{
    // 使能电机
    if (kAxis.motor_ctl_sm_output.state == MOTOR_CTL_SM_STATE_DISABLE &&
        kAxis.motor_ctl_sm_input.motor_enable != MOTOR_CTL_SM_MOTOR_DISABLE)
    {
        // 先失能  再使能电机   0->1 上升沿使能电机
        kAxis.motor_ctl_sm_input.motor_enable = MOTOR_CTL_SM_MOTOR_DISABLE; // 失能电机
    }
    else if (kAxis.motor_ctl_sm_output.state == MOTOR_CTL_SM_STATE_DISABLE &&
             kAxis.motor_ctl_sm_input.motor_enable == MOTOR_CTL_SM_MOTOR_DISABLE)
    {
        kAxis.motor_ctl_sm_config.mode = MOTOR_CTL_SM_MODE_DIRECTION_IDENTIFICATION; // 方向辨识模式

        // kAxis.direction_id_config.elec_angle_add = xxx   //一般无需配置 默认参数就行

        kAxis.direction_id_output.state_now = IDENTIFICATION_MODE_STATE_IDLE; // 重置辨识状态

        kAxis.motor_ctl_sm_input.motor_enable = MOTOR_CTL_SM_MOTOR_ENABLE; // 使能电机  0->1 上升沿使能电机
    }

    if (kAxis.direction_id_output.state_now == IDENTIFICATION_MODE_STATE_FINISH) // 辨识完成 会自动失能电机
    {
        // 控制层内部会自动更行UVW相序方向  自动刷新在  kAxis.current_ctl_config.phase_dir 变量中
        kAxis.motor_ctl_sm_input.motor_enable = MOTOR_CTL_SM_MOTOR_DISABLE; // 失能电机  辨识结束
        kMotorCtlTestMode = 0;                                              // 只执行一次
    }
}

static void motor_ctl_test_pole_pairs_id_mode(void)
{
    // 使能电机
    if (kAxis.motor_ctl_sm_output.state == MOTOR_CTL_SM_STATE_DISABLE &&
        kAxis.motor_ctl_sm_input.motor_enable != MOTOR_CTL_SM_MOTOR_DISABLE)
    {
        // 先失能  再使能电机   0->1 上升沿使能电机
        kAxis.motor_ctl_sm_input.motor_enable = MOTOR_CTL_SM_MOTOR_DISABLE; // 失能电机
    }
    else if (kAxis.motor_ctl_sm_output.state == MOTOR_CTL_SM_STATE_DISABLE &&
             kAxis.motor_ctl_sm_input.motor_enable == MOTOR_CTL_SM_MOTOR_DISABLE)
    {
        kAxis.motor_ctl_sm_config.mode = MOTOR_CTL_SM_MODE_POLE_PAIRS_IDENTIFICATION; // 极对数辨识模式
        kAxis.pole_pairs_id_config.id_tar_max_A = kAxis.pmsm_config.rated_current;    // 设置极对数辨识最大电流，一般设置为电机额定电流

        kAxis.pole_pairs_id_output.state_now = IDENTIFICATION_MODE_STATE_IDLE; // 重置辨识状态

        kAxis.motor_ctl_sm_input.motor_enable = MOTOR_CTL_SM_MOTOR_ENABLE; // 使能电机  0->1 上升沿使能电机
    }

    if (kAxis.pole_pairs_id_output.state_now == IDENTIFICATION_MODE_STATE_FINISH) // 辨识完成 会自动失能电机
    {
        // 辨识结束 自动更新内部极对数参数  kAxis.pmsm_config.pn  kAxis.motor_pos_sensor_config.pn
        kAxis.motor_ctl_sm_input.motor_enable = MOTOR_CTL_SM_MOTOR_DISABLE; // 失能电机  辨识结束
        kMotorCtlTestMode = 0;                                              // 只执行一次
    }
}

static void motor_ctl_test_elec_angle_id_mode(void)
{
    // 使能电机
    if (kAxis.motor_ctl_sm_output.state == MOTOR_CTL_SM_STATE_DISABLE &&
        kAxis.motor_ctl_sm_input.motor_enable != MOTOR_CTL_SM_MOTOR_DISABLE)
    {
        // 先失能  再使能电机   0->1 上升沿使能电机
        kAxis.motor_ctl_sm_input.motor_enable = MOTOR_CTL_SM_MOTOR_DISABLE; // 失能电机
    }
    else if (kAxis.motor_ctl_sm_output.state == MOTOR_CTL_SM_STATE_DISABLE &&
             kAxis.motor_ctl_sm_input.motor_enable == MOTOR_CTL_SM_MOTOR_DISABLE)
    {
        kAxis.motor_ctl_sm_config.mode = MOTOR_CTL_SM_MODE_ELECTRIC_ANGLE_IDENTIFICATION; // 电角度辨识模式

        kAxis.elec_angle_id_output.state_now = IDENTIFICATION_MODE_STATE_IDLE; // 重置辨识状态

        kAxis.motor_ctl_sm_input.motor_enable = MOTOR_CTL_SM_MOTOR_ENABLE; // 使能电机  0->1 上升沿使能电机
    }

    if (kAxis.elec_angle_id_output.state_now == IDENTIFICATION_MODE_STATE_FINISH) // 辨识完成 会自动失能电机
    {
        // 辨识结束 自动更新内部电角度偏移值  kAxis.motor_pos_sensor_config.elec_angle_bias_rad
        kAxis.motor_ctl_sm_input.motor_enable = MOTOR_CTL_SM_MOTOR_DISABLE; // 失能电机  辨识结束
        kMotorCtlTestMode = 0;                                              // 只执行一次
    }
}

static void motor_ctl_test_mec_id_mode(void)
{
    static uint8_t step_num = 0; // 执行步骤

    switch (step_num)
    {
    case 0:                                                                 // 失能电机
        kAxis.motor_ctl_sm_input.motor_enable = MOTOR_CTL_SM_MOTOR_DISABLE; // 失能电机
        step_num++;                                                         // 进入下一个步骤
        break;
    case 1:                                                                           // 设置参数启动
        kAxis.motor_ctl_sm_config.mode = MOTOR_CTL_SM_MODE_MECHANICAL_IDENTIFICATION; // 机械特性辨识模式

        kAxis.mec_id_config.i_max_A = kAxis.pmsm_config.rated_current; // 设置辨识最大电流，一般设置为电机额定电流
        kAxis.mec_id_config.signal_type = 0;                           // 机械特性辨识信号类型 0：chirp 一般默认 1：阶跃信号，超大惯量辨识适用

        kAxis.mec_id_output.state_now = IDENTIFICATION_MODE_STATE_IDLE; // 重置辨识状态

        kAxis.motor_ctl_sm_input.motor_enable = MOTOR_CTL_SM_MOTOR_ENABLE; // 使能电机  0->1 上升沿使能电机

        step_num++; // 进入下一个步骤
        break;
    case 2:                                                                    // 辨识完成退出测试步骤
        if (kAxis.mec_id_output.state_now == IDENTIFICATION_MODE_STATE_FINISH) // 辨识完成 会自动失能电机
        {
            kAxis.motor_ctl_sm_input.motor_enable = MOTOR_CTL_SM_MOTOR_DISABLE;
            kMotorCtlTestMode = 0; // 只执行一次
            step_num = 0;          // 步骤重置
        }
        break;

    default:
        break;
    }
}
static void motor_ctl_test_tp_fc_id_mode(void)
{
    // TODO:
}

float kTorqueUserTarget = 0.0f;                      // 力矩用户目标值  A
float kTorqueSlope = 10.0f;                          // 力矩上升斜率 A/s
float kTrajectoryPeriod = 0.001f;                    // 力矩规划器运行周期
linear_trajectory_planning_DW_f kTorqueTrajTestDw = {0}; // 力矩规划器内部缓存
int8_T kTroqueTrajStateNow = 0;
static void motor_ctl_test_pt_mode(void) // kMotorCtlTestMode = 10
{
    static uint8_t step_num = 0; // 执行步骤

    switch (step_num)
    {
    case 0:                                                                 // 失能电机
        kAxis.motor_ctl_sm_input.motor_enable = MOTOR_CTL_SM_MOTOR_DISABLE; // 失能电机
        step_num++;                                                         // 进入下一个步骤
        break;
    case 1:                                                        // 设置参数启动
        kAxis.motor_ctl_sm_config.mode = MOTOR_CTL_SM_MODE_TORQUE; // 力矩模式

        // 初始化当前规划器 为当前 q轴电流
        kTorqueTrajTestDw.traj_now = kAxis.current_ctl_output.idq_now_A[1]; // 力矩规划器初始化为当前 q轴电流 从当前值开始规划

        kAxis.motor_ctl_sm_input.motor_enable = MOTOR_CTL_SM_MOTOR_ENABLE; // 使能电机  0->1 上升沿使能电机

        step_num++; // 进入下一个步骤
        break;
    case 2: // 用户更新目标力矩指令  循环执行

        linear_trajectory_planning(&kTorqueUserTarget,
                                   &kTorqueSlope,
                                   &kTrajectoryPeriod,
                                   &kAxis.current_ctl_input.idq_tar_A[1],
                                   &kTroqueTrajStateNow, &(kTorqueTrajTestDw));

        break;

    default:
        break;
    }
}

float kSpeedUserTarget = 0.0f;                      // 速度用户目标值  P/s
float kPvAcc = 1e6f;                                // 加速度 P/s^2
linear_trajectory_planning_DW_f kSpeedTrajTestDw = {0}; // 速度规划器内部规划缓存
int8_T kSpeedTrajStateNow = 0;
static void motor_ctl_test_pv_mode(void) // kMotorCtlTestMode = 11
{
    static uint8_t step_num = 0; // 执行步骤

    switch (step_num)
    {
    case 0:                                                                 // 失能电机
        kAxis.motor_ctl_sm_input.motor_enable = MOTOR_CTL_SM_MOTOR_DISABLE; // 失能电机
        step_num++;                                                         // 进入下一个步骤
        break;
    case 1:                                                       // 设置参数启动
        kAxis.motor_ctl_sm_config.mode = MOTOR_CTL_SM_MODE_SPEED; // 速度模式

        kAxis.pos_speed_ctl_input.iq_max_A = 5.0f; // 按用户设定设置最大q轴电流限制

        // 初始化当前规划器 为当前 速度
        kSpeedTrajTestDw.traj_now = kAxis.pos_speed_ctl_input.speed_now_rad_s /
                                MOTOR_CTL_SM_TWO_PI * kAxis.pmsm_config.enc_line_p_n; // 从当前速度开始规划  p/s

        kAxis.motor_ctl_sm_input.motor_enable = MOTOR_CTL_SM_MOTOR_ENABLE; // 使能电机  0->1 上升沿使能电机

        step_num++; // 进入下一个步骤
        break;
    case 2: // 用户更新目标力矩指令  循环执行

        linear_trajectory_planning(&kSpeedUserTarget,
                                   &kPvAcc,
                                   &kTrajectoryPeriod,
                                   &kAxis.pos_speed_ctl_input.speed_tar_p_s,
                                   &kSpeedTrajStateNow, &(kSpeedTrajTestDw));

        break;

    default:
        break;
    }
}

int64_t kPosUserTarget = 0;                    // 位置用户目标值  P/s
float kPosTrajOutDec = 0.0f;                   // 位置用户目标值 小数位 p/s
float kProfileSpeed = 1e6f;                    // 轮廓速度
float kProfileAcc = 1e6f;                      // 轮廓加速度
float kProfileDec = 1e6f;                      // 轮廓减速度
pos_trajectory_planning_DW_f kPosTrajTestDw = {0}; // 位置规划器内部缓存
int8_T kPosTrajStateNow = 0;                   // TODO：规划器状态更新待修复
static void motor_ctl_test_pp_mode(void)
{
    static uint8_t step_num = 0; // 执行步骤

    switch (step_num)
    {
    case 0:                                                                 // 失能电机
        kAxis.motor_ctl_sm_input.motor_enable = MOTOR_CTL_SM_MOTOR_DISABLE; // 失能电机
        step_num++;                                                         // 进入下一个步骤
        break;
    case 1:                                                          // 设置参数启动
        kAxis.motor_ctl_sm_config.mode = MOTOR_CTL_SM_MODE_POSITION; // 位置模式

        kAxis.pos_speed_ctl_input.iq_max_A = 5.0f; // 按用户设定设置最大q轴电流限制

        // 初始化当前规划器 为当前速度  当前位置
        kPosTrajTestDw.q0_int = kAxis.pos_speed_ctl_input.pos_now_p;
        kPosTrajTestDw.q0_dec = 0.0f;
        kPosTrajTestDw.dq0 = kAxis.pos_speed_ctl_input.speed_now_rad_s /
                         MOTOR_CTL_SM_TWO_PI * kAxis.pmsm_config.enc_line_p_n; // 从当前速度开始规划  p/s
        kPosTrajTestDw.x = kAxis.pos_speed_ctl_input.pos_now_p;

        kAxis.motor_ctl_sm_input.motor_enable = MOTOR_CTL_SM_MOTOR_ENABLE; // 使能电机  0->1 上升沿使能电机

        step_num++; // 进入下一个步骤
        break;
    case 2: // 用户更新目标力矩指令  循环执行
            // 速度梯形规划
        pos_trajectory_planning(&kPosUserTarget,
                                &kProfileSpeed,
                                &kProfileAcc,
                                &kProfileDec,
                                &kTrajectoryPeriod,
                                &kAxis.input_shaping_input.pos_cmd_p,
                                &kPosTrajOutDec,
                                &kAxis.pos_speed_ctl_input.speed_tar_p_s,
                                &kAxis.pos_speed_ctl_input.acc_tar_p_ss,
                                &kPosTrajStateNow, &kPosTrajTestDw);

        break;

    default:
        break;
    }
}

int64_T kMitPosUserTarget = 0.0f; // 用户规划目标位置
float kMitSpeedUserTarget = 0.0f; // 用户规划目标速度
float kMitTorqueTarget = 0.0f;    // 用户规划目标力矩

static void motor_ctl_test_mit_mode(void) // kMotorCtlTestMode  = 13
{
    // mit 模式 由用户规划目标值
    static uint8_t step_num = 0; // 执行步骤

    switch (step_num)
    {
    case 0:                                                                 // 失能电机
        kAxis.motor_ctl_sm_input.motor_enable = MOTOR_CTL_SM_MOTOR_DISABLE; // 失能电机
        step_num++;                                                         // 进入下一个步骤
        break;
    case 1:                                                     // 设置参数启动
        kAxis.motor_ctl_sm_config.mode = MOTOR_CTL_SM_MODE_MIT; // MIT模式

        kAxis.mit_ctl_input.iq_max_A = 5.0f; // 按用户设定设置最大q轴电流限制

        kAxis.motor_ctl_sm_input.motor_enable = MOTOR_CTL_SM_MOTOR_ENABLE; // 使能电机  0->1 上升沿使能电机

        step_num++; // 进入下一个步骤
        break;
    case 2: //  更新用户目标值 循环执行

        kAxis.mit_ctl_input.pos_tar_p = kMitPosUserTarget;
        kAxis.mit_ctl_input.speed_tar_p_s = kMitSpeedUserTarget;
        kAxis.mit_ctl_input.tq_set_A = kMitTorqueTarget;

        break;

    default:
        break;
    }
}

static void motor_ctl_test(void)
{
    switch (kMotorCtlTestMode)
    {
    case 1: // 参数设置关联更新测试
        motor_ctl_test_param_updata();
        break;
    case 2: // 安全保护模块参数设置
        motor_ctl_test_security();
        break;
    case 3: // 电机控制状态机测试
        motor_ctl_test_motor_ctl_sm();
        break;

    case 4: // 电气辨识模式
        motor_ctl_test_elec_id_mode();
        break;

    case 5: // 方向辨识模式
        motor_ctl_test_dir_id_mode();
        break;

    case 6: // 极对数辨识
        motor_ctl_test_pole_pairs_id_mode();
        break;
    case 7: // 电角度辨识
        motor_ctl_test_elec_angle_id_mode();
        break;
    case 8: // 机械特性辨识模式
        motor_ctl_test_mec_id_mode();
        break;

    case 9: // 参数设置关联更新测试
        motor_ctl_test_tp_fc_id_mode();
        break;

    case 10: // PT模式
        motor_ctl_test_pt_mode();
        break;
    case 11: // PV模式
        motor_ctl_test_pv_mode();
        break;
    case 12: // PP模式
        motor_ctl_test_pp_mode();
        break;

    case 13: // MIT模式
        motor_ctl_test_mit_mode();
        break;
    default:
        break;
    }
}

#endif
