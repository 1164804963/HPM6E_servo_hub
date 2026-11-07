#ifndef COORDINATE_CONVERSION_H
#define COORDINATE_CONVERSION_H

#ifdef __cplusplus
extern "C" {
#endif

#include "unit_conversion.h"

#pragma region //单位分子分母设置

void SetPosNumerator(uint32_t val);            // 设置位置单位分子
void SetPosDenominator(uint32_t val);          // 设置位置单位分母

void SetVelNumerator(uint32_t val);            // 设置速度单位分子
void SetVelDenominator(uint32_t val);          // 设置速度单位分母

void SetAccNumerator(uint32_t val);            // 设置加速度单位分子
void SetAccDenominator(uint32_t val);          // 设置加速度单位分母

void SetForceNumerator(uint32_t val);          // 设置力单位分子
void SetForceDenominator(uint32_t val);        // 设置力单位分母

void SetGearNumerator(uint32_t val);           // 设置齿轮比分子
void SetGearDenominator(uint32_t val);         // 设置齿轮比母子

#pragma endregion

#pragma region //极性设置

void SetPosPolarity(int8_t val);                // 设置位置极性
int8_t GetPosPolarity(void);                     // 获取位置极性

void SetVelPolarity(int8_t val);                // 设置速度极性
int8_t GetVelPolarity(void);                     // 获取速度极性

void SetTqPolarity(int8_t val);                 // 设置力矩极性
int8_t GetTqPolarity(void);                      // 获取力矩极性

void SetForcePolarity(int8_t val);              // 设置力极性
int8_t GetForcePolarity(void);                   // 获取力极性

#pragma endregion

#pragma region //标量单位转换

inline int64_t PosUnitUserToInternal(uint32_t val);    // 位置单位转换 用户转内部
inline uint32_t PosUnitInternalToUser(int64_t val);    // 位置单位转换 内部转用户

inline int64_t VelUnitUserToInternal(uint32_t val);    // 速度单位转换 用户转内部
inline uint32_t VelUnitInternalToUser(int64_t val);    // 速度单位转换 内部转用户

inline int64_t AccUnitUserToInternal(uint32_t val);    // 加速度单位转换 用户转内部
inline uint32_t AccUnitInternalToUser(int64_t val);    // 加速度单位转换 内部转用户`

inline uint32_t ForceUnitUserToInternal(uint32_t val); // 力单位转换 用户转内部
inline uint32_t ForceUnitInternalToUser(uint32_t val); // 力单位转换 内部转用户

#pragma endregion


#pragma region //坐标转换

inline int64_t PosCoordUserToInternal(int32_t val);    // 位置坐标转换 用户转内部
inline int32_t PosCoordInternalToUser(int64_t val);    // 位置坐标转换 内部转用户

inline int64_t VelCoordUserToInternal(int32_t val);    // 速度坐标转换 用户转内部
inline int32_t VelCoordInternalToUser(int64_t val);    // 速度坐标转换 内部转用户

inline int64_t TqCoordUserToInternal(int32_t val);     // 力矩坐标转换 用户转内部
inline int32_t TqCoordInternalToUser(int64_t val);     // 力矩坐标转换 内部转用户

inline int64_t ForceCoordUserToInternal(int32_t val);  // 力坐标转换 用户转内部
inline int32_t ForceCoordInternalToUser(int64_t val);  // 力坐标转换 内部转用户

#pragma endregion

#pragma region //其他数据转换

static inline int64_t PosUnitMotorToLoad(int64_t val) // 位置坐标转换 电机端转负载端
{
    int64_t pos_motor = val;
    int64_t pos_load = 0;

    conver_den_div_num(&pos_motor, &pos_load, E_GEAR_RATIO);

    return pos_load;
}

static inline int64_t PosUnitLoadToMotor(int64_t val)
{
    int64_t pos_motor = 0;
    int64_t pos_load = val;

    conver_num_div_den(&pos_load, &pos_motor, E_GEAR_RATIO);

    return pos_motor;
}

#pragma endregion
#ifdef __cplusplus
}
#endif

#endif // COORDINATE_CONVERSION_H
