/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: servo_hub_example.c
 *
 * Code generated for Simulink model 'servo_hub_example'.
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

#include "servo_hub_example.h"
#include "rtwtypes.h"
#include "direction_id.h"
#include "pole_pairs_id.h"
#include "current_ctl_loop_task.h"
#include "pos_speed_ctl_pip.h"
#include "notch_filter.h"
#include "database_init.h"
#include "motor_pos_sensor.h"
#include "speed_obs_pll.h"
#include "elec_angle_id.h"
#include "pos_trajectory_planning.h"
#include "protect_check.h"
#include "notch_filter_config_set.h"
#include "input_shaping_ei.h"
#include "tq_fc_id.h"
#include "reciprocal_motion.h"
#include "reference_signal.h"
#include "mit_ctl.h"
#include "math_lib.h"
#include "linear_trajectory_planning.h"
#include "load_pos_sensor.h"
#include "sim_plant.h"
#include "csv_planning.h"
#include "cst_planning.h"
#include "csp_planning.h"

/* Block signals and states (default storage) */
DW _rt_DW;

/* External inputs (root inport signals with default storage) */
ExtU _rt_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY _rt_Y;

/* Model step function for TID1 */
void current_ctl_pi_step(void)         /* Explicit Task: current_ctl_pi_step */
{
    /* RootInportFunctionCallGenerator generated from: '<Root>/current_ctl_pi_step' */

    /* ModelReference generated from: '<Root>/current_ctl_loop_task' incorporates:
     *  Inport: '<Root>/current_ctl_config'
     *  Inport: '<Root>/current_ctl_input'
     *  Outport: '<Root>/current_ctl_output'
     */
    current_ctl_loop_task(&_rt_U.current_ctl_input, &_rt_U.current_ctl_config,
                          &_rt_Y.current_ctl_output,
                          &(_rt_DW.current_ctl_loop_task_InstanceData.rtdw));

    /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/current_ctl_pi_step' */
}

/* Model step function for TID2 */
void pos_speed_ctl_pip_step(void)    /* Explicit Task: pos_speed_ctl_pip_step */
{
    /* RootInportFunctionCallGenerator generated from: '<Root>/pos_speed_ctl_pip_step' */

    /* ModelReference generated from: '<Root>/pos_speed_ctl_pip' incorporates:
     *  Inport: '<Root>/pos_speed_ctl_config'
     *  Inport: '<Root>/pos_speed_ctl_input'
     *  Outport: '<Root>/pos_speed_ctl_output'
     */
    pos_speed_ctl_pip(&_rt_U.pos_speed_ctl_input, &_rt_U.pos_speed_ctl_config,
                      &_rt_Y.pos_speed_ctl_output,
                      &(_rt_DW.pos_speed_ctl_pip_InstanceData.rtdw));

    /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/pos_speed_ctl_pip_step' */
}

/* Model step function for TID3 */
void notch_filter_step(void)           /* Explicit Task: notch_filter_step */
{
    /* RootInportFunctionCallGenerator generated from: '<Root>/notch_filter_step' */

    /* ModelReference generated from: '<Root>/notch_filter' incorporates:
     *  Inport: '<Root>/notch_filter_input'
     *  Inport: '<Root>/notch_filter_internal'
     *  Outport: '<Root>/notch_filter_output'
     */
    notch_filter(&_rt_U.notch_filter_input, &_rt_U.notch_filter_internal,
                 &_rt_Y.notch_filter_output,
                 &(_rt_DW.notch_filter_InstanceData.rtdw));

    /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/notch_filter_step' */
}

/* Model step function for TID4 */
void database_init_step(void)          /* Explicit Task: database_init_step */
{
    /* RootInportFunctionCallGenerator generated from: '<Root>/database_init_step' */

    /* ModelReference generated from: '<Root>/database_init' incorporates:
     *  Inport: '<Root>/database_init_input'
     *  Outport: '<Root>/database_init_output'
     */
    database_init(&_rt_U.database_init_input, &_rt_Y.database_init_output);

    /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/database_init_step' */
}

