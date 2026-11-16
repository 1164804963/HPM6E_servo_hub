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

## 参数保存入口

先与母体保持一致，撤回前期新增的普通CAN 0x1010保存和0x2000状态对象。普通CAN未知对象仍按母体形成回包，不能凭回包判断存在或保存成功。旧t415等示例与上述扩展已不适用。

参数保存使用原MAVLink AppBaseConfig等参数写入和SystemCmd.Sys_cmd=2，通过SystemStatus.Storage_status确认结果；命令常量APP_SYSTEM_CMD_SAVE_CONFIG及字段映射为准。保留原串口console。HPM前台服务提交时清旧完成状态，只对BOARD_SERVO_HPM6E80生效；电机使能时仍拒绝保存。不新增工厂擦除或运动测试。

## 职责与验收

Board/ 放芯片/外设驱动和通用 BSP 实现；Application/ 放 servo_can/host/console/bringup/storage 应用适配及 BSP 的 CAN 兼容桥。main.c 为组合根。边界脚本只允许适配目录跨两侧，硬件目录继续检查直接依赖；没有通过间接头隐藏 app_store_param 或 data_param。

历史验收使用无电机初始化的专用存储固件和同一真实 NOR/FlashDB，测试键在结束时删除。该一次性测试固件及生产源码中的故障注入入口已按用户要求从工程清理，源文件和证据归档于工程外。覆盖真实软件复位恢复、PWM 活动拒绝、非法索引、写调用边界失败注入、重开恢复、超过分区容量的更新/GC、长度不兼容、CRC 损坏拒绝、删除后重写。失败注入模拟中断写入，不等同于物理断电试验。

正常 CAN 固件通过 J8 把 0x605A 从原值 2 临时改为 3，保存、重新烧录/启动后读回 3；再将原值 2 保存并重启确认。未使能电机。证据路径 D:/Documents/ChatGPT/YeeZi/tmp/canable-help/store-*.log。硬件供电完全断开再上电、EtherCAT 在线 SDO 与运动工况不在本次实测范围。

2026-11-15对齐更新：FlashDB的move_kv/do_gc通用错误处理补丁已撤回，库文件与servo_hub-master相同。上文历史故障注入验证属于当时带修复版本，不代表当前库拥有同样失败恢复保证。原生风险是GC搬移失败后仍可能删除源记录或擦源扇区；记录后待优化，不在本阶段注入失败或进行断电试验。NOR端口的I/O失败锁定、布局/CRC/长度检查和失能限制仍保留，但不能等同于库GC保护。
