#ifndef DRV_CAN_APP_H
#define DRV_CAN_APP_H

#include "board.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifdef USE_CAN
void fdcan_app_init(void);
void fdcan_app_fifo0_handle(FDCAN_HandleTypeDef* hfdcan);
void fdcan_app_fifo1_handle(FDCAN_HandleTypeDef* hfdcan);

#ifdef USE_CANOPEN
#define CANOPEN_ID_MAX      (0x7F)
#define CANID_STD_FILTER_FUNC_GLOBAL 0
#define CANID_STD_FILTER_FUNC_SLAVE 1
void CANopen_DispatchFromISR(void);
#endif // USE_CANOPEN

#if IS_USE_CAN_PASSTHROUGH == FC_CTRL_ON

#define CANID_ID_CAN_MAPPING_COMP   (true) // MAVLink CAN ID 映射到 组件ID
#define CANID_SYSID_DEFAULT         (0x1)
#define CANID_COMPID_DEFAULT        (CAN_ID_DEFAULT)


#define CANFD_RECV_BUFF_SIZE 300
#define CANFD_SEND_BUFF_SIZE 300

#define CANID_PRIORITY 1

#define CANFD_MESSAGE 1
#define CANFD_DEBUG   2

/* ========= 滤波器ID 相关定义 ========= */
// 滤波器ID Flag定义
#define CANID_FLAG_GLOBAL           2U
#define CANID_FLAG_SYSTEM           1U

// 滤波器ID 索引定义
#define CANID_EXT_FILTER_FUNC_GLOBAL 0U
#define CANID_EXT_FILTER_FUNC_SYSTEM 1U
#define CANID_EXT_FILTER_FUNC_SLAVE  2U

/* ========= 位移定义 ========= */
#define CANID_VERSION_SHIFT        0
#define CANID_FLAG_END_SHIFT       2
#define CANID_CNT_TX_SHIFT         3
#define CANID_SEQ_SHIFT            6
#define CANID_FLAG_SHIFT           11
#define CANID_COMPID_SHIFT         13
#define CANID_SYSID_SHIFT          21
#define CANID_PRIORITY_SHIFT       26


/* ========= 位掩码 ========= */
#define CANID_VERSION_MASK   (0x3  << CANID_VERSION_SHIFT)
#define CANID_FLAG_END_MASK  (0x1  << CANID_FLAG_END_SHIFT)
#define CANID_CNT_TX_MASK    (0x7  << CANID_CNT_TX_SHIFT)
#define CANID_SEQ_MASK       (0x1F << CANID_SEQ_SHIFT)
#define CANID_FLAG_MASK      (0x3  << CANID_FLAG_SHIFT)
#define CANID_COMPID_MASK    (0xFF << CANID_COMPID_SHIFT)
#define CANID_SYSID_MASK     (0x1F << CANID_SYSID_SHIFT)
#define CANID_PRIORITY_MASK  (0x7  << CANID_PRIORITY_SHIFT)
// ==========================================
// MAVCAN 协议位定义 (29Bit Extended ID)
// ==========================================
#define CAN_POS_PRIORITY      26 // [28:26] 3bit
#define CAN_POS_SYSID         21 // [25:21] 5bit
#define CAN_POS_COMPID        13 // [20:13] 8bit
#define CAN_POS_FLAG_CAST     11 // [12:11] 2bit
#define CAN_POS_TRANS_SEQ     6  // [10:6]  5bit
#define CAN_POS_CNT_OF_TX     3  // [5:3]   3bit
#define CAN_POS_FLAG_END      2  // [2]     1bit
#define CAN_POS_VERSION       0  // [1:0]   2bit

// 默认配置
#define MAVCAN_VERSION        0
#define MAVCAN_BROADCAST_NONE 0

uint32_t fdcan_app_ide_make(uint8_t version, uint8_t flag_end, uint8_t cnt_tx, uint8_t seq, \
                            uint8_t flag, uint8_t compid, uint8_t sysid, uint8_t priority);
uint8_t fdcan_app_mav_send_packet(FDCAN_HandleTypeDef *hfdcan, uint8_t *pData, uint16_t len, \
                              uint8_t sysId, uint8_t compId, uint8_t priority,uint8_t ch);

#endif // IS_USE_CAN_PASSTHROUGH

#endif // USE_CAN
#ifdef __cplusplus
}
#endif

#endif // DRV_CAN_APP_H
