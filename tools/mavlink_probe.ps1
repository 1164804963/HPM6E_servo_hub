# 上位机协议探针：按 MAVLink v2 发一帧 ReadParam，把板子的回包解出来。
#
# 用途：官方 servo_hub 上位机连不上时，先用它确认固件这条链是通的。
#
# 用法：
#   powershell -File tools/mavlink_probe.ps1 -ReadParam 30077     # 读 HeartBit
#   powershell -File tools/mavlink_probe.ps1 -ReadParam 30000     # 读 ReadParam 本身
#   powershell -File tools/mavlink_probe.ps1 -SendHex "FD040000..."  # 直接发原始字节

param(
    [string]$Port = "COM4",
    [int]$Baud = 921600,
    [int]$ReadParam = 0,
    [string]$SendHex = "",
    [switch]$SetHost,
    [switch]$Enable,
    [int]$MsgId = 0,
    [string]$PayloadHex = "",
    [int]$CrcExtra = 0,
    [switch]$Disable,
    [double]$SetVelocity = 0,
    [int]$WaitMs = 700
)

# CRC-16/MCRF4XX（MAVLink 用的就是它，含 crc_extra 那个字节）
function Get-MavCrc {
    param([byte[]]$Data, [byte]$CrcExtra)
    $crc = 0xFFFF
    $bytes = New-Object System.Collections.Generic.List[byte]
    $bytes.AddRange($Data)
    $bytes.Add($CrcExtra)
    foreach ($b in $bytes) {
        $tmp = $b -bxor ($crc -band 0xFF)
        $tmp = ($tmp -bxor ($tmp -shl 4)) -band 0xFF
        $crc = (($crc -shr 8) -bxor ($tmp -shl 8) -bxor ($tmp -shl 3) -bxor ($tmp -shr 4)) -band 0xFFFF
    }
    return $crc
}

function New-MavFrame {
    param([int]$MsgId, [byte[]]$Payload, [byte]$CrcExtra, [byte]$Seq = 1, [byte]$SysId = 255, [byte]$CompId = 190)
    $len = $Payload.Length
    $body = New-Object System.Collections.Generic.List[byte]
    $body.Add([byte]$len)
    $body.Add(0)                 # incompat
    $body.Add(0)                 # compat
    $body.Add($Seq)
    $body.Add($SysId)
    $body.Add($CompId)
    $body.Add([byte]($MsgId -band 0xFF))
    $body.Add([byte](($MsgId -shr 8) -band 0xFF))
    $body.Add([byte](($MsgId -shr 16) -band 0xFF))
    $body.AddRange($Payload)
    $crc = Get-MavCrc -Data $body.ToArray() -CrcExtra $CrcExtra
    $frame = New-Object System.Collections.Generic.List[byte]
    $frame.Add(0xFD)
    $frame.AddRange($body)
    $frame.Add([byte]($crc -band 0xFF))
    $frame.Add([byte](($crc -shr 8) -band 0xFF))
    return $frame.ToArray()
}

# 把收到的字节流切成帧，打印每帧的 msgid / 长度 / 载荷
function Read-Frames {
    param([byte[]]$Buf)
    $i = 0
    $count = 0
    while ($i -lt $Buf.Length) {
        if ($Buf[$i] -ne 0xFD -and $Buf[$i] -ne 0xFE) { $i++; continue }
        $magic = $Buf[$i]
        if ($i + 2 -gt $Buf.Length) { break }
        $plen = $Buf[$i + 1]
        $total = if ($magic -eq 0xFD) { 10 + $plen + 2 } else { 6 + $plen + 2 }
        if ($i + $total -gt $Buf.Length) { break }
        $hdr = if ($magic -eq 0xFD) { 10 } else { 6 }
        $msgid = if ($magic -eq 0xFD) {
            ([int]$Buf[$i + 7]) -bor (([int]$Buf[$i + 8]) -shl 8) -bor (([int]$Buf[$i + 9]) -shl 16)
        } else {
            $Buf[$i + 5]
        }
        $payload = $Buf[($i + $hdr)..($i + $hdr + $plen - 1)]
        $hex = ($payload | ForEach-Object { $_.ToString('X2') }) -join ' '
        "frame#{0}: magic=0x{1:X2} msgid={2} len={3} payload=[{4}]" -f $count, $magic, $msgid, $plen, $hex
        $count++
        $i += $total
    }
    if ($count -eq 0) { "no valid frame in {0} bytes" -f $Buf.Length }
}

# 消息表：只放常用几个，够验证链路即可
$msgTable = @{
    30000 = @{ name = 'ReadParam'; len = 4; crc = 43 }
    30077 = @{ name = 'HeartBit'; len = 1; crc = 45 }
    30001 = @{ name = 'ScopeConfig'; len = 0; crc = 0 }
}

