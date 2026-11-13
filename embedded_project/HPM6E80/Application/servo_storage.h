#ifndef SERVO_STORAGE_H
#define SERVO_STORAGE_H

#ifdef __cplusplus
extern "C" {
#endif

/* 主循环里每圈调一次。到服务时间才处理存储命令，不保证严格 1 ms。 */
void servo_storage_poll(void);

#ifdef __cplusplus
}
#endif

#endif /* SERVO_STORAGE_H */
