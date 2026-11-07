/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: load_pos_sensor.h
 *
 * Code generated for Simulink model 'load_pos_sensor'.
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

#ifndef RTW_HEADER_load_pos_sensor_h_
#define RTW_HEADER_load_pos_sensor_h_
#ifndef load_pos_sensor_COMMON_INCLUDES_
#define load_pos_sensor_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* load_pos_sensor_COMMON_INCLUDES_ */

#include "servo_hub_database_type.h"

/* Block signals and states (default storage) for model 'load_pos_sensor' */
typedef struct
{
    int64_T circle_int_n_;             /* '<S1>/MATLAB Function' */
    uint32_T enc_counts_now_last;      /* '<S1>/enc_counts_now_last' */
}
load_pos_sensor_DW_f;

typedef struct
{
    load_pos_sensor_DW_f rtdw;
}
load_pos_sensor_MdlrefDW;

extern void load_pos_sensor_Init(void);
extern void load_pos_sensor(const LoadPosSensorInput *rtu_input, const
    LoadPosSensorConfig *rtu_config, LoadPosSensorOutput *rty_output,
    load_pos_sensor_DW_f *localDW);

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
 * '<Root>' : 'load_pos_sensor'
 * '<S1>'   : 'load_pos_sensor/load_pos_sensor'
 * '<S2>'   : 'load_pos_sensor/load_pos_sensor/If Action Subsystem'
 * '<S3>'   : 'load_pos_sensor/load_pos_sensor/If Action Subsystem1'
 * '<S4>'   : 'load_pos_sensor/load_pos_sensor/MATLAB Function'
 */

/*-
 * Requirements for '<Root>': load_pos_sensor

 */
#endif                                 /* RTW_HEADER_load_pos_sensor_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
