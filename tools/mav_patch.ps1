# 读-改-写一条 MAVLink 参数消息：先 ReadParam 拿到设备当前值，改掉指定偏移的字段，再整包写回。
#
#   .\tools\mav_patch.ps1 -MsgId 30022 -Crc 124 -Len 33 -Set "32:u8=1"
#   .\tools\mav_patch.ps1 -MsgId 30019 -Crc 8  -Len 44 -Set "0:i64=47032803;24:f32=0.5"
#
# -Set 语法：偏移:类型=值，类型 u8/i8/u16/i16/u32/i32/u64/i64/f32，多条用分号隔开。
# -Len 是消息声明长度：MAVLink v2 会把尾部 0 截掉，写回前要补回原长度，否则改高偏移字段会越界。

param(
    [Parameter(Mandatory = $true)][int]$MsgId,
    [Parameter(Mandatory = $true)][int]$Crc,
    [string]$Port = "COM4",
    [int]$Baud = 921600,
    [string]$Set = "",
    [int]$Len = 0,
    [switch]$Dump,
    [int]$WaitMs = 400
)

function MavCrc([byte[]]$data, [byte]$extra) {
    $crc = 0xFFFF
    $all = New-Object System.Collections.Generic.List[byte]
    $all.AddRange($data)
    $all.Add($extra)
    foreach ($b in $all) {
        $tmp = $b -bxor ($crc -band 0xFF)
        $tmp = ($tmp -bxor ($tmp -shl 4)) -band 0xFF
        $crc = (($crc -shr 8) -bxor ($tmp -shl 8) -bxor ($tmp -shl 3) -bxor ($tmp -shr 4)) -band 0xFFFF
    }
    return $crc
}

function NewFrame([int]$id, [byte[]]$payload, [byte]$crcExtra, [byte]$seq) {
    $b = New-Object System.Collections.Generic.List[byte]
    $b.Add([byte]$payload.Length); $b.Add(0); $b.Add(0); $b.Add($seq); $b.Add(255); $b.Add(190)
    $b.Add([byte]($id -band 0xFF)); $b.Add([byte](($id -shr 8) -band 0xFF)); $b.Add([byte](($id -shr 16) -band 0xFF))
    $b.AddRange($payload)
    $crc = MavCrc -data $b.ToArray() -extra $crcExtra
    $f = New-Object System.Collections.Generic.List[byte]
    $f.Add(0xFD); $f.AddRange($b)
    $f.Add([byte]($crc -band 0xFF)); $f.Add([byte](($crc -shr 8) -band 0xFF))
    return $f.ToArray()
}

$sp = New-Object System.IO.Ports.SerialPort $Port, $Baud, "None", 8, "One"
$sp.ReadTimeout = 300
$sp.Open()
Start-Sleep -Milliseconds 100
$sp.DiscardInBuffer()

# 1) 发 ReadParam，拿回该消息的当前值
$req = NewFrame 30000 ([BitConverter]::GetBytes([uint32]$MsgId)) 43 1
$sp.Write($req, 0, $req.Length)
Start-Sleep -Milliseconds 250
$n = $sp.BytesToRead
$buf = New-Object byte[] $n
if ($n -gt 0) { [void]$sp.Read($buf, 0, $n) }

$payloadLen = 0
$payload = $null
for ($i = 0; $i -lt $n - 1; $i++) {
    if ($buf[$i] -eq 0xFD) {
        $plen = $buf[$i + 1]
        $mid = ([int]$buf[$i + 7]) -bor (([int]$buf[$i + 8]) -shl 8) -bor (([int]$buf[$i + 9]) -shl 16)
        if ($mid -eq $MsgId) {
            $payloadLen = $plen
            $payload = New-Object byte[] ([Math]::Max($plen, 1))
            [Array]::Copy($buf, $i + 10, $payload, 0, $plen)
            break
        }
    }
}
if ($null -eq $payload) {
    "读 $MsgId 失败：没收到回包（端口被占用？设备没响应？）"
    $sp.Close()
    exit 1
}

# 补齐到消息声明长度（v2 会把尾部 0 截掉，写回时补回来才不越界）
if ($Len -gt 0 -and $payload.Length -lt $Len) {
    $tmp = New-Object byte[] $Len
    [Array]::Copy($payload, $tmp, $payload.Length)
    $payload = $tmp
}

# 2) 按 -Set 改字段
# 打印读到的原始载荷（调试用，格式 HEX）
if ($Dump -and $null -ne $payload) {
    "read[$MsgId]: " + (($payload | ForEach-Object { $_.ToString('X2') }) -join '')
}

foreach ($item in ($Set -split ';' | Where-Object { $_ -ne "" })) {
    $parts = $item -split '[:=]'
    $off = [int]$parts[0]
    $type = $parts[1]
    $val = $parts[2]
    $bytes = switch ($type) {
        "u8"  { [byte[]]@([byte]([int]$val)) }
        "i8"  { [byte[]]@([byte]([int]$val -band 0xFF)) }
        "u16" { [BitConverter]::GetBytes([uint16][int]$val) }
        "i16" { [BitConverter]::GetBytes([int16][int]$val) }
        "u32" { [BitConverter]::GetBytes([uint32][double]$val) }
        "i32" { [BitConverter]::GetBytes([int32][double]$val) }
        "u64" { [BitConverter]::GetBytes([uint64][double]$val) }
        "i64" { [BitConverter]::GetBytes([int64][double]$val) }
        "f32" { [BitConverter]::GetBytes([single][double]$val) }
        default { throw "未知类型 $type" }
    }
    if ($off + $bytes.Length -gt $payload.Length) {
        "字段 $item 超出载荷长度 $($payload.Length)，需要 -Len"
        $sp.Close()
        exit 1
    }
    for ($k = 0; $k -lt $bytes.Length; $k++) { $payload[$off + $k] = $bytes[$k] }
}

# 3) 整包写回
$frame = NewFrame $MsgId $payload ([byte]$Crc) 2
$sp.Write($frame, 0, $frame.Length)
Start-Sleep -Milliseconds $WaitMs
$n2 = $sp.BytesToRead
$rbuf = New-Object byte[] $n2
if ($n2 -gt 0) { [void]$sp.Read($rbuf, 0, $n2) }
$sp.Close()

"写 $MsgId 完成：原 ${payloadLen} 字节 -> 发 $($payload.Length) 字节，改 [$Set]，回包 $n2 字节"
