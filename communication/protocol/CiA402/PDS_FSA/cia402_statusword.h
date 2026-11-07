#ifndef CIA402_STATUSWORD_H
#define CIA402_STATUSWORD_H

#include "cia402_common.h"

typedef enum
{
    kOd6041_StateMark = 111,  //状态相关掩码
    kOd6041_Start = 111,      /* Default value */
    kOd6041_NotReadyToSwitchOn = 0,
    kOd6041_SwitchedOnDisable = 64,
    kOd6041_ReadyToSwitchOn = 33,
    kOd6041_SwitchedOn = 35,
    kOd6041_OperationEnable = 39,
    kOd6041_QuickStopActive = 7, //修正该值
    kOd6041_FaultReactionActive = 15,
    kOd6041_Fault = 8,
    kOd6041_StateSwitch = 256,
    kOd6041_VoltageEnabled = 16,
    kOd6041_Warning = 128,
    kOd6041_Remote = 512,
    kOd6041_TargetReached = 1024,//bit10
    kOd6041_InternalLimitActive = 2048,

    /// 表示具体模式下 运行状态
    kOd6041_OperationModeMark = 12288,   //模式操作掩码
    kOd6041_SetPointAcknowledge = 4096,  //bit12
    kOd6041_FollowingError = 8192,       //bit13
    kOd6041_SpeedRunning = 4096,
    kOd6041_MaxSlippageError = 8192,
    kOd6041_HomingAttained = 4096,       //bit12
    kOd6041_HomingError = 8192,
    kOd6041_IpModeActive = 4096,
    kOd6041_DriveFollowCommandValue = 4096, //bit12 CSP、CSV、CST

    ///系统辨识掩码 kOd6041_IDENT_ERROR
    kOd6041_IdentStateMark = 49152,
    ///辨识空闲状态
    kOd6041_IdentIdle = 0,
    ///辨识成功
    kOd6041_IdentSuccess = 1,
    ///辨识运行中
    kOd6041_IdentRunning = 2,
    ///辨识错误 具体原因查询错误代码
    kOd6041_IdentError = 3,
}Od6041Mask;

typedef struct {
    int8_t op_mode;        // 运行模式
    uint16_t bit_mask;         // 对应的位掩码
    bool (*check_state)(void); // 检查状态的函数指针
} StateTableEntry;

void UpdateStatusword(void);

//允许特殊情况下,在其它应用代码更新状态字
void SpecificModeStatuswordUpdate(Od6041Mask status_bit, bool state);

bool get_velocity_zero_state(void);

#endif // CIA402_STATUSWORD_UPDATE_H