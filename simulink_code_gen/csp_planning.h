/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: csp_planning.h
 *
 * Code generated for Simulink model 'csp_planning'.
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

#ifndef RTW_HEADER_csp_planning_h_
#define RTW_HEADER_csp_planning_h_
#ifndef csp_planning_COMMON_INCLUDES_
#define csp_planning_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* csp_planning_COMMON_INCLUDES_ */

/* Block signals and states (default storage) for model 'csp_planning' */
typedef struct
{
    real32_T pp_coefs[12];
    real32_T Product[4];               /* '<S1>/Product' */
    real32_T x0_sum;                   /* '<S4>/Discrete-Time Integrator' */
    real32_T delta_0;
    real32_T delta_m1;
    real32_T delta_n;
}
csp_planning_DW_f;

typedef struct
{
    csp_planning_DW_f rtdw;
}
csp_planning_MdlrefDW;

extern void csp_planning_Init(csp_planning_DW_f *localDW);
extern void csp_planning(const int64_T rtu_pos_target_ip_buff[4], const real32_T
    *rtu_ip_dt, const real32_T *rtu_dt_p, int64_T *rty_pos_cmd, real32_T
    *rty_v_cmd, real32_T *rty_acc_cmd, csp_planning_DW_f *localDW);

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
 * '<Root>' : 'csp_planning'
 * '<S1>'   : 'csp_planning/Subsystem1'
 * '<S2>'   : 'csp_planning/Subsystem1/Initialize Function'
 * '<S3>'   : 'csp_planning/Subsystem1/MATLAB Function'
 * '<S4>'   : 'csp_planning/Subsystem1/x0'
 */

/*-
 * Requirements for '<Root>': csp_planning

 */
#endif                                 /* RTW_HEADER_csp_planning_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
