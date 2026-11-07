# ServoHub 联调记录（2026-11-07，阶段1）

结论：已接通上位机 MCP 和 COM4，确认基本通信、零目标使能/失能及参数写入回读链路可用。低速跟踪尚未通过验收；不能认定上下位机所有功能正常。本阶段未修改下位机源码、未烧录，不把编译成功等同于板上运行正常。

## 对象与 Git

- 工程：D:\Documents\SoftwareProject\YeeZi_HPM6E\MyProject\HPM6E_servo_hub_dsh。
- 首个基线提交：65180f6，1036 个文件；保留已有源码及必需库，忽略 build-hpm6e80、Python缓存及 .env 文件，未配置远程或推送。
- 上位机：D:\servohub_pc_monitor-v3.0.3\pc_monitor.exe；MCP serverInfo=servohub-pc-monitor 1.0.0，19 个工具，使用用户提供的 stdio 桥接到 127.0.0.1:8848。本次是脚本客户端实际接入，未修改 Codex 全局 MCP 配置。
- 用户确认：电机空载、台架固定、已供电，电源限流2A，COM4。上位机实际串口921600、8N1；HOST/CTRL内部控制调试模式。
- 实测对象是板上原有固件；新编译产物未烧录，未建立板上二进制与基线源码的哈希一致性。

## 验证结果

| 项目 | 结果和证据 |
| --- | --- |
| MCP握手和工具目录 | 通过，initialize及tools/list真实返回 |
| COM4连接及心跳 | 通过，上位机自身COM4连接按钮接通，心跳正常，解析错误计数0 |
| 参数写入及回读 | 通过，30019回包确认iq_max_A=0.1、acc_tar_p_ss=2730、speed_tar_p_s=0；连续设置同消息字段时曾被旧值覆盖，改为逐项提交和回读 |
| 零目标使能/失能 | 协议链路通过，30023/30024回报使能1再失能0，错误/警告均0；这不证明零速闭环稳定性 |
| 约5RPM短时正向目标 | 未通过跟踪验收，1365.33P/s、16384计数/圈、iq上限0.1A、加速度2730P/s²；目标被回读确认，但速度显示约-178~-203RPM，位置在24098900附近往复波动约百余计数，力矩指令+0.1A限幅 |
| 归零目标及自动失能 | 通过，30019确认目标0，30023确认失能0，30024最终state0/error0/warning0/mode2 |
| 测试参数恢复 | 通过，30019最终回读iq_max_A=1、acc_tar_p_ss=0、speed_tar_p_s=0，均与测试前一致；未保存Flash |
| 内部模式选择（0/1/2/3/4/5/6/127） | 8种配置写入/读回均通过，30022依次回报0/1/2/3/4/5/6/127，结束恢复2；全程失能。30024的mode_now在失能期间仍为上次运行模式2；不能代替各模式运动验证 |
| 力矩/位置/往复/参考信号/MIT/电压实际运动 | 未测，先解决低速试验异常 |
| 应用层PT/PV/PP/MIT/回零及暂停/急停/清错 | 未测，不把内部模式测试套用于应用层；普通失能不能代替急停验证 |
| 目标/增益/电流环/观测器/滤波/补偿/表格导入导出 | 除上述三个临时参数外未逐项验证，不宣称全部正常 |
| 限位/回零开关/故障注入/断线停机 | 未实测；不通过拔线或提高电流触发未知故障 |
| 参数保存与重启保持 | 实测未做；源码确认当前HPM板级是RAM存储桩，不具备Flash持久化 |
| 架构边界检查 | tools/check_layer_boundary.ps1通过；提示部分新bsp接口仍需同步SIL实现 |
| 当前基线全量构建 | clean后135个目标完成，退出0，实际ELF/BIN存在；无编译错误，619条GCC warning（大量重复inline声明未定义）及CMake策略/调用顺序警告 |

## 异常与证据边界

0.1A是本次选用的低测试上限，可能不足以克服摩擦；速度显示也可能包含真实高频往复运动。当前证据无法将问题唯一归因于软件、方向/电角度标定、环路参数或电流限幅。停止扩大运动测试，先同步采集位置差分、观测器速度、dq目标/实测电流及电角度，再区分原因。源码静态审查给出的PLL/方向链疑点只是待验证假设，不是已证明根因。

protocol_context.msgs中有尚未刷新及历史数据，不能单独作为实时验收依据。本次通过update_data记录真实回包，使用上位机实时曲线数值作运动反馈；未用外部转速计独立测量。测试末已移除临时信号观察器。

HOST/CTRL与HOST/APP是不同路径：前者直接使用MotorCtlSMConfig(30022)/Input(30023)，支持内部模式4/5/127；后者通过AppOpMode(30056)/AppControlWord(30054)，不能据应用层无对应case断言内部调试模式不可用。源码位置：motor_control/motor_ctl_loop.c:202、motor_control/motor_ctl_sm.c:1277、database/data_param.c:750、communication/callback/mavlink/mavlink_callback.c:1015。

持久化证据：embedded_project/HPM6E80/Board/bsp_api.c:499-545是内存注册表，read/write不落Flash；embedded_project/HPM6E80/CMakeLists.txt:60-89未编译board_public/flash_db。界面显示保存成功不代表掉电保持。

## 构建及交付

仅当前进程设置HPM_SDK_BASE为项目sdk_env_v1.13.0/hpm_sdk，执行tools/build_hpm6e80.ps1，全量日志位于build-hpm6e80/build_stage2_clean.log（原日志有混合编码，归一化版本在交接工作区build_baseline_utf8.log）。

- demo.elf：1,381,972字节；SHA256 EC5F0444CCEC6E99D21AB0C1EF8334F93A9613DDB85C9BC3F090D2211BF16D23。
- demo.bin：263,944字节；SHA256 AF423B4DDD155D561F35001B37BE2EC441C941ABC8169E6324781784463522E3。
- 产物时间2026-11-07 11:18:18；没有烧录、复位、安装依赖或修改全局设置。
- 原始MCP回包、截图、OpenCode日志及简短交接：D:\Documents\ChatGPT\YeeZi\SERVOHUB_HANDOFF.md所在目录。
- 项目内保留forward_evidence.json、zero_result.json、final_restored.json、mode_selection.json作为关键证据。

后续每轮下位机代码改动按“检查差异→适当编译/行为验证→记录失败和未测项→本地Git提交”汇总；保留用户改动，不以修改测试掩盖失败，未经授权不推送远程。

下一阶段：先定位低速跟踪异常、确认板上固件来源，再修复/烧录/复测，随后按模式逐项完成剩余功能。新聊天先读交接文件并核对设备、项目、Git和OpenCode会话实际状态。
