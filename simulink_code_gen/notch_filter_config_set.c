/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: notch_filter_config_set.c
 *
 * Code generated for Simulink model 'notch_filter_config_set'.
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

#include "notch_filter_config_set.h"
#include "servo_hub_database_type.h"
#include "rtwtypes.h"

/* Output and update for referenced model: 'notch_filter_config_set' */
void notch_filter_config_set(const NotchFilterConfig *rtu_config, const real32_T
    *rtu_dt, NotchFilterInternal *rty_internal)
{
    int32_T i;

    /* MATLAB Function 'set_notch_filter_config': '<S1>:1' */
    /* '<S1>:1:3' num = uint8(6); */
    /* 6组滤波器 */
    /* '<S1>:1:4' b0 = single(0); */
    /* '<S1>:1:5' b1 = single(0); */
    /* '<S1>:1:6' b2 = single(0); */
    /* '<S1>:1:8' u2 = single(zeros(num, 1)); */
    /* '<S1>:1:9' u0 = single(zeros(num, 1)); */
    /* '<S1>:1:10' u1 = single(zeros(num, 1)); */
    /* '<S1>:1:11' y0 = single(zeros(num, 1)); */
    /* '<S1>:1:12' y1 = single(zeros(num, 1)); */
    /* '<S1>:1:14' for i=1:1:num */
    for (i = 0; i < 6; i++)
    {
        real32_T b0;
        real32_T b2;
        real32_T rtb_u1_tmp;
        real32_T rtb_u2_tmp;
        real32_T rtb_u2_tmp_tmp;

        /* MATLAB Function: '<Root>/set_notch_filter_config' */
        /* '<S1>:1:15' if frq(i) < single(0.0001) */
        b0 = rtu_config->frq[i];
        if (b0 < 0.0001F)
        {
            /*  频率设置为0.0fHZ  表示滤波器不生效 frq 必须 >=0 */
            /* '<S1>:1:16' u2(i) = single(1.0); */
            b2 = 1.0F;

            /* '<S1>:1:17' u0(i) = single(0.0); */
            rtb_u2_tmp = 0.0F;

            /* '<S1>:1:18' u1(i) = single(0.0); */
            rtb_u2_tmp_tmp = 0.0F;

            /* '<S1>:1:19' y0(i) = single(0.0); */
            b0 = 0.0F;

            /* '<S1>:1:20' y1(i) = single(0.0); */
            rtb_u1_tmp = 0.0F;
        }
        else
        {
            real32_T rtb_u2_tmp_0;
            real32_T rtb_u2_tmp_tmp_0;

            /* '<S1>:1:21' else */
            /* '<S1>:1:22' b0 = frq(i) * single(2.0) * pi; */
            b0 = b0 * 2.0F * 3.14159274F;

            /* '<S1>:1:23' b2 = width(i) * single(2.0) * pi; */
            b2 = rtu_config->width[i] * 2.0F * 3.14159274F;

            /* '<S1>:1:24' b1 = depth(i) * b2; */
            /* '<S1>:1:26' u2(i) = (dt + 2*b1/(b0*b0) + 4/(dt*b0*b0)) / (dt + 2*b2/(b0*b0) + 4/(dt*b0*b0)); */
            rtb_u2_tmp = b0 * b0;
            rtb_u2_tmp_tmp = *rtu_dt * b0 * b0;
            b0 = 4.0F / rtb_u2_tmp_tmp;
            rtb_u2_tmp_tmp_0 = 2.0F * b2 / rtb_u2_tmp;
            rtb_u2_tmp_0 = (rtb_u2_tmp_tmp_0 + *rtu_dt) + b0;
            rtb_u2_tmp = rtu_config->depth[i] * b2 * 2.0F / rtb_u2_tmp;
            b2 = ((rtb_u2_tmp + *rtu_dt) + b0) / rtb_u2_tmp_0;

            /* '<S1>:1:27' u1(i) = (2*dt - 8/(dt*b0*b0)) / (dt + 2*b2/(b0*b0) + 4/(dt*b0*b0)); */
            rtb_u1_tmp = 2.0F * *rtu_dt - 8.0F / rtb_u2_tmp_tmp;
            rtb_u2_tmp_tmp = rtb_u1_tmp / rtb_u2_tmp_0;

            /* '<S1>:1:28' u0(i) = (dt - 2*b1/(b0*b0) + 4/(dt*b0*b0)) / (dt + 2*b2/(b0*b0) + 4/(dt*b0*b0)); */
            rtb_u2_tmp = ((*rtu_dt - rtb_u2_tmp) + b0) / rtb_u2_tmp_0;

            /* '<S1>:1:30' y1(i) = -(2*dt - 8/(dt*b0*b0)) / (dt + 2*b2/(b0*b0) + 4/(dt*b0*b0)); */
            rtb_u1_tmp = -rtb_u1_tmp / rtb_u2_tmp_0;

            /* '<S1>:1:31' y0(i) = -(dt - 2*b2/(b0*b0) + 4/(dt*b0*b0)) / (dt + 2*b2/(b0*b0) + 4/(dt*b0*b0)); */
            b0 = -((*rtu_dt - rtb_u2_tmp_tmp_0) + b0) / rtb_u2_tmp_0;
        }

        /* End of MATLAB Function: '<Root>/set_notch_filter_config' */

        /* BusAssignment: '<Root>/Bus Assignment' */
        rty_internal->u0[i] = rtb_u2_tmp;
        rty_internal->u1[i] = rtb_u2_tmp_tmp;
        rty_internal->u2[i] = b2;
        rty_internal->y0[i] = b0;
        rty_internal->y1[i] = rtb_u1_tmp;
    }
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
