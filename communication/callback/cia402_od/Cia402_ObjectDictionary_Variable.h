#pragma once

#include <stdint.h>

typedef int8_t INTEGER8;
typedef int16_t INTEGER16;
typedef int32_t INTEGER32;
typedef uint8_t UNS8;
typedef uint16_t UNS16;
typedef uint32_t UNS32;

#define ABORT_CODE_SUCCESSFUL               (0x00000000)
#define ABORT_CODE_UNSUPPORTED_ACCESS       (0x06010000) //Unsupported access to an object
#define ABORT_CODE_CANNOT_READ_WO_OBJECT    (0x06010001) //Attempt to read a write only object
#define ABORT_CODE_CANNOT_WRITE_RO_OBJECT   (0x06010002) //Attempt to write a read only object
#define ABORT_CODE_SUB_INDEX_NOT_EXIST      (0x06090011) //Sub-index does not exist
#define ABORT_CODE_VALUE_TOO_HIGH           (0x06090031) //Value of parameter written too high
#define ABORT_CODE_VALUE_TOO_LOW            (0x06090032) //Value of parameter written too low
#define ABORT_CODE_DRIVE_STATE_DENIED       (0x08000022) //Data cannot be transferred or stored to the application because of the present device state

typedef struct
{
    UNS16 Controlword; //402控制字
    UNS16 Statusword; //402状态字
    UNS16 Error_code; //错误码
    INTEGER16 Quick_stop_option_code; //快速停止操作代码
    INTEGER8 Modes_of_operation; //运行模式
    INTEGER8 Modes_of_operation_display; //显示运行模式
}PDS_FSA;

typedef struct
{
    UNS8 Position_encoder_resolution;
    UNS32 Position_encoder_resolution_Encoder_increments; //负载端位置反馈分辨率
    UNS32 Position_encoder_resolution_Motor_revolutions; //电机端位置反馈分辨率
    UNS8 Gear_ratio;
    UNS32 Motor_revolutions; //齿轮比分母
    UNS32 Shaft_revolutions; //齿轮比分子
    UNS8 Polarity; //运动极性
}Factor_group;

typedef struct
{
    INTEGER32 Target_position; //位置目标值
    UNS8 Position_range_limit;
    INTEGER32 Position_range_limit_Minimal_position_limit; //位置溢出最小值
    INTEGER32 Position_range_limit_Maximal_position_limit; //位置溢出最大值
    UNS8 Software_position_limit;
    INTEGER32 Software_position_limit_Minimal_position_limit; //应用位置下限
    INTEGER32 Software_position_limit_Maximal_position_limit; //应用位置上限
    UNS32 Max_profile_velocity; //应用速度限制
    UNS32 Max_motor_speed; //电机最大转速（弃用实际不生效）
    UNS32 Profile_velocity; //轮廓速度
    UNS32 Profile_acceleration; //轮廓加速度
    UNS32 Profile_deceleration; //轮廓减速度
    UNS32 Quick_stop_deceleration; //快速停止减速度
    UNS32 Max_acceleration; //应用加速度限制
    UNS32 Max_deceleration; //应用减速度限制
}Profile_position_mode;

typedef struct
{
    INTEGER32 Home_offset; //回零偏移
    INTEGER8 Homing_method; //回零方法
    UNS8 Homing_speeds;
    UNS32 Homing_speeds_Speed_for_switch_search; //回零搜索开关速度
    UNS32 Homing_speeds_Speed_for_zero_search; //回零搜索零点速度
    UNS32 Homing_acceleration; //回零加速度
}Homing_mode;

typedef struct
{
    INTEGER32 Position_demand_value; //负载端位置指令值
    INTEGER32 Position_actual_value_inc; //负载端内部位置当前值
    INTEGER32 Position_actual_value; //负载端位置当前值
    UNS32 Following_error_window; //位置跟随误差阈值
    UNS16 Following_error_time_out; //位置跟随误差阈值时间
    UNS32 Position_window; //位置到达检测窗口
    UNS16 Position_window_time; //位置到达检测窗口时间
    INTEGER32 Following_error_actual_value; //负载端位置误差值
}Position_control_function;

typedef struct
{
    UNS8 Interpolation_time_period;
    UNS8 Interpolation_time_period_Ip_time_units; //插值模式时间单位
    INTEGER8 Interpolation_time_period_Ip_time_index; //插值模式时间指数
}Interpolated_position_mode;

typedef struct
{
    INTEGER32 Velocity_demand_value; //负载端速度指令值
    INTEGER32 Velocity_actual_value; //负载端速度当前值
    UNS16 Velocity_window; //速度到达检测窗口
    UNS16 Velocity_window_time; //速度到达检测窗口时间
    UNS16 Velocity_threshold; //零速检测窗口
    UNS16 Velocity_threshold_time; //零速检测窗口时间
    INTEGER32 Target_velocity; //速度目标值
}Profile_velocity_mode;

