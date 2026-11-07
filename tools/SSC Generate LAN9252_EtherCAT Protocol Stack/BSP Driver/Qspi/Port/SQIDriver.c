#include "SQIDriver.h"
#include "STM32_LAN9252_HW.h"

UINT32 SQIReadDWord(UINT16 Address)
{
    OSPI_RegularCmdTypeDef cmd = {
        .OperationType = HAL_OSPI_OPTYPE_COMMON_CFG,
        .FlashId = HAL_OSPI_FLASH_ID_1,
        .Instruction = CMD_QUAD_OP_READ,
        .InstructionMode = HAL_OSPI_INSTRUCTION_1_LINE,
        .InstructionSize = HAL_OSPI_INSTRUCTION_8_BITS,
        .InstructionDtrMode = HAL_OSPI_INSTRUCTION_DTR_DISABLE,
        .Address = Address,
        .AddressMode = HAL_OSPI_ADDRESS_1_LINE,
        .AddressSize = HAL_OSPI_ADDRESS_16_BITS,
        .AddressDtrMode = HAL_OSPI_ADDRESS_DTR_DISABLE,
        .AlternateBytes = 0,
        .AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE,
        .AlternateBytesSize = HAL_OSPI_ALTERNATE_BYTES_8_BITS,
        .AlternateBytesDtrMode = HAL_OSPI_ALTERNATE_BYTES_DTR_DISABLE,
        .DataMode = HAL_OSPI_DATA_4_LINES,
        .NbData = 4,
        .DataDtrMode = HAL_OSPI_DATA_DTR_DISABLE,
        .DummyCycles = 8,
        .DQSMode = HAL_OSPI_DQS_DISABLE,
        .SIOOMode = HAL_OSPI_SIOO_INST_EVERY_CMD,
    };
    HAL_OSPI_Command(&LAN9252_SQI_HANDLE, &cmd, 10);
    UINT32 dwResult;
    HAL_OSPI_Receive(&LAN9252_SQI_HANDLE, (UINT8 *)&dwResult, 10);
    return dwResult;
}

void SQIWriteDWord(UINT16 Address, UINT32 Val)
{
    OSPI_RegularCmdTypeDef cmd = {
        .OperationType = HAL_OSPI_OPTYPE_COMMON_CFG,
        .FlashId = HAL_OSPI_FLASH_ID_1,
        .Instruction = CMD_QUAD_DATA_WRITE,
        .InstructionMode = HAL_OSPI_INSTRUCTION_1_LINE,
        .InstructionSize = HAL_OSPI_INSTRUCTION_8_BITS,
        .InstructionDtrMode = HAL_OSPI_INSTRUCTION_DTR_DISABLE,
        .Address = Address,
        .AddressMode = HAL_OSPI_ADDRESS_1_LINE,
        .AddressSize = HAL_OSPI_ADDRESS_16_BITS,
        .AddressDtrMode = HAL_OSPI_ADDRESS_DTR_DISABLE,
        .AlternateBytes = 0,
        .AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE,
        .AlternateBytesSize = HAL_OSPI_ALTERNATE_BYTES_8_BITS,
        .AlternateBytesDtrMode = HAL_OSPI_ALTERNATE_BYTES_DTR_DISABLE,
        .DataMode = HAL_OSPI_DATA_4_LINES,
        .NbData = 4,
        .DataDtrMode = HAL_OSPI_DATA_DTR_DISABLE,
        .DummyCycles = 0,
        .DQSMode = HAL_OSPI_DQS_DISABLE,
        .SIOOMode = HAL_OSPI_SIOO_INST_EVERY_CMD,
    };
    HAL_OSPI_Command(&LAN9252_SQI_HANDLE, &cmd, 10);
    HAL_OSPI_Transmit(&LAN9252_SQI_HANDLE, (uint8_t *)&Val, 10);
}

void SQIReadRegUsingCSR(UINT8 *ReadBuffer, UINT16 Address, UINT8 Count)
{
    UINT32_VAL param32_1 = {0};
    UINT8 i = 0;
    UINT16_VAL wAddr;
    wAddr.Val = Address;
    param32_1.v[0] = wAddr.byte.LB;
    param32_1.v[1] = wAddr.byte.HB;
    param32_1.v[2] = Count;
    param32_1.v[3] = ESC_READ_BYTE;
    SQIWriteDWord(ESC_CSR_CMD_REG, param32_1.Val);
    do
    {
        param32_1.Val = SQIReadDWord(ESC_CSR_CMD_REG);

    } while (param32_1.v[3] & ESC_CSR_BUSY);
    param32_1.Val = SQIReadDWord(ESC_CSR_DATA_REG);
    for (i = 0; i < Count; i++)
        ReadBuffer[i] = param32_1.v[i];
    return;
}

