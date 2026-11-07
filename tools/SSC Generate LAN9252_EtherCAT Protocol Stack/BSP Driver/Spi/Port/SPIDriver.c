#include "SPIDriver.h"
#include "STM32_LAN9252_HW.h"

void SPIWriteByte(UINT8 data)
{
    HAL_SPI_Transmit(&LAN9252_SPI_HANDLE, &data, 1, 10);
}

UINT8 SPIReadByte()
{
    UINT8 data;
    HAL_SPI_Receive(&LAN9252_SPI_HANDLE, &data, 1, 10);
    return (data);
}

void SPISendAddr(UINT16 Address)
{
    UINT16_VAL wAddr;
    wAddr.Val = Address;
    UINT8 data[2] = {wAddr.byte.HB, wAddr.byte.LB};
    HAL_SPI_Transmit(&LAN9252_SPI_HANDLE, data, 2, 10);
}

UINT32 SPIReadDWord(UINT16 Address)
{
    UINT32_VAL dwResult;
    UINT8 data[4] = {0};
    CSLOW();
    SPIWriteByte(CMD_FAST_READ);
    SPISendAddr(Address);
    SPIWriteByte(CMD_FAST_READ_DUMMY);
    HAL_SPI_Receive(&LAN9252_SPI_HANDLE, data, 4, 10);
    CSHIGH();
    dwResult.byte.LB = data[0];
    dwResult.byte.HB = data[1];
    dwResult.byte.UB = data[2];
    dwResult.byte.MB = data[3];
    return dwResult.Val;
}

void SPIWriteDWord(UINT16 Address, UINT32 Val)
{
    UINT32_VAL dwData;
    UINT16_VAL wAddr;
    wAddr.Val = Address;
    dwData.Val = Val;
    CSLOW();
    SPIWriteByte(CMD_SERIAL_WRITE);
    SPISendAddr(wAddr.Val);
    UINT8 data[4] = {dwData.byte.LB, dwData.byte.HB, dwData.byte.UB, dwData.byte.MB};
    HAL_SPI_Transmit(&LAN9252_SPI_HANDLE, data, 4, 10);
    CSHIGH();
}

UINT32 SPIReadBurstMode()
{
    UINT32_VAL dwResult;
    UINT8 data[4] = {0};
    HAL_SPI_Receive(&LAN9252_SPI_HANDLE, data, 4, 10);
    dwResult.byte.LB = data[0];
    dwResult.byte.HB = data[1];
    dwResult.byte.UB = data[2];
    dwResult.byte.MB = data[3];
    return dwResult.Val;
}

void SPIWriteBurstMode(UINT32 Val)
{
    UINT32_VAL dwData;
    dwData.Val = Val;
    UINT8 data[4] = {dwData.byte.LB, dwData.byte.HB, dwData.byte.UB, dwData.byte.MB};
    HAL_SPI_Transmit(&LAN9252_SPI_HANDLE, data, 4, 10);
}

void SPIReadRegUsingCSR(UINT8 *ReadBuffer, UINT16 Address, UINT8 Count)
{
    UINT32_VAL param32_1 = {0};
    UINT8 i = 0;
    UINT16_VAL wAddr;
    wAddr.Val = Address;
    param32_1.v[0] = wAddr.byte.LB;
    param32_1.v[1] = wAddr.byte.HB;
    param32_1.v[2] = Count;
    param32_1.v[3] = ESC_READ_BYTE;
    SPIWriteDWord(ESC_CSR_CMD_REG, param32_1.Val);
    do
    {
        param32_1.Val = SPIReadDWord(ESC_CSR_CMD_REG);

    } while (param32_1.v[3] & ESC_CSR_BUSY);
    param32_1.Val = SPIReadDWord(ESC_CSR_DATA_REG);
    for (i = 0; i < Count; i++)
        ReadBuffer[i] = param32_1.v[i];
    return;
}

void SPIWriteRegUsingCSR(UINT8 *WriteBuffer, UINT16 Address, UINT8 Count)
{
    UINT32_VAL param32_1 = {0};
    UINT8 i = 0;
    UINT16_VAL wAddr;
    for (i = 0; i < Count; i++)
        param32_1.v[i] = WriteBuffer[i];
    SPIWriteDWord(ESC_CSR_DATA_REG, param32_1.Val);
    wAddr.Val = Address;
    param32_1.v[0] = wAddr.byte.LB;
    param32_1.v[1] = wAddr.byte.HB;
    param32_1.v[2] = Count;
    param32_1.v[3] = ESC_WRITE_BYTE;
    SPIWriteDWord(0x304, param32_1.Val);
    do
    {
        param32_1.Val = SPIReadDWord(0x304);

    } while (param32_1.v[3] & ESC_CSR_BUSY);
    return;
}

