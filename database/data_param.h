#pragma once

#include <stdint.h>

/* USER CODE BEGIN AREA 0 */
#include "data_type_define.h"
#include "bsp_api.h"

#include "version.h"

typedef enum
{
    APP_SYSTEM_CMD_NONE = 0,                    // 无指令
    APP_SYSTEM_CMD_HOMING = 1,                  // 当前位置回零
    APP_SYSTEM_CMD_SAVE_CONFIG = 2,             // 保存参数到FLASH
    APP_SYSTEM_CMD_REBOOT = 3,                  // 重启系统
    APP_SYSTEM_CMD_SAVE_TQ_FC_TABLE = 4,        // 保存转矩脉动摩擦补偿表到FLASH
    //...
    APP_SYSTEM_CMD_TQ_FC_TABLE_CLEAR = 253,     // 清除转矩脉动摩擦补偿表
    APP_SYSTEM_CMD_ERROR_RECORD_CLEAR = 254,    // 清除错误记录
    APP_SYSTEM_CMD_FACTORY_RESET = 255,         // 恢复出厂设置
} APP_SYSTEM_CMD;

typedef enum
{
    APP_PARAM_SUCCESS = 0,              //参数设置成功
    APP_PARAM_READ_ONLY = 1,            //参数只读
    APP_PARAM_OUT_OF_RANGE = 2,         //参数超出范围
    APP_PARAM_WRITE_STATE_ERROR = 3,    //参数写入状态错误，不能在电机使能状态下写入
} APP_PARAM_STATUS;

void AppParamInit(void);
/* USER CODE END AREA 0 */

typedef struct
{
    uint16_t Controlword; //控制字
    uint8_t Halt_running_cmd; //运行中暂停控制命令
}AppControlWord;

typedef struct
{
    uint32_t Statusword; //状态字
    uint32_t Error_word; //错误字
    float DC_link_circuit_voltage; //母线电压当前值
    float Drive_accumulated_heat; //驱动器热量累计值
    float Drive_temperature; //驱动器当前温度
    uint32_t Alarm_word; //告警字
    int8_t Modes_of_operation_display; //当前模式
    uint32_t Version; //软件版本
    float Motor_temperature; //电机当前温度
    float Motor_power; //电机当前功率
    float Mcu_temperature; //Mcu当前温度
    uint32_t Digital_io_inputs_status; //数字IO输入状态
    uint8_t Brake_state; //抱闸状态
}AppStatusInfo;

typedef struct
{
    int8_t Modes_of_operation; //运行模式
}AppOpMode;

typedef struct
{
    uint32_t Load_encoder_resolution; //负载端位置反馈分辨率
    uint32_t Motor_encoder_resolution; //电机端位置反馈分辨率
    uint8_t Motor_encoder_type; //电机端编码器类型
    uint8_t Load_encoder_type; //负载端编码器类型
    uint8_t Motor_encoder_options; //电机端编码器选项
    float Load_pps_2_rpm; //负载端指令RPM转换系数
    float Load_rpm_2_pps; //负载端指令pps转换系数
    float Motor_pps_2_rpm; //电机端指令RPM转换系数
    float Motor_rpm_2_pps; //电机端指令pps转换系数
    float P_load_2_motor; //负载端到电机端P转换系数
    float P_motor_2_load; //电机端到负载端P转换系数
    uint32_t Load_control_resolution; //负载端控制位置分辨率
    uint32_t Motor_control_resolution; //电机端控制位置分辨率
    uint8_t Load_encoder_options; //负载端编码器选项
}AppEncoderConfig;

typedef struct
{
    uint8_t Polarity; //运动极性
    int64_t Home_position_offset_value; //回零完成位置偏移值
    uint32_t Can_id; //CAN ID
    uint32_t Can_baudrate; //CAN 波特率
    int16_t Quick_stop_option_code; //快速停机方式选择
    float Brake_engage_time; //抱闸动作时间
    float Brake_release_time; //松闸动作时间
    float Dynamic_brake_speed_threshold; //抱闸制动速度阈值
    float Brake_release_hold_voltage; //松闸保持电压
    uint32_t Digital_io_outputs_phys; //数字IO输出物理值
    uint32_t Digital_io_outputs_mask; //数字IO输出掩码
    uint8_t Brake_control_mode; //抱闸控制模式
    float Brake_rated_voltage; //抱闸器额定电压
    float Brake_release_action_voltage; //松闸动作电压
    uint16_t Brake_release_pwm_freq; //松闸PWM频率
    float Brake_engage_delay_time; //抱闸延迟时间
    float Brake_release_delay_time; //松闸延迟时间
}AppBaseConfig;

