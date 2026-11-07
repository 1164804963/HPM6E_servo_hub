#ifndef MOTOR_PARAMETER_KTM59XX_SPI_H
#define MOTOR_PARAMETER_KTM59XX_SPI_H

// 整个模组参数，电机参数、编码器参数、减速器参数

#ifdef __cplusplus
extern "C"
{
#endif

// --------------------------
// 电机及负载参数
// --------------------------
// 电机参数
#define PMSM_J                          (7.00e-06f)                     // 电机转动惯量（kg*m^2）
#define PMSM_Lp2p                       (6.98e-05f)                     // 相间电感（H）
#define PMSM_Rp2p                       (2.76e-01f)                     // 相间电阻（Ω）
#define PMSM_RATED_CURRENT              (6.0f)                          // 电机额定电流（A）
#define PMSM_PEAK_CURRENT               (12.0f)                         // 电机峰值电流（A）
#define PMSM_PN                         (21.0f)                         // 极对数（N）
#define PMSM_SPEED_MAX_RPM              (2500.0f)                       // 电机最大转速（RPM）
#define PMSM_TORQUE_CONSTANT_MNM_A      (168.64f)                       // 电机转矩常数（mN*M/A）
// 编码器类型通过宏定义指定
#define ENCODER1_TYPE_OPTION            (ENCODER_TYPE_ABS_SPI_KTM59XX)  // 电机端编码器类型
#define ENCODER2_TYPE_OPTION            (ENCODER_TYPE_ABS_SPI_KTM59XX)  // 负载端编码器类型
// 电机端编码器参数
#define PMSM_MOTOR_ENC_LINE_ORG         (16777216u)                     // 电机端编码器原始分辨率（P/R）
#if PMSM_MOTOR_ENC_LINE_ORG == 0
#error "PMSM_MOTOR_ENC_LINE_ORG must be greater than 0"
#endif /*PMSM_MOTOR_ENC_LINE_ORG == 0*/
#define PMSM_MOTOR_ENC_LINE_P_N         (PMSM_MOTOR_ENC_LINE_ORG / 128u)// 电机端编码器控制分辨率（P/R）
#define PMSM_MOTOR_ENC_MULTI_LINE_P_N   (0u)                            // 电机端编码器多圈分辨率（P/R）
#define PMSM_MOTOR_ENC_DIR              (0u)                            // 电机端编码器方向（0：不变，1：反向）
// 负载端编码器参数
#define PMSM_LOAD_ENC_LINE_ORG          (16777216u)                     // 负载端编码器原始分辨率（P/R）
#define PMSM_LOAD_ENC_LINE_P_N          (PMSM_LOAD_ENC_LINE_ORG / 128u) // 负载端编码器实际分辨率（P/R）
#define PMSM_LOAD_ENC_MULTI_LINE_P_N    (0u)                            // 负载端编码器多圈分辨率（P/R）
#define PMSM_LOAD_ENC_DIR               (1u)                            // 负载端编码器方向（0：不变，1：反向）
// 负载端（齿轮/减速机...）参数
#define GEAR_RATIO_NUM                  (10u)                           // 减速比分子
#define GEAR_RATIO_DEN                  (1u)                            // 减速比分母
#define GEAR_RATIO                      (10.0f)                         // 减速比
#define GEAR_BACKLASH_LOAD              (0.03f)                         // 负载端齿轮间隙，负载端间隙 单位：°  eg: 0.03°，表示齿轮间隙会产生±0.03度的误差
// 电机端齿轮间隙参数  单位：电机端脉冲数 = GEAR_BACKLASH_LOAD * GEAR_RATIO / 360.0f * PMSM_MOTOR_ENC_LINE_P_N
#define GEAR_BACKLASH_MOTOR_PULSE       (GEAR_BACKLASH_LOAD * GEAR_RATIO / 360.0f * PMSM_MOTOR_ENC_LINE_P_N)

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
#define CURRENT_CTL_CONFIG_KP_LD                    (1.86e-01f)         // d轴电流环比例增益
#define CURRENT_CTL_CONFIG_KI_LD                    (3.96e+03f)         // d轴电流环积分增益
#define CURRENT_CTL_CONFIG_KP_LQ                    (1.86e-01f)         // q轴电流环比例增益
#define CURRENT_CTL_CONFIG_KI_LQ                    (3.96e+03f)         // q轴电流环积分增益
#define CURRENT_CTL_CONFIG_PWM_DUTY_CYCLE_MAX       (0.9f)              // 最大占空比
#define CURRENT_CTL_CONFIG_ELEC_ANGLE_COMPENSATION  (2.0f)              // 电角度补偿系数
#define CURRENT_CTL_CONFIG_PHASE_DIR                (1)                 // 电机相序 1:abc -1:cba

// 位置速度环参数
#define POS_SPEED_CTL_CONFIG_KP_P                   (3.28e+02f)         // 位置环比例增益
#define POS_SPEED_CTL_CONFIG_KI_S                   (6.24e+01f)         // 速度环积分增益
#define POS_SPEED_CTL_CONFIG_KP_S                   (2.92e+00f)         // 速度环比例增益
#define POS_SPEED_CTL_CONFIG_J_KT                   (9.97e-04f)         // 惯性系数
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
// 电机、负载端编码器参数
typedef enum
{
    KTM59XX_CF_INIT                     = 0x00,     // 初始化指令
    // KTM59xx SPI编码器 CF_ID（bit31~24） 宏定义（协议标准值）
    KTM59XX_CF_ID_1                     = 0x5B,     // 指令1：控制寄存器写入
    KTM59XX_CF_ID_2                     = 0x62,     // 指令2：控制寄存器读取
    KTM59XX_CF_ID_3                     = 0x23,     // 指令3：角度和内部信号读取

    KTM59XX_REG_ADD_CALIB               = 0xA0,     // 校准寄存器地址
    KTM59XX_REG_VAL_CALIB_OFF           = 0x00,     // 校准寄存器值：关闭校准
} EncKtm59xxCf_t; // 编码器控制字段

typedef enum
{
    KTM59XX_FRAME_LEN_INIT              = 0,        // 初始值
    // KTM59xx编码器各CF_ID对应的帧长度（单位：字节）
    KTM59XX_FRAME_LEN_ID_1              = 4,        // KTM59XX_CF_ID_1：控制寄存器写入
    KTM59XX_FRAME_LEN_ID_2              = 4,        // KTM59XX_CF_ID_2：控制寄存器读取
    KTM59XX_FRAME_LEN_ID_3              = 8,        // KTM59XX_CF_ID_3：角度和内部信号读取

    KTM59xx_FRAME_LEN_TX                = 8,        // KTM59xx 数据帧发送长度
    KTM59xx_FRAME_LEN_TX_BW             = 8 * KTM59xx_FRAME_LEN_TX,
    KTM59xx_FRAME_LEN_RX                = 8,        // KTM59xx 数据帧接收长度
    KTM59xx_FRAME_LEN_RX_BW             = 8 * KTM59xx_FRAME_LEN_RX,
    KTM59xx_FRAME_LEN_ANGLE_BW          = 24,       // KTM59xx 角度数据位宽
    KTM59xx_FRAME_LEN_RC_BW             = 0,        // KTM59xx 内部信号数据位宽
    KTM59xx_FRAME_LEN_STATUS_BW         = 2,        // KTM59xx 状态数据位宽
    KTM59xx_FRAME_LEN_CRC_BW            = 8,        // KTM59xx CRC校验位宽
    KTM59xx_FRAME_LEN_DATA_BW           = (KTM59xx_FRAME_LEN_ANGLE_BW + \
                                           KTM59xx_FRAME_LEN_RC_BW + \
                                           KTM59xx_FRAME_LEN_STATUS_BW),    // KTM59xx 数据帧数据位宽
    KTM59xx_FRAME_LEN_TOTAL_BW          = (KTM59xx_FRAME_LEN_DATA_BW + \
                                           KTM59xx_FRAME_LEN_CRC_BW),       // KTM59xx 数据帧总位宽
} EncKtm59xxFrameLen_t; // 编码器帧长度

// 编码器校验值最终异或值
#define KTM5XXX_CRC8_FINAL_XOR          (0xFF)

// 编码器校准相关参数
#define KTM59XX_CALIBRATION_NONE        0           // 编码器正常工作，不校准(默认)
#define KTM59XX_CALIBRATION_PREV        1           // 进入校准状态(用于停止位置环编码器数据读取，为开始校准做准备)
#define KTM59XX_CALIBRATION_START       2           // 开始校准（VF开环运行后，启动开始校准，主函数中运行校准）
#define KTM59XX_CALIBRATION_FINISH      3           // 校准完成(校准完成后，会自动更新)
#define KTM59XX_CALIBRATION_TIMEOUT     4           // 校准超时(检测不到成功标志)
#define KTM59XX_CALIBRATION_SUCCESS     5           // 校准成功

#define ENC_CALI_FRE                    (1000.0f)   // 校准频率（Hz）
#define ENC_CALI_MAX_CURRENT            (10.0f)     // 最大校准增益，IF模式该值表示10A电流（A）
#define ENC_CALI_TIME_PERIOD            (500u)      // 500ms周期运行（ms）
#define ENC_CALI_FRE_INC                (0.5f)      // 每个周期增加0.5（Hz）
#define ENC_CALI_SPEED_0                (10.0f)     // 第一阶段目标转速（Hz）
#define ENC_CALI_SPEED_1                (20.0f)     // 第二阶段目标转速（Hz）
#define ENC_CALI_SPEED_SW_0             (30.0f)     // 达到30RPM打开编码器校准模式（RPM）
#define ENC_CALI_SPEED_SW_1             (40.0f)     // 达到40RPM打开编码器校准模式（RPM）
#define ENC_CALI_CHECK_CNT              (6u)        // 编码器状态查询周期（s）
#define ENC_CALI_TIMEOUT                (600u)      // 启动app120s后编码器校准模式超时（s）

#ifdef __cplusplus
}
#endif

#endif // MOTOR_PARAMETER_KTM59XX_SPI_H
