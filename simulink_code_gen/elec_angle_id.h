/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: elec_angle_id.h
 *
 * Code generated for Simulink model 'elec_angle_id'.
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

#ifndef RTW_HEADER_elec_angle_id_h_
#define RTW_HEADER_elec_angle_id_h_
#ifndef elec_angle_id_COMMON_INCLUDES_
#define elec_angle_id_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* elec_angle_id_COMMON_INCLUDES_ */

#include "servo_hub_database_type.h"

/* Block signals and states (default storage) for model 'elec_angle_id' */
typedef struct
{
    real32_T time_counts;              /* '<S1>/Data Store Memory' */
}
elec_angle_id_DW_f;

typedef struct
{
    elec_angle_id_DW_f rtdw;
}
elec_angle_id_MdlrefDW;

extern void elec_angle_id_Init(ElecAngleIdOutput *rty_output, elec_angle_id_DW_f
    *localDW);
extern void elec_angle_id(ElecAngleIdOutput *rty_output);

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
 * '<Root>' : 'elec_angle_id'
 * '<S1>'   : 'elec_angle_id/elec_angle_id'
 * '<S2>'   : 'elec_angle_id/elec_angle_id/Initialize Function'
 */

/*-
 * Requirements for '<Root>': elec_angle_id

 */
#endif                                 /* RTW_HEADER_elec_angle_id_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
