#ifndef BOARD_H
#define BOARD_H

#include "main.h"

#include "motor_ctl_loop.h"
#include "mavlink_callback.h"

#include "system_init.h"
#include "system_timer.h"

#include "bsp_fdcan.h"
#include "drv_can_app.h"
#include "drv_encoder.h"
#include "drv_nor_flash.h"
#include "drv_upgrade.h"

typedef enum
{
    CS_SOURCE_IDLE     = 0,
    CS_SOURCE_SYNC0    = 1,
    CS_SOURCE_SYNC1    = 2,
    CS_SOURCE_IRQ_SM   = 3,
} CS_SOURCE;

typedef struct
{
    bool sync0_trigger;                 // DC同步中断触发标志
    CS_SOURCE ctrl_source;              // 同步控制源
    uint8_t pl_period_cs_cnt;           // 位置环周期同步计数
    uint8_t pl_period_total;            // 位置环周期总数
    uint8_t pl_period_cnt;              // 位置环周期计数
    uint8_t pl_period_index;            // 位置环周期索引
    uint8_t frame_pl_period_index;      // 数据帧位置环周期索引
    uint8_t shift_max_pl_period_index;  // 最大偏移量位置环周期索引
    uint8_t latch_pl_period_index;      // 目标锁存更新位置环周期索引
} BspCyclicSync; //同步周期模式控制参数

typedef struct
{
    uint16_t adc1_raw_buffer[3];
    uint16_t adc2_raw_buffer[3];
    uint16_t adc3_raw_buffer[3];
    float dc_bus_voltage_val;
    float dc_bus_current_val;
    float motor_temp_val;
    float mos_temp_val;
    float mcu_temp[3];
    volatile float uvw_current[3];
    volatile float uvw_target_voltage[3];
    bool pwm_en_state;
    bool pwm_ready_state;
    uint32_t pwm_state_cnt;
    uint16_t brake_pwm_timer_psc;         // PWM抱闸IO输出定时器预分频值
    uint32_t brake_pwm_timer_arr;         // PWM抱闸IO输出定时器自动重装载值
    uint32_t brake_pwm_duty_ccr_tar;      // 抱闸PWM占空比对应CCR目标值
    uint32_t brake_pwm_duty_ccr_action;   // 抱闸PWM占空比对应CCR动作值
    uint32_t brake_pwm_duty_ccr_hold;     // 抱闸PWM占空比对应CCR保持值
    bool pl_start_state;
    BspCyclicSync cs;
} BspData;


#pragma region // MCU 外设寄存器映射
#pragma region // ANALOG
#define ADC_REFERENCE_V             (3.3f)      // ADC参考电压(V)
#define ADC_REFERENCE_MV            (3300)      // ADC参考电压(mV)
#define ADC_RESOLTION               (65536.0f)  // ADC采样分辨率(16位)

#define UVW_CURRENT_U_HANDLE        (hadc1)
#define UVW_CURRENT_V_HANDLE        (hadc2)
#define UVW_CURRENT_W_HANDLE        (hadc3)
#define UVW_CURRENT_U_CHANNEL       (UVW_CURRENT_U_HANDLE.Instance->JDR1)
#define UVW_CURRENT_V_CHANNEL       (UVW_CURRENT_V_HANDLE.Instance->JDR1)
#define UVW_CURRENT_W_CHANNEL       (UVW_CURRENT_W_HANDLE.Instance->JDR1)
#define CURRENT_LOOP_IRQ_TASK       HAL_ADCEx_InjectedConvCpltCallback

#define ADC1_REGULAR_RANK_NUMBER    (2)
#define ADC2_REGULAR_RANK_NUMBER    (2)
#define ADC3_REGULAR_RANK_NUMBER    (2)

