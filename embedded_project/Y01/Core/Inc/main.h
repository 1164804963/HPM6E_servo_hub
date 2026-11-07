/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define ECAT_QSPI_D2_Pin GPIO_PIN_2
#define ECAT_QSPI_D2_GPIO_Port GPIOE
#define USER_IO1_Pin GPIO_PIN_3
#define USER_IO1_GPIO_Port GPIOE
#define USER_IO2_Pin GPIO_PIN_4
#define USER_IO2_GPIO_Port GPIOE
#define USER_IO3_Pin GPIO_PIN_5
#define USER_IO3_GPIO_Port GPIOE
#define USER_IO4_Pin GPIO_PIN_6
#define USER_IO4_GPIO_Port GPIOE
#define USER_IO5_Pin GPIO_PIN_13
#define USER_IO5_GPIO_Port GPIOC
#define USER_IO6_Pin GPIO_PIN_14
#define USER_IO6_GPIO_Port GPIOC
#define USER_IO7_Pin GPIO_PIN_15
#define USER_IO7_GPIO_Port GPIOC
#define IU_Pin GPIO_PIN_0
#define IU_GPIO_Port GPIOC
#define IV_Pin GPIO_PIN_1
#define IV_GPIO_Port GPIOC
#define IW_Pin GPIO_PIN_2
#define IW_GPIO_Port GPIOC
#define TEMP_MOT_Pin GPIO_PIN_3
#define TEMP_MOT_GPIO_Port GPIOC
#define DC_CURRENT_Pin GPIO_PIN_0
#define DC_CURRENT_GPIO_Port GPIOA
#define DC_BUS_Pin GPIO_PIN_2
#define DC_BUS_GPIO_Port GPIOA
#define TEMP_MOS_Pin GPIO_PIN_3
#define TEMP_MOS_GPIO_Port GPIOA
#define ENC1_SPI_NSS_Pin GPIO_PIN_4
#define ENC1_SPI_NSS_GPIO_Port GPIOA
#define ENC1_SPI_SCK_Pin GPIO_PIN_5
#define ENC1_SPI_SCK_GPIO_Port GPIOA
#define ENC1_SPI_MISO_Pin GPIO_PIN_6
#define ENC1_SPI_MISO_GPIO_Port GPIOA
#define ENC1_SPI_MOSI_Pin GPIO_PIN_7
#define ENC1_SPI_MOSI_GPIO_Port GPIOA
#define USER_ADC1_Pin GPIO_PIN_4
#define USER_ADC1_GPIO_Port GPIOC
#define DRV_EN_GATE_Pin GPIO_PIN_5
#define DRV_EN_GATE_GPIO_Port GPIOC
#define ECAT_QSPI_CLK_Pin GPIO_PIN_2
#define ECAT_QSPI_CLK_GPIO_Port GPIOB
#define PWM_UL_Pin GPIO_PIN_8
#define PWM_UL_GPIO_Port GPIOE
#define PWM_UH_Pin GPIO_PIN_9
#define PWM_UH_GPIO_Port GPIOE
#define PWM_VL_Pin GPIO_PIN_10
#define PWM_VL_GPIO_Port GPIOE
#define PWM_VH_Pin GPIO_PIN_11
#define PWM_VH_GPIO_Port GPIOE
#define PWM_WL_Pin GPIO_PIN_12
#define PWM_WL_GPIO_Port GPIOE
#define PWM_WH_Pin GPIO_PIN_13
#define PWM_WH_GPIO_Port GPIOE
#define DRV_NFAULT_Pin GPIO_PIN_15
#define DRV_NFAULT_GPIO_Port GPIOE
#define ECAT_QSPI_NCS_Pin GPIO_PIN_10
#define ECAT_QSPI_NCS_GPIO_Port GPIOB
#define BRAKE_PWM_Pin GPIO_PIN_11
#define BRAKE_PWM_GPIO_Port GPIOB
#define ENC2_SPI_NSS_Pin GPIO_PIN_12
#define ENC2_SPI_NSS_GPIO_Port GPIOB
#define ENC2_SPI_SCK_Pin GPIO_PIN_13
#define ENC2_SPI_SCK_GPIO_Port GPIOB
#define ENC2_SPI_MISO_Pin GPIO_PIN_14
#define ENC2_SPI_MISO_GPIO_Port GPIOB
#define ENC2_SPI_MOSI_Pin GPIO_PIN_15
#define ENC2_SPI_MOSI_GPIO_Port GPIOB
#define ECAT_SYNC1_Pin GPIO_PIN_8
#define ECAT_SYNC1_GPIO_Port GPIOD
#define ECAT_SYNC1_EXTI_IRQn EXTI9_5_IRQn
#define ECAT_SYNC0_Pin GPIO_PIN_9
#define ECAT_SYNC0_GPIO_Port GPIOD
#define ECAT_SYNC0_EXTI_IRQn EXTI9_5_IRQn
#define ECAT_IRQ_Pin GPIO_PIN_10
#define ECAT_IRQ_GPIO_Port GPIOD
#define ECAT_IRQ_EXTI_IRQn EXTI15_10_IRQn
#define ECAT_QSPI_D0_Pin GPIO_PIN_11
#define ECAT_QSPI_D0_GPIO_Port GPIOD
#define ECAT_QSPI_D1_Pin GPIO_PIN_12
#define ECAT_QSPI_D1_GPIO_Port GPIOD
#define ECAT_QSPI_D3_Pin GPIO_PIN_13
#define ECAT_QSPI_D3_GPIO_Port GPIOD
#define ENC2_RS485_DE_Pin GPIO_PIN_15
#define ENC2_RS485_DE_GPIO_Port GPIOD
#define ENC1_A_Pin GPIO_PIN_6
#define ENC1_A_GPIO_Port GPIOC
#define ENC1_B_Pin GPIO_PIN_7
#define ENC1_B_GPIO_Port GPIOC
#define ENC1_Z_Pin GPIO_PIN_8
#define ENC1_Z_GPIO_Port GPIOC
#define USER_USART1_CK_Pin GPIO_PIN_8
#define USER_USART1_CK_GPIO_Port GPIOA
#define USER_USART1_TX_Pin GPIO_PIN_9
#define USER_USART1_TX_GPIO_Port GPIOA
#define USER_USART1_RX_Pin GPIO_PIN_10
#define USER_USART1_RX_GPIO_Port GPIOA
#define SWDIO_Pin GPIO_PIN_13
#define SWDIO_GPIO_Port GPIOA
#define SWCLK_Pin GPIO_PIN_14
#define SWCLK_GPIO_Port GPIOA
#define ENC1_RS485_DE_Pin GPIO_PIN_15
#define ENC1_RS485_DE_GPIO_Port GPIOA
#define AF_SPI_SCK_Pin GPIO_PIN_10
#define AF_SPI_SCK_GPIO_Port GPIOC
#define AF_SPI_MISO_Pin GPIO_PIN_11
#define AF_SPI_MISO_GPIO_Port GPIOC
#define AF_SPI_MOSI_Pin GPIO_PIN_12
#define AF_SPI_MOSI_GPIO_Port GPIOC
#define ENC1_RS485_RX_Pin GPIO_PIN_0
#define ENC1_RS485_RX_GPIO_Port GPIOD
#define ENC1_RS485_TX_Pin GPIO_PIN_1
#define ENC1_RS485_TX_GPIO_Port GPIOD
#define DRV_AF_SPI_NSS_Pin GPIO_PIN_2
#define DRV_AF_SPI_NSS_GPIO_Port GPIOD
#define FLASH_AF_SPI_NSS_Pin GPIO_PIN_3
#define FLASH_AF_SPI_NSS_GPIO_Port GPIOD
#define HOST_UART_DE_Pin GPIO_PIN_4
#define HOST_UART_DE_GPIO_Port GPIOD
#define HOST_UART_TX_Pin GPIO_PIN_5
#define HOST_UART_TX_GPIO_Port GPIOD
#define HOST_UART_RX_Pin GPIO_PIN_6
#define HOST_UART_RX_GPIO_Port GPIOD
#define USER_SPI_NSS_Pin GPIO_PIN_7
#define USER_SPI_NSS_GPIO_Port GPIOD
#define USER_SPI_SCK_Pin GPIO_PIN_3
#define USER_SPI_SCK_GPIO_Port GPIOB
#define USER_SPI_MISO_Pin GPIO_PIN_4
#define USER_SPI_MISO_GPIO_Port GPIOB
#define USER_SPI_MOSI_Pin GPIO_PIN_5
#define USER_SPI_MOSI_GPIO_Port GPIOB
#define LED_RED_Pin GPIO_PIN_6
#define LED_RED_GPIO_Port GPIOB
#define LED_BLUE_Pin GPIO_PIN_7
#define LED_BLUE_GPIO_Port GPIOB
#define USER_IIC_SCL_Pin GPIO_PIN_8
#define USER_IIC_SCL_GPIO_Port GPIOB
#define USER_IIC_SDA_Pin GPIO_PIN_9
#define USER_IIC_SDA_GPIO_Port GPIOB
#define ENC2_RS485_RX_Pin GPIO_PIN_0
#define ENC2_RS485_RX_GPIO_Port GPIOE
#define ENC2_RS485_TX_Pin GPIO_PIN_1
#define ENC2_RS485_TX_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */
extern ADC_HandleTypeDef hadc1;
extern ADC_HandleTypeDef hadc2;
extern ADC_HandleTypeDef hadc3;
extern DMA_HandleTypeDef hdma_adc1;
extern DMA_HandleTypeDef hdma_adc2;
extern DMA_HandleTypeDef hdma_adc3;

