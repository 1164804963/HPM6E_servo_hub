/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: sim_plant.c
 *
 * Code generated for Simulink model 'sim_plant'.
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

#include "sim_plant.h"
#include "rtwtypes.h"
#include "servo_hub_database_type.h"
#include "rt_urand_Upu32_Yd_f_pw.h"
#include "yuanhub_math.h"

/*
 * Output and update for atomic system:
 *    '<S15>/mod2pi_fun'
 *    '<S6>/mod2pi_fun'
 */
void sim_plant_mod2pi_fun(real32_T rtu_ang, real32_T *rty_n_ang)
{
    *rty_n_ang = rtu_ang;

    /*  将角度限制在0到2π范围内 */
    /* MATLAB Function 'sim_plant/sm_pmsm_model/dis_int_wm/mod2pi_fun': '<S18>:1' */
    /* '<S18>:1:3' TWO_PI = single(2*pi); */
    /* '<S18>:1:4' n_ang = single(ang); */
    /* '<S18>:1:5' while n_ang < 0 */
    while (*rty_n_ang < 0.0F)
    {
        /* '<S18>:1:6' n_ang = n_ang + TWO_PI; */
        *rty_n_ang += 6.28318548F;
    }

    /* '<S18>:1:8' while n_ang >= TWO_PI */
    while (*rty_n_ang >= 6.28318548F)
    {
        /* '<S18>:1:9' n_ang = n_ang - TWO_PI; */
        *rty_n_ang -= 6.28318548F;
    }
}

/* System initialize for referenced model: 'sim_plant' */
void sim_plant_Init(sim_plant_DW_f *localDW)
{
    /* InitializeConditions for UniformRandomNumber: '<S3>/Uniform Random Number' */
    localDW->RandSeed = 1144108930U;
    localDW->UniformRandomNumber_NextOutput = rt_urand_Upu32_Yd_f_pw
        (&localDW->RandSeed) * 2.0 - 1.0;

    /* InitializeConditions for UniformRandomNumber: '<S2>/Uniform Random Number1' */
    localDW->RandSeed_o = 262144U;
    localDW->UniformRandomNumber1_NextOutput = rt_urand_Upu32_Yd_f_pw
        (&localDW->RandSeed_o) * 2.0 - 1.0;

    /* SystemInitialize for Atomic SubSystem: '<S5>/Subsystem' */
    /* InitializeConditions for UniformRandomNumber: '<S10>/Uniform Random Number' */
    localDW->RandSeed_i = 65536U;
    localDW->UniformRandomNumber_NextOutput_o = rt_urand_Upu32_Yd_f_pw
        (&localDW->RandSeed_i) * 2.0 - 1.0;

    /* End of SystemInitialize for SubSystem: '<S5>/Subsystem' */

    /* SystemInitialize for Atomic SubSystem: '<S5>/Subsystem1' */
    /* InitializeConditions for UniformRandomNumber: '<S11>/Uniform Random Number' */
    localDW->RandSeed_l = 131072U;
    localDW->UniformRandomNumber_NextOutput_j = rt_urand_Upu32_Yd_f_pw
        (&localDW->RandSeed_l) * 2.0 - 1.0;

    /* End of SystemInitialize for SubSystem: '<S5>/Subsystem1' */

    /* SystemInitialize for Atomic SubSystem: '<S5>/Subsystem2' */
    /* InitializeConditions for UniformRandomNumber: '<S12>/Uniform Random Number' */
    localDW->RandSeed_n = 196608U;
    localDW->UniformRandomNumber_NextOutput_a = rt_urand_Upu32_Yd_f_pw
        (&localDW->RandSeed_n) * 2.0 - 1.0;

    /* End of SystemInitialize for SubSystem: '<S5>/Subsystem2' */
}

