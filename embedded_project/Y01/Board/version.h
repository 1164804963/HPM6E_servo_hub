#ifndef VERSION_H
#define VERSION_H

#ifdef __cplusplus
extern "C"
{
#endif

// 次版本号定义
#define V_CAN_CIA402            (0x00)  // 0：CAN CiA402 协议版本
#define V_CAN_ENCOS             (0x01)  // 1：CAN ENCOS 协议版本
#define V_CANOPEN_CIA402        (0x02)  // 2：CANopen CiA402 协议版本
#define V_ECAT_CIA402           (0x03)  // 3：EtherCAT CiA402 协议版本
#define V_CANFD_CUSTOM          (0x04)  // 4：CANFD 自定义协议版本

// 版本定义
#define MAJOR_VERSION           (0x03)              // 主版本号
#ifndef MINOR_VERSION           // 若工程编译选项或其他位置未定义次版本号，在此定义
#define MINOR_VERSION           (V_CAN_CIA402)      // 次版本号
#endif // MINOR_VERSION
#define REVISION_VERSION        (0x03)              // 修订号
#define BUILD_VERSION           (0x00)              // 构建号
#define VERSION_ENCODE (((MAJOR_VERSION) << 24) | ((MINOR_VERSION) << 16) | ((REVISION_VERSION) << 8) | (BUILD_VERSION))

// 定义功能开关控制宏
#define FC_CTRL_ON              (1)
#define FC_CTRL_OFF             (!(FC_CTRL_ON))

// 定义基于CAN透传开启MAVLink上位机调试功能
#define IS_USE_CAN_PASSTHROUGH  (FC_CTRL_OFF)

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

#if IS_USE_CAN_PASSTHROUGH == FC_CTRL_ON
#ifndef USE_CAN
#define USE_CAN
#endif /* USE_CAN */
#define USE_CAN_MAVLINK_HOST
#endif /* IS_USE_CAN_PASSTHROUGH */

#ifdef __cplusplus
}
#endif

#endif // VERSION_H
