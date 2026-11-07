# ADC IRQ 优先级单变量对照结果

状态：**构建通过；未做硬件验证**。本轮只做 priority 交换和只读 adcinfo 扩展；未改优化级别、ADC 配置、1kHz 任务位置、控制算法或协议。

## 改动

- `embedded_project/HPM6E80/Board/board.c`
  - ADC3 IRQ priority：5 → **6**
  - ADC2 IRQ priority：6 → **5**
  - 相关注释改为“ADC3 更高；但仍需 PLIC preemption 才真正抢占”。
- `embedded_project/HPM6E80/Board/servo_console.c`
  - `adcinfo` 增加只读 `PLIC feature / preempt / threshold / ADC2_pri / ADC3_pri` 打印。
  - 使用 `HPM_PLIC->FEATURE`、`PLIC_FEATURE_PREEMPT_GET`、`HPM_PLIC->TARGETCONFIG[M].THRESHOLD`、`PRIORITY[IRQ-1]`；这些寄存器为 RW，读取不会清标志。
- `servo_console.h` 及既有 diagnostic capture 代码保持不变；未恢复或覆盖上一阶段改动。
- GPTMR 仍为 priority 6；未改。

## 产物与差异

目录：`build-hpm6e80/diagnosis/dma_priority/`

- `demo.elf`：1,394,128 B，SHA256 `5f136f46a1f76b91087a88b6ccbdb8bb3e6c82950f4b00e4d5fb80451ba82c4e`
- `demo.bin`：267,424 B，SHA256 `8d16c1ee4e499a485197570231d28863382a5a8beb80fdc3316f92d0ba727d5f`
- `build.log`：完整构建日志
- `board_priority.patch`：相对当前 diagnostic 版本的 board.c 精确差异，SHA256 `3632ba7bb9b34b51839000b1d8be7a60490f8bb698096a458b53d40e6501bc2f`
- `servo_console_adcinfo.patch`：相对 diagnostic 的 adcinfo 差异，SHA256 `98dd520ec6f035b6fe37364a97cf0ed331517cb1391a99863759bddabfdef406`
- `pre_priority/`：改前三个 Board 文件快照及 hash，保留诊断改动
- `pt_load.txt`、`flash_ranges.txt`、`program_headers.txt`
- `manifest.txt`、`sha256.txt`

构建环境：与 `dma_capture` 相同 process-only `HPM_SDK_BASE`/PATH，debug O0，未改 `CMAKE_BUILD_TYPE`。

## 资源与 Flash

| 区域 | 使用 | 容量 | 占比 |
|---|---:|---:|---:|
| FLASH | 267,900 B | 16 MB | 1.60% |
| AXI_SRAM | 98,968 B | 512 KB | 18.88% |
| ILM | 4,080 B | 256 KB | 1.56% |
| DLM | 32,768 B | 256 KB | 12.50% |
| AXI_SRAM_NONCACHEABLE | 1,408 B | 256 KB | 0.54% |

Flash PT_LOAD：

- `0x80000400..0x8000108F`，`0xC90`
- `0x80003000..0x80003057`，`0x58`
- `0x80003058..0x80004047`，`0xFF0`
- `0x80004048..0x8004167B`，`0x3D634`
- `0x80041680..0x8004189F`，`0x220`

最高 Flash LMA 结束地址 `0x8004189F`，低于 `0x80100000`；全部落在已备份前 1MB 内。`manifest.txt` 记录 `within_first_1mb=True`。

## 优先级与实测上下文

- HPM PLIC 数值越大优先级越高（`hpm_plic_regs.h:67-69`）；交换后 **ADC3=6，ADC2=5**。
- SDK vector wrapper 在 handler 中重新打开 MIE（`hpm_interrupt.h:1040-1048,1227-1240`）；但 PLIC `FEATURE.PREEMPT`/threshold 是否允许硬件抢占，本轮只做读取，不在无硬件时下结论。`adcinfo` 将打印实际值。
- Codex 实测 4 组确认：长间隔多出现在每 20 条（如 `[14,34,54,...]`），ADC3 最终落后 **105~200 次/1024**，raw 三相 σ **41~53mA**；队列/通道/触发正确，无错误状态。该模式支持“20kHz 调度/ADC3 服务积压”与“raw ADC 底噪”分别处理；**不能声称本次 IRQ 交换会消除底噪**，也不是速度故障最终修复。
- 交换优先级只改变 ADC3 服务顺序/抢占机会；ADC2 的 `CurrentLoopCtrl` 仍可能在 ADC3 更新 V 前读取旧 V。带电流运行时需一致快照；空载/零电压诊断无此影响。
- 实机需用 `adcinfo` 读取实际的 `preempt/threshold/priority`，再决定是否继续；若 ADC3 仍积压，下一步应查 PLIC 真正抢占条件或把 1kHz position 分支移出 20kHz ISR，而不是继续调 ADC。

## 验证边界

- 构建成功；未烧录、未运行、未读串口/MCP/JTAG。
- `adcinfo` 的 PLIC 打印尚未实机验证；本轮只核对编译和寄存器读法。
- 当前工作区仍保留上一阶段 diagnostic 三文件修改；本轮在其上仅追加上述 priority 与 adcinfo 变化，未提交。
