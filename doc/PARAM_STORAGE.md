# HPM6E80 参数存储

HPM6EMotorV20 当前实板 ROM 探测为 4MiB NOR、4KiB 扇区、256B 页。SDK 板包声明的 16MiB 不能作为实板容量依据。初始化会检查真实容量和几何参数，不符则报错。

| 区域（XPI0 偏移） | 用途 |
|---|---|
| 0..0x1FFFFF | 启动头与程序；CMake 生成的本工程链接脚本硬限制为前 2MiB |
| 0x200000..0x20FFFF | 既有 EtherCAT SII 模拟 EEPROM |
| 0x210000..0x23FFFF | 保留，实板在 0x210000/0x211000 有历史标定记录，不改写 |
| 0x240000..0x27FFFF | 本工程独占 FlashDB KV，256KiB，64 个扇区 |
| 0x280000..实际 Flash 末尾 | 保留，不由参数存储使用 |

FlashDB/FAL 复用 board_public/flash_db；硬件端口在 Board/bsp_store.c、fal_cfg.h。ROM 擦写调用及配置入口在 ILM，数据源复制到对齐 RAM；操作期间保存/关闭/恢复中断，完成后失效目标数据缓存。不要改成从 XIP 执行裸擦写，也不要把分区移到末尾猜空闲区。

HPM6E80 上 `main` 的 `while(1)` 调用 `Application/servo_storage.c` 里的 `servo_storage_poll`，不放进 1 ms 定时器中断。到服务时间后，桥臂已打开、控制字不是失能、或电机使能请求还在时，这次命令被丢掉并写 `FLASH_STORE_STATUS_WARNING`；否则调用 `AppStoreUpdata1ms`。间隔按 CPU 周期计数，主循环被堵住时不会按严格 1 ms 触发。擦写期间 `bsp_flashdb_write` 仍关闭中断；桥臂已打开时驱动直接返回失败。电机已使能时，`set_app_Sys_cmd` 也会拒绝保存并写 `FLASH_STORE_STATUS_WARNING`。Y01 仍在 `UnrealTimeBase1ms` 里调用。

三个正式键仍为 AllParam、ErrorRecord、TqFcTable。每个 blob 增加 SPV1 魔数、schema=1、精确长度，FlashDB 提供 CRC 与写入提交/恢复状态。读取先检查 CRC、已提交状态和布局，再复制到注册缓冲区；不把截断或部分数据应用到运行参数。最大单键有效载荷 3072B，超过则注册失败。更改持久结构时必须升级 schema 并决定迁移方案，不能只因为长度相同就认定兼容。

缺键（首次使用或删除后）保留已初始化的 RAM 默认值，不假报已读取。擦写/初始化失败进入 ERROR_FLASH_STORE 与失败状态。检测到不识别的扇区布局拒绝初始化，保留原数据；已识别 FlashDB 区域按库的状态恢复。CRC 损坏值不应用，复位扫描后被库丢弃的键回默认值。多键工厂恢复不是跨键事务；不承诺任意掉电时机下所有键同时更新。

标定数据的影子表示、魔数和校验属于 app/app_store_param.c 的 USER CODE；硬件仅验证/安装 ADC 零漂。电角度识别把结果交给 AppStoreElecBias。参数快照保留标定字段，SysCmd=2 时随 AllParam 保存。重新生成数据映射时应保留 USER CODE，并保持 flash_param_update 不清空标定元数据。旧硬编码的首次快照清零逻辑已经删除。

## J8 保存

继续使用标准 ID 0x015、1Mbps、原有应用 CAN 帧格式，走 J8 这一路总线。新增 0x1010:01，32 位写入 ASCII `save`，即值 0x65766173。通信权限为 BUS 时可以写；权限为 HOST 时与其它对象一样拒绝。写入回包表示请求已接受，必须再读取 0x2000:00 的 Storage_status，2 才表示本次完成成功；0=待执行，1=忙，-1=失败，-2=当前不允许，-3=频率保护。重复未完成请求被拒绝，坏签名/子索引被拒绝。0x1010:00 和 :01 读回 1，表示一个保存子项与命令保存能力。

SLCAN 示例（每行末尾 CR）：
```
t01580110100173617665
t01550000200000
```
成功状态回复 `t01580000200002000000`。不通过 J8 新增工厂清除或运动动作。EtherCAT 的 SDO 对象表未新增上述 CAN 扩展，原 MAVLink SysCmd=2 继续可用。

## 职责与验收

Board/ 放芯片/外设驱动和通用 BSP 实现；Application/ 放 servo_can/host/console/bringup/storage 应用适配及 BSP 的 CAN 兼容桥。main.c 为组合根。边界脚本只允许适配目录跨两侧，硬件目录继续检查直接依赖；没有通过间接头隐藏 app_store_param 或 data_param。

历史验收使用无电机初始化的专用存储固件和同一真实 NOR/FlashDB，测试键在结束时删除。该一次性测试固件及生产源码中的故障注入入口已按用户要求从工程清理，源文件和证据归档于工程外。覆盖真实软件复位恢复、PWM 活动拒绝、非法索引、写调用边界失败注入、重开恢复、超过分区容量的更新/GC、长度不兼容、CRC 损坏拒绝、删除后重写。失败注入模拟中断写入，不等同于物理断电试验。

正常 CAN 固件通过 J8 把 0x605A 从原值 2 临时改为 3，保存、重新烧录/启动后读回 3；再将原值 2 保存并重启确认。未使能电机。证据路径 D:/Documents/ChatGPT/YeeZi/tmp/canable-help/store-*.log。硬件供电完全断开再上电、EtherCAT 在线 SDO 与运动工况不在本次实测范围。

本地 FlashDB 补丁：move_kv 的准备、读、写、提交和删除均检查返回值，任一步失败保留源记录；do_gc 在搬移/格式化失败时立即停止，禁止继续擦源扇区。NOR 端口首次 I/O 失败后阻止后续写/擦并使数据库失效，复位后重新扫描恢复，不能仅再调用 init 沿用旧缓存。该问题在有写入历史的实板故障注入中复现，修复后 12 边界中 8 次真实失败返回均恢复到完整旧值或新值，并检查另一独立键保持不变。

2026-11-13 清理后，正常存储端口不再包含 `SERVO_STORAGE_TEST` 分支或人为损坏 Flash 的测试入口；CRC、长度校验、失败锁定和 GC 修复完整保留。串口调试台及 MAVLink 通道保留。
