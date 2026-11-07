/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: servo_hub_database_type.h
 *
 * Code generated for Simulink model 'servo_hub_example'.
 *
 * Simulink Coder version         : 9.9 (R2023a) 19-Nov-2022
 */

#ifndef RTW_HEADER_servo_hub_database_type_h_
#define RTW_HEADER_servo_hub_database_type_h_
#include "rtwtypes.h"

typedef struct
{
    /* 电流采样噪声绝对值 */
    real32_T i_noise_A;

    /* 死区补偿电压大小 */
    real32_T comp_du_V;

    /* 电流环目标带宽 % */
    real32_T bandwidth_percentage;

    /* 电流环运行周期 */
    real32_T dt_s;

    /* 磁链系数 */
    real32_T flux_wb;

    /* d轴 kp控制增益 */
    real32_T kp_ld;

    /* d轴 ki控制增益 */
    real32_T ki_ld;

    /* q轴 kp控制增益 */
    real32_T kp_lq;

    /* q轴 ki控制增益 */
    real32_T ki_lq;

    /* pwm 占空比最大值 */
    real32_T pwm_duty_cycle_max;

    /* 电角度补偿系数 */
    real32_T elec_angle_compensation;

    /* UVW相序 */
    int8_T phase_dir;
}

CurrentCtlConfig;

typedef struct
{
    /* 目标id iq 电流 */
    real32_T idq_tar_A[2];

    /* iabc 三相当前电流反馈 */
    real32_T iabc_now_A[3];

    /* 当前电角度 */
    real32_T elec_theta_rad;

    /* 当前母线电压 */
    real32_T dc_bus_now_V;

    /* 电流环控制模式 */
    uint8_T mode;

    /* 三相目标电压 */
    real32_T uabc_tar_V[3];

    /* 驱动器当前温度 */
    real32_T driver_temp;

    /* 电角速度 */
    real32_T elec_angle_speed_rad_s;

    /* iq 目标电流偏置 */
    real32_T iq_offset_A;
}

CurrentCtlInput;

typedef struct
{
    /* 死区补偿后目标三相电压 */
    real32_T uabc_tar_comp_V[3];

    /* 当前dq轴电流 */
    real32_T idq_now_A[2];

    /* 补偿前目标三相电压 */
    real32_T uabc_tar_org_V[3];
}

CurrentCtlOutput;

typedef struct
{
    /* 电角度步进的增量 */
    real32_T elec_angle_add_rad;

    /* 电流上升斜率%每s */
    real32_T current_slope_percentage;

    /* d轴目标电流最大值 */
    real32_T id_tar_max_A;
}

DirectionIdConfig;

typedef struct
{
    /* 编码器位置累计值 */
    int64_T enc_counts_sum_p;
}

DirectionIdInput;

typedef struct
{
    /* 开环的目标电角度 */
    real32_T elec_angle_tar_rad;

    /* 辨识的方向结果 */
    int8_T direction;

    /* 运行状态 */
    int8_T state_now;

    /* d轴电流目标值 */
    real32_T id_tar_A;
}

DirectionIdOutput;

typedef struct
{
    /* id 目标电流最大值 */
    real32_T id_max_A;

    /* 运行周期 */
    real32_T dt_s;

    /* 辨识方法 */
    uint8_T method;

    /* 电角度强拉增量 */
    real32_T angle_add_rad;

    /* 强拉角度等待时间 */
    real32_T wait_time_s;

    /* 测试拖动角度 */
    real32_T test_angle_rad;

    /* 电流上升斜率%每s */
    real32_T current_slope_percentage;
}

ElecAngleIdConfig;

typedef struct
{
    /* 转子当前位置 */
    real32_T pos_now_rad;
}

ElecAngleIdInput;

typedef struct
{
    /* 目标d轴电流 */
    real32_T id_tar_A;

    /* 电角度偏移值 */
    real32_T elec_bias_rad;

    /* 运行状态 */
    int8_T state_now;

    /* 内部电角度偏移值缓存值 */
    real32_T elec_bias_buff_rad[2];

    /* 内部辨识步骤 */
    uint8_T step_num;
}

ElecAngleIdOutput;

typedef struct
{
    /* 运行周期
     */
    real32_T dt_s;

    /* 终止频率 */
    real32_T end_fs_Hz;

    /* 电气辨识最大电流
     */
    real32_T i_max_A;

    /* 初始激励频率 */
    real32_T init_fs_Hz;

    /* 激励信号持续时间 */
    real32_T target_time_s;

    /* 电气辨识最大电压 */
    real32_T u_max_V;

    /* 激励信号自动调整等待时间 */
    real32_T wait_time_s;
}

