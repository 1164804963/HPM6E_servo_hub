# HPM6E80 移植补丁与适配配置说明

本工程在 `servo_hub-master`（上游通用工程）基础上做了 **MCU 更换 + 电机/驱动板重新适配**。
为了让"原工程代码尽量不动、且换 MCU/换板子仍然通用"，所有对**通用层**
（`motor_control/` `app/` `database/`）的改动都做成了**可开关的移植补丁**：

```c
#if defined(PORT_PATCH_xxx) && (PORT_PATCH_xxx)
    /* 本板需要的修法 */
#else
    /* 原工程逻辑，一字不改 */
#endif
```

开关集中定义在**板级参数头**里：`board_public/driver_parameter_hw_hpm6emotorv20.h`。
其它平台（Y01、未来的新板）不定义这些宏，编译结果与上游**完全一致**。

---

## 一、适配配置（不是补丁，是这块板/这台电机的参数）

| 文件 | 项 | 值 | 说明 |
|---|---|---|---|
| `driver_parameter_hw_hpm6emotorv20.h` | `DRIVER_RATED_CURRENT_A` | 1.20 A | 过载积分基准，跟电机额定走（EC1636-12120：效率点 0.45 A / 最大功率点 1.52 A） |
| 同上 | `DRIVER_PEAK_CURRENT_A` | 3.00 A | 峰值保护阈值 = 0.9×3.0 = 2.7 A（板子实测可到 2.5~3 A） |
| 同上 | `DRIVER_OVERCURRENT_LIMIT_A` | 3.00 A | 20 kHz 板级逐周期过流 + App 单相过流阈值，必须 ≥ 0.9×峰值 |
| `motor_parameter_hpm6emotorv20_bldc12v.h` | `GEAR_RATIO_NUM / GEAR_RATIO` | 107 / 107.0 | 电机轴经 107:1 减速器输出；负载端位置 = 电机端位置 ÷ 107 |

> 注意：减速比、驱动器过流阈值这类参数**会被 FlashDB 覆盖**（`app_store_param.c` 启动时
> 从 flash 恢复），所以改宏之后要么"恢复出厂设置"，要么在上位机里改好并保存。
> 上位机"保护参数 → 驱动器过流阈值"存的是 2.0 A 时，会把固件默认的 3.0 A 覆盖回去。

---

## 二、移植补丁清单

### 补丁 1 · 桥臂被关掉后每周期重试开波

- **开关**：`PORT_PATCH_PWM_KEEPALIVE`
- **位置**：`motor_control/motor_ctl_loop.c` → `PosSpeedLoopCtrl()`
- **现象**：点"开始辨识"后电机抖一下就停，`hw_ready_state` 恒 0，`DirectionIdOutput.state_now`
  永远 0，上位机一直"辨识中"，且 `Error_word = 0`（没有任何报警）。
- **根因**：原逻辑只在 `state_last == DISABLE` 的那一个 1 ms 周期请求一次开波。
  本板新增了两个"中途会把桥臂关掉"的来源（零漂门禁、20 kHz 板级过流），
  关掉之后 `state_last` 恒为 ENABLE，再也不会重试 → `ModeRun()` 永不执行。
- **修法**：ENABLE 态下每周期 `if (!bsp_get_pwm_state()) bsp_set_pwm_state(PWM_ENABLE);`（幂等）。
  正常路径（桥臂已开）**不改变任何行为**。
- **何时可删**：上游把开波改成"请求 + 状态保持"模型之后。

### 补丁 2 · 零漂标定与开波的互锁

- **开关**：`PORT_PATCH_CAL_AUTOSTART`
- **位置**：`motor_control/motor_ctl_loop.c`（`cal != OK` 分支）、`embedded_project/HPM6E80/Board/bsp_api.c`
- **现象**：上电自检的零漂标定一旦失败，之后永远开不了波（串口只有一行
  `bringup: current calibration FAILED`，上位机看不到）。
