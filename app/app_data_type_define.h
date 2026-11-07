#ifndef APP_DATA_TYPE_DEFINE_H
#define APP_DATA_TYPE_DEFINE_H

#include "data_type_define.h"
#include "data_param.h"

typedef enum
{
    APP_RET_IDLE = 0,
    APP_RET_FAIL,
    APP_RET_SUCCESS,
    APP_RET_RUNNING,
    APP_RET_MAX = 0xFF,
} AppResult;

typedef enum
{
    APP_STA_IDLE = 0,
    APP_STA_READY,
    APP_STA_RUNNING,
    APP_STA_SUCCESS,
    APP_STA_ERROR,
    APP_STA_MAX = 0xFF,
} AppState;

typedef struct
{
    int64_t pos_tar_p;   // 位置用户目标值p
    float profile_speed; // 轮廓速度
    float profile_acc;   // 轮廓加速度
    float profile_dec;   // 轮廓减速度
    float period_s;      // 位置规划器运行周期s
    float pos_out_dec_p; // 位置用户目标值小数位p
} POS_TRAJECTORY_DATA;

typedef struct
{
    float speed_tar_p; // 速度用户目标值p/s
    float acc;         // 加速度 p/s^2
    float period_s;    // 速度规划器运行周期s
} SPEED_TRAJECTORY_DATA;

typedef struct
{
    float torque_tar; // 力矩用户目标值A
    float slope;      // 力矩上升斜率 A/s
    float period_s;   // 力矩规划器运行周期s
} TORQUE_TRAJECTORY_DATA;

typedef struct
{
    int64_t pos_tar_p;     // 位置用户目标值p
    float speed_tar_p_s;   // 速度用户目标值p/s
    float tq_set_NM;       // 力矩用户目标值NM
    float iq_max_A;        // 电流最大值A
    float kp_pos_NM_rad;   // 位置环比例系数rad/NM
    float kd_spd_NM_rad_s; // 速度环比例系数(rad/s)/NM
} MIT_TRAJECTORY_DATA;

typedef struct
{
    bool is_update_tar;         // 是否更新目标值
    int64_t pos_tar_buff_p[4];  // 插值位置用户目标值数组p
    float ip_dt_s;              // 插值周期时间s
    float period_s;             // 位置规划器运行周期s
} CSP_TRAJECTORY_DATA;

typedef struct
{
    bool is_update_tar;         // 是否更新目标值
    float speed_tar_buff_p_s[4];// 插值速度用户目标值数组p/s
    float ip_dt_s;              // 插值周期时间s
    float period_s;             // 速度规划器运行周期s
} CSV_TRAJECTORY_DATA;

typedef struct
{
    bool is_update_tar;         // 是否更新目标值
    float torque_tar_buff_A[4]; // 插值力矩用户目标值数组A
    float ip_dt_s;              // 插值周期时间s
    float period_s;             // 力矩规划器运行周期s
} CST_TRAJECTORY_DATA;

#endif // APP_DATA_TYPE_DEFINE_H
