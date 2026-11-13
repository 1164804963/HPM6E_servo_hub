# HPM6EMotorV20 原理图文字说明

- 来源 PDF：`D:\Document\YeeZi_HPM6E\YeeZi HPM6E开发板资料\1 图纸\HPM6EMotorV20.pdf`
- 原 PDF SHA256：`76C6EA76656F3B567C44B2C6FACE5BB2FA17E3A954AD39D573E7E40C3F3514D1`
- 页数：9 页（page-1 至 page-9）；核验范围覆盖全部 9 页。
- 本文用途：让没有 PDF 阅读能力的 AI 或工程师，仅凭文字即可理解板级供电、主控、功率驱动、采样、接口与调试链路。
- 本文是独立文档，不依赖工作目录中的中间提取文件；文中的图示事实均已按 9 页原理图图像核对，拓扑计算与设计意图另行标注。
- 本文明确区分“图示事实”“拓扑推导”和“未知/装配不确定”。未核实的连接不会被写成确定连接。

## 1. 阅读约定

1. 网络标签大小写按原图保留，例如 `+5V`、`+5P`、`VBUS`、`+3V3`、`+3V3A`、`+3.3VD`、`+1.8VD`、`5V_QEI`、`5V_RS`、`VCC_3V3`、`SNSU_P`、`Z_U`、`G0_MDI0_P`。
2. `NC` 画在引脚上表示该引脚未连接；`NC/0Ω`、`NC/10K`、`NC/120Ω`、`DNP` 表示可选器件按图示不装；模式表中的 `x` 表示“不关心”，不是 DNP。没有装配 BOM 时，只能说明图纸意图，不能保证实物状态。
3. `0Ω`、`10Ω`、`33Ω`、`2.49K` 等均为图中标注值；`10mR`、`10mΩ` 表示采样电阻。
4. 元件位号后的引脚号来自原理图符号。图中 `BSC040N10NS5` 的八脚符号中 `1/2/3` 为源极、`4` 为栅极、`5/6/7/8` 为漏极；`2N7002` 等 SOT-23 器件不套用这套编号，实际封装以器件手册为准。
5. 文本提取（page-N.txt）存在字符重复、左右文字交错、相邻文字被拼到同一行的问题。本文只把其中可被图像核验或可被网络名/位号明确支持的内容作为事实；不能从“文字相邻”推断“电气相连”。
6. 页脚（Title、Size、Date、File、Drawn By、Sheet of）在本文中省略。图框边缘的 `1..8`、`A..D` 是图幅分区，不是网络名；端口名后的小红数字是跨页/跨图编号，不是引脚号。
7. 本文用 `网络A -> 元件(引脚) -> 网络B` 表示关键拓扑。箭头只表示信号/功率流向，不表示元件内部结构。
8. 所有“推断”均以 `【推断】` 标注；所有“未核实”均以 `【待核实】` 标注。

## 2. 全板系统框图（文字形式）

```text
主控：U3 HPM6E8YIGN1，U3A/U3B/U3C/U3D 是同一器件的不同符号分部。

主电源：J6(5) VM -> U1/L1 -> +5V -> U2/L2/FB4 -> +3V3
                      |        |-> U11/FB3 -> +3V3A（MCU模拟电源、温度与钳位）
                      |        |-> U10/FB1/FB2 -> VREF（ADC参考与电流偏置参考）
                      |        |-> R70 -> 5V_QEI -> U20 -> 5V_RS
                      |        |-> U16 -> +5P -> J4总线供电
                      |                    |-> U14 -> VBUS -> D25 -> +5V
                      |-> U9 VS；U9 REG12引出 +12VREG
调试USB供电：J13 VBUS -> D4 -> +5V
MCU内核供电：+3V3 -> FB6 -> U3 DCDC_IN；U3 DCDC_LP -> L5 -> FB5 -> VDD_SOC

电机驱动：U3 PD0..PD5 -> U9 -> Q1/Q4、Q2/Q5、Q3/Q6 -> OUT_U/V/W -> J6(1/2/3)
电流反馈：PR1/2/3(10mΩ，下桥臂采样) -> U6差分放大 -> I_U/V/W -> PF28/29/30
          I_U/V/W -> 带对地负载的汇合网络 -> CP -> U9(1)及PF9
相电压：OUT_U/V/W -> 分压及耦合网络 -> PU/PV/PW、OUT_M
        PU/PV/PW与OUT_M -> U5 -> Z_U/V/W -> PF5/6/7；OUT_M -> Z_M -> PF10
母线电压：VM -> 分压/钳位 -> VBUS_VOL -> PF31
温度：U18及选配R182 -> NTC1 -> PF8
制动：VM -> J5外接电阻 -> Q11 -> BGND；Q12控制Q11栅极，BRAKE至Q12连接未见画出

通信：PB0..PB11、PF0..PF3 -> U4外部千兆PHY -> RJ1
      PA16..PA31 -> 集成PHY相关线路 -> J1/J2双口EtherCAT
      PC16..PC18、PC29..PC31 -> U12/U13 -> J8/J9双CAN
      PC/PD/PF部分端口 -> U8/U7/U19/U21 -> J14编码器、霍尔与RS485复用
存储：PB26..PB31 -> U17 QSPI Flash
USB应用口：U3专用USB0_DP/DN -> L10及U15保护 -> J4
调试：J13 -> U22 FT2232HL -> U24总线开关 -> MCU JTAG/UART；外部接口J7/J12
扩展与人机：J10显示/触摸、J11通用IO、SW1..SW6、LED1..LED6
```

GND、AGND、BGND、DCDC_GND 通过图示 0Ω 电阻连接。电容、TVS 等并联保护元件在上述功能框图中省略，逐页章节给出它们的实际连接。

## 3. 电源域、地与上电关系

### 3.1 电源域清单

| 电源域 | 产生方式 | 主要负载 | 备注 |
|---|---|---|---|
| `VM` | 外部电机母线，经 J6-5 引入 | U1 输入、U9 VS、三相桥 Q1/Q2/Q3 漏极、制动 Q11 | 图中未见 VM 的输入额定值；不能从 63V 电容或 100V MOS 反推板额定 |
| `+5V` | U1 LM5164DDAR 降压，L1 68uH | U2、U10、U11、U16、U12/U13、U20、LED 等 | D1 SMF5.0A 保护；C4 47uF/16V |
| `+3V3` | U2 SM8082AAAC 降压，L2 4.7uH，经 FB4 | 数字/IO、U3 VCC_3V3、U8 A 侧、U21、上拉 | FB4 = BLM18EG101TN1D |
| `VCC_3V3` | `+3V3` 经 R7 0Ω | U3 VIO_B01、VPLLVUSB | 不是独立电源 |
| `+3.3VD` | `+3V3` 经 R118 0Ω | U22 FT2232HL、U24、调试接口 | 调试域 |
| `+1.8VD` | U22 FT2232HL VREGOUT(49) | U22 VCORE 内核与相关去耦；VCCIO 使用 +3.3VD | 不是外部 LDO |
| `+3V3A` | U11 LP5907MFX-3.3，输入 +5V 经 FB3 | U3 VANA（经FB7）、U18、选配R182、D27钳位 | U5/U6 实际由 +3V3 供电；U10 由 +5V 供电 |
| `VREF` | U10 REF3033AIDBZR，OUT 经 FB2 | U3 VREFH、U6D 分压、ADC 基准 | 3.3V 基准 |
| `+12VREG` | U9 STDRIVE101 REG12(5) | U9 内部、制动 Q11 栅极上拉 | 不是独立 12V 输入，也不是外置稳压器 |
| `+5P` | U16 AP2151WG-7 OUT(1)，输入 +5V | J4 VBUS 四脚、U14 IN | 注意是 `+5P`，不是 `+5V` |
| `VBUS` | U14 PW1515 OUT(1)，输入 +5P | D25 到 +5V；USB0_VBUS 检测 | USB0 供电/检测链，详见第 8 页 |
| `5V_QEI` | +5V 经 R70 0Ω | U8 B 侧、编码器/差分接口 | 编码器 5V 域 |
| `5V_RS` | U20 MT9700 输出，输入 5V_QEI | U7、U19、RS485/差分接收 | 受 RSPWON 控制 |
| `DCDC_GND` | U3 DCDC_GND 经 R8 0Ω 到 GND | U3 内部 DCDC 地 | 与 GND 同电位（0Ω） |
| `AGND` | 模拟地 | U10/U11/U18/U6/U5、采样 | 经 R59 0Ω 到 GND |
| `BGND` | 功率桥地 | U9 EP、PR1/2/3 下端、Q11 源极、J6-4 | 经 R164 0Ω 到 GND |

### 3.2 地体系

图示事实：

- `AGND` 与 `GND` 通过 `R59 0Ω` 连接。
- `GND` 与 `BGND` 通过 `R164 0Ω` 连接。
- `DCDC_GND` 与 `GND` 通过 `R8 0Ω` 连接。
- 因而 GND/AGND/BGND/DCDC_GND 在电气上不是隔离地，而是单点/低阻连接的不同铜皮名称。图中没有隔离电源、隔离运放或隔离收发器。

【推断】这种命名主要用于分开数字噪声、模拟小信号和功率回路，实际 PCB 的铺铜与单点位置需看 PCB，原理图不能证明 Kelvin 采样或地回流质量。

### 3.3 上电与供电链（按图）

```text
VM -> U1(2 VIN, 3 EN/UVLO) -> U1(8 SW) -> L1(68uH) -> +5V
+5V -> U2(4 IN) -> U2(3 LX) -> L2(4.7uH) -> 输出节点 -> FB4 -> +3V3
+5V -> U11(1 IN) -> U11(5 OUT) -> +3V3A
+5V -> FB1 -> U10(1 IN) -> U10(2 OUT) -> FB2 -> VREF
+5V -> U16(5 IN) -> U16(1 OUT) -> +5P -> J4 VBUS 四脚
+5P -> U14(5 IN) -> U14(1 OUT) -> VBUS -> D25 -> +5V
+5V -> R70 0Ω -> 5V_QEI -> U20(5 VIN) -> U20(1 VOUT) -> 5V_RS
VM -> U9(4 VS)（经 R116 0Ω） -> U9(5 REG12) -> +12VREG
J13 VBUS -> D4 SS14 -> +5V（调试 USB 可反灌 +5V）
外部 VBAT / +3V3 -> D2 BAT54C 共阴极 -> R11 0Ω -> U3(N4 VBAT)
```

图示事实：U1 的 PGOOD(5) 未见外接网络。
【待核实】`+5V` 与 `VBUS` 经 D25 形成“+5V -> U16 -> +5P -> U14 -> VBUS -> D25 -> +5V”的环路。按图 U16 与 U14 都是使能可控的开关，实际是“板供 USB”还是“USB 供板”，取决于 U16/U14 的使能组合与固件；不能从原理图直接断言 USB PD、OTG 或防反灌能力。

## 4. 逐页模块说明

### 4.1 第 1 页 power：一次电源、MCU 电源、基准、复位、时钟

页面文件：`File: D:\work\..\power.SchDoc`。

#### 4.1.1 U1 LM5164DDAR：VM 到 +5V

图示事实：

| 项目 | 连接/参数 |
|---|---|
| 输入 | `VM` -> U1(2 VIN)，同时 -> U1(3 EN/UVLO) |
| 地 | U1(1 GND)、U1(9 EP) -> GND |
| RON | U1(4 RON) -> R6 47K -> GND |
| 开关 | U1(8 SW) -> L1 `SWPA6045S680MT` 68uH -> `+5V` |
| 自举 | U1(7 BST) -> C1 2.2nF -> U1(8 SW) |
| 反馈 | `+5V` -> R4 200K -> U1(6 FB)；U1(6 FB) -> R5 62K -> GND |
| 输入电容 | `VM` -> C3 2.2uF/63V -> GND |
| 输出电容 | `+5V` -> C4 47uF/16V -> GND |
| 输出保护 | `+5V` -> D1 `SMF5.0A` -> GND |
| PGOOD | U1(5 PGOOD) 未见连接 |

关键拓扑：

```text
VM -> U1(2 VIN) -> U1 内部 -> U1(8 SW) -> L1 -> +5V
+5V -> R4(200K) -> U1(6 FB) -> R5(62K) -> GND
U1(7 BST) -> C1(2.2nF) -> U1(8 SW)
```

反馈分压由 R4/R5 设定；图中输出命名为 +5V，未另外给出 FB 内部基准，本文不据猜测基准计算精确输出。

#### 4.1.2 U2 SM8082AAAC：+5V 到 +3V3

图示事实：

| 项目 | 连接/参数 |
|---|---|
| 输入 | `+5V` -> U2(4 IN)；输入电容 C5 22uF、C6 22uF、C7 100nF 到 GND |
| 使能 | U2(1 EN) -> R2 10K -> `+5V` |
| 地 | U2(2 GND) -> GND |
| 开关 | U2(3 LX) -> L2 `SLO322512T4R7MTT` 4.7uH 2A -> 输出节点 |
| 反馈 | 输出节点 -> R3 100K -> U2(5 FB)；U2(5 FB) -> R1 22.1K -> GND；C2 22pF 跨 R3 |
| 输出滤波 | 输出节点 -> C8 22uF、C9 22uF -> GND；再经 FB4 `BLM18EG101TN1D` -> `+3V3`；FB4 后 C10 22uF、C11 22uF |
| 电源指示 | `+3V3` -> R69 2K -> LED2（`LED_RED`） -> GND |

关键拓扑：

```text
+5V -> U2(4 IN) -> U2(3 LX) -> L2(4.7uH) -> Vout
Vout -> R3(100K) -> U2(5 FB) -> R1(22.1K) -> GND
Vout -> C8/C9(22uF) -> GND
Vout -> FB4(BLM18EG101TN1D) -> +3V3 -> C10/C11(22uF) -> GND
+3V3 -> R69(2K) -> LED2 -> GND
```

反馈分压由 R3/R1 设定；图中电源名为 +3V3，本文不从未给出的内部 FB 基准推导精确输出。

#### 4.1.3 U3A：HPM6E8YIGN1 电源单元

U3A/U3B/U3C/U3D 是同一颗 `HPM6E8YIGN1` 的四个符号单元，不是四颗 MCU。

图示事实：

| 引脚组 | 球号 | 连接 | 去耦/外围 |
|---|---|---|---|
| VDD_SOC | H9、G9、G6、F9、F6 | `VDD_SOC` | C16 22uF、C17 22uF、C18/C19/C20/C21/C22 各 100nF 到 GND |
| DCDC_LP | N2、P3 | 经 L5 `SLO322512T4R7MTT` 4.7uH 2A 到滤波节点；该节点经 FB5 `BLM18EG101TN1D` 到 `VDD_SOC` | C27 22uF、C28 22uF、C29 100nF 到 GND |
| DCDC_IN | M1、M2 | `+3V3` 经 FB6 `BLM18EG101TN1D` | C34 22uF、C35 22uF、C36 100nF 到 DCDC_GND |
| DCDC_GND | N1、P2 | `DCDC_GND` 经 R8 0Ω 到 GND | 与 DCDC_IN 电容回流配套 |
| VDD_PMCCAP | K8 | `VDD_PMCCAP` | C12 100nF、C13 4.7uF 到 GND |
| VDD_OTPCAP | K7 | `VDD_OTPCAP` | C14 4.7uF、C15 100nF 到 GND |
| VDD_PHY0CAP | J6 | `VDD_PHY0CAP` | C23 100nF、C24 4.7uF 到 GND |
| VDD_PHY1CAP | H6 | `VDD_PHY1CAP` | C25 4.7uF、C26 100nF 到 GND |
| VIO_B01 | K6、E8、E7、E6 | `VCC_3V3` | C30/C31/C32/C33 各 100nF 到 GND；`VCC_3V3` 经 R7 0Ω 到 `+3V3` |
| VPLLVUSB | E9 | `VCC_3V3` | C37 100nF 到 GND |
| VPMC | P4 | 经 R10 10Ω 到 `+3V3` | C43 100nF 到 GND |
| USB0_VBUS | L12 | 经 R9 10Ω 到 `VBUS` | C40 100nF 到 GND |
| RSTN | M3 | 网络 `RSTN` | 见 4.1.5 |
| WKUP | L3 | 网络 `WAKEUP` | 见 4.1.5 |
| USB0_DP | L14 | `USB0_DP` | 到 USB0 连接器侧 |
| USB0_DN | L13 | `USB0_DN` | 到 USB0 连接器侧 |
| XTALI | K14 | `XTALI` | X3 24MHz |
| XTALO | K13 | `XTALO` | X3 24MHz |
| VREFH | K9 | `VREF` | C38 100nF、C39 4.7uF 到 AGND |
| VREFL | J8 | `AGND` |  |
| VANA | J9 | `+3V3A` 经 FB7 `BLM18EG101TN1D` | C41 100nF、C42 4.7uF 到 AGND |
| VSSA | H8 | `AGND` |  |
| VBAT | N4 | 经 R11 0Ω 到 D2 共阴极 | C44 100nF 到 GND |
| VSS | A1、A14、E5、E10、F7、F8、G7、G8、P14、P1、N3、K10、K5、J7、H7 | 全部接 GND | 与 VSSA、DCDC_GND 的连接分别记录 |

