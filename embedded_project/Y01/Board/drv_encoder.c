#include "drv_encoder.h"

// 编码器接收数据缓冲区
__attribute__((section(".RAM_D1"))) uint8_t encoder_tx_buff[ENCODER_NUM][ENCODER_FRAME_MAX_LEN] = { 0 };
__attribute__((section(".RAM_D1"))) uint8_t encoder_rx_buff[ENCODER_NUM][ENCODER_FRAME_MAX_LEN] = { 0 };

static inline void detect_abs_encoder_zero_crossing(EncoderDataInfo_t* const enc_data);
static inline void Encoder_None(EncoderDataInfo_t* enc_data);
static inline uint8_t crc8(uint8_t const *data, size_t length, uint8_t polynomial);
#if ENCODER1_TYPE_OPTION == ENCODER_TYPE_INC_AB_ABZ || ENCODER2_TYPE_OPTION == ENCODER_TYPE_INC_AB_ABZ
static void ABZ_Encoder_Init(EncoderDataInfo_t* enc_data);
static void ABZ_Encoder_Data_Read(EncoderDataInfo_t* enc_data);
static void ABZ_Encoder_Data_Process(EncoderDataInfo_t* enc_data);
#endif // ENCODER_TYPE_INC_AB_ABZ
#if ENCODER1_TYPE_OPTION == ENCODER_TYPE_ABS_RS485_TAMAGAWA || ENCODER2_TYPE_OPTION == ENCODER_TYPE_ABS_RS485_TAMAGAWA
static void TAMAGAWA_Encoder_Init(EncoderDataInfo_t* enc_data);
static void TAMAGAWA_Encoder_Data_Read(EncoderDataInfo_t* enc_data);
static void TAMAGAWA_Encoder_Data_Process(EncoderDataInfo_t* enc_data);
#endif // ENCODER_TYPE_ABS_RS485_TAMAGAWA
#if ENCODER1_TYPE_OPTION == ENCODER_TYPE_ABS_SPI_MT68XX || ENCODER2_TYPE_OPTION == ENCODER_TYPE_ABS_SPI_MT68XX
static void MT68XX_Encoder_Init(EncoderDataInfo_t* enc_data);
static void MT68XX_Encoder_Data_Read(EncoderDataInfo_t* enc_data);
static void MT68XX_Encoder_Data_Process(EncoderDataInfo_t* enc_data);
static inline bool MT68XX_Encoder_Crc8_Check(uint64_t input, int32_t len);
#endif // ENCODER_TYPE_ABS_SPI_MT68XX
#if ENCODER1_TYPE_OPTION == ENCODER_TYPE_ABS_SPI_KTM59XX || ENCODER2_TYPE_OPTION == ENCODER_TYPE_ABS_SPI_KTM59XX
static void KTM59XX_Encoder_Init(EncoderDataInfo_t* enc_data);
static void KTM59XX_Encoder_Data_Read(EncoderDataInfo_t* enc_data);
static void KTM59XX_Encoder_Data_Process(EncoderDataInfo_t* enc_data);
static inline bool KTM59XX_Encoder_Crc8_Check(uint64_t input, int32_t len);
#endif // ENCODER_TYPE_ABS_SPI_KTM59XX
#if ENCODER1_TYPE_OPTION == ENCODER_TYPE_ABS_BISSC_SMC40S || ENCODER2_TYPE_OPTION == ENCODER_TYPE_ABS_BISSC_SMC40S || \
    ENCODER1_TYPE_OPTION == ENCODER_TYPE_ABS_BISSC_BRT38M || ENCODER2_TYPE_OPTION == ENCODER_TYPE_ABS_BISSC_BRT38M
static void BISSC_Encoder_Init(EncoderDataInfo_t* enc_data);
static void BISSC_Encoder_Data_Read(EncoderDataInfo_t* enc_data);
static void BISSC_Encoder_Data_Process(EncoderDataInfo_t* enc_data);
//static inline uint8_t BISSC_Crc6_Calc(uint32_t data, uint8_t bit_len, uint8_t final_xor);
#endif // ENCODER_TYPE_ABS_BISSC_XXX

