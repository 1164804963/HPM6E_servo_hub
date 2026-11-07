/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: servo_hub_example.h
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

#ifndef RTW_HEADER_servo_hub_example_h_
#define RTW_HEADER_servo_hub_example_h_
#ifndef servo_hub_example_COMMON_INCLUDES_
#define servo_hub_example_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* servo_hub_example_COMMON_INCLUDES_ */

#include "servo_hub_database_type.h"
#include "csp_planning.h"
#include "cst_planning.h"
#include "csv_planning.h"
#include "current_ctl_loop_task.h"
#include "database_init.h"
#include "direction_id.h"
#include "elec_angle_id.h"
#include "input_shaping_ei.h"
#include "linear_trajectory_planning.h"
#include "load_pos_sensor.h"
#include "math_lib.h"
#include "mit_ctl.h"
#include "motor_pos_sensor.h"
#include "notch_filter.h"
#include "notch_filter_config_set.h"
#include "pole_pairs_id.h"
#include "pos_speed_ctl_pip.h"
#include "pos_trajectory_planning.h"
#include "protect_check.h"
#include "reciprocal_motion.h"
#include "reference_signal.h"
#include "sim_plant.h"
#include "speed_obs_pll.h"
#include "tq_fc_id.h"
#include "zero_crossing_types.h"

/* Block signals and states (default storage) for system '<Root>' */
typedef struct
{
    csp_planning_MdlrefDW csp_planning_InstanceData;/* '<Root>/csp_planning' */
    cst_planning_MdlrefDW cst_planning_InstanceData;/* '<Root>/cst_planning' */
    csv_planning_MdlrefDW csv_planning_InstanceData;/* '<Root>/csv_planning' */
    current_ctl_loop_task_MdlrefDW current_ctl_loop_task_InstanceData;/* '<Root>/current_ctl_loop_task' */
    direction_id_MdlrefDW direction_id_InstanceData;/* '<Root>/direction_id' */
    elec_angle_id_MdlrefDW elec_angle_id_InstanceData;/* '<Root>/elec_angle_id' */
    input_shaping_ei_MdlrefDW input_shaping_InstanceData;/* '<Root>/input_shaping' */
    linear_trajectory_planning_MdlrefDW linear_trajectory_planning_InstanceData;/* '<Root>/linear_trajectory_planning' */
    load_pos_sensor_MdlrefDW load_pos_sensor_InstanceData;/* '<Root>/load_pos_sensor' */
    motor_pos_sensor_MdlrefDW motor_pos_sensor_InstanceData;/* '<Root>/motor_pos_sensor' */
    notch_filter_MdlrefDW notch_filter_InstanceData;/* '<Root>/notch_filter' */
    pole_pairs_id_MdlrefDW pole_pairs_id_InstanceData;/* '<Root>/pole_pairs_id' */
    pos_speed_ctl_pip_MdlrefDW pos_speed_ctl_pip_InstanceData;/* '<Root>/pos_speed_ctl_pip' */
    pos_trajectory_planning_MdlrefDW pos_trajectory_planning_InstanceData;/* '<Root>/pos_trajectory_planning' */
    reciprocal_motion_MdlrefDW reciprocal_motion_InstanceData;/* '<Root>/reciprocal_motion' */
    reference_signal_MdlrefDW reference_signal_InstanceData;/* '<Root>/reference_signal' */
    sim_plant_MdlrefDW sim_plant_InstanceData;/* '<Root>/sim_plant' */
    speed_obs_pll_MdlrefDW speed_obs_pll_InstanceData;/* '<Root>/speed_obs_pll' */
    tq_fc_id_MdlrefDW tq_fc_id_InstanceData;/* '<Root>/tq_fc_id' */
}
DW;

