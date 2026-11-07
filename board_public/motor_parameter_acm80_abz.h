#ifndef MOTOR_PARAMETER_ACM80_ABZ_H
#define MOTOR_PARAMETER_ACM80_ABZ_H

// 整个模组参数，电机参数、编码器参数、减速器参数

#ifdef __cplusplus
extern "C"
{
#endif

// --------------------------
// 电机及负载参数
// --------------------------
// 电机参数
#define PMSM_J                          (1.50e-04f)                     // 电机转动惯量（kg*m^2）
#define PMSM_Lp2p                       (0.31e-03f)                     // 相间电感（H）
#define PMSM_Rp2p                       (0.09f)                         // 相间电阻（Ω）
#define PMSM_RATED_CURRENT              (3.0f)                          // 电机额定电流（A）
#define PMSM_PEAK_CURRENT               (9.0f)                          // 电机峰值电流（A）
#define PMSM_PN                         (4.0f)                          // 极对数（N）
#define PMSM_SPEED_MAX_RPM              (4000.0f)                       // 电机最大转速（RPM）
#define PMSM_TORQUE_CONSTANT_MNM_A      (130.0f)                        // 电机转矩常数（mN*M/A）
// 编码器类型通过宏定义指定
#define ENCODER1_TYPE_OPTION            (ENCODER_TYPE_INC_AB_ABZ)       // 电机端编码器类型
#define ENCODER2_TYPE_OPTION            (ENCODER_TYPE_NONE)             // 负载端编码器类型
// 电机端编码器参数
#define PMSM_MOTOR_ENC_LINE_ORG         (4000u)                         // 电机端编码器原始分辨率（P/R）
#if PMSM_MOTOR_ENC_LINE_ORG == 0
#error "PMSM_MOTOR_ENC_LINE_ORG must be greater than 0"
#endif /*PMSM_MOTOR_ENC_LINE_ORG == 0*/
#define PMSM_MOTOR_ENC_LINE_P_N         (PMSM_MOTOR_ENC_LINE_ORG / 1u)  // 电机端编码器控制分辨率（P/R）
#define PMSM_MOTOR_ENC_MULTI_LINE_P_N   (0u)                            // 电机端编码器多圈分辨率（P/R）
#define PMSM_MOTOR_ENC_DIR              (0u)                            // 电机端编码器方向（0：不变，1：反向）
// 负载端编码器参数
#define PMSM_LOAD_ENC_LINE_ORG          (0u)                            // 负载端编码器原始分辨率（P/R）
#define PMSM_LOAD_ENC_LINE_P_N          (PMSM_LOAD_ENC_LINE_ORG / 1u)   // 负载端编码器实际分辨率（P/R）
#define PMSM_LOAD_ENC_MULTI_LINE_P_N    (0u)                            // 负载端编码器多圈分辨率（P/R）
#define PMSM_LOAD_ENC_DIR               (0u)                            // 负载端编码器方向（0：不变，1：反向）
// 负载端（齿轮/减速机...）参数
#define GEAR_RATIO_NUM                  (1u)                            // 减速比分子
#define GEAR_RATIO_DEN                  (1u)                            // 减速比分母
#define GEAR_RATIO                      (1.0f)                          // 减速比
// #define GEAR_BACKLASH_LOAD              (0.03f)                         // 负载端齿轮间隙，负载端间隙 单位：°  eg: 0.03°，表示齿轮间隙会产生±0.03度的误差
// // 电机端齿轮间隙参数  单位：电机端脉冲数 = GEAR_BACKLASH_LOAD * GEAR_RATIO / 360.0f * PMSM_MOTOR_ENC_LINE_P_N
// #define GEAR_BACKLASH_MOTOR_PULSE       (GEAR_BACKLASH_LOAD * GEAR_RATIO / 360.0f * PMSM_MOTOR_ENC_LINE_P_N)

// --------------------------
// 电机保护参数
// --------------------------
// 温度传感器参数
#define MOTOR_TEMP_SENSOR_K                 (-0.31283f)                 // (0℃-120℃)/(ADC(0) - ADC(120))
#define MOTOR_TEMP_SENSOR_BIAS              (645.72f)                   // 0℃ 时候 偏置值
// 电机温度保护阈值
#define MOTOR_HIGH_TEMP_FAULT_THRESHOLD     (145.0f)                    // 电机过温保护阈值（℃）
#define MOTOR_LOW_TEMP_FAULT_THRESHOLD      (-40.0f)                    // 电机低温保护阈值（℃）
#define MOTOR_HIGH_TEMP_WARING_THRESHOLD    (120.0f)                    // 电机过温警告阈值（℃）
#define MOTOR_LOW_TEMP_WARING_THRESHOLD     (-20.0f)                    // 电机低温警告阈值（℃）
// 抱闸相关参数
#define BRAKE_RATED_VOLTAGE                 (24.0f)                     // 抱闸器额定电压（V）
#define DYNAMIC_BRAKE_SPEED_THRESHOLD       (10.0f)                     // 抱闸制动速度阈值（RPM）
#define BRAKE_ENGAGE_DELAY_TIME             (0.0f)                      // 抱闸延迟时间（s）
#define BRAKE_ENGAGE_ACTION_TIME            (0.0f)                      // 抱闸动作时间（s）
#define BRAKE_RELEASE_DELAY_TIME            (0.0f)                      // 松闸延迟时间（s）
#define BRAKE_RELEASE_ACTION_TIME           (0.0f)                      // 松闸动作时间（s）
#define BRAKE_RELEASE_ACTION_VOLTAGE        (BRAKE_RATED_VOLTAGE * 1.0f)// 松闸动作电压（V）
#define BRAKE_RELEASE_HOLD_VOLTAGE          (BRAKE_RATED_VOLTAGE * 0.5f)// 松闸保持电压（V）
#define BRAKE_RELEASE_PWM_FREQ              (10000u)                    // 松闸PWM频率（Hz）

// --------------------------
// 电机控制参数
// --------------------------
// 电流环参数
#define CURRENT_CTL_CONFIG_KP_LD                    (5.16e-01f)         // d轴电流环比例增益
#define CURRENT_CTL_CONFIG_KI_LD                    (2.90e+02f)         // d轴电流环积分增益
#define CURRENT_CTL_CONFIG_KP_LQ                    (5.16e-01f)         // q轴电流环比例增益
#define CURRENT_CTL_CONFIG_KI_LQ                    (2.90e+02f)         // q轴电流环积分增益
#define CURRENT_CTL_CONFIG_PWM_DUTY_CYCLE_MAX       (1.0f)              // 最大占空比
#define CURRENT_CTL_CONFIG_ELEC_ANGLE_COMPENSATION  (4.0f)              // 电角度补偿系数
#define CURRENT_CTL_CONFIG_PHASE_DIR                (1)                 // 电机相序 1:abc -1:cba

// 位置速度环参数
#define POS_SPEED_CTL_CONFIG_KP_P                   (1.47e+02f)         // 位置环比例增益
#define POS_SPEED_CTL_CONFIG_KI_S                   (1.47e+02f)         // 速度环积分增益
#define POS_SPEED_CTL_CONFIG_KP_S                   (1.36e+00f)         // 速度环比例增益
#define POS_SPEED_CTL_CONFIG_J_KT                   (1.15e-03f)         // 惯性系数
#define POS_SPEED_CTL_CONFIG_AFF                    (0.0f)              // 加速度前馈增益
#define POS_SPEED_CTL_CONFIG_VFF                    (1.0f)              // 速度前馈增益

// 负载扰动观测器
#define POS_SPEED_CTL_CONFIG_DOB_ENABLE             (0u)                // 负载扰动观测器使能（0：禁用，1：启用）
#define POS_SPEED_CTL_CONFIG_DOB_WN_HZ              (4.00e+02f)         // 负载扰动观测器角频率（Hz）

// 速度观测器带宽
#define SPEED_OBS_PLL_WN_HZ                         (9.60e+02f)         // 速度观测器带宽（Hz）

// --------------------------
// 其他参数补充定义
// --------------------------
// 电机端编码器参数
#define ENCODER_ABZ_ERROR_RATIO         (0.05f)     // 编码器ABZ通信错误最大偏差比例（基于分辨率）

// 负载端编码器参数
// NULL
#ifdef __cplusplus
}
#endif

#endif // MOTOR_PARAMETER_ACM80_ABZ_H
