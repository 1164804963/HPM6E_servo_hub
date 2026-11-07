/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: math_lib.h
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

#ifndef RTW_HEADER_math_lib_h_
#define RTW_HEADER_math_lib_h_
#ifndef math_lib_COMMON_INCLUDES_
#define math_lib_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* math_lib_COMMON_INCLUDES_ */

extern void math_lib_first_order_lpf_iir(const real32_T *rtu_data_in, const
    real32_T *rtu_factor, const real32_T *rtu_data_out, real32_T
    *rty_data_filter);
extern void math_lib_median_filter(const real32_T rtu_u[3], real32_T *rty_Out1);
extern void math_lib_set_first_order_lpf_iir_config(const real32_T *rtu_fc,
    const real32_T *rtu_ts, real32_T *rty_factor);
extern void math_lib(const real32_T *rtu_data_in, const real32_T *rtu_factor,
                     const real32_T *rtu_data_out, const real32_T *rtu_fc, const
                     real32_T *rtu_ts, const real32_T rtu_data_src[3], real32_T *
                     rty_data_filter, real32_T *rty_factor_set, real32_T
                     *rty_data_filter1);

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'math_lib'
 * '<S1>'   : 'math_lib/first_order_lpf_iir'
 * '<S2>'   : 'math_lib/median_filter'
 * '<S3>'   : 'math_lib/set_first_order_lpf_iir_config'
 * '<S4>'   : 'math_lib/median_filter/MATLAB Function'
 */

/*-
 * Requirements for '<Root>': math_lib

 */
#endif                                 /* RTW_HEADER_math_lib_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
