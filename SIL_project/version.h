#ifndef VERSION_H
#define VERSION_H

#ifdef __cplusplus
extern "C"
{
#endif

// 次版本号定义
#define V_SIL                   (0xFF)  // 0xFF：SIL 协议版本

// 版本定义
#define MAJOR_VERSION           (0x02)              // 主版本号
#ifndef MINOR_VERSION           // 若工程编译选项或其他位置未定义次版本号，在此定义
#define MINOR_VERSION           (V_SIL)      // 次版本号
#endif // MINOR_VERSION
#define REVISION_VERSION        (0x02)              // 修订号
#define BUILD_VERSION           (0x02)              // 构建号
#define VERSION_ENCODE (((MAJOR_VERSION) << 24) | ((MINOR_VERSION) << 16) | ((REVISION_VERSION) << 8) | (BUILD_VERSION))


#ifdef __cplusplus
}
#endif

#endif // VERSION_H
