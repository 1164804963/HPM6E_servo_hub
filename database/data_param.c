#include "data_param.h"
#include "motor_ctl_loop.h"

/* USER CODE BEGIN AREA 0 */

CallbackRegistry callback_registry = {
    .set_app_callback = NULL,
    .get_check_error_val = NULL,
    .get_check_warning_val = NULL,
    .get_check_status_val = NULL,
    .get_check_di_io_val = NULL
};

// 设置切换APP模式回调函数到注册表
void RegisterSetAppCallback(void* callback) {
    callback_registry.set_app_callback = (void (*)(APP_NAMES app_name))callback;
}

// 设置状态检查回调函数到注册表
void RegisterCheckErrorCallback(void* callback) {
    callback_registry.get_check_error_val = (uint32_t (*)(void))callback;
}

// 设置警告检查回调函数到注册表
void RegisterCheckWarningCallback(void* callback) {
    callback_registry.get_check_warning_val = (uint32_t (*)(void))callback;
}

// 设置状态检查回调函数到注册表
void RegisterCheckStatusCallback(void* callback) {
    callback_registry.get_check_status_val = (uint32_t (*)(void))callback;
}

// 设置输入状态检查回调函数到注册表
void RegisterCheckIoInputsStatusCallback(void* callback) {
    callback_registry.get_check_di_io_val = (uint32_t (*)(void))callback;
}

// 处理Mavlink升级固件文件回调函数
void FwUpgradeOverMavlinkCallback(uint16_t const index, uint16_t const length, void const *data) {
    bsp_set_fw_upgrade_write(index, length, data);
}

static Axis *const axis = &kAxis;

void AppParamInit(void)
{
    // 初始化控制字
    kAppControlWord.Controlword = 0;      // 控制字
    kAppControlWord.Halt_running_cmd = 0; // 运行中暂停控制命令

    // 初始化状态信息
    kAppStatusInfo.Statusword = 0;                   // 状态字
    kAppStatusInfo.Error_word = 0;                   // 错误码
    kAppStatusInfo.Alarm_word = 0;                   // 警告码
    kAppStatusInfo.DC_link_circuit_voltage = 0.0f;   // 母线电压当前值
    kAppStatusInfo.Drive_accumulated_heat = 0.0f;    // 驱动器热量累计值
    kAppStatusInfo.Drive_temperature = 0.0f;         // 驱动器当前温度
    kAppStatusInfo.Motor_temperature = 0.0f;         // 电机当前温度
    kAppStatusInfo.Mcu_temperature = 0.0f;           // MCU当前温度
    kAppStatusInfo.Digital_io_inputs_status = 0;     // 数字输入状态
    kAppStatusInfo.Brake_state = BRAKE_STATE_ENGAGED;// 抱闸状态

    // 初始化运动信息
    kAppMotionInfo.Position_demand_value = 0;        // 位置指令值
    kAppMotionInfo.Position_actual_value_inc = 0;    // 负载端位置当前值
    kAppMotionInfo.Position_actual_value = 0;        // 位置当前值
    kAppMotionInfo.Following_error_actual_value = 0; // 负载端位置误差值
    kAppMotionInfo.Velocity_demand_value = 0.0f;     // 速度指令值
    kAppMotionInfo.Velocity_actual_value = 0.0f;     // 负载端速度当前值
    kAppMotionInfo.Torque_demand_value = 0.0f;       // 力矩指令值
    kAppMotionInfo.Torque_actual_value = 0.0f;       // 力矩当前值
    kAppMotionInfo.Current_actual_value = 0.0f;      // 电流当前值
    kAppMotionInfo.D_current_actual_value = 0.0f;    // D轴电流当前值

    // 初始化操作模式
    kAppOpMode.Modes_of_operation = 0; // 运行模式

    // 初始化基础配置  恢复出厂的默认配置
    kAppBaseConfig.Home_position_offset_value = 0;                                              // 回零完成位置偏移值
    kAppBaseConfig.Polarity = 0;                                                                // 运动极性
    kAppBaseConfig.Can_id = 0x15;                                                               // CAN ID
    kAppBaseConfig.Can_baudrate = 1000000;                                                      // CAN 波特率
    kAppBaseConfig.Quick_stop_option_code = 2;                                                  // 快速停机方式选择
    kAppBaseConfig.Brake_engage_time = BRAKE_ENGAGE_ACTION_TIME;                                // 抱闸动作时间
    kAppBaseConfig.Brake_release_time = BRAKE_RELEASE_ACTION_TIME;                              // 松闸动作时间
    kAppBaseConfig.Dynamic_brake_speed_threshold = DYNAMIC_BRAKE_SPEED_THRESHOLD;               // 抱闸制动速度阈值
    kAppBaseConfig.Brake_release_hold_voltage = BRAKE_RELEASE_HOLD_VOLTAGE;                     // 松闸保持电压
    kAppBaseConfig.Digital_io_outputs_phys = 0;                                                 // 数字输出物理状态
    kAppBaseConfig.Digital_io_outputs_mask = 0;                                                 // 数字输出掩码
    kAppBaseConfig.Brake_control_mode = BRAKE_CONTROL_MODE_IO_AUTO;                             // 抱闸控制模式
    kAppBaseConfig.Brake_rated_voltage = BRAKE_RATED_VOLTAGE;                                   // 抱闸器额定电压
    kAppBaseConfig.Brake_release_pwm_freq = BRAKE_RELEASE_PWM_FREQ;                             // 松闸PWM频率
    kAppBaseConfig.Brake_engage_delay_time = BRAKE_ENGAGE_DELAY_TIME;                           // 抱闸延迟时间
    kAppBaseConfig.Brake_release_delay_time = BRAKE_RELEASE_DELAY_TIME;                         // 松闸延迟时间

    // 初始化编码器配置
    kAppEncoderConfig.Load_encoder_resolution = PMSM_LOAD_ENC_LINE_ORG;                         // 负载端位置反馈分辨率
    kAppEncoderConfig.Motor_encoder_resolution = PMSM_MOTOR_ENC_LINE_ORG;                       // 电机端位置反馈分辨率
    kAppEncoderConfig.Motor_encoder_options = 0;                                                // 电机端编码器选项
    kAppEncoderConfig.Motor_encoder_options |= (PMSM_MOTOR_ENC_DIR << 0);                       // 电机端编码器选项Bit0-编码器A方向

    kAppEncoderConfig.Load_pps_2_rpm = (PMSM_LOAD_ENC_LINE_P_N != 0u) ?                         // 负载端速度P/s转换RPM系数
                                       (60.0f / (float)PMSM_LOAD_ENC_LINE_P_N) :
                                       (60.0f / (float)PMSM_MOTOR_ENC_LINE_P_N);
    kAppEncoderConfig.Load_rpm_2_pps = (PMSM_LOAD_ENC_LINE_P_N != 0u) ?                         // 负载端速度RPM转换P/s系数
                                       ((float)PMSM_LOAD_ENC_LINE_P_N / 60.0f) :
                                       ((float)PMSM_MOTOR_ENC_LINE_P_N / 60.0f);
    kAppEncoderConfig.Motor_pps_2_rpm = 60.0f / (float)PMSM_MOTOR_ENC_LINE_P_N;                 // 电机端速度P/s转换RPM系数
    kAppEncoderConfig.Motor_rpm_2_pps = (float)PMSM_MOTOR_ENC_LINE_P_N / 60.0f;                 // 电机端速度RPM转换P/s系数
    kAppEncoderConfig.P_load_2_motor = (PMSM_LOAD_ENC_LINE_P_N != 0u) ?                         // 负载端到电机端P转换系数
                                       ((float)PMSM_MOTOR_ENC_LINE_P_N /
                                       (float)PMSM_LOAD_ENC_LINE_P_N) : 1.0f;
    kAppEncoderConfig.P_motor_2_load = (float)PMSM_LOAD_ENC_LINE_P_N /                          // 电机端到负载端P转换系数
                                       (float)PMSM_MOTOR_ENC_LINE_P_N;

    kAppEncoderConfig.Load_control_resolution = PMSM_LOAD_ENC_LINE_P_N;                         // 负载端位置指令分辨率
    kAppEncoderConfig.Motor_control_resolution = PMSM_MOTOR_ENC_LINE_P_N;                       // 电机端位置指令分辨率
    kAppEncoderConfig.Load_encoder_options = 0;                                                 // 负载端编码器选项
    kAppEncoderConfig.Load_encoder_options |= (PMSM_LOAD_ENC_DIR << 0);                         // 负载端编码器选项Bit0-编码器A方向

    // 初始化电机配置
    kAppMotorConfig.Motor_rated_current = PMSM_RATED_CURRENT;                                    // 电机额定电流
    kAppMotorConfig.Motor_rated_torque = 0.0f;                                                   // 电机额定力矩/推力
    kAppMotorConfig.Motor_peak_current = PMSM_PEAK_CURRENT;                                      // 电机峰值电流
    kAppMotorConfig.Motor_pole_pairs = PMSM_PN;                                                  // 电机极对数（旋转电机）
    kAppMotorConfig.Motor_maximum_speed = PMSM_SPEED_MAX_RPM;                                    // 电机最大转速/速度
    kAppMotorConfig.Resistance = PMSM_Rp2p;                                                      // 电机相间电阻
    kAppMotorConfig.Inductance = PMSM_Lp2p;                                                      // 电机相间电感
    kAppMotorConfig.Reduction_ratio_num = GEAR_RATIO_NUM;                                        // 减速比分子
    kAppMotorConfig.Reduction_ratio_den = GEAR_RATIO_DEN;                                        // 减速比分母
    kAppMotorConfig.Torque_constant = PMSM_TORQUE_CONSTANT_MNM_A;                                // 转矩常数 mNm/A
    kAppMotorConfig.Reduction_ratio_inv = (float)GEAR_RATIO_DEN / (float)GEAR_RATIO_NUM;         // 减速比倒数
    kAppMotorConfig.Reduction_ratio = (float)GEAR_RATIO_NUM / (float)GEAR_RATIO_DEN;             // 减速比系数
    kAppMotorConfig.Motor_rotor_inertia = PMSM_J * 1e4f;                                         // 电机转子惯量

    // 初始化保护配置
    kAppProtectConfig.Bus_under_voltage_threshold = UNDER_VOLTAGE_PROTECTION_V;                    // 母线欠压阈值
    kAppProtectConfig.Bus_over_voltage_threshold = OVER_VOLTAGE_PROTECTION_V;                      // 母线过压阈值
    kAppProtectConfig.Drive_overload_current_duration = 2.0f;                                      // 驱动器过流持续时间
    kAppProtectConfig.Drive_peak_current_duration = 0.2f;                                          // 驱动器峰值电流持续时间
    kAppProtectConfig.Drive_temperature_threshold_time = 2.0f;                                     // 驱动器温度保护阈值时间
    kAppProtectConfig.Drive_low_temperature_fault_threshold = UNDER_TEMP_PROTECTION_C;             // 驱动器低温报错阈值
    kAppProtectConfig.Drive_high_temperature_fault_threshold = OVER_TEMP_PROTECTION_C;             // 驱动器高温报错阈值
    kAppProtectConfig.Overspeed_threshold = PMSM_SPEED_MAX_RPM * 1.2f;                             // 过速阈值
    kAppProtectConfig.Drive_overcurrent_threshold = DRIVER_OVERCURRENT_LIMIT_A;                    // 驱动器过流保护阈值 软件检测过流
    kAppProtectConfig.Protection_enable = 0xFFFF;                                                  // 软件保护 默认全部生效
    kAppProtectConfig.Motor_high_temperature_fault_threshold = MOTOR_HIGH_TEMP_FAULT_THRESHOLD;    // 电机过温保护
    kAppProtectConfig.Motor_low_temperature_fault_threshold = MOTOR_LOW_TEMP_FAULT_THRESHOLD;      // 电机低温保护
    kAppProtectConfig.Can_timeout = 0.5f;                                                          // CAN通讯超时时间
    kAppProtectConfig.Motor_low_temperature_warning_threshold = MOTOR_LOW_TEMP_WARING_THRESHOLD;   // 电机过温警告
    kAppProtectConfig.Motor_high_temperature_warning_threshold = MOTOR_HIGH_TEMP_WARING_THRESHOLD; // 电机低温警告
    kAppProtectConfig.Mcu_temperature_threshold_time = 2.0f;                                       // MCU温度保护阈值时间
    kAppProtectConfig.Mcu_low_temperature_fault_threshold = UNDER_TEMP_PROTECTION_C;               // MCU低温报错阈值
    kAppProtectConfig.Mcu_high_temperature_fault_threshold = OVER_TEMP_PROTECTION_C;               // MCU高温报错阈值
    kAppProtectConfig.Mcu_low_temperature_warning_threshold = UNDER_TEMP_WARNING_C;                // MCU低温警告阈值
    kAppProtectConfig.Mcu_high_temperature_warning_threshold = OVER_TEMP_WARNING_C;                // MCU高温警告阈值
    kAppProtectConfig.Drive_low_temperature_warning_threshold = UNDER_TEMP_WARNING_C;              // 驱动器低温警告阈值
    kAppProtectConfig.Drive_high_temperature_warning_threshold = OVER_TEMP_WARNING_C;              // 驱动器高温警告阈值

    // 初始化运动参数
    kAppMotionParam.Target_position = 0;                              // 位置目标值
    kAppMotionParam.Profile_velocity = 10.0f;                         // 轮廓速度
    kAppMotionParam.Profile_acceleration = 10.0f;                     // 轮廓加速度
    kAppMotionParam.Profile_deceleration = 10.0f;                     // 轮廓减速度
    kAppMotionParam.Quick_stop_deceleration = (float)(0xFFFFFFFF) * kAppEncoderConfig.Load_pps_2_rpm;   // 快速停止减速度
    kAppMotionParam.Motion_profile_type = 0;                          // 运动轮廓模式（规划器类型）
    kAppMotionParam.Home_offset = 0;                                  // 回零偏移
    kAppMotionParam.Homing_method = 0;                                // 回零方法
    kAppMotionParam.Target_velocity = 0.0f;                           // 速度目标值
    kAppMotionParam.Target_torque = 0.0f;                             // 力矩目标值
    kAppMotionParam.Torque_slope = 1.0f;                              // 力矩上升斜率
    kAppMotionParam.MIT_max_current = PMSM_PEAK_CURRENT;              // 电机峰值电流
    kAppMotionParam.MIT_kp = 0.01f;                                   // MIT位置刚度
    kAppMotionParam.MIT_kd = 0.01f;                                   // MIT速度阻尼系数
    kAppMotionParam.Interp_time_value = 1;                            // 插值时间基数
    kAppMotionParam.Interp_time_index = -3;                           // 插值时间指数
    kAppMotionParam.Homing_speed_search_for_switch = 10.0f;           // 回零搜索开关速度
    kAppMotionParam.Homing_speed_search_for_zero = 1.0f;              // 回零搜索零点速度
    kAppMotionParam.Homing_acceleration = 100.0f;                     // 回零加速度

    // 初始化限制参数
    kAppRestrictParam.Position_range_limit_Minimal_position_limit = 0x8000000000000000;     // 位置溢出最小值
    kAppRestrictParam.Position_range_limit_Maximal_position_limit = 0x7FFFFFFFFFFFFFFF;     // 位置溢出最大值
    kAppRestrictParam.Software_position_limit_Minimal_position_limit = 0x8000000000000000;  // 应用位置下限
    kAppRestrictParam.Software_position_limit_Maximal_position_limit = 0x7FFFFFFFFFFFFFFF;  // 应用位置上限
    kAppRestrictParam.Max_profile_velocity = kAppMotorConfig.Motor_maximum_speed * kAppMotorConfig.Reduction_ratio_inv; // 应用速度限制
    kAppRestrictParam.Max_motor_speed = kAppMotorConfig.Motor_maximum_speed;                // 电机最大转速/速度(RPM)
    kAppRestrictParam.Max_acceleration = (float)(0xFFFFFFFF) * kAppEncoderConfig.Load_pps_2_rpm;   // 应用加速度限制
    kAppRestrictParam.Max_deceleration = (float)(0xFFFFFFFF) * kAppEncoderConfig.Load_pps_2_rpm;   // 应用减速度限制
    kAppRestrictParam.Max_current = kAppMotorConfig.Motor_rated_current; // 应用电流限制相对值
    kAppRestrictParam.Position_limit_enable = 0;        // 位置限制使能

    // 初始化窗口参数
    kAppWindowParam.Following_error_window = 10000;     // 位置跟随误差阈值
    kAppWindowParam.Following_error_time_out = 0.02f;   // 位置跟随误差阈值时间
    kAppWindowParam.Position_window = 100;              // 位置到达检测窗口
    kAppWindowParam.Position_window_time = 0.02f;       // 位置到达检测窗口时间
    kAppWindowParam.Velocity_window = 10.0f;            // 速度到达检测窗口
    kAppWindowParam.Velocity_window_time = 0.02f;       // 速度到达检测窗口时间
    kAppWindowParam.Velocity_threshold = 10.0f;         // 零速检测窗口(RPM)
    kAppWindowParam.Velocity_threshold_time = 0.02f;    // 零速检测窗口时间

    // 初始化Mavlink参数
    kAppMavlinkConfig.Sys_id = 1;                       // mavlink系统id
    kAppMavlinkConfig.Comp_id = 1;                      // mavlink组件id

    // 初始化系统指令
    kSystemCmd.Sys_cmd = APP_SYSTEM_CMD_NONE;           // 系统指令

    // 初始化控制权限
    kAppPermissionConfig.Comm_control_authority = COMM_CONTROL_BUS;    // 默认开启进入总线控制

    // 其它参数初始化
    kEncoderCalibrationCmd.Calibration_time = 5;        // 校准时间(S)

    kHeartBit.Sys_init_flag = 0xEA;                     // 系统初始化标志位(0xEA（Energy Active）)

    // 初始化历史信息
    for (uint8_t i = 0; i < ERROR_RECORD_NUM; i++)
    {
        kHistoricalInfo.Error_records_list[i] = 0;
    }

    // 初始化文件传输配置
    kAppFileTransferConfig.File_type = APP_FILE_TYPE_IDLE;          //文件传输类型
    kAppFileTransferConfig.File_size = 0;                           //文件传输大小
    kAppFileTransferConfig.File_direction = APP_FILE_DIR_DOWNLOAD;  //文件传输方向
    kAppFileTransferConfig.File_index_complete = 0;                 //文件传输完成帧索引

    // 初始化固件传输参数
    kAppFwUpgradeParam.Fw_mode = 0;                                 //固件传输模式

    // 额定参数初始化
    set_app_Load_encoder_resolution(kAppEncoderConfig.Load_encoder_resolution);
    set_app_Motor_encoder_resolution(kAppEncoderConfig.Motor_encoder_resolution);
    set_app_Polarity(kAppBaseConfig.Polarity);
    set_app_Motor_rated_current(kAppMotorConfig.Motor_rated_current);
    set_app_Motor_rated_torque(kAppMotorConfig.Motor_rated_torque);
    set_app_Overspeed_threshold(kAppProtectConfig.Overspeed_threshold);
    set_app_Motor_peak_current(kAppMotorConfig.Motor_peak_current);
    set_app_Motor_pole_pairs(kAppMotorConfig.Motor_pole_pairs);
    set_app_Motor_maximum_speed(kAppMotorConfig.Motor_maximum_speed);
    set_app_Reduction_ratio_num(kAppMotorConfig.Reduction_ratio_num);
    set_app_Reduction_ratio_den(kAppMotorConfig.Reduction_ratio_den);
    set_app_Motor_encoder_options(kAppEncoderConfig.Motor_encoder_options);
    set_app_Load_encoder_options(kAppEncoderConfig.Load_encoder_options);
    set_app_Load_control_resolution(kAppEncoderConfig.Load_control_resolution);
    set_app_Motor_control_resolution(kAppEncoderConfig.Motor_control_resolution);

    // 限制参数初始化
    set_app_Position_range_limit_Maximal_position_limit(kAppRestrictParam.Position_range_limit_Maximal_position_limit);
    set_app_Position_range_limit_Minimal_position_limit(kAppRestrictParam.Position_range_limit_Minimal_position_limit);
    set_app_Software_position_limit_Maximal_position_limit(kAppRestrictParam.Software_position_limit_Maximal_position_limit);
    set_app_Software_position_limit_Minimal_position_limit(kAppRestrictParam.Software_position_limit_Minimal_position_limit);
    set_app_Max_profile_velocity(kAppRestrictParam.Max_profile_velocity);
    set_app_Max_motor_speed(kAppRestrictParam.Max_motor_speed);
    set_app_Max_acceleration(kAppRestrictParam.Max_acceleration);
    set_app_Max_deceleration(kAppRestrictParam.Max_deceleration);

    // 关联更新参数
    app_param_update();
}

// app 参数相互限制关系更新
void app_param_restrictions_update(void)
{
    // 电流相关限制关系更新
    //  电机峰值电流>=应用电流限制>=最大电流(各个应用)>=目标电流
    float motor_peak_current_Apeak = kAppMotorConfig.Motor_peak_current * MATH_ARMS2APEAK;

    if (kAppRestrictParam.Max_current > motor_peak_current_Apeak) // 更新应用限制电流
    {
        kAppRestrictParam.Max_current = motor_peak_current_Apeak;
    }
    axis->pos_speed_ctl_input.iq_max_A = kAppRestrictParam.Max_current;

    if (MATH_ABS(kAppMotionParam.Target_torque) > kAppRestrictParam.Max_current) // 当设定 最大力矩时候 ，目标力矩更大则限制
    {
        if (kAppMotionParam.Target_torque >= 0)
        {
            kAppMotionParam.Target_torque = kAppRestrictParam.Max_current;
        }
        else
        {
            kAppMotionParam.Target_torque = -kAppRestrictParam.Max_current;
        }
    }

    if (kAppMotionParam.MIT_max_current > kAppRestrictParam.Max_current) // 更新各个应用最大电流
    {
        kAppMotionParam.MIT_max_current = kAppRestrictParam.Max_current;
    }

    // 速度相关限制关系更新
    // 电机最大速度 >=应用速度限制>=轮廓速度、目标速度
    if (kAppRestrictParam.Max_profile_velocity >= kAppMotorConfig.Motor_maximum_speed * kAppMotorConfig.Reduction_ratio_inv)
    {
        kAppRestrictParam.Max_profile_velocity = kAppMotorConfig.Motor_maximum_speed * kAppMotorConfig.Reduction_ratio_inv;
    }
}

// 用户自定义的更新的变量
void AppParamSyncUser(void)
{
    get_app_Statusword();
    get_app_Error_word();

    get_app_Position_demand_value();
    get_app_Position_actual_value_inc();
    get_app_Position_actual_value();
    get_app_Following_error_actual_value();
    get_app_Velocity_demand_value();
    get_app_Velocity_actual_value();
    get_app_Torque_demand_value();

    get_app_Torque_actual_value();
    get_app_Current_actual_value();
    get_app_DC_link_circuit_voltage();

    get_app_Drive_temperature();

    get_app_D_current_actual_value();

    get_app_Alarm_word();

    get_app_Modes_of_operation_display();

    get_app_Version();

    get_app_U_current_actual_value();
    get_app_V_current_actual_value();
    get_app_W_current_actual_value();

    get_app_Motor_position_demand_value();
    get_app_Motor_position_actual_value();
    get_app_Motor_following_error_actual_value();
    get_app_Motor_velocity_demand_value();
    get_app_Motor_velocity_actual_value();

    get_app_Motor_power();

    get_app_Current_loop_time();
    get_app_Position_loop_time();
    get_app_Current_loop_cycle();
    get_app_Position_loop_cycle();
}

/* USER CODE END AREA 0 */

AppControlWord kAppControlWord;
AppStatusInfo kAppStatusInfo;
AppOpMode kAppOpMode;
AppEncoderConfig kAppEncoderConfig;
AppBaseConfig kAppBaseConfig;
AppMotionParam kAppMotionParam;
AppRestrictParam kAppRestrictParam;
AppMotionInfo kAppMotionInfo;
AppWindowParam kAppWindowParam;
AppMotorConfig kAppMotorConfig;
AppProtectConfig kAppProtectConfig;
AppPermissionConfig kAppPermissionConfig;
SystemCmd kSystemCmd;
SystemStatus kSystemStatus;
EncoderCalibrationCmd kEncoderCalibrationCmd;
EncoderCalibrationStatus kEncoderCalibrationStatus;
CustomInfo kCustomInfo;
HeartBit kHeartBit;
HistoricalInfo kHistoricalInfo;
AppDebugParam kAppDebugParam;
AppMavlinkConfig kAppMavlinkConfig;
AppFileTransferConfig kAppFileTransferConfig;
AppFwUpgradeParam kAppFwUpgradeParam;

