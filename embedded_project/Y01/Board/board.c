#include "board.h"

#ifdef USE_CAN
#include "drv_can_app.h"
#endif // USE_CAN
#ifdef USE_ECAT
#include "ecat_app_hw.h"
#include "ecatappl.h"
#endif // USE_ECAT

__attribute__((section(".RAM_D1"))) BspData kBspData =
{
    .adc1_raw_buffer[0] = 0,
    .adc1_raw_buffer[1] = 0,
    .adc1_raw_buffer[2] = 0,
    .adc2_raw_buffer[0] = 0,
    .adc2_raw_buffer[1] = 0,
    .adc2_raw_buffer[2] = 0,
    .adc3_raw_buffer[0] = 0,
    .adc3_raw_buffer[1] = 0,
    .adc3_raw_buffer[2] = 0,
    .dc_bus_voltage_val = 0.0f,
    .dc_bus_current_val = 0.0f,
    .motor_temp_val = 20.0f,
    .mos_temp_val = 25.0f,
    .mcu_temp[0] = 30.0f,
    .mcu_temp[1] = 30.0f,
    .mcu_temp[2] = 30.0f,
    .uvw_current[0] = 0.0f,
    .uvw_current[1] = 0.0f,
    .uvw_current[2] = 0.0f,
    .uvw_target_voltage[0] = 0.0f,
    .uvw_target_voltage[1] = 0.0f,
    .uvw_target_voltage[2] = 0.0f,
    .pwm_en_state = PWM_DISABLE,
    .pwm_ready_state = false,
    .pwm_state_cnt = 0,
    .brake_pwm_timer_psc = 0,
    .brake_pwm_timer_arr = 0,
    .brake_pwm_duty_ccr_tar = 0,
    .brake_pwm_duty_ccr_action = 0,
    .brake_pwm_duty_ccr_hold = 0,
    .pl_start_state = false,
    .cs = {
        .sync0_trigger = false,
        .ctrl_source = CS_SOURCE_IDLE,
        .pl_period_cs_cnt = 0,
        .pl_period_total = 0,
        .pl_period_cnt = 0,
        .pl_period_index = 0,
        .frame_pl_period_index = 0,
        .shift_max_pl_period_index = 0,
        .latch_pl_period_index = 0,
        },
};

static void PositionLoopInit(void);
static void EcatTaskInit(void);

