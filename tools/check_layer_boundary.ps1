# 架构边界检查：确认 HPM 板级细节没有渗进便携层。
#
# 用法：pwsh -File tools/check_layer_boundary.ps1
# 返回码 0 = 通过，1 = 越界。建议在提交前跑一次。

param(
    [string]$Root = (Join-Path $PSScriptRoot "..")
)

$ErrorActionPreference = "Stop"
$failed = $false

$portableDirs = @(
    "app",
    "common",
    "database",
    "motor_control",
    "simulink_code_gen",
    "communication\callback",
    "communication\protocol\CiA402",
    "board_public"
) | ForEach-Object { Join-Path $Root $_ }

$boardDir = Join-Path $Root "embedded_project\HPM6E80\Board"
$silDir = Join-Path $Root "SIL_project"

function Report([string]$message) {
    Write-Host "FAIL: $message" -ForegroundColor Red
    $script:failed = $true
}

# 允许的既存例外（移植时不放大，见 doc/PORTING_HPM6E80.md 第 2 节）：
#   yuanhub_math.h      —— 平台分支：ARM_MATH_* / HPMSOC_* / 标准库三选一
#   mavlink_callback.h  —— 同一个 HPMSOC 平台分支
#   system_init.h       —— 原始工程既有的 board_public -> board.h 依赖，HPM 侧解析到 SDK 板级包
$includeWhitelist = @("yuanhub_math.h", "mavlink_callback.h", "system_init.h")

# 规则 1：便携层不得出现 HPM SDK 头文件
Get-ChildItem -Path $portableDirs -Recurse -File -Include *.c,*.h | ForEach-Object {
    $file = $_
    if ($includeWhitelist -contains $file.Name) { return }
    $hits = Select-String -Path $file.FullName -Pattern '#include\s*[<"](hpm_|board\.h)' -ErrorAction SilentlyContinue
    foreach ($hit in $hits) {
        Report "$($file.FullName):$($hit.LineNumber) 便携层包含板级头文件"
    }
}

# 规则 2：板级硬件文件不得直接包含便携层内部头文件。
# Application/ contains explicit board/application adapters and is not a hardware driver directory.
# main.c 是组合根（写死初始化顺序），允许同时看到两侧。
Get-ChildItem -Path $boardDir -Recurse -File -Include *.c,*.h | ForEach-Object {
    $file = $_
    if ($file.Name -eq "main.c") { return }
    $hits = Select-String -Path $file.FullName -Pattern '#include\s*"(app_|data_param)' -ErrorAction SilentlyContinue
    foreach ($hit in $hits) {
        Report "$($file.FullName):$($hit.LineNumber) 板级直接引用了应用层内部头文件"
    }
}

# 规则 3：bsp_api.h 的函数集合冻结，新增能力应进板级自己的头文件
$apiHeader = Join-Path $Root "board_public\bsp_api.h"
$expectedFunctions = @(
    "bsp_system_reset","bsp_system_global_irq_enable","bsp_system_global_irq_disable",
    "sys_set_bsp_error_state","sys_get_bsp_error_state","sys_get_hardware_self_test_status",
    "sys_bus_voltage_check","sys_current_calibration_step","sys_get_current_calibration_status",
    "sys_get_current_calibration_drift","bsp_set_pwm_state","bsp_pwm_ready_state_updata",
    "bsp_get_pwm_state","bsp_set_phase_voltage","bsp_get_phase_current","bsp_get_dc_bus_voltage",
    "bsp_get_dc_bus_current","bsp_get_motor_temp","bsp_get_mos_temperature","bsp_get_mcu_temperature",
    "bsp_get_user_adc1_val","bsp_set_encoder_config","bsp_get_encoder_state","bsp_get_encoder_cnt",
    "bsp_get_encoder_turns","bsp_get_encoder_type","bsp_flashdb_init","bsp_get_digital_input_state",
    "bsp_set_digital_output_state","bsp_sys_blocking_delay_us","bsp_sys_blocking_delay_ms",
    "bsp_set_timer_record_start","bsp_set_timer_record_stop","bsp_get_timer_duration_records_us",
    "bsp_set_run_led_state","bsp_set_run_led_toggle","bsp_set_error_led_state","bsp_set_error_led_toggle"
)
$declared = (Select-String -Path $apiHeader -Pattern '^\s*[A-Za-z_][\w \*]*\b(bsp_|sys_)\w+\s*\(' |
             ForEach-Object { ($_.Line -split '\(')[0].Trim().Split(' ')[-1].Trim('*') }) | Sort-Object -Unique
foreach ($fn in $declared) {
    if ($expectedFunctions -notcontains $fn) {
        Write-Host "NOTE: $fn 是 bsp_api.h 里的新接口，请同步 SIL_project/bsp_api_virtual.c" -ForegroundColor Yellow
    }
}

# 规则 4：SIL 必须仍能独立构建（只检查关键文件存在）
foreach ($path in @("SIL_project\main.c", "SIL_project\bsp_api_virtual.c", "CMakePresets.json")) {
    if (-not (Test-Path (Join-Path $Root $path))) {
        Report "SIL 工程文件缺失：$path（移植不得破坏离线仿真）"
    }
}

if ($failed) {
    Write-Host "`n边界检查未通过。" -ForegroundColor Red
    exit 1
}
Write-Host "边界检查通过：便携层未渗入板级细节。" -ForegroundColor Green
exit 0
