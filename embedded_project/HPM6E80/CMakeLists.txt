# HPM6E80 板级工程：servo_hub 移植
#
# 只负责把便携层与 Board/ + SDK 板级包链接起来；总线在 SERVO_BUS 选择。

cmake_minimum_required(VERSION 3.20)

include("${CMAKE_CURRENT_LIST_DIR}/../../cmake/hpm-project.cmake")

if("${HPM_BUILD_TYPE}" STREQUAL "")
    set(HPM_BUILD_TYPE flash_xip)
endif()

# HPM SDK 的功能开关必须在 find_package 之前设好。
set(CONFIG_HPM_ADC_V2 1)

# HPM6E80 有单精度硬件浮点，必须使用 rv32imafc + ilp32f。
set(RV_ABI "ilp32f")
set(RV_ARCH "rv32imafc")

find_package(hpm-sdk REQUIRED HINTS $ENV{HPM_SDK_BASE})

project(servo_hub_hpm6e80)

set(SERVO_BUS "ETHERCAT" CACHE STRING "Servo bus: ETHERCAT or CAN_CIA402")
set_property(CACHE SERVO_BUS PROPERTY STRINGS ETHERCAT CAN_CIA402)
if(NOT SERVO_BUS STREQUAL "ETHERCAT" AND NOT SERVO_BUS STREQUAL "CAN_CIA402")
    message(FATAL_ERROR "Unknown SERVO_BUS='${SERVO_BUS}', expected ETHERCAT or CAN_CIA402")
endif()

set(SERVO_ROOT "${CMAKE_CURRENT_LIST_DIR}/../..")

sdk_compile_definitions(-DBOARD_SERVO_HPM6E80=1)
sdk_compile_options("-O2")
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
sdk_inc("${SERVO_ROOT}/communication/callback/cia402_od")
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
    "${SERVO_ROOT}/communication/callback/mavlink/*.c"
)
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
sdk_app_src(Board/main.c)

# --- CiA402 共用对象字典 / PDS_FSA ----------------------------------------
sdk_src("${SERVO_ROOT}/communication/callback/cia402_od/Cia402_ObjectDictionary_Callback.c")
sdk_src("${SERVO_ROOT}/communication/callback/cia402_od/Cia402_ObjectDictionary_Variable.c")
sdk_src("${SERVO_ROOT}/communication/protocol/CiA402/PDS_FSA/cia402_fsm.c")
sdk_src("${SERVO_ROOT}/communication/protocol/CiA402/PDS_FSA/cia402_statusword.c")
sdk_src("${SERVO_ROOT}/communication/protocol/CiA402/PDS_FSA/cia402_error_code.c")

if(SERVO_BUS STREQUAL "ETHERCAT")
    sdk_compile_definitions(-DCONFIG_SERVO_ETHERCAT=1)
    sdk_compile_definitions(-DMINOR_VERSION=3)

    set(ECAT_SRC "${SERVO_ROOT}/communication/protocol/EtherCAT_LAN925x/Src")
    set(HPM_ECAT_PORT "${HPM_SDK_BASE}/samples/ethercat/port")
    sdk_inc("${ECAT_SRC}")
    sdk_inc("${HPM_ECAT_PORT}")

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
    sdk_src("${SERVO_ROOT}/communication/protocol/EtherCAT_LAN925x/ecat_app.c")

    sdk_inc("${SERVO_ROOT}/communication/callback/ethercat")
    sdk_src("${SERVO_ROOT}/communication/callback/ethercat/ecat_callback.c")

    sdk_src("${HPM_ECAT_PORT}/hpm_ecat_hw.c")
    sdk_src("${HPM_ECAT_PORT}/hpm_ecat_phy.c")
    sdk_src("${HPM_ECAT_PORT}/hpm_ecat_e2p_emulation.c")
    sdk_src(Board/ecat_eeprom.c)

    sdk_compile_definitions(-DESC_EEPROM_EMULATION=1)
    sdk_compile_definitions(-DECAT_EEPROM_EMULATION=1)
    sdk_compile_definitions(-DCONFIG_HPM_ESC=1)
    sdk_compile_definitions(-DUSE_DEFAULT_MAIN=0)

    set(HPM_EEPROM_EMU "${HPM_SDK_BASE}/components/eeprom_emulation")
    sdk_inc("${HPM_EEPROM_EMU}")
    sdk_inc("${HPM_EEPROM_EMU}/port")
    sdk_src("${HPM_EEPROM_EMU}/eeprom_emulation.c")
    sdk_src("${HPM_EEPROM_EMU}/port/hpm_nor_flash.c")
else()
    sdk_compile_definitions(-DCONFIG_SERVO_CAN=1)
    sdk_compile_definitions(-DMINOR_VERSION=0)

    sdk_inc("${SERVO_ROOT}/communication/protocol/can_cia402")
    sdk_src("${SERVO_ROOT}/communication/protocol/can_cia402/can_cia402.c")
    sdk_src("${SERVO_ROOT}/communication/callback/cia402_od/master_cia402_callback.c")
    sdk_src(Board/bsp_can.c)
    sdk_src(Board/servo_can.c)
    sdk_src(Board/servo_debug_can.c)
endif()

generate_ide_projects()