void app_param_update(void)
{
    set_app_Controlword(kAppControlWord.Controlword);
    set_app_Statusword(kAppStatusInfo.Statusword);
    set_app_Error_word(kAppStatusInfo.Error_word);
    set_app_Modes_of_operation(kAppOpMode.Modes_of_operation);
    set_app_Load_encoder_resolution(kAppEncoderConfig.Load_encoder_resolution);
    set_app_Motor_encoder_resolution(kAppEncoderConfig.Motor_encoder_resolution);
    set_app_Polarity(kAppBaseConfig.Polarity);
    set_app_Target_position(kAppMotionParam.Target_position);
    set_app_Position_range_limit_Minimal_position_limit(kAppRestrictParam.Position_range_limit_Minimal_position_limit);
    set_app_Position_range_limit_Maximal_position_limit(kAppRestrictParam.Position_range_limit_Maximal_position_limit);
    set_app_Software_position_limit_Minimal_position_limit(kAppRestrictParam.Software_position_limit_Minimal_position_limit);
    set_app_Software_position_limit_Maximal_position_limit(kAppRestrictParam.Software_position_limit_Maximal_position_limit);
    set_app_Max_profile_velocity(kAppRestrictParam.Max_profile_velocity);
    set_app_Max_motor_speed(kAppRestrictParam.Max_motor_speed);
    set_app_Profile_velocity(kAppMotionParam.Profile_velocity);
    set_app_Profile_acceleration(kAppMotionParam.Profile_acceleration);
    set_app_Profile_deceleration(kAppMotionParam.Profile_deceleration);
    set_app_Quick_stop_deceleration(kAppMotionParam.Quick_stop_deceleration);
    set_app_Motion_profile_type(kAppMotionParam.Motion_profile_type);
    set_app_Max_acceleration(kAppRestrictParam.Max_acceleration);
    set_app_Max_deceleration(kAppRestrictParam.Max_deceleration);
    set_app_Home_offset(kAppMotionParam.Home_offset);
    set_app_Homing_method(kAppMotionParam.Homing_method);
    set_app_Position_demand_value(kAppMotionInfo.Position_demand_value);
    set_app_Position_actual_value_inc(kAppMotionInfo.Position_actual_value_inc);
    set_app_Position_actual_value(kAppMotionInfo.Position_actual_value);
    set_app_Following_error_window(kAppWindowParam.Following_error_window);
    set_app_Following_error_time_out(kAppWindowParam.Following_error_time_out);
    set_app_Position_window(kAppWindowParam.Position_window);
    set_app_Position_window_time(kAppWindowParam.Position_window_time);
    set_app_Following_error_actual_value(kAppMotionInfo.Following_error_actual_value);
    set_app_Velocity_demand_value(kAppMotionInfo.Velocity_demand_value);
    set_app_Velocity_actual_value(kAppMotionInfo.Velocity_actual_value);
    set_app_Velocity_window(kAppWindowParam.Velocity_window);
    set_app_Velocity_window_time(kAppWindowParam.Velocity_window_time);
    set_app_Velocity_threshold(kAppWindowParam.Velocity_threshold);
    set_app_Velocity_threshold_time(kAppWindowParam.Velocity_threshold_time);
    set_app_Target_velocity(kAppMotionParam.Target_velocity);
    set_app_Target_torque(kAppMotionParam.Target_torque);
    set_app_Max_current(kAppRestrictParam.Max_current);
    set_app_Torque_demand_value(kAppMotionInfo.Torque_demand_value);
    set_app_Motor_rated_current(kAppMotorConfig.Motor_rated_current);
    set_app_Motor_rated_torque(kAppMotorConfig.Motor_rated_torque);
    set_app_Torque_actual_value(kAppMotionInfo.Torque_actual_value);
    set_app_Current_actual_value(kAppMotionInfo.Current_actual_value);
    set_app_DC_link_circuit_voltage(kAppStatusInfo.DC_link_circuit_voltage);
    set_app_Torque_slope(kAppMotionParam.Torque_slope);
    set_app_Home_position_offset_value(kAppBaseConfig.Home_position_offset_value);
    set_app_Bus_under_voltage_threshold(kAppProtectConfig.Bus_under_voltage_threshold);
    set_app_Bus_over_voltage_threshold(kAppProtectConfig.Bus_over_voltage_threshold);
    set_app_Drive_overload_current_duration(kAppProtectConfig.Drive_overload_current_duration);
    set_app_Drive_peak_current_duration(kAppProtectConfig.Drive_peak_current_duration);
    set_app_Drive_temperature_threshold_time(kAppProtectConfig.Drive_temperature_threshold_time);
    set_app_Drive_low_temperature_fault_threshold(kAppProtectConfig.Drive_low_temperature_fault_threshold);
    set_app_Drive_high_temperature_fault_threshold(kAppProtectConfig.Drive_high_temperature_fault_threshold);
    set_app_Overspeed_threshold(kAppProtectConfig.Overspeed_threshold);
    set_app_Drive_accumulated_heat(kAppStatusInfo.Drive_accumulated_heat);
    set_app_Drive_temperature(kAppStatusInfo.Drive_temperature);
    set_app_Motor_peak_current(kAppMotorConfig.Motor_peak_current);
    set_app_Motor_pole_pairs(kAppMotorConfig.Motor_pole_pairs);
    set_app_Motor_maximum_speed(kAppMotorConfig.Motor_maximum_speed);
    set_app_D_current_actual_value(kAppMotionInfo.D_current_actual_value);
    set_app_Alarm_word(kAppStatusInfo.Alarm_word);
    set_app_Modes_of_operation_display(kAppStatusInfo.Modes_of_operation_display);
    set_app_Resistance(kAppMotorConfig.Resistance);
    set_app_Inductance(kAppMotorConfig.Inductance);
    set_app_Drive_overcurrent_threshold(kAppProtectConfig.Drive_overcurrent_threshold);
    set_app_Protection_enable(kAppProtectConfig.Protection_enable);
    set_app_Encoder_calibration_speed(kAppMotionParam.Encoder_calibration_speed);
    set_app_MIT_feedforward_torque(kAppMotionParam.MIT_feedforward_torque);
    set_app_MIT_target_position(kAppMotionParam.MIT_target_position);
    set_app_MIT_max_current(kAppMotionParam.MIT_max_current);
    set_app_MIT_target_velocity(kAppMotionParam.MIT_target_velocity);
    set_app_Comm_control_authority(kAppPermissionConfig.Comm_control_authority);
    set_app_Version(kAppStatusInfo.Version);
    set_app_U_current_actual_value(kAppMotionInfo.U_current_actual_value);
    set_app_V_current_actual_value(kAppMotionInfo.V_current_actual_value);
    set_app_W_current_actual_value(kAppMotionInfo.W_current_actual_value);
    set_app_Reduction_ratio_num(kAppMotorConfig.Reduction_ratio_num);
    set_app_Reduction_ratio_den(kAppMotorConfig.Reduction_ratio_den);
    set_app_Can_id(kAppBaseConfig.Can_id);
    set_app_Can_baudrate(kAppBaseConfig.Can_baudrate);
    set_app_MIT_kp(kAppMotionParam.MIT_kp);
    set_app_MIT_kd(kAppMotionParam.MIT_kd);
    set_app_Sys_cmd(kSystemCmd.Sys_cmd);
    set_app_Motor_encoder_type(kAppEncoderConfig.Motor_encoder_type);
    set_app_Load_encoder_type(kAppEncoderConfig.Load_encoder_type);
    set_app_Torque_constant(kAppMotorConfig.Torque_constant);
    set_app_Motor_position_demand_value(kAppMotionInfo.Motor_position_demand_value);
    set_app_Motor_position_actual_value(kAppMotionInfo.Motor_position_actual_value);
    set_app_Motor_following_error_actual_value(kAppMotionInfo.Motor_following_error_actual_value);
    set_app_Motor_velocity_demand_value(kAppMotionInfo.Motor_velocity_demand_value);
    set_app_Motor_velocity_actual_value(kAppMotionInfo.Motor_velocity_actual_value);
    set_app_Storage_status(kSystemStatus.Storage_status);
    set_app_Motor_temperature(kAppStatusInfo.Motor_temperature);
    set_app_Motor_low_temperature_fault_threshold(kAppProtectConfig.Motor_low_temperature_fault_threshold);
    set_app_Motor_high_temperature_fault_threshold(kAppProtectConfig.Motor_high_temperature_fault_threshold);
    set_app_Can_timeout(kAppProtectConfig.Can_timeout);
    set_app_Quick_stop_option_code(kAppBaseConfig.Quick_stop_option_code);
    set_app_Motor_power(kAppStatusInfo.Motor_power);
    set_app_Motor_low_temperature_warning_threshold(kAppProtectConfig.Motor_low_temperature_warning_threshold);
    set_app_Motor_high_temperature_warning_threshold(kAppProtectConfig.Motor_high_temperature_warning_threshold);
    set_app_Brake_engage_time(kAppBaseConfig.Brake_engage_time);
    set_app_Brake_release_time(kAppBaseConfig.Brake_release_time);
    set_app_Dynamic_brake_speed_threshold(kAppBaseConfig.Dynamic_brake_speed_threshold);
    set_app_Brake_release_hold_voltage(kAppBaseConfig.Brake_release_hold_voltage);
    set_app_Calibration_cmd(kEncoderCalibrationCmd.Calibration_cmd);
    set_app_Calibration_time(kEncoderCalibrationCmd.Calibration_time);
    set_app_Calibration_status(kEncoderCalibrationStatus.Calibration_status);
    set_app_Mcu_temperature(kAppStatusInfo.Mcu_temperature);
    set_app_Internal_control_authority(kAppPermissionConfig.Internal_control_authority);
    set_app_U_adc_mid_val(kAppMotionInfo.U_adc_mid_val);
    set_app_V_adc_mid_val(kAppMotionInfo.V_adc_mid_val);
    set_app_W_adc_mid_val(kAppMotionInfo.W_adc_mid_val);
    set_app_Current_loop_time(kAppMotionInfo.Current_loop_time);
    set_app_Position_loop_time(kAppMotionInfo.Position_loop_time);
    set_app_Current_loop_cycle(kAppMotionInfo.Current_loop_cycle);
    set_app_Position_loop_cycle(kAppMotionInfo.Position_loop_cycle);
    set_app_Halt_running_cmd(kAppControlWord.Halt_running_cmd);
    set_app_Mcu_temperature_threshold_time(kAppProtectConfig.Mcu_temperature_threshold_time);
    set_app_Mcu_low_temperature_fault_threshold(kAppProtectConfig.Mcu_low_temperature_fault_threshold);
    set_app_Mcu_high_temperature_fault_threshold(kAppProtectConfig.Mcu_high_temperature_fault_threshold);
    set_app_Mcu_low_temperature_warning_threshold(kAppProtectConfig.Mcu_low_temperature_warning_threshold);
    set_app_Mcu_high_temperature_warning_threshold(kAppProtectConfig.Mcu_high_temperature_warning_threshold);
    set_app_Drive_low_temperature_warning_threshold(kAppProtectConfig.Drive_low_temperature_warning_threshold);
    set_app_Drive_high_temperature_warning_threshold(kAppProtectConfig.Drive_high_temperature_warning_threshold);
    set_app_User_module_code(kCustomInfo.User_module_code);
    set_app_Sys_init_flag(kHeartBit.Sys_init_flag);
    set_app_Error_records_list(0, kHistoricalInfo.Error_records_list[0]);
    set_app_Motor_encoder_options(kAppEncoderConfig.Motor_encoder_options);
    set_app_Reduction_ratio(kAppMotorConfig.Reduction_ratio);
    set_app_Reduction_ratio_inv(kAppMotorConfig.Reduction_ratio_inv);
    set_app_Load_pps_2_rpm(kAppEncoderConfig.Load_pps_2_rpm);
    set_app_Load_rpm_2_pps(kAppEncoderConfig.Load_rpm_2_pps);
    set_app_Storage_cmd(kSystemStatus.Storage_cmd);
    set_app_Motor_rotor_inertia(kAppMotorConfig.Motor_rotor_inertia);
    set_app_Debug_float(0, kAppDebugParam.Debug_float[0]);
    set_app_Debug_uint32(0, kAppDebugParam.Debug_uint32[0]);
    set_app_Motor_pps_2_rpm(kAppEncoderConfig.Motor_pps_2_rpm);
    set_app_Motor_rpm_2_pps(kAppEncoderConfig.Motor_rpm_2_pps);
    set_app_P_load_2_motor(kAppEncoderConfig.P_load_2_motor);
    set_app_P_motor_2_load(kAppEncoderConfig.P_motor_2_load);
    set_app_Debug_int32(0, kAppDebugParam.Debug_int32[0]);
    set_app_Load_control_resolution(kAppEncoderConfig.Load_control_resolution);
    set_app_Motor_control_resolution(kAppEncoderConfig.Motor_control_resolution);
    set_app_Load_encoder_options(kAppEncoderConfig.Load_encoder_options);
    set_app_Position_limit_enable(kAppRestrictParam.Position_limit_enable);
    set_app_Digital_io_inputs_status(kAppStatusInfo.Digital_io_inputs_status);
    set_app_Digital_io_outputs_phys(kAppBaseConfig.Digital_io_outputs_phys);
    set_app_Digital_io_outputs_mask(kAppBaseConfig.Digital_io_outputs_mask);
    set_app_Brake_state(kAppStatusInfo.Brake_state);
    set_app_Brake_control_mode(kAppBaseConfig.Brake_control_mode);
    set_app_Brake_rated_voltage(kAppBaseConfig.Brake_rated_voltage);
    set_app_Brake_release_action_voltage(kAppBaseConfig.Brake_release_action_voltage);
    set_app_Brake_release_pwm_freq(kAppBaseConfig.Brake_release_pwm_freq);
    set_app_Brake_engage_delay_time(kAppBaseConfig.Brake_engage_delay_time);
    set_app_Brake_release_delay_time(kAppBaseConfig.Brake_release_delay_time);
    set_app_Interp_time_value(kAppMotionParam.Interp_time_value);
    set_app_Interp_time_index(kAppMotionParam.Interp_time_index);
    set_app_Sys_id(kAppMavlinkConfig.Sys_id);
    set_app_Comp_id(kAppMavlinkConfig.Comp_id);
    set_app_Interp_period(kAppMotionInfo.Interp_period);
    set_app_Emergency_brake_requested(kAppMotionInfo.Emergency_brake_requested);
    set_app_Target_update_state(kAppMotionInfo.Target_update_state);
    set_app_Homing_speed_search_for_switch(kAppMotionParam.Homing_speed_search_for_switch);
    set_app_Homing_speed_search_for_zero(kAppMotionParam.Homing_speed_search_for_zero);
    set_app_Homing_acceleration(kAppMotionParam.Homing_acceleration);
    set_app_Homing_step(kAppMotionInfo.Homing_step);
    set_app_Encoder_zero_crossing_state(kAppMotionInfo.Encoder_zero_crossing_state);
    set_app_Homing_state(kAppMotionInfo.Homing_state);
    set_app_File_type(kAppFileTransferConfig.File_type);
    set_app_File_size(kAppFileTransferConfig.File_size);
    set_app_File_direction(kAppFileTransferConfig.File_direction);
    set_app_File_index_complete(kAppFileTransferConfig.File_index_complete);
    set_app_File_status(kAppFileTransferConfig.File_status);
    set_app_Fw_mode(kAppFwUpgradeParam.Fw_mode);
    set_app_Fw_app_index(kAppFwUpgradeParam.Fw_app_index);
    set_app_Fw_flash_size(kAppFwUpgradeParam.Fw_flash_size);
    set_app_Fw_operating_steps(kAppFwUpgradeParam.Fw_operating_steps);
}

void app_param_sync(void)
{
    get_app_Controlword();
    get_app_Statusword();
    get_app_Error_word();
    get_app_Modes_of_operation();
    get_app_Load_encoder_resolution();
    get_app_Motor_encoder_resolution();
    get_app_Polarity();
    get_app_Target_position();
    get_app_Position_range_limit_Minimal_position_limit();
    get_app_Position_range_limit_Maximal_position_limit();
    get_app_Software_position_limit_Minimal_position_limit();
    get_app_Software_position_limit_Maximal_position_limit();
    get_app_Max_profile_velocity();
    get_app_Max_motor_speed();
    get_app_Profile_velocity();
    get_app_Profile_acceleration();
    get_app_Profile_deceleration();
    get_app_Quick_stop_deceleration();
    get_app_Motion_profile_type();
    get_app_Max_acceleration();
    get_app_Max_deceleration();
    get_app_Home_offset();
    get_app_Homing_method();
    get_app_Position_demand_value();
    get_app_Position_actual_value_inc();
    get_app_Position_actual_value();
    get_app_Following_error_window();
    get_app_Following_error_time_out();
    get_app_Position_window();
    get_app_Position_window_time();
    get_app_Following_error_actual_value();
    get_app_Velocity_demand_value();
    get_app_Velocity_actual_value();
    get_app_Velocity_window();
    get_app_Velocity_window_time();
    get_app_Velocity_threshold();
    get_app_Velocity_threshold_time();
    get_app_Target_velocity();
    get_app_Target_torque();
    get_app_Max_current();
    get_app_Torque_demand_value();
    get_app_Motor_rated_current();
    get_app_Motor_rated_torque();
    get_app_Torque_actual_value();
    get_app_Current_actual_value();
    get_app_DC_link_circuit_voltage();
    get_app_Torque_slope();
    get_app_Home_position_offset_value();
    get_app_Bus_under_voltage_threshold();
    get_app_Bus_over_voltage_threshold();
    get_app_Drive_overload_current_duration();
    get_app_Drive_peak_current_duration();
    get_app_Drive_temperature_threshold_time();
    get_app_Drive_low_temperature_fault_threshold();
    get_app_Drive_high_temperature_fault_threshold();
    get_app_Overspeed_threshold();
    get_app_Drive_accumulated_heat();
    get_app_Drive_temperature();
    get_app_Motor_peak_current();
    get_app_Motor_pole_pairs();
    get_app_Motor_maximum_speed();
    get_app_D_current_actual_value();
    get_app_Alarm_word();
    get_app_Modes_of_operation_display();
    get_app_Resistance();
    get_app_Inductance();
    get_app_Drive_overcurrent_threshold();
    get_app_Protection_enable();
    get_app_Encoder_calibration_speed();
    get_app_MIT_feedforward_torque();
    get_app_MIT_target_position();
    get_app_MIT_max_current();
    get_app_MIT_target_velocity();
    get_app_Comm_control_authority();
    get_app_Version();
    get_app_U_current_actual_value();
    get_app_V_current_actual_value();
    get_app_W_current_actual_value();
    get_app_Reduction_ratio_num();
    get_app_Reduction_ratio_den();
    get_app_Can_id();
    get_app_Can_baudrate();
    get_app_MIT_kp();
    get_app_MIT_kd();
    get_app_Sys_cmd();
    get_app_Motor_encoder_type();
    get_app_Load_encoder_type();
    get_app_Torque_constant();
    get_app_Motor_position_demand_value();
    get_app_Motor_position_actual_value();
    get_app_Motor_following_error_actual_value();
    get_app_Motor_velocity_demand_value();
    get_app_Motor_velocity_actual_value();
    get_app_Storage_status();
    get_app_Motor_temperature();
    get_app_Motor_low_temperature_fault_threshold();
    get_app_Motor_high_temperature_fault_threshold();
    get_app_Can_timeout();
    get_app_Quick_stop_option_code();
    get_app_Motor_power();
    get_app_Motor_low_temperature_warning_threshold();
    get_app_Motor_high_temperature_warning_threshold();
    get_app_Brake_engage_time();
    get_app_Brake_release_time();
    get_app_Dynamic_brake_speed_threshold();
    get_app_Brake_release_hold_voltage();
    get_app_Calibration_cmd();
    get_app_Calibration_time();
    get_app_Calibration_status();
    get_app_Mcu_temperature();
    get_app_Internal_control_authority();
    get_app_U_adc_mid_val();
    get_app_V_adc_mid_val();
    get_app_W_adc_mid_val();
    get_app_Current_loop_time();
    get_app_Position_loop_time();
    get_app_Current_loop_cycle();
    get_app_Position_loop_cycle();
    get_app_Halt_running_cmd();
    get_app_Mcu_temperature_threshold_time();
    get_app_Mcu_low_temperature_fault_threshold();
    get_app_Mcu_high_temperature_fault_threshold();
    get_app_Mcu_low_temperature_warning_threshold();
    get_app_Mcu_high_temperature_warning_threshold();
    get_app_Drive_low_temperature_warning_threshold();
    get_app_Drive_high_temperature_warning_threshold();
    get_app_User_module_code();
    get_app_Sys_init_flag();
    get_app_Error_records_list(0);
    get_app_Motor_encoder_options();
    get_app_Reduction_ratio();
    get_app_Reduction_ratio_inv();
    get_app_Load_pps_2_rpm();
    get_app_Load_rpm_2_pps();
    get_app_Storage_cmd();
    get_app_Motor_rotor_inertia();
    get_app_Debug_float(0);
    get_app_Debug_uint32(0);
    get_app_Motor_pps_2_rpm();
    get_app_Motor_rpm_2_pps();
    get_app_P_load_2_motor();
    get_app_P_motor_2_load();
    get_app_Debug_int32(0);
    get_app_Load_control_resolution();
    get_app_Motor_control_resolution();
    get_app_Load_encoder_options();
    get_app_Position_limit_enable();
    get_app_Digital_io_inputs_status();
    get_app_Digital_io_outputs_phys();
    get_app_Digital_io_outputs_mask();
    get_app_Brake_state();
    get_app_Brake_control_mode();
    get_app_Brake_rated_voltage();
    get_app_Brake_release_action_voltage();
    get_app_Brake_release_pwm_freq();
    get_app_Brake_engage_delay_time();
    get_app_Brake_release_delay_time();
    get_app_Interp_time_value();
    get_app_Interp_time_index();
    get_app_Sys_id();
    get_app_Comp_id();
    get_app_Interp_period();
    get_app_Emergency_brake_requested();
    get_app_Target_update_state();
    get_app_Homing_speed_search_for_switch();
    get_app_Homing_speed_search_for_zero();
    get_app_Homing_acceleration();
    get_app_Homing_step();
    get_app_Encoder_zero_crossing_state();
    get_app_Homing_state();
    get_app_File_type();
    get_app_File_size();
    get_app_File_direction();
    get_app_File_index_complete();
    get_app_File_status();
    get_app_Fw_mode();
    get_app_Fw_app_index();
    get_app_Fw_flash_size();
    get_app_Fw_operating_steps();
}

uint32_t set_app_Controlword(uint16_t val)
{
    if (val < 0)
        return APP_PARAM_OUT_OF_RANGE;
    if (val > 3)
        return APP_PARAM_OUT_OF_RANGE;

    /* USER CODE BEGIN set_app_Controlword 0 */
    // 切换到控制层控制后,应用层控制字不再生效
    if (get_app_Internal_control_authority() == INTERNAL_CONTROL_CTRL)
    {
        return APP_PARAM_READ_ONLY;
    }
    /* USER CODE END set_app_Controlword 0 */
    kAppControlWord.Controlword = val;
    /* USER CODE BEGIN set_app_Controlword 1 */
    axis->motor_ctl_sm_input.motor_enable = val;
    /* USER CODE END set_app_Controlword 1 */
    return APP_PARAM_SUCCESS;
}
uint16_t get_app_Controlword(void)
{
    /* USER CODE BEGIN get_app_Controlword */
    /* USER CODE END get_app_Controlword */
    return kAppControlWord.Controlword;
}

uint32_t set_app_Halt_running_cmd(uint8_t val)
{
    if (val < 0)
        return APP_PARAM_OUT_OF_RANGE;
    if (val > 1)
        return APP_PARAM_OUT_OF_RANGE;

    /* USER CODE BEGIN set_app_Halt_running_cmd 0 */
    /* USER CODE END set_app_Halt_running_cmd 0 */
    kAppControlWord.Halt_running_cmd = val;
    /* USER CODE BEGIN set_app_Halt_running_cmd 1 */
    /* USER CODE END set_app_Halt_running_cmd 1 */
    return APP_PARAM_SUCCESS;
}
uint8_t get_app_Halt_running_cmd(void)
{
    /* USER CODE BEGIN get_app_Halt_running_cmd */
    /* USER CODE END get_app_Halt_running_cmd */
    return kAppControlWord.Halt_running_cmd;
}

uint32_t set_app_Statusword(uint32_t val)
{
    /* USER CODE BEGIN set_app_Statusword 0 */
    /* USER CODE END set_app_Statusword 0 */
    kAppStatusInfo.Statusword = val;

    return APP_PARAM_SUCCESS;
}
uint32_t get_app_Statusword(void)
{
    /* USER CODE BEGIN get_app_Statusword */
    if (callback_registry.get_check_status_val != NULL){
        kAppStatusInfo.Statusword = callback_registry.get_check_status_val();
    }
    /* USER CODE END get_app_Statusword */
    return kAppStatusInfo.Statusword;
}

uint32_t set_app_Error_word(uint32_t val)
{
    /* USER CODE BEGIN set_app_Error_word 0 */
    /* USER CODE END set_app_Error_word 0 */
    kAppStatusInfo.Error_word = val;

    return APP_PARAM_SUCCESS;
}
uint32_t get_app_Error_word(void)
{
    /* USER CODE BEGIN get_app_Error_word */
    if (callback_registry.get_check_error_val != NULL){
        kAppStatusInfo.Error_word = callback_registry.get_check_error_val();
    }
    /* USER CODE END get_app_Error_word */
    return kAppStatusInfo.Error_word;
}

uint32_t set_app_DC_link_circuit_voltage(float val)
{
    /* USER CODE BEGIN set_app_DC_link_circuit_voltage 0 */
    /* USER CODE END set_app_DC_link_circuit_voltage 0 */
    kAppStatusInfo.DC_link_circuit_voltage = val;

    return APP_PARAM_SUCCESS;
}
float get_app_DC_link_circuit_voltage(void)
{
    /* USER CODE BEGIN get_app_DC_link_circuit_voltage */
    kAppStatusInfo.DC_link_circuit_voltage = axis->current_ctl_input.dc_bus_now_V;
    /* USER CODE END get_app_DC_link_circuit_voltage */
    return kAppStatusInfo.DC_link_circuit_voltage;
}