关键拓扑：

```text
VDD_SOC -> FB5(BLM18EG101TN1D) -> L5(4.7uH) -> U3A(N2/P3 DCDC_LP)
+3V3 -> FB6(BLM18EG101TN1D) -> U3A(M1/M2 DCDC_IN)
U3A(N1/P2 DCDC_GND) -> R8(0Ω) -> GND
VCC_3V3 -> R7(0Ω) -> +3V3
+3V3 -> R10(10Ω) -> U3A(P4 VPMC)
VBUS -> R9(10Ω) -> U3A(L12 USB0_VBUS)
+3V3A -> FB7(BLM18EG101TN1D) -> U3A(J9 VANA)
VBAT_EXT / +3V3 -> D2 BAT54C 共阴极 -> R11(0Ω) -> U3A(N4 VBAT)
```

【待核实】`VDD_SOC` 是 U3 内部 DCDC 经 L5/FB5 产生的内核域，不能写成“外部 +3V3 直接给 VDD_SOC”。图中没有给出 VDD_SOC 的目标电压，不应猜测 1.1V/1.2V 等数值。
【待核实】U3A 的 `VDD_PMCCAP`、`VDD_OTPCAP`、`VDD_PHY0CAP`、`VDD_PHY1CAP` 是内部稳压节点，不能描述为“给其他模块供电的电源输出”。

#### 4.1.4 VREF、+3V3A 与 AGND

图示事实：

- U10 `REF3033AIDBZR`：`+5V` 经 FB1 `BLM18EG101TN1D` 到 U10(1 IN)；U10(2 OUT) 经 FB2 `BLM18EG101TN1D` 到 `VREF`；U10(3 GND) 到 `AGND`。
- FB1 前：C116 10uF、C117 100nF 到 GND；FB1 后：C118 10uF、C119 100nF 到 AGND。
- U10 输出侧：C120 22uF（U10 OUT 到 AGND）、C121 100nF（VREF 到 AGND）。
- `R59 0Ω` 连接 `AGND` 与 `GND`。
- U11 `LP5907MFX-3.3/NOPB`：`+5V` 经 FB3 `BLM18EG101TN1D` 到 U11(1 IN)；U11(5 OUT) = `+3V3A`；U11(2 GND) = `AGND`；U11(3 EN) 经 R60 10K 上拉到 `+5V`；U11(4 N/C) 未接。
- U11 输入 C122 4.7uF；输出 C123 100nF、C124 10uF。

关键拓扑：

```text
+5V -> FB1 -> U10(1 IN) -> U10(2 OUT) -> FB2 -> VREF
U10(3 GND) -> AGND
AGND -> R59(0Ω) -> GND
+5V -> FB3 -> U11(1 IN) -> U11(5 OUT) -> +3V3A
+5V -> R60(10K) -> U11(3 EN)
```

【推断】U10 是 3.3V 串联基准，U11 是 3.3V LDO；两者都为模拟侧服务，但 U10 的 `VREF` 还直接进 U3 的 VREFH，因此 `VREF` 同时是 ADC 基准和运放偏置参考。

#### 4.1.5 复位、唤醒、24MHz 晶振、VBAT

图示事实：

- `SW1`（`BTN4.5X4.5`）：按下把 `RSTN` 拉低；`RSTN` 经 R12 10K 上拉到 `+3V3`；C47 100nF 从 `RSTN` 到 GND；网络名 `RSTN`，图注另有 `RSTN`（旁边 1 为跨页号） 跨页标记。
- `SW2`（`BTN4.5X4.5`）：按下把 `WAKEUP` 拉高（接 `+3V3`）；`WAKEUP` 经 R14 10K 下拉到 GND；C48 100nF 从 `WAKEUP` 到 GND。
- `X3` 24MHz ±10ppm：1 XIN -> `XTALI`，3 XOUT -> `XTALO`，2/4 GND；R13 1M 跨 XIN/XOUT；C45 12pF 从 XIN 到 GND；C46 12pF 从 XOUT 到 GND。
- `J3` 标 `MX1.25-2P`，局部放大确认：左侧信号 `1 = VBAT`、`2 = GND`；右侧另有两个标 `G` 的端接 GND。`G` 端在图中未注机械/屏蔽含义，不能据此把信号 1 误判为接地。
- `D2` `BAT54C` 共阴极把 `+3V3` 与外部 `VBAT` 二极管或合，经 R11 0Ω 到 U3(N4 VBAT)；C44 100nF 到 GND。
- `D2` 的封装/引脚按图：两个阳极分别接 `+3V3` 和 `VBAT`，共阴极输出到 R11。

关键拓扑：

```text
+3V3 -> R12(10K) -> RSTN -> SW1 -> GND
RSTN -> C47(100nF) -> GND
+3V3 -> SW2 -> WAKEUP -> R14(10K) -> GND
WAKEUP -> C48(100nF) -> GND
XTALI -> X3(1 XIN)；XTALO -> X3(3 XOUT)；R13(1M) 跨 XIN/XOUT
XTALI -> C45(12pF) -> GND；XTALO -> C46(12pF) -> GND
```

- `J3` 的 `1=VBAT`、`2=GND` 是信号针；右侧两个 `G` 端只按图记录为接 GND，其机械/屏蔽定义图中未注，不能据此推断信号 1 也接地。
- `RSTN` 同时被 SW1、R12、C47、U3(M3) 以及第 9 页 FT2232 的 `FT_RESET_N` 经 R149 0Ω 驱动；图中 `RSTN`（旁边 1 为跨页号） 的 `1` 是跨页编号，按同一 `RSTN` 网络处理，不另列为命名冲突。

### 4.2 第 2 页 io：主控 IO、J10、J11

页面文件：`File: D:\work\..\io.SchDoc`。

#### 4.2.1 U3B/U3C/U3D：端口与网络

图示事实（端口名 -> 网络/用途）：

| 端口 | 网络/用途 | 端口 | 网络/用途 |
|---|---|---|---|
| PA00..PA09 | 见 4.2.2 与 JTAG/BOOT/以太网表 | PB00..PB11 | RTL8211E RGMII 信号（见第 5 页） |
| PA16..PA19 | P1 以太网 RD/TD 差分（第 6 页） | PB24 | `LED_G` |
| PA20..PA23 | P0 以太网 RD/TD 差分（第 6 页） | PB25 | `LED_R` |
| PA24 | `P1RBIAS` | PB26 | QSPI `D0` |
| PA25 | `P1LED1` | PB27 | QSPI `D1` |
| PA26 | `P1LED0` | PB28 | QSPI `D2` |
| PA27 | `P0RBIAS` | PB29 | QSPI `SCLK` |
| PA28 | `P0LED1` | PB30 | QSPI `CS0` |
| PA29 | `P0LED0` | PB31 | QSPI `D3` |
| PA30 | `MDIO`（集成 PHY 侧） | PC00 | `HU` |
| PA31 | `MDC`（集成 PHY 侧） | PC01 | `HV` |
| PC02 | `HW` | PC03 | J10 `RESET` |
| PC04 | J10 `DC/RS` | PC05 | `QEIZ` |
| PC06 | `QEIB` / `SEI0_RX` | PC07 | `QEIA` / `SEI0_TX` |
| PC08 | J10 `LED` | PC09 | J10 `T_IRQ` |
| PC10 | J10 `SCLK` | PC11 | J10 `CS` |
| PC12 | J10 `MISO` | PC13 | J10 `MOSI` |
| PC14 | `KEYA` | PC15 | `KEYB` |
| PC16 | `CAN4_TXD` | PC17 | `CAN4_RXD` |
| PC18 | `CAN4_STBY` | PC19 | `KEYC` |
| PC20 | J10 `T_SCLK` | PC21 | J10 `T_CS` |
| PC22 | J10 `T_MISO` | PC23 | J10 `T_MOSI` |
| PC24 | J11-11 | PC25 | J11-27 |
| PC26 | J11-31 | PC27 | `BRAKE` |
| PC28 | J11-10 | PC29 | `CAN7_STBY` |
| PC30 | `CAN7_RXD` | PC31 | `CAN7_TXD` |
| PD00 | `IN_UH` | PD01 | `IN_UL` |
| PD02 | `IN_VH` | PD03 | `IN_VL` |
| PD04 | `IN_WH` | PD05 | `IN_WL` |
| PD06 | `RSDE` | PD07 | `RSPWON` |
| PD08 | J11-42 | PD09 | J11-7 |
| PD10 | J11-8 | PD11 | J11-9 |
| PD12 | `SEI2_CK`（经 R196 22Ω 到 `QEIZ`） | PD13 | `SEI2DE` |
| PD14 | `SEI2RXD` / `UART_RX11` | PD15 | `SEI2TXD` / `UART_TX11` |
| PD16 | J11-12 | PD17 | J11-3 |
| PD18 | J11-4 | PD19 | J11-14 |
| PD20 | J11-5 | PD21 | J11-6 |
| PD22 | J11-16 | PD23 | J11-22 |
| PD24 | J11-13 | PD25 | J11-24 |
| PD26 | J11-15 | PD27 | J11-23 |
| PD28 | J11-17 | PD29 | J11-26 |
| PD30 | J11-18 | PD31 | J11-21 |
| PF00 | `RTL_MDC` | PF01 | `RTL_MDIO` |
| PF02 | `RTL_RST` | PF03 | `RTL_INT` |
| PF04 | `SEI0CK` | PF05 | `Z_U` / `ACMP0_CH0_IN4` |
| PF06 | `Z_V` / `ACMP0_CH0_IN5` | PF07 | `Z_W` / `ACMP0_CH0_IN3` |
| PF08 | `NTC1` | PF09 | `CP` |
| PF10 | `Z_M` / `ACMP0_CH0_IN6` | PF11 | J11-32 |
| PF12 | J11-28 | PF13 | J11-25 |
| PF14 | J11-29 | PF15 | J11-30 |
| PF16 | J11-33 | PF17 | J11-34 |
| PF18 | `USB0_ID` | PF19 | J11-41 |
| PF20 | J11-38 | PF21 | J11-39 |
| PF22 | `USB0_PWR` | PF23 | `USB0_OC` |
| PF24 | J11-40 | PF25 | J11-37 |
| PF26 | J11-35 | PF27 | J11-36 |
| PF28 | `I_U` | PF29 | `I_V` |
| PF30 | `I_W` | PF31 | `VBUS_VOL` |

说明：

- 表中 PF00..PF03 的 `RTL_MDC/RTL_MDIO/RTL_RST/RTL_INT` 是 RTL8211E 的外部 PHY 管理/复位/中断；PA30/PA31 的 `MDIO/MDC` 是第 6 页集成 PHY/EtherCAT 口的管理总线。两组用途不同，不存在原图冲突，不要混为一组。
- 完整的 142 条 GPIO/球位/板级用途表见第 5 节；本节只按功能块分组，不再重复逐球号。
- `A13` 球位存在原图标注冲突：芯片框内名称为 `PC24`，左侧外部网络标签为 `PC23`；下一行 `B14` 的框内和外部网络均为 `PC24`。本文按外部网络记录 `PC23=A13`、`PC24=B14`，不能声称已用官方芯片手册确认该复用关系。
- `PA10..PA15`、`PB12..PB23` 等未在 U3B/U3C/U3D 图中画出的端口，本文不补写。

#### 4.2.2 J10：MSP2402 显示/扩展接口

图示事实：

| J10 引脚 | 网络 | 说明 |
|---|---|---|
| 1 VCC | 两条选配：`+5V` 经 0Ω；`+3V3` 经 `NC/0Ω` | 位号未分配，图上写作 `R?`/`R?`，不能当作已装配 |
| 2 GND | GND |  |
| 3 CS | `PC11` | 片选 |
| 4 RESET | `PC03` | 复位 |
| 5 DC/RS | `PC04` | 数据/命令 |
| 6 MOSI | `PC13` | SPI MOSI |
| 7 SCLK | `PC10` | SPI 时钟 |
| 8 LED | `PC08` | 背光/指示灯 |
| 9 MISO | `PC12` | SPI MISO |
| 10 T_SCLK | `PC20` | 触摸 SPI 时钟 |
| 11 T_CS | `PC21` | 触摸片选 |
| 12 T_MOSI | `PC23` | 触摸 MOSI |
| 13 T_MISO | `PC22` | 触摸 MISO |
| 14 T_IRQ | `PC09` | 触摸中断 |
| 15 Hall | `BGND` | 符号标注 `Hall`，不能据此断定是霍尔传感器 |
| 16 Hall | `BGND` | 同上 |

关键拓扑：

```text
+5V -> R?(0Ω) -> J10(1 VCC)
+3V3 -> R?(NC/0Ω) -> J10(1 VCC)
J10(3 CS) -> PC11；J10(4 RESET) -> PC03；J10(5 DC/RS) -> PC04
J10(6 MOSI) -> PC13；J10(7 SCLK) -> PC10；J10(9 MISO) -> PC12
J10(15/16 Hall) -> BGND
```

【待核实】J10 的 VCC 选择电阻位号在图中未分配（`R?`），且 `+5V 0Ω` 与 `+3V3 NC/0Ω` 只能装其一；不能从图判断实物装的是 5V 还是 3.3V。

#### 4.2.3 J11：2×22 通用 IO 排针

图示事实（逐脚）：

| 引脚 | 网络 | 引脚 | 网络 |
|---|---|---|---|
| 1 | `+5V` | 2 | `+5V` |
| 3 | `PD17` | 4 | `PD18` |
| 5 | `PD20` | 6 | `PD21` |
| 7 | `PD9` | 8 | `PD10` |
| 9 | `PD11` | 10 | `PC28` |
| 11 | `PC24` | 12 | `PD16` |
| 13 | `PD24` | 14 | `PD19` |
| 15 | `PD26` | 16 | `PD22` |
| 17 | `PD28` | 18 | `PD30` |
| 19 | `GND` | 20 | `GND` |
| 21 | `PD31` | 22 | `PD23` |
| 23 | `PD27` | 24 | `PD25` |
| 25 | `PF13` | 26 | `PD29` |
| 27 | `PC25` | 28 | `PF12` |
| 29 | `PF14` | 30 | `PF15` |
| 31 | `PC26` | 32 | `PF11` |
| 33 | `PF16` | 34 | `PF17` |
| 35 | `PF26` | 36 | `PF27` |
| 37 | `PF25` | 38 | `PF20` |
| 39 | `PF21` | 40 | `PF24` |
| 41 | `PF19` | 42 | `PD8` |
| 43 | `+3V3` | 44 | `+3V3` |

【待核实】J11 的 1/2、43/44 是电源脚，19/20 是地脚；其余均为 MCU 端口直出，没有串联电阻或 ESD 器件。实际可承受电压/电流需查 MCU 与连接器规格。

### 4.3 第 3 页 bridge：STDRIVE101、三相桥、采样电阻、制动

页面文件：`File: D:\work\..\bridge.SchDoc`。

#### 4.3.1 PWM 输入网络

图示事实：

- `PD0` -> `IN_UH`
- `PD1` -> `IN_UL`
- `PD2` -> `IN_VH`
- `PD3` -> `IN_VL`
- `PD4` -> `IN_WH`
- `PD5` -> `IN_WL`
- `PC27` -> `BRAKE`
- `PF9` -> `CP`

【待核实】`BRAKE` 只在页面左上出现网络标签，未见它连到右上 Q12 栅极驱动节点的导线或同名标签；这是图内断点/跨页疑点，不能补写为已连接。

#### 4.3.2 U9 STDRIVE101 引脚表

| U9 引脚 | 名称 | 连接/网络 |
|---|---|---|
| 1 | CP | `CP`（与第 4 页 CP 求和网络相连；内部功能按芯片手册） |
| 2 | DT/MODE | 经 R75 0Ω 到 `BGND` |
| 3 | SCREF | `SCREF`（过流参考；与 `CP` 不是同一网络） |
| 4 | VS | 经 R116 0Ω 到 `VM` |
| 5 | REG12 | `+12VREG` |
| 6 | nFAULT | `FAULT` |
| 7 | INH1/IN1 | `IN_UH` |
| 8 | INH2/IN2 | `IN_VH` |
| 9 | INH3/IN3 | `IN_WH` |
| 10 | INL1/EN1 | `IN_UL` |
| 11 | INL2/EN2 | `IN_VL` |
| 12 | INL3/EN3 | `IN_WL` |
| 13 | BOOT3 | C79 1uF 到 `OUT_W` |
| 14 | GHS3 | 到 Q3 栅极驱动 |
| 15 | OUT3 | `OUT_W` |
| 16 | GLS3 | 到 Q6 栅极驱动 |
| 17 | BOOT2 | C78 1uF 到 `OUT_V` |
| 18 | GHS2 | 到 Q2 栅极驱动 |
| 19 | OUT2 | `OUT_V` |
| 20 | GLS2 | 到 Q5 栅极驱动 |
| 21 | BOOT1 | C75 1uF 到 `OUT_U` |
| 22 | GHS1 | 到 Q1 栅极驱动 |
| 23 | OUT1 | `OUT_U` |
| 24 | GLS1 | 到 Q4 栅极驱动 |
| 25 | EP | `BGND` |

