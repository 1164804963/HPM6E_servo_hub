/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: mit_ctl.h
 *
 * Code generated for Simulink model 'mit_ctl'.
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

#ifndef RTW_HEADER_mit_ctl_h_
#define RTW_HEADER_mit_ctl_h_
#ifndef mit_ctl_COMMON_INCLUDES_
#define mit_ctl_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* mit_ctl_COMMON_INCLUDES_ */

#include "servo_hub_database_type.h"

extern void mit_ctl(const MitCtlInput *rtu_input, const MitCtlConfig *rtu_config,
                    MitCtlOutput *rty_output);

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S2>/Data Type Duplicate' : Unused code path elimination
 * Block '<S2>/Data Type Propagation' : Unused code path elimination
 */

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
 * '<Root>' : 'mit_ctl'
 * '<S1>'   : 'mit_ctl/mit_ctl'
 * '<S2>'   : 'mit_ctl/mit_ctl/Saturation Dynamic'
 * '<S3>'   : 'mit_ctl/mit_ctl/pulse_to_rad1'
 * '<S4>'   : 'mit_ctl/mit_ctl/pulse_to_rad2'
 */

/*-
 * Requirements for '<Root>': mit_ctl

 */
#endif                                 /* RTW_HEADER_mit_ctl_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
