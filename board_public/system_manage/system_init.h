#ifndef SYSTEM_INIT_H
#define SYSTEM_INIT_H

#include "board.h"

#ifdef __cplusplus
extern "C" {
#endif

#define HARDWARE_SELF_TEST_RUN_CNT              (1000)  // 硬件自检运行次数,位置环周期

#define HARDWARE_UNDER_BUS_VOLTAGE_CNT          (2000)  // 检测到母线欠压次数
#define HARDWARE_NORMAL_BUS_VOLTAGE_CNT         (500)   // 检测到母线正常电压次数
#define HARDWARE_BUS_VOLTAGE_CHECK_OVERTIME_CNT (3000)  // 母线电压检测超时次数

#define CURRENTCCALIBRATION_TIMES_SHIFT     (10)    //电流采样校准次数移位数
#define CURRENTCCALIBRATION_TIMES           (1 << CURRENTCCALIBRATION_TIMES_SHIFT)  //电流采样校准次数

typedef struct
{
    bool start_flag;                    // 当前采样开始标志位 0未开始  1开始
    CURRENT_CALIBRATION_STATUS result;  // 电流采样标志位 0未校准  1校准完成  2校准中心电流过大错误  3校准过程中母线电压不稳定错误
    uint32_t drift[3];  // 校准值
} CurrentCalibration_t;

typedef struct
{
    bool first_time_enable_flag;                // 第一次使能标志位
    bool hardware_self_test_status;             // 硬件自检状态 false:自检未完成 true:自检完成
    int8_t bus_voltage_check_flag;              // 母线电压检测标志位
    BspErrorCode_t bsp_error_code;              // BSP错误码
    CurrentCalibration_t current_calibration;   // 电流校准相关参数

} SystemMessage_t;

void HalInit(void);
VOLTAGE_CHECK_STATUS BusVoltageCheck(void);
void HardwareSelfTestRun(void);
void BspReadyStateupdata(void);
void CurrentCalibrationStep(void);

bool get_first_time_enable_flag(void);
void set_first_time_enable_flag(bool flag);
bool get_hardware_self_test_status(void);
void set_bsp_error_state(BSP_ERROR_CODE type, BSP_ERROR_OPERATION op);
BspErrorCode_t* get_bsp_error_state(void);
CURRENT_CALIBRATION_STATUS get_current_calibration_status(void);
void get_current_calibration_drift(uint16_t *drift);

#ifdef __cplusplus
}
#endif

#endif
