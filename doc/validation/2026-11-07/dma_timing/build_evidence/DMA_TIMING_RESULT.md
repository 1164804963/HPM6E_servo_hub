# ADC/DMA 中断时序与 deadline 结论

状态：只读审阅；未改源码、未构建、未操作硬件、未提交。首轮实测数据：`D:/Documents/ChatGPT/YeeZi/dma_measurements/first/`。

## 结论摘要

- **优先级方向**：HPM PLIC 的数值越大优先级越高（`soc/HPM6E00/ip/hpm_plic_regs.h:63-70`）。当前 ADC2=6、ADC3=5，**ADC2 更高**；`board.c` 里“ADC3 更高”的注释是反的。
- **嵌套**：实际编译未定义 `DISABLE_IRQ_PREEMPTIVE`，也未定义 `USE_NONVECTOR_MODE`。走 vector wrapper，`ENTER_NESTED_IRQ_HANDLING_M()` 会 `csrsi mstatus, 8` 重新打开 MIE（`arch/riscv/intc/hpm_interrupt.h:1040-1048`、`1227-1240`）。所以 **软件上允许嵌套**；但 board 没有配置 PLIC 的 `FEATURE.PREEMPT`/threshold，硬件是否真正抢占尚未证实（`hpm_plic_regs.h:51-60`）。
- **deadline**：`PosSpeedLoopCtrl` 的 `st pos=100~140us` 单独已超过 50us。只要该分支在某个 ADC2 周期执行，这一拍 ADC2 ISR 的总时长必然超过 20kHz 的 50us 期限；但 `st pos` 只测 `PosSpeedLoopCtrl`，不是整个 ISR。本次采集的 `start_cycle` 相邻间隔均值仍约 50.2us、最大 123us，不能把每个周期都归因于 100~140us，需按 `pos_div` 对齐确认。
- **ADC3 落后**：`seq3` 最终落后 143/186，`status3=0x80000000`（ADC3 TRIG_CMPT 仍 pending）在关 PWM 有 420/1024、零 PWM 191/1024 次。这说明 ADC3 ISR 没及时清完成位，多个触发会合并成一个 pending bit；不是 FIFO/AHB/冲突错误，也不能直接说 DMA 数据无效。
- **V 的控制影响**：ADC2 ISR 先处理 U/W；ADC3 的 V(20 cycles) 与 VBUS(160 cycles) 只有 VBUS 完成才触发 ADC3 ISR，`kBspData.adc_v_raw` 也只在 ADC3 ISR 更新（`board.c:255-256`）。所以 U/W 是当前 ADC2 数据，控制中的 V 至少可能落后一个 ADC3 中断；V 确实进入 `bsp_get_phase_current()`（`bsp_api.c:317-319`）和 `CurrentLoopCtrl`（`motor_ctl_loop.c:183`）。这是采样时序问题，不能解释 PWM 关闭时仍存在的 43~51mA raw 底噪。

## 1. 优先级、MIE 和嵌套

### 优先级方向

PLIC 寄存器定义明确：

- `soc/HPM6E00/ip/hpm_plic_regs.h:67-69`：priority 有效 1~31，**数值越大优先级越高**。
- `arch/riscv/intc/hpm_interrupt.h:348-352`：`intc_m_enable_irq_with_priority()` 只调用 `intc_set_irq_priority()` 和 `intc_m_enable_irq()`，没有反转数值。
- `board.c:437` 为 ADC3=5，`board.c:441` 为 ADC2=6，所以当前 **ADC2 高于 ADC3**。

因此 board.c 中“ADC3 优先级更高”的假设不成立。ADC2 的高优先级会先于 ADC3 服务；如果 ADC2 ISR 长，ADC3 的 pending 位会积压。

### MIE 是否恢复

`compile_commands.json` 中：

- `DISABLE_IRQ_PREEMPTIVE` 出现 0 次；
- `USE_NONVECTOR_MODE` 出现 0 次；
- 使用 vector 模式。

`hpm_interrupt.h:1227-1240` 的 `SDK_DECLARE_EXT_ISR_M` wrapper 执行：

- `SAVE_CALLER_CONTEXT()`
- `ENTER_NESTED_IRQ_HANDLING_M()`：保存 `mepc/mstatus`，并 `csrsi mstatus, 8` 打开 MIE（`:1040-1048`）
- 调用应用 ISR
- `COMPLETE_IRQ_HANDLING_M()` 先清 MIE，再写 PLIC complete（`:1053-1058`）
- `EXIT_NESTED_IRQ_HANDLING_M()` 恢复 `mstatus/mepc`

所以 C ISR 执行期间 MIE 是打开的，软件嵌套路径已启用。非 vector 的 `trap.c:162` 也有 `enable_global_irq(MIE)`，但本项目未走该分支。

### 只改优先级能否真正抢占

