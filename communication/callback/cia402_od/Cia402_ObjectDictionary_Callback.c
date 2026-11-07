#include "Cia402_ObjectDictionary_Callback.h"

#define STATUS_WORD_ENABLE_MASK (0x0027)

UNS32 OD_0x6040_Controlword_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x6040 0x00 WRITE 0 */
    
    /* USER CODE END 0x6040 0x00 WRITE 0 */
    abort_code = set_Controlword(*(UNS16*)value);
    /* USER CODE BEGIN 0x6040 0x00 WRITE 1 */
    
    /* USER CODE END 0x6040 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x6040_Controlword_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x6040 0x00 READ 0 */
    
    /* USER CODE END 0x6040 0x00 READ 0 */
    *(UNS16*)value = get_Controlword();
    /* USER CODE BEGIN 0x6040 0x00 READ 1 */
    
    /* USER CODE END 0x6040 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x6041_Statusword_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x6041 0x00 READ 0 */
    
    /* USER CODE END 0x6041 0x00 READ 0 */
    *(UNS16*)value = get_Statusword();
    /* USER CODE BEGIN 0x6041 0x00 READ 1 */
    
    /* USER CODE END 0x6041 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x603F_Error_code_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x603F 0x00 READ 0 */
    
    /* USER CODE END 0x603F 0x00 READ 0 */
    *(UNS16*)value = get_Error_code();
    /* USER CODE BEGIN 0x603F 0x00 READ 1 */
    
    /* USER CODE END 0x603F 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x605A_Quick_stop_option_code_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x605A 0x00 WRITE 0 */
    
    /* USER CODE END 0x605A 0x00 WRITE 0 */
    abort_code = set_Quick_stop_option_code(*(INTEGER16*)value);
    /* USER CODE BEGIN 0x605A 0x00 WRITE 1 */
    
    /* USER CODE END 0x605A 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x605A_Quick_stop_option_code_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x605A 0x00 READ 0 */
    
    /* USER CODE END 0x605A 0x00 READ 0 */
    *(INTEGER16*)value = get_Quick_stop_option_code();
    /* USER CODE BEGIN 0x605A 0x00 READ 1 */
    
    /* USER CODE END 0x605A 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x6060_Modes_of_operation_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x6060 0x00 WRITE 0 */
    
    /* USER CODE END 0x6060 0x00 WRITE 0 */
    abort_code = set_Modes_of_operation(*(INTEGER8*)value);
    /* USER CODE BEGIN 0x6060 0x00 WRITE 1 */
    
    /* USER CODE END 0x6060 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x6060_Modes_of_operation_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x6060 0x00 READ 0 */
    
    /* USER CODE END 0x6060 0x00 READ 0 */
    *(INTEGER8*)value = get_Modes_of_operation();
    /* USER CODE BEGIN 0x6060 0x00 READ 1 */
    
    /* USER CODE END 0x6060 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x6061_Modes_of_operation_display_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x6061 0x00 READ 0 */
    
    /* USER CODE END 0x6061 0x00 READ 0 */
    *(INTEGER8*)value = get_Modes_of_operation_display();
    /* USER CODE BEGIN 0x6061 0x00 READ 1 */
    
    /* USER CODE END 0x6061 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x608F_Position_encoder_resolution_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    if ((get_Statusword() & STATUS_WORD_ENABLE_MASK) == STATUS_WORD_ENABLE_MASK)
    {
        return ABORT_CODE_DRIVE_STATE_DENIED;
    }
    switch(subindex)
    {
        case 0x00:
    /* USER CODE BEGIN 0x608F 0x00 WRITE 0 */
    
    /* USER CODE END 0x608F 0x00 WRITE 0 */
            abort_code = ABORT_CODE_CANNOT_WRITE_RO_OBJECT;
    /* USER CODE BEGIN 0x608F 0x00 WRITE 1 */
    
    /* USER CODE END 0x608F 0x00 WRITE 1 */
            break;
        case 0x01:
    /* USER CODE BEGIN 0x608F 0x01 WRITE 0 */
    
    /* USER CODE END 0x608F 0x01 WRITE 0 */
            abort_code = set_Position_encoder_resolution_Encoder_increments(*(UNS32*)value);
    /* USER CODE BEGIN 0x608F 0x01 WRITE 1 */
    
    /* USER CODE END 0x608F 0x01 WRITE 1 */
            break;
        case 0x02:
    /* USER CODE BEGIN 0x608F 0x02 WRITE 0 */
    
    /* USER CODE END 0x608F 0x02 WRITE 0 */
            abort_code = set_Position_encoder_resolution_Motor_revolutions(*(UNS32*)value);
    /* USER CODE BEGIN 0x608F 0x02 WRITE 1 */
    
    /* USER CODE END 0x608F 0x02 WRITE 1 */
            break;
        default:
            abort_code = ABORT_CODE_SUB_INDEX_NOT_EXIST;
            break;
    }
    return abort_code;
}
UNS32 OD_0x608F_Position_encoder_resolution_Read_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    switch(subindex)
    {
        case 0x00:
    /* USER CODE BEGIN 0x608F 0x00 READ 0 */
    
    /* USER CODE END 0x608F 0x00 READ 0 */
            *(UNS8*)value = 0x2;
            abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x608F 0x00 READ 1 */
    
    /* USER CODE END 0x608F 0x00 READ 1 */
            break;
        case 0x01:
    /* USER CODE BEGIN 0x608F 0x01 READ 0 */
    
    /* USER CODE END 0x608F 0x01 READ 0 */
            *(UNS32*)value = get_Position_encoder_resolution_Encoder_increments();
    /* USER CODE BEGIN 0x608F 0x01 READ 1 */
    
    /* USER CODE END 0x608F 0x01 READ 1 */
            break;
        case 0x02:
    /* USER CODE BEGIN 0x608F 0x02 READ 0 */
    
    /* USER CODE END 0x608F 0x02 READ 0 */
            *(UNS32*)value = get_Position_encoder_resolution_Motor_revolutions();
    /* USER CODE BEGIN 0x608F 0x02 READ 1 */
    
    /* USER CODE END 0x608F 0x02 READ 1 */
            break;
        default:
            abort_code = ABORT_CODE_SUB_INDEX_NOT_EXIST;
            break;
    }
    return abort_code;
}
UNS32 OD_0x6091_Gear_ratio_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    if ((get_Statusword() & STATUS_WORD_ENABLE_MASK) == STATUS_WORD_ENABLE_MASK)
    {
        return ABORT_CODE_DRIVE_STATE_DENIED;
    }
    switch(subindex)
    {
        case 0x00:
    /* USER CODE BEGIN 0x6091 0x00 WRITE 0 */
    
    /* USER CODE END 0x6091 0x00 WRITE 0 */
            abort_code = ABORT_CODE_CANNOT_WRITE_RO_OBJECT;
    /* USER CODE BEGIN 0x6091 0x00 WRITE 1 */
    
    /* USER CODE END 0x6091 0x00 WRITE 1 */
            break;
        case 0x01:
    /* USER CODE BEGIN 0x6091 0x01 WRITE 0 */
    
    /* USER CODE END 0x6091 0x01 WRITE 0 */
            abort_code = set_Motor_revolutions(*(UNS32*)value);
    /* USER CODE BEGIN 0x6091 0x01 WRITE 1 */
    
    /* USER CODE END 0x6091 0x01 WRITE 1 */
            break;
        case 0x02:
    /* USER CODE BEGIN 0x6091 0x02 WRITE 0 */
    
    /* USER CODE END 0x6091 0x02 WRITE 0 */
            abort_code = set_Shaft_revolutions(*(UNS32*)value);
    /* USER CODE BEGIN 0x6091 0x02 WRITE 1 */
    
    /* USER CODE END 0x6091 0x02 WRITE 1 */
            break;
        default:
            abort_code = ABORT_CODE_SUB_INDEX_NOT_EXIST;
            break;
    }
    return abort_code;
}
UNS32 OD_0x6091_Gear_ratio_Read_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    switch(subindex)
    {
        case 0x00:
    /* USER CODE BEGIN 0x6091 0x00 READ 0 */
    
    /* USER CODE END 0x6091 0x00 READ 0 */
            *(UNS8*)value = 0x2;
            abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x6091 0x00 READ 1 */
    
    /* USER CODE END 0x6091 0x00 READ 1 */
            break;
        case 0x01:
    /* USER CODE BEGIN 0x6091 0x01 READ 0 */
    
    /* USER CODE END 0x6091 0x01 READ 0 */
            *(UNS32*)value = get_Motor_revolutions();
    /* USER CODE BEGIN 0x6091 0x01 READ 1 */
    
    /* USER CODE END 0x6091 0x01 READ 1 */
            break;
        case 0x02:
    /* USER CODE BEGIN 0x6091 0x02 READ 0 */
    
    /* USER CODE END 0x6091 0x02 READ 0 */
            *(UNS32*)value = get_Shaft_revolutions();
    /* USER CODE BEGIN 0x6091 0x02 READ 1 */
    
    /* USER CODE END 0x6091 0x02 READ 1 */
            break;
        default:
            abort_code = ABORT_CODE_SUB_INDEX_NOT_EXIST;
            break;
    }
    return abort_code;
}
UNS32 OD_0x607E_Polarity_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    if (*(UNS8*)value > 1)
    {
        return ABORT_CODE_VALUE_TOO_HIGH;
    }
    /* USER CODE BEGIN 0x607E 0x00 WRITE 0 */
    
    /* USER CODE END 0x607E 0x00 WRITE 0 */
    abort_code = set_Polarity(*(UNS8*)value);
    /* USER CODE BEGIN 0x607E 0x00 WRITE 1 */
    
    /* USER CODE END 0x607E 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x607E_Polarity_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x607E 0x00 READ 0 */
    
    /* USER CODE END 0x607E 0x00 READ 0 */
    *(UNS8*)value = get_Polarity();
    /* USER CODE BEGIN 0x607E 0x00 READ 1 */
    
    /* USER CODE END 0x607E 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x607A_Target_position_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x607A 0x00 WRITE 0 */
    
    /* USER CODE END 0x607A 0x00 WRITE 0 */
    abort_code = set_Target_position(*(INTEGER32*)value);
    /* USER CODE BEGIN 0x607A 0x00 WRITE 1 */
    
    /* USER CODE END 0x607A 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x607A_Target_position_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x607A 0x00 READ 0 */
    
    /* USER CODE END 0x607A 0x00 READ 0 */
    *(INTEGER32*)value = get_Target_position();
    /* USER CODE BEGIN 0x607A 0x00 READ 1 */
    
    /* USER CODE END 0x607A 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x607B_Position_range_limit_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    if ((get_Statusword() & STATUS_WORD_ENABLE_MASK) == STATUS_WORD_ENABLE_MASK)
    {
        return ABORT_CODE_DRIVE_STATE_DENIED;
    }
    switch(subindex)
    {
        case 0x00:
    /* USER CODE BEGIN 0x607B 0x00 WRITE 0 */
    
    /* USER CODE END 0x607B 0x00 WRITE 0 */
            abort_code = ABORT_CODE_CANNOT_WRITE_RO_OBJECT;
    /* USER CODE BEGIN 0x607B 0x00 WRITE 1 */
    
    /* USER CODE END 0x607B 0x00 WRITE 1 */
            break;
        case 0x01:
    /* USER CODE BEGIN 0x607B 0x01 WRITE 0 */
    
    /* USER CODE END 0x607B 0x01 WRITE 0 */
            abort_code = set_Position_range_limit_Minimal_position_limit(*(INTEGER32*)value);
    /* USER CODE BEGIN 0x607B 0x01 WRITE 1 */
    
    /* USER CODE END 0x607B 0x01 WRITE 1 */
            break;
        case 0x02:
    /* USER CODE BEGIN 0x607B 0x02 WRITE 0 */
    
    /* USER CODE END 0x607B 0x02 WRITE 0 */
            abort_code = set_Position_range_limit_Maximal_position_limit(*(INTEGER32*)value);
    /* USER CODE BEGIN 0x607B 0x02 WRITE 1 */
    
    /* USER CODE END 0x607B 0x02 WRITE 1 */
            break;
        default:
            abort_code = ABORT_CODE_SUB_INDEX_NOT_EXIST;
            break;
    }
    return abort_code;
}
UNS32 OD_0x607B_Position_range_limit_Read_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    switch(subindex)
    {
        case 0x00:
    /* USER CODE BEGIN 0x607B 0x00 READ 0 */
    
    /* USER CODE END 0x607B 0x00 READ 0 */
            *(UNS8*)value = 0x2;
            abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x607B 0x00 READ 1 */
    
    /* USER CODE END 0x607B 0x00 READ 1 */
            break;
        case 0x01:
    /* USER CODE BEGIN 0x607B 0x01 READ 0 */
    
    /* USER CODE END 0x607B 0x01 READ 0 */
            *(INTEGER32*)value = get_Position_range_limit_Minimal_position_limit();
    /* USER CODE BEGIN 0x607B 0x01 READ 1 */
    
    /* USER CODE END 0x607B 0x01 READ 1 */
            break;
        case 0x02:
    /* USER CODE BEGIN 0x607B 0x02 READ 0 */
    
    /* USER CODE END 0x607B 0x02 READ 0 */
            *(INTEGER32*)value = get_Position_range_limit_Maximal_position_limit();
    /* USER CODE BEGIN 0x607B 0x02 READ 1 */
    
    /* USER CODE END 0x607B 0x02 READ 1 */
            break;
        default:
            abort_code = ABORT_CODE_SUB_INDEX_NOT_EXIST;
            break;
    }
    return abort_code;
}
UNS32 OD_0x607D_Software_position_limit_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    if ((get_Statusword() & STATUS_WORD_ENABLE_MASK) == STATUS_WORD_ENABLE_MASK)
    {
        return ABORT_CODE_DRIVE_STATE_DENIED;
    }
    switch(subindex)
    {
        case 0x00:
    /* USER CODE BEGIN 0x607D 0x00 WRITE 0 */
    
    /* USER CODE END 0x607D 0x00 WRITE 0 */
            abort_code = ABORT_CODE_CANNOT_WRITE_RO_OBJECT;
    /* USER CODE BEGIN 0x607D 0x00 WRITE 1 */
    
    /* USER CODE END 0x607D 0x00 WRITE 1 */
            break;
        case 0x01:
    /* USER CODE BEGIN 0x607D 0x01 WRITE 0 */
    
    /* USER CODE END 0x607D 0x01 WRITE 0 */
            abort_code = set_Software_position_limit_Minimal_position_limit(*(INTEGER32*)value);
    /* USER CODE BEGIN 0x607D 0x01 WRITE 1 */
    
    /* USER CODE END 0x607D 0x01 WRITE 1 */
            break;
        case 0x02:
    /* USER CODE BEGIN 0x607D 0x02 WRITE 0 */
    
    /* USER CODE END 0x607D 0x02 WRITE 0 */
            abort_code = set_Software_position_limit_Maximal_position_limit(*(INTEGER32*)value);
    /* USER CODE BEGIN 0x607D 0x02 WRITE 1 */
    
    /* USER CODE END 0x607D 0x02 WRITE 1 */
            break;
        default:
            abort_code = ABORT_CODE_SUB_INDEX_NOT_EXIST;
            break;
    }
    return abort_code;
}
UNS32 OD_0x607D_Software_position_limit_Read_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    switch(subindex)
    {
        case 0x00:
    /* USER CODE BEGIN 0x607D 0x00 READ 0 */
    
    /* USER CODE END 0x607D 0x00 READ 0 */
            *(UNS8*)value = 0x2;
            abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x607D 0x00 READ 1 */
    
    /* USER CODE END 0x607D 0x00 READ 1 */
            break;
        case 0x01:
    /* USER CODE BEGIN 0x607D 0x01 READ 0 */
    
    /* USER CODE END 0x607D 0x01 READ 0 */
            *(INTEGER32*)value = get_Software_position_limit_Minimal_position_limit();
    /* USER CODE BEGIN 0x607D 0x01 READ 1 */
    
    /* USER CODE END 0x607D 0x01 READ 1 */
            break;
        case 0x02:
    /* USER CODE BEGIN 0x607D 0x02 READ 0 */
    
    /* USER CODE END 0x607D 0x02 READ 0 */
            *(INTEGER32*)value = get_Software_position_limit_Maximal_position_limit();
    /* USER CODE BEGIN 0x607D 0x02 READ 1 */
    
    /* USER CODE END 0x607D 0x02 READ 1 */
            break;
        default:
            abort_code = ABORT_CODE_SUB_INDEX_NOT_EXIST;
            break;
    }
    return abort_code;
}
UNS32 OD_0x607F_Max_profile_velocity_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x607F 0x00 WRITE 0 */
    
    /* USER CODE END 0x607F 0x00 WRITE 0 */
    abort_code = set_Max_profile_velocity(*(UNS32*)value);
    /* USER CODE BEGIN 0x607F 0x00 WRITE 1 */
    
    /* USER CODE END 0x607F 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x607F_Max_profile_velocity_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x607F 0x00 READ 0 */
    
    /* USER CODE END 0x607F 0x00 READ 0 */
    *(UNS32*)value = get_Max_profile_velocity();
    /* USER CODE BEGIN 0x607F 0x00 READ 1 */
    
    /* USER CODE END 0x607F 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x6080_Max_motor_speed_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x6080 0x00 WRITE 0 */
    return ABORT_CODE_UNSUPPORTED_ACCESS;  // 暂不支持该字典
    /* USER CODE END 0x6080 0x00 WRITE 0 */
    abort_code = set_Max_motor_speed(*(UNS32*)value);
    /* USER CODE BEGIN 0x6080 0x00 WRITE 1 */

    /* USER CODE END 0x6080 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x6080_Max_motor_speed_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x6080 0x00 READ 0 */
    
    /* USER CODE END 0x6080 0x00 READ 0 */
    *(UNS32*)value = get_Max_motor_speed();
    /* USER CODE BEGIN 0x6080 0x00 READ 1 */
    *(UNS32*)value = 0;  // 暂不支持该字典，返回0
    /* USER CODE END 0x6080 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x6081_Profile_velocity_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x6081 0x00 WRITE 0 */
    
    /* USER CODE END 0x6081 0x00 WRITE 0 */
    abort_code = set_Profile_velocity(*(UNS32*)value);
    /* USER CODE BEGIN 0x6081 0x00 WRITE 1 */
    
    /* USER CODE END 0x6081 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x6081_Profile_velocity_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x6081 0x00 READ 0 */
    
    /* USER CODE END 0x6081 0x00 READ 0 */
    *(UNS32*)value = get_Profile_velocity();
    /* USER CODE BEGIN 0x6081 0x00 READ 1 */
    
    /* USER CODE END 0x6081 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x6083_Profile_acceleration_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x6083 0x00 WRITE 0 */
    
    /* USER CODE END 0x6083 0x00 WRITE 0 */
    abort_code = set_Profile_acceleration(*(UNS32*)value);
    /* USER CODE BEGIN 0x6083 0x00 WRITE 1 */
    
    /* USER CODE END 0x6083 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x6083_Profile_acceleration_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x6083 0x00 READ 0 */
    
    /* USER CODE END 0x6083 0x00 READ 0 */
    *(UNS32*)value = get_Profile_acceleration();
    /* USER CODE BEGIN 0x6083 0x00 READ 1 */
    
    /* USER CODE END 0x6083 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x6084_Profile_deceleration_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x6084 0x00 WRITE 0 */
    
    /* USER CODE END 0x6084 0x00 WRITE 0 */
    abort_code = set_Profile_deceleration(*(UNS32*)value);
    /* USER CODE BEGIN 0x6084 0x00 WRITE 1 */
    
    /* USER CODE END 0x6084 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x6084_Profile_deceleration_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x6084 0x00 READ 0 */
    
    /* USER CODE END 0x6084 0x00 READ 0 */
    *(UNS32*)value = get_Profile_deceleration();
    /* USER CODE BEGIN 0x6084 0x00 READ 1 */
    
    /* USER CODE END 0x6084 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x6085_Quick_stop_deceleration_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x6085 0x00 WRITE 0 */
    
    /* USER CODE END 0x6085 0x00 WRITE 0 */
    abort_code = set_Quick_stop_deceleration(*(UNS32*)value);
    /* USER CODE BEGIN 0x6085 0x00 WRITE 1 */
    
    /* USER CODE END 0x6085 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x6085_Quick_stop_deceleration_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x6085 0x00 READ 0 */
    
    /* USER CODE END 0x6085 0x00 READ 0 */
    *(UNS32*)value = get_Quick_stop_deceleration();
    /* USER CODE BEGIN 0x6085 0x00 READ 1 */
    
    /* USER CODE END 0x6085 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x60C5_Max_acceleration_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x60C5 0x00 WRITE 0 */
    
    /* USER CODE END 0x60C5 0x00 WRITE 0 */
    abort_code = set_Max_acceleration(*(UNS32*)value);
    /* USER CODE BEGIN 0x60C5 0x00 WRITE 1 */
    
    /* USER CODE END 0x60C5 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x60C5_Max_acceleration_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x60C5 0x00 READ 0 */
    
    /* USER CODE END 0x60C5 0x00 READ 0 */
    *(UNS32*)value = get_Max_acceleration();
    /* USER CODE BEGIN 0x60C5 0x00 READ 1 */
    
    /* USER CODE END 0x60C5 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x60C6_Max_deceleration_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x60C6 0x00 WRITE 0 */
    
    /* USER CODE END 0x60C6 0x00 WRITE 0 */
    abort_code = set_Max_deceleration(*(UNS32*)value);
    /* USER CODE BEGIN 0x60C6 0x00 WRITE 1 */
    
    /* USER CODE END 0x60C6 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x60C6_Max_deceleration_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x60C6 0x00 READ 0 */
    
    /* USER CODE END 0x60C6 0x00 READ 0 */
    *(UNS32*)value = get_Max_deceleration();
    /* USER CODE BEGIN 0x60C6 0x00 READ 1 */
    
    /* USER CODE END 0x60C6 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x607C_Home_offset_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x607C 0x00 WRITE 0 */

    /* USER CODE END 0x607C 0x00 WRITE 0 */
    abort_code = set_Home_offset(*(INTEGER32*)value);
    /* USER CODE BEGIN 0x607C 0x00 WRITE 1 */

    /* USER CODE END 0x607C 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x607C_Home_offset_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x607C 0x00 READ 0 */
    
    /* USER CODE END 0x607C 0x00 READ 0 */
    *(INTEGER32*)value = get_Home_offset();
    /* USER CODE BEGIN 0x607C 0x00 READ 1 */
    
    /* USER CODE END 0x607C 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x6098_Homing_method_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x6098 0x00 WRITE 0 */
    
    /* USER CODE END 0x6098 0x00 WRITE 0 */
    abort_code = set_Homing_method(*(INTEGER8*)value);
    /* USER CODE BEGIN 0x6098 0x00 WRITE 1 */
    
    /* USER CODE END 0x6098 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x6098_Homing_method_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x6098 0x00 READ 0 */
    
    /* USER CODE END 0x6098 0x00 READ 0 */
    *(INTEGER8*)value = get_Homing_method();
    /* USER CODE BEGIN 0x6098 0x00 READ 1 */
    
    /* USER CODE END 0x6098 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x6099_Homing_speeds_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    if ((get_Statusword() & STATUS_WORD_ENABLE_MASK) == STATUS_WORD_ENABLE_MASK)
    {
        return ABORT_CODE_DRIVE_STATE_DENIED;
    }
    switch(subindex)
    {
        case 0x00:
    /* USER CODE BEGIN 0x6099 0x00 WRITE 0 */
    
    /* USER CODE END 0x6099 0x00 WRITE 0 */
            abort_code = ABORT_CODE_CANNOT_WRITE_RO_OBJECT;
    /* USER CODE BEGIN 0x6099 0x00 WRITE 1 */
    
    /* USER CODE END 0x6099 0x00 WRITE 1 */
            break;
        case 0x01:
    /* USER CODE BEGIN 0x6099 0x01 WRITE 0 */
    
    /* USER CODE END 0x6099 0x01 WRITE 0 */
            abort_code = set_Homing_speeds_Speed_for_switch_search(*(UNS32*)value);
    /* USER CODE BEGIN 0x6099 0x01 WRITE 1 */
    
    /* USER CODE END 0x6099 0x01 WRITE 1 */
            break;
        case 0x02:
    /* USER CODE BEGIN 0x6099 0x02 WRITE 0 */
    
    /* USER CODE END 0x6099 0x02 WRITE 0 */
            abort_code = set_Homing_speeds_Speed_for_zero_search(*(UNS32*)value);
    /* USER CODE BEGIN 0x6099 0x02 WRITE 1 */
    
    /* USER CODE END 0x6099 0x02 WRITE 1 */
            break;
        default:
            abort_code = ABORT_CODE_SUB_INDEX_NOT_EXIST;
            break;
    }
    return abort_code;
}
UNS32 OD_0x6099_Homing_speeds_Read_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    switch(subindex)
    {
        case 0x00:
    /* USER CODE BEGIN 0x6099 0x00 READ 0 */
    
    /* USER CODE END 0x6099 0x00 READ 0 */
            *(UNS8*)value = 0x2;
            abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x6099 0x00 READ 1 */
    
    /* USER CODE END 0x6099 0x00 READ 1 */
            break;
        case 0x01:
    /* USER CODE BEGIN 0x6099 0x01 READ 0 */
    
    /* USER CODE END 0x6099 0x01 READ 0 */
            *(UNS32*)value = get_Homing_speeds_Speed_for_switch_search();
    /* USER CODE BEGIN 0x6099 0x01 READ 1 */
    
    /* USER CODE END 0x6099 0x01 READ 1 */
            break;
        case 0x02:
    /* USER CODE BEGIN 0x6099 0x02 READ 0 */
    
    /* USER CODE END 0x6099 0x02 READ 0 */
            *(UNS32*)value = get_Homing_speeds_Speed_for_zero_search();
    /* USER CODE BEGIN 0x6099 0x02 READ 1 */
    
    /* USER CODE END 0x6099 0x02 READ 1 */
            break;
        default:
            abort_code = ABORT_CODE_SUB_INDEX_NOT_EXIST;
            break;
    }
    return abort_code;
}
UNS32 OD_0x609A_Homing_acceleration_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x609A 0x00 WRITE 0 */

    /* USER CODE END 0x609A 0x00 WRITE 0 */
    abort_code = set_Homing_acceleration(*(UNS32*)value);
    /* USER CODE BEGIN 0x609A 0x00 WRITE 1 */

    /* USER CODE END 0x609A 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x609A_Homing_acceleration_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x609A 0x00 READ 0 */
    
    /* USER CODE END 0x609A 0x00 READ 0 */
    *(UNS32*)value = get_Homing_acceleration();
    /* USER CODE BEGIN 0x609A 0x00 READ 1 */
    
    /* USER CODE END 0x609A 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x6062_Position_demand_value_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x6062 0x00 READ 0 */
    
    /* USER CODE END 0x6062 0x00 READ 0 */
    *(INTEGER32*)value = get_Position_demand_value();
    /* USER CODE BEGIN 0x6062 0x00 READ 1 */
    
    /* USER CODE END 0x6062 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x6063_Position_actual_value_inc_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x6063 0x00 READ 0 */
    
    /* USER CODE END 0x6063 0x00 READ 0 */
    *(INTEGER32*)value = get_Position_actual_value_inc();
    /* USER CODE BEGIN 0x6063 0x00 READ 1 */
    
    /* USER CODE END 0x6063 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x6064_Position_actual_value_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x6064 0x00 READ 0 */
    
    /* USER CODE END 0x6064 0x00 READ 0 */
    *(INTEGER32*)value = get_Position_actual_value();
    /* USER CODE BEGIN 0x6064 0x00 READ 1 */
    
    /* USER CODE END 0x6064 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x6065_Following_error_window_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x6065 0x00 WRITE 0 */
    
    /* USER CODE END 0x6065 0x00 WRITE 0 */
    abort_code = set_Following_error_window(*(UNS32*)value);
    /* USER CODE BEGIN 0x6065 0x00 WRITE 1 */
    
    /* USER CODE END 0x6065 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x6065_Following_error_window_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x6065 0x00 READ 0 */
    
    /* USER CODE END 0x6065 0x00 READ 0 */
    *(UNS32*)value = get_Following_error_window();
    /* USER CODE BEGIN 0x6065 0x00 READ 1 */
    
    /* USER CODE END 0x6065 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x6066_Following_error_time_out_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x6066 0x00 WRITE 0 */
    
    /* USER CODE END 0x6066 0x00 WRITE 0 */
    abort_code = set_Following_error_time_out(*(UNS16*)value);
    /* USER CODE BEGIN 0x6066 0x00 WRITE 1 */
    
    /* USER CODE END 0x6066 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x6066_Following_error_time_out_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x6066 0x00 READ 0 */
    
    /* USER CODE END 0x6066 0x00 READ 0 */
    *(UNS16*)value = get_Following_error_time_out();
    /* USER CODE BEGIN 0x6066 0x00 READ 1 */
    
    /* USER CODE END 0x6066 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x6067_Position_window_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x6067 0x00 WRITE 0 */
    
    /* USER CODE END 0x6067 0x00 WRITE 0 */
    abort_code = set_Position_window(*(UNS32*)value);
    /* USER CODE BEGIN 0x6067 0x00 WRITE 1 */
    
    /* USER CODE END 0x6067 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x6067_Position_window_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x6067 0x00 READ 0 */
    
    /* USER CODE END 0x6067 0x00 READ 0 */
    *(UNS32*)value = get_Position_window();
    /* USER CODE BEGIN 0x6067 0x00 READ 1 */
    
    /* USER CODE END 0x6067 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x6068_Position_window_time_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x6068 0x00 WRITE 0 */
    
    /* USER CODE END 0x6068 0x00 WRITE 0 */
    abort_code = set_Position_window_time(*(UNS16*)value);
    /* USER CODE BEGIN 0x6068 0x00 WRITE 1 */
    
    /* USER CODE END 0x6068 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x6068_Position_window_time_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x6068 0x00 READ 0 */
    
    /* USER CODE END 0x6068 0x00 READ 0 */
    *(UNS16*)value = get_Position_window_time();
    /* USER CODE BEGIN 0x6068 0x00 READ 1 */
    
    /* USER CODE END 0x6068 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x60F4_Following_error_actual_value_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x60F4 0x00 READ 0 */
    
    /* USER CODE END 0x60F4 0x00 READ 0 */
    *(INTEGER32*)value = get_Following_error_actual_value();
    /* USER CODE BEGIN 0x60F4 0x00 READ 1 */
    
    /* USER CODE END 0x60F4 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x60C2_Interpolation_time_period_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    if ((get_Statusword() & STATUS_WORD_ENABLE_MASK) == STATUS_WORD_ENABLE_MASK)
    {
        return ABORT_CODE_DRIVE_STATE_DENIED;
    }
    switch(subindex)
    {
        case 0x00:
    /* USER CODE BEGIN 0x60C2 0x00 WRITE 0 */
    
    /* USER CODE END 0x60C2 0x00 WRITE 0 */
            abort_code = ABORT_CODE_CANNOT_WRITE_RO_OBJECT;
    /* USER CODE BEGIN 0x60C2 0x00 WRITE 1 */
    
    /* USER CODE END 0x60C2 0x00 WRITE 1 */
            break;
        case 0x01:
    /* USER CODE BEGIN 0x60C2 0x01 WRITE 0 */
    
    /* USER CODE END 0x60C2 0x01 WRITE 0 */
            abort_code = set_Interpolation_time_period_Ip_time_units(*(UNS8*)value);
    /* USER CODE BEGIN 0x60C2 0x01 WRITE 1 */
    
    /* USER CODE END 0x60C2 0x01 WRITE 1 */
            break;
        case 0x02:
    /* USER CODE BEGIN 0x60C2 0x02 WRITE 0 */
    
    /* USER CODE END 0x60C2 0x02 WRITE 0 */
            abort_code = set_Interpolation_time_period_Ip_time_index(*(INTEGER8*)value);
    /* USER CODE BEGIN 0x60C2 0x02 WRITE 1 */
    
    /* USER CODE END 0x60C2 0x02 WRITE 1 */
            break;
        default:
            abort_code = ABORT_CODE_SUB_INDEX_NOT_EXIST;
            break;
    }
    return abort_code;
}
UNS32 OD_0x60C2_Interpolation_time_period_Read_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    switch(subindex)
    {
        case 0x00:
    /* USER CODE BEGIN 0x60C2 0x00 READ 0 */
    
    /* USER CODE END 0x60C2 0x00 READ 0 */
            *(UNS8*)value = 0x2;
            abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x60C2 0x00 READ 1 */
    
    /* USER CODE END 0x60C2 0x00 READ 1 */
            break;
        case 0x01:
    /* USER CODE BEGIN 0x60C2 0x01 READ 0 */
    
    /* USER CODE END 0x60C2 0x01 READ 0 */
            *(UNS8*)value = get_Interpolation_time_period_Ip_time_units();
    /* USER CODE BEGIN 0x60C2 0x01 READ 1 */
    
    /* USER CODE END 0x60C2 0x01 READ 1 */
            break;
        case 0x02:
    /* USER CODE BEGIN 0x60C2 0x02 READ 0 */
    
    /* USER CODE END 0x60C2 0x02 READ 0 */
            *(INTEGER8*)value = get_Interpolation_time_period_Ip_time_index();
    /* USER CODE BEGIN 0x60C2 0x02 READ 1 */
    
    /* USER CODE END 0x60C2 0x02 READ 1 */
            break;
        default:
            abort_code = ABORT_CODE_SUB_INDEX_NOT_EXIST;
            break;
    }
    return abort_code;
}
UNS32 OD_0x606B_Velocity_demand_value_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x606B 0x00 READ 0 */
    
    /* USER CODE END 0x606B 0x00 READ 0 */
    *(INTEGER32*)value = get_Velocity_demand_value();
    /* USER CODE BEGIN 0x606B 0x00 READ 1 */
    
    /* USER CODE END 0x606B 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x606C_Velocity_actual_value_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x606C 0x00 READ 0 */
    
    /* USER CODE END 0x606C 0x00 READ 0 */
    *(INTEGER32*)value = get_Velocity_actual_value();
    /* USER CODE BEGIN 0x606C 0x00 READ 1 */
    
    /* USER CODE END 0x606C 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x606D_Velocity_window_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x606D 0x00 WRITE 0 */
    
    /* USER CODE END 0x606D 0x00 WRITE 0 */
    abort_code = set_Velocity_window(*(UNS16*)value);
    /* USER CODE BEGIN 0x606D 0x00 WRITE 1 */
    
    /* USER CODE END 0x606D 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x606D_Velocity_window_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x606D 0x00 READ 0 */
    
    /* USER CODE END 0x606D 0x00 READ 0 */
    *(UNS16*)value = get_Velocity_window();
    /* USER CODE BEGIN 0x606D 0x00 READ 1 */
    
    /* USER CODE END 0x606D 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x606E_Velocity_window_time_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x606E 0x00 WRITE 0 */
    
    /* USER CODE END 0x606E 0x00 WRITE 0 */
    abort_code = set_Velocity_window_time(*(UNS16*)value);
    /* USER CODE BEGIN 0x606E 0x00 WRITE 1 */
    
    /* USER CODE END 0x606E 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x606E_Velocity_window_time_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x606E 0x00 READ 0 */
    
    /* USER CODE END 0x606E 0x00 READ 0 */
    *(UNS16*)value = get_Velocity_window_time();
    /* USER CODE BEGIN 0x606E 0x00 READ 1 */
    
    /* USER CODE END 0x606E 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x606F_Velocity_threshold_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x606F 0x00 WRITE 0 */
    
    /* USER CODE END 0x606F 0x00 WRITE 0 */
    abort_code = set_Velocity_threshold(*(UNS16*)value);
    /* USER CODE BEGIN 0x606F 0x00 WRITE 1 */
    
    /* USER CODE END 0x606F 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x606F_Velocity_threshold_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x606F 0x00 READ 0 */
    
    /* USER CODE END 0x606F 0x00 READ 0 */
    *(UNS16*)value = get_Velocity_threshold();
    /* USER CODE BEGIN 0x606F 0x00 READ 1 */
    
    /* USER CODE END 0x606F 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x6070_Velocity_threshold_time_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x6070 0x00 WRITE 0 */
    
    /* USER CODE END 0x6070 0x00 WRITE 0 */
    abort_code = set_Velocity_threshold_time(*(UNS16*)value);
    /* USER CODE BEGIN 0x6070 0x00 WRITE 1 */
    
    /* USER CODE END 0x6070 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x6070_Velocity_threshold_time_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x6070 0x00 READ 0 */
    
    /* USER CODE END 0x6070 0x00 READ 0 */
    *(UNS16*)value = get_Velocity_threshold_time();
    /* USER CODE BEGIN 0x6070 0x00 READ 1 */
    
    /* USER CODE END 0x6070 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x60FF_Target_velocity_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x60FF 0x00 WRITE 0 */
    
    /* USER CODE END 0x60FF 0x00 WRITE 0 */
    abort_code = set_Target_velocity(*(INTEGER32*)value);
    /* USER CODE BEGIN 0x60FF 0x00 WRITE 1 */
    
    /* USER CODE END 0x60FF 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x60FF_Target_velocity_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x60FF 0x00 READ 0 */
    
    /* USER CODE END 0x60FF 0x00 READ 0 */
    *(INTEGER32*)value = get_Target_velocity();
    /* USER CODE BEGIN 0x60FF 0x00 READ 1 */
    
    /* USER CODE END 0x60FF 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x6071_Target_torque_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x6071 0x00 WRITE 0 */
    
    /* USER CODE END 0x6071 0x00 WRITE 0 */
    abort_code = set_Target_torque(*(INTEGER16*)value);
    /* USER CODE BEGIN 0x6071 0x00 WRITE 1 */
    
    /* USER CODE END 0x6071 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x6071_Target_torque_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x6071 0x00 READ 0 */
    
    /* USER CODE END 0x6071 0x00 READ 0 */
    *(INTEGER16*)value = get_Target_torque();
    /* USER CODE BEGIN 0x6071 0x00 READ 1 */
    
    /* USER CODE END 0x6071 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x6072_Max_torque_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x6072 0x00 WRITE 0 */
    
    /* USER CODE END 0x6072 0x00 WRITE 0 */
    abort_code = set_Max_torque(*(UNS16*)value);
    /* USER CODE BEGIN 0x6072 0x00 WRITE 1 */
    
    /* USER CODE END 0x6072 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x6072_Max_torque_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x6072 0x00 READ 0 */
    
    /* USER CODE END 0x6072 0x00 READ 0 */
    *(UNS16*)value = get_Max_torque();
    /* USER CODE BEGIN 0x6072 0x00 READ 1 */
    
    /* USER CODE END 0x6072 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x6073_Max_current_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x6073 0x00 WRITE 0 */
    
    /* USER CODE END 0x6073 0x00 WRITE 0 */
    abort_code = set_Max_current(*(UNS16*)value);
    /* USER CODE BEGIN 0x6073 0x00 WRITE 1 */
    
    /* USER CODE END 0x6073 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x6073_Max_current_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x6073 0x00 READ 0 */
    
    /* USER CODE END 0x6073 0x00 READ 0 */
    *(UNS16*)value = get_Max_current();
    /* USER CODE BEGIN 0x6073 0x00 READ 1 */
    
    /* USER CODE END 0x6073 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x6074_Torque_demand_value_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x6074 0x00 READ 0 */
    
    /* USER CODE END 0x6074 0x00 READ 0 */
    *(INTEGER16*)value = get_Torque_demand_value();
    /* USER CODE BEGIN 0x6074 0x00 READ 1 */
    
    /* USER CODE END 0x6074 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x6075_Motor_rated_current_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x6075 0x00 WRITE 0 */
    
    /* USER CODE END 0x6075 0x00 WRITE 0 */
    abort_code = set_Motor_rated_current(*(UNS32*)value);
    /* USER CODE BEGIN 0x6075 0x00 WRITE 1 */
    
    /* USER CODE END 0x6075 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x6075_Motor_rated_current_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x6075 0x00 READ 0 */
    
    /* USER CODE END 0x6075 0x00 READ 0 */
    *(UNS32*)value = get_Motor_rated_current();
    /* USER CODE BEGIN 0x6075 0x00 READ 1 */
    
    /* USER CODE END 0x6075 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x6076_Motor_rated_torque_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x6076 0x00 WRITE 0 */
    
    /* USER CODE END 0x6076 0x00 WRITE 0 */
    abort_code = set_Motor_rated_torque(*(UNS32*)value);
    /* USER CODE BEGIN 0x6076 0x00 WRITE 1 */
    
    /* USER CODE END 0x6076 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x6076_Motor_rated_torque_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x6076 0x00 READ 0 */
    
    /* USER CODE END 0x6076 0x00 READ 0 */
    *(UNS32*)value = get_Motor_rated_torque();
    /* USER CODE BEGIN 0x6076 0x00 READ 1 */
    
    /* USER CODE END 0x6076 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x6077_Torque_actual_value_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x6077 0x00 READ 0 */
    
    /* USER CODE END 0x6077 0x00 READ 0 */
    *(INTEGER16*)value = get_Torque_actual_value();
    /* USER CODE BEGIN 0x6077 0x00 READ 1 */
    
    /* USER CODE END 0x6077 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x6078_Current_actual_value_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x6078 0x00 READ 0 */
    
    /* USER CODE END 0x6078 0x00 READ 0 */
    *(INTEGER16*)value = get_Current_actual_value();
    /* USER CODE BEGIN 0x6078 0x00 READ 1 */
    
    /* USER CODE END 0x6078 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x6079_DC_link_circuit_voltage_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x6079 0x00 READ 0 */
    
    /* USER CODE END 0x6079 0x00 READ 0 */
    *(UNS32*)value = get_DC_link_circuit_voltage();
    /* USER CODE BEGIN 0x6079 0x00 READ 1 */
    
    /* USER CODE END 0x6079 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x6087_Torque_slope_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x6087 0x00 WRITE 0 */
    
    /* USER CODE END 0x6087 0x00 WRITE 0 */
    abort_code = set_Torque_slope(*(UNS32*)value);
    /* USER CODE BEGIN 0x6087 0x00 WRITE 1 */
    
    /* USER CODE END 0x6087 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x6087_Torque_slope_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x6087 0x00 READ 0 */
    
    /* USER CODE END 0x6087 0x00 READ 0 */
    *(UNS32*)value = get_Torque_slope();
    /* USER CODE BEGIN 0x6087 0x00 READ 1 */
    
    /* USER CODE END 0x6087 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x60B0_Position_offset_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x60B0 0x00 WRITE 0 */

    /* USER CODE END 0x60B0 0x00 WRITE 0 */
    abort_code = set_Position_offset(*(INTEGER32*)value);
    /* USER CODE BEGIN 0x60B0 0x00 WRITE 1 */

    /* USER CODE END 0x60B0 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x60B0_Position_offset_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x60B0 0x00 READ 0 */
    
    /* USER CODE END 0x60B0 0x00 READ 0 */
    *(INTEGER32*)value = get_Position_offset();
    /* USER CODE BEGIN 0x60B0 0x00 READ 1 */
    
    /* USER CODE END 0x60B0 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x60B1_Velocity_offset_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x60B1 0x00 WRITE 0 */

    /* USER CODE END 0x60B1 0x00 WRITE 0 */
    abort_code = set_Velocity_offset(*(INTEGER32*)value);
    /* USER CODE BEGIN 0x60B1 0x00 WRITE 1 */

    /* USER CODE END 0x60B1 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x60B1_Velocity_offset_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x60B1 0x00 READ 0 */
    
    /* USER CODE END 0x60B1 0x00 READ 0 */
    *(INTEGER32*)value = get_Velocity_offset();
    /* USER CODE BEGIN 0x60B1 0x00 READ 1 */
    
    /* USER CODE END 0x60B1 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x60B2_Torque_offset_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x60B2 0x00 WRITE 0 */

    /* USER CODE END 0x60B2 0x00 WRITE 0 */
    abort_code = set_Torque_offset(*(INTEGER16*)value);
    /* USER CODE BEGIN 0x60B2 0x00 WRITE 1 */

    /* USER CODE END 0x60B2 0x00 WRITE 1 */
    return abort_code;
}
UNS32 OD_0x60B2_Torque_offset_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x60B2 0x00 READ 0 */
    
    /* USER CODE END 0x60B2 0x00 READ 0 */
    *(INTEGER16*)value = get_Torque_offset();
    /* USER CODE BEGIN 0x60B2 0x00 READ 1 */
    
    /* USER CODE END 0x60B2 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x60FD_Digital_inputs_Read_Callback(UNS8 subindex, void *value)
{
    /* USER CODE BEGIN 0x60FD 0x00 READ 0 */
    
    /* USER CODE END 0x60FD 0x00 READ 0 */
    *(UNS32*)value = get_Digital_inputs();
    /* USER CODE BEGIN 0x60FD 0x00 READ 1 */
    
    /* USER CODE END 0x60FD 0x00 READ 1 */
    return ABORT_CODE_SUCCESSFUL;
}
UNS32 OD_0x60FE_Digital_outputs_Write_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    switch(subindex)
    {
        case 0x00:
    /* USER CODE BEGIN 0x60FE 0x00 WRITE 0 */
    
    /* USER CODE END 0x60FE 0x00 WRITE 0 */
            abort_code = ABORT_CODE_CANNOT_WRITE_RO_OBJECT;
    /* USER CODE BEGIN 0x60FE 0x00 WRITE 1 */
    
    /* USER CODE END 0x60FE 0x00 WRITE 1 */
            break;
        case 0x01:
    /* USER CODE BEGIN 0x60FE 0x01 WRITE 0 */
    
    /* USER CODE END 0x60FE 0x01 WRITE 0 */
            abort_code = set_Digital_outputs_Physical_outputs(*(UNS32*)value);
    /* USER CODE BEGIN 0x60FE 0x01 WRITE 1 */
    
    /* USER CODE END 0x60FE 0x01 WRITE 1 */
            break;
        case 0x02:
    /* USER CODE BEGIN 0x60FE 0x02 WRITE 0 */
    
    /* USER CODE END 0x60FE 0x02 WRITE 0 */
            abort_code = set_Digital_outputs_Bit_mask(*(UNS32*)value);
    /* USER CODE BEGIN 0x60FE 0x02 WRITE 1 */
    
    /* USER CODE END 0x60FE 0x02 WRITE 1 */
            break;
        default:
            abort_code = ABORT_CODE_SUB_INDEX_NOT_EXIST;
            break;
    }
    return abort_code;
}
UNS32 OD_0x60FE_Digital_outputs_Read_Callback(UNS8 subindex, void *value)
{
    UNS32 abort_code = ABORT_CODE_SUCCESSFUL;
    switch(subindex)
    {
        case 0x00:
    /* USER CODE BEGIN 0x60FE 0x00 READ 0 */
    
    /* USER CODE END 0x60FE 0x00 READ 0 */
            *(UNS8*)value = 0x2;
            abort_code = ABORT_CODE_SUCCESSFUL;
    /* USER CODE BEGIN 0x60FE 0x00 READ 1 */
    
    /* USER CODE END 0x60FE 0x00 READ 1 */
            break;
        case 0x01:
    /* USER CODE BEGIN 0x60FE 0x01 READ 0 */
    
    /* USER CODE END 0x60FE 0x01 READ 0 */
            *(UNS32*)value = get_Digital_outputs_Physical_outputs();
    /* USER CODE BEGIN 0x60FE 0x01 READ 1 */
    
    /* USER CODE END 0x60FE 0x01 READ 1 */
            break;
        case 0x02:
    /* USER CODE BEGIN 0x60FE 0x02 READ 0 */
    
    /* USER CODE END 0x60FE 0x02 READ 0 */
            *(UNS32*)value = get_Digital_outputs_Bit_mask();
    /* USER CODE BEGIN 0x60FE 0x02 READ 1 */
    
    /* USER CODE END 0x60FE 0x02 READ 1 */
            break;
        default:
            abort_code = ABORT_CODE_SUB_INDEX_NOT_EXIST;
            break;
    }
    return abort_code;
}
