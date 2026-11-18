# HPM6E80 参数库生成

双击本目录中的 `生成数据库.cmd`。选择 1 预览结果，或选择 2 编译验证后应用。窗口会保留执行结果。需要 Windows、Python 3 和 Git。

也可以在 PowerShell 的工程根目录运行以下命令。

```powershell
python tools/database_generate/generate_database.py
python tools/database_generate/generate_database.py --output .\database-preview
python tools/database_generate/generate_database.py --apply
```

第一条列出生成结果中会变化的文件。第二条把 13 个候选文件按工程目录结构导出到一个新目录，方便在应用前查看差异。第三条先在临时工程中编译 EtherCAT、普通 CAN 和 CANopen，再更新有变化的生成文件。需要已有 HPM SDK 和正常可用的固件构建配置。生成或编译失败时，正式源码不会被更新。

入口复用原来的两个 EXE，覆盖 CiA402 字典、APP 参数、Flash 参数结构、CANopen EDS／SlaveOD、EtherCAT 对象字典回调五个生成入口。版本化补丁保留 HPM 平台差异、CiA402 和 APP 修复及 EtherCAT SDO 错误返回。补丁上下文失配时，先在导出的临时结果或生成器副本中核对对应代码，再更新补丁。若手工修改处不在生成器保留的 USER CODE 内，需要同时维护这份补丁。

EtherCAT SSC、ESI 和板级运行代码由各自原有流程维护。现有 CSV 的再生成前后，EtherCAT、普通 CAN 和 CANopen 的烧录镜像逐字节一致。主动修改共享对象定义可能改变 EtherCAT 行为，构建通过后仍须核对相应的主站行为。生成工具不会烧录固件。
