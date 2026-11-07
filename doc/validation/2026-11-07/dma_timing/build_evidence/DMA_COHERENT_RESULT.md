# ADC 同帧控制与默认 -O2 构建结果

状态：**构建通过；硬件未验证**。已按设计把 ADC3 V/VBUS 完成 ISR 作为唯一控制节拍；ADC2 U/W 由该节拍检查完成后消费。未改 ADC 配置/窗口、1k 算法、控制参数或生成代码。

## 控制路径

- ADC3：V(20)+VBUS(160)+转换周期，完成后进 `isr_adc_bus()`；先清 ADC3 完成、fence、拷贝 V/VBUS，再调用 `board_control_tick()`。
- `board_control_tick()`：
  1. 检查 ADC2 `TRIG_COMPLETE`；未完成则只递增 `board_adc2_not_ready_count` 并返回，无忙等；
  2. 完成则清 ADC2、fence、拷贝 U/W；
  3. 调用 capture（仍取 ADC2/ADC3 DMA 原字）；
  4. 执行原有全部 20kHz 电流、编码器分频、过流、1kHz 位置/速度任务。
- ADC2 外部 IRQ **未 enable**；ADC2 peripheral 完成标志/队列/DMA 保持工作，仅由 ADC3 节拍轮询。
- ADC3 优先级保持 6；ADC2 的 `intc_m_enable_irq_with_priority` 已删除。ADC2/ADC3 必须都在本拍完成才执行控制；ADC2 未完成次数可由 `adcinfo` 只读打印。
- capture 字段名保留，但含义已更新：`seq2`=control tick 计数；`seq3`=ADC3 ISR 计数；`adcdump` header 已同步，避免再称 ADC2 ISR。

## 默认优化

- `embedded_project/HPM6E80/CMakeLists.txt:39` 加入 `sdk_compile_options("-O2")`，只影响本工程。
- 默认 `tools/build_hpm6e80.ps1` 构建 exit 0；`build-hpm6e80/compile_commands.json` 全部 **131** 个 C 单元有效最后 `-O2`；相关 Board/算法 **58** 个单元最后 `-O2`。
- 无 `-O0`、无 `-ffast-math`/`-Ofast`；仍为 `-mabi=ilp32f`、`-march=rv32imafc_zifencei_zba_zbb_zbc_zbs`，保留 debug 符号。
- 未修改 `tools/build_hpm6e80.ps1` 或共享 SDK。

## 产物

目录：`build-hpm6e80/diagnosis/dma_coherent/`

- `demo.elf`：1,678,380 B，SHA256 `2f3bbf9c4606fcb581ac02bd162fa571716002792f844cb232d59a770c635a76`
- `demo.bin`：180,960 B，SHA256 `0bbc79407184771061211df150cfe3d6a9320eade8bf548012b58b6f6778b8fc`
- `build.log`、`manifest.json`、`source_coherent.patch`、`source_git_diff.patch`
- `program_headers.txt`、`flash_ranges.txt`、`compile_flags_summary.txt`
- `pre_coherent_src/`：priority-O2 源码基线；`pre_default_o0/`：改前 O0 产物
- `source_coherent.patch` SHA256 `1be6729faa21bdc205bfccb1702f1bc7729c91ceca25ace0546f3419026d3027`
- Git diff SHA256 `fe2440c85d03ed1ee51ab2f434ea3ca6e70ab79a0a0eabb2f565f3cc4c8e2854`

默认 `build-hpm6e80/output` 现在是本同帧 -O2 版本。改前的 priority O0 产物保存在 `pre_default_o0/`，原哈希仍为 `5f136f46...` / `8d16c1ee...`。

## 资源与 Flash

| 区域 | 使用 | 容量 | 占比 |
|---|---:|---:|---:|
| FLASH | 181,436 B | 16 MB | 1.08% |
| AXI_SRAM | 98,960 B | 512 KB | 18.88% |
| ILM | 4,008 B | 256 KB | 1.53% |
| DLM | 32,768 B | 256 KB | 12.50% |
| AXI_SRAM_NONCACHEABLE | 1,408 B | 256 KB | 0.54% |

Flash PT_LOAD：

- `0x80000400..0x8000108F`，`0xC90`
- `0x80003000..0x80003057`，`0x58`
- `0x80003058..0x80003FFF`，`0xFA8`
- `0x80004000..0x8002C4BB`，`0x284BC`
- `0x8002C4C0..0x8002C6DF`，`0x220`

最高 Flash LMA 结束 `0x8002C6DF`，低于 `0x80100000`，全部落在已备份前 1MB 内。

## 边界

- 未串口/MCP/JTAG、未烧录、未提交。
- 未实机验证 ADC2-not-ready 计数、同帧控制、raw 噪声或 10RPM 速度；不能宣称本次改动必然消除 44~56mA 底噪或修复速度。
- O2 默认是本工程构建配置改变，可能影响时序；仍需 Codex 独立抓取与速度验收。
- 工作区仍保留 diagnostic + priority + 本轮 coherent 修改，未提交。