EncoderDataInfo_t encoder_data[ENCODER_NUM] = {
    [ENCODER_ID_1] = {
        .id = ENCODER_ID_1,
        .type = ENCODER_TYPE_NONE,
        .tim_handle = NULL,
        .uart_handle = &ENCODER1_UART_HANDLE,
        .spi_handle = &ENCODER1_SPI_HANDLE,
        .abz_ab_cnt = 0,
        .abz_z_first_flag = true,
        .abz_z_first_ab_cnt = 0,
        .abz_z_last_ab_cnt = 0,
        .data_raw = { 0 },
        .frame_len = 0,
        .cf = 0,
        .sf = 0,
        .almc = 0,
        .enid = 0,
        .check_val = 0,
        .err_cnt = 0,
        .options.val = 0,
        .a_single_res = 0,
        .a_single_res_real = 0,
        .a_single_less_factor = 1,
        .a_multi_res = 0,
        .a_single_raw = 0,
        .a_multi_raw = 0,
        .b_single_res = 0,
        .b_single_res_real = 0,
        .b_single_less_factor = 1,
        .b_multi_res = 0,
        .b_single_raw = 0,
        .b_multi_raw = 0,
        .single_cnt = 0,
        .multi_turns = 0,
        .zero_crossing_state = false,
        .is_first_read = true,
        .pos_last = 0,
        .real_motor_turns_res = 0,
    #if ENCODER1_TYPE_OPTION == ENCODER_TYPE_INC_AB_ABZ
        .init = ABZ_Encoder_Init,
        .read = ABZ_Encoder_Data_Read,
        .process = ABZ_Encoder_Data_Process,
    #elif ENCODER1_TYPE_OPTION == ENCODER_TYPE_ABS_RS485_TAMAGAWA
        .init = TAMAGAWA_Encoder_Init,
        .read = TAMAGAWA_Encoder_Data_Read,
        .process = TAMAGAWA_Encoder_Data_Process,
    #elif ENCODER1_TYPE_OPTION == ENCODER_TYPE_ABS_SPI_MT68XX
        .init = MT68XX_Encoder_Init,
        .read = MT68XX_Encoder_Data_Read,
        .process = MT68XX_Encoder_Data_Process,
    #elif ENCODER1_TYPE_OPTION == ENCODER_TYPE_ABS_SPI_KTM59XX
        .init = KTM59XX_Encoder_Init,
        .read = KTM59XX_Encoder_Data_Read,
        .process = KTM59XX_Encoder_Data_Process,
    #elif ENCODER1_TYPE_OPTION == ENCODER_TYPE_ABS_BISSC_SMC40S || \
          ENCODER1_TYPE_OPTION == ENCODER_TYPE_ABS_BISSC_BRT38M
        .init = BISSC_Encoder_Init,
        .read = BISSC_Encoder_Data_Read,
        .process = BISSC_Encoder_Data_Process,
    #else
        .init = Encoder_None,
        .read = Encoder_None,
        .process = Encoder_None,
    #endif
    },
    [ENCODER_ID_2] = {
        .id = ENCODER_ID_2,
        .type = ENCODER_TYPE_NONE,
        .tim_handle = NULL,
        .uart_handle = &ENCODER2_UART_HANDLE,
        .spi_handle = &ENCODER2_SPI_HANDLE,
        .abz_ab_cnt = 0,
        .abz_z_first_flag = true,
        .abz_z_first_ab_cnt = 0,
        .abz_z_last_ab_cnt = 0,
        .data_raw = { 0 },
        .frame_len = 0,
        .cf = 0,
        .sf = 0,
        .almc = 0,
        .enid = 0,
        .check_val = 0,
        .err_cnt = 0,
        .options.val = 0,
        .a_single_res = 0,
        .a_single_res_real = 0,
        .a_single_less_factor = 1,
        .a_multi_res = 0,
        .a_single_raw = 0,
        .a_multi_raw = 0,
        .b_single_res = 0,
        .b_single_res_real = 0,
        .b_single_less_factor = 1,
        .b_multi_res = 0,
        .b_single_raw = 0,
        .b_multi_raw = 0,
        .single_cnt = 0,
        .multi_turns = 0,
        .zero_crossing_state = false,
        .is_first_read = true,
        .pos_last = 0,
        .real_motor_turns_res = 0,
    #if ENCODER2_TYPE_OPTION == ENCODER_TYPE_INC_AB_ABZ
        .init = ABZ_Encoder_Init,
        .read = ABZ_Encoder_Data_Read,
        .process = ABZ_Encoder_Data_Process,
    #elif ENCODER2_TYPE_OPTION == ENCODER_TYPE_ABS_RS485_TAMAGAWA
        .init = TAMAGAWA_Encoder_Init,
        .read = TAMAGAWA_Encoder_Data_Read,
        .process = TAMAGAWA_Encoder_Data_Process,
    #elif ENCODER2_TYPE_OPTION == ENCODER_TYPE_ABS_SPI_MT68XX
        .init = MT68XX_Encoder_Init,
        .read = MT68XX_Encoder_Data_Read,
        .process = MT68XX_Encoder_Data_Process,
    #elif ENCODER2_TYPE_OPTION == ENCODER_TYPE_ABS_SPI_KTM59XX
        .init = KTM59XX_Encoder_Init,
        .read = KTM59XX_Encoder_Data_Read,
        .process = KTM59XX_Encoder_Data_Process,
    #elif ENCODER2_TYPE_OPTION == ENCODER_TYPE_ABS_BISSC_SMC40S || \
          ENCODER2_TYPE_OPTION == ENCODER_TYPE_ABS_BISSC_BRT38M
        .init = BISSC_Encoder_Init,
        .read = BISSC_Encoder_Data_Read,
        .process = BISSC_Encoder_Data_Process,
    #else
        .init = Encoder_None,
        .read = Encoder_None,
        .process = Encoder_None,
    #endif
    }
};

/**
 * @brief 初始化编码器数据
 * @param
 * @return
 * @note 根据所使用的编码器类型及接口，初始化编码器数据
 */
void EncoderDataInit(void)
{
    for (ENCODER_ID enc_id = ENCODER_ID_1; enc_id <= ENCODER_ID_MAXIMUN; enc_id ++)
    {
        encoder_data[enc_id].init(&encoder_data[enc_id]);
    }
}

/**
 * @brief 读取编码器数据
 * @param
 * @return
 * @note 根据所使用的编码器类型及接口，读取编码器数据
 */
void EncoderDataRead(void)
{
    for (ENCODER_ID enc_id = ENCODER_ID_1; enc_id <= ENCODER_ID_MAXIMUN; enc_id ++)
    {
        // 转存上周期读取的编码器器数据
        for (uint8_t i = 0; i < encoder_data[enc_id].frame_len; i++)
        {
            encoder_data[enc_id].data_raw[i] = encoder_rx_buff[enc_id][i];
            encoder_rx_buff[enc_id][i] = 0;
        }

        encoder_data[enc_id].read(&encoder_data[enc_id]);
    }
}

/**
 * @brief 处理编码器数据
 * @param
 * @return
 * @note 根据所使用的编码器类型及协议，解析编码器数据
 */
