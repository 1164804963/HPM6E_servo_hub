/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: math_lib.c
 *
 * Code generated for Simulink model 'math_lib'.
 *
 * Simulink Coder version         : 9.9 (R2023a) 19-Nov-2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Not run
 */

#include "math_lib.h"
#include "rtwtypes.h"

/* Output and update for atomic system: '<Root>/first_order_lpf_iir' */
void math_lib_first_order_lpf_iir(const real32_T *rtu_data_in, const real32_T
    *rtu_factor, const real32_T *rtu_data_out, real32_T *rty_data_filter)
{
    real32_T rtb_Add1;
    real32_T rtb_Product;

    /* Product: '<S1>/Product' */
    rtb_Product = *rtu_data_in * *rtu_factor;

    /* Sum: '<S1>/Add1' incorporates:
     *  Constant: '<S1>/Constant'
     */
    rtb_Add1 = 1.0F - *rtu_factor;

    /* Product: '<S1>/Product1' */
    rtb_Add1 *= *rtu_data_out;

    /* Sum: '<S1>/Add' */
    *rty_data_filter = rtb_Product + rtb_Add1;
}

/* Output and update for atomic system: '<Root>/median_filter' */
void math_lib_median_filter(const real32_T rtu_u[3], real32_T *rty_Out1)
{
    int32_T tmp;

    /* MATLAB Function: '<S2>/MATLAB Function' */
    /* MATLAB Function 'median_filter/MATLAB Function': '<S4>:1' */
    /* '<S4>:1:3' y = median(x); */
    if (rtu_u[0] < rtu_u[1])
    {
        if (rtu_u[1] < rtu_u[2])
        {
            tmp = 1;
        }
        else if (rtu_u[0] < rtu_u[2])
        {
            tmp = 2;
        }
        else
        {
            tmp = 0;
        }
    }
    else if (rtu_u[0] < rtu_u[2])
    {
        tmp = 0;
    }
    else if (rtu_u[1] < rtu_u[2])
    {
        tmp = 2;
    }
    else
    {
        tmp = 1;
    }

    *rty_Out1 = rtu_u[tmp];

    /* End of MATLAB Function: '<S2>/MATLAB Function' */
}

/* Output and update for atomic system: '<Root>/set_first_order_lpf_iir_config' */
void math_lib_set_first_order_lpf_iir_config(const real32_T *rtu_fc, const
    real32_T *rtu_ts, real32_T *rty_factor)
{
    real32_T rtb_Gain;

    /* Gain: '<S3>/Gain' */
    rtb_Gain = 6.28318548F * *rtu_fc;

    /* Sum: '<S3>/Add' incorporates:
     *  Constant: '<S3>/Constant'
     *  Product: '<S3>/Divide'
     */
    rtb_Gain = 1.0F / rtb_Gain + *rtu_ts;

    /* Product: '<S3>/Divide1' */
    *rty_factor = *rtu_ts / rtb_Gain;
}

/* Output and update for referenced model: 'math_lib' */
void math_lib(const real32_T *rtu_data_in, const real32_T *rtu_factor, const
              real32_T *rtu_data_out, const real32_T *rtu_fc, const real32_T
              *rtu_ts, const real32_T rtu_data_src[3], real32_T *rty_data_filter,
              real32_T *rty_factor_set, real32_T *rty_data_filter1)
{
    /* Outputs for Atomic SubSystem: '<Root>/first_order_lpf_iir' */
    math_lib_first_order_lpf_iir(rtu_data_in, rtu_factor, rtu_data_out,
        rty_data_filter);

    /* End of Outputs for SubSystem: '<Root>/first_order_lpf_iir' */

    /* Outputs for Atomic SubSystem: '<Root>/set_first_order_lpf_iir_config' */
    math_lib_set_first_order_lpf_iir_config(rtu_fc, rtu_ts, rty_factor_set);

    /* End of Outputs for SubSystem: '<Root>/set_first_order_lpf_iir_config' */

    /* Outputs for Atomic SubSystem: '<Root>/median_filter' */
    math_lib_median_filter(rtu_data_src, rty_data_filter1);

    /* End of Outputs for SubSystem: '<Root>/median_filter' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