void SQIWriteRegUsingCSR(UINT8 *WriteBuffer, UINT16 Address, UINT8 Count)
{
    UINT32_VAL param32_1 = {0};
    UINT8 i = 0;
    UINT16_VAL wAddr;
    for (i = 0; i < Count; i++)
        param32_1.v[i] = WriteBuffer[i];
    SQIWriteDWord(ESC_CSR_DATA_REG, param32_1.Val);
    wAddr.Val = Address;
    param32_1.v[0] = wAddr.byte.LB;
    param32_1.v[1] = wAddr.byte.HB;
    param32_1.v[2] = Count;
    param32_1.v[3] = ESC_WRITE_BYTE;
    SQIWriteDWord(ESC_CSR_CMD_REG, param32_1.Val);
    do
    {
        param32_1.Val = SQIReadDWord(ESC_CSR_CMD_REG);

    } while (param32_1.v[3] & ESC_CSR_BUSY);
    return;
}

void SQIReadPDRamRegister(UINT8 *ReadBuffer, UINT16 Address, UINT16 Count)
{
    UINT32_VAL param32_1 = {0};
    UINT8 i = 0, nlength, nBytePosition;
    UINT8 nReadSpaceAvblCount;
    /*Reset/Abort any previous commands.*/
    param32_1.Val = PRAM_RW_ABORT_MASK;
    SQIWriteDWord(PRAM_READ_CMD_REG, param32_1.Val);
    /*The host should not modify this field unless the PRAM Read Busy
    (PRAM_READ_BUSY) bit is a 0.*/
    uint32_t timeout = 0;
    do
    {
        param32_1.Val = SQIReadDWord(PRAM_READ_CMD_REG);
        timeout++;
        if (timeout > 10000)
            return;
    } while ((param32_1.v[3] & PRAM_RW_BUSY_8B));
    /*Write address and length in the EtherCAT Process RAM Read Address and
     * Length Register (ECAT_PRAM_RD_ADDR_LEN)*/
    param32_1.w[0] = Address;
    param32_1.w[1] = Count;
    SQIWriteDWord(PRAM_READ_ADDR_LEN_REG, param32_1.Val);
    /*Set PRAM Read Busy (PRAM_READ_BUSY) bit(-EtherCAT Process RAM Read Command Register)
     *  to start read operatrion*/
    param32_1.Val = PRAM_RW_BUSY_32B; /*TODO:replace with #defines*/
    SQIWriteDWord(PRAM_READ_CMD_REG, param32_1.Val);
    /*Read PRAM Read Data Available (PRAM_READ_AVAIL) bit is set*/
    timeout = 0;
    do
    {
        param32_1.Val = SQIReadDWord(PRAM_READ_CMD_REG);
        timeout++;
        if (timeout > 10000)
            return;
    } while (!(param32_1.v[0] & IS_PRAM_SPACE_AVBL_MASK));
    nReadSpaceAvblCount = param32_1.v[1] & PRAM_SPACE_AVBL_COUNT_MASK;
    /*Fifo registers are aliased address. In indexed it will read indexed data reg 0x04, but it will point to reg 0
     In other modes read 0x04 FIFO register since all registers are aliased*/
    /*get the UINT8 lenth for first read*/
    // Auto increment is supported in SPIO
    param32_1.Val = SQIReadDWord(PRAM_READ_FIFO_REG);
    nReadSpaceAvblCount--;
    nBytePosition = (Address & 0x03);
    nlength = (4 - nBytePosition) > Count ? Count : (4 - nBytePosition);
    memcpy(ReadBuffer + i, &param32_1.v[nBytePosition], nlength);
    Count -= nlength;
    i += nlength;
    // Lets do it in auto increment mode
    if (Count)
    {
        OSPI_RegularCmdTypeDef cmd = {
            .OperationType = HAL_OSPI_OPTYPE_COMMON_CFG,
            .FlashId = HAL_OSPI_FLASH_ID_1,
            .Instruction = CMD_QUAD_OP_READ,
            .InstructionMode = HAL_OSPI_INSTRUCTION_1_LINE,
            .InstructionSize = HAL_OSPI_INSTRUCTION_8_BITS,
            .InstructionDtrMode = HAL_OSPI_INSTRUCTION_DTR_DISABLE,
            .Address = PRAM_READ_FIFO_REG,
            .AddressMode = HAL_OSPI_ADDRESS_1_LINE,
            .AddressSize = HAL_OSPI_ADDRESS_16_BITS,
            .AddressDtrMode = HAL_OSPI_ADDRESS_DTR_DISABLE,
            .AlternateBytes = 0,
            .AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE,
            .AlternateBytesSize = HAL_OSPI_ALTERNATE_BYTES_8_BITS,
            .AlternateBytesDtrMode = HAL_OSPI_ALTERNATE_BYTES_DTR_DISABLE,
            .DataMode = HAL_OSPI_DATA_4_LINES,
            .NbData = Count,
            .DataDtrMode = HAL_OSPI_DATA_DTR_DISABLE,
            .DummyCycles = 8,
            .DQSMode = HAL_OSPI_DQS_DISABLE,
            .SIOOMode = HAL_OSPI_SIOO_INST_EVERY_CMD,
        };
        if (HAL_OSPI_Command(&LAN9252_SQI_HANDLE, &cmd, 10) != HAL_OK)
        {
            Error_Handler();
        }
        HAL_OSPI_Receive(&LAN9252_SQI_HANDLE, ReadBuffer + i, 100);
    }
    return;
}

