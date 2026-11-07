# 烧录 HPM6E80 固件（FT2232 JTAG + HPM 官方 OpenOCD）。
#
# 用法：
#   powershell -NoProfile -ExecutionPolicy Bypass -File tools/flash_hpm6e80.ps1
#   powershell ... -Elf build-hpm6e80/output/demo.elf
#
# SDK 路径与 .vscode/settings.json 里的 hpm.sdkEnvPath 保持一致（和 CMake 用的是同一个值）。
#
# 脚本做三件额外的事，都是踩过坑换来的：
#   1. 烧录前先通过串口下发 dis，把桥臂封锁——电机转着的时候复位/烧录，
#      反电动势会打在门驱上，STDRIVE101 会锁存故障，只能断电才能恢复。
#   2. 如果 OpenOCD 报 "Unable to halt"，用 DM 的 ndmreset 把内核救回来再试一次
#      （这块板的 nSRST 没接调试器，普通 reset 命令没用）。
#   3. 烧完校验、复位、退出，返回码非 0 就抛错。

param(
    [string]$Root = (Join-Path $PSScriptRoot ".."),
    [string]$Elf = "",
    [string]$Port = "COM4",
    [switch]$NoDisable
)

$Root = (Resolve-Path $Root).Path
$settings = Get-Content (Join-Path $Root ".vscode\settings.json") -Raw | ConvertFrom-Json
$sdkEnv = $settings.'hpm.sdkEnvPath'
$sdk = Join-Path $sdkEnv "hpm_sdk"
$openocd = Join-Path $sdkEnv "tools\openocd\openocd.exe"

if (-not $Elf) {
    $Elf = Join-Path $Root "build-hpm6e80\output\demo.elf"
}
if (-not (Test-Path $Elf)) {
    throw "固件不存在：$Elf（先跑 cmake --build build-hpm6e80）"
}
if (-not (Test-Path $openocd)) {
    throw "找不到 OpenOCD：$openocd"
}

$openocdCfg = Join-Path $sdk "boards\openocd"
$boardCfg = Join-Path $Root "boards\openocd\boards\hpm6e00YZ.cfg"

# OpenOCD 的 Tcl 会把反斜杠当转义，路径一律用正斜杠传进去。
$ElfTcl = $Elf -replace '\\', '/'

# --- 1. 烧录前先封锁桥臂（串口不在线也无所谓，继续烧） -----------------------
if (-not $NoDisable) {
    try {
        $sp = New-Object System.IO.Ports.SerialPort $Port, 921600, "None", 8, "One"
        $sp.ReadTimeout = 100
        $sp.Open()
        Start-Sleep -Milliseconds 80
        $sp.Write("dis`r")
        Start-Sleep -Milliseconds 120
        $sp.Close()
        Write-Host "serial: sent dis (bridge locked)" -ForegroundColor DarkGray
    } catch {
        Write-Host "serial: $Port not usable, skip dis" -ForegroundColor DarkYellow
    }
}

function Invoke-Flash {
    $ErrorActionPreference = "Continue"
    $result = & $openocd `
        -s $openocdCfg `
        -f (Join-Path $openocdCfg "probes\ft2232.cfg") `
        -f (Join-Path $openocdCfg "soc\hpm6e80-single-core.cfg") `
        -f $boardCfg `
        -c "program `"$ElfTcl`" verify reset exit" 2>&1
    $script:lastExit = $LASTEXITCODE
    $ErrorActionPreference = "Stop"
    return $result
}

# --- 2. 烧录（halt 失败时先做一次 DMI 复位再重试） ---------------------------
Write-Host "flashing $Elf" -ForegroundColor Cyan
$out = Invoke-Flash
$code = $script:lastExit

if ("$out" -match "Unable to halt|examination failed") {
    Write-Host "target stuck, recovering with DM ndmreset..." -ForegroundColor Yellow
    $ErrorActionPreference = "Continue"
    $null = & $openocd `
        -f (Join-Path $Root "tools\openocd_dmi.cfg") `
        -f (Join-Path $Root "tools\openocd_dmi_reset.tcl") 2>&1
    $ErrorActionPreference = "Stop"
    Start-Sleep -Milliseconds 500
    $out = Invoke-Flash
    $code = $script:lastExit
}

$out | ForEach-Object { Write-Host $_ }

if ($code -ne 0) {
    throw "OpenOCD 烧录失败（exit $code）"
}
if ("$out" -match "\*\* Programming Failed") {
    throw "OpenOCD 报告烧录失败"
}

Write-Host "flash OK" -ForegroundColor Green
