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

- CAN 初始化成功后 `COMM_CONTROL_BUS`；失败置 `ERROR_COMMS_INIT` 并保持电机失能，不伪报成功。
- 节点 ID/波特率 setter 先校验（0..0x7FF、500k/1M），非法返回 `APP_PARAM_OUT_OF_RANGE`，不写数据库、不调用 BSP。
- `get_app_Can_*`/`bsp_get_can_*` 反映当前已生效值；requested 值由 CAN 状态诊断显示。启动时 main 读取 AppStoreInit 完成后的应用配置字段，再交给 CAN 初始化，避免 applied getter 覆盖恢复后的值；运行期间的变更使用 requested。
- 串口 ISR 只改 requested；实际 reinit 在前台 poll。普通重配需等待上一回复已排入 TX 且硬件 TX0 完成；`can reset` 是显式维护入口，可丢弃旧待发并重初始化。
- 重 init 前走 CiA402 Disable Voltage + APP 失能，Fault 不被清除；不强制改 `CurrentState`/不整栈复位。

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

1. 正常 CAN 主固件：`build-hpm6e80-can/output/demo.elf`，真实 J9 CAN7。
2. EtherCAT 主固件：`build-hpm6e80/output/demo.elf`，真实 ESC。
3. 纯软件测试：`build-hpm6e80-can-software-test/output/demo.elf`，使用生产 codec/adapter + stubs，不访问真实 CAN；另有 `tests/can_software` host CTest，本机无 native 编译器，未运行。
4. stage1 内部回环：`embedded_project/HPM6E80_CAN_LOOPBACK`，只验证 MCAN 内部环回，不等同外部收发。

## 已知边界

- FlashDB 当前为内存桩，参数掉电不持久化；不要依赖参数保存。
- 尚未上板/联调；本机没有 gcc/clang/cl，host CTest 未运行，交叉测试固件未烧录。测试固件里的 `TEST PASS` 只是将来串口输出；当前仅确认编译通过，不能当作运行通过。
- `flash_hpm6e80.ps1` 已支持 `-Elf`，CAN ELF 示例：
  `powershell -File tools/flash_hpm6e80.ps1 -Elf build-hpm6e80-can/output/demo.elf`
  该命令仅文档示例，本轮未执行。
- 后续实机清单：J9 终端电阻/收发器、1M/500k 波形、错帧/abort 不回复、busoff 恢复、AppCanBusDisconnection 超时、`can reset`。

## 无 USB 转 CAN 时的测试顺序

先构建纯软件测试，下载该测试 ELF 后通过板载调试串口观察 `TEST PASS/FAIL`：

```powershell
cmake -S embedded_project/HPM6E80_CAN_SOFTWARE_TEST -B build-hpm6e80-can-software-test -G Ninja -DBOARD=hpm6e00YZ -DHPM_BUILD_TYPE=flash_xip -DCMAKE_BUILD_TYPE=debug
cmake --build build-hpm6e80-can-software-test
```

再构建独立 MCAN 内部回环，下载对应 ELF 后观察 `CAN_LOOPBACK PASS/FAIL`：

```powershell
cmake -S embedded_project/HPM6E80_CAN_LOOPBACK -B build-hpm6e80-can-loopback -G Ninja -DBOARD=hpm6e00YZ -DHPM_BUILD_TYPE=flash_xip -DCMAKE_BUILD_TYPE=debug
cmake --build build-hpm6e80-can-loopback
```

两者都不要求 USB 转 CAN。前者使用依赖替身验证真实生产解析/调度代码；后者操作真实 MCAN 内部回环。当前两者都只做了编译，未在板上运行。

有原生 C 编译器的电脑也可执行主机软件测试：

```powershell
cmake -S tests/can_software -B build-hpm6e80-can-software-host -G Ninja
cmake --build build-hpm6e80-can-software-host
ctest --test-dir build-hpm6e80-can-software-host --output-on-failure
```

最后使用正常 CAN 主固件，与另一 CAN 节点或 USB 转 CAN 进行外部通信测试。`can` 查看状态，`can reset` 显式重初始化并失能；重初始化成功不代表已清除 CiA402 Fault，后续仍需正常故障复位/使能流程。