void BspInit(void)
{
    // 初始化固件升级
#ifdef YH_RELEASE
    drv_upgrade_init();
#endif // YH_RELEASE

    // 初始化抱闸定时器，输出抱闸信号为合闸状态
    __HAL_TIM_SET_COMPARE(&BRAKE_PWM_TIM_HANDLE, BRAKE_PWM_TIM_CHANNEL, BRAKE_PWM_DUTY_CCR_ENGAGED);
    HAL_TIM_PWM_Start(&BRAKE_PWM_TIM_HANDLE, BRAKE_PWM_TIM_CHANNEL);

    // 触发规则通道队列DMA采样
    HAL_ADC_Start_DMA(&DC_BUS_VOLTAGE_HANDLE, (uint32_t *)kBspData.adc1_raw_buffer, ADC1_REGULAR_RANK_NUMBER);
    // 等待母线电压稳定
    do
    {
        HAL_Delay(1);
    } while (sys_bus_voltage_check() == VOLTAGE_STATUS_UNKNOWN);

    HAL_ADC_Stop_DMA(&DC_BUS_VOLTAGE_HANDLE);

    // 启动 ADC 校准
    if (HAL_ADCEx_Calibration_Start(&UVW_CURRENT_U_HANDLE,
                                    ADC_CALIB_OFFSET_LINEARITY, ADC_SINGLE_ENDED) != HAL_OK)
    {
        sys_set_bsp_error_state(ERROR_CURRENT_SAMPLE, ERROR_SET);
    }
    else if (HAL_ADCEx_Calibration_Start(&UVW_CURRENT_V_HANDLE,
                                         ADC_CALIB_OFFSET_LINEARITY, ADC_SINGLE_ENDED) != HAL_OK)
    {
        sys_set_bsp_error_state(ERROR_CURRENT_SAMPLE, ERROR_SET);
    }
    else if (HAL_ADCEx_Calibration_Start(&UVW_CURRENT_W_HANDLE,
                                         ADC_CALIB_OFFSET_LINEARITY, ADC_SINGLE_ENDED) != HAL_OK)
    {
        sys_set_bsp_error_state(ERROR_CURRENT_SAMPLE, ERROR_SET);
    }

    HAL_ADC_Start_DMA(&DC_BUS_VOLTAGE_HANDLE, (uint32_t *)kBspData.adc1_raw_buffer, ADC1_REGULAR_RANK_NUMBER);
    HAL_ADC_Start_DMA(&TEMP_MOS_HANDLE, (uint32_t *)kBspData.adc2_raw_buffer, ADC2_REGULAR_RANK_NUMBER);
    HAL_ADC_Start_DMA(&TEMP_MCU_HANDLE, (uint32_t *)kBspData.adc3_raw_buffer, ADC3_REGULAR_RANK_NUMBER);
    HAL_Delay(5);

    // 启动 1ms 任务
    HAL_TIM_Base_Start_IT(&NRT_TASK_TIM_HANDLE);

    // 位置环软中断初始化，可配置运行周期
    //PositionLoopInit();

    // 启动ADC注入中断
    HAL_ADCEx_InjectedStart_IT(&UVW_CURRENT_U_HANDLE);
    HAL_ADCEx_InjectedStart(&UVW_CURRENT_V_HANDLE);
    HAL_ADCEx_InjectedStart(&UVW_CURRENT_W_HANDLE);

    // 初始化时关闭pwm波
    PWM_TIM_U_CCR_VAL = 0;
    PWM_TIM_V_CCR_VAL = 0;
    PWM_TIM_W_CCR_VAL = 0;
    HAL_TIM_PWM_Start(&PWM_TIM_HANDLE, PWM_TIM_U_CHANNEL);
    HAL_TIMEx_PWMN_Start(&PWM_TIM_HANDLE, PWM_TIM_U_CHANNEL);
    HAL_TIM_PWM_Start(&PWM_TIM_HANDLE, PWM_TIM_V_CHANNEL);
    HAL_TIMEx_PWMN_Start(&PWM_TIM_HANDLE, PWM_TIM_V_CHANNEL);
    HAL_TIM_PWM_Start(&PWM_TIM_HANDLE, PWM_TIM_W_CHANNEL);
    HAL_TIMEx_PWMN_Start(&PWM_TIM_HANDLE, PWM_TIM_W_CHANNEL);
    bsp_set_pwm_state(PWM_DISABLE);
    __HAL_TIM_ENABLE_IT(&PWM_TIM_HANDLE, TIM_IT_BREAK);

#ifdef USE_CAN
    // 初始化CAN外设
    if (bsp_fdcan_init() != HAL_OK)
    {
        sys_set_bsp_error_state(ERROR_COMMS_INIT, ERROR_SET);
    }
    else
    {
        // CAN相关应用初始化
        fdcan_app_init();
    }
#endif // USE_CAN

    // 启动调试软件通讯
    __HAL_UART_CLEAR_IDLEFLAG(&HOST_UART_HANDLE);
    HAL_UART_Receive_DMA(&HOST_UART_HANDLE, mavlink_rx_buff, MAVLINK_RECV_BUFF_SIZE);
    __HAL_UART_ENABLE_IT(&HOST_UART_HANDLE, UART_IT_IDLE);

    HAL_Delay(10);
#ifdef USE_ECAT
    EcatTaskInit();
#endif // USE_ECAT
}

