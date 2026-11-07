/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: pos_speed_ctl_pip.h
 *
 * Code generated for Simulink model 'pos_speed_ctl_pip'.
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

#ifndef RTW_HEADER_pos_speed_ctl_pip_h_
#define RTW_HEADER_pos_speed_ctl_pip_h_
#ifndef pos_speed_ctl_pip_COMMON_INCLUDES_
#define pos_speed_ctl_pip_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* pos_speed_ctl_pip_COMMON_INCLUDES_ */

#include "servo_hub_database_type.h"

/* Block signals and states (default storage) for model 'pos_speed_ctl_pip' */
typedef struct
{
    int64_T pos_now_pulse_last;        /* '<S10>/Delay1' */
    real32_T iq_tar_last;              /* '<S11>/Delay1' */
    real32_T speed_ki_int;             /* '<S11>/Delay' */
    real32_T x_err_last;               /* '<S10>/Delay2' */
    real32_T x3;                       /* '<S13>/Delay3' */
    real32_T x2_ev_rad_s;              /* '<S12>/Delay3' */
    real32_T ev_last;                  /* '<S10>/Delay' */
}
pos_speed_ctl_pip_DW_f;

typedef struct
{
    pos_speed_ctl_pip_DW_f rtdw;
}
pos_speed_ctl_pip_MdlrefDW;

extern void pos_speed_ctl_pip_Init(pos_speed_ctl_pip_DW_f *localDW);
extern void pos_speed_ctl_pip(const PosSpeedCtlInput *rtu_input, const
    PosSpeedCtlConfig *rtu_config, PosSpeedCtlOutput *rty_output,
    pos_speed_ctl_pip_DW_f *localDW);

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S4>/Data Type Duplicate' : Unused code path elimination
 * Block '<S4>/Data Type Propagation' : Unused code path elimination
 * Block '<S5>/Data Type Duplicate' : Unused code path elimination
 * Block '<S5>/Data Type Propagation' : Unused code path elimination
 * Block '<S15>/Data Type Duplicate' : Unused code path elimination
 * Block '<S15>/Data Type Propagation' : Unused code path elimination
 * Block '<S16>/Data Type Duplicate' : Unused code path elimination
 * Block '<S16>/Data Type Propagation' : Unused code path elimination
 * Block '<S17>/Data Type Duplicate' : Unused code path elimination
 * Block '<S17>/Data Type Propagation' : Unused code path elimination
 * Block '<S18>/Data Type Duplicate' : Unused code path elimination
 * Block '<S18>/Data Type Propagation' : Unused code path elimination
 * Block '<S10>/l3' : Eliminated nontunable gain of 1
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
 * '<Root>' : 'pos_speed_ctl_pip'
 * '<S1>'   : 'pos_speed_ctl_pip/pos_speed_ctl_pip'
 * '<S2>'   : 'pos_speed_ctl_pip/pos_speed_ctl_pip/pos_speed_ctl'
 * '<S3>'   : 'pos_speed_ctl_pip/pos_speed_ctl_pip/pos_speed_ctl/Initialize Function'
 * '<S4>'   : 'pos_speed_ctl_pip/pos_speed_ctl_pip/pos_speed_ctl/Saturation Dynamic'
 * '<S5>'   : 'pos_speed_ctl_pip/pos_speed_ctl_pip/pos_speed_ctl/Saturation Dynamic1'
 * '<S6>'   : 'pos_speed_ctl_pip/pos_speed_ctl_pip/pos_speed_ctl/pulse_to_rad1'
 * '<S7>'   : 'pos_speed_ctl_pip/pos_speed_ctl_pip/pos_speed_ctl/pulse_to_rad2'
 * '<S8>'   : 'pos_speed_ctl_pip/pos_speed_ctl_pip/pos_speed_ctl/pulse_to_rad3'
 * '<S9>'   : 'pos_speed_ctl_pip/pos_speed_ctl_pip/pos_speed_ctl/pulse_to_rad4'
 * '<S10>'  : 'pos_speed_ctl_pip/pos_speed_ctl_pip/pos_speed_ctl/tl_dob'
 * '<S11>'  : 'pos_speed_ctl_pip/pos_speed_ctl_pip/pos_speed_ctl/vel_ctl_pi'
 * '<S12>'  : 'pos_speed_ctl_pip/pos_speed_ctl_pip/pos_speed_ctl/tl_dob/dis_int'
 * '<S13>'  : 'pos_speed_ctl_pip/pos_speed_ctl_pip/pos_speed_ctl/tl_dob/dis_int1'
 * '<S14>'  : 'pos_speed_ctl_pip/pos_speed_ctl_pip/pos_speed_ctl/tl_dob/p_to_rad'
 * '<S15>'  : 'pos_speed_ctl_pip/pos_speed_ctl_pip/pos_speed_ctl/tl_dob/dis_int/Saturation Dynamic'
 * '<S16>'  : 'pos_speed_ctl_pip/pos_speed_ctl_pip/pos_speed_ctl/tl_dob/dis_int1/Saturation Dynamic'
 * '<S17>'  : 'pos_speed_ctl_pip/pos_speed_ctl_pip/pos_speed_ctl/vel_ctl_pi/Saturation Dynamic'
 * '<S18>'  : 'pos_speed_ctl_pip/pos_speed_ctl_pip/pos_speed_ctl/vel_ctl_pi/Saturation Dynamic1'
 */

/*-
 * Requirements for '<Root>': pos_speed_ctl_pip

 */
#endif                                 /* RTW_HEADER_pos_speed_ctl_pip_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
