/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: linear_trajectory_planning.h
 *
 * Code generated for Simulink model 'linear_trajectory_planning'.
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

#ifndef RTW_HEADER_linear_trajectory_planning_h_
#define RTW_HEADER_linear_trajectory_planning_h_
#ifndef linear_trajectory_planning_COMMON_INCLUDES_
#define linear_trajectory_planning_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                         /* linear_trajectory_planning_COMMON_INCLUDES_ */

/* Block signals and states (default storage) for model 'linear_trajectory_planning' */
typedef struct
{
    real32_T traj_now;                 /* '<Root>/Data Store Memory' */
}
linear_trajectory_planning_DW_f;

typedef struct
{
    linear_trajectory_planning_DW_f rtdw;
}
linear_trajectory_planning_MdlrefDW;

extern void linear_trajectory_planning(const real32_T *rtu_traj_cmd, const
    real32_T *rtu_slope, const real32_T *rtu_dt_s, real32_T *rty_traj_out,
    int8_T *rty_state_now, linear_trajectory_planning_DW_f *localDW);

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
 * '<Root>' : 'linear_trajectory_planning'
 * '<S1>'   : 'linear_trajectory_planning/linear_trajectory_planning'
 */

/*-
 * Requirements for '<Root>': linear_trajectory_planning

 */
#endif                            /* RTW_HEADER_linear_trajectory_planning_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
