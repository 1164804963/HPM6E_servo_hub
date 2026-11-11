# HPM6E80 板级工程：servo_hub 移植
#
# 只负责“把便携层（app/common/database/motor_control/simulink_code_gen/communication）
# 和本板 Board/ + SDK 板级包链接起来”。便携层不感知任何 HPM 细节。

cmake_minimum_required(VERSION 3.20)

include("${CMAKE_CURRENT_LIST_DIR}/../../cmake/hpm-project.cmake")

if("${HPM_BUILD_TYPE}" STREQUAL "")
    set(HPM_BUILD_TYPE flash_xip)
endif()

# HPM SDK 的功能开关必须在 find_package 之前设好：SDK 的 components/middleware
# 在 find_package 里就被 add_subdirectory 了。
#   CONFIG_HPM_ADC_V2  ADC16 的 v2 接口（hpm_adc_v2.h），board.c 用的是这套
# CONFIG_HPM_MATH 不能开：hpm_math 中间件要求 Andes 工具链，本工程用 riscv gcc，
# 只用 hpm_math.h 里的软件 sin/cos（下面单独加头文件路径）。
set(CONFIG_HPM_ADC_V2 1)

# HPM6E80 有单精度硬件浮点，必须用 rv32imafc + ilp32f 的 multilib。
# 用默认的 rv32imac（软浮点）时实测：20kHz 电流环 26us + 1kHz 位置环 75us，
# 中断占掉 60% 以上 CPU，串口调试台只剩不到 200B/s，还会丢 ADC 触发。
# SDK 的 bldc_foc 例程也是这么选的。
set(RV_ABI "ilp32f")
set(RV_ARCH "rv32imafc")

# HPM SDK 的 find_package 负责选定编译器与链接脚本，必须在 project() 之前。
find_package(hpm-sdk REQUIRED HINTS $ENV{HPM_SDK_BASE})

project(servo_hub_hpm6e80)

# 便携层根目录：本文件在 embedded_project/HPM6E80/ 下，上两级就是工程根。
set(SERVO_ROOT "${CMAKE_CURRENT_LIST_DIR}/../..")

# 板级参数：由 Board/servo_system_cfg.h 选择，这里只给编译开关
sdk_compile_definitions(-DBOARD_SERVO_HPM6E80=1)
# Keep the HPM6E80 debug build at -O2; no fast-math or ABI change.
sdk_compile_options("-O2")

# yuanhub_math.h 在 HPMSOC 分支下要 hpm_math.h。SDK 的 hpm_math 中间件只做 Andes DSP
# 版本（CMake 里硬性要求 nds 工具链），本工程用 Board/hpm_math.h + servo_math_port.c
# 两个小文件顶上，所以这里不引入 SDK 的中间件，也不加它的 include 路径。
sdk_ld_options("-lm")

# --- 便携层 ---------------------------------------------------------------
sdk_inc("${SERVO_ROOT}/app")
sdk_inc("${SERVO_ROOT}/app/Identify")
sdk_inc("${SERVO_ROOT}/board_public")
sdk_inc("${SERVO_ROOT}/common/math_lib")
sdk_inc("${SERVO_ROOT}/common/ring_buff")
sdk_inc("${SERVO_ROOT}/common/software_scope")
sdk_inc("${SERVO_ROOT}/common/unit_conversion")
sdk_inc("${SERVO_ROOT}/communication/callback/mavlink")
sdk_inc("${SERVO_ROOT}/communication/protocol")
sdk_inc("${SERVO_ROOT}/communication/protocol/mavlink/servo_hub_database")
sdk_inc("${SERVO_ROOT}/communication/protocol/CiA402/PDS_FSA")
sdk_inc("${SERVO_ROOT}/database")
sdk_inc("${SERVO_ROOT}/motor_control")
sdk_inc("${SERVO_ROOT}/simulink_code_gen")

file(GLOB PORTABLE_SRC
    "${SERVO_ROOT}/app/*.c"
    "${SERVO_ROOT}/app/Identify/*.c"
    "${SERVO_ROOT}/common/ring_buff/*.c"
    "${SERVO_ROOT}/common/software_scope/*.c"
    "${SERVO_ROOT}/common/unit_conversion/*.c"
    "${SERVO_ROOT}/database/*.c"
    "${SERVO_ROOT}/motor_control/*.c"
    "${SERVO_ROOT}/simulink_code_gen/*.c"
    # 官方 servo_hub 上位机走的就是这两个文件里的 MAVLink 收发回调。
    # 传输（UART0 收发与分流）在 Board/servo_host.c。
    "${SERVO_ROOT}/communication/callback/mavlink/*.c"
)
# 不编译 board_public/system_manage/system_init.c：它的零漂校准直接引用 Y01 的
# UVW_CURRENT_*_CHANNEL 宏，本板把同一状态机实现在 bsp_api.c 里，见移植文档「已知偏差」。
foreach(src ${PORTABLE_SRC})
    sdk_src(${src})
endforeach()

# --- 本板 ---------------------------------------------------------------
sdk_inc(Board)
sdk_src(Board/board.c)
sdk_src(Board/bsp_api.c)
sdk_src(Board/servo_math_port.c)
sdk_src(Board/servo_bringup.c)
sdk_src(Board/servo_console.c)
sdk_src(Board/servo_host.c)
sdk_src(Board/system_timer.c)
sdk_src(Board/drv_encoder.c)
sdk_src(Board/encoder_mt6816.c)

# 应用入口
sdk_app_src(Board/main.c)