ElecIdSinConfig;

typedef struct
{
    /* 当前三相电流 */
    real32_T i_abc_now_A[3];
}

ElecIdSinInput;

typedef struct
{
    /* 激励信号状态标志位 */
    int8_T state_now;

    /* 三相目标电压 */
    real32_T u_abc_tar_V[3];

    /* alpha轴当前电压 */
    real32_T u_alpha_now_V;

    /* alpha轴当前电流 */
    real32_T i_alpha_now_A;
}

ElecIdSinOutput;

typedef struct
{
    /* 末端振动抑制的频率 */
    real32_T wn_Hz;

    /* 模块运行频率 */
    real32_T run_frq_Hz;

    /* 使能末端振动抑制开关 */
    uint8_T enable;
}

InputShapingConfig;

typedef struct
{
    /* 指令目标位置 */
    int64_T pos_cmd_p;

    /* 指令目标位置初始值 */
    int64_T pos_cmd_p_init;
}

InputShapingInput;

typedef struct
{
    /* 整形后指令目标位置 */
    int64_T pos_cmd_shaping_p;
}

InputShapingOutput;

typedef struct
{
    /* 编码器分辨率 */
    uint32_T enc_line_p_n;

    /* 编码器初始位置 */
    int64_T init_pos_p;

    /* 计数方向 */
    int8_T dir;
}

LoadPosSensorConfig;

typedef struct
{
    /* 编码器当前单圈位置脉冲数 */
    uint32_T enc_counts_now_p;
}

LoadPosSensorInput;

typedef struct
{
    /* 编码器累计脉冲值 */
    int64_T enc_sum_p;
}

LoadPosSensorOutput;

typedef struct
{
    /* 运行周期
     */
    real32_T dt_s;

    /* 扫描终止频率 */
    real32_T end_fs_Hz;

    /* 扫描起始频率 */
    real32_T start_fs_Hz;

    /* 激励信号持续时间 */
    real32_T target_time_s;

    /* 辨识过程中最大目标力矩电流iq */
    real32_T i_max_A;

    /* 辨识过程中搜索频率的最大转速 */
    real32_T search_speed_max_rad_s;

    /* 搜索等待时间 */
    real32_T wait_time_s;

    /* 激励信号类型 */
    uint8_T signal_type;
}

MecIdConfig;

typedef struct
{
    /* 当前速度 */
    real32_T speed_now_rad_s;
}

MecIdInput;

typedef struct
{
    /* 目标力矩电流 */
    real32_T iq_tar_A;

    /* 激励信号状态标志位 */
    int8_T state_now;
}

MecIdOutput;

typedef struct
{
    /* 位置刚度 */
    real32_T kp_pos_NM_rad;

    /* 速度阻尼 */
    real32_T kd_spd_NM_rad_s;

    /* 编码器分辨率倒数 */
    real32_T enc_line_inv_p_n;

    /* 转矩常数 */
    real32_T kt_NM_A;
}

MitCtlConfig;

typedef struct
{
    /* 前馈力矩电流 */
    real32_T tq_set_NM;

    /* 目标位置 */
    int64_T pos_tar_p;

    /* 当前位置 */
    int64_T pos_now_p;

    /* q轴最大输出电流 */
    real32_T iq_max_A;

    /* 目标速度 */
    real32_T speed_tar_p_s;

    /* 当前速度 */
    real32_T speed_now_rad_s;
}

MitCtlInput;

typedef struct
{
    /* 目标q轴电流 */
    real32_T iq_tar_A;
}

MitCtlOutput;

typedef struct
{
    /* 运行模式 */
    int8_T mode;

    /* 欠压保护阈值 */
    real32_T under_voltage_protection_V;

    /* 过压保护阈值 */
    real32_T over_voltage_protection_V;

    /* 过速保护阈值 */
    real32_T over_speed_protection_rad_s;

    /* 欠温保护阈值 */
    real32_T under_temperature_protection_d;

    /* 过温保护阈值 */
    real32_T over_temperature_protection_d;

    /* 位置跟随误差保护阈值 */
    int32_T position_following_error_protection;

    /* 保护生效 */
    uint32_T error_enable;

    /* 过流保护阈值 */
    real32_T over_current_protection_A;
}

MotorCtlSmConfig;

typedef struct
{
    /* 电机使能控制指令 */
    uint8_T motor_enable;

    /* 硬件准备的状态 */
    uint8_T hw_ready_state;
}

MotorCtlSmInput;

