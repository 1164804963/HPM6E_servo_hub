# 交接说明（HANDOFF）

> 读者：接手本任务的 AI / 工程师。本文自包含，不需要上一轮对话。
> 架构与硬件映射在 [PORTING_HPM6E80.md](PORTING_HPM6E80.md)，本文是入口、现状和调试手册。

---

## 0. 一句话现状

`servo_hub` 已移植到 **HPM6EMotorV20**（HPM6E8YIGN1 + 12V 无刷电机 + MT6816）。
**工程能编译、能烧录、能上板跑，L0/L1/L2 已在实板验证通过**，电机在电流模式下被稳定控制
（1.0A 阶跃稳态误差 <3%）。速度环能闭环转起来，但电机在 65Hz 上来回荡（见第 6.1 节），
这是下一步唯一的功能缺口。

已验证的部分（实板，串口记录见第 4 节）：

| 级别 | 内容 | 结果 |
|---|---|---|
| L0 | ADC 三相零点、母线电压、零漂校准 | 通过（母线 12.0V，零点 32215/32550/32805） |
| L1 | 电压模式极性、电角度零点、相电流方向 | 通过（0°→+90° 转子转 +89.9°，偏置 221.6°） |
| L2 | d 轴电流阶跃 0.2 / 0.5 / 1.0A | 通过（1.0A 时实测 0.98~1.03A，上升 ~100us，无自激） |
| L3 | 速度环 | **未通过**：能转到 200~300rpm，但转子在 65Hz 上等幅来回荡 |

---

## 1. 目标与约束

### 1.1 这个工程要做什么

长期目标不是"跑通一台电机"，而是**电机驱动算法开发平台**：同一套硬件上开发、对比、回归各种驱动算法。
因此 `servo_hub` 的分层必须完整保留。

### 1.2 两条硬约束

| 约束 | 含义 | 违反后果 |
|---|---|---|
| **不改便携层** | `app/` `common/` `database/` `motor_control/` `simulink_code_gen/` `communication/` `board_public/bsp_api.h` 一行不改 | 架构被打散，SIL 与实板失去可比性 |
| **不手改生成代码** | `simulink_code_gen/` 是 Simulink 生成物 | 下次重新生成即丢失 |

允许改：`board_public/driver_parameter_*.h`、`board_public/motor_parameter_*.h`、
`embedded_project/HPM6E80/**`、`boards/hpm6e00YZ/**`、`boards/openocd/**`、`cmake/hpm-project.cmake`、
`.vscode/settings.json`、`tools/**`、`doc/**`。

