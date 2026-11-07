/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: reciprocal_motion.h
 *
 * Code generated for Simulink model 'reciprocal_motion'.
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

#ifndef RTW_HEADER_reciprocal_motion_h_
#define RTW_HEADER_reciprocal_motion_h_
#ifndef reciprocal_motion_COMMON_INCLUDES_
#define reciprocal_motion_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* reciprocal_motion_COMMON_INCLUDES_ */

#include "servo_hub_database_type.h"

/* Block signals and states (default storage) for model 'reciprocal_motion' */
typedef struct
{
    int64_T pos_last;                  /* '<Root>/Delay' */
    int64_T q0_int;                    /* '<S1>/tv_tra_gen' */
    int64_T x;
    real32_T times;                    /* '<Root>/reciprocal_motion' */
    real32_T q0_dec;                   /* '<S1>/tv_tra_gen' */
    real32_T dq0;                      /* '<S1>/tv_tra_gen' */
    boolean_T pos_id;                  /* '<Root>/reciprocal_motion' */
}
reciprocal_motion_DW_f;

typedef struct
{
    reciprocal_motion_DW_f rtdw;
}
reciprocal_motion_MdlrefDW;

extern void reciprocal_motion_Init(void);
extern void reciprocal_motion(const ReciprocalMotionConfig *rtu_config,
    ReciprocalMotionOutput *rty_output, reciprocal_motion_DW_f *localDW);

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
 * '<Root>' : 'reciprocal_motion'
 * '<S1>'   : 'reciprocal_motion/pos_trajectory_planning'
 * '<S2>'   : 'reciprocal_motion/reciprocal_motion'
 * '<S3>'   : 'reciprocal_motion/pos_trajectory_planning/tv_tra_gen'
 */

/*-
 * Requirements for '<Root>': reciprocal_motion

 */
#endif                                 /* RTW_HEADER_reciprocal_motion_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
