# HPM6E80 CAN（V_CAN_CIA402）说明

## 总线选择

`embedded_project/HPM6E80` 通过 CMake `SERVO_BUS` 选择主固件总线：

- `ETHERCAT`：默认，保留原 EtherCAT SSC/CiA402/PDO/DC 路径。次版本号 3。
- `CAN_CIA402`：J8/MCAN4，CiA402 主路径。次版本号 0。当前使用的固件。
- `CAN_ENCOS`：次版本号 1。原工程 `fdcan_encos_handle` 是空函数，这里同样收到帧后直接返回。
- `CANOPEN_CIA402`：次版本号 2。CanFestival 从站，NMT/SYNC 过滤器和节点号掩码，GPTMR2 通道 1 做 1 µs 节拍。SYNC `0x080` 置目标更新。
- `CANFD_CUSTOM`：次版本号 4。把收到的经典帧或 CAN FD 帧按本节点号回发，保留扩展帧和速率切换。

J9 不初始化。`SERVO_CAN_PASSTHROUGH=ON` 时再打开 Y01 的 MAVLink CAN FD 透传：扩展帧进 FIFO1，速率切换关闭的帧交给 `MavlinkRecvCallback`，上位机发送改走 CAN FD 分包。默认关闭。

`USE_CIA402` 由 `version.h` 产生。CiA402 和 CANopen 会带上对象字典与 1 kHz PDS_FSA。不同 `SERVO_BUS` 不能同时编进一个固件。

## 硬件

当前只有一路 CAN，对标 Y01 `bsp_fdcan`，接在 J8。

- J8 = MCAN4：PC16 TXD、PC17 RXD、PC18 STBY；U12 TJA1042T/3。STBY 高为待机、低为正常。
- 端子为 2Pin：pin2=CANH，pin1=CANL；无 GND 脚，需另接公共地。
- 板载固定分裂端接 R144/R146 各 60.4Ω、C129 10nF，无跳线。
- J9 = MCAN7（PC31/PC30/PC29，U13）先不初始化。等这一路调通后再考虑是否拆成第二路。
- 默认节点 ID `0x15`，默认 1 Mbps；初始化只接受 500 kbps 和 1 Mbps。节点 ID 改完下一帧就用；波特率只保存，下次上电才写入位时间。
- 位时间与 Y01 在 80 MHz 下的配置相同。1 Mbps：分频 4、SEG1 14、SEG2 5、SJW 2。500 kbps：分频 10、SEG1 13、SEG2 2、SJW 2。
- 控制器为 CAN FD、关闭速率切换，对应 Y01 的 `FDCAN_FRAME_FD_NO_BRS`。CiA402 回复仍是 8 字节经典标准帧，走 TX FIFO。

## 协议（主机侧）

经典 CAN 标准帧；请求总长只接受 5、6、8：

```
[op, index_lo, index_hi, subindex, value_le(1/2/4 bytes)]
op=0 读，op=1 写
```

示例：

- 读 0x6041.0：`00 41 60 00 00`
- 写 0x6040.0 = 0x000F：`01 40 60 00 0F`
- 写 0x6060.0 = 3（速度模式）：`01 60 60 00 03`
- 写 0x607A.0 = 0x00000180：`01 7A 60 00 80 01 00 00`

成功回复固定 8 字节：

```
[op, index_lo, index_hi, subindex, value_le32]
```

与 Y01 `fdcan_cia402_handle` 一致：回调返回值不改变回复，读和写之后都发 8 字节。帧长按字节数判断（5、6、8 对应值长 1、2、4）。MCAN 先把 DLC 换成字节数，不沿用 STM32 HAL 里把 DLC 编码直接拿来减的写法。

使能需按当前 CiA402 状态发送 `0x0006 → 0x0007 → 0x000F` 并读取状态字确认；上面的单条 `0x000F` 仅为编码示例。

## 权限、参数与故障

