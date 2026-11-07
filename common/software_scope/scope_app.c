#include "scope_app.h"

#include "scope_map.h"
#include "ringbuffer.h"

ScopeStruct kScopeObject;
ChannelStruct kChannelObjectArray[SCOPE_CHANNEL_NUM_MAX];
static uint8_t scope_buff[SCOPE_BUF_MAX];

/**
 * @brief 初始化示波器通道，任务中运行，根据状态进行切换
 */
static uint8_t scope_channel_config(void) {
    uint8_t channel_amount = 0;
    uint8_t channel_active_list[SCOPE_CHANNEL_NUM_MAX] = {0};

    /* 计算总共有多少通道打开 */
    for (uint8_t i = 0; i < SCOPE_CHANNEL_NUM_MAX; i++) {
        if (kRecordOpenFlag == kScopeObject.channel_object[i]->recoder_flag) {
            channel_active_list[channel_amount] = i;
            channel_amount++;
            get_database_param_info(kScopeObject.channel_object[i]->data_index,
                                    &kScopeObject.channel_object[i]->data_val,
                                    &kScopeObject.channel_object[i]->data_type,
                                    &kScopeObject.channel_object[i]->data_size,
                                    &kScopeObject.channel_object[i]->data_ptr);
        }
    }

    /* 获取触发通道信息 */
    get_database_param_info(kScopeObject.trigger_object.data_index,
                            &kScopeObject.trigger_object.data_val,
                            &kScopeObject.trigger_object.data_type,
                            &kScopeObject.trigger_object.data_size,
                            &kScopeObject.trigger_object.data_ptr);

    /* 如果没有通道打开，则直接退出 */
    if (0 == channel_amount) { 
        return 1;
    }

    //各个通道的数据类型不同，但是要确保每个通道的采样点数是一样的，根据scope_buff的大小来计算
    uint8_t data_size_all = 0;
    for (uint8_t i = 0; i < channel_amount; i++) {
        data_size_all += kScopeObject.channel_object[channel_active_list[i]]->data_size;
    }
    uint32_t points_max = kScopeObject.storage_data_buffer_size / data_size_all;

    //实际采样点数 = 配置采样点数 / 配置采样间隔
    kScopeObject.sample_points_all = kScopeObject.sample_points;

    //如果buffer的大小不够，则直接返回
    if(points_max < kScopeObject.sample_points_all){
        return 2;
    }

    uint32_t buffer_offset = 0;

    //初始化ringbuffer
    for (uint8_t i = 0; i < channel_amount; i++) {
        ringbuffer_init(&kScopeObject.channel_object[channel_active_list[i]]->recoder_buffer,
            &kScopeObject.storage_data_buffer[buffer_offset], points_max * kScopeObject.channel_object[channel_active_list[i]]->data_size);
            buffer_offset += points_max * kScopeObject.channel_object[channel_active_list[i]]->data_size;
    }

    return 0;
}

/**
 * @brief 扫描所有示波器通道，数据采样，中断运行
 */
static void scope_data_sample_run(void) {
    uint32_t data_val = 0;

    for (uint8_t i = 0; i < SCOPE_CHANNEL_NUM_MAX; i++) {
        if (kRecordOpenFlag == kScopeObject.channel_object[i]->recoder_flag) {
            get_database_param_val(kScopeObject.channel_object[i]->data_ptr, kScopeObject.channel_object[i]->data_type, &data_val);
            if (kTriggerSuccessFlag != kScopeObject.trigger_flag) {
                ringbuffer_put_overlayable(&kScopeObject.channel_object[i]->recoder_buffer,
                                           (uint8_t*)&data_val,
                                           kScopeObject.channel_object[i]->data_size);
            } else {
                ringbuffer_put(&kScopeObject.channel_object[i]->recoder_buffer,
                               (uint8_t*)&data_val, kScopeObject.channel_object[i]->data_size);
            }
        }
    }
    kScopeObject.sample_point_count++;
}

/**
 * @brief 改变计数规则
 * @note  1.修改存储buffer的起始位置
 *        2.计算还需要记录的数据量
 *        3.不再提供循环计数的功能，从起始位置开始的数据不能再被覆盖
 */