uint32_t set_app_Drive_accumulated_heat(float val)
{
    /* USER CODE BEGIN set_app_Drive_accumulated_heat 0 */
    /* USER CODE END set_app_Drive_accumulated_heat 0 */
    kAppStatusInfo.Drive_accumulated_heat = val;

    return APP_PARAM_SUCCESS;
}
float get_app_Drive_accumulated_heat(void)
{
    /* USER CODE BEGIN get_app_Drive_accumulated_heat */
    /* USER CODE END get_app_Drive_accumulated_heat */
    return kAppStatusInfo.Drive_accumulated_heat;
}

uint32_t set_app_Drive_temperature(float val)
{
    /* USER CODE BEGIN set_app_Drive_temperature 0 */
    /* USER CODE END set_app_Drive_temperature 0 */
    kAppStatusInfo.Drive_temperature = val;

    return APP_PARAM_SUCCESS;
}
float get_app_Drive_temperature(void)
{
    /* USER CODE BEGIN get_app_Drive_temperature */
    kAppStatusInfo.Drive_temperature = axis->current_ctl_input.driver_temp;
    /* USER CODE END get_app_Drive_temperature */
    return kAppStatusInfo.Drive_temperature;
}

uint32_t set_app_Alarm_word(uint32_t val)
{
    /* USER CODE BEGIN set_app_Alarm_word 0 */
    /* USER CODE END set_app_Alarm_word 0 */
    kAppStatusInfo.Alarm_word = val;

    return APP_PARAM_SUCCESS;
}
uint32_t get_app_Alarm_word(void)
{
    /* USER CODE BEGIN get_app_Alarm_word */
    if (callback_registry.get_check_warning_val != NULL){
        kAppStatusInfo.Alarm_word = callback_registry.get_check_warning_val();
    }
    /* USER CODE END get_app_Alarm_word */
    return kAppStatusInfo.Alarm_word;
}

uint32_t set_app_Modes_of_operation_display(int8_t val)
{
    /* USER CODE BEGIN set_app_Modes_of_operation_display 0 */
    /* USER CODE END set_app_Modes_of_operation_display 0 */
    kAppStatusInfo.Modes_of_operation_display = val;

    return APP_PARAM_SUCCESS;
}
int8_t get_app_Modes_of_operation_display(void)
{
    /* USER CODE BEGIN get_app_Modes_of_operation_display */
    kAppStatusInfo.Modes_of_operation_display = kAppOpMode.Modes_of_operation;
    /* USER CODE END get_app_Modes_of_operation_display */
    return kAppStatusInfo.Modes_of_operation_display;
}

uint32_t set_app_Version(uint32_t val)
{
    /* USER CODE BEGIN set_app_Version 0 */
    /* USER CODE END set_app_Version 0 */
    kAppStatusInfo.Version = val;

    return APP_PARAM_SUCCESS;
}
uint32_t get_app_Version(void)
{
    /* USER CODE BEGIN get_app_Version */
    kAppStatusInfo.Version = VERSION_ENCODE;
    /* USER CODE END get_app_Version */
    return kAppStatusInfo.Version;
}

uint32_t set_app_Motor_temperature(float val)
{
    /* USER CODE BEGIN set_app_Motor_temperature 0 */
    /* USER CODE END set_app_Motor_temperature 0 */
    kAppStatusInfo.Motor_temperature = val;

    return APP_PARAM_SUCCESS;
}
float get_app_Motor_temperature(void)
{
    /* USER CODE BEGIN get_app_Motor_temperature */
    /* USER CODE END get_app_Motor_temperature */
    return kAppStatusInfo.Motor_temperature;
}

uint32_t set_app_Motor_power(float val)
{
    /* USER CODE BEGIN set_app_Motor_power 0 */
    /* USER CODE END set_app_Motor_power 0 */
    kAppStatusInfo.Motor_power = val;

    return APP_PARAM_SUCCESS;
}
float get_app_Motor_power(void)
{
    /* USER CODE BEGIN get_app_Motor_power */
    kAppStatusInfo.Motor_power = axis->current_ctl_output.idq_now_A[1] *
                                 axis->pmsm_config.kt * axis->speed_obs_pll_output.ev_rad_s;
    /* USER CODE END get_app_Motor_power */
    return kAppStatusInfo.Motor_power;
}

uint32_t set_app_Mcu_temperature(float val)
{
    /* USER CODE BEGIN set_app_Mcu_temperature 0 */
    /* USER CODE END set_app_Mcu_temperature 0 */
    kAppStatusInfo.Mcu_temperature = val;

    return APP_PARAM_SUCCESS;
}
float get_app_Mcu_temperature(void)
{
    /* USER CODE BEGIN get_app_Mcu_temperature */
    /* USER CODE END get_app_Mcu_temperature */
    return kAppStatusInfo.Mcu_temperature;
}

uint32_t set_app_Digital_io_inputs_status(uint32_t val)
{
    /* USER CODE BEGIN set_app_Digital_io_inputs_status 0 */
    /* USER CODE END set_app_Digital_io_inputs_status 0 */
    kAppStatusInfo.Digital_io_inputs_status = val;

    return APP_PARAM_SUCCESS;
}
uint32_t get_app_Digital_io_inputs_status(void)
{
    /* USER CODE BEGIN get_app_Digital_io_inputs_status */
    if (callback_registry.get_check_di_io_val != NULL) {
        kAppStatusInfo.Digital_io_inputs_status = callback_registry.get_check_di_io_val();
    }
    /* USER CODE END get_app_Digital_io_inputs_status */
    return kAppStatusInfo.Digital_io_inputs_status;
}

uint32_t set_app_Brake_state(uint8_t val)
{
    /* USER CODE BEGIN set_app_Brake_state 0 */
    /* USER CODE END set_app_Brake_state 0 */
    kAppStatusInfo.Brake_state = val;

    return APP_PARAM_SUCCESS;
}
uint8_t get_app_Brake_state(void)
{
    /* USER CODE BEGIN get_app_Brake_state */
    /* USER CODE END get_app_Brake_state */
    return kAppStatusInfo.Brake_state;
}

uint32_t set_app_Modes_of_operation(int8_t val)
{
    /* USER CODE BEGIN set_app_Modes_of_operation 0 */
    if (val == get_app_Modes_of_operation_display())
    {
        return APP_PARAM_SUCCESS;
    }
    /* USER CODE END set_app_Modes_of_operation 0 */
    kAppOpMode.Modes_of_operation = val;
    /* USER CODE BEGIN set_app_Modes_of_operation 1 */
    if (callback_registry.set_app_callback == NULL)
    {
        return APP_PARAM_OUT_OF_RANGE;
    }
    switch (kAppOpMode.Modes_of_operation)
    {
    case MOTOR_CTL_SM_MODE_POSITION:
        axis->motor_ctl_sm_config.mode = MOTOR_CTL_SM_MODE_POSITION;
        callback_registry.set_app_callback(APP_PP_MODE);
        break;
    case MOTOR_CTL_SM_MODE_SPEED:
        axis->motor_ctl_sm_config.mode = MOTOR_CTL_SM_MODE_SPEED;
        callback_registry.set_app_callback(APP_PV_MODE);
        break;
    case MOTOR_CTL_SM_MODE_TORQUE:
        axis->motor_ctl_sm_config.mode = MOTOR_CTL_SM_MODE_TORQUE;
        callback_registry.set_app_callback(APP_PT_MODE);
        break;
    case MOTOR_CTL_SM_MODE_MIT:
        axis->motor_ctl_sm_config.mode = MOTOR_CTL_SM_MODE_MIT;
        callback_registry.set_app_callback(APP_MIT_MODE);
        break;
    case MOTOR_CTL_SM_MODE_HOMING: // 回零模式实际使用速度模式
        axis->motor_ctl_sm_config.mode = MOTOR_CTL_SM_MODE_SPEED;
        callback_registry.set_app_callback(APP_HM_MODE);
        break;
    case MOTOR_CTL_SM_MODE_CSP:
        axis->motor_ctl_sm_config.mode = MOTOR_CTL_SM_MODE_POSITION;
        callback_registry.set_app_callback(APP_CSP_MODE);
        break;
    case MOTOR_CTL_SM_MODE_CSV:
        axis->motor_ctl_sm_config.mode = MOTOR_CTL_SM_MODE_SPEED;
        callback_registry.set_app_callback(APP_CSV_MODE);
        break;
    case MOTOR_CTL_SM_MODE_CST:
        axis->motor_ctl_sm_config.mode = MOTOR_CTL_SM_MODE_TORQUE;
        callback_registry.set_app_callback(APP_CST_MODE);
        break;
    case MOTOR_CTL_SM_MODE_DIRECTION_IDENTIFICATION:
        axis->motor_ctl_sm_config.mode = MOTOR_CTL_SM_MODE_DIRECTION_IDENTIFICATION;
        callback_registry.set_app_callback(APP_DIR_ID_MODE);
        break;
    case MOTOR_CTL_SM_MODE_ELECTRIC_ANGLE_IDENTIFICATION:
        axis->motor_ctl_sm_config.mode = MOTOR_CTL_SM_MODE_ELECTRIC_ANGLE_IDENTIFICATION;
        callback_registry.set_app_callback(APP_ELEC_ANGLE_ID_MODE);
        break;
    case MOTOR_CTL_SM_MODE_ELECTRIC_IDENTIFICATION:
        axis->motor_ctl_sm_config.mode = MOTOR_CTL_SM_MODE_ELECTRIC_IDENTIFICATION;
        callback_registry.set_app_callback(APP_ELEC_ID_MODE);
        break;
    case MOTOR_CTL_SM_MODE_MECHANICAL_IDENTIFICATION:
        axis->motor_ctl_sm_config.mode = MOTOR_CTL_SM_MODE_MECHANICAL_IDENTIFICATION;
        callback_registry.set_app_callback(APP_MEC_ID_MODE);
        break;
    case MOTOR_CTL_SM_MODE_POLE_PAIRS_IDENTIFICATION:
        axis->motor_ctl_sm_config.mode = MOTOR_CTL_SM_MODE_POLE_PAIRS_IDENTIFICATION;
        callback_registry.set_app_callback(APP_POLE_PAIRS_ID_MODE);
        break;
    case MOTOR_CTL_SM_MODE_TQ_FRICTION_IDENTIFICATION:
        axis->motor_ctl_sm_config.mode = MOTOR_CTL_SM_MODE_TQ_FRICTION_IDENTIFICATION;
        callback_registry.set_app_callback(APP_TQ_FC_ID_MODE);
        break;
    default:
        axis->motor_ctl_sm_config.mode = MOTOR_CTL_SM_MODE_IDLE;
        break;
    }
    /* USER CODE END set_app_Modes_of_operation 1 */
    return APP_PARAM_SUCCESS;
}
int8_t get_app_Modes_of_operation(void)
{
    /* USER CODE BEGIN get_app_Modes_of_operation */
    /* USER CODE END get_app_Modes_of_operation */
    return kAppOpMode.Modes_of_operation;
}

uint32_t set_app_Load_encoder_resolution(uint32_t val)
{
    /* USER CODE BEGIN set_app_Load_encoder_resolution 0 */
    if (axis->motor_ctl_sm_output.state == MOTOR_CTL_SM_MOTOR_ENABLE)
    {
        return APP_PARAM_WRITE_STATE_ERROR;
    }
    /* USER CODE END set_app_Load_encoder_resolution 0 */
    kAppEncoderConfig.Load_encoder_resolution = val;
    /* USER CODE BEGIN set_app_Load_encoder_resolution 1 */
    uint32_t load_res_real = get_app_Load_control_resolution();
    if (load_res_real == 0)
    {
        load_res_real = kAppEncoderConfig.Load_encoder_resolution;
    }
    bsp_set_encoder_config(ENCODER_ID_LOAD, 0, get_app_Load_encoder_options(), \
                           val, load_res_real, PMSM_LOAD_ENC_MULTI_LINE_P_N, 0, 0, 0);
    /* USER CODE END set_app_Load_encoder_resolution 1 */
    return APP_PARAM_SUCCESS;
}
uint32_t get_app_Load_encoder_resolution(void)
{
    /* USER CODE BEGIN get_app_Load_encoder_resolution */
    /* USER CODE END get_app_Load_encoder_resolution */
    return kAppEncoderConfig.Load_encoder_resolution;
}

uint32_t set_app_Motor_encoder_resolution(uint32_t val)
{
    /* USER CODE BEGIN set_app_Motor_encoder_resolution 0 */
    if (axis->motor_ctl_sm_output.state == MOTOR_CTL_SM_MOTOR_ENABLE)
    {
        return APP_PARAM_WRITE_STATE_ERROR;
    }
    if (val == 0)
    {
        return APP_PARAM_OUT_OF_RANGE;
    }
    /* USER CODE END set_app_Motor_encoder_resolution 0 */
    kAppEncoderConfig.Motor_encoder_resolution = val;
    /* USER CODE BEGIN set_app_Motor_encoder_resolution 1 */
    uint32_t motor_res_real = get_app_Motor_control_resolution();
    if (motor_res_real == 0)
    {
        motor_res_real = kAppEncoderConfig.Motor_encoder_resolution;
    }
    bsp_set_encoder_config(ENCODER_ID_MOTOR, 0, get_app_Motor_encoder_options(), \
                           val, motor_res_real, PMSM_MOTOR_ENC_MULTI_LINE_P_N, 0, 0, 0);
    /* USER CODE END set_app_Motor_encoder_resolution 1 */
    return APP_PARAM_SUCCESS;
}
uint32_t get_app_Motor_encoder_resolution(void)
{
    /* USER CODE BEGIN get_app_Motor_encoder_resolution */
    /* USER CODE END get_app_Motor_encoder_resolution */
    return kAppEncoderConfig.Motor_encoder_resolution;
}

uint32_t set_app_Motor_encoder_type(uint8_t val)
{
    /* USER CODE BEGIN set_app_Motor_encoder_type 0 */
    /* USER CODE END set_app_Motor_encoder_type 0 */
    kAppEncoderConfig.Motor_encoder_type = val;
    /* USER CODE BEGIN set_app_Motor_encoder_type 1 */
    /* USER CODE END set_app_Motor_encoder_type 1 */
    return APP_PARAM_SUCCESS;
}
uint8_t get_app_Motor_encoder_type(void)
{
    /* USER CODE BEGIN get_app_Motor_encoder_type */
    /* USER CODE END get_app_Motor_encoder_type */
    return kAppEncoderConfig.Motor_encoder_type;
}

uint32_t set_app_Load_encoder_type(uint8_t val)
{
    /* USER CODE BEGIN set_app_Load_encoder_type 0 */
    /* USER CODE END set_app_Load_encoder_type 0 */
    kAppEncoderConfig.Load_encoder_type = val;
    /* USER CODE BEGIN set_app_Load_encoder_type 1 */
    /* USER CODE END set_app_Load_encoder_type 1 */
    return APP_PARAM_SUCCESS;
}
uint8_t get_app_Load_encoder_type(void)
{
    /* USER CODE BEGIN get_app_Load_encoder_type */
    /* USER CODE END get_app_Load_encoder_type */
    return kAppEncoderConfig.Load_encoder_type;
}

uint32_t set_app_Motor_encoder_options(uint8_t val)
{
    if (val < 0)
        return APP_PARAM_OUT_OF_RANGE;
    /* USER CODE BEGIN set_app_Motor_encoder_options 0 */
    if (axis->motor_ctl_sm_output.state == MOTOR_CTL_SM_MOTOR_ENABLE)
    {
        return APP_PARAM_WRITE_STATE_ERROR;
    }
    /* USER CODE END set_app_Motor_encoder_options 0 */
    kAppEncoderConfig.Motor_encoder_options = val;
    /* USER CODE BEGIN set_app_Motor_encoder_options 1 */
    uint32_t motor_res = get_app_Motor_encoder_resolution();
    uint32_t motor_res_real = get_app_Motor_control_resolution();
    if (motor_res_real == 0)
    {
        motor_res_real = motor_res;
    }
    bsp_set_encoder_config(ENCODER_ID_MOTOR, 0, val, \
                           motor_res, motor_res_real, \
                           PMSM_MOTOR_ENC_MULTI_LINE_P_N, 0, 0, 0);
    MotorCtlParamSetUpdata(axis);
    /* USER CODE END set_app_Motor_encoder_options 1 */
    return APP_PARAM_SUCCESS;
}
uint8_t get_app_Motor_encoder_options(void)
{
    /* USER CODE BEGIN get_app_Motor_encoder_options */
    /* USER CODE END get_app_Motor_encoder_options */
    return kAppEncoderConfig.Motor_encoder_options;
}

uint32_t set_app_Load_pps_2_rpm(float val)
{
    /* USER CODE BEGIN set_app_Load_pps_2_rpm 0 */
    /* USER CODE END set_app_Load_pps_2_rpm 0 */
    kAppEncoderConfig.Load_pps_2_rpm = val;

    return APP_PARAM_SUCCESS;
}
float get_app_Load_pps_2_rpm(void)
{
    /* USER CODE BEGIN get_app_Load_pps_2_rpm */
    /* USER CODE END get_app_Load_pps_2_rpm */
    return kAppEncoderConfig.Load_pps_2_rpm;
}

uint32_t set_app_Load_rpm_2_pps(float val)
{
    /* USER CODE BEGIN set_app_Load_rpm_2_pps 0 */
    /* USER CODE END set_app_Load_rpm_2_pps 0 */
    kAppEncoderConfig.Load_rpm_2_pps = val;

    return APP_PARAM_SUCCESS;
}
float get_app_Load_rpm_2_pps(void)
{
    /* USER CODE BEGIN get_app_Load_rpm_2_pps */
    /* USER CODE END get_app_Load_rpm_2_pps */
    return kAppEncoderConfig.Load_rpm_2_pps;
}

uint32_t set_app_Motor_pps_2_rpm(float val)
{
    /* USER CODE BEGIN set_app_Motor_pps_2_rpm 0 */
    /* USER CODE END set_app_Motor_pps_2_rpm 0 */
    kAppEncoderConfig.Motor_pps_2_rpm = val;

    return APP_PARAM_SUCCESS;
}
float get_app_Motor_pps_2_rpm(void)
{
    /* USER CODE BEGIN get_app_Motor_pps_2_rpm */
    /* USER CODE END get_app_Motor_pps_2_rpm */
    return kAppEncoderConfig.Motor_pps_2_rpm;
}

uint32_t set_app_Motor_rpm_2_pps(float val)
{
    /* USER CODE BEGIN set_app_Motor_rpm_2_pps 0 */
    /* USER CODE END set_app_Motor_rpm_2_pps 0 */
    kAppEncoderConfig.Motor_rpm_2_pps = val;

    return APP_PARAM_SUCCESS;
}
float get_app_Motor_rpm_2_pps(void)
{
    /* USER CODE BEGIN get_app_Motor_rpm_2_pps */
    /* USER CODE END get_app_Motor_rpm_2_pps */
    return kAppEncoderConfig.Motor_rpm_2_pps;
}

uint32_t set_app_P_load_2_motor(float val)
{
    /* USER CODE BEGIN set_app_P_load_2_motor 0 */
    /* USER CODE END set_app_P_load_2_motor 0 */
    kAppEncoderConfig.P_load_2_motor = val;

    return APP_PARAM_SUCCESS;
}
float get_app_P_load_2_motor(void)
{
    /* USER CODE BEGIN get_app_P_load_2_motor */
    /* USER CODE END get_app_P_load_2_motor */
    return kAppEncoderConfig.P_load_2_motor;
}

uint32_t set_app_P_motor_2_load(float val)
{
    /* USER CODE BEGIN set_app_P_motor_2_load 0 */
    /* USER CODE END set_app_P_motor_2_load 0 */
    kAppEncoderConfig.P_motor_2_load = val;

    return APP_PARAM_SUCCESS;
}
float get_app_P_motor_2_load(void)
{
    /* USER CODE BEGIN get_app_P_motor_2_load */
    /* USER CODE END get_app_P_motor_2_load */
    return kAppEncoderConfig.P_motor_2_load;
}

uint32_t set_app_Load_control_resolution(uint32_t val)
{
    /* USER CODE BEGIN set_app_Load_control_resolution 0 */
    if (axis->motor_ctl_sm_output.state == MOTOR_CTL_SM_MOTOR_ENABLE)
    {
        return APP_PARAM_WRITE_STATE_ERROR;
    }

    uint32_t motor_control_resolution = get_app_Motor_control_resolution();
    uint32_t load_encoder_resolution = get_app_Load_encoder_resolution();
    if (val > load_encoder_resolution || \
       (val != 0 && load_encoder_resolution % val != 0))
    {
        return APP_PARAM_OUT_OF_RANGE;
    }
    /* USER CODE END set_app_Load_control_resolution 0 */
    kAppEncoderConfig.Load_control_resolution = val;
    /* USER CODE BEGIN set_app_Load_control_resolution 1 */
    // 单位转化因子计算
    if (val > 0)
    {
        kAppEncoderConfig.Load_pps_2_rpm = 60.0f / (float)val;
        kAppEncoderConfig.Load_rpm_2_pps = (float)val / 60.0f;

        kAppEncoderConfig.P_load_2_motor = (float)motor_control_resolution / (float)val;
        if (motor_control_resolution != 0)
        {
            kAppEncoderConfig.P_motor_2_load = (float)val / (float)motor_control_resolution;
        }
        else
        {
            kAppEncoderConfig.P_motor_2_load = 1.0f;
        }
    }
    bsp_set_encoder_config(ENCODER_ID_LOAD, 0, get_app_Load_encoder_options(), \
                           load_encoder_resolution, val, \
                           PMSM_LOAD_ENC_MULTI_LINE_P_N, 0, 0, 0);
    // 关联控制层设置
    axis->load_pos_sensor_config.enc_line_p_n = val;
    // 失能状态下调用，设置此参数时状态先由上位机限制
    MotorCtlParamSetUpdata(axis);
    /* USER CODE END set_app_Load_control_resolution 1 */
    return APP_PARAM_SUCCESS;
}
uint32_t get_app_Load_control_resolution(void)
{
    /* USER CODE BEGIN get_app_Load_control_resolution */
    /* USER CODE END get_app_Load_control_resolution */
    return kAppEncoderConfig.Load_control_resolution;
}

uint32_t set_app_Motor_control_resolution(uint32_t val)
{
    /* USER CODE BEGIN set_app_Motor_control_resolution 0 */
    if (axis->motor_ctl_sm_output.state == MOTOR_CTL_SM_MOTOR_ENABLE)
    {
        return APP_PARAM_WRITE_STATE_ERROR;
    }

    uint32_t motor_encoder_resolution = get_app_Motor_encoder_resolution();
    uint32_t load_control_resolution = get_app_Load_control_resolution();
    if (val == 0 || val > motor_encoder_resolution || \
        (motor_encoder_resolution % val != 0))
    {
        return APP_PARAM_OUT_OF_RANGE;
    }
    /* USER CODE END set_app_Motor_control_resolution 0 */
    kAppEncoderConfig.Motor_control_resolution = val;
    /* USER CODE BEGIN set_app_Motor_control_resolution 1 */
    // 单位转化因子计算
    if (val > 0)
    {
        kAppEncoderConfig.Motor_pps_2_rpm = 60.0f / (float)val;
        kAppEncoderConfig.Motor_rpm_2_pps = (float)val / 60.0f;

        if (load_control_resolution != 0)
        {
            kAppEncoderConfig.P_load_2_motor = (float)val / (float)load_control_resolution;
        }
        else
        {
            kAppEncoderConfig.P_load_2_motor = 1.0f;
        }
        kAppEncoderConfig.P_motor_2_load = (float)load_control_resolution / (float)val;
    }
    bsp_set_encoder_config(ENCODER_ID_MOTOR, 0, get_app_Motor_encoder_options(), \
                           motor_encoder_resolution, val, \
                           PMSM_MOTOR_ENC_MULTI_LINE_P_N, 0, 0, 0);
    // 关联控制层设置
    axis->pmsm_config.enc_line_p_n = val;
    // 失能状态下调用，设置此参数时状态先由上位机限制
    MotorCtlParamSetUpdata(axis);
    /* USER CODE END set_app_Motor_control_resolution 1 */
    return APP_PARAM_SUCCESS;
}
uint32_t get_app_Motor_control_resolution(void)
{
    /* USER CODE BEGIN get_app_Motor_control_resolution */
    /* USER CODE END get_app_Motor_control_resolution */
    return kAppEncoderConfig.Motor_control_resolution;
}

uint32_t set_app_Load_encoder_options(uint8_t val)
{
    if (val < 0)
        return APP_PARAM_OUT_OF_RANGE;
    /* USER CODE BEGIN set_app_Load_encoder_options 0 */
    if (axis->motor_ctl_sm_output.state == MOTOR_CTL_SM_MOTOR_ENABLE)
    {
        return APP_PARAM_WRITE_STATE_ERROR;
    }
    /* USER CODE END set_app_Load_encoder_options 0 */
    kAppEncoderConfig.Load_encoder_options = val;
    /* USER CODE BEGIN set_app_Load_encoder_options 1 */
    uint32_t load_res = get_app_Load_encoder_resolution();
    uint32_t load_res_real = get_app_Load_control_resolution();
    if (load_res_real == 0)
    {
        load_res_real = load_res;
    }
    bsp_set_encoder_config(ENCODER_ID_LOAD, 0, val, \
                           load_res, load_res_real, \
                           PMSM_LOAD_ENC_MULTI_LINE_P_N, 0, 0, 0);
    MotorCtlParamSetUpdata(axis);
    /* USER CODE END set_app_Load_encoder_options 1 */
    return APP_PARAM_SUCCESS;
}
uint8_t get_app_Load_encoder_options(void)
{
    /* USER CODE BEGIN get_app_Load_encoder_options */
    /* USER CODE END get_app_Load_encoder_options */
    return kAppEncoderConfig.Load_encoder_options;
}