// 电流环中断任务 典型频率  20KHZ
void CURRENT_LOOP_IRQ_TASK(ADC_HandleTypeDef *hadc)
{
    if (hadc->Instance == UVW_CURRENT_U_HANDLE.Instance)
    {
        bsp_set_timer_record_stop(SYS_TIMER_RECORD_CURRENT_LOOP_CYCLE_INDEX); // 测量电流环周期
        bsp_set_timer_record_start(SYS_TIMER_RECORD_CURRENT_LOOP_CYCLE_INDEX);

        bsp_set_timer_record_start(SYS_TIMER_RECORD_CURRENT_LOOP_TIME_INDEX); // 测量电流环运行时间
        // 硬件自检完毕且电流校准通过，运行电流环
        if (sys_get_hardware_self_test_status() == true &&
            sys_get_current_calibration_status() == CURRENT_CALIBRATION_STATUS_OK)
        {
            CurrentLoopCtrl();
        }
#ifdef VIRTUAL_MOTOR_MODEL
        SimPlantStep();
#endif
        bsp_set_timer_record_stop(SYS_TIMER_RECORD_CURRENT_LOOP_TIME_INDEX);

        // 第一次运行完电流环后启动常规非同步周期位置环
        if (kBspData.pl_start_state == false)
        {
            kBspData.pl_start_state = true;

            // 1. 重置计数器
            POSITION_LOOP_TIM_HANDLE.Instance->CNT = 0;
            // 2. 使能中断和计数器
            POSITION_LOOP_TIM_HANDLE.Instance->DIER |= TIM_DIER_UIE;
            POSITION_LOOP_TIM_HANDLE.Instance->CR1 |= TIM_CR1_CEN;
            // 3. 生成更新事件
            POSITION_LOOP_TIM_HANDLE.Instance->EGR |= TIM_EGR_UG;
        }
    }
}

// 位置环中断任务 典型频率  10KHZ
void POSITION_LOOP_TIM_IRQ_TASK(void)
{
    POSITION_LOOP_TIM_HANDLE.Instance->SR &= ~TIM_SR_UIF;

    bsp_set_timer_record_stop(SYS_TIMER_RECORD_POSITION_LOOP_CYCLE_INDEX); // 测量位置环周期
    bsp_set_timer_record_start(SYS_TIMER_RECORD_POSITION_LOOP_CYCLE_INDEX);

    bsp_set_timer_record_start(SYS_TIMER_RECORD_POSITION_LOOP_TIME_INDEX); // 测量位置环运行时间

    #ifdef USE_ECAT
    kBspData.cs.pl_period_cnt++;
    if (kBspData.cs.pl_period_total != 0)
    {
        kBspData.cs.pl_period_index = (kBspData.cs.pl_period_cnt - 1) % kBspData.cs.pl_period_total;

        if (kBspData.cs.pl_period_cnt > kBspData.cs.pl_period_total)
        {
            if (kBspData.cs.ctrl_source != CS_SOURCE_IRQ_SM)
            {
                // 同步周期变大或丢失，重新进行位置环同步
                kBspData.cs.ctrl_source = CS_SOURCE_IDLE;
                kBspData.cs.pl_period_total = 0;
                kBspData.cs.sync0_trigger = false;
            }
        }
        else if (kBspData.cs.ctrl_source != CS_SOURCE_IDLE && \
                 kBspData.cs.pl_period_index == kBspData.cs.latch_pl_period_index)
        {
            set_app_Target_update_state(true);
        }
    }
    #endif // USE_ECAT

#ifndef VIRTUAL_MOTOR_MODEL
    if (sys_get_hardware_self_test_status() == false)
    {
        EncoderDataInit();
        HardwareSelfTestRun();
    }

    // 编码器数据读取及处理
    EncoderDataRead();
    EncoderDataProcess();

    bsp_pwm_ready_state_updata(); // 更新PWM输出准备状态
#endif // VIRTUAL_MOTOR_MODEL
    if (sys_get_hardware_self_test_status() == true)
    {
        PosSpeedLoopCtrl();
    }
    bsp_set_timer_record_stop(SYS_TIMER_RECORD_POSITION_LOOP_TIME_INDEX);
}