static void change_count_rule(void) {
    /* 计算有效数据存储的起始位置，ps：用户需要采集的数据才是有效数据，而不是传进来的任何数据 */
    /* 因为边沿触发捕捉窗口有宽度，所以延迟了半个窗口的时间，此处需要补上 */
    /* 此处还需要加入采集延时的计算 */
    /* 计算偏移时，注意数据宽度，因为ringbuffer存储的是字节 */

    uint16_t offset_index = kScopeObject.sample_points_all * kScopeObject.sample_delay / 100;
    offset_index += CATCH_WINDOW_SIZE / 2;

    /* 此处需要修改一下已经记录的有效采样点数 */
    kScopeObject.sample_point_count = offset_index;

    /* 校准ringbuffer中的有效数据存储的有效位置，即修改read指针 */
    uint16_t actual_index = 0;
    uint16_t actual_mirror = 0;

    for (uint8_t i = 0; i < SCOPE_CHANNEL_NUM_MAX; i++) {
        if (kRecordOpenFlag == kScopeObject.channel_object[i]->recoder_flag) {
            //计算偏移量
            ringbuffer_get_write_index_offset(&kScopeObject.channel_object[i]->recoder_buffer,
                                            offset_index * kScopeObject.channel_object[i]->data_size, &actual_index, &actual_mirror);
            //重新校准read指针
            ringbuffer_set_read_index(&kScopeObject.channel_object[i]->recoder_buffer, actual_index,
                actual_mirror);
        }
    }
}

/**
 * @brief 触发采样函数，中断运行
 */
