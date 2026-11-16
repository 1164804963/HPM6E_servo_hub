#include <stdint.h>
#include "data_param.h"
#include "Cia402_ObjectDictionary_Callback.h"

UNS32 master_cia402_write_callback(uint16_t index, uint8_t subindex, void *data){
    if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){return ABORT_CODE_DRIVE_STATE_DENIED;}
    switch(index){
        case 0x6040: return OD_0x6040_Controlword_Write_Callback(subindex, data); break;
        case 0x605A: return OD_0x605A_Quick_stop_option_code_Write_Callback(subindex, data); break;
        case 0x6060: return OD_0x6060_Modes_of_operation_Write_Callback(subindex, data); break;
        case 0x608F: return OD_0x608F_Position_encoder_resolution_Write_Callback(subindex, data); break;
        case 0x6091: return OD_0x6091_Gear_ratio_Write_Callback(subindex, data); break;
        case 0x607E: return OD_0x607E_Polarity_Write_Callback(subindex, data); break;
        case 0x607A: return OD_0x607A_Target_position_Write_Callback(subindex, data); break;
        case 0x607B: return OD_0x607B_Position_range_limit_Write_Callback(subindex, data); break;
        case 0x607D: return OD_0x607D_Software_position_limit_Write_Callback(subindex, data); break;
        case 0x607F: return OD_0x607F_Max_profile_velocity_Write_Callback(subindex, data); break;
        case 0x6080: return OD_0x6080_Max_motor_speed_Write_Callback(subindex, data); break;
        case 0x6081: return OD_0x6081_Profile_velocity_Write_Callback(subindex, data); break;
        case 0x6083: return OD_0x6083_Profile_acceleration_Write_Callback(subindex, data); break;
        case 0x6084: return OD_0x6084_Profile_deceleration_Write_Callback(subindex, data); break;
        case 0x6085: return OD_0x6085_Quick_stop_deceleration_Write_Callback(subindex, data); break;
        case 0x60C5: return OD_0x60C5_Max_acceleration_Write_Callback(subindex, data); break;
        case 0x60C6: return OD_0x60C6_Max_deceleration_Write_Callback(subindex, data); break;
        case 0x607C: return OD_0x607C_Home_offset_Write_Callback(subindex, data); break;
        case 0x6098: return OD_0x6098_Homing_method_Write_Callback(subindex, data); break;
        case 0x6099: return OD_0x6099_Homing_speeds_Write_Callback(subindex, data); break;
        case 0x609A: return OD_0x609A_Homing_acceleration_Write_Callback(subindex, data); break;
        case 0x6065: return OD_0x6065_Following_error_window_Write_Callback(subindex, data); break;
        case 0x6066: return OD_0x6066_Following_error_time_out_Write_Callback(subindex, data); break;
        case 0x6067: return OD_0x6067_Position_window_Write_Callback(subindex, data); break;
        case 0x6068: return OD_0x6068_Position_window_time_Write_Callback(subindex, data); break;
        case 0x60C2: return OD_0x60C2_Interpolation_time_period_Write_Callback(subindex, data); break;
        case 0x606D: return OD_0x606D_Velocity_window_Write_Callback(subindex, data); break;
        case 0x606E: return OD_0x606E_Velocity_window_time_Write_Callback(subindex, data); break;
        case 0x606F: return OD_0x606F_Velocity_threshold_Write_Callback(subindex, data); break;
        case 0x6070: return OD_0x6070_Velocity_threshold_time_Write_Callback(subindex, data); break;
        case 0x60FF: return OD_0x60FF_Target_velocity_Write_Callback(subindex, data); break;
        case 0x6071: return OD_0x6071_Target_torque_Write_Callback(subindex, data); break;
        case 0x6072: return OD_0x6072_Max_torque_Write_Callback(subindex, data); break;
        case 0x6073: return OD_0x6073_Max_current_Write_Callback(subindex, data); break;
        case 0x6075: return OD_0x6075_Motor_rated_current_Write_Callback(subindex, data); break;
        case 0x6076: return OD_0x6076_Motor_rated_torque_Write_Callback(subindex, data); break;
        case 0x6087: return OD_0x6087_Torque_slope_Write_Callback(subindex, data); break;
        case 0x60B0: return OD_0x60B0_Position_offset_Write_Callback(subindex, data); break;
        case 0x60B1: return OD_0x60B1_Velocity_offset_Write_Callback(subindex, data); break;
        case 0x60B2: return OD_0x60B2_Torque_offset_Write_Callback(subindex, data); break;
        case 0x60FE: return OD_0x60FE_Digital_outputs_Write_Callback(subindex, data); break;
        default: return ABORT_CODE_CANNOT_WRITE_RO_OBJECT; break;
    }
}

