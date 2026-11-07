#ifndef DATA_TYPE_DEFINE_H
#define DATA_TYPE_DEFINE_H

/* #include "data_type_define.h" */

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "yuanhub_math.h"
#include "motor_ctl_sm.h"
#include "servo_system_cfg.h"

// 编码器数量定义
#define ENCODER_NUM             (2u)                    // 每轴的编码器数量（最大值）
#define ENCODER_ID_MAX          (ENCODER_NUM - 1)       // 编码器ID最大值

// 编码器类型/型号定义
#define ENCODER_TYPE_NONE               0x00 // 无编码器
#define ENCODER_TYPE_INC_AB_ABZ         0x01 // 增量式通用AB/ABZ编码器，注：由于硬件单接口，只可配置电机端/负载端任选一端
#define ENCODER_TYPE_ABS_RS485_TAMAGAWA 0x02 // 绝对式通用RS485多摩川编码器
#define ENCODER_TYPE_ABS_SPI_MT68XX     0x03 // 绝对式SPI MT68XX 编码器  BTR≤10MBps，CPOL=High，CPHA==2Edge
#define ENCODER_TYPE_ABS_SPI_KTM59XX    0x04 // 绝对式SPI KTM59xx 编码器 BTR≤10MBps，CPOL=Low，CPHA=1Edge
#define ENCODER_TYPE_ABS_BISSC_SMC40S   0x05 // 绝对式SPI BISS-C SMC40S 编码器 BTR≤10MBps，CPOL=Low，CPHA=1Edge
#define ENCODER_TYPE_ABS_BISSC_BRT38M   0x06 // 绝对式SPI BISS-C BRT38M 编码器 BTR≤2.5MBps，CPOL=High，CPHA=2Edge

typedef enum
{
    ENCODER_ID_1 = 0,
    ENCODER_ID_2 = 1,
    ENCODER_ID_MAXIMUN = ENCODER_ID_MAX,                // 可用为边界检查
    ENCODER_ID_MOTOR = 0,
    ENCODER_ID_LOAD = 1,
} ENCODER_ID;

typedef enum
{
    ERROR_CLEAR = 0,
    ERROR_SET = 1
} BSP_ERROR_OPERATION;

typedef enum
{
    ERROR_ENCODER_MOTOR = 0,                // 电机端编码器错误
    ERROR_ENCODER_LOAD,                     // 负载端编码器错误
    ERROR_NFAULT,                           // nFault引脚报错低电平触发
    ERROR_BUS_CURRENT_OC,                   // 母线过流错误
    ERROR_BUS_OFFLINE,                      // 母线掉线
    ERROR_FLASH_STORE,                      // Flash存储错误
    ERROR_COMMS_INIT,                       // 通讯初始化错误
    ERROR_DRV_INIT,                         // Drv初始化错误
    ERROR_BUS_VOLTAGE,                      // 母线电压错误
    ERROR_CURRENT_SAMPLE,                   // 电流采样错误
    ERROR_FIRMWARE,                         // 固件错误
    ERROR_LIMIT_SWITCH,                     // 限位开关错误
    //...
    ERROR_MAX = 0xff
} BSP_ERROR_CODE;

typedef enum
{
    DI_IO_MIN = 0,                          // 可用为边界检查
    DI_IO_NEGATIVE_LIMIT_SWITCH = DI_IO_MIN,
    DI_IO_POSITIVE_LIMIT_SWITCH = 1,
    DI_IO_HOME_SWITCH = 2,
    DI_IO_INTERLOCK = 3,
    //DI_IO_RESERVED = 4~15,                // 保留位，禁止使用

    DI_IO_USER_0 = 16,                      // 厂商（用户）自定义位0
    // ...  MAX = 31
    DI_IO_MAX = DI_IO_USER_0,               // 可用为边界检查
} DIGITAL_INPUTS_IO_BIT;

typedef enum
{
    DO_IO_MIN = 0,                          // 可用为边界检查
    DO_IO_SET_BRAKE = DO_IO_MIN,
    //DO_IO_RESERVED = 1~15,                // 保留位，禁止使用

    DO_IO_USER_0 = 16,                      // 厂商（用户）自定义位0
    // ... MAX = 31
    DO_IO_MAX = DO_IO_USER_0,               // 可用为边界检查
} DIGITAL_OUTPUTS_IO_BIT;

