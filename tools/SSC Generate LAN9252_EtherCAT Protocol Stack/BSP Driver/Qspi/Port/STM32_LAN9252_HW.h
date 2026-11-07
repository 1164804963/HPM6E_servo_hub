
#ifndef __STM32_LAN9252_HW_H
#define __STM32_LAN9252_HW_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "main.h"
#include "gpio.h"
#include "tim.h"
#include "esc.h"
#include "ecat_def.h"

/*-----------------------------------------------------------------------------------------
------
------    全局中断
------
-----------------------------------------------------------------------------------------*/
#define DISABLE_GLOBAL_INT __set_PRIMASK(1)
#define ENABLE_GLOBAL_INT __set_PRIMASK(0)
#define DISABLE_AL_EVENT_INT DISABLE_GLOBAL_INT
#define ENABLE_AL_EVENT_INT ENABLE_GLOBAL_INT

/*-----------------------------------------------------------------------------------------
------
------    SYNC0中断
------
-----------------------------------------------------------------------------------------*/
#define LAN9252_SYNC0_PIN ECAT_SYNC0_Pin
#define LAN9252_SYNC0_IRQ ECAT_SYNC0_EXTI_IRQn

#define INIT_SYNC0_INT()
#define DISABLE_SYNC0_INT() HAL_NVIC_DisableIRQ(LAN9252_SYNC0_IRQ)
#define ENABLE_SYNC0_INT() HAL_NVIC_EnableIRQ(LAN9252_SYNC0_IRQ)

/*-----------------------------------------------------------------------------------------
------
------    SYNC1中断
------
-----------------------------------------------------------------------------------------*/
#define LAN9252_SYNC1_PIN ECAT_SYNC1_Pin
#define LAN9252_SYNC1_IRQ ECAT_SYNC1_EXTI_IRQn

#define INIT_SYNC1_INT()
#define DISABLE_SYNC1_INT() HAL_NVIC_DisableIRQ(LAN9252_SYNC1_IRQ)
#define ENABLE_SYNC1_INT() HAL_NVIC_EnableIRQ(LAN9252_SYNC1_IRQ)

/*-----------------------------------------------------------------------------------------
------
------    定时器中断
------
-----------------------------------------------------------------------------------------*/
#define LAN9252_TIM_HANDLE htim7
#define ECAT_TIMER_INC_P_MS 1000

#define HW_GetTimer() __HAL_TIM_GET_COUNTER(&LAN9252_TIM_HANDLE)
#define HW_ClearTimer() __HAL_TIM_SET_COUNTER(&LAN9252_TIM_HANDLE, 0)

#define INIT_ECAT_TIMER() __HAL_TIM_SET_COUNTER(&LAN9252_TIM_HANDLE, 0)
#define DISABLE_ECAT_TIMER_INT() __HAL_TIM_DISABLE_IT(&LAN9252_TIM_HANDLE, TIM_IT_UPDATE);
#define ENABLE_ECAT_TIMER_INT() __HAL_TIM_ENABLE_IT(&LAN9252_TIM_HANDLE, TIM_IT_UPDATE);
#define STOP_ECAT_TIMER() HAL_TIM_Base_Stop_IT(&LAN9252_TIM_HANDLE)
#define START_ECAT_TIMER() HAL_TIM_Base_Start_IT(&LAN9252_TIM_HANDLE)

/*-----------------------------------------------------------------------------------------
------
------    ESC中断
------
-----------------------------------------------------------------------------------------*/
#define LAN9252_IRQ_PIN ECAT_IRQ_Pin
#define LAN9252_IRQ_IRQ ECAT_IRQ_EXTI_IRQn

#define INIT_ESC_INT()
#define DISABLE_ESC_INT()                     \
    {                                         \
        HAL_NVIC_DisableIRQ(LAN9252_IRQ_IRQ); \
        DISABLE_SYNC0_INT();                  \
        DISABLE_ECAT_TIMER_INT();             \
    }
#define ENABLE_ESC_INT()                     \
    {                                        \
        HAL_NVIC_EnableIRQ(LAN9252_IRQ_IRQ); \
        ENABLE_SYNC0_INT();                  \
        ENABLE_ECAT_TIMER_INT();             \
    }

#define ESC_RD 0x02
#define ESC_WR 0x04

#define ECAT_REG_BASE_ADDR 0x0300

#define CSR_DATA_REG_OFFSET 0x00
#define CSR_CMD_REG_OFFSET 0x04
#define PRAM_READ_ADDR_LEN_OFFSET 0x08
#define PRAM_READ_CMD_OFFSET 0x0c
#define PRAM_WRITE_ADDR_LEN_OFFSET 0x10
#define PRAM_WRITE_CMD_OFFSET 0x14

#define PRAM_SPACE_AVBL_COUNT_MASK 0x1f
#define IS_PRAM_SPACE_AVBL_MASK 0x01

