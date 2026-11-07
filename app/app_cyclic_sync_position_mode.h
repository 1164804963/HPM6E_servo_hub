#ifndef APP_CYCLIC_SYNC_POSITION_MODE_H
#define APP_CYCLIC_SYNC_POSITION_MODE_H

#include "app_data_type_define.h"

#include "app_trajectory.h"
#include "app_status_check.h"

typedef struct
{
    APP_CONTROL_WORD now_Controlword;               // 当前控制字
    APP_CONTROL_WORD pre_Controlword;               // 前一次控制字
    CSP_TRAJECTORY_DATA traj;                       // 位置规划器
    CheckStatusVal_t check_status_val;              // 检查状态
    APP_Emergency_Brake_Mode emergency_brake_mode;  // 紧急制动模式
    int64_t pos_tar_last_p;                         // 上一次目标位置缓存
    int64_t pos_tar_add_p;                          // 目标位置增量p
    int64_t pos_tar_p;                              // 位置用户目标值p
} CspMode_t;

AppResult CspModeInit(void);
AppResult CspModeStart(void);
AppResult CspModeRun(void);
AppResult CspModeStop(void);

#endif // APP_CYCLIC_SYNC_POSITION_MODE_H
