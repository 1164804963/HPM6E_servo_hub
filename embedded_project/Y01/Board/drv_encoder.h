#ifndef DRV_ENCODER_H
#define DRV_ENCODER_H

#include "board.h"

// 编码器参数定义
#define ENCODER_FRAME_MAX_LEN           16      // 数据帧最大帧长度
#define ENCODER_COMM_ERROR_MAX          20      // 编码器连续通信错误最大次数
// 编码器ID (固定值)
#define ENCODER_CONNECTED_ID            (0xCE)  // 当未读取编码器ID时，位置解析成功后强制设为0xCE（Connected Encoder）

typedef union
{
    uint8_t val;
    struct
    {
        uint8_t a_dir : 1;              // bit0：编码器A计数方向 0-默认, 1-取反
        uint8_t b_dir : 1;              // bit1：编码器B计数方向 0-默认, 1-取反
        uint8_t turns_overflow_0 : 1;   // bit2：多圈值溢出坐标为0/分辨率选项
        uint8_t l_cnt_2_m_turns : 1;    // bit3：负载端单圈作为值电机端多圈值选项

        uint8_t reserved : 4;
    } bits;
} Options_t; // 编码器配置选项

typedef struct EncoderDataInfo_t EncoderDataInfo_t;
struct EncoderDataInfo_t
{
    ENCODER_ID id;                              // 编码器编号
    uint8_t type;                               // 编码器类型

    TIM_HandleTypeDef *tim_handle;              // TIM句柄指针
    UART_HandleTypeDef *uart_handle;            // UART句柄指针
    SPI_HandleTypeDef *spi_handle;              // SPI句柄指针

    uint32_t abz_ab_cnt;                        // ABZ编码器AB相计数值
    bool abz_z_first_flag;                      // ABZ编码器Z相首次计数值标志位
    uint32_t abz_z_first_ab_cnt;                // ABZ编码器Z相首次计数值
    uint32_t abz_z_last_ab_cnt;                 // ABZ编码器Z相末次计数值
    uint8_t data_raw[ENCODER_FRAME_MAX_LEN];    // 编码器数据帧
    uint8_t frame_len;                          // 数据帧长度
    uint8_t cf;                                 // 控制字段
    uint8_t sf;                                 // 状态字段
    uint8_t almc;                               // 错误状态字段
    uint8_t enid;                               // 编码器ID
    uint8_t check_val;                          // 编码器校验值
    uint8_t err_cnt;                            // 错误计数

    Options_t options;                          // 编码器配置选项
    // 一个常规编码器含一套位置反馈数据，仅使用编码器A相关参数
    // 一个特殊编码器含两套位置反馈数据，分别对应编码器A和B相关参数
    uint32_t a_single_res;                      // 编码器A单圈分辨率
    uint32_t a_single_res_real;                 // 编码器A单圈分辨率实际值
    uint32_t a_single_less_factor;              // 编码器A单圈分辨率缩降倍数
    uint32_t a_multi_res;                       // 编码器A多圈分辨率
    uint32_t a_single_raw;                      // 编码器A单圈绝对值原始数据
    int64_t  a_multi_raw;                       // 编码器A多圈绝对值原始数据
    uint32_t b_single_res;                      // 编码器B单圈分辨率
    uint32_t b_single_res_real;                 // 编码器B单圈分辨率实际值
    uint32_t b_single_less_factor;              // 编码器B单圈分辨率缩降倍数
    uint32_t b_multi_res;                       // 编码器B多圈分辨率
    uint32_t b_single_raw;                      // 编码器B单圈绝对值原始数据
    int64_t  b_multi_raw;                       // 编码器B多圈绝对值原始数据
    // 编码器单圈值和多圈值为实际电机或负载端的位置反馈值
    volatile uint32_t single_cnt;               // 编码器单圈值
    volatile int64_t multi_turns;               // 编码器多圈值
    volatile bool zero_crossing_state;          // 编码器过零点状态

    volatile bool is_first_read;                // 首次读取标志
    volatile uint32_t pos_last;                 // 上一次位置值

    uint32_t real_motor_turns_res;              // 实际电机端编码器多圈分辨率

    void (*init)(EncoderDataInfo_t *enc_data);  // 编码器初始化函数指针
    void (*read)(EncoderDataInfo_t *enc_data);  // 编码器数据读取函数指针
    void (*process)(EncoderDataInfo_t *enc_data); // 编码器数据处理函数指针
};

void EncoderDataInit(void);
void EncoderDataRead(void);
void EncoderDataProcess(void);

uint32_t get_encoder_cnt(ENCODER_ID const enc_id);
int64_t get_encoder_turns(ENCODER_ID const enc_id);
bool get_encoder_status(ENCODER_ID const enc_id);
uint8_t get_encoder_type(ENCODER_ID enc_id);
bool get_encoder_zero_crossing_state(ENCODER_ID const enc_id);

void set_encoder_options(ENCODER_ID enc_id, uint8_t const options);
void set_encoder_a_resolution(ENCODER_ID const enc_id, uint32_t const single_res, \
                              uint32_t const single_res_real, uint32_t const multi_res);
void set_encoder_b_resolution(ENCODER_ID const enc_id, uint32_t const single_res, \
                              uint32_t const single_res_real, uint32_t const multi_res);

#endif // DRV_ENCODER_H