typedef struct
{
    int64_t Target_position; //位置目标值
    float Profile_velocity; //轮廓速度
    float Profile_acceleration; //轮廓加速度
    float Profile_deceleration; //轮廓减速度
    float Quick_stop_deceleration; //快速停止减速度
    int32_t Motion_profile_type; //运动轮廓模式
    int64_t Home_offset; //回零偏移
    int8_t Homing_method; //回零方法
    float Target_velocity; //速度目标值
    float Target_torque; //力矩目标值
    float Torque_slope; //力矩上升斜率
    float Encoder_calibration_speed; //编码器校准速度
    float MIT_feedforward_torque; //MIT前馈力矩
    int64_t MIT_target_position; //MIT目标位置
    float MIT_max_current; //MIT最大输出电流
    float MIT_target_velocity; //MIT目标速度
    float MIT_kp; //位置刚度
    float MIT_kd; //速度阻尼系数
    uint8_t Interp_time_value; //插值时间基数
    int8_t Interp_time_index; //插值时间指数
    float Homing_speed_search_for_switch; //回零搜索开关速度
    float Homing_speed_search_for_zero; //回零搜索零点速度
    float Homing_acceleration; //回零加速度
}AppMotionParam;

typedef struct
{
    int64_t Position_range_limit_Minimal_position_limit; //位置溢出最小值
    int64_t Position_range_limit_Maximal_position_limit; //位置溢出最大值
    int64_t Software_position_limit_Minimal_position_limit; //应用位置下限
    int64_t Software_position_limit_Maximal_position_limit; //应用位置上限
    float Max_profile_velocity; //应用速度限制
    float Max_motor_speed; //电机最大转速
    float Max_acceleration; //应用加速度限制
    float Max_deceleration; //应用减速度限制
    float Max_current; //应用电流限制
    uint8_t Position_limit_enable; //位置限位使能开关
}AppRestrictParam;

typedef struct
{
    int64_t Position_demand_value; //负载端位置指令值
    int64_t Position_actual_value_inc; //负载端内部位置当前值
    int64_t Position_actual_value; //负载端位置当前值
    int64_t Following_error_actual_value; //负载端位置误差值
    float Velocity_demand_value; //负载端速度指令值
    float Velocity_actual_value; //负载端速度当前值
    float Torque_demand_value; //力矩指令值
    float Torque_actual_value; //力矩当前值
    float Current_actual_value; //电流当前值
    float D_current_actual_value; //d轴电流当前值
    float U_current_actual_value; //U相当前电流
    float V_current_actual_value; //V相当前电流
    float W_current_actual_value; //W相当前电流
    int64_t Motor_position_demand_value; //电机端位置指令值
    int64_t Motor_position_actual_value; //电机端位置当前值
    int64_t Motor_following_error_actual_value; //电机端位置误差值
    float Motor_velocity_demand_value; //电机端速度指令值
    float Motor_velocity_actual_value; //电机端速度当前值
    uint16_t U_adc_mid_val; //U相电流校准值
    uint16_t V_adc_mid_val; //V相电流校准值
    uint16_t W_adc_mid_val; //W相电流校准值
    float Current_loop_time; //电流环耗时
    float Position_loop_time; //位置环耗时
    float Current_loop_cycle; //电流环周期
    float Position_loop_cycle; //位置环周期
    float Interp_period; //插值时间周期
    uint8_t Emergency_brake_requested; //紧急制动请求值
    uint8_t Target_update_state; //目标值更新状态
    int8_t Homing_step; //回零步骤
    uint8_t Encoder_zero_crossing_state; //编码器过零点状态
    int8_t Homing_state; //回零状态
}AppMotionInfo;

typedef struct
{
    int64_t Following_error_window; //位置跟随误差阈值
    float Following_error_time_out; //位置跟随误差阈值时间
    uint32_t Position_window; //位置到达检测窗口
    float Position_window_time; //位置到达检测窗口时间
    float Velocity_window; //速度到达检测窗口
    float Velocity_window_time; //速度到达检测窗口时间
    float Velocity_threshold; //零速检测窗口
    float Velocity_threshold_time; //零速检测窗口时间
}AppWindowParam;