/* Output and update for referenced model: 'sim_plant' */
void sim_plant(const SimPlantInput *rtu_input, const SimPlantConfig *rtu_config,
               SimPlantOutput *rty_output, sim_plant_DW_f *localDW)
{
    int32_T rtb_A;
    int32_T rtb_B;
    int32_T rtb_C;
    real32_T rtb_Add6;
    real32_T rtb_Add7;
    real32_T rtb_Add8;
    real32_T rtb_Add_c;
    real32_T rtb_Add_h;
    real32_T rtb_Add_k;
    real32_T rtb_n_ang;
    real32_T rtb_n_ang_c;
    real32_T rtb_n_ang_d;
    real32_T sita;

    /* Product: '<S17>/Product8' incorporates:
     *  Delay: '<S17>/wm_now_last_delay'
     *  Product: '<S17>/Product12'
     */
    rtb_Add7 = localDW->wm_now_last * rtu_config->pn;

    /* Sum: '<S17>/Add6' incorporates:
     *  Delay: '<S17>/id_now_last_delay'
     *  Delay: '<S17>/iq_now_last_delay'
     *  Delay: '<S6>/elec_angle_last_delay'
     *  Fcn: '<S14>/d'
     *  Gain: '<S14>/Gain1'
     *  Product: '<S17>/Product'
     *  Product: '<S17>/Product4'
     *  Product: '<S17>/Product5'
     *  Product: '<S17>/Product6'
     *  Product: '<S17>/Product7'
     *  Product: '<S17>/Product8'
     *  Sum: '<S17>/Add'
     */
    rtb_Add6 = ((((yuanhub_sin_f32((localDW->elec_angle_last + 1.57079637F) -
                    2.09439516F) * rtu_input->uabc_tar_V[1] + yuanhub_sin_f32
                   (localDW->elec_angle_last + 1.57079637F) *
                   rtu_input->uabc_tar_V[0]) + yuanhub_sin_f32
                  ((localDW->elec_angle_last + 1.57079637F) + 2.09439516F) *
                  rtu_input->uabc_tar_V[2]) * 0.666666687F + rtu_config->lq *
                 localDW->iq_now_last * rtb_Add7) - localDW->id_now_last *
                rtu_config->r) * rtu_config->ld_inv * rtu_config->dt_s +
        localDW->id_now_last;

    /* Sum: '<S17>/Add7' incorporates:
     *  Delay: '<S17>/id_now_last_delay'
     *  Delay: '<S17>/iq_now_last_delay'
     *  Delay: '<S6>/elec_angle_last_delay'
     *  Fcn: '<S14>/q'
     *  Gain: '<S14>/Gain1'
     *  Product: '<S17>/Product1'
     *  Product: '<S17>/Product10'
     *  Product: '<S17>/Product11'
     *  Product: '<S17>/Product13'
     *  Product: '<S17>/Product9'
     *  Sum: '<S17>/Add1'
     *  Sum: '<S17>/Add2'
     */
    rtb_Add7 = ((((yuanhub_cos_f32((localDW->elec_angle_last + 1.57079637F) -
                    2.09439516F) * rtu_input->uabc_tar_V[1] + yuanhub_cos_f32
                   (localDW->elec_angle_last + 1.57079637F) *
                   rtu_input->uabc_tar_V[0]) + yuanhub_cos_f32
                  ((localDW->elec_angle_last + 1.57079637F) + 2.09439516F) *
                  rtu_input->uabc_tar_V[2]) * 0.666666687F -
                 (localDW->id_now_last * rtu_config->ld + rtu_config->flux) *
                 rtb_Add7) - localDW->iq_now_last * rtu_config->r) *
        rtu_config->lq_inv * rtu_config->dt_s + localDW->iq_now_last;

    /* Product: '<S17>/Product17' incorporates:
     *  Delay: '<S17>/wm_now_last_delay'
     */
    rtb_n_ang_c = localDW->wm_now_last * rtu_config->b;

    /* Signum: '<S17>/Sign' incorporates:
     *  Delay: '<S17>/wm_now_last_delay'
     */
    if (localDW->wm_now_last < 0.0F)
    {
        rtb_n_ang_d = -1.0F;
    }
    else
    {
        rtb_n_ang_d = (real32_T)(localDW->wm_now_last > 0.0F);
    }

    /* Sum: '<S17>/Add8' incorporates:
     *  Delay: '<S17>/wm_now_last_delay'
     *  Gain: '<S17>/Gain7'
     *  Product: '<S17>/Product14'
     *  Product: '<S17>/Product15'
     *  Product: '<S17>/Product16'
     *  Product: '<S17>/Product18'
     *  Product: '<S17>/Product2'
     *  Product: '<S17>/Product3'
     *  Signum: '<S17>/Sign'
     *  Sum: '<S17>/Add3'
     *  Sum: '<S17>/Add4'
     *  Sum: '<S17>/Add5'
     */
    rtb_Add8 = (((((rtu_config->ld - rtu_config->lq) * rtb_Add6 +
                   rtu_config->flux) * (1.5F * rtb_Add7 * rtu_config->pn) -
                  rtu_input->tl_Nm) - rtb_n_ang_d * rtu_config->fc) -
                rtb_n_ang_c) * rtu_config->j_inv * rtu_config->dt_s +
        localDW->wm_now_last;

    /* MATLAB Function: '<S15>/mod2pi_fun' incorporates:
     *  Delay: '<S15>/pos_last_delay'
     *  Product: '<S15>/Product'
     *  Sum: '<S15>/Add'
     */
    sim_plant_mod2pi_fun(rtb_Add8 * rtu_config->dt_s + localDW->pos_last,
                         &rtb_n_ang_d);

    /* MATLAB Function: '<S6>/mod2pi_fun' incorporates:
     *  Product: '<S6>/Product'
     */
    sim_plant_mod2pi_fun(rtu_config->pn * rtb_n_ang_d, &rtb_n_ang_c);

    /* Outputs for Atomic SubSystem: '<S5>/Subsystem' */
    /* Sum: '<S10>/Add' incorporates:
     *  Constant: '<S5>/i_noise_A'
     *  DataTypeConversion: '<S10>/Data Type Conversion1'
     *  Fcn: '<S13>/a'
     *  Product: '<S10>/Product'
     *  UniformRandomNumber: '<S10>/Uniform Random Number'
     */
    rtb_Add_k = (yuanhub_sin_f32(rtb_n_ang_c + 1.57079637F) * rtb_Add6 +
                 yuanhub_cos_f32(rtb_n_ang_c + 1.57079637F) * rtb_Add7) + 0.05F *
        (real32_T)localDW->UniformRandomNumber_NextOutput_o;

    /* Update for UniformRandomNumber: '<S10>/Uniform Random Number' */
    localDW->UniformRandomNumber_NextOutput_o = rt_urand_Upu32_Yd_f_pw
        (&localDW->RandSeed_i) * 2.0 - 1.0;

    /* End of Outputs for SubSystem: '<S5>/Subsystem' */

    /* Outputs for Atomic SubSystem: '<S5>/Subsystem1' */
    /* Sum: '<S11>/Add' incorporates:
     *  Constant: '<S5>/i_noise_A'
     *  DataTypeConversion: '<S11>/Data Type Conversion1'
     *  Fcn: '<S13>/b'
     *  Product: '<S11>/Product'
     *  UniformRandomNumber: '<S11>/Uniform Random Number'
     */
    rtb_Add_h = (yuanhub_sin_f32((rtb_n_ang_c + 1.57079637F) - 2.09439516F) *
                 rtb_Add6 + yuanhub_cos_f32((rtb_n_ang_c + 1.57079637F) -
                  2.09439516F) * rtb_Add7) + 0.05F * (real32_T)
        localDW->UniformRandomNumber_NextOutput_j;

    /* Update for UniformRandomNumber: '<S11>/Uniform Random Number' */
    localDW->UniformRandomNumber_NextOutput_j = rt_urand_Upu32_Yd_f_pw
        (&localDW->RandSeed_l) * 2.0 - 1.0;

    /* End of Outputs for SubSystem: '<S5>/Subsystem1' */

    /* Outputs for Atomic SubSystem: '<S5>/Subsystem2' */
    /* Sum: '<S12>/Add' incorporates:
     *  Constant: '<S5>/i_noise_A'
     *  DataTypeConversion: '<S12>/Data Type Conversion1'
     *  Fcn: '<S13>/c'
     *  Product: '<S12>/Product'
     *  UniformRandomNumber: '<S12>/Uniform Random Number'
     */
    rtb_Add_c = (yuanhub_sin_f32((rtb_n_ang_c + 1.57079637F) + 2.09439516F) *
                 rtb_Add6 + yuanhub_cos_f32((rtb_n_ang_c + 1.57079637F) +
                  2.09439516F) * rtb_Add7) + 0.05F * (real32_T)
        localDW->UniformRandomNumber_NextOutput_a;

    /* Update for UniformRandomNumber: '<S12>/Uniform Random Number' */
    localDW->UniformRandomNumber_NextOutput_a = rt_urand_Upu32_Yd_f_pw
        (&localDW->RandSeed_n) * 2.0 - 1.0;

    /* End of Outputs for SubSystem: '<S5>/Subsystem2' */

    /* MATLAB Function: '<S3>/mod2pi_fun' incorporates:
     *  DataTypeConversion: '<S3>/Data Type Conversion'
     *  DataTypeConversion: '<S3>/Data Type Conversion1'
     *  Gain: '<S3>/Gain1'
     *  Product: '<S3>/Divide'
     *  Product: '<S3>/Product'
     *  Sum: '<S3>/Add1'
     *  UniformRandomNumber: '<S3>/Uniform Random Number'
     */
    /*  将角度限制在0到2π范围内 */
    /* MATLAB Function 'fast_math/mod2pi_fun': '<S8>:1' */
    /* '<S8>:1:3' TWO_PI = single(2*pi); */
    /* '<S8>:1:4' n_ang = single(ang); */
    /* '<S8>:1:5' while n_ang < 0 */
    for (rtb_n_ang = rtu_config->enc_noise * (real32_T)
            localDW->UniformRandomNumber_NextOutput / (real32_T)
            rtu_config->enc_line_p_n * 6.28318548F + rtb_n_ang_d; rtb_n_ang <
            0.0F; rtb_n_ang += 6.28318548F)
    {
        /* '<S8>:1:6' n_ang = n_ang + TWO_PI; */
    }

    /* '<S8>:1:8' while n_ang >= TWO_PI */
    while (rtb_n_ang >= 6.28318548F)
    {
        /* '<S8>:1:9' n_ang = n_ang - TWO_PI; */
        rtb_n_ang -= 6.28318548F;
    }

    /* End of MATLAB Function: '<S3>/mod2pi_fun' */

    /* MATLAB Function: '<S4>/hall_clc' */
    /* MATLAB Function 'sim_plant/hall_sensor/hall_clc': '<S9>:1' */
    /* '<S9>:1:2' sita = u*360/(2*pi); */
    sita = rtb_n_ang_c * 360.0F / 6.28318548F;

    /* '<S9>:1:4' if (sita>=0 && sita<30) || (sita>=330 && sita<=360) */
    if (((sita >= 0.0F) && (sita < 30.0F)) || ((sita >= 330.0F) && (sita <=
            360.0F)))
    {
        /* '<S9>:1:5' A = 1; */
        rtb_A = 1;

        /* '<S9>:1:6' B = 1; */
        rtb_B = 1;

        /* '<S9>:1:7' C = 0; */
        rtb_C = 0;
    }
    else if ((sita >= 30.0F) && (sita < 90.0F))
    {
        /* '<S9>:1:8' elseif sita>=30 && sita<90 */
        /* '<S9>:1:9' A = 0; */
        rtb_A = 0;

        /* '<S9>:1:10' B = 1; */
        rtb_B = 1;

        /* '<S9>:1:11' C = 0; */
        rtb_C = 0;
    }
    else if ((sita >= 90.0F) && (sita < 150.0F))
    {
        /* '<S9>:1:12' elseif sita >=90 && sita <150 */
        /* '<S9>:1:13' A = 0; */
        rtb_A = 0;

        /* '<S9>:1:14' B = 1; */
        rtb_B = 1;

        /* '<S9>:1:15' C = 1; */
        rtb_C = 1;
    }
    else if ((sita >= 150.0F) && (sita < 210.0F))
    {
        /* '<S9>:1:16' elseif sita >=150 && sita <210 */
        /* '<S9>:1:17' A = 0; */
        rtb_A = 0;

        /* '<S9>:1:18' B = 0; */
        rtb_B = 0;

        /* '<S9>:1:19' C = 1; */
        rtb_C = 1;
    }
    else if ((sita >= 210.0F) && (sita < 270.0F))
    {
        /* '<S9>:1:20' elseif sita >=210 && sita <270 */
        /* '<S9>:1:21' A = 1; */
        rtb_A = 1;

        /* '<S9>:1:22' B = 0; */
        rtb_B = 0;

        /* '<S9>:1:23' C = 1; */
        rtb_C = 1;
    }
    else if ((sita >= 270.0F) && (sita < 330.0F))
    {
        /* '<S9>:1:24' elseif sita >=270 && sita <330 */
        /* '<S9>:1:25' A = 1; */
        rtb_A = 1;

        /* '<S9>:1:26' B = 0; */
        rtb_B = 0;

        /* '<S9>:1:27' C = 0; */
        rtb_C = 0;
    }
    else
    {
        /* '<S9>:1:28' else */
        /* '<S9>:1:29' A = 0; */
        rtb_A = 0;

        /* '<S9>:1:30' B = 0; */
        rtb_B = 0;

        /* '<S9>:1:31' C = 0; */
        rtb_C = 0;
    }

    /* End of MATLAB Function: '<S4>/hall_clc' */

    /* Sum: '<S4>/Add' incorporates:
     *  Gain: '<S4>/Gain'
     *  Gain: '<S4>/Gain1'
     *  Gain: '<S4>/Gain2'
     */
    rty_output->hall_state = (uint8_T)(((uint32_T)(rtb_B << 1) + (uint32_T)rtb_A)
        + (uint32_T)(rtb_C << 2));

    /* Sum: '<S2>/Add' incorporates:
     *  Constant: '<S2>/dc_voltage_base'
     *  DataTypeConversion: '<S2>/Data Type Conversion1'
     *  Gain: '<S2>/dc_bus_noise_V'
     *  UniformRandomNumber: '<S2>/Uniform Random Number1'
     */
    rty_output->dc_bus_V = 0.1F * (real32_T)
        localDW->UniformRandomNumber1_NextOutput + 48.0F;

    /* BusCreator: '<S1>/Bus Creator' incorporates:
     *  SignalConversion generated from: '<S1>/Bus Creator'
     */
    rty_output->iabc_now_A[0] = rtb_Add_k;
    rty_output->iabc_now_A[1] = rtb_Add_h;
    rty_output->iabc_now_A[2] = rtb_Add_c;

    /* Math: '<S7>/Mod1' */
    if (rtu_config->enc_line_p_n == 0U)
    {
        /* BusCreator: '<S1>/Bus Creator' incorporates:
         *  DataTypeConversion: '<S7>/Data Type Conversion'
         *  Gain: '<S7>/enc_counts_tf'
         *  Product: '<S7>/Product'
         */
        rty_output->enc_counts_P = (uint32_T)(0.159154937F * rtb_n_ang *
            (real32_T)rtu_config->enc_line_p_n);
    }
    else
    {
        /* BusCreator: '<S1>/Bus Creator' incorporates:
         *  DataTypeConversion: '<S7>/Data Type Conversion'
         *  Gain: '<S7>/enc_counts_tf'
         *  Product: '<S7>/Product'
         */
        rty_output->enc_counts_P = (uint32_T)(0.159154937F * rtb_n_ang *
            (real32_T)rtu_config->enc_line_p_n) % rtu_config->enc_line_p_n;
    }

    /* End of Math: '<S7>/Mod1' */

    /* Update for Delay: '<S6>/elec_angle_last_delay' */
    localDW->elec_angle_last = rtb_n_ang_c;

    /* Update for Delay: '<S17>/id_now_last_delay' */
    localDW->id_now_last = rtb_Add6;

    /* Update for Delay: '<S17>/iq_now_last_delay' */
    localDW->iq_now_last = rtb_Add7;

    /* Update for Delay: '<S17>/wm_now_last_delay' */
    localDW->wm_now_last = rtb_Add8;

    /* Update for Delay: '<S15>/pos_last_delay' */
    localDW->pos_last = rtb_n_ang_d;

    /* Update for UniformRandomNumber: '<S3>/Uniform Random Number' */
    localDW->UniformRandomNumber_NextOutput = rt_urand_Upu32_Yd_f_pw
        (&localDW->RandSeed) * 2.0 - 1.0;

    /* Update for UniformRandomNumber: '<S2>/Uniform Random Number1' */
    localDW->UniformRandomNumber1_NextOutput = rt_urand_Upu32_Yd_f_pw
        (&localDW->RandSeed_o) * 2.0 - 1.0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