#define CSR_DATA_REG (ECAT_REG_BASE_ADDR + CSR_DATA_REG_OFFSET)
#define CSR_CMD_REG (ECAT_REG_BASE_ADDR + CSR_CMD_REG_OFFSET)
#define PRAM_READ_ADDR_LEN_REG (ECAT_REG_BASE_ADDR + PRAM_READ_ADDR_LEN_OFFSET)
#define PRAM_READ_CMD_REG (ECAT_REG_BASE_ADDR + PRAM_READ_CMD_OFFSET)
#define PRAM_WRITE_ADDR_LEN_REG (ECAT_REG_BASE_ADDR + PRAM_WRITE_ADDR_LEN_OFFSET)
#define PRAM_WRITE_CMD_REG (ECAT_REG_BASE_ADDR + PRAM_WRITE_CMD_OFFSET)

#define PRAM_READ_FIFO_REG 0x04
#define PRAM_WRITE_FIFO_REG 0x20

#define HBI_INDEXED_DATA0_REG 0x04
#define HBI_INDEXED_DATA1_REG 0x0c
#define HBI_INDEXED_DATA2_REG 0x14

#define HBI_INDEXED_INDEX0_REG 0x00
#define HBI_INDEXED_INDEX1_REG 0x08
#define HBI_INDEXED_INDEX2_REG 0x10

#define HBI_INDEXED_PRAM_READ_WRITE_FIFO 0x18

#define PRAM_RW_ABORT_MASK ((unsigned long)1 << 30)
#define PRAM_RW_BUSY_32B ((unsigned long)1 << 31)
#define PRAM_RW_BUSY_8B ((unsigned long)1 << 7)
#define PRAM_SET_READ ((unsigned long)1 << 6)
#define PRAM_SET_WRITE 0

#define HW_EscReadWord(WordValue, Address) HW_EscRead(((MEM_ADDR *)&(WordValue)), ((UINT16)(Address)), 2)
#define HW_EscReadDWord(DWordValue, Address) HW_EscRead(((MEM_ADDR *)&(DWordValue)), ((UINT16)(Address)), 4)
#define HW_EscReadByte(ByteValue, Address) HW_EscRead(((MEM_ADDR *)&(ByteValue)), ((UINT16)(Address)), 1)
#define HW_EscReadMbxMem(pData, Address, Len) HW_EscRead(((MEM_ADDR *)(pData)), ((UINT16)(Address)), (Len))

#define HW_EscReadWordIsr(WordValue, Address) HW_EscReadIsr(((MEM_ADDR *)&(WordValue)), ((UINT16)(Address)), 2)
#define HW_EscReadDWordIsr(DWordValue, Address) HW_EscReadIsr(((MEM_ADDR *)&(DWordValue)), ((UINT16)(Address)), 4)
#define HW_EscReadByteIsr(ByteValue, Address) HW_EscReadIsr(((MEM_ADDR *)&(ByteValue)), ((UINT16)(Address)), 1)

#define HW_EscWriteWord(WordValue, Address) HW_EscWrite(((MEM_ADDR *)&(WordValue)), ((UINT16)(Address)), 2)
#define HW_EscWriteDWord(DWordValue, Address) HW_EscWrite(((MEM_ADDR *)&(DWordValue)), ((UINT16)(Address)), 4)
#define HW_EscWriteByte(ByteValue, Address) HW_EscWrite(((MEM_ADDR *)&(ByteValue)), ((UINT16)(Address)), 1)
#define HW_EscWriteMbxMem(pData, Address, Len) HW_EscWrite(((MEM_ADDR *)(pData)), ((UINT16)(Address)), (Len))

#define HW_EscWriteWordIsr(WordValue, Address) HW_EscWriteIsr(((MEM_ADDR *)&(WordValue)), ((UINT16)(Address)), 2)
#define HW_EscWriteDWordIsr(DWordValue, Address) HW_EscWriteIsr(((MEM_ADDR *)&(DWordValue)), ((UINT16)(Address)), 4)
#define HW_EscWriteByteIsr(ByteValue, Address) HW_EscWriteIsr(((MEM_ADDR *)&(ByteValue)), ((UINT16)(Address)), 1)

    UINT8 HW_Init(void);
    void HW_Release(void);
    UINT16 HW_GetALEventRegister(void);
    UINT16 HW_GetALEventRegister_Isr(void);
    void HW_SetLed(UINT8 RunLed, UINT8 ErrLed);
    void HW_EscWrite(MEM_ADDR *pData, UINT16 Address, UINT16 Len);
    void HW_EscWriteIsr(MEM_ADDR *pData, UINT16 Address, UINT16 Len);
    void HW_EscRead(MEM_ADDR *pData, UINT16 Address, UINT16 Len);
    void HW_EscReadIsr(MEM_ADDR *pData, UINT16 Address, UINT16 Len);

#ifdef __cplusplus
}
#endif

#endif
