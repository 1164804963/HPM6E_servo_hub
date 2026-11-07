/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: notch_filter.c
 *
 * Code generated for Simulink model 'notch_filter'.
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

#include "notch_filter.h"
#include "servo_hub_database_type.h"
#include "rtwtypes.h"

/* System initialize for referenced model: 'notch_filter' */
void notch_filter_Init(notch_filter_DW_f *localDW)
{
    /* Outputs for Atomic SubSystem: '<Root>/Initialize Function' */
    /* StateWriter: '<S1>/State Writer' incorporates:
     *  Constant: '<S1>/Constant1'
     */
    localDW->u_last_ix = 0.0F;

    /* StateWriter: '<S1>/State Writer9' incorporates:
     *  Constant: '<S1>/Constant10'
     */
    localDW->y_last_fj = 0.0F;

    /* StateWriter: '<S1>/State Writer10' incorporates:
     *  Constant: '<S1>/Constant11'
     */
    localDW->u_last_o = 0.0F;

    /* StateWriter: '<S1>/State Writer11' incorporates:
     *  Constant: '<S1>/Constant12'
     */
    localDW->y_last_a = 0.0F;

    /* StateWriter: '<S1>/State Writer15' incorporates:
     *  Constant: '<S1>/Constant13'
     */
    localDW->y_last_e = 0.0F;

    /* StateWriter: '<S1>/State Writer12' incorporates:
     *  Constant: '<S1>/Constant14'
     */
    localDW->u_last_bm = 0.0F;

    /* StateWriter: '<S1>/State Writer13' incorporates:
     *  Constant: '<S1>/Constant15'
     */
    localDW->y_last_i = 0.0F;

    /* StateWriter: '<S1>/State Writer14' incorporates:
     *  Constant: '<S1>/Constant16'
     */
    localDW->u_last_f = 0.0F;

    /* StateWriter: '<S1>/State Writer19' incorporates:
     *  Constant: '<S1>/Constant17'
     */
    localDW->y_last_f = 0.0F;

    /* StateWriter: '<S1>/State Writer16' incorporates:
     *  Constant: '<S1>/Constant18'
     */
    localDW->u_last_b = 0.0F;

    /* StateWriter: '<S1>/State Writer17' incorporates:
     *  Constant: '<S1>/Constant19'
     */
    localDW->y_last_ct = 0.0F;

    /* StateWriter: '<S1>/State Writer1' incorporates:
     *  Constant: '<S1>/Constant2'
     */
    localDW->u_last_l = 0.0F;

    /* StateWriter: '<S1>/State Writer18' incorporates:
     *  Constant: '<S1>/Constant20'
     */
    localDW->u_last_bt = 0.0F;

    /* StateWriter: '<S1>/State Writer23' incorporates:
     *  Constant: '<S1>/Constant21'
     */
    localDW->y_last = 0.0F;

    /* StateWriter: '<S1>/State Writer20' incorporates:
     *  Constant: '<S1>/Constant22'
     */
    localDW->u_last = 0.0F;

    /* StateWriter: '<S1>/State Writer21' incorporates:
     *  Constant: '<S1>/Constant23'
     */
    localDW->y_last_c = 0.0F;

    /* StateWriter: '<S1>/State Writer22' incorporates:
     *  Constant: '<S1>/Constant24'
     */
    localDW->u_last_i = 0.0F;

    /* StateWriter: '<S1>/State Writer2' incorporates:
     *  Constant: '<S1>/Constant3'
     */
    localDW->y_last_p = 0.0F;

    /* StateWriter: '<S1>/State Writer3' incorporates:
     *  Constant: '<S1>/Constant4'
     */
    localDW->y_last_ov = 0.0F;

    /* StateWriter: '<S1>/State Writer4' incorporates:
     *  Constant: '<S1>/Constant5'
     */
    localDW->u_last_p2 = 0.0F;

    /* StateWriter: '<S1>/State Writer5' incorporates:
     *  Constant: '<S1>/Constant6'
     */
    localDW->y_last_o = 0.0F;

    /* StateWriter: '<S1>/State Writer6' incorporates:
     *  Constant: '<S1>/Constant7'
     */
    localDW->u_last_p = 0.0F;

    /* StateWriter: '<S1>/State Writer7' incorporates:
     *  Constant: '<S1>/Constant8'
     */
    localDW->y_last_cg = 0.0F;

    /* StateWriter: '<S1>/State Writer8' incorporates:
     *  Constant: '<S1>/Constant9'
     */
    localDW->u_last_m = 0.0F;

    /* End of Outputs for SubSystem: '<Root>/Initialize Function' */
}

