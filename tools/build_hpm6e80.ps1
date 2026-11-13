# 编译 HPM6E80 固件：先 configure 再 build。默认 EtherCAT。
# CAN 协议与 Y01 次版本号对应，各自使用独立目录。
#
# 参数与 .vscode/settings.json 里的 cmake.* 保持一致；改了那边的配置要同步改这里。

param(
    [string]$Root = (Join-Path $PSScriptRoot ".."),
    [ValidateSet("ETHERCAT", "CAN_CIA402", "CAN_ENCOS", "CANOPEN_CIA402", "CANFD_CUSTOM")]
    [string]$Bus = "ETHERCAT",
    [switch]$CanPassthrough
)

$Root = (Resolve-Path $Root).Path
$Bus = $Bus.ToUpperInvariant()
$buildDir = switch ($Bus) {
    "CAN_CIA402" { "build-hpm6e80-can" }
    "CAN_ENCOS" { "build-hpm6e80-encos" }
    "CANOPEN_CIA402" { "build-hpm6e80-canopen" }
    "CANFD_CUSTOM" { "build-hpm6e80-canfd" }
    default { "build-hpm6e80" }
}
$passthrough = if ($CanPassthrough) { "ON" } else { "OFF" }
Push-Location $Root
try {
    Write-Host "== configure ($Bus) ==" -ForegroundColor Cyan
    & cmake -S embedded_project/HPM6E80 -B $buildDir -G Ninja `
        -DBOARD=hpm6e00YZ `
        "-DSERVO_BUS=$Bus" `
        "-DSERVO_CAN_PASSTHROUGH=$passthrough" `
        -DHPM_BUILD_TYPE=flash_xip `
        -DCMAKE_BUILD_TYPE=debug `
        -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
    if ($LASTEXITCODE -ne 0) {
        throw "configure 失败（exit $LASTEXITCODE）"
    }

    Write-Host "== build ==" -ForegroundColor Cyan
    & cmake --build $buildDir
    if ($LASTEXITCODE -ne 0) {
        throw "编译失败（exit $LASTEXITCODE）"
    }

    $elf = Join-Path $Root "$buildDir\output\demo.elf"
    if (-not (Test-Path $elf)) {
        throw "没有生成 $elf"
    }
    $size = (Get-Item $elf).Length
    Write-Host ("build OK: {0} ({1:N0} bytes)" -f $elf, $size) -ForegroundColor Green
}
finally {
    Pop-Location
}