- **根因**：`bsp_set_pwm_state(true)` 要求"校准 OK"才允许放开桥臂，而
  `sys_current_calibration_step()` 又要求"桥臂已放开"才采样 → 互锁。
  上游的 `CurrentCalibrationStep()` 是自己开波再采样的，移植时把这段换掉了。
- **修法**：`bsp_api.c` 去掉开波门禁；`motor_ctl_loop.c` 在 `cal != OK` 时先按 0V 开波再调标定。
- **何时可删**：零漂标定改成"开机一次性、失败重试"的独立状态机之后。

### 补丁 3 · 板级 20 kHz 过流对 App 可见

- **开关**：`PORT_PATCH_FAST_OC_VISIBLE`
- **位置**：`app/app_status_check.c` → `AppDriverOverCurrentErrorCheck()`
- **现象**：过流时桥臂被静默封锁，上位机没有任何错误码。
- **根因**：`board.c::board_check_over_current()` 只置了 bsp 层 `error_bus_current_oc`，
  该标志不在 App 的 `CheckTable` 里。
- **修法**：把该标志并入"软件过流保护"错误位（bit14）。
- **何时可删**：板级错误统一接入 App 错误表之后。

### 补丁 4 · 清错命令不被 1 ms 扫描冲掉

- **开关**：`PORT_PATCH_CLEAR_ERROR_FIX`
- **位置**：`app/app_status_check.c` → `AppStatusScanFast()` / `AppStatusScanSlow()`
- **现象**：一旦报错，上位机点"清除错误"也清不掉，只能断电重启。
- **根因**：`if (error.all != 0) set_app_Controlword(APP_CTRL_DISABLE);` 每 1 ms 执行，
  会把上位机刚发的"清除错误(3)"在同一个周期里冲回 0，清错条件（0→3 上升沿）永远不成立。
  实测：写 3 之后只维持约 12 ms。**这是上游也存在的逻辑缺陷**，只是上游很少被踩到。
- **修法**：控制字当前是 `APP_CTRL_CLEAR_ERROR` 时不回写。
- **何时可删**：上游修掉这个问题之后（建议反馈给原工程）。

### 补丁 5 · 辨识模式允许重复下发

- **开关**：`PORT_PATCH_ID_MODE_RESEND`
- **位置**：`database/data_param.c` → `set_app_Modes_of_operation()`
- **现象**：不点"停止辨识"就再也点不动"开始辨识"。
- **根因**：模式值没变就 `return`，辨识 APP 不会重新 Init。
- **修法**：负值（辨识模式）允许重复下发。
- **何时可删**：上位机改成"开始辨识前先复位模式"之后。

---

### 补丁 6 · 极对数辨识电流取配置值

- **开关**：`PORT_PATCH_ID_CURRENT_FROM_CONFIG`
- **位置**：`motor_control/motor_ctl_sm.c` → `PolePairsIdStep()`
- **现象**：极对数辨识约 7 s 后触发过载保护。
- **根因**：辨识电流写死为 √2×额定（1.697 A），超过驱动额定 1.5 A。
- **修法**：改用 `pole_pairs_id_config.id_tar_max_A`（上位机配置值，1.2 A）。
- **注**：极对数辨识不建议使用——`pn_id` 会 1→2→3 爬升并可能覆盖 `pmsm_config.pn`。

---

### 补丁 7 · 电角度辨识不自动生效

- **开关**：`PORT_PATCH_ELEC_BIAS_NO_AUTOAPPLY`（被补丁 16 取代，见下）
- **位置**：`motor_control/motor_ctl_sm.c` → `ElecAngleIdStep()` 完成分支
- **现象**：跑一次电角度辨识，就把出厂标定零点覆盖成测量值。
- **根因**：原逻辑辨识完成直接 `elec_angle_bias_rad = elec_bias_rad`（测量值）；
  而本模式进入时 `ModeCheckInInit` 已把零点清 0，结束时必须写回一个有效值。
- **修法**：完成后恢复成标定值 `PMSM_ELEC_ANGLE_BIAS_RAD`（221.6°），测量值（≈220.7°）
  保留在 `ElecAngleIdOutput.elec_bias_rad` 供人工核对。
