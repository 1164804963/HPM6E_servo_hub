#include "motor_ctl_sm.h"
#include "yuanhub_math.h"
#if defined(PORT_PATCH_ELEC_BIAS_STORE_FLASH) && (PORT_PATCH_ELEC_BIAS_STORE_FLASH)
#include "bsp_api.h"   /* [移植补丁 16] bsp_elec_bias_store_to_shadow / restore */
#endif
/* [移植适配] 本文件用到 board_public 的 PORT_PATCH_* 开关（驱动参数头经由
 * data_type_define.h → servo_system_cfg.h 引入），否则 #if 判不到、会静默走 #else 上游分支。 */
#include "data_type_define.h"

// 所有电机控制对象进行实例化  Axis  AxisDw

#ifdef MOTOR_CTL_DEBUG                                  // 控制层调试模式  插入规划器  位置模式变为PP模式  速度模式变为PV模式
pos_trajectory_planning_DW_f kPosTrajDwTest = {0};      // 位置规划器内部缓存
linear_trajectory_planning_DW_f kSpeedTrajDwTest = {0}; // 速度规划器内部缓存
int8_T kSpeedTrajStateNowTest = 0;
#endif

// 静态函数声明
static void ModeRun(Axis *const axis, AxisDw *const axis_dw);
static void ModeCheckInInit(Axis *const axis, AxisDw *const axis_dw);
static void PosReferenceSignalTemp(const ReferenceSignalConfig *rtu_config,
                                   ReferenceSignalOutput *rty_output,
                                   reference_signal_DW_f *localDW);

#pragma region 内部数据库初始化
// 状态机初始化，在执行所有控制中断之前调用
void MotorCtlSmInit(Axis *const axis, AxisDw *const axis_dw)
{
   // 根据驱动器存储配置对参数进行初始化
   // 获取电机额定参数
   axis->pmsm_config.b = 1.0E-5F;
   axis->pmsm_config.fc = 1.0E-5F;
   axis->pmsm_config.j = 7.0E-6F;
   axis->pmsm_config.ld = 0.00056F;
   axis->pmsm_config.lq = 0.00056F;
   axis->pmsm_config.peak_current = 9.0F;
   axis->pmsm_config.pn = 4.0F;
   axis->pmsm_config.r = 1.02F;
   axis->pmsm_config.rated_current = 3.0F;
   axis->pmsm_config.speed_max_rpm = 3000.0F;
   axis->pmsm_config.tp_s = 10e-5f;
   axis->pmsm_config.tc_s = 5e-5f;
   axis->pmsm_config.enc_line_p_n = 4000;
   axis->pmsm_config.kt = 0.075f;                                                 // kt = 1.5*pn*flux
   axis->pmsm_config.flux = axis->pmsm_config.kt / (1.5f * axis->pmsm_config.pn); // flux = kt/(1.5*pn);

   // 初始化其他模块配置
   axis->motor_ctl_sm_config.mode = 0;
   axis->motor_ctl_sm_config.error_enable = 0x0000; // 关闭控制层所有保护
   axis->motor_ctl_sm_config.under_voltage_protection_V = 15.0F;
   axis->motor_ctl_sm_config.over_voltage_protection_V = 58.0F;
   axis->motor_ctl_sm_config.over_speed_protection_rad_s = 300.0F;
   axis->motor_ctl_sm_config.under_temperature_protection_d = -20.0F;
   axis->motor_ctl_sm_config.over_temperature_protection_d = 80.0F;
   axis->motor_ctl_sm_config.position_following_error_protection = 100000;
   axis->motor_ctl_sm_config.over_current_protection_A = 10.0F;

   axis->current_ctl_config.i_noise_A = 0.02;
   axis->current_ctl_config.comp_du_V = 0.35;
   axis->current_ctl_config.bandwidth_percentage = 100.0F;
   axis->current_ctl_config.dt_s = axis->pmsm_config.tc_s;
   axis->current_ctl_config.flux_wb = 0.0F;
   axis->current_ctl_config.kp_ld = 1.0 / axis->current_ctl_config.dt_s * 0.333 * 0.5 * axis->pmsm_config.ld;
   axis->current_ctl_config.ki_ld = axis->pmsm_config.r / axis->pmsm_config.ld;
   axis->current_ctl_config.kp_lq = axis->current_ctl_config.kp_ld;
   axis->current_ctl_config.ki_lq = axis->current_ctl_config.ki_ld;
   axis->current_ctl_config.pwm_duty_cycle_max = 0.9F;
   axis->current_ctl_config.phase_dir = 1;

   float wn = 1.0f / (2.12f * axis->pmsm_config.tc_s) * axis->current_ctl_config.bandwidth_percentage * 0.01f; // 电流环闭环带宽
   float delta = 8.0f;  // 速度环阻尼因子

   axis->pos_speed_ctl_config.aff = 0.0F;
   axis->pos_speed_ctl_config.vff = 1.0F;
   axis->pos_speed_ctl_config.enc_line_inv_p_n = 1.0f / axis->pmsm_config.enc_line_p_n; // 编码器分辨率倒数
   axis->pos_speed_ctl_config.j_kt = axis->pmsm_config.j / axis->pmsm_config.kt;        // kt = 0.05
   axis->pos_speed_ctl_config.ki_s = wn / (delta * delta);
   axis->pos_speed_ctl_config.kp_s = delta * axis->pos_speed_ctl_config.ki_s * axis->pos_speed_ctl_config.j_kt;
   axis->pos_speed_ctl_config.kp_p = delta * axis->pos_speed_ctl_config.ki_s * 0.25f * 0.5f;
   axis->pos_speed_ctl_config.speed_max_rad_s = 300.0F;
   axis->pos_speed_ctl_config.tp_s = axis->current_ctl_config.dt_s;
   axis->pos_speed_ctl_config.dob_wn_Hz = 400.0F;
   axis->pos_speed_ctl_config.dob_enable = 0;

   axis->speed_obs_pll_config.tp_s = axis->pmsm_config.tp_s;
   axis->speed_obs_pll_config.wn_Hz = 800.0F; // 默认速度观测器带宽 800Hz
   axis->speed_obs_pll_config.enc_line_inv_p_n = 1.0f / 4000.0f;
   axis->speed_obs_pll_config.speed_obs_max_rad_s = 400.0F;

   axis->elec_id_sin_config.dt_s = axis->pmsm_config.tp_s;
   axis->elec_id_sin_config.end_fs_Hz = 1.0F;
   axis->elec_id_sin_config.i_max_A = 1.0F;
   axis->elec_id_sin_config.init_fs_Hz = 500.0F;
   axis->elec_id_sin_config.target_time_s = 0.4F;
   axis->elec_id_sin_config.u_max_V = 12.0F;
   axis->elec_id_sin_config.wait_time_s = 0.2F;

   axis->mec_id_config.dt_s = axis->pmsm_config.tp_s;
   axis->mec_id_config.end_fs_Hz = 1000.0F;
   axis->mec_id_config.start_fs_Hz = 5.0F;
   axis->mec_id_config.target_time_s = 0.4F;
   axis->mec_id_config.i_max_A = 1.0F;
   axis->mec_id_config.search_speed_max_rad_s = 30.0F;
   axis->mec_id_config.wait_time_s = 0.2F;
   axis->mec_id_config.signal_type = 0U;

   axis->motor_ctl_sm_config.mode = 0;
   axis->motor_ctl_sm_config.under_voltage_protection_V = 15.0F;
   axis->motor_ctl_sm_config.over_voltage_protection_V = 58.0F;
   axis->motor_ctl_sm_config.over_speed_protection_rad_s = 1000.0F;
   axis->motor_ctl_sm_config.under_temperature_protection_d = -20.0F;
   axis->motor_ctl_sm_config.over_temperature_protection_d = 80.0F;
   axis->motor_ctl_sm_config.position_following_error_protection = 100000;

   axis->elec_angle_id_config.id_max_A = axis->pmsm_config.rated_current;
   axis->elec_angle_id_config.dt_s = axis->pmsm_config.tp_s;
   axis->elec_angle_id_config.method = 0U;
   axis->elec_angle_id_config.angle_add_rad = 0.0001F;
   axis->elec_angle_id_config.wait_time_s = 1.0F;
   axis->elec_angle_id_config.test_angle_rad = 0.5F;
   axis->elec_angle_id_config.current_slope_percentage = 0.5F;

   axis->direction_id_config.elec_angle_add_rad = 0.0005f;
   axis->direction_id_config.current_slope_percentage = 0.5f;
   axis->direction_id_config.id_tar_max_A = axis->pmsm_config.rated_current;

   axis->motor_pos_sensor_config.enc_line_p_n = 4000;
   axis->motor_pos_sensor_config.init_pos_p = 0;
   axis->motor_pos_sensor_config.pn = 4;
   axis->motor_pos_sensor_config.elec_angle_bias_rad = 0.0f;
   axis->motor_pos_sensor_config.dir = 1;

   axis->pole_pairs_id_config.elec_angle_add = 0.0005F;
   axis->pole_pairs_id_config.enc_line_p_n = 4000U;
   axis->pole_pairs_id_config.id_tar_max_A = axis->pmsm_config.rated_current;
   axis->pole_pairs_id_config.current_slope_percentage = 0.5F;

   axis->input_shaping_config.enable = 0;
   axis->input_shaping_config.run_frq_Hz = 10000.0f;
   axis->input_shaping_config.wn_Hz = 0.0f;

   axis->mit_ctl_config.kp_pos_NM_rad = 1.0f;
   axis->mit_ctl_config.kd_spd_NM_rad_s = 1.0f;
   axis->mit_ctl_config.enc_line_inv_p_n = 1.0f / axis->pmsm_config.enc_line_p_n; // 编码器分辨率倒数

   axis->load_pos_sensor_config.dir = 1;
   axis->load_pos_sensor_config.enc_line_p_n = 4000;
   axis->load_pos_sensor_config.init_pos_p = 0;

   axis->sim_plant_config.dt_s = axis->pmsm_config.tc_s / 5.0f;
   axis->sim_plant_config.j = axis->pmsm_config.j;
   axis->sim_plant_config.j_inv = 1.0f / axis->pmsm_config.j;
   axis->sim_plant_config.b = axis->pmsm_config.b;
   axis->sim_plant_config.fc = 0.001f;
   axis->sim_plant_config.flux = axis->pmsm_config.flux;
   axis->sim_plant_config.kt = axis->pmsm_config.kt;
   axis->sim_plant_config.pn = axis->pmsm_config.pn;
   axis->sim_plant_config.r = axis->pmsm_config.r;
   axis->sim_plant_config.ld = axis->pmsm_config.ld;
   axis->sim_plant_config.lq = axis->pmsm_config.lq;
   axis->sim_plant_config.ld_inv = 1.0f / axis->pmsm_config.ld;
   axis->sim_plant_config.lq_inv = 1.0f / axis->pmsm_config.lq;
   axis->sim_plant_config.enc_line_p_n = axis->pmsm_config.enc_line_p_n;
   axis->sim_plant_config.enc_line_init_pos_P = 0;
   axis->sim_plant_config.enc_noise = 1;

   MotorCtlParamSetUpdata(axis);

   // 数据库初始化将陷波滤波器都关闭
   axis->notch_filter_config.frq[0] = 0.0f;
   axis->notch_filter_config.frq[1] = 0.0f;
   axis->notch_filter_config.frq[2] = 0.0f;
   axis->notch_filter_config.frq[3] = 0.0f;
   axis->notch_filter_config.frq[4] = 0.0f;
   axis->notch_filter_config.frq[5] = 0.0f;

   notch_filter_config_set(&axis->notch_filter_config, &axis->pos_speed_ctl_config.tp_s,
                           &axis->notch_filter_internal);

   // 对各个模块内部缓存进行初始化
   current_ctl_loop_task_Init(&(axis_dw->current_ctl_loop_task_InstanceData.rtdw));

   pos_speed_ctl_pip_Init(&(axis_dw->pos_speed_ctl_pip_InstanceData.rtdw));

   notch_filter_Init(&(axis_dw->notch_filter_InstanceData.rtdw));

   speed_obs_pll_Init(&(axis_dw->speed_obs_pll_InstanceData.rtdw));

   elec_angle_id_Init(&(axis->elec_angle_id_output), &(axis_dw->elec_angle_id_InstanceData.rtdw));

   direction_id_initialize(&(axis_dw->direction_id_InstanceData.rtzce));
   direction_id_Init(&(axis_dw->direction_id_InstanceData.rtdw),
                     &(axis_dw->direction_id_InstanceData.rtzce));

   pole_pairs_id_initialize(&(axis_dw->pole_pairs_id_InstanceData.rtzce));
   pole_pairs_id_Init(&(axis_dw->pole_pairs_id_InstanceData.rtdw),
                      &(axis_dw->pole_pairs_id_InstanceData.rtzce));

   input_shaping_ei_Init(&(axis_dw->input_shaping_InstanceData.rtdw));

   tq_fc_id_Init(&axis->tq_fc_id_output, &(axis_dw->tq_fc_id_InstanceData.rtdw));

   sim_plant_Init(&(axis_dw->sim_plant_InstanceData.rtdw));
}

