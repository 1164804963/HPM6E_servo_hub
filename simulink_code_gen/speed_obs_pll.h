/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: speed_obs_pll.h
 *
 * Code generated for Simulink model 'speed_obs_pll'.
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

#ifndef RTW_HEADER_speed_obs_pll_h_
#define RTW_HEADER_speed_obs_pll_h_
#ifndef speed_obs_pll_COMMON_INCLUDES_
#define speed_obs_pll_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* speed_obs_pll_COMMON_INCLUDES_ */

#include "servo_hub_database_type.h"

/* Block signals and states (default storage) for model 'speed_obs_pll' */
typedef struct
{
    int64_T pos_now_p_last;            /* '<S1>/Delay1' */
    real32_T pos_err_last;             /* '<S1>/Delay2' */
    real32_T ev_rad_s_last;            /* '<S1>/Delay' */
}
speed_obs_pll_DW_f;

typedef struct
{
    speed_obs_pll_DW_f rtdw;
}
speed_obs_pll_MdlrefDW;

extern void speed_obs_pll_Init(speed_obs_pll_DW_f *localDW);
extern void speed_obs_pll(const SpeedObsPllInput *rtu_input, const
    SpeedObsPllConfig *rtu_config, SpeedObsPllOutput *rty_output,
    speed_obs_pll_DW_f *localDW);

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S3>/Data Type Duplicate' : Unused code path elimination
 * Block '<S3>/Data Type Propagation' : Unused code path elimination
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
 * '<Root>' : 'speed_obs_pll'
 * '<S1>'   : 'speed_obs_pll/speed_obs_pll'
 * '<S2>'   : 'speed_obs_pll/speed_obs_pll/Initialize Function'
 * '<S3>'   : 'speed_obs_pll/speed_obs_pll/Saturation Dynamic'
 * '<S4>'   : 'speed_obs_pll/speed_obs_pll/p_to_rad'
 */

/*-
 * Requirements for '<Root>': speed_obs_pll

 */
#endif                                 /* RTW_HEADER_speed_obs_pll_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
