#include "unit_conversion.h"
#include "libdivide.h"


static uint32_t numerator[UNIT_CONVERSION_NUM] = {1, 1, 1, 1, 1, 1};   // 单位转换系数分子
static uint32_t denominator[UNIT_CONVERSION_NUM] = {1, 1, 1, 1, 1, 1}; // 单位转换系数分母

static struct libdivide_s64_t div64_numerator[UNIT_CONVERSION_NUM] = { 0 };
static struct libdivide_s64_t div64_denominator[UNIT_CONVERSION_NUM] = { 0 };

//设置分子
void set_numerator(uint32_t val, UNIT_CONVERSION_TYPE type)
{
    if (val)
    {
        numerator[type] = val;
        div64_numerator[type] = libdivide_s64_gen(val);
    }
}

//设置分母
void set_denominator(uint32_t val, UNIT_CONVERSION_TYPE type)
{
    if (val)
    {
        denominator[type] = val;
        div64_denominator[type] = libdivide_s64_gen(val);
    }
}

//分子除以分母
int conver_num_div_den(int64_t *src, int64_t *dec, UNIT_CONVERSION_TYPE type)
{
    struct libdivide_s64_t* temp_div = &div64_denominator[type];

    //第1次除法
    int64_t quor = libdivide_s64_do(*src, temp_div);
    int64_t rem = (*src - quor * denominator[type]) * numerator[type];

    //第2次除法
    int rem_quor = libdivide_s64_do(rem, temp_div);
    int rem_rem = rem - (int64_t)rem_quor * denominator[type];

    *dec = quor * numerator[type] + rem_quor;

    // 向零取整改为向下取整
    if (rem_rem < 0)
    {
        *dec -= 1;
    }

    return rem_rem;
}

//分母除以分子
int conver_den_div_num(int64_t *src, int64_t *dec, UNIT_CONVERSION_TYPE type)
{
    struct libdivide_s64_t* temp_div = &div64_numerator[type];

    //第1次除法
    int64_t quor = libdivide_s64_do(*src, temp_div);
    int64_t rem = (*src - quor * numerator[type]) * denominator[type];

    //第2次除法
    int rem_quor = libdivide_s64_do(rem, temp_div);
    int rem_rem = rem - (int64_t)rem_quor * numerator[type];

    *dec = quor * denominator[type] + rem_quor;

    // 向零取整改为向下取整
    if (rem_rem < 0)
    {
        *dec -= 1;
    }

    return rem_rem;
}