/* Model step function for TID5 */
void motor_pos_sensor_step(void)      /* Explicit Task: motor_pos_sensor_step */
{
    /* RootInportFunctionCallGenerator generated from: '<Root>/motor_pos_sensor_step' */

    /* ModelReference generated from: '<Root>/motor_pos_sensor' incorporates:
     *  Inport: '<Root>/motor_pos_sensor_config'
     *  Inport: '<Root>/motor_pos_sensor_input'
     *  Outport: '<Root>/motor_pos_sensor_output'
     */
    motor_pos_sensor(&_rt_U.motor_pos_sensor_input,
                     &_rt_U.motor_pos_sensor_config,
                     &_rt_Y.motor_pos_sensor_output,
                     &(_rt_DW.motor_pos_sensor_InstanceData.rtdw));

    /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/motor_pos_sensor_step' */
}

/* Model step function for TID6 */
void speed_obs_pll_step(void)          /* Explicit Task: speed_obs_pll_step */
{
    /* RootInportFunctionCallGenerator generated from: '<Root>/speed_obs_pll_step' */

    /* ModelReference generated from: '<Root>/speed_obs_pll' incorporates:
     *  Inport: '<Root>/speed_obs_pll_config'
     *  Inport: '<Root>/speed_obs_pll_input'
     *  Outport: '<Root>/speed_obs_pll_output'
     */
    speed_obs_pll(&_rt_U.speed_obs_pll_input, &_rt_U.speed_obs_pll_config,
                  &_rt_Y.speed_obs_pll_output,
                  &(_rt_DW.speed_obs_pll_InstanceData.rtdw));

    /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/speed_obs_pll_step' */
}

/* Model step function for TID7 */
void elec_angle_id_step(void)          /* Explicit Task: elec_angle_id_step */
{
    /* RootInportFunctionCallGenerator generated from: '<Root>/elec_angle_id_step' */

    /* ModelReference generated from: '<Root>/elec_angle_id' incorporates:
     *  Outport: '<Root>/elec_angle_id_output'
     */
    elec_angle_id(&_rt_Y.elec_angle_id_output);

    /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/elec_angle_id_step' */
}

/* Model step function for TID8 */
void direction_id_step(void)           /* Explicit Task: direction_id_step */
{
    /* RootInportFunctionCallGenerator generated from: '<Root>/direction_id_step' */

    /* ModelReference generated from: '<Root>/direction_id' incorporates:
     *  Inport: '<Root>/direction_id_config'
     *  Inport: '<Root>/direction_id_input'
     *  Outport: '<Root>/direction_id_output'
     */
    direction_id(&_rt_U.direction_id_input, &_rt_U.direction_id_config,
                 &_rt_Y.direction_id_output,
                 &(_rt_DW.direction_id_InstanceData.rtdw),
                 &(_rt_DW.direction_id_InstanceData.rtzce));

    /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/direction_id_step' */
}

/* Model step function for TID9 */
void pole_pairs_id_step(void)          /* Explicit Task: pole_pairs_id_step */
{
    /* RootInportFunctionCallGenerator generated from: '<Root>/pole_pairs_id_step' */

    /* ModelReference generated from: '<Root>/pole_pairs_id' incorporates:
     *  Inport: '<Root>/pole_pairs_id_config'
     *  Inport: '<Root>/pole_pairs_id_input'
     *  Outport: '<Root>/pole_pairs_id_output'
     */
    pole_pairs_id(&_rt_U.pole_pairs_id_input, &_rt_U.pole_pairs_id_config,
                  &_rt_Y.pole_pairs_id_output,
                  &(_rt_DW.pole_pairs_id_InstanceData.rtdw),
                  &(_rt_DW.pole_pairs_id_InstanceData.rtzce));

    /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/pole_pairs_id_step' */
}