void EncoderDataProcess(void)
{
    uint32_t u32_calc_temp = 0;
    int64_t i64_calc_temp = 0;

    for (ENCODER_ID enc_id = ENCODER_ID_1; enc_id <= ENCODER_ID_MAXIMUN; enc_id ++)
    {
        // 按各自编码器协议对应解析
        encoder_data[enc_id].process(&encoder_data[enc_id]);

        // 编码器配置选项bit3，负载端(编码器B)单圈值 用作为 电机端多圈值(编码器A)
        if (encoder_data[enc_id].options.bits.l_cnt_2_m_turns)
        {
            encoder_data[enc_id].a_multi_raw = encoder_data[enc_id].b_single_raw;  // 编码器A多圈值 = 编码器B单圈值
            encoder_data[enc_id].b_single_raw = 0;    // 编码器B单圈值 = 0
            encoder_data[enc_id].real_motor_turns_res = encoder_data[enc_id].b_single_res_real; // 电机端多圈值分辨率 = 负载端单圈值分辨率
        }
        else
        {
            encoder_data[enc_id].real_motor_turns_res = encoder_data[enc_id].a_multi_res;
        }

        // 编码器配置选项bit2，多圈值溢出坐标选项，默认为0：按正负分辨率一半溢出
        if (!encoder_data[enc_id].options.bits.turns_overflow_0)
        {
            // 大于半圈则作为负圈数
            if (encoder_data[enc_id].a_multi_raw > (encoder_data[enc_id].real_motor_turns_res >> 1))
            {
                i64_calc_temp = encoder_data[enc_id].a_multi_raw - (int64_t)(encoder_data[enc_id].real_motor_turns_res);
                encoder_data[enc_id].a_multi_raw = i64_calc_temp;
            }
            if (encoder_data[enc_id].b_multi_raw > (encoder_data[enc_id].b_multi_res >> 1))
            {
                i64_calc_temp = encoder_data[enc_id].b_multi_raw - (int64_t)(encoder_data[enc_id].b_multi_res);
                encoder_data[enc_id].b_multi_raw = i64_calc_temp;
            }
        }

        // 编码器配置选项bit0，编码器A方向
        if (encoder_data[enc_id].options.bits.a_dir)
        {
            u32_calc_temp = encoder_data[enc_id].a_single_res_real - 1 - encoder_data[enc_id].a_single_raw;
            encoder_data[enc_id].a_single_raw = u32_calc_temp;
            if (encoder_data[enc_id].real_motor_turns_res > 0) // 有多圈值，才处理多圈值
            {
                i64_calc_temp = encoder_data[enc_id].real_motor_turns_res - 1 - encoder_data[enc_id].a_multi_raw;
                encoder_data[enc_id].a_multi_raw = i64_calc_temp;
            }
        }
        // 编码器配置选项bit1，编码器B方向
        if (encoder_data[enc_id].options.bits.b_dir)
        {
            u32_calc_temp = encoder_data[enc_id].b_single_res_real - 1 - encoder_data[enc_id].b_single_raw;
            encoder_data[enc_id].b_single_raw = u32_calc_temp;
            if (encoder_data[enc_id].b_multi_res > 0) // 有多圈值，才处理多圈值
            {
                i64_calc_temp = encoder_data[enc_id].b_multi_res - 1 - encoder_data[enc_id].b_multi_raw;
                encoder_data[enc_id].b_multi_raw = i64_calc_temp;
            }
        }
    }

    if(encoder_data[ENCODER_ID_2].type == ENCODER_TYPE_NONE)  //只有电机端编码器
    {
        // 设置电机端编码器数据
        encoder_data[ENCODER_ID_MOTOR].single_cnt = encoder_data[ENCODER_ID_1].a_single_raw;
        encoder_data[ENCODER_ID_MOTOR].multi_turns = encoder_data[ENCODER_ID_1].a_multi_raw;
        // 设置负载端编码器数据
        encoder_data[ENCODER_ID_LOAD].single_cnt = 0;
        encoder_data[ENCODER_ID_LOAD].multi_turns = 0;
    }
    else if (encoder_data[ENCODER_ID_2].type != ENCODER_TYPE_NONE) //双编码器 电机端+负载端编码器
    {
        // 设置电机端编码器数据
        encoder_data[ENCODER_ID_MOTOR].single_cnt = encoder_data[ENCODER_ID_1].a_single_raw;
        encoder_data[ENCODER_ID_MOTOR].multi_turns = encoder_data[ENCODER_ID_1].a_multi_raw;
        // 设置负载端编码器数据
        encoder_data[ENCODER_ID_LOAD].single_cnt = encoder_data[ENCODER_ID_2].a_single_raw;
        encoder_data[ENCODER_ID_LOAD].multi_turns = encoder_data[ENCODER_ID_2].a_multi_raw;
    }

    // 检测编码器过零点
    detect_abs_encoder_zero_crossing(&encoder_data[ENCODER_ID_MOTOR]);
    detect_abs_encoder_zero_crossing(&encoder_data[ENCODER_ID_LOAD]);
}

/**
 * @brief 获取编码器单圈值
 * @param[in] enc_id 编码器端ID：ENCODER_ID_MOTOR、ENCODER_ID_LOAD
 * @retval 对应编码器端ID单圈值
 */
uint32_t get_encoder_cnt(ENCODER_ID const enc_id)
{
    return encoder_data[enc_id].single_cnt;
}
/**
 * @brief 获取编码器多圈值
 * @param[in] enc_id 编码器端ID：ENCODER_ID_MOTOR、ENCODER_ID_LOAD
 * @retval 对应编码器端ID多圈值
 */
int64_t get_encoder_turns(ENCODER_ID const enc_id)
{
    return encoder_data[enc_id].multi_turns;
}

/**
 * @brief 获取编码器状态
 * @param[in] enc_id 编码器ID
 * @retval false 编码器异常/未准备好
 * @retval true  编码器正常/已准备好
 */
bool get_encoder_status(ENCODER_ID const enc_id)
{
    // 获取到编码器id，并且通讯错误次数小于最大值
    if (enc_id == ENCODER_ID_1)
    {
    #if ENCODER1_TYPE_OPTION != ENCODER_TYPE_NONE
        if (encoder_data[enc_id].enid != 0 && \
            encoder_data[enc_id].err_cnt < ENCODER_COMM_ERROR_MAX)
        {
            return true;
        }
    #else
        return true;
    #endif
    }
    else// if (enc_id == ENCODER_ID_2)
    {
    #if ENCODER2_TYPE_OPTION != ENCODER_TYPE_NONE
        if (encoder_data[enc_id].enid != 0 && \
            encoder_data[enc_id].err_cnt < ENCODER_COMM_ERROR_MAX)
        {
            return true;
        }
    #else
        return true;
    #endif
    }
    return false;
}

/**
 * @brief 获取编码器类型
 * @param[in] enc_id 编码器ID
 * @retval type 编码器类型  eg：ENCODER_TYPE_NONE、ENCODER_TYPE_INC_AB_ABZ...
 */
uint8_t get_encoder_type(ENCODER_ID enc_id)
{
    return encoder_data[enc_id].type;
}

/**
 * @brief 获取编码器过零点状态
 * @param[in] enc_id 编码器端ID：ENCODER_ID_MOTOR、ENCODER_ID_LOAD
 * @retval false 编码器未过零点
 * @retval true  编码器已过零点
 * @note 获取后编码器过零点状态会自动被清除
 */