void SPIReadPDRamRegister(UINT8 *ReadBuffer, UINT16 Address, UINT16 Count)
{
    UINT32_VAL param32_1 = {0};
    UINT8 i = 0, nlength, nBytePosition;
    UINT8 nReadSpaceAvblCount;
    param32_1.Val = PRAM_RW_ABORT_MASK;
    SPIWriteDWord(PRAM_READ_CMD_REG, param32_1.Val);
    do
    {
        param32_1.Val = SPIReadDWord(PRAM_READ_CMD_REG);

    } while ((param32_1.v[3] & PRAM_RW_BUSY_8B));
    param32_1.w[0] = Address;
    param32_1.w[1] = Count;
    SPIWriteDWord(PRAM_READ_ADDR_LEN_REG, param32_1.Val);
    param32_1.Val = PRAM_RW_BUSY_32B;
    SPIWriteDWord(PRAM_READ_CMD_REG, param32_1.Val);
    do
    {
        param32_1.Val = SPIReadDWord(PRAM_READ_CMD_REG);

    } while (!(param32_1.v[0] & IS_PRAM_SPACE_AVBL_MASK));
    nReadSpaceAvblCount = param32_1.v[1] & PRAM_SPACE_AVBL_COUNT_MASK;
    param32_1.Val = SPIReadDWord(PRAM_READ_FIFO_REG);
    nReadSpaceAvblCount--;
    nBytePosition = (Address & 0x03);
    nlength = (4 - nBytePosition) > Count ? Count : (4 - nBytePosition);
    memcpy(ReadBuffer + i, &param32_1.v[nBytePosition], nlength);
    Count -= nlength;
    i += nlength;
    CSLOW();
    SPIWriteByte(CMD_FAST_READ);
    SPISendAddr(PRAM_READ_FIFO_REG);
    SPIWriteByte(CMD_FAST_READ_DUMMY);
    while (Count)
    {
        param32_1.Val = SPIReadBurstMode();
        nlength = Count > 4 ? 4 : Count;
        memcpy((ReadBuffer + i), &param32_1, nlength);
        i += nlength;
        Count -= nlength;
        nReadSpaceAvblCount--;
    }
    CSHIGH();
    return;
}

void SPIWritePDRamRegister(UINT8 *WriteBuffer, UINT16 Address, UINT16 Count)
{
    UINT32_VAL param32_1 = {0};
    UINT8 i = 0, nlength, nBytePosition, nWrtSpcAvlCount;
    param32_1.Val = PRAM_RW_ABORT_MASK;
    SPIWriteDWord(PRAM_WRITE_CMD_REG, param32_1.Val);
    do
    {
        param32_1.Val = SPIReadDWord(PRAM_WRITE_CMD_REG);

    } while ((param32_1.v[3] & PRAM_RW_BUSY_8B));
    param32_1.w[0] = Address;
    param32_1.w[1] = Count;
    SPIWriteDWord(PRAM_WRITE_ADDR_LEN_REG, param32_1.Val);
    param32_1.Val = PRAM_RW_BUSY_32B;
    SPIWriteDWord(PRAM_WRITE_CMD_REG, param32_1.Val);
    do
    {
        param32_1.Val = SPIReadDWord(PRAM_WRITE_CMD_REG);

    } while (!(param32_1.v[0] & IS_PRAM_SPACE_AVBL_MASK));
    nWrtSpcAvlCount = param32_1.v[1] & PRAM_SPACE_AVBL_COUNT_MASK;
    nBytePosition = (Address & 0x03);
    nlength = (4 - nBytePosition) > Count ? Count : (4 - nBytePosition);
    param32_1.Val = 0;
    memcpy(&param32_1.v[nBytePosition], WriteBuffer + i, nlength);
    SPIWriteDWord(PRAM_WRITE_FIFO_REG, param32_1.Val);
    nWrtSpcAvlCount--;
    Count -= nlength;
    i += nlength;
    CSLOW();
    SPIWriteByte(CMD_SERIAL_WRITE);
    SPISendAddr(PRAM_WRITE_FIFO_REG);
    while (Count)
    {
        nlength = Count > 4 ? 4 : Count;
        param32_1.Val = 0;
        memcpy(&param32_1, (WriteBuffer + i), nlength);
        SPIWriteBurstMode(param32_1.Val);
        i += nlength;
        Count -= nlength;
        nWrtSpcAvlCount--;
    }
    CSHIGH();
    return;
}

void SPIReadDRegister(UINT8 *ReadBuffer, UINT16 Address, UINT16 Count)
{
    if (Address >= 0x1000)
        SPIReadPDRamRegister(ReadBuffer, Address, Count);
    else
        SPIReadRegUsingCSR(ReadBuffer, Address, Count);
}

void SPIWriteRegister(UINT8 *WriteBuffer, UINT16 Address, UINT16 Count)
{
    if (Address >= 0x1000)
        SPIWritePDRamRegister(WriteBuffer, Address, Count);
    else
        SPIWriteRegUsingCSR(WriteBuffer, Address, Count);
}