外围：

- C75/C78/C79 各 1uF：分别跨 BOOT1-OUT_U、BOOT2-OUT_V、BOOT3-OUT_W。
- C76 1uF、C77 100nF：`VS` 到 `BGND`。
- C80 4.7uF、C81 100nF：`+12VREG` 到 `BGND`。
- `+12VREG` 只由 U9(5 REG12) 产生，板上没有独立的 12V 输入或外置 12V 稳压器。

#### 4.3.3 三相桥 Q1..Q6

器件：Q1/Q2/Q3/Q4/Q5/Q6 均为 `BSC040N10NS5`，N 沟道 MOSFET。

| 桥臂 | 上管 | 下管 | 相输出 | 采样电阻 |
|---|---|---|---|---|
| U 相 | Q1 | Q4 | `OUT_U` | PR1 10mΩ |
| V 相 | Q2 | Q5 | `OUT_V` | PR2 10mΩ |
| W 相 | Q3 | Q6 | `OUT_W` | PR3 10mΩ |

关键拓扑（以 U 相为例）：

```text
VM -> Q1(漏 5/6/7/8) -> Q1(源 1/2/3) -> OUT_U
OUT_U -> Q4(漏 5/6/7/8) -> Q4(源 1/2/3) -> PR1(1/2) -> BGND
PR1(3) -> SNSU_P；PR1(4) -> SNSU_N
J6(1) -> OUT_U；J6(2) -> OUT_V；J6(3) -> OUT_W；J6(4) -> BGND；J6(5) -> VM
C140 220uF/63V、C141 220uF/63V：VM 到 BGND
C72/C73/C74 各 220nF/100V：VM 到 BGND（各桥臂就近去耦，不是跨相输出）
```

栅极驱动：

| MOS | 驱动网络 | 串联栅阻 | 跨栅阻二极管 | 栅源下拉 |
|---|---|---|---|---|
| Q1 | GHS1 | R66 33Ω | D8 BAT43WS-7-F，跨 R66 | R72 22K |
| Q2 | GHS2 | R67 33Ω | D9 BAT43WS-7-F，跨 R67 | R73 22K |
| Q3 | GHS3 | R68 33Ω | D10 BAT43WS-7-F，跨 R68 | R74 22K |
| Q4 | GLS1 | R76 33Ω | D11 BAT43WS-7-F，跨 R76 | R82 22K |
| Q5 | GLS2 | R77 33Ω | D12 BAT43WS-7-F，跨 R77 | R83 22K |
| Q6 | GLS3 | R78 33Ω | D13 BAT43WS-7-F，跨 R78 | R84 22K |

二极管与 **33Ω 串联栅阻** 并联，22K 电阻则从 MOS 栅极到自身源极；两者不是跨同一对节点。二极管提供一个方向的栅极充放电旁路，具体开关动态需结合其方向和驱动器输出分析。

PR1/PR2/PR3 为四端 10mΩ：1/2 为功率端，3 为 SNSx_P，4 为 SNSx_N。原理图表达分开取样，但无法证明 PCB 的实际 Kelvin 走线。

#### 4.3.4 FAULT、SCREF

图示事实：

- `FAULT`：`+3V3` -> R88 10K -> `FAULT`；`+3V3` -> R89 2K -> LED4（`LED_RED`） -> `FAULT`。U9(6 nFAULT) 也接 `FAULT`。
- 本页未见 `FAULT` 接 MCU 的引脚，不能补出“故障中断 IO”。
- `SCREF`：R95 0Ω 到 `+3V3`；R97 10K 到 `BGND`；C87 100nF 也接到 `BGND`，只有 C87 旁标 `NC`。
- 图旁注：`Open (default): SC protection enabled` / `Closed: SC protection disabled`。

【待核实】SCREF 的“Open/Closed”没有明确开关位号，也没有画出跳线/开关器件；不能确定实际默认装配。`SCREF` 只接 U9(3) 与 R95/R97/C87，和 `CP` 是两个不同的网络；具体阈值由 R95/R97 及 U9 内部决定，图中未给公式。

#### 4.3.5 制动电路

图示事实：

```text
+12VREG -> R63 10K -> Q11(4 栅)
Q11(4 栅) -> R65 200K -> Q11(1/2/3 源) -> BGND
VM -> J5(2) -> 外接制动电阻 -> J5(1) -> Q11(漏 5/6/7/8)
R62 NC/10mΩ 跨 J5 两端
Q12(2N7002)：漏 -> Q11(4 栅)；源 -> BGND
Q12 栅 -> R139 10Ω -> 节点；该节点 -> R64 10K -> +3V3；C139 10nF 栅源
```

- J5 标 `CON2`，旁注“外接大功率电阻，刹车电阻”。
- Q11 为 `BSC040N10NS5`。
- 【待核实】`BRAKE` 网络未见图内连到 Q12 栅极节点；不能把 `PC27` 直接写成“制动 PWM 已连接到 Q12”。
- 按图 Q12 栅极经 R64 上拉到 `+3V3`（该连接已由图像确认），默认可能使 Q12 导通、Q11 关断；但 `BRAKE` 的极性、有效电平、是否低有效，以及 `PC27 -> BRAKE` 如何接到 Q12 栅极，图中未见，不能补写软件制动控制逻辑。

### 4.4 第 4 页 monitor：母线电压、相电压、电流、温度、比较器、CP

页面文件：`File: D:\work\..\monitor.SchDoc`。

#### 4.4.1 模拟输出到 MCU 的网络

| 网络 | MCU 引脚 | 来源 |
|---|---|---|
| `I_U` | PF28 | U6A 电流差分放大 |
| `I_V` | PF29 | U6B 电流差分放大 |
| `I_W` | PF30 | U6C 电流差分放大 |
| `Z_U` | PF5 / ACMP0_CH0_IN4 | U5A 输出；R85 可选 0Ω 到 PU（默认不装） |
| `Z_V` | PF6 / ACMP0_CH0_IN5 | U5B 输出；R86 可选 0Ω 到 PV（默认不装） |
| `Z_W` | PF7 / ACMP0_CH0_IN3 | U5C 输出；R87 可选 0Ω 到 PW（默认不装） |
| `Z_M` | PF10 / ACMP0_CH0_IN6 | OUT_M 经 R184 1K |
| `VBUS_VOL` | PF31 | VM 分压 |
| `NTC1` | PF8 | MCP9700 与选配 NTC |
| `CP` | PF9 | 三相电流求和/滤波；同时去 U9(1) |

#### 4.4.2 母线电压 VBUS_VOL

图示事实：

```text
VM -> R140 200K -> VBUS_VOL 节点
VBUS_VOL 节点 -> R179 10K -> AGND
VBUS_VOL 节点 -> C142 1nF -> AGND
VBUS_VOL 节点 -> D27 LMBR160FT1G -> +3V3A（上钳位）
VBUS_VOL 节点 -> D28 LMBR160FT1G -> AGND（下钳位）
VBUS_VOL -> U3(PF31)
```

【推断】理想分压比 `VBUS_VOL = VM × 10K/(200K+10K) = VM/21`。D27/D28 把节点限制在 AGND 与 +3V3A 之间；实际钳位电压还要加二极管正向压降。

#### 4.4.3 相电压分压与 OUT_M

图示事实：

```text
OUT_U -> R15 62K -> PU
OUT_V -> R17 62K -> PV
OUT_W -> R20 62K -> PW
PU -> R24 2.4K -> AGND；PU -> C50 100nF -> AGND
PV -> R23 2.4K -> AGND；PV -> C51 100nF -> AGND
PW -> R22 2.4K -> AGND；PW -> C52 100nF -> AGND
PU -> R16 2.4K -> OUT_M
PV -> R18 2.4K -> OUT_M
PW -> R21 2.4K -> OUT_M
OUT_M -> R184 1K -> Z_M
```

注意对应关系：R22 对应 PW，R23 对应 PV，R24 对应 PU；R16/R18/R21 分别对应 U/V/W 的汇合电阻。

【推导】三路不是彼此独立的 62K/2.4K 分压，而是通过 R16/R18/R21 共同汇到 OUT_M，互相有负载关系。按三路对称、忽略电容、R85/R86/R87 默认不装、比较器和 Z_M 输入高阻的条件，可写成（详见第 15 节）：

```text
V(OUT_M) ≈ 0.037267 × [V(OUT_U)+V(OUT_V)+V(OUT_W)]/3
V(PU) - V(OUT_M) ≈ 0.018987 × [V(OUT_U) - Vavg]
```

其中 `Vavg = [V(OUT_U)+V(OUT_V)+V(OUT_W)]/3`。不能把每一路机械套成孤立的 `2.4/(62+2.4)=0.0373` 分压；R184 1K 与 Z_M 输入侧还构成限流/滤波。具体时间常数需把 MCU 输入电容和 PCB 寄生一起算，图中未给全。

#### 4.4.4 比较器 U5 LM339（Z_U/Z_V/Z_W）

图示事实（按图注）：

| 单元 | 同相输入 | 反相输入 | 输出 |
|---|---|---|---|
| U5A | 6（`PU` 直连） | 7（`OUT_M`） | 1（`Z_U`） |
| U5B | 5（`PV` 直连） | 4（`OUT_M`） | 2（`Z_V`） |
| U5C | 9（`PW` 直连） | 8（`OUT_M`） | 14（`Z_W`） |

- `PU` 直连 U5A 同相 6；R85 `NC/0Ω` 跨接 `Z_U` 与 `PU`，默认不装。
- `PV` 直连 U5B 同相 5；R86 `NC/0Ω` 跨接 `Z_V` 与 `PV`，默认不装。
- `PW` 直连 U5C 同相 9；R87 `NC/0Ω` 跨接 `Z_W` 与 `PW`，默认不装。
- 输出上拉：R19/R180/R181 各 4.7K 到 `+3V3`；C49/C143/C144 各 100nF 从输出到 `AGND`。
- U5 电源：3 -> `+3V3`，12 -> `AGND`，C91 100nF。
- U5D：11（+）、10（-）悬空，13 输出未接。

关键拓扑：

```text
PU -> U5A(6 +)
OUT_M -> U5A(7 -)
U5A(1 输出) -> Z_U
R85(NC/0Ω) 跨 Z_U 与 PU（默认不装）
PV -> U5B(5 +)
OUT_M -> U5B(4 -)
U5B(2 输出) -> Z_V
R86(NC/0Ω) 跨 Z_V 与 PV（默认不装）
PW -> U5C(9 +)
OUT_M -> U5C(8 -)
U5C(14 输出) -> Z_W
R87(NC/0Ω) 跨 Z_W 与 PW（默认不装）
```

- 默认 `NC` 时，比较器输入 `PU/PV/PW` 与输出 `Z_U/Z_V/Z_W` 是分开的，比较器按“相电压节点对 OUT_M”正常比较；这不是“输入输出已经被短接”。
- 若装配 R85/R86/R87 为 0Ω，则对应相的 `PU/PV/PW` 与输出 `Z_U/Z_V/Z_W` 被同网连接，比较器输入输出被短接，配置目的和是否能正常工作需要另行确认。这是选装 0Ω 的后果，不是默认状态下的重复标签错误。

#### 4.4.5 电流差分放大 U6 TP2274-TR

U6 为四运放 `TP2274-TR`，供电：4 -> `+3V3`，11 -> `AGND`，C55 100nF。

U 相：

```text
SNSU_N -> R26 1K -> U6A(2 -)
SNSU_P -> R29 1K -> U6A(3 +)
U6A(1 输出) -> R25 10K || C53 27pF -> U6A(2 -)
U6A(3 +) -> R30 10K || C56 27pF -> 共用偏置（U6D 输出）
U6A(1 输出) -> R27 10Ω -> I_U
I_U -> C54 10nF -> AGND
```

V 相：

```text
SNSV_N -> R32 1K -> U6B(6 -)
SNSV_P -> R36 1K -> U6B(5 +)
U6B(7 输出) -> R31 10K || C57 27pF -> U6B(6 -)
U6B(5 +) -> R38 10K || C61 27pF -> 共用偏置
U6B(7 输出) -> R33 10Ω -> I_V
I_V -> C59 10nF -> AGND
```

W 相：

```text
SNSW_N -> R41 1K -> U6C(9 -)
SNSW_P -> R44 1K -> U6C(10 +)
U6C(8 输出) -> R40 10K || C62 27pF -> U6C(9 -)
U6C(10 +) -> R45 10K || C65 27pF -> 共用偏置
U6C(8 输出) -> R42 10Ω -> I_W
I_W -> C64 10nF -> AGND
```

共用偏置：

```text
VREF -> R35 10K -> 节点 -> R39 10K -> AGND
节点 -> C63 100nF -> AGND
节点 -> U6D(12 +)
U6D(13 -) -> U6D(14 输出)
U6D(14 输出) -> C60 100nF -> AGND
U6D(14 输出) -> R30/R38/R45 的偏置端
```

- C53/C56/C57/C61/C62/C65 均为 27pF ±5%、0402。
- 【推断】U6D 把 VREF 经 10K/10K 分压得到 VREF/2，作为三路差分放大的共模偏置；因此 I_U/I_V/I_W 是围绕 VREF/2 的双极性电流信号，不是从 0V 开始的单极性信号。

#### 4.4.6 三相电流求和 CP

图示事实：

```text
I_U -> R28 10K -> 求和节点
I_V -> R34 10K -> 求和节点
I_W -> R43 10K -> 求和节点
求和节点 -> R37 1.1K -> AGND
求和节点 -> C58 3.3nF -> AGND
求和节点 -> R117 10Ω -> CP
CP -> U3(PF9)
CP -> U9(1 CP)
```

【推导】把 I_U/I_V/I_W 视为理想电压源、忽略 R117 后级负载，则

```text
V(CP) ≈ [V(I_U) + V(I_V) + V(I_W)] / [3 + 10000/1100]
      ≈ 0.082707 × 三路电压之和
```

零分流电流时三路各约 1.65V，因此 CP 直流基线约 0.4094V。该式不是简单相加或平均；只在运放输出阻抗足够低、R117 后级输入阻抗足够高时成立。CP 同时连 U9 的 CP 脚和 MCU PF9，原图未直接给出 CP 触发阈值或软件阈值，不能把该基线当成保护阈值。

#### 4.4.7 温度 NTC1

图示事实：

```text
+3V3A -> U18(1 VDD)
U18(3 GND) -> AGND
U18(2 VOUT) -> NTC1
+3V3A -> C145 100nF -> AGND
+3V3A -> R182 NC/HNTC0603-103F3450FA（10kΩ at 25°C） -> NTC1
NTC1 -> R183 4.7K -> AGND
NTC1 -> C146 33nF -> AGND
NTC1 -> U3(PF8)
```

- U18 为 `MCP9700` 模拟温度传感器。
- R182 是“NC/HNTC0603-103F3450FA”可选热敏电阻，与 MCP9700 输出并在同一 `NTC1` 网络。
- 【推断】板上温度可由 MCP9700 的模拟电压读取；若装配 R182，则 NTC 分压也会叠加到同一节点，二者不能同时作为独立通道使用。具体装配关系需看 BOM。

### 4.5 第 5 页 ethernet：RTL8211E 千兆 PHY 与 RJ45

页面文件：`File: D:\work\..\enternet.SchDoc`（原图文件名拼写如此）。

#### 4.5.1 U4 RTL8211E-VB-CG

图示主要引脚与电源：