**不能只看优先级就下结论。** 软件 MIE 已打开；但 PLIC 还有 `FEATURE.PREEMPT`（`hpm_plic_regs.h:51-60`）和 target threshold。board/SDK 初始化路径没有显式调用 `__plic_set_feature()` 或 `intc_m_set_threshold()`；本次也没有读回这两个寄存器。若 PLIC preempt 未生效，交换优先级只会改变下一次 claim/服务顺序，不会在 ADC2 ISR 中途抢占。

## 2. ISR 时长、20kHz deadline、tm 覆盖范围

### 当前 ISR 的调用段

`board.c:283-352` 的 ADC2 ISR：

1. 清 ADC2 trigger、fence、读 U/W；
2. `servo_console_isr_adc_capture()`：实测 copy mean 0.557us、max 2.305us；仅诊断 armed 时；
3. 每 20 拍：`drv_encoder_sample()` + `servo_console_isr_encoder()`（`board.c:310-315`）；
4. 进入 `s_ctrl_running` 后：
   - `set_timer_record_start(CURRENT)`（`board.c:322`）
   - PWM 状态/首次使能初始化
   - `CurrentLoopCtrl()`（`board.c:339`）
   - `set_timer_record_stop(CURRENT)`（`:340`）
   - `servo_console_isr_sample()`、`board_check_over_current()`
   - 每 20 拍：`set_timer_record_start(POSITION)`（`:348`）、`PosSpeedLoopCtrl()`（`:349`）、stop（`:350`）

### tm / st 实际包含什么

- `st` 的 `cur`/`pos` 来自 `servo_console.c:114-117`；`tm` 来自 `cmd_timing`（`servo_console.c:397-404`）。
- **cur**：只覆盖 `CurrentLoopCtrl()`；包含 `bsp_get_phase_current()`、`CurrentCtlLoopTask()`、`bsp_set_phase_voltage()`（`motor_ctl_loop.c:179-190`）。
- **pos**：只覆盖 `PosSpeedLoopCtrl()`；包含 `AppStatusCheck/AppStatusScanFast/AppMotionPreConditionRun/AppRun`（内部权限时）、`PosSpeedCtlLoopTask`、PWM 状态、`AppParamSyncUser`、`ScopeIsrHandle`（`motor_ctl_loop.c:195-258`）。
- **不包括**：ADC 状态/raw 读取、capture、`ctrl_tick`、编码器 SPI、`servo_console_isr_sample`、过流检查、vector wrapper 的整数/FPU 上下文保存。
- `tm` 打印的 “budget 50us” 是对 cur/pos 两者的提示，但 **pos 是 1kHz 任务**，不能用 50us 衡量；`st pos=100~140us` 本身已经超过 50us。
- 因此，**不能把 `tm cur` 当作 ADC2 ISR 总时长**；也不能用 `st pos` 之外的 50us 期限直接推断整个 ISR。

### 是否跨过 deadline

- 只要 1kHz 的 `PosSpeedLoopCtrl` 在该 ADC2 ISR 内执行，`st pos` 已 100~140us > 50us，**这一拍必然超期**。
- 但不能据此说每一拍都超期。本次 `start_cycle` 间隔均值 50.15~50.25us、最大 123us；如果每 1ms 都插入 100~140us，均值应明显大于 50us。需把 `start_cycle`/`pos_div` 对齐，确认采集期间 position 分支实际执行频次。
- `st pos` 是采集前的测量；当前采集是否同状态未由数据证明。当前 debug 构建也影响数值：`CMAKE_BUILD_TYPE=debug`，编译命令无 `-O`（GCC 默认 O0）；release 时间会不同。

### 其他未计时的函数

- `drv_encoder_sample()` 在 `board.c:313` 每 20 拍执行；内部 `encoder_mt6816_sample()` 是阻塞 `spi_transfer()`（`encoder_mt6816.c:212`）。`st/tm` 都不覆盖。
- vector wrapper 在每个中断保存/恢复调用者整数寄存器；由于 `-march=rv32imafc...`、`-mabi=ilp32f`，`__riscv_flen=32`，还保存/恢复 20 个 FPU caller 寄存器（`hpm_interrupt.h:621-624,694-744`）。这也在 `st/tm` 之外；不能把 `tm` 当成完整 ISR 时间。
- `servo_console_isr_sample`、`board_check_over_current` 在 cur timer 之外；`PosSpeedLoopCtrl` 的 `AppRun` 等全部在 pos timer 内。

**没有静态 WCET 证据**：无法从现有源码/测量给出每个函数的最大执行时间；目前可确认的硬事实是 capture 0.557/2.305us、pos 100~140us，以及 `st/tm` 的覆盖边界。

## 3. ADC3 落后、新旧数据、V 控制

### ADC3 时序

