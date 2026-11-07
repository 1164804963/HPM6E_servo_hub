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
#define DRIVER_RATED_CURRENT_A          (1.20f)     // 驱动器额定电流 iq峰值电流
#define DRIVER_PEAK_CURRENT_A           (1.52f)     // 驱动器峰值电流 iq峰值电流
#define DRIVER_OVERCURRENT_LIMIT_A      (2.00f)     // 驱动器过电流保护阈值
#define DRIVER_PWM_READY_TIME           (0)         // PWM使能后等待时间 (单位 位置环周期数)

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
