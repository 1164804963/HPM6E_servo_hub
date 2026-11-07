#include "app_motion_precondition.h"

MotionPrecondition_t kMotionPrecondition = {0};

/**
 * @brief 检查是否需要进入QuickStop保护模式（Float）
 * @param[in] negative_limit 负限位状态
 * @param[in] positive_limit 正限位状态
 * @param[in] target_val 目标值
 * @param[in] check_val 检查值
 * @retval false 无需进入QuickStop保护模式
 * @retval true 需要进入QuickStop保护模式
 */
inline static bool IsLimitForFloat(bool const negative_limit, bool const positive_limit, \
                                   float const target_val, float const check_val)
{
    if ((negative_limit && target_val > check_val) || \
        (positive_limit && target_val < check_val))
    {
        return false;
    }
    return true;
}

/**
 * @brief 检查是否需要进入QuickStop保护模式（Int64）
 * @param[in] negative_limit 负限位状态
 * @param[in] positive_limit 正限位状态
 * @param[in] target_val 目标位置
 * @param[in] check_val 当前位置
 * @retval false 无需进入QuickStop保护模式
 * @retval true 需要进入QuickStop保护模式
 */
inline static bool IsLimitForInt64(bool const negative_limit, bool const positive_limit, \
                                   int64_t const target_val, int64_t const check_val)
{
    if ((negative_limit && target_val > check_val) || \
        (positive_limit && target_val < check_val))
    {
        return false;
    }
    return true;
}

/**
 * @brief 运动限位检查初始化函数
 * @param[in] limit 限位检查结构体指针
 * @note  应在应用启动时调用本函数以初始化限位检查状态。
 */
static void MotionLimitCheckInit(LimitCheck_t *limit)
{
    limit->status.all = 0;
    limit->warning = app_set_check_warning_val();

    limit->di_io_now.all = 0;
    limit->pos_actual_val = 0;
    limit->pos_soft_negative = get_app_Software_position_limit_Minimal_position_limit();
    limit->pos_soft_positive = get_app_Software_position_limit_Maximal_position_limit();
}

/**
 * @brief 运动限位检查运行函数
 * @param[in] limit 限位检查结构体指针
 * @retval false 限位无需进入QuickStop保护模式
 * @retval true 限位需要进入QuickStop保护模式
 */
static bool MotionLimitCheckRun(LimitCheck_t *limit)
{
    bool quickstop = false;

    if (get_app_Position_limit_enable())
    {
        //TODO: 暂不考虑运动极性
        // 硬件限位状态检查
        limit->di_io_now.all = get_app_Digital_io_inputs_status();
        limit->status.bits.hw_negative = limit->di_io_now.bits.negative_limit_switch;
        limit->status.bits.hw_positive = limit->di_io_now.bits.positive_limit_switch;
        // 硬件限位同时触发，报错
        if (limit->status.bits.hw_negative && limit->status.bits.hw_positive)
        {
            sys_set_bsp_error_state(ERROR_LIMIT_SWITCH, ERROR_SET);
            return true;
        }

        // 软件限位状态检查
        limit->pos_actual_val = get_app_Position_actual_value();
        limit->pos_soft_negative = get_app_Software_position_limit_Minimal_position_limit();
        limit->pos_soft_positive = get_app_Software_position_limit_Maximal_position_limit();
        limit->status.bits.soft_negative = (limit->pos_actual_val < limit->pos_soft_negative ? true : false);
        limit->status.bits.soft_positive = (limit->pos_actual_val > limit->pos_soft_positive ? true : false);

        // 限位警告统一处理
        if (limit->warning != NULL)
        {
            limit->warning->bits.hardware_limit_negative = limit->status.bits.hw_negative;
            limit->warning->bits.hardware_limit_positive = limit->status.bits.hw_positive;
            limit->warning->bits.software_limit_negative = limit->status.bits.soft_negative;
            limit->warning->bits.software_limit_positive = limit->status.bits.soft_positive;
        }

        // 软、硬件限位状态合并
        limit->status.bits.negative = (limit->status.bits.hw_negative || limit->status.bits.soft_negative) ? true : false;
        limit->status.bits.positive = (limit->status.bits.hw_positive || limit->status.bits.soft_positive) ? true : false;

        // 运动趋势判断是否需要QuickStop保护
        if (limit->status.all)
        {
            switch (get_app_Modes_of_operation_display())
            {
            case MOTOR_CTL_SM_MODE_TORQUE:
                quickstop = IsLimitForFloat(limit->status.bits.negative, limit->status.bits.positive, \
                                            get_app_Target_torque(), 0.0f);
                break;
            case MOTOR_CTL_SM_MODE_SPEED:
                quickstop = IsLimitForFloat(limit->status.bits.negative, limit->status.bits.positive, \
                                            get_app_Target_velocity(), 0.0f);
                break;
            case MOTOR_CTL_SM_MODE_POSITION:
                quickstop = IsLimitForInt64(limit->status.bits.negative, limit->status.bits.positive, \
                                            get_app_Target_position(), limit->pos_actual_val);
                break;
            case MOTOR_CTL_SM_MODE_HOMING:
                //只检查软件限位，硬件限位参与回零过程
                quickstop = (limit->status.bits.soft_negative || limit->status.bits.soft_positive) ? true : false;
                if (limit->warning != NULL)
                {
                    limit->warning->bits.hardware_limit_negative = false;
                    limit->warning->bits.hardware_limit_positive = false;
                }
                break;
            // ...
            default: // 无需处理模式则直接进入QuickStop保护模式
                quickstop = true;
                break;
            }
        }
    }
    else
    {
        limit->status.all = 0;
    }

    return quickstop;
}

/**
 * @brief 初始化运动前条件检查
 * @note  应在应用启动时调用本函数以初始化运动前条件检查状态。
 */
void AppMotionPreConditionInit(void)
{
    kMotionPrecondition.emergency_brake_requested = false;
    MotionLimitCheckInit(&kMotionPrecondition.limit);
}

/**
 * @brief 运行运动前条件检查
 * @note  应位置环周期性调用本函数以监测和更新运动前条件检查状态。
 */
void AppMotionPreConditionRun(void)
{
    // 运行限位检查
    kMotionPrecondition.emergency_brake_requested = MotionLimitCheckRun(&kMotionPrecondition.limit);
    set_app_Emergency_brake_requested(kMotionPrecondition.emergency_brake_requested);
}