typedef struct
{
    INTEGER16 Target_torque; //力矩目标值
    UNS16 Max_torque; //应用力矩限制相对值
    UNS16 Max_current; //应用电流限制相对值
    INTEGER16 Torque_demand_value; //力矩指令值
    UNS32 Motor_rated_current; //电机额定电流
    UNS32 Motor_rated_torque; //电机额定力矩/推力
    INTEGER16 Torque_actual_value; //力矩当前值
    INTEGER16 Current_actual_value; //电流当前值
    UNS32 DC_link_circuit_voltage; //母线电压当前值
    UNS32 Torque_slope; //力矩上升斜率
}Profile_torque_mode;

typedef struct
{
    INTEGER32 Position_offset; //目标位置偏置值
    INTEGER32 Velocity_offset; //目标速度偏置值
    INTEGER16 Torque_offset; //目标转矩偏置值
}CSP_CSV_CST;

typedef struct
{
    UNS32 Digital_inputs; //数字IO输入值
    UNS8 Digital_outputs;
    UNS32 Digital_outputs_Physical_outputs; //数字IO输出值
    UNS32 Digital_outputs_Bit_mask; //数字IO输出掩码开关
}Optional_application;

UNS32 set_Controlword(UNS16 val);
UNS16 get_Controlword(void);

UNS32 set_Statusword(UNS16 val);
UNS16 get_Statusword(void);

UNS32 set_Error_code(UNS16 val);
UNS16 get_Error_code(void);

UNS32 set_Quick_stop_option_code(INTEGER16 val);
INTEGER16 get_Quick_stop_option_code(void);

UNS32 set_Modes_of_operation(INTEGER8 val);
INTEGER8 get_Modes_of_operation(void);

UNS32 set_Modes_of_operation_display(INTEGER8 val);
INTEGER8 get_Modes_of_operation_display(void);

UNS32 set_Position_encoder_resolution(UNS8 val);
UNS8 get_Position_encoder_resolution(void);

UNS32 set_Position_encoder_resolution_Encoder_increments(UNS32 val);
UNS32 get_Position_encoder_resolution_Encoder_increments(void);

UNS32 set_Position_encoder_resolution_Motor_revolutions(UNS32 val);
UNS32 get_Position_encoder_resolution_Motor_revolutions(void);

UNS32 set_Gear_ratio(UNS8 val);
UNS8 get_Gear_ratio(void);

UNS32 set_Motor_revolutions(UNS32 val);
UNS32 get_Motor_revolutions(void);

UNS32 set_Shaft_revolutions(UNS32 val);
UNS32 get_Shaft_revolutions(void);

UNS32 set_Polarity(UNS8 val);
UNS8 get_Polarity(void);

UNS32 set_Target_position(INTEGER32 val);
INTEGER32 get_Target_position(void);

UNS32 set_Position_range_limit(UNS8 val);
UNS8 get_Position_range_limit(void);

UNS32 set_Position_range_limit_Minimal_position_limit(INTEGER32 val);
INTEGER32 get_Position_range_limit_Minimal_position_limit(void);

UNS32 set_Position_range_limit_Maximal_position_limit(INTEGER32 val);
INTEGER32 get_Position_range_limit_Maximal_position_limit(void);

UNS32 set_Software_position_limit(UNS8 val);
UNS8 get_Software_position_limit(void);

UNS32 set_Software_position_limit_Minimal_position_limit(INTEGER32 val);
INTEGER32 get_Software_position_limit_Minimal_position_limit(void);

UNS32 set_Software_position_limit_Maximal_position_limit(INTEGER32 val);
INTEGER32 get_Software_position_limit_Maximal_position_limit(void);

UNS32 set_Max_profile_velocity(UNS32 val);
UNS32 get_Max_profile_velocity(void);

UNS32 set_Max_motor_speed(UNS32 val);
UNS32 get_Max_motor_speed(void);

UNS32 set_Profile_velocity(UNS32 val);
UNS32 get_Profile_velocity(void);

UNS32 set_Profile_acceleration(UNS32 val);
UNS32 get_Profile_acceleration(void);

UNS32 set_Profile_deceleration(UNS32 val);
UNS32 get_Profile_deceleration(void);

UNS32 set_Quick_stop_deceleration(UNS32 val);
UNS32 get_Quick_stop_deceleration(void);

UNS32 set_Max_acceleration(UNS32 val);
UNS32 get_Max_acceleration(void);

UNS32 set_Max_deceleration(UNS32 val);
UNS32 get_Max_deceleration(void);

