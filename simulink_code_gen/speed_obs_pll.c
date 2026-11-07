/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: speed_obs_pll.c
 *
 * Code generated for Simulink model 'speed_obs_pll'.
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

#include "speed_obs_pll.h"
#include "servo_hub_database_type.h"
#include "rtwtypes.h"

/* System initialize for referenced model: 'speed_obs_pll' */
void speed_obs_pll_Init(speed_obs_pll_DW_f *localDW)
{
    /* Outputs for Atomic SubSystem: '<S1>/Initialize Function' */
    /* StateWriter: '<S2>/State Writer' incorporates:
     *  Constant: '<S2>/Constant1'
     */
    localDW->ev_rad_s_last = 0.0F;

    /* StateWriter: '<S2>/State Writer1' incorporates:
     *  Constant: '<S2>/Constant2'
     */
    localDW->pos_now_p_last = 0LL;

    /* StateWriter: '<S2>/State Writer2' incorporates:
     *  Constant: '<S2>/Constant3'
     */
    localDW->pos_err_last = 0.0F;

    /* End of Outputs for SubSystem: '<S1>/Initialize Function' */
}

/* Output and update for referenced model: 'speed_obs_pll' */
void speed_obs_pll(const SpeedObsPllInput *rtu_input, const SpeedObsPllConfig
                   *rtu_config, SpeedObsPllOutput *rty_output,
                   speed_obs_pll_DW_f *localDW)
{
    real32_T rtb_Saturation;
    real32_T rtb_ev_rad_s;
    real32_T rtb_wn_rad;

    /* Gain: '<S1>/Gain' */
    rtb_wn_rad = 6.28318548F * rtu_config->wn_Hz;

    /* Sum: '<S1>/Add3' incorporates:
     *  DataTypeConversion: '<S1>/Data Type Conversion'
     *  Delay: '<S1>/Delay1'
     *  Delay: '<S1>/Delay2'
     *  Gain: '<S4>/Gain1'
     *  Product: '<S4>/Product'
     *  Sum: '<S1>/Add'
     */
    rtb_Saturation = (real32_T)(rtu_input->pos_now_p - localDW->pos_now_p_last) *
        6.28318548F * rtu_config->enc_line_inv_p_n + localDW->pos_err_last;

    /* Saturate: '<S1>/Saturation' */
    if (rtb_Saturation > 1.0F)
    {
        rtb_Saturation = 1.0F;
    }
    else if (rtb_Saturation < -1.0F)
    {
        rtb_Saturation = -1.0F;
    }

    /* End of Saturate: '<S1>/Saturation' */

    /* Sum: '<S1>/Add4' incorporates:
     *  Delay: '<S1>/Delay'
     *  Product: '<S1>/Product2'
     *  Product: '<S1>/Product3'
     */
    rtb_ev_rad_s = rtb_wn_rad * rtb_wn_rad * rtu_config->tp_s * rtb_Saturation +
        localDW->ev_rad_s_last;

    /* BusCreator generated from: '<Root>/output' */
    rty_output->ev_rad_s = rtb_ev_rad_s;

    /* Switch: '<S3>/Switch2' incorporates:
     *  Gain: '<S1>/Gain3'
     *  RelationalOperator: '<S3>/LowerRelop1'
     *  RelationalOperator: '<S3>/UpperRelop'
     *  Switch: '<S3>/Switch'
     */
    if (rtb_ev_rad_s > rtu_config->speed_obs_max_rad_s)
    {
        /* Update for Delay: '<S1>/Delay' */
        localDW->ev_rad_s_last = rtu_config->speed_obs_max_rad_s;
    }
    else if (rtb_ev_rad_s < -rtu_config->speed_obs_max_rad_s)
    {
        /* Switch: '<S3>/Switch' incorporates:
         *  Delay: '<S1>/Delay'
         *  Gain: '<S1>/Gain3'
         */
        localDW->ev_rad_s_last = -rtu_config->speed_obs_max_rad_s;
    }
    else
    {
        /* Update for Delay: '<S1>/Delay' incorporates:
         *  Switch: '<S3>/Switch'
         */
        localDW->ev_rad_s_last = rtb_ev_rad_s;
    }

    /* End of Switch: '<S3>/Switch2' */

    /* Update for Delay: '<S1>/Delay1' */
    localDW->pos_now_p_last = rtu_input->pos_now_p;

    /* Update for Delay: '<S1>/Delay2' incorporates:
     *  Constant: '<S1>/cos_45_2'
     *  Product: '<S1>/Product'
     *  Product: '<S1>/Product1'
     *  Product: '<S1>/Product4'
     *  Sum: '<S1>/Add1'
     *  Sum: '<S1>/Add2'
     */
    localDW->pos_err_last = rtb_Saturation - (rtb_wn_rad * 1.414F *
        rtb_Saturation + rtb_ev_rad_s) * rtu_config->tp_s;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
