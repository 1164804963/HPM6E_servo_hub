#include "main.h"
#include "motor_ctl_loop.h"
#include "data_param.h"
#include "zmq_handler.h"
#include "mavlink_callback.h"
#include "app_scheduler.h"
#include "app_brake_control.h"
#include "app_motion_precondition.h"

int main(void)
{
    RegisterSetAppCallback(set_app);
    RegisterCheckErrorCallback(app_get_check_error_val);
    RegisterCheckWarningCallback(app_get_check_warning_val);
    RegisterCheckStatusCallback(app_get_check_status_val);
    RegisterCheckIoInputsStatusCallback(app_get_check_di_io_val);

    AppParamInit();
    MotorCtrlInit();  //电机控制相关初始化
    AppInit();
    AppStatusScanInit();
    ScopeInit();
    AppBrakeControlInit();
    AppMotionPreConditionInit();



    int rc = ZmqHandlerInit();
    if (rc != 0)
    {
        printf("zmq_init failed, rc = %d\n", rc);
        return -1;
    }

    RegisterSendCallback(ZmqSendData);
    RegisterRecvCallback(&MavlinkRecvCallback);

    HighPrecisionTimer* motor_ctrl_timer = CreateHighPrecisionTimer(MotorCtrlTimerCallback, NULL, NULL);
    StartHighPrecisionTimer(motor_ctrl_timer, 0, 1);
    HighPrecisionTimer* unreal_time_timer = CreateHighPrecisionTimer(UnrealTimeCallback, NULL, NULL);
    StartHighPrecisionTimer(unreal_time_timer, 0, 1);
    HighPrecisionTimer* zmq_recv_timer = CreateHighPrecisionTimer(ZmqRecvTimerCallback, &kAxis, &kAxisDw);
    StartHighPrecisionTimer(zmq_recv_timer, 0, 1);

    printf("The virtual driver and motor are running, press Enter to stop...\n");
    getchar();

    DestroyHighPrecisionTimer(motor_ctrl_timer);
    DestroyHighPrecisionTimer(unreal_time_timer);
    DestroyHighPrecisionTimer(zmq_recv_timer);

    ZmqDestroy();
}

void MotorCtrlTimerCallback(void* arg, void* arg_dw)
{
    for (size_t i = 0; i < 20; i++)
    {
        static volatile uint8_t position_frq_div = 0;
        CurrentLoopCtrl();
        SimPlantStep();
        if (position_frq_div == 0)
        {
            PosSpeedLoopCtrl();
            position_frq_div = 1; // 1:10KHZ 位置环   3:5KHZ 位置环
        }
        else
        {
            position_frq_div--;
        }
    }
}

void UnrealTimeCallback(void* arg, void* arg_dw)
{
    UnrealTimeBase1ms();
}

void ZmqRecvTimerCallback(void* arg, void* arg_dw)
{
    ZmqAsyncRecv(arg, arg_dw);
}

// 创建高精度定时器
HighPrecisionTimer* CreateHighPrecisionTimer(TimerCallback callback, void* context, void* context_dw) {
    HighPrecisionTimer* timer = (HighPrecisionTimer*)malloc(sizeof(HighPrecisionTimer));
    if (!timer) return NULL;

    timer->callback = callback;
    timer->context = context;
    timer->context_dw = context_dw;
    timer->timerHandle = NULL;
    timer->dueTime.QuadPart = 0;
    timer->period = 0;

    return timer;
}

// 定时器回调函数（由系统调用）
static VOID CALLBACK TimerAPCProc(LPVOID lpArgToCompletionRoutine,
                                 DWORD dwTimerLowValue,
                                 DWORD dwTimerHighValue) {
    HighPrecisionTimer* timer = (HighPrecisionTimer*)lpArgToCompletionRoutine;
    if (timer && timer->callback) {
        timer->callback(timer->context, timer->context_dw);
    }
}

// 启动定时器
BOOL StartHighPrecisionTimer(HighPrecisionTimer* timer, ULONGLONG initialDelayMs, LONG periodMs) {
    if (!timer) return FALSE;

    // 转换为100纳秒单位 (1毫秒=10000个100纳秒)
    timer->dueTime.QuadPart = -((LONGLONG)initialDelayMs * 10000);
    timer->period = periodMs;

    // 创建定时器队列定时器
    // 注意：第一个参数是输出参数，用于接收定时器句柄
    BOOL success = CreateTimerQueueTimer(
        &timer->timerHandle,  // 输出参数，接收新定时器的句柄
        NULL,                 // 默认定时器队列
        (WAITORTIMERCALLBACK)TimerAPCProc,
        timer,                // 传递给回调的参数
        initialDelayMs,       // 首次触发延迟(ms)
        periodMs,             // 周期(ms)，0表示只触发一次
        WT_EXECUTEINTIMERTHREAD | WT_EXECUTEONLYONCE);

    return success;
}

// 停止定时器
void StopHighPrecisionTimer(HighPrecisionTimer* timer) {
    if (timer && timer->timerHandle) {
        DeleteTimerQueueTimer(NULL, timer->timerHandle, NULL);
        timer->timerHandle = NULL;
    }
}

// 销毁定时器
void DestroyHighPrecisionTimer(HighPrecisionTimer* timer) {
    if (timer) {
        StopHighPrecisionTimer(timer);
        free(timer);
    }
}
