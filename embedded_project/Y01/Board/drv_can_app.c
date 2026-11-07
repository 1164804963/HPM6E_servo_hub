#include "drv_can_app.h"

#ifdef USE_CAN
#include "bsp_fdcan.h"

#if defined (USE_CANOPEN)
#include "SlaveOD.h"
#define CANOPEN_MSG_QUEUE_SIZE      8
typedef struct
{
    TIMEVAL elapsed_time;
    TIMEVAL last_counter_val;
    // 发送失败，待发送消息缓存队列
    uint8_t msg_pending_head;
    uint8_t msg_pending_tail;
    Message msg_pending_fifo[CANOPEN_MSG_QUEUE_SIZE];
} FDCAN_CanopenTypeDef;
static inline void fdcan_canopen_init(FDCAN_DeviceTypeDef* bsp_fdcan);
static inline void fdcan_canopen_hendle(FDCAN_DeviceTypeDef* bsp_fdcan);
#elif defined (USE_ENCOS)
static inline void fdcan_encos_handle(FDCAN_DeviceTypeDef* bsp_fdcan);
#elif defined (USE_CUSTOM)
static inline void fdcan_custom_handle(FDCAN_DeviceTypeDef* bsp_fdcan);
#else // CAN + CiA402
static inline void fdcan_cia402_handle(FDCAN_DeviceTypeDef* bsp_fdcan);
#endif

#if IS_USE_CAN_PASSTHROUGH == FC_CTRL_ON
static inline void fdcan_passthrough_handle(FDCAN_DeviceTypeDef* bsp_fdcan);
#endif // IS_USE_CAN_PASSTHROUGH

typedef struct
{
    FDCAN_DeviceTypeDef* p_fdcan;
    // CANopen data start
#ifdef USE_CANOPEN
    FDCAN_CanopenTypeDef canopen;
#endif
    // CANopen data end

    // ... User defined data of the application
} FDCAN_AppTypeDef;

static FDCAN_AppTypeDef drv_can_app =
{
    .p_fdcan = NULL,
    // CANopen data start
#ifdef USE_CANOPEN
    .canopen = {0, 0, 0, 0, {0}},
#endif
    // CANopen data end

    // ... Init user defined data of the application
};


void fdcan_app_init(void)
{
    drv_can_app.p_fdcan = bsp_fdcan_get_fdcan_handle();
#ifdef USE_CANOPEN
    fdcan_canopen_init(drv_can_app.p_fdcan);
#endif
}

void fdcan_app_fifo0_handle(FDCAN_HandleTypeDef* hfdcan)
{
    // Check if FDCAN handle is valid
    if (drv_can_app.p_fdcan == NULL || drv_can_app.p_fdcan->handle != hfdcan)
    {
        sys_set_bsp_error_state(ERROR_COMMS_INIT, ERROR_SET);
        return;
    }

    // Get message from RX FIFO
    if (HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO0, &drv_can_app.p_fdcan->rx_header, \
                               drv_can_app.p_fdcan->rx_data) != HAL_OK)
    {
        //Error_Handler();
        return;
    }
    #if defined (USE_CANOPEN)
        fdcan_canopen_hendle(drv_can_app.p_fdcan);
    #elif defined (USE_ENCOS)
        fdcan_encos_handle(drv_can_app.p_fdcan);
    #elif defined (USE_CUSTOM)
        fdcan_custom_handle(drv_can_app.p_fdcan);
    #else // CAN + CiA402
        fdcan_cia402_handle(drv_can_app.p_fdcan);
    #endif
}

void fdcan_app_fifo1_handle(FDCAN_HandleTypeDef* hfdcan)
{
    // Check if FDCAN handle is valid
    if (drv_can_app.p_fdcan == NULL || drv_can_app.p_fdcan->handle != hfdcan)
    {
        sys_set_bsp_error_state(ERROR_COMMS_INIT, ERROR_SET);
        return;
    }

    // Get message from RX FIFO
    if (HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO1, &drv_can_app.p_fdcan->rx_header, \
                               drv_can_app.p_fdcan->rx_data) != HAL_OK)
    {
        //Error_Handler();
        return;
    }
    #if IS_USE_CAN_PASSTHROUGH == FC_CTRL_ON
        fdcan_passthrough_handle(drv_can_app.p_fdcan);
    #endif // IS_USE_CAN_PASSTHROUGH
}