void SQIWritePDRamRegister(UINT8 *WriteBuffer, UINT16 Address, UINT16 Count)
{
    UINT32_VAL param32_1 = {0};
    UINT8 i = 0, nlength, nBytePosition, nWrtSpcAvlCount;
    /*Reset or Abort any previous commands.*/
    param32_1.Val = PRAM_RW_ABORT_MASK;
    SQIWriteDWord(PRAM_WRITE_CMD_REG, param32_1.Val);
    /*Make sure there is no previous write is pending
    (PRAM Write Busy) bit is a 0 */
    uint32_t timeout = 0;
    do
    {
        param32_1.Val = SQIReadDWord(PRAM_WRITE_CMD_REG);
        timeout++;
        if (timeout > 10000)
            return;
    } while ((param32_1.v[3] & PRAM_RW_BUSY_8B));
    /*Write Address and Length Register (ECAT_PRAM_WR_ADDR_LEN) with the
    starting UINT8 address and length)*/
    param32_1.w[0] = Address;
    param32_1.w[1] = Count;
    SQIWriteDWord(PRAM_WRITE_ADDR_LEN_REG, param32_1.Val);
    /*write to the EtherCAT Process RAM Write Command Register (ECAT_PRAM_WR_CMD) with the  PRAM Write Busy
    (PRAM_WRITE_BUSY) bit set*/
    param32_1.Val = PRAM_RW_BUSY_32B; /*TODO:replace with #defines*/
    SQIWriteDWord(PRAM_WRITE_CMD_REG, param32_1.Val);
    /*Read PRAM write Data Available (PRAM_READ_AVAIL) bit is set*/
    timeout = 0;
    do
    {
        param32_1.Val = SQIReadDWord(PRAM_WRITE_CMD_REG);
        timeout++;
        if (timeout > 10000)
            return;
    } while (!(param32_1.v[0] & IS_PRAM_SPACE_AVBL_MASK));
    /*Check write data available count*/
    nWrtSpcAvlCount = param32_1.v[1] & PRAM_SPACE_AVBL_COUNT_MASK;
    /*Write data to Write FIFO) */
    /*get the byte lenth for first read*/
    nBytePosition = (Address & 0x03);
    nlength = (4 - nBytePosition) > Count ? Count : (4 - nBytePosition);
    param32_1.Val = 0;
    memcpy(&param32_1.v[nBytePosition], WriteBuffer + i, nlength);
    SQIWriteDWord(PRAM_WRITE_FIFO_REG, param32_1.Val);
    nWrtSpcAvlCount--;
    Count -= nlength;
    i += nlength;
    if (Count)
    {
        OSPI_RegularCmdTypeDef cmd = {
            .OperationType = HAL_OSPI_OPTYPE_COMMON_CFG,
            .FlashId = HAL_OSPI_FLASH_ID_1,
            .Instruction = CMD_QUAD_DATA_WRITE,
            .InstructionMode = HAL_OSPI_INSTRUCTION_1_LINE,
            .InstructionSize = HAL_OSPI_INSTRUCTION_8_BITS,
            .InstructionDtrMode = HAL_OSPI_INSTRUCTION_DTR_DISABLE,
            .Address = PRAM_WRITE_FIFO_REG,
            .AddressMode = HAL_OSPI_ADDRESS_1_LINE,
            .AddressSize = HAL_OSPI_ADDRESS_16_BITS,
            .AddressDtrMode = HAL_OSPI_ADDRESS_DTR_DISABLE,
            .AlternateBytes = 0,
            .AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE,
            .AlternateBytesSize = HAL_OSPI_ALTERNATE_BYTES_8_BITS,
            .AlternateBytesDtrMode = HAL_OSPI_ALTERNATE_BYTES_DTR_DISABLE,
            .DataMode = HAL_OSPI_DATA_4_LINES,
            .NbData = Count,
            .DataDtrMode = HAL_OSPI_DATA_DTR_DISABLE,
            .DummyCycles = 0,
            .DQSMode = HAL_OSPI_DQS_DISABLE,
            .SIOOMode = HAL_OSPI_SIOO_INST_EVERY_CMD,
        };
        if (HAL_OSPI_Command(&LAN9252_SQI_HANDLE, &cmd, 10) != HAL_OK)
        {
            Error_Handler();
        }
        HAL_OSPI_Transmit(&LAN9252_SQI_HANDLE, WriteBuffer + i, 100);
    }
    return;
}

void SQIReadDRegister(UINT8 *ReadBuffer, UINT16 Address, UINT16 Count)
{
    if (Address >= 0x1000)
        SQIReadPDRamRegister(ReadBuffer, Address, Count);
    else
        SQIReadRegUsingCSR(ReadBuffer, Address, Count);
}

void SQIWriteRegister(UINT8 *WriteBuffer, UINT16 Address, UINT16 Count)
{
    if (Address >= 0x1000)
        SQIWritePDRamRegister(WriteBuffer, Address, Count);
    else
        SQIWriteRegUsingCSR(WriteBuffer, Address, Count);
}
