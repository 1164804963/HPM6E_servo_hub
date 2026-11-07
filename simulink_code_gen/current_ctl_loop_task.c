/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: current_ctl_loop_task.c
 *
 * Code generated for Simulink model 'current_ctl_loop_task'.
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

#include "current_ctl_loop_task.h"
#include "rtwtypes.h"
#include "servo_hub_database_type.h"
#include "yuanhub_math.h"

/*
 * Output and update for atomic system:
 *    '<S2>/deadband_comp_ua'
 *    '<S2>/deadband_comp_ub'
 *    '<S2>/deadband_comp_uc'
 */
void current_ctl_loop_task_deadband_comp_ua(real32_T rtu_u_tar, real32_T
    rtu_i_now, const real32_T *rtu_i_noise, const real32_T *rtu_comp_du,
    real32_T *rty_u_tar_comp)
{
    /* MATLAB Function: '<S7>/deadband_comp' */
    /* MATLAB Function 'current_ctl_loop_task/current_ctl_loop/deadband_comp_ua/deadband_comp': '<S25>:1' */
    /* '<S25>:1:2' if i_noise < 0.00001 */
    if (*rtu_i_noise < 1.0E-5)
    {
        /* '<S25>:1:3' u_tar_comp = single(0); */
        *rty_u_tar_comp = 0.0F;
    }
    else
    {
        real32_T line_range;

        /* '<S25>:1:7' du = single(0); */
        /* 补偿电压大小 */
        /* '<S25>:1:8' line_range = i_noise * single(2); */
        line_range = *rtu_i_noise * 2.0F;

        /* 线性区域范围 */
        /* '<S25>:1:9' k = comp_du / line_range; */
        /* 线性补偿斜率 */
        /* '<S25>:1:12' if i_now <= line_range && i_now >= -line_range */
        if ((rtu_i_now <= line_range) && (rtu_i_now >= -line_range))
        {
            /*  在线性补偿范围内 */
            /* '<S25>:1:13' du = k * i_now; */
            line_range = *rtu_comp_du / line_range * rtu_i_now;

            /* '<S25>:1:14' else */
            /* 在非线性范围 */
            /* '<S25>:1:15' if i_now > single(0) */
        }
        else if (rtu_i_now > 0.0F)
        {
            /* '<S25>:1:16' du = comp_du; */
            line_range = *rtu_comp_du;
        }
        else
        {
            /* '<S25>:1:17' else */
            /* '<S25>:1:18' du = -comp_du; */
            line_range = -*rtu_comp_du;
        }

        /* '<S25>:1:22' u_tar_comp = u_tar + du; */
        *rty_u_tar_comp = rtu_u_tar + line_range;
    }

    /* End of MATLAB Function: '<S7>/deadband_comp' */
}

/* System initialize for referenced model: 'current_ctl_loop_task' */
void current_ctl_loop_task_Init(current_ctl_loop_task_DW_f *localDW)
{
    /* Outputs for Atomic SubSystem: '<S2>/Initialize Function' */
    /* StateWriter: '<S3>/State Writer' incorporates:
     *  Constant: '<S3>/Constant1'
     */
    localDW->id_ki_int = 0.0F;

    /* StateWriter: '<S3>/State Writer1' incorporates:
     *  Constant: '<S3>/Constant2'
     */
    localDW->iq_ki_int = 0.0F;

    /* End of Outputs for SubSystem: '<S2>/Initialize Function' */
}

