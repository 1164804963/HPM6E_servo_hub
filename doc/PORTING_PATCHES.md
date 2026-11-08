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

## 三、应用层修改（不属于通用驱动，风险最低）

`app/Identify/app_id_dir_mode.c`（方向辨识 APP）：

1. `Init()` 补上辨识电流：`min(电机额定, 0.81×电机峰值)`。
   上游其它 5 个辨识 APP 都设了，唯独方向辨识漏了，导致用控制层默认的 √2×额定。
2. `Init()` 清掉上次残留的 `state_now / direction / elec_angle_tar`。
3. `Run()`：完成返回 `SUCCESS`、急停/超时返回 `FAIL`（原来永远 `RUNNING`）；
   加 `s_armed`，必须看到过"非完成"状态才认 FINISH，防止残留的 3 直接判成功。

> 另外 5 个辨识 APP（电角度 / 机械特性 / 极对数 / 转矩脉动 / 电气特性）存在同样问题：
> `Run()` 永远返回 RUNNING，且结果判断挂在"抱闸已松"的条件里。本机
> `Brake_control_mode=0(自动)` 能松到位所以暂时没问题，换无抱闸/手动抱闸模式会卡住。
> **目前未改**，如果需要可以照方向辨识的写法补齐。

---

## 四、已知未修（与本次问题无关，单独排）

1. **速度观测器噪声**：位置静止（编码器 ±1 count）时，`ev_rad_s` 仍在 ±22 rad/s 抖动，
   真实平均速度只有 0.5 rad/s。怀疑 PLL 带宽（100 Hz）/ `enc_line_inv_p_n` / 编码器量化。
2. **编码器多圈值异常**：静止或使能沿附近出现 −59017 → −50064 → −91780、
   42524 → 60323 → 42482 这类回跳。怀疑 `MotorCtlSmStateInit()` 每次使能按
   `motor_circle_int_n` 重算 `init_pos_p`，或 `drv_encoder.c` 三点中值挡不住连续坏帧。
   这一项会直接污染方向辨识的判据（判方向就是比编码器差值），建议优先。
3. `servo_bringup_self_test()` 的零漂标定失败只打串口，上位机看不到。