bool get_encoder_zero_crossing_state(ENCODER_ID const enc_id)
{
    ENCODER_ID real_enc_id = enc_id;
    // 当编码器ID为负载端且类型为无编码器时，实际获取的是电机端的过零点状态
    if (enc_id == ENCODER_ID_LOAD && get_encoder_type(enc_id) == ENCODER_TYPE_NONE)
    {
        real_enc_id = ENCODER_ID_MOTOR;
    }
    bool zero_crossing_state = encoder_data[real_enc_id].zero_crossing_state;
    if (zero_crossing_state)
    {
        encoder_data[real_enc_id].zero_crossing_state = false;
    }
    return zero_crossing_state;
}

/**
 * @brief 检测绝对式编码器过零状态
 * @param[in] enc_data 编码器数据信息结构体指针
 */
static inline void detect_abs_encoder_zero_crossing(EncoderDataInfo_t* const enc_data)
{
    if (enc_data->type != ENCODER_TYPE_INC_AB_ABZ)
    {
        if (enc_data->is_first_read == true)
        {
            enc_data->is_first_read = false;
            enc_data->pos_last = enc_data->single_cnt;
            return;
        }
        // 计算位置增量
        int32_t delta = (int32_t)enc_data->single_cnt - (int32_t)enc_data->pos_last;
        // 使用绝对值判断是否发生环形计数器溢出，溢出则为跨圈时刻
        enc_data->zero_crossing_state = ((MATH_ABS(delta) > (enc_data->a_single_res_real >> 1)) ? true : false);
        enc_data->pos_last = enc_data->single_cnt;
    }
}

/**
 * @brief 编码器配置选项设置
 * @param[in] enc_id 编码器ID
 * @param[in] options 编码器配置选项整体值
 * @retval
 */
void set_encoder_options(ENCODER_ID enc_id, uint8_t const options)
{
    encoder_data[enc_id].options.val = options;
}

/**
 * @brief 编码器A分辨率设置
 * @param[in] enc_id 编码器ID
 * @param[in] single_res 编码器单圈分辨率
 * @param[in] single_res_real 编码器单圈实际分辨率
 * @param[in] multi_res 编码器多圈分辨率
 * @retval
 */
void set_encoder_a_resolution(ENCODER_ID const enc_id, uint32_t const single_res, \
                              uint32_t const single_res_real, uint32_t const multi_res)
{
    encoder_data[enc_id].a_single_res = single_res;
    encoder_data[enc_id].a_single_res_real = single_res_real;
    encoder_data[enc_id].a_single_less_factor = (single_res_real == 0U) ? 1U : (single_res / single_res_real);
    encoder_data[enc_id].a_multi_res = multi_res;
}
/**
 * @brief 编码器B分辨率设置
 * @param[in] enc_id 编码器ID
 * @param[in] single_res 编码器单圈分辨率
 * @param[in] single_res_real 编码器单圈实际分辨率
 * @param[in] multi_res 编码器多圈分辨率
 * @retval
 */
void set_encoder_b_resolution(ENCODER_ID const enc_id, uint32_t const single_res, \
                              uint32_t const single_res_real, uint32_t const multi_res)
{
    encoder_data[enc_id].b_single_res = single_res;
    encoder_data[enc_id].b_single_res_real = single_res_real;
    encoder_data[enc_id].b_single_less_factor = (single_res_real == 0U) ? 1U : (single_res / single_res_real);
    encoder_data[enc_id].b_multi_res = multi_res;
}

/**
 * @brief 编码器无操作
 * @param[in] enc_data 编码器数据信息结构体指针
 * @retval
 */
static inline void Encoder_None(EncoderDataInfo_t* enc_data)
{
    enc_data->type = ENCODER_TYPE_NONE;
    return;
}
#pragma region ENCODER_TYPE_INC_AB_ABZ
#if ENCODER1_TYPE_OPTION == ENCODER_TYPE_INC_AB_ABZ || ENCODER2_TYPE_OPTION == ENCODER_TYPE_INC_AB_ABZ
/**
 * @brief ABZ编码器初始化
 * @param[in] enc_data 编码器数据信息结构体指针
 * @retval
 */
static void ABZ_Encoder_Init(EncoderDataInfo_t* enc_data)
{
    enc_data->type = ENCODER_TYPE_INC_AB_ABZ;

    enc_data->abz_ab_cnt = 0;
    enc_data->abz_z_first_flag = true;
    enc_data->abz_z_first_ab_cnt = 0;
    enc_data->abz_z_last_ab_cnt = 0;

    if (enc_data->id == ENCODER_ID_1)
    {
        enc_data->tim_handle = &ENCODER1_ABZ_TIM_HANDLE;
    }
    else if (enc_data->id == ENCODER_ID_2)
    {
        enc_data->tim_handle = &ENCODER2_ABZ_TIM_HANDLE;
    }
    else
    {
        enc_data->type = ENCODER_TYPE_NONE;
        return;
    }
    enc_data->tim_handle->Instance->ARR = enc_data->a_single_res - 1; //设置为编码器4倍频增量计数分辨率 - 1
    HAL_TIM_Encoder_Start(enc_data->tim_handle, TIM_CHANNEL_ALL);
    HAL_TIM_IC_Start_IT(enc_data->tim_handle, TIM_CHANNEL_3); // 根据实际情况配置通道
}
/**
 * @brief ABZ编码器数据读取
 * @param[in] enc_data 编码器数据信息结构体指针
 * @retval
 */
static void ABZ_Encoder_Data_Read(EncoderDataInfo_t* enc_data)
{
    enc_data->abz_ab_cnt = enc_data->tim_handle->Instance->CNT;
}
/**
 * @brief ABZ编码器数据处理
 * @param[in] enc_data 编码器数据信息结构体指针
 * @retval
 */
