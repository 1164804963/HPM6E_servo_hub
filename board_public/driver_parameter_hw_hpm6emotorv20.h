#ifndef DRIVER_PARAMETER_HW_HPM6EMOTORV20_H
#define DRIVER_PARAMETER_HW_HPM6EMOTORV20_H

// 整个驱动器硬件参数：HPM6EMotorV20（HPM6E8YIGN1 + STDRIVE101 + 6x BSC040N10NS5）

#ifdef __cplusplus
extern "C"
{
#endif

// 硬件固有参数
// 电流环 20kHz，与现有已验证固件一致；位置速度环 1kHz，对应现有固件 1ms 位置环。
#define CURRENT_FREQUENCY_HZ            (20000.0f)  // 电流环工作频率
#define POSITION_FREQUENCY_HZ           (1000.0f)   // 位置速度环工作频率
#define NRT_TASK_FREQUENCY_HZ           (1000.0f)   // 非实时任务工作频率
#define NRT_TASK_PERIOD_S               (1.0f / NRT_TASK_FREQUENCY_HZ)  // 非实时任务周期

// 电流采样：PR1/2/3 四端 10mΩ 下桥臂取样 -> U6(TP2274) 差分放大，1K/10K 增益 10
// -> 偏置 VREF/2 = 1.65V -> PF28(I_U) PF29(I_V) PF30(I_W)，ADC 16bit，VREFH = 3.3V
// 0.10 V/A，1A 约 1986 counts
#define UVW_CURRENT_SAMP_RES            (0.010f)    // UVW电流采样电阻值 Ω
#define DC_BUS_CURRENT_SAMP_RES         (0.001f)    // 本板无独立母线电流采样电阻，保留定义供算法层编译
#define CURRENT_SAMP_OPAMP_VOLTAGE_GAIN (10.0f)     // 电流采样电路 运算放大器 电压放大倍数
#define UVW_CURRENT_SAMP_ADC_K          (ADC_REFERENCE_V / ADC_RESOLTION / \
                                        (CURRENT_SAMP_OPAMP_VOLTAGE_GAIN * UVW_CURRENT_SAMP_RES))   //UVW电流采样ADC转化系数
#define DC_BUS_CURRENT_SAMP_ADC_K       (ADC_REFERENCE_V / ADC_RESOLTION / \
                                        (CURRENT_SAMP_OPAMP_VOLTAGE_GAIN * DC_BUS_CURRENT_SAMP_RES)) //母线电流采样ADC转化系数
// 母线电压：VM -> R140 200K -> VBUS_VOL -> R179 10K -> AGND，分压比 21:1，PF31
// 满量程 = 3.3V * 21 = 69.3V；本板母线 12V，量程余量充足
#define DC_BUS_ADC_VOLTAGE_K            (ADC_REFERENCE_V / ADC_RESOLTION * 21.0f)  //母线电压采样ADC转换系数
#define DC_BUS_ADC_VOLTAGE_BIAS         (0.0f)      // 母线电压校准偏置，L0 阶段用万用表实测修正
#define DC_BUS_ADC_CURRENT_BIAS         (0.0f)      // 无独立母线电流通道，保留定义

#define UVW_CURRENT_MID_VAL             (ADC_RESOLTION * 0.5f) // 电流校准理论值（分辨率中间值）
#define UVW_CURRENT_ERROR_RANGE         (0.10f)     // 电流校准误差范围(10%)
// 采样极性：SNSU_P/SNSU_N 接法决定符号。
// L0 实测（电压模式给 vec 1V@0° -> u=+1.0/v=-0.5/w=-0.5V）时读到的是
// iu=-0.38A / iv=+0.34A / iw=+0.21A，与"加正电压的相电流为正"相反，故取 -1。
// 这一位填错会让电流环变成正反馈：积分十几毫秒就顶到限幅，一使能就过流。
#define UVW_CURRENT_DIRECTION           (-1.0f)     // 电流采样方向 1：正向  -1：反向

#define CURRENT_SAMP_NOISE_A            (0.02f)     // 电流采样噪声绝对值
#define VOLTAGE_COMPENSATION_V          (0.00f)     // 死区电压补偿值：死区由 U9 DT/MODE 引脚设定，软件不叠加

