#ifndef __BSP_FDCAN_H
#define __BSP_FDCAN_H

#include "board.h"

#ifdef __cplusplus
extern "C" {
#endif

#define CAN_ID_DEFAULT              (0x15)
#define CAN_DATA_LEN_MAX            (8u)
#define FDCAN_DATA_LEN_MAX          (64u)

typedef enum {
    // ... Other CAN Baudrates Slow
    FDCAN_BAUDRATE_500K_BPS = 500000u,
    FDCAN_BAUDRATE_1M_BPS   = 1000000u
    // ... Other CAN Baudrates Fast
} FDCAN_BaudrateTypeDef;

/**
 * @brief FDCAN设备结构体
 */
typedef struct {
    FDCAN_HandleTypeDef *handle;        // FDCAN句柄指针
    FDCAN_FilterTypeDef sFilterConfig;  // 过滤器配置
    FDCAN_RxHeaderTypeDef rx_header;    // 接收帧头
    FDCAN_TxHeaderTypeDef tx_can;       // 发送CAN帧头
    FDCAN_TxHeaderTypeDef tx_fdcan;     // 发送FDCAN帧头
    FDCAN_BaudrateTypeDef baudrate;     // 波特率
    uint32_t id;                        // CAN通信ID
    uint32_t mav_sys_id;                // mavlink系统ID
    uint32_t mav_comp_id;               // mavlink组件ID
    uint32_t mg_counts;                 // 接收消息计数器
    uint8_t rx_data[FDCAN_DATA_LEN_MAX];// 接收数据缓冲区
    uint8_t tx_data[FDCAN_DATA_LEN_MAX];// 发送数据缓冲区
} FDCAN_DeviceTypeDef;


FDCAN_DeviceTypeDef* bsp_fdcan_get_fdcan_handle(void);
HAL_StatusTypeDef bsp_fdcan_init(void);
void bsp_fdcan_set_id(uint32_t can_id);
uint32_t bsp_fdcan_get_id(void);
void bsp_fdcan_set_mav_id(uint8_t sys_id, uint8_t comp_id);
void bsp_fdcan_get_mav_id(uint8_t *sys_id, uint8_t *comp_id);
void bsp_fdcan_set_baudrate(uint32_t baudrate);
uint32_t bsp_fdcan_get_baudrate(void);
uint32_t bsp_fdcan_get_mg_counts(void);

HAL_StatusTypeDef bsp_can_send_message(FDCAN_DeviceTypeDef* bsp_fdcan, uint32_t id, \
                                       bool is_ide, bool is_rtr, uint8_t* data, uint8_t len);
HAL_StatusTypeDef bsp_fdcan_send_message(FDCAN_DeviceTypeDef* bsp_fdcan, uint32_t std_id,\
                                         bool is_ide, bool is_brs, uint8_t *data, uint8_t len);
uint8_t bsp_fdcan_dlc_to_bytes(uint32_t dlc);
uint32_t bsp_fdcan_bytes_to_dlc(uint8_t bytes_len);

#ifdef __cplusplus
}
#endif

#endif /* __BSP_FDCAN_H */