static void ABZ_Encoder_Data_Process(EncoderDataInfo_t* enc_data)
{
    int32_t abz_ab_cnt_diff = (int32_t)enc_data->abz_z_last_ab_cnt - (int32_t)enc_data->abz_z_first_ab_cnt;
    if (MATH_ABS(abz_ab_cnt_diff) > (int32_t)(enc_data->a_single_res * ENCODER_ABZ_ERROR_RATIO))
    {
        enc_data->abz_z_last_ab_cnt = enc_data->abz_z_first_ab_cnt; //等待下一圈更新
        enc_data->err_cnt ++;
        if (enc_data->err_cnt >= ENCODER_COMM_ERROR_MAX)
        {
            enc_data->err_cnt = ENCODER_COMM_ERROR_MAX;
            sys_set_bsp_error_state((BSP_ERROR_CODE)enc_data->id, ERROR_SET);
        }
        return;
    }
    // else if (enc_data->err_cnt > 0)
    // {
    //     enc_data->err_cnt --;
    // }

    enc_data->a_single_raw = enc_data->abz_ab_cnt;
    enc_data->a_single_raw /= enc_data->a_single_less_factor;
    enc_data->a_multi_raw = 0;
    enc_data->b_single_raw = 0;
    enc_data->b_single_raw /= enc_data->b_single_less_factor;
    enc_data->b_multi_raw = 0;
    enc_data->sf = 0;
    enc_data->almc = 0;
    enc_data->enid = ENCODER_CONNECTED_ID;
}

/**
 * @brief ABZ编码器Z相中断回调函数
 * @param[in] htim 定时器句柄指针
 * @retval
 */
void ENCODER_ABZ_TIM_Z_IRQ_TASK(TIM_HandleTypeDef *htim)
{
    if(htim == encoder_data[ENCODER_ID_1].tim_handle)
    {
        encoder_data[ENCODER_ID_1].zero_crossing_state = true;
        encoder_data[ENCODER_ID_1].abz_z_last_ab_cnt = htim->Instance->CNT;
        if(encoder_data[ENCODER_ID_1].abz_z_first_flag == true)  //第一次进入记录CNT 的值
        {
            encoder_data[ENCODER_ID_1].abz_z_first_flag = false;
            encoder_data[ENCODER_ID_1].abz_z_first_ab_cnt = encoder_data[ENCODER_ID_1].abz_z_last_ab_cnt;
        }
        // 重置CNT计数器的值为第一次记录的值，需考虑Z脉冲宽度及电机正反转进入Z相情况
        htim->Instance->CNT = encoder_data[ENCODER_ID_1].abz_z_first_ab_cnt;
    }
    else if(htim == encoder_data[ENCODER_ID_2].tim_handle)
    {
        encoder_data[ENCODER_ID_2].zero_crossing_state = true;
        encoder_data[ENCODER_ID_2].abz_z_last_ab_cnt = htim->Instance->CNT;
        if(encoder_data[ENCODER_ID_2].abz_z_first_flag == true)  //第一次进入记录CNT 的值
        {
            encoder_data[ENCODER_ID_2].abz_z_first_flag = false;
            encoder_data[ENCODER_ID_2].abz_z_first_ab_cnt = encoder_data[ENCODER_ID_2].abz_z_last_ab_cnt;
        }
        // 重置CNT计数器的值为第一次记录的值，需考虑Z脉冲宽度及电机正反转进入Z相情况
        htim->Instance->CNT = encoder_data[ENCODER_ID_2].abz_z_first_ab_cnt;
    }
}
#endif // ENCODER_TYPE_INC_AB_ABZ
#pragma endregion ENCODER_TYPE_INC_AB_ABZ

#pragma region ENCODER_TYPE_ABS_RS485_TAMAGAWA
#if ENCODER1_TYPE_OPTION == ENCODER_TYPE_ABS_RS485_TAMAGAWA || ENCODER2_TYPE_OPTION == ENCODER_TYPE_ABS_RS485_TAMAGAWA
/**
 * @brief TAMAGAWA编码器初始化
 * @param[in] enc_data 编码器数据信息结构体指针
 * @retval
 */
static void TAMAGAWA_Encoder_Init(EncoderDataInfo_t* enc_data)
{
    enc_data->type = ENCODER_TYPE_ABS_RS485_TAMAGAWA;
    if (enc_data->id == ENCODER_ID_1)
    {
        enc_data->uart_handle = &ENCODER1_UART_HANDLE;
    }
    else if (enc_data->id == ENCODER_ID_2)
    {
        enc_data->uart_handle = &ENCODER2_UART_HANDLE;
    }
    else
    {
        enc_data->type = ENCODER_TYPE_NONE;
        return;
    }
    enc_data->frame_len = (uint8_t)TAMAGAWA_FRAME_LEN_ID_0;
    enc_data->cf =  (uint8_t)TAMAGAWA_CF_ID_0;

    // 为兼容各厂家设计差异，防止数据帧错位等异常情况，启动过程多次重置UART DMA传输
    if (enc_data->err_cnt)
    {
        enc_data->err_cnt = 0;
        HAL_UART_DMAStop(enc_data->uart_handle);
        __HAL_UART_DISABLE(enc_data->uart_handle);
        __HAL_UART_ENABLE(enc_data->uart_handle);
        HAL_UART_DMAResume(enc_data->uart_handle);
    }
}
/**
 * @brief TAMAGAWA编码器数据读取
 * @param[in] enc_data 编码器数据信息结构体指针
 * @retval
 */
static void TAMAGAWA_Encoder_Data_Read(EncoderDataInfo_t* enc_data)
{
    if (HAL_UART_Receive_DMA(enc_data->uart_handle, encoder_rx_buff[enc_data->id], \
                             enc_data->frame_len) != HAL_OK)
    {
        // 传输启动失败，增加错误计数
        enc_data->err_cnt++;
    }
    else
    {
        // 发送CF指令
        enc_data->uart_handle->Instance->TDR = enc_data->cf;
    }
}
/**
 * @brief TAMAGAWA编码器数据处理
 * @param[in] enc_data 编码器数据信息结构体指针
 * @retval
 */
