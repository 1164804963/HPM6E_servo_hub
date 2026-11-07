/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: tq_fc_id.c
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

#include "tq_fc_id.h"
#include "servo_hub_database_type.h"
#include <string.h>

/* System initialize for referenced model: 'tq_fc_id' */
void tq_fc_id_Init(TqFcIdOutput *rty_output, tq_fc_id_DW_f *localDW)
{
    /* SystemInitialize for BusCreator: '<S1>/Bus Creator' incorporates:
     *  Constant: '<S1>/Constant'
     */
    rty_output->pos_cmd_p = 0LL;
    rty_output->state_now = 0;

    /* Outputs for Atomic SubSystem: '<S1>/Initialize Function' */
    /* DataStoreWrite: '<S2>/Data Store Write' */
    memset(&localDW->com_table[0], 0, 360U * sizeof(real32_T));

    /* DataStoreWrite: '<S2>/Data Store Write4' incorporates:
     *  Constant: '<S2>/Constant5'
     */
    localDW->index_max = 360U;

    /* End of Outputs for SubSystem: '<S1>/Initialize Function' */
}

/* Output and update for referenced model: 'tq_fc_id' */
void tq_fc_id(TqFcIdOutput *rty_output)
{
    /* BusCreator: '<S1>/Bus Creator' incorporates:
     *  Constant: '<S1>/Constant'
     */
    rty_output->pos_cmd_p = 0LL;
    rty_output->state_now = 0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