extern CRC_HandleTypeDef hcrc;

extern FDCAN_HandleTypeDef hfdcan1;

extern I2C_HandleTypeDef hi2c1;

extern QSPI_HandleTypeDef hqspi;

extern SPI_HandleTypeDef hspi1;
extern SPI_HandleTypeDef hspi2;
extern SPI_HandleTypeDef hspi3;
extern SPI_HandleTypeDef hspi6;
extern DMA_HandleTypeDef hdma_spi1_rx;
extern DMA_HandleTypeDef hdma_spi1_tx;
extern DMA_HandleTypeDef hdma_spi2_rx;
extern DMA_HandleTypeDef hdma_spi2_tx;

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim5;
extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim7;
extern TIM_HandleTypeDef htim13;

extern UART_HandleTypeDef huart4;
extern UART_HandleTypeDef huart8;
extern USART_HandleTypeDef husart1;
extern UART_HandleTypeDef huart2;
extern DMA_HandleTypeDef hdma_uart4_rx;
extern DMA_HandleTypeDef hdma_uart4_tx;
extern DMA_HandleTypeDef hdma_uart8_rx;
extern DMA_HandleTypeDef hdma_uart8_tx;
extern DMA_HandleTypeDef hdma_usart2_rx;
extern DMA_HandleTypeDef hdma_usart2_tx;

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