- **后续**：补丁 16 把"标定值来源"从写死头文件改为 FlashDB，本补丁的语义并入补丁 16。

---

### 补丁 8 · 电角度辨识零点 180° 错误修正（历史）

- **位置**：`board_public/motor_parameter_hpm6emotorv20_bldc12v.h` → `PMSM_ELEC_ANGLE_BIAS_DEG`
- **结论**：最终确认正确值为 **221.6°**。曾经误判为 41.6°，是被一次 541,045 counts
  的位置跟随误差污染了 A/B 结果；该误差修掉后，221.6° 给出正确转向、速度模式稳定。
  180° 错时电流环仍"稳"（dq 同反），但 q 轴出力反向→速度环正反馈→飞车、iq 顶限幅。

---

### 补丁 9 · 辨识跑飞/超时中止

- **开关**：`PORT_PATCH_ID_ABORT_ON_RUNAWAY`
- **位置**：`motor_control/motor_ctl_sm.c` → `TqFcIdStep()`
- **现象**：转矩脉动辨识卡在"辨识中"下不来、无结果。
- **根因**：本机低速压不住，辨识会反向飞转；而阶段 1 完成条件要求"正向转满一圈"，
  反向时差值越来越负，永远不成立。
- **修法**：位置跟随误差超 `TQ_FC_ID_ABORT_ERR_P`(2 圈) 持续 200 ms，或总时长超 60 s，
  就置错误并关波。含 1 s 启动宽限（使能瞬间观测器尖峰不算）。

---

### 补丁 10 · 辨识转速提高

- **开关**：`PORT_PATCH_TQFC_ID_SPEED`（转速宏 `TQ_FC_ID_SPEED_RPM`=120）
- **位置**：`motor_control/motor_ctl_sm.c` → `TqFcIdStep()`
- **根因**：本机静止通电有 ±1.5~2.7° 定位力微振（编码器 ±30~120 counts），
  折合峰值角速度 10~15 rad/s，远大于 10 rpm 目标速度（1.05 rad/s），位置环被扰动主导。
- **修法**：辨识转速提到 120 rpm，提高信噪比。代价是转矩脉动表转速分辨率变差。

---

### 补丁 11 · 辨识期间打开 DOB

- **开关**：`PORT_PATCH_TQFC_ID_DOB`
- **位置**：`motor_control/motor_ctl_sm.c` → `TqFcIdStep()`
- **修法**：辨识期间使能负载扰动观测器，帮助压住低速扰动。

---

### 补丁 12 · 辨识后不自动启用补偿

- **开关**：`PORT_PATCH_TQFC_LEAVE_COMP_OFF`
- **位置**：`motor_control/motor_ctl_sm.c` → `TqFcIdStep()` FINISH 分支
- **现象**：辨识"成功"后，速度模式一使能就抖甚至飞车（给定 0 也飞到 −889 rad/s）。
- **根因**：上游在辨识完成时自动置 `tq_com_enable=1 / fc_com_enable=1`，直接投入补偿。
  实测辨识出的 `fc_p_com≈±0.143 A` 符号在零速附近来回翻，形成自持振荡。A/B 证实：
  补偿关则 `speed_now ±1.7 rad/s` 稳定，补偿开则飞车。
- **修法**：辨识完成只算数据、不自动启用；是否启用由人确认后手动打开。

---

### 补丁 13 · 运行模式切换后确保对应 APP 被使能（13b，当前默认关）

- **开关**：`PORT_PATCH_APP_ENSURE_ENABLED`（**默认 0**）
- **位置**：`app/app_scheduler.c` → `AppRun()`
- **现象**：写 opmode=速度模式后 `motor_ctl_sm_config.mode` 切了，但 `PvModeRun()`
  从不执行、`speed_tar_p_s` 恒 0、电机不动。
- **根因（补丁 15 已修）**：`set_app_Modes_of_operation` 的重复检查恒真，`set_app(APP_PV_MODE)`
  没被调用，PV 应用一直 IDLE。13b 是"每周期兜底补调 set_app"的绕路方案。
