# HPM6E80 当前工程入口（2026-11-13）

用户本次决定：保留完整 COM4 串口调试台和 MAVLink。CAN 只使用 J8/MCAN4，对标 Y01 `bsp_fdcan`；J9 先不启用。

## 构建和烧录

- 正常工程：`embedded_project/HPM6E80`，总线 `SERVO_BUS=CAN_CIA402` 或 `ETHERCAT`。
- 构建：`tools/build_hpm6e80.ps1 -Bus CAN_CIA402`；默认 EtherCAT。SDK 路径来自 `.vscode/settings.json`。
- 产物：`build-hpm6e80-can/output/demo.elf`、`build-hpm6e80/output/demo.elf`。
- 烧录：`tools/flash_hpm6e80.ps1 -Elf build-hpm6e80-can/output/demo.elf`。脚本依赖的串口 `dis` 和 DMI 恢复保留。
- 串口：COM4、921600 8N1，MAVLink 和串口调试台共用；`tools/serial_cmd.ps1 -Command st` 保留。
- J8：CANable COM10，SLCAN、1Mbps、默认 ID 0x015，总线权限下读写；见 [CAN_PORT.md](CAN_PORT.md)。
- 参数保存、分区、XIP安全及状态：见 [PARAM_STORAGE.md](PARAM_STORAGE.md)。

## 清理范围

已删除独立 CAN 回环、板上软件测试、存储测试三个固件目录及其构建目录；移除 `bsp_store.c` 中专用故障注入/人为损坏 Flash 入口；移除废弃 SRST/DMI 探测、临时 MAVLink 探测/改包及 MCP 操作脚本。`doc/validation` 原始历史数据已移出工程。

主机 CAN 测试源码已按用户要求删除。保留 MATLAB/Simulink 模型验证、原厂库及 Y01/SIL 工程，未按文件名含 test/debug 盲删。

删除前归档（含改动前文件、删除清单与SHA256）：`D:\Documents\ChatGPT\YeeZi\tmp\canable-help\cleanup-2026-11-13`。其中 `before/doc/validation` 为历史原始验证材料；`manifest.json` 列出文件。工程外还有本阶段真实参数存储验收日志，位置 `D:/Documents/ChatGPT/YeeZi/tmp/canable-help`。

Board/ 为硬件；Application/ 为本板应用适配，含完整串口调试台。接口分层检查：`tools/check_layer_boundary.ps1`。此次清理不修改正常通信或控制逻辑。用户随后明确授权烧录验证并提交、推送。

## 清理后实机验证（2026-11-13）

已烧录清理后的 CAN 固件，OpenOCD `Verified OK`，FlashDB 启动初始化成功。串口调试台完整保留；MAVLink 读取 AppControlWord(30054)、AppStatusInfo(30055)，响应 CRC 正确，控制字和错误字均为 0。

J8 将 0x605A 从原值 2 临时写为 3，执行保存并读到成功状态；重新烧录/启动后读回 3。随后恢复原值 2、保存、重启后再次读回 2。结束保持失能、PWM=0、err=0，未发送使能或运动目标。CAN/EtherCAT 两种 BIN 已核对与清理前相同，分层检查和差异格式检查通过。

证据：工程外 `D:/Documents/ChatGPT/YeeZi/tmp/canable-help/postcleanup-*.log`。这次为清理后正常 CAN 固件验收；EtherCAT 只构建，物理断电与电机运动未测试。