#ifdef USE_CANOPEN
/**
 * @brief 初始化CANopen协议栈
 * @param bsp_fdcan Pointer to FDCAN BSP structure
 * @return None
 */
static inline void fdcan_canopen_init(FDCAN_DeviceTypeDef* bsp_fdcan)
{
    if (bsp_fdcan == NULL)
    {
        return;
    }
    HAL_TIM_Base_Start_IT(&CANOPEN_TIM_HANDLE);
    setNodeId(&SlaveOD_Data, bsp_fdcan->id);
    setState(&SlaveOD_Data, Initialisation);
    setState(&SlaveOD_Data, Operational);
}

/**
 * @brief 设置下一个定时器值
 * @param value 下一个定时器值
 */
void setTimer(TIMEVAL value)
{
    TIMEVAL timer = __HAL_TIM_GetCounter(&CANOPEN_TIM_HANDLE);

    drv_can_app.canopen.elapsed_time += timer - drv_can_app.canopen.last_counter_val;
    drv_can_app.canopen.last_counter_val = CANOPEN_TIM_ARR - value;
    __HAL_TIM_SetCounter(&CANOPEN_TIM_HANDLE, CANOPEN_TIM_ARR - value);
    HAL_TIM_Base_Start_IT(&CANOPEN_TIM_HANDLE);
}

/**
 * @brief 获取已过去的时间
 * @return 已过去的时间
 */
TIMEVAL getElapsedTime(void)
{
    TIMEVAL timer = __HAL_TIM_GetCounter(&CANOPEN_TIM_HANDLE);

    if (timer < drv_can_app.canopen.last_counter_val)
    {
        timer += CANOPEN_TIM_ARR;
    }

    return drv_can_app.canopen.elapsed_time + (timer - drv_can_app.canopen.last_counter_val);
}

/**
 * @brief CANopen协议定时器调度任务
 * @param None
 * @return None
 */
void CANopen_DispatchFromISR(void)
{
    // 若已外部判断清除中断标志位，无需重复清除
    drv_can_app.canopen.last_counter_val = 0;
    drv_can_app.canopen.elapsed_time = 0;
    TimeDispatch();
}

/**
 * @brief 发送CANopen消息
 * @param notused 未使用参数
 * @param message Pointer to Message structure
 * @return 发送状态（1成功，0失败）
 */
uint8_t canSend(CAN_PORT notused, Message *message)
{
    if (message == NULL)
    {
        return 0; // failed
    }

    if (HAL_OK != bsp_can_send_message(drv_can_app.p_fdcan, message->cob_id, false, \
                                       (bool)message->rtr, message->data, message->len))
    {
        // 若发送失败，缓存消息，可在定时器中断中尝试重新发送（按需求实现）
        if (((drv_can_app.canopen.msg_pending_tail + 1) % CANOPEN_MSG_QUEUE_SIZE) != \
            drv_can_app.canopen.msg_pending_head)
        {
            drv_can_app.canopen.msg_pending_fifo[drv_can_app.canopen.msg_pending_tail] = *message;
            drv_can_app.canopen.msg_pending_tail = (drv_can_app.canopen.msg_pending_tail + 1) % CANOPEN_MSG_QUEUE_SIZE;
        }
        else
        {
            // 队列已满，无法入队，报错CAN通讯错误
        }
        return 0; // failed to send message
    }

    return 1; //success
}

/**
 * @brief CAN + CANopen协议处理
 * @param hfdcan Pointer to FDCAN handle
 * @param bsp_fdcan Pointer to FDCAN BSP structure
 * @return None
 */
