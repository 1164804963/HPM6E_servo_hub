#ifndef SERVO_HOST_H
#define SERVO_HOST_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * 上位机通道：UART0（COM4，921600 8N1）上同时跑两件事——
 *   1. 官方 servo_hub 上位机的 MAVLink 协议（帧首字节 0xFD / 0xFE）
 *   2. 本板调试台（其余字节）
 * 分流按字节做，所以两条通道共用一个串口，不用改接线。
 */
void servo_host_init(void);
void servo_host_poll(void);
/* UART0 中断服务（接收/发送都在这里处理，主循环不再轮询） */
void servo_host_uart_isr(void);

#ifdef __cplusplus
}
#endif

#endif // SERVO_HOST_H