- **副作用**：`PvModeInit()` 会 `set_app_Controlword(DISABLE)`，13b 靠事后恢复 cw 兜底，
  本质是跟自己的副作用打架（曾导致补丁把使能吃掉的时序问题）。
- **现状**：根因已被补丁 15 修复，13b 冗余；因暂无法烧录验证"关掉后仍正常"，**代码保留、
  默认关闭**。验证通过后可整块删除。

---

### 补丁 14 · 电流零漂标定结果存 Flash

- **开关**：`PORT_PATCH_CAL_DRIFT_STORE_FLASH`
- **位置**：`bsp_api.c`（存/取）、`main.c`（上电恢复）、`app_store_param.*`（结构字段）
- **现象**：每次上电都要先"使能一次做标定"电机才能转，否则不动、无报警。
- **根因**：`s_cal_status/s_cal_drift` 只在 RAM，复位回 READY；`hw_ready` 要求 cal==OK。
- **修法**：标定成功后把三路漂移+魔数('CAL1')+CRC 写进 `kFlashStorage`（随 AllParam 走
  SysCmd=2 落盘）；上电从 Flash 恢复，校验通过即置 cal=OK。
- **验证**：已端到端验证——标定后 `s_cal_drift=[32214,32560,32819]`，存盘复位后上电
  `cal_status=OK`、`drift≈[32217,32563,32841]`，不再需要先使能做标定。

---

### 补丁 15 · 运行模式切换的恒真检查 + 帧回写覆盖

- **开关**：`PORT_PATCH_OPMODE_DIRECT_APPLY`
- **位置**：`database/data_param.c` → `set_app_Modes_of_operation()`；
  `communication/callback/mavlink/mavlink_callback.c` → `MotorCtlSmConfig` 帧处理
- **现象**：切速度/位置模式没反应、使能后电机不动、标定做不完。
- **根因**（三处叠加）：
  1. `get_app_Modes_of_operation_display()` 内部就是回读 `kAppOpMode`，导致
     `if(val==display) return` 在写非负模式时恒成立——0/1/2/3 全被吞，只有负值辨识能切；
  2. `MotorCtlSmConfig` 帧每周期把上位机缓存的旧 mode(0) 回写覆盖 `motor_ctl_sm_config.mode`；
  3. 上位机轮询把 opmode=0 发下来，覆盖刚切的运行模式。
- **修法**：① 重复判据改为"与控制层实际 mode 比较"；② `MotorCtlSmConfig` 帧不再写 mode；
  ③ `set_app_Modes_of_operation` 收到 IDLE(0) 且控制层非 IDLE 时视为回写噪声忽略。
- **关键提醒**：`MOTOR_CTL_SM_MODE_SPEED = 2`（不是 1，1 是力矩模式）——之前"失控飞车"
  很大程度是拿 opmode=1 当速度模式测、实际进了力矩模式透传残留电流所致。

---

### 补丁 16 · 电角度零点存 FlashDB

- **开关**：`PORT_PATCH_ELEC_BIAS_STORE_FLASH`
- **位置**：`bsp_api.c`（存/取）、`servo_bringup.c`（上电恢复）、`motor_ctl_sm.c`（辨识完成写影子）、
  `app_store_param.*`（结构字段）
- **背景**：原程序零点靠"每次上电跑电角度辨识"现场获取，辨识不可靠时零点会错；
  本板此前只能把头文件 `PMSM_ELEC_ANGLE_BIAS_RAD` 写死，改一次就得重刷固件。
- **修法**：`FLASH_PARAM_STRUCT` 增 `elec_angle_bias_magic/'ELB1'/rad/crc` 三字段；
  - `servo_bringup.c`：上电优先从 Flash 恢复零点，无有效值才用头文件静态值兜底；
  - `motor_ctl_sm.c`：辨识完成把测量值写入 Flash 影子（候选值），本次运行仍用当前有效零点
    不立即覆盖（保留补丁 7 的"不自动应用"原则），SysCmd=2 存盘后下次上电生效；
  - 校验：魔数 + CRC + 弧度范围 0~2π 合理性检查。
