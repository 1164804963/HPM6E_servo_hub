/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: pole_pairs_id.c
 *
 * Code generated for Simulink model 'pole_pairs_id'.
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

#include "pole_pairs_id.h"
#include "servo_hub_database_type.h"
#include <math.h>
#include "rtwtypes.h"
#include "zero_crossing_types.h"

/* System initialize for referenced model: 'pole_pairs_id' */
void pole_pairs_id_Init(pole_pairs_id_DW_f *localDW, pole_pairs_id_ZCE *localZCE)
{
    /* Outputs for Atomic SubSystem: '<S1>/Initialize Function' */
    /* StateWriter: '<S3>/State Writer' incorporates:
     *  Constant: '<S3>/Constant1'
     */
    localDW->elec_angle_tar_last = 0.0F;

    /* StateWriter: '<S3>/State Writer3' incorporates:
     *  Constant: '<S3>/Constant4'
     */
    localZCE->pn_clc_Trig_ZCE = 0U;

    /* StateWriter: '<S3>/State Writer4' incorporates:
     *  Constant: '<S3>/Constant5'
     */
    localDW->pn = 0U;

    /* StateWriter: '<S3>/State Writer5' incorporates:
     *  Constant: '<S3>/Constant6'
     */
    localDW->pn_sum = 0U;

    /* StateWriter: '<S3>/State Writer6' incorporates:
     *  Constant: '<S3>/Constant7'
     */
    localDW->step_num = 0U;

    /* End of Outputs for SubSystem: '<S1>/Initialize Function' */
}

