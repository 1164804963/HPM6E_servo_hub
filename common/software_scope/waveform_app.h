#ifndef WAVEFORM_APP_H
#define WAVEFORM_APP_H

#include "scope_map.h"

// 实时波形通道数量
#define WAVEFORM_CHANNEL_NUM 6

void WaveformMapInit(int32_t *waveform_map_info);
void set_waveform_map(int32_t *waveform_map_info);
void get_waveform_map(int32_t *waveform_map_info);
void get_waveform_data(int64_t *waveform_data_array);

#endif