typedef struct
{
    /* 运行状态 */
    int8_T state;

    /* 错误代码 */
    uint32_T error;

    /* 警告代码 */
    uint32_T warning;

    /* 当前运行模式 */
    int8_T mode_now;

    /* 电机使能控制上一个周期的值 */
    uint8_T motor_enable_last;

    /* 上一个周期运行状态 */
    int8_T state_last;
}

MotorCtlSmOutput;

typedef struct
{
    /* 编码器分辨率 */
    uint32_T enc_line_p_n;

    /* 编码器初始位置 */
    int64_T init_pos_p;

    /* 电机极对数 */
    uint32_T pn;

    /* 电角度偏移值 */
    real32_T elec_angle_bias_rad;

    /* 计数方向 */
    int8_T dir;
}

MotorPosSensorConfig;

typedef struct
{
    /* 编码器当前单圈位置脉冲数 */
    uint32_T enc_counts_now_p;
}

MotorPosSensorInput;

typedef struct
{
    /* 编码器累计脉冲值 */
    int64_T enc_sum_p;

    /* 电角度当前值 */
    real32_T elec_angle_now_rad;
}

MotorPosSensorOutput;

typedef struct
{
    /* 陷波滤波器频率 */
    real32_T frq[6];

    /* 陷波滤波器宽度 */
    real32_T width[6];

    /* 陷波滤波器深度 */
    real32_T depth[6];
}

NotchFilterConfig;

typedef struct
{
    /* 速度环输出目标电流 */
    real32_T iq_tar_A;
}

NotchFilterInput;

typedef struct
{
    /* 前馈系数0 */
    real32_T u0[6];

    /* 前馈系数1 */
    real32_T u1[6];

    /* 前馈系数2 */
    real32_T u2[6];

    /* 反馈系数0 */
    real32_T y0[6];

    /* 反馈系数1 */
    real32_T y1[6];
}

NotchFilterInternal;

typedef struct
{
    /* 滤波后的目标电流 */
    real32_T iq_tar_filter_A;
}

NotchFilterOutput;

typedef struct
{
    /* 速度阻尼系数 */
    real32_T b;

    /* 静摩擦大小 */
    real32_T fc;

    /* 磁链系数 */
    real32_T flux;

    /* 转子惯量 */
    real32_T j;

    /* d定子电感 */
    real32_T ld;

    /* q定子电感 */
    real32_T lq;

    /* 电机峰值电流 */
    real32_T peak_current;

    /* 极对数 */
    real32_T pn;

    /* 定子电阻 */
    real32_T r;

    /* 电机额定电流 */
    real32_T rated_current;

    /* 电机最大转速 */
    real32_T speed_max_rpm;

    /* 位置环运行周期 */
    real32_T tp_s;

    /* 电流环运行周期 */
    real32_T tc_s;

    /* 编码器分辨率 */
    uint32_T enc_line_p_n;

    /* 转矩常数 */
    real32_T kt;
}

PmsmConfig;

typedef struct
{
    /* 电角度步进的增量 */
    real32_T elec_angle_add;

    /* 编码器分辨率 */
    uint32_T enc_line_p_n;

    /* d轴目标电流最大值 */
    real32_T id_tar_max_A;

    /* 电流上升斜率%每s */
    real32_T current_slope_percentage;
}

PolePairsIdConfig;

typedef struct
{
    /* 编码器位置累计值 */
    int64_T enc_counts_sum_p;
}

PolePairsIdInput;

typedef struct
{
    /* 极对数辨识结果 */
    uint32_T pn_id;

    /* 运行状态 */
    int8_T state_now;

    /* 电角度目标值 */
    real32_T elec_angle_tar_rad;

    /* d轴电流目标值 */
    real32_T id_tar_A;
}

PolePairsIdOutput;

typedef struct
{
    /* 加速度前馈系数 */
    real32_T aff;

    /* 速度前馈系数 */
    real32_T vff;

    /* 编码器分辨率倒数 */
    real32_T enc_line_inv_p_n;

    /* 惯性系数 */
    real32_T j_kt;

    /* 速度环积分系数 */
    real32_T ki_s;

    /* 位置环比例系数 */
    real32_T kp_p;

    /* 速度环比例系数 */
    real32_T kp_s;

    /* 最大目标速度限制 */
    real32_T speed_max_rad_s;

    /* 位置速度环运行周期 */
    real32_T tp_s;

    /* 运行模式 */
    real32_T mode;

    /* 负载扰动观测器带宽 */
    real32_T dob_wn_Hz;

    /* 负载扰动观测使能开关 */
    uint8_T dob_enable;

    /* 速度环动态积分使能 */
    uint8_T dynamic_integration_enable;
}

