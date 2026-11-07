#ifndef APP_HOMING_MODE_H
#define APP_HOMING_MODE_H

#include "app_data_type_define.h"

#include "app_trajectory.h"
#include "app_status_check.h"

typedef enum
{
    HOMING_METHOD_MANUFACTURER_SPECIFIC = -1,     // 厂商特定回零方法 -128 ~ -1
    HOMING_METHOD_NO_HOMING_METHOD_ASSIGNED = 0,  // 未分配回零方法 0
    HOMING_METHOD_1 = 1,                          // 回零方法1
    HOMING_METHOD_2 = 2,                          // 回零方法2
    HOMING_METHOD_3 = 3,                          // 回零方法3
    HOMING_METHOD_4 = 4,                          // 回零方法4
    HOMING_METHOD_5 = 5,                          // 回零方法5
    HOMING_METHOD_6 = 6,                          // 回零方法6
    HOMING_METHOD_7 = 7,                          // 回零方法7
    HOMING_METHOD_8 = 8,                          // 回零方法8
    HOMING_METHOD_9 = 9,                          // 回零方法9
    HOMING_METHOD_10 = 10,                        // 回零方法10
    HOMING_METHOD_11 = 11,                        // 回零方法11
    HOMING_METHOD_12 = 12,                        // 回零方法12
    HOMING_METHOD_13 = 13,                        // 回零方法13
    HOMING_METHOD_14 = 14,                        // 回零方法14
    HOMING_METHOD_15 = 15,                        // 回零方法15
    HOMING_METHOD_16 = 16,                        // 回零方法16
    HOMING_METHOD_17 = 17,                        // 回零方法17
    HOMING_METHOD_18 = 18,                        // 回零方法18
    HOMING_METHOD_19 = 19,                        // 回零方法19
    HOMING_METHOD_20 = 20,                        // 回零方法20
    HOMING_METHOD_21 = 21,                        // 回零方法21
    HOMING_METHOD_22 = 22,                        // 回零方法22
    HOMING_METHOD_23 = 23,                        // 回零方法23
    HOMING_METHOD_24 = 24,                        // 回零方法24
    HOMING_METHOD_25 = 25,                        // 回零方法25
    HOMING_METHOD_26 = 26,                        // 回零方法26
    HOMING_METHOD_27 = 27,                        // 回零方法27
    HOMING_METHOD_28 = 28,                        // 回零方法28
    HOMING_METHOD_29 = 29,                        // 回零方法29
    HOMING_METHOD_30 = 30,                        // 回零方法30
    HOMING_METHOD_31 = 31,                        // 回零方法31
    HOMING_METHOD_32 = 32,                        // 回零方法32
    HOMING_METHOD_33 = 33,                        // 回零方法33
    HOMING_METHOD_34 = 34,                        // 回零方法34
    HOMING_METHOD_35 = 35,                        // 回零方法35
    HOMING_METHOD_36 = 36,                        // 回零方法36
    HOMING_METHOD_Reserved = 37,                  // 保留 回零方法 37 ~ 127
} HOMING_METHOD;

typedef enum
{
    HOMING_STEP_FAIL = -1,                        // 回零方法不存在/回零失败
    HOMING_STEP_INIT = 0,                         // 初始化状态
    HOMING_STEP_START = 1,                        // 起始状态
    HOMING_STEP_SEARCH_SWITCH = 2,                // 搜索开关
    HOMING_STEP_SEARCH_HOME_SWITCH = 3,           // 搜索回零开关
    HOMING_STEP_RETRACT_FROM_HOME_SWITCH = 4,     // 退出回零开关
    HOMING_STEP_CLOSE_TO_HOME_SWITCH = 5,         // 靠近回零开关
    HOMING_STEP_SEARCH_INDEX = 6,                 // 搜索Index信号
    HOMING_STEP_DECELERATE = 7,                   // 回零减速中
    HOMING_STEP_COMPLETE = 8,                     // 回零完成
} HOMING_STEP;

typedef struct
{
    APP_CONTROL_WORD now_Controlword;               // 当前控制字
    APP_CONTROL_WORD pre_Controlword;               // 前一次控制字
    SPEED_TRAJECTORY_DATA traj;                     // 回零模式使用速度规划器
    CheckStatusVal_t check_status_val;              // 检查状态
    APP_Emergency_Brake_Mode emergency_brake_mode;  // 紧急制动模式
    HOMING_METHOD method;                           // 回零方法
    HOMING_STEP step;                               // 当前步骤
    float speed_tar_to_switch;                      // 搜索开关速度
    float speed_tar_to_zero;                        // 搜索零点速度
    DigitalInputsIo_t io_status;                    // IO输入状态
    bool index_state;                               // Index信号状态
    float dt;                                       // 运行周期
    float timer;                                    // 计时器，可用作超时保护
} HomingMode_t;

AppResult HomingModeInit(void);
AppResult HomingModeStart(void);
AppResult HomingModeRun(void);
AppResult HomingModeStop(void);

#endif // APP_HOMING_MODE_H
