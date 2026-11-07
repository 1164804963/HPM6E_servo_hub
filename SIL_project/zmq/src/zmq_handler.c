#include "zmq_handler.h"


void *responder;
void *context;
ZmqRecvCallback msgs_callback = {
    .recv_callback = NULL,
};


int ZmqHandlerInit(void)
{
    context = zmq_ctx_new();
    responder = zmq_socket(context, ZMQ_PAIR);
    int rc = zmq_bind(responder, "tcp://localhost:5555");
    return rc;
}

// zmq销毁
void ZmqDestroy(void)
{
    zmq_close(responder);
    zmq_ctx_destroy(context);
}



// 发送mavlink数据
void ZmqSendData(uint8_t *pdata, uint32_t len)
{
    zmq_send(responder, pdata, len, ZMQ_DONTWAIT);
}


// zmq异步接收函数
void ZmqAsyncRecv(void* args, void* args_dw) {
    zmq_msg_t msg;
    zmq_msg_init(&msg);
    
    // 非阻塞接收
    int rc = zmq_msg_recv(&msg, responder, ZMQ_DONTWAIT);
    if (rc == -1) {
        zmq_msg_close(&msg);
        return;
    }

    // 处理消息
    size_t size = zmq_msg_size(&msg);
    // 调用注册的回调函数
    if (msgs_callback.recv_callback != NULL) {
        msgs_callback.recv_callback(args, args_dw, (uint8_t*)zmq_msg_data(&msg), size);
    }
    zmq_msg_close(&msg);
}

void RegisterRecvCallback(void* callback) {
    msgs_callback.recv_callback = (void (*)(void *args, void *args_dw, uint8_t rx_data[], uint32_t len))callback;
}