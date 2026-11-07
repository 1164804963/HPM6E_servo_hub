/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: input_shaping_ei.c
 *
 * Code generated for Simulink model 'input_shaping_ei'.
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

#include "input_shaping_ei.h"
#include "servo_hub_database_type.h"
#include "rtwtypes.h"

/* System initialize for referenced model: 'input_shaping_ei' */
void input_shaping_ei_Init(input_shaping_ei_DW_f *localDW)
{
    /* InitializeConditions for Delay: '<S1>/Delay' */
    localDW->icLoad = true;

    /* InitializeConditions for Delay: '<S1>/Delay1' */
    localDW->icLoad_o = true;
}

/* Output and update for referenced model: 'input_shaping_ei' */
void input_shaping_ei(const InputShapingInput *rtu_input, const
                      InputShapingConfig *rtu_config, InputShapingOutput
                      *rty_output, input_shaping_ei_DW_f *localDW)
{
    int64_T rtb_Delay;
    int64_T rtb_Delay1;
    int32_T i;
    uint32_T rtb_t2_num;
    uint32_T tmp;

    /* DataTypeConversion: '<S1>/Data Type Conversion' incorporates:
     *  Constant: '<S1>/Constant1'
     *  Product: '<S1>/Divide'
     *  Sum: '<S1>/Add'
     */
    rtb_t2_num = (uint32_T)(0.5F / rtu_config->wn_Hz * rtu_config->run_frq_Hz +
                            0.5F);

    /* Delay: '<S1>/Delay' */
    if (localDW->icLoad)
    {
        for (i = 0; i < 500; i++)
        {
            localDW->t2_delay_buffer[i] = rtu_input->pos_cmd_p_init;
        }
    }

    if (rtb_t2_num <= 0U)
    {
        rtb_Delay = rtu_input->pos_cmd_p;
    }
    else
    {
        if (rtb_t2_num > 500U)
        {
            i = 500;
        }
        else
        {
            i = (int32_T)rtb_t2_num;
        }

        if ((uint32_T)i <= localDW->CircBufIdx)
        {
            tmp = localDW->CircBufIdx - (uint32_T)i;
        }
        else
        {
            tmp = (localDW->CircBufIdx - (uint32_T)i) + 500U;
        }

        rtb_Delay = localDW->t2_delay_buffer[tmp];
    }

    /* End of Delay: '<S1>/Delay' */

    /* Delay: '<S1>/Delay1' incorporates:
     *  Delay: '<S1>/Delay'
     */
    if (localDW->icLoad_o)
    {
        for (i = 0; i < 500; i++)
        {
            localDW->t3_delay_buffer[i] = rtu_input->pos_cmd_p_init;
        }
    }

    if (rtb_t2_num <= 0U)
    {
        rtb_Delay1 = rtb_Delay;
    }
    else
    {
        if (rtb_t2_num > 500U)
        {
            i = 500;
        }
        else
        {
            i = (int32_T)rtb_t2_num;
        }

        if ((uint32_T)i <= localDW->CircBufIdx_e)
        {
            tmp = localDW->CircBufIdx_e - (uint32_T)i;
        }
        else
        {
            tmp = (localDW->CircBufIdx_e - (uint32_T)i) + 500U;
        }

        rtb_Delay1 = localDW->t3_delay_buffer[tmp];
    }

    /* End of Delay: '<S1>/Delay1' */

    /* Switch: '<S1>/Switch' incorporates:
     *  ArithShift: '<S1>/Shift Arithmetic'
     *  ArithShift: '<S1>/Shift Arithmetic1'
     *  ArithShift: '<S1>/Shift Arithmetic2'
     *  Delay: '<S1>/Delay'
     *  Delay: '<S1>/Delay1'
     *  Sum: '<S1>/Add2'
     */
    if (rtu_config->enable > 0)
    {
        rty_output->pos_cmd_shaping_p = ((rtu_input->pos_cmd_p >> 2) +
            (rtb_Delay >> 1)) + (rtb_Delay1 >> 2);
    }
    else
    {
        rty_output->pos_cmd_shaping_p = rtu_input->pos_cmd_p;
    }

    /* End of Switch: '<S1>/Switch' */

    /* Update for Delay: '<S1>/Delay' */
    localDW->icLoad = false;
    localDW->t2_delay_buffer[localDW->CircBufIdx] = rtu_input->pos_cmd_p;
    if (localDW->CircBufIdx < 499U)
    {
        localDW->CircBufIdx++;
    }
    else
    {
        localDW->CircBufIdx = 0U;
    }

    /* End of Update for Delay: '<S1>/Delay' */

    /* Update for Delay: '<S1>/Delay1' incorporates:
     *  Delay: '<S1>/Delay'
     */
    localDW->icLoad_o = false;
    localDW->t3_delay_buffer[localDW->CircBufIdx_e] = rtb_Delay;
    if (localDW->CircBufIdx_e < 499U)
    {
        localDW->CircBufIdx_e++;
    }
    else
    {
        localDW->CircBufIdx_e = 0U;
    }

    /* End of Update for Delay: '<S1>/Delay1' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
