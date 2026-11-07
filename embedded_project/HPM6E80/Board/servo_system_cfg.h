#ifndef SERVO_SYSTEM_CFG_H
#define SERVO_SYSTEM_CFG_H

// 本板参数选择：硬件参数 + 电机模组参数。
// 换板改 driver_parameter_*，换电机改 motor_parameter_*，其余代码不动。

#include <stdint.h>
#include <stdbool.h>

// ADC 基准与分辨率：VREFH 由 U10 REF3033 提供 3.3V，ADC 16bit
#define ADC_REFERENCE_V     (3.3f)
#define ADC_REFERENCE_MV    (3300)
#define ADC_RESOLTION       (65536.0f)

#include "driver_parameter_hw_hpm6emotorv20.h"
#include "motor_parameter_hpm6emotorv20_bldc12v.h"

// 本板在原始工程里由 data_type_define.h 引用，这里补齐两处只在硬件层用到的常量
#define UVW_CURRENT_SAMP_MIN_A          (-1.0f * DRIVER_PEAK_CURRENT_A)

#endif // SERVO_SYSTEM_CFG_H
