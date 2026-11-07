/*
* This source file is part of the EtherCAT Slave Stack Code licensed by Beckhoff Automation GmbH & Co KG, 33415 Verl, Germany.
* The corresponding license agreement applies. This hint shall not be removed.
*/

/**
\addtogroup ecat_app ecat_app
@{
*/

/**
\file ecat_app.c
\brief Implementation
 Created with SSC Tool application parser 1.6.4.0
\version 0.0.0.1
*/


/*-----------------------------------------------------------------------------------------
------
------    Includes
------
-----------------------------------------------------------------------------------------*/
#include "ecat_def.h"

#include "applInterface.h"

#define _ECAT_APP_ 1
#include "ecat_app.h"
#undef _ECAT_APP_
/*--------------------------------------------------------------------------------------
------
------    local types and defines
------
--------------------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */
/**
 * APPL_GenerateMapping记录TPDO和RPDO基础信息
 * APPL_InputMapping中执行TPDO回调
 * APPL_OutputMapping中执行RPDO回调
 */
#define PDO_MAP_NUM 4
#define PDO_SUB_MAX 32
typedef struct
{
    UINT16 index;
    UINT8 subindex;
    UINT8 size;
    UINT8 (*HandleCallback)(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
    UINT32 u32_buff;
}PdoCallbackStruct;

PdoCallbackStruct RxPdoList[PDO_MAP_NUM][PDO_SUB_MAX];
PdoCallbackStruct TxPdoList[PDO_MAP_NUM][PDO_SUB_MAX];
/* USER CODE END 1 */
/*-----------------------------------------------------------------------------------------
------
------    local variables and constants
------
-----------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------
------
------    application specific functions
------
-----------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------
------
------    generic functions
------
-----------------------------------------------------------------------------------------*/

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \brief    The function is called when an error state was acknowledged by the master

*////////////////////////////////////////////////////////////////////////////////////////

void    APPL_AckErrorInd(UINT16 stateTrans)
{

}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \return    AL Status Code (see ecatslv.h ALSTATUSCODE_....)

 \brief    The function is called in the state transition from INIT to PREOP when
             all general settings were checked to start the mailbox handler. This function
             informs the application about the state transition, the application can refuse
             the state transition when returning an AL Status error code.
            The return code NOERROR_INWORK can be used, if the application cannot confirm
            the state transition immediately, in that case this function will be called cyclically
            until a value unequal NOERROR_INWORK is returned

*////////////////////////////////////////////////////////////////////////////////////////

UINT16 APPL_StartMailboxHandler(void)
{
    return ALSTATUSCODE_NOERROR;
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \return     0, NOERROR_INWORK

 \brief    The function is called in the state transition from PREEOP to INIT
             to stop the mailbox handler. This functions informs the application
             about the state transition, the application cannot refuse
             the state transition.

*////////////////////////////////////////////////////////////////////////////////////////

UINT16 APPL_StopMailboxHandler(void)
{
    return ALSTATUSCODE_NOERROR;
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \param    pIntMask    pointer to the AL Event Mask which will be written to the AL event Mask
                       register (0x204) when this function is succeeded. The event mask can be adapted
                       in this function
 \return    AL Status Code (see ecatslv.h ALSTATUSCODE_....)

 \brief    The function is called in the state transition from PREOP to SAFEOP when
           all general settings were checked to start the input handler. This function
           informs the application about the state transition, the application can refuse
           the state transition when returning an AL Status error code.
           The return code NOERROR_INWORK can be used, if the application cannot confirm
           the state transition immediately, in that case the application need to be complete 
           the transition by calling ECAT_StateChange.
*////////////////////////////////////////////////////////////////////////////////////////

UINT16 APPL_StartInputHandler(UINT16 *pIntMask)
{
    return ALSTATUSCODE_NOERROR;
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \return     0, NOERROR_INWORK

 \brief    The function is called in the state transition from SAFEOP to PREEOP
             to stop the input handler. This functions informs the application
             about the state transition, the application cannot refuse
             the state transition.

*////////////////////////////////////////////////////////////////////////////////////////

UINT16 APPL_StopInputHandler(void)
{
    return ALSTATUSCODE_NOERROR;
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \return    AL Status Code (see ecatslv.h ALSTATUSCODE_....)

 \brief    The function is called in the state transition from SAFEOP to OP when
             all general settings were checked to start the output handler. This function
             informs the application about the state transition, the application can refuse
             the state transition when returning an AL Status error code.
           The return code NOERROR_INWORK can be used, if the application cannot confirm
           the state transition immediately, in that case the application need to be complete 
           the transition by calling ECAT_StateChange.
*////////////////////////////////////////////////////////////////////////////////////////

UINT16 APPL_StartOutputHandler(void)
{
    return ALSTATUSCODE_NOERROR;
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \return     0, NOERROR_INWORK

 \brief    The function is called in the state transition from OP to SAFEOP
             to stop the output handler. This functions informs the application
             about the state transition, the application cannot refuse
             the state transition.

*////////////////////////////////////////////////////////////////////////////////////////

UINT16 APPL_StopOutputHandler(void)
{
    return ALSTATUSCODE_NOERROR;
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
\return     0(ALSTATUSCODE_NOERROR), NOERROR_INWORK
\param      pInputSize  pointer to save the input process data length
\param      pOutputSize  pointer to save the output process data length

\brief    This function calculates the process data sizes from the actual SM-PDO-Assign
            and PDO mapping
*////////////////////////////////////////////////////////////////////////////////////////
UINT16 APPL_GenerateMapping(UINT16 *pInputSize,UINT16 *pOutputSize)
{
    UINT16 result = ALSTATUSCODE_NOERROR;
    UINT16 InputSize = 0;
    UINT16 OutputSize = 0;

#if COE_SUPPORTED
    UINT16 PDOAssignEntryCnt = 0;
    OBJCONST TOBJECT OBJMEM * pPDO = NULL;
    UINT16 PDOSubindex0 = 0;
    UINT32 *pPDOEntry = NULL;
    UINT16 PDOEntryCnt = 0;

    UINT32 value = 0;
    OBJCONST TOBJECT OBJMEM* pRxPDO = NULL;
    OBJCONST TOBJECT OBJMEM* pTxPDO = NULL;
#if MAX_PD_OUTPUT_SIZE > 0
    /*Scan object 0x1C12 RXPDO assign*/
    for(PDOAssignEntryCnt = 0; PDOAssignEntryCnt < sRxPDOassign.u16SubIndex0; PDOAssignEntryCnt++)
    {
        pPDO = OBJ_GetObjectHandle(sRxPDOassign.aEntries[PDOAssignEntryCnt]);
        if(pPDO != NULL)
        {
            PDOSubindex0 = *((UINT16 *)pPDO->pVarPtr);
            for(PDOEntryCnt = 0; PDOEntryCnt < PDOSubindex0; PDOEntryCnt++)
            {
                pPDOEntry = (UINT32 *)(((UINT16 *)pPDO->pVarPtr) + (OBJ_GetEntryOffset((PDOEntryCnt+1),pPDO)>>4));    //goto PDO entry
                // we increment the expected output size depending on the mapped Entry
                OutputSize += (UINT16) ((*pPDOEntry) & 0xFF);
                /* USER CODE BEGIN 2 */
                value = *pPDOEntry;
                RxPdoList[PDOAssignEntryCnt][PDOEntryCnt].index = value >> 16;
                RxPdoList[PDOAssignEntryCnt][PDOEntryCnt].subindex = (value & 0xFF00) >> 8;
                RxPdoList[PDOAssignEntryCnt][PDOEntryCnt].size = (value & 0xFF) >> 3;
                pRxPDO = OBJ_GetObjectHandle(value >> 16);
                if((0 == pRxPDO)||(NULL == pRxPDO))
                {
                    RxPdoList[PDOAssignEntryCnt][PDOEntryCnt].HandleCallback = NULL;
                }
                else
                {
                    RxPdoList[PDOAssignEntryCnt][PDOEntryCnt].HandleCallback = pRxPDO->Write;
                }
                /* USER CODE END 2 */
            }
        }
        else
        {
            /*assigned PDO was not found in object dictionary. return invalid mapping*/
            OutputSize = 0;
            result = ALSTATUSCODE_INVALIDOUTPUTMAPPING;
            break;
        }
    }

    OutputSize = (OutputSize + 7) >> 3;
#endif

#if MAX_PD_INPUT_SIZE > 0
    if(result == 0)
    {
        /*Scan Object 0x1C13 TXPDO assign*/
        for(PDOAssignEntryCnt = 0; PDOAssignEntryCnt < sTxPDOassign.u16SubIndex0; PDOAssignEntryCnt++)
        {
            pPDO = OBJ_GetObjectHandle(sTxPDOassign.aEntries[PDOAssignEntryCnt]);
            if(pPDO != NULL)
            {
                PDOSubindex0 = *((UINT16 *)pPDO->pVarPtr);
                for(PDOEntryCnt = 0; PDOEntryCnt < PDOSubindex0; PDOEntryCnt++)
                {
                    pPDOEntry = (UINT32 *)(((UINT16 *)pPDO->pVarPtr) + (OBJ_GetEntryOffset((PDOEntryCnt+1),pPDO)>>4));    //goto PDO entry
                    // we increment the expected output size depending on the mapped Entry
                    InputSize += (UINT16) ((*pPDOEntry) & 0xFF);
                    /* USER CODE BEGIN 3 */
                    value = *pPDOEntry;
                    TxPdoList[PDOAssignEntryCnt][PDOEntryCnt].index = value >> 16;
                    TxPdoList[PDOAssignEntryCnt][PDOEntryCnt].subindex = (value & 0xFF00) >> 8;
                    TxPdoList[PDOAssignEntryCnt][PDOEntryCnt].size = (value & 0xFF) >> 3;
                    pTxPDO = OBJ_GetObjectHandle(value >> 16);
                    if((0 == pTxPDO)||(NULL == pTxPDO))
                    {
                        TxPdoList[PDOAssignEntryCnt][PDOEntryCnt].HandleCallback = NULL;
                    }
                    else
                    {
                        TxPdoList[PDOAssignEntryCnt][PDOEntryCnt].HandleCallback = pTxPDO->Read;
                    }
                    /* USER CODE END 3 */
                }
            }
            else
            {
                /*assigned PDO was not found in object dictionary. return invalid mapping*/
                InputSize = 0;
                result = ALSTATUSCODE_INVALIDINPUTMAPPING;
                break;
            }
        }
    }
    InputSize = (InputSize + 7) >> 3;
#endif

#else
#if _WIN32
   #pragma message ("Warning: Define 'InputSize' and 'OutputSize'.")
#else
    #warning "Define 'InputSize' and 'OutputSize'."
#endif
#endif

    *pInputSize = InputSize;
    *pOutputSize = OutputSize;
    return result;
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
\param      pData  pointer to input process data

\brief      This function will copies the inputs from the local memory to the ESC memory
            to the hardware
*////////////////////////////////////////////////////////////////////////////////////////
void APPL_InputMapping(UINT16* pData)
{
    UINT8 *pDataTemp = (UINT8 *)pData;
    UINT32 value = 0;
    UINT16 PDOAssignEntryCnt = 0;
    UINT16 PDOSubindex0 = 0;

    for (PDOAssignEntryCnt = 0; PDOAssignEntryCnt < sTxPDOassign.u16SubIndex0; PDOAssignEntryCnt++)
    {
        uint8_t pdo_order = sTxPDOassign.aEntries[PDOAssignEntryCnt] & 0x000F;
        switch (pdo_order)
        {
        case 0:
            PDOSubindex0 = Obj0x1A00.u16SubIndex0;
            break;
        case 1:
            PDOSubindex0 = Obj0x1A01.u16SubIndex0;
            break;
        case 2:
            PDOSubindex0 = Obj0x1A02.u16SubIndex0;
            break;
        case 3:
            PDOSubindex0 = Obj0x1A03.u16SubIndex0;
            break;
        }
        for (uint8_t i = 0; i < PDOSubindex0; i++)
        {
            value = 0;
            if (NULL != TxPdoList[PDOAssignEntryCnt][i].HandleCallback)
            {
                TxPdoList[PDOAssignEntryCnt][i].HandleCallback(0, TxPdoList[PDOAssignEntryCnt][i].subindex, 0, (UINT16*)&value, 0);
            }
            switch (TxPdoList[PDOAssignEntryCnt][i].size)
            {
            case 1:
                *pDataTemp = value & 0xFF;
                pDataTemp++;
                break;
            case 2:
                *pDataTemp = value & 0xFF;
                pDataTemp++;
                *pDataTemp = (value >> 8) & 0xFF;
                pDataTemp++;
                break;
            case 4:
                *pDataTemp = value & 0xFF;
                pDataTemp++;
                *pDataTemp = (value >> 8) & 0xFF;
                pDataTemp++;
                *pDataTemp = (value >> 16) & 0xFF;
                pDataTemp++;
                *pDataTemp = (value >> 24) & 0xFF;
                pDataTemp++;
                break;
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
\param      pData  pointer to output process data

\brief    This function will copies the outputs from the ESC memory to the local memory
            to the hardware
*////////////////////////////////////////////////////////////////////////////////////////
void APPL_OutputMapping(UINT16* pData)
{
    UINT8* pDataTemp = (UINT8*)pData;
    UINT32 value = 0;
    UINT16 PDOAssignEntryCnt = 0;
    UINT16 PDOSubindex0 = 0;

    for (PDOAssignEntryCnt = 0; PDOAssignEntryCnt < sRxPDOassign.u16SubIndex0; PDOAssignEntryCnt++)
    {
        uint8_t pdo_order = sRxPDOassign.aEntries[PDOAssignEntryCnt] & 0x000F;
        switch (pdo_order)
        {
        case 0:
            PDOSubindex0 = Obj0x1600.u16SubIndex0;
            break;
        case 1:
            PDOSubindex0 = Obj0x1601.u16SubIndex0;
            break;
        case 2:
            PDOSubindex0 = Obj0x1602.u16SubIndex0;
            break;
        case 3:
            PDOSubindex0 = Obj0x1603.u16SubIndex0;
            break;
        }
        for (uint8_t i = 0; i < PDOSubindex0; i++)
        {
            value = 0;
            switch (RxPdoList[PDOAssignEntryCnt][i].size)
            {
            case 1:
                value = *pDataTemp;
                pDataTemp++;
                break;
            case 2:
                value = *pDataTemp;
                pDataTemp++;
                value += ((*pDataTemp) << 8);
                pDataTemp++;
                break;
            case 4:
                value = *pDataTemp;
                pDataTemp++;
                value += ((*pDataTemp) << 8);
                pDataTemp++;
                value += ((*pDataTemp) << 16);
                pDataTemp++;
                value += ((*pDataTemp) << 24);
                pDataTemp++;
                break;
            }
            if (NULL != RxPdoList[PDOAssignEntryCnt][i].HandleCallback)
            {
                // if (!(bDcSyncActive && bDcRunning))
                // {
                    RxPdoList[PDOAssignEntryCnt][i].HandleCallback(0, RxPdoList[PDOAssignEntryCnt][i].subindex, 0, (UINT16*)&value, 0);
                // }
                RxPdoList[PDOAssignEntryCnt][i].u32_buff = value;
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
\brief    This function will called from the synchronisation ISR 
            or from the mainloop if no synchronisation is supported
*////////////////////////////////////////////////////////////////////////////////////////
void APPL_Application(void)
{
    uint16_t subindex_count = 0;

    for (uint8_t i = 0; i < sRxPDOassign.u16SubIndex0; i++)
    {
        switch ((sRxPDOassign.aEntries[i] & 0x000F))
        {
        case 0:
            subindex_count = Obj0x1600.u16SubIndex0;
            break;
        case 1:
            subindex_count = Obj0x1601.u16SubIndex0;
            break;
        case 2:
            subindex_count = Obj0x1602.u16SubIndex0;
            break;
        case 3:
            subindex_count = Obj0x1603.u16SubIndex0;
            break;
        default:
            subindex_count = 0;
            break;
        }

        for (int j = 0; j < subindex_count; j++)
        {
            if (RxPdoList[i][j].HandleCallback != NULL)
            {
                RxPdoList[i][j].HandleCallback(0, RxPdoList[i][j].subindex, 0, (UINT16*)&(RxPdoList[i][j].u32_buff), 0);
            }
        }
    }
}

#if EXPLICIT_DEVICE_ID
/////////////////////////////////////////////////////////////////////////////////////////
/**
 \return    The Explicit Device ID of the EtherCAT slave

 \brief     Read the Explicit Device ID (from an external ID switch)
*////////////////////////////////////////////////////////////////////////////////////////
UINT16 APPL_GetDeviceID()
{
#if _WIN32
   #pragma message ("Warning: Implement explicit Device ID latching")
#else
    #warning "Implement explicit Device ID latching"
#endif
    /* Explicit Device 5 is expected by Explicit Device ID conformance tests*/
    return 0x5;
}
#endif

#if USE_DEFAULT_MAIN
/////////////////////////////////////////////////////////////////////////////////////////
/**

 \brief    This is the main function

*////////////////////////////////////////////////////////////////////////////////////////
#if _PIC24 && EL9800_HW
int main(void)
#elif _WIN32
int main(int argc, char* argv[])
#else
void ecat_main(void)
#endif
{
    /* initialize the Hardware and the EtherCAT Slave Controller */
#if FC1100_HW
#if _WIN32
    u16FcInstance = 0;
    if (argc > 1)
    {
        u16FcInstance = atoi(argv[1]);
    }
#endif
    if(HW_Init())
    {
        HW_Release();
        return;
    }
#else
    HW_Init();
#endif
    MainInit();

    bRunApplication = TRUE;
    do
    {
        MainLoop();
        
    } while (bRunApplication == TRUE);

    HW_Release();
#if _PIC24
    return 0;
#endif
}
#endif //#if USE_DEFAULT_MAIN
/** @} */

