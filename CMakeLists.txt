cmake_minimum_required(VERSION 3.10.0)
project(servo_hub_hil VERSION 0.1.0 LANGUAGES C)

project(ServoHubSil)

file(GLOB SRC_FILES
    "${PROJECT_SOURCE_DIR}/app/*.c"
    "${PROJECT_SOURCE_DIR}/app/Identify/*.c"
    "${PROJECT_SOURCE_DIR}/common/ring_buff/*.c"
    "${PROJECT_SOURCE_DIR}/common/software_scope/*.c"
    "${PROJECT_SOURCE_DIR}/common/unit_conversion/*.c"
    "${PROJECT_SOURCE_DIR}/communication/callback/mavlink/*.c"
    "${PROJECT_SOURCE_DIR}/database/*.c"
    "${PROJECT_SOURCE_DIR}/motor_control/*.c"
    "${PROJECT_SOURCE_DIR}/simulink_code_gen/*.c"
    "${PROJECT_SOURCE_DIR}/SIL_project/*.c"
    "${PROJECT_SOURCE_DIR}/SIL_project/zmq/src/zmq_handler.c"
)

add_executable(${CMAKE_PROJECT_NAME}
    ${PROJECT_SOURCE_DIR}/SIL_project/main.c
    ${SRC_FILES}
)

find_library(MY_LIBRARY_PATH NAMES zmq PATHS ${PROJECT_SOURCE_DIR}/SIL_project/zmq/lib/)
if(MY_LIBRARY_PATH)
    message(STATUS "Found zmq library: ${MY_LIBRARY_PATH}")
    target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ${MY_LIBRARY_PATH})
else()
    message(FATAL_ERROR "Could not find zmq library")
endif()

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    ${PROJECT_SOURCE_DIR}/app
    ${PROJECT_SOURCE_DIR}/app/Identify
    ${PROJECT_SOURCE_DIR}/board_public
    ${PROJECT_SOURCE_DIR}/board_public/system_manage
    ${PROJECT_SOURCE_DIR}/common/math_lib
    ${PROJECT_SOURCE_DIR}/common/ring_buff
    ${PROJECT_SOURCE_DIR}/common/software_scope
    # ${PROJECT_SOURCE_DIR}/common/system_timer
    ${PROJECT_SOURCE_DIR}/common/unit_conversion
    ${PROJECT_SOURCE_DIR}/communication/callback/mavlink
    ${PROJECT_SOURCE_DIR}/communication/protocol
    # ${PROJECT_SOURCE_DIR}/communication/protocol/mavlink
    ${PROJECT_SOURCE_DIR}/communication/protocol/mavlink/servo_hub_database
    ${PROJECT_SOURCE_DIR}/motor_control
    ${PROJECT_SOURCE_DIR}/database
    ${PROJECT_SOURCE_DIR}/simulink_code_gen
    ${PROJECT_SOURCE_DIR}/SIL_project
    ${PROJECT_SOURCE_DIR}/SIL_project/zmq/include
)

# 自动复制运行时 DLL（仅 Windows MinGW）
if(WIN32 AND MINGW)
    # 定义需要复制的 DLL
    set(RUNTIME_DLLS
        "${PROJECT_SOURCE_DIR}/SIL_project/zmq/bin/libzmq.dll"
        "${PROJECT_SOURCE_DIR}/../mingw64/bin/libstdc++-6.dll"
        "${PROJECT_SOURCE_DIR}/../mingw64/bin/libgcc_s_seh-1.dll"
        "${PROJECT_SOURCE_DIR}/../mingw64/bin/libwinpthread-1.dll"
    )
    
    # 为每个 DLL 添加复制命令
    foreach(DLL ${RUNTIME_DLLS})
        if(EXISTS ${DLL})
            add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    "${DLL}"
                    "$<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>"
                COMMENT "Copying ${DLL}"
            )
        endif()
    endforeach()
endif()