// 控制层内部状态变量初始化，执行位置环之前调用
// motor_init_pos_p 电机端编码器初始位置圈数
// motor_pos_now_p  电机端当前单圈位置
void MotorCtlSmStateInit(Axis *const axis, AxisDw *const axis_dw,
                         int64_T motor_circle_int_n, uint32_T motor_pos_now_p,
                         int64_T load_circle_int_n, uint32_T load_pos_now_p)
{
   axis->motor_pos_sensor_config.init_pos_p = motor_circle_int_n * axis->motor_pos_sensor_config.enc_line_p_n;
   // TODO：负载端多圈值处理

   axis_dw->motor_pos_sensor_InstanceData.rtdw.enc_counts_now_last = motor_pos_now_p;
   axis_dw->load_pos_sensor_InstanceData.rtdw.enc_counts_now_last = load_pos_now_p;

   axis->motor_pos_sensor_input.enc_counts_now_p = motor_pos_now_p;

   // 运行电机端位置传感器数据处理
   motor_pos_sensor(&axis->motor_pos_sensor_input,
                    &axis->motor_pos_sensor_config,
                    &axis->motor_pos_sensor_output,
                    &(axis_dw->motor_pos_sensor_InstanceData.rtdw));

   axis->pos_speed_ctl_input.pos_now_p = axis->motor_pos_sensor_output.enc_sum_p; // 获取电机端当前绝对位置

   // 运行负载端位置传感器数据处理
   load_pos_sensor(&axis->load_pos_sensor_input,
                   &axis->load_pos_sensor_config,
                   &axis->load_pos_sensor_output,
                   &(axis_dw->load_pos_sensor_InstanceData.rtdw));

   axis_dw->speed_obs_pll_InstanceData.rtdw.pos_now_p_last = axis->pos_speed_ctl_input.pos_now_p; // 初始化速度观测器当前位置

   // 运行速度观测器 进行速度估计
   axis->speed_obs_pll_input.pos_now_p = axis->pos_speed_ctl_input.pos_now_p;

   speed_obs_pll(&axis->speed_obs_pll_input, &axis->speed_obs_pll_config,
                 &axis->speed_obs_pll_output,
                 &(axis_dw->speed_obs_pll_InstanceData.rtdw));

   axis->pos_speed_ctl_input.speed_now_rad_s = axis->speed_obs_pll_output.ev_rad_s; // 速度观测器输出
}

// 控制层参数关联设置接口函数  失能状态下调用
void MotorCtlParamSetUpdata(Axis *const axis)
{
   /* 各辨识模块的"辨识电流"只做兜底，不再每周期强制覆盖。
    *
    * 原实现在这里直接把它们写成 pmsm_config.rated_current（= 电机额定电流的峰值，√2 倍）。
    * 而本函数被 AppParamSyncUser() 在位置环（1kHz）、失能状态下反复调用，后果是：
    *   1) 上位机/辨识 APP 写进去的辨识电流会在 1ms 内被改回去，辨识电流事实上不可配置；
    *   2) 该值（本机 1.697A）直接顶到 App 层 0.9×驱动器峰值 的保护线上。
    * 辨识电流现在由各辨识 APP 的 Init() 用 get_app_Motor_rated_current() 设置
    * （见 app/Identify/app_id_*_mode.c），这里只在"还没被设置过"时用额定值兜底，
    * 因此 fresh boot 后的默认行为与原工程一致。 */
   if (axis->elec_id_sin_config.i_max_A <= 0.0f)
   {
      axis->elec_id_sin_config.i_max_A = axis->pmsm_config.rated_current;
   }
   if (axis->mec_id_config.i_max_A <= 0.0f)
   {
      axis->mec_id_config.i_max_A = axis->pmsm_config.rated_current;
   }
   if (axis->elec_angle_id_config.id_max_A <= 0.0f)
   {
      axis->elec_angle_id_config.id_max_A = axis->pmsm_config.rated_current;
   }
   if (axis->pole_pairs_id_config.id_tar_max_A <= 0.0f)
   {
      axis->pole_pairs_id_config.id_tar_max_A = axis->pmsm_config.rated_current;
   }
   if (axis->direction_id_config.id_tar_max_A <= 0.0f)
   {
      axis->direction_id_config.id_tar_max_A = axis->pmsm_config.rated_current;
   }
   axis->motor_ctl_sm_config.over_current_protection_A = axis->pmsm_config.peak_current * 1.2f;

   // 极对数
   axis->motor_pos_sensor_config.pn = axis->pmsm_config.pn;

   // 转矩常数和永磁磁链 关联更新                                              // kt = 1.5*pn*flux
   axis->pmsm_config.flux = axis->pmsm_config.kt / (1.5f * axis->pmsm_config.pn); // flux = kt/(1.5*pn);
   axis->pos_speed_ctl_config.j_kt = axis->pmsm_config.j / axis->pmsm_config.kt;
   axis->mit_ctl_config.kt_NM_A = axis->pmsm_config.kt; // 关联设置

   // 电机最大转速
   axis->pos_speed_ctl_config.speed_max_rad_s = axis->pmsm_config.speed_max_rpm * MOTOR_CTL_SM_RPM_2_RAD_S;
   axis->speed_obs_pll_config.speed_obs_max_rad_s = axis->pmsm_config.speed_max_rpm * MOTOR_CTL_SM_RPM_2_RAD_S * 1.2f;

   // 位置环运行周期
   axis->elec_id_sin_config.dt_s = axis->pmsm_config.tp_s;
   axis->input_shaping_config.run_frq_Hz = 1.0f / axis->pmsm_config.tp_s;
   axis->mec_id_config.dt_s = axis->pmsm_config.tp_s;
   axis->pos_speed_ctl_config.tp_s = axis->pmsm_config.tp_s;
   axis->speed_obs_pll_config.tp_s = axis->pmsm_config.tp_s;
   axis->elec_angle_id_config.dt_s = axis->pmsm_config.tp_s;
   axis->reciprocal_motion_config.dt_s = axis->pmsm_config.tp_s;
   axis->reference_signal_config.dt_s = axis->pmsm_config.tp_s;

   // 电流环运行周期
   axis->current_ctl_config.dt_s = axis->pmsm_config.tc_s;

   // 编码器分辨率
   uint32_t enc_line_p_n = (axis->pmsm_config.enc_line_p_n == 0 ? 1 : axis->pmsm_config.enc_line_p_n);
   axis->pos_speed_ctl_config.enc_line_inv_p_n = 1.0f / enc_line_p_n;
   axis->speed_obs_pll_config.enc_line_inv_p_n = 1.0f / enc_line_p_n;
   axis->motor_pos_sensor_config.enc_line_p_n = enc_line_p_n;
   axis->pole_pairs_id_config.enc_line_p_n = enc_line_p_n;
   axis->tq_fc_id_config.enc_line_p_n = enc_line_p_n;
   axis->mit_ctl_config.enc_line_inv_p_n = 1.0f / enc_line_p_n; // 编码器分辨率倒数

   // 陷波滤波器参数关联更新
   notch_filter_config_set(&axis->notch_filter_config, &axis->pos_speed_ctl_config.tp_s,
                           &axis->notch_filter_internal);
}
#pragma endregion

#pragma region 控制中断任务
// 电流环中断调用
void CurrentCtlLoopTask(Axis *const axis, AxisDw *const axis_dw)
{
   current_ctl_loop_task(&axis->current_ctl_input, &axis->current_ctl_config,
                         &axis->current_ctl_output,
                         &(axis_dw->current_ctl_loop_task_InstanceData.rtdw));
}

