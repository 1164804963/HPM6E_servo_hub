cmake_minimum_required(VERSION 3.20)

include("${CMAKE_CURRENT_LIST_DIR}/../../cmake/hpm-project.cmake")

if("${HPM_BUILD_TYPE}" STREQUAL "")
    set(HPM_BUILD_TYPE flash_xip)
endif()

set(RV_ABI "ilp32f")
set(RV_ARCH "rv32imafc")

find_package(hpm-sdk REQUIRED HINTS $ENV{HPM_SDK_BASE})

project(servo_hub_hpm6e80_can_software_test)

set(SERVO_ROOT "${CMAKE_CURRENT_LIST_DIR}/../..")
set(CAN_TEST_ROOT "${SERVO_ROOT}/tests/can_software")

sdk_inc("${SERVO_ROOT}/embedded_project/HPM6E80/Board")
sdk_inc("${CAN_TEST_ROOT}/stubs")
sdk_inc("${SERVO_ROOT}/communication/protocol/can_cia402")
sdk_inc("${SERVO_ROOT}/communication/callback/cia402_od")
sdk_inc("${CAN_TEST_ROOT}")

set(CAN_TEST_SOURCES
    "${SERVO_ROOT}/communication/protocol/can_cia402/can_cia402.c"
    "${SERVO_ROOT}/embedded_project/HPM6E80/Board/servo_can.c"
    "${CAN_TEST_ROOT}/test_can_software.c"
    "${CAN_TEST_ROOT}/test_od.c"
    "${CAN_TEST_ROOT}/stubs/bsp_can_stub.c"
    "${CAN_TEST_ROOT}/stubs/servo_stubs.c"
)
foreach(src ${CAN_TEST_SOURCES})
    sdk_src(${src})
endforeach()

sdk_app_src(main.c)

generate_ide_projects()