/* Output and update for referenced model: 'notch_filter' */
void notch_filter(const NotchFilterInput *rtu_input, const NotchFilterInternal
                  *rtu_internal, NotchFilterOutput *rty_output,
                  notch_filter_DW_f *localDW)
{
    real32_T rtb_Add;
    real32_T rtb_Add_e5;
    real32_T rtb_Add_i;
    real32_T rtb_Add_m;
    real32_T rtb_Add_n;
    real32_T rtb_Add_o;

    /* Sum: '<S2>/Add' incorporates:
     *  Delay: '<S2>/Delay'
     *  Delay: '<S2>/Delay1'
     *  Delay: '<S2>/Delay2'
     *  Delay: '<S2>/Delay3'
     *  Product: '<S2>/Product'
     *  Product: '<S2>/Product1'
     *  Product: '<S2>/Product2'
     *  Product: '<S2>/Product3'
     *  Product: '<S2>/Product4'
     */
    rtb_Add = (((localDW->y_last_ov * rtu_internal->y0[0] + localDW->y_last_p *
                 rtu_internal->y1[0]) + rtu_internal->u0[0] * localDW->u_last_l)
               + rtu_internal->u1[0] * localDW->u_last_ix) + rtu_internal->u2[0]
        * rtu_input->iq_tar_A;

    /* Sum: '<S3>/Add' incorporates:
     *  Delay: '<S3>/Delay'
     *  Delay: '<S3>/Delay1'
     *  Delay: '<S3>/Delay2'
     *  Delay: '<S3>/Delay3'
     *  Product: '<S3>/Product'
     *  Product: '<S3>/Product1'
     *  Product: '<S3>/Product2'
     *  Product: '<S3>/Product3'
     *  Product: '<S3>/Product4'
     */
    rtb_Add_n = (((localDW->y_last_o * rtu_internal->y0[1] + localDW->y_last_cg *
                   rtu_internal->y1[1]) + rtu_internal->u0[1] *
                  localDW->u_last_p) + rtu_internal->u1[1] * localDW->u_last_p2)
        + rtu_internal->u2[1] * rtb_Add;

    /* Sum: '<S4>/Add' incorporates:
     *  Delay: '<S4>/Delay'
     *  Delay: '<S4>/Delay1'
     *  Delay: '<S4>/Delay2'
     *  Delay: '<S4>/Delay3'
     *  Product: '<S4>/Product'
     *  Product: '<S4>/Product1'
     *  Product: '<S4>/Product2'
     *  Product: '<S4>/Product3'
     *  Product: '<S4>/Product4'
     */
    rtb_Add_e5 = (((localDW->y_last_fj * rtu_internal->y0[2] + localDW->y_last_a
                    * rtu_internal->y1[2]) + rtu_internal->u0[2] *
                   localDW->u_last_o) + rtu_internal->u1[2] * localDW->u_last_m)
        + rtu_internal->u2[2] * rtb_Add_n;

    /* Sum: '<S5>/Add' incorporates:
     *  Delay: '<S5>/Delay'
     *  Delay: '<S5>/Delay1'
     *  Delay: '<S5>/Delay2'
     *  Delay: '<S5>/Delay3'
     *  Product: '<S5>/Product'
     *  Product: '<S5>/Product1'
     *  Product: '<S5>/Product2'
     *  Product: '<S5>/Product3'
     *  Product: '<S5>/Product4'
     */
    rtb_Add_i = (((localDW->y_last_e * rtu_internal->y0[3] + localDW->y_last_i *
                   rtu_internal->y1[3]) + rtu_internal->u0[3] *
                  localDW->u_last_bm) + rtu_internal->u1[3] * localDW->u_last_f)
        + rtu_internal->u2[3] * rtb_Add_e5;

    /* Sum: '<S6>/Add' incorporates:
     *  Delay: '<S6>/Delay'
     *  Delay: '<S6>/Delay1'
     *  Delay: '<S6>/Delay2'
     *  Delay: '<S6>/Delay3'
     *  Product: '<S6>/Product'
     *  Product: '<S6>/Product1'
     *  Product: '<S6>/Product2'
     *  Product: '<S6>/Product3'
     *  Product: '<S6>/Product4'
     */
    rtb_Add_m = (((localDW->y_last_f * rtu_internal->y0[4] + localDW->y_last_ct *
                   rtu_internal->y1[4]) + rtu_internal->u0[4] *
                  localDW->u_last_b) + rtu_internal->u1[4] * localDW->u_last_bt)
        + rtu_internal->u2[4] * rtb_Add_i;

    /* Sum: '<S7>/Add' incorporates:
     *  Delay: '<S7>/Delay'
     *  Delay: '<S7>/Delay1'
     *  Delay: '<S7>/Delay2'
     *  Delay: '<S7>/Delay3'
     *  Product: '<S7>/Product'
     *  Product: '<S7>/Product1'
     *  Product: '<S7>/Product2'
     *  Product: '<S7>/Product3'
     *  Product: '<S7>/Product4'
     */
    rtb_Add_o = (((localDW->y_last * rtu_internal->y0[5] + localDW->y_last_c *
                   rtu_internal->y1[5]) + rtu_internal->u0[5] * localDW->u_last)
                 + rtu_internal->u1[5] * localDW->u_last_i) + rtu_internal->u2[5]
        * rtb_Add_m;

    /* BusCreator: '<Root>/Bus Creator' */
    rty_output->iq_tar_filter_A = rtb_Add_o;

    /* Update for Delay: '<S7>/Delay3' incorporates:
     *  Delay: '<S7>/Delay2'
     */
    localDW->y_last = localDW->y_last_c;

    /* Update for Delay: '<S7>/Delay2' */
    localDW->y_last_c = rtb_Add_o;

    /* Update for Delay: '<S7>/Delay1' incorporates:
     *  Delay: '<S7>/Delay'
     */
    localDW->u_last = localDW->u_last_i;

    /* Update for Delay: '<S7>/Delay' */
    localDW->u_last_i = rtb_Add_m;

    /* Update for Delay: '<S6>/Delay3' incorporates:
     *  Delay: '<S6>/Delay2'
     */
    localDW->y_last_f = localDW->y_last_ct;

    /* Update for Delay: '<S6>/Delay2' */
    localDW->y_last_ct = rtb_Add_m;

    /* Update for Delay: '<S6>/Delay1' incorporates:
     *  Delay: '<S6>/Delay'
     */
    localDW->u_last_b = localDW->u_last_bt;

    /* Update for Delay: '<S6>/Delay' */
    localDW->u_last_bt = rtb_Add_i;

    /* Update for Delay: '<S5>/Delay3' incorporates:
     *  Delay: '<S5>/Delay2'
     */
    localDW->y_last_e = localDW->y_last_i;

    /* Update for Delay: '<S5>/Delay2' */
    localDW->y_last_i = rtb_Add_i;

    /* Update for Delay: '<S5>/Delay1' incorporates:
     *  Delay: '<S5>/Delay'
     */
    localDW->u_last_bm = localDW->u_last_f;

    /* Update for Delay: '<S5>/Delay' */
    localDW->u_last_f = rtb_Add_e5;

    /* Update for Delay: '<S4>/Delay3' incorporates:
     *  Delay: '<S4>/Delay2'
     */
    localDW->y_last_fj = localDW->y_last_a;

    /* Update for Delay: '<S4>/Delay2' */
    localDW->y_last_a = rtb_Add_e5;

    /* Update for Delay: '<S4>/Delay1' incorporates:
     *  Delay: '<S4>/Delay'
     */
    localDW->u_last_o = localDW->u_last_m;

    /* Update for Delay: '<S4>/Delay' */
    localDW->u_last_m = rtb_Add_n;

    /* Update for Delay: '<S3>/Delay3' incorporates:
     *  Delay: '<S3>/Delay2'
     */
    localDW->y_last_o = localDW->y_last_cg;

    /* Update for Delay: '<S3>/Delay2' */
    localDW->y_last_cg = rtb_Add_n;

    /* Update for Delay: '<S3>/Delay1' incorporates:
     *  Delay: '<S3>/Delay'
     */
    localDW->u_last_p = localDW->u_last_p2;

    /* Update for Delay: '<S3>/Delay' */
    localDW->u_last_p2 = rtb_Add;

    /* Update for Delay: '<S2>/Delay3' incorporates:
     *  Delay: '<S2>/Delay2'
     */
    localDW->y_last_ov = localDW->y_last_p;

    /* Update for Delay: '<S2>/Delay2' */
    localDW->y_last_p = rtb_Add;

    /* Update for Delay: '<S2>/Delay1' incorporates:
     *  Delay: '<S2>/Delay'
     */
    localDW->u_last_l = localDW->u_last_ix;

    /* Update for Delay: '<S2>/Delay' */
    localDW->u_last_ix = rtu_input->iq_tar_A;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