static void TAMAGAWA_Encoder_Data_Process(EncoderDataInfo_t* enc_data)
{
    uint8_t check_cnt_val = 0;

    // 计算数据帧校验和
    for (uint8_t i = 0; i < (enc_data->frame_len - 1); i++)
    {
        check_cnt_val ^= enc_data->data_raw[i];
    }

    // 读取状态字段和校验和
    enc_data->check_val = enc_data->data_raw[enc_data->frame_len - 1];
    // 检查数据帧是否有效，是否存在异常
    if (enc_data->check_val != check_cnt_val ||\
        enc_data->cf != enc_data->data_raw[0])
    {
        enc_data->err_cnt ++;
        if (enc_data->err_cnt >= ENCODER_COMM_ERROR_MAX)
        {
            enc_data->err_cnt = ENCODER_COMM_ERROR_MAX;
            sys_set_bsp_error_state((BSP_ERROR_CODE)enc_data->id, ERROR_SET);
            //停止并重启UART DMA传输
            HAL_UART_DMAStop(enc_data->uart_handle);
            __HAL_UART_DISABLE(enc_data->uart_handle);
            __HAL_UART_ENABLE(enc_data->uart_handle);
            HAL_UART_DMAResume(enc_data->uart_handle);
        }
        return;
    }
    else if (enc_data->err_cnt > 0)
    {
        enc_data->err_cnt --;
    }

    //sys_set_bsp_error_state((BSP_ERROR_CODE)enc_id, ERROR_CLEAR); // 自动清除编码器错误状态

    // 可根据实际情况是否关闭检查SF寄存器
    enc_data->sf = enc_data->data_raw[1];
    if (IS_TAMAGAWA_SF_ERR(enc_data->sf))
    {
        // 可进一步检查具体错误类型，做一些特殊处理，现仅设置编码器错误状态
        sys_set_bsp_error_state((BSP_ERROR_CODE)enc_data->id, ERROR_SET);
    }

    // 数据无异常，进一步按协议解析数据
    enc_data->a_single_raw = enc_data->data_raw[2] + \
                            (enc_data->data_raw[3] << 8) + \
                            (enc_data->data_raw[4] << 16);
    enc_data->a_single_raw /= enc_data->a_single_less_factor;
    enc_data->a_multi_raw = 0;
    enc_data->b_single_raw = 0;
    enc_data->b_single_raw /= enc_data->b_single_less_factor;
    enc_data->b_multi_raw = 0;
    enc_data->almc = 0;
    enc_data->enid = ENCODER_CONNECTED_ID;
}
#endif // ENCODER_TYPE_ABS_RS485_TAMAGAWA
#pragma endregion ENCODER_TYPE_ABS_RS485_TAMAGAWA

#pragma region ENCODER_TYPE_ABS_SPI_MT68XX
#if ENCODER1_TYPE_OPTION == ENCODER_TYPE_ABS_SPI_MT68XX || ENCODER2_TYPE_OPTION == ENCODER_TYPE_ABS_SPI_MT68XX
/**
 * @brief MT68XX编码器初始化
 * @param[in] enc_data 编码器数据信息结构体指针
 * @retval
 */
static void MT68XX_Encoder_Init(EncoderDataInfo_t* enc_data)
{
    enc_data->type = ENCODER_TYPE_ABS_SPI_MT68XX;
    if (enc_data->id == ENCODER_ID_1)
    {
        enc_data->spi_handle = &ENCODER1_SPI_HANDLE;
        /* SPI parameter reconfiguration*/
        // enc_data->spi_handle->Init.CLKPolarity = SPI_POLARITY_HIGH;
        // enc_data->spi_handle->Init.CLKPhase = SPI_PHASE_2EDGE;
        // if (HAL_SPI_Init(enc_data->spi_handle) != HAL_OK)
        // {
        //     sys_set_bsp_error_state((BSP_ERROR_CODE)enc_data->id, ERROR_SET);
        // }
    }
    else if (enc_data->id == ENCODER_ID_2)
    {
        enc_data->spi_handle = &ENCODER2_SPI_HANDLE;
        /* SPI parameter reconfiguration*/
        // enc_data->spi_handle->Init.CLKPolarity = SPI_POLARITY_HIGH;
        // enc_data->spi_handle->Init.CLKPhase = SPI_PHASE_2EDGE;
        // if (HAL_SPI_Init(enc_data->spi_handle) != HAL_OK)
        // {
        //     sys_set_bsp_error_state((BSP_ERROR_CODE)enc_data->id, ERROR_SET);
        // }
    }
    else
    {
        enc_data->type = ENCODER_TYPE_NONE;
        return;
    }
    enc_data->frame_len = (uint8_t)MT68XX_FRAME_LEN_RD_ANGLE;
    enc_data->cf =  (uint8_t)MT68XX_CF_ID_RD;
    // 首2字节为cf+reg，其他字节均为0
    uint16_t tx_cmd = enc_data->cf << 8 | MT_REG_ANGLE_H;
    encoder_tx_buff[enc_data->id][0] = tx_cmd >> 8;
    encoder_tx_buff[enc_data->id][1] = tx_cmd & 0xFF;
    for (uint8_t i = 2; i < enc_data->frame_len; i++)
    {
        encoder_tx_buff[enc_data->id][i] = 0x00;
    }
}
/**
 * @brief MT68XX编码器数据读取
 * @param[in] enc_data 编码器数据信息结构体指针
 * @retval
 */
static void MT68XX_Encoder_Data_Read(EncoderDataInfo_t* enc_data)
{
    if (HAL_SPI_TransmitReceive_DMA(enc_data->spi_handle, encoder_tx_buff[enc_data->id], \
                                    encoder_rx_buff[enc_data->id], enc_data->frame_len) != HAL_OK)
    {
        // 传输启动失败，增加错误计数
        enc_data->err_cnt++;
    }
}
/**
 * @brief MT68XX编码器数据处理
 * @param[in] enc_data 编码器数据信息结构体指针
 * @retval
 */
static void MT68XX_Encoder_Data_Process(EncoderDataInfo_t* enc_data)
{
    if (crc8(&encoder_data[enc_data->id].data_raw[MT68XX_FRAME_LEN_RD_ANGLE - MT68XX_DATA_LEN_RD_ANGLE], \
             MT68XX_DATA_LEN_RD_ANGLE - 1, MT68XX_CRC8_POLY) != \
             encoder_data[enc_data->id].data_raw[MT68XX_FRAME_LEN_RD_ANGLE - 1])
    {
        if (enc_data->err_cnt >= ENCODER_COMM_ERROR_MAX)
        {
            enc_data->err_cnt = ENCODER_COMM_ERROR_MAX;
            sys_set_bsp_error_state((BSP_ERROR_CODE)enc_data->id, ERROR_SET);
        }
        return;
    }
    else if (enc_data->err_cnt > 0)
    {
        enc_data->err_cnt --;
    }

    enc_data->a_single_raw = (uint32_t)encoder_data[enc_data->id].data_raw[2] << 13 | /*bit20 ~ bit13*/ \
                             ((uint32_t)encoder_data[enc_data->id].data_raw[3] << 5) |  /*bit12 ~ bit5*/ \
                             (encoder_data[enc_data->id].data_raw[4] >> MT68XX_RD_ANGLE_STATUS_BW); /*bit4 ~ bit0*/
    enc_data->a_single_raw /= enc_data->a_single_less_factor;
    enc_data->a_multi_raw = 0;
    enc_data->b_single_raw = 0;
    enc_data->b_single_raw /= enc_data->b_single_less_factor;
    enc_data->b_multi_raw = 0;
    enc_data->sf = (uint8_t)(encoder_data[enc_data->id].data_raw[4] & ((0x01 << MT68XX_RD_ANGLE_STATUS_BW) - 1));
    enc_data->almc = 0;
    enc_data->enid = ENCODER_CONNECTED_ID;
}
#endif // ENCODER_TYPE_ABS_SPI_MT68XX
#pragma endregion ENCODER_TYPE_ABS_SPI_MT68XX

