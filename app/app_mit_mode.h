#ifndef APP_MIT_MODE_H
#define APP_MIT_MODE_H

#include "app_data_type_define.h"

#include "app_trajectory.h"
#include "app_status_check.h"

typedef struct
{
    APP_CONTROL_WORD now_Controlword;               // 当前控制字
    APP_CONTROL_WORD pre_Controlword;               // 前一次控制字
    MIT_TRAJECTORY_DATA traj;                       // MIT规划器
    CheckStatusVal_t check_status_val;              // 检查状态
    APP_Emergency_Brake_Mode emergency_brake_mode;  // 紧急制动模式
    int64_t pos_tar_p_add;                          // 位置目标值增量
} MitMode_t;

AppResult MitModeInit(void);
AppResult MitModeStart(void);
AppResult MitModeRun(void);
AppResult MitModeStop(void);

#endif // APP_MIT_MODE_H