- **效果**：标定一次→存盘→以后上电自动从 Flash 读，不再依赖重刷固件、也不用每次靠辨识取零点。
- **状态**：已全量编译通过，**尚未烧录验证**（调试器未接）。

---

## 三、应用层修改（只有一行）

**原则**：`app/` 属于原工程，除必须外不动。前后评估过两轮，真正必要的只有**一行**：

`app/Identify/app_id_dir_mode.c` → `IdDirModeInit()`：

```c
axis->direction_id_config.id_tar_max_A = get_app_Motor_rated_current();
```

上游另外 5 个辨识 APP 都在 `Init()` 里设了辨识电流，**唯独方向辨识漏了**，于是沿用控制层
默认的 `pmsm_config.rated_current`（= √2 × 电机额定 = 1.697A），连续保持 25 s 会累积成
驱动器过载（`Error_word` bit1）被强制失能。补这一行后与其它 5 个 APP 一致。

**明确不改的（评估后放弃）**：

| 曾经考虑过 | 放弃原因 |
|---|---|
| `Init()` 清残留 `state_now` | 控制层在“失能→使能”沿的 `ModeCheckInInit()` 已经会清 |
| `Run()`/`Start()` 判 FINISH 返回 SUCCESS | 控制层在 FINISH 时自己会关 PWM 失能；上位机按 `state_now==3` 判断，本来就正常 |
| 完成后把 `Controlword` 归零 | 残留 1 不会重新使能（没有上升沿），无实际影响 |
| 使能 1 s 超时返回 FAIL | 同样只是显示层面，不影响辨识本身 |

> 遗留（保留上游行为）：6 个辨识 APP 的 `Run()` 仍永远返回 `RUNNING`，成功后 APP 不自己结束。
> 若以后要改，注意一个坑：**FINISH 时控制层会关 PWM → `hw_ready_state=0` → `AppRun()`
> 不再调用 `Run()`**，所以收尾判断必须放在 `Start()`（READY 状态下会被反复调用）里，
> 放 `Run()` 里永远走不到。

---

## 四、五个补丁的实机验证记录

| 补丁 | 结论 | 验证方法与实测数据 |
|---|---|---|
| `PORT_PATCH_PWM_KEEPALIVE` | ✅ 有效 | 方向辨识 `state_now` 0→2→3，编码器 +32642 counts（≈2 圈），全程 `Error_word=0` |
| `PORT_PATCH_CAL_AUTOSTART` | ✅ **必要** | A/B 对照：开关改 0 烧一版 → 上电后 `hw_ready` **恒为 0**、`state` 永远进不了 ENABLE，**且 `Error_word` 仍为 0（静默死锁）**；改回 1 后使能正常（`hw_ready=1`） |
| `PORT_PATCH_FAST_OC_VISIBLE` | ✅ 有效 | 临时把 `DRIVER_OVERCURRENT_LIMIT_A` 调到 0.4 A 烧一版（App 单相阈值仍为 3.0 A，由 FlashDB 恢复），给 1.2 A 电流 → 0.3 s 内 `Error_word` 置 **bit14（16384）= 驱动器过流**、`Controlword` 自动归 0。若没有该补丁，板级 20 kHz 只静默封桥，App 侧 `Error_word` 会是 0 |
| `PORT_PATCH_CLEAR_ERROR_FIX` | ✅ 有效 | `Error_word=2`（驱动器过载）锁存后，发 `Controlword 0→3→0` → 读回 **0** |
| `PORT_PATCH_ID_MODE_RESEND` | ✅ 有效 | 进入 -4 后把 `ElecAngleIdConfig.id_max_A` 人为改成 1.6 → 重复下发 `Modes_of_operation=-4` → 约 0.4~0.8 s 后 `id_max_A` 回到 **1.2**（`IdElecAngleModeInit()` 重新执行）。延迟来自上位机发送队列，不是固件 |