改完**必须**跑边界检查（现在用 Windows PowerShell 也能跑了，脚本已加 BOM）：

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File tools/check_layer_boundary.ps1
```

---

## 2. 环境

工程根目录：`D:\Documents\SoftwareProject\YeeZi_HPM6E\MyProject\HPM6E_servo_hub_dsh`（工程整体搬过位置，
除 `build-hpm6e80/` 之外没有任何文件写死工程绝对路径；**搬家后必须删掉 `build-hpm6e80` 重新 configure**，
CMake/Ninja 的缓存里存的是旧的绝对路径）。

### 只想看固件代码时

用 VSCode 打开根目录下的 **`HPM6E80_Firmware.code-workspace`**：仿真、旧工程、上位机代码生成工具和
`build-hpm6e80/` 都从资源管理器里隐藏，只剩固件相关的 203 个文件（1.9 MB）。

| 属于固件（会被编译，或构建时必需） | 不属于固件 |
|---|---|
| `embedded_project/HPM6E80/`、`app/`、`common/`、`database/`、`motor_control/`、`simulink_code_gen/`、`board_public/`、`boards/hpm6e00YZ/`、`cmake/` | `SIL_project/`（SIL 虚拟 BSP）、`simulink_project/`（.slx 模型）、根 `CMakeLists.txt` + `CMakePresets.json`（SIL 构建入口） |
| `boards/openocd/`、`.vscode/`、`tools/` 顶层脚本（烧录/串口/边界检查） | `embedded_project/Y01/`（旧 STM32 工程）、`tools/database_generate/`、`tools/SSC Generate …/`（上位机代码生成工具） |
| — | `doc/`、`HANDOFF.md`、`README*`、`AGENTS.md`、`LICENSE`（文档） |

注：`communication/`（MAVLink/CiA402/CANopen/EtherCAT）和 `board_public/flash_db/`（FlashDB+FAL）
目前**只用了头文件、没有编译进固件**——既不是"已启用功能"，也不能删。

### VSCode 里编译 / 调试 / 下载

`.vscode/` 这一套是照 `HPM6E80共享SDK工程模板` 配的，插件也用的模板那三个：

| 动作 | 怎么做 |
|---|---|
| 装插件 | 打开工程时按提示装 `C/C++`、`CMake Tools`、`Cortex-Debug`（`.vscode/extensions.json` 已列） |
| 编译 | `Ctrl+Shift+B`（任务 `CMake: Build firmware` → 跑 `tools/build_hpm6e80.ps1`，configure+build 一步到位，产物 `build-hpm6e80/output/demo.elf`） |
| 调试/下载 | 选调试配置「HPM6E80 调试（当前CMake构建）」→ F5：cortex-debug 自己起 SDK 的 OpenOCD，烧进 Flash，停在 `main`；再按 F5 继续跑 |
| 断点/单步 | F9 / F10 / F11 正常用（`compile_commands.json` 已生成，128 个编译单元） |
| 烧录（不开调试） | 任务 `固件: 烧录（命令行）`，或命令行 `tools/flash_hpm6e80.ps1` |
| 看串口 | 任务 `固件: 串口状态`，或 `tools/serial_cmd.ps1 -Command "st"` |

几条必须知道的：

- **本机没装 PowerShell 7（`pwsh`）**。VSCode 的集成终端如果指向 pwsh 就会报
  「终端进程启动失败(退出代码: -1)」。本工程已做两件事兜住：
  ① `.vscode/settings.json` 把 `terminal.integrated.defaultProfile.windows` 钉到
  `C:\Windows\System32\WindowsPowerShell\v1.0\powershell.exe`；
  ② 所有任务改成 `type: process`（直接 spawn `powershell.exe`，压根不经过集成终端）。
  别的工程要是也报这个错，按这两条改。
- **F5 不会自动编译**，改了源码先 `Ctrl+Shift+B`。
- **F5 会 reset 板子**（`boards/openocd/boards/hpm6e00YZ.cfg` 的 `gdb-attach` 是 `reset halt`），
  所以调试前电机会先失能；跑起来之后要重新 `mode`/`en` 才会转。
- **不要同时手动起 OpenOCD**：cortex-debug 自己会起一个，同时开会抢 FTDI，报 "Unable to halt"。
- 改了 `.vscode/settings.json` 里的 `cmake.*` 要同步改 `tools/build_hpm6e80.ps1`（两处参数是一样的），
  因为构建任务走脚本、不走 CMake Tools 的状态。

| 项 | 值 | 说明 |
|---|---|---|
| HPM SDK | `D:/Documents/SoftwareProject/YeeZi_HPM6E/sdk_env_v1.13.0` | 已写进 `.vscode/settings.json` 的 `hpm.sdkEnvPath`，CMake 与烧录脚本都从这里读 |
| 工具链 | `rv32imac_zicsr_zifencei_multilib_b_ext-win` | 用 **rv32imafc + ilp32f**（硬件浮点），见第 5 节 |
| 板级包 | `boards/hpm6e00YZ` | `BOARD=hpm6e00YZ` |
| 构建 | `cmake -S embedded_project/HPM6E80 -B build-hpm6e80 -G Ninja -DBOARD=hpm6e00YZ -DHPM_BUILD_TYPE=flash_xip` | 产物 `build-hpm6e80/output/demo.elf` |
| 烧录 | `powershell -File tools/flash_hpm6e80.ps1` | FT2232 + HPM OpenOCD，已验证 |
| 串口 | **COM4**，921600 8N1 | SDK 控制台 UART0 |
| 调试台 | `powershell -File tools/serial_cmd.ps1 -Command "st"` | 不依赖 ComAssistant，直接开串口 |

> 本机没有 `pwsh`（PowerShell 7），只有 Windows PowerShell 5.1。
> 所有 `.ps1` 必须是 **UTF-8 with BOM**，否则中文注释会让 5.1 解析失败。

### 官方 servo_hub 上位机（MAVLink）怎么用

上位机走 MAVLink，跟调试台**共用 UART0（COM4，921600 8N1）**：首字节 `0xFD/0xFE` 的帧归上位机，
其余字节归调试台，由 `Board/servo_host.c` 分流。上位机打开 COM4 就能用，不用改接线。

上位机的操作顺序（已经实板验证）：

| 步 | 上位机动作 | 报文 | 说明 |
|---|---|---|---|
| 1 | 连串口 | — | COM4 / 921600 / 8N1 |
| 2 | 轮询读参数 | `ReadParam(30000)`，`struct_id` 填要读的消息号 | 设备回一条同 ID 的完整结构体 |
| 3 | 取控制权 | `AppPermissionConfig(30068)`：`Comm=0(HOST)`、`Internal=0(APP)` | 不取权则所有参数写入返回只读 |
| 4 | 选运行模式 | `AppOpMode(30056)`：`1`=PP `3`=PV `4`=PT `10`=CST 等 CiA402 模式号 | 切换模式会复位控制字 |
| 5 | 使能 | `AppControlWord(30054)`：`Controlword=1` | 应用层把 `motor_enable` 下发给控制层 |
| 6 | 给指令 | `AppMotionParam(30059)` 里的 `Target_velocity`（偏移 44，float，rpm）等 | 只写关心的字段，其余按读回值原样写回 |
| 7 | 失能 | `AppControlWord(30054)`：`Controlword=0` | |

没有上位机时，可以用 `tools/mavlink_probe.ps1` 把上面整套流程手工走一遍（已经用它验证过）：

```powershell
powershell -File tools/mavlink_probe.ps1 -SetHost                  # 取控制权
powershell -File tools/mavlink_probe.ps1 -MsgId 30056 -PayloadHex "03" -CrcExtra 26   # PV 模式
powershell -File tools/mavlink_probe.ps1 -Enable                   # 使能
powershell -File tools/mavlink_probe.ps1 -SetVelocity 300          # 300rpm
powershell -File tools/mavlink_probe.ps1 -ReadParam 30055          # 读 AppStatusInfo
powershell -File tools/mavlink_probe.ps1 -Disable                  # 失能
```

实测记录（证明链路通）：

```
TX ReadParam(30077)          -> RX msgid=30077 len=1  payload=[EA]      # HeartBit=Sys_init_flag
TX AppPermissionConfig(0,0)  -> RX msgid=30068 payload=[00]             # 回显 HOST/APP
TX AppControlWord(1)         -> RX msgid=30054 payload=[01]
之后调试台 st: state sm=1 mode=3 pwm=1 hw_ready=1   （PWM 放开、电流环在跑）
TX AppControlWord(0)          -> 同一行变回 sm=0 pwm=0
```

排查"上位机使能不了"时的两个读法（板上串口调试台不打印应用层状态，因为板级不能引应用层头文件）：

```powershell
powershell -File tools/mavlink_probe.ps1 -ReadParam 30068   # 控制权：回 00 00 = HOST/APP
powershell -File tools/mavlink_probe.ps1 -ReadParam 30055   # AppStatusInfo，偏移 4 是 Error_word
```

`Error_word` 的位定义在 `app/app_status_check.h` 的 `CheckErrorCode_t`；只要非 0，应用层就会
每 1ms 下发一次失能——上面第 1、2 条缺口当初就是靠这个位（bit10 flash、bit18 马达欠温）查出来的。

为了让上位机能真正使能电机，适配时补了三处**板级**缺口（都在 `Board/`，没动便携层）：

1. **存储**：`bsp_flashdb_*` 原来是返回错误。应用层错误表里有 `AppFlashStoreErrorCheck`，
   一报错就每 1ms 下发失能，上位机永远使能不了。现在 `bsp_api.c` 里改成**内存版**存储
   （注册的缓冲区就是存储，read/write 空操作）——参数掉电丢，接真 FlashDB 见第 6.2 节。
2. **温度**：`motor_temp` 原来是 -50℃（ADC 没采），命中 `AppTooLowTemperatureMotorErrorCheck`，
   同样会一直失能。现在固定返回 25℃，**过温保护因此是失效的**。
   顺带查清：`PF08` 在 HPM6E80 上只有数字复用，**没有 ADC 通道**，所以原理图标的 NTC1 不是这个脚，
   真实 NTC 引脚待查。
3. **控制权**：`main.c` 上电默认 `INTERNAL_CONTROL_CTRL`（控制字归控制层，串口 `en` 能用）。
   上位机取权后自动变 APP，由应用层接管使能和模式；**这时不要再用串口 `en`/`mode` 去改**，
   两边会打架。复位后权限回到 BUS/CTRL，上位机要重新取权。

---

## 3. 硬件事实（改代码前对照）

| 功能 | 引脚 | 代码 |
|---|---|---|
| 六路 PWM | PD00..PD05 → IN_UH/UL/VH/VL/WH/WL | `BOARD_PWM0` ch0..ch5 |
| PWM→ADC 触发 | PWM0 TRGO_0 → TRGM0 → ADC PTRGI0A | `board_init_trigger_mux()` |
| 相电流 U/V/W | PF28/PF29/PF30 | ADC2.CH5 / ADC3.CH4 / ADC2.CH6 |
| 母线电压 | PF31，R140/R179 = 21:1 | ADC3.CH7 |
| 温度 | PF8 MCP9700 | **还没进 ADC 队列**，`adc_temp_raw` 恒 0，所以 `motor_temp` 打印 -50℃ 属正常 |
| 编码器 | SPI7 PD20..PD23 | `encoder_mt6816.c`，14bit=16384 P/R |
| LED | LED_G=PB24，LED_R=PB25 | `bsp_led_write()` |

### 实测校准值（已经写进参数头，不要重算）

```
电流零点    : U=32211  V=32539  W=32814   （理论 32768，偏差 -0.28/-0.11/+0.02 A）
电流换算    : K = 5.0354e-4 A/count
母线        : 12.0V 时 ADC ≈ 11450 counts，K = 1.0574e-3 V/count（误差 <1%，不需要修 bias）
相电流方向  : UVW_CURRENT_DIRECTION = -1   （L1 实测，填 +1 会让电流环变成正反馈）
电角度零点  : PMSM_ELEC_ANGLE_BIAS_DEG = 221.6  （L1 实测，填错 180° 会让速度环正反馈）
```

---

## 4. 上板怎么用（已实测的命令序列）

串口工具：`powershell -NoProfile -File tools/serial_cmd.ps1 -Command "st"`

```
st            打印状态（ADC/电流/母线/编码器/状态机/环耗时/偏置）
cal           打印零漂结果与当前三相电流（零点在上电自检里做）
mode <n>      1=力矩 2=速度 3=位置 127=电压 -4=电角度辨识 -3=方向辨识 -2=极对数辨识
en / dis      走控制层状态机使能 / 失能（自动处理 0->1 上升沿）
clr           清错误
id <A>        d 轴电流（转子不动，做电流环阶跃）
iq <A>        q 轴电流
spd <rpm>     速度目标
pos <deg>     位置目标（相对当前角度）
vec <V> <deg> 电压模式给矢量（L1 用，|V| ≤ 6V）
uvw <a> <b> <c>  电压模式直接给三相电压
scope <n> [A] 抓 20kHz idq 波形，可选带一个 d 轴阶跃，相当于简易示波器
enc           200ms 编码器实测（位移、折算转速、跳变次数）
step <n>      连续打印 n 次 idq（每 2ms）
tm / tick     环耗时 / 20kHz 节拍实际频率
hb            每秒一行心跳（主循环里打印，用来判断中断和主循环是否都活着）
```

### 已验证的 L2 记录（可直接复现）

```
mode 1 → en → scope 40 0.5
scope: 40 pts @20kHz
#  t_us  id_mA  iq_mA  ref_mA
    0     ...       ...     500
  100    470      ...
 1950    304     101     500
