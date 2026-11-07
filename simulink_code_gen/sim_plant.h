/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: sim_plant.h
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

#ifndef RTW_HEADER_sim_plant_h_
#define RTW_HEADER_sim_plant_h_
#ifndef sim_plant_COMMON_INCLUDES_
#define sim_plant_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* sim_plant_COMMON_INCLUDES_ */

#include "servo_hub_database_type.h"

/* Block signals and states (default storage) for model 'sim_plant' */
typedef struct
{
    real_T UniformRandomNumber_NextOutput;/* '<S3>/Uniform Random Number' */
    real_T UniformRandomNumber1_NextOutput;/* '<S2>/Uniform Random Number1' */
    real_T UniformRandomNumber_NextOutput_a;/* '<S12>/Uniform Random Number' */
    real_T UniformRandomNumber_NextOutput_j;/* '<S11>/Uniform Random Number' */
    real_T UniformRandomNumber_NextOutput_o;/* '<S10>/Uniform Random Number' */
    real32_T elec_angle_last;          /* '<S6>/elec_angle_last_delay' */
    real32_T id_now_last;              /* '<S17>/id_now_last_delay' */
    real32_T iq_now_last;              /* '<S17>/iq_now_last_delay' */
    real32_T wm_now_last;              /* '<S17>/wm_now_last_delay' */
    real32_T pos_last;                 /* '<S15>/pos_last_delay' */
    uint32_T RandSeed;                 /* '<S3>/Uniform Random Number' */
    uint32_T RandSeed_o;               /* '<S2>/Uniform Random Number1' */
    uint32_T RandSeed_n;               /* '<S12>/Uniform Random Number' */
    uint32_T RandSeed_l;               /* '<S11>/Uniform Random Number' */
    uint32_T RandSeed_i;               /* '<S10>/Uniform Random Number' */
}
sim_plant_DW_f;

typedef struct
{
    sim_plant_DW_f rtdw;
}
sim_plant_MdlrefDW;

extern void sim_plant_mod2pi_fun(real32_T rtu_ang, real32_T *rty_n_ang);
extern void sim_plant_Init(sim_plant_DW_f *localDW);
extern void sim_plant(const SimPlantInput *rtu_input, const SimPlantConfig
                      *rtu_config, SimPlantOutput *rty_output, sim_plant_DW_f
                      *localDW);

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S13>/Gain1' : Eliminated nontunable gain of 1
 */

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
 * '<Root>' : 'sim_plant'
 * '<S1>'   : 'sim_plant/sim_plant'
 * '<S2>'   : 'sim_plant/sim_plant/dc_voltage_source'
 * '<S3>'   : 'sim_plant/sim_plant/encoder_sensor'
 * '<S4>'   : 'sim_plant/sim_plant/hall_sensor'
 * '<S5>'   : 'sim_plant/sim_plant/iabc_noise_add'
 * '<S6>'   : 'sim_plant/sim_plant/sm_pmsm_model'
 * '<S7>'   : 'sim_plant/sim_plant/encoder_sensor/encoder_tf'
 * '<S8>'   : 'sim_plant/sim_plant/encoder_sensor/mod2pi_fun'
 * '<S9>'   : 'sim_plant/sim_plant/hall_sensor/hall_clc'
 * '<S10>'  : 'sim_plant/sim_plant/iabc_noise_add/Subsystem'
 * '<S11>'  : 'sim_plant/sim_plant/iabc_noise_add/Subsystem1'
 * '<S12>'  : 'sim_plant/sim_plant/iabc_noise_add/Subsystem2'
 * '<S13>'  : 'sim_plant/sim_plant/sm_pmsm_model/InverseParkTransform'
 * '<S14>'  : 'sim_plant/sim_plant/sm_pmsm_model/ParkTransform'
 * '<S15>'  : 'sim_plant/sim_plant/sm_pmsm_model/dis_int_wm'
 * '<S16>'  : 'sim_plant/sim_plant/sm_pmsm_model/mod2pi_fun'
 * '<S17>'  : 'sim_plant/sim_plant/sm_pmsm_model/sm_pmsm_dq'
 * '<S18>'  : 'sim_plant/sim_plant/sm_pmsm_model/dis_int_wm/mod2pi_fun'
 */

/*-
 * Requirements for '<Root>': sim_plant

 */
#endif                                 /* RTW_HEADER_sim_plant_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