/* Model step function for TID10 */
void pos_trajectory_planning_step(void)
                               /* Explicit Task: pos_trajectory_planning_step */
{
    /* RootInportFunctionCallGenerator generated from: '<Root>/pos_trajectory_planning_step' */

    /* ModelReference generated from: '<Root>/pos_trajectory_planning' incorporates:
     *  Inport: '<Root>/acc_p_ss'
     *  Inport: '<Root>/dec_p_ss'
     *  Inport: '<Root>/pos_tar_p'
     *  Inport: '<Root>/tp_s'
     *  Inport: '<Root>/vmax_p_s'
     *  Outport: '<Root>/acc_out_p_ss'
     *  Outport: '<Root>/pos_out_dec_p'
     *  Outport: '<Root>/pos_out_int_p'
     *  Outport: '<Root>/state_now'
     *  Outport: '<Root>/v_out_p_s'
     */
    pos_trajectory_planning(&_rt_U.pos_tar_p, &_rt_U.vmax_p_s, &_rt_U.acc_p_ss,
                            &_rt_U.dec_p_ss, &_rt_U.tp_s, &_rt_Y.pos_out_int_p,
                            &_rt_Y.pos_out_dec_p, &_rt_Y.v_out_p_s,
                            &_rt_Y.acc_out_p_ss, &_rt_Y.state_now,
                            &(_rt_DW.pos_trajectory_planning_InstanceData.rtdw));

    /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/pos_trajectory_planning_step' */
}

/* Model step function for TID11 */
void protect_check_step(void)          /* Explicit Task: protect_check_step */
{
    /* RootInportFunctionCallGenerator generated from: '<Root>/protect_check_step' */

    /* ModelReference generated from: '<Root>/protect_check' incorporates:
     *  Inport: '<Root>/config'
     *  Inport: '<Root>/dc_bus'
     *  Inport: '<Root>/driver_temp'
     *  Inport: '<Root>/iabc_now'
     *  Inport: '<Root>/pos_ctl_error'
     *  Inport: '<Root>/speed_now'
     *  Outport: '<Root>/error'
     */
    protect_check(&_rt_U.iabc_now[0], &_rt_U.dc_bus, &_rt_U.driver_temp,
                  &_rt_U.pos_ctl_error, &_rt_U.speed_now, &_rt_U.config,
                  &_rt_Y.error);

    /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/protect_check_step' */
}

/* Model step function for TID12 */
void set_notch_filter_config_step(void)
                               /* Explicit Task: set_notch_filter_config_step */
{
    /* RootInportFunctionCallGenerator generated from: '<Root>/set_notch_filter_config_step' */

    /* ModelReference generated from: '<Root>/set_notch_filter_config' incorporates:
     *  Inport: '<Root>/dt'
     *  Inport: '<Root>/notch_filter_config'
     *  Outport: '<Root>/notch_filter_internal_config'
     */
    notch_filter_config_set(&_rt_U.notch_filter_config, &_rt_U.dt,
                            &_rt_Y.notch_filter_internal_config);

    /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/set_notch_filter_config_step' */
}

/* Model step function for TID13 */
void input_shaping_step(void)          /* Explicit Task: input_shaping_step */
{
    /* RootInportFunctionCallGenerator generated from: '<Root>/input_shaping_step' */

    /* ModelReference generated from: '<Root>/input_shaping' incorporates:
     *  Inport: '<Root>/input_shaping_config'
     *  Inport: '<Root>/input_shaping_input'
     *  Outport: '<Root>/input_shaping_output'
     */
    input_shaping_ei(&_rt_U.input_shaping_input, &_rt_U.input_shaping_config,
                     &_rt_Y.input_shaping_output,
                     &(_rt_DW.input_shaping_InstanceData.rtdw));

    /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/input_shaping_step' */
}

/* Model step function for TID14 */
void tq_fc_id_step(void)               /* Explicit Task: tq_fc_id_step */
{
    /* RootInportFunctionCallGenerator generated from: '<Root>/tq_fc_id_step' */

    /* ModelReference generated from: '<Root>/tq_fc_id' incorporates:
     *  Outport: '<Root>/tq_fc_id_output'
     */
    tq_fc_id(&_rt_Y.tq_fc_id_output);

    /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/tq_fc_id_step' */
}