typedef struct
{
    float Motor_rated_current; //电机额定电流
    float Motor_rated_torque; //电机额定力矩
    float Motor_peak_current; //电机峰值电流
    float Motor_pole_pairs; //电机极对数
    float Motor_maximum_speed; //电机最大转速
    float Resistance; //电机相间电阻
    float Inductance; //电机相间电感
    uint32_t Reduction_ratio_num; //减速比分子
    uint32_t Reduction_ratio_den; //减速比分母
    float Torque_constant; //电机转矩常数
    float Reduction_ratio; //减速比系数
    float Reduction_ratio_inv; //减速比系数倒数
    float Motor_rotor_inertia; //电机转子惯量
}AppMotorConfig;

typedef struct
{
    float Bus_under_voltage_threshold; //母线欠压阈值
    float Bus_over_voltage_threshold; //母线过压阈值
    float Drive_overload_current_duration; //驱动器过载持续时间
    float Drive_peak_current_duration; //驱动器峰值电流持续时间
    float Drive_temperature_threshold_time; //驱动器温度保护阈值时间
    float Drive_low_temperature_fault_threshold; //驱动器低温报错阈值
    float Drive_high_temperature_fault_threshold; //驱动器高温报错阈值
    float Overspeed_threshold; //过速阈值
    float Drive_overcurrent_threshold; //驱动器过流保护阈值
    uint32_t Protection_enable; //保护生效
    float Motor_low_temperature_fault_threshold; //电机低温报错阈值
    float Motor_high_temperature_fault_threshold; //电机高温报错阈值
    float Can_timeout; //CAN通讯超时时间
    float Motor_low_temperature_warning_threshold; //电机低温警告阈值
    float Motor_high_temperature_warning_threshold; //电机高温警告阈值
    float Mcu_temperature_threshold_time; //MCU温度保护阈值时间
    float Mcu_low_temperature_fault_threshold; //MCU低温报错阈值
    float Mcu_high_temperature_fault_threshold; //MCU高温报错阈值
    float Mcu_low_temperature_warning_threshold; //MCU低温警告阈值
    float Mcu_high_temperature_warning_threshold; //MCU高温警告阈值
    float Drive_low_temperature_warning_threshold; //驱动器低温警告阈值
    float Drive_high_temperature_warning_threshold; //驱动器高温警告阈值
}AppProtectConfig;

typedef struct
{
    uint8_t Comm_control_authority; //通信控制权限
    uint8_t Internal_control_authority; //内部控制权限切换
}AppPermissionConfig;

typedef struct
{
    uint8_t Sys_cmd; //系统指令
}SystemCmd;

typedef struct
{
    int8_t Storage_status; //参数存储状态
    uint8_t Storage_cmd; //Flash存储命令
}SystemStatus;

typedef struct
{
    uint16_t Calibration_cmd; //编码器校准控制字
    uint16_t Calibration_time; //校准时间
}EncoderCalibrationCmd;

typedef struct
{
    uint16_t Calibration_status; //编码器校准状态字
}EncoderCalibrationStatus;

typedef struct
{
    uint64_t User_module_code; //用户模型编码
}CustomInfo;

typedef struct
{
    uint8_t Sys_init_flag; //系统初始化标志位
}HeartBit;

typedef struct
{
    uint32_t Error_records_list[16]; //错误记录表单
}HistoricalInfo;

typedef struct
{
    float Debug_float[16]; //临时debug变量 float 类型
    uint32_t Debug_uint32[16]; //临时debug变量 uint32 类型
    int32_t Debug_int32[16]; //临时debug变量 int32 类型
}AppDebugParam;

typedef struct
{
    uint8_t Sys_id; //mavlink系统ID
    uint8_t Comp_id; //mavlink组件ID
}AppMavlinkConfig;

typedef struct
{
    uint8_t File_type; //文件传输类型
    uint32_t File_size; //文件传输大小
    uint8_t File_direction; //文件传输方向
    uint32_t File_index_complete; //文件传输完成帧索引
    int8_t File_status; //文件传输状态
}AppFileTransferConfig;

typedef struct
{
    uint8_t Fw_mode; //固件传输模式
    uint8_t Fw_app_index; //固件传输APP分区
    uint32_t Fw_flash_size; //固件存储空间大小
    int8_t Fw_operating_steps; //固件当前操作步骤（状态）
}AppFwUpgradeParam;

uint32_t set_app_Controlword(uint16_t val);
uint16_t get_app_Controlword(void);

uint32_t set_app_Statusword(uint32_t val);
uint32_t get_app_Statusword(void);

uint32_t set_app_Error_word(uint32_t val);
uint32_t get_app_Error_word(void);

uint32_t set_app_Modes_of_operation(int8_t val);
int8_t get_app_Modes_of_operation(void);