/* Output and update for referenced model: 'current_ctl_loop_task' */
void current_ctl_loop_task(const CurrentCtlInput *rtu_input, const
    CurrentCtlConfig *rtu_config, CurrentCtlOutput *rty_output,
    current_ctl_loop_task_DW_f *localDW)
{
    real32_T rtb_Add;
    real32_T rtb_Add3;
    real32_T rtb_Gain;
    real32_T rtb_SinCos_o1;
    real32_T rtb_SinCos_o2;
    real32_T rtb_Switch2_e;
    real32_T rtb_Switch_idx_0;
    real32_T rtb_Switch_idx_1;
    real32_T rtb_TmpSignalConversionAtBusCreatorInport2_idx_0;
    real32_T rtb_TmpSignalConversionAtBusCreatorInport2_idx_1;
    real32_T rtb_u_tar_comp;
    real32_T rtb_u_tar_comp_a;
    real32_T rtb_u_tar_comp_j;

    /* Switch: '<S4>/Switch' */
    if (rtu_config->phase_dir > 0)
    {
        rtb_Switch_idx_0 = rtu_input->iabc_now_A[0];
        rtb_Switch_idx_1 = rtu_input->iabc_now_A[1];
    }
    else
    {
        rtb_Switch_idx_0 = rtu_input->iabc_now_A[1];
        rtb_Switch_idx_1 = rtu_input->iabc_now_A[0];
    }

    /* Sum: '<S2>/Add' incorporates:
     *  Product: '<S2>/Product'
     */
    rtb_u_tar_comp_a = rtu_input->elec_angle_speed_rad_s * rtu_config->dt_s *
        rtu_config->elec_angle_compensation + rtu_input->elec_theta_rad;

    /* Trigonometry: '<S6>/SinCos' */
    rtb_SinCos_o1 = yuanhub_sin_f32(rtb_u_tar_comp_a);
    rtb_SinCos_o2 = yuanhub_cos_f32(rtb_u_tar_comp_a);

    /* Gain: '<S15>/Gain' incorporates:
     *  Product: '<S15>/Product'
     */
    rtb_Gain = rtu_input->dc_bus_now_V * rtu_config->pwm_duty_cycle_max *
        0.666666687F;

    /* Outputs for Atomic SubSystem: '<S6>/Clarke Transform' */
    /* Gain: '<S11>/one_by_sqrt3' incorporates:
     *  Sum: '<S11>/a_plus_2b'
     */
    rtb_u_tar_comp = ((rtb_Switch_idx_0 + rtb_Switch_idx_1) + rtb_Switch_idx_1) *
        0.577350259F;

    /* Outputs for Atomic SubSystem: '<S6>/Park Transform1' */
    /* Switch: '<S17>/Switch' incorporates:
     *  AlgorithmDescriptorDelegate generated from: '<S11>/a16'
     *  Product: '<S14>/acos'
     *  Product: '<S14>/asin'
     *  Product: '<S14>/bcos'
     *  Product: '<S14>/bsin'
     *  Sum: '<S14>/sum_Ds'
     *  Sum: '<S14>/sum_Qs'
     */
    rtb_TmpSignalConversionAtBusCreatorInport2_idx_0 = rtb_Switch_idx_0 *
        rtb_SinCos_o2 + rtb_u_tar_comp * rtb_SinCos_o1;
    rtb_TmpSignalConversionAtBusCreatorInport2_idx_1 = rtb_u_tar_comp *
        rtb_SinCos_o2 - rtb_Switch_idx_0 * rtb_SinCos_o1;

    /* End of Outputs for SubSystem: '<S6>/Clarke Transform' */

    /* Product: '<S20>/Product1' incorporates:
     *  AlgorithmDescriptorDelegate generated from: '<S14>/a16'
     *  Gain: '<S20>/Gain2'
     *  Product: '<S20>/Product3'
     *  Sum: '<S15>/Add'
     */
    rtb_u_tar_comp_a = (rtu_input->idq_tar_A[0] -
                        rtb_TmpSignalConversionAtBusCreatorInport2_idx_0) *
        rtu_config->bandwidth_percentage * 0.01F * rtu_config->kp_ld;

    /* End of Outputs for SubSystem: '<S6>/Park Transform1' */

    /* Sum: '<S20>/Add' incorporates:
     *  Delay: '<S20>/Delay'
     *  Product: '<S20>/Product'
     *  Product: '<S20>/Product2'
     */
    rtb_Add = rtu_config->ki_ld * rtb_u_tar_comp_a * rtu_config->dt_s +
        localDW->id_ki_int;

    /* Switch: '<S23>/Switch2' incorporates:
     *  Gain: '<S15>/Gain1'
     *  RelationalOperator: '<S23>/LowerRelop1'
     *  RelationalOperator: '<S23>/UpperRelop'
     *  Switch: '<S23>/Switch'
     */
    if (rtb_Add > rtb_Gain)
    {
        rtb_Add = rtb_Gain;
    }
    else if (rtb_Add < -rtb_Gain)
    {
        /* Switch: '<S23>/Switch' incorporates:
         *  Gain: '<S15>/Gain1'
         */
        rtb_Add = -rtb_Gain;
    }

    /* End of Switch: '<S23>/Switch2' */

    /* Sum: '<S20>/Add3' */
    rtb_Add3 = rtb_Add + rtb_u_tar_comp_a;

    /* Switch: '<S18>/Switch2' incorporates:
     *  Gain: '<S15>/Gain1'
     *  RelationalOperator: '<S18>/LowerRelop1'
     *  RelationalOperator: '<S18>/UpperRelop'
     *  Switch: '<S18>/Switch'
     */
    if (rtb_Add3 > rtb_Gain)
    {
        rtb_Switch2_e = rtb_Gain;
    }
    else if (rtb_Add3 < -rtb_Gain)
    {
        /* Switch: '<S18>/Switch' incorporates:
         *  Gain: '<S15>/Gain1'
         */
        rtb_Switch2_e = -rtb_Gain;
    }
    else
    {
        rtb_Switch2_e = rtb_Add3;
    }

    /* End of Switch: '<S18>/Switch2' */

    /* Outputs for Atomic SubSystem: '<S6>/Park Transform1' */
    /* Product: '<S21>/Product2' incorporates:
     *  AlgorithmDescriptorDelegate generated from: '<S14>/a16'
     *  Gain: '<S21>/Gain2'
     *  Product: '<S21>/Product3'
     *  Sum: '<S15>/Add1'
     *  Sum: '<S6>/Add'
     */
    rtb_u_tar_comp_j = ((rtu_input->idq_tar_A[1] + rtu_input->iq_offset_A) -
                        rtb_TmpSignalConversionAtBusCreatorInport2_idx_1) *
        rtu_config->bandwidth_percentage * 0.01F * rtu_config->kp_lq;

    /* End of Outputs for SubSystem: '<S6>/Park Transform1' */

    /* Sum: '<S21>/Add' incorporates:
     *  Delay: '<S21>/Delay'
     *  Product: '<S21>/Product'
     *  Product: '<S21>/Product1'
     */
    rtb_Add3 = rtu_config->ki_lq * rtb_u_tar_comp_j * rtu_config->dt_s +
        localDW->iq_ki_int;

    /* Switch: '<S24>/Switch2' incorporates:
     *  Gain: '<S15>/Gain1'
     *  RelationalOperator: '<S24>/LowerRelop1'
     *  RelationalOperator: '<S24>/UpperRelop'
     *  Switch: '<S24>/Switch'
     */
    if (rtb_Add3 > rtb_Gain)
    {
        rtb_Add3 = rtb_Gain;
    }
    else if (rtb_Add3 < -rtb_Gain)
    {
        /* Switch: '<S24>/Switch' incorporates:
         *  Gain: '<S15>/Gain1'
         */
        rtb_Add3 = -rtb_Gain;
    }

    /* End of Switch: '<S24>/Switch2' */

    /* Sum: '<S21>/Add3' */
    rtb_u_tar_comp_a = rtb_Add3 + rtb_u_tar_comp_j;

    /* Switch: '<S19>/Switch2' incorporates:
     *  Gain: '<S15>/Gain1'
     *  RelationalOperator: '<S19>/LowerRelop1'
     *  RelationalOperator: '<S19>/UpperRelop'
     *  Switch: '<S19>/Switch'
     */
    if (rtb_u_tar_comp_a > rtb_Gain)
    {
        rtb_u_tar_comp_a = rtb_Gain;
    }
    else if (rtb_u_tar_comp_a < -rtb_Gain)
    {
        /* Switch: '<S19>/Switch' incorporates:
         *  Gain: '<S15>/Gain1'
         */
        rtb_u_tar_comp_a = -rtb_Gain;
    }

    /* End of Switch: '<S19>/Switch2' */

    /* MATLAB Function: '<S15>/udq_max_lim' */
    /* MATLAB Function 'current_ctl_loop_task/current_ctl_loop/current_ctl_pi/current_ctl_pi/udq_max_lim': '<S22>:1' */
    /* '<S22>:1:3' uq_temp = single(v_out_limit^2-ud_tar^2); */
    rtb_Gain = rtb_Gain * rtb_Gain - rtb_Switch2_e * rtb_Switch2_e;

    /* '<S22>:1:5' if(uq_temp >= 0) */
    if (rtb_Gain >= 0.0F)
    {
        /* '<S22>:1:6' uq_max = single(sqrt(uq_temp)); */
        rtb_Gain = yuanhub_sqrt_f32(rtb_Gain);
    }
    else
    {
        /* '<S22>:1:7' else */
        /* '<S22>:1:8' uq_max = single(0); */
        rtb_Gain = 0.0F;
    }

    /* '<S22>:1:11' if(uq_tar > uq_max) */
    if (rtb_u_tar_comp_a > rtb_Gain)
    {
        /* '<S22>:1:12' uq_tar = uq_max; */
        rtb_u_tar_comp_a = rtb_Gain;
    }
    else if (rtb_u_tar_comp_a < -rtb_Gain)
    {
        /* '<S22>:1:13' elseif(uq_tar < -uq_max) */
        /* '<S22>:1:14' uq_tar = -uq_max; */
        rtb_u_tar_comp_a = -rtb_Gain;
    }

    /* Outputs for Atomic SubSystem: '<S6>/Inverse Park Transform' */
    /* Sum: '<S13>/sum_beta' incorporates:
     *  MATLAB Function: '<S15>/udq_max_lim'
     *  Product: '<S13>/dsin'
     *  Product: '<S13>/qcos'
     */
    /* '<S22>:1:17' ud = single(ud_tar); */
    /* '<S22>:1:18' uq = single(uq_tar); */
    rtb_u_tar_comp = rtb_u_tar_comp_a * rtb_SinCos_o2 + rtb_Switch2_e *
        rtb_SinCos_o1;

    /* Sum: '<S13>/sum_alpha' incorporates:
     *  MATLAB Function: '<S15>/udq_max_lim'
     *  Product: '<S13>/dcos'
     *  Product: '<S13>/qsin'
     */
    rtb_u_tar_comp_j = rtb_Switch2_e * rtb_SinCos_o2 - rtb_u_tar_comp_a *
        rtb_SinCos_o1;

    /* End of Outputs for SubSystem: '<S6>/Inverse Park Transform' */

    /* Switch: '<S2>/Switch' incorporates:
     *  Sum: '<S12>/add_b'
     *  Sum: '<S12>/add_c'
     */
    if (rtu_input->mode > 0)
    {
        /* Outputs for Atomic SubSystem: '<S6>/Inverse Park Transform' */
        /* Gain: '<S12>/sqrt3_by_two' incorporates:
         *  Switch: '<S16>/Switch'
         */
        rtb_SinCos_o1 = 0.866025388F * rtb_u_tar_comp;

        /* Gain: '<S12>/one_by_two' incorporates:
         *  Switch: '<S16>/Switch'
         */
        rtb_SinCos_o2 = 0.5F * rtb_u_tar_comp_j;

        /* End of Outputs for SubSystem: '<S6>/Inverse Park Transform' */
        rtb_u_tar_comp_a = rtb_SinCos_o1 - rtb_SinCos_o2;
        rtb_Gain = (0.0F - rtb_SinCos_o2) - rtb_SinCos_o1;
    }
    else
    {
        rtb_u_tar_comp_j = rtu_input->uabc_tar_V[0];
        rtb_u_tar_comp_a = rtu_input->uabc_tar_V[1];
        rtb_Gain = rtu_input->uabc_tar_V[2];
    }

    /* End of Switch: '<S2>/Switch' */

    /* MATLAB Function: '<S2>/svpwm ' */
    /* 最大值最小值法 */
    /* MATLAB Function 'current_ctl_loop_task/current_ctl_loop/svpwm ': '<S10>:1' */
    /* '<S10>:1:3' va = single(uabc(1)); */
    /* '<S10>:1:4' vb = single(uabc(2)); */
    /* '<S10>:1:5' vc = single(uabc(3)); */
    /* '<S10>:1:6' sv_uabc = single(zeros(3,1)); */
    /* '<S10>:1:8' if va>vb */
    if (rtb_u_tar_comp_j > rtb_u_tar_comp_a)
    {
        /* '<S10>:1:9' vmax = va; */
        rtb_SinCos_o1 = rtb_u_tar_comp_j;

        /* '<S10>:1:10' vmin = vb; */
        rtb_SinCos_o2 = rtb_u_tar_comp_a;
    }
    else
    {
        /* '<S10>:1:11' else */
        /* '<S10>:1:12' vmax = vb; */
        rtb_SinCos_o1 = rtb_u_tar_comp_a;

        /* '<S10>:1:13' vmin = va; */
        rtb_SinCos_o2 = rtb_u_tar_comp_j;
    }

    /* '<S10>:1:16' if vc>vmax */
    if (rtb_Gain > rtb_SinCos_o1)
    {
        /* '<S10>:1:17' vmax = vc; */
        rtb_SinCos_o1 = rtb_Gain;
    }
    else if (rtb_Gain < rtb_SinCos_o2)
    {
        /* '<S10>:1:18' elseif vc<vmin */
        /* '<S10>:1:19' vmin = vc; */
        rtb_SinCos_o2 = rtb_Gain;
    }

    /* '<S10>:1:22' vcom = 0.5*(vmax+vmin); */
    rtb_SinCos_o1 = (rtb_SinCos_o1 + rtb_SinCos_o2) * 0.5F;

    /* '<S10>:1:24' ua = va-vcom; */
    rty_output->uabc_tar_org_V[0] = rtb_u_tar_comp_j - rtb_SinCos_o1;

    /* '<S10>:1:25' ub = vb-vcom; */
    rty_output->uabc_tar_org_V[1] = rtb_u_tar_comp_a - rtb_SinCos_o1;

    /* '<S10>:1:26' uc = vc-vcom; */
    rty_output->uabc_tar_org_V[2] = rtb_Gain - rtb_SinCos_o1;

    /* End of MATLAB Function: '<S2>/svpwm ' */

    /* Outputs for Atomic SubSystem: '<S2>/deadband_comp_ua' */
    /* '<S10>:1:28' sv_uabc(1) = single(ua); */
    /* '<S10>:1:29' sv_uabc(2) = single(ub); */
    /* '<S10>:1:30' sv_uabc(3) = single(uc); */
    current_ctl_loop_task_deadband_comp_ua(rty_output->uabc_tar_org_V[0],
        rtb_Switch_idx_0, &rtu_config->i_noise_A, &rtu_config->comp_du_V,
        &rtb_u_tar_comp);

    /* End of Outputs for SubSystem: '<S2>/deadband_comp_ua' */

    /* Outputs for Atomic SubSystem: '<S2>/deadband_comp_ub' */
    current_ctl_loop_task_deadband_comp_ua(rty_output->uabc_tar_org_V[1],
        rtb_Switch_idx_1, &rtu_config->i_noise_A, &rtu_config->comp_du_V,
        &rtb_u_tar_comp_a);

    /* End of Outputs for SubSystem: '<S2>/deadband_comp_ub' */

    /* Outputs for Atomic SubSystem: '<S2>/deadband_comp_uc' */
    /* Switch: '<S4>/Switch' */
    current_ctl_loop_task_deadband_comp_ua(rty_output->uabc_tar_org_V[2],
        rtu_input->iabc_now_A[2], &rtu_config->i_noise_A, &rtu_config->comp_du_V,
        &rtb_u_tar_comp_j);

    /* End of Outputs for SubSystem: '<S2>/deadband_comp_uc' */

    /* Switch: '<S5>/Switch' */
    if (rtu_config->phase_dir > 0)
    {
        rty_output->uabc_tar_comp_V[0] = rtb_u_tar_comp;
        rty_output->uabc_tar_comp_V[1] = rtb_u_tar_comp_a;
    }
    else
    {
        rty_output->uabc_tar_comp_V[0] = rtb_u_tar_comp_a;
        rty_output->uabc_tar_comp_V[1] = rtb_u_tar_comp;
    }

    rty_output->uabc_tar_comp_V[2] = rtb_u_tar_comp_j;

    /* End of Switch: '<S5>/Switch' */

    /* Outputs for Atomic SubSystem: '<S6>/Park Transform1' */
    /* BusCreator: '<S1>/Bus Creator' incorporates:
     *  AlgorithmDescriptorDelegate generated from: '<S14>/a16'
     */
    rty_output->idq_now_A[0] = rtb_TmpSignalConversionAtBusCreatorInport2_idx_0;
    rty_output->idq_now_A[1] = rtb_TmpSignalConversionAtBusCreatorInport2_idx_1;

    /* End of Outputs for SubSystem: '<S6>/Park Transform1' */

    /* Update for Delay: '<S20>/Delay' */
    localDW->id_ki_int = rtb_Add;

    /* Update for Delay: '<S21>/Delay' */
    localDW->iq_ki_int = rtb_Add3;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