#define DC_BUS_VOLTAGE_HANDLE       (hadc1)
#define DC_BUS_CURRENT_HANDLE       (hadc1)
#define DC_BUS_VOLTAGE_RANK1_INDEX  (0)
#define DC_BUS_CURRENT_RANK2_INDEX  (1)
#define TEMP_MOS_HANDLE             (hadc2)
#define USER_ADC1_HANDLE            (hadc2)
#define TEMP_MOS_RANK1_INDEX        (0)
#define USER_ADC1_RANK2_INDEX       (1)
#define TEMP_MCU_HANDLE             (hadc3)
#define TEMP_MOTOR_HANDLE           (hadc3)
#define TEMP_MCU_RANK1_INDEX        (0)
#define TEMP_MOTOR_RANK2_INDEX      (1)
#pragma endregion // ANALOG

#pragma region // TIMERS
#define PWM_TIM_ARR                 (6000u)  // PWM定时器ARR值，此宏可同步用于CubeMX配置框（No Check）
#define PWM_TIM_ARR_HALF            (3000u)  // PWM定时器ARR值的一半，此宏可同步用于CubeMX配置框（No Check）
#define PWM_TIM_ARR_P_LIMIT         (5400u)  // PWM定时器ARR上限值（PWM_TIM_ARR * 90%）
#define PWM_TIM_ARR_LIMIT_HALF      (2700u)  // PWM定时器ARR上限值的一半
#define PWM_TIM_ARR_N_LIMIT         (0u)     // PWM定时器ARR下限值（0）

#define PWM_TIM_HANDLE              (htim1)
#define PWM_TIM_U_CHANNEL           (TIM_CHANNEL_1)
#define PWM_TIM_V_CHANNEL           (TIM_CHANNEL_2)
#define PWM_TIM_W_CHANNEL           (TIM_CHANNEL_3)
#define PWM_TIM_U_CCR_VAL           (PWM_TIM_HANDLE.Instance->CCR1)
#define PWM_TIM_V_CCR_VAL           (PWM_TIM_HANDLE.Instance->CCR2)
#define PWM_TIM_W_CCR_VAL           (PWM_TIM_HANDLE.Instance->CCR3)
#define PWM_TIM_BREAK_IRQ_HANDLE    HAL_TIMEx_BreakCallback

#define BRAKE_PWM_TIM_HANDLE        (htim2)                     //PWM抱闸IO输出定时器
#define BRAKE_PWM_TIM_CHANNEL       (TIM_CHANNEL_4)             //PWM抱闸IO输出定时器通道
#define BRAKE_PWM_TIM_FREQ          (HAL_RCC_GetPCLK1Freq())    //PWM抱闸IO输出定时器频率（内部分频前）
#define BRAKE_PWM_DUTY_CCR_ENGAGED  (0u)                        //抱闸PWM合闸占对应空比CCR值
#define BRAKE_PWM_TIM_PSC_VAL       (BRAKE_PWM_TIM_HANDLE.Instance->PSC)
#define BRAKE_PWM_TIM_ARR_VAL       (BRAKE_PWM_TIM_HANDLE.Instance->ARR)
#define BRAKE_PWM_TIM_CCR_VAL       (BRAKE_PWM_TIM_HANDLE.Instance->CCR4)
#define ENCODER1_ABZ_TIM_HANDLE     (htim3)                     //ABZ增量式编码器1定时器
#define ENCODER1_ABZ_TIM_Z_CHANNEL  (TIM_CHANNEL_3)             //ABZ增量式编码器1定时器Z相捕获通道
#define ENCODER2_ABZ_TIM_HANDLE     (htim3)                     //ABZ增量式编码器2定时器
#define ENCODER2_ABZ_TIM_Z_CHANNEL  (TIM_CHANNEL_3)             //ABZ增量式编码器2定时器Z相捕获通道
#define ENCODER_ABZ_TIM_Z_IRQ_TASK  HAL_TIM_IC_CaptureCallback  //Z相中断回调函数
#define POSITION_LOOP_TIM_HANDLE    (htim5)                     //位置环定时器
#define POSITION_LOOP_TIM_IRQ_TASK  TIM5_IRQHandler             //位置环定时器中断回调函数
#define CANOPEN_TIM_HANDLE          (htim6)                     //CANopen定时器
#define CANOPEN_TIM_ARR             (1000 - 1)                  //CANopen定时器ARR值，此宏可同步用于CubeMX配置框（No Check）
#define ECAT_LAN9252_TIM_HANDLE     (htim7)                     //EtherCAT定时器
#define NRT_TASK_TIM_HANDLE         (htim13)                    //非实时(1ms)任务定时器
#define NRT_CAN_ECAT_IRQ_TASK       HAL_TIM_PeriodElapsedCallback

