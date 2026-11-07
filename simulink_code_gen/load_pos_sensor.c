/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: load_pos_sensor.c
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

#include "load_pos_sensor.h"
#include "servo_hub_database_type.h"
#include "rtwtypes.h"

/* System initialize for referenced model: 'load_pos_sensor' */
void load_pos_sensor_Init(void)
{
    /* '<S4>:1:6' circle_int_n_ = int64(0); */
}

/* Output and update for referenced model: 'load_pos_sensor' */
void load_pos_sensor(const LoadPosSensorInput *rtu_input, const
                     LoadPosSensorConfig *rtu_config, LoadPosSensorOutput
                     *rty_output, load_pos_sensor_DW_f *localDW)
{
    int64_T tmp;
    uint32_T enc_line_half;
    uint32_T qY;
    uint32_T rtb_Merge;

    /* If: '<S1>/If' */
    if (rtu_config->dir > 0)
    {
        /* Outputs for IfAction SubSystem: '<S1>/If Action Subsystem' incorporates:
         *  ActionPort: '<S2>/Action Port'
         */
        /* SignalConversion generated from: '<S2>/In1' incorporates:
         *  SignalConversion generated from: '<S1>/Bus Selector'
         */
        rtb_Merge = rtu_input->enc_counts_now_p;

        /* End of Outputs for SubSystem: '<S1>/If Action Subsystem' */
    }
    else
    {
        /* Outputs for IfAction SubSystem: '<S1>/If Action Subsystem1' incorporates:
         *  ActionPort: '<S3>/Action Port'
         */
        /* Sum: '<S3>/Add' incorporates:
         *  Constant: '<S3>/Constant'
         *  SignalConversion generated from: '<S1>/Bus Selector'
         */
        rtb_Merge = (rtu_config->enc_line_p_n - rtu_input->enc_counts_now_p) -
            1U;

        /* End of Outputs for SubSystem: '<S1>/If Action Subsystem1' */
    }

    /* End of If: '<S1>/If' */

    /* MATLAB Function: '<S1>/MATLAB Function' incorporates:
     *  Delay: '<S1>/enc_counts_now_last'
     */
    /* MATLAB Function 'load_pos_sensor/MATLAB Function': '<S4>:1' */
    /* '<S4>:1:5' if  isempty(circle_int_n_) */
    /* '<S4>:1:8' sum_pos = int64(0); */
    /* '<S4>:1:9' enc_line_half = enc_line / uint32(2); */
    enc_line_half = rtu_config->enc_line_p_n >> 1;
    if (rtu_config->enc_line_p_n - (enc_line_half << 1) > 0U)
    {
        enc_line_half++;
    }

    /* '<S4>:1:11' if pos_now > pos_now_last */
    qY = rtb_Merge - /*MW:OvSatOk*/ localDW->enc_counts_now_last;
    if (qY > rtb_Merge)
    {
        qY = 0U;
    }

    if ((rtb_Merge > localDW->enc_counts_now_last) && (qY > enc_line_half))
    {
        /* '<S4>:1:12' if (pos_now - pos_now_last) > enc_line_half */
        /* 向下溢出 */
        /* '<S4>:1:13' circle_int_n_ = circle_int_n_ - int64(enc_line); */
        if (localDW->circle_int_n_ < rtu_config->enc_line_p_n + MIN_int64_T)
        {
            localDW->circle_int_n_ = MIN_int64_T;
        }
        else
        {
            localDW->circle_int_n_ -= rtu_config->enc_line_p_n;
        }

        /* 累计圈数 -1 */
    }

    /* '<S4>:1:17' if pos_now < pos_now_last */
    qY = localDW->enc_counts_now_last - /*MW:OvSatOk*/ rtb_Merge;
    if (qY > localDW->enc_counts_now_last)
    {
        qY = 0U;
    }

    if ((rtb_Merge < localDW->enc_counts_now_last) && (qY > enc_line_half))
    {
        /* '<S4>:1:18' if (pos_now_last - pos_now) > enc_line_half */
        /* 向上溢出 */
        /* '<S4>:1:19' circle_int_n_ = circle_int_n_ + int64(enc_line); */
        if (localDW->circle_int_n_ > MAX_int64_T - rtu_config->enc_line_p_n)
        {
            localDW->circle_int_n_ = MAX_int64_T;
        }
        else
        {
            localDW->circle_int_n_ += rtu_config->enc_line_p_n;
        }

        /* 累计圈数 +1 */
    }

    /* '<S4>:1:24' sum_pos = circle_int_n_ + int64(pos_now); */
    if (localDW->circle_int_n_ > MAX_int64_T - rtb_Merge)
    {
        tmp = MAX_int64_T;
    }
    else
    {
        tmp = localDW->circle_int_n_ + rtb_Merge;
    }

    /* Sum: '<S1>/Add1' incorporates:
     *  MATLAB Function: '<S1>/MATLAB Function'
     */
    rty_output->enc_sum_p = rtu_config->init_pos_p + tmp;

    /* Update for Delay: '<S1>/enc_counts_now_last' */
    localDW->enc_counts_now_last = rtb_Merge;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