static inline void fdcan_canopen_hendle(FDCAN_DeviceTypeDef* bsp_fdcan)
{
    // Initialize receive message structure
    Message rx_message = {0};

    // Convert FDCAN header to CANopen message format
    rx_message.cob_id = bsp_fdcan->rx_header.Identifier;
    rx_message.rtr = (bsp_fdcan->rx_header.RxFrameType == FDCAN_DATA_FRAME) ? 0 : 1;
    rx_message.len = bsp_fdcan->rx_header.DataLength;

    // Copy message data
    memcpy(rx_message.data, bsp_fdcan->rx_data, rx_message.len);

    // Dispatch message to object dictionary
    canDispatch(&SlaveOD_Data, &rx_message);

    // 判断是否为同步消息，若节点状态为Operational，认为是同步启动更新目标状态值
    if (rx_message.cob_id == 0x080 && SlaveOD_Data.nodeState == Operational)
    {
        set_app_Target_update_state(true);
    }

    // Re-enable RX FIFO0 notification
    HAL_FDCAN_ActivateNotification(bsp_fdcan->handle, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0);
}
#endif // USE_CANOPEN

#ifdef USE_ENCOS
/**
 * @brief CAN + ENCOS协议处理
 * @param hfdcan Pointer to FDCAN handle
 * @param bsp_fdcan Pointer to FDCAN BSP structure
 * @return None
 */
static inline void fdcan_encos_handle(FDCAN_DeviceTypeDef* bsp_fdcan)
{
    return; // TODO
}
#endif // USE_ENCOS

#ifdef USE_CIA402
/**
 * @brief CAN + CIA402协议处理
 * @param hfdcan Pointer to FDCAN handle
 * @param FDCAN_DeviceTypeDef Pointer to FDCAN BSP structure
 * @return None
 */
static inline void fdcan_cia402_handle(FDCAN_DeviceTypeDef* bsp_fdcan)
{
    // Check if message is for this device
    if (bsp_fdcan->rx_header.Identifier != bsp_fdcan->id)
    {
        return;
    }

    // Update message counter (ensure non-zero)
    bsp_fdcan->mg_counts = (bsp_fdcan->mg_counts == 0) ? 1 : bsp_fdcan->mg_counts + 1;

    // Validate minimum data length
    if (bsp_fdcan->rx_header.DataLength < 5)
    {
        return;
    }

    // Parse message header
    uint8_t is_write = bsp_fdcan->rx_data[0];
    uint16_t obj_index = bsp_fdcan->rx_data[1] | (bsp_fdcan->rx_data[2] << 8);
    uint8_t obj_subindex = bsp_fdcan->rx_data[3];
    uint32_t obj_data = 0;

    // Extract data based on length
    const uint8_t data_length = bsp_fdcan->rx_header.DataLength - 4;
    switch (data_length)
    {
        case 1: // 1 byte data
            obj_data = bsp_fdcan->rx_data[4];
            break;
        case 2: // 2 bytes data
            obj_data = bsp_fdcan->rx_data[4] | (bsp_fdcan->rx_data[5] << 8);
            break;
        case 4: // 4 bytes data
            obj_data = bsp_fdcan->rx_data[4] | (bsp_fdcan->rx_data[5] << 8) |
                      (bsp_fdcan->rx_data[6] << 16) | (bsp_fdcan->rx_data[7] << 24);
            break;
        default: // Unsupported length
            return;
    }

    // Process read/write request
    extern uint32_t master_cia402_read_callback(uint16_t index, uint8_t subindex, void *data);
    extern uint32_t master_cia402_write_callback(uint16_t index, uint8_t subindex, void *data);
    if (is_write == 1)
    {
        master_cia402_write_callback(obj_index, obj_subindex, &obj_data);
    }
    else if (is_write == 0)
    {
        master_cia402_read_callback(obj_index, obj_subindex, &obj_data);
    }
    else
    {
        return;
    }

    // Prepare response
    bsp_fdcan->tx_data[0] = is_write;
    bsp_fdcan->tx_data[1] = obj_index & 0xFF;
    bsp_fdcan->tx_data[2] = (obj_index >> 8) & 0xFF;
    bsp_fdcan->tx_data[3] = obj_subindex;
    bsp_fdcan->tx_data[4] = obj_data & 0xFF;
    bsp_fdcan->tx_data[5] = (obj_data >> 8) & 0xFF;
    bsp_fdcan->tx_data[6] = (obj_data >> 16) & 0xFF;
    bsp_fdcan->tx_data[7] = (obj_data >> 24) & 0xFF;

    // Send response
    HAL_FDCAN_AddMessageToTxFifoQ(bsp_fdcan->handle, &bsp_fdcan->tx_can, bsp_fdcan->tx_data);
}
#endif // USE_CIA402

