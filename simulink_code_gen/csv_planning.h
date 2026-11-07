/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: csv_planning.h
 *
 * Code generated for Simulink model 'csv_planning'.
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

#ifndef RTW_HEADER_csv_planning_h_
#define RTW_HEADER_csv_planning_h_
#ifndef csv_planning_COMMON_INCLUDES_
#define csv_planning_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* csv_planning_COMMON_INCLUDES_ */

/* Block signals and states (default storage) for model 'csv_planning' */
typedef struct
{
    real32_T pp_coefs[12];
    real32_T Product[4];               /* '<S1>/Product' */
    real32_T x0_sum;                   /* '<S4>/Discrete-Time Integrator' */
    real32_T delta_0;
    real32_T delta_m1;
    real32_T delta_n;
}
csv_planning_DW_f;

typedef struct
{
    csv_planning_DW_f rtdw;
}
csv_planning_MdlrefDW;

extern void csv_planning_Init(csv_planning_DW_f *localDW);
extern void csv_planning(const real32_T rtu_v_target_ip_buff[4], const real32_T *
    rtu_ip_dt, const real32_T *rtu_dt_p, real32_T *rty_v_cmd, real32_T
    *rty_acc_cmd, csv_planning_DW_f *localDW);

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
 * '<Root>' : 'csv_planning'
 * '<S1>'   : 'csv_planning/Subsystem'
 * '<S2>'   : 'csv_planning/Subsystem/Initialize Function'
 * '<S3>'   : 'csv_planning/Subsystem/MATLAB Function'
 * '<S4>'   : 'csv_planning/Subsystem/x0'
 */

/*-
 * Requirements for '<Root>': csv_planning

 */
#endif                                 /* RTW_HEADER_csv_planning_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