UNS32 set_Home_offset(INTEGER32 val);
INTEGER32 get_Home_offset(void);

UNS32 set_Homing_method(INTEGER8 val);
INTEGER8 get_Homing_method(void);

UNS32 set_Homing_speeds(UNS8 val);
UNS8 get_Homing_speeds(void);

UNS32 set_Homing_speeds_Speed_for_switch_search(UNS32 val);
UNS32 get_Homing_speeds_Speed_for_switch_search(void);

UNS32 set_Homing_speeds_Speed_for_zero_search(UNS32 val);
UNS32 get_Homing_speeds_Speed_for_zero_search(void);

UNS32 set_Homing_acceleration(UNS32 val);
UNS32 get_Homing_acceleration(void);

UNS32 set_Position_demand_value(INTEGER32 val);
INTEGER32 get_Position_demand_value(void);

UNS32 set_Position_actual_value_inc(INTEGER32 val);
INTEGER32 get_Position_actual_value_inc(void);

UNS32 set_Position_actual_value(INTEGER32 val);
INTEGER32 get_Position_actual_value(void);

UNS32 set_Following_error_window(UNS32 val);
UNS32 get_Following_error_window(void);

UNS32 set_Following_error_time_out(UNS16 val);
UNS16 get_Following_error_time_out(void);

UNS32 set_Position_window(UNS32 val);
UNS32 get_Position_window(void);

UNS32 set_Position_window_time(UNS16 val);
UNS16 get_Position_window_time(void);

UNS32 set_Following_error_actual_value(INTEGER32 val);
INTEGER32 get_Following_error_actual_value(void);

UNS32 set_Interpolation_time_period(UNS8 val);
UNS8 get_Interpolation_time_period(void);

UNS32 set_Interpolation_time_period_Ip_time_units(UNS8 val);
UNS8 get_Interpolation_time_period_Ip_time_units(void);

UNS32 set_Interpolation_time_period_Ip_time_index(INTEGER8 val);
INTEGER8 get_Interpolation_time_period_Ip_time_index(void);

UNS32 set_Velocity_demand_value(INTEGER32 val);
INTEGER32 get_Velocity_demand_value(void);

UNS32 set_Velocity_actual_value(INTEGER32 val);
INTEGER32 get_Velocity_actual_value(void);

UNS32 set_Velocity_window(UNS16 val);
UNS16 get_Velocity_window(void);

UNS32 set_Velocity_window_time(UNS16 val);
UNS16 get_Velocity_window_time(void);

UNS32 set_Velocity_threshold(UNS16 val);
UNS16 get_Velocity_threshold(void);

UNS32 set_Velocity_threshold_time(UNS16 val);
UNS16 get_Velocity_threshold_time(void);

UNS32 set_Target_velocity(INTEGER32 val);
INTEGER32 get_Target_velocity(void);

UNS32 set_Target_torque(INTEGER16 val);
INTEGER16 get_Target_torque(void);

UNS32 set_Max_torque(UNS16 val);
UNS16 get_Max_torque(void);

UNS32 set_Max_current(UNS16 val);
UNS16 get_Max_current(void);

UNS32 set_Torque_demand_value(INTEGER16 val);
INTEGER16 get_Torque_demand_value(void);

UNS32 set_Motor_rated_current(UNS32 val);
UNS32 get_Motor_rated_current(void);

UNS32 set_Motor_rated_torque(UNS32 val);
UNS32 get_Motor_rated_torque(void);

UNS32 set_Torque_actual_value(INTEGER16 val);
INTEGER16 get_Torque_actual_value(void);

UNS32 set_Current_actual_value(INTEGER16 val);
INTEGER16 get_Current_actual_value(void);

UNS32 set_DC_link_circuit_voltage(UNS32 val);
UNS32 get_DC_link_circuit_voltage(void);

UNS32 set_Torque_slope(UNS32 val);
UNS32 get_Torque_slope(void);

UNS32 set_Position_offset(INTEGER32 val);
INTEGER32 get_Position_offset(void);

UNS32 set_Velocity_offset(INTEGER32 val);
INTEGER32 get_Velocity_offset(void);

UNS32 set_Torque_offset(INTEGER16 val);
INTEGER16 get_Torque_offset(void);

UNS32 set_Digital_inputs(UNS32 val);
UNS32 get_Digital_inputs(void);

UNS32 set_Digital_outputs(UNS8 val);
UNS8 get_Digital_outputs(void);

UNS32 set_Digital_outputs_Physical_outputs(UNS32 val);
UNS32 get_Digital_outputs_Physical_outputs(void);

UNS32 set_Digital_outputs_Bit_mask(UNS32 val);
UNS32 get_Digital_outputs_Bit_mask(void);

