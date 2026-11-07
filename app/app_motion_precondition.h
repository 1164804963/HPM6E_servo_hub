#ifndef APP_MOTION_PRECONDITION_H
#define APP_MOTION_PRECONDITION_H

#include "app_data_type_define.h"

#include "app_status_check.h"

// 限位状态联合体
typedef union
{
    uint8_t all;                        // 所有限位状态
    struct
    {
        uint8_t negative : 1;           // 负向限位状态
        uint8_t hw_negative : 1;        // 负向硬件限位状态
        uint8_t soft_negative : 1;      // 负向软件限位状态
        uint8_t reserved1 : 1;          // 保留位

        uint8_t positive : 1;           // 正向限位状态
        uint8_t hw_positive : 1;        // 正向硬件限位状态
        uint8_t soft_positive : 1;      // 正向软件限位状态
        uint8_t reserved2 : 1;          // 保留位
    } bits;
} LimitStatus_t;

typedef struct
{
    LimitStatus_t status;               // 限位状态
    CheckWarningVal* warning;           // 限位警告

    DigitalInputsIo_t di_io_now;        // 硬件限位IO状态（当前）
    int64_t pos_actual_val;             // （负载端）位置当前值
    int64_t pos_soft_negative;          // 负向软件限位位置
    int64_t pos_soft_positive;          // 正向软件限位位置

} LimitCheck_t;

typedef struct
{
    bool emergency_brake_requested;     // 紧急制动请求
    LimitCheck_t limit;                 // 限位相关检查

} MotionPrecondition_t;

// 函数声明
void AppMotionPreConditionInit(void);
void AppMotionPreConditionRun(void);

#endif // APP_MOTION_PRECONDITION_H