#pragma region ENCODER_TYPE_ABS_SPI_KTM59XX
#if ENCODER1_TYPE_OPTION == ENCODER_TYPE_ABS_SPI_KTM59XX || ENCODER2_TYPE_OPTION == ENCODER_TYPE_ABS_SPI_KTM59XX
/**
 * @brief KTM59XX编码器初始化
 * @param[in] enc_data 编码器数据信息结构体指针
 * @retval
 */
static void KTM59XX_Encoder_Init(EncoderDataInfo_t* enc_data)
{
    enc_data->type = ENCODER_TYPE_ABS_SPI_KTM59XX;
    if (enc_data->id == ENCODER_ID_1)
    {
        enc_data->spi_handle = &ENCODER1_SPI_HANDLE;
    }
    else if (enc_data->id == ENCODER_ID_2)
    {
        enc_data->spi_handle = &ENCODER2_SPI_HANDLE;
    }
    else
    {
        enc_data->type = ENCODER_TYPE_NONE;
        return;
    }
    enc_data->frame_len = (uint8_t)KTM59XX_FRAME_LEN_ID_3;
    enc_data->cf =  (uint8_t)KTM59XX_CF_ID_3;
    // 首字节为cf，其他字节均为0
    encoder_tx_buff[enc_data->id][0] = enc_data->cf;
    for (uint8_t i = 1; i < enc_data->frame_len; i++)
    {
        encoder_tx_buff[enc_data->id][i] = 0x00;
    }
}
/**
 * @brief KTM59XX编码器数据读取
 * @param[in] enc_data 编码器数据信息结构体指针
 * @retval
 */
static void KTM59XX_Encoder_Data_Read(EncoderDataInfo_t* enc_data)
{
    if (HAL_SPI_TransmitReceive_DMA(enc_data->spi_handle, encoder_tx_buff[enc_data->id], \
                                    encoder_rx_buff[enc_data->id], enc_data->frame_len) != HAL_OK)
    {
        // 传输启动失败，增加错误计数
        enc_data->err_cnt++;
    }
}
/**
 * @brief KTM59XX编码器数据处理
 * @param[in] enc_data 编码器数据信息结构体指针
 * @retval
 */
static void KTM59XX_Encoder_Data_Process(EncoderDataInfo_t* enc_data)
{
    uint64_t frame_data = 0;

    for (uint8_t i = 0; i < enc_data->frame_len; i++)
    {
        frame_data <<= 8;
        frame_data |= enc_data->data_raw[i];
    }

    if (KTM59XX_Encoder_Crc8_Check(frame_data, KTM59xx_FRAME_LEN_DATA_BW) == false)
    {
        enc_data->err_cnt ++;
        if (enc_data->err_cnt >= ENCODER_COMM_ERROR_MAX)
        {
            enc_data->err_cnt = ENCODER_COMM_ERROR_MAX;
            sys_set_bsp_error_state((BSP_ERROR_CODE)enc_data->id, ERROR_SET);
        }
        return;
    }
    else if (enc_data->err_cnt > 0)
    {
        enc_data->err_cnt --;
    }

    enc_data->a_single_raw = (uint32_t)((frame_data << KTM59xx_FRAME_LEN_RC_BW) >> \
                                        (KTM59xx_FRAME_LEN_RX_BW - KTM59xx_FRAME_LEN_ANGLE_BW));
    enc_data->a_single_raw /= enc_data->a_single_less_factor;
    enc_data->a_multi_raw = 0;
    enc_data->b_single_raw = 0;
    enc_data->b_single_raw /= enc_data->b_single_less_factor;
    enc_data->b_multi_raw = 0;
    enc_data->sf = (uint8_t)((frame_data << (KTM59xx_FRAME_LEN_RC_BW + KTM59xx_FRAME_LEN_ANGLE_BW)) >> \
                                (KTM59xx_FRAME_LEN_RX_BW - KTM59xx_FRAME_LEN_STATUS_BW));
    enc_data->almc = 0;
    enc_data->enid = ENCODER_CONNECTED_ID;
}
/**
 * @brief KTM59XX编码器CRC8校验
 * @param[in] input 待校验数据
 * @param[in] len 校验数据位宽
 * @retval true 校验成功 false 校验失败
 */
static inline bool KTM59XX_Encoder_Crc8_Check(uint64_t input, int32_t len)
{
    input >>= 56 - len;
    uint64_t data = input;
    input &= 0xFFFFFFFFFFFFFF00;
    uint64_t inputTemp = input;
    uint64_t mark = 0x8000000000000000;
    uint64_t ploy = 0x8380000000000000;
    ploy >>= 56 - len;
    mark >>= 56 - len;

    for (int32_t i = 0; i < len; i++)
    {
        if ((input & mark) != 0)
        {
            input ^= ploy;
        }

        mark >>= 1;
        ploy >>= 1;
    }

    inputTemp += (input ^ KTM5XXX_CRC8_FINAL_XOR) & 0xFF;
    return (inputTemp == data) ? true : false;
}
#endif // ENCODER_TYPE_ABS_SPI_KTM59XX
#pragma endregion ENCODER_TYPE_ABS_SPI_KTM59XX