#pragma endregion // TIMERS

#pragma region // CONNECTIVITY
#define CAN_FDCAN_HANDLE            (hfdcan1)
#define CAN_FDCAN_NUMBER            (FDCAN1)
#define CAN_FDCAN_RX_FIFO0_CALLBACK HAL_FDCAN_RxFifo0Callback
#define CAN_FDCAN_RX_FIFO1_CALLBACK HAL_FDCAN_RxFifo1Callback

#define ECAT_LAN9252_QSPI_HANDLE    (hqspi)

#define ENCODER1_SPI_HANDLE         (hspi1)
#define ENCODER2_SPI_HANDLE         (hspi2)
#define AF_SPI_HANDLE               (hspi3)
#define DRV_SPI_HANDLE              (AF_SPI_HANDLE)
#define DRV_SPI_CS_ENABLE()         (HAL_GPIO_WritePin(DRV_AF_SPI_NSS_GPIO_Port, DRV_AF_SPI_NSS_Pin, GPIO_PIN_RESET))
#define DRV_SPI_CS_DISABLE()        (HAL_GPIO_WritePin(DRV_AF_SPI_NSS_GPIO_Port, DRV_AF_SPI_NSS_Pin, GPIO_PIN_SET))
#define FLASH_SPI_HANDLE            (AF_SPI_HANDLE)
#define FLASH_SPI_CS_ENABLE()       (HAL_GPIO_WritePin(FLASH_AF_SPI_NSS_GPIO_Port, FLASH_AF_SPI_NSS_Pin, GPIO_PIN_RESET))
#define FLASH_SPI_CS_DISABLE()      (HAL_GPIO_WritePin(FLASH_AF_SPI_NSS_GPIO_Port, FLASH_AF_SPI_NSS_Pin, GPIO_PIN_SET))

#define ENCODER_DUAL_UART_HANDLE    (huart4)
#define ENCODER1_UART_HANDLE        (huart4)
#define ENCODER2_UART_HANDLE        (huart8)

#define HOST_UART_HANDLE            (huart2)
#define HOST_UART_IRQ_TASK          USART2_IRQHandler
#define HOST_UART_ERROR_HANDLE      HAL_UART_ErrorCallback

#define USER_IIC_HANDLE             (hi2c1)
#define USER_USART_HANDLE           (husart1)

#define USER_SPI_HANDLE             (hspi6)
#define USER_SPI_CS_ENABLE()        (HAL_GPIO_WritePin(USER_SPI_NSS_GPIO_Port, USER_SPI_NSS_Pin, GPIO_PIN_RESET))
#define USER_SPI_CS_DISABLE()       (HAL_GPIO_WritePin(USER_SPI_NSS_GPIO_Port, USER_SPI_NSS_Pin, GPIO_PIN_SET))
#pragma endregion // CONNECTIVITY

#pragma region // GPIO
#define DRV_GATE_ENABLE()           (HAL_GPIO_WritePin(DRV_EN_GATE_GPIO_Port, DRV_EN_GATE_Pin, GPIO_PIN_SET))
#define DRV_GATE_DISABLE()          (HAL_GPIO_WritePin(DRV_EN_GATE_GPIO_Port, DRV_EN_GATE_Pin, GPIO_PIN_RESET))

