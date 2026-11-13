# HPM6E80 CAN（V_CAN_CIA402）说明

## 总线选择

`embedded_project/HPM6E80` 通过 CMake `SERVO_BUS` 选择主固件总线：

- `ETHERCAT`：默认，保留原 EtherCAT SSC/CiA402/PDO/DC 路径。
- `CAN_CIA402`：CAN7 + 经典 CAN CiA402 主路径，不编译 EtherCAT SSC/ESC port/eeprom。

`MINOR_VERSION` 由 CMake 设为 3（ETHERCAT）或 0（CAN_CIA402）；`USE_CIA402` 由 `version.h` 产生，OD 与 1kHz PDS_FSA 两条总线共用。两条总线不能同时驱动同一 OD/FSA。

## 硬件

- CAN7 = J9：PC31 TXD、PC30 RXD、PC29 STBY。
- TJA1042T/3：STBY 高为待机、低为正常；enable 时输出低（active-low）。板上 STBY 经 10k 下拉。
- 默认节点 ID `0x15`（11 位范围 0..0x7FF），默认 1 Mbps；可选 500 kbps。
- 内部回环工程不初始化 J9 引脚/收发器；正常主固件才初始化。

### J8 调试口（默认 HOST 读写）

- **J8 = CAN4**：PC16 TXD、PC17 RXD、PC18 STBY；U12 TJA1042T/3，STBY 高待机、低正常。
- 端子为 2Pin：pin2=CANH，pin1=CANL；无 GND 脚，需另接公共地。
- 板载固定分裂端接 R144/R146 各 60.4Ω、C129 10nF，无跳线；J9 同样有 R141/R142。
- 两端各 120Ω 时并联约 60Ω 属正常，不要只保留一端。
- 固定经典 CAN 标准帧、1 Mbps、ID `0x015`，与 J9 独立总线；参数不与 J9 运行期配置耦合。
- 接受 `DLC 5/6/8`，`op=0` 读、`op=1` 写；其余操作码拒绝。读不要求控制权，J8 写要求 HOST 权限，J9 写要求 BUS 权限。
- 复用 `can_cia402` 读写格式：读 0x6041 发 `00 41 60 00 00`，回复固定 8 字节 `00 41 60 00 + value_le32`。
- cangaroo：1 Mbps、标准帧；发送上述 5 字节，接收同 ID 8 字节。
- 控制台 `dcan` 只读显示 J8 状态（ready/实例/ID/位率/rx/tx/invalid/wrej/abort/txerr/ovf/boff）；`can` 仍只显示 J9。
- 当前以 J8 为主；J9 保留原有代码，后续再设计其功能和参数。写成功回显原请求和值；拒绝无成功回包，记录 abort/wrej。

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

与原 Y01 `drv_can_app.c:253-330` 的成功行为一致。差异：原实现忽略 callback abort；本实现 callback 非 0 时**不回复**，记录 `abort_count/last_abort`，不发明 CANopen 错误帧。

使能需按当前 CiA402 状态发送 `0x0006 → 0x0007 → 0x000F` 并读取状态字确认；上面的单条 `0x000F` 仅为编码示例。

## 权限、参数与故障

- CAN 主固件启动默认 `COMM_CONTROL_HOST`，J9 初始化成功不抢控制权。当前活动源（HOST=J8、BUS=J9）初始化失败进入应用通信故障链；硬件恢复不代替正常 Fault Reset。非活动 J9 不触发 HOST 掉线失能。
- 节点 ID/波特率 setter 先校验（0..0x7FF、500k/1M），非法返回 `APP_PARAM_OUT_OF_RANGE`，不写数据库、不调用 BSP。
- `get_app_Can_*`/`bsp_get_can_*` 反映当前已生效值；requested 值由 CAN 状态诊断显示。启动时 main 读取 AppStoreInit 完成后的应用配置字段，再交给 CAN 初始化，避免 applied getter 覆盖恢复后的值；运行期间的变更使用 requested。
- 串口 ISR 只改 requested；实际 reinit 在前台 poll。普通重配需等待上一回复已排入 TX 且硬件 TX0 完成；`can reset` 是显式维护入口，可丢弃旧待发并重初始化。
- 重 init 请求安全停机并立即 APP 失能；Fault 不被清除。所有 PDS 转移统一在 1kHz 上下文，通信只入队。四槽环形队列可容纳三个请求，满时拒绝且不更改生效控制字。成功入队不等于已完成状态转换，应读状态字确认。

