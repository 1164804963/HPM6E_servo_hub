#include "Cia402_ObjectDictionary_Callback.h"
#include "ecat_def.h"
#include "data_param.h"
UINT8 EtherCAT_Read_0x603F_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    OD_0x603F_Error_code_Read_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Read_0x6040_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    OD_0x6040_Controlword_Read_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Read_0x6041_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    OD_0x6041_Statusword_Read_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Read_0x605A_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    OD_0x605A_Quick_stop_option_code_Read_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Read_0x6060_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    OD_0x6060_Modes_of_operation_Read_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Read_0x6061_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    OD_0x6061_Modes_of_operation_display_Read_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Read_0x6062_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    OD_0x6062_Position_demand_value_Read_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Read_0x6063_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    OD_0x6063_Position_actual_value_inc_Read_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Read_0x6064_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    OD_0x6064_Position_actual_value_Read_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Read_0x6065_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    OD_0x6065_Following_error_window_Read_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Read_0x6066_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    OD_0x6066_Following_error_time_out_Read_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Read_0x6067_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    OD_0x6067_Position_window_Read_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Read_0x6068_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    OD_0x6068_Position_window_time_Read_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Read_0x606B_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    OD_0x606B_Velocity_demand_value_Read_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Read_0x606C_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    OD_0x606C_Velocity_actual_value_Read_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Read_0x606D_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    OD_0x606D_Velocity_window_Read_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Read_0x606E_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    OD_0x606E_Velocity_window_time_Read_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Read_0x606F_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    OD_0x606F_Velocity_threshold_Read_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Read_0x6070_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    OD_0x6070_Velocity_threshold_time_Read_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Read_0x6071_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    OD_0x6071_Target_torque_Read_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Read_0x6072_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    OD_0x6072_Max_torque_Read_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Read_0x6073_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    OD_0x6073_Max_current_Read_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Read_0x6074_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    OD_0x6074_Torque_demand_value_Read_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Read_0x6075_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    OD_0x6075_Motor_rated_current_Read_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Read_0x6076_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    OD_0x6076_Motor_rated_torque_Read_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Read_0x6077_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    OD_0x6077_Torque_actual_value_Read_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Read_0x6078_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    OD_0x6078_Current_actual_value_Read_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Read_0x6079_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    OD_0x6079_DC_link_circuit_voltage_Read_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Read_0x607A_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    OD_0x607A_Target_position_Read_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Read_0x607B_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    OD_0x607B_Position_range_limit_Read_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Read_0x607D_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    OD_0x607D_Software_position_limit_Read_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Read_0x607E_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    OD_0x607E_Polarity_Read_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Read_0x607F_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    OD_0x607F_Max_profile_velocity_Read_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Read_0x6080_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    OD_0x6080_Max_motor_speed_Read_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Read_0x6081_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    OD_0x6081_Profile_velocity_Read_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Read_0x6083_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    OD_0x6083_Profile_acceleration_Read_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Read_0x6084_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    OD_0x6084_Profile_deceleration_Read_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Read_0x6085_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    OD_0x6085_Quick_stop_deceleration_Read_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Read_0x6087_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    OD_0x6087_Torque_slope_Read_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Read_0x608F_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    OD_0x608F_Position_encoder_resolution_Read_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Read_0x6091_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    OD_0x6091_Gear_ratio_Read_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Read_0x6098_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    OD_0x6098_Homing_method_Read_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Read_0x60B0_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    OD_0x60B0_Position_offset_Read_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Read_0x60B1_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    OD_0x60B1_Velocity_offset_Read_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Read_0x60B2_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    OD_0x60B2_Torque_offset_Read_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Read_0x60C2_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    OD_0x60C2_Interpolation_time_period_Read_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Read_0x60C5_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    OD_0x60C5_Max_acceleration_Read_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Read_0x60C6_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    OD_0x60C6_Max_deceleration_Read_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Read_0x60F4_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    OD_0x60F4_Following_error_actual_value_Read_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Read_0x60FD_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    OD_0x60FD_Digital_inputs_Read_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Read_0x60FE_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    OD_0x60FE_Digital_outputs_Read_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Read_0x60FF_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    OD_0x60FF_Target_velocity_Read_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Write_0x6040_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){
        return 0;
    }
    OD_0x6040_Controlword_Write_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Write_0x605A_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){
        return 0;
    }
    OD_0x605A_Quick_stop_option_code_Write_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Write_0x6060_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){
        return 0;
    }
    OD_0x6060_Modes_of_operation_Write_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Write_0x6065_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){
        return 0;
    }
    OD_0x6065_Following_error_window_Write_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Write_0x6066_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){
        return 0;
    }
    OD_0x6066_Following_error_time_out_Write_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Write_0x6067_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){
        return 0;
    }
    OD_0x6067_Position_window_Write_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Write_0x6068_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){
        return 0;
    }
    OD_0x6068_Position_window_time_Write_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Write_0x606D_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){
        return 0;
    }
    OD_0x606D_Velocity_window_Write_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Write_0x606E_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){
        return 0;
    }
    OD_0x606E_Velocity_window_time_Write_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Write_0x606F_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){
        return 0;
    }
    OD_0x606F_Velocity_threshold_Write_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Write_0x6070_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){
        return 0;
    }
    OD_0x6070_Velocity_threshold_time_Write_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Write_0x6071_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){
        return 0;
    }
    OD_0x6071_Target_torque_Write_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Write_0x6072_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){
        return 0;
    }
    OD_0x6072_Max_torque_Write_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Write_0x6073_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){
        return 0;
    }
    OD_0x6073_Max_current_Write_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Write_0x6075_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){
        return 0;
    }
    OD_0x6075_Motor_rated_current_Write_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Write_0x6076_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){
        return 0;
    }
    OD_0x6076_Motor_rated_torque_Write_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Write_0x607A_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){
        return 0;
    }
    OD_0x607A_Target_position_Write_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Write_0x607B_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){
        return 0;
    }
    OD_0x607B_Position_range_limit_Write_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Write_0x607D_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){
        return 0;
    }
    OD_0x607D_Software_position_limit_Write_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Write_0x607E_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){
        return 0;
    }
    OD_0x607E_Polarity_Write_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Write_0x607F_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){
        return 0;
    }
    OD_0x607F_Max_profile_velocity_Write_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Write_0x6080_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){
        return 0;
    }
    OD_0x6080_Max_motor_speed_Write_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Write_0x6081_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){
        return 0;
    }
    OD_0x6081_Profile_velocity_Write_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Write_0x6083_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){
        return 0;
    }
    OD_0x6083_Profile_acceleration_Write_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Write_0x6084_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){
        return 0;
    }
    OD_0x6084_Profile_deceleration_Write_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Write_0x6085_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){
        return 0;
    }
    OD_0x6085_Quick_stop_deceleration_Write_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Write_0x6087_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){
        return 0;
    }
    OD_0x6087_Torque_slope_Write_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Write_0x608F_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){
        return 0;
    }
    OD_0x608F_Position_encoder_resolution_Write_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Write_0x6091_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){
        return 0;
    }
    OD_0x6091_Gear_ratio_Write_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Write_0x6098_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){
        return 0;
    }
    OD_0x6098_Homing_method_Write_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Write_0x60B0_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){
        return 0;
    }
    OD_0x60B0_Position_offset_Write_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Write_0x60B1_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){
        return 0;
    }
    OD_0x60B1_Velocity_offset_Write_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Write_0x60B2_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){
        return 0;
    }
    OD_0x60B2_Torque_offset_Write_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Write_0x60C2_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){
        return 0;
    }
    OD_0x60C2_Interpolation_time_period_Write_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Write_0x60C5_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){
        return 0;
    }
    OD_0x60C5_Max_acceleration_Write_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Write_0x60C6_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){
        return 0;
    }
    OD_0x60C6_Max_deceleration_Write_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Write_0x60FE_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){
        return 0;
    }
    OD_0x60FE_Digital_outputs_Write_Callback(subindex, pData);
    return 0;
}

UINT8 EtherCAT_Write_0x60FF_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess){
    if(get_app_Comm_control_authority() == COMM_CONTROL_HOST){
        return 0;
    }
    OD_0x60FF_Target_velocity_Write_Callback(subindex, pData);
    return 0;
}

