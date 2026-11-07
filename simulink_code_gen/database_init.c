/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: database_init.c
 *
 * Code generated for Simulink model 'database_init'.
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

#include "database_init.h"
#include "servo_hub_database_type.h"

/* Output and update for referenced model: 'database_init' */
void database_init(const Axis *rtu_input, Axis *rty_output)
{
    /* BusAssignment: '<S1>/Bus Assignment' incorporates:
     *  Constant: '<S1>/Constant'
     */
    *rty_output = *rtu_input;
    rty_output->current_ctl_config.dt_s = 5.0E-5F;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
