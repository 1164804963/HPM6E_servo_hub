/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: linear_trajectory_planning.c
 *
 * Code generated for Simulink model 'linear_trajectory_planning'.
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

#include "linear_trajectory_planning.h"
#include "rtwtypes.h"

/* Output and update for referenced model: 'linear_trajectory_planning' */
void linear_trajectory_planning(const real32_T *rtu_traj_cmd, const real32_T
    *rtu_slope, const real32_T *rtu_dt_s, real32_T *rty_traj_out, int8_T
    *rty_state_now, linear_trajectory_planning_DW_f *localDW)
{
    real32_T traj_last_temp;

    /* MATLAB Function: '<Root>/linear_trajectory_planning' incorporates:
     *  DataStoreRead: '<Root>/Data Store Read'
     */
    /*  state_now  规划状态   */
    /*  0 初始状态 */
    /*  1 规划完成 */
    /*  2 规划中 */
    /* MATLAB Function 'linear_trajectory_planning': '<S1>:1' */
    /* '<S1>:1:8' traj_last_temp = single(0); */
    /* '<S1>:1:9' state_now_temp = int8(0); */
    /* '<S1>:1:11' if traj_now > traj_cmd */
    if (localDW->traj_now > *rtu_traj_cmd)
    {
        /* '<S1>:1:12' traj_last_temp = traj_now - slope * dt_s; */
        traj_last_temp = localDW->traj_now - *rtu_slope * *rtu_dt_s;

        /* '<S1>:1:13' state_now_temp = int8(2); */
        *rty_state_now = 2;

        /* '<S1>:1:14' if traj_last_temp < traj_cmd */
        if (traj_last_temp < *rtu_traj_cmd)
        {
            /* '<S1>:1:15' traj_last_temp = traj_cmd; */
            traj_last_temp = *rtu_traj_cmd;

            /* '<S1>:1:16' state_now_temp = int8(1); */
            *rty_state_now = 1;
        }
    }
    else
    {
        /* '<S1>:1:18' else */
        /* '<S1>:1:19' traj_last_temp = traj_now + slope * dt_s; */
        traj_last_temp = *rtu_slope * *rtu_dt_s + localDW->traj_now;

        /* '<S1>:1:20' state_now_temp = int8(2); */
        *rty_state_now = 2;

        /* '<S1>:1:21' if traj_last_temp > traj_cmd */
        if (traj_last_temp > *rtu_traj_cmd)
        {
            /* '<S1>:1:22' traj_last_temp = traj_cmd; */
            traj_last_temp = *rtu_traj_cmd;

            /* '<S1>:1:23' state_now_temp = int8(1); */
            *rty_state_now = 1;
        }
    }

    /* '<S1>:1:28' traj_last = traj_last_temp; */
    *rty_traj_out = traj_last_temp;

    /* End of MATLAB Function: '<Root>/linear_trajectory_planning' */

    /* DataStoreWrite: '<Root>/Data Store Write' */
    /* '<S1>:1:29' state_now = state_now_temp; */
    localDW->traj_now = *rty_traj_out;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
