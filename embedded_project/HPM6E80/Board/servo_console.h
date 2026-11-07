#ifndef SERVO_CONSOLE_H
#define SERVO_CONSOLE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * 串口调试台：UART0（SDK 控制台，921600 8N1），主循环里轮询。
 * 只做"看状态 + 给指令"，控制逻辑仍在 20kHz/1kHz 中断里。
 *
 * 命令表见 servo_console.c 的 s_commands，或串口输入 help。
 */
void servo_console_init(void);

/* 主循环里每圈调一次：只管心跳打印，收字节由 servo_host_poll() 分发。 */
void servo_console_poll(void);

/* 处理一个收到的字节（非 MAVLink 的字节由 servo_host_poll() 转进来）。 */
void servo_console_feed(uint8_t c);

/* 20kHz 电流环中断里调用：采集 idq 波形（console 的 scope 命令用）。 */
void servo_console_isr_sample(void);

/* 1kHz 位置环里调用：采集编码器计数序列（console 的 escope 命令用）。 */
void servo_console_isr_encoder(uint32_t cnt);

#ifdef __cplusplus
}
#endif

#endif // SERVO_CONSOLE_H