/* Output and update for referenced model: 'pole_pairs_id' */
void pole_pairs_id(const PolePairsIdInput *rtu_input, const PolePairsIdConfig
                   *rtu_config, PolePairsIdOutput *rty_output,
                   pole_pairs_id_DW_f *localDW, pole_pairs_id_ZCE *localZCE)
{
    real32_T rtb_n_ang;
    boolean_T rtb_RelationalOperator;

    /* MATLAB Function: '<S1>/mod2pi_fun1' incorporates:
     *  Delay: '<S1>/Delay'
     *  Sum: '<S1>/Add'
     */
    /*  将角度限制在0到2π范围内 */
    /* MATLAB Function 'pole_pairs_id/mod2pi_fun1': '<S4>:1' */
    /* '<S4>:1:3' TWO_PI = single(2*pi); */
    /* '<S4>:1:4' n_ang = single(ang); */
    /* '<S4>:1:5' while n_ang < 0 */
    for (rtb_n_ang = rtu_config->elec_angle_add + localDW->elec_angle_tar_last;
            rtb_n_ang < 0.0F; rtb_n_ang += 6.28318548F)
    {
        /* '<S4>:1:6' n_ang = n_ang + TWO_PI; */
    }

    /* '<S4>:1:8' while n_ang >= TWO_PI */
    while (rtb_n_ang >= 6.28318548F)
    {
        /* '<S4>:1:9' n_ang = n_ang - TWO_PI; */
        rtb_n_ang -= 6.28318548F;
    }

    /* End of MATLAB Function: '<S1>/mod2pi_fun1' */

    /* RelationalOperator: '<S1>/Relational Operator' incorporates:
     *  Constant: '<S1>/Constant5'
     *  Sum: '<S2>/Diff'
     *  UnitDelay: '<S2>/UD'
     *
     * Block description for '<S2>/Diff':
     *
     *  Add in CPU
     *
     * Block description for '<S2>/UD':
     *
     *  Store in Global RAM
     */
    rtb_RelationalOperator = (rtb_n_ang - localDW->UD_DSTATE_j <=
        -1.5707963267948966);

    /* Outputs for Triggered SubSystem: '<S1>/pn_clc' incorporates:
     *  TriggerPort: '<S5>/Trigger'
     */
    if (rtb_RelationalOperator && (localZCE->pn_clc_Trig_ZCE != POS_ZCSIG))
    {
        int64_T rtb_Diff;

        /* Sum: '<S7>/Diff' incorporates:
         *  UnitDelay: '<S7>/UD'
         *
         * Block description for '<S7>/Diff':
         *
         *  Add in CPU
         *
         * Block description for '<S7>/UD':
         *
         *  Store in Global RAM
         */
        rtb_Diff = rtu_input->enc_counts_sum_p - localDW->UD_DSTATE;

        /* MATLAB Function: '<S5>/MATLAB Function' incorporates:
         *  DataTypeConversion: '<S5>/Data Type Conversion'
         *  Sum: '<S7>/Diff'
         *
         * Block description for '<S7>/Diff':
         *
         *  Add in CPU
         */
        /* MATLAB Function 'pole_pairs_id/pn_clc/MATLAB Function': '<S8>:1' */
        /* '<S8>:1:3' if diff_pos ~= 0 */
        if (rtb_Diff != 0.0F)
        {
            real32_T tmp;

            /* '<S8>:1:4' pn = uint32(round(single(enc_line) / diff_pos)); */
            tmp = roundf((real32_T)rtu_config->enc_line_p_n / (real32_T)rtb_Diff);
            if (tmp < 4.2949673E+9F)
            {
                if (tmp >= 0.0F)
                {
                    localDW->pn = (uint32_T)tmp;
                }
                else
                {
                    localDW->pn = 0U;
                }
            }
            else
            {
                localDW->pn = MAX_uint32_T;
            }
        }
        else
        {
            /* '<S8>:1:5' else */
            /* '<S8>:1:6' pn = uint32(1); */
            localDW->pn = 1U;
        }

        /* End of MATLAB Function: '<S5>/MATLAB Function' */

        /* Update for UnitDelay: '<S7>/UD'
         *
         * Block description for '<S7>/UD':
         *
         *  Store in Global RAM
         */
        localDW->UD_DSTATE = rtu_input->enc_counts_sum_p;
    }

    localZCE->pn_clc_Trig_ZCE = rtb_RelationalOperator;

    /* End of Outputs for SubSystem: '<S1>/pn_clc' */

    /* Outputs for Triggered SubSystem: '<S1>/state_update' incorporates:
     *  TriggerPort: '<S6>/Trigger'
     */
    if (rtb_RelationalOperator && (localZCE->state_update_Trig_ZCE != POS_ZCSIG))
    {
        uint32_T rtb_Add;

        /* Switch: '<S6>/Switch2' incorporates:
         *  Constant: '<S6>/Constant'
         *  Constant: '<S6>/Constant3'
         *  Delay: '<S6>/Delay2'
         *  Sum: '<S6>/Add1'
         */
        if (localDW->step_num + 1U > 1U)
        {
            rtb_Add = localDW->pn;
        }
        else
        {
            rtb_Add = 0U;
        }

        /* Sum: '<S6>/Add' incorporates:
         *  Delay: '<S6>/Delay'
         *  Switch: '<S6>/Switch2'
         */
        rtb_Add += localDW->pn_sum;

        /* Switch: '<S6>/Switch1' incorporates:
         *  Constant: '<S6>/Constant'
         *  Constant: '<S6>/Constant1'
         *  Constant: '<S6>/Constant2'
         *  Constant: '<S6>/Constant5'
         *  DataTypeConversion: '<S6>/Data Type Conversion'
         *  DataTypeConversion: '<S6>/Data Type Conversion1'
         *  DataTypeConversion: '<S6>/Data Type Conversion2'
         *  Delay: '<S6>/Delay2'
         *  Product: '<S6>/Divide'
         *  Sum: '<S6>/Add1'
         *  Sum: '<S6>/Add2'
         *  Switch: '<S6>/Switch'
         */
        if (localDW->step_num + 1U > 4U)
        {
            rty_output->pn_id = (uint32_T)roundf((real32_T)rtb_Add / ((real32_T)
                (localDW->step_num + 1U) - 1.0F));
            rty_output->state_now = 3;
        }
        else
        {
            rty_output->pn_id = rtb_Add;
            rty_output->state_now = 2;
        }

        /* End of Switch: '<S6>/Switch1' */

        /* Update for Delay: '<S6>/Delay2' incorporates:
         *  Constant: '<S6>/Constant'
         *  Sum: '<S6>/Add1'
         */
        localDW->step_num++;

        /* Update for Delay: '<S6>/Delay' */
        localDW->pn_sum = rtb_Add;
    }

    /* Outputs for Triggered SubSystem: '<S1>/pn_clc' incorporates:
     *  TriggerPort: '<S5>/Trigger'
     */
    localZCE->state_update_Trig_ZCE = rtb_RelationalOperator;

    /* End of Outputs for SubSystem: '<S1>/pn_clc' */
    /* End of Outputs for SubSystem: '<S1>/state_update' */

    /* BusCreator: '<S1>/Bus Creator' */
    rty_output->elec_angle_tar_rad = rtb_n_ang;
    rty_output->id_tar_A = rtu_config->id_tar_max_A;

    /* Update for Delay: '<S1>/Delay' */
    localDW->elec_angle_tar_last = rtb_n_ang;

    /* Update for UnitDelay: '<S2>/UD'
     *
     * Block description for '<S2>/UD':
     *
     *  Store in Global RAM
     */
    localDW->UD_DSTATE_j = rtb_n_ang;
}

/* Model initialize function */
void pole_pairs_id_initialize(pole_pairs_id_ZCE *localZCE)
{
    localZCE->pn_clc_Trig_ZCE = POS_ZCSIG;
    localZCE->state_update_Trig_ZCE = POS_ZCSIG;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
