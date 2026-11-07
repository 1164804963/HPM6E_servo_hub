/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: direction_id.c
 *
 * Code generated for Simulink model 'direction_id'.
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

#include "direction_id.h"
#include "servo_hub_database_type.h"
#include "rtwtypes.h"
#include "zero_crossing_types.h"

/* System initialize for referenced model: 'direction_id' */
void direction_id_Init(direction_id_DW_f *localDW, direction_id_ZCE *localZCE)
{
    /* Outputs for Atomic SubSystem: '<S1>/Initialize Function' */
    /* StateWriter: '<S3>/State Writer' incorporates:
     *  Constant: '<S3>/Constant1'
     */
    localDW->elec_angle_tar_last = 0.0F;

    /* StateWriter: '<S3>/State Writer1' incorporates:
     *  Constant: '<S3>/Constant2'
     */
    localDW->step_num = 0U;

    /* StateWriter: '<S3>/State Writer3' incorporates:
     *  Constant: '<S3>/Constant4'
     */
    localDW->state_now = 0;

    /* StateWriter: '<S3>/State Writer4' incorporates:
     *  Constant: '<S3>/Constant5'
     */
    localZCE->Subsystem_Trig_ZCE = 0U;

    /* End of Outputs for SubSystem: '<S1>/Initialize Function' */
}

/* Output and update for referenced model: 'direction_id' */
void direction_id(const DirectionIdInput *rtu_input, const DirectionIdConfig
                  *rtu_config, DirectionIdOutput *rty_Out1, direction_id_DW_f
                  *localDW, direction_id_ZCE *localZCE)
{
    real32_T rtb_n_ang;
    boolean_T rtb_RelationalOperator;

    /* MATLAB Function: '<S1>/mod2pi_fun' incorporates:
     *  Delay: '<S1>/Delay'
     *  Sum: '<S1>/Add'
     */
    /*  将角度限制在0到2π范围内 */
    /* MATLAB Function 'direction_id/mod2pi_fun': '<S5>:1' */
    /* '<S5>:1:3' TWO_PI = single(2*pi); */
    /* '<S5>:1:4' n_ang = single(ang); */
    /* '<S5>:1:5' while n_ang < 0 */
    for (rtb_n_ang = rtu_config->elec_angle_add_rad +
            localDW->elec_angle_tar_last; rtb_n_ang < 0.0F; rtb_n_ang +=
            6.28318548F)
    {
        /* '<S5>:1:6' n_ang = n_ang + TWO_PI; */
    }

    /* '<S5>:1:8' while n_ang >= TWO_PI */
    while (rtb_n_ang >= 6.28318548F)
    {
        /* '<S5>:1:9' n_ang = n_ang - TWO_PI; */
        rtb_n_ang -= 6.28318548F;
    }

    /* End of MATLAB Function: '<S1>/mod2pi_fun' */

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
    rtb_RelationalOperator = (rtb_n_ang - localDW->UD_DSTATE_b <=
        -1.5707963267948966);

    /* Outputs for Triggered SubSystem: '<S1>/Subsystem' incorporates:
     *  TriggerPort: '<S4>/Trigger'
     */
    if (rtb_RelationalOperator && (localZCE->Subsystem_Trig_ZCE != POS_ZCSIG))
    {
        int64_T rtb_Switch2;

        /* Switch: '<S4>/Switch2' incorporates:
         *  Constant: '<S4>/Constant'
         *  Constant: '<S4>/Constant1'
         *  Delay: '<S4>/Delay2'
         *  Sum: '<S4>/Add1'
         *  Sum: '<S6>/Diff'
         *  UnitDelay: '<S6>/UD'
         *
         * Block description for '<S6>/Diff':
         *
         *  Add in CPU
         *
         * Block description for '<S6>/UD':
         *
         *  Store in Global RAM
         */
        if ((uint8_T)(localDW->step_num + 1U) > 1)
        {
            rtb_Switch2 = rtu_input->enc_counts_sum_p - localDW->UD_DSTATE;
        }
        else
        {
            rtb_Switch2 = 0LL;
        }

        /* End of Switch: '<S4>/Switch2' */

        /* MATLAB Function: '<S4>/MATLAB Function' incorporates:
         *  Switch: '<S4>/Switch2'
         */
        /* MATLAB Function 'direction_id/Subsystem/MATLAB Function': '<S7>:1' */
        /* '<S7>:1:3' if diff_pos > int64(0) */
        if (rtb_Switch2 > 0LL)
        {
            /* '<S7>:1:4' direction = int8(1); */
            localDW->direction = 1;

            /* '<S7>:1:5' state_now = int8(3); */
            localDW->state_now = 3;
        }
        else if (rtb_Switch2 < 0LL)
        {
            /* '<S7>:1:6' elseif diff_pos < int64(0) */
            /* '<S7>:1:7' direction = int8(-1); */
            localDW->direction = -1;

            /* '<S7>:1:8' state_now = int8(3); */
            localDW->state_now = 3;
        }
        else
        {
            /* '<S7>:1:9' else */
            /* '<S7>:1:10' direction = int8(0); */
            localDW->direction = 0;

            /* '<S7>:1:11' state_now = int8(2); */
            localDW->state_now = 2;
        }

        /* End of MATLAB Function: '<S4>/MATLAB Function' */

        /* Update for Delay: '<S4>/Delay2' incorporates:
         *  Constant: '<S4>/Constant'
         *  Sum: '<S4>/Add1'
         */
        localDW->step_num++;

        /* Update for UnitDelay: '<S6>/UD'
         *
         * Block description for '<S6>/UD':
         *
         *  Store in Global RAM
         */
        localDW->UD_DSTATE = rtu_input->enc_counts_sum_p;
    }

    localZCE->Subsystem_Trig_ZCE = rtb_RelationalOperator;

    /* End of Outputs for SubSystem: '<S1>/Subsystem' */

    /* BusCreator: '<S1>/Bus Creator' incorporates:
     *  Constant: '<S1>/id_tar'
     */
    rty_Out1->elec_angle_tar_rad = rtb_n_ang;
    rty_Out1->direction = localDW->direction;
    rty_Out1->state_now = localDW->state_now;
    rty_Out1->id_tar_A = 0.0F;

    /* Update for Delay: '<S1>/Delay' */
    localDW->elec_angle_tar_last = rtb_n_ang;

    /* Update for UnitDelay: '<S2>/UD'
     *
     * Block description for '<S2>/UD':
     *
     *  Store in Global RAM
     */
    localDW->UD_DSTATE_b = rtb_n_ang;
}

/* Model initialize function */
void direction_id_initialize(direction_id_ZCE *localZCE)
{
    localZCE->Subsystem_Trig_ZCE = POS_ZCSIG;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
