/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: reference_signal.h
 *
 * Code generated for Simulink model 'reference_signal'.
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

#ifndef RTW_HEADER_reference_signal_h_
#define RTW_HEADER_reference_signal_h_
#ifndef reference_signal_COMMON_INCLUDES_
#define reference_signal_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* reference_signal_COMMON_INCLUDES_ */

#include "servo_hub_database_type.h"

/* Block signals and states (default storage) for model 'reference_signal' */
typedef struct
{
    real32_T sin_time;                 /* '<Root>/Delay' */
    real32_T times;                    /* '<Root>/pulse_gen' */
}
reference_signal_DW_f;

typedef struct
{
    reference_signal_DW_f rtdw;
}
reference_signal_MdlrefDW;

extern void reference_signal_Init(reference_signal_DW_f *localDW);
extern void reference_signal(const ReferenceSignalConfig *rtu_config,
    ReferenceSignalOutput *rty_output, reference_signal_DW_f *localDW);

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
 * '<Root>' : 'reference_signal'
 * '<S1>'   : 'reference_signal/Initialize Function'
 * '<S2>'   : 'reference_signal/mod2pi_fun'
 * '<S3>'   : 'reference_signal/pulse_gen'
 */

/*-
 * Requirements for '<Root>': reference_signal

 */
#endif                                 /* RTW_HEADER_reference_signal_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