typedef union
{
    uint32_t all;
    struct
    {
        uint32_t negative_limit_switch : 1;             // 负向硬件限位开关状态
        uint32_t positive_limit_switch : 1;             // 正向硬件限位开关状态
        uint32_t home_switch : 1;                       // 回零开关状态
        uint32_t interlock : 1;                         // 互锁开关状态
        uint32_t reserved : 12;                         // 保留位

        uint32_t user_0 : 1;                            // 厂商（用户）自定义位0
        uint32_t manufacturer_specific : 15;            // 厂商（用户）待定义位
    } bits; // 位字段
} DigitalInputsIo_t; // 数字输入IO状态（OD60FD）

typedef union
{
    uint32_t all;
    struct
    {
        uint32_t set_brake : 1;                         // 设置刹车状态
        uint32_t reserved : 15;                         // 保留位

        uint32_t user_0 : 1;                            // 厂商（用户）自定义位0
        uint32_t manufacturer_specific : 15;            // 厂商（用户）待定义位
    } bits; // 位字段
} DigitalOutputsIo_t; // 数字输出IO状态（OD60FE）

typedef union
{
    uint32_t code;
    struct
    {
        uint32_t error_encoder_motor : 1;               // 电机端编码器错误
        uint32_t error_encoder_load : 1;                // 负载端编码器错误
        uint32_t error_nfault : 1;                      // Drv预驱nFault报错
        uint32_t error_bus_current_oc : 1;              // 母线过流错误
        uint32_t error_bus_offline : 1;                 // 母线掉线
        uint32_t error_flash_store : 1;                 // Flash存储错误
        uint32_t error_comms_init : 1;                  // 通讯初始化错误
        uint32_t error_drv_init : 1;                    // Drv初始化错误
        uint32_t error_bus_voltage : 1;                 // 母线电压错误
        uint32_t error_current_sample : 1;              // 电流采样错误
        uint32_t error_firmware : 1;                    // 固件错误
        uint32_t error_limit_switch : 1;                // 限位开关错误

        uint32_t reserved : 20;                         // 保留位
    } bit_band;
} BspErrorCode_t;

typedef union
{
    uint32_t all;
    struct
    {
        uint32_t target_reached : 1;                // 目标到达
        uint32_t velocity_zero : 1;                 // 零速到达
        uint32_t homing_attained : 1;               // 回零完成
        uint32_t position_target_reached : 1;       // 位置到达
        uint32_t velocity_target_reached : 1;       // 速度到达
        uint32_t target_torque_reached : 1;         // 力矩到达
        uint32_t motor_enable_state : 1;            // 电机使能状态
        uint32_t encoder_zero_crossing_state : 1;   // 编码器过零点状态

        uint32_t reserved : 24;
    } bits; // 位字段
} CheckStatusVal_t;

typedef enum {
    VOLTAGE_STATUS_ERROR = -1,
    VOLTAGE_STATUS_UNKNOWN = 0,
    VOLTAGE_STATUS_NORMAL = 1,
} VOLTAGE_CHECK_STATUS;

typedef enum {
    CURRENT_CALIBRATION_STATUS_READY = 0,           // 0未校准
    CURRENT_CALIBRATION_STATUS_OK = 1,              // 1校准完成
    CURRENT_CALIBRATION_STATUS_ERR_BIG_CURRENT = 2, // 2校准中心电流过大错误
    CURRENT_CALIBRATION_STATUS_ERR_BUS_VOLTAGE = 3, // 3校准过程中母线电压不稳定错误
} CURRENT_CALIBRATION_STATUS;

// APP控制字定义(兼容控制层的控制字定义和应用层的控制字定义)
#define APP_NUM         15   //如果需要新增应用 在此处增加枚举定义 和 增加应用数量
typedef enum
{
    APP_NULL = 0,
    APP_PP_MODE,
    APP_PV_MODE,
    APP_PT_MODE,
    APP_MIT_MODE,
    APP_HM_MODE,
    APP_CSP_MODE,
    APP_CSV_MODE,
    APP_CST_MODE,
    APP_DIR_ID_MODE,
    APP_ELEC_ANGLE_ID_MODE,
    APP_ELEC_ID_MODE,
    APP_MEC_ID_MODE,
    APP_POLE_PAIRS_ID_MODE,
    APP_TQ_FC_ID_MODE,
    // ...
    APP_MAX = APP_NUM,
} APP_NAMES;