// 位置环中断调用
void PosSpeedCtlLoopTask(Axis *const axis, AxisDw *const axis_dw)
{
   uint32_T error_code = 0;

   // 运行电机端位置传感器数据处理
   motor_pos_sensor(&axis->motor_pos_sensor_input,
                    &axis->motor_pos_sensor_config,
                    &axis->motor_pos_sensor_output,
                    &(axis_dw->motor_pos_sensor_InstanceData.rtdw));

   axis->pos_speed_ctl_input.pos_now_p = axis->motor_pos_sensor_output.enc_sum_p; // 获取电机端当前绝对位置

   // 运行负载端位置传感器数据处理
   load_pos_sensor(&axis->load_pos_sensor_input,
                   &axis->load_pos_sensor_config,
                   &axis->load_pos_sensor_output,
                   &(axis_dw->load_pos_sensor_InstanceData.rtdw));

   // 运行速度观测器 进行速度估计
   axis->speed_obs_pll_input.pos_now_p = axis->pos_speed_ctl_input.pos_now_p;

   speed_obs_pll(&axis->speed_obs_pll_input, &axis->speed_obs_pll_config,
                 &axis->speed_obs_pll_output,
                 &(axis_dw->speed_obs_pll_InstanceData.rtdw));

   axis->pos_speed_ctl_input.speed_now_rad_s = axis->speed_obs_pll_output.ev_rad_s; // 速度观测器输出

   // 保护检测  更新状态机错误代码
   protect_check(&axis->current_ctl_input.iabc_now_A[0], &axis->current_ctl_input.dc_bus_now_V,
                 &axis->current_ctl_input.driver_temp,
                 &axis->pos_speed_ctl_output.pos_ctl_error_p,
                 &axis->pos_speed_ctl_input.speed_now_rad_s,
                 &axis->motor_ctl_sm_config,
                 &error_code);

   // 状态机切换
   // 错误状态
   if (error_code != MOTOR_CTL_SM_NONE_ERROR) // 有错误 进入错误状态
   {
      axis->motor_ctl_sm_output.state = MOTOR_CTL_SM_STATE_ERROR;
      axis->motor_ctl_sm_output.error = error_code;
   }

   if (axis->motor_ctl_sm_output.state == MOTOR_CTL_SM_STATE_ERROR)
   {
      if (axis->motor_ctl_sm_input.motor_enable == MOTOR_CTL_SM_MOTOR_CLEAR_ERROR &&
          axis->motor_ctl_sm_output.motor_enable_last == MOTOR_CTL_SM_MOTOR_DISABLE) // 清除错误  0->3 清除错误
      {
         axis->pos_speed_ctl_output.pos_ctl_error_p = 0;               // 清除位置跟随误差
         axis->motor_ctl_sm_output.state = MOTOR_CTL_SM_STATE_DISABLE; // 进入空闲状态
         axis->motor_ctl_sm_output.error = MOTOR_CTL_SM_NONE_ERROR;    // 清除错误
      }
      axis->motor_ctl_sm_output.motor_enable_last = axis->motor_ctl_sm_input.motor_enable;
      return; // 没有清除错误指令 直接退出
   }

   // 其他状态下 失能指令会立即进入失能状态
   if (axis->motor_ctl_sm_input.motor_enable == MOTOR_CTL_SM_MOTOR_DISABLE) // 失能电机状态
   {
      axis->motor_ctl_sm_output.state = MOTOR_CTL_SM_STATE_DISABLE; // 进入失能状态
   }

   // 失能状态
   if (axis->motor_ctl_sm_output.state == MOTOR_CTL_SM_STATE_DISABLE)
   {
      // 电流环 进入 电压控制  输出电压为 0
      axis->current_ctl_input.idq_tar_A[0] = 0.0f;
      axis->current_ctl_input.idq_tar_A[1] = 0.0f;
      axis->current_ctl_input.mode = 0; // 电压直接控制模式
      axis->current_ctl_input.uabc_tar_V[0] = 0.0f;
      axis->current_ctl_input.uabc_tar_V[1] = 0.0f;
      axis->current_ctl_input.uabc_tar_V[2] = 0.0f;
      axis->pos_speed_ctl_output.pos_ctl_error_p = 0; // 清除位置跟随误差
   }

   // 空闲状态
   if (axis->motor_ctl_sm_output.state == MOTOR_CTL_SM_STATE_DISABLE) // 空闲状态等待使能指令
   {
      // 使能状态  0->1 电机进入使能状态
      if (axis->motor_ctl_sm_input.motor_enable == MOTOR_CTL_SM_MOTOR_ENABLE &&
          axis->motor_ctl_sm_output.motor_enable_last == MOTOR_CTL_SM_MOTOR_DISABLE)
      {
         ModeCheckInInit(axis, axis_dw);                              // 使能前初始化
         axis->motor_ctl_sm_output.state = MOTOR_CTL_SM_STATE_ENABLE; // 进入使能状态
      }
   }

   // 使能状态 且 硬件准备就绪
   if (axis->motor_ctl_sm_output.state == MOTOR_CTL_SM_STATE_ENABLE)
   {
      if (axis->motor_ctl_sm_input.hw_ready_state)
      {
         ModeRun(axis, axis_dw); // 模式运行
      }
   }

   // 记录上个周期指令和状态
   axis->motor_ctl_sm_output.motor_enable_last = axis->motor_ctl_sm_input.motor_enable;
}

#pragma endregion

#pragma region 模式从失能到使能切换，状态初始化
// 模型运行 从失能状态 切入 使能状态 初始化各个模块
static void ModeCheckInInit(Axis *const axis, AxisDw *const axis_dw)
{
   switch (axis->motor_ctl_sm_config.mode)
   {
   case MOTOR_CTL_SM_MODE_POSITION:
      /* code */
      break;
   case MOTOR_CTL_SM_MODE_SPEED:
      /* code */
      break;
   case MOTOR_CTL_SM_MODE_IDLE:
      /* code */
      break;
   case MOTOR_CTL_SM_MODE_TORQUE:
      /* code */
      break;
   case MOTOR_CTL_SM_MODE_TQ_FRICTION_IDENTIFICATION:
      tq_fc_id_Init(&axis->tq_fc_id_output, &(axis_dw->tq_fc_id_InstanceData.rtdw));
      axis->tq_fc_id_input.pos_init_p = axis->motor_pos_sensor_output.enc_sum_p;
#if defined(PORT_PATCH_TQFC_POS_TAR_INIT) && (PORT_PATCH_TQFC_POS_TAR_INIT)
      /* [移植补丁] 重新进入本辨识时：
       * 1) 复位状态机——上一次中止会留下 ERROR(-1)，不复位的话再进就直接报错、
       *    电机使能不上（TqFcIdStep 在 ERROR 分支里每周期强制失能）。
       * 2) 位置目标对齐到当前位置——否则 pos_tar_p 是陈旧值，位置环跟随误差可达
       *    几十万 counts，kp_p=20 一乘直接把速度给定顶到几百万 p/s → 飞车。
       * 见 doc/PORTING_PATCHES.md 补丁 9。 */
      axis->tq_fc_id_output.state_now = IDENTIFICATION_MODE_STATE_IDLE;
      axis->tq_fc_id_input.start = 0;
      axis->pos_speed_ctl_input.pos_tar_p = axis->motor_pos_sensor_output.enc_sum_p;
#endif
      break;
   case MOTOR_CTL_SM_MODE_MECHANICAL_IDENTIFICATION:
      break;
   case MOTOR_CTL_SM_MODE_ELECTRIC_ANGLE_IDENTIFICATION:
      elec_angle_id_Init(&(axis->elec_angle_id_output), &(axis_dw->elec_angle_id_InstanceData.rtdw));
      axis->elec_angle_id_output.state_now = IDENTIFICATION_MODE_STATE_IDLE;
      axis->motor_pos_sensor_config.elec_angle_bias_rad = 0.0f;
      break;
   case MOTOR_CTL_SM_MODE_DIRECTION_IDENTIFICATION:
      direction_id_initialize(&(axis_dw->direction_id_InstanceData.rtzce));
      direction_id_Init(&(axis_dw->direction_id_InstanceData.rtdw),
                        &(axis_dw->direction_id_InstanceData.rtzce));
      axis->direction_id_output.state_now = IDENTIFICATION_MODE_STATE_IDLE;
      break;
   case MOTOR_CTL_SM_MODE_POLE_PAIRS_IDENTIFICATION:
      pole_pairs_id_initialize(&(axis_dw->pole_pairs_id_InstanceData.rtzce));
      pole_pairs_id_Init(&(axis_dw->pole_pairs_id_InstanceData.rtdw),
                         &(axis_dw->pole_pairs_id_InstanceData.rtzce));
      axis->pole_pairs_id_output.state_now = IDENTIFICATION_MODE_STATE_IDLE;
      break;
   case MOTOR_CTL_SM_MODE_ELECTRIC_IDENTIFICATION:
      break;
   case MOTOR_CTL_SM_MODE_RECIPROCAL_MOTION:
      reciprocal_motion_Init();

      axis_dw->reciprocal_motion_InstanceData.rtdw.pos_last = axis->motor_pos_sensor_output.enc_sum_p;
      axis_dw->reciprocal_motion_InstanceData.rtdw.q0_int = axis->motor_pos_sensor_output.enc_sum_p;
      axis_dw->reciprocal_motion_InstanceData.rtdw.x = axis->motor_pos_sensor_output.enc_sum_p;
      axis_dw->reciprocal_motion_InstanceData.rtdw.times = 0.0f;
      axis_dw->reciprocal_motion_InstanceData.rtdw.q0_dec = 0.0f;
      axis_dw->reciprocal_motion_InstanceData.rtdw.pos_id = true;

      break;
   case MOTOR_CTL_SM_MODE_REFERENCE_SIGNAL:
      axis_dw->reference_signal_InstanceData.rtdw.sin_time = 0.0f;
      axis_dw->reference_signal_InstanceData.rtdw.times = 0.0f;
      axis->reference_signal_config.signal_start_pos = axis->motor_pos_sensor_output.enc_sum_p;
      reference_signal_Init(&(axis_dw->reference_signal_InstanceData.rtdw));
      break;
   case MOTOR_CTL_SM_MODE_MIT:

      break;
   default:
      break;
   }

#ifdef MOTOR_CTL_DEBUG // 控制层调试模式，加入规划器

   kPosTrajDwTest.q0_int = axis->pos_speed_ctl_input.pos_now_p;
   kPosTrajDwTest.q0_dec = 0.0f;
   kPosTrajDwTest.dq0 = 0.0f;
   kPosTrajDwTest.x = axis->pos_speed_ctl_input.pos_now_p;

   kSpeedTrajDwTest.traj_now = axis->pos_speed_ctl_input.speed_now_rad_s /
                               MOTOR_CTL_SM_TWO_PI * axis->pmsm_config.enc_line_p_n; // 从当前速度开始规划  p/s
#endif

   axis->current_ctl_input.elec_angle_speed_rad_s = 0.0f;                     // 获取当前电角速度
   axis->input_shaping_input.pos_cmd_p = axis->pos_speed_ctl_input.pos_now_p; // 位置环输入指令
   axis->input_shaping_input.pos_cmd_p_init = axis->pos_speed_ctl_input.pos_now_p;
   axis->pos_speed_ctl_input.pos_tar_p = axis->pos_speed_ctl_input.pos_now_p;

   current_ctl_loop_task_Init(&(axis_dw->current_ctl_loop_task_InstanceData.rtdw));
   pos_speed_ctl_pip_Init(&(axis_dw->pos_speed_ctl_pip_InstanceData.rtdw));
   notch_filter_Init(&(axis_dw->notch_filter_InstanceData.rtdw));

   axis_dw->pos_speed_ctl_pip_InstanceData.rtdw.pos_now_pulse_last = axis->pos_speed_ctl_input.pos_now_p;
}
#pragma endregion