```
稳态 id ≈ 0.47~0.59A（目标 0.5），iq ≈ ±0.05A，输出相电压 ±0.9V。
电流环耗时 5.5~7us（50us 预算的 12%）。

### L1 记录

```
mode 127 → en → vec 1 0   → 转子停在 elec=3.868rad（编码器 10087）
vec 1 90                  → 编码器 10087→14176 = +89.9°，方向一致
```
结论：相序、电压极性、编码器方向都一致，只需一个零点偏置。

---

## 5. 本次修掉的问题（按重要性）

### 构建

1. `CMakeLists.txt` 的 `include` 路径 `../../../cmake/hpm-project.cmake` 多了一级（跑到桌面去了）→ 改 `../../`。
2. `include(...)`/`find_package` 必须在 `project()` 之前，否则 CMake 找不到编译器。
3. `sdk_inc(../../../app)` 等路径同样错一级，便携层一个头文件都找不到 → 改成基于 `SERVO_ROOT` 的绝对路径。
4. 缺 `version.h`（便携层 `data_param.h` 要）→ 新增 `Board/version.h`，默认 `V_CONSOLE`（无总线协议）。
5. `hpm_math.h`：SDK 的 hpm_math 中间件只做 Andes DSP 版本，CMake 里硬性要求 nds 工具链 →
   新增 `Board/hpm_math.h` + `Board/servo_math_port.c` 两个小文件顶替，并加 `-lm`。
6. `hpm_adc_v2.h` 找不到 → `set(CONFIG_HPM_ADC_V2 1)`，且必须在 `find_package` 之前。
7. `IOC_PAD_FUNC_CTL_GPIO_MASK` 不存在 → `IOC_PAD_FUNC_CTL_ALT_SELECT_SET(0)`。

### 最坑的一个：PWM 引脚从来没被复用成 PWM

8. **`board_init_pwm()` 里漏了引脚复用**。SDK 板级包的 `board_init()` 只配了时钟/控制台/PMP，
   六路 PWM 的引脚复用（PD00..PD05 → PWM0_P_0..5）是官方例程在自己的 `pwm_init()` 里调的。
   我们照抄板级包时漏了这一步，现象极其迷惑：

   - 状态机说 `pwm=1`、影子比较值写对了、计数器在跑、输出没有被强制；
   - 但三相电流恒为 0，用万用表量 U/V/W 对地都是 0V；
   - **而且前几次上板电机还能转**——因为 IOC 的引脚配置不在内核复位范围内，
     板上残留的是上一版（厂商）固件留下的 PWM 复用状态，一断电就没了。

   修复：`board_init_servo()` 里先调 `init_pwm_pins(BOARD_BLDCPWM)`。
   教训：换了固件之后**一定要断电冷启动一次**再判断硬件好坏，否则会被残留的 IOC 状态骗。

### 实时性

9. **必须开硬件浮点**：默认 `rv32imac` 软浮点下，20kHz 电流环 26us、1kHz 位置环 75us，
   中断吃掉 60% 以上 CPU，串口调试台只剩 ~150B/s，还会丢 ADC 触发。
   改成 `RV_ARCH=rv32imafc` + `RV_ABI=ilp32f`（与 SDK `bldc_foc` 例程一致）后电流环降到 5.5~7us。

### 控制

10. **电流环 ki 的写法错了**：生成代码里的积分器是 `ki*err*dt_s`（连续域），
    原来按离散域算的 `0.1781` 会让积分慢 20000 倍，表现为只有比例项、电流停在 0.1A 上不去。
    正确值 `ki = R*wc = 1.89Ω*1885 = 3562`。
11. **相电流方向反了**：L1 实测 `vec 1V@0°` 时 u=+1.0/V，但读到的 U 相电流是负的。
    `UVW_CURRENT_DIRECTION` 改成 `-1`，否则电流环是正反馈，一使能就过流。
12. **零漂必须在"桥臂放开、相电压 0"的条件下采**：运放零点随共模电压变化，
    桥臂封锁时测的零点比运行时偏 0.1~0.2A，三相之和不为零，电流环会把它当真误差。
    现在上电自检里先把比较值设成 50%、放开桥臂、再采 1024 次，然后立刻封锁。
    零点上限也从 0.2A 放宽到 0.5A（实测偏差 -0.28/-0.11/+0.02A 属正常）。
13. **速度观测器带宽**：`SPEED_OBS_PLL_WN_HZ` 原来照抄 1200Hz，1kHz 采样下超过稳定极限，
    估出上千 rpm 直接报过速。改成 100Hz（1kHz 环下稳定边界约 160Hz）。
14. **电流环积分在电压模式/失能期间会顶到限幅**：生成代码的 PI 一直在算，只有最后一级才切输出。
    带着这个积分进电流模式，使能瞬间就输出几伏。现在桥臂放开的第一拍调 `current_ctl_loop_task_Init()` 清零。
    速度观测器的状态也在同一拍复位（`speed_obs_pll_Init` + 补 `pos_now_p_last`），
    PLL 每拍最多表示 1.0rad/T（1ms 约 9550rpm），高速被饱和过之后会卡在极限环里。
15. **电角度零点**：`PMSM_ELEC_ANGLE_BIAS_DEG = 221.6`（L1 实测），boot 时由 `servo_bringup_self_test()` 填进
    `motor_pos_sensor_config.elec_angle_bias_rad`。填错 180° 时电流环仍然"稳"（dq 一起反），
    但 q 轴出力方向反过来，速度环会变成正反馈。
16. **转动惯量实测**：`PMSM_J` 从 0.075 改成 3.0e-6（kg·m²）。实测方法：0.2A 转矩阶跃看加速度，
    `J = kt*I/(dω/dt)`；0.2A 下 0→7000rpm 约 1.25s，和 3e-6 对得上。
    速度环增益也按这个惯量重算：`kp_s=0.102`、`ki_s=7.67`（wn=150rad/s，阻尼 1）。
    并在 bringup 里打开 `pos_speed_ctl_config.dynamic_integration_enable = 1`（抗积分饱和）。

### 保护与调试

15. **中断里不能 printf**：newlib 的 stdout 带锁，1ms 中断打印时正好打断主循环的 printf 会死等同一把锁，
    现象是串口卡死、板子"假死"。零漂结果改成查询接口，心跳改到主循环打印。
16. 新增 **20kHz 逐周期过流兜底**（`board_check_over_current`）：控制层的过流保护在 1kHz 才查一次，
    电流环异常时 1ms 足够把电流推到几安培。超限立刻封锁桥臂并置 `ERROR_BUS_CURRENT_OC`。
17. `bsp_set_phase_voltage` 加 NaN 保护：NaN 与任何数比较都为假，限幅拦不住，
    `(uint32_t)NaN` 还是未定义行为。
18. `sys_timer_init()` 原来没人调用（`HalInit` 没被编译进来），导致 `bsp_sys_blocking_delay_*` 立即返回、
    环耗时恒 0。现在 `board_init_servo()` 里第一件事就调它。
19. **编码器采样从 20kHz 改到 1kHz，并加 3 点中值滤波**：控制层用到的电角度/位置本来就是 1kHz 更新的，
    20kHz 读 SPI 只是白占 ISR 时间（9us/50us），还更容易把开关瞬间的噪声采进位置。
    改完电流环耗时 5.5us → 3.3us。滤波见 `drv_encoder.c`，`enc` 命令会打印 SPI 失败帧数。
20. `tools/check_layer_boundary.ps1`、`tools/flash_hpm6e80.ps1`、`tools/serial_cmd.ps1`
    都改成 UTF-8 with BOM，Windows PowerShell 5.1 才能解析中文。

---

## 6. 已知未解决

### 6.1 速度环（L3）——唯一的硬缺口

实测（`mode 2` + `en` + `spd 300`）：

- 电机转起来并且在 200~300rpm 之间，但 **200ms 内编码器方向反转 20 次**，
  `escope` 看到的是一段干净的正弦：周期约 15ms（**65Hz**）、幅度约 ±900 count（±20° 机械角）。
- 同期的 `iq` 波形（20kHz `scope`）是**平稳的 0.6~0.7A，没有 65Hz 分量**。
- 把速度环 `KP_S` 从 0.219 降到 0.102、再降到 0.02（5 倍），振荡**幅度和频率都不变**。
- 反过来，**力矩模式（开环速度）完全没有这个振荡**：0.2A 转矩阶跃，编码器 delta 均匀
  （+1878/+1888/+1899 count per ms），`reversals=0`，PLL 读数 7091rpm vs 实测 6977rpm，很准。

结论：振荡是**转子真的在 65Hz 上来回摆**，而且不是速度环增益问题（增益无关），
最可能是**电角度被干扰**导致转矩脉动，也可能是转子-安装座的机械共振。

按可能性：

1. **编码器/电角度受定子磁场干扰**（首要）。转速低、电流大时干扰最明显：
   速度环 0.7A 时角度抖 ±20°，力矩模式 0.2A 时角度很干净。MT6816 是磁编码器、贴装在电机轴上，
   定子电流产生的磁场会直接叠加到它读到的磁场上。这类误差是**随转子位置周期性变化**的，
   典型做法是做位置相关的角度补偿表（上电自标定：慢速正反转一圈，记录角度误差曲线）。
   软件侧已经做的：采样降到 1kHz、3 点中值滤波，都压不住（因为不是随机噪声，是真实的角度偏差）。
2. **机械共振**：65Hz 且与电流幅值相关，也可能是转子+联轴器的扭转共振被转矩脉动激起。
   可以把电机空载悬空/夹紧分别试一次来区分。
3. 速度环结构本身没问题：`PMSM_J` 已按实测改成 3e-6，`KP_S/KI_S` 按 wn=150rad/s 阻尼 1 重算，
   并打开了 `dynamic_integration_enable` 抗积分饱和。这些改动是必要的（原来的 J 差 4 个数量级），
   但不是这次振荡的主因。

调试建议顺序：
1. 先分离"角度干扰"和"机械共振"：断开电机三相、用手匀速转轴，看 `escope` 的 delta 是否均匀
   （此时没有电流，只有机械）。再在力矩模式下给不同电流（0.1 / 0.3 / 0.5A）看角度误差是否随电流变大。
2. 如果确认是磁场干扰：做电角度误差标定表（`app/Identify/app_id_elec_angle_mode.c` 那套流程
   本来就有电角度辨识，可以扩展成整圈补偿表），或在硬件上给编码器加磁屏蔽/加大气隙。
3. 如果是机械共振：加陷波滤波器（`notch_filter_config` 已经接在主链路上，填 65Hz 试）。

#### 已经排除的可能（2026-11-07 实测，别再重复）

| 假设 | 实验 | 结果 |
|---|---|---|
| 编码器被电磁干扰 | 力矩模式开环 iq=0.3A 阶跃，`escope` 40 帧 | delta 稳定 2200~2350（±3%），**没有跳变** |
| 转子-安装座机械共振 | 同上（力矩阶跃就是一次冲激激励） | **没有 65Hz 振铃**，delta 单调 |
| 速度环增益太高 | kp_s 0.102→0.01、ki_s 7.67→0.77（各降 10 倍） | `max_step` 734→645，几乎不变 |
| 积分器/抗饱和/前馈 | ki_s=0、`dynamic_integration_enable=0`、`vff=0` 各试一次 | 700~820，全部无改善 |
| PLL/观测器带宽 | wn 20 / 100 / 150 / 300 Hz | 20→2882、150→2982（都更差）、300→过速跳闸 err=3，**100 最好** |

结论：**振荡只在速度环闭合时出现，开环力矩下转子完全平稳**；且对环路参数几乎不敏感，
只有 PLL 带宽能改变它（往两边调都更差）。所以是**带延迟的闭环极限环**，
延迟主要来自 PLL（wn=100Hz 时群延迟约 2ms）+ 1kHz 采样，而不是机械或编码器。

下一步该做的（定量而不是试凑）：用**参考信号模式**（`AppOpMode/控制层 mode=5` + `ReferenceSignalConfig`）
注入不同频率的小幅速度正弦，测闭环幅频/相频，找出穿越频率和 -180° 频率，
再决定是降带宽、改 PLL 结构（比如用位置差分 + 低通替代 PLL），还是加陷波。

### 6.1.1 上位机「运动控制」逐模式实测记录（2026-11-07）

用上位机加直连报文两种方式跑的，判据是控制台 `st`/`enc` 的真实读数：

| 运行模式 | 参数 | 实测 | 结论 |
|---|---|---|---|
| 空模式 | 使能 | `sm=1 pwm=1`，iabc≈0，不转 | 正常（空模式本来就无出力） |
| 力矩模式 | `idq_tar q=0.3A` | **6917 rpm，200ms 内 0 次反向**，编码器 delta 均匀 | **正常** |
| 速度模式 | 目标 300 rpm | **291.7 rpm**（均值跟得上），但 `max_step=1028`、**200ms 反向 19 次**（±20°/65Hz） | 能跟速，叠加振荡（见 6.1） |
| 位置模式 | 目标 = 当前位置 +800 count | 使能即 **err=6（位置跟随误差过大）**，PWM 都不放开 | **不可用** |

位置模式那条的关键数字：`MotorCtlSmConfig.position_following_error_protection` 默认 **1638 count
（0.1 圈）**。根因已经查清（新增控制台命令 `pl` 可以直接看）：

- `pos_ctl_error_p = pos_tar_p - pos_now_p + position_offset_p`（`pos_speed_ctl_pip.c:84`），
  `protect_check` 在 `pos_ctl_error > 1638` 且 `error_enable` 的 bit5 打开时返回 err=6；
- `error_enable` 上电是 `0x0000`（控制层保护全关），**切到 `INTERNAL_CONTROL_CTRL` 后变成 `0xFFFF`**；
- 实测 `pos_tar=16702 / pos_now=14703 / pos_ctl_error=-1686 / limit=1638` —— 我直接写 `pos_tar`
  做 2000 count 阶跃，误差 1686 超阈值，保护按设计动作，**不是 bug**；
- 走应用层（`AppOpMode=3` 轮廓位置 + `AppMotionParam.Target_position`）时 `pos_tar` 由轨迹规划
  生成，误差稳定在 1000~1550，不会跳保护，电机能朝目标走；
- 坑：**使能瞬间 `pos_tar` 会被重写成当前 `pos_now`**，所以"先给目标再使能"等于没给。

测试时的两个操作要点（不知道就会白测）：

1. **必须先选「控制模式」**（上位机那个"轮廓力矩/速度/位置/MIT/回零"下拉框 → `AppOpMode`），
   否则点使能会弹「请先设置控制模式」的模态框，整个界面卡住、报文也不发。
2. **目标要在使能之后再下发**：PWM 上升沿会调 `current_ctl_loop_task_Init()`，把 `idq_tar` 等清零。
   先给目标再使能，等于白给。

### 6.1.2 上位机软件自身的问题（不是固件）

- **两种"看着像断线"的状态要分清**（日志 `log\app_*.log` 是唯一可靠判据）：

  | 状态 | 界面 | 日志 | 实际 |
  |---|---|---|---|
  | ① GUI 线程被卡住 | 绿灯「已连接」不变，曲线数据定格 | **一段时间没有任何 `发送数据` 行**，也没有 disconnect | 链路还在，是上位机自己不动了（模态框、脚本在 GUI 线程跑重活都会这样） |
  | ② 真断开 | 标签变「未连接」，并弹「设备COMx已断开连接！」 | `send_data error: Write timeout` → `disconnect COMx` | 端口句柄废了，必须重连 |

  ①只需关掉弹窗/重连；②必须重连。别把①当成硬件掉线。
  已核实的日志实例：`app_20261106-233958.log` L170、`app_20261106-235038.log` L103、
  `app_20261106-235730.log` L109，且每次 Write timeout 之前都有一分半以上的"零发送"空档。
- 三个串口 COM4/COM5/COM7 列在一起，**本板只接 COM4**（COM7 是空口）。三条「连接」按钮文字完全一样、
  没有 objectName，用脚本按文字点很容易点到别的行（我第一次就点到了 COM7，弹「设备COM7已断开连接」）。
  要按行点就先找到文本是 `COM4` 的 `QLabel`，再点它父控件里的那个 `QPushButton`。
- **上位机会"假死"：界面还显示「已连接」，但数据定格、发出去的报文不到设备**。
  实测原因不是 JTAG 干扰——专门做过对照：一边开着 COM4，一边跑 OpenOCD（正常 `shutdown` 和
  `Stop-Process` 强杀各试一次），同一个串口句柄前后都能正常收发（RX 89/90 字节一致）。
  真正的诱因是**上位机自己的 GUI 线程被卡住**：弹「请先设置控制模式」这类模态框、
  或者脚本在 GUI 线程里跑重活，都会让它的轮询和串口线程一起停摆，日志里表现为
  `send_data error: Write timeout` → `disconnect COM4`。
  所以看到"发了没反应"，先看日志有没有 Write timeout / 有没有模态框，再怀疑调试器。

### 6.2 其它（有意留空，不阻塞）

| 项 | 现状 |
|---|---|
| FlashDB 参数存储 | `bsp_flashdb_*` 全返回错误；电角度偏置、惯量先写死在参数头 |
| 温度采样 | PF8 没进 ADC 队列，`motor_temp` 恒 -50℃ |
| MOS/MCU 温度 | 返回 0℃ |
| CAN / EtherCAT / MAVLink | 只有 get/set 变量 |
| 抱闸 / 固件升级 / 数字 IO | 空实现 |
| 位置环 | 位置模式代码路径没在实板上跑过（L2 之后没继续） |

### 6.3 硬件层面注意

- **IOC 的引脚配置不吃内核复位**。上一版固件（比如厂商固件）配好的引脚复用会一直留着，
  直到真正断电。所以**换固件之后一定要冷启动一次再判断硬件**，否则会被残留状态骗
  （这次就是靠这个"骗"过了一整个下午，电机能转，其实新固件根本没配 PWM 引脚）。
- **不要在电机转着的时候烧录/复位**。反电动势会通过关断的桥臂打到门驱上，
  实测出现过门驱锁存、之后必须断 12V 才能恢复。`tools/flash_hpm6e80.ps1` 现在会在烧录前
  自动通过串口下发 `dis`，就是为了这个。
- **板子的 nSRST 没有接到调试器**（实测：拉低 nSRST 时 IDCODE 不变），所以 OpenOCD 的
  `reset` 命令对这块板子无效。
- 如果内核卡死（现象：JTAG 能读到 IDCODE 但 halt 失败，`dmstatus` 一直 allrunning、串口全无输出），
  用 **DM 的 ndmreset** 恢复（已验证有效，`flash_hpm6e80.ps1` 里也内置了自动重试）：

  ```powershell
  # tools/openocd_dmi.cfg + tools/openocd_dmi_reset.tcl：直接写 dmcontrol 触发整芯片复位
  & "$sdk\tools\openocd\openocd.exe" -f tools/openocd_dmi.cfg -f tools/openocd_dmi_reset.tcl
  ```
  正常情况下不需要断电重启。
- **任何时刻只允许一个进程占用 FTDI**。后台挂着 OpenOCD 服务时再跑一次性的 openocd 命令，
  症状就是 "Unable to halt / Examination failed"，别误判成板子坏了——先把后台进程杀干净。

---

## 7. 工具清单（`tools/`）

| 文件 | 用途 |
|---|---|
| `flash_hpm6e80.ps1` | 烧录（先自动 `dis` 封锁桥臂、halt 失败自动做 DMI 复位重试）+ 校验 + 复位 |
| `serial_cmd.ps1` | 发一行命令、收到静默为止，输出到 stdout（不依赖 ComAssistant） |
| `check_layer_boundary.ps1` | 分层边界检查 |
| `openocd_dmi.cfg` + `openocd_dmi_reset.tcl` | 内核卡死时用 DMI ndmreset 恢复 |
| `openocd_srst_probe.cfg` | 探测 nSRST 是否接线的实验配置（结论：没接） |

调试 OpenOCD 交互会话时可临时起服务：

```powershell
& "$sdk\tools\openocd\openocd.exe" -s "$sdk\hpm_sdk\boards\openocd" `
  -f "$sdk\hpm_sdk\boards\openocd\probes\ft2232.cfg" `
  -f "$sdk\hpm_sdk\boards\openocd\soc\hpm6e80-single-core.cfg" `
  -f boards\openocd\boards\hpm6e00YZ.cfg
# 然后 gdb: riscv32-unknown-elf-gdb -ex "target remote :3333"
```

