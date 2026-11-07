/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: direction_id.h
 *
 * Code generated for Simulink model 'direction_id'.
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

#ifndef RTW_HEADER_direction_id_h_
#define RTW_HEADER_direction_id_h_
#ifndef direction_id_COMMON_INCLUDES_
#define direction_id_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* direction_id_COMMON_INCLUDES_ */

#include "servo_hub_database_type.h"
#include "zero_crossing_types.h"

/* Block signals and states (default storage) for model 'direction_id' */
typedef struct
{
    int64_T UD_DSTATE;                 /* '<S6>/UD' */
    real32_T elec_angle_tar_last;      /* '<S1>/Delay' */
    real32_T UD_DSTATE_b;              /* '<S2>/UD' */
    int8_T direction;                  /* '<S4>/MATLAB Function' */
    int8_T state_now;                  /* '<S4>/MATLAB Function' */
    uint8_T step_num;                  /* '<S4>/Delay2' */
}
direction_id_DW_f;

/* Zero-crossing (trigger) state for model 'direction_id' */
typedef struct
{
    real_T Subsystem_Trig_ZC;          /* '<S1>/Subsystem' */
}
direction_id_ZCV_g;

/* Zero-crossing (trigger) state for model 'direction_id' */
typedef struct
{
    ZCSigState Subsystem_Trig_ZCE;     /* '<S1>/Subsystem' */
}
direction_id_ZCE;

typedef struct
{
    direction_id_DW_f rtdw;
    direction_id_ZCE rtzce;
}
direction_id_MdlrefDW;

/* Model reference registration function */
extern void direction_id_initialize(direction_id_ZCE *localZCE);
extern void direction_id_Init(direction_id_DW_f *localDW, direction_id_ZCE
    *localZCE);
extern void direction_id(const DirectionIdInput *rtu_input, const
    DirectionIdConfig *rtu_config, DirectionIdOutput *rty_Out1,
    direction_id_DW_f *localDW, direction_id_ZCE *localZCE);

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S4>/Data Type Duplicate' : Unused code path elimination
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
 * '<Root>' : 'direction_id'
 * '<S1>'   : 'direction_id/direction_id'
 * '<S2>'   : 'direction_id/direction_id/Difference'
 * '<S3>'   : 'direction_id/direction_id/Initialize Function'
 * '<S4>'   : 'direction_id/direction_id/Subsystem'
 * '<S5>'   : 'direction_id/direction_id/mod2pi_fun'
 * '<S6>'   : 'direction_id/direction_id/Subsystem/Difference'
 * '<S7>'   : 'direction_id/direction_id/Subsystem/MATLAB Function'
 */

/*-
 * Requirements for '<Root>': direction_id

 */
#endif                                 /* RTW_HEADER_direction_id_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