uint32_t set_app_Load_encoder_resolution(uint32_t val);
uint32_t get_app_Load_encoder_resolution(void);

uint32_t set_app_Motor_encoder_resolution(uint32_t val);
uint32_t get_app_Motor_encoder_resolution(void);

uint32_t set_app_Polarity(uint8_t val);
uint8_t get_app_Polarity(void);

uint32_t set_app_Target_position(int64_t val);
int64_t get_app_Target_position(void);

uint32_t set_app_Position_range_limit_Minimal_position_limit(int64_t val);
int64_t get_app_Position_range_limit_Minimal_position_limit(void);

uint32_t set_app_Position_range_limit_Maximal_position_limit(int64_t val);
int64_t get_app_Position_range_limit_Maximal_position_limit(void);

uint32_t set_app_Software_position_limit_Minimal_position_limit(int64_t val);
int64_t get_app_Software_position_limit_Minimal_position_limit(void);

uint32_t set_app_Software_position_limit_Maximal_position_limit(int64_t val);
int64_t get_app_Software_position_limit_Maximal_position_limit(void);

uint32_t set_app_Max_profile_velocity(float val);
float get_app_Max_profile_velocity(void);

uint32_t set_app_Max_motor_speed(float val);
float get_app_Max_motor_speed(void);

uint32_t set_app_Profile_velocity(float val);
float get_app_Profile_velocity(void);

uint32_t set_app_Profile_acceleration(float val);
float get_app_Profile_acceleration(void);

uint32_t set_app_Profile_deceleration(float val);
float get_app_Profile_deceleration(void);

uint32_t set_app_Quick_stop_deceleration(float val);
float get_app_Quick_stop_deceleration(void);

uint32_t set_app_Motion_profile_type(int32_t val);
int32_t get_app_Motion_profile_type(void);

uint32_t set_app_Max_acceleration(float val);
float get_app_Max_acceleration(void);

uint32_t set_app_Max_deceleration(float val);
float get_app_Max_deceleration(void);

uint32_t set_app_Home_offset(int64_t val);
int64_t get_app_Home_offset(void);

uint32_t set_app_Homing_method(int8_t val);
int8_t get_app_Homing_method(void);

uint32_t set_app_Position_demand_value(int64_t val);
int64_t get_app_Position_demand_value(void);

uint32_t set_app_Position_actual_value_inc(int64_t val);
int64_t get_app_Position_actual_value_inc(void);

uint32_t set_app_Position_actual_value(int64_t val);
int64_t get_app_Position_actual_value(void);

uint32_t set_app_Following_error_window(int64_t val);
int64_t get_app_Following_error_window(void);

uint32_t set_app_Following_error_time_out(float val);
float get_app_Following_error_time_out(void);

uint32_t set_app_Position_window(uint32_t val);
uint32_t get_app_Position_window(void);

uint32_t set_app_Position_window_time(float val);
float get_app_Position_window_time(void);

uint32_t set_app_Following_error_actual_value(int64_t val);
int64_t get_app_Following_error_actual_value(void);

uint32_t set_app_Velocity_demand_value(float val);
float get_app_Velocity_demand_value(void);

uint32_t set_app_Velocity_actual_value(float val);
float get_app_Velocity_actual_value(void);

uint32_t set_app_Velocity_window(float val);
float get_app_Velocity_window(void);

uint32_t set_app_Velocity_window_time(float val);
float get_app_Velocity_window_time(void);

uint32_t set_app_Velocity_threshold(float val);
float get_app_Velocity_threshold(void);

uint32_t set_app_Velocity_threshold_time(float val);
float get_app_Velocity_threshold_time(void);

uint32_t set_app_Target_velocity(float val);
float get_app_Target_velocity(void);

uint32_t set_app_Target_torque(float val);
float get_app_Target_torque(void);

uint32_t set_app_Max_current(float val);
float get_app_Max_current(void);

uint32_t set_app_Torque_demand_value(float val);
float get_app_Torque_demand_value(void);

uint32_t set_app_Motor_rated_current(float val);
float get_app_Motor_rated_current(void);

uint32_t set_app_Motor_rated_torque(float val);
float get_app_Motor_rated_torque(void);

uint32_t set_app_Torque_actual_value(float val);
float get_app_Torque_actual_value(void);

uint32_t set_app_Current_actual_value(float val);
float get_app_Current_actual_value(void);

uint32_t set_app_DC_link_circuit_voltage(float val);
float get_app_DC_link_circuit_voltage(void);

