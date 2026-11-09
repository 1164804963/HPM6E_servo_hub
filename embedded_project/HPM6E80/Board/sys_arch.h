/*
 * [ECAT 适配] sys_arch.h 桩。
 *
 * SDK 的 HPM ESC port 层在 EOE_SUPPORTED=1（baremetal）时会引入 lwIP 的
 * sys_arch.h 并周期调用 sys_timer_callback()（lwIP 的 tick）。
 * 本工程 EtherCAT 从站只做 CoE/CiA402，不做 EoE 真实 TCP/IP 转发，无需 lwIP。
 * 这里提供最小桩：sys_timer_callback 为空实现，满足 port 层编译与链接。
 */
#ifndef ECAT_SYS_ARCH_STUB_H
#define ECAT_SYS_ARCH_STUB_H

static inline void sys_timer_callback(void)
{
    /* lwIP sys tick —— 本工程不跑 lwIP，空实现 */
}

#endif
