#ifndef SCOPE_APP_H
#define SCOPE_APP_H

#include "ringbuffer.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SCOPE_BUF_MAX 32000  // 示波器缓存区最大
#define SCOPE_CHANNEL_NUM_MAX 8  // 通道数量
#define CATCH_WINDOW_SIZE 4  // 捕捉窗口大小，即边沿捕捉窗口的大小
#define FRAME_SIZE 120  //打包的帧数据长度,单位为字节

// 示波器读写宏定义
#define SCOPE_READ 0
#define SCOPE_WRITE 1

typedef enum {
    kInitFailedFlag = 0,
    kInitSuccessFlag = 1,
} InitStatusFlagEnum;

typedef enum {
    kRisingEdgeMode = 0,
    kFallingEdgeMode,
} SampleTriggerModeEnum;

typedef enum {
    kTriggerFailedFalg = 0,
    kTriggerSuccessFlag = 1,
} SampleTriggerFlagEnum;

typedef enum {
    kScopeNull = 0,
    kScopeConfig,
    kSampleTrigger,
    kSampleImmediately,
    kSampleStop,
    kScopeReset,
    kNullControl = 0xFF,
} ScopeControlWord;

typedef enum {
    kScopeNormal,
    kScopeError,
    kSampleSuccess,
    kNullStatus = 0xFF,
} ScopeStatusWord;

typedef enum {
    kRecordCloseFlag = 0,
    kRecordOpenFlag = 1,
} ChannelRecordFlagEnum;

typedef enum {
    kSampleUnComplete = 0,
    kSampleComplete = 1,
} SampleCompleteFlagEnum;
;

typedef enum {
    kSampleIsrClose = 0,
    kSampleIsrOpen = 1,
} SampleIsrSwitchFlagEnum;

/* 定义类型转换联合 */
typedef union {
    uint32_t u32;
    uint8_t u8;
    uint16_t u16;
    int8_t i8;
    int16_t i16;
    int32_t i32;
    float f32;
} TypeConverter;

typedef struct {
    ChannelRecordFlagEnum recoder_flag;
    uint16_t package_count;
    uint32_t data_index;  // 数据索引
    ToolModuleRingBuffer recoder_buffer;
    uint8_t data_size;  // 通道数据大小(单位为字节)
    void* data_ptr;
    uint32_t data_val;
    uint8_t data_type;
} ChannelStruct;

typedef struct {
    uint32_t data_index;  // 数据索引
    uint8_t catch_count;  // 捕捉计数，即边沿捕捉窗口捕捉到了多少符合要求的数据
    uint8_t catch_data_type;  // 捕捉数据类型 kTypeUint32 kTypeInt32 kTypeFloat32
    uint32_t catch_window_uint32[CATCH_WINDOW_SIZE];
    int32_t catch_window_int32[CATCH_WINDOW_SIZE];
    float catch_window_float32[CATCH_WINDOW_SIZE];
    uint32_t threshold_uint32;
    int32_t threshold_int32;
    float threshold_float32;
    void* data_ptr;
    uint32_t data_val;
    uint8_t data_type;
    uint8_t data_size;  // 通道数据大小(单位为字节)
} TriggerStruct;

typedef struct {
    InitStatusFlagEnum init_flag;
    ScopeControlWord control_word;
    ScopeStatusWord status_word;
    SampleTriggerModeEnum sample_trigger_mode;
    SampleTriggerFlagEnum trigger_flag;
    SampleCompleteFlagEnum sample_complete_flag;  // 采样完成标志
    SampleIsrSwitchFlagEnum sample_isr_flag;      // 采样中断开关标志
    uint8_t* storage_data_buffer;                 // 存储数据缓存地址
    uint32_t storage_data_buffer_size;            // 存储数据缓存大小
    uint32_t sample_delay;  // 采样延时：即边沿触发占位置的百分比
    int32_t sample_trigger_threshold;
    uint32_t sample_interval;  // 采样间隔：单位为周期
    uint32_t sample_interval_count;
    uint32_t sample_points;         // 采样周期，采样的总周期长度
    uint32_t sample_points_all;  // 采样的总目标数
    uint32_t sample_point_count;    // 采样点计数，这是有效值的计数
    ChannelStruct* channel_object[SCOPE_CHANNEL_NUM_MAX];
    TriggerStruct trigger_object;
} ScopeStruct;

void ScopeInit(void);

void ScopeIsrHandle(void);

void ControlWordWriteCallback(ScopeControlWord control_word);

void ScopeChannelDataRead(uint32_t channel_num, uint16_t subindex, uint8_t* data_length,
                             uint8_t* p_data);

void get_database_param_info(uint32_t index, uint32_t *pdata, uint8_t *type, uint8_t *size, void **pdata_ptr);

void get_database_param_val(void *pdata_ptr, uint8_t type, uint32_t *pdata);

extern ScopeStruct kScopeObject;

#ifdef __cplusplus
}
#endif


#endif