uint32_t set_app_Polarity(uint8_t val)
{
    if (val < 0)
        return APP_PARAM_OUT_OF_RANGE;
    if (val > 1)
        return APP_PARAM_OUT_OF_RANGE;

    /* USER CODE BEGIN set_app_Polarity 0 */
    /* USER CODE END set_app_Polarity 0 */
    kAppBaseConfig.Polarity = val;
    /* USER CODE BEGIN set_app_Polarity 1 */
    if (val > 0) // 如果用户设置极性，则所有运动极性全部取反
    {
        SetPosPolarity(-1);
        SetVelPolarity(-1);
        SetTqPolarity(-1);
    }
    else
    {
        SetPosPolarity(1);
        SetVelPolarity(1);
        SetTqPolarity(1);
    }

    /* USER CODE END set_app_Polarity 1 */
    return APP_PARAM_SUCCESS;
}
uint8_t get_app_Polarity(void)
{
    /* USER CODE BEGIN get_app_Polarity */
    /* USER CODE END get_app_Polarity */
    return kAppBaseConfig.Polarity;
}

uint32_t set_app_Home_position_offset_value(int64_t val)
{
    /* USER CODE BEGIN set_app_Home_position_offset_value 0 */
    // 只能内部写入，外部可以考虑
    kAppBaseConfig.Home_position_offset_value = val;
    /* USER CODE END set_app_Home_position_offset_value 0 */
    kAppBaseConfig.Home_position_offset_value = val;

    return APP_PARAM_SUCCESS;
}
int64_t get_app_Home_position_offset_value(void)
{
    /* USER CODE BEGIN get_app_Home_position_offset_value */
    /* USER CODE END get_app_Home_position_offset_value */
    return kAppBaseConfig.Home_position_offset_value;
}

uint32_t set_app_Can_id(uint32_t val)
{
    /* USER CODE BEGIN set_app_Can_id 0 */
    /* USER CODE END set_app_Can_id 0 */
    kAppBaseConfig.Can_id = val;
    /* USER CODE BEGIN set_app_Can_id 1 */
    bsp_set_can_id(val);
    get_app_Comp_id(); // 从底层更新组件ID到数据库
    /* USER CODE END set_app_Can_id 1 */
    return APP_PARAM_SUCCESS;
}
uint32_t get_app_Can_id(void)
{
    /* USER CODE BEGIN get_app_Can_id */
    kAppBaseConfig.Can_id = bsp_get_can_id();
    /* USER CODE END get_app_Can_id */
    return kAppBaseConfig.Can_id;
}

uint32_t set_app_Can_baudrate(uint32_t val)
{
    /* USER CODE BEGIN set_app_Can_baudrate 0 */
    /* USER CODE END set_app_Can_baudrate 0 */
    kAppBaseConfig.Can_baudrate = val;
    /* USER CODE BEGIN set_app_Can_baudrate 1 */
    bsp_set_can_baudrate(val);
    /* USER CODE END set_app_Can_baudrate 1 */
    return APP_PARAM_SUCCESS;
}
uint32_t get_app_Can_baudrate(void)
{
    /* USER CODE BEGIN get_app_Can_baudrate */
    kAppBaseConfig.Can_baudrate = bsp_get_can_baudrate();
    /* USER CODE END get_app_Can_baudrate */
    return kAppBaseConfig.Can_baudrate;
}

uint32_t set_app_Quick_stop_option_code(int16_t val)
{
    if (val < 0)
        return APP_PARAM_OUT_OF_RANGE;
    if (val > 7)
        return APP_PARAM_OUT_OF_RANGE;

    /* USER CODE BEGIN set_app_Quick_stop_option_code 0 */
    /* USER CODE END set_app_Quick_stop_option_code 0 */
    kAppBaseConfig.Quick_stop_option_code = val;
    /* USER CODE BEGIN set_app_Quick_stop_option_code 1 */
    /* USER CODE END set_app_Quick_stop_option_code 1 */
    return APP_PARAM_SUCCESS;
}
int16_t get_app_Quick_stop_option_code(void)
{
    /* USER CODE BEGIN get_app_Quick_stop_option_code */
    /* USER CODE END get_app_Quick_stop_option_code */
    return kAppBaseConfig.Quick_stop_option_code;
}

uint32_t set_app_Brake_engage_time(float val)
{
    if (val < 0.0)
        return APP_PARAM_OUT_OF_RANGE;
    /* USER CODE BEGIN set_app_Brake_engage_time 0 */
    /* USER CODE END set_app_Brake_engage_time 0 */
    kAppBaseConfig.Brake_engage_time = val;
    /* USER CODE BEGIN set_app_Brake_engage_time 1 */
    /* USER CODE END set_app_Brake_engage_time 1 */
    return APP_PARAM_SUCCESS;
}
float get_app_Brake_engage_time(void)
{
    /* USER CODE BEGIN get_app_Brake_engage_time */
    /* USER CODE END get_app_Brake_engage_time */
    return kAppBaseConfig.Brake_engage_time;
}

uint32_t set_app_Brake_release_time(float val)
{
    if (val < 0.0)
        return APP_PARAM_OUT_OF_RANGE;
    /* USER CODE BEGIN set_app_Brake_release_time 0 */
    /* USER CODE END set_app_Brake_release_time 0 */
    kAppBaseConfig.Brake_release_time = val;
    /* USER CODE BEGIN set_app_Brake_release_time 1 */
    /* USER CODE END set_app_Brake_release_time 1 */
    return APP_PARAM_SUCCESS;
}
float get_app_Brake_release_time(void)
{
    /* USER CODE BEGIN get_app_Brake_release_time */
    /* USER CODE END get_app_Brake_release_time */
    return kAppBaseConfig.Brake_release_time;
}

uint32_t set_app_Dynamic_brake_speed_threshold(float val)
{
    if (val < 0.0)
        return APP_PARAM_OUT_OF_RANGE;
    /* USER CODE BEGIN set_app_Dynamic_brake_speed_threshold 0 */
    /* USER CODE END set_app_Dynamic_brake_speed_threshold 0 */
    kAppBaseConfig.Dynamic_brake_speed_threshold = val;
    /* USER CODE BEGIN set_app_Dynamic_brake_speed_threshold 1 */
    /* USER CODE END set_app_Dynamic_brake_speed_threshold 1 */
    return APP_PARAM_SUCCESS;
}
float get_app_Dynamic_brake_speed_threshold(void)
{
    /* USER CODE BEGIN get_app_Dynamic_brake_speed_threshold */
    /* USER CODE END get_app_Dynamic_brake_speed_threshold */
    return kAppBaseConfig.Dynamic_brake_speed_threshold;
}

uint32_t set_app_Brake_release_hold_voltage(float val)
{
    if (val < 0.0)
        return APP_PARAM_OUT_OF_RANGE;
    /* USER CODE BEGIN set_app_Brake_release_hold_voltage 0 */
    if (val > kAppBaseConfig.Brake_rated_voltage)
        return APP_PARAM_OUT_OF_RANGE;
    if (axis->motor_ctl_sm_output.state == MOTOR_CTL_SM_MOTOR_ENABLE)
    {
        return APP_PARAM_WRITE_STATE_ERROR;
    }
    /* USER CODE END set_app_Brake_release_hold_voltage 0 */
    kAppBaseConfig.Brake_release_hold_voltage = val;
    /* USER CODE BEGIN set_app_Brake_release_hold_voltage 1 */
    /* USER CODE END set_app_Brake_release_hold_voltage 1 */
    return APP_PARAM_SUCCESS;
}
float get_app_Brake_release_hold_voltage(void)
{
    /* USER CODE BEGIN get_app_Brake_release_hold_voltage */
    /* USER CODE END get_app_Brake_release_hold_voltage */
    return kAppBaseConfig.Brake_release_hold_voltage;
}

uint32_t set_app_Digital_io_outputs_phys(uint32_t val)
{
    /* USER CODE BEGIN set_app_Digital_io_outputs_phys 0 */
    /* USER CODE END set_app_Digital_io_outputs_phys 0 */
    kAppBaseConfig.Digital_io_outputs_phys = val;
    /* USER CODE BEGIN set_app_Digital_io_outputs_phys 1 */
    uint32_t do_ctrl = get_app_Digital_io_outputs_phys() & get_app_Digital_io_outputs_mask();

    // 按位设置bsp层实际DO输出有效状态
    for (DIGITAL_OUTPUTS_IO_BIT do_num = DO_IO_MIN; do_num <= DO_IO_MAX; do_num++)
    {
        bsp_set_digital_output_state(do_num, (do_ctrl >> do_num) & 0x1);
    }
    /* USER CODE END set_app_Digital_io_outputs_phys 1 */
    return APP_PARAM_SUCCESS;
}
uint32_t get_app_Digital_io_outputs_phys(void)
{
    /* USER CODE BEGIN get_app_Digital_io_outputs_phys */
    // 抱闸由内部自动控制，更新DO_IO_SET_BRAKE位状态
    APP_BRAKE_CONTROL_MODE mode = get_app_Brake_control_mode();
    if (mode == BRAKE_CONTROL_MODE_IO_AUTO || mode == BRAKE_CONTROL_MODE_PWM_AUTO)
    {
        bool brake_io_phys = (APP_BRAKE_STATE)get_app_Brake_state() == BRAKE_STATE_RELEASED ? \
                             true : false;
        uint32_t val = kAppBaseConfig.Digital_io_outputs_phys;
        uint32_t brake_bit_mask = (uint32_t)1 << DO_IO_SET_BRAKE;
        // 使用brake_io_phys的值设置DO_IO_SET_BRAKE位，其他位保持不变
        val = (val & ~brake_bit_mask) | (brake_io_phys ? brake_bit_mask : 0);
        kAppBaseConfig.Digital_io_outputs_phys = val;
    }
    /* USER CODE END get_app_Digital_io_outputs_phys */
    return kAppBaseConfig.Digital_io_outputs_phys;
}

uint32_t set_app_Digital_io_outputs_mask(uint32_t val)
{
    /* USER CODE BEGIN set_app_Digital_io_outputs_mask 0 */
    /* USER CODE END set_app_Digital_io_outputs_mask 0 */
    kAppBaseConfig.Digital_io_outputs_mask = val;
    /* USER CODE BEGIN set_app_Digital_io_outputs_mask 1 */
    uint32_t do_ctrl = get_app_Digital_io_outputs_phys() & get_app_Digital_io_outputs_mask();

    // 按位设置bsp层实际DO输出有效状态
    for (DIGITAL_OUTPUTS_IO_BIT do_num = DO_IO_MIN; do_num <= DO_IO_MAX; do_num++)
    {
        bsp_set_digital_output_state(do_num, (do_ctrl >> do_num) & 0x1);
    }
    /* USER CODE END set_app_Digital_io_outputs_mask 1 */
    return APP_PARAM_SUCCESS;
}
uint32_t get_app_Digital_io_outputs_mask(void)
{
    /* USER CODE BEGIN get_app_Digital_io_outputs_mask */
    // 抱闸由内部自动控制，更新DO_IO_SET_BRAKE位状态
    APP_BRAKE_CONTROL_MODE mode = get_app_Brake_control_mode();
    if (mode == BRAKE_CONTROL_MODE_IO_AUTO || mode == BRAKE_CONTROL_MODE_PWM_AUTO)
    {
        uint32_t val = kAppBaseConfig.Digital_io_outputs_mask;
        uint32_t brake_bit_mask = (uint32_t)1 << DO_IO_SET_BRAKE;
        // 使用brake_io_mask的值设置DO_IO_SET_BRAKE位为1，其他位保持不变
        val = val | brake_bit_mask;
        kAppBaseConfig.Digital_io_outputs_mask = val;
    }
    /* USER CODE END get_app_Digital_io_outputs_mask */
    return kAppBaseConfig.Digital_io_outputs_mask;
}

uint32_t set_app_Brake_control_mode(uint8_t val)
{
    if (val < 0)
        return APP_PARAM_OUT_OF_RANGE;
    if (val > 3)
        return APP_PARAM_OUT_OF_RANGE;

    /* USER CODE BEGIN set_app_Brake_control_mode 0 */
    if (axis->motor_ctl_sm_output.state == MOTOR_CTL_SM_MOTOR_ENABLE)
    {
        return APP_PARAM_WRITE_STATE_ERROR;
    }
    /* USER CODE END set_app_Brake_control_mode 0 */
    kAppBaseConfig.Brake_control_mode = val;
    /* USER CODE BEGIN set_app_Brake_control_mode 1 */
    /* USER CODE END set_app_Brake_control_mode 1 */
    return APP_PARAM_SUCCESS;
}
uint8_t get_app_Brake_control_mode(void)
{
    /* USER CODE BEGIN get_app_Brake_control_mode */
    /* USER CODE END get_app_Brake_control_mode */
    return kAppBaseConfig.Brake_control_mode;
}

uint32_t set_app_Brake_rated_voltage(float val)
{
    if (val < 0.0)
        return APP_PARAM_OUT_OF_RANGE;
    /* USER CODE BEGIN set_app_Brake_rated_voltage 0 */
    if (axis->motor_ctl_sm_output.state == MOTOR_CTL_SM_MOTOR_ENABLE)
    {
        return APP_PARAM_WRITE_STATE_ERROR;
    }
    /* USER CODE END set_app_Brake_rated_voltage 0 */
    kAppBaseConfig.Brake_rated_voltage = val;
    /* USER CODE BEGIN set_app_Brake_rated_voltage 1 */
    /* USER CODE END set_app_Brake_rated_voltage 1 */
    return APP_PARAM_SUCCESS;
}
float get_app_Brake_rated_voltage(void)
{
    /* USER CODE BEGIN get_app_Brake_rated_voltage */
    /* USER CODE END get_app_Brake_rated_voltage */
    return kAppBaseConfig.Brake_rated_voltage;
}

uint32_t set_app_Brake_release_action_voltage(float val)
{
    if (val < 0.0)
        return APP_PARAM_OUT_OF_RANGE;
    /* USER CODE BEGIN set_app_Brake_release_action_voltage 0 */
    if (val > kAppBaseConfig.Brake_rated_voltage)
        return APP_PARAM_OUT_OF_RANGE;
    if (axis->motor_ctl_sm_output.state == MOTOR_CTL_SM_MOTOR_ENABLE)
    {
        return APP_PARAM_WRITE_STATE_ERROR;
    }
    /* USER CODE END set_app_Brake_release_action_voltage 0 */
    kAppBaseConfig.Brake_release_action_voltage = val;
    /* USER CODE BEGIN set_app_Brake_release_action_voltage 1 */
    /* USER CODE END set_app_Brake_release_action_voltage 1 */
    return APP_PARAM_SUCCESS;
}
float get_app_Brake_release_action_voltage(void)
{
    /* USER CODE BEGIN get_app_Brake_release_action_voltage */
    /* USER CODE END get_app_Brake_release_action_voltage */
    return kAppBaseConfig.Brake_release_action_voltage;
}

uint32_t set_app_Brake_release_pwm_freq(uint16_t val)
{
    if (val < 1)
        return APP_PARAM_OUT_OF_RANGE;
    /* USER CODE BEGIN set_app_Brake_release_pwm_freq 0 */
    if (axis->motor_ctl_sm_output.state == MOTOR_CTL_SM_MOTOR_ENABLE)
    {
        return APP_PARAM_WRITE_STATE_ERROR;
    }
    /* USER CODE END set_app_Brake_release_pwm_freq 0 */
    kAppBaseConfig.Brake_release_pwm_freq = val;
    /* USER CODE BEGIN set_app_Brake_release_pwm_freq 1 */
    /* USER CODE END set_app_Brake_release_pwm_freq 1 */
    return APP_PARAM_SUCCESS;
}
uint16_t get_app_Brake_release_pwm_freq(void)
{
    /* USER CODE BEGIN get_app_Brake_release_pwm_freq */
    /* USER CODE END get_app_Brake_release_pwm_freq */
    return kAppBaseConfig.Brake_release_pwm_freq;
}

uint32_t set_app_Brake_engage_delay_time(float val)
{
    if (val < 0.0)
        return APP_PARAM_OUT_OF_RANGE;
    /* USER CODE BEGIN set_app_Brake_engage_delay_time 0 */
    /* USER CODE END set_app_Brake_engage_delay_time 0 */
    kAppBaseConfig.Brake_engage_delay_time = val;
    /* USER CODE BEGIN set_app_Brake_engage_delay_time 1 */
    /* USER CODE END set_app_Brake_engage_delay_time 1 */
    return APP_PARAM_SUCCESS;
}
float get_app_Brake_engage_delay_time(void)
{
    /* USER CODE BEGIN get_app_Brake_engage_delay_time */
    /* USER CODE END get_app_Brake_engage_delay_time */
    return kAppBaseConfig.Brake_engage_delay_time;
}

uint32_t set_app_Brake_release_delay_time(float val)
{
    if (val < 0.0)
        return APP_PARAM_OUT_OF_RANGE;
    /* USER CODE BEGIN set_app_Brake_release_delay_time 0 */
    /* USER CODE END set_app_Brake_release_delay_time 0 */
    kAppBaseConfig.Brake_release_delay_time = val;
    /* USER CODE BEGIN set_app_Brake_release_delay_time 1 */
    /* USER CODE END set_app_Brake_release_delay_time 1 */
    return APP_PARAM_SUCCESS;
}
float get_app_Brake_release_delay_time(void)
{
    /* USER CODE BEGIN get_app_Brake_release_delay_time */
    /* USER CODE END get_app_Brake_release_delay_time */
    return kAppBaseConfig.Brake_release_delay_time;
}

uint32_t set_app_Target_position(int64_t val)
{
    /* USER CODE BEGIN set_app_Target_position 0 */
    if (val < kAppRestrictParam.Software_position_limit_Minimal_position_limit ||
        val > kAppRestrictParam.Software_position_limit_Maximal_position_limit)
    {
        return APP_PARAM_OUT_OF_RANGE;
    }

    /* USER CODE END set_app_Target_position 0 */
    kAppMotionParam.Target_position = val;
    /* USER CODE BEGIN set_app_Target_position 1 */
    /* USER CODE END set_app_Target_position 1 */
    return APP_PARAM_SUCCESS;
}
int64_t get_app_Target_position(void)
{
    /* USER CODE BEGIN get_app_Target_position */
    /* USER CODE END get_app_Target_position */
    return kAppMotionParam.Target_position;
}

uint32_t set_app_Profile_velocity(float val)
{
    if (val < 0.0)
        return APP_PARAM_OUT_OF_RANGE;
    /* USER CODE BEGIN set_app_Profile_velocity 0 */
    if (MATH_ABS(val) > kAppRestrictParam.Max_profile_velocity)
    {
        return APP_PARAM_OUT_OF_RANGE;
    }

    /* USER CODE END set_app_Profile_velocity 0 */
    kAppMotionParam.Profile_velocity = val;
    /* USER CODE BEGIN set_app_Profile_velocity 1 */
    /* USER CODE END set_app_Profile_velocity 1 */
    return APP_PARAM_SUCCESS;
}
float get_app_Profile_velocity(void)
{
    /* USER CODE BEGIN get_app_Profile_velocity */
    /* USER CODE END get_app_Profile_velocity */
    return kAppMotionParam.Profile_velocity;
}

uint32_t set_app_Profile_acceleration(float val)
{
    if (val < 0.0)
        return APP_PARAM_OUT_OF_RANGE;
    /* USER CODE BEGIN set_app_Profile_acceleration 0 */

    if (val > kAppRestrictParam.Max_acceleration)
    {
        return APP_PARAM_OUT_OF_RANGE;
    }

    /* USER CODE END set_app_Profile_acceleration 0 */
    kAppMotionParam.Profile_acceleration = val;
    /* USER CODE BEGIN set_app_Profile_acceleration 1 */
    /* USER CODE END set_app_Profile_acceleration 1 */
    return APP_PARAM_SUCCESS;
}
float get_app_Profile_acceleration(void)
{
    /* USER CODE BEGIN get_app_Profile_acceleration */
    /* USER CODE END get_app_Profile_acceleration */
    return kAppMotionParam.Profile_acceleration;
}

uint32_t set_app_Profile_deceleration(float val)
{
    if (val < 0.0)
        return APP_PARAM_OUT_OF_RANGE;
    /* USER CODE BEGIN set_app_Profile_deceleration 0 */
    if (val > kAppRestrictParam.Max_deceleration)
    {
        return APP_PARAM_OUT_OF_RANGE;
    }

    /* USER CODE END set_app_Profile_deceleration 0 */
    kAppMotionParam.Profile_deceleration = val;
    /* USER CODE BEGIN set_app_Profile_deceleration 1 */
    /* USER CODE END set_app_Profile_deceleration 1 */
    return APP_PARAM_SUCCESS;
}
float get_app_Profile_deceleration(void)
{
    /* USER CODE BEGIN get_app_Profile_deceleration */
    /* USER CODE END get_app_Profile_deceleration */
    return kAppMotionParam.Profile_deceleration;
}

uint32_t set_app_Quick_stop_deceleration(float val)
{
    if (val < 0.0)
        return APP_PARAM_OUT_OF_RANGE;
    /* USER CODE BEGIN set_app_Quick_stop_deceleration 0 */
    if (val > kAppRestrictParam.Max_deceleration)
    {
        return APP_PARAM_OUT_OF_RANGE;
    }

    /* USER CODE END set_app_Quick_stop_deceleration 0 */
    kAppMotionParam.Quick_stop_deceleration = val;
    /* USER CODE BEGIN set_app_Quick_stop_deceleration 1 */
    /* USER CODE END set_app_Quick_stop_deceleration 1 */
    return APP_PARAM_SUCCESS;
}
float get_app_Quick_stop_deceleration(void)
{
    /* USER CODE BEGIN get_app_Quick_stop_deceleration */
    /* USER CODE END get_app_Quick_stop_deceleration */
    return kAppMotionParam.Quick_stop_deceleration;
}

uint32_t set_app_Motion_profile_type(int32_t val)
{
    /* USER CODE BEGIN set_app_Motion_profile_type 0 */
    /* USER CODE END set_app_Motion_profile_type 0 */
    kAppMotionParam.Motion_profile_type = val;
    /* USER CODE BEGIN set_app_Motion_profile_type 1 */
    /* USER CODE END set_app_Motion_profile_type 1 */
    return APP_PARAM_SUCCESS;
}
int32_t get_app_Motion_profile_type(void)
{
    /* USER CODE BEGIN get_app_Motion_profile_type */
    /* USER CODE END get_app_Motion_profile_type */
    return kAppMotionParam.Motion_profile_type;
}

uint32_t set_app_Home_offset(int64_t val)
{
    /* USER CODE BEGIN set_app_Home_offset 0 */
    /* USER CODE END set_app_Home_offset 0 */
    kAppMotionParam.Home_offset = val;
    /* USER CODE BEGIN set_app_Home_offset 1 */
    /* USER CODE END set_app_Home_offset 1 */
    return APP_PARAM_SUCCESS;
}
int64_t get_app_Home_offset(void)
{
    /* USER CODE BEGIN get_app_Home_offset */
    /* USER CODE END get_app_Home_offset */
    return kAppMotionParam.Home_offset;
}

uint32_t set_app_Homing_method(int8_t val)
{
    if (val < -2)
        return APP_PARAM_OUT_OF_RANGE;
    if (val > 35)
        return APP_PARAM_OUT_OF_RANGE;

    /* USER CODE BEGIN set_app_Homing_method 0 */
    /* USER CODE END set_app_Homing_method 0 */
    kAppMotionParam.Homing_method = val;
    /* USER CODE BEGIN set_app_Homing_method 1 */
    /* USER CODE END set_app_Homing_method 1 */
    return APP_PARAM_SUCCESS;
}
int8_t get_app_Homing_method(void)
{
    /* USER CODE BEGIN get_app_Homing_method */
    /* USER CODE END get_app_Homing_method */
    return kAppMotionParam.Homing_method;
}

uint32_t set_app_Target_velocity(float val)
{
    /* USER CODE BEGIN set_app_Target_velocity 0 */
    if (MATH_ABS(val) > kAppRestrictParam.Max_profile_velocity)
    {
        return APP_PARAM_OUT_OF_RANGE;
    }

    /* USER CODE END set_app_Target_velocity 0 */
    kAppMotionParam.Target_velocity = val;
    /* USER CODE BEGIN set_app_Target_velocity 1 */
    /* USER CODE END set_app_Target_velocity 1 */
    return APP_PARAM_SUCCESS;
}
float get_app_Target_velocity(void)
{
    /* USER CODE BEGIN get_app_Target_velocity */
    /* USER CODE END get_app_Target_velocity */
    return kAppMotionParam.Target_velocity;
}

uint32_t set_app_Target_torque(float val)
{
    /* USER CODE BEGIN set_app_Target_torque 0 */
    if (MATH_ABS(val) > kAppRestrictParam.Max_current)
    {
        return APP_PARAM_OUT_OF_RANGE;
    }

    /* USER CODE END set_app_Target_torque 0 */
    kAppMotionParam.Target_torque = val;
    /* USER CODE BEGIN set_app_Target_torque 1 */
    /* USER CODE END set_app_Target_torque 1 */
    return APP_PARAM_SUCCESS;
}
float get_app_Target_torque(void)
{
    /* USER CODE BEGIN get_app_Target_torque */
    /* USER CODE END get_app_Target_torque */
    return kAppMotionParam.Target_torque;
}