#pragma region 控制步骤模块
// 指令电流滤波
static inline void CommandCurrentFilter(Axis *const axis, AxisDw *const axis_dw)
{
   // 执行陷波滤波器
   axis->notch_filter_input.iq_tar_A = axis->pos_speed_ctl_output.iq_tar_A;
   notch_filter(&axis->notch_filter_input, &axis->notch_filter_internal,
                &axis->notch_filter_output,
                &(axis_dw->notch_filter_InstanceData.rtdw));

   // TODO: 执行低通滤波器
   axis->current_ctl_input.elec_angle_speed_rad_s =
       axis->pos_speed_ctl_input.speed_now_rad_s * axis->pmsm_config.pn; // 获取当前电角速度

   axis->current_ctl_input.elec_theta_rad = axis->motor_pos_sensor_output.elec_angle_now_rad; // 获取当前电角度;
   axis->current_ctl_input.idq_tar_A[0] = 0.0f;                                               // TODO：考虑 用户设定弱磁控制情况
   axis->current_ctl_input.idq_tar_A[1] = axis->notch_filter_output.iq_tar_filter_A;
   axis->current_ctl_input.mode = 1; // 电流控制模式
}

// 转矩脉动和摩擦补偿运行函数  在速度控制器输出指令电流后，进行陷波滤波器之前调用
static inline void TqFcComStep(Axis *const axis, AxisDw *const axis_dw)
{
   uint32_T index = 0;

   if (axis->tq_fc_id_config.tq_com_enable == 1)
   {
      index = (float)(axis->motor_pos_sensor_input.enc_counts_now_p) /
              (float)axis->pmsm_config.enc_line_p_n * axis_dw->tq_fc_id_InstanceData.rtdw.index_max;

      if (index < axis_dw->tq_fc_id_InstanceData.rtdw.index_max)
      {
         axis->pos_speed_ctl_output.iq_tar_A -= axis_dw->tq_fc_id_InstanceData.rtdw.com_table[index];
      }
      if (index >= axis_dw->tq_fc_id_InstanceData.rtdw.index_max)
      {
         index = axis_dw->tq_fc_id_InstanceData.rtdw.index_max - 1;
         // TODO:error
      }
   }

   if (axis->tq_fc_id_config.fc_com_enable == 1)
   {
      //TODO：摩擦补偿这里还可以优化 更加平滑  目前是简单阶跃补偿 
      // 进行摩擦补偿， 以指令速度方向补偿
      if (axis->pos_speed_ctl_input.speed_tar_p_s > 0.0f)
      {
         axis->pos_speed_ctl_output.iq_tar_A += axis->tq_fc_id_config.fc_p_com;
      }
      else if (axis->pos_speed_ctl_input.speed_tar_p_s < -0.0f)
      {
         axis->pos_speed_ctl_output.iq_tar_A += axis->tq_fc_id_config.fc_n_com;
      }
   }
}

#pragma endregion

#pragma region 模式运行函数
// 转矩脉动辨识
static void TqFcIdStep(Axis *const axis, AxisDw *const axis_dw)
{
   uint32_T index = 0;
   float fc_hz = 100.0f;                       // 100Hz截止频率
   float lpf_k = 0.38f;                        // 低通滤波系数
#if defined(PORT_PATCH_TQFC_ID_SPEED) && (PORT_PATCH_TQFC_ID_SPEED)
   /* [移植补丁] 辨识转速从 10rpm 提到 TQ_FC_ID_SPEED_RPM。
    * 原因：本机电机静止通电时有 ±1.5~2.7° 的定位力微振（编码器实测 ±30~120 counts），
    * 若振动在几十 Hz，其峰值角速度达 10~15 rad/s，比 10rpm(1.05rad/s) 的目标速度
    * 大一个数量级——位置环被扰动主导，实测 kp_p 从 0.5 调到 20 都只是原地振荡、
    * 净转动≈0。提高辨识转速后信噪比提高一个数量级，环才有可能压住。
    * 代价：转矩脉动表的转速分辨率变差，但总比跑不了强。见补丁 10。 */
   float speed_tar_rpm = TQ_FC_ID_SPEED_RPM;
#else
   float speed_tar_rpm = TQ_FC_COM_MIN_SPEED_RAD_S * MATH_RAD2RPM; // 转矩脉动辨识速度低速 10RPM
#endif

#if defined(PORT_PATCH_ID_ABORT_ON_RUNAWAY) && (PORT_PATCH_ID_ABORT_ON_RUNAWAY)
   /* [移植补丁] 辨识跑飞 / 卡死保护。
    * 本机低速位置环压不住（编码器开波抖动折合 ±48rpm，远超 10rpm 设计转速），
    * 转矩脉动辨识实测会反向飞转；而阶段 1 的完成条件是
    *     (enc_sum_p - pos_init_p) >= enc_line_p_n   // 必须"正向"转满一圈
    * 反向飞转时这个差值越来越负，永远不成立 → 状态机卡在 STABLE_INCENTIVE，
    * APP 一直 RUNNING，上位机表现为"一直辨识中、停不下来、没有结果"。
    * 这里加两条兜底：转速超限持续 200ms，或总时长超过 60s，就置错误并关波。 */
   {
      static uint16_t s_over_speed_ms = 0;
      static uint16_t s_total_ms = 0;
      uint8_t abort_id = 0;

      if (axis->tq_fc_id_output.state_now == IDENTIFICATION_MODE_STATE_ERROR)
      {
         axis->current_ctl_input.idq_tar_A[0] = 0.0f;
         axis->current_ctl_input.idq_tar_A[1] = 0.0f;
         axis->current_ctl_input.mode = 1;
         axis->motor_ctl_sm_output.state = MOTOR_CTL_SM_STATE_DISABLE;
         return;
      }

      if (axis->motor_ctl_sm_output.state != MOTOR_CTL_SM_STATE_ENABLE)
      {
         s_over_speed_ms = 0;
         s_total_ms = 0;
      }
      else if (axis->tq_fc_id_output.state_now != IDENTIFICATION_MODE_STATE_FINISH)
      {
         s_total_ms++;

         /* 启动宽限：使能瞬间速度观测器会有 ±20rad/s 甚至更大的尖峰（实测），
          * 所以不看速度、改看位置跟随误差——它才是"跟不上目标/跑飞"的直接指标。 */
         if (s_total_ms > TQ_FC_ID_GRACE_MS)
         {
            int32_T perr = axis->pos_speed_ctl_output.pos_ctl_error_p;

            if ((perr > TQ_FC_ID_ABORT_ERR_P) || (perr < -TQ_FC_ID_ABORT_ERR_P))
            {
               if (++s_over_speed_ms > 200U)
               {
                  abort_id = 1;
               }
            }
            else
            {
               s_over_speed_ms = 0;
            }
         }

         if (s_total_ms > TQ_FC_ID_TIMEOUT_MS)
         {
            abort_id = 1;
         }
      }

      if (abort_id != 0U)
      {
         s_over_speed_ms = 0;
         s_total_ms = 0;
         axis->tq_fc_id_input.start = 0;
         axis->tq_fc_id_output.state_now = IDENTIFICATION_MODE_STATE_ERROR;
         axis->current_ctl_input.idq_tar_A[0] = 0.0f;
         axis->current_ctl_input.idq_tar_A[1] = 0.0f;
         axis->current_ctl_input.mode = 1;
         axis->motor_ctl_sm_output.state = MOTOR_CTL_SM_STATE_DISABLE;
         return;
      }
   }
#endif

   if (axis->tq_fc_id_output.state_now == IDENTIFICATION_MODE_STATE_IDLE)
   {
      axis->tq_fc_id_input.start = 1;            // 启动转矩脉动辨识
      axis->tq_fc_id_input.pos_abs_p = 0;        // 绝对位置计数器清零
#if defined(PORT_PATCH_TQFC_POS_TAR_INIT) && (PORT_PATCH_TQFC_POS_TAR_INIT)
      /* [移植补丁] 把位置目标对齐到当前位置再开始。
       * 上游这里没有初始化 pos_tar_p，它会保留上一次的陈旧值；而位置环
       * speed_tar = kp_p * (pos_tar - pos_now)，kp_p=20。实测进辨识瞬间
       * pos_tar_p=6899、pos_now_p=-534146，跟随误差 541045 counts，
       * 速度给定直接到 1e7 p/s（远超限幅）→ 电机反向飞转、剧烈震动，
       * 而且阶段 1 要求"正向转满一圈"永远不成立 → 卡住不结束。
       * 见 doc/PORTING_PATCHES.md 补丁 9。 */
      axis->pos_speed_ctl_input.pos_tar_p = axis->motor_pos_sensor_output.enc_sum_p;
#endif
#if defined(PORT_PATCH_TQFC_ID_DOB) && (PORT_PATCH_TQFC_ID_DOB)
      /* [移植补丁] 辨识期间保留扰动观测器（DOB）。
       * 上游这里把 dob_enable 关 0，而摩擦系数正是从 dob_iq_com_A 采出来的
       * （fc_n_com 由 iq_com_A 低通得到），DOB 一关那条通路恒为 0，
       * 实测辨识跑完 fc_p_com / fc_n_com 都是 0.0，等于摩擦项白辨识。
       * 见补丁 11。 */
      axis->pos_speed_ctl_config.dob_enable = 1; // 保留扰动观测器（摩擦辨识需要它）
#else
      axis->pos_speed_ctl_config.dob_enable = 0; // 关闭扰动观测器
#endif
      axis->tq_fc_id_config.tq_com_enable = 0;   // 关闭转矩脉动补偿
      axis->tq_fc_id_config.fc_com_enable = 0;   // 关闭摩擦补偿
      axis->tq_fc_id_output.state_now = IDENTIFICATION_MODE_STATE_SEARCH;
   }
   if (axis->tq_fc_id_input.start == 1) // 转矩脉动辨识阶段
   {
      if (axis->tq_fc_id_output.state_now == IDENTIFICATION_MODE_STATE_SEARCH) // 等待位置模式运行稳定 等待 0.5s
      {
         // 一直更新目标位置  以10RPM匀速运行
         axis->pos_speed_ctl_input.pos_tar_p += speed_tar_rpm / 60.0f * axis->pmsm_config.enc_line_p_n * axis->pmsm_config.tp_s; // 10RPM匀速运行

         axis->tq_fc_id_input.pos_abs_p++;                                             // 充当计数器使用
         if ((float)(axis->tq_fc_id_input.pos_abs_p) * axis->pmsm_config.tp_s >= 0.5f) // 等待 0.5s
         {
            axis->tq_fc_id_input.pos_init_p = axis->motor_pos_sensor_output.enc_sum_p;      // 记录累计初始位置
            axis->tq_fc_id_input.pos_abs_p = axis->motor_pos_sensor_input.enc_counts_now_p; // 记录单圈绝对位置信息
            axis->tq_fc_id_output.state_now = IDENTIFICATION_MODE_STATE_STABLE_INCENTIVE;
         }
      }
      else if (axis->tq_fc_id_output.state_now == IDENTIFICATION_MODE_STATE_STABLE_INCENTIVE) // 稳定匀速运行阶段
      {
         // 一直更新目标位置  以10RPM匀速运行
         axis->pos_speed_ctl_input.pos_tar_p += speed_tar_rpm / 60.0f * axis->pmsm_config.enc_line_p_n * axis->pmsm_config.tp_s; // 10RPM匀速运行

         // 记录负载观测器补偿电流值
         axis->tq_fc_id_input.iq_com_A = axis->pos_speed_ctl_output.dob_iq_com_A;

         index = (float)(axis->motor_pos_sensor_input.enc_counts_now_p) /
                 (float)axis->pmsm_config.enc_line_p_n * axis_dw->tq_fc_id_InstanceData.rtdw.index_max;

         if (index >= axis_dw->tq_fc_id_InstanceData.rtdw.index_max)
         {
            index = axis_dw->tq_fc_id_InstanceData.rtdw.index_max - 1;
         }

         axis_dw->tq_fc_id_InstanceData.rtdw.com_table[index] = axis->tq_fc_id_input.iq_com_A;

         if ((axis->motor_pos_sensor_output.enc_sum_p - axis->tq_fc_id_input.pos_init_p) >=
             axis->pmsm_config.enc_line_p_n)
         {
            // 旋转一圈后 进入到摩擦辨识 速度切换到 1RPM
            // 开启摩擦辨识  此方法假设摩擦力是正负运动方向对称的
            axis->tq_fc_id_input.start = 2;
            axis->tq_fc_id_input.pos_abs_p = 0;
            axis->tq_fc_id_output.state_now = IDENTIFICATION_MODE_STATE_SEARCH;
            // 开启转矩脉动补偿
            axis->tq_fc_id_config.tq_com_enable = 1;
         }
      }
   }
   else if (axis->tq_fc_id_input.start == 2) // 摩擦辨识阶段
   {
      if (axis->tq_fc_id_output.state_now == IDENTIFICATION_MODE_STATE_SEARCH)
      {
         // 一直更新目标位置  以-10RPM匀速运行
         axis->pos_speed_ctl_input.pos_tar_p -= speed_tar_rpm / 60.0f * axis->pmsm_config.enc_line_p_n * axis->pmsm_config.tp_s; // -10RPM匀速运行

         axis->tq_fc_id_input.pos_abs_p++; // 充当计数器使用

         axis->tq_fc_id_input.iq_com_A = axis->pos_speed_ctl_output.dob_iq_com_A; // 获取反向2倍的摩擦力

         // 低通滤波
         math_lib_set_first_order_lpf_iir_config(&fc_hz, &axis->pmsm_config.tp_s, &lpf_k);

         math_lib_first_order_lpf_iir(&axis->tq_fc_id_input.iq_com_A, &lpf_k,
                                      &axis->tq_fc_id_config.fc_n_com,
                                      &axis->tq_fc_id_config.fc_n_com);

         if ((float)(axis->tq_fc_id_input.pos_abs_p) * axis->pmsm_config.tp_s >= 5.0f) // 等待 5s
         {
            axis->tq_fc_id_input.pos_init_p = axis->motor_pos_sensor_output.enc_sum_p;      // 记录累计初始位置
            axis->tq_fc_id_input.pos_abs_p = axis->motor_pos_sensor_input.enc_counts_now_p; // 记录单圈绝对位置信息
            axis->tq_fc_id_output.state_now = IDENTIFICATION_MODE_STATE_STABLE_INCENTIVE;
         }
      }
      else if (axis->tq_fc_id_output.state_now == IDENTIFICATION_MODE_STATE_STABLE_INCENTIVE) // 匀速稳定后进行摩擦力辨识
      {
         // 一直更新目标位置  以-10RPM匀速运行
         axis->pos_speed_ctl_input.pos_tar_p -= speed_tar_rpm / 60.0f * axis->pmsm_config.enc_line_p_n * axis->pmsm_config.tp_s; // -1RPM匀速运行

         // 记录负载观测器补偿电流值
         axis->tq_fc_id_input.iq_com_A = axis->pos_speed_ctl_output.dob_iq_com_A;

         // 低通滤波
         math_lib_set_first_order_lpf_iir_config(&fc_hz, &axis->pmsm_config.tp_s, &lpf_k);

         math_lib_first_order_lpf_iir(&axis->tq_fc_id_input.iq_com_A, &lpf_k,
                                      &axis->tq_fc_id_config.fc_n_com,
                                      &axis->tq_fc_id_config.fc_n_com);

         // 辨识完成、分离转矩脉动辨识补偿表，计算摩擦力
         axis->tq_fc_id_config.fc_p_com = axis->tq_fc_id_config.fc_n_com * 0.5f;
         axis->tq_fc_id_config.fc_n_com = -axis->tq_fc_id_config.fc_p_com;

         for (uint32_T i = 0; i < axis_dw->tq_fc_id_InstanceData.rtdw.index_max; i++)
         {
            axis_dw->tq_fc_id_InstanceData.rtdw.com_table[i] += axis->tq_fc_id_config.fc_p_com;
         }
         axis->tq_fc_id_output.state_now = IDENTIFICATION_MODE_STATE_FINISH;
      }
   }

   axis->pos_speed_ctl_config.mode = POS_SPEED_CTL_MODE_POSITION; // 一直运行位置模式匀速
   pos_speed_ctl_pip(
       &axis->pos_speed_ctl_input,
       &axis->pos_speed_ctl_config,
       &axis->pos_speed_ctl_output,
       &(axis_dw->pos_speed_ctl_pip_InstanceData.rtdw));

   // 转矩脉动与摩擦补偿
   TqFcComStep(axis, axis_dw);

   // 指令电流滤波
   CommandCurrentFilter(axis, axis_dw);

   if (axis->tq_fc_id_output.state_now == IDENTIFICATION_MODE_STATE_FINISH) // 辨识完成 自动失能
   {
      axis->tq_fc_id_input.start = 0;
#if defined(PORT_PATCH_TQFC_LEAVE_COMP_OFF) && (PORT_PATCH_TQFC_LEAVE_COMP_OFF)
      /* [移植补丁] 辨识完成时不自动打开补偿开关。
       * 上游这里直接把 tq_com_enable / fc_com_enable 置 1，等于"辨识完立刻投入补偿"。
       * 实测本机这样做会直接把环路搞崩：辨识出 fc_p_com≈0.143A，一启用，
       * 速度模式在给定 0 时就自己飙到 −889rad/s（±0.143A 的符号在零速附近来回翻，
       * 形成自持振荡）。关掉补偿开关后同样的测试立刻稳定（±1.7rad/s）。
       * 所以改成只把数据算出来，是否启用由人确认后再手动打开。见补丁 12。 */
      axis->tq_fc_id_config.tq_com_enable = 0; // 不自动启用转矩脉动补偿
      axis->tq_fc_id_config.fc_com_enable = 0; // 不自动启用摩擦补偿
#else
      // 开启所有补偿开关
      axis->tq_fc_id_config.tq_com_enable = 1; // 开启转矩脉动补偿
      axis->tq_fc_id_config.fc_com_enable = 1; // 开启摩擦补偿
#endif

      axis->motor_ctl_sm_output.state = MOTOR_CTL_SM_STATE_DISABLE;
   }
}

