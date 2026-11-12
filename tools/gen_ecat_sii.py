#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""生成 ESC 模拟 EEPROM 的 SII 头文件（embedded_project/HPM6E80/Board/ecat_eeprom.h）。

用法：
    python tools/gen_ecat_sii.py [模板 eeprom.h] [-o 输出头文件]

模板默认用 my_ecat_cia402 工程里已经在这块板上验证过的 2048 字节 SII
（app/SSC/Src/eeprom.h）。脚本只做三件事：
  1) 身份区改为本工程 ESI（YuanHub_EtherCAT_Slave_LAN925x.xml）里的
     Vendor / Product / Revision / Serial；
  2) 过程数据 SM2/SM3 长度按实际 PDO 映射使能（26 / 44 字节）；
  3) 重算配置区 CRC-8（多项式 0x07、初值 0xFF、覆盖 word0..word6，结果放 word7 低字节）。

改 ESI 的 PDO 之后重新跑一遍即可，不要手改生成出来的数组。
"""
import argparse
import os
import re
import sys

# 与本工程 ESI 保持一致（communication/protocol/EtherCAT_LAN925x/*.xml）
VENDOR = 0x00000000
PRODUCT = 0x00009252
REVISION = 0x00000004
SERIAL = 0x00000000

# PDO 映射算出来的过程数据长度（字节）：
#   RxPDO 0x1600..0x1603 = 4 + 8 + 8 + 6      = 26
#   TxPDO 0x1A00..0x1A03 = 12 + 12 + 10 + 10  = 44
OUTPUT_SIZE = 26
INPUT_SIZE = 44

DEFAULT_TEMPLATE = r"D:\Documents\SoftwareProject\YeeZi_HPM6E\MyProject\my_ecat_cia402\app\SSC\Src\eeprom.h"
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
DEFAULT_OUT = os.path.join(ROOT, "embedded_project", "HPM6E80", "Board", "ecat_eeprom.h")


def crc8(buf):
    """ETG.1000.6 配置区校验：poly 0x07，初值 0xFF。"""
    crc = 0xFF
    for b in buf:
        crc ^= b
        for _ in range(8):
            crc = ((crc << 1) ^ 0x07) & 0xFF if crc & 0x80 else (crc << 1) & 0xFF
    return crc


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("template", nargs="?", default=DEFAULT_TEMPLATE, help="模板 eeprom.h")
    ap.add_argument("-o", "--output", default=DEFAULT_OUT, help="输出头文件")
    args = ap.parse_args()

    if not os.path.exists(args.template):
        sys.exit("模板不存在: %s" % args.template)

    raw = open(args.template, encoding="utf-8", errors="ignore").read()
    body = raw[raw.index("{"):]
    data = bytes(int(x, 16) for x in re.findall(r"0x([0-9A-Fa-f]{2})", body))
    if len(data) != 2048:
        sys.exit("模板不是 2048 字节（%d）" % len(data))
    d = bytearray(data)

    def w(off, val):
        d[off] = val & 0xFF
        d[off + 1] = (val >> 8) & 0xFF

    def rdw(off):
        return d[off] | (d[off + 1] << 8)

    # ---- 身份区（word 8..13）---------------------------------------------
    w(0x10, VENDOR & 0xFFFF)
    w(0x12, (VENDOR >> 16) & 0xFFFF)
    w(0x14, PRODUCT & 0xFFFF)
    w(0x16, (PRODUCT >> 16) & 0xFFFF)
    w(0x18, REVISION & 0xFFFF)
    w(0x1A, (REVISION >> 16) & 0xFFFF)
    w(0x1C, SERIAL & 0xFFFF)
    w(0x1E, (SERIAL >> 16) & 0xFFFF)

    # ---- SYNCM 分类（type 41）里的 SM2/SM3 长度与使能位 --------------------
    def find_category(typ):
        a = 0x40
        while a < 0x400:
            t, n = rdw(a * 2), rdw(a * 2 + 2)
            if t == 0xFFFF:
                break
            if t == typ:
                return a
            a += 2 + n
        sys.exit("找不到分类 %d" % typ)

    syncm = find_category(41) * 2 + 4     # 跳过分类头，指向 SM0
    if rdw(syncm) != 0x1000 or rdw(syncm + 8) != 0x1080:
        sys.exit("模板的 SYNCM 结构不是预期布局，先人工确认")
    # SM 条目布局：word0 地址、word1 长度、byte4 控制、byte5 保留、byte6 使能、byte7 类型
    w(syncm + 18, OUTPUT_SIZE)            # SM2 = Outputs
    d[syncm + 22] = 0x01
    w(syncm + 26, INPUT_SIZE)             # SM3 = Inputs
    d[syncm + 30] = 0x01
    # SM3 控制字保持模板的 1-buffer(0x20)：实测改成 3-buffer(0x24) 后
    # 主站 SAFEOP 请求会被从站静默拒绝（AL Status 停在 PREOP、StatusCode=0），
    # 所以回退。要走 FreeRun/轮询模式还需要另外打通，见 doc 待办。
    d[syncm + 28] = 0x20

    # ---- 配置区 CRC -------------------------------------------------------
    d[14] = crc8(d[0:14])

    lines = []
    lines.append("/*")
    lines.append(" * [ECAT 适配] ESC 模拟 EEPROM 的 SII 内容（ETG.1000.6，2048 字节）。")
    lines.append(" *")
    lines.append(" * 由 tools/gen_ecat_sii.py 从已验证模板生成，改动只有：")
    lines.append(" *   1) 身份区：Vendor=0x%08X Product=0x%08X Rev=0x%08X Serial=0x%08X"
                 % (VENDOR, PRODUCT, REVISION, SERIAL))
    lines.append(" *      —— 与本工程 ESI YuanHub_EtherCAT_Slave_LAN925x.xml 对齐；")
    lines.append(" *   2) 过程数据 SM：SM2(Outputs 0x1100)=%d 字节、SM3(Inputs 0x1400)=%d 字节，均使能；"
                 % (OUTPUT_SIZE, INPUT_SIZE))
    lines.append(" *   3) 配置区 CRC（字节 14）按字 0..6 重算。")
    lines.append(" *")
    lines.append(" * 启动时由 hpm_ecat_e2p_emulation.c 的 ecat_flash_eeprom_init() 写进 Flash 模拟 EEPROM")
    lines.append(" * （BOARD_ECAT_FLASH_EMULATE_EEPROM_ADDR = 0x200000）。改 ESI 的 PDO 后重新生成，勿手改。")
    lines.append(" */")
    lines.append("#ifndef ECAT_EEPROM_DATA_H")
    lines.append("#define ECAT_EEPROM_DATA_H")
    lines.append("")
    lines.append("unsigned char aEepromData[2048] = {")
    for i in range(0, 2048, 16):
        lines.append("    " + ",".join("0x%02X" % b for b in d[i:i + 16]) + ",")
    lines.append("};")
    lines.append("")
    lines.append("#endif /* ECAT_EEPROM_DATA_H */")
    lines.append("")

    with open(args.output, "w", encoding="utf-8", newline="\n") as f:
        f.write("\n".join(lines))
    print("written: %s (%d bytes)" % (args.output, os.path.getsize(args.output)))


if __name__ == "__main__":
    main()
