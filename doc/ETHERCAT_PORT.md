# HPM6E80 EtherCAT 移植结构

## 总线选择

HPM6E80 主固件通过 CMake `SERVO_BUS` 选择：

- `ETHERCAT`：默认，`CONFIG_SERVO_ETHERCAT=1`，`MINOR_VERSION=3`。
- `CAN_CIA402`：另一条总线，`CONFIG_SERVO_CAN=1`，`MINOR_VERSION=0`。

旧的 `PORT_PATCH_ENABLE_ECAT` 已由上述正式开关替代，源码不再引用该宏。两条总线互斥，不能同时驱动同一 OD/FSA。

## 主干与硬件接口

- 保留 servo_hub 的 SSC、对象字典、PDO 回调和 CiA402 PDS 状态机。
- `Board/main.c` 初始化 HPM 内置 ESC、SSC，挂接 `pAPPL_EEPROM_Read/Write/Reload/Store`，生成 PDO 映射；主循环执行 `MainLoop()`。
- HPM 硬件访问、PHY、模拟 EEPROM 和中断开关使用 SDK `samples/ethercat/port`；SSC 管理 ESC 事件掩码和同步状态。
- EEPROM 命令由 `ECAT_Main()` 的 pending 处理进入 `EEPROM_CommandHandler()`，不再从主循环额外轮询或 PDI 中断重复分发。

## 电机控制与 DC

- 恢复 servo_hub 主干的固定分频：`CURRENT_FREQUENCY_HZ=20000`、`POSITION_FREQUENCY_HZ=1000`，每 20 个 20kHz 控制拍执行一次位置速度环。
- 位置速度环不由 SYNC0 标志触发，也没有 SYNC0 丢失后的额外回退分支；CiA402/故障处理不会因同步中断消失而停摆。
- SSC 的 `Sync0_Isr()`、PDO 同步、`DC_CheckWatchdog()` 和 AL 状态降级继续使用原协议路径。
- 电机固定周期控制与协议 DC 是两条独立路径，不表示电机环严格锁相 SYNC0；未修改控制频率或算法。

## 退出 OP

`APPL_StopOutputHandler()` 通过 `set_Controlword(0)` 发送 CiA402 Disable Voltage，然后显式失能并交还 HOST 控制权。故障恢复仍需正常 Fault Reset，不在 AL 回 INIT 时强改 `CurrentState` 或重新初始化整栈。

## 已移除的旁路

`ecat_port_compat.c` 已删除，不再包含 EEPROM 命令轮询、32 次循环、INIT 整栈重置、额外事件掩码、动态 IRQ 跟随、SYNC0 强开、自定义 SYNC0 节拍和周期统计。串口状态保留 AL/PDO/链路/看门狗与 SSC 的 DC 激活状态。

## 构建与验证边界

使用 `tools/build_hpm6e80.ps1`（默认 `-Bus ETHERCAT`）或配置 `embedded_project/HPM6E80` 后编译。SDK、工具链和 SDK Python 由 `cmake/hpm-project.cmake` 根据 `.vscode/settings.json` 统一选择。

当前验收为静态核对及编译链接；尚未验证实机状态转换、通信时序、断线停机时间或 Flash 写入对 DC 的影响。既有编译告警仍需另行处理。