typedef enum {
    HOMING_STATE_FAIL = -1,     // 回零失败/超时
    HOMING_STATE_IDLE = 0,      // 回零空闲
    HOMING_STATE_SUCCEED = 1,   // 回零成功
} HOMING_STATE;

typedef enum
{
    APP_CTRL_DISABLE = MOTOR_CTL_SM_MOTOR_DISABLE,                 // 0: 失能电机
    APP_CTRL_ENABLE = MOTOR_CTL_SM_MOTOR_ENABLE,                   // 1: 使能电机  0->1 上升沿使能电机
    APP_CTRL_EMERGENCY_BRAKE = MOTOR_CTL_SM_MOTOR_EMERGENCY_BRAKE, // 2: 紧急停车（QuickStop）
    APP_CTRL_CLEAR_ERROR = MOTOR_CTL_SM_MOTOR_CLEAR_ERROR,         // 3: 清除错误  0->3 上升沿清除错误
} APP_CONTROL_WORD;

typedef enum
{
    EMERGENCY_BRAKE_MODE_DISABLED = 0,           // Disable emergency stop
    EMERGENCY_BRAKE_MODE_SLOW_DOWN_RAMP,         // Slow down the ramp
    EMERGENCY_BRAKE_MODE_QUICK_STOP_RAMP,        // Quick stop the ramp
    EMERGENCY_BRAKE_MODE_CURRENT_LIMIT,          // Limit the current
    EMERGENCY_BRAKE_MODE_VOLTAGE_LIMIT,          // Limit the voltage
    EMERGENCY_BRAKE_MODE_SLOW_DOWN_RAMP_ENABLE,  // Enable after slow down ramp
    EMERGENCY_BRAKE_MODE_QUICK_STOP_RAMP_ENABLE, // Enable after quick stop ramp
    EMERGENCY_BRAKE_MODE_CURRENT_LIMIT_ENABLE,   // Enable after current limit
    EMERGENCY_BRAKE_MODE_VOLTAGE_LIMIT_ENABLE,   // Enable after voltage limit
} APP_Emergency_Brake_Mode;

typedef enum
{
    BRAKE_CONTROL_MODE_IO_AUTO = 0,             // 内部逻辑自动控制控制IO
    BRAKE_CONTROL_MODE_IO_MANUAL = 1,           // 外部命令手动控制控制IO

    BRAKE_CONTROL_MODE_PWM_AUTO = 2,            // 内部逻辑自动控制控制PWM
    BRAKE_CONTROL_MODE_PWM_MANUAL = 3,          // 外部命令手动控制控制PWM
} APP_BRAKE_CONTROL_MODE;

typedef enum
{
    BRAKE_STATE_ENGAGED = 0,                    // 抱闸完成
    BRAKE_STATE_RELEASING = 1,                  // 松闸进行中
    BRAKE_STATE_RELEASED = 2,                   // 松闸完成
    BRAKE_STATE_ENGAGING = 3,                   // 抱闸进行中
} APP_BRAKE_STATE;

typedef enum
{
    COMM_CONTROL_HOST = 0, // 上位机通信
    COMM_CONTROL_BUS = 1,  // 总线通信
} APP_COMM_CONTROL_AUTHORITY;

typedef enum
{
    INTERNAL_CONTROL_APP = 0,    // 应用层控制
    INTERNAL_CONTROL_CTRL = 1,   // 控制层控制
} APP_INTERNAL_CONTROL_AUTHORITY;

typedef enum
{
    SYS_TIMER_RECORD_CURRENT_LOOP_CYCLE_INDEX = 0,      // 电流环周期
    SYS_TIMER_RECORD_CURRENT_LOOP_TIME_INDEX = 1,       // 电流环时间
    SYS_TIMER_RECORD_POSITION_LOOP_CYCLE_INDEX = 2,     // 位置环周期
    SYS_TIMER_RECORD_POSITION_LOOP_TIME_INDEX = 3,      // 位置环时间
    SYS_TIMER_RECORD_TIM_1MS_CYCLE_INDEX = 4,           // 1ms定时器任务周期
    SYS_TIMER_RECORD_TIM_1MS_TIME_INDEX = 5,            // 1ms定时器任务时间
    SYS_TIMER_RECORD_TEST_1_INDEX = 6,                  // 测试1索引
    SYS_TIMER_RECORD_TEST_2_INDEX = 7,                  // 测试2索引
    SYS_TIMER_RECORD_TEST_3_INDEX = 8,                  // 测试3索引
    SYS_TIMER_RECORD_TEST_4_INDEX = 9,                  // 测试4索引
    // SYS_TIMER_RECORD_USER_MAX_INDEX = (SYS_TIMER_RECORD_MAX_INDEX - 1),
} SYS_TIMER_RECORD_INDEX;