uint32_t set_app_Torque_slope(float val);
float get_app_Torque_slope(void);

uint32_t set_app_Home_position_offset_value(int64_t val);
int64_t get_app_Home_position_offset_value(void);

uint32_t set_app_Bus_under_voltage_threshold(float val);
float get_app_Bus_under_voltage_threshold(void);

uint32_t set_app_Bus_over_voltage_threshold(float val);
float get_app_Bus_over_voltage_threshold(void);

uint32_t set_app_Drive_overload_current_duration(float val);
float get_app_Drive_overload_current_duration(void);

uint32_t set_app_Drive_peak_current_duration(float val);
float get_app_Drive_peak_current_duration(void);

uint32_t set_app_Drive_temperature_threshold_time(float val);
float get_app_Drive_temperature_threshold_time(void);

uint32_t set_app_Drive_low_temperature_fault_threshold(float val);
float get_app_Drive_low_temperature_fault_threshold(void);

uint32_t set_app_Drive_high_temperature_fault_threshold(float val);
float get_app_Drive_high_temperature_fault_threshold(void);

uint32_t set_app_Overspeed_threshold(float val);
float get_app_Overspeed_threshold(void);

uint32_t set_app_Drive_accumulated_heat(float val);
float get_app_Drive_accumulated_heat(void);

uint32_t set_app_Drive_temperature(float val);
float get_app_Drive_temperature(void);

uint32_t set_app_Motor_peak_current(float val);
float get_app_Motor_peak_current(void);

uint32_t set_app_Motor_pole_pairs(float val);
float get_app_Motor_pole_pairs(void);

uint32_t set_app_Motor_maximum_speed(float val);
float get_app_Motor_maximum_speed(void);

uint32_t set_app_D_current_actual_value(float val);
float get_app_D_current_actual_value(void);

uint32_t set_app_Alarm_word(uint32_t val);
uint32_t get_app_Alarm_word(void);

uint32_t set_app_Modes_of_operation_display(int8_t val);
int8_t get_app_Modes_of_operation_display(void);

uint32_t set_app_Resistance(float val);
float get_app_Resistance(void);

uint32_t set_app_Inductance(float val);
float get_app_Inductance(void);

uint32_t set_app_Drive_overcurrent_threshold(float val);
float get_app_Drive_overcurrent_threshold(void);

uint32_t set_app_Protection_enable(uint32_t val);
uint32_t get_app_Protection_enable(void);

uint32_t set_app_Encoder_calibration_speed(float val);
float get_app_Encoder_calibration_speed(void);

uint32_t set_app_MIT_feedforward_torque(float val);
float get_app_MIT_feedforward_torque(void);

uint32_t set_app_MIT_target_position(int64_t val);
int64_t get_app_MIT_target_position(void);

uint32_t set_app_MIT_max_current(float val);
float get_app_MIT_max_current(void);

uint32_t set_app_MIT_target_velocity(float val);
float get_app_MIT_target_velocity(void);

uint32_t set_app_Comm_control_authority(uint8_t val);
uint8_t get_app_Comm_control_authority(void);

uint32_t set_app_Version(uint32_t val);
uint32_t get_app_Version(void);

uint32_t set_app_U_current_actual_value(float val);
float get_app_U_current_actual_value(void);

uint32_t set_app_V_current_actual_value(float val);
float get_app_V_current_actual_value(void);

uint32_t set_app_W_current_actual_value(float val);
float get_app_W_current_actual_value(void);

uint32_t set_app_Reduction_ratio_num(uint32_t val);
uint32_t get_app_Reduction_ratio_num(void);

uint32_t set_app_Reduction_ratio_den(uint32_t val);
uint32_t get_app_Reduction_ratio_den(void);

uint32_t set_app_Can_id(uint32_t val);
uint32_t get_app_Can_id(void);

uint32_t set_app_Can_baudrate(uint32_t val);
uint32_t get_app_Can_baudrate(void);

uint32_t set_app_MIT_kp(float val);
float get_app_MIT_kp(void);

uint32_t set_app_MIT_kd(float val);
float get_app_MIT_kd(void);

uint32_t set_app_Sys_cmd(uint8_t val);
uint8_t get_app_Sys_cmd(void);

uint32_t set_app_Motor_encoder_type(uint8_t val);
uint8_t get_app_Motor_encoder_type(void);

uint32_t set_app_Load_encoder_type(uint8_t val);
uint8_t get_app_Load_encoder_type(void);

