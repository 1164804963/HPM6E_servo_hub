# 同步 ADC/DMA 最小只读诊断实现结果

状态：**构建通过；未做硬件验证**。本阶段未访问 MCP/COM/JTAG、未烧录、未提交 Git、未安装依赖。

## 改动

仅改 3 个文件，`git diff --check` 无报错：

- `embedded_project/HPM6E80/Board/board.c`：ADC3 ISR 推进序号；ADC2 ISR 在 armed 时调用快照。
- `embedded_project/HPM6E80/Board/servo_console.c`：1024 点静态快照、`adccap`/`adcdump`/`adcinfo`。
- `embedded_project/HPM6E80/Board/servo_console.h`：两个 ISR 接口。

未改 `board.h`（仍 20/4）、ADC 配置、触发、控制数学、协议或生成算法。`cmd_burst` 的中文注释已从 `adcinfo` 前移回它自己的位置。

## 接口与行为

- `adccap`：清零并 arm 1024 点；不等待、不打印快照。最后发布 `armed=true` 前有编译器内存屏障。
- `adcdump`：未采满时打印 `NOT READY n=/1024 armed= done=` 后立即返回；采满后导出全部 1024 行，不是只给统计。
- `adcinfo`：只读打印 CPU/ADC2/ADC3 时钟、`CONV_CFG1` 分频/转换时钟、`ADC_CFG0`、`SAMPLE_CFG`、`COV_END`、`wait_dis`。
- 快照结构 10 个 32bit 字：ADC2 U/W、ADC3 V/VBUS 四个 DMA 原字，`sts2/sts3`、`seq2`、`seq3_before/after`、`start_cycle`。静态数组 `1024*10*4=40,960 B`，无动态分配。
- `sts2/sts3` 只在 armed 分支读取，未启动采集时不产生额外两次 MMIO；ISR 接口已简化，不再每拍传状态参数。

## 采样点与跨 ADC 关系

- PWM 触发点在计数器=1（`board.c:120-129`）；ADC2：U(5)→W(6)，ADC3：V(4)→VBUS(7)。
- ADC3 IRQ 优先级 5，ADC2 优先级 6（`board.c:437-441`）。
- 快照在 **ADC2 完成 ISR** 中，`hpm_adc_v2_clear_status_flags` 和 `fence` 之后拷贝；ADC3 完成 ISR 只推进 `seq3`。
- 不假定 ADC3 与 ADC2 同一时刻完成：`seq3_before/after` 可暴露 ADC2 拷贝期间 ADC3 是否更新；`seq2` 是 ADC2 快照计数，`seq3` 是 ADC3 完成计数，末值差异可提示漏/多周期。
- 不是硬件时间戳；ADC3 原始字可能属于前一周期，必须结合 `seq3`、DMA 字内 `seq_num/cycle_bit` 判断。

## 原始 32bit 字布局

`ADC_SOC_IP_VERSION=3`（`hpm_soc_feature.h:151`），对应 `adc16_pmt_dma_data_t` 的 else 分支（`hpm_adc16_drv.h:258-265`）：

| 位 | 字段 | 说明 |
|---|---|---|
| `[15:0]` | result | 原始转换结果，低 16 位 |
| `[19:16]` | reserved | 保留 |
| `[24:20]` | adc_ch | 硬件通道 |
| `[28:25]` | trig_ch | 硬件触发通道 |
| `[30:29]` | seq_num | 队列序号 |
| `[31]` | cycle_bit | 周期位；**不是 valid** |

字段行号（`hpm_adc16_drv.h`）：result 259、reserved 260、adc_ch 261、trig_ch 262、seq_num 263、cycle_bit 264。`hpm_adc_v2_port.c:252-264` 的 `adc_v2_port_fill_from_adc16_pmt()` 按同一布局解析；`adcdump` 使用 `hpm_adc_v2_parse_pmt_dma_word()`，没有手写猜位。

**没有 per-word valid 位**：`ADC16_BUS_RESULT.VALID` 是 bus/oneshot 结果字段（`hpm_adc16_regs.h:193-203`），不能拿来解释 PMT DMA 字。PMT DMA 的无效应由 `seq3` 差异、DMA 字字段及 `INT_STS` 状态联合判断。