#define FLASHDB_KEYS_NUM     3
typedef enum {
    FLASHDB_KEY_INDEX_ALL_PARAM         = 0,
    FLASHDB_KEY_INDEX_ERROR_RECORD      = 1,
    FLASHDB_KEY_INDEX_TQ_FC_TABLE       = 2,
    // ...
    FLASHDB_KEY_INDEX_MAX = FLASHDB_KEYS_NUM - 1,
} FLASHDB_KEY_INDEX;
/*redefine flashdb's error code from fdb_def.h */
typedef enum {
    FLASHDB_NO_ERR,
    FLASHDB_ERASE_ERR,
    FLASHDB_READ_ERR,
    FLASHDB_WRITE_ERR,
    FLASHDB_PART_NOT_FOUND,
    FLASHDB_KV_NAME_ERR,
    FLASHDB_KV_NAME_EXIST,
    FLASHDB_SAVED_FULL,
    FLASHDB_INIT_FAILED,
} FLASHDB_STATUS;
typedef enum {
    FLASH_STORE_CMD_NULL = 0,       // 无操作/空闲
    FLASH_STORE_CMD_READ_PARAM,     // 读取数据库参数
    FLASH_STORE_CMD_WRITE_PARAM,    // 写入数据库参数
    FLASH_STORE_CMD_ERASE_PARAM,    // 擦除数据库参数
    FLASH_STORE_CMD_READ_ERROR,     // 读取错误记录
    FLASH_STORE_CMD_WRITE_ERROR,    // 写入错误记录
    FLASH_STORE_CMD_ERASE_ERROR,    // 擦除错误记录
    FLASH_STORE_CMD_READ_TQ_FC,     // 读取转矩脉动摩擦补偿表
    FLASH_STORE_CMD_WRITE_TQ_FC,    // 写入转矩脉动摩擦补偿表
    FLASH_STORE_CMD_ERASE_TQ_FC,    // 擦除转矩脉动摩擦补偿表
} FLASH_STORE_CMD;
typedef enum
{
    FLASH_STORE_STATUS_PROTECT = -3,    // 存储保护状态(写入频率超过最大允许次数)
    FLASH_STORE_STATUS_WARNING = -2,    // 存储警告(当前状态不允许操作)
    FLASH_STORE_STATUS_ERROR   = -1,    // 存储失败
    FLASH_STORE_STATUS_IDLE    = 0,     // 空闲状态
    FLASH_STORE_STATUS_BUSY    = 1,     // 存储中
    FLASH_STORE_STATUS_SUCCESS = 2,     // 存储成功
} FLASH_STORE_STATUS;

typedef enum
{
    APP_FILE_TYPE_IDLE      = 0,        // 无类型/复位状态
    APP_FILE_TYPE_FIRMWARE  = 1,        // 固件文件类型
    // ...
} APP_FILE_TYPE;

typedef enum
{
    APP_FILE_DIR_DOWNLOAD   = 0,        // 文件传输下载
    APP_FILE_DIR_UPLOAD     = 1,        // 文件传输上传
    // ...
} APP_FILE_DIR;

typedef enum
{
    // ...
    APP_FILE_STATUS_CHECK_ERR       = -2,   // 文件传输校验错误状态
    APP_FILE_STATUS_TRANSFER_ERR    = -1,   // 文件传输错误状态
    APP_FILE_STATUS_IDLE            = 0,    // 文件传输空闲状态
    APP_FILE_STATUS_READY           = 1,    // 文件传输准备状态
    APP_FILE_STATUS_BUSY            = 2,    // 文件传输进行中状态
    APP_FILE_STATUS_SUCCESS         = 3,    // 文件传输成功状态
    // ...
} APP_FILE_STATUS;

#endif // DATA_TYPE_DEFINE_H