#define ECAT_IRQ_EXTI_LINE          (ECAT_IRQ_Pin)
#define ECAT_IRQ_ECTI_IRQN          (ECAT_IRQ_EXTI_IRQn)
#define ECAT_SYNC0_EXTI_LINE        (ECAT_SYNC0_Pin)
#define ECAT_SYNC0_EXTI_IRQN        (ECAT_SYNC0_EXTI_IRQn)
#define ECAT_SYNC1_EXTI_LINE        (ECAT_SYNC1_Pin)
#define ECAT_SYNC1_EXTI_IRQN        (ECAT_SYNC1_EXTI_IRQn)
#define ECAT_EXTI_IRQ_TASK          HAL_GPIO_EXTI_Callback
#define ECAT_EXTI_PR1_PR            EXTI_PR1_PR9

#define CS_PL_PERIOD_CS_JUDGE_CNT   (50u) //同步周期判断次数，time = CS_PL_PERIOD_CS_JUDGE_CNT * DC_CYCLE_TIME

#define ECAT_SYNC_NVIC_PRIORITY     (4u)               //同步任务GPIO软件中断优先级
#define ECAT_SYNC_IRQ_TASK          EXTI0_IRQHandler   //同步任务GPIO软件中断回调函数
#define ECAT_SYNC_EXTIX_IRQN        EXTI0_IRQn         //同步任务GPIO软件中断号
#define ECAT_SYNC_EXTI_LINE_X       EXTI_LINE_0        //同步任务GPIO软件中断线
#define ECAT_SYNC_SWIER1_SWIER      EXTI_SWIER1_SWIER0 //同步任务GPIO软件中断使能位
#define ECAT_SYNC_PR1_PR            EXTI_PR1_PR0       //同步任务GPIO软件中断标志位

#define ECAT_PDI_NVIC_PRIORITY      (5u)               //PDI任务GPIO软件中断优先级
#define ECAT_PDI_IRQ_TASK           EXTI1_IRQHandler   //PDI任务GPIO软件中断回调函数
#define ECAT_PDI_EXTIX_IRQN         EXTI1_IRQn         //PDI任务GPIO软件中断号
#define ECAT_PDI_EXTI_LINE_X        EXTI_LINE_1        //PDI任务GPIO软件中断线
#define ECAT_PDI_SWIER1_SWIER       EXTI_SWIER1_SWIER1 //PDI任务GPIO软件中断使能位
#define ECAT_PDI_PR1_PR             EXTI_PR1_PR1       //PDI任务GPIO软件中断标志位

#define LED_ON_GPIO_LEVEL           (GPIO_PIN_RESET)
#define LED_OFF_GPIO_LEVEL          (!LED_ON_GPIO_LEVEL)

#define LED_RED_ON()                (HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, LED_ON_GPIO_LEVEL))
#define LED_RED_OFF()               (HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, LED_OFF_GPIO_LEVEL))
#define LED_RED_TOGGLE()            (HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin))
#define LED_BLUE_ON()               (HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, LED_ON_GPIO_LEVEL))
#define LED_BLUE_OFF()              (HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, LED_OFF_GPIO_LEVEL))
#define LED_BLUE_TOGGLE()           (HAL_GPIO_TogglePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin))