PosSpeedCtlConfig;

typedef struct
{
    /* 目标位置 */
    int64_T pos_tar_p;

    /* 当前位置 */
    int64_T pos_now_p;

    /* 最大目标q轴电流 */
    real32_T iq_max_A;

    /* 目标速度 */
    real32_T speed_tar_p_s;

    /* 目标加速度 */
    real32_T acc_tar_p_ss;

    /* 当前转速 */
    real32_T speed_now_rad_s;

    /* 目标位置偏置 */
    int64_T position_offset_p;

    /* 目标速度偏置 */
    real32_T speed_offset_p_s;
}

PosSpeedCtlInput;

typedef struct
{
    /* 目标q轴电流 */
    real32_T iq_tar_A;

    /* 当前位置控制误差 */
    int32_T pos_ctl_error_p;

    /* 负载扰动补偿电流 */
    real32_T dob_iq_com_A;
}

PosSpeedCtlOutput;

typedef struct
{
    /* 目标位置1 */
    int64_T pos_tar1_p;

    /* 目标位置2 */
    int64_T pos_tar2_p;

    /* 等待时间 */
    real32_T dwell_time_s;

    /* 轮廓速度 */
    real32_T profile_velocity_p_s;

    /* 轮廓加速度 */
    real32_T profile_acc_p_ss;

    /* 轮廓减速度 */
    real32_T profile_dec_p_ss;

    /* 运行周期 */
    real32_T dt_s;
}

ReciprocalMotionConfig;

typedef struct
{
    /* 规划位置 */
    int64_T pos_tar_p;

    /* 规划速度 */
    real32_T v_tar_p_s;

    /* 规划加速度 */
    real32_T acc_tar_p_ss;

    /* 规划器状态 */
    int8_T state_now;
}

ReciprocalMotionOutput;

typedef struct
{
    /* 运行周期 */
    real32_T dt_s;

    /* 信号类型 */
    uint8_T signal_type;

    /* 信号幅值 */
    real32_T amp;

    /* 运行频率 */
    real32_T frq_Hz;

    /* 信号偏移 */
    real32_T bias;

    /* 信号激励目标 */
    uint8_T signal_target;

    /* 参考信号启动位置 */
    int64_T signal_start_pos;
}

ReferenceSignalConfig;

typedef struct
{
    /* 参考信号输出 */
    real32_T signal_out;

    /* 参考信号输出位置 */
    int64_T signal_pos;

    /* 参考信号输出速度 */
    real32_T signal_vel;

    /* 参考信号输出加速度 */
    real32_T signal_acc;
}

ReferenceSignalOutput;

typedef struct
{
    /* 速度阻尼系数 */
    real32_T b;

    /* 静摩擦大小 */
    real32_T fc;

    /* 磁链系数 */
    real32_T flux;

    /* 转矩常数 */
    real32_T kt;

    /* 转子惯量 */
    real32_T j;

    /* d定子电感 */
    real32_T ld;

    /* q定子电感 */
    real32_T lq;

    /* 电机峰值电流 */
    real32_T peak_current_A;

    /* 极对数 */
    real32_T pn;

    /* 定子电阻 */
    real32_T r;

    /* 电机额定电流 */
    real32_T rated_current_A;

    /* 电机最大转速 */
    real32_T speed_max_rpm;

    /* 虚拟电机模型运行周期 */
    real32_T dt_s;

    /* 编码器分辨率 */
    uint32_T enc_line_p_n;

    /* 转子惯量倒数 */
    real32_T j_inv;

    /* d定子电感倒数 */
    real32_T ld_inv;

    /* q定子电感倒数 */
    real32_T lq_inv;

    /* 编码器初始位置 */
    int64_T enc_line_init_pos_P;

    /* 编码器传感器噪声 */
    real32_T enc_noise;
}

SimPlantConfig;

typedef struct
{
    /* 虚拟模型三相电压输入 */
    real32_T uabc_tar_V[3];

    /* 虚拟模型转矩输入 */
    real32_T tl_Nm;
}

SimPlantInput;

typedef struct
{
    /* 虚拟模型三相电流输出 */
    real32_T iabc_now_A[3];

    /* 虚拟模型编码器单圈值 */
    uint32_T enc_counts_P;

    /* 虚拟模型霍尔传感器输出 */
    uint8_T hall_state;

    /* 虚拟母线电源电压输出 */
    real32_T dc_bus_V;
}

SimPlantOutput;