uint32_t set_app_Torque_slope(float val)
{
    if (val < 0.0)
        return APP_PARAM_OUT_OF_RANGE;
    /* USER CODE BEGIN set_app_Torque_slope 0 */
    if (val <= 0)
    {
        return 0; // TODO:应用层参数设置错误返回值
    }

    /* USER CODE END set_app_Torque_slope 0 */
    kAppMotionParam.Torque_slope = val;
    /* USER CODE BEGIN set_app_Torque_slope 1 */
    /* USER CODE END set_app_Torque_slope 1 */
    return APP_PARAM_SUCCESS;
}
float get_app_Torque_slope(void)
{
    /* USER CODE BEGIN get_app_Torque_slope */
    /* USER CODE END get_app_Torque_slope */
    return kAppMotionParam.Torque_slope;
}

uint32_t set_app_Encoder_calibration_speed(float val)
{
    if (val < 0.0)
        return APP_PARAM_OUT_OF_RANGE;
    /* USER CODE BEGIN set_app_Encoder_calibration_speed 0 */
    if (axis->motor_ctl_sm_output.state == MOTOR_CTL_SM_MOTOR_ENABLE)
    {
        return APP_PARAM_WRITE_STATE_ERROR;
    }
    /* USER CODE END set_app_Encoder_calibration_speed 0 */
    kAppMotionParam.Encoder_calibration_speed = val;
    /* USER CODE BEGIN set_app_Encoder_calibration_speed 1 */
    /* USER CODE END set_app_Encoder_calibration_speed 1 */
    return APP_PARAM_SUCCESS;
}
float get_app_Encoder_calibration_speed(void)
{
    /* USER CODE BEGIN get_app_Encoder_calibration_speed */
    /* USER CODE END get_app_Encoder_calibration_speed */
    return kAppMotionParam.Encoder_calibration_speed;
}

uint32_t set_app_MIT_feedforward_torque(float val)
{
    /* USER CODE BEGIN set_app_MIT_feedforward_torque 0 */
    /* USER CODE END set_app_MIT_feedforward_torque 0 */
    kAppMotionParam.MIT_feedforward_torque = val;
    /* USER CODE BEGIN set_app_MIT_feedforward_torque 1 */
    /* USER CODE END set_app_MIT_feedforward_torque 1 */
    return APP_PARAM_SUCCESS;
}
float get_app_MIT_feedforward_torque(void)
{
    /* USER CODE BEGIN get_app_MIT_feedforward_torque */
    /* USER CODE END get_app_MIT_feedforward_torque */
    return kAppMotionParam.MIT_feedforward_torque;
}

uint32_t set_app_MIT_target_position(int64_t val)
{
    /* USER CODE BEGIN set_app_MIT_target_position 0 */
    /* USER CODE END set_app_MIT_target_position 0 */
    kAppMotionParam.MIT_target_position = val;
    /* USER CODE BEGIN set_app_MIT_target_position 1 */
    /* USER CODE END set_app_MIT_target_position 1 */
    return APP_PARAM_SUCCESS;
}
int64_t get_app_MIT_target_position(void)
{
    /* USER CODE BEGIN get_app_MIT_target_position */
    /* USER CODE END get_app_MIT_target_position */
    return kAppMotionParam.MIT_target_position;
}

uint32_t set_app_MIT_max_current(float val)
{
    if (val < 0.0)
        return APP_PARAM_OUT_OF_RANGE;
    /* USER CODE BEGIN set_app_MIT_max_current 0 */
    if (val > kAppRestrictParam.Max_current)
    {
        return APP_PARAM_OUT_OF_RANGE;
    }

    /* USER CODE END set_app_MIT_max_current 0 */
    kAppMotionParam.MIT_max_current = val;
    /* USER CODE BEGIN set_app_MIT_max_current 1 */
    /* USER CODE END set_app_MIT_max_current 1 */
    return APP_PARAM_SUCCESS;
}
float get_app_MIT_max_current(void)
{
    /* USER CODE BEGIN get_app_MIT_max_current */
    /* USER CODE END get_app_MIT_max_current */
    return kAppMotionParam.MIT_max_current;
}

uint32_t set_app_MIT_target_velocity(float val)
{
    /* USER CODE BEGIN set_app_MIT_target_velocity 0 */
    // TODO:增加限制
    /* USER CODE END set_app_MIT_target_velocity 0 */
    kAppMotionParam.MIT_target_velocity = val;
    /* USER CODE BEGIN set_app_MIT_target_velocity 1 */
    /* USER CODE END set_app_MIT_target_velocity 1 */
    return APP_PARAM_SUCCESS;
}
float get_app_MIT_target_velocity(void)
{
    /* USER CODE BEGIN get_app_MIT_target_velocity */
    /* USER CODE END get_app_MIT_target_velocity */
    return kAppMotionParam.MIT_target_velocity;
}

uint32_t set_app_MIT_kp(float val)
{
    /* USER CODE BEGIN set_app_MIT_kp 0 */
    // TODO:增加限制
    /* USER CODE END set_app_MIT_kp 0 */
    kAppMotionParam.MIT_kp = val;
    /* USER CODE BEGIN set_app_MIT_kp 1 */
    /* USER CODE END set_app_MIT_kp 1 */
    return APP_PARAM_SUCCESS;
}
float get_app_MIT_kp(void)
{
    /* USER CODE BEGIN get_app_MIT_kp */
    /* USER CODE END get_app_MIT_kp */
    return kAppMotionParam.MIT_kp;
}

uint32_t set_app_MIT_kd(float val)
{
    /* USER CODE BEGIN set_app_MIT_kd 0 */
    // TODO:增加限制
    /* USER CODE END set_app_MIT_kd 0 */
    kAppMotionParam.MIT_kd = val;
    /* USER CODE BEGIN set_app_MIT_kd 1 */
    /* USER CODE END set_app_MIT_kd 1 */
    return APP_PARAM_SUCCESS;
}
float get_app_MIT_kd(void)
{
    /* USER CODE BEGIN get_app_MIT_kd */
    /* USER CODE END get_app_MIT_kd */
    return kAppMotionParam.MIT_kd;
}

uint32_t set_app_Interp_time_value(uint8_t val)
{
    /* USER CODE BEGIN set_app_Interp_time_value 0 */
    const float factors[] = {1e-5f, 1e-4f, 1e-3f, 1e-2f, 1e-1f, \
                             1.0f,1e+1f, 1e+2f, 1e+3f, 1e+4f, 1e+5f};
    /* USER CODE END set_app_Interp_time_value 0 */
    kAppMotionParam.Interp_time_value = val;
    /* USER CODE BEGIN set_app_Interp_time_value 1 */
    uint8_t index = get_app_Interp_time_index() + 5;
    float ip_period = factors[index] * val;
    set_app_Interp_period(ip_period);
    /* USER CODE END set_app_Interp_time_value 1 */
    return APP_PARAM_SUCCESS;
}
uint8_t get_app_Interp_time_value(void)
{
    /* USER CODE BEGIN get_app_Interp_time_value */
    /* USER CODE END get_app_Interp_time_value */
    return kAppMotionParam.Interp_time_value;
}

uint32_t set_app_Interp_time_index(int8_t val)
{
    if (val < -5)
        return APP_PARAM_OUT_OF_RANGE;
    if (val > 5)
        return APP_PARAM_OUT_OF_RANGE;

    /* USER CODE BEGIN set_app_Interp_time_index 0 */
    const float factors[] = {1e-5f, 1e-4f, 1e-3f, 1e-2f, 1e-1f, \
                             1.0f,1e+1f, 1e+2f, 1e+3f, 1e+4f, 1e+5f};
    /* USER CODE END set_app_Interp_time_index 0 */
    kAppMotionParam.Interp_time_index = val;
    /* USER CODE BEGIN set_app_Interp_time_index 1 */
    uint8_t index = val + 5;
    float ip_period = factors[index] * get_app_Interp_time_value();
    set_app_Interp_period(ip_period);
    /* USER CODE END set_app_Interp_time_index 1 */
    return APP_PARAM_SUCCESS;
}
int8_t get_app_Interp_time_index(void)
{
    /* USER CODE BEGIN get_app_Interp_time_index */
    /* USER CODE END get_app_Interp_time_index */
    return kAppMotionParam.Interp_time_index;
}

uint32_t set_app_Homing_speed_search_for_switch(float val)
{
    if (val < 0.0)
        return APP_PARAM_OUT_OF_RANGE;
    /* USER CODE BEGIN set_app_Homing_speed_search_for_switch 0 */
    if (val > kAppRestrictParam.Max_profile_velocity)
    {
        return APP_PARAM_OUT_OF_RANGE;
    }
    /* USER CODE END set_app_Homing_speed_search_for_switch 0 */
    kAppMotionParam.Homing_speed_search_for_switch = val;
    /* USER CODE BEGIN set_app_Homing_speed_search_for_switch 1 */
    /* USER CODE END set_app_Homing_speed_search_for_switch 1 */
    return APP_PARAM_SUCCESS;
}
float get_app_Homing_speed_search_for_switch(void)
{
    /* USER CODE BEGIN get_app_Homing_speed_search_for_switch */
    /* USER CODE END get_app_Homing_speed_search_for_switch */
    return kAppMotionParam.Homing_speed_search_for_switch;
}

uint32_t set_app_Homing_speed_search_for_zero(float val)
{
    if (val < 0.0)
        return APP_PARAM_OUT_OF_RANGE;
    /* USER CODE BEGIN set_app_Homing_speed_search_for_zero 0 */
    if (val > kAppRestrictParam.Max_profile_velocity)
    {
        return APP_PARAM_OUT_OF_RANGE;
    }
    /* USER CODE END set_app_Homing_speed_search_for_zero 0 */
    kAppMotionParam.Homing_speed_search_for_zero = val;
    /* USER CODE BEGIN set_app_Homing_speed_search_for_zero 1 */
    /* USER CODE END set_app_Homing_speed_search_for_zero 1 */
    return APP_PARAM_SUCCESS;
}
float get_app_Homing_speed_search_for_zero(void)
{
    /* USER CODE BEGIN get_app_Homing_speed_search_for_zero */
    /* USER CODE END get_app_Homing_speed_search_for_zero */
    return kAppMotionParam.Homing_speed_search_for_zero;
}

uint32_t set_app_Homing_acceleration(float val)
{
    if (val < 0.0)
        return APP_PARAM_OUT_OF_RANGE;
    /* USER CODE BEGIN set_app_Homing_acceleration 0 */
    if (val > kAppRestrictParam.Max_acceleration)
    {
        return APP_PARAM_OUT_OF_RANGE;
    }
    /* USER CODE END set_app_Homing_acceleration 0 */
    kAppMotionParam.Homing_acceleration = val;
    /* USER CODE BEGIN set_app_Homing_acceleration 1 */
    /* USER CODE END set_app_Homing_acceleration 1 */
    return APP_PARAM_SUCCESS;
}
float get_app_Homing_acceleration(void)
{
    /* USER CODE BEGIN get_app_Homing_acceleration */
    /* USER CODE END get_app_Homing_acceleration */
    return kAppMotionParam.Homing_acceleration;
}

uint32_t set_app_Position_range_limit_Minimal_position_limit(int64_t val)
{
    /* USER CODE BEGIN set_app_Position_range_limit_Minimal_position_limit 0 */
    if (val > kAppRestrictParam.Position_range_limit_Maximal_position_limit)
    {
        return APP_PARAM_OUT_OF_RANGE;
    }
    /* USER CODE END set_app_Position_range_limit_Minimal_position_limit 0 */
    kAppRestrictParam.Position_range_limit_Minimal_position_limit = val;
    /* USER CODE BEGIN set_app_Position_range_limit_Minimal_position_limit 1 */
    /* USER CODE END set_app_Position_range_limit_Minimal_position_limit 1 */
    return APP_PARAM_SUCCESS;
}
int64_t get_app_Position_range_limit_Minimal_position_limit(void)
{
    /* USER CODE BEGIN get_app_Position_range_limit_Minimal_position_limit */
    /* USER CODE END get_app_Position_range_limit_Minimal_position_limit */
    return kAppRestrictParam.Position_range_limit_Minimal_position_limit;
}

uint32_t set_app_Position_range_limit_Maximal_position_limit(int64_t val)
{
    /* USER CODE BEGIN set_app_Position_range_limit_Maximal_position_limit 0 */
    if (val < kAppRestrictParam.Position_range_limit_Minimal_position_limit)
    {
        return APP_PARAM_OUT_OF_RANGE;
    }
    /* USER CODE END set_app_Position_range_limit_Maximal_position_limit 0 */
    kAppRestrictParam.Position_range_limit_Maximal_position_limit = val;
    /* USER CODE BEGIN set_app_Position_range_limit_Maximal_position_limit 1 */
    /* USER CODE END set_app_Position_range_limit_Maximal_position_limit 1 */
    return APP_PARAM_SUCCESS;
}
int64_t get_app_Position_range_limit_Maximal_position_limit(void)
{
    /* USER CODE BEGIN get_app_Position_range_limit_Maximal_position_limit */
    /* USER CODE END get_app_Position_range_limit_Maximal_position_limit */
    return kAppRestrictParam.Position_range_limit_Maximal_position_limit;
}

uint32_t set_app_Software_position_limit_Minimal_position_limit(int64_t val)
{
    /* USER CODE BEGIN set_app_Software_position_limit_Minimal_position_limit 0 */
    if (val > kAppRestrictParam.Software_position_limit_Maximal_position_limit)
    {
        return APP_PARAM_OUT_OF_RANGE;
    }
    /* USER CODE END set_app_Software_position_limit_Minimal_position_limit 0 */
    kAppRestrictParam.Software_position_limit_Minimal_position_limit = val;
    /* USER CODE BEGIN set_app_Software_position_limit_Minimal_position_limit 1 */
    /* USER CODE END set_app_Software_position_limit_Minimal_position_limit 1 */
    return APP_PARAM_SUCCESS;
}
int64_t get_app_Software_position_limit_Minimal_position_limit(void)
{
    /* USER CODE BEGIN get_app_Software_position_limit_Minimal_position_limit */
    /* USER CODE END get_app_Software_position_limit_Minimal_position_limit */
    return kAppRestrictParam.Software_position_limit_Minimal_position_limit;
}

uint32_t set_app_Software_position_limit_Maximal_position_limit(int64_t val)
{
    /* USER CODE BEGIN set_app_Software_position_limit_Maximal_position_limit 0 */
    if (val < kAppRestrictParam.Software_position_limit_Minimal_position_limit)
    {
        return APP_PARAM_OUT_OF_RANGE;
    }
    /* USER CODE END set_app_Software_position_limit_Maximal_position_limit 0 */
    kAppRestrictParam.Software_position_limit_Maximal_position_limit = val;
    /* USER CODE BEGIN set_app_Software_position_limit_Maximal_position_limit 1 */
    /* USER CODE END set_app_Software_position_limit_Maximal_position_limit 1 */
    return APP_PARAM_SUCCESS;
}
int64_t get_app_Software_position_limit_Maximal_position_limit(void)
{
    /* USER CODE BEGIN get_app_Software_position_limit_Maximal_position_limit */
    /* USER CODE END get_app_Software_position_limit_Maximal_position_limit */
    return kAppRestrictParam.Software_position_limit_Maximal_position_limit;
}

uint32_t set_app_Max_profile_velocity(float val)
{
    if (val < 0.0)
        return APP_PARAM_OUT_OF_RANGE;
    /* USER CODE BEGIN set_app_Max_profile_velocity 0 */
    if (axis->motor_ctl_sm_output.state == MOTOR_CTL_SM_MOTOR_ENABLE)
    {
        return APP_PARAM_WRITE_STATE_ERROR;
    }
    /* USER CODE END set_app_Max_profile_velocity 0 */
    kAppRestrictParam.Max_profile_velocity = val;
    /* USER CODE BEGIN set_app_Max_profile_velocity 1 */
    app_param_restrictions_update();
    /* USER CODE END set_app_Max_profile_velocity 1 */
    return APP_PARAM_SUCCESS;
}
float get_app_Max_profile_velocity(void)
{
    /* USER CODE BEGIN get_app_Max_profile_velocity */
    /* USER CODE END get_app_Max_profile_velocity */
    return kAppRestrictParam.Max_profile_velocity;
}

uint32_t set_app_Max_motor_speed(float val)
{
    if (val < 0.0)
        return APP_PARAM_OUT_OF_RANGE;
    /* USER CODE BEGIN set_app_Max_motor_speed 0 */
    /* USER CODE END set_app_Max_motor_speed 0 */
    kAppRestrictParam.Max_motor_speed = val;
    /* USER CODE BEGIN set_app_Max_motor_speed 1 */
    //应用层写入无效，这个参数等同与电机额定参数中最大速度
    kAppRestrictParam.Max_motor_speed = kAppMotorConfig.Motor_maximum_speed;
    /* USER CODE END set_app_Max_motor_speed 1 */
    return APP_PARAM_SUCCESS;
}
float get_app_Max_motor_speed(void)
{
    /* USER CODE BEGIN get_app_Max_motor_speed */
    /* USER CODE END get_app_Max_motor_speed */
    return kAppRestrictParam.Max_motor_speed;
}

uint32_t set_app_Max_acceleration(float val)
{
    if (val < 0.0)
        return APP_PARAM_OUT_OF_RANGE;
    /* USER CODE BEGIN set_app_Max_acceleration 0 */
    /* USER CODE END set_app_Max_acceleration 0 */
    kAppRestrictParam.Max_acceleration = val;
    /* USER CODE BEGIN set_app_Max_acceleration 1 */
    /* USER CODE END set_app_Max_acceleration 1 */
    return APP_PARAM_SUCCESS;
}
float get_app_Max_acceleration(void)
{
    /* USER CODE BEGIN get_app_Max_acceleration */
    /* USER CODE END get_app_Max_acceleration */
    return kAppRestrictParam.Max_acceleration;
}

uint32_t set_app_Max_deceleration(float val)
{
    if (val < 0.0)
        return APP_PARAM_OUT_OF_RANGE;
    /* USER CODE BEGIN set_app_Max_deceleration 0 */
    /* USER CODE END set_app_Max_deceleration 0 */
    kAppRestrictParam.Max_deceleration = val;
    /* USER CODE BEGIN set_app_Max_deceleration 1 */
    /* USER CODE END set_app_Max_deceleration 1 */
    return APP_PARAM_SUCCESS;
}
float get_app_Max_deceleration(void)
{
    /* USER CODE BEGIN get_app_Max_deceleration */
    /* USER CODE END get_app_Max_deceleration */
    return kAppRestrictParam.Max_deceleration;
}

uint32_t set_app_Max_current(float val)
{
    if (val < 0.0)
        return APP_PARAM_OUT_OF_RANGE;
    /* USER CODE BEGIN set_app_Max_current 0 */
    /* USER CODE END set_app_Max_current 0 */
    kAppRestrictParam.Max_current = val;
    /* USER CODE BEGIN set_app_Max_current 1 */
    app_param_restrictions_update();

    /* USER CODE END set_app_Max_current 1 */
    return APP_PARAM_SUCCESS;
}
float get_app_Max_current(void)
{
    /* USER CODE BEGIN get_app_Max_current */
    /* USER CODE END get_app_Max_current */
    return kAppRestrictParam.Max_current;
}

uint32_t set_app_Position_limit_enable(uint8_t val)
{
    if (val < 0)
        return APP_PARAM_OUT_OF_RANGE;
    if (val > 1)
        return APP_PARAM_OUT_OF_RANGE;

    /* USER CODE BEGIN set_app_Position_limit_enable 0 */
    /* USER CODE END set_app_Position_limit_enable 0 */
    kAppRestrictParam.Position_limit_enable = val;
    /* USER CODE BEGIN set_app_Position_limit_enable 1 */
    /* USER CODE END set_app_Position_limit_enable 1 */
    return APP_PARAM_SUCCESS;
}
uint8_t get_app_Position_limit_enable(void)
{
    /* USER CODE BEGIN get_app_Position_limit_enable */
    /* USER CODE END get_app_Position_limit_enable */
    return kAppRestrictParam.Position_limit_enable;
}

uint32_t set_app_Position_demand_value(int64_t val)
{
    /* USER CODE BEGIN set_app_Position_demand_value 0 */
    /* USER CODE END set_app_Position_demand_value 0 */
    kAppMotionInfo.Position_demand_value = val;

    return APP_PARAM_SUCCESS;
}
int64_t get_app_Position_demand_value(void)
{
    /* USER CODE BEGIN get_app_Position_demand_value */
    kAppMotionInfo.Position_demand_value = kAppMotionInfo.Position_actual_value + kAppMotionInfo.Following_error_actual_value;

    /* USER CODE END get_app_Position_demand_value */
    return kAppMotionInfo.Position_demand_value;
}

uint32_t set_app_Position_actual_value_inc(int64_t val)
{
    /* USER CODE BEGIN set_app_Position_actual_value_inc 0 */
    /* USER CODE END set_app_Position_actual_value_inc 0 */
    kAppMotionInfo.Position_actual_value_inc = val;

    return APP_PARAM_SUCCESS;
}
int64_t get_app_Position_actual_value_inc(void)
{
    /* USER CODE BEGIN get_app_Position_actual_value_inc */
    if (bsp_get_encoder_type(ENCODER_ID_LOAD) == 0x00)  //负载端无编码器，内部位置反馈都以电机端编码器为参考
    {
        if (kAppMotorConfig.Reduction_ratio_num == 1) //减速比1:1  直接以电机端编码器位置为反馈
        {
            kAppMotionInfo.Position_actual_value_inc = axis->motor_pos_sensor_output.enc_sum_p;
        }
        else  //减速比不为1:1  将电机端编码器位置经过减速比换算到负载端脉冲数
        {
            kAppMotionInfo.Position_actual_value_inc = PosUnitMotorToLoad(axis->motor_pos_sensor_output.enc_sum_p);
        }
    }
    else  //负载端有编码器则以负载端编码器为参考
    {
        kAppMotionInfo.Position_actual_value_inc = axis->load_pos_sensor_output.enc_sum_p;
    }

    /* USER CODE END get_app_Position_actual_value_inc */
    return kAppMotionInfo.Position_actual_value_inc;
}

uint32_t set_app_Position_actual_value(int64_t val)
{
    /* USER CODE BEGIN set_app_Position_actual_value 0 */
    /* USER CODE END set_app_Position_actual_value 0 */
    kAppMotionInfo.Position_actual_value = val;

    return APP_PARAM_SUCCESS;
}
int64_t get_app_Position_actual_value(void)
{
    /* USER CODE BEGIN get_app_Position_actual_value */
    kAppMotionInfo.Position_actual_value = kAppMotionInfo.Position_actual_value_inc - kAppBaseConfig.Home_position_offset_value;
    /* USER CODE END get_app_Position_actual_value */
    return kAppMotionInfo.Position_actual_value;
}

uint32_t set_app_Following_error_actual_value(int64_t val)
{
    /* USER CODE BEGIN set_app_Following_error_actual_value 0 */
    /* USER CODE END set_app_Following_error_actual_value 0 */
    kAppMotionInfo.Following_error_actual_value = val;

    return APP_PARAM_SUCCESS;
}
int64_t get_app_Following_error_actual_value(void)
{
    /* USER CODE BEGIN get_app_Following_error_actual_value */
    kAppMotionInfo.Following_error_actual_value = (float)(axis->pos_speed_ctl_output.pos_ctl_error_p) * kAppMotorConfig.Reduction_ratio_inv;
    /* USER CODE END get_app_Following_error_actual_value */
    return kAppMotionInfo.Following_error_actual_value;
}

uint32_t set_app_Velocity_demand_value(float val)
{
    /* USER CODE BEGIN set_app_Velocity_demand_value 0 */
    /* USER CODE END set_app_Velocity_demand_value 0 */
    kAppMotionInfo.Velocity_demand_value = val;

    return APP_PARAM_SUCCESS;
}
float get_app_Velocity_demand_value(void)
{
    /* USER CODE BEGIN get_app_Velocity_demand_value */
    kAppMotionInfo.Velocity_demand_value = axis->pos_speed_ctl_input.speed_tar_p_s *
                                           axis->pos_speed_ctl_config.enc_line_inv_p_n * 60.0f * kAppMotorConfig.Reduction_ratio_inv;
    /* USER CODE END get_app_Velocity_demand_value */
    return kAppMotionInfo.Velocity_demand_value;
}

uint32_t set_app_Velocity_actual_value(float val)
{
    /* USER CODE BEGIN set_app_Velocity_actual_value 0 */
    /* USER CODE END set_app_Velocity_actual_value 0 */
    kAppMotionInfo.Velocity_actual_value = val;

    return APP_PARAM_SUCCESS;
}
float get_app_Velocity_actual_value(void)
{
    /* USER CODE BEGIN get_app_Velocity_actual_value */
    kAppMotionInfo.Velocity_actual_value = axis->pos_speed_ctl_input.speed_now_rad_s * MATH_RAD2RPM * kAppMotorConfig.Reduction_ratio_inv;
    /* USER CODE END get_app_Velocity_actual_value */
    return kAppMotionInfo.Velocity_actual_value;
}