#pragma region ENCODER_TYPE_ABS_BISSC_XXX
#if ENCODER1_TYPE_OPTION == ENCODER_TYPE_ABS_BISSC_SMC40S || ENCODER2_TYPE_OPTION == ENCODER_TYPE_ABS_BISSC_SMC40S || \
    ENCODER1_TYPE_OPTION == ENCODER_TYPE_ABS_BISSC_BRT38M || ENCODER2_TYPE_OPTION == ENCODER_TYPE_ABS_BISSC_BRT38M
/**
 * @brief BISSC编码器初始化
 * @param[in] enc_data 编码器数据信息结构体指针
 * @retval
 */
static void BISSC_Encoder_Init(EncoderDataInfo_t* enc_data)
{
    if (enc_data->id == ENCODER_ID_1)
    {
        enc_data->type = ENCODER1_TYPE_OPTION;
        enc_data->spi_handle = &ENCODER1_SPI_HANDLE;
    }
    else if (enc_data->id == ENCODER_ID_2)
    {
        enc_data->type = ENCODER2_TYPE_OPTION;
        enc_data->spi_handle = &ENCODER2_SPI_HANDLE;
    }
    else
    {
        enc_data->type = ENCODER_TYPE_NONE;
        return;
    }
    enc_data->frame_len = (uint8_t)BISSC_FRAME_LEN_ID_0;
    enc_data->cf =  (uint8_t)BISSC_CF_ID_0;
    for (uint8_t i = 0; i < enc_data->frame_len; i++)
    {
        encoder_tx_buff[enc_data->id][i] = enc_data->cf;
    }
}
/**
 * @brief BISSC编码器数据读取
 * @param[in] enc_data 编码器数据信息结构体指针
 * @retval
 */
static void BISSC_Encoder_Data_Read(EncoderDataInfo_t* enc_data)
{
    if (HAL_SPI_TransmitReceive_DMA(enc_data->spi_handle, encoder_tx_buff[enc_data->id], \
                                    encoder_rx_buff[enc_data->id], enc_data->frame_len) != HAL_OK)
    {
        // 传输启动失败，增加错误计数
        enc_data->err_cnt++;
    }
}
/**
 * @brief BISSC编码器数据处理
 * @param[in] enc_data 编码器数据信息结构体指针
 * @retval
 */
static void BISSC_Encoder_Data_Process(EncoderDataInfo_t* enc_data)
{
    uint32_t frame_data = 0;
    // uint8_t frame_crc = 0;
    // uint32_t frame_check_data = 0;

    for (uint8_t i = 0; i < enc_data->frame_len; i++)
    {
        frame_data <<= 8;
        frame_data |= enc_data->data_raw[i];
    }

    // frame_crc = (~enc_data->data_raw[enc_data->frame_len - 1] ) & (((uint8_t)1 << BISSC_FRAME_LEN_CRC_BW) - 1);
    // frame_check_data = (frame_data >> BISSC_FRAME_LEN_CRC_BW) & (((uint32_t)1 << (BISSC_FRAME_LEN_TOTAL_BW - BISSC_FRAME_LEN_CRC_BW)) - 1);

    // if (BISSC_Crc6_Calc(frame_check_data, (BISSC_FRAME_LEN_TOTAL_BW - BISSC_FRAME_LEN_CRC_BW), BISSC_CRC6_FINAL_XOR) != frame_crc)
    // {
    //     // CRC校验失败，增加错误计数
    //     enc_data->err_cnt++;
    //     return;
    // }
    // else if (enc_data->err_cnt > 0)
    // {
    //     enc_data->err_cnt --;
    // }

    enc_data->a_single_raw = (uint32_t)((frame_data >> (BISSC_FRAME_LEN_TOTAL_BW - BISSC_FRAME_LEN_DATA_BW)) & (enc_data->a_single_res - 1));
    enc_data->a_single_raw /= enc_data->a_single_less_factor;
    enc_data->a_multi_raw = 0;
    enc_data->b_single_raw = 0;
    enc_data->b_single_raw /= enc_data->b_single_less_factor;
    enc_data->b_multi_raw = 0;
    enc_data->sf = (frame_data >> (BISSC_FRAME_LEN_CRC_BW + BISSC_FRAME_LEN_WARNING_BW)) & (((uint8_t)1 << BISSC_FRAME_LEN_ERROR_BW) - 1);
    enc_data->almc = (frame_data >> BISSC_FRAME_LEN_CRC_BW) & (((uint8_t)1 << BISSC_FRAME_LEN_WARNING_BW) - 1);
    enc_data->enid = ENCODER_CONNECTED_ID;
}
/**
 * @brief BISSC编码器CRC6校验值计算
 * @param[in] data 待校验数据
 * @param[in] bit_len 校验数据位宽
 * @param[in] final_xor 最终异或值
 * @retval uint8_t CRC6校验值
 */
// static inline uint8_t BISSC_Crc6_Calc(uint32_t data, uint8_t bit_len, uint8_t final_xor)
// {
//     uint8_t crc = 0x00;  // 起始值
//     for (int i = bit_len - 1; i >= 0; i--) {  // MSB先行
//         uint8_t bit = (data >> i) & 0x01;
//         crc ^= (bit << 5);  // 最高位对齐
//         if (crc & 0x20) {   // 第6位为1
//             crc = (crc << 1) ^ final_xor;  // 多项式
//         } else {
//             crc <<= 1;
//         }
//         crc &= 0x3F;  // 保持6位
//     }
//     return crc ^ 0x3F;  // 输出反转（0x3F=6位全1）
// }
#endif // ENCODER_TYPE_ABS_BISSC_XXX
#pragma endregion ENCODER_TYPE_ABS_BISSC_XXX

#pragma region 其它公共组件
/**
 * @brief CRC8校验值计算
 * @param[in] data 待校验数据
 * @param[in] length 校验数据长度
 * @param[in] polynomial 校验多项式
 * @retval uint8_t CRC8校验值
 */
static inline uint8_t crc8(uint8_t const *data, size_t length, uint8_t polynomial)
{
    uint8_t crc = 0x00;

    for (size_t i = 0; i < length; i++)
    {
        crc ^= data[i];
        for (uint8_t j = 0; j < 8; j++)
        {
            if (crc & 0x80)
            {
                crc = (crc << 1) ^ polynomial;
            }
            else
            {
                crc <<= 1;
            }
        }
    }

    return crc;
}