#ifdef USE_ECAT
// 同步任务软件中断初始化函数
static void EcatTaskInit(void)
{
    EXTI_HandleTypeDef sync_task_exit;
    EXTI_ConfigTypeDef sync_task_exit_config;
    sync_task_exit_config.GPIOSel = EXTI_GPIOB;
    sync_task_exit_config.Line = ECAT_SYNC_EXTI_LINE_X;
    sync_task_exit_config.Mode = EXTI_MODE_INTERRUPT;
    sync_task_exit_config.Trigger = EXTI_TRIGGER_RISING;
    HAL_EXTI_SetConfigLine(&sync_task_exit, &sync_task_exit_config);
    HAL_NVIC_SetPriority(ECAT_SYNC_EXTIX_IRQN, ECAT_SYNC_NVIC_PRIORITY, 0);
    HAL_NVIC_EnableIRQ(ECAT_SYNC_EXTIX_IRQN);

    EXTI_HandleTypeDef pdi_task_exit;
    EXTI_ConfigTypeDef pdi_task_exit_config;
    pdi_task_exit_config.GPIOSel = EXTI_GPIOB;
    pdi_task_exit_config.Line = ECAT_PDI_EXTI_LINE_X;
    pdi_task_exit_config.Mode = EXTI_MODE_INTERRUPT;
    pdi_task_exit_config.Trigger = EXTI_TRIGGER_RISING;
    HAL_EXTI_SetConfigLine(&pdi_task_exit, &pdi_task_exit_config);
    HAL_NVIC_SetPriority(ECAT_PDI_EXTIX_IRQN, ECAT_PDI_NVIC_PRIORITY, 0);
    HAL_NVIC_EnableIRQ(ECAT_PDI_EXTIX_IRQN);
}

/**
 * @brief  自适应同步周期配置对应位置环周期个数
 * @param  cs: 同步周期模式控制参数
 * @retval bool: 同步完成标志
 */
static bool bsp_adaptive_pl_period_config(BspCyclicSync *cs)
{
    bool sync_complete = false;

    // 自适应同步周期配置对应位置环周期个数
    if (cs->pl_period_total != cs->pl_period_cnt)
    {
        cs->pl_period_cs_cnt++; // 同步周期连续判断次数
        if (cs->pl_period_cs_cnt >= CS_PL_PERIOD_CS_JUDGE_CNT)
        {
            cs->pl_period_cs_cnt = 0;
            cs->pl_period_total = cs->pl_period_cnt;
            cs->shift_max_pl_period_index = cs->pl_period_total - 1;
            cs->frame_pl_period_index = 0;
            sync_complete = true; // 同步完成
        }
    }
    else
    {
        cs->pl_period_cs_cnt = 0;
    }

    // Shift Time 使用自适应配置策略，TODO：可通过添加OD1C33h:sub03h(Shift time)配置为相同，可实现多轴同步
    if (cs->frame_pl_period_index < cs->shift_max_pl_period_index && \
        cs->frame_pl_period_index != 0) // 靠近同步帧最小的Frame位置环周期索引数
    {
        cs->shift_max_pl_period_index = cs->frame_pl_period_index;
        // 自动配置最大Shift Time
        cs->latch_pl_period_index = cs->shift_max_pl_period_index;
    }

    // 重置位置环周期总数索引
    cs->pl_period_cnt = 0;

    return sync_complete;
}

