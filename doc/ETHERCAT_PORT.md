# HPM6E80 EtherCAT 当前移植结构

本文说明当前实现。`PORTING_PATCHES.md` 中涉及 EtherCAT 的轮询、整栈重置、中断覆盖和 SYNC0 电机环触发属于历史联调记录。

## 主干与硬件接口

- 保留 servo_hub 的 SSC、对象字典、PDO 回调与 CiA402 PDS 状态机。
- `Board/main.c` 初始化 HPM 内置 ESC、SSC，挂接 `pAPPL_EEPROM_Read/Write/Reload/Store`，生成 PDO 映射；主循环执行 `MainLoop()`。
- HPM 硬件访问、PHY、模拟 EEPROM 和 MCU 中断开关使用 SDK 的 `samples/ethercat/port`，SSC 管理 ESC 事件掩码和同步状态。
- EEPROM 命令由 `ECAT_Main()` 的正常 pending 处理进入 `EEPROM_CommandHandler()`，不再从主循环额外循环或 PDI 中断重复分发。

## 电机控制节拍与 DC

- 恢复 servo_hub 主干的固定分频调度方式；HPM 保留现有 `CURRENT_FREQUENCY_HZ=20000`、`POSITION_FREQUENCY_HZ=1000`，每 20 个有效 ADC 控制拍执行一次位置速度环。
- 原 Y01 默认位置环参数为 10000 Hz；本次未将其参数照搬至 HPM，也未修改 HPM 控制算法或频率配置。
- 位置速度环不再由 SYNC0 标志触发，也没有丢 SYNC0 后的额外回退分支，因此 CiA402 和故障处理不会随同步中断消失而停摆。
- SSC 的 `Sync0_Isr()`、PDO 同步、`DC_CheckWatchdog()` 和 AL 状态降级继续使用原协议路径。电机固定周期控制与协议 DC 是两条独立路径，不代表电机环严格锁相 SYNC0。

## 退出 OP

`APPL_StopOutputHandler()` 通过 `set_Controlword(0)` 发送 CiA402 Disable Voltage，然后显式失能并交还 HOST 控制权。故障恢复仍需正常 Fault Reset，不在 AL 回 INIT 时强改 `CurrentState` 或重新初始化整栈。

## 已移除的旁路

`ecat_port_compat.c` 已删除，不再包含 EEPROM 命令轮询、32 次循环、INIT 整栈重置、额外事件掩码、动态 IRQ 跟随、SYNC0 强开、自定义 SYNC0 节拍和周期统计。串口状态保留 AL/PDO/链路/看门狗与 SSC 的 DC 激活状态。

## 构建与验证边界

首次检出时，将 `.vscode/settings.example.json` 复制为 `.vscode/settings.json`，按本机修改 SDK 路径和工具链名称。实际 `settings.json` 为本机配置，按仓库规则不提交。

使用 `tools/build_hpm6e80.ps1`，或配置 `embedded_project/HPM6E80` 后编译。SDK、工具链和 SDK Python 由 `cmake/hpm-project.cmake` 根据 `.vscode/settings.json` 统一选择。

当前验收为静态核对及编译链接。尚未验证实机状态转换、通信时序、断线停机时间或 Flash 写入对 DC 的影响；现有编译警告仍需另行处理。