uint32_t set_app_Torque_demand_value(float val)
{
    /* USER CODE BEGIN set_app_Torque_demand_value 0 */
    /* USER CODE END set_app_Torque_demand_value 0 */
    kAppMotionInfo.Torque_demand_value = val;

    return APP_PARAM_SUCCESS;
}
float get_app_Torque_demand_value(void)
{
    /* USER CODE BEGIN get_app_Torque_demand_value */
    kAppMotionInfo.Torque_demand_value = axis->current_ctl_input.idq_tar_A[1];
    /* USER CODE END get_app_Torque_demand_value */
    return kAppMotionInfo.Torque_demand_value;
}

uint32_t set_app_Torque_actual_value(float val)
{
    /* USER CODE BEGIN set_app_Torque_actual_value 0 */
    /* USER CODE END set_app_Torque_actual_value 0 */
    kAppMotionInfo.Torque_actual_value = val;

    return APP_PARAM_SUCCESS;
}
float get_app_Torque_actual_value(void)
{
    /* USER CODE BEGIN get_app_Torque_actual_value */
    // todo:这里要给出实际转矩值，不是实际的q轴电流，需要乘以力矩系数
    kAppMotionInfo.Torque_actual_value = axis->current_ctl_output.idq_now_A[1];
    /* USER CODE END get_app_Torque_actual_value */
    return kAppMotionInfo.Torque_actual_value;
}

uint32_t set_app_Current_actual_value(float val)
{
    /* USER CODE BEGIN set_app_Current_actual_value 0 */
    /* USER CODE END set_app_Current_actual_value 0 */
    kAppMotionInfo.Current_actual_value = val;

    return APP_PARAM_SUCCESS;
}
float get_app_Current_actual_value(void)
{
    /* USER CODE BEGIN get_app_Current_actual_value */
    kAppMotionInfo.Current_actual_value = axis->current_ctl_output.idq_now_A[1];
    /* USER CODE END get_app_Current_actual_value */
    return kAppMotionInfo.Current_actual_value;
}

uint32_t set_app_D_current_actual_value(float val)
{
    /* USER CODE BEGIN set_app_D_current_actual_value 0 */
    /* USER CODE END set_app_D_current_actual_value 0 */
    kAppMotionInfo.D_current_actual_value = val;

    return APP_PARAM_SUCCESS;
}
float get_app_D_current_actual_value(void)
{
    /* USER CODE BEGIN get_app_D_current_actual_value */
    kAppMotionInfo.D_current_actual_value = axis->current_ctl_output.idq_now_A[0];
    /* USER CODE END get_app_D_current_actual_value */
    return kAppMotionInfo.D_current_actual_value;
}

uint32_t set_app_U_current_actual_value(float val)
{
    /* USER CODE BEGIN set_app_U_current_actual_value 0 */
    /* USER CODE END set_app_U_current_actual_value 0 */
    kAppMotionInfo.U_current_actual_value = val;

    return APP_PARAM_SUCCESS;
}
float get_app_U_current_actual_value(void)
{
    /* USER CODE BEGIN get_app_U_current_actual_value */
    kAppMotionInfo.U_current_actual_value = axis->current_ctl_input.iabc_now_A[0];
    /* USER CODE END get_app_U_current_actual_value */
    return kAppMotionInfo.U_current_actual_value;
}

uint32_t set_app_V_current_actual_value(float val)
{
    /* USER CODE BEGIN set_app_V_current_actual_value 0 */
    /* USER CODE END set_app_V_current_actual_value 0 */
    kAppMotionInfo.V_current_actual_value = val;

    return APP_PARAM_SUCCESS;
}
float get_app_V_current_actual_value(void)
{
    /* USER CODE BEGIN get_app_V_current_actual_value */
    kAppMotionInfo.V_current_actual_value = axis->current_ctl_input.iabc_now_A[1];
    /* USER CODE END get_app_V_current_actual_value */
    return kAppMotionInfo.V_current_actual_value;
}

uint32_t set_app_W_current_actual_value(float val)
{
    /* USER CODE BEGIN set_app_W_current_actual_value 0 */
    /* USER CODE END set_app_W_current_actual_value 0 */
    kAppMotionInfo.W_current_actual_value = val;

    return APP_PARAM_SUCCESS;
}
float get_app_W_current_actual_value(void)
{
    /* USER CODE BEGIN get_app_W_current_actual_value */
    kAppMotionInfo.W_current_actual_value = axis->current_ctl_input.iabc_now_A[2];
    /* USER CODE END get_app_W_current_actual_value */
    return kAppMotionInfo.W_current_actual_value;
}

uint32_t set_app_Motor_position_demand_value(int64_t val)
{
    /* USER CODE BEGIN set_app_Motor_position_demand_value 0 */
    /* USER CODE END set_app_Motor_position_demand_value 0 */
    kAppMotionInfo.Motor_position_demand_value = val;

    return APP_PARAM_SUCCESS;
}
int64_t get_app_Motor_position_demand_value(void)
{
    /* USER CODE BEGIN get_app_Motor_position_demand_value */
    kAppMotionInfo.Motor_position_demand_value = axis->input_shaping_input.pos_cmd_p;
    /* USER CODE END get_app_Motor_position_demand_value */
    return kAppMotionInfo.Motor_position_demand_value;
}

uint32_t set_app_Motor_position_actual_value(int64_t val)
{
    /* USER CODE BEGIN set_app_Motor_position_actual_value 0 */
    /* USER CODE END set_app_Motor_position_actual_value 0 */
    kAppMotionInfo.Motor_position_actual_value = val;

    return APP_PARAM_SUCCESS;
}
int64_t get_app_Motor_position_actual_value(void)
{
    /* USER CODE BEGIN get_app_Motor_position_actual_value */
    kAppMotionInfo.Motor_position_actual_value = axis->motor_pos_sensor_output.enc_sum_p;
    /* USER CODE END get_app_Motor_position_actual_value */
    return kAppMotionInfo.Motor_position_actual_value;
}

uint32_t set_app_Motor_following_error_actual_value(int64_t val)
{
    /* USER CODE BEGIN set_app_Motor_following_error_actual_value 0 */
    /* USER CODE END set_app_Motor_following_error_actual_value 0 */
    kAppMotionInfo.Motor_following_error_actual_value = val;

    return APP_PARAM_SUCCESS;
}
int64_t get_app_Motor_following_error_actual_value(void)
{
    /* USER CODE BEGIN get_app_Motor_following_error_actual_value */
    kAppMotionInfo.Motor_following_error_actual_value = axis->pos_speed_ctl_output.pos_ctl_error_p;
    /* USER CODE END get_app_Motor_following_error_actual_value */
    return kAppMotionInfo.Motor_following_error_actual_value;
}

uint32_t set_app_Motor_velocity_demand_value(float val)
{
    /* USER CODE BEGIN set_app_Motor_velocity_demand_value 0 */
    /* USER CODE END set_app_Motor_velocity_demand_value 0 */
    kAppMotionInfo.Motor_velocity_demand_value = val;

    return APP_PARAM_SUCCESS;
}
float get_app_Motor_velocity_demand_value(void)
{
    /* USER CODE BEGIN get_app_Motor_velocity_demand_value */
    kAppMotionInfo.Motor_velocity_demand_value = axis->pos_speed_ctl_input.speed_tar_p_s *
                                                 axis->pos_speed_ctl_config.enc_line_inv_p_n * 60.0f;
    /* USER CODE END get_app_Motor_Velocity_demand_value */
    /* USER CODE END get_app_Motor_velocity_demand_value */
    return kAppMotionInfo.Motor_velocity_demand_value;
}

uint32_t set_app_Motor_velocity_actual_value(float val)
{
    /* USER CODE BEGIN set_app_Motor_velocity_actual_value 0 */
    /* USER CODE END set_app_Motor_velocity_actual_value 0 */
    kAppMotionInfo.Motor_velocity_actual_value = val;

    return APP_PARAM_SUCCESS;
}
float get_app_Motor_velocity_actual_value(void)
{
    /* USER CODE BEGIN get_app_Motor_velocity_actual_value */
    kAppMotionInfo.Motor_velocity_actual_value = axis->pos_speed_ctl_input.speed_now_rad_s * MATH_RAD2RPM;
    /* USER CODE END get_app_Motor_velocity_actual_value */
    return kAppMotionInfo.Motor_velocity_actual_value;
}

uint32_t set_app_U_adc_mid_val(uint16_t val)
{
    /* USER CODE BEGIN set_app_U_adc_mid_val 0 */
    /* USER CODE END set_app_U_adc_mid_val 0 */
    kAppMotionInfo.U_adc_mid_val = val;

    return APP_PARAM_SUCCESS;
}
uint16_t get_app_U_adc_mid_val(void)
{
    /* USER CODE BEGIN get_app_U_adc_mid_val */
    uint16_t drift[3];
    sys_get_current_calibration_drift(drift);
    kAppMotionInfo.U_adc_mid_val = drift[0];
    /* USER CODE END get_app_U_adc_mid_val */
    return kAppMotionInfo.U_adc_mid_val;
}

uint32_t set_app_V_adc_mid_val(uint16_t val)
{
    /* USER CODE BEGIN set_app_V_adc_mid_val 0 */
    /* USER CODE END set_app_V_adc_mid_val 0 */
    kAppMotionInfo.V_adc_mid_val = val;

    return APP_PARAM_SUCCESS;
}
uint16_t get_app_V_adc_mid_val(void)
{
    /* USER CODE BEGIN get_app_V_adc_mid_val */
    uint16_t drift[3];
    sys_get_current_calibration_drift(drift);
    kAppMotionInfo.V_adc_mid_val = drift[1];
    /* USER CODE END get_app_V_adc_mid_val */
    return kAppMotionInfo.V_adc_mid_val;
}

uint32_t set_app_W_adc_mid_val(uint16_t val)
{
    /* USER CODE BEGIN set_app_W_adc_mid_val 0 */
    /* USER CODE END set_app_W_adc_mid_val 0 */
    kAppMotionInfo.W_adc_mid_val = val;

    return APP_PARAM_SUCCESS;
}
uint16_t get_app_W_adc_mid_val(void)
{
    /* USER CODE BEGIN get_app_W_adc_mid_val */
    uint16_t drift[3];
    sys_get_current_calibration_drift(drift);
    kAppMotionInfo.W_adc_mid_val = drift[2];
    /* USER CODE END get_app_W_adc_mid_val */
    return kAppMotionInfo.W_adc_mid_val;
}

uint32_t set_app_Current_loop_time(float val)
{
    /* USER CODE BEGIN set_app_Current_loop_time 0 */
    /* USER CODE END set_app_Current_loop_time 0 */
    kAppMotionInfo.Current_loop_time = val;

    return APP_PARAM_SUCCESS;
}
float get_app_Current_loop_time(void)
{
    /* USER CODE BEGIN get_app_Current_loop_time */
    kAppMotionInfo.Current_loop_time = bsp_get_timer_duration_records_us(SYS_TIMER_RECORD_CURRENT_LOOP_TIME_INDEX);
    /* USER CODE END get_app_Current_loop_time */
    return kAppMotionInfo.Current_loop_time;
}

uint32_t set_app_Position_loop_time(float val)
{
    /* USER CODE BEGIN set_app_Position_loop_time 0 */
    /* USER CODE END set_app_Position_loop_time 0 */
    kAppMotionInfo.Position_loop_time = val;

    return APP_PARAM_SUCCESS;
}
float get_app_Position_loop_time(void)
{
    /* USER CODE BEGIN get_app_Position_loop_time */
    kAppMotionInfo.Position_loop_time = bsp_get_timer_duration_records_us(SYS_TIMER_RECORD_POSITION_LOOP_TIME_INDEX);
    /* USER CODE END get_app_position_loop_time */
    /* USER CODE END get_app_Position_loop_time */
    return kAppMotionInfo.Position_loop_time;
}

uint32_t set_app_Current_loop_cycle(float val)
{
    /* USER CODE BEGIN set_app_Current_loop_cycle 0 */
    /* USER CODE END set_app_Current_loop_cycle 0 */
    kAppMotionInfo.Current_loop_cycle = val;

    return APP_PARAM_SUCCESS;
}
float get_app_Current_loop_cycle(void)
{
    /* USER CODE BEGIN get_app_Current_loop_cycle */
    kAppMotionInfo.Current_loop_cycle = bsp_get_timer_duration_records_us(SYS_TIMER_RECORD_CURRENT_LOOP_CYCLE_INDEX);
    /* USER CODE END get_app_Current_loop_cycle */
    return kAppMotionInfo.Current_loop_cycle;
}

uint32_t set_app_Position_loop_cycle(float val)
{
    /* USER CODE BEGIN set_app_Position_loop_cycle 0 */
    /* USER CODE END set_app_Position_loop_cycle 0 */
    kAppMotionInfo.Position_loop_cycle = val;

    return APP_PARAM_SUCCESS;
}
float get_app_Position_loop_cycle(void)
{
    /* USER CODE BEGIN get_app_Position_loop_cycle */
    kAppMotionInfo.Position_loop_cycle = bsp_get_timer_duration_records_us(SYS_TIMER_RECORD_POSITION_LOOP_CYCLE_INDEX);
    /* USER CODE END get_app_Position_loop_cycle */
    return kAppMotionInfo.Position_loop_cycle;
}

uint32_t set_app_Interp_period(float val)
{
    /* USER CODE BEGIN set_app_Interp_period 0 */
    /* USER CODE END set_app_Interp_period 0 */
    kAppMotionInfo.Interp_period = val;
    /* USER CODE BEGIN set_app_Interp_period 1 */
    /* USER CODE END set_app_Interp_period 1 */
    return APP_PARAM_SUCCESS;
}
float get_app_Interp_period(void)
{
    /* USER CODE BEGIN get_app_Interp_period */
    /* USER CODE END get_app_Interp_period */
    return kAppMotionInfo.Interp_period;
}

uint32_t set_app_Emergency_brake_requested(uint8_t val)
{
    /* USER CODE BEGIN set_app_Emergency_brake_requested 0 */
    /* USER CODE END set_app_Emergency_brake_requested 0 */
    kAppMotionInfo.Emergency_brake_requested = val;
    /* USER CODE BEGIN set_app_Emergency_brake_requested 1 */
    /* USER CODE END set_app_Emergency_brake_requested 1 */
    return APP_PARAM_SUCCESS;
}
uint8_t get_app_Emergency_brake_requested(void)
{
    /* USER CODE BEGIN get_app_Emergency_brake_requested */
    /* USER CODE END get_app_Emergency_brake_requested */
    return kAppMotionInfo.Emergency_brake_requested;
}

uint32_t set_app_Target_update_state(uint8_t val)
{
    /* USER CODE BEGIN set_app_Target_update_state 0 */
    /* USER CODE END set_app_Target_update_state 0 */
    kAppMotionInfo.Target_update_state = val;
    /* USER CODE BEGIN set_app_Target_update_state 1 */
    /* USER CODE END set_app_Target_update_state 1 */
    return APP_PARAM_SUCCESS;
}
uint8_t get_app_Target_update_state(void)
{
    /* USER CODE BEGIN get_app_Target_update_state */
    /* USER CODE END get_app_Target_update_state */
    return kAppMotionInfo.Target_update_state;
}

uint32_t set_app_Homing_step(int8_t val)
{
    /* USER CODE BEGIN set_app_Homing_step 0 */
    /* USER CODE END set_app_Homing_step 0 */
    kAppMotionInfo.Homing_step = val;
    /* USER CODE BEGIN set_app_Homing_step 1 */
    /* USER CODE END set_app_Homing_step 1 */
    return APP_PARAM_SUCCESS;
}
int8_t get_app_Homing_step(void)
{
    /* USER CODE BEGIN get_app_Homing_step */
    /* USER CODE END get_app_Homing_step */
    return kAppMotionInfo.Homing_step;
}

uint32_t set_app_Encoder_zero_crossing_state(uint8_t val)
{
    /* USER CODE BEGIN set_app_Encoder_zero_crossing_state 0 */
    /* USER CODE END set_app_Encoder_zero_crossing_state 0 */
    kAppMotionInfo.Encoder_zero_crossing_state = val;
    /* USER CODE BEGIN set_app_Encoder_zero_crossing_state 1 */
    /* USER CODE END set_app_Encoder_zero_crossing_state 1 */
    return APP_PARAM_SUCCESS;
}
uint8_t get_app_Encoder_zero_crossing_state(void)
{
    /* USER CODE BEGIN get_app_Encoder_zero_crossing_state */
    /* USER CODE END get_app_Encoder_zero_crossing_state */
    return kAppMotionInfo.Encoder_zero_crossing_state;
}

uint32_t set_app_Homing_state(int8_t val)
{
    /* USER CODE BEGIN set_app_Homing_state 0 */
    /* USER CODE END set_app_Homing_state 0 */
    kAppMotionInfo.Homing_state = val;
    /* USER CODE BEGIN set_app_Homing_state 1 */
    /* USER CODE END set_app_Homing_state 1 */
    return APP_PARAM_SUCCESS;
}
int8_t get_app_Homing_state(void)
{
    /* USER CODE BEGIN get_app_Homing_state */
    /* USER CODE END get_app_Homing_state */
    return kAppMotionInfo.Homing_state;
}

uint32_t set_app_Following_error_window(int64_t val)
{
    if (val < 0)
        return APP_PARAM_OUT_OF_RANGE;
    /* USER CODE BEGIN set_app_Following_error_window 0 */
    /* USER CODE END set_app_Following_error_window 0 */
    kAppWindowParam.Following_error_window = val;
    /* USER CODE BEGIN set_app_Following_error_window 1 */
    /* USER CODE END set_app_Following_error_window 1 */
    return APP_PARAM_SUCCESS;
}
int64_t get_app_Following_error_window(void)
{
    /* USER CODE BEGIN get_app_Following_error_window */
    /* USER CODE END get_app_Following_error_window */
    return kAppWindowParam.Following_error_window;
}

uint32_t set_app_Following_error_time_out(float val)
{
    if (val < 0.0)
        return APP_PARAM_OUT_OF_RANGE;
    /* USER CODE BEGIN set_app_Following_error_time_out 0 */
    /* USER CODE END set_app_Following_error_time_out 0 */
    kAppWindowParam.Following_error_time_out = val;
    /* USER CODE BEGIN set_app_Following_error_time_out 1 */
    /* USER CODE END set_app_Following_error_time_out 1 */
    return APP_PARAM_SUCCESS;
}
float get_app_Following_error_time_out(void)
{
    /* USER CODE BEGIN get_app_Following_error_time_out */
    /* USER CODE END get_app_Following_error_time_out */
    return kAppWindowParam.Following_error_time_out;
}

uint32_t set_app_Position_window(uint32_t val)
{
    if (val < 0)
        return APP_PARAM_OUT_OF_RANGE;
    /* USER CODE BEGIN set_app_Position_window 0 */
    /* USER CODE END set_app_Position_window 0 */
    kAppWindowParam.Position_window = val;
    /* USER CODE BEGIN set_app_Position_window 1 */
    /* USER CODE END set_app_Position_window 1 */
    return APP_PARAM_SUCCESS;
}
uint32_t get_app_Position_window(void)
{
    /* USER CODE BEGIN get_app_Position_window */
    /* USER CODE END get_app_Position_window */
    return kAppWindowParam.Position_window;
}

uint32_t set_app_Position_window_time(float val)
{
    if (val < 0.0)
        return APP_PARAM_OUT_OF_RANGE;
    /* USER CODE BEGIN set_app_Position_window_time 0 */
    /* USER CODE END set_app_Position_window_time 0 */
    kAppWindowParam.Position_window_time = val;
    /* USER CODE BEGIN set_app_Position_window_time 1 */
    /* USER CODE END set_app_Position_window_time 1 */
    return APP_PARAM_SUCCESS;
}
float get_app_Position_window_time(void)
{
    /* USER CODE BEGIN get_app_Position_window_time */
    /* USER CODE END get_app_Position_window_time */
    return kAppWindowParam.Position_window_time;
}

uint32_t set_app_Velocity_window(float val)
{
    if (val < 0.0)
        return APP_PARAM_OUT_OF_RANGE;
    /* USER CODE BEGIN set_app_Velocity_window 0 */
    /* USER CODE END set_app_Velocity_window 0 */
    kAppWindowParam.Velocity_window = val;
    /* USER CODE BEGIN set_app_Velocity_window 1 */
    /* USER CODE END set_app_Velocity_window 1 */
    return APP_PARAM_SUCCESS;
}
float get_app_Velocity_window(void)
{
    /* USER CODE BEGIN get_app_Velocity_window */
    /* USER CODE END get_app_Velocity_window */
    return kAppWindowParam.Velocity_window;
}

uint32_t set_app_Velocity_window_time(float val)
{
    if (val < 0.0)
        return APP_PARAM_OUT_OF_RANGE;
    /* USER CODE BEGIN set_app_Velocity_window_time 0 */
    /* USER CODE END set_app_Velocity_window_time 0 */
    kAppWindowParam.Velocity_window_time = val;
    /* USER CODE BEGIN set_app_Velocity_window_time 1 */
    /* USER CODE END set_app_Velocity_window_time 1 */
    return APP_PARAM_SUCCESS;
}
float get_app_Velocity_window_time(void)
{
    /* USER CODE BEGIN get_app_Velocity_window_time */
    /* USER CODE END get_app_Velocity_window_time */
    return kAppWindowParam.Velocity_window_time;
}

uint32_t set_app_Velocity_threshold(float val)
{
    if (val < 0.0)
        return APP_PARAM_OUT_OF_RANGE;
    /* USER CODE BEGIN set_app_Velocity_threshold 0 */
    /* USER CODE END set_app_Velocity_threshold 0 */
    kAppWindowParam.Velocity_threshold = val;
    /* USER CODE BEGIN set_app_Velocity_threshold 1 */
    /* USER CODE END set_app_Velocity_threshold 1 */
    return APP_PARAM_SUCCESS;
}
float get_app_Velocity_threshold(void)
{
    /* USER CODE BEGIN get_app_Velocity_threshold */
    /* USER CODE END get_app_Velocity_threshold */
    return kAppWindowParam.Velocity_threshold;
}

uint32_t set_app_Velocity_threshold_time(float val)
{
    if (val < 0.0)
        return APP_PARAM_OUT_OF_RANGE;
    /* USER CODE BEGIN set_app_Velocity_threshold_time 0 */
    /* USER CODE END set_app_Velocity_threshold_time 0 */
    kAppWindowParam.Velocity_threshold_time = val;
    /* USER CODE BEGIN set_app_Velocity_threshold_time 1 */
    /* USER CODE END set_app_Velocity_threshold_time 1 */
    return APP_PARAM_SUCCESS;
}
float get_app_Velocity_threshold_time(void)
{
    /* USER CODE BEGIN get_app_Velocity_threshold_time */
    /* USER CODE END get_app_Velocity_threshold_time */
    return kAppWindowParam.Velocity_threshold_time;
}

uint32_t set_app_Motor_rated_current(float val)
{
    if (val < 0.0)
        return APP_PARAM_OUT_OF_RANGE;
    /* USER CODE BEGIN set_app_Motor_rated_current 0 */
    if (axis->motor_ctl_sm_output.state == MOTOR_CTL_SM_MOTOR_ENABLE)
    {
        return APP_PARAM_WRITE_STATE_ERROR;
    }
    /* USER CODE END set_app_Motor_rated_current 0 */
    kAppMotorConfig.Motor_rated_current = val;
    /* USER CODE BEGIN set_app_Motor_rated_current 1 */
    axis->pmsm_config.rated_current = val * MATH_ARMS2APEAK;
    // 失能状态下调用，设置此参数时状态先由上位机限制
    MotorCtlParamSetUpdata(axis);
    /* USER CODE END set_app_Motor_rated_current 1 */
    return APP_PARAM_SUCCESS;
}
float get_app_Motor_rated_current(void)
{
    /* USER CODE BEGIN get_app_Motor_rated_current */
    /* USER CODE END get_app_Motor_rated_current */
    return kAppMotorConfig.Motor_rated_current;
}

uint32_t set_app_Motor_rated_torque(float val)
{
    if (val < 0.0)
        return APP_PARAM_OUT_OF_RANGE;
    /* USER CODE BEGIN set_app_Motor_rated_torque 0 */
    /* USER CODE END set_app_Motor_rated_torque 0 */
    kAppMotorConfig.Motor_rated_torque = val;
    /* USER CODE BEGIN set_app_Motor_rated_torque 1 */
    /* USER CODE END set_app_Motor_rated_torque 1 */
    return APP_PARAM_SUCCESS;
}
float get_app_Motor_rated_torque(void)
{
    /* USER CODE BEGIN get_app_Motor_rated_torque */
    /* USER CODE END get_app_Motor_rated_torque */
    return kAppMotorConfig.Motor_rated_torque;
}

uint32_t set_app_Motor_peak_current(float val)
{
    if (val < 0.0)
        return APP_PARAM_OUT_OF_RANGE;
    /* USER CODE BEGIN set_app_Motor_peak_current 0 */
    /* USER CODE END set_app_Motor_peak_current 0 */
    kAppMotorConfig.Motor_peak_current = val;
    /* USER CODE BEGIN set_app_Motor_peak_current 1 */
    app_param_restrictions_update();
    /* USER CODE END set_app_Motor_peak_current 1 */
    return APP_PARAM_SUCCESS;
}
float get_app_Motor_peak_current(void)
{
    /* USER CODE BEGIN get_app_Motor_peak_current */
    /* USER CODE END get_app_Motor_peak_current */
    return kAppMotorConfig.Motor_peak_current;
}

