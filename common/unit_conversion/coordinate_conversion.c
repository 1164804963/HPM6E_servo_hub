#include "coordinate_conversion.h"

static int8_t kPolarity[UNIT_CONVERSION_NUM] = {1, 1, 1, 1, 1};  // 极性默认值1

#pragma region //单位分子分母设置

// 设置位置单位分子
void SetPosNumerator(uint32_t val)
{
    set_numerator(val, E_POSITION_UNIT);
}

// 设置位置单位分母
void SetPosDenominator(uint32_t val)
{
    set_denominator(val, E_POSITION_UNIT);
}


// 设置速度单位分子
void SetVelNumerator(uint32_t val)
{
    set_numerator(val, E_VELOCITY_UNIT);
}

// 设置速度单位分母
void SetVelDenominator(uint32_t val)
{
    set_denominator(val, E_VELOCITY_UNIT);
}

// 设置加速度单位分子
void SetAccNumerator(uint32_t val)
{
    set_numerator(val, E_ACCELERATION_UNIT);
}

// 设置加速度单位分母
void SetAccDenominator(uint32_t val)
{
    set_denominator(val, E_ACCELERATION_UNIT);
}

// 设置力单位分子
void SetForceNumerator(uint32_t val)
{
    set_numerator(val, E_FORCE_UNIT);
}

// 设置力单位分母
void SetForceDenominator(uint32_t val)
{
    set_denominator(val, E_FORCE_UNIT);
}

// 设置齿轮比分子
void SetGearNumerator(uint32_t val)
{
    set_numerator(val, E_GEAR_RATIO);
}

// 设置齿轮比分母
void SetGearDenominator(uint32_t val)
{
    set_denominator(val, E_GEAR_RATIO);
}

#pragma endregion


#pragma region //标量单位转换

// 位置单位转换 用户转内部
inline int64_t PosUnitUserToInternal(uint32_t val)
{
    int64_t pos_user = val;
    int64_t pos_internal = 0;

    conver_num_div_den(&pos_user, &pos_internal, E_POSITION_UNIT);

    return pos_internal;
}

// 位置单位转换 内部转用户
inline uint32_t PosUnitInternalToUser(int64_t val)
{
    int64_t pos_internal = val;
    int64_t pos_user = 0;

    conver_den_div_num(&pos_internal, &pos_user, E_POSITION_UNIT);

    return pos_user;
}

// 速度单位转换 用户转内部
inline int64_t VelUnitUserToInternal(uint32_t val)
{
    int64_t vel_user = val;
    int64_t vel_internal = 0;

    conver_num_div_den(&vel_user, &vel_internal, E_VELOCITY_UNIT);

    return vel_internal;
}

// 速度单位转换 内部转用户
inline uint32_t VelUnitInternalToUser(int64_t val)
{
    int64_t vel_internal = val;
    int64_t vel_user = 0;

    conver_den_div_num(&vel_internal, &vel_user, E_VELOCITY_UNIT);

    return vel_user;
}

// 加速度单位转换 用户转内部
inline int64_t AccUnitUserToInternal(uint32_t val)
{
    int64_t acc_user = val;
    int64_t acc_internal = 0;

    conver_num_div_den(&acc_user, &acc_internal, E_ACCELERATION_UNIT);

    return acc_internal;
}

// 加速度单位转换 内部转用户
inline uint32_t AccUnitInternalToUser(int64_t val)
{
    int64_t acc_internal = val;
    int64_t acc_user = 0;

    conver_den_div_num(&acc_internal, &acc_user, E_ACCELERATION_UNIT);

    return acc_user;
}

// 力单位转换 用户转内部
inline uint32_t ForceUnitUserToInternal(uint32_t val)
{
    int64_t force_user = val;
    int64_t force_internal = 0;

    conver_num_div_den(&force_user, &force_internal, E_FORCE_UNIT);

    return force_internal;
}

// 力单位转换 内部转用户
inline uint32_t ForceUnitInternalToUser(uint32_t val)
{
    int64_t force_internal = val;
    int64_t force_user = 0;

    conver_den_div_num(&force_internal, &force_user, E_FORCE_UNIT);

    return force_user;
}