/* Model step function for TID15 */
void reciprocal_motion_step(void)    /* Explicit Task: reciprocal_motion_step */
{
    /* RootInportFunctionCallGenerator generated from: '<Root>/reciprocal_motion_step' */

    /* ModelReference generated from: '<Root>/reciprocal_motion' incorporates:
     *  Inport: '<Root>/reciprocal_motion_config'
     *  Outport: '<Root>/reciprocal_motion_output'
     */
    reciprocal_motion(&_rt_U.reciprocal_motion_config,
                      &_rt_Y.reciprocal_motion_output,
                      &(_rt_DW.reciprocal_motion_InstanceData.rtdw));

    /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/reciprocal_motion_step' */
}

/* Model step function for TID16 */
void reference_signal_step(void)      /* Explicit Task: reference_signal_step */
{
    /* RootInportFunctionCallGenerator generated from: '<Root>/reference_signal_step' */

    /* ModelReference generated from: '<Root>/reference_signal' incorporates:
     *  Inport: '<Root>/reference_signal_config'
     *  Outport: '<Root>/reference_signal_output'
     */
    reference_signal(&_rt_U.reference_signal_config,
                     &_rt_Y.reference_signal_output,
                     &(_rt_DW.reference_signal_InstanceData.rtdw));

    /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/reference_signal_step' */
}

/* Model step function for TID17 */
void mit_ctl_step(void)                /* Explicit Task: mit_ctl_step */
{
    /* RootInportFunctionCallGenerator generated from: '<Root>/mit_ctl_step' */

    /* ModelReference generated from: '<Root>/mit_ctl' incorporates:
     *  Inport: '<Root>/mit_ctl_config'
     *  Inport: '<Root>/mit_ctl_input'
     *  Outport: '<Root>/mit_ctl_output'
     */
    mit_ctl(&_rt_U.mit_ctl_input, &_rt_U.mit_ctl_config, &_rt_Y.mit_ctl_output);

    /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/mit_ctl_step' */
}

/* Model step function for TID18 */
void math_lib_step(void)               /* Explicit Task: math_lib_step */
{
    /* RootInportFunctionCallGenerator generated from: '<Root>/math_lib_step' */

    /* ModelReference generated from: '<Root>/math_lib' incorporates:
     *  Inport: '<Root>/data_in'
     *  Inport: '<Root>/data_in1'
     *  Inport: '<Root>/data_out'
     *  Inport: '<Root>/factor'
     *  Inport: '<Root>/fc'
     *  Inport: '<Root>/ts'
     *  Outport: '<Root>/data_filter'
     *  Outport: '<Root>/data_filter1'
     *  Outport: '<Root>/factor_set'
     */
    math_lib(&_rt_U.fc, &_rt_U.ts, &_rt_U.data_in, &_rt_U.factor,
             &_rt_U.data_out, &_rt_U.data_in1[0], &_rt_Y.factor_set,
             &_rt_Y.data_filter, &_rt_Y.data_filter1);

    /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/math_lib_step' */
}

/* Model step function for TID19 */
void linear_trajectory_planning_step(void)
                            /* Explicit Task: linear_trajectory_planning_step */
{
    /* RootInportFunctionCallGenerator generated from: '<Root>/linear_trajectory_planning_step' */

    /* ModelReference generated from: '<Root>/linear_trajectory_planning' incorporates:
     *  Inport: '<Root>/dt_s'
     *  Inport: '<Root>/slop'
     *  Inport: '<Root>/traj_cmd'
     *  Outport: '<Root>/state_now1'
     *  Outport: '<Root>/traj_out'
     */
    linear_trajectory_planning(&_rt_U.traj_cmd, &_rt_U.slop, &_rt_U.dt_s,
        &_rt_Y.traj_out, &_rt_Y.state_now1,
        &(_rt_DW.linear_trajectory_planning_InstanceData.rtdw));

    /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/linear_trajectory_planning_step' */
}