`sts2/sts3` 是 `INT_STS` 的只读快照；该寄存器为 RW1C（`hpm_adc16_regs.h:554`），读取不清除。可用位：`b31 TRIG_CMPT`、`b30 TRIG_SW_CFLCT`、`b29 TRIG_HW_CFLCT`、`b28 READ_CFLCT`、`b22 DMA_FIFO_FULL`、`b21 AHB_ERR`（`hpm_adc16_regs.h:556-660`）。ISR 已先清除 `TRIG_CMPT`，故快照中 b31 通常为 0；其他冲突/溢出位保留。快照代码不写 `INT_STS`。

## 采集开销与发布顺序

- 在 armed 分支内用 **RISC-V `mcycle` 低 32 位**（`csrr mcycle`）记录复制开始；每行保存 `start_cycle`。复制结束再次读取，差值计入总/最大 copy cycles。
- 该 delta 是 wall time，**包含 ADC3 高优先级 ISR 抢占**；不是纯指令数，也不是整个 ADC2 ISR 时长。
- `adcdump` 表头打印 `copy max/mean` 与 arm 时 `clock_cpu0`；每行打印 `cyc`，可检查相邻周期的 cycle 间隔和漏采。`adcinfo` 也打印 CPU 时钟。
- 发布顺序：先写快照/长度/统计，`adc_capture_barrier()`（仅编译器内存屏障，不是硬件 fence；单核 ISR/主循环可见性足够），再发布 `done=true`；arm 时同样在 `armed=true` 前加屏障。无原子库/锁。

## Flash 段与内存

构建：`tools/build_hpm6e80.ps1`，process-only `HPM_SDK_BASE`/PATH，exit 0。
完整日志：`build-hpm6e80/diagnosis/dma_capture_build_r2.log`。

| 区域 | 使用 | 容量 | 占比 |
|---|---:|---:|---:|
| FLASH | 267,756 B | 16 MB | 1.60% |
| AXI_SRAM | 98,968 B | 512 KB | 18.88% |
| ILM | 4,080 B | 256 KB | 1.56% |
| DLM | 32,768 B | 256 KB | 12.50% |
| AXI_SRAM_NONCACHEABLE | 1,408 B | 256 KB | 0.54% |

Flash PT_LOAD（LMA/FileSiz）：

- `0x80000400` / `0xC90`
- `0x80003000` / `0x58`
- `0x80003058` / `0xFF0`
- `0x80004048` / `0x3D5A4`
- `0x800415F0` / `0x220`（VMA `0x01200000` 的初始化数据）

新增静态快照使 AXI_SRAM 从 57,976 B 增至 98,968 B；其中 40,960 B 是快照数组，仍在 512 KB 内，因此采用 1024 点。未改 `.ld`、DMA buffer 或非缓存区。

构建产物：`demo.elf` 1,393,276 B，SHA256 `d6b9e19fd22506bf2b19bed4a46d4fb52670423ed9675e2fbbd8398b5fa41c0b`；`demo.bin` 267,280 B，SHA256 `788960e07d599942472ed23bf53ad338780824b4afac63e597a496dd08e265e8`。

## 时序测量方法

本阶段未实测。不要用 `tm` 的当前环指标来归因新增采集开销：当前 `set_timer_record_start` 在 `servo_console_isr_adc_capture` **之后**，`tm` 不覆盖这段。实际使用 `adcdump` 头部的 copy max/mean 与每行 `cyc`：1024 点按 20 kHz 约 **51.2 ms**；相邻 `start_cycle` 差值应接近 CPU 时钟/20 kHz，异常间隔可提示漏采或 ISR 延迟。`mcycle` 低 32 位会回绕，本快照窗口足够短，回绕不影响差值；跨回绕需额外处理，本阶段不做。

## 风险与未确认

- 未经实机验证；`adcinfo`、`adccap`、`adcdump` 的串口行为需 Codex 验收。
- PMT DMA 无 valid 位；不能把 `cycle_bit` 当有效标志。
- ADC3 与 ADC2 不是硬件同步采样；`seq3_before/after` 只能提示顺序/竞态，不能证明同拍。
- `seq2` 是快照计数，不提供绝对时间戳；跨周期判断依赖 `seq3` 差值、相邻 `start_cycle` 和原始 `seq_num/cycle_bit/INT_STS`。
- `INT_STS` 的其他位若被 SDK/其他 ISR 清除，快照只能反映读取时状态；本实现不写状态寄存器。
- 40 KB AXI_SRAM 对当前工程可接受；若后续内存紧张，可按证据降为 512 点（约 20 KB），但会缩短 51.2 ms 观察窗。
