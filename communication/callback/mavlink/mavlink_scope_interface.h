#ifndef MAVLINK_SCOPE_INTERFACE_H
#define MAVLINK_SCOPE_INTERFACE_H

#include <stdint.h>

#include "mavlink.h"
#include "scope_app.h"
#include "scope_map.h"


#ifdef __cplusplus
extern "C" {
#endif

// 示波器mavlink回调函数
void mavlink_scope_config_callback(mavlink_scopeconfig_t *mavlink_config, ScopeStruct *scope_struct,
                                   uint8_t rw);
void mavlink_scope_control_callback(mavlink_scopecontrol_t *mavlink_control,
                                    ScopeStruct *scope_struct, uint8_t rw);
void mavlink_get_scope_data_callback(mavlink_scopedata_t *mavlink_scope_data,
                                     mavlink_scopecontrol_t *mavlink_control,
                                     ScopeStruct *scope_struct, uint8_t rw);

#ifdef __cplusplus
}
#endif

#endif