#pragma endregion


#pragma region //极性设置

// 设置位置极性
void SetPosPolarity(int8_t val)
{
    if (val == 1 || val == -1)
    {
        kPolarity[E_POSITION_UNIT] = val;
    }
}

// 获取位置极性
int8_t GetPosPolarity(void)
{
    return kPolarity[E_POSITION_UNIT];
}

// 设置速度极性
void SetVelPolarity(int8_t val)
{
    if (val == 1 || val == -1)
    {
        kPolarity[E_VELOCITY_UNIT] = val;
    }
}

// 获取速度极性
int8_t GetVelPolarity(void)
{
    return kPolarity[E_VELOCITY_UNIT];
}

// 设置力矩极性
void SetTqPolarity(int8_t val)
{
    if (val == 1 || val == -1)
    {
        kPolarity[E_TORQUE_UNIT] = val;
    }
}

// 获取力矩极性
int8_t GetTqPolarity(void)
{
    return kPolarity[E_TORQUE_UNIT];
}

// 设置力极性
void SetForcePolarity(int8_t val)
{
    if (val == 1 || val == -1)
    {
        kPolarity[E_FORCE_UNIT] = val;
    }
}

// 获取力极性
int8_t GetForcePolarity(void)
{
    return kPolarity[E_FORCE_UNIT];
}

#pragma endregion


#pragma region //坐标转换

// 位置坐标转换 用户转内部
inline int64_t PosCoordUserToInternal(int32_t val)
{
    int64_t pos_user = val * kPolarity[E_POSITION_UNIT];
    int64_t pos_internal = 0;

    conver_num_div_den(&pos_user, &pos_internal, E_POSITION_UNIT);

    return pos_internal;
}

// 位置坐标转换 内部转用户
inline int32_t PosCoordInternalToUser(int64_t val)
{
    int64_t pos_internal = val;
    int64_t pos_user = 0;

    conver_den_div_num(&pos_internal, &pos_user, E_POSITION_UNIT);

    return pos_user * kPolarity[E_POSITION_UNIT];
}

// 速度坐标转换 用户转内部
inline int64_t VelCoordUserToInternal(int32_t val)
{
    int64_t vel_user = val * kPolarity[E_VELOCITY_UNIT];
    int64_t vel_internal = 0;

    conver_num_div_den(&vel_user, &vel_internal, E_VELOCITY_UNIT);

    return vel_internal;
}

// 速度坐标转换 内部转用户
inline int32_t VelCoordInternalToUser(int64_t val)
{
    int64_t vel_internal = val;
    int64_t vel_user = 0;

    conver_den_div_num(&vel_internal, &vel_user, E_VELOCITY_UNIT);

    return vel_user * kPolarity[E_VELOCITY_UNIT];
}

// 力矩坐标转换 用户转内部
inline int64_t TqCoordUserToInternal(int32_t val)
{
    int64_t tq_user = val * kPolarity[E_TORQUE_UNIT];
    int64_t tq_internal = 0;

    conver_num_div_den(&tq_user, &tq_internal, E_TORQUE_UNIT);

    return tq_internal;
}

// 力矩坐标转换 内部转用户
inline int32_t TqCoordInternalToUser(int64_t val)
{
    int64_t tq_internal = val;
    int64_t tq_user = 0;

    conver_den_div_num(&tq_internal, &tq_user, E_TORQUE_UNIT);

    return tq_user * kPolarity[E_TORQUE_UNIT];
}

// 力坐标转换 用户转内部
inline int64_t ForceCoordUserToInternal(int32_t val)
{
    int64_t force_user = val * kPolarity[E_FORCE_UNIT];
    int64_t force_internal = 0;

    conver_num_div_den(&force_user, &force_internal, E_FORCE_UNIT);

    return force_internal;
}

// 力坐标转换 内部转用户
inline int32_t ForceCoordInternalToUser(int64_t val)
{
    int64_t force_internal = val;
    int64_t force_user = 0;

    conver_den_div_num(&force_internal, &force_user, E_FORCE_UNIT);

    return force_user * kPolarity[E_FORCE_UNIT];
}

#pragma endregion
