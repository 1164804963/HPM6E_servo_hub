#ifndef APP_SCHEDULER_H
#define APP_SCHEDULER_H

#include "app_data_type_define.h"

#include "app_id_dir_mode.h"
#include "app_id_elec_angle_mode.h"
#include "app_id_elec_mode.h"
#include "app_id_mec_mode.h"
#include "app_id_pole_pairs_mode.h"
#include "app_id_tq_fc_mode.h"
#include "app_cyclic_sync_position_mode.h"
#include "app_cyclic_sync_velocity_mode.h"
#include "app_cyclic_sync_torque_mode.h"
#include "app_profile_position_mode.h"
#include "app_profile_velocity_mode.h"
#include "app_profile_torque_mode.h"
#include "app_homing_mode.h"
#include "app_mit_mode.h"

typedef enum
{
    APP_TYPE_PDS = 0,   //控制模式,只有一个运行(Object 6060, mode of operation)
    APP_TYPE_NORMOL,    //普通模式,可以同时运行多个
    APP_TYPE_MAX = 0xFF,
} AppType;

typedef struct
{
    APP_NAMES name;
    AppResult (*init)(void);
    AppResult (*start)(void);
    AppResult (*run)(void);
    AppResult (*stop)(void);
    AppType type;
} AppTable;

typedef struct
{
    const AppTable *app_ptr;//指向应用程序的指针
    bool enable;            //应用程序使能标志
    AppState app_state;     //应用程序状态
    AppResult app_result;   //应用程序结果
} AppInfo;

void AppInit(void);
void AppRun(uint8_t hw_ready_state);
void AppStop(APP_NAMES name);

void set_app(APP_NAMES name);
AppInfo get_current_app_info(APP_NAMES name);

#endif /* APP_SCHEDULER_H */
