cmake_minimum_required(VERSION 3.20)
# Keep machine-specific paths in one place: .vscode/settings.json (strict JSON).
get_filename_component(HPM_PROJECT_ROOT "${CMAKE_CURRENT_LIST_DIR}/.." ABSOLUTE)
set(HPM_SETTINGS_FILE "${HPM_PROJECT_ROOT}/.vscode/settings.json")
file(READ "${HPM_SETTINGS_FILE}" HPM_SETTINGS_JSON)
string(JSON HPM_SDK_ENV_PATH GET "${HPM_SETTINGS_JSON}" "hpm.sdkEnvPath")
string(JSON HPM_TOOLCHAIN_NAME GET "${HPM_SETTINGS_JSON}" "hpm.toolchainName")
file(TO_CMAKE_PATH "${HPM_SDK_ENV_PATH}" HPM_SDK_ENV_PATH)
set(ENV{HPM_SDK_BASE} "${HPM_SDK_ENV_PATH}/hpm_sdk")
set(ENV{GNURISCV_TOOLCHAIN_PATH} "${HPM_SDK_ENV_PATH}/toolchains/${HPM_TOOLCHAIN_NAME}")
set(ENV{HPM_SDK_TOOLCHAIN_VARIANT} "gcc")
if(NOT EXISTS "$ENV{HPM_SDK_BASE}/cmake/hpm-sdk-config.cmake")
    message(FATAL_ERROR "Shared HPM SDK not found. Check hpm.sdkEnvPath in ${HPM_SETTINGS_FILE}")
endif()
if(NOT EXISTS "$ENV{GNURISCV_TOOLCHAIN_PATH}/bin/riscv32-unknown-elf-gcc.exe")
    message(FATAL_ERROR "Windows RISC-V GCC not found. Check hpm.toolchainName in ${HPM_SETTINGS_FILE}")
endif()
# SDK 的 cmake/python.cmake 用 python_exec 这个缓存名；必须在 find_package 前覆盖默认 Python。
set(HPM_PYTHON_EXECUTABLE "${HPM_SDK_ENV_PATH}/tools/python3/python.exe")
if(NOT EXISTS "${HPM_PYTHON_EXECUTABLE}")
    message(FATAL_ERROR "SDK Python not found: ${HPM_PYTHON_EXECUTABLE}. Check hpm.sdkEnvPath in ${HPM_SETTINGS_FILE}")
endif()
execute_process(
    COMMAND "${HPM_PYTHON_EXECUTABLE}" -c "import yaml"
    RESULT_VARIABLE HPM_PYTHON_YAML_RESULT
    OUTPUT_QUIET
    ERROR_VARIABLE HPM_PYTHON_YAML_ERROR
)
if(NOT HPM_PYTHON_YAML_RESULT EQUAL 0)
    message(FATAL_ERROR "SDK Python cannot import yaml: ${HPM_PYTHON_EXECUTABLE}\n${HPM_PYTHON_YAML_ERROR}")
endif()
set(python_exec "${HPM_PYTHON_EXECUTABLE}" CACHE FILEPATH "Python interpreter used by HPM SDK" FORCE)
# Force the SDK package path so a previous private-SDK cache is never selected.
set(hpm-sdk_DIR "$ENV{HPM_SDK_BASE}/cmake" CACHE PATH "Shared HPM SDK" FORCE)
set(BOARD_SEARCH_PATH "${HPM_PROJECT_ROOT}/boards" CACHE PATH "Project boards" FORCE)
set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS "${HPM_SETTINGS_FILE}")
if(CMAKE_HOST_WIN32)
    set(ENV{PATH} "${HPM_SDK_ENV_PATH}/tools/openocd;$ENV{PATH}")
endif()
message(STATUS "Shared SDK environment: ${HPM_SDK_ENV_PATH}")
