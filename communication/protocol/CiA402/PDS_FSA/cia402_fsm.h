/*  CiA Draft Standard Proposal 402
    Drives and motion control device profile, Part 2: Operation modes and application data
    Version: 3.0, 14 December 2007
*/

#ifndef CIA402_FSM_H
#define CIA402_FSM_H

#include "cia402_common.h"

typedef enum
{
    kStart = 0,
    kNotReadyToSwitchOn,
    kSwitchOnDisable,
    kReadyToSwitchOn,
    kSwitchOn,
    kOperationEnable,
    kQuickStopActive,
    kFaultReactionActive,
    kFault,
    kAnyState
}Cia402State;


//Chapter 8, Table 27 - Command Coding
typedef enum
{
    kOd6040_StandardMark = 143,

    kOd6040_ShutdownMark = 135,
    kOd6040_Shutdown = 6,                   //Transitions 2,6,8

    kOd6040_SwitchOn = 7,                   //Transitions 3

    kOd6040_SwitchOn_EnableOperation = 15,  //Transitions 3,4（note:Automatic transition to Enable operation state after executing SWITCHED ON state functionality）

    kOd6040_DisableVoltageMark = 130,
    kOd6040_DisableVoltage = 0,             //Transitions 7,9,10,12

    kOd6040_QuickStopMark = 134,
    kOd6040_QuickStop = 2,                  //Transitions 7,10,11

    kOd6040_DisableOperation = 7,           //Transitions 5

    kOd6040_EnableOperation = 15,           //Transitions 4，16

    kOd6040_FaultReset = 128,               //Transitions 15

    kOd6040_Halt = 256,                 //bit 8   暂停使能位
    kOd6040_NewSetPoint = 16,           //bit 4
    kOd6040_HomingOperationStart = 16,  //bit 4
    kOd6040_EnableInterpolation = 16,   //bit 4
    kOd6040_ChangeSetImmediately = 32,  //bit 5
    kOd6040_Relative = 64,              //使能相对位置  //bit 6
}CiakOd6040;


typedef bool (*EventFunction)(void);
typedef void (*ActionFunction)(void);

typedef struct {
    Cia402State CurrentState;
    Cia402State NextState;
    bool auto_transition;   //自动转换标志，true表示自动转换，false表示控制字跳转
    EventFunction event;
    ActionFunction action;
}FSATransition;

void PDS_FSA_Run(void);
void ControlwordChange_PDAS_FSA(void);
Cia402State get_CurrentState(void);

#endif // CIA402_FSM_H