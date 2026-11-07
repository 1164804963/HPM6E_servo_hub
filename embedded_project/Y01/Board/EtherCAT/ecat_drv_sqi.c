#include "ecat_drv_sqi.h"

UINT32 SQIReadDWord(UINT16 Address)
{
    uint32_t rt_qspi = 0;

    QSPI_CommandTypeDef qspi_cmd;

    qspi_cmd.Instruction = CMD_QUAD_IO_READ;//CMD_QUAD_OP_READ;
    qspi_cmd.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    qspi_cmd.AddressMode = QSPI_ADDRESS_4_LINES;//QSPI_ADDRESS_1_LINE;
    qspi_cmd.Address = Address;
    qspi_cmd.AddressSize = QSPI_ADDRESS_16_BITS;
    qspi_cmd.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    qspi_cmd.DataMode = QSPI_DATA_4_LINES;
    qspi_cmd.NbData = 4;
    qspi_cmd.DummyCycles = 8;
    qspi_cmd.DdrMode = QSPI_DDR_MODE_DISABLE;
    qspi_cmd.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    qspi_cmd.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

    HAL_QSPI_Command(&LAN9252_SQI_HANDLE, &qspi_cmd, 1000);
    HAL_QSPI_Receive(&LAN9252_SQI_HANDLE, (uint8_t *)&rt_qspi, 1000);

    return rt_qspi;
}

void SQIWriteDWord(UINT16 Address, UINT32 Val)
{
    QSPI_CommandTypeDef qspi_cmd;

    qspi_cmd.Instruction = CMD_QUAD_ADDR_DARA_WRITE;//CMD_QUAD_DATA_WRITE;
    qspi_cmd.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    qspi_cmd.AddressMode = QSPI_ADDRESS_4_LINES;//QSPI_ADDRESS_1_LINE;
    qspi_cmd.Address = Address;
    qspi_cmd.AddressSize = QSPI_ADDRESS_16_BITS;
    qspi_cmd.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    qspi_cmd.DataMode = QSPI_DATA_4_LINES;
    qspi_cmd.NbData = 4;
    qspi_cmd.DummyCycles = 0;
    qspi_cmd.DdrMode = QSPI_DDR_MODE_DISABLE;
    qspi_cmd.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    qspi_cmd.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

    HAL_QSPI_Command(&LAN9252_SQI_HANDLE, &qspi_cmd, 1000);
    HAL_QSPI_Transmit(&LAN9252_SQI_HANDLE, (uint8_t *)&Val, 1000);
}

void SQIReadPDRamRegister(UINT8 *ReadBuffer, UINT16 Address, UINT16 Count)
{
    UINT32_VAL param32_1 = {0};
    UINT8 i = 0, nlength, nUINT8Position;

    /*Reset/Abort any previous commands.*/
    param32_1.Val = 0x40000000; /*TODO:replace with #defines*/

    SQIWriteDWord(0x30c, param32_1.Val);

    /*The host should not modify this field unless the PRAM Read Busy
    (PRAM_READ_BUSY) bit is a 0.*/
    do
    {
        param32_1.Val = SQIReadDWord(0x30C);

    } while ((param32_1.v[3] & 0x80));

    /*Write address and length in the EtherCAT Process RAM Read Address and
     * Length Register (ECAT_PRAM_RD_ADDR_LEN)*/
    param32_1.w[0] = Address;
    param32_1.w[1] = Count;

    SQIWriteDWord(0x308, param32_1.Val);

    param32_1.Val = SQIReadDWord(0x14);
    /*Set PRAM Read Busy (PRAM_READ_BUSY) bit(-EtherCAT Process RAM Read Command Register)
     *  to start read operatrion*/

    param32_1.Val = 0x80000000; /*TODO:replace with #defines*/

    SQIWriteDWord(0x30c, param32_1.Val);

    /*Read PRAM Read Data Available (PRAM_READ_AVAIL) bit is set*/
    do
    {
        param32_1.Val = SQIReadDWord(0x30C);

    } while (!(param32_1.v[0] & 0x01));

    /*Fifo registers are aliased address. In indexed it will read indexed data reg 0x04, but it will point to reg 0
     In other modes read 0x04 FIFO register since all registers are aliased*/

    /*get the UINT8 lenth for first read*/
    param32_1.Val = SQIReadDWord(4);
    nUINT8Position = (Address & 0x03);
    nlength = (4 - nUINT8Position) > Count ? Count : (4 - nUINT8Position);
    memcpy(ReadBuffer, &param32_1.v[nUINT8Position], nlength);
    Count -= nlength;
    i = nlength;

    while (Count)
    {
        param32_1.Val = SQIReadDWord(4);

        nlength = Count > 4 ? 4 : Count;
        memcpy((ReadBuffer + i), &param32_1, nlength);

        i += nlength;
        Count -= nlength;
    }

    return;
}

void SQIWritePDRamRegister(UINT8 *WriteBuffer, UINT16 Address, UINT16 Count)
{
    UINT32_VAL param32_1 = {0};
    UINT8 i = 0, nlength, nUINT8Position, nWrtSpcAvlCount, test;

    /*Reset or Abort any previous commands.*/
    param32_1.Val = 0x40000000; /*TODO:replace with #defines*/

    SQIWriteDWord(0x314, param32_1.Val);

    /*Make sure there is no previous write is pending
    (PRAM Write Busy) bit is a 0 */
    do
    {
        param32_1.Val = SQIReadDWord(0x314);

    } while ((param32_1.v[3] & 0x80));

    /*Write Address and Length Register (ECAT_PRAM_WR_ADDR_LEN) with the
    starting UINT8 address and length)*/
    param32_1.w[0] = Address;
    param32_1.w[1] = Count;

    SQIWriteDWord(0x310, param32_1.Val);

    /*write to the EtherCAT Process RAM Write Command Register (ECAT_PRAM_WR_CMD) with the  PRAM Write Busy
    (PRAM_WRITE_BUSY) bit set*/

    param32_1.Val = 0x80000000; /*TODO:replace with #defines*/

    SQIWriteDWord(0x314, param32_1.Val);

    /*Read PRAM write Data Available (PRAM_READ_AVAIL) bit is set*/
    do
    {
        param32_1.Val = SQIReadDWord(0x314);

    } while (!(param32_1.v[0] & 0x01));

    /*Check write data available count*/
    nWrtSpcAvlCount = param32_1.v[1];

    /*Write data to Write FIFO) */
    /*get the UINT8 lenth for first read*/
    nUINT8Position = (Address & 0x03);

    nlength = (4 - nUINT8Position) > Count ? Count : (4 - nUINT8Position);

    param32_1.Val = 0;
    memcpy(&param32_1.v[nUINT8Position], WriteBuffer, nlength);

    SQIWriteDWord(0x20, param32_1.Val);

    Count -= nlength;
    i = nlength;
    nWrtSpcAvlCount--;

    while (Count)
    {

        nlength = Count > 4 ? 4 : Count;
        memcpy(&param32_1, (WriteBuffer + i), nlength);

        SQIWriteDWord(0x20, param32_1.Val);

        i += nlength;
        Count -= nlength;
        nWrtSpcAvlCount--;
    }

    return;
}

void SQIReadDRegister(UINT8 *ReadBuffer, UINT16 Address, UINT16 Count)
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

void SQIWriteRegister(UINT8 *WriteBuffer, UINT16 Address, UINT16 Count)
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

    SQIWriteDWord(0x304, param32_1.Val);
    do
    {
        param32_1.Val = SQIReadDWord(0x304);

    } while (param32_1.v[3] & ESC_CSR_BUSY);

    return;
}
