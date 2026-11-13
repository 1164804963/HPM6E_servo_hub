#ifndef SERVO_BRINGUP_H
#define SERVO_BRINGUP_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * 上电自检：补上 board_public/system_manage/system_init.c 里 HalInit() 之后的两步。
 * 1. 等编码器出第一帧有效数据，用它的多圈/单圈值初始化控制层位置状态；
 * 2. 桥臂封锁状态下做三相电流零漂校准。
 * 返回 false 表示编码器没就绪或校准失败，此时不要使能电机。
 * 必须在 servo_app_init()（MotorCtrlInit/AppInit）之后、board_start_ctrl_tick() 之前调用。
 */
bool servo_bringup_self_test(void);

/* 打印上电自检的原始采样（母线、三相电流零点），给 L0 做记录用。 */
void servo_bringup_print_l0(void);

#ifdef __cplusplus
}
#endif

#endif // SERVO_BRINGUP_H
