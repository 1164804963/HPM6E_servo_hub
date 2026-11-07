/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: reference_signal.c
 *
 * Code generated for Simulink model 'reference_signal'.
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

#include "reference_signal.h"
#include "servo_hub_database_type.h"
#include "yuanhub_math.h"
#include "rtwtypes.h"

/* System initialize for referenced model: 'reference_signal' */
void reference_signal_Init(reference_signal_DW_f *localDW)
{
    /* Outputs for Atomic SubSystem: '<Root>/Initialize Function' */
    /* StateWriter: '<S1>/State Writer' incorporates:
     *  Constant: '<S1>/Constant1'
     */
    /* '<S3>:1:6' times = single(0); */
    localDW->sin_time = 0.0F;

    /* End of Outputs for SubSystem: '<Root>/Initialize Function' */
}

/* Output and update for referenced model: 'reference_signal' */
void reference_signal(const ReferenceSignalConfig *rtu_config,
                      ReferenceSignalOutput *rty_output, reference_signal_DW_f
                      *localDW)
{
    real32_T rtb_n_ang;
    real32_T time_out;

    /* MATLAB Function: '<Root>/mod2pi_fun' incorporates:
     *  Delay: '<Root>/Delay'
     *  Gain: '<Root>/two_pi'
     *  Product: '<Root>/Product'
     *  Sum: '<Root>/Add'
     */
    /*  将角度限制在0到2π范围内 */
    /* MATLAB Function 'fast_math/mod2pi_fun': '<S2>:1' */
    /* '<S2>:1:3' TWO_PI = single(2*pi); */
    /* '<S2>:1:4' n_ang = single(ang); */
    /* '<S2>:1:5' while n_ang < 0 */
    for (rtb_n_ang = 6.28318548F * rtu_config->frq_Hz * rtu_config->dt_s +
            localDW->sin_time; rtb_n_ang < 0.0F; rtb_n_ang += 6.28318548F)
    {
        /* '<S2>:1:6' n_ang = n_ang + TWO_PI; */
    }

    /* '<S2>:1:8' while n_ang >= TWO_PI */
    while (rtb_n_ang >= 6.28318548F)
    {
        /* '<S2>:1:9' n_ang = n_ang - TWO_PI; */
        rtb_n_ang -= 6.28318548F;
    }

    /* End of MATLAB Function: '<Root>/mod2pi_fun' */

    /* MATLAB Function: '<Root>/pulse_gen' */
    /* MATLAB Function 'pulse_gen': '<S3>:1' */
    /* '<S3>:1:5' if isempty(times) */
    /* '<S3>:1:9' time_out = single(1.0)/frq; */
    time_out = 1.0F / rtu_config->frq_Hz;

    /* '<S3>:1:10' half_time_out = single(0.5) * time_out; */
    /* '<S3>:1:12' if times >= time_out */
    if (localDW->times >= time_out)
    {
        /* '<S3>:1:13' times = single(0); */
        localDW->times = 0.0F;
    }

    /* '<S3>:1:16' times = times + dt; */
    localDW->times += rtu_config->dt_s;

    /* '<S3>:1:19' if times > half_time_out */
    if (localDW->times > 0.5F * time_out)
    {
        /* '<S3>:1:20' y = single(1); */
        time_out = 1.0F;
    }
    else
    {
        /* '<S3>:1:21' else */
        /* '<S3>:1:22' y = single(0); */
        time_out = 0.0F;
    }

    /* End of MATLAB Function: '<Root>/pulse_gen' */

    /* Switch: '<Root>/Switch' incorporates:
     *  Product: '<Root>/Product1'
     *  Product: '<Root>/Product2'
     *  Trigonometry: '<Root>/Sin'
     */
    if (rtu_config->signal_type > 0)
    {
        time_out = rtu_config->amp * yuanhub_sin_f32(rtb_n_ang);
    }
    else
    {
        time_out *= rtu_config->amp;
    }

    /* BusCreator: '<Root>/Bus Creator' incorporates:
     *  Constant: '<Root>/Constant'
     *  Constant: '<Root>/Constant1'
     *  Constant: '<Root>/Constant2'
     *  Sum: '<Root>/Add1'
     *  Switch: '<Root>/Switch'
     */
    rty_output->signal_out = rtu_config->bias + time_out;
    rty_output->signal_pos = 0LL;
    rty_output->signal_vel = 0.0F;
    rty_output->signal_acc = 0.0F;

    /* Update for Delay: '<Root>/Delay' */
    localDW->sin_time = rtb_n_ang;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
