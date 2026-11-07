#include "waveform_app.h"


uint32_t struct_index[WAVEFORM_CHANNEL_NUM];  //数据索引
uint32_t array_index[WAVEFORM_CHANNEL_NUM];   //数组子索引
uint32_t waveform_ch_default[6] = {
    (uint32_t)63<<16,\
    (uint32_t)38<<16, \
    ((uint32_t)103<<16) + 2, \
    ((uint32_t)15<<16) + 1, \
    ((uint32_t)15<<16) + 2, \
    (uint32_t)17<<16
};


/**
 * @brief 实时波形默认通道初始化
 * @param[in] waveform_map_info 实时波形数据通道映射
 */
void WaveformMapInit(int32_t *waveform_map_info) {
    //上电后映射默认通道参数
    for (uint8_t i = 0; i < WAVEFORM_CHANNEL_NUM; i++) {
        waveform_map_info[i] = waveform_ch_default[i];
    }

    set_waveform_map(waveform_map_info);
}


void set_waveform_map(int32_t *waveform_map_info) {
    for (uint32_t i = 0; i < (sizeof(kParamDataBase) / sizeof(kParamDataBase[0])); i++) {
        for (uint8_t j = 0; j < WAVEFORM_CHANNEL_NUM; j++) {
            if (kParamDataBase[i].index == (uint32_t)(waveform_map_info[j] >> 16)) {
                struct_index[j] = i;  //提取数据索引
                array_index[j] =
                    waveform_map_info[j] & 0xFFFF;  //提取数组子索引
            }
        }
    }
}


void get_waveform_map(int32_t *waveform_map_info) {
    for (uint8_t i = 0; i < WAVEFORM_CHANNEL_NUM; i++) {
        waveform_map_info[i] = kParamDataBase[struct_index[i]].index << 16 | array_index[i];
    }
}


void get_waveform_data(int64_t *waveform_data_array) {
    uint32_t array_index_temp = 0;

    for (uint8_t i = 0; i < WAVEFORM_CHANNEL_NUM; i++) {
        //单个变量的子索引是0，数组子索引(1-n)，访问数组成员时，索引要减一
        array_index_temp = 0;
        if(array_index[i] != 0){
            array_index_temp = array_index[i] - 1;
        }
        switch (kParamDataBase[struct_index[i]].type) {
            case kTypeUint8:
                waveform_data_array[i] =
                    *((uint8_t *)kParamDataBase[struct_index[i]].pdata + array_index_temp);
                break;
            case kTypeInt8:
                waveform_data_array[i] =
                    *((int8_t *)kParamDataBase[struct_index[i]].pdata + array_index_temp);
                break;
            case kTypeUint16:
                waveform_data_array[i] =
                    *((uint16_t *)kParamDataBase[struct_index[i]].pdata + array_index_temp);
                break;
            case kTypeInt16:
                waveform_data_array[i] =
                    *((int16_t *)kParamDataBase[struct_index[i]].pdata + array_index_temp);
                break;
            case kTypeUint32:
                waveform_data_array[i] =
                    *((uint32_t *)kParamDataBase[struct_index[i]].pdata + array_index_temp);
                break;
            case kTypeInt32:
                waveform_data_array[i] =
                    *((int32_t *)kParamDataBase[struct_index[i]].pdata + array_index_temp);
                break;
            case kTypeFloat32:
                waveform_data_array[i] =
                    *((uint32_t *)kParamDataBase[struct_index[i]].pdata + array_index_temp);
                break;
            case kTypeFloat64:
                waveform_data_array[i] =
                    *((uint64_t *)kParamDataBase[struct_index[i]].pdata + array_index_temp);
                break;
            case kTypeInt64:
                waveform_data_array[i] =
                    *((int64_t *)kParamDataBase[struct_index[i]].pdata + array_index_temp);
                break;
            case kTypeUint64:
                waveform_data_array[i] =
                    *((uint64_t *)kParamDataBase[struct_index[i]].pdata + array_index_temp);
                break;
        }
    }
}
