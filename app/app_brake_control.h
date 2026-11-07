#ifndef APP_BRAKE_CONTROL_H
#define APP_BRAKE_CONTROL_H

#include "app_data_type_define.h"

typedef enum
{
    BRAKE_NULL = 0,       // 无
    BRAKE_ENGAGE,         // 抱闸
    BRAKE_RELEASE,        // 松闸
} APP_BRAKE_ACTION;

typedef struct
{
    APP_BRAKE_STATE state;          // 抱闸状态
    APP_BRAKE_CONTROL_MODE mode;    // 抱闸控制模式

    bool now_release_enable;        // 释放使能状态
    bool pre_release_enable;        // 释放使能状态上一次值
    APP_BRAKE_ACTION do_req;        // 数字IO输出抱闸请求

    float dt;                       // 时间步长
    float timer;                    // 计时器，用于控制抱闸时间
} BrakeControl_t;

// 函数声明
void AppBrakeControlInit(void);
void AppBrakeControlRun(void);

#endif // APP_BRAKE_CONTROL_H