uint32_t set_app_Motor_pole_pairs(float val)
{
    if (val < 1.0)
        return APP_PARAM_OUT_OF_RANGE;
    /* USER CODE BEGIN set_app_Motor_pole_pairs 0 */
    if (axis->motor_ctl_sm_output.state == MOTOR_CTL_SM_MOTOR_ENABLE)
    {
        return APP_PARAM_WRITE_STATE_ERROR;
    }
    /* USER CODE END set_app_Motor_pole_pairs 0 */
    kAppMotorConfig.Motor_pole_pairs = val;
    /* USER CODE BEGIN set_app_Motor_pole_pairs 1 */
    axis->pmsm_config.pn = val;
    // 失能状态下调用，设置此参数时状态先由上位机限制
    MotorCtlParamSetUpdata(axis);
    /* USER CODE END set_app_Motor_pole_pairs 1 */
    return APP_PARAM_SUCCESS;
}
float get_app_Motor_pole_pairs(void)
{
    /* USER CODE BEGIN get_app_Motor_pole_pairs */
    kAppMotorConfig.Motor_pole_pairs = axis->pmsm_config.pn;
    /* USER CODE END get_app_Motor_pole_pairs */
    return kAppMotorConfig.Motor_pole_pairs;
}

uint32_t set_app_Motor_maximum_speed(float val)
{
    if (val < 0.0)
        return APP_PARAM_OUT_OF_RANGE;
    /* USER CODE BEGIN set_app_Motor_maximum_speed 0 */
    if (axis->motor_ctl_sm_output.state == MOTOR_CTL_SM_MOTOR_ENABLE)
    {
        return APP_PARAM_WRITE_STATE_ERROR;
    }
    /* USER CODE END set_app_Motor_maximum_speed 0 */
    kAppMotorConfig.Motor_maximum_speed = val;
    /* USER CODE BEGIN set_app_Motor_maximum_speed 1 */

    app_param_restrictions_update();

    axis->pmsm_config.speed_max_rpm = val;
    // 失能状态下调用，设置此参数时状态先由上位机限制
    MotorCtlParamSetUpdata(axis);
    /* USER CODE END set_app_Motor_maximum_speed 1 */
    return APP_PARAM_SUCCESS;
}
float get_app_Motor_maximum_speed(void)
{
    /* USER CODE BEGIN get_app_Motor_maximum_speed */
    /* USER CODE END get_app_Motor_maximum_speed */
    return kAppMotorConfig.Motor_maximum_speed;
}

uint32_t set_app_Resistance(float val)
{
    if (val < 0.0)
        return APP_PARAM_OUT_OF_RANGE;
    /* USER CODE BEGIN set_app_Resistance 0 */
    /* USER CODE END set_app_Resistance 0 */
    kAppMotorConfig.Resistance = val;
    /* USER CODE BEGIN set_app_Resistance 1 */
    axis->pmsm_config.r = val * 0.5f; // 控制层是定子电阻  相间电阻一半
    /* USER CODE END set_app_Resistance 1 */
    return APP_PARAM_SUCCESS;
}
float get_app_Resistance(void)
{
    /* USER CODE BEGIN get_app_Resistance */
    kAppMotorConfig.Resistance = axis->pmsm_config.r * 2.0f;
    /* USER CODE END get_app_Resistance */
    return kAppMotorConfig.Resistance;
}

uint32_t set_app_Inductance(float val)
{
    if (val < 0.0)
        return APP_PARAM_OUT_OF_RANGE;
    /* USER CODE BEGIN set_app_Inductance 0 */
    /* USER CODE END set_app_Inductance 0 */
    kAppMotorConfig.Inductance = val;
    /* USER CODE BEGIN set_app_Inductance 1 */
    axis->pmsm_config.ld = val * 0.5f;
    axis->pmsm_config.lq = val * 0.5f;
    /* USER CODE END set_app_Inductance 1 */
    return APP_PARAM_SUCCESS;
}
float get_app_Inductance(void)
{
    /* USER CODE BEGIN get_app_Inductance */
    kAppMotorConfig.Inductance = axis->pmsm_config.lq * 2.0f;
    /* USER CODE END get_app_Inductance */
    return kAppMotorConfig.Inductance;
}

uint32_t set_app_Reduction_ratio_num(uint32_t val)
{
    /* USER CODE BEGIN set_app_Reduction_ratio_num 0 */
    /* USER CODE END set_app_Reduction_ratio_num 0 */
    kAppMotorConfig.Reduction_ratio_num = val;
    /* USER CODE BEGIN set_app_Reduction_ratio_num 1 */
    SetGearNumerator(kAppMotorConfig.Reduction_ratio_num);  //设置64bit快速除法分子
    kAppMotorConfig.Reduction_ratio = (float)kAppMotorConfig.Reduction_ratio_num / (float)kAppMotorConfig.Reduction_ratio_den;
    kAppMotorConfig.Reduction_ratio_inv = 1.0f / kAppMotorConfig.Reduction_ratio;
    /* USER CODE END set_app_Reduction_ratio_num 1 */
    return APP_PARAM_SUCCESS;
}
uint32_t get_app_Reduction_ratio_num(void)
{
    /* USER CODE BEGIN get_app_Reduction_ratio_num */
    /* USER CODE END get_app_Reduction_ratio_num */
    return kAppMotorConfig.Reduction_ratio_num;
}

uint32_t set_app_Reduction_ratio_den(uint32_t val)
{
    /* USER CODE BEGIN set_app_Reduction_ratio_den 0 */
    /* USER CODE END set_app_Reduction_ratio_den 0 */
    kAppMotorConfig.Reduction_ratio_den = val;
    /* USER CODE BEGIN set_app_Reduction_ratio_den 1 */
    SetGearDenominator(kAppMotorConfig.Reduction_ratio_den);   //设置64bit快速除法分母 
    kAppMotorConfig.Reduction_ratio = (float)kAppMotorConfig.Reduction_ratio_num / (float)kAppMotorConfig.Reduction_ratio_den;
    kAppMotorConfig.Reduction_ratio_inv = 1.0f / kAppMotorConfig.Reduction_ratio;
    /* USER CODE END set_app_Reduction_ratio_den 1 */
    return APP_PARAM_SUCCESS;
}
uint32_t get_app_Reduction_ratio_den(void)
{
    /* USER CODE BEGIN get_app_Reduction_ratio_den */
    /* USER CODE END get_app_Reduction_ratio_den */
    return kAppMotorConfig.Reduction_ratio_den;
}

uint32_t set_app_Torque_constant(float val)
{
    if (val < 0.0)
        return APP_PARAM_OUT_OF_RANGE;
    /* USER CODE BEGIN set_app_Torque_constant 0 */
    /* USER CODE END set_app_Torque_constant 0 */
    kAppMotorConfig.Torque_constant = val;
    /* USER CODE BEGIN set_app_Torque_constant 1 */
    // 关联设置控制层参数
    axis->pmsm_config.kt = val * 0.001f;
    //转矩常数单独关联更新，因为用户在MIT模式下可能频繁修改KT参数
    // MotorCtlParamSetUpdata(axis);
    // 转矩常数和永磁磁链 关联更新 // kt = 1.5*pn*flux
    axis->pmsm_config.flux = axis->pmsm_config.kt / (1.5f * axis->pmsm_config.pn); // flux = kt/(1.5*pn);
    axis->pos_speed_ctl_config.j_kt = axis->pmsm_config.j / axis->pmsm_config.kt;
    axis->mit_ctl_config.kt_NM_A = axis->pmsm_config.kt; //关联设置

    /* USER CODE END set_app_Torque_constant 1 */
    return APP_PARAM_SUCCESS;
}
float get_app_Torque_constant(void)
{
    /* USER CODE BEGIN get_app_Torque_constant */
    /* USER CODE END get_app_Torque_constant */
    return kAppMotorConfig.Torque_constant;
}

uint32_t set_app_Reduction_ratio(float val)
{
    /* USER CODE BEGIN set_app_Reduction_ratio 0 */
    /* USER CODE END set_app_Reduction_ratio 0 */
    kAppMotorConfig.Reduction_ratio = val;

    return APP_PARAM_SUCCESS;
}
float get_app_Reduction_ratio(void)
{
    /* USER CODE BEGIN get_app_Reduction_ratio */
    /* USER CODE END get_app_Reduction_ratio */
    return kAppMotorConfig.Reduction_ratio;
}

uint32_t set_app_Reduction_ratio_inv(float val)
{
    /* USER CODE BEGIN set_app_Reduction_ratio_inv 0 */
    /* USER CODE END set_app_Reduction_ratio_inv 0 */
    kAppMotorConfig.Reduction_ratio_inv = val;

    return APP_PARAM_SUCCESS;
}
float get_app_Reduction_ratio_inv(void)
{
    /* USER CODE BEGIN get_app_Reduction_ratio_inv */
    /* USER CODE END get_app_Reduction_ratio_inv */
    return kAppMotorConfig.Reduction_ratio_inv;
}

uint32_t set_app_Motor_rotor_inertia(float val)
{
    if (val < 0.0)
        return APP_PARAM_OUT_OF_RANGE;
    /* USER CODE BEGIN set_app_Motor_rotor_inertia 0 */
    /* USER CODE END set_app_Motor_rotor_inertia 0 */
    kAppMotorConfig.Motor_rotor_inertia = val;
    /* USER CODE BEGIN set_app_Motor_rotor_inertia 1 */
    // 关联设置控制层参数
    axis->pmsm_config.j = val * 1e-4f;
    MotorCtlParamSetUpdata(axis);
    /* USER CODE END set_app_Motor_rotor_inertia 1 */
    return APP_PARAM_SUCCESS;
}
float get_app_Motor_rotor_inertia(void)
{
    /* USER CODE BEGIN get_app_Motor_rotor_inertia */
    /* USER CODE END get_app_Motor_rotor_inertia */
    return kAppMotorConfig.Motor_rotor_inertia;
}

uint32_t set_app_Bus_under_voltage_threshold(float val)
{
    if (val < 0.0)
        return APP_PARAM_OUT_OF_RANGE;
    /* USER CODE BEGIN set_app_Bus_under_voltage_threshold 0 */
    if (val > kAppProtectConfig.Bus_over_voltage_threshold)
    {
        return APP_PARAM_OUT_OF_RANGE;
    }

    /* USER CODE END set_app_Bus_under_voltage_threshold 0 */
    kAppProtectConfig.Bus_under_voltage_threshold = val;
    /* USER CODE BEGIN set_app_Bus_under_voltage_threshold 1 */
    /* USER CODE END set_app_Bus_under_voltage_threshold 1 */
    return APP_PARAM_SUCCESS;
}
float get_app_Bus_under_voltage_threshold(void)
{
    /* USER CODE BEGIN get_app_Bus_under_voltage_threshold */
    /* USER CODE END get_app_Bus_under_voltage_threshold */
    return kAppProtectConfig.Bus_under_voltage_threshold;
}

uint32_t set_app_Bus_over_voltage_threshold(float val)
{
    if (val < 0.0)
        return APP_PARAM_OUT_OF_RANGE;
    /* USER CODE BEGIN set_app_Bus_over_voltage_threshold 0 */
    if (val < kAppProtectConfig.Bus_under_voltage_threshold)
    {
        return APP_PARAM_OUT_OF_RANGE;
    }

    /* USER CODE END set_app_Bus_over_voltage_threshold 0 */
    kAppProtectConfig.Bus_over_voltage_threshold = val;
    /* USER CODE BEGIN set_app_Bus_over_voltage_threshold 1 */
    /* USER CODE END set_app_Bus_over_voltage_threshold 1 */
    return APP_PARAM_SUCCESS;
}
float get_app_Bus_over_voltage_threshold(void)
{
    /* USER CODE BEGIN get_app_Bus_over_voltage_threshold */
    /* USER CODE END get_app_Bus_over_voltage_threshold */
    return kAppProtectConfig.Bus_over_voltage_threshold;
}

uint32_t set_app_Drive_overload_current_duration(float val)
{
    if (val < 0.0)
        return APP_PARAM_OUT_OF_RANGE;
    /* USER CODE BEGIN set_app_Drive_overload_current_duration 0 */
    /* USER CODE END set_app_Drive_overload_current_duration 0 */
    kAppProtectConfig.Drive_overload_current_duration = val;
    /* USER CODE BEGIN set_app_Drive_overload_current_duration 1 */
    /* USER CODE END set_app_Drive_overload_current_duration 1 */
    return APP_PARAM_SUCCESS;
}
float get_app_Drive_overload_current_duration(void)
{
    /* USER CODE BEGIN get_app_Drive_overload_current_duration */
    /* USER CODE END get_app_Drive_overload_current_duration */
    return kAppProtectConfig.Drive_overload_current_duration;
}

uint32_t set_app_Drive_peak_current_duration(float val)
{
    if (val < 0.0)
        return APP_PARAM_OUT_OF_RANGE;
    /* USER CODE BEGIN set_app_Drive_peak_current_duration 0 */
    /* USER CODE END set_app_Drive_peak_current_duration 0 */
    kAppProtectConfig.Drive_peak_current_duration = val;
    /* USER CODE BEGIN set_app_Drive_peak_current_duration 1 */
    /* USER CODE END set_app_Drive_peak_current_duration 1 */
    return APP_PARAM_SUCCESS;
}
float get_app_Drive_peak_current_duration(void)
{
    /* USER CODE BEGIN get_app_Drive_peak_current_duration */
    /* USER CODE END get_app_Drive_peak_current_duration */
    return kAppProtectConfig.Drive_peak_current_duration;
}

uint32_t set_app_Drive_temperature_threshold_time(float val)
{
    if (val < 0.0)
        return APP_PARAM_OUT_OF_RANGE;
    /* USER CODE BEGIN set_app_Drive_temperature_threshold_time 0 */
    /* USER CODE END set_app_Drive_temperature_threshold_time 0 */
    kAppProtectConfig.Drive_temperature_threshold_time = val;
    /* USER CODE BEGIN set_app_Drive_temperature_threshold_time 1 */
    /* USER CODE END set_app_Drive_temperature_threshold_time 1 */
    return APP_PARAM_SUCCESS;
}
float get_app_Drive_temperature_threshold_time(void)
{
    /* USER CODE BEGIN get_app_Drive_temperature_threshold_time */
    /* USER CODE END get_app_Drive_temperature_threshold_time */
    return kAppProtectConfig.Drive_temperature_threshold_time;
}

uint32_t set_app_Drive_low_temperature_fault_threshold(float val)
{
    /* USER CODE BEGIN set_app_Drive_low_temperature_fault_threshold 0 */
    if (val > kAppProtectConfig.Drive_high_temperature_fault_threshold)
    {
        return APP_PARAM_OUT_OF_RANGE;
    }

    /* USER CODE END set_app_Drive_low_temperature_fault_threshold 0 */
    kAppProtectConfig.Drive_low_temperature_fault_threshold = val;
    /* USER CODE BEGIN set_app_Drive_low_temperature_fault_threshold 1 */
    /* USER CODE END set_app_Drive_low_temperature_fault_threshold 1 */
    return APP_PARAM_SUCCESS;
}
float get_app_Drive_low_temperature_fault_threshold(void)
{
    /* USER CODE BEGIN get_app_Drive_low_temperature_fault_threshold */
    /* USER CODE END get_app_Drive_low_temperature_fault_threshold */
    return kAppProtectConfig.Drive_low_temperature_fault_threshold;
}

uint32_t set_app_Drive_high_temperature_fault_threshold(float val)
{
    /* USER CODE BEGIN set_app_Drive_high_temperature_fault_threshold 0 */
    if (val < kAppProtectConfig.Drive_low_temperature_fault_threshold)
    {
        return APP_PARAM_OUT_OF_RANGE;
    }

    /* USER CODE END set_app_Drive_high_temperature_fault_threshold 0 */
    kAppProtectConfig.Drive_high_temperature_fault_threshold = val;
    /* USER CODE BEGIN set_app_Drive_high_temperature_fault_threshold 1 */
    /* USER CODE END set_app_Drive_high_temperature_fault_threshold 1 */
    return APP_PARAM_SUCCESS;
}
float get_app_Drive_high_temperature_fault_threshold(void)
{
    /* USER CODE BEGIN get_app_Drive_high_temperature_fault_threshold */
    /* USER CODE END get_app_Drive_high_temperature_fault_threshold */
    return kAppProtectConfig.Drive_high_temperature_fault_threshold;
}

uint32_t set_app_Overspeed_threshold(float val)
{
    if (val < 0.0)
        return APP_PARAM_OUT_OF_RANGE;
    /* USER CODE BEGIN set_app_Overspeed_threshold 0 */
    /* USER CODE END set_app_Overspeed_threshold 0 */
    kAppProtectConfig.Overspeed_threshold = val;
    /* USER CODE BEGIN set_app_Overspeed_threshold 1 */
    /* USER CODE END set_app_Overspeed_threshold 1 */
    return APP_PARAM_SUCCESS;
}
float get_app_Overspeed_threshold(void)
{
    /* USER CODE BEGIN get_app_Overspeed_threshold */
    /* USER CODE END get_app_Overspeed_threshold */
    return kAppProtectConfig.Overspeed_threshold;
}

uint32_t set_app_Drive_overcurrent_threshold(float val)
{
    if (val < 0.0)
        return APP_PARAM_OUT_OF_RANGE;
    /* USER CODE BEGIN set_app_Drive_overcurrent_threshold 0 */
    /* USER CODE END set_app_Drive_overcurrent_threshold 0 */
    kAppProtectConfig.Drive_overcurrent_threshold = val;
    /* USER CODE BEGIN set_app_Drive_overcurrent_threshold 1 */
    /* USER CODE END set_app_Drive_overcurrent_threshold 1 */
    return APP_PARAM_SUCCESS;
}
float get_app_Drive_overcurrent_threshold(void)
{
    /* USER CODE BEGIN get_app_Drive_overcurrent_threshold */
    /* USER CODE END get_app_Drive_overcurrent_threshold */
    return kAppProtectConfig.Drive_overcurrent_threshold;
}

uint32_t set_app_Protection_enable(uint32_t val)
{
    /* USER CODE BEGIN set_app_Protection_enable 0 */
    /* USER CODE END set_app_Protection_enable 0 */
    kAppProtectConfig.Protection_enable = val;
    /* USER CODE BEGIN set_app_Protection_enable 1 */
    /* USER CODE END set_app_Protection_enable 1 */
    return APP_PARAM_SUCCESS;
}
uint32_t get_app_Protection_enable(void)
{
    /* USER CODE BEGIN get_app_Protection_enable */
    /* USER CODE END get_app_Protection_enable */
    return kAppProtectConfig.Protection_enable;
}

uint32_t set_app_Motor_low_temperature_fault_threshold(float val)
{
    /* USER CODE BEGIN set_app_Motor_low_temperature_fault_threshold 0 */
    if (val > kAppProtectConfig.Motor_high_temperature_fault_threshold)
    {
        return APP_PARAM_OUT_OF_RANGE;
    }

    /* USER CODE END set_app_Motor_low_temperature_fault_threshold 0 */
    kAppProtectConfig.Motor_low_temperature_fault_threshold = val;
    /* USER CODE BEGIN set_app_Motor_low_temperature_fault_threshold 1 */
    /* USER CODE END set_app_Motor_low_temperature_fault_threshold 1 */
    return APP_PARAM_SUCCESS;
}
float get_app_Motor_low_temperature_fault_threshold(void)
{
    /* USER CODE BEGIN get_app_Motor_low_temperature_fault_threshold */
    /* USER CODE END get_app_Motor_low_temperature_fault_threshold */
    return kAppProtectConfig.Motor_low_temperature_fault_threshold;
}

uint32_t set_app_Motor_high_temperature_fault_threshold(float val)
{
    /* USER CODE BEGIN set_app_Motor_high_temperature_fault_threshold 0 */
    if (val < kAppProtectConfig.Motor_low_temperature_fault_threshold)
    {
        return APP_PARAM_OUT_OF_RANGE;
    }
    /* USER CODE END set_app_Motor_high_temperature_fault_threshold 0 */
    kAppProtectConfig.Motor_high_temperature_fault_threshold = val;
    /* USER CODE BEGIN set_app_Motor_high_temperature_fault_threshold 1 */
    /* USER CODE END set_app_Motor_high_temperature_fault_threshold 1 */
    return APP_PARAM_SUCCESS;
}
float get_app_Motor_high_temperature_fault_threshold(void)
{
    /* USER CODE BEGIN get_app_Motor_high_temperature_fault_threshold */
    /* USER CODE END get_app_Motor_high_temperature_fault_threshold */
    return kAppProtectConfig.Motor_high_temperature_fault_threshold;
}

uint32_t set_app_Can_timeout(float val)
{
    if (val < 0.0)
        return APP_PARAM_OUT_OF_RANGE;
    /* USER CODE BEGIN set_app_Can_timeout 0 */
    /* USER CODE END set_app_Can_timeout 0 */
    kAppProtectConfig.Can_timeout = val;
    /* USER CODE BEGIN set_app_Can_timeout 1 */
    /* USER CODE END set_app_Can_timeout 1 */
    return APP_PARAM_SUCCESS;
}
float get_app_Can_timeout(void)
{
    /* USER CODE BEGIN get_app_Can_timeout */
    /* USER CODE END get_app_Can_timeout */
    return kAppProtectConfig.Can_timeout;
}

uint32_t set_app_Motor_low_temperature_warning_threshold(float val)
{
    /* USER CODE BEGIN set_app_Motor_low_temperature_warning_threshold 0 */
    if (val > kAppProtectConfig.Motor_high_temperature_warning_threshold)
    {
        return APP_PARAM_OUT_OF_RANGE;
    }

    /* USER CODE END set_app_Motor_low_temperature_warning_threshold 0 */
    kAppProtectConfig.Motor_low_temperature_warning_threshold = val;
    /* USER CODE BEGIN set_app_Motor_low_temperature_warning_threshold 1 */
    /* USER CODE END set_app_Motor_low_temperature_warning_threshold 1 */
    return APP_PARAM_SUCCESS;
}
float get_app_Motor_low_temperature_warning_threshold(void)
{
    /* USER CODE BEGIN get_app_Motor_low_temperature_warning_threshold */
    /* USER CODE END get_app_Motor_low_temperature_warning_threshold */
    return kAppProtectConfig.Motor_low_temperature_warning_threshold;
}

uint32_t set_app_Motor_high_temperature_warning_threshold(float val)
{
    /* USER CODE BEGIN set_app_Motor_high_temperature_warning_threshold 0 */
    if (val < kAppProtectConfig.Motor_low_temperature_warning_threshold)
    {
        return APP_PARAM_OUT_OF_RANGE;
    }

    /* USER CODE END set_app_Motor_high_temperature_warning_threshold 0 */
    kAppProtectConfig.Motor_high_temperature_warning_threshold = val;
    /* USER CODE BEGIN set_app_Motor_high_temperature_warning_threshold 1 */
    /* USER CODE END set_app_Motor_high_temperature_warning_threshold 1 */
    return APP_PARAM_SUCCESS;
}
float get_app_Motor_high_temperature_warning_threshold(void)
{
    /* USER CODE BEGIN get_app_Motor_high_temperature_warning_threshold */
    /* USER CODE END get_app_Motor_high_temperature_warning_threshold */
    return kAppProtectConfig.Motor_high_temperature_warning_threshold;
}

uint32_t set_app_Mcu_temperature_threshold_time(float val)
{
    if (val < 0.0)
        return APP_PARAM_OUT_OF_RANGE;
    /* USER CODE BEGIN set_app_Mcu_temperature_threshold_time 0 */
    /* USER CODE END set_app_Mcu_temperature_threshold_time 0 */
    kAppProtectConfig.Mcu_temperature_threshold_time = val;
    /* USER CODE BEGIN set_app_Mcu_temperature_threshold_time 1 */
    /* USER CODE END set_app_Mcu_temperature_threshold_time 1 */
    return APP_PARAM_SUCCESS;
}
float get_app_Mcu_temperature_threshold_time(void)
{
    /* USER CODE BEGIN get_app_Mcu_temperature_threshold_time */
    /* USER CODE END get_app_Mcu_temperature_threshold_time */
    return kAppProtectConfig.Mcu_temperature_threshold_time;
}

uint32_t set_app_Mcu_low_temperature_fault_threshold(float val)
{
    /* USER CODE BEGIN set_app_Mcu_low_temperature_fault_threshold 0 */
    /* USER CODE END set_app_Mcu_low_temperature_fault_threshold 0 */
    kAppProtectConfig.Mcu_low_temperature_fault_threshold = val;
    /* USER CODE BEGIN set_app_Mcu_low_temperature_fault_threshold 1 */
    /* USER CODE END set_app_Mcu_low_temperature_fault_threshold 1 */
    return APP_PARAM_SUCCESS;
}
float get_app_Mcu_low_temperature_fault_threshold(void)
{
    /* USER CODE BEGIN get_app_Mcu_low_temperature_fault_threshold */
    /* USER CODE END get_app_Mcu_low_temperature_fault_threshold */
    return kAppProtectConfig.Mcu_low_temperature_fault_threshold;
}

uint32_t set_app_Mcu_high_temperature_fault_threshold(float val)
{
    /* USER CODE BEGIN set_app_Mcu_high_temperature_fault_threshold 0 */
    /* USER CODE END set_app_Mcu_high_temperature_fault_threshold 0 */
    kAppProtectConfig.Mcu_high_temperature_fault_threshold = val;
    /* USER CODE BEGIN set_app_Mcu_high_temperature_fault_threshold 1 */
    /* USER CODE END set_app_Mcu_high_temperature_fault_threshold 1 */
    return APP_PARAM_SUCCESS;
}
float get_app_Mcu_high_temperature_fault_threshold(void)
{
    /* USER CODE BEGIN get_app_Mcu_high_temperature_fault_threshold */
    /* USER CODE END get_app_Mcu_high_temperature_fault_threshold */
    return kAppProtectConfig.Mcu_high_temperature_fault_threshold;
}