UNS32 master_cia402_read_callback(uint16_t index, uint8_t subindex, void *data){
    switch(index){
        case 0x6040: return OD_0x6040_Controlword_Read_Callback(subindex, data); break;
        case 0x6041: return OD_0x6041_Statusword_Read_Callback(subindex, data); break;
        case 0x603F: return OD_0x603F_Error_code_Read_Callback(subindex, data); break;
        case 0x605A: return OD_0x605A_Quick_stop_option_code_Read_Callback(subindex, data); break;
        case 0x6060: return OD_0x6060_Modes_of_operation_Read_Callback(subindex, data); break;
        case 0x6061: return OD_0x6061_Modes_of_operation_display_Read_Callback(subindex, data); break;
        case 0x608F: return OD_0x608F_Position_encoder_resolution_Read_Callback(subindex, data); break;
        case 0x6091: return OD_0x6091_Gear_ratio_Read_Callback(subindex, data); break;
        case 0x607E: return OD_0x607E_Polarity_Read_Callback(subindex, data); break;
        case 0x607A: return OD_0x607A_Target_position_Read_Callback(subindex, data); break;
        case 0x607B: return OD_0x607B_Position_range_limit_Read_Callback(subindex, data); break;
        case 0x607D: return OD_0x607D_Software_position_limit_Read_Callback(subindex, data); break;
        case 0x607F: return OD_0x607F_Max_profile_velocity_Read_Callback(subindex, data); break;
        case 0x6080: return OD_0x6080_Max_motor_speed_Read_Callback(subindex, data); break;
        case 0x6081: return OD_0x6081_Profile_velocity_Read_Callback(subindex, data); break;
        case 0x6083: return OD_0x6083_Profile_acceleration_Read_Callback(subindex, data); break;
        case 0x6084: return OD_0x6084_Profile_deceleration_Read_Callback(subindex, data); break;
        case 0x6085: return OD_0x6085_Quick_stop_deceleration_Read_Callback(subindex, data); break;
        case 0x60C5: return OD_0x60C5_Max_acceleration_Read_Callback(subindex, data); break;
        case 0x60C6: return OD_0x60C6_Max_deceleration_Read_Callback(subindex, data); break;
        case 0x607C: return OD_0x607C_Home_offset_Read_Callback(subindex, data); break;
        case 0x6098: return OD_0x6098_Homing_method_Read_Callback(subindex, data); break;
        case 0x6099: return OD_0x6099_Homing_speeds_Read_Callback(subindex, data); break;
        case 0x609A: return OD_0x609A_Homing_acceleration_Read_Callback(subindex, data); break;
        case 0x6062: return OD_0x6062_Position_demand_value_Read_Callback(subindex, data); break;
        case 0x6063: return OD_0x6063_Position_actual_value_inc_Read_Callback(subindex, data); break;
        case 0x6064: return OD_0x6064_Position_actual_value_Read_Callback(subindex, data); break;
        case 0x6065: return OD_0x6065_Following_error_window_Read_Callback(subindex, data); break;
        case 0x6066: return OD_0x6066_Following_error_time_out_Read_Callback(subindex, data); break;
        case 0x6067: return OD_0x6067_Position_window_Read_Callback(subindex, data); break;
        case 0x6068: return OD_0x6068_Position_window_time_Read_Callback(subindex, data); break;
        case 0x60F4: return OD_0x60F4_Following_error_actual_value_Read_Callback(subindex, data); break;
        case 0x60C2: return OD_0x60C2_Interpolation_time_period_Read_Callback(subindex, data); break;
        case 0x606B: return OD_0x606B_Velocity_demand_value_Read_Callback(subindex, data); break;
        case 0x606C: return OD_0x606C_Velocity_actual_value_Read_Callback(subindex, data); break;
        case 0x606D: return OD_0x606D_Velocity_window_Read_Callback(subindex, data); break;
        case 0x606E: return OD_0x606E_Velocity_window_time_Read_Callback(subindex, data); break;
        case 0x606F: return OD_0x606F_Velocity_threshold_Read_Callback(subindex, data); break;
        case 0x6070: return OD_0x6070_Velocity_threshold_time_Read_Callback(subindex, data); break;
        case 0x60FF: return OD_0x60FF_Target_velocity_Read_Callback(subindex, data); break;
        case 0x6071: return OD_0x6071_Target_torque_Read_Callback(subindex, data); break;
        case 0x6072: return OD_0x6072_Max_torque_Read_Callback(subindex, data); break;
        case 0x6073: return OD_0x6073_Max_current_Read_Callback(subindex, data); break;
        case 0x6074: return OD_0x6074_Torque_demand_value_Read_Callback(subindex, data); break;
        case 0x6075: return OD_0x6075_Motor_rated_current_Read_Callback(subindex, data); break;
        case 0x6076: return OD_0x6076_Motor_rated_torque_Read_Callback(subindex, data); break;
        case 0x6077: return OD_0x6077_Torque_actual_value_Read_Callback(subindex, data); break;
        case 0x6078: return OD_0x6078_Current_actual_value_Read_Callback(subindex, data); break;
        case 0x6079: return OD_0x6079_DC_link_circuit_voltage_Read_Callback(subindex, data); break;
        case 0x6087: return OD_0x6087_Torque_slope_Read_Callback(subindex, data); break;
        case 0x60B0: return OD_0x60B0_Position_offset_Read_Callback(subindex, data); break;
        case 0x60B1: return OD_0x60B1_Velocity_offset_Read_Callback(subindex, data); break;
        case 0x60B2: return OD_0x60B2_Torque_offset_Read_Callback(subindex, data); break;
        case 0x60FD: return OD_0x60FD_Digital_inputs_Read_Callback(subindex, data); break;
        case 0x60FE: return OD_0x60FE_Digital_outputs_Read_Callback(subindex, data); break;
        default: return ABORT_CODE_CANNOT_READ_WO_OBJECT; break;
    }
}
