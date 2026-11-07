#include "ecat_app_hw.h"

typedef union
{
    unsigned short Word;
    unsigned char Byte[2];

} UBYTETOWORD;

typedef union
{
    UINT8 Byte[2];
    UINT16 Word;

} UALEVENT;

UALEVENT EscALEvent;

static void GetInterruptRegister(void)
{
    DISABLE_AL_EVENT_INT;
    HW_EscReadIsr((MEM_ADDR *)&EscALEvent.Word, 0x220, 2);
    ENABLE_AL_EVENT_INT;
}

static void ISR_GetInterruptRegister(void)
{
    HW_EscReadIsr((MEM_ADDR *)&EscALEvent.Word, 0x220, 2);
}

UINT8 HW_Init(void)
{
    UINT16 intMask;
    UINT32 data;
    do
    {
        data = SQIReadDWord(0x64);
    } while (0x87654321 != data);
    do
    {
        intMask = 0x93;
        HW_EscWriteWord(intMask, ESC_AL_EVENTMASK_OFFSET);
        intMask = 0;
        HW_EscReadWord(intMask, ESC_AL_EVENTMASK_OFFSET);
    } while (intMask != 0x93);
    intMask = 0x00;
    HW_EscWriteDWord(intMask, ESC_AL_EVENTMASK_OFFSET);
    data = 0x00000101;
    SQIWriteDWord(0x54, data);
    data = 0x00000001;
    SQIWriteDWord(0x5C, data);
    SQIReadDWord(0x58);
    INIT_ESC_INT();
    ENABLE_ESC_INT();
    INIT_SYNC0_INT();
    INIT_SYNC1_INT();
    ENABLE_SYNC0_INT();
    ENABLE_SYNC1_INT();
    INIT_ECAT_TIMER();
    START_ECAT_TIMER();
    ENABLE_GLOBAL_INT;
    return 0;
}

void HW_Release(void)
{
}

UINT16 HW_GetALEventRegister(void)
{
    GetInterruptRegister();
    return EscALEvent.Word;
}

UINT16 HW_GetALEventRegister_Isr(void)
{
    ISR_GetInterruptRegister();
    return EscALEvent.Word;
}

void HW_SetLed(UINT8 RunLed, UINT8 ErrLed)
{
}

void HW_EscRead(MEM_ADDR *pData, UINT16 Address, UINT16 Len)
{
    UINT16 i;
    UINT8 *pTmpData = (UINT8 *)pData;

    /* loop for all bytes to be read */
    while (Len > 0)
    {

        i = (Len > 4) ? 4 : Len;

        if (Address & 01)
        {
            i = 1;
        }
        else if (Address & 02)
        {
            i = (i & 1) ? 1 : 2;
        }
        else if (i == 03)
        {
            i = 1;
        }

        DISABLE_AL_EVENT_INT;

        SQIReadDRegister(pTmpData, Address, i);

        ENABLE_AL_EVENT_INT;

        Len -= i;
        pTmpData += i;
        Address += i;
    }
}

void HW_EscReadIsr(MEM_ADDR *pData, UINT16 Address, UINT16 Len)
{
    UINT16 i;
    UINT8 *pTmpData = (UINT8 *)pData;

    /* send the address and command to the ESC */

    /* loop for all bytes to be read */
    while (Len > 0)
    {

        i = (Len > 4) ? 4 : Len;

        if (Address & 01)
        {
            i = 1;
        }
        else if (Address & 02)
        {
            i = (i & 1) ? 1 : 2;
        }
        else if (i == 03)
        {
            i = 1;
        }

        SQIReadDRegister(pTmpData, Address, i);

        Len -= i;
        pTmpData += i;
        Address += i;
    }
}

void HW_EscWrite(MEM_ADDR *pData, UINT16 Address, UINT16 Len)
{
    UINT16 i;
    UINT8 *pTmpData = (UINT8 *)pData;

    /* loop for all bytes to be written */
    while (Len)
    {
        i = (Len > 4) ? 4 : Len;

        if (Address & 01)
        {
            i = 1;
        }
        else if (Address & 02)
        {
            i = (i & 1) ? 1 : 2;
        }
        else if (i == 03)
        {
            i = 1;
        }

        DISABLE_AL_EVENT_INT;

        SQIWriteRegister(pTmpData, Address, i);

        ENABLE_AL_EVENT_INT;

        /* next address */
        Len -= i;
        pTmpData += i;
        Address += i;
    }
}

void HW_EscWriteIsr(MEM_ADDR *pData, UINT16 Address, UINT16 Len)
{
    UINT16 i;
    UINT8 *pTmpData = (UINT8 *)pData;
    while (Len)
    {
        i = (Len > 4) ? 4 : Len;

        if (Address & 01)
        {
            i = 1;
        }
        else if (Address & 02)
        {
            i = (i & 1) ? 1 : 2;
        }
        else if (i == 03)
        {
            i = 1;
        }
        SQIWriteRegister(pTmpData, Address, i);
        Len -= i;
        pTmpData += i;
        Address += i;
    }
}
