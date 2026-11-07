/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: protect_check.h
 *
 * Code generated for Simulink model 'protect_check'.
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

#ifndef RTW_HEADER_protect_check_h_
#define RTW_HEADER_protect_check_h_
#ifndef protect_check_COMMON_INCLUDES_
#define protect_check_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* protect_check_COMMON_INCLUDES_ */

#include "servo_hub_database_type.h"

extern void protect_check(const real32_T rtu_iabc_now[3], const real32_T
    *rtu_dc_bus, const real32_T *rtu_driver_temp, const int32_T
    *rtu_pos_ctl_error, const real32_T *rtu_speed_now, const MotorCtlSmConfig
    *rtu_config, uint32_T *rty_error);

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
 * '<Root>' : 'protect_check'
 * '<S1>'   : 'protect_check/protect_check'
 * '<S2>'   : 'protect_check/protect_check/protect_check_fun'
 */

/*-
 * Requirements for '<Root>': protect_check

 */
#endif                                 /* RTW_HEADER_protect_check_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
