# 编译 HPM6E80 固件：先 configure 再 build，产物 build-hpm6e80/output/demo.elf。
#
# 给 VSCode 的 "CMake: Build firmware" 任务用。之所以不直接用 CMake Tools 的原生构建任务，
# 是因为本机 VSCode 的集成终端起不来（"终端进程启动失败(退出代码: -1)"），
# 这个脚本用 process 型任务直接调用，不经过终端。
#
# 参数与 .vscode/settings.json 里的 cmake.* 保持一致；改了那边的配置要同步改这里。

param(
    [string]$Root = (Join-Path $PSScriptRoot "..")
)

$Root = (Resolve-Path $Root).Path
Push-Location $Root
try {
    Write-Host "== configure ==" -ForegroundColor Cyan
    & cmake -S embedded_project/HPM6E80 -B build-hpm6e80 -G Ninja `
        -DBOARD=hpm6e00YZ `
        -DHPM_BUILD_TYPE=flash_xip `
        -DCMAKE_BUILD_TYPE=debug `
        -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
    if ($LASTEXITCODE -ne 0) {
        throw "configure 失败（exit $LASTEXITCODE）"
    }

    Write-Host "== build ==" -ForegroundColor Cyan
    & cmake --build build-hpm6e80
    if ($LASTEXITCODE -ne 0) {
        throw "编译失败（exit $LASTEXITCODE）"
    }

    $elf = Join-Path $Root "build-hpm6e80\output\demo.elf"
    if (-not (Test-Path $elf)) {
        throw "没有生成 $elf"
    }
    $size = (Get-Item $elf).Length
    Write-Host ("build OK: {0} ({1:N0} bytes)" -f $elf, $size) -ForegroundColor Green
}
finally {
    Pop-Location
}