`boards/openocd/boards/hpm6e00YZ.cfg` 里的 `gdb-attach` 已从 `reset halt` 改成 `halt`
（调电机不能一接调试器就复位，否则桥臂状态和实时变量全丢）。

---

## 8. 下一步

1. **分离并解决速度环的 65Hz 振荡**（第 6.1 节）。先做"断电手动转轴 / 不同电流下看角度误差"两步实验，
   确定是电角度被磁场干扰还是机械共振，再决定做角度补偿表还是陷波滤波器。
2. 位置环（L4）：`mode 3` + `pos <deg>`，看梯形轨迹跟随；顺便验证使能瞬间无冲击电流。
3. 保护（L5）：欠压/过压/过流/编码器断线逐项跳闸并恢复。
4. 补 `alg_custom/`（Iq 二次谐波前馈）。
5. EtherCAT：HPM 内置 ESC 替 LAN9252，SSC 应用层不动。
6. 参数存储：把电角度偏置、PID、保护阈值搬进 FlashDB，`PMSM_ELEC_ANGLE_BIAS_DEG` / `PMSM_J` 就可以删掉。

### 这次验证出来的"好数据"（后面调参直接用）

```
母线 12.0V；三相电流零点 32215/32550/32805；K = 5.0354e-4 A/count
相电阻（含驱动）1.77Ω：1.0A 时 d 轴电压 ≈ 1.6V
转矩常数 kt = 8.775 mN*m/A，极对数 1，编码器 16384 P/R
转动惯量 J ≈ 3e-6 kg*m^2（0.2A 转矩阶跃 0→7000rpm 约 1.25s）
最高转速 ≈ 9900rpm（12V 反电动势限制）
电流环耗时 3~5us / 50us；位置环 80~100us / 1000us
```

---

## 9. 工作约定

1. 每次改动后跑 `tools/check_layer_boundary.ps1`。
2. 便携层的任何修改都视为"越界"，需要单独一轮并说明理由。
3. 新增 `bsp_api.h` 接口时，`SIL_project/bsp_api_virtual.c` 必须同步实现。
4. 注释用中文；新增文件用 UTF-8 无 BOM，`.ps1` 用 UTF-8 **有** BOM。
5. 中断里不要 printf。
6. 每次上板测试留串口记录，不要凭"能转"下结论。
