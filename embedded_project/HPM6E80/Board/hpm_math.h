#ifndef HPM_MATH_H
#define HPM_MATH_H

/*
 * 本工程替代 SDK 的 middleware/hpm_math/hpm_math.h。
 *
 * SDK 的 hpm_math 只实现 Andes DSP 指令集的版本（需要 nds 工具链），本工程用
 * riscv32-unknown-elf-gcc，所以只补便携层实际用到的两个函数，
 * 实现见 Board/servo_math_port.c（标准库 sinf/cosf 包装）。
 *
 * 便携层 common/math_lib/yuanhub_math.h 在 HPMSOC 分支下直接调用这两个名字。
 */

#ifdef __cplusplus
extern "C" {
#endif

float hpm_dsp_sin_f32(float src);
float hpm_dsp_cos_f32(float src);

#ifdef __cplusplus
}
#endif

#endif // HPM_MATH_H
