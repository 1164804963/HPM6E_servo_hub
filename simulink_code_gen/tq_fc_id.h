/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: tq_fc_id.h
 *
 * Code generated for Simulink model 'tq_fc_id'.
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

#ifndef RTW_HEADER_tq_fc_id_h_
#define RTW_HEADER_tq_fc_id_h_
#ifndef tq_fc_id_COMMON_INCLUDES_
#define tq_fc_id_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* tq_fc_id_COMMON_INCLUDES_ */

#include "servo_hub_database_type.h"

/* Block signals and states (default storage) for model 'tq_fc_id' */
typedef struct
{
    real32_T com_table[360];           /* '<S1>/Data Store Memory' */
    uint32_T index_max;                /* '<S1>/Data Store Memory4' */
}
tq_fc_id_DW_f;

typedef struct
{
    tq_fc_id_DW_f rtdw;
}
tq_fc_id_MdlrefDW;

extern void tq_fc_id_Init(TqFcIdOutput *rty_output, tq_fc_id_DW_f *localDW);
extern void tq_fc_id(TqFcIdOutput *rty_output);

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
 * '<Root>' : 'tq_fc_id'
 * '<S1>'   : 'tq_fc_id/tq_fc_id'
 * '<S2>'   : 'tq_fc_id/tq_fc_id/Initialize Function'
 */

/*-
 * Requirements for '<Root>': tq_fc_id

 */
#endif                                 /* RTW_HEADER_tq_fc_id_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
