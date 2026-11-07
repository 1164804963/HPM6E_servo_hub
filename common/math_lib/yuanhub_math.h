#ifndef YUANHUB_MATH_H
#define YUANHUB_MATH_H

/* #include "yuanhub_math.h" */

#include "coordinate_conversion.h"

//根据不同硬件平台选择对应库函数
#if defined(ARM_MATH_CM7) || defined(ARM_MATH_CM4) || defined(ARM_MATH_CM3)
#include "arm_math.h"
#define yuanhub_sin_f32 arm_sin_f32
#define yuanhub_cos_f32 arm_cos_f32
#define yuanhub_sqrt_f32 _sqrtf
#elif defined(HPMSOC_HAS_HPMSDK_MCHTMR)
#include "hpm_math.h"
#include "math.h"
#define yuanhub_sin_f32 hpm_dsp_sin_f32
#define yuanhub_cos_f32 hpm_dsp_cos_f32
#define yuanhub_sqrt_f32 sqrtf
#else  //其他平台使用标准库函数
#include "math.h"
#define yuanhub_sin_f32 sinf
#define yuanhub_cos_f32 cosf
#define yuanhub_sqrt_f32 sqrtf
#endif


// 公共宏定义
#define MATH_ARMS2APEAK (1.414213562373f) // 电流指令 Arms 转 Apeak 系数
#define MATH_PI (3.14159265358979323846f)
#define MATH_RAD2RPM   (9.549296585513721f)  // 60/(2*pi)
#define MATH_ABS(x) (((x) > 0) ? (x) : -(x))
#define MATH_ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))
#define MATH_FLOAT_EQUAL (1E-4F)  // 判断2个float是否相等 的误差范围
#endif