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
 *
 * UART RX 由HDMA搬入非缓存ring，IRQ只处理错误和TX；MAVLink/console的解析
 * 在 servo_host_poll() 前台执行。
 */
void servo_host_init(void);
void servo_host_poll(void);
/* UART0 中断服务：线路错误恢复 + 非阻塞TX，不在ISR解析协议/控制台 */
void servo_host_uart_isr(void);

#ifdef __cplusplus
}
#endif

#endif // SERVO_HOST_H
