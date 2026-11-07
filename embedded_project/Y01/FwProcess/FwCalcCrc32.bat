@echo off
cd /d "%~dp0"
set "scriptDir=%~dp0"
setlocal enabledelayedexpansion

echo ========================================================================
echo     Firmware Generation Tool [Add CRC32 Verification (srec_cat.exe)]

rem -------- Configuration ----------
set "srcFileName=STM32H743VGT6_Y01"
set "keilOutDir=%scriptDir%..\MDK-ARM\STM32H743VGT6_Y01"
set "srcFile=%keilOutDir%\%srcFileName%.bin"
set "dstDir=%scriptDir%"
set "srec_cat_exe=srec_cat.exe"
rem ---------------------------

rem -------- Check srec_cat.exe exists ----------
if not exist "%srec_cat_exe%" (
    echo [ERROR] %srec_cat_exe% not found in current directory!
    echo Please put srec_cat.exe in the same folder as this script.
    echo ========================================================================
    exit /b 1
)

rem -------- Check source file exists ----------
if not exist "%srcFile%" (
    echo [ERROR] Source file "%srcFile%" not found!
    echo Please ensure Keil build output is at: %keilOutDir%
    echo ========================================================================
    exit /b 1
)

rem -------- Check destination directory exists ----------
if not exist "%dstDir%" mkdir "%dstDir%"

rem -------- Copy source file to script directory ----------
copy /Y "%srcFile%" "%dstDir%" >nul
if errorlevel 1 (
    echo [ERROR] Failed to copy source file to %dstDir%
    echo ========================================================================
    exit /b 1
)

rem -------- Change to script directory ----------
cd /d "%dstDir%"

rem -------- Get source file size ----------
for %%i in ("%srcFileName%.bin") do set "fwSize=%%~zi"
echo [INFO] Source file size: %fwSize% bytes

rem -------- Generate new file name with timestamp suffix ----------
rem Use PowerShell to get timestamp
for /f "usebackq delims=" %%t in (`powershell -Command "Get-Date -Format 'yyyyMMddHHmmss'"`) do set "time=%%t"
if "%time%"=="" (
    rem Fallback: use wmic to get timestamp
    for /f "tokens=2 delims==" %%a in ('wmic OS Get localdatetime /value 2^>nul') do set "dt=%%a"
    set "time=!dt:~0,8!!dt:~8,6!"
)
set "outputFile=Y01_Release_%time%.bin"

rem -------- Call srec_cat to calculate CRC ----------
echo [INFO] Generating CRC32 and creating %outputFile% ...
%srec_cat_exe% "%srcFileName%.bin" -Binary -crop 0 %fwSize% -STM32_Little_Endian %fwSize% -o "%outputFile%" -Binary
if errorlevel 1 (
    echo [ERROR] srec_cat failed! Source file NOT deleted.
    echo ========================================================================
    exit /b 1
)

rem -------- Delete source file ----------
del "%srcFileName%.bin"
if errorlevel 1 (
    echo [WARNING] Failed to delete source file, but new file created.
)

rem -------- Get new file size and display result ----------
for %%i in ("%outputFile%") do set "newSize=%%~zi"
echo [SUCCESS] New bin file generated:
echo   Path: %dstDir%%outputFile%
echo   Size: %newSize% bytes
echo ========================================================================
exit /b 0