$sp = New-Object System.IO.Ports.SerialPort $Port, $Baud, "None", 8, "One"
$sp.ReadTimeout = 100
$sp.Open()
Start-Sleep -Milliseconds 150
$sp.DiscardInBuffer()

if ($SendHex -ne "") {
    $bytes = ($SendHex -split '\s+|,' | Where-Object { $_ -ne '' } | ForEach-Object { [Convert]::ToByte($_, 16) })
    $sp.Write([byte[]]$bytes, 0, $bytes.Count)
    "TX raw: $($bytes.Count) bytes"
}
elseif ($SetVelocity -ne 0) {
    # 读回 AppMotionParam(30059)，改 Target_velocity（偏移 44），整包写回。
    # 这是上位机下发转速的原始流程，手工验证用。
    $req = New-MavFrame -MsgId 30000 -Payload ([BitConverter]::GetBytes([uint32]30059)) -CrcExtra 43
    $sp.Write($req, 0, $req.Length)
    Start-Sleep -Milliseconds 300
    $n = $sp.BytesToRead
    $buf = New-Object byte[] $n
    if ($n -gt 0) { [void]$sp.Read($buf, 0, $n) }
    $payload = New-Object byte[] 95
    for ($i = 0; $i -lt $n - 1; $i++) {
        if ($buf[$i] -eq 0xFD) {
            $plen = $buf[$i + 1]
            for ($k = 0; $k -lt [Math]::Min($plen, 95); $k++) { $payload[$k] = $buf[$i + 10 + $k] }
            break
        }
    }
    [BitConverter]::GetBytes([float]$SetVelocity).CopyTo($payload, 44)
    $frame = New-MavFrame -MsgId 30059 -Payload $payload -CrcExtra 221
    $sp.Write($frame, 0, $frame.Length)
    "TX AppMotionParam(Target_velocity={0} rpm) : {1} bytes" -f $SetVelocity, $frame.Length
}elseif ($MsgId -ne 0) {
    # 通用发送：-MsgId 30056 -PayloadHex "03" -CrcExtra 26
    $bytes = @()
    if ($PayloadHex -ne "") {
        $bytes = ($PayloadHex -split '\s+|,' | Where-Object { $_ -ne '' } | ForEach-Object { [byte][Convert]::ToByte($_, 16) })
    }
    $frame = New-MavFrame -MsgId $MsgId -Payload ([byte[]]$bytes) -CrcExtra ([byte]$CrcExtra)
    $sp.Write($frame, 0, $frame.Length)
    "TX msgid={0} payload[{1}] : {2} bytes" -f $MsgId, $PayloadHex, $frame.Length
}elseif ($Enable) {
    # AppControlWord(30054)：Controlword=1(使能)、Halt_running_cmd=0
    $payload = [byte[]]@(1, 0, 0)
    $frame = New-MavFrame -MsgId 30054 -Payload $payload -CrcExtra 108
    $sp.Write($frame, 0, $frame.Length)
    "TX AppControlWord(Controlword=1 enable) : {0} bytes" -f $frame.Length
}
elseif ($Disable) {
    # AppControlWord(30054)：Controlword=0(失能)
    $payload = [byte[]]@(0, 0, 0)
    $frame = New-MavFrame -MsgId 30054 -Payload $payload -CrcExtra 108
    $sp.Write($frame, 0, $frame.Length)
    "TX AppControlWord(Controlword=0 disable) : {0} bytes" -f $frame.Length
}elseif ($SetHost) {
    # AppPermissionConfig(30068)：Comm_control_authority=0(HOST)、Internal_control_authority=0(APP)
    $payload = [byte[]]@(0, 0)
    $frame = New-MavFrame -MsgId 30068 -Payload $payload -CrcExtra 134
    $sp.Write($frame, 0, $frame.Length)
    "TX AppPermissionConfig(Comm=HOST, Internal=APP) : {0} bytes" -f $frame.Length
}elseif ($ReadParam -ne 0) {
    $payload = [BitConverter]::GetBytes([uint32]$ReadParam)
    $frame = New-MavFrame -MsgId 30000 -Payload $payload -CrcExtra 43
    $sp.Write($frame, 0, $frame.Length)
    "TX ReadParam(struct_id={0}) : {1} bytes" -f $ReadParam, $frame.Length
}
else {
    "nothing to send, use -ReadParam <id> or -SendHex <hex>"
}

Start-Sleep -Milliseconds $WaitMs
$n = $sp.BytesToRead
$buf = New-Object byte[] $n
if ($n -gt 0) { [void]$sp.Read($buf, 0, $n) }
$sp.Close()

"RX: $n bytes"
if ($n -gt 0) {
    "raw: {0}" -f (($buf | ForEach-Object { $_.ToString('X2') }) -join ' ')
    Read-Frames -Buf $buf
}
