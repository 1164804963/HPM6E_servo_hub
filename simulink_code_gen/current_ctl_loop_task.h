/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: current_ctl_loop_task.h
 *
 * Code generated for Simulink model 'current_ctl_loop_task'.
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

#ifndef RTW_HEADER_current_ctl_loop_task_h_
#define RTW_HEADER_current_ctl_loop_task_h_
#ifndef current_ctl_loop_task_COMMON_INCLUDES_
#define current_ctl_loop_task_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                              /* current_ctl_loop_task_COMMON_INCLUDES_ */

#include "servo_hub_database_type.h"

/* Block signals and states (default storage) for model 'current_ctl_loop_task' */
typedef struct
{
    real32_T id_ki_int;                /* '<S20>/Delay' */
    real32_T iq_ki_int;                /* '<S21>/Delay' */
}
current_ctl_loop_task_DW_f;

typedef struct
{
    current_ctl_loop_task_DW_f rtdw;
}
current_ctl_loop_task_MdlrefDW;

extern void current_ctl_loop_task_deadband_comp_ua(real32_T rtu_u_tar, real32_T
    rtu_i_now, const real32_T *rtu_i_noise, const real32_T *rtu_comp_du,
    real32_T *rty_u_tar_comp);
extern void current_ctl_loop_task_Init(current_ctl_loop_task_DW_f *localDW);
extern void current_ctl_loop_task(const CurrentCtlInput *rtu_input, const
    CurrentCtlConfig *rtu_config, CurrentCtlOutput *rty_output,
    current_ctl_loop_task_DW_f *localDW);

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S11>/Data Type Duplicate' : Unused code path elimination
 * Block '<S12>/Data Type Duplicate' : Unused code path elimination
 * Block '<S13>/Data Type Duplicate' : Unused code path elimination
 * Block '<S13>/Data Type Duplicate1' : Unused code path elimination
 * Block '<S14>/Data Type Duplicate' : Unused code path elimination
 * Block '<S14>/Data Type Duplicate1' : Unused code path elimination
 * Block '<S18>/Data Type Duplicate' : Unused code path elimination
 * Block '<S18>/Data Type Propagation' : Unused code path elimination
 * Block '<S19>/Data Type Duplicate' : Unused code path elimination
 * Block '<S19>/Data Type Propagation' : Unused code path elimination
 * Block '<S23>/Data Type Duplicate' : Unused code path elimination
 * Block '<S23>/Data Type Propagation' : Unused code path elimination
 * Block '<S24>/Data Type Duplicate' : Unused code path elimination
 * Block '<S24>/Data Type Propagation' : Unused code path elimination
 * Block '<S16>/Offset' : Unused code path elimination
 * Block '<S16>/Unary_Minus' : Unused code path elimination
 * Block '<S17>/Offset' : Unused code path elimination
 * Block '<S17>/Unary_Minus' : Unused code path elimination
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
 * '<Root>' : 'current_ctl_loop_task'
 * '<S1>'   : 'current_ctl_loop_task/current_ctl_loop_task'
 * '<S2>'   : 'current_ctl_loop_task/current_ctl_loop_task/current_ctl_loop'
 * '<S3>'   : 'current_ctl_loop_task/current_ctl_loop_task/current_ctl_loop/Initialize Function'
 * '<S4>'   : 'current_ctl_loop_task/current_ctl_loop_task/current_ctl_loop/Subsystem'
 * '<S5>'   : 'current_ctl_loop_task/current_ctl_loop_task/current_ctl_loop/Subsystem1'
 * '<S6>'   : 'current_ctl_loop_task/current_ctl_loop_task/current_ctl_loop/current_ctl_pi'
 * '<S7>'   : 'current_ctl_loop_task/current_ctl_loop_task/current_ctl_loop/deadband_comp_ua'
 * '<S8>'   : 'current_ctl_loop_task/current_ctl_loop_task/current_ctl_loop/deadband_comp_ub'
 * '<S9>'   : 'current_ctl_loop_task/current_ctl_loop_task/current_ctl_loop/deadband_comp_uc'
 * '<S10>'  : 'current_ctl_loop_task/current_ctl_loop_task/current_ctl_loop/svpwm '
 * '<S11>'  : 'current_ctl_loop_task/current_ctl_loop_task/current_ctl_loop/current_ctl_pi/Clarke Transform'
 * '<S12>'  : 'current_ctl_loop_task/current_ctl_loop_task/current_ctl_loop/current_ctl_pi/Inverse Clarke Transform'
 * '<S13>'  : 'current_ctl_loop_task/current_ctl_loop_task/current_ctl_loop/current_ctl_pi/Inverse Park Transform'
 * '<S14>'  : 'current_ctl_loop_task/current_ctl_loop_task/current_ctl_loop/current_ctl_pi/Park Transform1'
 * '<S15>'  : 'current_ctl_loop_task/current_ctl_loop_task/current_ctl_loop/current_ctl_pi/current_ctl_pi'
 * '<S16>'  : 'current_ctl_loop_task/current_ctl_loop_task/current_ctl_loop/current_ctl_pi/Inverse Park Transform/Switch_Axis'
 * '<S17>'  : 'current_ctl_loop_task/current_ctl_loop_task/current_ctl_loop/current_ctl_pi/Park Transform1/Switch_Axis'
 * '<S18>'  : 'current_ctl_loop_task/current_ctl_loop_task/current_ctl_loop/current_ctl_pi/current_ctl_pi/Saturation Dynamic'
 * '<S19>'  : 'current_ctl_loop_task/current_ctl_loop_task/current_ctl_loop/current_ctl_pi/current_ctl_pi/Saturation Dynamic1'
 * '<S20>'  : 'current_ctl_loop_task/current_ctl_loop_task/current_ctl_loop/current_ctl_pi/current_ctl_pi/id_pi_ctl'
 * '<S21>'  : 'current_ctl_loop_task/current_ctl_loop_task/current_ctl_loop/current_ctl_pi/current_ctl_pi/iq_pi_ctl'
 * '<S22>'  : 'current_ctl_loop_task/current_ctl_loop_task/current_ctl_loop/current_ctl_pi/current_ctl_pi/udq_max_lim'
 * '<S23>'  : 'current_ctl_loop_task/current_ctl_loop_task/current_ctl_loop/current_ctl_pi/current_ctl_pi/id_pi_ctl/Saturation Dynamic'
 * '<S24>'  : 'current_ctl_loop_task/current_ctl_loop_task/current_ctl_loop/current_ctl_pi/current_ctl_pi/iq_pi_ctl/Saturation Dynamic'
 * '<S25>'  : 'current_ctl_loop_task/current_ctl_loop_task/current_ctl_loop/deadband_comp_ua/deadband_comp'
 * '<S26>'  : 'current_ctl_loop_task/current_ctl_loop_task/current_ctl_loop/deadband_comp_ub/deadband_comp'
 * '<S27>'  : 'current_ctl_loop_task/current_ctl_loop_task/current_ctl_loop/deadband_comp_uc/deadband_comp'
 */

/*-
 * Requirements for '<Root>': current_ctl_loop_task

 */
#endif                                 /* RTW_HEADER_current_ctl_loop_task_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