# --- EtherCAT 从站（HPM6E80 内置 ESC）------------------------------------
# 上层：本工程已有的 ETG SSC 协议栈 + CiA402 应用层（YuanHub，已对接 kAxis），
#       位于 communication/protocol/EtherCAT_LAN925x/Src。
# 底层：改用 SDK 的 HPM 内置 ESC port 层（hpm_ecat_hw/phy + Flash 模拟 EEPROM），
#       替换原 LAN9252(SPI) 的 ecat_app_hw.c/ecat_drv_sqi.c。
set(ECAT_SRC "${SERVO_ROOT}/communication/protocol/EtherCAT_LAN925x/Src")
set(HPM_ECAT_PORT "${HPM_SDK_BASE}/samples/ethercat/port")

sdk_inc("${ECAT_SRC}")
sdk_inc("${HPM_ECAT_PORT}")

# 协议栈 + 应用层（含 EoE/FoE 的 SSC 协议层：mailbox.c 无条件调用 EOE_Init/FOE_Init，
# 且 BL_Start/BL_Stop 在 bootmode.c，故一并编入。这些 SSC 文件不依赖 lwIP。）
sdk_src("${ECAT_SRC}/ecatappl.c")
sdk_src("${ECAT_SRC}/ecatslv.c")
sdk_src("${ECAT_SRC}/ecatcoe.c")
sdk_src("${ECAT_SRC}/coeappl.c")
sdk_src("${ECAT_SRC}/mailbox.c")
sdk_src("${ECAT_SRC}/objdef.c")
sdk_src("${ECAT_SRC}/sdoserv.c")
sdk_src("${ECAT_SRC}/emcy.c")
sdk_src("${ECAT_SRC}/ecateoe.c")
sdk_src("${ECAT_SRC}/eoeappl.c")
sdk_src("${ECAT_SRC}/ecatfoe.c")
sdk_src("${ECAT_SRC}/foeappl.c")
sdk_src("${ECAT_SRC}/bootmode.c")
# 注意：不要编 ${ECAT_SRC}/ecat_app.c —— 那是 SSC Tool 生成的空模板
# （APPL_InputMapping/APPL_OutputMapping 只有 #warning，PDO 数据根本不搬运）。
# 真正和本工程 CiA402/kAxis 对接的是 EtherCAT_LAN925x/ecat_app.c（同版本 SSC，
# 按 sTxPDOassign/sRxPDOassign 逐项回调 OD 的 Read/Write）。
sdk_src("${SERVO_ROOT}/communication/protocol/EtherCAT_LAN925x/ecat_app.c")

# CiA402 对象字典 <-> 驱动应用层的回调桥接（0x6040/0x6041/0x6060/0x6064 ...）
sdk_inc("${SERVO_ROOT}/communication/callback/ethercat")
sdk_inc("${SERVO_ROOT}/communication/callback/cia402_od")
sdk_src("${SERVO_ROOT}/communication/callback/ethercat/ecat_callback.c")
sdk_src("${SERVO_ROOT}/communication/callback/cia402_od/Cia402_ObjectDictionary_Callback.c")
sdk_src("${SERVO_ROOT}/communication/callback/cia402_od/Cia402_ObjectDictionary_Variable.c")

# CiA402 PDS 状态机（1kHz 控制环里 PDS_FSA_Run，产生 Statusword 与使能动作）
sdk_src("${SERVO_ROOT}/communication/protocol/CiA402/PDS_FSA/cia402_fsm.c")
sdk_src("${SERVO_ROOT}/communication/protocol/CiA402/PDS_FSA/cia402_statusword.c")
sdk_src("${SERVO_ROOT}/communication/protocol/CiA402/PDS_FSA/cia402_error_code.c")

# HPM 内置 ESC 硬件适配层
sdk_src("${HPM_ECAT_PORT}/hpm_ecat_hw.c")
sdk_src("${HPM_ECAT_PORT}/hpm_ecat_phy.c")
sdk_src("${HPM_ECAT_PORT}/hpm_ecat_e2p_emulation.c")
# ESC 模拟 EEPROM 的 SII 内容（强符号覆盖 SDK 的 weak aEepromData）
sdk_src(Board/ecat_eeprom.c)

# 使用 Flash 模拟 EEPROM；ESC 走内置 ESC
sdk_compile_definitions(-DESC_EEPROM_EMULATION=1)
sdk_compile_definitions(-DECAT_EEPROM_EMULATION=1)
sdk_compile_definitions(-DCONFIG_HPM_ESC=1)
# CiA402：让 motor_ctl_loop.c 的 1kHz 环里跑 PDS_FSA_Run()，
# 并让 OD 的 set_Controlword 触发状态机（与 Y01 的 V_ECAT_CIA402 版本一致）
sdk_compile_definitions(-DUSE_CIA402=1)
# 不用 ecat_app.c 自带的 main（那是 Y01 独立入口），入口用本项目 Board/main.c
sdk_compile_definitions(-DUSE_DEFAULT_MAIN=0)

# Flash 模拟 EEPROM 组件（SDK 中间件），port 层的 hpm_ecat_e2p_emulation 依赖它
set(HPM_EEPROM_EMU "${HPM_SDK_BASE}/components/eeprom_emulation")
sdk_inc("${HPM_EEPROM_EMU}")
sdk_inc("${HPM_EEPROM_EMU}/port")
sdk_src("${HPM_EEPROM_EMU}/eeprom_emulation.c")
sdk_src("${HPM_EEPROM_EMU}/port/hpm_nor_flash.c")

generate_ide_projects()