/* External inputs (root inport signals with default storage) */
typedef struct
{
    CurrentCtlInput current_ctl_input; /* '<Root>/current_ctl_input' */
    CurrentCtlConfig current_ctl_config;/* '<Root>/current_ctl_config' */
    PosSpeedCtlInput pos_speed_ctl_input;/* '<Root>/pos_speed_ctl_input' */
    PosSpeedCtlConfig pos_speed_ctl_config;/* '<Root>/pos_speed_ctl_config' */
    NotchFilterInput notch_filter_input;/* '<Root>/notch_filter_input' */
    NotchFilterInternal notch_filter_internal;/* '<Root>/notch_filter_internal' */
    MotorPosSensorInput motor_pos_sensor_input;/* '<Root>/motor_pos_sensor_input' */
    MotorPosSensorConfig motor_pos_sensor_config;/* '<Root>/motor_pos_sensor_config' */
    SpeedObsPllInput speed_obs_pll_input;/* '<Root>/speed_obs_pll_input' */
    SpeedObsPllConfig speed_obs_pll_config;/* '<Root>/speed_obs_pll_config' */
    ElecAngleIdInput elec_angle_id_input;/* '<Root>/elec_angle_id_input' */
    ElecAngleIdConfig elec_angle_id_config;/* '<Root>/elec_angle_id_config' */
    DirectionIdInput direction_id_input;/* '<Root>/direction_id_input' */
    DirectionIdConfig direction_id_config;/* '<Root>/direction_id_config' */
    PolePairsIdInput pole_pairs_id_input;/* '<Root>/pole_pairs_id_input' */
    PolePairsIdConfig pole_pairs_id_config;/* '<Root>/pole_pairs_id_config' */
    int64_T pos_tar_p;                 /* '<Root>/pos_tar_p' */
    real32_T vmax_p_s;                 /* '<Root>/vmax_p_s' */
    real32_T acc_p_ss;                 /* '<Root>/acc_p_ss' */
    real32_T dec_p_ss;                 /* '<Root>/dec_p_ss' */
    real32_T tp_s;                     /* '<Root>/tp_s' */
    real32_T iabc_now[3];              /* '<Root>/iabc_now' */
    real32_T dc_bus;                   /* '<Root>/dc_bus' */
    real32_T driver_temp;              /* '<Root>/driver_temp' */
    int32_T pos_ctl_error;             /* '<Root>/pos_ctl_error' */
    MotorCtlSmConfig config;           /* '<Root>/config' */
    real32_T speed_now;                /* '<Root>/speed_now' */
    NotchFilterConfig notch_filter_config;/* '<Root>/notch_filter_config' */
    real32_T dt;                       /* '<Root>/dt' */
    NotchFilterInternal notch_filter_internal_config_last;
                                /* '<Root>/notch_filter_internal_config_last' */
    InputShapingInput input_shaping_input;/* '<Root>/input_shaping_input' */
    InputShapingConfig input_shaping_config;/* '<Root>/input_shaping_config' */
    TqFcIdInput tq_fc_id_input;        /* '<Root>/tq_fc_id_input' */
    TqFcIdConfig tq_fc_id_config;      /* '<Root>/tq_fc_id_config' */
    ReciprocalMotionConfig reciprocal_motion_config;/* '<Root>/reciprocal_motion_config' */
    ReferenceSignalConfig reference_signal_config;/* '<Root>/reference_signal_config' */
    MitCtlInput mit_ctl_input;         /* '<Root>/mit_ctl_input' */
    MitCtlConfig mit_ctl_config;       /* '<Root>/mit_ctl_config' */
    real32_T fc;                       /* '<Root>/fc' */
    real32_T ts;                       /* '<Root>/ts' */
    real32_T data_in;                  /* '<Root>/data_in' */
    real32_T factor;                   /* '<Root>/factor' */
    real32_T data_out;                 /* '<Root>/data_out' */
    real32_T data_in1[3];              /* '<Root>/data_in1' */
    real32_T traj_cmd;                 /* '<Root>/traj_cmd' */
    real32_T slop;                     /* '<Root>/slop' */
    real32_T dt_s;                     /* '<Root>/dt_s' */
    LoadPosSensorInput load_pos_sensor_input;/* '<Root>/load_pos_sensor_input' */
    LoadPosSensorConfig load_pos_sensor_config;/* '<Root>/load_pos_sensor_config' */
    SimPlantInput sim_plant_input;     /* '<Root>/sim_plant_input' */
    SimPlantConfig sim_plant_config;   /* '<Root>/sim_plant_config' */
    Axis database_init_input;          /* '<Root>/database_init_input' */
    real32_T v_target_ip_buff[4];      /* '<Root>/v_target_ip_buff' */
    real32_T ip_dt;                    /* '<Root>/ip_dt' */
    real32_T ip_dt1;                   /* '<Root>/ip_dt1' */
    real32_T iq_target_ip_buff[4];     /* '<Root>/iq_target_ip_buff' */
    real32_T ip_dt2;                   /* '<Root>/ip_dt2' */
    real32_T ip_dt3;                   /* '<Root>/ip_dt3' */
    int64_T pos_target_ip_buff[4];     /* '<Root>/pos_target_ip_buff' */
    real32_T ip_dt4;                   /* '<Root>/ip_dt4' */
    real32_T ip_dt5;                   /* '<Root>/ip_dt5' */
}
ExtU;

