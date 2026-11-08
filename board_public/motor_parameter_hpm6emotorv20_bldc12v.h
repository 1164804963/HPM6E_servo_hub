#ifndef MOTOR_PARAMETER_HPM6EMOTORV20_BLDC12V_H
#define MOTOR_PARAMETER_HPM6EMOTORV20_BLDC12V_H

// 模组参数：12V 微型无刷电机 + MT6816(14bit SPI) 电机端编码器 + 107:1 行星减速器。
// 数值取自现有已跑通固件 app/motor/bldc_foc.c 的 motor_init()，见各条注释。

#ifdef __cplusplus
extern "C"
{
#endif

// --------------------------
// 电机及负载参数
// --------------------------
#define PMSM_J                          (3.0e-06f)                      // 转动惯量 kg*m^2（本次实测：0.5A 转矩阶跃 0->9500rpm 约 0.7s，J = kt*I/alpha）
#define PMSM_Lp2p                       (0.234e-03f)                    // 相间电感 H（相电感 117uH * 2）
#define PMSM_Rp2p                       (3.54f)                         // 相间电阻 Ω（相电阻 1.77Ω * 2）
#define PMSM_RATED_CURRENT              (1.20f)                         // 电机额定电流 A（速度环 q 轴限幅）
#define PMSM_PEAK_CURRENT               (1.52f)                         // 电机峰值电流 A（现有固件 motor.i_max）
#define PMSM_PN                         (1.0f)                          // 极对数
#define PMSM_SPEED_MAX_RPM              (12000.0f)                      // 电机最大转速 RPM
// KT = 1.5 * pn * flux = 1.5 * 1 * 5.85mWb = 8.775e-03 N*m/A = 8.775 mN*m/A
#define PMSM_TORQUE_CONSTANT_MNM_A      (8.775f)                        // 电机转矩常数 mN*M/A

// 电角度零点：编码器角减去这个偏置才是电角度（见 motor_pos_sensor.c）。
// L1 实测：mode 127 + 电压矢量打在 0° 时转子停住，当时的编码器角 = 221.6°，
// 填进来以后电角度 0 就对应转子 d 轴与 A 相轴线重合。
// 【复核记录 2026-11-08】曾一度改成 41.6°（= 221.6-180），理由是怀疑"电压矢量对齐
//   有 180° 模糊、当时选错了分支"。该结论是**错的**：当时的 A/B 对照被另一个 bug 污染
//   ——转矩脉动辨识进入时没有把 pos_tar_p 对齐到当前位置，跟随误差高达 54 万 counts
//   （见 motor_ctl_sm.c 补丁 9）。修掉那个 bug 后重新做干净对照：
//     零点 221.6°：辨识正向平缓转动（+34rpm），速度模式 ±2rad/s 稳定，方向正确；
//     零点  41.6°：辨识强力反向飞车（-1220rpm），是正确的反向。
//   另外电角度辨识实测 220.7°（两次采样 3.8622/3.8373），与 221.6° 只差 0.9°，
//   也印证 221.6° 是对的。**保持 221.6°，不要再减 180°。**
#define PMSM_ELEC_ANGLE_BIAS_DEG        (221.6f)
#define PMSM_ELEC_ANGLE_BIAS_RAD        (PMSM_ELEC_ANGLE_BIAS_DEG / 57.29578f)

// 编码器类型通过宏定义指定
#define ENCODER1_TYPE_OPTION            (ENCODER_TYPE_ABS_SPI_MT68XX)   // 电机端编码器类型
#define ENCODER2_TYPE_OPTION            (ENCODER_TYPE_NONE)             // 负载端无编码器
// 电机端编码器参数：MT6816 14bit，每圈 16384
#define PMSM_MOTOR_ENC_LINE_ORG         (16384u)                        // 电机端编码器原始分辨率（P/R）
#if PMSM_MOTOR_ENC_LINE_ORG == 0
#error "PMSM_MOTOR_ENC_LINE_ORG must be greater than 0"
#endif /*PMSM_MOTOR_ENC_LINE_ORG == 0*/
#define PMSM_MOTOR_ENC_LINE_P_N         (PMSM_MOTOR_ENC_LINE_ORG / 1u)  // 电机端编码器控制分辨率（P/R）
#define PMSM_MOTOR_ENC_MULTI_LINE_P_N   (0u)                            // 硬件无多圈，由软件累计
#define PMSM_MOTOR_ENC_DIR              (0u)                            // 0：不变，1：反向（L1 阶段实测确认）
// 负载端编码器参数：无
#define PMSM_LOAD_ENC_LINE_ORG          (0u)
#define PMSM_LOAD_ENC_LINE_P_N          (0u)
#define PMSM_LOAD_ENC_MULTI_LINE_P_N    (0u)
#define PMSM_LOAD_ENC_DIR               (0u)
// 负载端（齿轮/减速机...）参数：电机轴经 107:1 行星减速器输出（编码器仍在电机端）
//   负载端位置 = 电机端位置 / 107，负载端速度 = 电机端速度 / 107。
//   走的是 data_param.c 的 get_app_Position_actual_value_inc()：
//   负载端无编码器 且 Reduction_ratio_num != 1 → PosUnitMotorToLoad() 换算。
//   方向辨识等控制层算法仍用电机端编码器(enc_sum_p)，不受此值影响。
// 注意：减速比会被 FlashDB 参数覆盖（app_store_param.c:304-305），
//       已存过参数的板子升级后需要"恢复出厂设置"或在上位机里改 107/1 并保存才生效。
#define GEAR_RATIO_NUM                  (107u)
#define GEAR_RATIO_DEN                  (1u)
#define GEAR_RATIO                      (107.0f)
#define GEAR_BACKLASH_LOAD              (0.0f)
#define GEAR_BACKLASH_MOTOR_PULSE       (GEAR_BACKLASH_LOAD * GEAR_RATIO / 360.0f * PMSM_MOTOR_ENC_LINE_P_N)

// --------------------------
// 电机保护参数
// --------------------------
// 温度传感器：MCP9700，10mV/℃，0℃ = 500mV；ADC 16bit / 3.3V
// ℃ = count * (3.3/65535) * 1000 / 10 - 50 = count * 0.005036 - 50
#define MOTOR_TEMP_SENSOR_K                 (0.005036f)                 // 每 ADC count 对应 ℃
#define MOTOR_TEMP_SENSOR_BIAS              (-50.0f)                    // 0℃ 时候 偏置值
#define MOTOR_HIGH_TEMP_FAULT_THRESHOLD     (100.0f)                    // 电机过温保护阈值（℃）
#define MOTOR_LOW_TEMP_FAULT_THRESHOLD      (-40.0f)                    // 电机低温保护阈值（℃）
#define MOTOR_HIGH_TEMP_WARING_THRESHOLD    (85.0f)                     // 电机过温警告阈值（℃）
#define MOTOR_LOW_TEMP_WARING_THRESHOLD     (-20.0f)                    // 电机低温警告阈值（℃）
// 抱闸：本板制动电路（Q11/Q12/J5）已画，但 BRAKE 到 Q12 栅极的连接在原理图中未确证，
// 首版 bsp 侧按空实现处理，见 PORTING_HPM6E80.md「已知未实现」。
#define BRAKE_RATED_VOLTAGE                 (24.0f)
#define DYNAMIC_BRAKE_SPEED_THRESHOLD       (10.0f)
#define BRAKE_ENGAGE_DELAY_TIME             (0.0f)
#define BRAKE_ENGAGE_ACTION_TIME            (0.0f)
#define BRAKE_RELEASE_DELAY_TIME            (0.0f)
#define BRAKE_RELEASE_ACTION_TIME           (0.0f)
#define BRAKE_RELEASE_ACTION_VOLTAGE        (BRAKE_RATED_VOLTAGE * 1.0f)
#define BRAKE_RELEASE_HOLD_VOLTAGE          (BRAKE_RATED_VOLTAGE * 0.5f)
#define BRAKE_RELEASE_PWM_FREQ              (10000u)

// --------------------------
// 电机控制参数
// --------------------------
// 电流环：按 300Hz 带宽算（wc = 2π*300 = 1885 rad/s）
//   kp = L*wc = 117uH*1885 = 0.2205
//   ki = R*wc = 1.89Ω*1885 = 3562   （R 取含驱动侧的 1.89Ω）
// 注意 ki 是连续域增益：生成代码里的积分器写的是 ki*err*dt_s（见 current_ctl_loop_task.c），
// 不是"每个采样周期累加 ki*err"。按后者算出来的 0.1781 会让积分项慢 1/dt_s = 20000 倍，
// 表现就是只有比例项在起作用、电流停在 0.1A 上不去。
#define CURRENT_CTL_CONFIG_KP_LD                    (2.205e-01f)        // d轴电流环比例增益
#define CURRENT_CTL_CONFIG_KI_LD                    (3.562e+03f)        // d轴电流环积分增益（1/s）
#define CURRENT_CTL_CONFIG_KP_LQ                    (2.205e-01f)        // q轴电流环比例增益
#define CURRENT_CTL_CONFIG_KI_LQ                    (3.562e+03f)        // q轴电流环积分增益（1/s）
#define CURRENT_CTL_CONFIG_PWM_DUTY_CYCLE_MAX       (0.9f)              // 最大占空比
#define CURRENT_CTL_CONFIG_ELEC_ANGLE_COMPENSATION  (0.0f)              // 电角度补偿系数（度），先 0，L2 再标
#define CURRENT_CTL_CONFIG_PHASE_DIR                (1)                 // 电机相序 1:abc -1:cba

// 位置速度环：按实测惯量重算（J = 3e-6 kg*m^2，kt = 8.775 mN*m/A）
//   速度环对象: dw/dt = (kt/J) * iq = 2933 * iq      [1/s^2 per A]
//   生成代码里 P 通道 = kp_s，I 通道 = ki_s * (kt/J)（见 pos_speed_ctl_pip.c 的 1/j_kt）
//   【实测标定（2026-11-08）】本机编码器在开波状态下有 ±30~120 counts 的读数抖动
//   （电机静止通电时的定位力微振，见 PORTING_PATCHES.md 第五节），折合速度噪声约 ±5 rad/s。
//   速度环增益过高会把这份噪声放大成自激：
//     kp_s=0.102 / ki_s=7.67  → 速度模式一起使能就飞到 −906 rad/s（-8650rpm）
//     kp_s=0.020 / ki_s=1.00  → 仍然飞车（−920 rad/s）
//     kp_s=0.040 / ki_s=2.00  → 仍然飞车（−914 rad/s）
//     kp_s=0.010 / ki_s=0.50  → 稳定，speed_now 只有 ±1.3 rad/s，err=0
//   对应 wn = sqrt(ki_s * kt/J) ≈ 38 rad/s（6Hz）。稳定边界在 0.01~0.02 之间，留了余量。
//   要提速的话应先降低编码器噪声（硬件屏蔽/滤波），再往上调增益。
#define POS_SPEED_CTL_CONFIG_KP_P                   (2.00e+01f)         // 位置环比例增益 1/s
#define POS_SPEED_CTL_CONFIG_KI_S                   (5.00e-01f)         // 速度环积分增益
#define POS_SPEED_CTL_CONFIG_KP_S                   (1.00e-02f)         // 速度环比例增益 A/(rad/s)
#define POS_SPEED_CTL_CONFIG_J_KT                   (0.0f)              // 惯性前馈，待惯量单位确认后填
#define POS_SPEED_CTL_CONFIG_AFF                    (0.0f)              // 加速度前馈增益
#define POS_SPEED_CTL_CONFIG_VFF                    (1.0f)              // 速度前馈增益

// 负载扰动观测器
#define POS_SPEED_CTL_CONFIG_DOB_ENABLE             (0u)                // 0：禁用，1：启用
#define POS_SPEED_CTL_CONFIG_DOB_WN_HZ              (4.00e+02f)         // 负载扰动观测器角频率（Hz）

// 速度观测器带宽：位置环 1kHz 下必须远低于采样率。
// 观测器是 PLL 的欧拉离散实现，稳定条件大约是 wn_Hz < 0.16 * fs（1kHz 时约 160Hz）；
// 原固件 4kHz 位置环用 800Hz，比值 0.2，照搬到 1kHz 就是 200Hz —— 实测发散（速度估到
// 上千 rpm，控制层直接报过速）。这里取 100Hz，留足裕量。
#define SPEED_OBS_PLL_WN_HZ                         (100.0f)            // 速度观测器带宽（Hz）

// MT6816 协议定义（与现有固件 encoder_mt6816.c 一致）
typedef enum
{
    MT68XX_CF_INIT                      = 0x00,
    MT68XX_CF_ID_RD                     = 0x30,
    MT68XX_CF_ID_WR                     = 0x60,
} EncMt68xxCf_t;

typedef enum
{
    MT68XX_LEN_INIT                     = 0,
    MT68XX_FRAME_LEN_RD_ANGLE           = 6,
    MT68XX_DATA_LEN_RD_ANGLE            = 4,
    MT68XX_RD_ANGLE_STATUS_BW           = 3,
} EncMt68xxFrameLen_t;

typedef enum
{
    MT_STAS_NORMAL_BIT                  = 0,
    MT_STAS_OVER_SPEED_BIT              = 1,
    MT_STAS_MAGNETIC_WEAK_BIT           = 2,
    MT_STAS_UNDER_VOL_BIT               = 4,
    MT_STAS_CRC_CHECK_ERROR_BIT         = 8,
} MT6835_STATUS_DEF;

typedef enum
{
    MT_REG_USER                         = (0x001),
    MT_REG_ANGLE_H                      = (0x003),
    MT_REG_ANGLE_M                      = (0x004),
    MT_REG_ANGLE_L                      = (0x005),
    MT_REG_CRC8                         = (0x006),
    MT_REG_IO_CALSPD                    = (0x00E),
    MT_REG_CAL_STAS                     = (0x113),
} MT6835_REG_DEF;

#define MT68XX_CRC8_POLY                (0x07)

#ifdef __cplusplus
}
#endif

#endif // MOTOR_PARAMETER_HPM6EMOTORV20_BLDC12V_H