- ADC2：U(5)→W(6)，每通道 sample 20 + conversion 21 = 41 cycles；两通道约 82 cycles、1.64us 后完成；ISR 读 U/W。
- ADC3：V(4)→VBUS(7)，V 约 41 cycles（0.82us），VBUS 约 160+21=181 cycles（3.62us）；`inten[1]=true`，只在 VBUS 完成后触发 ADC3 ISR（`board.c:201-205`）。ADC3 总完成约 4.44us，仍远小于 50us。
- ADC3 完成位是单 bit `TRIG_CMPT`（`hpm_adc16_regs.h:556-563`）。如果 ISR 未及时清，多个触发会合并；每清一次只代表一次服务，不能保存丢失次数。
- 实测 `status3=0x80000000` 在关 PWM 420/1024、零 PWM 191/1024 次；`seq3` 最终落后 143/186。这是 **ADC3 服务积压** 的直接证据，不是 FIFO/AHB/冲突错误（INT_STS 无对应错误位）。
- `adc3_copy_races=0` 只说明 ADC2 copy 期间 seq3 没变；不等于 ADC3 是当前周期。`cycle_bit=1` 且无跳变，不能据此判 stale 或 fresh。

### 读到的数据是“新”还是“旧”

- ADC2 的 U/W raw 来自当前 ADC2 DMA，通常是当前触发。
- ADC3 的 V 在 DMA 里可能已完成，但 **控制变量 `kBspData.adc_v_raw` 只在 ADC3 ISR 更新**（`board.c:255-256`）；ADC2 ISR 在它之前运行，所以 `CurrentLoopCtrl` 中的 V 至少可能落后一个 ADC3 服务。
- VBUS 是第二个 slot，ADC3 ISR 等 VBUS 完成；ADC2 ISR 较早读取 `adc_buff[1]` 时，VBUS 可能仍是上一拍；V 是否新要看 `status3/seq3`。
- `status3` 置位时 ADC3 转换已完成，DMA 字可能是新值；但 ISR 未更新 `kBspData`，控制仍用旧 V。`status3=0` 时也不能仅凭 seq 判新旧，需结合 DMA/触发时序。
- 若 ADC3 积压多个触发，DMA 最终保留最近一次结果；丢失的是中间样本/中断计数，不是当前 DMA 字。

### V 是否参与控制

是。`CurrentLoopCtrl()` 调用 `bsp_get_phase_current()`（`motor_ctl_loop.c:183`），后者使用 `kBspData.adc_v_raw`（`bsp_api.c:317-319`）。因此 U/W 当前、V 可能落后会形成三相不同步；这在有电流、运动时可能造成控制误差。但在 PWM 关闭/零电压时，43~51mA 的 raw 底噪仍然存在，说明 **V 时序不是该底噪的唯一/充分解释**，也不能直接认定为速度故障唯一根因。

## 最小可区分实验/修复建议

**建议先做一次只改一处的最小实验：交换优先级为 ADC3=6、ADC2=5（当前相反），其他不动，再采一轮 1024 点。** 观察：

- `seq3` 最终差值和 `status3=0x80000000` 次数是否显著下降；
- `start_cycle` 最大间隔/周期分布是否改善；
- ADC2/ADC3 是否出现新的 preempt 交错。

若交换后 ADC3 完成位不再积压，说明是当前 ADC2 高优先级 + 长 ISR 造成的调度问题；若不变，优先检查 PLIC `FEATURE.PREEMPT`/threshold（本次未读）以及 1kHz position 分支的实际执行频次。即使交换后 ADC3 能抢占，ADC2 的 `CurrentLoopCtrl` 也可能已在 4.44us 前读取旧 V；该实验验证的是调度/积压，不保证同一拍 V 已用于控制。

共享数据约束：

- ADC3 变高后可在 ADC2 ISR 中间抢占；`kBspData.adc_v_raw/vbus_raw` 由 ADC3 更新，而 ADC2 的 `CurrentLoopCtrl` 正在读取三相。**空载/零电压诊断可接受；带电流运行时需使用一致快照/临界区，不能把交换优先级直接当最终修复。**
- `adc_buff[0]` 与 `adc_buff[1]` 分属 ADC2/ADC3，copy 已用 `seq3_before/after` 检测；不要扩大到通用 scheduler。
- 若优先级交换无效，再考虑把 1kHz `PosSpeedLoopCtrl` 下放主循环/分段；那会共享 `kAxis` 与 20kHz 控制数据，必须先定义一致快照/临界区，不能直接搬。

## 仍需确认

- PLIC `FEATURE.PREEMPT` 和 target threshold 的实际值；本次未读，不能断言当前一定发生硬件抢占。
- 采集期间 `pos_div`/`PosSpeedLoopCtrl` 的实际执行时刻；`st pos` 是采集前测量，不能直接代表本次每个 1024 点周期。
- `CurrentLoopCtrl` 和 `drv_encoder_sample` 的最大执行时间；现有 `tm` 不覆盖编码器，且只覆盖部分控制段。
- `status3` pending 的具体服务间隔与 ADC2/ADC3 ISR 进入/退出时间；当前只有 copy 开始 cycle 与 seq，不是完整 ISR trace。