/* 电流保护基准（motor: EC1636-12120 12V，板子实测可输出 2.5~3A）
 *   DRIVER_RATED_CURRENT_A  —— 过载积分基准，取"电机额定"，保住电机热保护：
 *                              电机数据 最大效率点 0.45A / 最大功率点 1.52A，
 *                              1.52A 也只能短时运行，不能当连续额定用。
 *   DRIVER_PEAK_CURRENT_A   —— 峰值保护基准（阈值 = 0.9×该值），按板子能力给 3A；
 *                              原来填 1.52A 导致阈值只有 1.368A，而方向辨识电流
 *                              √2×额定 = 1.697A，一使能就必然被判过流。
 *   DRIVER_OVERCURRENT_LIMIT_A —— 20kHz 板级逐周期过流 + App 层单相过流阈值，
 *                              必须 ≥ 0.9×峰值，否则板级会先于软件封桥。
 * 注意：改这三个值要同步改上位机"保护参数→驱动器过流阈值"，否则上位机会把旧值写回来。 */
#define DRIVER_RATED_CURRENT_A          (1.20f)     // 驱动器额定电流（过载积分基准）
#define DRIVER_PEAK_CURRENT_A           (3.00f)     // 驱动器峰值电流（峰值保护阈值 = 0.9×3.0 = 2.7A）
#define DRIVER_OVERCURRENT_LIMIT_A      (3.00f)     // 驱动器过电流保护阈值（板级逐周期 + App 单相）
#define DRIVER_PWM_READY_TIME           (0)         // PWM使能后等待时间 (单位 位置环周期数)

/* ============================================================================
 * 移植补丁开关（PORT PATCH SWITCHES）
 *
 * 只在本板定义。通用层（motor_control / app / database）里的这几处改动全部用
 *     #if defined(PORT_PATCH_xxx) && (PORT_PATCH_xxx)  ...  #else 原工程逻辑 ... #endif
 * 包起来了：换到 Y01 或其它没定义这些宏的平台，编译出来就是原工程的行为，一行不变。
 *
 * 每条补丁的"现象 / 根因 / 为什么只能在这里改 / 何时可以删"见
 *     doc/PORTING_PATCHES.md
 * ========================================================================== */
#ifndef PORT_PATCH_PWM_KEEPALIVE
#define PORT_PATCH_PWM_KEEPALIVE        (1)  // 桥臂被关掉后每周期重试开波（防 hw_ready 死锁）
#endif
#ifndef PORT_PATCH_CAL_AUTOSTART
#define PORT_PATCH_CAL_AUTOSTART        (1)  // 零漂未完成时先开波再标定（解开"标定↔开波"互锁）
#endif
#ifndef PORT_PATCH_FAST_OC_VISIBLE
#define PORT_PATCH_FAST_OC_VISIBLE      (1)  // 板级 20kHz 过流上报到 App 错误位
#endif
#ifndef PORT_PATCH_CLEAR_ERROR_FIX
#define PORT_PATCH_CLEAR_ERROR_FIX      (1)  // 清错命令期间不要回写失能（否则错误永远清不掉）
#endif
#ifndef PORT_PATCH_ID_MODE_RESEND
#define PORT_PATCH_ID_MODE_RESEND       (1)  // 辨识模式（负值）允许重复下发
#endif

/* 关掉全部补丁（= 完全回到上游逻辑）时可以用编译选项覆盖：
 *     -DPORT_PATCH_PWM_KEEPALIVE=0 -DPORT_PATCH_CAL_AUTOSTART=0 ... */

// 温度：PF8 = MCP9700(10mV/℃, 0℃=500mV) 与选配 NTC 共用节点
#define MOS_TEMP_VOLTAGE_K              (3300.0f / ADC_RESOLTION)
#define MOS_TEMP_SENSOR_K               (0.1f)
#define MOS_TEMP_SENSOR_BIAS            (500.0f)
#define MOTOR_TO_IN_VOLTAGE_RATIO       (1.0f)      // MCP9700 直接进 ADC，无额外分压

// 硬件保护参数（母线 12V 系统）
#define UNDER_VOLTAGE_PROTECTION_V      (9.0f)      // 低压保护电压
#define OVER_VOLTAGE_PROTECTION_V       (15.0f)     // 高压保护电压

#define K_LPF_TEMP                      (0.3859f)   // 温度滤波系数  100HZ  1ms周期
#define MOTOR_NTC_FAULT_C               (600.0f * K_LPF_TEMP)   // 电机温度NTC传感器故障温度阈值
#define OVER_TEMP_PROTECTION_C          (115.0f)    // 高温保护温度
#define OVER_TEMP_WARNING_C             (105.0f)    // 高温警告温度
#define UNDER_TEMP_PROTECTION_C         (-40.0f)    // 低温保护温度
#define UNDER_TEMP_WARNING_C            (-25.0f)    // 低温警告温度

#ifdef __cplusplus
}
#endif

#endif // DRIVER_PARAMETER_HW_HPM6EMOTORV20_H
