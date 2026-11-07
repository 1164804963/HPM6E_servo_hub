# 直接调 ServoHub PC Monitor 的 MCP 后端（127.0.0.1:8848，按行 JSON-RPC）。
#
# 不用 stdio 桥也能用：后端是纯 TCP + 一行一条 JSON，token 放在请求里。
#
#   .\tools\servohub_mcp.ps1 -List
#   .\tools\servohub_mcp.ps1 -Tool app_info
#   .\tools\servohub_mcp.ps1 -Tool settings_get -ArgsJson '{"name":"scope_settings.json"}'

param(
    [string]$Host_ = "127.0.0.1",
    [int]$Port = 8848,
    [string]$Token = "servohub-local",
    [string]$Tool = "",
    [string]$ArgsJson = "{}",
    [switch]$List,
    [string]$RawJson = "",
    [int]$TimeoutSec = 30
)

function Send-Rpc {
    param([string]$Line)
    $client = New-Object System.Net.Sockets.TcpClient
    $client.Connect($Host_, $Port)
    $stream = $client.GetStream()
    $stream.ReadTimeout = $TimeoutSec * 1000
    $writer = New-Object System.IO.StreamWriter($stream)
    $reader = New-Object System.IO.StreamReader($stream)
    $writer.AutoFlush = $true
    $writer.WriteLine('{"jsonrpc":"2.0","id":1,"method":"initialize","params":{"protocolVersion":"2024-11-05","capabilities":{},"clientInfo":{"name":"dsh","version":"1"}},"token":"' + $Token + '"}')
    [void]$reader.ReadLine()
    $writer.WriteLine($Line)
    $back = $reader.ReadLine()
    $client.Close()
    return $back
}

if ($RawJson -ne "") {
    Send-Rpc -Line $RawJson
    return
}

if ($List) {
    $back = Send-Rpc -Line ('{"jsonrpc":"2.0","id":2,"method":"tools/list","params":{},"token":"' + $Token + '"}')
    ($back | ConvertFrom-Json).result.tools | ForEach-Object { "{0,-24} {1}" -f $_.name, $_.description }
    return
}

if ($Tool -eq "") {
    "usage: -List | -Tool <name> [-ArgsJson '<json>'] | -RawJson '<json>'"
    return
}

$line = '{"jsonrpc":"2.0","id":3,"method":"tools/call","params":{"name":"' + $Tool + '","arguments":' + $ArgsJson + '},"token":"' + $Token + '"}'
$back = Send-Rpc -Line $line
$obj = $back | ConvertFrom-Json
if ($obj.error) {
    "ERROR: $($obj.error.message)"
    return
}
foreach ($item in $obj.result.content) {
    if ($item.type -eq "text") { $item.text }
}