uint32_t set_app_Mcu_low_temperature_warning_threshold(float val)
{
    /* USER CODE BEGIN set_app_Mcu_low_temperature_warning_threshold 0 */
    /* USER CODE END set_app_Mcu_low_temperature_warning_threshold 0 */
    kAppProtectConfig.Mcu_low_temperature_warning_threshold = val;
    /* USER CODE BEGIN set_app_Mcu_low_temperature_warning_threshold 1 */
    /* USER CODE END set_app_Mcu_low_temperature_warning_threshold 1 */
    return APP_PARAM_SUCCESS;
}
float get_app_Mcu_low_temperature_warning_threshold(void)
{
    /* USER CODE BEGIN get_app_Mcu_low_temperature_warning_threshold */
    /* USER CODE END get_app_Mcu_low_temperature_warning_threshold */
    return kAppProtectConfig.Mcu_low_temperature_warning_threshold;
}

uint32_t set_app_Mcu_high_temperature_warning_threshold(float val)
{
    /* USER CODE BEGIN set_app_Mcu_high_temperature_warning_threshold 0 */
    /* USER CODE END set_app_Mcu_high_temperature_warning_threshold 0 */
    kAppProtectConfig.Mcu_high_temperature_warning_threshold = val;
    /* USER CODE BEGIN set_app_Mcu_high_temperature_warning_threshold 1 */
    /* USER CODE END set_app_Mcu_high_temperature_warning_threshold 1 */
    return APP_PARAM_SUCCESS;
}
float get_app_Mcu_high_temperature_warning_threshold(void)
{
    /* USER CODE BEGIN get_app_Mcu_high_temperature_warning_threshold */
    /* USER CODE END get_app_Mcu_high_temperature_warning_threshold */
    return kAppProtectConfig.Mcu_high_temperature_warning_threshold;
}

uint32_t set_app_Drive_low_temperature_warning_threshold(float val)
{
    /* USER CODE BEGIN set_app_Drive_low_temperature_warning_threshold 0 */
    /* USER CODE END set_app_Drive_low_temperature_warning_threshold 0 */
    kAppProtectConfig.Drive_low_temperature_warning_threshold = val;
    /* USER CODE BEGIN set_app_Drive_low_temperature_warning_threshold 1 */
    /* USER CODE END set_app_Drive_low_temperature_warning_threshold 1 */
    return APP_PARAM_SUCCESS;
}
float get_app_Drive_low_temperature_warning_threshold(void)
{
    /* USER CODE BEGIN get_app_Drive_low_temperature_warning_threshold */
    /* USER CODE END get_app_Drive_low_temperature_warning_threshold */
    return kAppProtectConfig.Drive_low_temperature_warning_threshold;
}

uint32_t set_app_Drive_high_temperature_warning_threshold(float val)
{
    /* USER CODE BEGIN set_app_Drive_high_temperature_warning_threshold 0 */
    /* USER CODE END set_app_Drive_high_temperature_warning_threshold 0 */
    kAppProtectConfig.Drive_high_temperature_warning_threshold = val;
    /* USER CODE BEGIN set_app_Drive_high_temperature_warning_threshold 1 */
    /* USER CODE END set_app_Drive_high_temperature_warning_threshold 1 */
    return APP_PARAM_SUCCESS;
}
float get_app_Drive_high_temperature_warning_threshold(void)
{
    /* USER CODE BEGIN get_app_Drive_high_temperature_warning_threshold */
    /* USER CODE END get_app_Drive_high_temperature_warning_threshold */
    return kAppProtectConfig.Drive_high_temperature_warning_threshold;
}

uint32_t set_app_Comm_control_authority(uint8_t val)
{
    if (val < 0)
        return APP_PARAM_OUT_OF_RANGE;
    if (val > 1)
        return APP_PARAM_OUT_OF_RANGE;

    /* USER CODE BEGIN set_app_Comm_control_authority 0 */
    /* USER CODE END set_app_Comm_control_authority 0 */
    kAppPermissionConfig.Comm_control_authority = val;
    /* USER CODE BEGIN set_app_Comm_control_authority 1 */
    /* USER CODE END set_app_Comm_control_authority 1 */
    return APP_PARAM_SUCCESS;
}
uint8_t get_app_Comm_control_authority(void)
{
    /* USER CODE BEGIN get_app_Comm_control_authority */
    /* USER CODE END get_app_Comm_control_authority */
    return kAppPermissionConfig.Comm_control_authority;
}

uint32_t set_app_Internal_control_authority(uint8_t val)
{
    if (val < 0)
        return APP_PARAM_OUT_OF_RANGE;
    if (val > 1)
        return APP_PARAM_OUT_OF_RANGE;

    /* USER CODE BEGIN set_app_Internal_control_authority 0 */
    /* USER CODE END set_app_Internal_control_authority 0 */
    kAppPermissionConfig.Internal_control_authority = val;
    /* USER CODE BEGIN set_app_Internal_control_authority 1 */
    if (kAppPermissionConfig.Internal_control_authority == INTERNAL_CONTROL_CTRL)
    {
        kAxis.motor_ctl_sm_config.error_enable = 0xffff; // 使能控制层所有保护
    }
    if (kAppPermissionConfig.Internal_control_authority == INTERNAL_CONTROL_APP)
    {
        kAxis.motor_ctl_sm_config.error_enable = 0x0000; // 屏蔽控制层所有保护
    }
    /* USER CODE END set_app_Internal_control_authority 1 */
    return APP_PARAM_SUCCESS;
}
uint8_t get_app_Internal_control_authority(void)
{
    /* USER CODE BEGIN get_app_Internal_control_authority */
    /* USER CODE END get_app_Internal_control_authority */
    return kAppPermissionConfig.Internal_control_authority;
}

uint32_t set_app_Sys_cmd(uint8_t val)
{
    /* USER CODE BEGIN set_app_Sys_cmd 0 */
    /* USER CODE END set_app_Sys_cmd 0 */
    kSystemCmd.Sys_cmd = val;
    /* USER CODE BEGIN set_app_Sys_cmd 1 */
    switch (val)
    {
    case APP_SYSTEM_CMD_NONE:
        // Do nothing
        break;
    case APP_SYSTEM_CMD_HOMING:
        // 设置当前位置为系统零点
        // 负载端累计的绝对位置
        // 设置当前目标位置为0
        kAppBaseConfig.Home_position_offset_value = kAppMotionInfo.Position_actual_value_inc;
        set_app_Target_position(0);

        break;
    case APP_SYSTEM_CMD_SAVE_CONFIG:
        if (axis->motor_ctl_sm_output.state == MOTOR_CTL_SM_MOTOR_ENABLE)
        {
            set_app_Storage_status(FLASH_STORE_STATUS_WARNING);
            return APP_PARAM_WRITE_STATE_ERROR;
        }
        set_app_Storage_cmd(FLASH_STORE_CMD_WRITE_PARAM);
        break;
    case APP_SYSTEM_CMD_REBOOT:
        bsp_system_reset();
        break;
    case APP_SYSTEM_CMD_SAVE_TQ_FC_TABLE:
        if (axis->motor_ctl_sm_output.state == MOTOR_CTL_SM_MOTOR_ENABLE)
        {
            set_app_Storage_status(FLASH_STORE_STATUS_WARNING);
            return APP_PARAM_WRITE_STATE_ERROR;
        }
        set_app_Storage_cmd(FLASH_STORE_CMD_WRITE_TQ_FC);
        break;
    case APP_SYSTEM_CMD_TQ_FC_TABLE_CLEAR:
        if (axis->motor_ctl_sm_output.state == MOTOR_CTL_SM_MOTOR_ENABLE)
        {
            set_app_Storage_status(FLASH_STORE_STATUS_WARNING);
            return APP_PARAM_WRITE_STATE_ERROR;
        }
        set_app_Storage_cmd(FLASH_STORE_CMD_ERASE_TQ_FC);
        break;
    case APP_SYSTEM_CMD_ERROR_RECORD_CLEAR:
        if (axis->motor_ctl_sm_output.state == MOTOR_CTL_SM_MOTOR_ENABLE)
        {
            set_app_Storage_status(FLASH_STORE_STATUS_WARNING);
            return APP_PARAM_WRITE_STATE_ERROR;
        }
        set_app_Storage_cmd(FLASH_STORE_CMD_ERASE_ERROR);
        break;
    case APP_SYSTEM_CMD_FACTORY_RESET:
        if (axis->motor_ctl_sm_output.state == MOTOR_CTL_SM_MOTOR_ENABLE)
        {
            set_app_Storage_status(FLASH_STORE_STATUS_WARNING);
            return APP_PARAM_WRITE_STATE_ERROR;
        }
        set_app_Storage_cmd(FLASH_STORE_CMD_ERASE_PARAM);
        break;
    default:
        break;
    }

    /* USER CODE END set_app_Sys_cmd 1 */
    return APP_PARAM_SUCCESS;
}
uint8_t get_app_Sys_cmd(void)
{
    /* USER CODE BEGIN get_app_Sys_cmd */
    /* USER CODE END get_app_Sys_cmd */
    return kSystemCmd.Sys_cmd;
}

uint32_t set_app_Storage_status(int8_t val)
{
    /* USER CODE BEGIN set_app_Storage_status 0 */
    /* USER CODE END set_app_Storage_status 0 */
    kSystemStatus.Storage_status = val;
    /* USER CODE BEGIN set_app_Storage_status 1 */
    /* USER CODE END set_app_Storage_status 1 */
    return APP_PARAM_SUCCESS;
}
int8_t get_app_Storage_status(void)
{
    /* USER CODE BEGIN get_app_Storage_status */
    /* USER CODE END get_app_Storage_status */
    return kSystemStatus.Storage_status;
}

uint32_t set_app_Storage_cmd(uint8_t val)
{
    /* USER CODE BEGIN set_app_Storage_cmd 0 */
    /* USER CODE END set_app_Storage_cmd 0 */
    kSystemStatus.Storage_cmd = val;
    /* USER CODE BEGIN set_app_Storage_cmd 1 */
    /* USER CODE END set_app_Storage_cmd 1 */
    return APP_PARAM_SUCCESS;
}
uint8_t get_app_Storage_cmd(void)
{
    /* USER CODE BEGIN get_app_Storage_cmd */
    /* USER CODE END get_app_Storage_cmd */
    return kSystemStatus.Storage_cmd;
}

uint32_t set_app_Calibration_cmd(uint16_t val)
{
    /* USER CODE BEGIN set_app_Calibration_cmd 0 */
    /* USER CODE END set_app_Calibration_cmd 0 */
    kEncoderCalibrationCmd.Calibration_cmd = val;
    /* USER CODE BEGIN set_app_Calibration_cmd 1 */
    /* USER CODE END set_app_Calibration_cmd 1 */
    return APP_PARAM_SUCCESS;
}
uint16_t get_app_Calibration_cmd(void)
{
    /* USER CODE BEGIN get_app_Calibration_cmd */
    /* USER CODE END get_app_Calibration_cmd */
    return kEncoderCalibrationCmd.Calibration_cmd;
}

uint32_t set_app_Calibration_time(uint16_t val)
{
    if (val < 1)
        return APP_PARAM_OUT_OF_RANGE;
    /* USER CODE BEGIN set_app_Calibration_time 0 */
    /* USER CODE END set_app_Calibration_time 0 */
    kEncoderCalibrationCmd.Calibration_time = val;
    /* USER CODE BEGIN set_app_Calibration_time 1 */
    /* USER CODE END set_app_Calibration_time 1 */
    return APP_PARAM_SUCCESS;
}
uint16_t get_app_Calibration_time(void)
{
    /* USER CODE BEGIN get_app_Calibration_time */
    /* USER CODE END get_app_Calibration_time */
    return kEncoderCalibrationCmd.Calibration_time;
}

uint32_t set_app_Calibration_status(uint16_t val)
{
    /* USER CODE BEGIN set_app_Calibration_status 0 */
    /* USER CODE END set_app_Calibration_status 0 */
    kEncoderCalibrationStatus.Calibration_status = val;
    /* USER CODE BEGIN set_app_Calibration_status 1 */
    /* USER CODE END set_app_Calibration_status 1 */
    return APP_PARAM_SUCCESS;
}
uint16_t get_app_Calibration_status(void)
{
    /* USER CODE BEGIN get_app_Calibration_status */
    /* USER CODE END get_app_Calibration_status */
    return kEncoderCalibrationStatus.Calibration_status;
}

uint32_t set_app_User_module_code(uint64_t val)
{
    /* USER CODE BEGIN set_app_User_module_code 0 */
    /* USER CODE END set_app_User_module_code 0 */
    kCustomInfo.User_module_code = val;

    return APP_PARAM_SUCCESS;
}
uint64_t get_app_User_module_code(void)
{
    /* USER CODE BEGIN get_app_User_module_code */
    /* USER CODE END get_app_User_module_code */
    return kCustomInfo.User_module_code;
}

uint32_t set_app_Sys_init_flag(uint8_t val)
{
    /* USER CODE BEGIN set_app_Sys_init_flag 0 */
    /* USER CODE END set_app_Sys_init_flag 0 */
    kHeartBit.Sys_init_flag = val;
    /* USER CODE BEGIN set_app_Sys_init_flag 1 */
    /* USER CODE END set_app_Sys_init_flag 1 */
    return APP_PARAM_SUCCESS;
}
uint8_t get_app_Sys_init_flag(void)
{
    /* USER CODE BEGIN get_app_Sys_init_flag */
    /* USER CODE END get_app_Sys_init_flag */
    return kHeartBit.Sys_init_flag;
}

uint32_t set_app_Error_records_list(uint32_t index, uint32_t val)
{
    /* USER CODE BEGIN set_app_Error_records_list 0 */
    /* USER CODE END set_app_Error_records_list 0 */
    kHistoricalInfo.Error_records_list[index] = val;

    return APP_PARAM_SUCCESS;
}
uint32_t get_app_Error_records_list(uint32_t index)
{
    /* USER CODE BEGIN get_app_Error_records_list */
    /* USER CODE END get_app_Error_records_list */
    return kHistoricalInfo.Error_records_list[index];
}

uint32_t* get_app_Error_records_list_addr(void)
{
    /* USER CODE BEGIN get_app_Error_records_list_addr */
    /* USER CODE END get_app_Error_records_list_addr */
    return kHistoricalInfo.Error_records_list;
}

uint32_t set_app_Debug_float(uint32_t index, float val)
{
    /* USER CODE BEGIN set_app_Debug_float 0 */
    /* USER CODE END set_app_Debug_float 0 */
    kAppDebugParam.Debug_float[index] = val;
    /* USER CODE BEGIN set_app_Debug_float 1 */
    /* USER CODE END set_app_Debug_float 1 */
    return APP_PARAM_SUCCESS;
}
float get_app_Debug_float(uint32_t index)
{
    /* USER CODE BEGIN get_app_Debug_float */
    /* USER CODE END get_app_Debug_float */
    return kAppDebugParam.Debug_float[index];
}

float* get_app_Debug_float_addr(void)
{
    /* USER CODE BEGIN get_app_Debug_float_addr */
    /* USER CODE END get_app_Debug_float_addr */
    return kAppDebugParam.Debug_float;
}

uint32_t set_app_Debug_uint32(uint32_t index, uint32_t val)
{
    /* USER CODE BEGIN set_app_Debug_uint32 0 */
    /* USER CODE END set_app_Debug_uint32 0 */
    kAppDebugParam.Debug_uint32[index] = val;
    /* USER CODE BEGIN set_app_Debug_uint32 1 */
    /* USER CODE END set_app_Debug_uint32 1 */
    return APP_PARAM_SUCCESS;
}
uint32_t get_app_Debug_uint32(uint32_t index)
{
    /* USER CODE BEGIN get_app_Debug_uint32 */
    /* USER CODE END get_app_Debug_uint32 */
    return kAppDebugParam.Debug_uint32[index];
}

uint32_t* get_app_Debug_uint32_addr(void)
{
    /* USER CODE BEGIN get_app_Debug_uint32_addr */
    /* USER CODE END get_app_Debug_uint32_addr */
    return kAppDebugParam.Debug_uint32;
}

uint32_t set_app_Debug_int32(uint32_t index, int32_t val)
{
    /* USER CODE BEGIN set_app_Debug_int32 0 */
    /* USER CODE END set_app_Debug_int32 0 */
    kAppDebugParam.Debug_int32[index] = val;
    /* USER CODE BEGIN set_app_Debug_int32 1 */
    /* USER CODE END set_app_Debug_int32 1 */
    return APP_PARAM_SUCCESS;
}
int32_t get_app_Debug_int32(uint32_t index)
{
    /* USER CODE BEGIN get_app_Debug_int32 */
    /* USER CODE END get_app_Debug_int32 */
    return kAppDebugParam.Debug_int32[index];
}

int32_t* get_app_Debug_int32_addr(void)
{
    /* USER CODE BEGIN get_app_Debug_int32_addr */
    /* USER CODE END get_app_Debug_int32_addr */
    return kAppDebugParam.Debug_int32;
}

uint32_t set_app_Sys_id(uint8_t val)
{
    /* USER CODE BEGIN set_app_Sys_id 0 */
    /* USER CODE END set_app_Sys_id 0 */
    kAppMavlinkConfig.Sys_id = val;
    /* USER CODE BEGIN set_app_Sys_id 1 */
    bsp_set_can_mav_id(val, get_app_Comp_id());
    /* USER CODE END set_app_Sys_id 1 */
    return APP_PARAM_SUCCESS;
}
uint8_t get_app_Sys_id(void)
{
    /* USER CODE BEGIN get_app_Sys_id */
    bsp_get_can_mav_id(&kAppMavlinkConfig.Sys_id, &kAppMavlinkConfig.Comp_id);
    /* USER CODE END get_app_Sys_id */
    return kAppMavlinkConfig.Sys_id;
}

uint32_t set_app_Comp_id(uint8_t val)
{
    /* USER CODE BEGIN set_app_Comp_id 0 */
    /* USER CODE END set_app_Comp_id 0 */
    kAppMavlinkConfig.Comp_id = val;
    /* USER CODE BEGIN set_app_Comp_id 1 */
    bsp_set_can_mav_id(get_app_Sys_id(), val);
    /* USER CODE END set_app_Comp_id 1 */
    return APP_PARAM_SUCCESS;
}
uint8_t get_app_Comp_id(void)
{
    /* USER CODE BEGIN get_app_Comp_id */
    bsp_get_can_mav_id(&kAppMavlinkConfig.Sys_id, &kAppMavlinkConfig.Comp_id);
    /* USER CODE END get_app_Comp_id */
    return kAppMavlinkConfig.Comp_id;
}

uint32_t set_app_File_type(uint8_t val)
{
    /* USER CODE BEGIN set_app_File_type 0 */
    /* USER CODE END set_app_File_type 0 */
    kAppFileTransferConfig.File_type = val;
    /* USER CODE BEGIN set_app_File_type 1 */
    bsp_set_file_transfer_config(val, get_app_File_size(), get_app_File_direction());
    /* USER CODE END set_app_File_type 1 */
    return APP_PARAM_SUCCESS;
}
uint8_t get_app_File_type(void)
{
    /* USER CODE BEGIN get_app_File_type */
    /* USER CODE END get_app_File_type */
    return kAppFileTransferConfig.File_type;
}

uint32_t set_app_File_size(uint32_t val)
{
    /* USER CODE BEGIN set_app_File_size 0 */
    /* USER CODE END set_app_File_size 0 */
    kAppFileTransferConfig.File_size = val;
    /* USER CODE BEGIN set_app_File_size 1 */
    bsp_set_file_transfer_config(get_app_File_type(), val, get_app_File_direction());
    /* USER CODE END set_app_File_size 1 */
    return APP_PARAM_SUCCESS;
}
uint32_t get_app_File_size(void)
{
    /* USER CODE BEGIN get_app_File_size */
    /* USER CODE END get_app_File_size */
    return kAppFileTransferConfig.File_size;
}

uint32_t set_app_File_direction(uint8_t val)
{
    /* USER CODE BEGIN set_app_File_direction 0 */
    /* USER CODE END set_app_File_direction 0 */
    kAppFileTransferConfig.File_direction = val;
    /* USER CODE BEGIN set_app_File_direction 1 */
    bsp_set_file_transfer_config(get_app_File_type(), get_app_File_size(), val);
    /* USER CODE END set_app_File_direction 1 */
    return APP_PARAM_SUCCESS;
}
uint8_t get_app_File_direction(void)
{
    /* USER CODE BEGIN get_app_File_direction */
    /* USER CODE END get_app_File_direction */
    return kAppFileTransferConfig.File_direction;
}

uint32_t set_app_File_index_complete(uint32_t val)
{
    /* USER CODE BEGIN set_app_File_index_complete 0 */
    /* USER CODE END set_app_File_index_complete 0 */
    kAppFileTransferConfig.File_index_complete = val;
    /* USER CODE BEGIN set_app_File_index_complete 1 */
    /* USER CODE END set_app_File_index_complete 1 */
    return APP_PARAM_SUCCESS;
}
uint32_t get_app_File_index_complete(void)
{
    /* USER CODE BEGIN get_app_File_index_complete */
    APP_FILE_TYPE file_type = (APP_FILE_TYPE)get_app_File_type();
    if (file_type == APP_FILE_TYPE_FIRMWARE)
    {
        kAppFileTransferConfig.File_index_complete = bsp_get_fw_file_index_complete();
    }
    /* USER CODE END get_app_File_index_complete */
    return kAppFileTransferConfig.File_index_complete;
}

uint32_t set_app_File_status(int8_t val)
{
    /* USER CODE BEGIN set_app_File_status 0 */
    /* USER CODE END set_app_File_status 0 */
    kAppFileTransferConfig.File_status = val;
    /* USER CODE BEGIN set_app_File_status 1 */
    /* USER CODE END set_app_File_status 1 */
    return APP_PARAM_SUCCESS;
}
int8_t get_app_File_status(void)
{
    /* USER CODE BEGIN get_app_File_status */
    APP_FILE_TYPE file_type = (APP_FILE_TYPE)get_app_File_type();
    if (file_type == APP_FILE_TYPE_FIRMWARE)
    {
        kAppFileTransferConfig.File_status = bsp_get_fw_file_status();
    }
    /* USER CODE END get_app_File_status */
    return kAppFileTransferConfig.File_status;
}

uint32_t set_app_Fw_mode(uint8_t val)
{
    /* USER CODE BEGIN set_app_Fw_mode 0 */
    /* USER CODE END set_app_Fw_mode 0 */
    kAppFwUpgradeParam.Fw_mode = val;
    /* USER CODE BEGIN set_app_Fw_mode 1 */
    bsp_set_fw_upgrade_config(val);
    /* USER CODE END set_app_Fw_mode 1 */
    return APP_PARAM_SUCCESS;
}
uint8_t get_app_Fw_mode(void)
{
    /* USER CODE BEGIN get_app_Fw_mode */
    /* USER CODE END get_app_Fw_mode */
    return kAppFwUpgradeParam.Fw_mode;
}

uint32_t set_app_Fw_app_index(uint8_t val)
{
    /* USER CODE BEGIN set_app_Fw_app_index 0 */
    /* USER CODE END set_app_Fw_app_index 0 */
    kAppFwUpgradeParam.Fw_app_index = val;
    /* USER CODE BEGIN set_app_Fw_app_index 1 */
    /* USER CODE END set_app_Fw_app_index 1 */
    return APP_PARAM_SUCCESS;
}
uint8_t get_app_Fw_app_index(void)
{
    /* USER CODE BEGIN get_app_Fw_app_index */
    /* USER CODE END get_app_Fw_app_index */
    return kAppFwUpgradeParam.Fw_app_index;
}

uint32_t set_app_Fw_flash_size(uint32_t val)
{
    /* USER CODE BEGIN set_app_Fw_flash_size 0 */
    /* USER CODE END set_app_Fw_flash_size 0 */
    kAppFwUpgradeParam.Fw_flash_size = val;
    /* USER CODE BEGIN set_app_Fw_flash_size 1 */
    /* USER CODE END set_app_Fw_flash_size 1 */
    return APP_PARAM_SUCCESS;
}
uint32_t get_app_Fw_flash_size(void)
{
    /* USER CODE BEGIN get_app_Fw_flash_size */
    /* USER CODE END get_app_Fw_flash_size */
    return kAppFwUpgradeParam.Fw_flash_size;
}

uint32_t set_app_Fw_operating_steps(int8_t val)
{
    /* USER CODE BEGIN set_app_Fw_operating_steps 0 */
    /* USER CODE END set_app_Fw_operating_steps 0 */
    kAppFwUpgradeParam.Fw_operating_steps = val;
    /* USER CODE BEGIN set_app_Fw_operating_steps 1 */
    /* USER CODE END set_app_Fw_operating_steps 1 */
    return APP_PARAM_SUCCESS;
}
int8_t get_app_Fw_operating_steps(void)
{
    /* USER CODE BEGIN get_app_Fw_operating_steps */
    kAppFwUpgradeParam.Fw_operating_steps = bsp_get_fw_operating_steps();
    /* USER CODE END get_app_Fw_operating_steps */
    return kAppFwUpgradeParam.Fw_operating_steps;
}


/* USER CODE BEGIN AREA 1 */
/* USER CODE END AREA 1 */