/* Model step function for TID20 */
void load_pos_sensor_step(void)        /* Explicit Task: load_pos_sensor_step */
{
    /* RootInportFunctionCallGenerator generated from: '<Root>/load_pos_sensor_step' */

    /* ModelReference generated from: '<Root>/load_pos_sensor' incorporates:
     *  Inport: '<Root>/load_pos_sensor_config'
     *  Inport: '<Root>/load_pos_sensor_input'
     *  Outport: '<Root>/load_pos_sensor_output'
     */
    load_pos_sensor(&_rt_U.load_pos_sensor_input, &_rt_U.load_pos_sensor_config,
                    &_rt_Y.load_pos_sensor_output,
                    &(_rt_DW.load_pos_sensor_InstanceData.rtdw));

    /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/load_pos_sensor_step' */
}

/* Model step function for TID21 */
void sim_plant_step(void)              /* Explicit Task: sim_plant_step */
{
    /* RootInportFunctionCallGenerator generated from: '<Root>/sim_plant_step' */

    /* ModelReference generated from: '<Root>/sim_plant' incorporates:
     *  Inport: '<Root>/sim_plant_config'
     *  Inport: '<Root>/sim_plant_input'
     *  Outport: '<Root>/sim_plant_output'
     */
    sim_plant(&_rt_U.sim_plant_input, &_rt_U.sim_plant_config,
              &_rt_Y.sim_plant_output, &(_rt_DW.sim_plant_InstanceData.rtdw));

    /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/sim_plant_step' */
}

/* Model step function for TID22 */
void csv_planning_step(void)           /* Explicit Task: csv_planning_step */
{
    /* RootInportFunctionCallGenerator generated from: '<Root>/csv_planning_step' */

    /* ModelReference generated from: '<Root>/csv_planning' incorporates:
     *  Inport: '<Root>/ip_dt'
     *  Inport: '<Root>/ip_dt1'
     *  Inport: '<Root>/v_target_ip_buff'
     *  Outport: '<Root>/acc_cmd'
     *  Outport: '<Root>/v_cmd'
     */
    csv_planning(&_rt_U.v_target_ip_buff[0], &_rt_U.ip_dt, &_rt_U.ip_dt1,
                 &_rt_Y.v_cmd, &_rt_Y.acc_cmd,
                 &(_rt_DW.csv_planning_InstanceData.rtdw));

    /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/csv_planning_step' */
}

/* Model step function for TID23 */
void cst_planning_step(void)           /* Explicit Task: cst_planning_step */
{
    /* RootInportFunctionCallGenerator generated from: '<Root>/cst_planning_step' */

    /* ModelReference generated from: '<Root>/cst_planning' incorporates:
     *  Inport: '<Root>/ip_dt2'
     *  Inport: '<Root>/ip_dt3'
     *  Inport: '<Root>/iq_target_ip_buff'
     *  Outport: '<Root>/iq_cmd'
     */
    cst_planning(&_rt_U.iq_target_ip_buff[0], &_rt_U.ip_dt2, &_rt_U.ip_dt3,
                 &_rt_Y.iq_cmd, &(_rt_DW.cst_planning_InstanceData.rtdw));

    /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/cst_planning_step' */
}

/* Model step function for TID24 */
void csp_planning_step(void)           /* Explicit Task: csp_planning_step */
{
    /* RootInportFunctionCallGenerator generated from: '<Root>/csp_planning_step' */

    /* ModelReference generated from: '<Root>/csp_planning' incorporates:
     *  Inport: '<Root>/ip_dt4'
     *  Inport: '<Root>/ip_dt5'
     *  Inport: '<Root>/pos_target_ip_buff'
     *  Outport: '<Root>/acc_cmd1'
     *  Outport: '<Root>/pos_cmd'
     *  Outport: '<Root>/v_cmd1'
     */
    csp_planning(&_rt_U.pos_target_ip_buff[0], &_rt_U.ip_dt4, &_rt_U.ip_dt5,
                 &_rt_Y.pos_cmd, &_rt_Y.v_cmd1, &_rt_Y.acc_cmd1,
                 &(_rt_DW.csp_planning_InstanceData.rtdw));

    /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/csp_planning_step' */
}

