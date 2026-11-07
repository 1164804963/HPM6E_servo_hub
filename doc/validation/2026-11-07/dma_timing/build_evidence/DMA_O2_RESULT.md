# -O2 单变量构建对照结果

状态：**构建通过；未实机验证**。仅在相同当前源码（priority 修正 + diagnostic）上改变优化级别，未改 ADC/IRQ/1k 任务/控制参数/算法，未提交。

## 构建配置

构建目录：`build-hpm6e80/diagnosis/build-o2`

```text
cmake -S embedded_project/HPM6E80 -B build-hpm6e80/diagnosis/build-o2 -G Ninja
  -DBOARD=hpm6e00YZ -DHPM_BUILD_TYPE=flash_xip -DCMAKE_BUILD_TYPE=debug
  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_C_FLAGS=-O2
```

- 项目语言核对：C 编译单元 130 个（另有 `start.S`），C++ 编译单元 **0** 个；不需要 CXX flags。
- 相关 `Board`/`motor_control`/`simulink_code_gen`/`app` C 文件共 58 个，**有效最后 `-O` 全部为 `-O2`**。
- 全部 C 编译单元最后 `-O` 为 `-O2`；唯一无 `-O` 的是 SDK `start.S` 汇编，不属于 C 源码。
- 未见 `-O0`、`-ffast-math`、`-Ofast`；`-mabi=ilp32f`、`-march=rv32imafc_zifencei_zba_zbb_zbc_zbs` 与 O0 版本相同。

完整日志：`build-hpm6e80/diagnosis/dma_o2/build.log`
配置命令：`build-hpm6e80/diagnosis/dma_o2/configuration_command.txt`
编译参数证据：`build-hpm6e80/diagnosis/dma_o2/compile_flags_summary.txt`；原始 `build-hpm6e80/diagnosis/build-o2/compile_commands.json`。

## 产物

目录：`build-hpm6e80/diagnosis/dma_o2/`

- `demo.elf`：1,679,080 B，SHA256 `a431866058e2b8b3010e0686ad1bda343f821a8004b823a824dcc908a4bf50a9`
- `demo.bin`：180,928 B，SHA256 `79cabd0894e4f997b785c3f620fe5cc799597f6ed64acad63f62635ffdefafb9`
- `manifest.json`：包含源 Git diff hash、源文件 hash、优化参数、Flash/内存、产物 hash
- `source_git_diff.patch`：当前 tracked diff 快照（诊断+priority，不是新提交）
- `program_headers.txt`、`flash_ranges.txt`
- `make_manifest.py`：生成 manifest 的本地脚本

当前 `build-hpm6e80/output` 的 priority O0 产物未被覆盖：

- ELF `5f136f46a1f76b91087a88b6ccbdb8bb3e6c82950f4b00e4d5fb80451ba82c4e`
- BIN `8d16c1ee4e499a485197570231d28863382a5a8beb80fdc3316f92d0ba727d5f`

## 资源与 Flash

| 区域 | 使用 | 容量 | 占比 |
|---|---:|---:|---:|
| FLASH | 181,404 B | 16 MB | 1.08% |
| AXI_SRAM | 98,960 B | 512 KB | 18.88% |
| ILM | 4,008 B | 256 KB | 1.53% |
| DLM | 32,768 B | 256 KB | 12.50% |
| AXI_SRAM_NONCACHEABLE | 1,408 B | 256 KB | 0.54% |

Flash PT_LOAD：

- `0x80000400..0x8000108F`，`0xC90`
- `0x80003000..0x80003057`，`0x58`
- `0x80003058..0x80003FFF`，`0xFA8`
- `0x80004000..0x8002C49B`，`0x2849C`
- `0x8002C4A0..0x8002C6BF`，`0x220`

最高 Flash LMA 结束地址 **0x8002C6BF**，低于 `0x80100000`，全部落在已备份前 1MB 内。

## 源与哈希

- Git HEAD：`37d80417f37d8f62dd60a61a7e91750dcb9a9060`
- 当前 tracked `git diff --binary` SHA256：`7b08226cbcdbe96711eb828851baaedc1f102482a3e06da30ee178649f2769ef`
- `board.c`：`825e4c8919ecf8bb07bbb6104d291e53c4e2ca6a5737a16d03710f9ad3249630`
- `servo_console.c`：`aa374a239c4debce84efdbbf73a7212cbab1d17ea24cea65285135175fe182f0`
- `servo_console.h`：`7d0b094a946c1278b49e949269b04ffcc5aaa24150f2796e7ad07dd5165d6786`

## 边界

- 这是 O2 构建对照，不证明 O2 会修复 1kHz 分支造成的 deadline，也不证明会消除 41~56mA raw 底噪；需由 Codex 烧写后独立实测。
- 当前 `build-hpm6e80/output` 仍是 priority O0；O2 产物只放在 `diagnosis/dma_o2`，避免误烧。
- 未修改 `tools/build_hpm6e80.ps1`，未永久改优化级别。
- 未串口/MCP/JTAG，未烧录，未提交；工作区仍保留上一阶段 diagnostic + priority 的 3 个 Board 文件修改。