| U4 引脚 | 符号名称 | 连接/网络 |
|---|---|---|
| 19 | RXC | 经 R121 33Ω 接 RTL_RXCK（MCU PB5） |
| 14 | RXD[0]/SELRGV | RTL_RXD0（PB1），R123 4.7K 上拉 +3V3 |
| 16 | RXD[1]/TXDLY | RTL_RXD1（PB2） |
| 17 | RXD[2]/AN0 | RTL_RXD2（PB3） |
| 18 | RXD[3]/AN1 | RTL_RXD3（PB4） |
| 13 | RXCTL/PHY_AD | RTL_RXDV（PB0） |
| 22 | TXC | 经 R128 33Ω 接 RTL_TXCK（PB6） |
| 23/24/25/26 | TXD[0..3] | RTL_TXD0..3（PB7..PB10） |
| 27 | TXCTL | RTL_TXEN（PB11） |
| 30 | MDC | RTL_MDC（PF0），R130 4.7K 上拉 |
| 31 | MDIO | RTL_MDIO（PF1），R132 4.7K 上拉 |
| 29 | PHYRSTB | RTL_RST（PF2），R131 4.7K 上拉、C101 100nF 到 GND |
| 20 | INTB | RTL_INT（PF3），R137 4.7K 上拉 |
| 38 | ENSWREG | R129 4.7K 上拉 +3V3 |
| 32 | LED2/RXDLY | G0-RXDLY 配置网络 |
| 33 | PMEB | 未接（图中叉号） |
| 12 | NC | 未接 |
| 39 | RSET | R138 2.49K 到 GND |
| 42/43 | CKXTAL1/CKXTAL2 | X1 25MHz ±10ppm，C113/C114 各 18pF 到 GND |
| 46 | CLK125 | 画出引脚，未见外接网络；不将其写作 25MHz 时钟源 |
| 48 | REG_OUT | 经 L8 FTC252010S4R7MBCA 4.7uH / 1.4A 到 VDD10 |
| 6/41 | AVDD33 | +3V3；C99 100nF、C100 10uF 到 GND |
| 15/21/37 | DVDD33 | +3V3 |
| 44/45 | VDDREG | +3V3；与 DVDD33 共供电，C102..C105 各 100nF，C106 10uF 到 GND |
| 3/9/40 | AVDD10 | VDD10 |
| 36/28 | DVDD10 | VDD10 |
| 47/49 | GND/EPAD | GND |
| 11/10 | MDI[3]-/+ | G0_MDI3_N/P |
| 8/7 | MDI[2]-/+ | G0_MDI2_N/P |
| 5/4 | MDI[1]-/+ | G0_MDI1_N/P |
| 2/1 | MDI[0]-/+ | G0_MDI0_N/P |
| 34 | LED0/PHY_AD0 | G0_ACTIVITY |
| 35 | LED1/PHY_AD1 | G0_LINK |

VDD10 去耦：C107 10uF，C108/C109/C110 各 100nF，C111/C112 各 100nF。其他配置电阻：RTL_RXD2 经 R61 4.7K 上拉；RTL_RXD3 经 R122 4.7K 上拉；RTL_RXD1 经 R124 4.7K 上拉、经 R125 NC/4.7K 可选下拉；G0-RXDLY 经 R126 4.7K 上拉、经 R127 NC/4.7K 可选下拉。上拉均到 +3V3，下拉到 GND。图中这些线路兼有复位配置名称，但本文不从电阻值擅自推定全部 PHY 地址、时钟延迟或自协商配置位。

#### 4.5.2 RJ1 HR911130A 与 MDI 映射

图示事实：

| RJ1 引脚 | 连接 |
|---|---|
| 1 | GND |
| 2 | `G0_MDI0_P` |
| 3 | `G0_MDI0_N` |
| 4 | `G0_MDI1_P` |
| 5 | `G0_MDI2_N` |
| 6 | `G0_MDI2_P` |
| 7 | `G0_MDI1_N` |
| 8 | `G0_MDI3_P` |
| 9 | `G0_MDI3_N` |
| 10 | 经 C115 1nF/2kV 到 GND |
| SH1/SH2 | 屏蔽地到 GND |

对应关系（PHY -> RJ）：

```text
U4(1 MDI0_P) -> RJ1(2)
U4(2 MDI0_N) -> RJ1(3)
U4(4 MDI1_P) -> RJ1(4)
U4(5 MDI1_N) -> RJ1(7)
U4(7 MDI2_P) -> RJ1(6)
U4(8 MDI2_N) -> RJ1(5)
U4(10 MDI3_P) -> RJ1(8)
U4(11 MDI3_N) -> RJ1(9)
```

- RJ1 内部含磁性器件（HR911130A），所以 PHY 侧到 RJ 侧没有再画独立变压器。
- RJ1 LED 实际连接：G0_LINK 经 R133 330Ω 到 RJ1(12)，RJ1(11) 接 +3V3，G0_LINK 同时经 R134 4.7K 上拉 +3V3；G0_ACTIVITY 经 R135 4.7K 下拉到 GND，同时直连 RJ1(14)，RJ1(13) 经 R136 330Ω 到 GND。按原图逐端记录，不将两个 LED 改写成同一种驱动接法。

### 4.6 第 6 页 ethercat：双 RJ45 口 J1/J2

页面文件：`File: D:\work\..\ethercat.SchDoc`。

#### 4.6.1 端口与 MCU 引脚

图示事实：

| 端口 | MCU 引脚 | 网络 |
|---|---|---|
| P0 RD_N | PA20 | `P0RD_N` |
| P0 RD_P | PA21 | `P0RD_P` |
| P0 TD_N | PA22 | `P0TD_N` |
| P0 TD_P | PA23 | `P0TD_P` |
| P0 RBIAS | PA27 | `P0RBIAS` |
| P0 LED1 | PA28 | `P0LED1` |
| P0 LED0 | PA29 | `P0LED0` |
| P1 RD_N | PA16 | `P1RD_N` |
| P1 RD_P | PA17 | `P1RD_P` |
| P1 TD_N | PA18 | `P1TD_N` |
| P1 TD_P | PA19 | `P1TD_P` |
| P1 RBIAS | PA24 | `P1RBIAS` |
| P1 LED1 | PA25 | `P1LED1` |
| P1 LED0 | PA26 | `P1LED0` |
| MDIO | PA30 | `MDIO` |
| MDC | PA31 | `MDC` |

- R46/R53 各 2.49K：`P0RBIAS`/`P1RBIAS` 到 GND。
- R51/R52 各 4.7K：`MDIO`/`MDC` 上拉到 `+3V3`。
- 本页把 MCU 侧差分对直接接到带磁性的 RJ45，页内没有第二颗外部 PHY。不能把 J1/J2 写成“另有两颗 PHY”。

#### 4.6.2 J1/J2 HR911105A 引脚表

J1、J2 引脚定义相同：

| 引脚 | 名称 | 连接 |
|---|---|---|
| 1 | TD+ | 端口 TD_P |
| 2 | TD- | 端口 TD_N |
| 3 | RD+ | 端口 RD_P |
| 4 | TD 中心抽头 | C67/C70 10nF 到 GND |
| 5 | RD 中心抽头 | C66/C69 10nF 到 GND |
| 6 | RD- | 端口 RD_N |
| 7 | NC | 未接 |
| 8 | CHS GND | C68/C71 10nF 到 GND |
| 9 | 绿色 LED 阳极 | P0LED1 / P1 侧 +3V3 |
| 10 | 绿色 LED 阴极 | 经 R49/R56 330Ω |
| 11 | 黄色 LED 阴极 | 经 R50/R57 330Ω |
| 12 | 黄色 LED 阳极 | P0LED0 / P1 侧 +3V3 |

- J1 的 C66 在 pin5、C67 在 pin4、C68 在 pin8，均为 10nF 到 GND；J2 对应 C69/C70/C71。
- SH1/SH2 到 GND。

LED 侧细节（保留 P0/P1 的不对称，不强行统一）：

- P0：R47/R48 各 4.7K 到 GND；`P0LED1` 直连 J1(9)，并经 R49 330Ω 到 J1(10)；`P0LED0` 直连 J1(12)，并经 R50 330Ω 到 J1(11)。
- P1：R54 4.7K 到 GND（`P1LED1` 侧）；R55 4.7K 到 `+3V3`（`P1LED0` 侧）；J2(9)/J2(12) 均接 `+3V3`；`P1LED1` 经 R56 330Ω 到 J2(10)，`P1LED0` 经 R57 330Ω 到 J2(11)。

【待核实】P0 与 P1 的 LED 上拉/下拉方式不同（P0 两路下拉，P1 一路下拉一路上拉，且 J2 的 9/12 直接 +3V3）。这是原图连接，不能为了“对称”而改写。

### 4.7 第 7 页 encoder：编码器、RS485、差分接收、电平转换

页面文件：`File: D:\work\..\encoder.SchDoc`。

#### 4.7.1 MCU 侧网络

| MCU 引脚 | 网络 | 用途 |
|---|---|---|
| PC0 | `HU` | 霍尔 U / 编码器 U |
| PC1 | `HV` | 霍尔 V |
| PC2 | `HW` | 霍尔 W |
| PC5 | `QEIZ` | QEI Z |
| PC6 | `QEIB` / `SEI0_RX` | QEI B / SEI0 接收 |
| PC7 | `QEIA` / `SEI0_TX` | QEI A / SEI0 发送 |
| PF4 | `SEI0CK` | SEI0 时钟 |
| PD12 | `SEI2_CK` 经 R196 22Ω 到 `QEIZ` | SEI2 时钟/QEI Z 复用 |
| PD6 | `RSDE` | RS485 差分使能 |
| PD7 | `RSPWON` | 5V_RS 电源开关使能 |
| PD13 | `SEI2DE` | SEI2 差分使能 |
| PD14 | `SEI2RXD` / `UART_RX11` | SEI2 接收 |
| PD15 | `SEI2TXD` / `UART_TX11` | SEI2 发送 |

#### 4.7.2 U8 TXB0108PWR：3.3V 与 5V_QEI 电平转换

| 通道 | A 侧物理脚 / 网络 | B 侧物理脚 / 网络 |
|---|---|---|
| 1 | 1 A1 / QEIA | 20 B1 / QEIA_C |
| 2 | 3 A2 / SEI2TXD | 18 B2 / SEI2TX_C |
| 3 | 4 A3 / SEI0CK | 17 B3 / SEI0CK_C |
| 4 | 5 A4 / QEIB | 16 B4 / QEIB_C |
| 5 | 6 A5 / QEIZ | 15 B5 / QEIZ_C |
| 6 | 7 A6 / HU | 14 B6 / HU_C |
| 7 | 8 A7 / HV | 13 B7 / HV_C |
| 8 | 9 A8 / HW | 12 B8 / HW_C |

VCCA(2)=+3V3，C98 100nF 到 GND；VCCB(19)=5V_QEI，C147 100nF 到 GND；GND(11)=GND；OE(10) 经 R109 10K 上拉 +3V3。5V_QEI 由 +5V 经 R70 0Ω 得到。

单端接口侧滤波/偏置：QEIA_C/QEIB_C/QEIZ_C 分别有 R100/R101/R102（NC/10K）可选上拉到 5V_QEI，并分别有 C92/C93/C94 220pF 到 GND；HU_C/HV_C/HW_C 分别经 R119/R120/R147 10K 上拉 5V_QEI，并分别经 C96/C97/C84 220pF 到 GND。

#### 4.7.3 U20 MT9700：5V_QEI 到 5V_RS

图示事实：

```text
5V_QEI -> U20(5 VIN)
RSPWON -> U20(4 EN)
U20(3 SET) -> R103 4.7K -> GND
U20(1 VOUT) -> 5V_RS
C149 10uF：5V_QEI 到 GND；C150 10uF：5V_RS 到 GND
```

【推断】U20 是受 `RSPWON` 控制的 5V 负载开关/限流开关；SET 电阻设定限流，具体公式需查 MT9700 手册，图中未给。

#### 4.7.4 U7 UA9637A：两路差分接收

图示事实：

```text
5V_RS -> U7 VCC
QEIB_P -> U7(8 1IN+)
QEIB_N -> U7(7 1IN-)
U7(2 1OUT) -> QEIB_C
QEIZ_P -> U7(6 2IN+)
QEIZ_N -> U7(5 2IN-)
U7(3 2OUT) -> QEIZ_C
U7 GND -> GND
```

- U7 为双路差分线路接收器，把 QEI B/Z 的差分对转成 5V 单端 `QEIB_C`/`QEIZ_C`。

#### 4.7.5 U19 MX485：RS485/QEIA 差分

图示事实：

```text
5V_RS -> U19 VCC(8)
U19(6 A) -> QEIA_P
U19(7 B) -> QEIA_N
U19(4 DI) -> SEI0CK_C
U19(1 RO) -> QEIA_C
U19(3 DE) 与 U19(2 RE#) 并接 -> RSDE
RSDE -> R162 4.7K -> GND
C151 100nF：5V_RS 到 GND
```

- U19 为 5V RS485 收发器；`RSDE` 同时控制发送使能和接收使能（DE/RE# 并联）。
- R162 4.7K 下拉，默认使能为低。

#### 4.7.6 U21 SP3485EN-L/TR：3.3V RS485

图示事实：

```text
+3V3 -> U21 VCC(8)
U21(6 A) -> RS_U_P
U21(7 B) -> RS_U_N
U21(4 DI) -> SEI2TXD
U21(1 RO) -> SEI2RXD
U21(3 DE) 与 U21(2 RE#) 并接 -> SEI2DE
C154 100nF：+3V3 到 GND
```

#### 4.7.7 QEI/RS485 输入网络

图示事实：

```text
QA_P -> R90 22Ω -> QEIA_P；QEIA_P -> C83 220pF -> GND
QA_N -> R91 22Ω -> QEIA_N；QEIA_N -> C85 220pF -> GND
QB_P -> R93 22Ω -> QEIB_P；QEIB_P -> C86 220pF -> GND
QB_N -> R94 22Ω -> QEIB_N；QEIB_N -> C88 220pF -> GND
QZ_P -> R98 22Ω -> QEIZ_P；QEIZ_P -> C89 220pF -> GND
QZ_N -> R99 22Ω -> QEIZ_N；QEIZ_N -> C90 220pF -> GND
RS_P -> R107 22Ω -> RS_U_P；RS_U_P -> C152 220pF -> GND
RS_N -> R108 22Ω -> RS_U_N；RS_U_N -> C153 220pF -> GND
```

可选/默认件：

- R104/R105/R106/R145 各 `NC/120Ω`：分别跨 QEIA_P/QEIA_N、QEIB_P/QEIB_N、QEIZ_P/QEIZ_N、RS_U_P/RS_U_N。
- R58/R92/R96 各 `NC/10K`：从 `5V_QEI` 到 QA_P/QB_P/QZ_P（偏置/上拉，按图不装）。
- `5V_RS` 为 U19/U7 的供电；U21 用 +3V3。

#### 4.7.8 J14：2×9 编码器/RS485 接口

| J14 引脚 | 网络 | 说明 |
|---|---|---|
| 1 | `5V_QEI` | 5V 编码器电源 |
| 2 | `GND` |  |
| 3 | `QA_P` | A 相正 |
| 4 | `QEIA_C` | A 相单端/转换后 |
| 5 | `QA_N` | A 相负 |
| 6 | `QEIB_C` | B 相单端/转换后 |
| 7 | `QB_P` | B 相正 |
| 8 | `SEI0CK_C` | SEI0 时钟 |
| 9 | `QB_N` | B 相负 |
| 10 | `QEIZ_C` | Z 相单端/转换后 |
| 11 | `QZ_P` | Z 相正 |
| 12 | `SEI2TX_C` | SEI2 发送 |
| 13 | `QZ_N` | Z 相负 |
| 14 | `HU_C` | 霍尔 U |
| 15 | `RS_P` | RS485 正 |
| 16 | `HV_C` | 霍尔 V |
| 17 | `RS_N` | RS485 负 |
| 18 | `HW_C` | 霍尔 W |

【待核实·高风险】`QEIA_C/QEIB_C/QEIZ_C` 等 5V 侧网络同时连到 U8 的 B 侧和 U7/U19 的输出，存在“电平转换器输出”和“差分接收器输出”共同驱动同一节点的可能。实际是否通过装配/使能避免冲突，图中没有明确开关；不能写成“可永远同时独立驱动”。

#### 4.7.9 模式表（按原图抄录）

| PWON | RSDE | SSI2DE | 模式 | 电平 |
|---|---|---|---|---|
| 0 | x | x | ABZ+RS485 模式 | TTL 电平 |
| 0 | x | x | AB+QEI2(OUT) 模式 | TTL 电平 |
| 0 | x | x | QEI0(IN)+QEI2(OUT) 模式 | TTL 电平 |
| 1 | 0 | x | ABZ+RS485 模式 | 差分电平 |
| 1 | 0 | 1 | AB+QEI2(OUT) 模式 | 差分电平 |
| 1 | 1 | x | QEI0(IN)+RS485 模式 | 差分电平 |
| 1 | 1 | 1 | QEI0(IN)+QEI2(OUT) 模式 | 差分电平 |

- 原表用 `PWON`、`RSDE`、`SSI2DE`；网络名实际是 `RSPWON`、`RSDE`、`SEI2DE`。`SSI2DE` 与 `SEI2DE` 拼写不一致，按原文保留。
- 原表 `x` 与 `1` 的部分表项存在重叠，不能擅自补互斥逻辑。

### 4.8 第 8 页 misc：CAN、USB0、QSPI、启动、按键、LED

页面文件：`File: D:\work\..\misc.SchDoc`。

#### 4.8.1 CAN4 / CAN7

图示事实：

| 通道 | TXD | RXD | STBY | 收发器 | 连接器 |
|---|---|---|---|---|---|
| CAN4 | PC16 `CAN4_TXD` | PC17 `CAN4_RXD` | PC18 `CAN4_STBY` | U12 TJA1042T/3 | J8 |
| CAN7 | PC31 `CAN7_TXD` | PC30 `CAN7_RXD` | PC29 `CAN7_STBY` | U13 TJA1042T/3 | J9 |

U12/U13 引脚（TJA1042T/3）：