// 机械特性辨识
static void MecIdStep(Axis *const axis, AxisDw *const axis_dw)
{
   axis->current_ctl_input.elec_angle_speed_rad_s =
       axis->pos_speed_ctl_input.speed_now_rad_s * axis->pmsm_config.pn;                      // 获取当前电角速度
   axis->current_ctl_input.elec_theta_rad = axis->motor_pos_sensor_output.elec_angle_now_rad; // 获取当前电角度
   axis->current_ctl_input.idq_tar_A[0] = 0.0f;
   axis->current_ctl_input.idq_tar_A[1] = axis->mec_id_output.iq_tar_A;
   axis->current_ctl_input.mode = 1; // 电流控制模式

   if (axis->mec_id_output.state_now == IDENTIFICATION_MODE_STATE_FINISH) // 辨识完成 自动失能
   {
      // mec_id_chirp_Init(&axis->mec_id_output, &(axis_dw->mec_id_chirp_InstanceData.rtdw)); // 重新初始化模块 等待下次启动
      axis->motor_ctl_sm_output.state = MOTOR_CTL_SM_STATE_DISABLE;
   }
}

// 电角度辨识模式
static void ElecAngleIdStep(Axis *const axis, AxisDw *const axis_dw)
{
   axis->elec_angle_id_input.pos_now_rad = (float)axis->pos_speed_ctl_input.pos_now_p;
   axis->current_ctl_input.elec_angle_speed_rad_s = 0.0f;

   if (axis->elec_angle_id_output.state_now < IDENTIFICATION_MODE_STATE_STABLE_INCENTIVE) // 搜索阶段
   {
      axis_dw->elec_angle_id_InstanceData.rtdw.time_counts += axis->pmsm_config.tp_s;

      if (axis_dw->elec_angle_id_InstanceData.rtdw.time_counts >= axis->elec_angle_id_config.wait_time_s * 3.0f)
      {
         axis_dw->elec_angle_id_InstanceData.rtdw.time_counts = 0.0f;
         axis->elec_angle_id_output.state_now = IDENTIFICATION_MODE_STATE_STABLE_INCENTIVE;
      }

      axis->elec_angle_id_output.id_tar_A = axis->elec_angle_id_config.id_max_A;

      axis->current_ctl_input.elec_theta_rad = 0.0f;
      axis->current_ctl_input.idq_tar_A[0] = axis->elec_angle_id_output.id_tar_A;
      axis->current_ctl_input.idq_tar_A[1] = 0.0f;
      axis->current_ctl_input.mode = 1; // 电流控制模式
   }
   else // 进入摩擦补偿阶段
   {
      // 执行静摩擦补偿
      switch (axis->elec_angle_id_output.step_num)
      {
      case 0: // 记录当前电角度值  和 偏移值
         axis->elec_angle_id_output.step_num = 1;
         break;
      case 1: // 正方向偏移 0.5rad
         axis->current_ctl_input.elec_theta_rad += axis->elec_angle_id_config.angle_add_rad;
         if (axis->current_ctl_input.elec_theta_rad >= axis->elec_angle_id_config.test_angle_rad)
         {
            axis->elec_angle_id_output.step_num = 2;
         }
         break;
      case 2: // 返回零点
         axis->current_ctl_input.elec_theta_rad -= axis->elec_angle_id_config.angle_add_rad;
         if (axis->current_ctl_input.elec_theta_rad <= 0.0f)
         {
            axis->current_ctl_input.elec_theta_rad = 0.0f;
            axis->elec_angle_id_output.step_num = 3;
         }
         break;
      case 3: // 零点等待1s稳定
         axis_dw->elec_angle_id_InstanceData.rtdw.time_counts += axis->pmsm_config.tp_s;
         axis->current_ctl_input.elec_theta_rad = 0.0f;

         if (axis_dw->elec_angle_id_InstanceData.rtdw.time_counts >= axis->elec_angle_id_config.wait_time_s)
         {
            axis_dw->elec_angle_id_InstanceData.rtdw.time_counts = 0.0f;
            axis->elec_angle_id_output.elec_bias_buff_rad[0] = axis->motor_pos_sensor_output.elec_angle_now_rad; // 获取当前电角度;
            axis->elec_angle_id_output.step_num = 4;
         }
         break;
      case 4: // 负方向偏移 0.5rad
         axis->current_ctl_input.elec_theta_rad -= axis->elec_angle_id_config.angle_add_rad;
         if (axis->current_ctl_input.elec_theta_rad <= -axis->elec_angle_id_config.test_angle_rad)
         {
            axis->elec_angle_id_output.step_num = 5;
         }
         break;
      case 5: // 返回零点
         axis->current_ctl_input.elec_theta_rad += axis->elec_angle_id_config.angle_add_rad;
         if (axis->current_ctl_input.elec_theta_rad >= 0.0f)
         {
            axis->current_ctl_input.elec_theta_rad = 0.0f;

            axis->elec_angle_id_output.step_num = 6;
         }

         break;
      case 6: // 零点等待1s稳定
         axis_dw->elec_angle_id_InstanceData.rtdw.time_counts += axis->pmsm_config.tp_s;
         axis->current_ctl_input.elec_theta_rad = 0.0f;

         if (axis_dw->elec_angle_id_InstanceData.rtdw.time_counts >= axis->elec_angle_id_config.wait_time_s)
         {
            axis_dw->elec_angle_id_InstanceData.rtdw.time_counts = 0.0f;
            axis->elec_angle_id_output.elec_bias_buff_rad[1] =
                axis->motor_pos_sensor_output.elec_angle_now_rad; // 获取当前电角度;

            // 判断是否刚好处于电角度0点 2次缓存的电角度值刚好越过零点
            if (MATH_ABS(axis->elec_angle_id_output.elec_bias_buff_rad[1] -
                         axis->elec_angle_id_output.elec_bias_buff_rad[0]) >= MATH_PI)
            {
               axis->elec_angle_id_output.elec_bias_rad =
                   (axis->elec_angle_id_output.elec_bias_buff_rad[0] +
                    axis->elec_angle_id_output.elec_bias_buff_rad[1] + MATH_PI * 2.0f) *
                   0.5f;

               if (axis->elec_angle_id_output.elec_bias_rad >= MATH_PI * 2.0f)
               {
                  axis->elec_angle_id_output.elec_bias_rad -= MATH_PI * 2.0f;
               }
            }
            else
            {
               axis->elec_angle_id_output.elec_bias_rad =
                   (axis->elec_angle_id_output.elec_bias_buff_rad[0] + axis->elec_angle_id_output.elec_bias_buff_rad[1]) * 0.5f;
            }

            // 辨识成功赋值给位置传感器模块
#if defined(PORT_PATCH_ELEC_BIAS_STORE_FLASH) && (PORT_PATCH_ELEC_BIAS_STORE_FLASH)
            /* [移植补丁 16] 辨识完成后：
             *  1) 把测量值写入 Flash 影子（候选标定值），SysCmd=2 存盘后下次上电生效；
             *  2) 但本次运行仍写回"当前有效零点"，不立即用测量值覆盖正在用的零点，
             *     避免跑一次辨识就改变行为（真实测量值保留在 ElecAngleIdOutput.elec_bias_rad）。
             * 当前有效零点：优先 Flash 已存值，否则头文件静态标定值。 */
            {
                float effective_bias = PMSM_ELEC_ANGLE_BIAS_RAD;
                float flash_bias = 0.0f;

                bsp_elec_bias_store_to_shadow(axis->elec_angle_id_output.elec_bias_rad);
                if (bsp_elec_bias_restore_from_flash(&flash_bias))
                {
                    effective_bias = flash_bias;
                }
                axis->motor_pos_sensor_config.elec_angle_bias_rad = effective_bias;
            }
#elif defined(PORT_PATCH_ELEC_BIAS_NO_AUTOAPPLY) && (PORT_PATCH_ELEC_BIAS_NO_AUTOAPPLY)
            /* [移植补丁] 辨识完成后把零点恢复成标定值，而不是直接采用测量值。
             * 原因：本模式进入时 ModeCheckInInit 会把零点清 0（辨识需要），所以结束时
             * 必须写一个有效值回去，否则零点留在 0；而直接写测量值会让"跑一次辨识"
             * 就把标定值覆盖掉（实测测量值 220.7°、标定值 221.6°，差 0.9°，量级一致，
             * 但没必要让辨识去改这个标定）。测量值仍保留在
             * ElecAngleIdOutput.elec_bias_rad 里供人工核对。见补丁 7。 */
            axis->motor_pos_sensor_config.elec_angle_bias_rad = PMSM_ELEC_ANGLE_BIAS_RAD;
#else
            axis->motor_pos_sensor_config.elec_angle_bias_rad = axis->elec_angle_id_output.elec_bias_rad;
#endif

            axis->elec_angle_id_output.step_num = 0;
            axis->elec_angle_id_output.state_now = IDENTIFICATION_MODE_STATE_FINISH;
         }
         break;

      default:
         break;
      }

      axis->elec_angle_id_output.id_tar_A = axis->elec_angle_id_config.id_max_A;
      axis->current_ctl_input.idq_tar_A[0] = axis->elec_angle_id_output.id_tar_A;
      axis->current_ctl_input.idq_tar_A[1] = 0.0f;
      axis->current_ctl_input.mode = 1; // 电流控制模式
   }

   if (axis->elec_angle_id_output.state_now == IDENTIFICATION_MODE_STATE_FINISH) // 辨识完成 自动失能
   {
      // elec_angle_id_Init(&(axis->elec_angle_id_output), &(axis_dw->elec_angle_id_InstanceData.rtdw)); // 重新初始化模块 等待下次启动
      axis_dw->elec_angle_id_InstanceData.rtdw.time_counts = 0.0f; // 清除内部缓存
      axis->motor_ctl_sm_output.state = MOTOR_CTL_SM_STATE_DISABLE;
   }
}

