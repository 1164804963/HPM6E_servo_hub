@echo off
cd /d "%~dp0"
set "scriptDir=%~dp0"
setlocal enabledelayedexpansion

echo ========================================================================
echo     Firmware Generation Tool [Two Firmware Merge (srec_cat.exe)]

REM -------- User Configuration ----------
set "BOOT_FILE_DEFAULT=BootLoader.bin"
set "APP_FILE_DEFAULT=Y01_Release_*.bin"
set "OUTPUT_FILE_DEFAULT=FW_Boot_App"
set "BOOT_START_DEFAULT=0x08000000"
set "APP_START_DEFAULT=0x08100000"
set "FILL_VALUE_DEFAULT=0xFF"
REM ---------------------------

REM -------- Auto-detect latest existing App file ----------
for /f "delims=" %%i in ('dir /b /od Y01_Release_*.bin 2^>nul') do set "LATEST_APP=%%i"
if defined LATEST_APP (
    echo [INFO] Auto-detected latest App: !LATEST_APP!
    set "APP_FILE_DEFAULT=!LATEST_APP!"
    set "OUTPUT_FILE_DEFAULT=!OUTPUT_FILE_DEFAULT!_!LATEST_APP!"
)

REM -------- Interactive Input (with default values) ----------
set /p "BOOT_FILE=Enter Bootloader file name [!BOOT_FILE_DEFAULT!]: "
if "!BOOT_FILE!"=="" set "BOOT_FILE=!BOOT_FILE_DEFAULT!"

set /p "APP_FILE=Enter App file name [!APP_FILE_DEFAULT!]: "
if "!APP_FILE!"=="" set "APP_FILE=!APP_FILE_DEFAULT!"

set /p "OUTPUT_FILE=Enter output merged file name [!OUTPUT_FILE_DEFAULT!]: "
if "!OUTPUT_FILE!"=="" set "OUTPUT_FILE=!OUTPUT_FILE_DEFAULT!"

set /p "BOOT_START=Enter Bootloader start address (hex) [!BOOT_START_DEFAULT!]: "
if "!BOOT_START!"=="" set "BOOT_START=!BOOT_START_DEFAULT!"

set /p "APP_START=Enter App start address (hex) [!APP_START_DEFAULT!]: "
if "!APP_START!"=="" set "APP_START=!APP_START_DEFAULT!"

set /p "FILL_VALUE=Enter fill byte value (hex, e.g. 0xFF) [!FILL_VALUE_DEFAULT!]: "
if "!FILL_VALUE!"=="" set "FILL_VALUE=!FILL_VALUE_DEFAULT!"

REM -------- Validate key file existence ----------
if not exist "!BOOT_FILE!" (
    echo [ERROR] Bootloader file '!BOOT_FILE!' not found!
    echo ========================================================================
    pause
    exit /b 1
)
if not exist "!APP_FILE!" (
    echo [ERROR] App file '!APP_FILE!' not found!
    echo ========================================================================
    pause
    exit /b 1
)
if not exist "srec_cat.exe" (
    echo [ERROR] srec_cat.exe not found in current directory!
    echo Please put srec_cat.exe in the same folder as this script.
    echo ========================================================================
    pause
    exit /b 1
)

REM -------- Get file size ----------
for %%i in ("!BOOT_FILE!") do set "BOOT_SIZE=%%~zi"
for %%i in ("!APP_FILE!") do set "APP_SIZE=%%~zi"

REM -------- Convert hex address to decimal for calculation ----------
set /a "BOOT_START_DEC=!BOOT_START!"
set /a "APP_START_DEC=!APP_START!"
set /a "BOOT_END_DEC=BOOT_START_DEC + BOOT_SIZE - 1"
set /a "APP_END_DEC=APP_START_DEC + APP_SIZE - 1"
set /a "OFFSET=APP_START_DEC - BOOT_START_DEC"

REM -------- Display merge info ----------
echo.
echo -------- Merge Info --------
echo Boot file:    !BOOT_FILE!
echo Boot start:   !BOOT_START! ^(dec: !BOOT_START_DEC!^)
echo Boot size:    !BOOT_SIZE! bytes
echo Boot end:     0x!BOOT_END_DEC!
echo.
echo App file:     !APP_FILE!
echo App start:    !APP_START! ^(dec: !APP_START_DEC!^)
echo App size:     !APP_SIZE! bytes
echo App end:      0x!APP_END_DEC!
echo.
echo Fill value:   !FILL_VALUE!
echo New file name: !OUTPUT_FILE!
echo ----------------------------
echo.

echo Merging firmware, please wait...
echo.

REM -------- Calculate offset (relative to Boot start) ----------
set /a "OFFSET=APP_START_DEC - BOOT_START_DEC"

REM -------- Merge firmware (Boot + App) ----------
srec_cat.exe ^
    "!BOOT_FILE!" -Binary -offset 0 ^
    -fill !FILL_VALUE! !BOOT_SIZE! !OFFSET! ^
    "!APP_FILE!" -Binary -offset !OFFSET! ^
    -o "!OUTPUT_FILE!" -Binary

if errorlevel 1 (
    echo.
    echo [ERROR] Merge failed! srec_cat returned error code: !errorlevel!
    echo ========================================================================
    pause
    exit /b 1
) else (
    echo.
    echo [SUCCESS] New bin file generated:
    echo   Path: %scriptDir%%OUTPUT_FILE%
    for %%i in ("!OUTPUT_FILE!") do echo   Size: %%~zi bytes
)
echo ========================================================================
pause
exit /b 0
