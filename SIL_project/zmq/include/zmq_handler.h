#ifndef ZMQ_HANDLER_H
#define ZMQ_HANDLER_H
#include "zmq.h"

typedef struct {
    void (*recv_callback)(void *args, void* args_dw, uint8_t rx_data[], uint32_t len);
} ZmqRecvCallback;

// 初始化zmq
int ZmqHandlerInit(void);
// zmq异步接收函数
void ZmqAsyncRecv(void* args, void* args_dw);
// zmq发送数据
void ZmqSendData(uint8_t *pdata, uint32_t len);
// zmq销毁
void ZmqDestroy(void);
// zmq回调注册函数
void RegisterRecvCallback(void* callback);


#endif