#ifdef USE_CUSTOM
/**
 * @brief CAN/FDCAN + 用户自定义协议处理
 * @param hfdcan Pointer to FDCAN handle
 * @param FDCAN_DeviceTypeDef Pointer to FDCAN BSP structure
 * @return None
 */
static inline void fdcan_custom_handle(FDCAN_DeviceTypeDef* bsp_fdcan)
{
    // Custom protocol handling logic：
    bool is_ide = bsp_fdcan->rx_header.IdType == FDCAN_EXTENDED_ID;
    if (bsp_fdcan->rx_header.FDFormat == FDCAN_CLASSIC_CAN)
    {
        bsp_can_send_message(drv_can_app.p_fdcan, bsp_fdcan->id, is_ide, \
                             false, bsp_fdcan->rx_data, bsp_fdcan->rx_header.DataLength);
    }
    else
    {
        bool is_brs = bsp_fdcan->rx_header.BitRateSwitch == FDCAN_BRS_ON;
        bsp_fdcan_send_message(drv_can_app.p_fdcan, bsp_fdcan->id, is_ide, \
                               is_brs, bsp_fdcan->rx_data, bsp_fdcan->rx_header.DataLength);
    }
}
#endif // USE_CUSTOM

#if IS_USE_CAN_PASSTHROUGH == FC_CTRL_ON
static inline void fdcan_passthrough_handle(FDCAN_DeviceTypeDef* bsp_fdcan)
{
    // Custom protocol handling logic：
    uint16_t len;

    /* DLC → 实际字节长度 */
    len = bsp_fdcan_dlc_to_bytes(bsp_fdcan->rx_header.DataLength);

    /* 根据 BRS 区分消息类型 */
    if (bsp_fdcan->rx_header.BitRateSwitch == FDCAN_BRS_OFF)
    {
    #ifdef USE_CAN_MAVLINK_HOST
        MavlinkRecvCallback(&kAxis, &kAxisDw, bsp_fdcan->rx_data, len);
    #endif /* USE_CAN_MAVLINK_HOST */
    }
}

/**
 * @brief  构造 29-bit CAN FD 扩展帧 ID（按协议位定义）
 * @param  version     2 bit
 * @param  flag_end    1 bit
 * @param  cnt_tx      3 bit
 * @param  seq         5 bit
 * @param  flag        2 bit
 * @param  compid      8 bit
 * @param  sysid       5 bit
 * @param  priority    3 bit（越小优先级越高）
 * @return 29-bit CAN 扩展 ID（uint32_t）
 */
uint32_t fdcan_app_ide_make(uint8_t version,
                            uint8_t flag_end,
                            uint8_t cnt_tx,
                            uint8_t seq,
                            uint8_t flag,
                            uint8_t compid,
                            uint8_t sysid,
                            uint8_t priority)
{
    return
        (((uint32_t)(version  & 0x3))  << CANID_VERSION_SHIFT)  |

        (((uint32_t)(flag_end & 0x1))  << CANID_FLAG_END_SHIFT) |

        (((uint32_t)(cnt_tx   & 0x7))  << CANID_CNT_TX_SHIFT)   |

        (((uint32_t)(seq      & 0x1F)) << CANID_SEQ_SHIFT)      |

        (((uint32_t)(flag     & 0x3))  << CANID_FLAG_SHIFT)     |

        (((uint32_t)(compid   & 0xFF)) << CANID_COMPID_SHIFT)   |

        (((uint32_t)(sysid    & 0x1F)) << CANID_SYSID_SHIFT)    |

        (((uint32_t)(priority & 0x7))  << CANID_PRIORITY_SHIFT);
}