## 帧预算与忙处理

- 每 `servo_can_poll` 最多消费 8 帧，保持主循环响应。
- 非本节点/扩展帧丢弃并计 `invalid`。
- 回复排队到 TX0；忙时保留一条待发回复，不重新调用 OD 写回调，不建软件队列。
- `bsp_can_send` 成功只表示排入 TX buffer；硬件完成由 `bsp_can_tx_pending()` 观察。
- overflow/busoff/rx/tx/invalid/abort/last_abort 通过 `servo_can_get_status` 暴露。

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

`tools/build_hpm6e80.ps1 -Bus CAN_CIA402` 使用 `build-hpm6e80-can`；默认 `-Bus ETHERCAT` 仍为 `build-hpm6e80`。

## 四种产物

1. 正常 CAN 主固件：`build-hpm6e80-can/output/demo.elf`，J8/CAN4 HOST 读写及保留的 J9/CAN7 路径。
2. EtherCAT 主固件：`build-hpm6e80/output/demo.elf`，真实 ESC。
已验收的一次性板上软件测试与内部回环固件已于 2026-11-13 清理。主机回归源码仍保留在 `tests/can_software`，用于复查故障复位、队列和协议规则，不链接到正常固件。历史板上测试与日志保存在工程外的清理归档。

## 已知边界

- FlashDB 已接真实 NOR；保存协议、失能限制与恢复行为见 [PARAM_STORAGE.md](PARAM_STORAGE.md)。
- 2026-11-13：本轮交叉软件测试固件已上板输出 `TEST PASS`（真实 FSM/codec/adapter + 硬件替身），随后恢复正常 CAN 固件。主机 CTest 因无原生编译器未运行。J8 实测读取/原值写回 0x605A、拒绝非法模式2及非零标量子索引，模式不变且 pwm=0；不等于 J9 外部运动/异常联调通过。
- `flash_hpm6e80.ps1` 已支持 `-Elf`，CAN ELF 示例：
  `powershell -File tools/flash_hpm6e80.ps1 -Elf build-hpm6e80-can/output/demo.elf`
  本轮已用该脚本下载软件测试及恢复正常 CAN 固件，均校验通过。
- 后续实机清单：J9 终端电阻/收发器、1M/500k 波形、错帧/abort 不回复、busoff 恢复、AppCanBusDisconnection 超时、`can reset`。

## 主机回归测试

有原生 C 编译器的电脑也可执行主机软件测试：

```powershell
cmake -S tests/can_software -B build-hpm6e80-can-software-host -G Ninja
cmake --build build-hpm6e80-can-software-host
ctest --test-dir build-hpm6e80-can-software-host --output-on-failure
```

最后使用正常 CAN 主固件，与另一 CAN 节点或 USB 转 CAN 进行外部通信测试。`can` 查看状态，`can reset` 显式重初始化并失能；重初始化成功不代表已清除 CiA402 Fault，后续仍需正常故障复位/使能流程。

参数保存与异步完成状态见 [PARAM_STORAGE.md](PARAM_STORAGE.md)：J8/HOST 写 0x1010:01=`save`，再读 0x2000:00，状态 2 才表示保存完成。

清理记录：2026-11-13 保留完整 COM4 串口调试台、MAVLink、J8/CAN4 与 J9/CAN7 适配；删除独立测试固件/构建目录和一次性探测脚本。归档位置见 `doc/HANDOFF.md`。
