#ifndef APP_PROFILE_TORQUE_MODE_H
#define APP_PROFILE_TORQUE_MODE_H

#include "app_data_type_define.h"

#include "app_trajectory.h"
#include "app_status_check.h"

typedef struct
{
    APP_CONTROL_WORD now_Controlword;               // 当前控制字
    APP_CONTROL_WORD pre_Controlword;               // 前一次控制字
    TORQUE_TRAJECTORY_DATA traj;                    // 力矩规划
    CheckStatusVal_t check_status_val;              // 检查状态
    APP_Emergency_Brake_Mode emergency_brake_mode;  // 紧急制动模式
} PtMode_t;

AppResult PtModeInit(void);
AppResult PtModeStart(void);
AppResult PtModeRun(void);
AppResult PtModeStop(void);

#endif // APP_PROFILE_TORQUE_MODE_H