> 注意：验证 `ID_MODE_RESEND` 不能看 `state_now`——上游 APP 的 `Init()` 不清 `state_now`，
> 应看 `Init()` 有副作用的参数（如 `ElecAngleIdConfig.id_max_A`）。
> 验证完记得把临时改过的宏恢复（`DRIVER_OVERCURRENT_LIMIT_A=3.00f`，
> 开关全部 `(1)`），并重新编译烧录。

---

## 五、已知未修（与本次问题无关，单独排）

1. **速度观测器噪声**：位置静止（编码器 ±1 count）时，`ev_rad_s` 仍在 ±22 rad/s 抖动，
   真实平均速度只有 0.5 rad/s。~~怀疑 PLL 带宽（100 Hz）/ `enc_line_inv_p_n` / 编码器量化。~~
   **已定性**：用同板同电机的 my_ecat_cia402（v122）对照，关波时编码器抖动 0~1 count、
   开波保持时抖动 123 counts（本工程 74~136），两边一致；且对方 `encoderinfo` 的
   transfer/parity/magnetic 全为 0。结合“0.02 A 比 1.2 A 抖动更大”（电气噪声应随电流增大），
   结论是**电机静止通电时的定位力（齿槽）微振 ≈2.7° 机械角**，不是观测器或编码器问题，
   对方工程也是用 2θ 的 Iq 前馈去补偿，而不是改滤波器。**暂不处理。**
2. **编码器多圈值异常**：静止或使能沿附近出现 −59017 → −50064 → −91780、
   42524 → 60323 → 42482 这类回跳。**已定性**：在“磁场固定、转子不动”的窗口内实测
   `enc_sum_p` 只跟随原始抖动（±42 counts），**没有整圈累加错误**；那些回跳的时间点都落在
   “使能瞬间转子被磁场拉正（实测 −5102 → +1564 counts，约 77°）”或“链路冻结时的缓存假象”上。
   多圈累加逻辑本身正常，**暂不处理**；若以后要动，注意 `drv_encoder.c` 已有 3 点中值，
   挡得住孤立尖峰但挡不住连续 ±30 counts 的抖动。
3. `servo_bringup_self_test()` 的零漂标定失败只打串口，上位机看不到。
4. 速度模式低速不稳：目标 1 输出 rpm（≈107 电机 rpm）实测冲到 ~1770 rpm 后回落，
   且 `PosSpeedCtlInput.speed_tar_p_s` 读回一直为 0（与出力对不上），待单独排查。

---

## 2026-11-08 重大结论：速度模式号是 2 不是 1（之前"失控"是模式用错）

`motor_ctl_sm.h` 里：
```
#define MOTOR_CTL_SM_MODE_TORQUE (1)   // 1：力矩模式
#define MOTOR_CTL_SM_MODE_SPEED  (2)   // 2：速度模式   ← 速度模式是 2！
```

**长期误判**：一直用 opmode=1 当"速度模式"测试，实际切的是**力矩模式 TorqueStep**。
TorqueStep 直接透传上位机帧写进来的 `idq_tar_A`，不理会 `speed_tar_p_s`，
电机按残留 `idq_tar` 乱转→过速保护，被误判成"速度环正反馈失控"。

用 opmode=2 纠正后实测（GDB 直写 config.mode=2 同样成立）：
- state=1(ENABLE) 稳定，err=0，不再暴走
- 5 输出 rpm：speed_tar_p_s=146091 正确下发，speed_now 达 254 rad/s，iq_tar 顶限幅闭环出力
- 2/5/1 rpm 反复测均不失控

**整条链路（使能-模式-电流环-速度环）已打通**。剩下是速度环极性/增益整定 + 低速定位力，
属调参范畴。相关补丁：13（APP 使能补丁，13b 恢复 cw）、15（set_app_Modes_of_operation 恒真检查、
MotorCtlSmConfig 回写、opmode=0 回写保护）、14（零漂标定存 Flash，已端到端验证）。