uint32_t set_app_Torque_constant(float val);
float get_app_Torque_constant(void);

uint32_t set_app_Motor_position_demand_value(int64_t val);
int64_t get_app_Motor_position_demand_value(void);

uint32_t set_app_Motor_position_actual_value(int64_t val);
int64_t get_app_Motor_position_actual_value(void);

uint32_t set_app_Motor_following_error_actual_value(int64_t val);
int64_t get_app_Motor_following_error_actual_value(void);

uint32_t set_app_Motor_velocity_demand_value(float val);
float get_app_Motor_velocity_demand_value(void);

uint32_t set_app_Motor_velocity_actual_value(float val);
float get_app_Motor_velocity_actual_value(void);

uint32_t set_app_Storage_status(int8_t val);
int8_t get_app_Storage_status(void);

uint32_t set_app_Motor_temperature(float val);
float get_app_Motor_temperature(void);

uint32_t set_app_Motor_low_temperature_fault_threshold(float val);
float get_app_Motor_low_temperature_fault_threshold(void);

uint32_t set_app_Motor_high_temperature_fault_threshold(float val);
float get_app_Motor_high_temperature_fault_threshold(void);

uint32_t set_app_Can_timeout(float val);
float get_app_Can_timeout(void);

uint32_t set_app_Quick_stop_option_code(int16_t val);
int16_t get_app_Quick_stop_option_code(void);

uint32_t set_app_Motor_power(float val);
float get_app_Motor_power(void);

uint32_t set_app_Motor_low_temperature_warning_threshold(float val);
float get_app_Motor_low_temperature_warning_threshold(void);

uint32_t set_app_Motor_high_temperature_warning_threshold(float val);
float get_app_Motor_high_temperature_warning_threshold(void);

uint32_t set_app_Brake_engage_time(float val);
float get_app_Brake_engage_time(void);

uint32_t set_app_Brake_release_time(float val);
float get_app_Brake_release_time(void);

uint32_t set_app_Dynamic_brake_speed_threshold(float val);
float get_app_Dynamic_brake_speed_threshold(void);

uint32_t set_app_Brake_release_hold_voltage(float val);
float get_app_Brake_release_hold_voltage(void);

uint32_t set_app_Calibration_cmd(uint16_t val);
uint16_t get_app_Calibration_cmd(void);

uint32_t set_app_Calibration_time(uint16_t val);
uint16_t get_app_Calibration_time(void);

uint32_t set_app_Calibration_status(uint16_t val);
uint16_t get_app_Calibration_status(void);

uint32_t set_app_Mcu_temperature(float val);
float get_app_Mcu_temperature(void);

uint32_t set_app_Internal_control_authority(uint8_t val);
uint8_t get_app_Internal_control_authority(void);

uint32_t set_app_U_adc_mid_val(uint16_t val);
uint16_t get_app_U_adc_mid_val(void);

uint32_t set_app_V_adc_mid_val(uint16_t val);
uint16_t get_app_V_adc_mid_val(void);

uint32_t set_app_W_adc_mid_val(uint16_t val);
uint16_t get_app_W_adc_mid_val(void);

uint32_t set_app_Current_loop_time(float val);
float get_app_Current_loop_time(void);

uint32_t set_app_Position_loop_time(float val);
float get_app_Position_loop_time(void);

uint32_t set_app_Current_loop_cycle(float val);
float get_app_Current_loop_cycle(void);

uint32_t set_app_Position_loop_cycle(float val);
float get_app_Position_loop_cycle(void);

uint32_t set_app_Halt_running_cmd(uint8_t val);
uint8_t get_app_Halt_running_cmd(void);

uint32_t set_app_Mcu_temperature_threshold_time(float val);
float get_app_Mcu_temperature_threshold_time(void);

uint32_t set_app_Mcu_low_temperature_fault_threshold(float val);
float get_app_Mcu_low_temperature_fault_threshold(void);

uint32_t set_app_Mcu_high_temperature_fault_threshold(float val);
float get_app_Mcu_high_temperature_fault_threshold(void);

uint32_t set_app_Mcu_low_temperature_warning_threshold(float val);
float get_app_Mcu_low_temperature_warning_threshold(void);

uint32_t set_app_Mcu_high_temperature_warning_threshold(float val);
float get_app_Mcu_high_temperature_warning_threshold(void);

uint32_t set_app_Drive_low_temperature_warning_threshold(float val);
float get_app_Drive_low_temperature_warning_threshold(void);

uint32_t set_app_Drive_high_temperature_warning_threshold(float val);
float get_app_Drive_high_temperature_warning_threshold(void);

