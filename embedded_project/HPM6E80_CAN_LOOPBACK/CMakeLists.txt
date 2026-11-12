cmake_minimum_required(VERSION 3.20)

include("${CMAKE_CURRENT_LIST_DIR}/../../cmake/hpm-project.cmake")

if("${HPM_BUILD_TYPE}" STREQUAL "")
    set(HPM_BUILD_TYPE flash_xip)
endif()

set(RV_ABI "ilp32f")
set(RV_ARCH "rv32imafc")

find_package(hpm-sdk REQUIRED HINTS $ENV{HPM_SDK_BASE})

project(servo_hub_hpm6e80_can_loopback)

set(SERVO_ROOT "${CMAKE_CURRENT_LIST_DIR}/../..")

sdk_inc("${SERVO_ROOT}/embedded_project/HPM6E80/Board")
sdk_src("${SERVO_ROOT}/embedded_project/HPM6E80/Board/bsp_can.c")

sdk_app_src(main.c)

generate_ide_projects()
