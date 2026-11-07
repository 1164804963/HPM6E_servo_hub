#ifndef APP_CYCLIC_SYNC_TORQUE_MODE_H
#define APP_CYCLIC_SYNC_TORQUE_MODE_H

#include "app_data_type_define.h"

#include "app_trajectory.h"
#include "app_status_check.h"

typedef struct
{
    APP_CONTROL_WORD now_Controlword;               // 当前控制字
    APP_CONTROL_WORD pre_Controlword;               // 前一次控制字
    CST_TRAJECTORY_DATA traj;                    // 力矩规划
    CheckStatusVal_t check_status_val;              // 检查状态
    APP_Emergency_Brake_Mode emergency_brake_mode;  // 紧急制动模式
} CstMode_t;

AppResult CstModeInit(void);
AppResult CstModeStart(void);
AppResult CstModeRun(void);
AppResult CstModeStop(void);

#endif // APP_CYCLIC_SYNC_TORQUE_MODE_H
