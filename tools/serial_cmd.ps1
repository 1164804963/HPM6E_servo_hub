# 串口调试小工具：发一行命令，收固定时长的回复。
# 用于 ComAssistant 没开的时候直接和板子上的调试台对话。
#
# 用法：
#   powershell -NoProfile -File tools/serial_cmd.ps1 -Command "st"
#   powershell -NoProfile -File tools/serial_cmd.ps1 -Command "mode 127" -WaitMs 500

param(
    [string]$Port = "COM4",
    [int]$Baud = 921600,
    [string]$Command = "",
    [int]$WaitMs = 800
)

$sp = New-Object System.IO.Ports.SerialPort $Port, $Baud, "None", 8, "One"
$sp.ReadTimeout = 100
$sp.WriteTimeout = 1000

try {
    $sp.Open()
} catch {
    Write-Error "打开 $Port 失败：$($_.Exception.Message)"
    exit 1
}

Start-Sleep -Milliseconds 150
$sp.DiscardInBuffer()

if ($Command -ne "") {
    $sp.Write($Command + "`r")
}

# 收数据直到"静默 400ms"或超时，避免固定窗口把一行截断
$t0 = Get-Date
$lastByteAt = Get-Date
$sb = New-Object System.Text.StringBuilder
while ($true) {
    $chunk = ""
    try {
        $chunk = $sp.ReadExisting()
    } catch {
    }
    if ($chunk -ne "") {
        [void]$sb.Append($chunk)
        $lastByteAt = Get-Date
    }
    $now = Get-Date
    if (($now - $lastByteAt).TotalMilliseconds -ge 400 -and $sb.Length -gt 0) { break }
    if (($now - $t0).TotalMilliseconds -ge $WaitMs) { break }
    Start-Sleep -Milliseconds 10
}

$sp.Close()
$sb.ToString()