uint32_t set_app_User_module_code(uint64_t val);
uint64_t get_app_User_module_code(void);

uint32_t set_app_Sys_init_flag(uint8_t val);
uint8_t get_app_Sys_init_flag(void);

uint32_t set_app_Error_records_list(uint32_t index, uint32_t val);
uint32_t get_app_Error_records_list(uint32_t index);
uint32_t* get_app_Error_records_list_addr(void);

uint32_t set_app_Motor_encoder_options(uint8_t val);
uint8_t get_app_Motor_encoder_options(void);

uint32_t set_app_Reduction_ratio(float val);
float get_app_Reduction_ratio(void);

uint32_t set_app_Reduction_ratio_inv(float val);
float get_app_Reduction_ratio_inv(void);

uint32_t set_app_Load_pps_2_rpm(float val);
float get_app_Load_pps_2_rpm(void);

uint32_t set_app_Load_rpm_2_pps(float val);
float get_app_Load_rpm_2_pps(void);

uint32_t set_app_Storage_cmd(uint8_t val);
uint8_t get_app_Storage_cmd(void);

uint32_t set_app_Motor_rotor_inertia(float val);
float get_app_Motor_rotor_inertia(void);

uint32_t set_app_Debug_float(uint32_t index, float val);
float get_app_Debug_float(uint32_t index);
float* get_app_Debug_float_addr(void);

uint32_t set_app_Debug_uint32(uint32_t index, uint32_t val);
uint32_t get_app_Debug_uint32(uint32_t index);
uint32_t* get_app_Debug_uint32_addr(void);

uint32_t set_app_Motor_pps_2_rpm(float val);
float get_app_Motor_pps_2_rpm(void);

uint32_t set_app_Motor_rpm_2_pps(float val);
float get_app_Motor_rpm_2_pps(void);

uint32_t set_app_P_load_2_motor(float val);
float get_app_P_load_2_motor(void);

uint32_t set_app_P_motor_2_load(float val);
float get_app_P_motor_2_load(void);

uint32_t set_app_Debug_int32(uint32_t index, int32_t val);
int32_t get_app_Debug_int32(uint32_t index);
int32_t* get_app_Debug_int32_addr(void);

uint32_t set_app_Load_control_resolution(uint32_t val);
uint32_t get_app_Load_control_resolution(void);

uint32_t set_app_Motor_control_resolution(uint32_t val);
uint32_t get_app_Motor_control_resolution(void);

uint32_t set_app_Load_encoder_options(uint8_t val);
uint8_t get_app_Load_encoder_options(void);

uint32_t set_app_Position_limit_enable(uint8_t val);
uint8_t get_app_Position_limit_enable(void);

uint32_t set_app_Digital_io_inputs_status(uint32_t val);
uint32_t get_app_Digital_io_inputs_status(void);

uint32_t set_app_Digital_io_outputs_phys(uint32_t val);
uint32_t get_app_Digital_io_outputs_phys(void);

uint32_t set_app_Digital_io_outputs_mask(uint32_t val);
uint32_t get_app_Digital_io_outputs_mask(void);

uint32_t set_app_Brake_state(uint8_t val);
uint8_t get_app_Brake_state(void);

uint32_t set_app_Brake_control_mode(uint8_t val);
uint8_t get_app_Brake_control_mode(void);

uint32_t set_app_Brake_rated_voltage(float val);
float get_app_Brake_rated_voltage(void);

uint32_t set_app_Brake_release_action_voltage(float val);
float get_app_Brake_release_action_voltage(void);

uint32_t set_app_Brake_release_pwm_freq(uint16_t val);
uint16_t get_app_Brake_release_pwm_freq(void);

uint32_t set_app_Brake_engage_delay_time(float val);
float get_app_Brake_engage_delay_time(void);

uint32_t set_app_Brake_release_delay_time(float val);
float get_app_Brake_release_delay_time(void);

uint32_t set_app_Interp_time_value(uint8_t val);
uint8_t get_app_Interp_time_value(void);

uint32_t set_app_Interp_time_index(int8_t val);
int8_t get_app_Interp_time_index(void);

uint32_t set_app_Sys_id(uint8_t val);
uint8_t get_app_Sys_id(void);

uint32_t set_app_Comp_id(uint8_t val);
uint8_t get_app_Comp_id(void);

uint32_t set_app_Interp_period(float val);
float get_app_Interp_period(void);

uint32_t set_app_Emergency_brake_requested(uint8_t val);
uint8_t get_app_Emergency_brake_requested(void);

