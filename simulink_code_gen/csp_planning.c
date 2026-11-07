/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: csp_planning.c
 *
 * Code generated for Simulink model 'csp_planning'.
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

#include "csp_planning.h"
#include "rtwtypes.h"
#include <math.h>

/* System initialize for referenced model: 'csp_planning' */
void csp_planning_Init(csp_planning_DW_f *localDW)
{
    /* Outputs for Atomic SubSystem: '<S1>/Initialize Function' */
    /* StateWriter: '<S2>/State Writer' incorporates:
     *  Constant: '<S2>/Constant1'
     */
    localDW->x0_sum = 0.0F;

    /* End of Outputs for SubSystem: '<S1>/Initialize Function' */
}

/* Output and update for referenced model: 'csp_planning' */
void csp_planning(const int64_T rtu_pos_target_ip_buff[4], const real32_T
                  *rtu_ip_dt, const real32_T *rtu_dt_p, int64_T *rty_pos_cmd,
                  real32_T *rty_v_cmd, real32_T *rty_acc_cmd, csp_planning_DW_f *
                  localDW)
{
    int32_T high_i;
    int32_T low_i;
    int32_T low_ip1;
    real32_T delta_idx_0;
    real32_T delta_idx_1;
    real32_T delta_idx_2;
    real32_T delta_n1;
    real32_T h;
    real32_T h_idx_1;
    real32_T rtb_DataTypeConversion_idx_1;
    real32_T rtb_DataTypeConversion_idx_2;
    real32_T slopes_idx_0;
    real32_T slopes_idx_2;
    real32_T w1;
    real32_T w2;

    /* Product: '<S1>/Product' incorporates:
     *  Constant: '<S1>/Constant'
     */
    localDW->Product[0] = 0.0F;

    /* DataTypeConversion: '<S1>/Data Type Conversion' incorporates:
     *  Sum: '<S1>/Add'
     */
    rtb_DataTypeConversion_idx_1 = (real32_T)(rtu_pos_target_ip_buff[1] -
        rtu_pos_target_ip_buff[0]);

    /* Product: '<S1>/Product' */
    localDW->Product[1] = *rtu_ip_dt;

    /* DataTypeConversion: '<S1>/Data Type Conversion' incorporates:
     *  Sum: '<S1>/Add'
     */
    rtb_DataTypeConversion_idx_2 = (real32_T)(rtu_pos_target_ip_buff[2] -
        rtu_pos_target_ip_buff[0]);

    /* Product: '<S1>/Product' incorporates:
     *  Constant: '<S1>/Constant'
     */
    localDW->Product[2] = *rtu_ip_dt * 2.0F;
    localDW->Product[3] = *rtu_ip_dt * 3.0F;

    /* MATLAB Function: '<S1>/MATLAB Function' incorporates:
     *  DataTypeConversion: '<S1>/Data Type Conversion'
     *  DiscreteIntegrator: '<S4>/Discrete-Time Integrator'
     *  Sum: '<S1>/Add'
     */
    /*  可选插值方法pchip、 makima 、spline一阶导数和二阶导数 */
    /*  输入: */
    /*    pp - 返回的分段多项式结构 */
    /*    x0 - 要计算的点（可以是向量） */
    /*  输出: */
    /*    y0  - 函数值 */
    /*    dy0 - 一阶导数 */
    /*    d2y0 - 二阶导数 */
    /* MATLAB Function 'Subsystem1/MATLAB Function': '<S3>:1' */
    /* '<S3>:1:12' pp = makima(x, y); */
    delta_idx_0 = rtb_DataTypeConversion_idx_1 / localDW->Product[1];
    h = localDW->Product[2] - localDW->Product[1];
    h_idx_1 = h;
    delta_idx_1 = (rtb_DataTypeConversion_idx_2 - rtb_DataTypeConversion_idx_1) /
        h;
    h = localDW->Product[3] - localDW->Product[2];
    delta_idx_2 = ((real32_T)(rtu_pos_target_ip_buff[3] -
                    rtu_pos_target_ip_buff[0]) - rtb_DataTypeConversion_idx_2) /
        h;
    localDW->delta_0 = 2.0F * delta_idx_0 - delta_idx_1;
    localDW->delta_m1 = 2.0F * localDW->delta_0 - delta_idx_0;
    localDW->delta_n = 2.0F * delta_idx_2 - delta_idx_1;
    delta_n1 = 2.0F * localDW->delta_n - delta_idx_2;
    w1 = fabsf(localDW->delta_0 + localDW->delta_m1) / 2.0F + fabsf
        (localDW->delta_0 - localDW->delta_m1);
    slopes_idx_2 = fabsf(delta_idx_1 + delta_idx_0) / 2.0F + fabsf(delta_idx_1 -
        delta_idx_0);
    localDW->delta_m1 = w1 + slopes_idx_2;
    if (localDW->delta_m1 == 0.0F)
    {
        slopes_idx_0 = 0.0F;
    }
    else
    {
        slopes_idx_0 = slopes_idx_2 / localDW->delta_m1 * localDW->delta_0 + w1 /
            localDW->delta_m1 * delta_idx_0;
    }

    w1 = fabsf(delta_idx_0 + localDW->delta_0) / 2.0F + fabsf(delta_idx_0 -
        localDW->delta_0);
    localDW->delta_0 = fabsf(delta_idx_2 + delta_idx_1) / 2.0F + fabsf
        (delta_idx_2 - delta_idx_1);
    localDW->delta_m1 = w1 + localDW->delta_0;
    if (localDW->delta_m1 == 0.0F)
    {
        w1 = 0.0F;
    }
    else
    {
        w1 = localDW->delta_0 / localDW->delta_m1 * delta_idx_0 + w1 /
            localDW->delta_m1 * delta_idx_1;
    }

    w2 = fabsf(localDW->delta_n + delta_idx_2) / 2.0F + fabsf(localDW->delta_n -
        delta_idx_2);
    localDW->delta_m1 = slopes_idx_2 + w2;
    if (localDW->delta_m1 == 0.0F)
    {
        slopes_idx_2 = 0.0F;
    }
    else
    {
        slopes_idx_2 = w2 / localDW->delta_m1 * delta_idx_1 + slopes_idx_2 /
            localDW->delta_m1 * delta_idx_2;
    }

    w2 = fabsf(delta_n1 + localDW->delta_n) / 2.0F + fabsf(delta_n1 -
        localDW->delta_n);
    localDW->delta_m1 = localDW->delta_0 + w2;
    if (localDW->delta_m1 == 0.0F)
    {
        localDW->delta_n = 0.0F;
    }
    else
    {
        localDW->delta_n = w2 / localDW->delta_m1 * delta_idx_2 +
            localDW->delta_0 / localDW->delta_m1 * localDW->delta_n;
    }

    localDW->delta_0 = (delta_idx_0 - slopes_idx_0) / localDW->Product[1];
    localDW->delta_m1 = (w1 - delta_idx_0) / localDW->Product[1];
    localDW->pp_coefs[0] = (localDW->delta_m1 - localDW->delta_0) /
        localDW->Product[1];
    localDW->pp_coefs[3] = 2.0F * localDW->delta_0 - localDW->delta_m1;
    localDW->pp_coefs[6] = slopes_idx_0;
    localDW->pp_coefs[9] = 0.0F;
    localDW->delta_0 = (delta_idx_1 - w1) / h_idx_1;
    localDW->delta_m1 = (slopes_idx_2 - delta_idx_1) / h_idx_1;
    localDW->pp_coefs[1] = (localDW->delta_m1 - localDW->delta_0) / h_idx_1;
    localDW->pp_coefs[4] = 2.0F * localDW->delta_0 - localDW->delta_m1;
    localDW->pp_coefs[7] = w1;
    localDW->pp_coefs[10] = rtb_DataTypeConversion_idx_1;
    localDW->delta_0 = (delta_idx_2 - slopes_idx_2) / h;
    localDW->delta_m1 = (localDW->delta_n - delta_idx_2) / h;
    localDW->pp_coefs[2] = (localDW->delta_m1 - localDW->delta_0) / h;
    localDW->pp_coefs[5] = 2.0F * localDW->delta_0 - localDW->delta_m1;
    localDW->pp_coefs[8] = slopes_idx_2;
    localDW->pp_coefs[11] = rtb_DataTypeConversion_idx_2;

    /*  1. 计算函数值 */
    /* '<S3>:1:15' y0 = ppval(pp, x0); */
    high_i = 4;
    low_i = 0;
    low_ip1 = 2;
    while (high_i > low_ip1)
    {
        int32_T mid_i;
        mid_i = ((low_i + high_i) + 1) >> 1;
        if (localDW->x0_sum >= localDW->Product[mid_i - 1])
        {
            low_i = mid_i - 1;
            low_ip1 = mid_i + 1;
        }
        else
        {
            high_i = mid_i;
        }
    }

    localDW->delta_m1 = localDW->x0_sum - localDW->Product[low_i];

    /* Gain: '<S1>/Gain' */
    /*  方法二：手动从系数计算 */
    /* '<S3>:1:18' breaks = pp.breaks; */
    /* '<S3>:1:19' coefs = pp.coefs; */
    /* x0必须始终在插值第一段 */
    /* '<S3>:1:23' c = coefs(1, :); */
    /*  系数为 [a, b, c, d]，对应 (x-break)^3, (x-break)^2, (x-break)^1, 常数项 */
    /* '<S3>:1:24' t = x0 - breaks(1); */
    /*  一阶导数 */
    /* '<S3>:1:26' dy0 = 3*c(1)*t^2 + 2*c(2)*t + c(3); */
    /*  二阶导数 */
    /* '<S3>:1:28' d2y0 = 6*c(1)*t + 2*c(2); */
    localDW->delta_n = 2.0F * *rtu_ip_dt;

    /* Switch: '<S1>/Switch3' incorporates:
     *  Constant: '<S1>/Constant1'
     *  Constant: '<S1>/Constant2'
     *  DataTypeConversion: '<S1>/Data Type Conversion1'
     *  DiscreteIntegrator: '<S4>/Discrete-Time Integrator'
     *  MATLAB Function: '<S1>/MATLAB Function'
     *  RelationalOperator: '<S1>/Relational Operator'
     *  Sum: '<S1>/Add1'
     *  Switch: '<S1>/Switch1'
     *  Switch: '<S1>/Switch2'
     */
    if (localDW->x0_sum < localDW->delta_n)
    {
        *rty_pos_cmd = (int64_T)floorf(((localDW->delta_m1 * localDW->
            pp_coefs[low_i] + localDW->pp_coefs[low_i + 3]) * localDW->delta_m1
            + localDW->pp_coefs[low_i + 6]) * localDW->delta_m1 +
            localDW->pp_coefs[low_i + 9]) + rtu_pos_target_ip_buff[0];
        *rty_acc_cmd = 6.0F * localDW->pp_coefs[0] * localDW->x0_sum + 2.0F *
            localDW->pp_coefs[3];
        *rty_v_cmd = (3.0F * localDW->pp_coefs[0] * (localDW->x0_sum *
                       localDW->x0_sum) + 2.0F * localDW->pp_coefs[3] *
                      localDW->x0_sum) + slopes_idx_0;
    }
    else
    {
        *rty_pos_cmd = rtu_pos_target_ip_buff[3];
        *rty_acc_cmd = 0.0F;
        *rty_v_cmd = 0.0F;
    }

    /* End of Switch: '<S1>/Switch3' */

    /* Update for DiscreteIntegrator: '<S4>/Discrete-Time Integrator' */
    localDW->x0_sum += *rtu_dt_p;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
