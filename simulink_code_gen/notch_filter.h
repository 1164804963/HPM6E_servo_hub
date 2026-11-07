/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: notch_filter.h
 *
 * Code generated for Simulink model 'notch_filter'.
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

#ifndef RTW_HEADER_notch_filter_h_
#define RTW_HEADER_notch_filter_h_
#ifndef notch_filter_COMMON_INCLUDES_
#define notch_filter_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* notch_filter_COMMON_INCLUDES_ */

#include "servo_hub_database_type.h"

/* Block signals and states (default storage) for model 'notch_filter' */
typedef struct
{
    real32_T y_last;                   /* '<S7>/Delay3' */
    real32_T y_last_c;                 /* '<S7>/Delay2' */
    real32_T u_last;                   /* '<S7>/Delay1' */
    real32_T u_last_i;                 /* '<S7>/Delay' */
    real32_T y_last_f;                 /* '<S6>/Delay3' */
    real32_T y_last_ct;                /* '<S6>/Delay2' */
    real32_T u_last_b;                 /* '<S6>/Delay1' */
    real32_T u_last_bt;                /* '<S6>/Delay' */
    real32_T y_last_e;                 /* '<S5>/Delay3' */
    real32_T y_last_i;                 /* '<S5>/Delay2' */
    real32_T u_last_bm;                /* '<S5>/Delay1' */
    real32_T u_last_f;                 /* '<S5>/Delay' */
    real32_T y_last_fj;                /* '<S4>/Delay3' */
    real32_T y_last_a;                 /* '<S4>/Delay2' */
    real32_T u_last_o;                 /* '<S4>/Delay1' */
    real32_T u_last_m;                 /* '<S4>/Delay' */
    real32_T y_last_o;                 /* '<S3>/Delay3' */
    real32_T y_last_cg;                /* '<S3>/Delay2' */
    real32_T u_last_p;                 /* '<S3>/Delay1' */
    real32_T u_last_p2;                /* '<S3>/Delay' */
    real32_T y_last_ov;                /* '<S2>/Delay3' */
    real32_T y_last_p;                 /* '<S2>/Delay2' */
    real32_T u_last_l;                 /* '<S2>/Delay1' */
    real32_T u_last_ix;                /* '<S2>/Delay' */
}
notch_filter_DW_f;

typedef struct
{
    notch_filter_DW_f rtdw;
}
notch_filter_MdlrefDW;

extern void notch_filter_Init(notch_filter_DW_f *localDW);
extern void notch_filter(const NotchFilterInput *rtu_input, const
    NotchFilterInternal *rtu_internal, NotchFilterOutput *rty_output,
    notch_filter_DW_f *localDW);

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
 * '<Root>' : 'notch_filter'
 * '<S1>'   : 'notch_filter/Initialize Function'
 * '<S2>'   : 'notch_filter/notch_filter1'
 * '<S3>'   : 'notch_filter/notch_filter2'
 * '<S4>'   : 'notch_filter/notch_filter3'
 * '<S5>'   : 'notch_filter/notch_filter4'
 * '<S6>'   : 'notch_filter/notch_filter5'
 * '<S7>'   : 'notch_filter/notch_filter6'
 */

/*-
 * Requirements for '<Root>': notch_filter

 */
#endif                                 /* RTW_HEADER_notch_filter_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