/* External outputs (root outports fed by signals with default storage) */
typedef struct
{
    CurrentCtlOutput current_ctl_output;/* '<Root>/current_ctl_output' */
    PosSpeedCtlOutput pos_speed_ctl_output;/* '<Root>/pos_speed_ctl_output' */
    NotchFilterOutput notch_filter_output;/* '<Root>/notch_filter_output' */
    MotorPosSensorOutput motor_pos_sensor_output;/* '<Root>/motor_pos_sensor_output' */
    SpeedObsPllOutput speed_obs_pll_output;/* '<Root>/speed_obs_pll_output' */
    ElecAngleIdOutput elec_angle_id_output;/* '<Root>/elec_angle_id_output' */
    DirectionIdOutput direction_id_output;/* '<Root>/direction_id_output' */
    PolePairsIdOutput pole_pairs_id_output;/* '<Root>/pole_pairs_id_output' */
    int64_T pos_out_int_p;             /* '<Root>/pos_out_int_p' */
    real32_T pos_out_dec_p;            /* '<Root>/pos_out_dec_p' */
    real32_T v_out_p_s;                /* '<Root>/v_out_p_s' */
    real32_T acc_out_p_ss;             /* '<Root>/acc_out_p_ss' */
    int8_T state_now;                  /* '<Root>/state_now' */
    uint32_T error;                    /* '<Root>/error' */
    NotchFilterInternal notch_filter_internal_config;
                                     /* '<Root>/notch_filter_internal_config' */
    InputShapingOutput input_shaping_output;/* '<Root>/input_shaping_output' */
    TqFcIdOutput tq_fc_id_output;      /* '<Root>/tq_fc_id_output' */
    ReciprocalMotionOutput reciprocal_motion_output;/* '<Root>/reciprocal_motion_output' */
    ReferenceSignalOutput reference_signal_output;/* '<Root>/reference_signal_output' */
    MitCtlOutput mit_ctl_output;       /* '<Root>/mit_ctl_output' */
    real32_T factor_set;               /* '<Root>/factor_set' */
    real32_T data_filter;              /* '<Root>/data_filter' */
    real32_T data_filter1;             /* '<Root>/data_filter1' */
    real32_T traj_out;                 /* '<Root>/traj_out' */
    int8_T state_now1;                 /* '<Root>/state_now1' */
    LoadPosSensorOutput load_pos_sensor_output;/* '<Root>/load_pos_sensor_output' */
    SimPlantOutput sim_plant_output;   /* '<Root>/sim_plant_output' */
    Axis database_init_output;         /* '<Root>/database_init_output' */
    real32_T v_cmd;                    /* '<Root>/v_cmd' */
    real32_T acc_cmd;                  /* '<Root>/acc_cmd' */
    real32_T iq_cmd;                   /* '<Root>/iq_cmd' */
    int64_T pos_cmd;                   /* '<Root>/pos_cmd' */
    real32_T v_cmd1;                   /* '<Root>/v_cmd1' */
    real32_T acc_cmd1;                 /* '<Root>/acc_cmd1' */
}
ExtY;

/* Block signals and states (default storage) */
extern DW _rt_DW;

/* External inputs (root inport signals with default storage) */
extern ExtU _rt_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY _rt_Y;

/* Model entry point functions */
extern void servo_hub_example_initialize(void);

/* Exported entry point function */
extern void current_ctl_pi_step(void);

/* Exported entry point function */
extern void pos_speed_ctl_pip_step(void);

/* Exported entry point function */
extern void notch_filter_step(void);

/* Exported entry point function */
extern void database_init_step(void);

/* Exported entry point function */
extern void motor_pos_sensor_step(void);

/* Exported entry point function */
extern void speed_obs_pll_step(void);

/* Exported entry point function */
extern void elec_angle_id_step(void);

/* Exported entry point function */
extern void direction_id_step(void);

/* Exported entry point function */
extern void pole_pairs_id_step(void);

/* Exported entry point function */
extern void pos_trajectory_planning_step(void);

/* Exported entry point function */
extern void protect_check_step(void);

/* Exported entry point function */
extern void set_notch_filter_config_step(void);

/* Exported entry point function */
extern void input_shaping_step(void);

/* Exported entry point function */
extern void tq_fc_id_step(void);

/* Exported entry point function */
extern void reciprocal_motion_step(void);

/* Exported entry point function */
extern void reference_signal_step(void);

/* Exported entry point function */
extern void mit_ctl_step(void);

/* Exported entry point function */
extern void math_lib_step(void);

/* Exported entry point function */
extern void linear_trajectory_planning_step(void);

/* Exported entry point function */
extern void load_pos_sensor_step(void);

/* Exported entry point function */
extern void sim_plant_step(void);

/* Exported entry point function */
extern void csv_planning_step(void);

/* Exported entry point function */
extern void cst_planning_step(void);

/* Exported entry point function */
extern void csp_planning_step(void);

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'servo_hub_example'
 */

/*-
 * Requirements for '<Root>': servo_hub_example


 */
#endif                                 /* RTW_HEADER_servo_hub_example_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