static void scope_trigger_catch(void) {
    uint32_t data_val = 0;
    TriggerStruct* trigger_object = &kScopeObject.trigger_object;
    TypeConverter conv_data = {0};
    TypeConverter conv_threshold = {0};

    /* 如果边沿已经触发，则直接退出 */
    if (kTriggerSuccessFlag == kScopeObject.trigger_flag) { return; }

    /* 边沿触发判断，需要已经捕捉到了足够的数据 */
    if (trigger_object->catch_count < CATCH_WINDOW_SIZE) {
        get_database_param_val(trigger_object->data_ptr, trigger_object->data_type, &data_val);
        //根据数据类型进行数据转换
        conv_data.u32 = data_val;
        conv_threshold.i32 = kScopeObject.sample_trigger_threshold;
        switch(trigger_object->data_type)
        {
            case kTypeUint8:
                trigger_object->catch_window_uint32[trigger_object->catch_count] = conv_data.u8;
                trigger_object->threshold_uint32 = conv_threshold.u8;
                trigger_object->catch_data_type = kTypeUint32;
                break;
            case kTypeUint16:
                trigger_object->catch_window_uint32[trigger_object->catch_count] = conv_data.u16;
                trigger_object->threshold_uint32 = conv_threshold.u16;
                trigger_object->catch_data_type = kTypeUint32;
                break;
            case kTypeUint32:
                trigger_object->catch_window_uint32[trigger_object->catch_count] = conv_data.u32;
                trigger_object->threshold_uint32 = conv_threshold.u32;
                trigger_object->catch_data_type = kTypeUint32;
                break;
            case kTypeUint64:
                // todo:暂时不支持64位数据触发采集，强制转为32位数据触发采集
                trigger_object->catch_window_uint32[trigger_object->catch_count] = conv_data.u32;
                trigger_object->threshold_uint32 = conv_threshold.u32;
                trigger_object->catch_data_type = kTypeUint32;
                break;
            case kTypeInt8:
                trigger_object->catch_window_int32[trigger_object->catch_count] = conv_data.i8;
                trigger_object->threshold_int32 = conv_threshold.i8;
                trigger_object->catch_data_type = kTypeInt32;
                break;
            case kTypeInt16:
                trigger_object->catch_window_int32[trigger_object->catch_count] = conv_data.i16;
                trigger_object->threshold_int32 = conv_threshold.i16;
                trigger_object->catch_data_type = kTypeInt32;
                break;
            case kTypeInt32:
                trigger_object->catch_window_int32[trigger_object->catch_count] = conv_data.i32;
                trigger_object->threshold_int32 = conv_threshold.i32;
                trigger_object->catch_data_type = kTypeInt32;
                break;
            case kTypeInt64:
                // todo:暂时不支持64位数据触发采集，强制转为32位数据触发采集
                trigger_object->catch_window_int32[trigger_object->catch_count] = conv_data.i32;
                trigger_object->threshold_int32 = conv_threshold.i32;
                trigger_object->catch_data_type = kTypeInt32;
                break;
            case kTypeFloat32:
                trigger_object->catch_window_float32[trigger_object->catch_count] = conv_data.f32;
                trigger_object->threshold_float32 = conv_threshold.f32;
                trigger_object->catch_data_type = kTypeFloat32;
                break;
            default:
                break;
        }
        trigger_object->catch_count++;
        if (trigger_object->catch_count < CATCH_WINDOW_SIZE) { return; }
    }

    //获取到足够数据后，进行触发判断
    switch (kScopeObject.sample_trigger_mode) {
        case kRisingEdgeMode:
            switch(trigger_object->catch_data_type)
            {
                case kTypeUint32:
                    if (trigger_object->catch_window_uint32[0] <= trigger_object->threshold_uint32 &&
                        trigger_object->catch_window_uint32[CATCH_WINDOW_SIZE - 1] >= trigger_object->threshold_uint32 && 
                        trigger_object->catch_window_uint32[0] < trigger_object->catch_window_uint32[CATCH_WINDOW_SIZE - 1]) {
                            kScopeObject.trigger_flag = kTriggerSuccessFlag; 
                        }
                    break;
                case kTypeInt32:
                    if (trigger_object->catch_window_int32[0] <= trigger_object->threshold_int32 &&
                        trigger_object->catch_window_int32[CATCH_WINDOW_SIZE - 1] >= trigger_object->threshold_int32 &&
                        trigger_object->catch_window_int32[0] < trigger_object->catch_window_int32[CATCH_WINDOW_SIZE - 1]) {
                            kScopeObject.trigger_flag = kTriggerSuccessFlag; 
                        }
                    break;
                case kTypeFloat32:
                    if (trigger_object->catch_window_float32[0] <= trigger_object->threshold_float32 &&
                        trigger_object->catch_window_float32[CATCH_WINDOW_SIZE - 1] >= trigger_object->threshold_float32 &&
                        trigger_object->catch_window_float32[0] < trigger_object->catch_window_float32[CATCH_WINDOW_SIZE - 1]) {
                            kScopeObject.trigger_flag = kTriggerSuccessFlag;
                        }
                    break;
                default:
                    break;
            }
            break;
        case kFallingEdgeMode:
            switch(trigger_object->catch_data_type)
            {
                case kTypeUint32:
                    if (trigger_object->catch_window_uint32[0] >= trigger_object->threshold_uint32 &&
                        trigger_object->catch_window_uint32[CATCH_WINDOW_SIZE - 1] <= trigger_object->threshold_uint32 && 
                        trigger_object->catch_window_uint32[0] > trigger_object->catch_window_uint32[CATCH_WINDOW_SIZE - 1]) {
                            kScopeObject.trigger_flag = kTriggerSuccessFlag; 
                        }
                    break;
                case kTypeInt32:
                    if (trigger_object->catch_window_int32[0] >= trigger_object->threshold_int32 &&
                        trigger_object->catch_window_int32[CATCH_WINDOW_SIZE - 1] <= trigger_object->threshold_int32 &&
                        trigger_object->catch_window_int32[0] > trigger_object->catch_window_int32[CATCH_WINDOW_SIZE - 1]) {
                            kScopeObject.trigger_flag = kTriggerSuccessFlag; 
                        }
                    break;
                case kTypeFloat32:
                    if (trigger_object->catch_window_float32[0] >= trigger_object->threshold_float32 &&
                        trigger_object->catch_window_float32[CATCH_WINDOW_SIZE - 1] <= trigger_object->threshold_float32 &&
                        trigger_object->catch_window_float32[0] > trigger_object->catch_window_float32[CATCH_WINDOW_SIZE - 1]) {
                            kScopeObject.trigger_flag = kTriggerSuccessFlag;
                        }
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
    /* 如果没有满足触发条件，则舍弃第一个数据，继续采集数据 */
    if (kTriggerSuccessFlag != kScopeObject.trigger_flag) {
        for (uint8_t i = 0; i < CATCH_WINDOW_SIZE - 1; i++) {
            switch(trigger_object->catch_data_type)
            {
                case kTypeUint32:
                    trigger_object->catch_window_uint32[i] = trigger_object->catch_window_uint32[i + 1];
                    break;
                case kTypeInt32:
                    trigger_object->catch_window_int32[i] = trigger_object->catch_window_int32[i + 1];
                    break;
                case kTypeFloat32:
                    trigger_object->catch_window_float32[i] = trigger_object->catch_window_float32[i + 1];
                    break;
                default:
                    break;
            }
        }
        trigger_object->catch_count--;
    } else {
        change_count_rule();
    }
}

/**
 * @brief 采样完成判断
 **/
static void sample_complete_judge(void) {
    /* 判断是否采集已经完成：采集完成有几种触发方式 */
    /* 检查是否是自然采集完成，自然完成的前提是捕捉到了有效数据，即有边沿触发 */
    if (kSampleComplete == kScopeObject.sample_complete_flag) { return; }
    if (kTriggerSuccessFlag == kScopeObject.trigger_flag) {
        if (kScopeObject.sample_point_count >= kScopeObject.sample_points_all) {
            kScopeObject.sample_complete_flag = kSampleComplete;
        }
    }
}

/**
 * @brief 采样完成处理
 */
static void sample_complete_deal(void) {
    if (kSampleComplete != kScopeObject.sample_complete_flag) { return; }

    /* 如果采样已经完成，则打包采样通道中的数据，打包的时候和数据的宽度有关 */
    uint16_t frame_point_count = 0;
    uint16_t frame_count = 0;

    for (uint8_t i = 0; i < SCOPE_CHANNEL_NUM_MAX; i++) {
        if (kRecordOpenFlag == kScopeObject.channel_object[i]->recoder_flag) {
            //计算单帧的采样点数
            frame_point_count = FRAME_SIZE / kScopeObject.channel_object[i]->data_size;
            //根据总点数计算总帧数
            frame_count = kScopeObject.sample_points_all / frame_point_count;
            //如果有余数，则需要加一帧
            if (kScopeObject.sample_points_all % frame_point_count) { frame_count++; }
            kScopeObject.channel_object[i]->package_count = frame_count;
        }
    }
}

/**
 * @brief 示波器配置
 */
static void scope_config(void) {
    /* 示波器的采样点数不能为0 */
    if (0 == kScopeObject.sample_points) {
        kScopeObject.status_word = kScopeError;
        return;
    }
    /* 示波器的采样间隔不能为0 */
    if (0 == kScopeObject.sample_interval) {
        kScopeObject.status_word = kScopeError;
        return;
    }
    /* 通道配置 */
    if(0 != scope_channel_config()){
        kScopeObject.status_word = kScopeError;
        return;
    }

    kScopeObject.status_word = kScopeNormal;
}

/**
 * @brief 示波器重置
 */
static void scope_reset(void) {
    /* 初始化存储采集数据的buffer */
    memset(kScopeObject.storage_data_buffer, 0, kScopeObject.storage_data_buffer_size);

    /* 释放数据库的离线波形缓存 */
    /* 初始化各通道 */
    for (uint8_t i = 0; i < SCOPE_CHANNEL_NUM_MAX; i++) {
        kScopeObject.channel_object[i]->recoder_flag = kRecordCloseFlag;
        kScopeObject.channel_object[i]->package_count = 0;
        kScopeObject.channel_object[i]->data_index = 0;
        ringbuffer_reset(&kScopeObject.channel_object[i]->recoder_buffer);
    }
    /* 初始化示波器自身的属性 */
    kScopeObject.sample_trigger_mode = kFallingEdgeMode;
    kScopeObject.trigger_flag = kTriggerFailedFalg;
    kScopeObject.sample_complete_flag = kSampleUnComplete;
    kScopeObject.sample_delay = 0;
    kScopeObject.sample_trigger_threshold = 0;
    kScopeObject.sample_interval = 1;
    kScopeObject.sample_interval_count = 0;
    kScopeObject.sample_points = 0;
    kScopeObject.sample_points_all = 0;
    kScopeObject.sample_point_count = 0;
    memset(&kScopeObject.trigger_object, 0, sizeof(TriggerStruct));
    /* 初始化标志位放到最后赋值 */
    kScopeObject.control_word = kScopeNull;
    kScopeObject.status_word = kScopeNormal;
}

/**
 * @brief 获取通道数据
 */
void ScopeChannelDataRead(uint32_t channel_num, uint16_t subindex, uint8_t* data_length,
                             uint8_t* p_data) {
    ChannelStruct* temp_channel = NULL;
    temp_channel = kScopeObject.channel_object[channel_num];
    *data_length = ringbuffer_get_offset(&(temp_channel->recoder_buffer), p_data,
                                         (subindex * FRAME_SIZE), FRAME_SIZE);
}

/**
 * @brief 示波器初始化，系统上电后仅执行一次
 */
void ScopeInit(void) {

    memset(&kScopeObject, 0, sizeof(ScopeStruct));

    /* 清除初始化成功标志 */
    kScopeObject.init_flag = kInitFailedFlag;

    /* 初始化存储采集数据的buffer */
    kScopeObject.storage_data_buffer = scope_buff;
    kScopeObject.storage_data_buffer_size = SCOPE_BUF_MAX;

    /* 初始化各通道 */
    for (uint8_t i = 0; i < SCOPE_CHANNEL_NUM_MAX; i++) {
        kScopeObject.channel_object[i] = &kChannelObjectArray[i];
        ringbuffer_reset(&kScopeObject.channel_object[i]->recoder_buffer);
    }
    kScopeObject.init_flag = kInitSuccessFlag;
}

/**
 * @brief 示波器中断处理
 */
void ScopeIsrHandle(void) {
    //初始化未完成，则直接返回
    if (kInitSuccessFlag != kScopeObject.init_flag) { return; }

    //示波器状态异常
    if (kScopeError == kScopeObject.status_word) { return; }

    /* 如果采集完成，则打包采集到的数据 */
    if ((kSampleComplete == kScopeObject.sample_complete_flag) &&
        (kScopeObject.status_word != kSampleSuccess)) {
        kScopeObject.status_word = kSampleSuccess;
        kScopeObject.sample_isr_flag = kSampleIsrClose;

        sample_complete_deal();
    }

    /* 如果采样中断没有打开，则直接返回 */
    if (kSampleIsrOpen != kScopeObject.sample_isr_flag) { return; }

    /* 返回值，如果已经采集完成，则返回 */
    if (kSampleComplete == kScopeObject.sample_complete_flag) { return; }

    /* 进行采样间隙判断 */
    kScopeObject.sample_interval_count++;
    if (kScopeObject.sample_interval_count < kScopeObject.sample_interval) { return; }

    kScopeObject.sample_interval_count = 0;
    /* 进行数据记录 */
    scope_data_sample_run();
    /* 捕捉触发边沿 */
    scope_trigger_catch();
    /* 判断是否已经采集完成 */
    sample_complete_judge();
}

/**
 * @brief 控制字写入回调函数
 * @param control_word 控制字
 */
void ControlWordWriteCallback(ScopeControlWord control_word) {
    kScopeObject.control_word = control_word;
    switch (kScopeObject.control_word) {
        case kScopeConfig:
            scope_config();
            break;

        case kSampleTrigger:
            kScopeObject.sample_isr_flag = kSampleIsrOpen;
            break;

        case kSampleImmediately:
            kScopeObject.sample_point_count = 0;
            kScopeObject.trigger_flag = kTriggerSuccessFlag;
            kScopeObject.sample_isr_flag = kSampleIsrOpen;
            break;

        case kSampleStop:
            if (kSampleComplete == kScopeObject.sample_complete_flag) { return; }
            /* 如果没有捕捉到边沿，则就以当前的累计值为找到的数据。否则就以有效值为找到的数据 */
            if (kTriggerSuccessFlag != kScopeObject.trigger_flag) {
                if (kScopeObject.sample_point_count > kScopeObject.sample_points_all) {
                    kScopeObject.sample_point_count = kScopeObject.sample_points_all;
                }
            }
            kScopeObject.sample_complete_flag = kSampleComplete;
            break;

        case kScopeReset:
            scope_reset();
            break;

        default:
            break;
    }
}


/**
 * @brief 根据索引获取数据库参数值和字节数
 * @param[in] index 数据库索引
 * @param[out] pdata 数据值
 * @param[out] type 数据类型
 * @param[out] size 字节数
 * @param[out] pdata_ptr 数据指针
 */
void get_database_param_info(uint32_t index, uint32_t *pdata, uint8_t *type, uint8_t *size, void **pdata_ptr) {

    uint32_t array_index_temp = 0;

    if (pdata == NULL || type == NULL || size == NULL) {
        return;
    }

    for (uint32_t i = 0; i < (sizeof(kParamDataBase) / sizeof(kParamDataBase[0])); i++) {
        if (kParamDataBase[i].index == (index >> 16)) {
            //单个变量的子索引是0，数组子索引(1-n)，访问数组成员时，索引要减一
            array_index_temp = 0;
            if((index & 0xffff) != 0){
                array_index_temp = (index & 0xffff) - 1; 
            }
            *type = kParamDataBase[i].type;
            switch (kParamDataBase[i].type) {
                case kTypeUint8:
                    *pdata = *((uint8_t *)kParamDataBase[i].pdata + array_index_temp);
                    *pdata_ptr = (uint8_t *)kParamDataBase[i].pdata + array_index_temp;
                    *size = 1;
                    return;

                case kTypeInt8:
                    *pdata = *((int8_t *)kParamDataBase[i].pdata + array_index_temp);
                    *pdata_ptr = (int8_t *)kParamDataBase[i].pdata + array_index_temp;
                    *size = 1;
                    return;

                case kTypeUint16:
                    *pdata = *((uint16_t *)kParamDataBase[i].pdata + array_index_temp);
                    *pdata_ptr = (uint16_t *)kParamDataBase[i].pdata + array_index_temp;
                    *size = 2;
                    return;

                case kTypeInt16:
                    *pdata = *((int16_t *)kParamDataBase[i].pdata + array_index_temp);
                    *pdata_ptr = (int16_t *)kParamDataBase[i].pdata + array_index_temp;
                    *size = 2;
                    return;

                case kTypeUint32:
                    *pdata = *((uint32_t *)kParamDataBase[i].pdata + array_index_temp);
                    *pdata_ptr = (uint32_t *)kParamDataBase[i].pdata + array_index_temp;
                    *size = 4;
                    return;

                case kTypeInt32:
                    *pdata = *((int32_t *)kParamDataBase[i].pdata + array_index_temp);
                    *pdata_ptr = (int32_t *)kParamDataBase[i].pdata + array_index_temp;
                    *size = 4;
                    return;
                //float类型数据存储完整的32位信息，所以指针是32位
                case kTypeFloat32:
                    *pdata = *((uint32_t *)kParamDataBase[i].pdata + array_index_temp);
                    *pdata_ptr = ((uint32_t *)kParamDataBase[i].pdata + array_index_temp);
                    *size = 4;
                    return;

                case kTypeInt64:    //离线波形64位数据截取32位数据处理
                    *pdata = (*((int64_t *)kParamDataBase[i].pdata + array_index_temp)) & 0xFFFFFFFF;
                    *pdata_ptr = ((int64_t *)kParamDataBase[i].pdata + array_index_temp);
                    *size = 4;
                    return;

                case kTypeUint64:   //离线波形64位数据截取32位数据处理
                    *pdata = (*((uint64_t *)kParamDataBase[i].pdata + array_index_temp)) & 0xFFFFFFFF;
                    *pdata_ptr = ((uint64_t *)kParamDataBase[i].pdata + array_index_temp);
                    *size = 4;
                    return;

                default:
                    break;
            }
            return;
        }
    }
}


/**
 * @brief 根据示波器初始化配置时，获取的变量指针和类型，获取变量值
 * @param[in] pdata_ptr 变量指针
 * @param[in] type 变量类型
 * @param[out] pdata 变量值
 */
void get_database_param_val(void *pdata_ptr, uint8_t type, uint32_t *pdata)
{
    if (pdata_ptr == NULL) {
        return;
    }
    switch (type)
    {
        case kTypeUint8:
            *pdata = *((uint8_t *)pdata_ptr);
            break;
        case kTypeInt8:
            *pdata = *((int8_t *)pdata_ptr);
            break;
        case kTypeUint16:
            *pdata = *((uint16_t *)pdata_ptr);
            break;
        case kTypeInt16:
            *pdata = *((int16_t *)pdata_ptr);
            break;
        case kTypeUint32:
            *pdata = *((uint32_t *)pdata_ptr);
            break;
        case kTypeInt32:
            *pdata = *((int32_t *)pdata_ptr);
            break;
        case kTypeFloat32:
            *pdata = *((uint32_t *)pdata_ptr);
            break;
        case kTypeInt64:
            *pdata = *((int64_t *)pdata_ptr) & 0xFFFFFFFF;
            break;
        case kTypeUint64:
            *pdata = *((uint64_t *)pdata_ptr) & 0xFFFFFFFF;
            break;
        default:
            break;
    }
}