#define USER_IO1_READ()             (HAL_GPIO_ReadPin(USER_IO1_GPIO_Port, USER_IO1_Pin))
#define USER_IO1_WRITE(pin_state)   (HAL_GPIO_WritePin(USER_IO1_GPIO_Port, USER_IO1_Pin, (GPIO_PinState)pin_state))
#define USER_IO2_READ()             (HAL_GPIO_ReadPin(USER_IO2_GPIO_Port, USER_IO2_Pin))
#define USER_IO2_WRITE(pin_state)   (HAL_GPIO_WritePin(USER_IO2_GPIO_Port, USER_IO2_Pin, (GPIO_PinState)pin_state))
#define USER_IO3_READ()             (HAL_GPIO_ReadPin(USER_IO3_GPIO_Port, USER_IO3_Pin))
#define USER_IO3_WRITE(pin_state)   (HAL_GPIO_WritePin(USER_IO3_GPIO_Port, USER_IO3_Pin, (GPIO_PinState)pin_state))
#define USER_IO4_READ()             (HAL_GPIO_ReadPin(USER_IO4_GPIO_Port, USER_IO4_Pin))
#define USER_IO4_WRITE(pin_state)   (HAL_GPIO_WritePin(USER_IO4_GPIO_Port, USER_IO4_Pin, (GPIO_PinState)pin_state))
#define USER_IO5_READ()             (HAL_GPIO_ReadPin(USER_IO5_GPIO_Port, USER_IO5_Pin))
#define USER_IO5_WRITE(pin_state)   (HAL_GPIO_WritePin(USER_IO5_GPIO_Port, USER_IO5_Pin, (GPIO_PinState)pin_state))
#define USER_IO6_READ()             (HAL_GPIO_ReadPin(USER_IO6_GPIO_Port, USER_IO6_Pin))
#define USER_IO6_WRITE(pin_state)   (HAL_GPIO_WritePin(USER_IO6_GPIO_Port, USER_IO6_Pin, (GPIO_PinState)pin_state))
#define USER_IO7_READ()             (HAL_GPIO_ReadPin(USER_IO7_GPIO_Port, USER_IO7_Pin))
#define USER_IO7_WRITE(pin_state)   (HAL_GPIO_WritePin(USER_IO7_GPIO_Port, USER_IO7_Pin, (GPIO_PinState)pin_state))
#define BRAKE_IO_READ()             (HAL_GPIO_ReadPin(BRAKE_PWM_GPIO_Port, BRAKE_PWM_Pin))
#define BRAKE_IO_WRITE(pin_state)   (HAL_GPIO_WritePin(BRAKE_PWM_GPIO_Port, BRAKE_PWM_Pin, (GPIO_PinState)pin_state))

// 数字输入IO功能自定义分配，有效电平及读取函数
#define DI_IO_NEGATIVE_LIMIT_SWITCH_LEVEL       (GPIO_PIN_RESET)
#define DI_IO_NEGATIVE_LIMIT_SWITCH_READ()      USER_IO1_READ()
#define DI_IO_POSITIVE_LIMIT_SWITCH_LEVEL       (GPIO_PIN_RESET)
#define DI_IO_POSITIVE_LIMIT_SWITCH_READ()      USER_IO2_READ()
#define DI_IO_HOME_SWITCH_LEVEL                 (GPIO_PIN_RESET)
#define DI_IO_HOME_SWITCH_READ()                USER_IO3_READ()
#define DI_IO_INTERLOCK_LEVEL                   (GPIO_PIN_RESET)
#define DI_IO_INTERLOCK_READ()                  USER_IO4_READ()
#define DI_IO_USER_0_LEVEL                      (GPIO_PIN_SET)
#define DI_IO_USER_0_READ()                     USER_IO4_READ()
// ...

// 数字输出IO功能自定义分配，有效电平及写入函数
#define DO_IO_SET_BRAKE_RELEASED_LEVEL          (GPIO_PIN_SET) // 松闸电平
#define DO_IO_SET_BRAKE_WRITE(pin_state)        BRAKE_IO_WRITE((GPIO_PinState)pin_state)
#define DO_IO_USER_0_LEVEL                      (GPIO_PIN_SET)
#define DO_IO_USER_0_WRITE(pin_state)           USER_IO6_WRITE((GPIO_PinState)pin_state)
// ...
#pragma endregion // GPIO

#pragma endregion // MCU 外设寄存器映射

extern BspData kBspData;

void BspInit(void);
void mavlink_send_data(uint8_t *pdata, uint32_t len);

#ifdef __cplusplus
extern "C"
{
#endif


#ifdef __cplusplus
}
#endif


#endif// BOARD_H
