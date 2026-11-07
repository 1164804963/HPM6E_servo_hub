#ifndef MOTOR_CTL_LOOP_H
#define MOTOR_CTL_LOOP_H

#ifdef __cplusplus
extern "C"
{
#endif
#include "motor_ctl_sm.h"
#include "servo_hub_database_type.h"
#include "data_type_define.h"

extern Axis kAxis;
extern AxisDw kAxisDw;

void MotorCtrlInit(void);
void UnrealTimeBase1ms(void);
void CurrentLoopCtrl(void);
void PosSpeedLoopCtrl(void);
void SimPlantStep(void);

#ifdef __cplusplus
}
#endif

#endif
