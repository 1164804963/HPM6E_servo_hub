@echo off
setlocal
chcp 65001 >nul
title HPM6E80 参数库生成

echo HPM6E80 参数库生成
echo.
echo [1] 预览生成结果
echo [2] 编译验证后应用
echo [3] 退出
set "GENERATE_ARGS="
choice /c 123 /n /m "请选择 [1/2/3]："
if errorlevel 255 exit /b 1
if errorlevel 3 exit /b 0
if not errorlevel 1 exit /b 1
if errorlevel 2 set "GENERATE_ARGS=--apply"

set "PYTHON_RUN=py -3"
%PYTHON_RUN% -c "import sys; sys.exit(sys.version_info.major != 3)" >nul 2>&1
if not errorlevel 1 goto run
set "PYTHON_RUN=python"
%PYTHON_RUN% -c "import sys; sys.exit(sys.version_info.major != 3)" >nul 2>&1
if not errorlevel 1 goto run
echo 未找到可用的 Python 3。请检查 Python 是否已加入 PATH。
pause
exit /b 1

:run
echo.
%PYTHON_RUN% "%~dp0generate_database.py" %GENERATE_ARGS%
set "GENERATE_EXIT=%ERRORLEVEL%"
echo.
if "%GENERATE_EXIT%"=="0" (
    echo 完成。请查看上方结果。
) else (
    echo 执行失败，退出码 %GENERATE_EXIT%。请查看上方错误信息。
)
pause
exit /b %GENERATE_EXIT%
