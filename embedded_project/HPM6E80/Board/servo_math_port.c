#include <math.h>

#include "hpm_math.h"

/*
 * hpm_dsp_sin_f32 / hpm_dsp_cos_f32 的软件实现。
 * 便携层的 yuanhub_math.h 在 HPMSOC 分支下用这两个函数名，SDK 只在 Andes DSP
 * 库里提供它们；本工程用 riscv gcc，直接落到标准库。
 * 20kHz 电流环里每次调用 2 次 sin/cos，性能见 doc/PORTING_HPM6E80.md 的时序记录。
 */

float hpm_dsp_sin_f32(float src)
{
    return sinf(src);
}

float hpm_dsp_cos_f32(float src)
{
    return cosf(src);
}