```text
1 TXD；2 GND；3 VCC = +5V；4 RXD；5 VIO = +3V3；6 CANL；7 CANH；8 STB
STB 分别经 R151/R143 10K 下拉到 GND
U12：C125 100nF 在 +5V，C132 100nF 在 +3V3；U13：C127 100nF 在 +5V，C126 100nF 在 +3V3，均到 GND
```

CAN 线：

```text
U12(7 CANH) -> L9(1) -> L9(4) -> CAN4_P -> J8(2)
U12(6 CANL) -> L9(2) -> L9(3) -> CAN4_N -> J8(1)
U13(7 CANH) -> L3(1) -> L3(4) -> CAN7_P -> J9(2)
U13(6 CANL) -> L3(2) -> L3(3) -> CAN7_N -> J9(1)
```

- L9/L3 为 `ACT45B-510-2P-TL003` 共模电感。
- 分裂终端：CAN4 的 R144/R146 各 60.4Ω，中点 C129 10nF 到 GND；CAN7 的 R141/R142 各 60.4Ω，中点 C155 10nF 到 GND。
- 线对地电容：C128/C130、C131/C156 各 47pF（按图）。
- D23/D3 为 `NUP2105L`，跨 CANH/CANL 作 TVS。
- J8/J9 为 2 位连接器：2 = P（CANH），1 = N（CANL）。

#### 4.8.2 USB0 与 USB-C J4

按 Codex 局部放大修正，以下连接为准：

```text
+5V -> U16(5 IN)
U16(1 OUT) -> +5P
+5P -> J4 VBUS（A4/A9/B4/B9 四脚）
+5P -> U14(5 IN)
U14(1 OUT) -> VBUS
VBUS -> D25 SS14 -> +5V
U14(4 EN) -> R153 10K -> GND
U14(3 IADJ) -> R154 330Ω -> GND
U14(2 GND) -> GND
C134 1uF：VBUS 到 GND
C133 4.7uF：J4 VBUS/+5P 到 GND
D25：阳极 VBUS，阴极 +5V
```

- U14 为 `PW1515`，U16 为 `AP2151WG-7`。
- 【重点】U16 是 `+5V -> +5P`；U14 是 `+5P -> VBUS`。不能写成“U16 输出 VBUS”。
- R155 `DNP NC/0Ω`：可把 U14 EN 可选接到 `USB0_PWR`。
- U16 使能/检测：
  ```text
  U16(4 EN) -> 节点；节点 -> R160 10K -> +3V3
  节点 -> Q7(漏)；Q7(源) -> GND
  节点 -> R158 0Ω -> USB0_PWR
  Q7(栅) -> R161 10K -> CC 检测节点
  CC 检测节点 -> R159 100K -> +3V3
  CC 检测节点 -> R169 0Ω -> USB0_ID
  D26 BAT54A-7-F：公共阳极接 CC 检测节点，两阴极分别接 CC1/CC2
  CC1 -> R167 NC/5.1K -> GND；CC2 -> R166 NC/5.1K -> GND
  ```
- U16 FLG：
  ```text
  U16(3 FLG) -> R168 0Ω -> USB0_OC
  U16(3 FLG) -> R163 2K -> LED1 阴极；LED1 阳极 -> +3V3
  ```
- C135 10uF 在 `+5V` 到 GND。
- J4 数据/配置：
  - A6 DP1、B6 DP2 接 `USB0+` 侧；A7 DN1、B7 DN2 接 `USB0-` 侧；经 L10 `DLW21SN900SQ2L` 共模后为 `USB0_P`/`USB0_N`。
  - A5 CC1、B5 CC2；A8 SUB1、B8 SUB2 均未连接；EP 到 GND。
  - U15 `PRTR5V0U2X` 作 ESD 保护。
- 第 8 页左上明确把 `USB0_DP` 端口接到 `USB0_P` 标签、把 `USB0_DN` 端口接到 `USB0_N` 标签；同时 D+ 经 L10 到 `USB0_P`，D- 经 L10 到 `USB0_N`。因此两套标签是同一 USB0 数据链的页内/页间命名，不是漏画或互不相连。L10 是串联共模器件，`USB0+/USB0-` 与 `USB0_P/USB0_N` 是被器件分隔的前后节点，不只是拼写别名。
- 【推断】板内供电到接口的路径为 +5V -> U16 -> +5P/J4；接口外部供电回板内的图示路径为 J4/+5P -> U14 -> VBUS -> D25 -> +5V。U14 并不串在 U16 与 J4 之间。实际是否启用相应路径，取决于开关芯片使能、电气特性和装配；图中没有 USB PD 控制器。

#### 4.8.3 U17 MX25L12833FM2I-10G QSPI Flash

图示事实：

| U17 引脚 | 名称 | 连接 |
|---|---|---|
| 1 | CS# | `PB30`（`CS0`）；R174 10K 上拉到 +3V3 |
| 2 | DO/IO1 | `PB27`（`D1`） |
| 3 | WP#/IO2 | `PB28`（`D2`） |
| 4 | GND | GND |
| 5 | DI/IO0 | `PB26`（`D0`） |
| 6 | CLK | 经 R175 33Ω 到 `PB29`（`SCLK`） |
| 7 | HOLD#/IO3 | `PB31`（`D3`） |
| 8 | VCC | `+3V3`；C138 100nF 到 GND |

#### 4.8.4 启动拨码 SW3

图示事实：

```text
+3V3 -> SW3 两路公共端
SW3 一路 -> BOOT_0 -> PA2
SW3 另一路 -> BOOT_1 -> PA3
BOOT_0 -> R156 10K -> GND
BOOT_1 -> R157 10K -> GND
```

- 闭合时对应 BOOT 网络被拉到 `+3V3`；断开时由 10K 下拉到 GND。
- 不能从图判断拨码的“ON”方向对应 0 还是 1，需看实物丝印。

#### 4.8.5 按键 SW4/SW5/SW6

| 按键 | 网络 | MCU | 上拉 | 去抖 |
|---|---|---|---|---|
| SW4 | `KEYA` | PC14 | R165 10K 到 +3V3 | C136 100nF 到 GND |
| SW5 | `KEYB` | PC15 | R170 10K 到 +3V3 | C137 100nF 到 GND |
| SW6 | `KEYC` | PC19 | R115 10K 到 +3V3 | C148 100nF 到 GND |

- 按键另一端到 GND；按下为低。

#### 4.8.6 RGB LED3 与指示灯

图示事实：

```text
+5V -> LED3 公共阳极
LED3 蓝 -> Q8(2N7002) 漏；Q8 源 -> GND；Q8 栅 -> LED_B(PA9)
LED3 绿 -> Q10(2N7002) 漏；Q10 源 -> GND；Q10 栅 -> LED_G(PB24)
LED3 红 -> Q9(2N7002) 漏；Q9 源 -> GND；Q9 栅 -> LED_R(PB25)
蓝限流 R171 1K；绿限流 R172 2K；红限流 R173 1.5K
Q8/Q9/Q10 栅极各 100K 下拉到 GND
```

- 另有电源/状态 LED1、LED2、LED4、LED5、LED6：LED1 在 USB 过流指示（R163 2K），LED2 在 +3V3（R69 2K），LED4 在 FAULT（R89 2K），LED5/LED6 在调试页（R190/R191 1K）。
- H1/H2/H3/H4 为安装孔/接地孔；LOGO1..LOGO3 为丝印图形，不是电气器件。

### 4.9 第 9 页 Debug：FT2232HL、JTAG、UART、总线隔离

页面文件：`File: D:\work\..\Debug.SchDoc`。

#### 4.9.1 调试电源

```text
+3V3 -> R118 0Ω -> +3.3VD -> U22 VREGIN(50)
U22 VREGOUT(49) -> +1.8VD
```

- `+3.3VD` 与 `+3V3` 通过 0Ω 连接，不是独立电源。
- `+1.8VD` 由 FT2232HL 内部稳压器输出，仅用于其自身/相关去耦。
- +1.8VD 去耦：C160/C161/C162 各 100nF、C163 10uF、C169 4.7uF；+3.3VD 去耦：C95/C157 各 10uF，C158/C159/C164/C165/C166/C168 各 100nF。RESET# 独立滤波为 C167 100nF。
- U22 电源脚：VCORE(12/37/64)=+1.8VD；VCCIO(20/31/42/56)、VPLL(9)、VPHY(4)=+3.3VD；AGND(10) 和 GND(1/5/11/15/25/35/47/51) 均接 GND。
- D4 `SS14` 从 J13 VBUS 到 +5V；C170 10uF 在 J13 VBUS 侧。

#### 4.9.2 U22 FT2232HL 主要引脚

| U22 引脚 | 名称 | 连接 |
|---|---|---|
| 8 | DP | `FT_USB_P`（来自 J13/USB-C 经 U23/L4） |
| 7 | DM | `FT_USB_N` |
| 14 | RESET# | R148 10K 上拉到 +3.3VD；C167 100nF 到 GND |
| 6 | REF | R150 12K 到 GND |
| 16 | ADBUS0 | `FT_JTAG_TCK` |
| 17 | ADBUS1 | `FT_JTAG_TDI` |
| 18 | ADBUS2 | `FT_JTAG_TDO` |
| 19 | ADBUS3 | `FT_JTAG_TMS` |
| 26 | ACBUS0 | `FT_JTAG_TRST` |
| 27 | ACBUS1 | `FT_RESET_N`，经 R149 0Ω 到 `RSTN` |
| 38 | BDBUS0 | 经 R186 0Ω 到 `FT_URT_TXD` |
| 39 | BDBUS1 | 经 R187 0Ω 到 `FT_URT_RXD` |
| 49 | VREGOUT | `+1.8VD` |
| 50 | VREGIN | `+3.3VD` |
| 60 | PWREN# | 未接，图中叉号 |
| 36 | SUSPEND# | 未接，图中叉号 |
| 63 | EECS | R192 10K 上拉；无 EEPROM 器件 |
| 62 | EECLK | R193 10K 上拉；无 EEPROM 器件 |
| 61 | EEDATA | R194 10K 上拉；无 EEPROM 器件 |

- X2 12MHz ±10ppm：C171/C172 各 12pF。
- `FT_URT_TXD`/`FT_URT_RXD` 另有 R152/R185 10K 上拉。
- BCBUS3/4 经 R190/R191 1K 驱动 LED5（蓝）/LED6（绿）到 +3.3VD。

#### 4.9.3 J13：调试 USB-C

图示事实：

- J13 为第二只 USB Type-C，不是 J4 的 USB0。
- VBUS -> D4 `SS14` -> `+5V`；C170 10uF 在 VBUS 到 GND。
- CC1 -> R188 5.1K -> GND；CC2 -> R189 5.1K -> GND。
- D+/D- 经 U23 `PRTR5V0U2X` 保护、L4 `DLW21SN900SQ2L` 共模后：
  ```text
  J13 D+ -> FT_USB_P -> U22(8 DP)
  J13 D- -> FT_USB_N -> U22(7 DM)
  ```
- J13 的 A/B 双排 D+/D- 是否并联：按图两只 D+ 脚并到同一网络、两只 D- 脚并到同一网络；若需极限验证请对照原图。

#### 4.9.4 J7：20 针 JTAG

| J7 引脚 | 名称 | 连接 |
|---|---|---|
| 1 | VTREF | `+3V3` |
| 2 | VCC | 经 R71 `0Ω DNP` 到 `+3V3` |
| 3 | TRST | 经 R81 100Ω 到 `JTAG_TRST` / MCU PA8；TRST 节点另接 U24 B3，作为板载调试支路 |
| 4 | GND | GND |
| 5 | TDI | 经 R113 100Ω 到 `JTAG_TDI`；MCU PA5 |
| 6 | 图中未单独列出 | 不从标准接口习惯推定连接 |
| 7 | TMS | 经 R111 100Ω 到 `JTAG_TMS`；MCU PA7 |
| 8 | 图中未单独列出 | 不从标准接口习惯推定连接 |
| 9 | TCK | 经 R110 100Ω 到 `JTAG_TCK`；MCU PA6 |
| 10 | 图中未单独列出 | 不从标准接口习惯推定连接 |
| 11 | RTCK | 未接 |
| 12 | 图中未单独列出 | 不从标准接口习惯推定连接 |
| 13 | TDO | 经 R112 100Ω 到 `JTAG_TDO`；MCU PA4 |
| 14 | 图中未单独列出 | 不从标准接口习惯推定连接 |
| 15 | SRST | 未接（图中 `SRST` 悬空） |
| 16 | 图中未单独列出 | 不从标准接口习惯推定连接 |
| 17 | DBGRQ/NC | 未接，图中叉号 |
| 18 | 图中未单独列出 | 不从标准接口习惯推定连接 |
| 19 | DBGACK/NC | 未接，图中叉号 |
| 20 | DET | `JLINK_DET` |

- R79/R80 各 10K 上拉 `TMS`/`TDI`（J7 与 U24 一侧）；R114 10K 下拉 `TCK`（R110 前）。
- 外部 JTAG 的 `JLINK_DET` 到 Q13 栅极；Q13 漏接 U24 的 OE#，源 GND；R197 4.7K 上拉 `JLINK_DET` 到 +3.3VD。R195 4.7K 上拉 U24 OE# 到 +3.3VD。
- 【推断】插入外部调试器时，J7(20) 被外部探头拉低，Q13 关断，OE# 被 R195 拉高，U24 隔离板载 FT2232 的 JTAG/UART 总线；不插外部探头时 Q13 导通，OE# 被拉低，U24 导通。该逻辑是拓扑推断，实际探头是否短接 pin20 需确认。

#### 4.9.5 U24 SN74CBTLV3245ARGYR 总线开关

图示事实：

```text
U24 VCC(20) = +3.3VD；GND(11) 与 EP(21) = GND；C173 10uF 跨电源与 GND
U24 OE#(19) -> R195 4.7K -> +3.3VD
U24 OE#(19) -> Q13(漏)；Q13(源) -> GND；Q13(栅) -> JLINK_DET
A1(FT_URT_RXD) <-> B1(TXD0)
A2(FT_URT_TXD) <-> B2(RXD0)
A3(FT_JTAG_TRST) <-> B3(TRST)
A4(FT_JTAG_TMS) <-> B4(TMS)
A5(FT_JTAG_TDO) <-> B5(TDO)
A6(FT_JTAG_TDI) <-> B6(TDI)
A7(FT_JTAG_TCK) <-> B7(TCK)
A8/B8 未用
```

- 注意 UART 的交叉：A1 是 FT 的 RXD，B1 是板级 TXD0；A2 是 FT 的 TXD，B2 是板级 RXD0。不能写成同名直连。
- `TXD0`/`RXD0` 同时去 J12 和 MCU PA0/PA1。

#### 4.9.6 J12：3 针调试 UART

| J12 引脚 | 网络 | MCU |
|---|---|---|
| 1 | `TXD0` | PA0 |
| 2 | `RXD0` | PA1 |
| 3 | `GND` |  |

- J12 为 3 针 `CON3`，与 U24 的 B1/B2 以及 MCU PA0/PA1 同网。

#### 4.9.7 MCU JTAG 引脚

| MCU 引脚 | 网络 | 说明 |
|---|---|---|
| PA8 | `JTAG_TRST` | 经 R81 100Ω 到 J7(3) |
| PA6 | `JTAG_TCK` | 经 R110 100Ω 到 J7(9) |
| PA7 | `JTAG_TMS` | 经 R111 100Ω 到 J7(7) |
| PA4 | `JTAG_TDO` | 经 R112 100Ω 到 J7(13) |
| PA5 | `JTAG_TDI` | 经 R113 100Ω 到 J7(5) |

## 5. 主控全部 142 个通用 I/O 的球位与板级用途

来源：原 PDF 第 2 页 U3B/U3C/U3D，板级用途交叉核对第 3 至 9 页。GPIO 名称使用网络标签形式（例如 PA0）；芯片框内 PA00 与 PA0 指同一信号。此表只列原图画出的引脚，不自行补出未画出的 PA10 等管脚。U3A 的电源、地、晶振和 USB 专用脚见正文第 1 页说明。

**原图标注冲突：** A13 球位的芯片框内名称写成 PC24，而其左侧外部网络标签为 PC23；下一行 B14 的芯片名和外部网名均为 PC24。下表按实际外部网络标签记录 PC23=A13、PC24=B14；不能将这视作已用芯片官方引脚表确认的复用关系。该冲突应在需要精确物理管脚时另行核对。