// 方向辨识模式
static void DirectionIdStep(Axis *const axis, AxisDw *const axis_dw)
{
   axis->direction_id_input.enc_counts_sum_p = axis->pos_speed_ctl_input.pos_now_p;

   direction_id(&axis->direction_id_input, &axis->direction_id_config,
                &axis->direction_id_output,
                &(axis_dw->direction_id_InstanceData.rtdw),
                &(axis_dw->direction_id_InstanceData.rtzce));

   axis->current_ctl_input.elec_angle_speed_rad_s = 0.0f;
   axis->current_ctl_input.elec_theta_rad = axis->direction_id_output.elec_angle_tar_rad;
   axis->current_ctl_input.idq_tar_A[0] = axis->direction_id_config.id_tar_max_A;
   // }

   axis->current_ctl_input.idq_tar_A[1] = 0.0f;
   axis->current_ctl_input.mode = 1; // 电流控制模式

   if (axis->direction_id_output.state_now == IDENTIFICATION_MODE_STATE_FINISH) // 辨识完成 自动失能
   {
      axis->direction_id_output.elec_angle_tar_rad = 0.0f;

      if (axis->direction_id_output.direction == -1) // 编码器方向 和 旋转磁场方向相反
      {
         axis->current_ctl_config.phase_dir = -axis->current_ctl_config.phase_dir; // 取反uvw相序
      }
      axis->current_ctl_input.idq_tar_A[0] = 0.0f;
      axis->current_ctl_input.idq_tar_A[1] = 0.0f;
      axis->motor_ctl_sm_output.state = MOTOR_CTL_SM_STATE_DISABLE;
   }
}

// 极对数辨识模式
static void PolePairsIdStep(Axis *const axis, AxisDw *const axis_dw)
{
   axis->pole_pairs_id_input.enc_counts_sum_p = axis->pos_speed_ctl_input.pos_now_p;

   pole_pairs_id(&axis->pole_pairs_id_input, &axis->pole_pairs_id_config,
                 &axis->pole_pairs_id_output,
                 &(axis_dw->pole_pairs_id_InstanceData.rtdw),
                 &(axis_dw->pole_pairs_id_InstanceData.rtzce));

   axis->current_ctl_input.elec_angle_speed_rad_s = 0.0f;
   axis->current_ctl_input.elec_theta_rad = axis->pole_pairs_id_output.elec_angle_tar_rad;
#if defined(PORT_PATCH_ID_CURRENT_FROM_CONFIG) && (PORT_PATCH_ID_CURRENT_FROM_CONFIG)
   /* [移植补丁] 用辨识配置里的电流，而不是 pmsm_config.rated_current。
    * 上游这里直接写 pmsm_config.rated_current（= √2 × 电机额定 = 1.697A），
    * 完全无视 APP Init 设置的 pole_pairs_id_config.id_tar_max_A；
    * 1.697A 持续约 7s 就会把过载积分顶爆（实测 Error_word bit1，辨识必然失败）。
    * 见 doc/PORTING_PATCHES.md 补丁 6。 */
   axis->current_ctl_input.idq_tar_A[0] = axis->pole_pairs_id_config.id_tar_max_A;
#else
   axis->current_ctl_input.idq_tar_A[0] = axis->pmsm_config.rated_current;
#endif
   axis->current_ctl_input.idq_tar_A[1] = 0.0f;
   axis->current_ctl_input.mode = 1; // 电流控制模式

   if (axis->pole_pairs_id_output.state_now == IDENTIFICATION_MODE_STATE_FINISH) // 辨识完成 自动失能
   {
      axis->pole_pairs_id_output.elec_angle_tar_rad = 0.0f;

      // 更新极对数参数
      axis->pmsm_config.pn = axis->pole_pairs_id_output.pn_id;
      axis->motor_pos_sensor_config.pn = axis->pmsm_config.pn;

      axis->current_ctl_input.idq_tar_A[0] = 0.0f;
      axis->current_ctl_input.idq_tar_A[1] = 0.0f;

      axis->motor_ctl_sm_output.state = MOTOR_CTL_SM_STATE_DISABLE;
   }
}

