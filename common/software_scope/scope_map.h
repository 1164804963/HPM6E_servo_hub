#ifndef SCOPE_MAP_H
#define SCOPE_MAP_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    kTypeUint8 = 0,
    kTypeInt8,
    kTypeUint16,
    kTypeInt16,
    kTypeUint32,
    kTypeInt32,
    kTypeFloat32,
    kTypeFloat64,
    kTypeInt64,
    kTypeUint64
} ScopeDataType;

typedef struct {
    uint32_t index;
    void *pdata;
    uint32_t type;
} InterVarStruct;

extern const InterVarStruct kParamDataBase[417];

#ifdef __cplusplus
}
#endif

#endif
