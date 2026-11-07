# servo_hub -> HPM6EMotorV20 移植说明

本文只记录**移植的边界、映射和验收方法**。架构设计理由见上一轮讨论，不在这里重复。

- 母体：`servo_hub`（MIT，YuanHub），分层为 便携层 / `bsp_api.h` / 板级。
- 目标板：`HPM6EMotorV20`（HPM6E8YIGN1 + STDRIVE101 + 6×BSC040N10NS5，12V 母线，MT6816 14bit SPI 编码器）。
- 原则：**只新增 `embedded_project/HPM6E80/` 一个目录 + `board_public/` 两份参数头；其余目录一行不改。**

---

## 0. 上板之后修正的几处说法（2026-11-06，实板 L0–L2 验证）

本文其余部分保留移植时的原始判断，下面这几条是实测后需要改的，以本节为准：

| 原文说法 | 实测结论 |
|---|---|
| 第 3 节"servo_hub 是逐相 SPWM，与现有固件 SVPWM 差 15.5% 电压利用率" | **错的**。`simulink_code_gen/current_ctl_loop_task.c` 里已经有 min-max 法 SVPWM（减去 `0.5*(vmax+vmin)`），`bsp_set_phase_voltage` 的 `duty = 0.5 + V/Vbus` 正好接上这个约定，不需要再改调制 |
| 第 3 节电流环 `KI_LD/KI_LQ = 0.1781`（按 `R*wc*Ts` 算） | **错的**。生成代码的积分器是 `ki*err*dt_s`（连续域），ki 应取 `R*wc = 3562`。用 0.1781 时积分慢 20000 倍，电流只能到 0.1A |
| 第 2 节 `UVW_CURRENT_DIRECTION = 1.0 待实测` | 实测为 **-1**：`vec 1V@0°` 时 U 相给定 +1.0V 却读到负电流。填错会让电流环正反馈 |
| 第 4 节 L1"示波器测相电压" | 没有示波器也能做：用编码器读数验证。`vec 1 0` 记住对齐角，`vec 1 90` 看编码器是否 +90°，同时得到电角度零点偏置 |
| 第 5 节"零漂校准在 PWM 封锁时做" | **要改**：运放零点随共模电压变化，桥臂封锁时采的零点与运行态差 0.1~0.2A。必须在"桥臂放开 + 相电压 0（50% 占空比）"时采，见 `servo_bringup.c` |
| 第 2 节温度采样"首版未接入 DMA 队列" | 仍未接，`motor_temp` 恒 -50℃，`st` 里会显示 `temp_raw=0` |
| 工具链"rv32imac" | 必须用 **rv32imafc + ilp32f**（硬件浮点），否则 20kHz 中断占掉 60% CPU |
| 第 2 节"六路 PWM PD00..PD05" | 引脚复用**必须在 `board_init_servo()` 里显式调 `init_pwm_pins(BOARD_BLDCPWM)`**。SDK 板级包的 `board_init()` 不含这一步（官方例程在应用自己的 `pwm_init` 里调）。漏掉时状态机显示 `pwm=1`、比较值也写对了，但相电流恒为 0。更坑的是 IOC 配置不吃内核复位，上一版固件留下的复用状态会让人以为"能转就是对的"，一断电就原形毕露 |

新增的 `Board/` 文件（都是这次为了上板补的）：
`version.h`、`hpm_math.h`、`servo_math_port.c`、`servo_bringup.c/.h`、`servo_console.c/.h`。

---

## 1. 目录与边界

