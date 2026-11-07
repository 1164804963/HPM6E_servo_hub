/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: mit_ctl.c
 *
 * Code generated for Simulink model 'mit_ctl'.
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

#include "mit_ctl.h"
#include "servo_hub_database_type.h"
#include "rtwtypes.h"

/* Output and update for referenced model: 'mit_ctl' */
void mit_ctl(const MitCtlInput *rtu_input, const MitCtlConfig *rtu_config,
             MitCtlOutput *rty_output)
{
    real32_T rtb_Divide;

    /* Product: '<S1>/Divide' incorporates:
     *  DataTypeConversion: '<S1>/Data Type Conversion'
     *  Gain: '<S3>/Gain1'
     *  Gain: '<S4>/Gain1'
     *  Product: '<S1>/Product'
     *  Product: '<S1>/Product1'
     *  Product: '<S3>/Product'
     *  Product: '<S4>/Product'
     *  Sum: '<S1>/Add'
     *  Sum: '<S1>/Add1'
     *  Sum: '<S1>/Add2'
     */
    rtb_Divide = (((real32_T)(rtu_input->pos_tar_p - rtu_input->pos_now_p) *
                   6.28318548F * rtu_config->enc_line_inv_p_n *
                   rtu_config->kp_pos_NM_rad + rtu_input->tq_set_NM) +
                  (6.28318548F * rtu_input->speed_tar_p_s *
                   rtu_config->enc_line_inv_p_n - rtu_input->speed_now_rad_s) *
                  rtu_config->kd_spd_NM_rad_s) / rtu_config->kt_NM_A;

    /* Switch: '<S2>/Switch2' incorporates:
     *  Gain: '<S1>/Gain'
     *  RelationalOperator: '<S2>/LowerRelop1'
     *  RelationalOperator: '<S2>/UpperRelop'
     *  Switch: '<S2>/Switch'
     */
    if (rtb_Divide > rtu_input->iq_max_A)
    {
        /* BusCreator: '<S1>/Bus Creator' */
        rty_output->iq_tar_A = rtu_input->iq_max_A;
    }
    else if (rtb_Divide < -rtu_input->iq_max_A)
    {
        /* Switch: '<S2>/Switch' incorporates:
         *  BusCreator: '<S1>/Bus Creator'
         *  Gain: '<S1>/Gain'
         */
        rty_output->iq_tar_A = -rtu_input->iq_max_A;
    }
    else
    {
        /* BusCreator: '<S1>/Bus Creator' incorporates:
         *  Switch: '<S2>/Switch'
         */
        rty_output->iq_tar_A = rtb_Divide;
    }

    /* End of Switch: '<S2>/Switch2' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
