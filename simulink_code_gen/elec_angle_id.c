/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: elec_angle_id.c
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

#include "elec_angle_id.h"
#include "servo_hub_database_type.h"

/* System initialize for referenced model: 'elec_angle_id' */
void elec_angle_id_Init(ElecAngleIdOutput *rty_output, elec_angle_id_DW_f
                        *localDW)
{
    /* SystemInitialize for BusCreator: '<S1>/Bus Creator' incorporates:
     *  Constant: '<S1>/Constant'
     *  Constant: '<S1>/Constant1'
     *  Constant: '<S1>/Constant2'
     *  Constant: '<S1>/Constant3'
     *  Constant: '<S1>/Constant4'
     *  Constant: '<S1>/Constant5'
     *  SignalConversion generated from: '<S1>/Bus Creator'
     */
    rty_output->id_tar_A = 0.0F;
    rty_output->elec_bias_rad = 0.0F;
    rty_output->state_now = 0;
    rty_output->elec_bias_buff_rad[0] = 0.0F;
    rty_output->elec_bias_buff_rad[1] = 0.0F;
    rty_output->step_num = 0U;

    /* Outputs for Atomic SubSystem: '<S1>/Initialize Function' */
    /* DataStoreWrite: '<S2>/Data Store Write' incorporates:
     *  Constant: '<S2>/Constant'
     */
    localDW->time_counts = 0.0F;

    /* End of Outputs for SubSystem: '<S1>/Initialize Function' */
}

/* Output and update for referenced model: 'elec_angle_id' */
void elec_angle_id(ElecAngleIdOutput *rty_output)
{
    /* BusCreator: '<S1>/Bus Creator' incorporates:
     *  Constant: '<S1>/Constant'
     *  Constant: '<S1>/Constant1'
     *  Constant: '<S1>/Constant2'
     *  Constant: '<S1>/Constant3'
     *  Constant: '<S1>/Constant4'
     *  Constant: '<S1>/Constant5'
     *  SignalConversion generated from: '<S1>/Bus Creator'
     */
    rty_output->id_tar_A = 0.0F;
    rty_output->elec_bias_rad = 0.0F;
    rty_output->state_now = 0;
    rty_output->elec_bias_buff_rad[0] = 0.0F;
    rty_output->elec_bias_buff_rad[1] = 0.0F;
    rty_output->step_num = 0U;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
