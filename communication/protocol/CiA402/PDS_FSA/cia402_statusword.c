#include "cia402_statusword.h"
#include "cia402_common.h"
#include "cia402_fsm.h"
#include "Cia402_ObjectDictionary_Variable.h"
#include "app_status_check.h"

static CheckErrorCode_t kCheckErrorVal;
static CheckStatusVal_t kCheckStatusVal;

static bool check_voltage_state(void) {
    return true;  //TODO：获取底层电压的状态
}

static bool check_position_target_reached_state(void) {

    //控制字非暂停，由各个应用更新目标到达状态
    if (CIA402_READ_BIT(get_Controlword(), kOd6040_Halt) == 0)
    {
        return kCheckStatusVal.bits.position_target_reached;
    }
    return kCheckStatusVal.bits.target_reached;
}

static bool check_velocity_target_reached_state(void) {

    //控制字非暂停，由各个应用更新目标到达状态
    if (CIA402_READ_BIT(get_Controlword(), kOd6040_Halt) == 0)
    {
        return kCheckStatusVal.bits.velocity_target_reached;
    }
    return kCheckStatusVal.bits.target_reached;
}

static bool check_set_point_acknowledge_state(void) {

    //控制字暂停，bit12置false
    if (CIA402_READ_BIT(get_Controlword(), kOd6040_Halt) == kOd6040_Halt)
    {
        return false;
    }
    else if (CIA402_READ_BIT(get_Controlword(), kOd6040_NewSetPoint) == kOd6040_NewSetPoint)
    {
        return true;
    }
    return false;
}

static bool check_position_following_error_state(void) {
    return kCheckErrorVal.bits.position_following_error;
}

static bool check_velocity_zero_state(void) {
    return kCheckStatusVal.bits.velocity_zero;
}

static bool check_homing_attained_state(void) {
    return kCheckStatusVal.bits.homing_attained;
}

static bool check_drive_follow_command_value_state(void) {

    // 非使能或暂停状态下，置false
    if (get_CurrentState() != kOperationEnable || \
        CIA402_READ_BIT(get_Controlword(), kOd6040_Halt) == kOd6040_Halt)
    {
        return false;
    }
    return true;
}

// 定义状态表,kOd6060_ANY表示任何模式下均检测
static const StateTableEntry state_table[] = {
    {kOd6060_ANY, kOd6041_VoltageEnabled, check_voltage_state},
    {kOd6060_PPM, kOd6041_TargetReached, check_position_target_reached_state},
    {kOd6060_PPM, kOd6041_FollowingError, check_position_following_error_state},
    {kOd6060_PPM, kOd6041_SetPointAcknowledge, check_set_point_acknowledge_state},
    {kOd6060_PVM, kOd6041_TargetReached, check_velocity_target_reached_state},
    {kOd6060_PVM, kOd6041_SpeedRunning, check_velocity_zero_state},
    {kOd6060_CSP, kOd6041_FollowingError, check_position_following_error_state},
    {kOd6060_CSP, kOd6041_DriveFollowCommandValue, check_drive_follow_command_value_state},
    {kOd6060_CSV, kOd6041_DriveFollowCommandValue, check_drive_follow_command_value_state},
    {kOd6060_CST, kOd6041_DriveFollowCommandValue, check_drive_follow_command_value_state},
    {kOd6060_HM, kOd6041_HomingAttained, check_homing_attained_state}
};

//内部信号更新状态字
void UpdateStatusword(void) {

    uint16_t statusword = get_Statusword();

    CIA402_SET_BIT(statusword, kOd6041_Remote);

    const StateTableEntry *entry = state_table;

    kCheckStatusVal = (CheckStatusVal_t)app_get_check_status_val();
    kCheckErrorVal = (CheckErrorCode_t)app_get_check_error_val();

    for (uint8_t i = 0; i < CIA402_ARRAY_SIZE(state_table); i++, entry++) {
        if ((entry->op_mode == get_Modes_of_operation()) || (entry->op_mode == kOd6060_ANY)) {
            if (entry->check_state()) {
                CIA402_SET_BIT(statusword, entry->bit_mask);
            }
            else {
                CIA402_CLEAR_BIT(statusword, entry->bit_mask);
            }
        }
    }
    set_Statusword(statusword);
}

void SpecificModeStatuswordUpdate(Od6041Mask status_bit, bool state) {
    uint16_t statusword = get_Statusword();
    if(state) {
        CIA402_SET_BIT(statusword, status_bit);
    }
    else {
        CIA402_CLEAR_BIT(statusword, status_bit);
    }
    set_Statusword(statusword);
}

bool get_velocity_zero_state(void) {
    return kCheckStatusVal.bits.velocity_zero;
}