// 电气特性辨识模式
static void ElectricIdStep(Axis *const axis, AxisDw *const axis_dw)
{
   if (axis->current_ctl_config.phase_dir == 1) // 正序
   {
      axis->elec_id_sin_input.i_abc_now_A[0] = axis->current_ctl_input.iabc_now_A[0];
      axis->elec_id_sin_input.i_abc_now_A[1] = axis->current_ctl_input.iabc_now_A[1];
      axis->elec_id_sin_input.i_abc_now_A[2] = axis->current_ctl_input.iabc_now_A[2];
   }
   else
   {
      axis->elec_id_sin_input.i_abc_now_A[0] = axis->current_ctl_input.iabc_now_A[1];
      axis->elec_id_sin_input.i_abc_now_A[1] = axis->current_ctl_input.iabc_now_A[0];
      axis->elec_id_sin_input.i_abc_now_A[2] = axis->current_ctl_input.iabc_now_A[2];
   }

   axis->current_ctl_input.elec_angle_speed_rad_s = 0.0f;
   axis->current_ctl_input.idq_tar_A[0] = 0.0f;
   axis->current_ctl_input.idq_tar_A[1] = 0.0f;
   axis->current_ctl_input.mode = 0; // 电压直接控制模式
   axis->current_ctl_input.uabc_tar_V[0] = axis->elec_id_sin_output.u_abc_tar_V[0];
   axis->current_ctl_input.uabc_tar_V[1] = axis->elec_id_sin_output.u_abc_tar_V[1];
   axis->current_ctl_input.uabc_tar_V[2] = axis->elec_id_sin_output.u_abc_tar_V[2];

   if (axis->elec_id_sin_output.state_now == IDENTIFICATION_MODE_STATE_FINISH) // 辨识完成  自动失能
   {
      axis->current_ctl_input.uabc_tar_V[0] = 0.0f;
      axis->current_ctl_input.uabc_tar_V[1] = 0.0f;
      axis->current_ctl_input.uabc_tar_V[2] = 0.0f;

      axis->motor_ctl_sm_output.state = MOTOR_CTL_SM_STATE_DISABLE;
   }
}

// 力矩模式
static void TorqueStep(Axis *const axis, AxisDw *const axis_dw)
{
   // 由用户指令电流控制直接控制
   //  axis->current_ctl_input.idq_tar_A[0] = 0.0f;
   //  axis->current_ctl_input.idq_tar_A[1] = 0.0f;

   axis->current_ctl_input.elec_angle_speed_rad_s =
       axis->pos_speed_ctl_input.speed_now_rad_s * axis->pmsm_config.pn; // 获取当前电角速度

   axis->current_ctl_input.elec_theta_rad = axis->motor_pos_sensor_output.elec_angle_now_rad; // 获取当前电角度;
   axis->current_ctl_input.mode = 1;                                                          // 电流控制模式
}

// 速度模式
static void SpeedStep(Axis *const axis, AxisDw *const axis_dw)
{
   axis->pos_speed_ctl_config.mode = POS_SPEED_CTL_MODE_SPEED; // 纯速度控制

#ifdef MOTOR_CTL_DEBUG // 控制层调试模式，加入规划器
   PosSpeedCtlInput pos_speed_ctl_input = axis->pos_speed_ctl_input;

   linear_trajectory_planning(&axis->pos_speed_ctl_input.speed_tar_p_s,
                              &axis->pos_speed_ctl_input.acc_tar_p_ss,
                              &axis->pmsm_config.tp_s,
                              &pos_speed_ctl_input.speed_tar_p_s,
                              &kSpeedTrajStateNowTest, &(kSpeedTrajDwTest));

   pos_speed_ctl_pip(
       &pos_speed_ctl_input,
       &axis->pos_speed_ctl_config,
       &axis->pos_speed_ctl_output,
       &(axis_dw->pos_speed_ctl_pip_InstanceData.rtdw));
#else
   axis->pos_speed_ctl_input.pos_tar_p = axis->pos_speed_ctl_input.pos_now_p; // 将位置目标等于当前值，位置误差清零

   pos_speed_ctl_pip(
       &axis->pos_speed_ctl_input,
       &axis->pos_speed_ctl_config,
       &axis->pos_speed_ctl_output,
       &(axis_dw->pos_speed_ctl_pip_InstanceData.rtdw));
#endif

   // 转矩脉动与摩擦补偿
   TqFcComStep(axis, axis_dw);

   // 指令电流滤波
   CommandCurrentFilter(axis, axis_dw);
}

// 位置模式
static void PositionStep(Axis *const axis, AxisDw *const axis_dw)
{
   axis->pos_speed_ctl_config.mode = POS_SPEED_CTL_MODE_POSITION; // 位置控制模式
   // 执行末端振动抑制
   // axis->input_shaping_input.pos_cmd_p 由用户指令设置目标位置 赋值该变量

#ifdef MOTOR_CTL_DEBUG // 控制层调试模式，加入规划器
   PosSpeedCtlInput pos_ctl_input = axis->pos_speed_ctl_input;

   real32_T pos_dec_traj_p = 0.0f; // 位置规划值 小数位
   int8_T traj_state_now = 0;      // 状态

   // 速度梯形规划
   pos_trajectory_planning(&axis->input_shaping_input.pos_cmd_p,
                           &axis->pos_speed_ctl_input.speed_tar_p_s,
                           &axis->pos_speed_ctl_input.acc_tar_p_ss,
                           &axis->pos_speed_ctl_input.acc_tar_p_ss,
                           &axis->pos_speed_ctl_config.tp_s,
                           &pos_ctl_input.pos_tar_p,
                           &pos_dec_traj_p, &pos_ctl_input.speed_tar_p_s,
                           &pos_ctl_input.acc_tar_p_ss,
                           &traj_state_now, &kPosTrajDwTest);

   pos_speed_ctl_pip(
       &pos_ctl_input,
       &axis->pos_speed_ctl_config,
       &axis->pos_speed_ctl_output,
       &(axis_dw->pos_speed_ctl_pip_InstanceData.rtdw));

#else
   input_shaping_ei(&axis->input_shaping_input, &axis->input_shaping_config,
                    &axis->input_shaping_output,
                    &(axis_dw->input_shaping_InstanceData.rtdw));

   axis->pos_speed_ctl_input.pos_tar_p = axis->input_shaping_output.pos_cmd_shaping_p;

   pos_speed_ctl_pip(
       &axis->pos_speed_ctl_input,
       &axis->pos_speed_ctl_config,
       &axis->pos_speed_ctl_output,
       &(axis_dw->pos_speed_ctl_pip_InstanceData.rtdw));

#endif

   // 转矩脉动与摩擦补偿
   TqFcComStep(axis, axis_dw);

   // 指令电流滤波
   CommandCurrentFilter(axis, axis_dw);
}

// 直接电压控制
static void VoltageStep(Axis *const axis, AxisDw *const axis_dw)
{
   axis->current_ctl_input.elec_angle_speed_rad_s = 0.0f;
   axis->current_ctl_input.idq_tar_A[0] = 0.0f;
   axis->current_ctl_input.idq_tar_A[1] = 0.0f;
   axis->current_ctl_input.mode = 0; // 电压直接控制模式
   // axis->current_ctl_input.uabc_tar_V[0]  用户直接输入电流环目标电压直接控制
   // axis->current_ctl_input.uabc_tar_V[1]
   // axis->current_ctl_input.uabc_tar_V[2]
}

// 往复运动模式
static void ReciprocalMotionStep(Axis *const axis, AxisDw *const axis_dw)
{
   reciprocal_motion(&axis->reciprocal_motion_config,
                     &axis->reciprocal_motion_output,
                     &(axis_dw->reciprocal_motion_InstanceData.rtdw));

   axis->input_shaping_input.pos_cmd_p = axis->reciprocal_motion_output.pos_tar_p;

   axis->pos_speed_ctl_input.speed_tar_p_s = axis->reciprocal_motion_output.v_tar_p_s;
   axis->pos_speed_ctl_input.acc_tar_p_ss = axis->reciprocal_motion_output.acc_tar_p_ss;

   input_shaping_ei(&axis->input_shaping_input, &axis->input_shaping_config,
                    &axis->input_shaping_output,
                    &(axis_dw->input_shaping_InstanceData.rtdw));

   axis->pos_speed_ctl_input.pos_tar_p = axis->input_shaping_output.pos_cmd_shaping_p;

   axis->pos_speed_ctl_config.mode = POS_SPEED_CTL_MODE_POSITION;
   pos_speed_ctl_pip(
       &axis->pos_speed_ctl_input,
       &axis->pos_speed_ctl_config,
       &axis->pos_speed_ctl_output,
       &(axis_dw->pos_speed_ctl_pip_InstanceData.rtdw));

   // 转矩脉动与摩擦补偿
   TqFcComStep(axis, axis_dw);

   // 指令电流滤波
   CommandCurrentFilter(axis, axis_dw);
}

