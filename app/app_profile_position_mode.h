#ifndef APP_PROFILE_POSITION_MODE_H
#define APP_PROFILE_POSITION_MODE_H

#include "app_data_type_define.h"

#include "app_trajectory.h"
#include "app_status_check.h"

typedef struct
{
    APP_CONTROL_WORD now_Controlword;               // 当前控制字
    APP_CONTROL_WORD pre_Controlword;               // 前一次控制字
    POS_TRAJECTORY_DATA traj;                       // 位置规划器
    CheckStatusVal_t check_status_val;              // 检查状态
    APP_Emergency_Brake_Mode emergency_brake_mode;  // 紧急制动模式
    bool start_upedge_latch;                        // 启动沿锁存
    bool start_upedge_state;                        // 启动沿状态
    int64_t position_target_last;                   // 上一次目标位置缓存
    int64_t pos_tar_p_add;                          // 目标位置增量
} PpMode_t;

void set_app_start_upedge_state(bool state);  //可由外部调用设置启动沿状态

AppResult PpModeInit(void);
AppResult PpModeStart(void);
AppResult PpModeRun(void);
AppResult PpModeStop(void);

#endif // APP_PROFILE_POSITION_MODE_H