void ECAT_EXTI_IRQ_TASK(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == ECAT_SYNC0_EXTI_LINE) // DC同步中断
    {
        // 自适应同步周期配置对应位置环周期个数
        if (bsp_adaptive_pl_period_config(&kBspData.cs))
        {
            kBspData.cs.ctrl_source = CS_SOURCE_SYNC0; // 完成同步，DC控制使能开启
        }

        if (kBspData.cs.sync0_trigger == false)
        {
            kBspData.cs.sync0_trigger = true;
            kBspData.cs.pl_period_total = 0;
            kBspData.cs.pl_period_cs_cnt = 0;
        }

        // 1. 重置计数器
        POSITION_LOOP_TIM_HANDLE.Instance->CNT = 0;
        // 2. 使能中断和计数器
        POSITION_LOOP_TIM_HANDLE.Instance->DIER |= TIM_DIER_UIE;
        POSITION_LOOP_TIM_HANDLE.Instance->CR1 |= TIM_CR1_CEN;
        // 3. 生成更新事件
        POSITION_LOOP_TIM_HANDLE.Instance->EGR |= TIM_EGR_UG;
        // 4. 触发 EXTI 线 ECAT_SYNC_EXTI_LINE_X 的软件中断
        EXTI->SWIER1 |= ECAT_SYNC_SWIER1_SWIER;
    }
    else if (GPIO_Pin == ECAT_SYNC1_EXTI_LINE)
    {
        // 暂不支持Sync1同步
        Sync1_Isr();
    }
    else if (GPIO_Pin == ECAT_IRQ_EXTI_LINE)
    {
        kBspData.cs.frame_pl_period_index = kBspData.cs.pl_period_index; // Frame位置环周期索引

        if (kBspData.cs.sync0_trigger == false) // 只有不是DC同步中断时，才是SM同步
        {
            // 自适应同步周期配置对应位置环周期个数
            if (bsp_adaptive_pl_period_config(&kBspData.cs))
            {
                kBspData.cs.ctrl_source = CS_SOURCE_IRQ_SM; // 完成同步，SM控制使能开启
            }
        }

        // 触发 EXTI 线 ECAT_PDI_EXTI_LINE_X 的软件中断
        EXTI->SWIER1 |= ECAT_PDI_SWIER1_SWIER;
    }
}

void ECAT_SYNC_IRQ_TASK(void)
{
    EXTI->PR1 |= ECAT_SYNC_PR1_PR; // 清除SYNC线挂起标志

    DISABLE_ESC_INT();
    Sync0_Isr();
    ENABLE_ESC_INT();
}

void ECAT_PDI_IRQ_TASK(void)
{
    EXTI->PR1 |= ECAT_PDI_PR1_PR; // 清除PDI线挂起标志

    PDI_Isr();
}
#endif // USE_ECAT

// 1ms低频任务 典型频率  1KHZ
void NRT_CAN_ECAT_IRQ_TASK(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == NRT_TASK_TIM_HANDLE.Instance)
    {
        UnrealTimeBase1ms();
    }
#ifdef USE_CANOPEN
    else if (htim->Instance == CANOPEN_TIM_HANDLE.Instance)
    {
        CANopen_DispatchFromISR();
    }
#endif // USE_CANOPEN
#ifdef USE_ECAT
    else if (htim->Instance == ECAT_LAN9252_TIM_HANDLE.Instance)
    {
        ECAT_CheckTimer();
    }
#endif // USE_ECAT
}

/**
 * @brief  定时器断路中断回调函数
 * @param  htim: 定时器句柄指针
 * @retval None
 * @note   处理PWM输出的断路保护事件
 */
void PWM_TIM_BREAK_IRQ_HANDLE(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == PWM_TIM_HANDLE.Instance)
    {
        __HAL_TIM_DISABLE_IT(htim, TIM_IT_BREAK);

        bsp_set_pwm_state(PWM_DISABLE);
        sys_set_bsp_error_state(ERROR_NFAULT, ERROR_SET);
    }
}

/**
 * @brief 上位机通讯，向上位机发送数据
 * 该函数用于处理UART中断事件，主要用于处理IDLE空闲中断
 * 当检测到UART空闲状态时，会停止DMA传输，处理接收到的数据，然后重新启动DMA接收
 */
void mavlink_send_data(uint8_t *pdata, uint32_t len)
{
#ifndef USE_CAN_MAVLINK_HOST
    HAL_UART_Transmit_DMA(&HOST_UART_HANDLE, pdata, len);
#else
    fdcan_app_mav_send_packet(&CAN_FDCAN_HANDLE, pdata, len, get_app_Sys_id(),
                              get_app_Comp_id(), CANID_PRIORITY, CANFD_MESSAGE);
#endif
}
/**
 * @brief 上位机通讯UART中断任务
 * 该函数用于处理UART中断事件，主要用于处理IDLE空闲中断
 * 当检测到UART空闲状态时，会停止DMA传输，处理接收到的数据，然后重新启动DMA接收
 */
