#ifndef DRV_ENCODER_H
#define DRV_ENCODER_H

// 编码器驱动层：把 encoder_mt6816（已在本板验证过的 SPI 绝对式驱动）包装成
// bsp_api.h 需要的单圈/多圈计数接口。
//
// 本板只有电机端编码器（MT6816，14bit，16384 P/R），负载端编码器不存在。

#include <stdint.h>
#include <stdbool.h>
#include "data_type_define.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 初始化 SPI7 + 引脚。失败时返回 false，调用方必须显式打印，否则现象只是"电机不转"。 */
bool drv_encoder_init(void);

/* 每个 20kHz 控制周期调一次：SPI 读角 + 刷新缓存 + 多圈累计。 */
void drv_encoder_sample(void);

uint32_t drv_encoder_get_cnt(ENCODER_ID id);
int64_t drv_encoder_get_turns(ENCODER_ID id);
bool drv_encoder_get_state(ENCODER_ID id);
uint8_t drv_encoder_get_type(ENCODER_ID id);

/* 上电以来 SPI 读角失败（CRC/状态位）的帧数，用来判断编码器线是否被干扰。 */
uint32_t drv_encoder_get_fail_count(void);

#ifdef __cplusplus
}
#endif

#endif // DRV_ENCODER_H