// -----------------------------------------------------------
// API 1: 发送函数 (自动分包)
// -----------------------------------------------------------
/**
 * @brief  将 MAVLink buffer 分包并通过 CAN FD 发送
 * @param  hfdcan: FDCAN 句柄
 * @param  pData:  MAVLink 完整数据包指针 (包含 Header, Payload, CRC)
 * @param  len:    数据总长度
 * @param  sysId:  本机 System ID
 * @param  compId: 本机 Component ID
 * @param  priority: 优先级 (越小越高, 默认传 2)
 * @return 0:成功, 1:失败
 */
// 内部静态变量，用于维护发送序列号 (0-31)
static uint8_t g_tx_transfer_seq = 0;
uint8_t fdcan_app_mav_send_packet(FDCAN_HandleTypeDef *hfdcan, uint8_t *pData, uint16_t len,
                                  uint8_t sysId, uint8_t compId, uint8_t priority,uint8_t ch)
{
    FDCAN_TxHeaderTypeDef TxHeader;
    uint32_t can_id_base = 0;
    uint16_t sent_len = 0;
    uint8_t cnt_of_tx = 0;
    uint8_t chunk_size = 0;
    uint8_t flag_end = 0;

    // 1. 构建 ID 的静态部分 (不会随分包变化的部分)
    can_id_base |= ((uint32_t)priority & 0x07) << CAN_POS_PRIORITY;
    can_id_base |= ((uint32_t)sysId    & 0x1F) << CAN_POS_SYSID;
    can_id_base |= ((uint32_t)compId   & 0xFF) << CAN_POS_COMPID;
    can_id_base |= ((uint32_t)MAVCAN_BROADCAST_NONE & 0x03) << CAN_POS_FLAG_CAST;
    can_id_base |= ((uint32_t)MAVCAN_VERSION      & 0x03) << CAN_POS_VERSION;

    // 2. 配置通用发送头参数
    TxHeader.IdType = FDCAN_EXTENDED_ID;
    TxHeader.TxFrameType = FDCAN_DATA_FRAME;
    TxHeader.ErrorStateIndicator = FDCAN_ESI_ACTIVE;

    if (ch == CANFD_DEBUG)
        TxHeader.BitRateSwitch = FDCAN_BRS_OFF; // 不开启加速
    else
        TxHeader.BitRateSwitch = FDCAN_BRS_ON; // 开启加速

    TxHeader.FDFormat = FDCAN_FD_CAN;
    TxHeader.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
    TxHeader.MessageMarker = 0;

    // 3. 循环发送分包
    while (sent_len < len)
    {
        // 计算本包大小
        if ((len - sent_len) > 64) {
            chunk_size = 64;
            flag_end = 1; // 还有后续
        } else {
            chunk_size = (uint8_t)(len - sent_len);
            flag_end = 0; // 最后一包
        }

        // 组合动态 ID 部分
        TxHeader.Identifier = can_id_base;
        TxHeader.Identifier |= ((uint32_t)g_tx_transfer_seq & 0x1F) << CAN_POS_TRANS_SEQ;
        TxHeader.Identifier |= ((uint32_t)cnt_of_tx         & 0x07) << CAN_POS_CNT_OF_TX;
        TxHeader.Identifier |= ((uint32_t)flag_end          & 0x01) << CAN_POS_FLAG_END;

        // 设置长度
        TxHeader.DataLength = bsp_fdcan_bytes_to_dlc(chunk_size);

        // 等待 FIFO 空闲 (简单的忙等待，实际项目可加超时)
        //while (HAL_FDCAN_GetTxFifoFreeLevel(hfdcan) == 0) {}

        // 发送
        if (HAL_FDCAN_AddMessageToTxFifoQ(hfdcan, &TxHeader, &pData[sent_len]) != HAL_OK) {
            return 1; // 发送失败
        }

        sent_len += chunk_size;
        cnt_of_tx++;

        // 3bit计数器溢出保护 (MAVLink包通常不会超过 8*64=512字节)
        if (cnt_of_tx > 7) break;
    }

    // 4. 整包发送完毕，序列号自增 (0-31循环)
    g_tx_transfer_seq = (g_tx_transfer_seq + 1) & 0x1F;

    return 0; // 成功
}

#endif // IS_USE_CAN_PASSTHROUGH

#endif // USE_CAN
