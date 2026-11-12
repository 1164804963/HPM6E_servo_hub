cmake_minimum_required(VERSION 3.16)
project(can_software_tests C)

set(CAN_TEST_ROOT "${CMAKE_CURRENT_LIST_DIR}")
set(SERVO_ROOT "${CAN_TEST_ROOT}/../..")

add_executable(test_can_software
    test_main.c
    test_can_software.c
    test_od.c
    stubs/bsp_can_stub.c
    stubs/servo_stubs.c
    "${SERVO_ROOT}/communication/protocol/can_cia402/can_cia402.c"
    "${SERVO_ROOT}/embedded_project/HPM6E80/Board/servo_can.c"
)

target_include_directories(test_can_software PRIVATE
    "${CAN_TEST_ROOT}/host_stubs"
    "${CAN_TEST_ROOT}/stubs"
    "${CAN_TEST_ROOT}"
    "${SERVO_ROOT}/embedded_project/HPM6E80/Board"
    "${SERVO_ROOT}/communication/protocol/can_cia402"
    "${SERVO_ROOT}/communication/callback/cia402_od"
)

enable_testing()
add_test(NAME can_software COMMAND test_can_software)