| 网络 / GPIO | U3 球位 | 原理图板级用途 |
|---|---|---|
| PA0 | G2 | TXD0 |
| PA1 | G3 | RXD0 |
| PA2 | G4 | BOOT_0 |
| PA3 | G5 | BOOT_1 |
| PA4 | F2 | JTAG_TDO |
| PA5 | F3 | JTAG_TDI |
| PA6 | F4 | JTAG_TCK |
| PA7 | F5 | JTAG_TMS |
| PA8 | G1 | JTAG_TRST |
| PA9 | F1 | LED_B |
| PA16 | L1 | P1RD_N |
| PA17 | L2 | P1RD_P |
| PA18 | K1 | P1TD_N |
| PA19 | K2 | P1TD_P |
| PA20 | J1 | P0RD_N |
| PA21 | J2 | P0RD_P |
| PA22 | H1 | P0TD_N |
| PA23 | H2 | P0TD_P |
| PA24 | K3 | P1RBIAS |
| PA25 | K4 | P1LED1 |
| PA26 | J3 | P1LED0 |
| PA27 | J4 | P0RBIAS |
| PA28 | J5 | P0LED1 |
| PA29 | H3 | P0LED0 |
| PA30 | H4 | MDIO（集成PHY侧） |
| PA31 | H5 | MDC（集成PHY侧） |
| PB0 | E1 | RTL_RXDV |
| PB1 | E2 | RTL_RXD0 |
| PB2 | D1 | RTL_RXD1 |
| PB3 | D2 | RTL_RXD2 |
| PB4 | C1 | RTL_RXD3 |
| PB5 | C2 | RTL_RXCK |
| PB6 | E3 | RTL_TXCK |
| PB7 | E4 | RTL_TXD0 |
| PB8 | D3 | RTL_TXD1 |
| PB9 | D4 | RTL_TXD2 |
| PB10 | C3 | RTL_TXD3 |
| PB11 | C4 | RTL_TXEN |
| PB24 | A2 | LED_G |
| PB25 | B1 | LED_R |
| PB26 | A3 | D0（Flash） |
| PB27 | B2 | D1（Flash） |
| PB28 | A4 | D2（Flash） |
| PB29 | B3 | SCLK（Flash） |
| PB30 | A5 | CS0（Flash） |
| PB31 | B4 | D3（Flash） |
| PC0 | B5 | HU |
| PC1 | A6 | HV |
| PC2 | B6 | HW |
| PC3 | A7 | J10 RESET |
| PC4 | B7 | J10 DC/RS |
| PC5 | A8 | QEIZ |
| PC6 | B8 | QEIB / SEI0_RX |
| PC7 | A9 | QEIA / SEI0_TX |
| PC8 | B9 | J10 LED |
| PC9 | C5 | J10 T_IRQ |
| PC10 | D5 | J10 SCLK |
| PC11 | C6 | J10 CS |
| PC12 | D6 | J10 MISO |
| PC13 | C7 | J10 MOSI |
| PC14 | D7 | KEYA |
| PC15 | C8 | KEYB |
| PC16 | D8 | CAN4_TXD |
| PC17 | C9 | CAN4_RXD |
| PC18 | A10 | CAN4_STBY |
| PC19 | B10 | KEYC |
| PC20 | A11 | J10 T_SCLK |
| PC21 | B11 | J10 T_CS |
| PC22 | A12 | J10 T_MISO |
| PC23 | A13 | J10 T_MOSI |
| PC24 | B14 | J11:11 |
| PC25 | C14 | J11:27 |
| PC26 | D14 | J11:31 |
| PC27 | D13 | BRAKE（未见连到Q12） |
| PC28 | E14 | J11:10 |
| PC29 | E13 | CAN7_STBY |
| PC30 | F14 | CAN7_RXD |
| PC31 | F13 | CAN7_TXD |
| PD0 | D9 | IN_UH |
| PD1 | C10 | IN_UL |
| PD2 | D10 | IN_VH |
| PD3 | C11 | IN_VL |
| PD4 | D11 | IN_WH |
| PD5 | B12 | IN_WL |
| PD6 | C12 | RSDE |
| PD7 | B13 | RSPWON |
| PD8 | C13 | J11:42 |
| PD9 | D12 | J11:7 |
| PD10 | E12 | J11:8 |
| PD11 | E11 | J11:9 |
| PD12 | F12 | SEI2_CK，经R196到QEIZ |
| PD13 | F11 | SEI2DE |
| PD14 | G14 | SEI2RXD / UART_RX11 |
| PD15 | G13 | SEI2TXD / UART_TX11 |
| PD16 | G12 | J11:12 |
| PD17 | H14 | J11:3 |
| PD18 | H13 | J11:4 |
| PD19 | H12 | J11:14 |
| PD20 | J14 | J11:5 |
| PD21 | J13 | J11:6 |
| PD22 | J12 | J11:16 |
| PD23 | F10 | J11:22 |
| PD24 | G11 | J11:13 |
| PD25 | G10 | J11:24 |
| PD26 | H11 | J11:15 |
| PD27 | H10 | J11:23 |
| PD28 | J11 | J11:17 |
| PD29 | J10 | J11:26 |
| PD30 | K12 | J11:18 |
| PD31 | K11 | J11:21 |
| PF0 | N10 | RTL_MDC |
| PF1 | L10 | RTL_MDIO |
| PF2 | P11 | RTL_RST |
| PF3 | M9 | RTL_INT |
| PF4 | M8 | SEI0CK |
| PF5 | L8 | Z_U / ACMP0_CH0_IN4 |
| PF6 | P12 | Z_V / ACMP0_CH0_IN5 |
| PF7 | M11 | Z_W / ACMP0_CH0_IN3 |
| PF8 | L11 | NTC1 |
| PF9 | M10 | CP |
| PF10 | P10 | Z_M / ACMP0_CH0_IN6 |
| PF11 | L9 | J11:32 |
| PF12 | N11 | J11:28 |
| PF13 | N12 | J11:25 |
| PF14 | N9 | J11:29 |
| PF15 | P9 | J11:30 |
| PF16 | N7 | J11:33 |
| PF17 | P7 | J11:34 |
| PF18 | P8 | USB0_ID |
| PF19 | M5 | J11:41 |
| PF20 | N6 | J11:38 |
| PF21 | L6 | J11:39 |
| PF22 | N8 | USB0_PWR |
| PF23 | L5 | USB0_OC |
| PF24 | M6 | J11:40 |
| PF25 | L7 | J11:37 |
| PF26 | P6 | J11:35 |
| PF27 | M7 | J11:36 |
| PF28 | P5 | I_U |
| PF29 | M4 | I_V |
| PF30 | L4 | I_W |
| PF31 | N5 | VBUS_VOL |

## 6. 功率驱动与三相桥（专项）

### 6.1 功率路径

```text
VM（J6-5） -> Q1/Q2/Q3 漏极
Q1 源 -> OUT_U -> J6-1 -> 电机 U
Q2 源 -> OUT_V -> J6-2 -> 电机 V
Q3 源 -> OUT_W -> J6-3 -> 电机 W
OUT_U -> Q4 漏；Q4 源 -> PR1(1/2) -> BGND
OUT_V -> Q5 漏；Q5 源 -> PR2(1/2) -> BGND
OUT_W -> Q6 漏；Q6 源 -> PR3(1/2) -> BGND
```

- Q1/Q2/Q3 为上管，Q4/Q5/Q6 为下管，全部 `BSC040N10NS5`。
- `PR1/PR2/PR3` 为 10mΩ 四端采样电阻，功率端 1/2，采样端 3=`SNSx_P`、4=`SNSx_N`。
- `C140/C141` 220uF/63V 与 `C72/C73/C74` 220nF/100V 都在 VM-BGND 之间，作母线/桥臂去耦；不要把 C72/C73/C74 写成跨相输出。

### 6.2 驱动时序与死区

- U9(2 DT/MODE) 经 R75 0Ω 到 BGND。按 STDRIVE101 的常见定义，该脚用于死区/模式选择；图中只给 0Ω 到地，不能据此算出具体死区时间。
- 6 路 PWM 由 PD0..PD5 直接进 U9，没有外部死区电阻/电容网络；死区由 MCU 波形与 U9 的具体模式共同决定，原图未给出完整条件。
- 【待核实】`DT/MODE` 接 0Ω 到 BGND 对应的具体模式（死区时间、EN 极性等）需查 STDRIVE101 数据手册；本文不补数值。

### 6.3 自举与栅极

- 每相高端自举电容 1uF：C75(U)、C78(V)、C79(W)，分别跨 BOOT1-OUT_U、BOOT2-OUT_V、BOOT3-OUT_W。
- 每相高端栅极串 33Ω：R66/R67/R68；低端串 33Ω：R76/R77/R78。
- 每相栅源 22K：R72/R73/R74（高端）、R82/R83/R84（低端）。
- 每个 22K 旁并一只 BAT43WS-7-F：D8/D9/D10（高端）、D11/D12/D13（低端）。
- 【待核实】BAT43WS 的阳极/阴极方向按原图；不能仅凭“并联二极管=加速关断”就断定方向。

### 6.4 过流/短路保护

- 采样电阻差分信号 `SNSU_P/N`、`SNSV_P/N`、`SNSW_P/N` 到第 4 页 U6 差分放大。
- 三路电流再求和为 `CP`，`CP` 同时进 U3(PF9) 和 U9(1 CP)。
- 原图只证明外部连接：`CP` 到 U9(1)、`SCREF` 到 U9(3)；`SCREF` 由 R95 0Ω 上拉到 +3V3，R97 10K 到 BGND，C87 100nF（NC）并联到 BGND。U9 内部如何比较、阈值多少、CP/SCREF 各自对应哪种保护，必须查 STDRIVE101 手册，不能凭图把内部模拟机制写成事实。
- 图注“Open (default): SC protection enabled / Closed: SC protection disabled”说明 SCREF 的装配状态会改变保护行为，但图中没有明确开关位号。
- `FAULT` 由 U9(6 nFAULT) 输出，R88 10K 上拉 +3V3，R89 2K + LED4 指示；本页未见 `FAULT` 接 MCU。

## 7. 采样调理（专项）

### 7.1 电流采样链

```text
PR1(3/4) -> SNSU_P/SNSU_N -> U6A 差分放大 -> R27/C54 -> I_U -> PF28
PR2(3/4) -> SNSV_P/SNSV_N -> U6B 差分放大 -> R33/C59 -> I_V -> PF29
PR3(3/4) -> SNSW_P/SNSW_N -> U6C 差分放大 -> R42/C64 -> I_W -> PF30
I_U/I_V/I_W -> R28/R34/R43 10K 求和 -> R37 1.1K/C58 3.3nF -> R117 10Ω -> CP -> PF9 / U9(1 CP)
```

- 差分放大器增益由 10K/1K 反馈/输入电阻决定，理论差分增益约 10；C53/C56 等 27pF 作低通。
- 单端输出经 10Ω/10nF RC 到 ADC，截止频率约 1/(2π×10×10nF)≈1.59MHz；实际还受 MCU 采样保持影响。
- 共用偏置为 VREF/2（U6D），所以电流为双极性。

### 7.2 相电压/中性点采样

```text
OUT_U/V/W -> 62K -> PU/PV/PW -> 2.4K -> AGND
PU/PV/PW -> 2.4K -> OUT_M -> R184 1K -> Z_M -> PF10
PU/PV/PW -> 直接连接对应比较器同相输入；R85/R86/R87 为到输出网的 NC/0Ω 可选旁路
OUT_M -> 比较器反相输入
```

- 三路相电压经 2.4K 共同汇到 OUT_M，存在互相负载，不能逐路套用孤立的 `2.4/(62+2.4)=0.0373`。对称条件下的耦合关系见 4.4.3 与第 15 节：`V(OUT_M)≈0.037267×Vavg`，`V(PU)-V(OUT_M)≈0.018987×[V(OUT_U)-Vavg]`。若 VM 高，仍需确认 MCU 输入不超过 3.3V。
- OUT_M 是三路经 2.4K 汇合的节点，不是严格的模拟中性点；其等效阻抗与三路分压网络有关。
- 【待核实·高风险】`Z_U/Z_V/Z_W` 同名网络问题见 4.4.4，直接关系到比较器输入/输出是否被短接。

### 7.3 母线电压/温度

```text
VM -> R140 200K -> VBUS_VOL -> R179 10K -> AGND；C142 1nF；D27/D28 钳位 -> PF31
+3V3A -> R182(NC NTC) -> NTC1；NTC1 -> R183 4.7K -> AGND；C146 33nF；U18 MCP9700 -> NTC1 -> PF8
```

- VBUS_VOL 理想为 VM/21；D27 上钳到 +3V3A，D28 下钳到 AGND。
- NTC1 同时可接 MCP9700 和可选 NTC，二者共享一个 ADC 通道。

## 8. 外部接口引脚总表

### 8.1 J6：电机/母线功率连接器（Header 5）

| 引脚 | 网络 | 说明 |
|---|---|---|
| 1 | `OUT_U` | U 相输出 |
| 2 | `OUT_V` | V 相输出 |
| 3 | `OUT_W` | W 相输出 |
| 4 | `BGND` | 功率地 |
| 5 | `VM` | 电机母线正 |

### 8.2 J5：制动电阻连接器（CON2）

| 引脚 | 网络 | 说明 |
|---|---|---|
| 1 | Q11 漏极 | 外接制动电阻一端 |
| 2 | `VM` | 外接制动电阻另一端 |

- R62 `NC/10mΩ` 跨 J5 两端；不装 J5 时可作为可选的极小阻值旁路/检测位置。
- 【待核实】J5 的 1/2 方向按图；外接电阻的功率/阻值未在图中给出。

### 8.3 J1/J2：EtherCAT RJ45（HR911105A）

见 4.6.2。两连接器引脚定义相同。

### 8.4 RJ1：RTL8211E RJ45（HR911130A）

见 4.5.2。

### 8.5 J14：编码器/RS485（Header 9X2）

见 4.7.8。

### 8.6 J8/J9：CAN 连接器

| 连接器 | 引脚 1 | 引脚 2 |
|---|---|---|
| J8（CAN4） | `CAN4_N`（CANL） | `CAN4_P`（CANH） |
| J9（CAN7） | `CAN7_N`（CANL） | `CAN7_P`（CANH） |

- 按图 2=P、1=N；不要按“1 正 2 负”的惯例改写。

### 8.7 J4：USB0 Type-C

| 引脚 | 名称 | 连接 |
|---|---|---|
| A1/B1/A12/B12 | GND | GND |
| A4/A9/B4/B9 | VBUS | `+5P`；C133 4.7uF 到 GND |
| A5 | CC1 | 到 U16 CC 检测网络 |
| B5 | CC2 | 到 U16 CC 检测网络 |
| A6 | DP1 | `USB0+` 侧 |
| B6 | DP2 | `USB0+` 侧 |
| A7 | DN1 | `USB0-` 侧 |
| B7 | DN2 | `USB0-` 侧 |
| A8 | SUB1 | 未连接 |
| B8 | SUB2 | 未连接 |
| EP | 屏蔽/地 | GND |

- D+/D- 经 U15 `PRTR5V0U2X`、L10 `DLW21SN900SQ2L` 后为 `USB0_P`/`USB0_N`。
- `USB0_P`/`USB0_N` 经第 8 页左上的 `USB0_DP`/`USB0_DN` 端口标签与 MCU 页对应；L10 串在 J4 侧 `USB0+/USB0-` 与 `USB0_P/N` 之间。详见 4.8.2。

### 8.8 J13：调试 USB Type-C

| 引脚 | 名称 | 连接 |
|---|---|---|
| A1/B1/A12/B12 | GND | GND |
| A4/A9/B4/B9 | VBUS | 经 D4 SS14 到 `+5V`；C170 10uF |
| A5 | CC1 | R188 5.1K 到 GND |
| B5 | CC2 | R189 5.1K 到 GND |
| A6/B6 | DP1/DP2 | `FT_USB_P` 侧 |
| A7/B7 | DN1/DN2 | `FT_USB_N` 侧 |
| A8/B8 | SUB1/SUB2 | 未连接 |
| EP | 屏蔽/地 | GND |

- D+/D- 经 U23 `PRTR5V0U2X`、L4 `DLW21SN900SQ2L` 到 U22。

### 8.9 J7：20 针 JTAG

见 4.9.4。

### 8.10 J12：3 针调试 UART

| 引脚 | 网络 | MCU |
|---|---|---|
| 1 | `TXD0` | PA0 |
| 2 | `RXD0` | PA1 |
| 3 | `GND` |  |

### 8.11 J10：MSP2402

见 4.2.2。

### 8.12 J11：2×22 通用 IO

见 4.2.3。

### 8.13 J3：MX1.25-2P 备用电源连接器

| 引脚/端子 | 图中连接 |
|---|---|
| 1 信号针 | VBAT，接 D2 的一个阳极 |
| 2 信号针 | GND |
| 另两个 G 端 | 均接 GND；图中未注明机械/屏蔽含义 |

J3 的 VBAT 与 +3V3 经 D2 共阴极二极管或合，再经 R11 0Ω 接 U3(N4 VBAT)。信号 1 与 G 端分别记录，不能因符号右侧另有 G 端而将信号 1 写成接地。

## 9. 关键器件参数与默认/DNP/可选配置

### 9.1 主要 IC

