/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: pos_trajectory_planning.h
 *
 * Code generated for Simulink model 'pos_trajectory_planning'.
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

#ifndef RTW_HEADER_pos_trajectory_planning_h_
#define RTW_HEADER_pos_trajectory_planning_h_
#ifndef pos_trajectory_planning_COMMON_INCLUDES_
#define pos_trajectory_planning_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                            /* pos_trajectory_planning_COMMON_INCLUDES_ */

/* Block signals and states (default storage) for model 'pos_trajectory_planning' */
typedef struct
{
    int64_T q0_int;                    /* '<S1>/tv_tra_gen' */
    int64_T x;
    real32_T q0_dec;                   /* '<S1>/tv_tra_gen' */
    real32_T dq0;                      /* '<S1>/tv_tra_gen' */
}
pos_trajectory_planning_DW_f;

typedef struct
{
    pos_trajectory_planning_DW_f rtdw;
}
pos_trajectory_planning_MdlrefDW;

extern void pos_trajectory_planning_Init(void);
extern void pos_trajectory_planning(const int64_T *rtu_pos_tar_p, const real32_T
    *rtu_vmax_p_s, const real32_T *rtu_acc_p_ss, const real32_T *rtu_dec_p_ss,
    const real32_T *rtu_tp_s, int64_T *rty_pos_out_int_p, real32_T
    *rty_pos_out_dec_p, real32_T *rty_v_out_p_s, real32_T *rty_acc_out_p_ss,
    int8_T *rty_state_now, pos_trajectory_planning_DW_f *localDW);

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
 * '<Root>' : 'pos_trajectory_planning'
 * '<S1>'   : 'pos_trajectory_planning/pos_trajectory_planning'
 * '<S2>'   : 'pos_trajectory_planning/pos_trajectory_planning/tv_tra_gen'
 */

/*-
 * Requirements for '<Root>': pos_trajectory_planning

 */
#endif                               /* RTW_HEADER_pos_trajectory_planning_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
