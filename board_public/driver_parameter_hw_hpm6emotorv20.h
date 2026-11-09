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
 *   DRIVER_RATED_CURRENT_A  —— 过载积分基准：取电机"最大功率点"1.52A（填 1.50A）。
 *                              不能取 1.20A：各辨识模式都会连续保持额定电流 10~20s，
 *                              基准等于辨识电流时，实测的轻微超调就会被积分成越限，
 *                              电角度辨识实测 3s 就报 Error_word=2（驱动器过载）被强制失能。
 *                              取 1.50A 后：≤1.5A 不计入积分，>1.5A 仍按 2s 窗口保护，
 *                              电机本体温升另有 100℃ 温度保护兜底。
 *   DRIVER_PEAK_CURRENT_A   —— 峰值保护基准（阈值 = 0.9×该值），按板子能力给 3A；
 *                              原来填 1.52A 导致阈值只有 1.368A，而方向辨识电流
 *                              √2×额定 = 1.697A，一使能就必然被判过流。
 *   DRIVER_OVERCURRENT_LIMIT_A —— 20kHz 板级逐周期过流 + App 层单相过流阈值，
 *                              必须 ≥ 0.9×峰值，否则板级会先于软件封桥。
 * 注意：改这三个值要同步改上位机"保护参数→驱动器过流阈值"，否则上位机会把旧值写回来。 */
#define DRIVER_RATED_CURRENT_A          (1.50f)     // 驱动器额定电流（过载积分基准，取电机最大功率点）
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
/* [移植补丁] 极对数辨识电流改用 pole_pairs_id_config.id_tar_max_A。
 * 上游 PolePairsIdStep() 直接写 pmsm_config.rated_current（= √2 × 电机额定 = 1.697A），
 * 完全无视 APP Init 设置的 id_tar_max_A；该电流持续 7s 就会把过载积分顶爆
 * （实测 Error_word=2，辨识必然失败）。见 doc/PORTING_PATCHES.md 补丁 6。 */
#ifndef PORT_PATCH_ID_CURRENT_FROM_CONFIG
#define PORT_PATCH_ID_CURRENT_FROM_CONFIG  (1)  // 极对数辨识电流取配置值而非 √2×额定
#endif
/* [移植补丁] 电角度辨识完成时不自动把结果写回零点。
 * 原因是 d 轴对齐对 PMSM 有 180° 模糊，本机辨识值 220.7° 而正确值 41.6°；
 * 自动写回会把正确的零点改反，导致后续闭环模式震动/飞车。见补丁 7。 */
#ifndef PORT_PATCH_ELEC_BIAS_NO_AUTOAPPLY
#define PORT_PATCH_ELEC_BIAS_NO_AUTOAPPLY  (1)  // 1=辨识结果不自动生效（推荐）
#endif
/* [移植补丁] 转矩脉动与摩擦辨识的跑飞/卡死保护。
 * 本机低速位置环压不住，辨识会反向飞转，而阶段 1 要求"正向转满一圈"，
 * 于是永远出不来（上位机一直"辨识中"、只能手动停）。见补丁 8。 */
#ifndef PORT_PATCH_ID_ABORT_ON_RUNAWAY
#define PORT_PATCH_ID_ABORT_ON_RUNAWAY     (1)  // 1=速度超限或超时则中止辨识
#endif
/* [移植补丁] 转矩脉动辨识开始时把位置目标对齐到当前位置。
 * 上游没初始化 pos_tar_p，进辨识瞬间跟随误差可达 54 万 counts → 直接飞车。见补丁 9。 */
#ifndef PORT_PATCH_TQFC_POS_TAR_INIT
#define PORT_PATCH_TQFC_POS_TAR_INIT       (1)  // 1=进入辨识时 pos_tar_p = pos_now_p
#endif
/* [移植补丁] 转矩脉动/摩擦辨识的运行转速。
 * 上游固定 1.0rad/s(≈10rpm)，本机在这个速度上被定位力微振淹没（扰动峰值速度比目标
 * 大一个数量级），位置环怎么调都只是原地振荡。提到 120rpm 换取信噪比。见补丁 10。 */
#ifndef PORT_PATCH_TQFC_ID_SPEED
#define PORT_PATCH_TQFC_ID_SPEED           (1)  // 1=用下面这个转速，0=用上游 1.0rad/s
#endif
#define TQ_FC_ID_SPEED_RPM                 (120.0f)   // 辨识转速（电机端 rpm）
/* [移植补丁] 辨识期间保留扰动观测器。上游把它关 0，而摩擦系数是从 dob_iq_com_A
 * 采的，关掉之后 fc_p_com/fc_n_com 恒为 0，摩擦项白辨识。见补丁 11。 */
#ifndef PORT_PATCH_TQFC_ID_DOB
#define PORT_PATCH_TQFC_ID_DOB             (1)  // 1=辨识期间打开 DOB
#endif
/* [移植补丁] 辨识完成后不自动启用补偿。上游会在 FINISH 时把 tq_com/fc_com 置 1，
 * 实测本机一启用就自持振荡（给定 0 也飞到 -889rad/s）。改成只算数据不启用。见补丁 12。 */
#ifndef PORT_PATCH_TQFC_LEAVE_COMP_OFF
#define PORT_PATCH_TQFC_LEAVE_COMP_OFF     (1)  // 1=辨识后保持补偿关闭（推荐）
#endif
/* [移植补丁] 运行模式切换后确保对应 APP 被使能。
 * 实测写 opmode 时 set_app() 没生效，APP 一直 IDLE，导致 PvModeRun 不执行、
 * 速度给定恒 0。见补丁 13。 */
#ifndef PORT_PATCH_APP_ENSURE_ENABLED
#define PORT_PATCH_APP_ENSURE_ENABLED      (0)  // 1=每周期检查并补调 set_app
#endif
/* [移植补丁 14] 电流零漂标定结果存 Flash。标定成功后写入 kFlashStorage，
 * 上电从 Flash 恢复，省掉每次上电"先使能做标定"这一步。
 * 注意：真正落盘需要上位机发 SysCmd=2（存盘），与其它参数一致。 */
#ifndef PORT_PATCH_CAL_DRIFT_STORE_FLASH
#define PORT_PATCH_CAL_DRIFT_STORE_FLASH   (1)  // 1=启用标定结果持久化
#endif
/* [移植补丁 15] 直接下发运行模式。上游 set_app_Modes_of_operation 里
 * "val == get_app_Modes_of_operation_display()" 恒真（display 就是回读自己），
 * 导致 0/1/2/3 这些非负运行模式全被吞，只有负值辨识模式能切。
 * 打开后改为与"控制层当前实际模式"比较。见补丁 15。 */
#ifndef PORT_PATCH_OPMODE_DIRECT_APPLY
#define PORT_PATCH_OPMODE_DIRECT_APPLY     (1)  // 1=修掉恒真重复检查
#endif
#define TQ_FC_ID_ABORT_ERR_P               (32768)   // 位置跟随误差超过 2 圈即判定跑飞/跟不上
#define TQ_FC_ID_GRACE_MS                  (1000U)    // 使能后 1s 内不判定
#define TQ_FC_ID_TIMEOUT_MS                (60000U)   // 辨识总时长上限（正常约 11s）

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