typedef struct
{
    /* 运行周期 */
    real32_T tp_s;

    /* 速度观测带宽 */
    real32_T wn_Hz;

    /* 编码器分辨率倒数 */
    real32_T enc_line_inv_p_n;

    /* 最大目标速度限制 */
    real32_T speed_obs_max_rad_s;
}

SpeedObsPllConfig;

typedef struct
{
    /* 电机当前位置 */
    int64_T pos_now_p;
}

SpeedObsPllInput;

typedef struct
{
    /* 观测转速 */
    real32_T ev_rad_s;
}

SpeedObsPllOutput;

typedef struct
{
    /* 编码器分辨率 */
    uint32_T enc_line_p_n;

    /* 使能负载扰动补偿开关 */
    uint8_T iq_com_enable;

    /* 使能转矩脉动补偿开关 */
    uint8_T tq_com_enable;

    /* 使能摩擦补偿开关 */
    uint8_T fc_com_enable;

    /* 摩擦补偿正方向补偿值 */
    real32_T fc_p_com;

    /* 摩擦补偿负方向补偿值 */
    real32_T fc_n_com;
}

TqFcIdConfig;

typedef struct
{
    /* 负载扰动观测器补偿值 */
    real32_T iq_com_A;

    /* 当前转子绝对位置 */
    uint32_T pos_abs_p;

    /* 电机初始位置 */
    int64_T pos_init_p;

    /* 启动辨识指令 */
    uint8_T start;
}

TqFcIdInput;

typedef struct
{
    /* 位置指令值 */
    int64_T pos_cmd_p;

    /* 当前辨识状态 */
    int8_T state_now;
}

TqFcIdOutput;

typedef struct
{
    CurrentCtlConfig current_ctl_config;
    CurrentCtlInput current_ctl_input;
    CurrentCtlOutput current_ctl_output;
    DirectionIdConfig direction_id_config;
    DirectionIdInput direction_id_input;
    DirectionIdOutput direction_id_output;
    ElecAngleIdConfig elec_angle_id_config;
    ElecAngleIdInput elec_angle_id_input;
    ElecAngleIdOutput elec_angle_id_output;
    ElecIdSinConfig elec_id_sin_config;
    ElecIdSinInput elec_id_sin_input;
    ElecIdSinOutput elec_id_sin_output;
    InputShapingConfig input_shaping_config;
    InputShapingInput input_shaping_input;
    InputShapingOutput input_shaping_output;
    LoadPosSensorConfig load_pos_sensor_config;
    LoadPosSensorInput load_pos_sensor_input;
    LoadPosSensorOutput load_pos_sensor_output;
    MecIdConfig mec_id_config;
    MecIdInput mec_id_input;
    MecIdOutput mec_id_output;
    MitCtlConfig mit_ctl_config;
    MitCtlInput mit_ctl_input;
    MitCtlOutput mit_ctl_output;
    MotorCtlSmConfig motor_ctl_sm_config;
    MotorCtlSmInput motor_ctl_sm_input;
    MotorCtlSmOutput motor_ctl_sm_output;
    MotorPosSensorConfig motor_pos_sensor_config;
    MotorPosSensorInput motor_pos_sensor_input;
    MotorPosSensorOutput motor_pos_sensor_output;
    NotchFilterConfig notch_filter_config;
    NotchFilterInput notch_filter_input;
    NotchFilterInternal notch_filter_internal;
    NotchFilterOutput notch_filter_output;
    PmsmConfig pmsm_config;
    PolePairsIdConfig pole_pairs_id_config;
    PolePairsIdInput pole_pairs_id_input;
    PolePairsIdOutput pole_pairs_id_output;
    PosSpeedCtlConfig pos_speed_ctl_config;
    PosSpeedCtlInput pos_speed_ctl_input;
    PosSpeedCtlOutput pos_speed_ctl_output;
    ReciprocalMotionConfig reciprocal_motion_config;
    ReciprocalMotionOutput reciprocal_motion_output;
    ReferenceSignalConfig reference_signal_config;
    ReferenceSignalOutput reference_signal_output;
    SimPlantConfig sim_plant_config;
    SimPlantInput sim_plant_input;
    SimPlantOutput sim_plant_output;
    SpeedObsPllConfig speed_obs_pll_config;
    SpeedObsPllInput speed_obs_pll_input;
    SpeedObsPllOutput speed_obs_pll_output;
    TqFcIdConfig tq_fc_id_config;
    TqFcIdInput tq_fc_id_input;
    TqFcIdOutput tq_fc_id_output;
}

Axis;

#endif                               /* RTW_HEADER_servo_hub_database_type_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