/* Model initialize function */
void servo_hub_example_initialize(void)
{
    /* Model Initialize function for ModelReference Block: '<Root>/direction_id' */
    direction_id_initialize(&(_rt_DW.direction_id_InstanceData.rtzce));

    /* Model Initialize function for ModelReference Block: '<Root>/pole_pairs_id' */
    pole_pairs_id_initialize(&(_rt_DW.pole_pairs_id_InstanceData.rtzce));

    /* SystemInitialize for RootInportFunctionCallGenerator generated from: '<Root>/current_ctl_pi_step' */

    /* SystemInitialize for ModelReference generated from: '<Root>/current_ctl_loop_task' */
    current_ctl_loop_task_Init(&(_rt_DW.current_ctl_loop_task_InstanceData.rtdw));

    /* End of SystemInitialize for RootInportFunctionCallGenerator generated from: '<Root>/current_ctl_pi_step' */

    /* SystemInitialize for RootInportFunctionCallGenerator generated from: '<Root>/pos_speed_ctl_pip_step' */

    /* SystemInitialize for ModelReference generated from: '<Root>/pos_speed_ctl_pip' */
    pos_speed_ctl_pip_Init(&(_rt_DW.pos_speed_ctl_pip_InstanceData.rtdw));

    /* End of SystemInitialize for RootInportFunctionCallGenerator generated from: '<Root>/pos_speed_ctl_pip_step' */

    /* SystemInitialize for RootInportFunctionCallGenerator generated from: '<Root>/notch_filter_step' */

    /* SystemInitialize for ModelReference generated from: '<Root>/notch_filter' */
    notch_filter_Init(&(_rt_DW.notch_filter_InstanceData.rtdw));

    /* End of SystemInitialize for RootInportFunctionCallGenerator generated from: '<Root>/notch_filter_step' */

    /* SystemInitialize for RootInportFunctionCallGenerator generated from: '<Root>/motor_pos_sensor_step' */

    /* SystemInitialize for ModelReference generated from: '<Root>/motor_pos_sensor' */
    motor_pos_sensor_Init();

    /* End of SystemInitialize for RootInportFunctionCallGenerator generated from: '<Root>/motor_pos_sensor_step' */

    /* SystemInitialize for RootInportFunctionCallGenerator generated from: '<Root>/speed_obs_pll_step' */

    /* SystemInitialize for ModelReference generated from: '<Root>/speed_obs_pll' */
    speed_obs_pll_Init(&(_rt_DW.speed_obs_pll_InstanceData.rtdw));

    /* End of SystemInitialize for RootInportFunctionCallGenerator generated from: '<Root>/speed_obs_pll_step' */

    /* SystemInitialize for RootInportFunctionCallGenerator generated from: '<Root>/elec_angle_id_step' */

    /* SystemInitialize for ModelReference generated from: '<Root>/elec_angle_id' incorporates:
     *  Outport: '<Root>/elec_angle_id_output'
     */
    elec_angle_id_Init(&_rt_Y.elec_angle_id_output,
                       &(_rt_DW.elec_angle_id_InstanceData.rtdw));

    /* End of SystemInitialize for RootInportFunctionCallGenerator generated from: '<Root>/elec_angle_id_step' */

    /* SystemInitialize for RootInportFunctionCallGenerator generated from: '<Root>/direction_id_step' */

    /* SystemInitialize for ModelReference generated from: '<Root>/direction_id' */
    direction_id_Init(&(_rt_DW.direction_id_InstanceData.rtdw),
                      &(_rt_DW.direction_id_InstanceData.rtzce));

    /* End of SystemInitialize for RootInportFunctionCallGenerator generated from: '<Root>/direction_id_step' */

    /* SystemInitialize for RootInportFunctionCallGenerator generated from: '<Root>/pole_pairs_id_step' */

    /* SystemInitialize for ModelReference generated from: '<Root>/pole_pairs_id' */
    pole_pairs_id_Init(&(_rt_DW.pole_pairs_id_InstanceData.rtdw),
                       &(_rt_DW.pole_pairs_id_InstanceData.rtzce));

    /* End of SystemInitialize for RootInportFunctionCallGenerator generated from: '<Root>/pole_pairs_id_step' */

    /* SystemInitialize for RootInportFunctionCallGenerator generated from: '<Root>/pos_trajectory_planning_step' */

    /* SystemInitialize for ModelReference generated from: '<Root>/pos_trajectory_planning' */
    pos_trajectory_planning_Init();

    /* End of SystemInitialize for RootInportFunctionCallGenerator generated from: '<Root>/pos_trajectory_planning_step' */

    /* SystemInitialize for RootInportFunctionCallGenerator generated from: '<Root>/input_shaping_step' */

    /* SystemInitialize for ModelReference generated from: '<Root>/input_shaping' */
    input_shaping_ei_Init(&(_rt_DW.input_shaping_InstanceData.rtdw));

    /* End of SystemInitialize for RootInportFunctionCallGenerator generated from: '<Root>/input_shaping_step' */

    /* SystemInitialize for RootInportFunctionCallGenerator generated from: '<Root>/tq_fc_id_step' */

    /* SystemInitialize for ModelReference generated from: '<Root>/tq_fc_id' incorporates:
     *  Outport: '<Root>/tq_fc_id_output'
     */
    tq_fc_id_Init(&_rt_Y.tq_fc_id_output, &(_rt_DW.tq_fc_id_InstanceData.rtdw));

    /* End of SystemInitialize for RootInportFunctionCallGenerator generated from: '<Root>/tq_fc_id_step' */

    /* SystemInitialize for RootInportFunctionCallGenerator generated from: '<Root>/reciprocal_motion_step' */

    /* SystemInitialize for ModelReference generated from: '<Root>/reciprocal_motion' */
    reciprocal_motion_Init();

    /* End of SystemInitialize for RootInportFunctionCallGenerator generated from: '<Root>/reciprocal_motion_step' */

    /* SystemInitialize for RootInportFunctionCallGenerator generated from: '<Root>/reference_signal_step' */

    /* SystemInitialize for ModelReference generated from: '<Root>/reference_signal' */
    reference_signal_Init(&(_rt_DW.reference_signal_InstanceData.rtdw));

    /* End of SystemInitialize for RootInportFunctionCallGenerator generated from: '<Root>/reference_signal_step' */

    /* SystemInitialize for RootInportFunctionCallGenerator generated from: '<Root>/load_pos_sensor_step' */

    /* SystemInitialize for ModelReference generated from: '<Root>/load_pos_sensor' */
    load_pos_sensor_Init();

    /* End of SystemInitialize for RootInportFunctionCallGenerator generated from: '<Root>/load_pos_sensor_step' */

    /* SystemInitialize for RootInportFunctionCallGenerator generated from: '<Root>/sim_plant_step' */

    /* SystemInitialize for ModelReference generated from: '<Root>/sim_plant' */
    sim_plant_Init(&(_rt_DW.sim_plant_InstanceData.rtdw));

    /* End of SystemInitialize for RootInportFunctionCallGenerator generated from: '<Root>/sim_plant_step' */

    /* SystemInitialize for RootInportFunctionCallGenerator generated from: '<Root>/csv_planning_step' */

    /* SystemInitialize for ModelReference generated from: '<Root>/csv_planning' */
    csv_planning_Init(&(_rt_DW.csv_planning_InstanceData.rtdw));

    /* End of SystemInitialize for RootInportFunctionCallGenerator generated from: '<Root>/csv_planning_step' */

    /* SystemInitialize for RootInportFunctionCallGenerator generated from: '<Root>/cst_planning_step' */

    /* SystemInitialize for ModelReference generated from: '<Root>/cst_planning' */
    cst_planning_Init(&(_rt_DW.cst_planning_InstanceData.rtdw));

    /* End of SystemInitialize for RootInportFunctionCallGenerator generated from: '<Root>/cst_planning_step' */

    /* SystemInitialize for RootInportFunctionCallGenerator generated from: '<Root>/csp_planning_step' */

    /* SystemInitialize for ModelReference generated from: '<Root>/csp_planning' */
    csp_planning_Init(&(_rt_DW.csp_planning_InstanceData.rtdw));

    /* End of SystemInitialize for RootInportFunctionCallGenerator generated from: '<Root>/csp_planning_step' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
