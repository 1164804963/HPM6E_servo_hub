#ifndef VERSION_H
#define VERSION_H

#ifdef __cplusplus
extern "C"
{
#endif

// 次版本号同时决定编译进哪些总线协议（与 Y01 板保持同一套约定）。
// 协议由 CMake SERVO_BUS 选择（ETHERCAT=3 / CAN_CIA402=0）；V_CONSOLE 仅用于独立测试或无总线 console fallback。
#define V_CAN_CIA402            (0x00)  // CAN CiA402 协议版本
#define V_CAN_ENCOS             (0x01)  // CAN ENCOS 协议版本
#define V_CANOPEN_CIA402        (0x02)  // CANopen CiA402 协议版本
#define V_ECAT_CIA402           (0x03)  // EtherCAT CiA402 协议版本
#define V_CANFD_CUSTOM          (0x04)  // CANFD 自定义协议版本
#define V_CONSOLE               (0xFF)  // 无总线协议，只用串口调试

// 版本定义
#define MAJOR_VERSION           (0x03)              // 主版本号
#ifndef MINOR_VERSION           // 若工程编译选项或其他位置未定义次版本号，在此定义
#define MINOR_VERSION           (V_CONSOLE)         // 次版本号
#endif // MINOR_VERSION
#define REVISION_VERSION        (0x00)              // 修订号
#define BUILD_VERSION           (0x00)              // 构建号
#define VERSION_ENCODE (((MAJOR_VERSION) << 24) | ((MINOR_VERSION) << 16) | ((REVISION_VERSION) << 8) | (BUILD_VERSION))

// 基于 CAN 透传开启 MAVLink 上位机调试
#define IS_USE_CAN_PASSTHROUGH  (0)

#if MINOR_VERSION == V_CAN_CIA402
#define USE_CAN
#define USE_CIA402
#endif /* V_CAN_CIA402 */

#if MINOR_VERSION == V_CAN_ENCOS
#define USE_CAN
#define USE_ENCOS
#endif /* V_CAN_ENCOS */

#if MINOR_VERSION == V_CANOPEN_CIA402
#define USE_CAN
#define USE_CANOPEN
#define USE_CIA402
#endif /* V_CANOPEN_CIA402 */

#if MINOR_VERSION == V_ECAT_CIA402
#define USE_ECAT
#define USE_CIA402
#endif /* V_ECAT_CIA402 */

#if MINOR_VERSION == V_CANFD_CUSTOM
#define USE_CAN
#define USE_CUSTOM
#endif /* V_CANFD_CUSTOM */

#ifdef __cplusplus
}
#endif

#endif // VERSION_H