| 位号 | 型号 | 功能 | 关键参数/备注 |
|---|---|---|---|
| U1 | LM5164DDAR | VM 到 +5V 同步降压 | L1 68uH；R4 200K/R5 62K；C1 2.2nF |
| U2 | SM8082AAAC | +5V 到 +3V3 同步降压 | L2 4.7uH 2A；R3 100K/R1 22.1K；C2 22pF |
| U3 | HPM6E8YIGN1 | 主控 MCU | BGA；U3A/U3B/U3C/U3D 为同一颗 |
| U4 | RTL8211E-VB-CG | 千兆以太网 PHY | RGMII；25MHz X1；R138 2.49K |
| U5 | LM339 | 四比较器 | 三路用于 Z_U/Z_V/Z_W，一路未用 |
| U6 | TP2274-TR | 四运放 | 三路电流差分 + 一路 VREF/2 偏置 |
| U7 | UA9637A | 双差分接收 | 5V_RS；QEIB/QEIZ |
| U8 | TXB0108PWR | 8 位电平转换 | 3V3 <-> 5V_QEI |
| U9 | STDRIVE101 | 三相栅极驱动器 | VS=VM；REG12=+12VREG；6 路 PWM |
| U10 | REF3033AIDBZR | 3.3V 基准 | +5V 经 FB1；OUT 经 FB2 到 VREF |
| U11 | LP5907MFX-3.3/NOPB | 3.3V LDO | +5V 经 FB3；输出 +3V3A |
| U12/U13 | TJA1042T/3 | CAN 收发器 | +5V VCC、+3V3 VIO、STB |
| U14 | PW1515 | USB 功率开关 | +5P 到 VBUS；R153 10K、R154 330Ω |
| U15 | PRTR5V0U2X | USB ESD 保护 | USB0 |
| U16 | AP2151WG-7 | USB 限流开关 | +5V 到 +5P；FLG 到 USB0_OC/LED1 |
| U17 | MX25L12833FM2I-10G | 128Mbit QSPI Flash | PB26..PB31 |
| U18 | MCP9700 | 模拟温度传感器 | +3V3A；输出 NTC1 |
| U19 | MX485 | RS485 收发器 | 5V_RS；QEIA |
| U20 | MT9700 | 5V 负载开关 | 5V_QEI 到 5V_RS；RSPWON |
| U21 | SP3485EN-L/TR | 3.3V RS485 | SEI2 |
| U22 | FT2232HL | USB 转 JTAG/UART | +3.3VD；+1.8VD 内部稳压 |
| U23 | PRTR5V0U2X | 调试 USB ESD | J13 |
| U24 | SN74CBTLV3245ARGYR | 8 位总线开关 | JTAG/UART 隔离 |
| Q1..Q6 | BSC040N10NS5 | 三相桥 MOSFET | N 沟道，型号按图记录，不推断板额定 |
| Q7..Q10 | 2N7002 | 小信号 NMOS | Q7 USB 检测；Q8/Q9/Q10 RGB LED 驱动 |
| Q11 | BSC040N10NS5 | 制动低边 MOS | 外接 J5 |
| Q12/Q13 | 2N7002 | 栅极/隔离驱动 | 制动、JTAG 检测 |

### 9.2 默认装配、NC/DNP、可选

| 位号 | 标注 | 解释 |
|---|---|---|
| R2 | 10K | U2 EN 上拉到 +5V，默认装 |
| R7 | 0Ω | VCC_3V3 到 +3V3，默认装 |
| R8 | 0Ω | DCDC_GND 到 GND，默认装 |
| R59 | 0Ω | AGND 到 GND，默认装 |
| R164 | 0Ω | GND 到 BGND，默认装 |
| R9/R10 | 10Ω | USB0_VBUS/VPMC 限流/滤波，默认装 |
| R11 | 0Ω | D2 共阴极到 U3 VBAT，默认装 |
| R13 | 1M | 24MHz 晶振并联反馈，默认装 |
| R47/R48 | 4.7K | P0 LED 下拉，默认装 |
| R49/R50 | 330Ω | P0 LED 限流，默认装 |
| R54 | 4.7K | P1 LED1 下拉，默认装 |
| R55 | 4.7K | P1 LED0 上拉到 +3V3，默认装 |
| R56/R57 | 330Ω | P1 LED 限流，默认装 |
| R58/R92/R96 | NC/10K | 5V_QEI 到 QA_P/QB_P/QZ_P 的可选上拉，默认不装 |
| R85/R86/R87 | NC/0Ω | PU/PV/PW 到 Z_U/Z_V/Z_W 的可选 0Ω，默认不装 |
| R104/R105/R106/R145 | NC/120Ω | 差分对可选终端，默认不装 |
| R166/R167 | NC/5.1K | USB-C CC 可选下拉，默认不装 |
| R155 | DNP NC/0Ω | U14 EN 可选接 USB0_PWR，默认不装 |
| R182 | NC/HNTC0603-103F3450FA | 可选 NTC，默认不装 |
| R97 | 10K | SCREF 到 BGND，电阻本身未标 NC；NC 注记位于 C87 旁 |
| C87 | 100nF | SCREF 到 BGND 的可选电容，标 NC |
| R62 | NC/10mΩ | J5 两端可选旁路，默认不装 |
| R71 | 0Ω DNP | J7 VCC 可选接 +3V3，默认不装 |
| R114 | 10K | JTAG TCK 下拉，默认装 |
| R162 | 4.7K | RSDE 下拉，默认装 |
| R151/R143 | 10K | CAN STB 下拉，默认装 |
| R174 | 10K | QSPI CS 上拉，默认装 |
| R175 | 33Ω | QSPI CLK 串阻，默认装 |
| R195/R197 | 4.7K | U24 OE#/JLINK_DET 上拉，默认装 |
| R149/R186/R187 | 0Ω | FT_RESET/FT_UART 串阻，默认装 |
| R118 | 0Ω | +3V3 到 +3.3VD，默认装 |
| R154 | 330Ω | U14 IADJ 设定，默认装 |
| R153 | 10K | U14 EN 下拉，默认装 |
| R160 | 10K | U16 EN 上拉，默认装 |
| R158 | 0Ω | U16 EN 到 USB0_PWR，默认装 |
| R161 | 10K | Q7 栅极串阻，默认装 |
| R159 | 100K | CC 检测上拉，默认装 |
| R169 | 0Ω | CC 检测到 USB0_ID，默认装 |
| R168 | 0Ω | U16 FLG 到 USB0_OC，默认装 |
| R163 | 2K | FLG 到 LED1，默认装 |
| R156/R157 | 10K | BOOT_0/1 下拉，默认装 |
| R171/R172/R173 | 1K/2K/1.5K | RGB LED 限流，默认装 |
| R165/R170/R115 | 10K | KEYA/B/C 上拉，默认装 |
| R148 | 10K | FT2232 RESET# 上拉，默认装 |
| R150 | 12K | FT2232 REF，默认装 |
| R192/R193/R194 | 10K | FT2232 EEPROM 脚上拉，默认装 |
| R188/R189 | 5.1K | 调试 USB-C CC 下拉，默认装 |
| R190/R191 | 1K | LED5/LED6 限流，默认装 |
| R81/R110..R113 | 100Ω | JTAG 串阻，默认装 |
| R79/R80 | 10K | JTAG TMS/TDI 上拉，默认装 |
| R66..R68/R76..R78 | 33Ω | 栅极串阻，默认装 |
| R72..R74/R82..R84 | 22K | 栅源电阻，默认装 |
| R88 | 10K | FAULT 上拉，默认装 |
| R89 | 2K | LED4 限流，默认装 |
| R95 | 0Ω | SCREF 上拉到 +3V3，默认装 |
| R116 | 0Ω | U9 VS 到 VM，默认装 |
| R75 | 0Ω | U9 DT/MODE 到 BGND，默认装 |
| R103 | 4.7K | U20 SET 到 GND，默认装 |
| R109 | 10K | U8 OE 上拉，默认装 |
| R138 | 2.49K | RTL8211E RSET，默认装 |
| R46/R53 | 2.49K | EtherCAT RBIAS，默认装 |
| R51/R52 | 4.7K | EtherCAT MDIO/MDC 上拉，默认装 |
| R140/R179 | 200K/10K | VBUS 分压，默认装 |
| R15/R17/R20 | 62K | 相电压分压上臂，默认装 |
| R22/R23/R24 | 2.4K | 相电压分压下臂，默认装 |
| R16/R18/R21 | 2.4K | OUT_M 汇合，默认装 |
| R184 | 1K | Z_M 限流，默认装 |
| R19/R180/R181 | 4.7K | 比较器输出上拉，默认装 |
| R25/R30/R31/R38/R40/R45 | 10K | 运放反馈/偏置，默认装 |
| R26/R29/R32/R36/R41/R44 | 1K | 运放输入，默认装 |
| R27/R33/R42 | 10Ω | 电流输出滤波，默认装 |
| R28/R34/R43 | 10K | CP 求和，默认装 |
| R37 | 1.1K | CP 对地，默认装 |
| R117 | 10Ω | CP 串阻，默认装 |
| R35/R39 | 10K | VREF 分压，默认装 |
| R183 | 4.7K | NTC1 下臂，默认装 |
| R12/R14 | 10K | 复位上拉/唤醒下拉，默认装 |
| R69 | 2K | LED2 限流，默认装 |
| R6 | 47K | U1 RON，默认装 |
| R4/R5 | 200K/62K | U1 FB 分压，默认装 |
| R1/R3 | 22.1K/100K | U2 FB 分压，默认装 |
| R90/R91/R93/R94/R98/R99/R107/R108 | 22Ω | QEI/RS485 串阻，默认装 |
| R196 | 22Ω | SEI2_CK 到 QEIZ，默认装 |
| R144/R146/R141/R142 | 60.4Ω | CAN 分裂终端，默认装 |
| R121/R128 | 33Ω | RTL8211E RXCK/TXCK 串阻，默认装 |

【待核实】上表“默认装”仅表示图中未标 NC/DNP，且数值已给出；没有装配 BOM 时不能保证实物一定贴装。

## 10. 复位、时钟、调试

### 10.1 复位

- 主复位 `RSTN`：SW1 按下拉低；R12 10K 上拉到 +3V3；C47 100nF 到 GND；U3(M3) 接收。
- 调试复位 `FT_RESET_N`：U22 ACBUS1(27) -> R149 0Ω -> `RSTN`。因此 FT2232 也能复位主控。
- J7 的 SRST(15) 未连接；外部 JTAG 不能通过 J7 的 SRST 直接复位主控（除非经其他路径）。
- 【待核实】`RSTN` 与 `RSTN`（旁边 1 为跨页号） 的命名在 page-1/page-9 之间可能为同一网络的跨页标记；本文按“同一复位网络”描述，但保留该命名差异。

### 10.2 时钟

| 时钟 | 频率/精度 | 负载 | 电容 |
|---|---|---|---|
| X3 | 24MHz ±10ppm | U3 XTALI/XTALO | C45/C46 12pF；R13 1M |
| X1 | 25MHz ±10ppm | U4 RTL8211E | C113/C114 18pF |
| X2 | 12MHz ±10ppm | U22 FT2232HL | C171/C172 12pF |

- 三颗晶振均为无源晶体，分别服务主控、PHY、调试芯片；不能互换频率。
- 【待核实】X2 的负载电容位号在 page-9 图中标为 C171/C172；其中 C171 与 U23 区域相邻，实际对应关系以原图为准。

### 10.3 调试链路

```text
PC USB -> J13 USB-C -> D4/U23/L4 -> U22 FT2232HL
U22 ADBUS0..3 -> FT_JTAG_TCK/TDI/TDO/TMS -> U24 -> JTAG_TRST/TCK/TMS/TDO/TDI -> MCU PA4..PA8
U22 ACBUS0 -> FT_JTAG_TRST
U22 ACBUS1 -> FT_RESET_N -> R149 0Ω -> RSTN
U22 BDBUS0/1 -> FT_URT_TXD/RXD -> U24 -> TXD0/RXD0 -> MCU PA0/PA1 + J12
外部 JTAG J7 -> 100Ω 串阻 -> 同名 JTAG 网络 -> U24/MCU
J7(20) JLINK_DET -> Q13 -> U24 OE# 隔离
```

- U24 的方向/使能：OE# 低时导通，高时高阻；Q13 和 R195 决定 OE#。
- 【推断】外部 JTAG 插入时通过 J7(20) 拉低 JLINK_DET，关断 Q13，OE# 上高，U24 隔离 FT2232；不插外部 JTAG 时 Q13 导通，OE# 低，FT2232 接管。该推断需实测确认探头是否短接 pin20。

## 11. 网络交叉索引

下表列出跨页/跨模块的关键网络。`源`/`目的`只列主要连接，不代替完整网表。

