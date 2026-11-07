/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: pole_pairs_id.h
 *
 * Code generated for Simulink model 'pole_pairs_id'.
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

#ifndef RTW_HEADER_pole_pairs_id_h_
#define RTW_HEADER_pole_pairs_id_h_
#ifndef pole_pairs_id_COMMON_INCLUDES_
#define pole_pairs_id_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* pole_pairs_id_COMMON_INCLUDES_ */

#include "servo_hub_database_type.h"
#include "zero_crossing_types.h"

/* Block signals and states (default storage) for model 'pole_pairs_id' */
typedef struct
{
    int64_T UD_DSTATE;                 /* '<S7>/UD' */
    real32_T elec_angle_tar_last;      /* '<S1>/Delay' */
    real32_T UD_DSTATE_j;              /* '<S2>/UD' */
    uint32_T pn;                       /* '<S5>/MATLAB Function' */
    uint32_T step_num;                 /* '<S6>/Delay2' */
    uint32_T pn_sum;                   /* '<S6>/Delay' */
}
pole_pairs_id_DW_f;

/* Zero-crossing (trigger) state for model 'pole_pairs_id' */
typedef struct
{
    real_T state_update_Trig_ZC;       /* '<S1>/state_update' */
    real_T pn_clc_Trig_ZC;             /* '<S1>/pn_clc' */
}
pole_pairs_id_ZCV_g;

/* Zero-crossing (trigger) state for model 'pole_pairs_id' */
typedef struct
{
    ZCSigState state_update_Trig_ZCE;  /* '<S1>/state_update' */
    ZCSigState pn_clc_Trig_ZCE;        /* '<S1>/pn_clc' */
}
pole_pairs_id_ZCE;

typedef struct
{
    pole_pairs_id_DW_f rtdw;
    pole_pairs_id_ZCE rtzce;
}
pole_pairs_id_MdlrefDW;

/* Model reference registration function */
extern void pole_pairs_id_initialize(pole_pairs_id_ZCE *localZCE);
extern void pole_pairs_id_Init(pole_pairs_id_DW_f *localDW, pole_pairs_id_ZCE
    *localZCE);
extern void pole_pairs_id(const PolePairsIdInput *rtu_input, const
    PolePairsIdConfig *rtu_config, PolePairsIdOutput *rty_output,
    pole_pairs_id_DW_f *localDW, pole_pairs_id_ZCE *localZCE);

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S5>/Scope' : Unused code path elimination
 * Block '<S6>/Data Type Conversion3' : Eliminate redundant data type conversion
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
 * '<Root>' : 'pole_pairs_id'
 * '<S1>'   : 'pole_pairs_id/pole_pairs_id'
 * '<S2>'   : 'pole_pairs_id/pole_pairs_id/Difference'
 * '<S3>'   : 'pole_pairs_id/pole_pairs_id/Initialize Function'
 * '<S4>'   : 'pole_pairs_id/pole_pairs_id/mod2pi_fun1'
 * '<S5>'   : 'pole_pairs_id/pole_pairs_id/pn_clc'
 * '<S6>'   : 'pole_pairs_id/pole_pairs_id/state_update'
 * '<S7>'   : 'pole_pairs_id/pole_pairs_id/pn_clc/Difference'
 * '<S8>'   : 'pole_pairs_id/pole_pairs_id/pn_clc/MATLAB Function'
 */

/*-
 * Requirements for '<Root>': pole_pairs_id

 */
#endif                                 /* RTW_HEADER_pole_pairs_id_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