uint32_t set_app_Target_update_state(uint8_t val);
uint8_t get_app_Target_update_state(void);

uint32_t set_app_Homing_speed_search_for_switch(float val);
float get_app_Homing_speed_search_for_switch(void);

uint32_t set_app_Homing_speed_search_for_zero(float val);
float get_app_Homing_speed_search_for_zero(void);

uint32_t set_app_Homing_acceleration(float val);
float get_app_Homing_acceleration(void);

uint32_t set_app_Homing_step(int8_t val);
int8_t get_app_Homing_step(void);

uint32_t set_app_Encoder_zero_crossing_state(uint8_t val);
uint8_t get_app_Encoder_zero_crossing_state(void);

uint32_t set_app_Homing_state(int8_t val);
int8_t get_app_Homing_state(void);

uint32_t set_app_File_type(uint8_t val);
uint8_t get_app_File_type(void);

uint32_t set_app_File_size(uint32_t val);
uint32_t get_app_File_size(void);

uint32_t set_app_File_direction(uint8_t val);
uint8_t get_app_File_direction(void);

uint32_t set_app_File_index_complete(uint32_t val);
uint32_t get_app_File_index_complete(void);

uint32_t set_app_File_status(int8_t val);
int8_t get_app_File_status(void);

uint32_t set_app_Fw_mode(uint8_t val);
uint8_t get_app_Fw_mode(void);

uint32_t set_app_Fw_app_index(uint8_t val);
uint8_t get_app_Fw_app_index(void);

uint32_t set_app_Fw_flash_size(uint32_t val);
uint32_t get_app_Fw_flash_size(void);

uint32_t set_app_Fw_operating_steps(int8_t val);
int8_t get_app_Fw_operating_steps(void);

extern AppControlWord kAppControlWord;
extern AppStatusInfo kAppStatusInfo;
extern AppOpMode kAppOpMode;
extern AppEncoderConfig kAppEncoderConfig;
extern AppBaseConfig kAppBaseConfig;
extern AppMotionParam kAppMotionParam;
extern AppRestrictParam kAppRestrictParam;
extern AppMotionInfo kAppMotionInfo;
extern AppWindowParam kAppWindowParam;
extern AppMotorConfig kAppMotorConfig;
extern AppProtectConfig kAppProtectConfig;
extern AppPermissionConfig kAppPermissionConfig;
extern SystemCmd kSystemCmd;
extern SystemStatus kSystemStatus;
extern EncoderCalibrationCmd kEncoderCalibrationCmd;
extern EncoderCalibrationStatus kEncoderCalibrationStatus;
extern CustomInfo kCustomInfo;
extern HeartBit kHeartBit;
extern HistoricalInfo kHistoricalInfo;
extern AppDebugParam kAppDebugParam;
extern AppMavlinkConfig kAppMavlinkConfig;
extern AppFileTransferConfig kAppFileTransferConfig;
extern AppFwUpgradeParam kAppFwUpgradeParam;

/* USER CODE BEGIN AREA 1 */
#define ERROR_RECORD_NUM    (sizeof(kHistoricalInfo.Error_records_list) / \
                            sizeof(kHistoricalInfo.Error_records_list[0]))
void AppParamInit(void);
void AppParamSyncUser(void);

void app_param_update(void);  //此函数由代码生成  使用set 接口更新所有应用层数据库变量

// 回调函数注册表结构体
typedef struct{
    void (*set_app_callback)(APP_NAMES app_name);
    uint32_t (*get_check_error_val)(void);
    uint32_t (*get_check_warning_val)(void);
    uint32_t (*get_check_status_val)(void);
    uint32_t (*get_check_di_io_val)(void);
} CallbackRegistry;

//应用层数据库注册接口 典型调用  eg:
//   RegisterSetAppCallback(set_app);
//   RegisterCheckErrorCallback(app_get_check_error_val);
//   RegisterCheckWarningCallback(app_get_check_warning_val);
//   RegisterCheckStatusCallback(app_get_check_status_val);
//   RegisterSendCallback(mavlink_send_data);

void RegisterSetAppCallback(void* callback);
void RegisterCheckErrorCallback(void* callback);
void RegisterCheckWarningCallback(void* callback);
void RegisterCheckStatusCallback(void* callback);
void RegisterCheckIoInputsStatusCallback(void* callback);
void FwUpgradeOverMavlinkCallback(uint16_t const index, uint16_t const length, void const *data);
/* USER CODE END AREA 1 */

