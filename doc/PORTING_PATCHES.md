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
