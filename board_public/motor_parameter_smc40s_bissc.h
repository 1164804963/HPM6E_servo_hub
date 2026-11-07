#ifndef MOTOR_PARAMETER_SMC40S_BISSC_H
#define MOTOR_PARAMETER_SMC40S_BISSC_H

// 整个模组参数，电机参数、编码器参数、减速器参数

#ifdef __cplusplus
extern "C"
{
#endif

// --------------------------
// 电机及负载参数
// --------------------------
// 电机参数
#define PMSM_J                          (3.30e-06f)                     // 电机转动惯量（kg*m^2）
#define PMSM_Lp2p                       (1.90e-03f)                     // 相间电感（H）
#define PMSM_Rp2p                       (1.5f)                          // 相间电阻（Ω）
#define PMSM_RATED_CURRENT              (3.2f)                          // 电机额定电流（A）
#define PMSM_PEAK_CURRENT               (9.6f)                          // 电机峰值电流（A）
#define PMSM_PN                         (5.0f)                          // 极对数（N）
#define PMSM_SPEED_MAX_RPM              (4000.0f)                       // 电机最大转速（RPM）
#define PMSM_TORQUE_CONSTANT_MNM_A      (50.0f)                         // 电机转矩常数（mN*M/A）
// 编码器类型通过宏定义指定
#define ENCODER1_TYPE_OPTION            (ENCODER_TYPE_ABS_BISSC_SMC40S) // 电机端编码器类型 BTR≤10MBps，CPOL=Low，CPHA=1Edge
#define ENCODER2_TYPE_OPTION            (ENCODER_TYPE_NONE)             // 负载端编码器类型
// 电机端编码器参数
#define PMSM_MOTOR_ENC_LINE_ORG         (524288u)                       // 电机端编码器原始分辨率（P/R）
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
#define CURRENT_CTL_CONFIG_KP_LD                    (3.16e+00f)         // d轴电流环比例增益
#define CURRENT_CTL_CONFIG_KI_LD                    (7.89e+02f)         // d轴电流环积分增益
#define CURRENT_CTL_CONFIG_KP_LQ                    (3.16e+00f)         // q轴电流环比例增益
#define CURRENT_CTL_CONFIG_KI_LQ                    (7.89e+02f)         // q轴电流环积分增益
#define CURRENT_CTL_CONFIG_PWM_DUTY_CYCLE_MAX       (1.0f)              // 最大占空比
#define CURRENT_CTL_CONFIG_ELEC_ANGLE_COMPENSATION  (4.0f)              // 电角度补偿系数
#define CURRENT_CTL_CONFIG_PHASE_DIR                (1)                 // 电机相序 1:abc -1:cba

// 位置速度环参数
#define POS_SPEED_CTL_CONFIG_KP_P                   (1.47e+02f)         // 位置环比例增益
#define POS_SPEED_CTL_CONFIG_KI_S                   (1.47e+02f)         // 速度环积分增益
#define POS_SPEED_CTL_CONFIG_KP_S                   (7.78e-02f)         // 速度环比例增益
#define POS_SPEED_CTL_CONFIG_J_KT                   (6.60e-05f)         // 惯性系数
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
// BRT38M BISS-C编码器 CF_ID宏定义
#define BISSC_CF_ID_0                   (0x00)      // 读取单圈数据，无需命令

// BRT38M BISS-C编码器 各CF_ID对应的帧长度定义（单位：BYTE(S)）
#define BISSC_FRAME_LEN_ID_0            (4u)        // CF_ID_0：读取单圈数据

// BRT38M BISS-C编码器 数据帧位宽定义（单位：BIT(S)）
#define BISSC_FRAME_LEN_ACK_BW          (6u)        // 数据帧应答位宽
#define BISSC_FRAME_LEN_START_BW        (1u)        // 数据帧起始位宽
#define BISSC_FRAME_LEN_CDS_BW          (1u)        // 数据帧命令位宽
#define BISSC_FRAME_LEN_DATA_BW         (19u)       // 数据帧数据位宽
#define BISSC_FRAME_LEN_ERROR_BW        (1u)        // 数据帧错误位宽
#define BISSC_FRAME_LEN_WARNING_BW      (1u)        // 数据帧警告位宽
#define BISSC_FRAME_LEN_CRC_BW          (6u)        // 数据帧CRC校验位宽
#define BISSC_FRAME_LEN_TOTAL_BW        (BISSC_FRAME_LEN_DATA_BW + \
                                         BISSC_FRAME_LEN_ERROR_BW + \
                                         BISSC_FRAME_LEN_WARNING_BW + \
                                         BISSC_FRAME_LEN_CRC_BW) // 数据帧总位宽

// 编码器校验值最终异或值
#define SMC40S_CRC6_FINAL_XOR           (0x43)
// 负载端编码器参数
// NULL
#ifdef __cplusplus
}
#endif

#endif // MOTOR_PARAMETER_SMC40S_BISSC_H