void HOST_UART_IRQ_TASK(void)
{
    HAL_UART_IRQHandler(&HOST_UART_HANDLE); // 调用HAL库的UART中断处理函数

    if (__HAL_UART_GET_FLAG(&HOST_UART_HANDLE, UART_FLAG_IDLE))
    {
        __HAL_UART_CLEAR_IDLEFLAG(&HOST_UART_HANDLE);

        HAL_UART_DMAStop(&HOST_UART_HANDLE);

        // 调用Mavlink数据接收回调函数，处理接收到的数据
        // 参数为接收缓冲区和实际接收到的数据长度
#ifndef USE_CAN_MAVLINK_HOST
        MavlinkRecvCallback(&kAxis, &kAxisDw, mavlink_rx_buff, MAVLINK_RECV_BUFF_SIZE - __HAL_DMA_GET_COUNTER(HOST_UART_HANDLE.hdmarx));
#endif /* USE_CAN_MAVLINK_HOST */
        // 重新启动DMA接收，准备接收下一批数据
        HAL_UART_Receive_DMA(&HOST_UART_HANDLE, mavlink_rx_buff, MAVLINK_RECV_BUFF_SIZE);
    }

    // 及时检查溢出错误(ORE)，清除错误标志并重新启动DMA接收
    if (__HAL_UART_GET_FLAG(&HOST_UART_HANDLE, UART_FLAG_ORE))
    {
        __HAL_UART_CLEAR_FLAG(&HOST_UART_HANDLE, UART_FLAG_ORE);
        HAL_UART_DMAStop(&HOST_UART_HANDLE);
        HAL_UART_Receive_DMA(&HOST_UART_HANDLE, mavlink_rx_buff, MAVLINK_RECV_BUFF_SIZE);
    }
}

/**
 * @brief 上位机通讯UART错误回调函数
 * @param huart: UART句柄指针，指向发生错误的UART实例
 * @note 该函数在UART通信发生错误时被调用，用于处理错误并恢复通信
 */
void HOST_UART_ERROR_HANDLE(UART_HandleTypeDef *huart)
{
    if (huart->Instance == HOST_UART_HANDLE.Instance)
    {
        // 检查是否存在奇偶校验错误(PE)、帧错误(FE)、噪声错误(NE)或溢出错误(ORE)
        if (__HAL_UART_GET_FLAG(huart, UART_FLAG_PE | UART_FLAG_FE |
                                           UART_FLAG_NE | UART_FLAG_ORE))
        {
            __HAL_UART_CLEAR_FLAG(huart, UART_FLAG_PE | UART_FLAG_FE |
                                             UART_FLAG_NE | UART_FLAG_ORE);
            HAL_UART_DMAStop(huart);
            // 重新启动UART DMA接收，使用指定的接收缓冲区和缓冲区大小
            HAL_UART_Receive_DMA(huart, mavlink_rx_buff, MAVLINK_RECV_BUFF_SIZE);
        }
    }
}

#ifdef USE_CAN
/**
 * @brief FDCAN接收FIFO0中断回调函数
 * @param hfdcan: FDCAN句柄
 * @param RxFifo0ITs: 中断标志位
 * @note 处理新接收的消息，解析数据并触发对应回调，同时回发响应
 */
void CAN_FDCAN_RX_FIFO0_CALLBACK(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs)
{
    if ((hfdcan->Instance == CAN_FDCAN_NUMBER) && (RxFifo0ITs & FDCAN_IT_RX_FIFO0_NEW_MESSAGE) != RESET)
    {
        fdcan_app_fifo0_handle(hfdcan);
    }
}
/**
 * @brief FDCAN接收FIFO1中断回调函数
 * @param hfdcan: FDCAN句柄
 * @param RxFifo0ITs: 中断标志位
 * @note 处理新接收的消息，解析数据并触发对应回调，同时回发响应
 */
void CAN_FDCAN_RX_FIFO1_CALLBACK(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo1ITs)
{
    if ((hfdcan->Instance == CAN_FDCAN_NUMBER) && (RxFifo1ITs & FDCAN_IT_RX_FIFO1_NEW_MESSAGE) != RESET)
    {
        fdcan_app_fifo1_handle(hfdcan);
    }
}
#endif // USE_CAN