```
board_public/
  driver_parameter_hw_hpm6emotorv20.h     新增：本板硬件常数
  motor_parameter_hpm6emotorv20_bldc12v.h 新增：本电机 + 编码器 + 环路初值
  bsp_api.h                               冻结，不改
embedded_project/HPM6E80/
  CMakeLists.txt                          HPM SDK 构建入口
  Board/
    main.c                                组合根：初始化顺序写死在这里
    servo_board.h                         本板硬件映射 + BspData
    servo_system_cfg.h                    选参数头（换板/换电机只改这里）
    board.c                               PWM / ADC / 20kHz 与 1ms 节拍 / 中断入口
    bsp_api.c                             bsp_api.h 的全部实现（含 sys_* 与电流零漂校准）
    system_timer.c/.h                     rdcycle 计时与阻塞延时
    drv_encoder.c/.h                      MT6816 适配到 bsp 编码器接口
    encoder_mt6816.c/.h                   从现有已验证工程原样拷贝
boards/hpm6e00YZ/                         SDK 板级包（时钟/引脚/BOARD_* 宏），原样拷贝
cmake/hpm-project.cmake                   原样拷贝，SDK 路径来自 .vscode/settings.json
```

边界检查：

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File tools/check_layer_boundary.ps1
```

检查三条：便携层不出现 `hpm_*`；板级硬件文件不引用 `app_*`；SIL 工程文件仍在。

### 既存例外（移植时照抄，不放大）

| 位置 | 现象 | 处理 |
|---|---|---|
| `common/math_lib/yuanhub_math.h` | 用 `ARM_MATH_*` / `HPMSOC_*` 宏做三平台分支 | 保留，HPM 分支已存在 |
| `communication/callback/mavlink/mavlink_callback.h` | 同一个 `HPMSOC` 分支 | 保留 |
| `board_public/system_manage/system_init.h` | 便携层反向包含 `board.h` | 保留；HPM 侧解析到 SDK 板级包 |
| `embedded_project/HPM6E80/Board/main.c` | 同时包含两侧头文件 | 允许——它是组合根，不承载逻辑 |

**不要**在移植期间顺手重构上面任何一处。等 L5 通过、SIL 回归跑起来之后再单独一轮收拾。

---

## 2. 硬件映射（原理图 → 代码）

| 功能 | 原理图 | 代码 |
|---|---|---|
| 六路 PWM | PD0..PD5 → IN_UH/UL/VH/VL/WH/WL | `BOARD_PWM0` ch0..ch5，`BOARD_BLDCPWM_*` |
| PWM 触发 ADC | PWM0 TRGO_0 → TRGM0 → ADC PTRGI0A | `board_init_trigger_mux()`，触发点 = 计数器 1（三角波底部） |
| 相电流 U | PF28 ← U6A(10mΩ×10) | ADC2.CH5，`BOARD_BLDC_ADC_CH_U` |
| 相电流 V | PF29 ← U6B | ADC3.CH4，`BOARD_BLDC_ADC_CH_V` |
| 相电流 W | PF30 ← U6C | ADC2.CH6，`BOARD_BLDC_ADC_CH_W`（与 U 同队列第 2 槽） |
| 母线电压 | PF31 ← R140/R179 = 21:1 | ADC3.CH7，`BOARD_BLDC_ADC_VBUS_CH` |
| 温度 | PF8 ← MCP9700 | ADC3，`adc_temp_raw`（**首版尚未接入 DMA 队列，见第 5 节**） |
| 编码器 | SPI7 PD20..PD23 | `encoder_mt6816.c`（自管引脚，不依赖板级 pinmux） |
| 死区 | U9 DT/MODE，R75 0Ω 到 BGND | 硬件死区 + `PWM_DEAD_AREA_TICK=100`，软件不做补偿 |
| 使能 | 六路 PWM 强制输出闸门 | `board_set_pwm_enable()` |

### 关键常数（`driver_parameter_hw_hpm6emotorv20.h`）

| 常数 | 值 | 来源 |
|---|---|---|
| `UVW_CURRENT_SAMP_RES` | 0.010 Ω | PR1/2/3 四端 10mΩ |
| `CURRENT_SAMP_OPAMP_VOLTAGE_GAIN` | 10 | R26/R29=1K，R25=10K |
| `UVW_CURRENT_SAMP_ADC_K` | 5.0354e-4 A/count | 3.3V / 65536 / (10×0.010)，1A≈1986 counts |
| `DC_BUS_ADC_VOLTAGE_K` | 1.0574e-3 V/count | 3.3V / 65536 × 21 |
| 母线量程 | 69.3V | 3.3V × 21，12V 系统余量充足 |
| `OVER/UNDER_VOLTAGE_PROTECTION_V` | 15V / 9V | 12V 母线 |
| `UVW_CURRENT_DIRECTION` | **1.0 待实测** | 由 SNSU_P/SNSU_N 接法决定，L0 阶段确认 |

---

## 3. 控制栈的差异（必须知道）

| 项 | 现有已跑通固件 | servo_hub（本工程） |
|---|---|---|
| 调制 | SVPWM（0.98 缩放 + 中心对齐影子比较值） | **逐相 SPWM**：`duty = 0.5 + V/Vbus` |
| 电流环输出 | dq 电压 → SVPWM | abc 三相电压 → BSP 直算占空比 |
| 死区补偿 | 关闭 | 关闭（`VOLTAGE_COMPENSATION_V = 0`） |
| 前馈 | Iq 二次谐波前馈（拟合系数） | 无，需在 `alg_custom/` 补回 |
| 速度/位置环 | 4kHz / 1kHz | 统一 1kHz（`POSITION_FREQUENCY_HZ`） |
| 相电流 | 两相重构（U、V） | 三相全采（U、V、W） |

**SPWM 与 SVPWM 的电压利用率差约 15.5%**，所以 `CURRENT_CTL_CONFIG_KP_LD/KI_LD` 的初值只是起点（按 300Hz 带宽算得 0.2205 / 0.1781），L2 阶段必须以 d 轴阶跃实测重标。

---

## 4. L0–L5 验收清单

每条都要留记录（串口输出或示波器截图），不要凭"能转"下结论。

### L0 静态映射（PWM 封锁）

- [ ] 上电不使能，串口打印的 `adc_u_raw/adc_v_raw/adc_w_raw` 都在 32768 附近
- [ ] 直流注入 1A（或已知负载）→ 对应相电流读数 1.00A ±2%
- [ ] 反向后确认 `UVW_CURRENT_DIRECTION` 符号正确
- [ ] 万用表测 VM = 12.0V → `bsp_get_dc_bus_voltage()` 读数 12.0V ±2%，否则修 `DC_BUS_ADC_VOLTAGE_BIAS`
- [ ] `sys_current_calibration_step()` 能把状态推到 `CURRENT_CALIBRATION_STATUS_OK`，打印三路零漂

### L1 开环电压（**极性实验，必须先做**）

- [ ] 封锁电流环，给 `bsp_set_phase_voltage()` 固定 1V/2V/5V，示波器测 U 相相对 BGND
- [ ] 相电压随指令**单调递增**，5V 指令误差 <5%
- [ ] 若极性相反：检查 `pwm_cmp_half` 与 `reload_half ± cmp_half` 的方向，**不要**直接翻 `voltage[i]` 符号掩盖
- [ ] 三相对称：同一指令下 U/V/W 幅值差 <2%

### L2 电流环闭锁

- [ ] 转子锁死，`idq_tar = [0.3, 0]` 阶跃到 `[0.7, 0]`
- [ ] 记录上升时间、超调、稳态误差，与现有固件同工况对比，差 <10%
- [ ] 不达标时改 `CURRENT_CTL_CONFIG_KP_LD/KI_LD`（因 SPWM 需重标）
- [ ] 用 `bsp_set_timer_record_start/stop` 量 `CurrentLoopCtrl()` 周期数，确认 50µs 预算有余量

### L3 速度环

- [ ] 空载 200/1000/2000/3000 rpm 稳转
- [ ] 相电流 THD 不劣于现有固件 20%
- [ ] 转矩脉动峰峰值（若补回 iqcomp 则对比开关前后）

### L4 位置环

- [ ] 梯形轨迹跟随误差峰值不劣于现有固件
- [ ] 使能瞬间无冲击电流（验证 `enable` 时 PI 积分已复位、占空比已预置中性值）

### L5 保护

- [ ] 欠压 9V、过压 15V 跳闸，误差 <5%
- [ ] 过流 2.0A 跳闸
- [ ] 拔掉编码器 SPI → 故障上报（当前由 `drv_encoder_get_state()` 反映）
- [ ] 每项都能清除并重新使能

---

## 5. 已知偏差（有意为之，不是遗漏）

`board_public/system_manage/system_init.c` 的 `CurrentCalibrationStep()` 直接引用
`UVW_CURRENT_U_CHANNEL / _V_ / _W_` 三个宏，这三个宏在 Y01 的 `board.h` 里展开成 `hadcX.Instance->JDR1`。
也就是说这个"共享"模块实际上和 Y01 板绑死。

本板处理方式：**不编译 `system_init.c`**，把同一套状态机（总线电压去抖、零漂校准 1024 次平均、
自检标志）实现在 `Board/bsp_api.c` 的 `sys_*` 函数里，数据源是 `kBspData` 而不是 ADC 寄存器；
`main.c` 把 `HalInit()` 的 10 步初始化显式展开成 `servo_app_init()`。

这样便携层一行没改，也没有把板级宏塞进 SDK 板级包。如果后续要恢复共享，
正确做法是给 `bsp_api.h` 加 `bsp_get_phase_current_raw(uint16_t raw[3])`，
让 `system_init.c` 不再碰 ADC —— 那是一次有测试兜底的独立改动，不在本次移植里做。

---

## 6. 已知未实现（首版明确留空）

| 项 | 现状 | 后续 |
|---|---|---|
| FlashDB 参数存储 | `bsp_flashdb_*` 全部返回错误 | 需要 fal_flash 端口（HPM ROM API + XPI NOR 分区），第 5 周后 |
| CAN 收发 | 只保留 get/set 变量 | 需要 HPM MCAN 驱动 + mavlink 传输 |
| 固件升级 / 文件传输 | 空实现 | 依赖 FlashDB 与 Bootloader 分区 |
| 抱闸 PWM | 空实现 | 原理图 BRAKE→Q12 连接未确证，需实板确认后再实现 |
| MOS/MCU 温度 | 返回 0℃ | 本板只有 NTC1，若确需可复用同一节点 |
| 数字 IO | 读回 false | J11 直出引脚，需要时再配 |
| 温度采样入队 | `adc_temp_raw` 未进 ADC 队列 | 需要第二个 ADC 触发或软件单次转换 |
| MAVLink 传输 | 未注册发送回调 | 与 CAN/ECAT 一起做 |

---

## 7. 与 SIL 的关系（回归基线）

`SIL_project` 仍在，**未做任何修改**，且它跑的是同一份便携层代码。所以：

1. 先 `cmake --preset servo_hil_demo` 构建 SIL，确认便携层没被移植破坏；
2. 实板调试时任何控制参数改动，先在 SIL 里跑一遍看波形；
3. 后续做算法 A/B 时，SIL 是唯一能"同一输入喂两个算法"的地方。

**移植期间不要动 `SIL_project/bsp_api_virtual.c`**：它是实板 BSP 的对照实现，两边函数签名必须同步。新增 `bsp_api.h` 接口时，两份实现一起改。

---

## 8. 下一步（按顺序）

1. 在 SIL 上确认便携层完好（零硬件成本）。
2. 配 `BOARD=hpm6e00YZ` 编译本工程，修 SDK 头文件路径/命名差异（预计集中在 `hpm_adc_v2.h`、`gpio_set_pin_output_with_initial` 两处）。
3. 串口打通，跑 L0。
4. 做 L1 极性实验，**这是唯一能导致飞车的一步**。
5. L2 重标电流环，进入常规调试节奏。
