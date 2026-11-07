/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: database_init.h
 *
 * Code generated for Simulink model 'database_init'.
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

#ifndef RTW_HEADER_database_init_h_
#define RTW_HEADER_database_init_h_
#ifndef database_init_COMMON_INCLUDES_
#define database_init_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* database_init_COMMON_INCLUDES_ */

#include "servo_hub_database_type.h"

extern void database_init(const Axis *rtu_input, Axis *rty_output);

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
 * '<Root>' : 'database_init'
 * '<S1>'   : 'database_init/init'
 */

/*-
 * Requirements for '<Root>': database_init

 */
#endif                                 /* RTW_HEADER_database_init_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
