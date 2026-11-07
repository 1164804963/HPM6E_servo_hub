#include "mavlink_scope_interface.h"

// uint32_t struct_index[WAVEFORM_CHANNEL_NUM];  //数据索引
// uint32_t array_index[WAVEFORM_CHANNEL_NUM];   //数组子索引

/**
 * @brief 示波器配置
 * @param[in] mavlink_config mavlink示波器配置结构体
 * @param[in] scope_struct 示波器结构体
 * @param[in] rw 0-read 1-write (read：上位机读取参数，write：上位机写入参数)
 * @note 该函数为回调函数，需要在mavlink_callback.c中调用
 */
void mavlink_scope_config_callback(mavlink_scopeconfig_t *mavlink_config, ScopeStruct *scope_struct,
                                   uint8_t rw) {
    if (rw == SCOPE_READ) {
        memset(mavlink_config, 0, sizeof(mavlink_scopeconfig_t));

        mavlink_config->trigger_source = scope_struct->trigger_object.data_index;
        mavlink_config->trigger_mode = scope_struct->sample_trigger_mode;
        mavlink_config->trigger_delay = scope_struct->sample_delay;
        mavlink_config->trigger_threshold = scope_struct->sample_trigger_threshold;
        mavlink_config->sample_interval = scope_struct->sample_interval;
        mavlink_config->sample_points = scope_struct->sample_points;

        // 通道开关
        for (int i = 0; i < SCOPE_CHANNEL_NUM_MAX; i++) {
            if (scope_struct->channel_object[i]->recoder_flag) {
                mavlink_config->channel_switch |= (1 << i);
            }
        }

        // 通道映射
        for (int i = 0; i < SCOPE_CHANNEL_NUM_MAX; i++) {
            mavlink_config->channel_map[i] = scope_struct->channel_object[i]->data_index;
        }
    } else if (rw == SCOPE_WRITE) {
        scope_struct->trigger_object.data_index = mavlink_config->trigger_source;
        scope_struct->sample_trigger_mode = mavlink_config->trigger_mode;
        scope_struct->sample_delay = mavlink_config->trigger_delay;
        scope_struct->sample_trigger_threshold = mavlink_config->trigger_threshold;
        scope_struct->sample_interval = mavlink_config->sample_interval;
        scope_struct->sample_points = mavlink_config->sample_points;

        // 通道开关
        for (int i = 0; i < SCOPE_CHANNEL_NUM_MAX; i++) {
            if (mavlink_config->channel_switch & (1 << i)) {
                scope_struct->channel_object[i]->recoder_flag = kRecordOpenFlag;
            } else {
                scope_struct->channel_object[i]->recoder_flag = kRecordCloseFlag;
            }
        }

        // 通道映射
        for (int i = 0; i < SCOPE_CHANNEL_NUM_MAX; i++) {
            scope_struct->channel_object[i]->data_index = mavlink_config->channel_map[i];
        }
    }
}

/**
 * @brief 示波器控制
 * @param[in] mavlink_control mavlink示波器控制结构体
 * @param[in] scope_struct 示波器结构体
 * @param[in] rw 0-read 1-write (read：上位机读取参数，write：上位机写入参数)
 * @note 该函数为回调函数，需要在mavlink_callback.c中调用
 */
void mavlink_scope_control_callback(mavlink_scopecontrol_t *mavlink_control,
                                    ScopeStruct *scope_struct, uint8_t rw) {
    if (rw == SCOPE_READ) {
        memset(mavlink_control, 0, sizeof(mavlink_scopecontrol_t));
        mavlink_control->control_word = scope_struct->control_word;
        mavlink_control->status_word = scope_struct->status_word;
        for (uint8_t i = 0; i < SCOPE_CHANNEL_NUM_MAX; i++) {
            mavlink_control->frame_num[i] = kScopeObject.channel_object[i]->package_count;
        }
    } else if (rw == SCOPE_WRITE) {
        if (mavlink_control->control_word != kNullControl) {
            scope_struct->control_word = mavlink_control->control_word;
            ControlWordWriteCallback(mavlink_control->control_word);
        }
    }
}

/**
 * @brief 通道数据获取
 * @param[in] mavlink_scope_data mavlink示波器数据结构体
 * @param[in] mavlink_control mavlink示波器控制结构体
 * @param[in] scope_struct 示波器结构体
 * @param[in] rw 0-read 1-write (read：上位机读取参数，write：上位机写入参数)
 * @note 该函数为回调函数，需要在mavlink_callback.c中调用
 */
void mavlink_get_scope_data_callback(mavlink_scopedata_t *mavlink_scope_data,
                                     mavlink_scopecontrol_t *mavlink_control,
                                     ScopeStruct *scope_struct, uint8_t rw) {
    if (rw == SCOPE_READ) {
        // frame_info 高16位-示波器通道，低16位-包索引（上位机通过设置这个参数，获取frame_data）
        uint16_t ch = mavlink_control->frame_info >> 16;
        uint16_t pack_index = mavlink_control->frame_info & 0xffff;

        // byte0:通道号(高字节)
        // byte1:通道号(低字节)
        // byte2:包索引(高字节)
        // byte3:包索引(低字节)
        // byte4:数据长度
        // byte5-byte7:保留0
        // byte8-byte127:示波器数据
        memset(mavlink_scope_data, 0, sizeof(mavlink_scopedata_t));
        mavlink_scope_data->frame_data[0] = ch >> 8;
        mavlink_scope_data->frame_data[1] = ch & 0xff;
        mavlink_scope_data->frame_data[2] = pack_index >> 8;
        mavlink_scope_data->frame_data[3] = pack_index & 0xff;
        ScopeChannelDataRead(ch, pack_index, &mavlink_scope_data->frame_data[4],
                                &mavlink_scope_data->frame_data[8]);
    }
}