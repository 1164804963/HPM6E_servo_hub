#ifndef MOTOR_PARAMETER_WB40ST_TAMAGAWA_H
#define MOTOR_PARAMETER_WB40ST_TAMAGAWA_H

// 整个模组参数，电机参数、编码器参数、减速器参数

#ifdef __cplusplus
extern "C"
{
#endif

// --------------------------
// 电机及负载参数
// --------------------------
// 电机参数
#define PMSM_J                          (5.00e-06f)                     // 电机转动惯量（kg*m^2）
#define PMSM_Lp2p                       (0.38e-03f)                     // 相间电感（H）
#define PMSM_Rp2p                       (0.4f)                          // 相间电阻（Ω）
#define PMSM_RATED_CURRENT              (6.5f)                          // 电机额定电流（A）
#define PMSM_PEAK_CURRENT               (19.5f)                         // 电机峰值电流（A）
#define PMSM_PN                         (5.0f)                          // 极对数（N）
#define PMSM_SPEED_MAX_RPM              (6000.0f)                       // 电机最大转速（RPM）
#define PMSM_TORQUE_CONSTANT_MNM_A      (50.0f)                         // 电机转矩常数（mN*M/A）
// 编码器类型通过宏定义指定
#define ENCODER1_TYPE_OPTION            (ENCODER_TYPE_ABS_RS485_TAMAGAWA)// 电机端编码器类型
#define ENCODER2_TYPE_OPTION            (ENCODER_TYPE_NONE)             // 负载端编码器类型
// 电机端编码器参数
#define PMSM_MOTOR_ENC_LINE_ORG         (131072u)                       // 电机端编码器原始分辨率（P/R）
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
#define CURRENT_CTL_CONFIG_KP_LD                    (6.33e-01f)         // d轴电流环比例增益
#define CURRENT_CTL_CONFIG_KI_LD                    (1.05e+03f)         // d轴电流环积分增益
#define CURRENT_CTL_CONFIG_KP_LQ                    (6.33e-01f)         // q轴电流环比例增益
#define CURRENT_CTL_CONFIG_KI_LQ                    (1.05e+03f)         // q轴电流环积分增益
#define CURRENT_CTL_CONFIG_PWM_DUTY_CYCLE_MAX       (1.0f)              // 最大占空比
#define CURRENT_CTL_CONFIG_ELEC_ANGLE_COMPENSATION  (4.0f)              // 电角度补偿系数
#define CURRENT_CTL_CONFIG_PHASE_DIR                (1)                 // 电机相序 1:abc -1:cba

// 位置速度环参数
#define POS_SPEED_CTL_CONFIG_KP_P                   (1.47e+02f)         // 位置环比例增益
#define POS_SPEED_CTL_CONFIG_KI_S                   (1.47e+02f)         // 速度环积分增益
#define POS_SPEED_CTL_CONFIG_KP_S                   (1.18e-01f)         // 速度环比例增益
#define POS_SPEED_CTL_CONFIG_J_KT                   (1.00e-04f)         // 惯性系数
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
typedef enum
{
    TAMAGAWA_CF_INIT = 0x00,        // 初始值
    // 多摩川编码器 CF_ID 宏定义（协议标准值）
    TAMAGAWA_CF_ID_0 = 0x02,        // 读取单圈数据（ABS0 ABS1 ABS2）
    TAMAGAWA_CF_ID_1 = 0x8A,        // 读取多圈数据（ABM0 ABM1 ABM2）
    TAMAGAWA_CF_ID_2 = 0x92,        // 读取编码器ID（ENID）
    TAMAGAWA_CF_ID_3 = 0x1A,        // 读取所有数据（ABS + ENID + ABM + ALMC）
    TAMAGAWA_CF_ID_4 = 0xA2,        // 读取单圈扩展数据（ABS0-ABS3）
    TAMAGAWA_CF_ID_5 = 0x2A,        // 读取单圈 + 多圈扩展数据（ABS0-ABS3 + ABM0-ABM1）
    TAMAGAWA_CF_ID_7 = 0xBA,        // 复位单圈计数 + 清除错误
    TAMAGAWA_CF_ID_8 = 0xC2,        // 复位单圈计数
    TAMAGAWA_CF_ID_C = 0x62,        // 复位多圈计数 + 清除错误
    TAMAGAWA_CF_ID_6 = 0x32,        // 写入EEPROM
    TAMAGAWA_CF_ID_D = 0xEA,        // 从EEPROM读取
} EncTamagawaCf_t; // 编码器控制字段

typedef enum
{
    TAMAGAWA_FRAME_LEN_INIT = 0,    // 初始值
    // 多摩川编码器各CF_ID对应的帧长度（单位：字节）
    TAMAGAWA_FRAME_LEN_ID_0 = 6,    // TAMAGAWA_CF_ID_0：读取单圈数据（ABS0 ABS1 ABS2）
    TAMAGAWA_FRAME_LEN_ID_1 = 6,    // TAMAGAWA_CF_ID_1：读取多圈数据（ABM0 ABM1 ABM2）
    TAMAGAWA_FRAME_LEN_ID_2 = 2,    // TAMAGAWA_CF_ID_2：读取编码器ID（ENID）
    TAMAGAWA_FRAME_LEN_ID_3 = 11,   // TAMAGAWA_CF_ID_3：读取所有数据（ABS + ENID + ABM + ALMC）
    TAMAGAWA_FRAME_LEN_ID_4 = 7,    // TAMAGAWA_CF_ID_4：读取单圈扩展数据（ABS0-ABS3）
    TAMAGAWA_FRAME_LEN_ID_5 = 9,    // TAMAGAWA_CF_ID_5：读取单圈 + 多圈扩展数据（ABS0-ABS3 + ABM0-ABM1）
    TAMAGAWA_FRAME_LEN_ID_7 = 2,    // TAMAGAWA_CF_ID_7：复位单圈计数 + 清除错误
    TAMAGAWA_FRAME_LEN_ID_8 = 2,    // TAMAGAWA_CF_ID_8：复位单圈计数
    TAMAGAWA_FRAME_LEN_ID_C = 2,    // TAMAGAWA_CF_ID_C：复位多圈计数 + 清除错误
    TAMAGAWA_FRAME_LEN_ID_6 = 4,    // TAMAGAWA_CF_ID_6：写入EEPROM
    TAMAGAWA_FRAME_LEN_ID_D = 4,    // TAMAGAWA_CF_ID_D：从EEPROM读取
} EncTamagawaFrameLen_t; // 编码器数据帧长度

// SF字段（MSB）固定位定义回读值（共8位，bit0为dd0最低位，bit7为ca1最高位）（文档6.3.2）
// SF字段（MSB）第bit0-bit3位：信息位，固定为b0000，无额外信息。
// SF字段 编码器错误位（Encoder Error，bit4 ea0、bit5 ea1）宏定义（文档6.3.2）
#define TAMAGAWA_SF_ENC_ERR_COUNTING        0x10  // 计数错误（bit4 ea0=1）
#define TAMAGAWA_SF_ENC_ERR_HARDWARE        0x20  // 硬件错误（bit5 ea1=1，过热、多圈错误、电池错误、电池警告）
#define TAMAGAWA_SF_ENC_ERR_ALL             (TAMAGAWA_SF_ENC_ERR_COUNTING | TAMAGAWA_SF_ENC_ERR_HARDWARE)  // 所有编码器错误位
// SF字段 通信告警位（Communication Alarm，bit6 ca0、bit7 ca1）宏定义（文档6.3.2）
#define TAMAGAWA_SF_COM_ERR_PARITY          0x40  // 奇偶校验错误（bit6 ca0=1）
#define TAMAGAWA_SF_COM_ERR_DELIMITER       0x80  // 分隔符错误（bit7 ca1=1）
#define TAMAGAWA_SF_COM_ERR_ALL             (TAMAGAWA_SF_COM_ERR_PARITY | TAMAGAWA_SF_COM_ERR_DELIMITER)  // 所有通信告警位
// SF字段 编码器错误汇总
#define TAMAGAWA_SF_ERR_ALL                 (TAMAGAWA_SF_ENC_ERR_ALL | TAMAGAWA_SF_COM_ERR_ALL)  // 所有编码器错误位
// 检查SF字段是否存在编码器错误（ea0/ea1/ca0/ca1）
#define IS_TAMAGAWA_SF_ERR(sf)              ((sf) & TAMAGAWA_SF_ERR_ALL)
// 检查SF字段具体错误
#define IS_TAMAGAWA_SF_ENC_ERR_COUNTING(sf)     ((sf) & TAMAGAWA_SF_ENC_ERR_COUNTING)
#define IS_TAMAGAWA_SF_ENC_ERR_HARDWARE(sf)     ((sf) & TAMAGAWA_SF_ENC_ERR_HARDWARE)
#define IS_TAMAGAWA_SF_COM_ERR_PARITY(sf)       ((sf) & TAMAGAWA_SF_COM_ERR_PARITY)
#define IS_TAMAGAWA_SF_COM_ERR_DELIMITER(sf)    ((sf) & TAMAGAWA_SF_COM_ERR_DELIMITER)

// 负载端编码器参数
// NULL
#ifdef __cplusplus
}
#endif

#endif // MOTOR_PARAMETER_WB40ST_TAMAGAWA_H
