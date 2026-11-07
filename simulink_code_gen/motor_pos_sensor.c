/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: motor_pos_sensor.c
 *
 * Code generated for Simulink model 'motor_pos_sensor'.
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

#include "motor_pos_sensor.h"
#include "servo_hub_database_type.h"
#include "rtwtypes.h"

/* System initialize for referenced model: 'motor_pos_sensor' */
void motor_pos_sensor_Init(void)
{
    /* '<S4>:1:6' circle_int_n_ = int64(0); */
}

/* Output and update for referenced model: 'motor_pos_sensor' */
void motor_pos_sensor(const MotorPosSensorInput *rtu_input, const
                      MotorPosSensorConfig *rtu_config, MotorPosSensorOutput
                      *rty_output, motor_pos_sensor_DW_f *localDW)
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

    /* MATLAB Function: '<S1>/mod2pi_fun' incorporates:
     *  DataTypeConversion: '<S1>/Data Type Conversion'
     *  DataTypeConversion: '<S1>/Data Type Conversion1'
     *  DataTypeConversion: '<S1>/Data Type Conversion2'
     *  Gain: '<S1>/Gain'
     *  Product: '<S1>/Divide'
     *  Product: '<S1>/Product'
     *  Sum: '<S1>/Add'
     */
    rty_output->elec_angle_now_rad = (real32_T)rtb_Merge / (real32_T)
        rtu_config->enc_line_p_n * 6.28318548F * (real32_T)rtu_config->pn -
        rtu_config->elec_angle_bias_rad;

    /*  将角度限制在0到2π范围内 */
    /* MATLAB Function 'fast_math/mod2pi_fun': '<S5>:1' */
    /* '<S5>:1:3' TWO_PI = single(2*pi); */
    /* '<S5>:1:4' n_ang = single(ang); */
    /* '<S5>:1:5' while n_ang < 0 */
    while (rty_output->elec_angle_now_rad < 0.0F)
    {
        /* '<S5>:1:6' n_ang = n_ang + TWO_PI; */
        rty_output->elec_angle_now_rad += 6.28318548F;
    }

    /* '<S5>:1:8' while n_ang >= TWO_PI */
    while (rty_output->elec_angle_now_rad >= 6.28318548F)
    {
        /* '<S5>:1:9' n_ang = n_ang - TWO_PI; */
        rty_output->elec_angle_now_rad -= 6.28318548F;
    }

    /* End of MATLAB Function: '<S1>/mod2pi_fun' */

    /* MATLAB Function: '<S1>/MATLAB Function' incorporates:
     *  Delay: '<S1>/enc_counts_now_last'
     */
    /* MATLAB Function 'motor_pos_sensor/MATLAB Function': '<S4>:1' */
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