| 网络 | 页 | 源 | 目的/说明 |
|---|---|---|---|
| `VM` | 1/3/4 | J6-5、U1 VIN、U9 VS | 三相桥上管漏极、制动 J5、VBUS 分压 R140 |
| `+5V` | 1/3/4/5/7/8/9 | U1 SW-L1、D25 阴极、J13 D4 | U2/U10/U11/U12/U13/U16/U20、LED、上拉 |
| `+3V3` | 1/2/3/4/5/7/8/9 | U2 输出经 FB4 | MCU VCC_3V3、U4/U5/U6/U8/U17/U21、上拉 |
| `+3V3A` | 1/4 | U11 OUT | U3 VANA 经 FB7、U18、选配 R182、D27 钳位 |
| `+3.3VD` | 9 | +3V3 经 R118 0Ω | U22/U24；J7 VTREF 直接标 +3V3 |
| `+1.8VD` | 9 | U22 VREGOUT(49) | U22 去耦 |
| `VREF` | 1/4 | U10 OUT 经 FB2 | U3 VREFH、U6D 分压 |
| `+12VREG` | 3 | U9 REG12(5) | Q11 栅极 R63、U9 内部 |
| `+5P` | 8 | U16 OUT(1) | J4 VBUS 四脚、U14 IN |
| `VBUS` | 1/8 | U14 OUT(1) | D25 到 +5V、U3 USB0_VBUS 经 R9 |
| `5V_QEI` | 7 | +5V 经 R70 0Ω | U8 VCCB、U20 VIN、QEI 上拉 |
| `5V_RS` | 7 | U20 VOUT(1) | U7/U19 VCC |
| `VCC_3V3` | 1/2 | +3V3 经 R7 0Ω | U3 VIO_B01、VPLLVUSB |
| `DCDC_GND` | 1 | U3 N1/P2 | R8 0Ω 到 GND |
| `AGND` | 1/4 | 模拟地 | R59 0Ω 到 GND；U5/U6/U10/U11/U18 |
| `BGND` | 3 | 功率地 | R164 0Ω 到 GND；U9 EP、Q11 源、PR1-3 下端 |
| `RSTN` | 1/9 | SW1、R12、C47、U3 M3 | R149 0Ω 到 FT_RESET_N |
| `WAKEUP` | 1 | SW2、R14、C48 | U3 L3 |
| `IN_UH/IN_UL` | 2/3 | PD0/PD1 | U9(7/10) |
| `IN_VH/IN_VL` | 2/3 | PD2/PD3 | U9(8/11) |
| `IN_WH/IN_WL` | 2/3 | PD4/PD5 | U9(9/12) |
| `GHS1/GLS1` | 3 | U9(22/24) | Q1/Q4 栅极 |
| `GHS2/GLS2` | 3 | U9(18/20) | Q2/Q5 栅极 |
| `GHS3/GLS3` | 3 | U9(14/16) | Q3/Q6 栅极 |
| `OUT_U/OUT_V/OUT_W` | 3/4 | Q1/Q2/Q3 源、Q4/Q5/Q6 漏 | J6-1/2/3、相电压分压 |
| `SNSU_P/N` | 3/4 | PR1(3/4) | U6A 输入 |
| `SNSV_P/N` | 3/4 | PR2(3/4) | U6B 输入 |
| `SNSW_P/N` | 3/4 | PR3(3/4) | U6C 输入 |
| `I_U/I_V/I_W` | 4/2 | U6A/B/C 输出 | PF28/PF29/PF30、CP 求和 |
| `CP` | 2/3/4 | 求和节点 R117 | PF9、U9(1 CP) |
| `FAULT` | 3 | U9(6) | R88/R89/LED4；未见 MCU |
| `SCREF` | 3 | R95 0Ω 到 +3V3 | U9(3) |
| `PU/PV/PW` | 4 | OUT_U/V/W 分压 | 比较器同相、OUT_M 汇合 |
| `OUT_M` | 4 | R16/R18/R21 汇合 | 比较器反相、R184 到 Z_M |
| `Z_U/Z_V/Z_W` | 2/4 | U5 输出 | PF5/PF6/PF7；R85-87 是默认 NC 的输入/输出可选旁路 |
| `Z_M` | 2/4 | R184 | PF10 |
| `VBUS_VOL` | 2/4 | R140/R179 分压 | PF31 |
| `NTC1` | 2/4 | U18/R182 | PF8 |
| `BRAKE` | 2/3 | PC27 | 图内未见连到 Q12 |
| `P0RD_N/P` | 2/6 | PA20/PA21 | J1 |
| `P0TD_N/P` | 2/6 | PA22/PA23 | J1 |
| `P1RD_N/P` | 2/6 | PA16/PA17 | J2 |
| `P1TD_N/P` | 2/6 | PA18/PA19 | J2 |
| `P0RBIAS` | 2/6 | PA27 | R46 2.49K 到 GND |
| `P1RBIAS` | 2/6 | PA24 | R53 2.49K 到 GND |
| `P0LED0/1` | 2/6 | PA29/PA28 | J1 LED |
| `P1LED0/1` | 2/6 | PA26/PA25 | J2 LED |
| `MDIO/MDC` | 2/6 | PA30/PA31 | J1/J2 侧上拉 |
| `RTL_RXDV` | 2/5 | PB0 | U4(13) |
| `RTL_RXD0..3` | 2/5 | PB1/PB2/PB3/PB4 | U4(14/16/17/18)，按此顺序 |
| `RTL_RXCK` | 2/5 | PB5 | U4(19) |
| `RTL_TXCK` | 2/5 | PB6 | U4(22) |
| `RTL_TXD0..3` | 2/5 | PB7..PB10 | U4(23..26) |
| `RTL_TXEN` | 2/5 | PB11 | U4(27) |
| `RTL_MDC/MDIO` | 2/5 | PF0/PF1 | U4(30/31) |
| `RTL_RST/INT` | 2/5 | PF2/PF3 | U4(29/20) |
| `G0_MDI0_P/N` | 5 | U4(1/2) | RJ1(2/3) |
| `G0_MDI1_P/N` | 5 | U4(4/5) | RJ1(4/7) |
| `G0_MDI2_P/N` | 5 | U4(7/8) | RJ1(6/5) |
| `G0_MDI3_P/N` | 5 | U4(10/11) | RJ1(8/9) |
| `G0_LINK/ACTIVITY` | 5 | U4(35/34) | RJ1 LED |
| `QEIA/QEIB/QEIZ` | 2/7 | PC7/PC6/PC5 | U8 A 侧 |
| `QEIA_C/QEIB_C/QEIZ_C` | 7 | U8 B 侧、U7/U19 输出 | J14 |
| `HU/HV/HW` | 2/7 | PC0/PC1/PC2 | U8 A 侧 |
| `HU_C/HV_C/HW_C` | 7 | U8 B 侧 | J14 |
| `SEI0CK` | 2/7 | PF4 | U8 A3 |
| `SEI2_CK` | 2/7 | PD12 | R196 22Ω 到 QEIZ |
| `SEI2TXD/RXD` | 2/7 | PD15/PD14 | U8/U21 |
| `RSDE` | 2/7 | PD6 | U19 DE/RE# |
| `RSPWON` | 2/7 | PD7 | U20 EN |
| `SEI2DE` | 2/7 | PD13 | U21 DE/RE# |
| `RS_U_P/N` | 7 | U21 A/B | R107/R108 到 RS_P/N |
| `5V_RS` | 7 | U20 | U7/U19 |
| `CAN4_TXD/RXD/STBY` | 2/8 | PC16/PC17/PC18 | U12 |
| `CAN7_TXD/RXD/STBY` | 2/8 | PC31/PC30/PC29 | U13 |
| `CAN4_P/N` | 8 | U12/L9 | J8(2/1) |
| `CAN7_P/N` | 8 | U13/L3 | J9(2/1) |
| `USB0_DP/DN` | 1/8 | U3 L14/L13 | 经 page-8 端口标签对应 `USB0_P/N` |
| `USB0_P/N` | 8 | L10 | L10 另一侧为 `USB0+/USB0-` 到 J4 |
| `USB0_PWR` | 8 | R158 | U16 EN/Q7 |
| `USB0_ID` | 8 | R169 | CC 检测 |
| `USB0_OC` | 8 | R168 | U16 FLG |
| `BOOT_0/1` | 2/8 | PA2/PA3 | SW3 |
| `KEYA/KEYB/KEYC` | 2/8 | PC14/PC15/PC19 | SW4/SW5/SW6 |
| `LED_R/G/B` | 2/8 | PB25/PB24/PA9 | Q9/Q10/Q8 |
| `D0/D1/D2/D3/SCLK/CS0` | 2/8 | PB26/PB27/PB28/PB31/PB29/PB30 | U17，按此顺序 |
| `FT_USB_P/N` | 9 | J13/U23/L4 | U22(8/7) |
| `FT_JTAG_TCK/TDI/TDO/TMS` | 9 | U22(16..19) | U24 -> MCU |
| `FT_JTAG_TRST` | 9 | U22(26) | U24/J7 |
| `FT_RESET_N` | 9 | U22(27) | R149 0Ω -> RSTN |
| `FT_URT_TXD/RXD` | 9 | U22(38/39) 经 R186/R187 | U24 后分别接 RXD0/TXD0，交叉连接 |
| `JTAG_TRST/TCK/TMS/TDO/TDI` | 9 | U24 | MCU PA8/PA6/PA7/PA4/PA5 |
| `TXD0/RXD0` | 9 | U24/MCU PA0/PA1 | J12 |
| `JLINK_DET` | 9 | J7(20) | Q13 栅极 |

## 12. 原图中的标注冲突、配置条件与未给出的信息

下表区分真正的连接疑点与已明确的选配条件；不把跨页编号或常规未用引脚当作错误。

| 事项 | 已能从原图确认的内容 | 留给后续使用者的判断边界 |
|---|---|---|
| U3C A13 标注冲突 | A13 行框内 PC24，外网 PC23；B14 行框内和外网均 PC24 | 本文按外网记录，精确物理引脚用途需要芯片手册或原 CAD 核准 |
| BRAKE 到 Q12 的连接 | PC27 接 BRAKE 标签；Q12 栅端只见 R64/R139/C139 偏置，没有同名 BRAKE 标签或接线 | 不能断言 MCU 已能控制制动；不能默默把这段补连 |
| U9 SCREF 的 Open/Closed 注释 | R95 0Ω 接 +3V3；R97 10K 接 BGND，C87 100nF（NC）并接 BGND；只有 C87 旁明确标 NC；旁注给出开闭与 SC 保护关系 | 未见明确开关位号，不能确定“开/闭”具体对应哪个装配操作；内部阈值、模式需要器件资料 |
| 比较器旁路 R85/R86/R87 | 默认 NC；PU/PV/PW 分别直达同相输入，输出分别是 Z_U/Z_V/Z_W | 默认输入输出分离；若选装 0Ω，会把各相分压节点接至对应输出网，必须确认预期配置，不能套用默认比较器模型 |
| 编码器单端网复用 | U8 B 侧和差分接收器输出共接部分 `_C` 网络；5V_RS 受 RSPWON 控制 | 模式、供电和 GPIO 方向需配合，不能宣称所有连接可以同时独立驱动 |
| 编码器模式表 | PWON/SSI2DE 与网络名 RSPWON/SEI2DE 不完全一致，x 和 1 的行有重叠 | 按原表保留，不能根据重叠行自行补出唯一的互斥控制真值表 |
| EtherCAT P0 LED | J1 的 LED 两端由同一 P0LED 网络直连/经 330Ω 分别接入；P1 端接法不同 | 本文保留原连接；不能为了图形对称改写成 J2 的接法 |
| FAULT 去向 | U9 nFAULT 只见本地上拉和 LED4，未见连接 MCU 引脚 | 不补出不存在于图中的故障中断线 |
| USB0 角色与供电 | +5V -> U16 -> +5P/J4；+5P -> U14 -> VBUS -> D25 -> +5V；R155 和 CC 下拉有 NC/DNP 配置 | 实际 USB 角色、开关行为和防回流特性取决于装配、芯片特性和固件；图示不能证明 USB PD 功能 |
| J10 供电选择 | +5V 0Ω 与 +3V3 NC/0Ω 两条选配，两个电阻位号都为 R? | 按图意图默认选 +5V，但没有装配 BOM 不能确认实物；不能把两电源同时直接连接 |
| J3 的 G 端 | 信号 1=VBAT、2=GND；另两个 G 端接地 | 图中未注 G 端的机械/屏蔽含义；这不改变 1/2 信号针脚定义 |
| J7 简化符号 | 明画 GND(4)、DET(20) 及信号脚；其余部分位置未单独列出，若干信号标叉未接 | 不把常见标准 JTAG 接口定义无条件补成此板已确认连接 |
| 装配及额定能力 | 已保留 NC/DNP、元件数值、电容耐压和电感标注 | 缺少装配 BOM、PCB 与测量；不能从元件型号或耐压直接推导板额定输入、相电流、散热能力 |
| 内部设置与软件 | VDD_SOC 目标值、U9 内部保护阈值/死区、PWM 频率和 ADC 时序未在图中给出 | 后续若需要这些数值，应另行查对应器件资料和固件；不使用常见默认值替代 |

明确的同网/跨页关系：USB0_DP 与 USB0_P、USB0_DN 与 USB0_N 在第 8 页左上通过端口和网络标签直接相连；RSTN 后的 1 是跨页编号。PF0/PF1 的 RTL_MDC/RTL_MDIO 与 PA31/PA30 的 MDC/MDIO 是两组不同的板级线路，分别用于 U4 与集成 PHY，不是因名称相似就存在短接。

## 13. 逐页覆盖清单

| 页 | 文件 | 主要内容 | 本文覆盖 |
|---|---|---|---|
| 1 | power.SchDoc | U1/U2 电源、U3A 电源脚、U10/U11 基准/LDO、复位、24MHz、VBAT、J3 | 4.1 |
| 2 | io.SchDoc | U3B/U3C/U3D 端口、J10 MSP2402、J11 2×22 | 4.2、5 |
| 3 | bridge.SchDoc | U9 STDRIVE101、Q1..Q6 三相桥、PR1..PR3、FAULT/SCREF、制动 | 4.3、6 |
| 4 | monitor.SchDoc | VBUS 分压、相电压分压/OUT_M、LM339、TP2274 电流放大、CP、NTC | 4.4、7 |
| 5 | enternet.SchDoc | RTL8211E、25MHz、RJ1 HR911130A、MDI/LED | 4.5 |
| 6 | ethercat.SchDoc | J1/J2 HR911105A、P0/P1 差分、RBIAS、MDIO/MDC、LED | 4.6 |
| 7 | encoder.SchDoc | QEI/RS485、U8 TXB0108、U20 MT9700、U7/U19/U21、J14、模式表 | 4.7 |
| 8 | misc.SchDoc | CAN4/CAN7、USB0/J4/U14/U16、QSPI、BOOT、按键、RGB LED | 4.8、8 |
| 9 | Debug.SchDoc | FT2232HL、J13 调试 USB、J7 JTAG、U24 隔离、J12 UART | 4.9、10 |

## 14. 使用本文继续分析的方法

先阅读第 2/3 节理解功能块与供电，再按第 4 节查看对应页面的器件和连接。查 MCU 球位使用第 5 节，查外部接口使用第 8 节，查装配选项使用第 9 节；网络交叉索引在第 11 节。第 12 节保留原图中的真实标注冲突和配置条件，第 15 节给出明确假设下的计算关系。

本文描述的是图示硬件连接和可由其推导的工作机制；原图没有给出的芯片内部参数、固件行为和实物装配状态仍保持未知。

## 15. 从图示拓扑推导的计算关系

本节是**拓扑计算/功能解释**，不是原图给出的性能指标。假设电阻为标称值、运放在线性范围、采样端高阻；未计入误差、寄生、钳位、芯片输入限制及软件校准。

### 三相桥与采样时序

每相由一只上管和一只下管构成半桥：`VM -> 上管 -> OUT_x -> 下管 -> PRx(10mΩ) -> BGND`。六路 `IN_UH/UL/VH/VL/WH/WL` 控制 U9，再由 U9 的高低侧驱动脚控制 MOS 栅极。BOOT 电容相对各相输出浮动，为高侧驱动提供局部储能；这不意味着原图已证明任意占空比都可持续工作。

PR1/PR2/PR3 位于三只下管源极与 BGND 之间，所以是**三下桥臂分流采样**。某一相通过上管导通时，其相电流不会必然流过该相下管分流器。后续 AI 做 FOC 或电流环分析时，应结合 PWM 状态、下管导通窗口、采样时刻和极性解释读数，不能直接假设三路在所有时刻都测到完整相电流。图中没有给出 PWM 频率、死区、ADC 触发时序或完整保护阈值。

### 电流通道标称关系

U6D 将 VREF 经两只 10kΩ 等分后缓冲，得到 `Vbias ≈ VREF / 2`。VREF 标称 3.3V 时，Vbias 标称约 1.65V。

三路差分网络的输入电阻为 1kΩ、反馈/偏置电阻为 10kΩ。忽略交流补偿和输出负载：

```text
V(I_U) ≈ Vbias + 10 × [V(SNSU_P) - V(SNSU_N)]
V(I_V) ≈ Vbias + 10 × [V(SNSV_P) - V(SNSV_N)]
V(I_W) ≈ Vbias + 10 × [V(SNSW_P) - V(SNSW_N)]
```

按 `SNSx_P 相对 SNSx_N 为正` 定义分流器电流正方向，10mΩ 分流器给出 `10 × 0.01Ω = 0.1V/A` 的标称电压灵敏度。由此：`I_shunt ≈ [V(I_x) - Vbias] / (0.1V/A)`。这只是模拟增益，不能由此宣称板卡允许的相电流范围；运放输出摆幅、ADC 满量程、分流器功耗和 PCB 散热仍需另外确认。

CP 前端不是简单平均器。三路 I_U/I_V/I_W 电压各经 10kΩ 接到共同节点，共同节点经 1.1kΩ 接 AGND：

```text
V(CP) ≈ [V(I_U) + V(I_V) + V(I_W)] / [3 + 10000/1100]
      ≈ 0.082707 × 三路电压之和
```

此处忽略 R117 后接收端负载。零分流电流时三路各约 1.65V，因此 CP 直流基线约 0.4094V。CP 同时连 U9 的 CP 脚和 MCU PF9。原图未直接给出 CP 触发阈值或软件阈值，不能把该基线当成保护阈值。

### 母线与相电压网络

`VM -> R140 200kΩ -> VBUS_VOL -> R179 10kΩ -> AGND`，在钳位二极管不导通、输入高阻时：`V(VBUS_VOL) ≈ VM / 21`。D27/D28 将采样节点向 +3V3A/AGND 钳位；不能将这种小信号钳位理解为 VM 主母线的浪涌吸收器。

PU/PV/PW 各由 62kΩ 从对应相输出取样，各有 2.4kΩ 到 AGND，又各经 2.4kΩ 连接共同 OUT_M。三路互相有负载关系，不能逐路机械套用孤立的 62kΩ/2.4kΩ 分压公式。

在三路元件对称、忽略电容的直流条件、R85/R86/R87 按 NC 不装、比较器及 Z_M 接收端高阻的条件下，定义 `Vavg = [V(OUT_U)+V(OUT_V)+V(OUT_W)]/3`：

```text
V(OUT_M) ≈ [2.4 / (62 + 2.4)] × Vavg ≈ 0.037267 × Vavg
V(PU) - V(OUT_M) ≈ [2.4 / (2.4 + 2×62)] × [V(OUT_U) - Vavg]
                 ≈ 0.018987 × [V(OUT_U) - Vavg]
```

V/W 两相对应替换。这个对称网络具有构造缩小后中性参考的意图；默认不装 R85/R86/R87 时，比较器输入与输出分离，可按此网络理解相电压与共同参考的比较；若选装 0Ω，则分压节点与对应输出网相连，须重新分析。此解释不能证明固件已经实现无感换相。

### 制动支路的逻辑解释

Q12 导通时，将 Q11 栅极拉向 BGND，倾向于关断 Q11；Q12 关断时，R63 将 Q11 栅极拉向 +12VREG，倾向于使 Q11 导通。Q11 导通后，外接 J5 电阻支路可形成 `VM -> 外接制动电阻 -> Q11 -> BGND` 的耗能路径。这是按 MOS 拓扑解释的逻辑。

但是图中 Q12 栅极目前仅见 +3V3 经 R64/R139 的偏置和 C139 滤波，左上角 `PC27 -> BRAKE` 未见实际接到此节点。因此文档不能把 PC27 对制动支路的控制写成已经接通，也不能推导可靠的软件制动功能。R62 标为 NC/10mΩ，不应把它当成已装的常规制动耗能电阻。

### 编码器与调试复用

编码器侧 U8 的 B 侧、U7/U19 接收器输出以及 J14 部分引脚共用 `_C` 网络，既可能用于 TTL，又可能用于差分接收后的逻辑信号。必须结合 5V_RS 上电状态、RSDE/SEI2DE、MCU 引脚方向和实际装配判断，不能把所有引脚当作同时可自由驱动的独立通道。

板载 FT2232HL 与 MCU 之间由 U24 总线开关连接。R197 默认将 Q13 栅极拉高，Q13 拉低 U24 OE#，倾向于接通板载调试路径；若外部调试器将 J7 的 JLINK_DET 拉低，则 Q13 关断，R195 将 OE# 拉高，倾向于隔离板载路径。是否与具体外部调试器匹配，仍由其 DET 针脚实际行为决定。J7 的 SRST 脚未接，不应假设外部探头可经该针脚直接控制系统复位。

