#ifndef MAIN_H
#define MAIN_H

#include <Windows.h>

// 定时器回调函数类型定义
typedef void (*TimerCallback)(void* context, void* context_dw);

// 定时器结构体
typedef struct {
    HANDLE timerHandle;
    TimerCallback callback;
    void* context;
    void* context_dw;
    LARGE_INTEGER dueTime;
    LONG period;
} HighPrecisionTimer;

HighPrecisionTimer* CreateHighPrecisionTimer(TimerCallback callback, void* context, void* context_dw);
BOOL StartHighPrecisionTimer(HighPrecisionTimer* timer, ULONGLONG initialDelayMs, LONG periodMs);
void StopHighPrecisionTimer(HighPrecisionTimer* timer);
void DestroyHighPrecisionTimer(HighPrecisionTimer* timer);
void MotorCtrlTimerCallback(void* arg, void* arg_dw);
void UnrealTimeCallback(void* arg, void* arg_dw);
void ZmqRecvTimerCallback(void* arg, void* arg_dw);


#endif // MAIN_H