// 参考信号模式
static void ReferenceSignalStep(Axis *const axis, AxisDw *const axis_dw)
{
   if (axis->reference_signal_config.signal_target <= REFERENCE_SIGNAL_TARGET_SPEED) // 位置模式暂时另外生成
   {
      reference_signal(&axis->reference_signal_config,
                       &axis->reference_signal_output,
                       &(axis_dw->reference_signal_InstanceData.rtdw));
   }

   switch (axis->reference_signal_config.signal_target)
   {
   case REFERENCE_SIGNAL_TARGET_D_CURRENT: // d轴
                                           // 由用户指令电流控制直接控制
      axis->current_ctl_input.idq_tar_A[0] = axis->reference_signal_output.signal_out;
      axis->current_ctl_input.idq_tar_A[1] = 0.0f;
      axis->current_ctl_input.elec_angle_speed_rad_s =
          axis->pos_speed_ctl_input.speed_now_rad_s * axis->pmsm_config.pn;                      // 获取当前电角速度
      axis->current_ctl_input.elec_theta_rad = axis->motor_pos_sensor_output.elec_angle_now_rad; // 获取当前电角度;
      axis->current_ctl_input.mode = 1;
      break;
   case REFERENCE_SIGNAL_TARGET_Q_CURRENT: // q轴
                                           // 由用户指令电流控制直接控制
      axis->current_ctl_input.idq_tar_A[0] = 0.0f;
      axis->current_ctl_input.idq_tar_A[1] = axis->reference_signal_output.signal_out;
      axis->current_ctl_input.elec_angle_speed_rad_s =
          axis->pos_speed_ctl_input.speed_now_rad_s * axis->pmsm_config.pn;                      // 获取当前电角速度
      axis->current_ctl_input.elec_theta_rad = axis->motor_pos_sensor_output.elec_angle_now_rad; // 获取当前电角度;
      axis->current_ctl_input.mode = 1;
      break;
   case REFERENCE_SIGNAL_TARGET_SPEED: // 速度
      axis->pos_speed_ctl_input.speed_tar_p_s = axis->reference_signal_output.signal_out;

      axis->pos_speed_ctl_config.mode = POS_SPEED_CTL_MODE_SPEED;
      pos_speed_ctl_pip(
          &axis->pos_speed_ctl_input,
          &axis->pos_speed_ctl_config,
          &axis->pos_speed_ctl_output,
          &(axis_dw->pos_speed_ctl_pip_InstanceData.rtdw));

      // 转矩脉动与摩擦补偿
      TqFcComStep(axis, axis_dw);

      // 指令电流滤波
      CommandCurrentFilter(axis, axis_dw);
      break;
   case REFERENCE_SIGNAL_TARGET_POSITION: // 位置
      PosReferenceSignalTemp(&axis->reference_signal_config,
                             &axis->reference_signal_output,
                             &(axis_dw->reference_signal_InstanceData.rtdw));

      axis->input_shaping_input.pos_cmd_p = axis->reference_signal_output.signal_pos;
      axis->pos_speed_ctl_input.speed_tar_p_s = axis->reference_signal_output.signal_vel;
      axis->pos_speed_ctl_input.acc_tar_p_ss = axis->reference_signal_output.signal_acc;

      input_shaping_ei(&axis->input_shaping_input, &axis->input_shaping_config,
                       &axis->input_shaping_output,
                       &(axis_dw->input_shaping_InstanceData.rtdw));

      axis->pos_speed_ctl_input.pos_tar_p = axis->input_shaping_output.pos_cmd_shaping_p;

      axis->pos_speed_ctl_config.mode = POS_SPEED_CTL_MODE_POSITION;
      pos_speed_ctl_pip(
          &axis->pos_speed_ctl_input,
          &axis->pos_speed_ctl_config,
          &axis->pos_speed_ctl_output,
          &(axis_dw->pos_speed_ctl_pip_InstanceData.rtdw));

      // 转矩脉动与摩擦补偿
      TqFcComStep(axis, axis_dw);

      // 指令电流滤波
      CommandCurrentFilter(axis, axis_dw);
      break;
   case REFERENCE_SIGNAL_IF_MODE: // 开环旋转磁场  可用于编码器校准  IF 模式
      axis->reference_signal_output.signal_out += axis->reference_signal_config.frq_Hz * MOTOR_CTL_SM_TWO_PI *
                                                  axis->pmsm_config.tp_s * axis->pmsm_config.pn;
      while (axis->reference_signal_output.signal_out < 0.0F)
      {
         /* '<S5>:1:6' n_ang = n_ang + TWO_PI; */
         axis->reference_signal_output.signal_out += MOTOR_CTL_SM_TWO_PI;
      }

      /* '<S5>:1:8' while n_ang >= TWO_PI */
      while (axis->reference_signal_output.signal_out >= MOTOR_CTL_SM_TWO_PI)
      {
         /* '<S5>:1:9' n_ang = n_ang - TWO_PI; */
         axis->reference_signal_output.signal_out -= MOTOR_CTL_SM_TWO_PI;
      }

      axis->current_ctl_input.elec_theta_rad = axis->reference_signal_output.signal_out;
      axis->current_ctl_input.idq_tar_A[0] = axis->reference_signal_config.amp;
      axis->current_ctl_input.idq_tar_A[1] = 0.0f;
      axis->current_ctl_input.mode = 1; // 电流控制模式

      break;
   case REFERENCE_SIGNAL_VF_MODE:
      // 计算角频率 w
      axis->reference_signal_output.signal_out += axis->reference_signal_config.frq_Hz * MOTOR_CTL_SM_TWO_PI *
                                                  axis->pmsm_config.tp_s;
      while (axis->reference_signal_output.signal_out < 0.0F)
      {
         /* '<S5>:1:6' n_ang = n_ang + TWO_PI; */
         axis->reference_signal_output.signal_out += MOTOR_CTL_SM_TWO_PI;
      }

      /* '<S5>:1:8' while n_ang >= TWO_PI */
      while (axis->reference_signal_output.signal_out >= MOTOR_CTL_SM_TWO_PI)
      {
         /* '<S5>:1:9' n_ang = n_ang - TWO_PI; */
         axis->reference_signal_output.signal_out -= MOTOR_CTL_SM_TWO_PI;
      }

      axis->current_ctl_input.uabc_tar_V[0] =
          axis->reference_signal_config.amp *
          yuanhub_sin_f32(axis->reference_signal_output.signal_out);

      axis->current_ctl_input.uabc_tar_V[1] =
          axis->reference_signal_config.amp *
          yuanhub_sin_f32(axis->reference_signal_output.signal_out - MOTOR_CTL_SM_120_DEG_RAD);

      axis->current_ctl_input.uabc_tar_V[2] =
          axis->reference_signal_config.amp *
          yuanhub_sin_f32(axis->reference_signal_output.signal_out + MOTOR_CTL_SM_120_DEG_RAD);

      axis->current_ctl_input.mode = 0; // 电压控制模式
      break;

   default:
      break;
   }
}

// MIT模式
static void MitCtlStep(Axis *const axis, AxisDw *const axis_dw)
{
   // axis->mit_ctl_pd_input.tq_set_A  用户指令设定
   // axis->mit_ctl_pd_input.pos_tar_p  用户指令设定
   // axis->mit_ctl_pd_input.speed_tar_rad_s  用户指令设定

   axis->mit_ctl_input.pos_now_p = axis->motor_pos_sensor_output.enc_sum_p;   // 获取电机端当前绝对位置
   axis->mit_ctl_input.speed_now_rad_s = axis->speed_obs_pll_output.ev_rad_s; // 速度观测器输出

   mit_ctl(&axis->mit_ctl_input, &axis->mit_ctl_config,
           &axis->mit_ctl_output);

   axis->pos_speed_ctl_output.iq_tar_A = axis->mit_ctl_output.iq_tar_A; // 设置电流环目标电流

   // 转矩脉动与摩擦补偿
   TqFcComStep(axis, axis_dw);

   // 指令电流滤波
   CommandCurrentFilter(axis, axis_dw);
}

#pragma endregion

// 位置环内部模式运行
static void ModeRun(Axis *const axis, AxisDw *const axis_dw)
{
   // TODO：增加模式切换 和 当前模式显示处理
   axis->motor_ctl_sm_output.mode_now = axis->motor_ctl_sm_config.mode;
   switch (axis->motor_ctl_sm_config.mode)
   {
   case MOTOR_CTL_SM_MODE_POSITION: // 位置模式
      PositionStep(axis, axis_dw);
      break;
   case MOTOR_CTL_SM_MODE_SPEED: // 速度模式
      SpeedStep(axis, axis_dw);
      break;
   case MOTOR_CTL_SM_MODE_TORQUE: // 力矩模式
      TorqueStep(axis, axis_dw);
      break;
   case MOTOR_CTL_SM_MODE_TQ_FRICTION_IDENTIFICATION: // 转矩脉动与摩擦辨识
      TqFcIdStep(axis, axis_dw);
      break;
   case MOTOR_CTL_SM_MODE_MECHANICAL_IDENTIFICATION: // 机械特性辨识模式
      MecIdStep(axis, axis_dw);
      break;
   case MOTOR_CTL_SM_MODE_ELECTRIC_ANGLE_IDENTIFICATION: // 电角度辨识模式
      ElecAngleIdStep(axis, axis_dw);
      break;
   case MOTOR_CTL_SM_MODE_DIRECTION_IDENTIFICATION: // 方向辨识模式
      DirectionIdStep(axis, axis_dw);
      break;
   case MOTOR_CTL_SM_MODE_POLE_PAIRS_IDENTIFICATION: // 极对数辨识模式
      PolePairsIdStep(axis, axis_dw);
      break;
   case MOTOR_CTL_SM_MODE_ELECTRIC_IDENTIFICATION: // 电气特性辨识模式
      ElectricIdStep(axis, axis_dw);
      break;
   case MOTOR_CTL_SM_MODE_IDLE: // 空闲模式
      axis->motor_ctl_sm_output.state = 0;
      break;
   case MOTOR_CTL_SM_MODE_VOLTAGE: // 电压直接控制模式
      VoltageStep(axis, axis_dw);
      break;
   case MOTOR_CTL_SM_MODE_RECIPROCAL_MOTION: // 往复运动模式
      ReciprocalMotionStep(axis, axis_dw);
      break;
   case MOTOR_CTL_SM_MODE_REFERENCE_SIGNAL: // 参考信号模式
      ReferenceSignalStep(axis, axis_dw);
      break;
   case MOTOR_CTL_SM_MODE_MIT: // MIT模式
      MitCtlStep(axis, axis_dw);
      break;

   default:
      break;
   }
}

/**
 * @brief 生成参考信号及其速度和加速度临时函数
 * @param rtu_config  参考信号配置
 * @param rty_output  参考信号输出(包含位置、速度、加速度)
 * @param localDW     局部工作区(存储状态)
 */
static void PosReferenceSignalTemp(const ReferenceSignalConfig *rtu_config,
                                   ReferenceSignalOutput *rty_output,
                                   reference_signal_DW_f *localDW)
{
   real32_T rtb_n_ang = 0.0f; // 当前角度
   real32_T time_out = 0.0f;  // 临时变量(用于方波值)
   real32_T omega = 0.0f;     // 角频率(ω = 2πf)

   // 计算角频率 ω = 2πf
   omega = rtu_config->frq_Hz * 6.28318548f;

   // 计算当前角度
   rtb_n_ang = omega * rtu_config->dt_s + localDW->sin_time;

   // 角度归一化：确保角度在0到2π之间
   while (rtb_n_ang < 0.0F)
   {
      rtb_n_ang += 6.28318548f;
   }
   while (rtb_n_ang >= 6.28318548f)
   {
      rtb_n_ang -= 6.28318548f;
   }

   // 计算方波的周期时间
   time_out = 1.0F / rtu_config->frq_Hz;

   // 如果计时器超过一个周期，重置为0
   if (localDW->times >= time_out)
   {
      localDW->times = 0.0F;
   }

   // 更新计时器
   localDW->times += rtu_config->dt_s;

   // 根据计时器判断是高电平(1)还是低电平(0)
   if (localDW->times > 0.5F * time_out)
   {
      time_out = 0.0F; // 低电平
   }
   else
   {
      time_out = 1.0F; // 高电平
   }

   // 根据信号类型生成正弦波或方波
   if (rtu_config->signal_type > 0)
   {
      // 正弦波：计算位置值
      rty_output->signal_pos = rtu_config->signal_start_pos + rtu_config->amp * yuanhub_sin_f32(rtb_n_ang) + rtu_config->bias;

      // 计算速度值：Vel(t) = A·ω·cos(ωt)
      rty_output->signal_vel = rtu_config->amp * omega * yuanhub_cos_f32(rtb_n_ang);

      // 计算加速度值：Acc(t) = -A·ω²·sin(ωt)
      rty_output->signal_acc = -rtu_config->amp * omega * omega * yuanhub_sin_f32(rtb_n_ang);
   }
   else
   {
      // 方波：将方波值(0或1)乘以幅度
      rty_output->signal_pos = rtu_config->signal_start_pos + rtu_config->amp * time_out + rtu_config->bias;
      rty_output->signal_vel = 0;
      rty_output->signal_acc = 0;
   }

   // 更新状态变量，为下一次计算做准备
   localDW->sin_time = rtb_n_ang;
}
