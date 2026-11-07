/** @file
 *  @brief MAVLink comm protocol generated from servo_hub_database.xml
 *  @see http://mavlink.org
 */
#pragma once
#ifndef MAVLINK_SERVO_HUB_DATABASE_H
#define MAVLINK_SERVO_HUB_DATABASE_H

#ifndef MAVLINK_H
    #error Wrong include order: MAVLINK_SERVO_HUB_DATABASE.H MUST NOT BE DIRECTLY USED. Include mavlink.h from the same directory instead or set ALL AND EVERY defines from MAVLINK.H manually accordingly, including the #define MAVLINK_H call.
#endif

#define MAVLINK_SERVO_HUB_DATABASE_XML_HASH 9145254239802846172

#ifdef __cplusplus
extern "C" {
#endif

// MESSAGE LENGTHS AND CRCS

#ifndef MAVLINK_MESSAGE_LENGTHS
#define MAVLINK_MESSAGE_LENGTHS {}
#endif

#ifndef MAVLINK_MESSAGE_CRCS
#define MAVLINK_MESSAGE_CRCS {{76, 168, 32, 32, 3, 28, 29}, {77, 143, 3, 13, 3, 8, 9}, {30000, 43, 4, 4, 0, 0, 0}, {30001, 118, 60, 60, 0, 0, 0}, {30002, 47, 12, 12, 0, 0, 0}, {30003, 180, 21, 21, 0, 0, 0}, {30004, 72, 28, 28, 0, 0, 0}, {30005, 99, 5, 5, 0, 0, 0}, {30006, 65, 29, 29, 0, 0, 0}, {30007, 247, 4, 4, 0, 0, 0}, {30008, 3, 120, 120, 0, 0, 0}, {30009, 4, 4, 4, 0, 0, 0}, {30010, 37, 4, 4, 0, 0, 0}, {30011, 152, 16, 16, 0, 0, 0}, {30012, 238, 9, 9, 0, 0, 0}, {30013, 107, 8, 8, 0, 0, 0}, {30014, 199, 81, 81, 0, 0, 0}, {30015, 108, 40, 40, 0, 0, 0}, {30016, 104, 128, 128, 0, 0, 0}, {30017, 78, 48, 48, 0, 0, 0}, {30018, 96, 24, 24, 0, 0, 0}, {30019, 8, 44, 44, 0, 0, 0}, {30020, 51, 12, 12, 0, 0, 0}, {30021, 109, 46, 46, 0, 0, 0}, {30022, 124, 33, 33, 0, 0, 0}, {30023, 152, 2, 2, 0, 0, 0}, {30024, 38, 12, 12, 0, 0, 0}, {30025, 191, 53, 53, 0, 0, 0}, {30026, 84, 45, 45, 0, 0, 0}, {30027, 58, 32, 32, 0, 0, 0}, {30028, 125, 72, 72, 0, 0, 0}, {30029, 30, 8, 8, 0, 0, 0}, {30030, 82, 16, 16, 0, 0, 0}, {30031, 244, 4, 4, 0, 0, 0}, {30032, 112, 25, 25, 0, 0, 0}, {30033, 25, 18, 18, 0, 0, 0}, {30034, 156, 4, 4, 0, 0, 0}, {30035, 232, 8, 8, 0, 0, 0}, {30036, 197, 12, 12, 0, 0, 0}, {30037, 103, 10, 10, 0, 0, 0}, {30038, 107, 4, 4, 0, 0, 0}, {30039, 88, 21, 21, 0, 0, 0}, {30040, 160, 12, 12, 0, 0, 0}, {30041, 88, 8, 8, 0, 0, 0}, {30042, 5, 16, 16, 0, 0, 0}, {30043, 20, 13, 13, 0, 0, 0}, {30044, 152, 8, 8, 0, 0, 0}, {30045, 246, 10, 10, 0, 0, 0}, {30046, 37, 17, 17, 0, 0, 0}, {30047, 39, 15, 15, 0, 0, 0}, {30048, 127, 9, 9, 0, 0, 0}, {30049, 34, 8, 8, 0, 0, 0}, {30050, 152, 36, 36, 0, 0, 0}, {30051, 103, 17, 17, 0, 0, 0}, {30052, 90, 26, 26, 0, 0, 0}, {30053, 154, 20, 20, 0, 0, 0}, {30054, 108, 3, 3, 0, 0, 0}, {30055, 3, 46, 46, 0, 0, 0}, {30056, 26, 1, 1, 0, 0, 0}, {30057, 220, 44, 44, 0, 0, 0}, {30058, 81, 62, 62, 0, 0, 0}, {30059, 221, 95, 95, 0, 0, 0}, {30060, 34, 53, 53, 0, 0, 0}, {30061, 83, 131, 131, 0, 0, 0}, {30062, 162, 36, 36, 0, 0, 0}, {30063, 239, 52, 52, 0, 0, 0}, {30064, 51, 88, 88, 0, 0, 0}, {30065, 17, 32, 32, 0, 0, 0}, {30066, 147, 16, 16, 0, 0, 0}, {30067, 53, 4, 4, 0, 0, 0}, {30068, 134, 2, 2, 0, 0, 0}, {30069, 169, 1, 1, 0, 0, 0}, {30070, 215, 4, 4, 0, 0, 0}, {30071, 27, 13, 13, 0, 0, 0}, {30072, 228, 8, 8, 0, 0, 0}, {30073, 245, 2, 2, 0, 0, 0}, {30074, 59, 4, 4, 0, 0, 0}, {30075, 207, 2, 2, 0, 0, 0}, {30076, 1, 8, 8, 0, 0, 0}, {30077, 45, 1, 1, 0, 0, 0}, {30078, 158, 64, 64, 0, 0, 0}, {30079, 79, 16, 16, 0, 0, 0}, {30080, 88, 21, 21, 0, 0, 0}, {30081, 135, 80, 80, 0, 0, 0}, {30082, 218, 192, 192, 0, 0, 0}, {30083, 166, 80, 80, 0, 0, 0}, {30084, 74, 2, 2, 0, 0, 0}, {30085, 213, 2, 2, 0, 0, 0}, {30086, 77, 11, 11, 0, 0, 0}, {30087, 158, 7, 7, 0, 0, 0}, {30088, 118, 255, 255, 0, 0, 0}}
#endif

#include "../protocol.h"

#define MAVLINK_ENABLED_SERVO_HUB_DATABASE

// ENUM DEFINITIONS


/** @brief  */
#ifndef HAVE_ENUM_DRV_SYS_CMD
#define HAVE_ENUM_DRV_SYS_CMD
typedef enum DRV_SYS_CMD
{
   DRV_SYS_NOP=0, /* No operation | */
   DRV_SYS_HOMING=1, /* Homing | */
   DRV_SYS_SAVE_FLASH=2, /* Save flash | */
   DRV_SYS_RESET=3, /* System reset | */
   DRV_SYS_CLEAR_ERROR=4, /* Clear Error | */
   DRV_SYS_FACTORY_RESET=5, /* Factory reset | */
   DRV_SYS_CMD_ENUM_END=6, /*  | */
} DRV_SYS_CMD;
#endif

/** @brief Result from a MAVLink command (MAV_CMD) */
#ifndef HAVE_ENUM_MAV_RESULT
#define HAVE_ENUM_MAV_RESULT
typedef enum MAV_RESULT
{
   MAV_RESULT_ACCEPTED=0, /* Command is valid (is supported and has valid parameters), and was executed. | */
   MAV_RESULT_TEMPORARILY_REJECTED=1, /* Command is valid, but cannot be executed at this time. This is used to indicate a problem that should be fixed just by waiting (e.g. a state machine is busy, can't arm because have not got GPS lock, etc.). Retrying later should work. | */
   MAV_RESULT_DENIED=2, /* MAV_RESULT_DENIED | */
   MAV_RESULT_UNSUPPORTED=3, /* MAV_RESULT_UNSUPPORTED | */
   MAV_RESULT_FAILED=4, /* MAV_RESULT_FAILED | */
   MAV_RESULT_IN_PROGRESS=5, /* MAV_RESULT_IN_PROGRESS | */
   MAV_RESULT_COMMAND_LONG_ONLY=7, /* MAV_RESULT_COMMAND_LONG_ONLY | */
   MAV_RESULT_COMMAND_INT_ONLY=8, /* MAV_RESULT_COMMAND_INT_ONLY | */
   MAV_RESULT_ENUM_END=9, /*  | */
} MAV_RESULT;
#endif

/** @brief  */
#ifndef HAVE_ENUM_MAV_CMD
#define HAVE_ENUM_MAV_CMD
typedef enum MAV_CMD
{
   MAV_CMD_DRV_REQUEST_MESSAGE=20000, /* This is MAV_CMD_DRV_REQUEST_MESSAGE cmd. |Request the target to emit a specific message| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)|  */
   MAV_CMD_DRV_SYSTEM_CMD=20001, /* This is MAV_CMD_DRV_SYSTEM_CMD cmd. |Issue a generic system command (factory reset, etc.).| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)|  */
   MAV_CMD_ENUM_END=20002, /*  | */
} MAV_CMD;
#endif

// MAVLINK VERSION

#ifndef MAVLINK_VERSION
#define MAVLINK_VERSION 2
#endif

#if (MAVLINK_VERSION == 0)
#undef MAVLINK_VERSION
#define MAVLINK_VERSION 2
#endif

// MESSAGE DEFINITIONS
#include "./mavlink_msg_command_long.h"
#include "./mavlink_msg_command_ack.h"
#include "./mavlink_msg_read_param.h"
#include "./mavlink_msg_pmsmconfig.h"
#include "./mavlink_msg_elecidsininput.h"
#include "./mavlink_msg_elecidsinoutput.h"
#include "./mavlink_msg_elecidsinconfig.h"
#include "./mavlink_msg_mecidoutput.h"
#include "./mavlink_msg_mecidconfig.h"
#include "./mavlink_msg_notchfilterinput.h"
#include "./mavlink_msg_notchfilterinternal.h"
#include "./mavlink_msg_notchfilteroutput.h"
#include "./mavlink_msg_mecidinput.h"
#include "./mavlink_msg_inputshapinginput.h"
#include "./mavlink_msg_inputshapingconfig.h"
#include "./mavlink_msg_inputshapingoutput.h"
#include "./mavlink_msg_scopeconfig.h"
#include "./mavlink_msg_scopecontrol.h"
#include "./mavlink_msg_scopedata.h"
#include "./mavlink_msg_waveformdata.h"
#include "./mavlink_msg_waveformmap.h"
#include "./mavlink_msg_posspeedctlinput.h"
#include "./mavlink_msg_posspeedctloutput.h"
#include "./mavlink_msg_posspeedctlconfig.h"
#include "./mavlink_msg_motorctlsmconfig.h"
#include "./mavlink_msg_motorctlsminput.h"
#include "./mavlink_msg_motorctlsmoutput.h"
#include "./mavlink_msg_currentctlinput.h"
#include "./mavlink_msg_currentctlconfig.h"
#include "./mavlink_msg_currentctloutput.h"
#include "./mavlink_msg_notchfilterconfig.h"
#include "./mavlink_msg_speedobspllinput.h"
#include "./mavlink_msg_speedobspllconfig.h"
#include "./mavlink_msg_speedobsplloutput.h"
#include "./mavlink_msg_elecangleidconfig.h"
#include "./mavlink_msg_elecangleidoutput.h"
#include "./mavlink_msg_elecangleidinput.h"
#include "./mavlink_msg_directionidinput.h"
#include "./mavlink_msg_directionidconfig.h"
#include "./mavlink_msg_directionidoutput.h"
#include "./mavlink_msg_motorpossensorinput.h"
#include "./mavlink_msg_motorpossensorconfig.h"
#include "./mavlink_msg_motorpossensoroutput.h"
#include "./mavlink_msg_polepairsidinput.h"
#include "./mavlink_msg_polepairsidconfig.h"
#include "./mavlink_msg_polepairsidoutput.h"
#include "./mavlink_msg_nonvolatileparam.h"
#include "./mavlink_msg_systemconfig.h"
#include "./mavlink_msg_tqfcidinput.h"
#include "./mavlink_msg_tqfcidconfig.h"
#include "./mavlink_msg_tqfcidoutput.h"
#include "./mavlink_msg_objectdictionary.h"
#include "./mavlink_msg_reciprocalmotionconfig.h"
#include "./mavlink_msg_reciprocalmotionoutput.h"
#include "./mavlink_msg_referencesignalconfig.h"
#include "./mavlink_msg_referencesignaloutput.h"
#include "./mavlink_msg_appcontrolword.h"
#include "./mavlink_msg_appstatusinfo.h"
#include "./mavlink_msg_appopmode.h"
#include "./mavlink_msg_appencoderconfig.h"
#include "./mavlink_msg_appbaseconfig.h"
#include "./mavlink_msg_appmotionparam.h"
#include "./mavlink_msg_apprestrictparam.h"
#include "./mavlink_msg_appmotioninfo.h"
#include "./mavlink_msg_appwindowparam.h"
#include "./mavlink_msg_appmotorconfig.h"
#include "./mavlink_msg_appprotectconfig.h"
#include "./mavlink_msg_mitctlinput.h"
#include "./mavlink_msg_mitctlconfig.h"
#include "./mavlink_msg_mitctloutput.h"
#include "./mavlink_msg_apppermissionconfig.h"
#include "./mavlink_msg_systemcmd.h"
#include "./mavlink_msg_loadpossensorinput.h"
#include "./mavlink_msg_loadpossensorconfig.h"
#include "./mavlink_msg_loadpossensoroutput.h"
#include "./mavlink_msg_systemstatus.h"
#include "./mavlink_msg_encodercalibrationcmd.h"
#include "./mavlink_msg_encodercalibrationstatus.h"
#include "./mavlink_msg_custominfo.h"
#include "./mavlink_msg_heartbit.h"
#include "./mavlink_msg_historicalinfo.h"
#include "./mavlink_msg_simplantinput.h"
#include "./mavlink_msg_simplantoutput.h"
#include "./mavlink_msg_simplantconfig.h"
#include "./mavlink_msg_appdebugparam.h"
#include "./mavlink_msg_tabledata.h"
#include "./mavlink_msg_tableconfig.h"
#include "./mavlink_msg_appmavlinkconfig.h"
#include "./mavlink_msg_appfiletransferconfig.h"
#include "./mavlink_msg_appfwupgradeparam.h"
#include "./mavlink_msg_appfiletransferstream.h"

// base include



#if MAVLINK_SERVO_HUB_DATABASE_XML_HASH == MAVLINK_PRIMARY_XML_HASH
# define MAVLINK_MESSAGE_INFO {MAVLINK_MESSAGE_INFO_COMMAND_LONG, MAVLINK_MESSAGE_INFO_COMMAND_ACK, MAVLINK_MESSAGE_INFO_READ_PARAM, MAVLINK_MESSAGE_INFO_PmsmConfig, MAVLINK_MESSAGE_INFO_ElecIdSinInput, MAVLINK_MESSAGE_INFO_ElecIdSinOutput, MAVLINK_MESSAGE_INFO_ElecIdSinConfig, MAVLINK_MESSAGE_INFO_MecIdOutput, MAVLINK_MESSAGE_INFO_MecIdConfig, MAVLINK_MESSAGE_INFO_NotchFilterInput, MAVLINK_MESSAGE_INFO_NotchFilterInternal, MAVLINK_MESSAGE_INFO_NotchFilterOutput, MAVLINK_MESSAGE_INFO_MecIdInput, MAVLINK_MESSAGE_INFO_InputShapingInput, MAVLINK_MESSAGE_INFO_InputShapingConfig, MAVLINK_MESSAGE_INFO_InputShapingOutput, MAVLINK_MESSAGE_INFO_ScopeConfig, MAVLINK_MESSAGE_INFO_ScopeControl, MAVLINK_MESSAGE_INFO_ScopeData, MAVLINK_MESSAGE_INFO_WaveformData, MAVLINK_MESSAGE_INFO_WaveformMap, MAVLINK_MESSAGE_INFO_PosSpeedCtlInput, MAVLINK_MESSAGE_INFO_PosSpeedCtlOutput, MAVLINK_MESSAGE_INFO_PosSpeedCtlConfig, MAVLINK_MESSAGE_INFO_MotorCtlSmConfig, MAVLINK_MESSAGE_INFO_MotorCtlSmInput, MAVLINK_MESSAGE_INFO_MotorCtlSmOutput, MAVLINK_MESSAGE_INFO_CurrentCtlInput, MAVLINK_MESSAGE_INFO_CurrentCtlConfig, MAVLINK_MESSAGE_INFO_CurrentCtlOutput, MAVLINK_MESSAGE_INFO_NotchFilterConfig, MAVLINK_MESSAGE_INFO_SpeedObsPllInput, MAVLINK_MESSAGE_INFO_SpeedObsPllConfig, MAVLINK_MESSAGE_INFO_SpeedObsPllOutput, MAVLINK_MESSAGE_INFO_ElecAngleIdConfig, MAVLINK_MESSAGE_INFO_ElecAngleIdOutput, MAVLINK_MESSAGE_INFO_ElecAngleIdInput, MAVLINK_MESSAGE_INFO_DirectionIdInput, MAVLINK_MESSAGE_INFO_DirectionIdConfig, MAVLINK_MESSAGE_INFO_DirectionIdOutput, MAVLINK_MESSAGE_INFO_MotorPosSensorInput, MAVLINK_MESSAGE_INFO_MotorPosSensorConfig, MAVLINK_MESSAGE_INFO_MotorPosSensorOutput, MAVLINK_MESSAGE_INFO_PolePairsIdInput, MAVLINK_MESSAGE_INFO_PolePairsIdConfig, MAVLINK_MESSAGE_INFO_PolePairsIdOutput, MAVLINK_MESSAGE_INFO_NonVolatileParam, MAVLINK_MESSAGE_INFO_SystemConfig, MAVLINK_MESSAGE_INFO_TqFcIdInput, MAVLINK_MESSAGE_INFO_TqFcIdConfig, MAVLINK_MESSAGE_INFO_TqFcIdOutput, MAVLINK_MESSAGE_INFO_ObjectDictionary, MAVLINK_MESSAGE_INFO_ReciprocalMotionConfig, MAVLINK_MESSAGE_INFO_ReciprocalMotionOutput, MAVLINK_MESSAGE_INFO_ReferenceSignalConfig, MAVLINK_MESSAGE_INFO_ReferenceSignalOutput, MAVLINK_MESSAGE_INFO_AppControlWord, MAVLINK_MESSAGE_INFO_AppStatusInfo, MAVLINK_MESSAGE_INFO_AppOpMode, MAVLINK_MESSAGE_INFO_AppEncoderConfig, MAVLINK_MESSAGE_INFO_AppBaseConfig, MAVLINK_MESSAGE_INFO_AppMotionParam, MAVLINK_MESSAGE_INFO_AppRestrictParam, MAVLINK_MESSAGE_INFO_AppMotionInfo, MAVLINK_MESSAGE_INFO_AppWindowParam, MAVLINK_MESSAGE_INFO_AppMotorConfig, MAVLINK_MESSAGE_INFO_AppProtectConfig, MAVLINK_MESSAGE_INFO_MitCtlInput, MAVLINK_MESSAGE_INFO_MitCtlConfig, MAVLINK_MESSAGE_INFO_MitCtlOutput, MAVLINK_MESSAGE_INFO_AppPermissionConfig, MAVLINK_MESSAGE_INFO_SystemCmd, MAVLINK_MESSAGE_INFO_LoadPosSensorInput, MAVLINK_MESSAGE_INFO_LoadPosSensorConfig, MAVLINK_MESSAGE_INFO_LoadPosSensorOutput, MAVLINK_MESSAGE_INFO_SystemStatus, MAVLINK_MESSAGE_INFO_EncoderCalibrationCmd, MAVLINK_MESSAGE_INFO_EncoderCalibrationStatus, MAVLINK_MESSAGE_INFO_CustomInfo, MAVLINK_MESSAGE_INFO_HeartBit, MAVLINK_MESSAGE_INFO_HistoricalInfo, MAVLINK_MESSAGE_INFO_SimPlantInput, MAVLINK_MESSAGE_INFO_SimPlantOutput, MAVLINK_MESSAGE_INFO_SimPlantConfig, MAVLINK_MESSAGE_INFO_AppDebugParam, MAVLINK_MESSAGE_INFO_TableData, MAVLINK_MESSAGE_INFO_TableConfig, MAVLINK_MESSAGE_INFO_AppMavlinkConfig, MAVLINK_MESSAGE_INFO_AppFileTransferConfig, MAVLINK_MESSAGE_INFO_AppFwUpgradeParam, MAVLINK_MESSAGE_INFO_AppFileTransferStream}
# define MAVLINK_MESSAGE_NAMES {{ "AppBaseConfig", 30058 }, { "AppControlWord", 30054 }, { "AppDebugParam", 30082 }, { "AppEncoderConfig", 30057 }, { "AppFileTransferConfig", 30086 }, { "AppFileTransferStream", 30088 }, { "AppFwUpgradeParam", 30087 }, { "AppMavlinkConfig", 30085 }, { "AppMotionInfo", 30061 }, { "AppMotionParam", 30059 }, { "AppMotorConfig", 30063 }, { "AppOpMode", 30056 }, { "AppPermissionConfig", 30068 }, { "AppProtectConfig", 30064 }, { "AppRestrictParam", 30060 }, { "AppStatusInfo", 30055 }, { "AppWindowParam", 30062 }, { "COMMAND_ACK", 77 }, { "COMMAND_LONG", 76 }, { "CurrentCtlConfig", 30026 }, { "CurrentCtlInput", 30025 }, { "CurrentCtlOutput", 30027 }, { "CustomInfo", 30076 }, { "DirectionIdConfig", 30036 }, { "DirectionIdInput", 30035 }, { "DirectionIdOutput", 30037 }, { "ElecAngleIdConfig", 30032 }, { "ElecAngleIdInput", 30034 }, { "ElecAngleIdOutput", 30033 }, { "ElecIdSinConfig", 30004 }, { "ElecIdSinInput", 30002 }, { "ElecIdSinOutput", 30003 }, { "EncoderCalibrationCmd", 30074 }, { "EncoderCalibrationStatus", 30075 }, { "HeartBit", 30077 }, { "HistoricalInfo", 30078 }, { "InputShapingConfig", 30012 }, { "InputShapingInput", 30011 }, { "InputShapingOutput", 30013 }, { "LoadPosSensorConfig", 30071 }, { "LoadPosSensorInput", 30070 }, { "LoadPosSensorOutput", 30072 }, { "MecIdConfig", 30006 }, { "MecIdInput", 30010 }, { "MecIdOutput", 30005 }, { "MitCtlConfig", 30066 }, { "MitCtlInput", 30065 }, { "MitCtlOutput", 30067 }, { "MotorCtlSmConfig", 30022 }, { "MotorCtlSmInput", 30023 }, { "MotorCtlSmOutput", 30024 }, { "MotorPosSensorConfig", 30039 }, { "MotorPosSensorInput", 30038 }, { "MotorPosSensorOutput", 30040 }, { "NonVolatileParam", 30044 }, { "NotchFilterConfig", 30028 }, { "NotchFilterInput", 30007 }, { "NotchFilterInternal", 30008 }, { "NotchFilterOutput", 30009 }, { "ObjectDictionary", 30049 }, { "PmsmConfig", 30001 }, { "PolePairsIdConfig", 30042 }, { "PolePairsIdInput", 30041 }, { "PolePairsIdOutput", 30043 }, { "PosSpeedCtlConfig", 30021 }, { "PosSpeedCtlInput", 30019 }, { "PosSpeedCtlOutput", 30020 }, { "READ_PARAM", 30000 }, { "ReciprocalMotionConfig", 30050 }, { "ReciprocalMotionOutput", 30051 }, { "ReferenceSignalConfig", 30052 }, { "ReferenceSignalOutput", 30053 }, { "ScopeConfig", 30014 }, { "ScopeControl", 30015 }, { "ScopeData", 30016 }, { "SimPlantConfig", 30081 }, { "SimPlantInput", 30079 }, { "SimPlantOutput", 30080 }, { "SpeedObsPllConfig", 30030 }, { "SpeedObsPllInput", 30029 }, { "SpeedObsPllOutput", 30031 }, { "SystemCmd", 30069 }, { "SystemConfig", 30045 }, { "SystemStatus", 30073 }, { "TableConfig", 30084 }, { "TableData", 30083 }, { "TqFcIdConfig", 30047 }, { "TqFcIdInput", 30046 }, { "TqFcIdOutput", 30048 }, { "WaveformData", 30017 }, { "WaveformMap", 30018 }}
# if MAVLINK_COMMAND_24BIT
#  include "../mavlink_get_info.h"
# endif
#endif

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MAVLINK_SERVO_HUB_DATABASE_H
