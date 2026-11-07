#ifndef MOTOR_PARAMETER_GIM6010_SPI_H
#define MOTOR_PARAMETER_GIM6010_SPI_H

// 整个模组参数，电机参数、编码器参数、减速器参数

#ifdef __cplusplus
extern "C"
{
#endif

// --------------------------
// 电机及负载参数
// --------------------------
// 电机参数
#define PMSM_J                          (5.00e-05f)                     // 电机转动惯量（kg*m^2）
#define PMSM_Lp2p                       (0.82e-03f)                     // 相间电感（H）
#define PMSM_Rp2p                       (1.45f)                         // 相间电阻（Ω）
#define PMSM_RATED_CURRENT              (3.8f)                          // 电机额定电流（A）
#define PMSM_PEAK_CURRENT               (19.5f)                         // 电机峰值电流（A）
#define PMSM_PN                         (14.0f)                         // 极对数（N）
#define PMSM_SPEED_MAX_RPM              (2500.0f)                       // 电机最大转速（RPM）
#define PMSM_TORQUE_CONSTANT_MNM_A      (1200.00f)                      // 电机转矩常数（mN*M/A）
// 编码器类型通过宏定义指定
#define ENCODER1_TYPE_OPTION            (ENCODER_TYPE_ABS_SPI_MT68XX)   // 电机端编码器类型
#define ENCODER2_TYPE_OPTION            (ENCODER_TYPE_ABS_SPI_MT68XX)   // 负载端编码器类型
// 电机端编码器参数
#define PMSM_MOTOR_ENC_LINE_ORG         (2097152u)                      // 电机端编码器原始分辨率（P/R）
#if PMSM_MOTOR_ENC_LINE_ORG == 0
#error "PMSM_MOTOR_ENC_LINE_ORG must be greater than 0"
#endif /*PMSM_MOTOR_ENC_LINE_ORG == 0*/
#define PMSM_MOTOR_ENC_LINE_P_N         (PMSM_MOTOR_ENC_LINE_ORG / 1u)  // 电机端编码器控制分辨率（P/R）
#define PMSM_MOTOR_ENC_MULTI_LINE_P_N   (0u)                            // 电机端编码器多圈分辨率（P/R）
#define PMSM_MOTOR_ENC_DIR              (0u)                            // 电机端编码器方向（0：不变，1：反向）
// 负载端编码器参数
#define PMSM_LOAD_ENC_LINE_ORG          (2097152u)                      // 负载端编码器原始分辨率（P/R）
#define PMSM_LOAD_ENC_LINE_P_N          (PMSM_LOAD_ENC_LINE_ORG / 1u)   // 负载端编码器实际分辨率（P/R）
#define PMSM_LOAD_ENC_MULTI_LINE_P_N    (0u)                            // 负载端编码器多圈分辨率（P/R）
#define PMSM_LOAD_ENC_DIR               (1u)                            // 负载端编码器方向（0：不变，1：反向）
// 负载端（齿轮/减速机...）参数
#define GEAR_RATIO_NUM                  (8u)                            // 减速比分子
#define GEAR_RATIO_DEN                  (1u)                            // 减速比分母
#define GEAR_RATIO                      (8.0f)                          // 减速比
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
#define CURRENT_CTL_CONFIG_KP_LD                    (1.37e+00f)         // d轴电流环比例增益
#define CURRENT_CTL_CONFIG_KI_LD                    (1.77e+03f)         // d轴电流环积分增益
#define CURRENT_CTL_CONFIG_KP_LQ                    (1.37e+00f)         // q轴电流环比例增益
#define CURRENT_CTL_CONFIG_KI_LQ                    (1.77e+03f)         // q轴电流环积分增益
#define CURRENT_CTL_CONFIG_PWM_DUTY_CYCLE_MAX       (0.9f)              // 最大占空比
#define CURRENT_CTL_CONFIG_ELEC_ANGLE_COMPENSATION  (2.0f)              // 电角度补偿系数
#define CURRENT_CTL_CONFIG_PHASE_DIR                (1)                 // 电机相序 1:abc -1:cba

// 位置速度环参数
#define POS_SPEED_CTL_CONFIG_KP_P                   (1.47e+02f)         // 位置环比例增益
#define POS_SPEED_CTL_CONFIG_KI_S                   (1.47e+02f)         // 速度环积分增益
#define POS_SPEED_CTL_CONFIG_KP_S                   (1.97e-01f)         // 速度环比例增益
#define POS_SPEED_CTL_CONFIG_J_KT                   (1.67e-04f)         // 惯性系数
#define POS_SPEED_CTL_CONFIG_AFF                    (0.0f)              // 加速度前馈增益
#define POS_SPEED_CTL_CONFIG_VFF                    (1.0f)              // 速度前馈增益

// 负载扰动观测器
#define POS_SPEED_CTL_CONFIG_DOB_ENABLE             (0u)                // 负载扰动观测器使能（0：禁用，1：启用）
#define POS_SPEED_CTL_CONFIG_DOB_WN_HZ              (4.00e+02f)         // 负载扰动观测器角频率（Hz）

// 速度观测器带宽
#define SPEED_OBS_PLL_WN_HZ                         (1200.0f)         // 速度观测器带宽（Hz）

// --------------------------
// 其他参数补充定义
// --------------------------
// 电机、负载端编码器参数
typedef enum
{
    MT68XX_CF_INIT                      = 0x00,     // 初始化寄存器
    // MT68XX SPI编码器 宏定义（bit15~8）（协议标准值）
    MT68XX_CF_ID_RD                     = 0x30,     // 读寄存器 （0b0011 << 12）
    MT68XX_CF_ID_WR                     = 0x60,     // 写寄存器 （0b0110 << 12）
} EncMt68xxCf_t; // 编码器控制字段

typedef enum
{
    MT68XX_LEN_INIT                     = 0,        // 初始化寄存器
    // MT68XX SPI编码器 各CF_ID对应的帧长度（单位：字节）
    MT68XX_FRAME_LEN_RD_ANGLE           = 6,        // MT68XX_CF_ID_RD：读角度寄存器帧长度
    MT68XX_DATA_LEN_RD_ANGLE            = 4,        // MT68XX_CF_ID_RD：读角度寄存器有效数据长度
    MT68XX_RD_ANGLE_STATUS_BW           = 3,        // MT68XX_CF_ID_RD：读角度寄存器状态位宽
} EncMt68xxFrameLen_t; // 编码器数据帧长度

// 编码器其它参数定义
typedef enum
{
    MT_STAS_NORMAL_BIT                  = 0,        // 正常状态
    MT_STAS_OVER_SPEED_BIT              = 1,        // 转速过快报警（超过12万转/分钟）
    MT_STAS_MAGNETIC_WEAK_BIT           = 2,        // 外加磁场太弱报警
    MT_STAS_UNDER_VOL_BIT               = 4,        // 芯片供电欠压报警
    MT_STAS_CRC_CHECK_ERROR_BIT         = 8,        // CRC8校验错误
} MT6835_STATUS_DEF;

typedef enum
{
    MT_REG_USER                         = (0x001),  // 用户自定义EEPROM寄存器
    MT_REG_ANGLE_H                      = (0x003),  // 角度数据寄存器高字节：角度值[b20:b13]
    MT_REG_ANGLE_M                      = (0x004),  // 角度数据寄存器中字节：角度值[b12:b5]
    MT_REG_ANGLE_L                      = (0x005),  // 角度数据寄存器低字节：角度值[b4:b0] + 状态值[b2:b0]
    MT_REG_CRC8                         = (0x006),  // CRC8校验码寄存器值
    // ...
    MT_REG_IO_CALSPD                    = (0x00E),  // IO驱动能力、自校转速寄存器：IO驱动能力[b7] + 自校转速[b6:b4] + 保留[b3:b0]
    MT_REG_CAL_STAS                     = (0x113),  // 自校准状态寄存器Bit[7,6]：00b=未校准，01b=校准中，10b=失败，11b=成功
} MT6835_REG_DEF;

// 编码器校验值多项式
#define MT68XX_CRC8_POLY                (0x07)  // MT68XX校验值多项式

// 编码器校准相关参数
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

#endif // MOTOR_PARAMETER_GIM6010_SPI_H
