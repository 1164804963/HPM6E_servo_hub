/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: input_shaping_ei.h
 *
 * Code generated for Simulink model 'input_shaping_ei'.
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

#ifndef RTW_HEADER_input_shaping_ei_h_
#define RTW_HEADER_input_shaping_ei_h_
#ifndef input_shaping_ei_COMMON_INCLUDES_
#define input_shaping_ei_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* input_shaping_ei_COMMON_INCLUDES_ */

#include "servo_hub_database_type.h"

/* Block signals and states (default storage) for model 'input_shaping_ei' */
typedef struct
{
    int64_T t2_delay_buffer[500];      /* '<S1>/Delay' */
    int64_T t3_delay_buffer[500];      /* '<S1>/Delay1' */
    uint32_T CircBufIdx;               /* '<S1>/Delay' */
    uint32_T CircBufIdx_e;             /* '<S1>/Delay1' */
    boolean_T icLoad;                  /* '<S1>/Delay' */
    boolean_T icLoad_o;                /* '<S1>/Delay1' */
}
input_shaping_ei_DW_f;

typedef struct
{
    input_shaping_ei_DW_f rtdw;
}
input_shaping_ei_MdlrefDW;

extern void input_shaping_ei_Init(input_shaping_ei_DW_f *localDW);
extern void input_shaping_ei(const InputShapingInput *rtu_input, const
    InputShapingConfig *rtu_config, InputShapingOutput *rty_output,
    input_shaping_ei_DW_f *localDW);

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
 * '<Root>' : 'input_shaping_ei'
 * '<S1>'   : 'input_shaping_ei/input_shaping_ei'
 */

/*-
 * Requirements for '<Root>': input_shaping_ei

 */
#endif                                 /* RTW_HEADER_input_shaping_ei_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