- CAN 主固件不把通信权限改成 HOST，保持参数初始化后的 `COMM_CONTROL_BUS`。写对象在权限为 HOST 时拒绝，与 Y01 `fdcan_cia402_handle` 相同。J8 初始化失败进入通信初始化故障；掉线检测只在权限为 BUS 且这一路已就绪时累计。
- `set_app_Can_id` / `set_app_Can_baudrate` 与 Y01 一样先保存。节点 ID 马上参与过滤；波特率留到下次 `bsp_can_init`。不是 500 kbps 或 1 Mbps 时，初始化失败，不改当前控制器。
- 收到本节点标准帧后在 MCAN 接收中断里解析并放入 TX FIFO。FIFO 满则这一帧回复丢掉，不再次调用对象字典回调。
- 所有 PDS 转移统一在 1kHz 上下文，通信只入队。四槽环形队列可容纳三个请求，满时拒绝且不更改生效控制字。成功入队不等于已完成状态转换，应读状态字确认。

## 构建

```powershell
# 默认 EtherCAT
cmake -S embedded_project/HPM6E80 -B build-hpm6e80 -G Ninja `
  -DBOARD=hpm6e00YZ -DSERVO_BUS=ETHERCAT -DHPM_BUILD_TYPE=flash_xip -DCMAKE_BUILD_TYPE=debug
cmake --build build-hpm6e80

# CAN 主固件
cmake -S embedded_project/HPM6E80 -B build-hpm6e80-can -G Ninja `
  -DBOARD=hpm6e00YZ -DSERVO_BUS=CAN_CIA402 -DHPM_BUILD_TYPE=flash_xip -DCMAKE_BUILD_TYPE=debug
cmake --build build-hpm6e80-can
```

`tools/build_hpm6e80.ps1 -Bus CAN_CIA402` 使用 `build-hpm6e80-can`。`-Bus` 还可以是 `CAN_ENCOS`、`CANOPEN_CIA402`、`CANFD_CUSTOM`，目录分别是 `build-hpm6e80-encos`、`build-hpm6e80-canopen`、`build-hpm6e80-canfd`。加上 `-CanPassthrough` 打开 MAVLink 透传。默认 `-Bus ETHERCAT` 仍为 `build-hpm6e80`。

## 正式固件

1. 正常 CAN 主固件：`build-hpm6e80-can/output/demo.elf`，只使用 J8/CAN4。
2. EtherCAT 主固件：`build-hpm6e80/output/demo.elf`，真实 ESC。

已验收的一次性板上软件测试、内部回环固件及主机测试源码已于 2026-11-13 按用户要求清理。历史板上测试与日志保存在工程外的清理归档。

## 已知边界

- FlashDB 已接真实 NOR；保存协议、失能限制与恢复行为见 [PARAM_STORAGE.md](PARAM_STORAGE.md)。
- 2026-11-13：本轮交叉软件测试固件已上板输出 `TEST PASS`（真实 FSM/codec/adapter + 硬件替身），随后恢复正常 CAN 固件。主机 CTest 因无原生编译器未运行。J8 实测读取/原值写回 0x605A、拒绝非法模式2及非零标量子索引，模式不变且 pwm=0；不等于 J9 外部运动/异常联调通过。
- `flash_hpm6e80.ps1` 已支持 `-Elf`，CAN ELF 示例：
  `powershell -File tools/flash_hpm6e80.ps1 -Elf build-hpm6e80-can/output/demo.elf`
  本轮已用该脚本下载软件测试及恢复正常 CAN 固件，均校验通过。
- 后续实机清单：J8 终端电阻/收发器、1M/500k 波形、错帧/abort 不回复、busoff 恢复、AppCanBusDisconnection 超时、`can reset`。J9 等这一路调通后再接。

## 后续实机验证

最后使用正常 CAN 主固件，与另一 CAN 节点或 USB 转 CAN 进行外部通信测试。`can` 查看状态，`can reset` 显式重初始化并失能；重初始化成功不代表已清除 CiA402 Fault，后续仍需正常故障复位/使能流程。

参数保存与异步完成状态见 [PARAM_STORAGE.md](PARAM_STORAGE.md)：总线权限下由 J8 写 0x1010:01=`save`，再读 0x2000:00，状态 2 才表示保存完成。

清理记录：2026-11-13 保留完整 COM4 串口调试台、MAVLink、J8/CAN4 与 J9/CAN7 适配；删除独立测试固件/构建目录和一次性探测脚本。归档位置见 `doc/HANDOFF.md`。
