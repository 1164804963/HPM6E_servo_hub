#include "app_status_check.h"
#include "motor_ctl_loop.h"

static Axis *const axis = &kAxis; // 引用电机对象实例化
AppCheckVal kAppCheck =
{
    .di_io.all = 0,
    .error.all = 0,
    .warning.all = 0,
    .status.all = 0,
    .p_bsp_error = NULL,
    .scan_ring_num = 0,
    .error_record_latch_flag = false,
    .error_record_addr = NULL,
    .pre_ctrl_word = APP_CTRL_DISABLE,
    .now_ctrl_word = APP_CTRL_DISABLE,
    .dt = 0,
    .dt_1ms = 0,
    .idq_now = {0, 0},
    .idq_squared_now = 0,
    .i_rated_squared = 0,
    .i_peak_squared_threshold = 0,
    .overload_heat_threshold_now = 0,
    .drive_heat_now = 0,
    .drive_temp_now = 0,
    .motor_temp_now = 0,
    .mcu_temp_now = 0,
    .motor_rpm_now = 0,
    .load_rpm_now = 0,
    .pos_error_now = 0,
    .pos_diff_now = 0,
    .vel_diff_now = 0,
    .trq_diff_now = 0,
    .over_current_threshold = 0,
    .iabc_now = {0, 0, 0},
    .can_mg_counts_now = 0,
    .can_mg_counts_last = 0,
};



// 内部错误检测函数声明
static inline bool AppDriveOverPeakCurrentErrorCheck(void);
static inline bool AppDriveOverloadErrorCheck(void);
static inline bool AppDCLinkOverVoltageErrorCheck(void);
static inline bool AppDCLinkUnderVoltageErrorCheck(void);
static inline bool AppExcessTemperatureDriveErrorCheck(void);
static inline bool AppTooLowTemperatureDriveErrorCheck(void);
static inline bool AppOverSpeedErrorCheck(void);
static inline bool AppPositionFollowingErrorCheck(void);
static inline bool AppLoadEncoderErrorCheck(void);
static inline bool AppMotorEncoderErrorCheck(void);
static inline bool AppFlashStoreErrorCheck(void);
static inline bool AppDrvInitErrorCheck(void);
static inline bool AppCurrentSampleErrorCheck(void);
static inline bool AppNfaultErrorCheck(void);
static inline bool AppDriverOverCurrentErrorCheck(void);
static inline bool AppBusVoltageErrorCheck(void);
static inline bool AppCanBusDisconnectionErrorCheck(void);
static inline bool AppExcessTemperatureMotorErrorCheck(void);
static inline bool AppTooLowTemperatureMotorErrorCheck(void);
static inline bool AppExcessTemperatureMcuErrorCheck(void);
static inline bool AppTooLowTemperatureMcuErrorCheck(void);
static inline bool AppExternalInhibitInputDetectedErrorCheck(void);

// 错误检测函数数组注册
static const CheckFunctionList CheckTable[] =
{
    {AppDriveOverPeakCurrentErrorCheck, false},
    {AppDriveOverloadErrorCheck, false},
    {AppDCLinkOverVoltageErrorCheck, true},
    {AppDCLinkUnderVoltageErrorCheck, false},
    {AppExcessTemperatureDriveErrorCheck, false},
    {AppTooLowTemperatureDriveErrorCheck, false},
    {AppOverSpeedErrorCheck, false},
    {AppPositionFollowingErrorCheck, false},

    {AppLoadEncoderErrorCheck, true},
    {AppMotorEncoderErrorCheck, true},
    {AppFlashStoreErrorCheck, true},
    {AppDrvInitErrorCheck, true},
    {AppCurrentSampleErrorCheck, true},
    {AppNfaultErrorCheck, true},
    {AppDriverOverCurrentErrorCheck, true},
    {AppBusVoltageErrorCheck, true},

    {AppCanBusDisconnectionErrorCheck, false},
    {AppExcessTemperatureMotorErrorCheck, false},
    {AppTooLowTemperatureMotorErrorCheck, false},
    {AppExcessTemperatureMcuErrorCheck, false},
    {AppTooLowTemperatureMcuErrorCheck, false},
    {AppExternalInhibitInputDetectedErrorCheck, true},
};

#pragma region 错误检测函数定义
static inline bool AppLoadEncoderErrorCheck(void)
{
    return kAppCheck.p_bsp_error->bit_band.error_encoder_load;
}
static inline bool AppMotorEncoderErrorCheck(void)
{
    return kAppCheck.p_bsp_error->bit_band.error_encoder_motor;
}

static inline bool AppFlashStoreErrorCheck(void)
{
    return kAppCheck.p_bsp_error->bit_band.error_flash_store;
}

static inline bool AppDrvInitErrorCheck(void)
{
    return kAppCheck.p_bsp_error->bit_band.error_drv_init;
}

static inline bool AppCurrentSampleErrorCheck(void)
{
    return kAppCheck.p_bsp_error->bit_band.error_current_sample;
}

static inline bool AppNfaultErrorCheck(void)
{
    return kAppCheck.p_bsp_error->bit_band.error_nfault;
}

static inline bool AppBusVoltageErrorCheck(void)
{
    return kAppCheck.p_bsp_error->bit_band.error_bus_voltage;
}

static inline bool AppExternalInhibitInputDetectedErrorCheck(void)
{
    return kAppCheck.p_bsp_error->bit_band.error_limit_switch;
}

/**
 * @brief 检查驱动电流是否超过峰值电流阈值，并处理错误状态及冷却时间。
 *
 * 该函数用于检测实际电流矢量是否超过峰值电流的90%阈值（i_peak * 0.9），
 * 若超过则开始计时，持续超过设定时长则返回错误并启动冷却时间（30秒）。
 * 在冷却时间内持续返回错误，冷却时间结束后恢复正常。
 *
 * @return true  如果检测到峰值电流错误或处于冷却时间内
 * @return false 正常，无峰值电流错误
 */
static inline bool AppDriveOverPeakCurrentErrorCheck(void)
{
    static float time_count[2] = {0, 0};

    // 超过峰值电流阈值，计时
    if (kAppCheck.idq_squared_now > kAppCheck.i_peak_squared_threshold)
    {
        time_count[0] += kAppCheck.dt_1ms;
        if (time_count[0] >= get_app_Drive_peak_current_duration())
        {
            time_count[0] = get_app_Drive_peak_current_duration();
            time_count[1] = DRIVE_OVER_PEAK_COOLING_TIME; // 启用冷却时间30秒
            return true;
        }
    }
    else
    {
        time_count[0] = 0;
    }

    // 冷却时间未结束，持续报错
    if (time_count[1] > 0)
    {
        time_count[1] -= kAppCheck.dt_1ms; // 冷却中
        return true;
    }

    return false;
}

/**
 * @brief 检查驱动器是否发生过载错误。
 *
 * 此函数通过累积电流的热量积分，判断驱动器是否达到过载阈值。
 * 具体做法是计算实际d轴和q轴电流的平方和，并与电机额定电流的平方做差，
 * 按时间步长累加到热量变量heat中。当heat超过过载热量阈值时，判定为过载错误。
 *
 * @return 如果发生过载错误，返回true；否则返回false。
 *
 * @note
 * - heat为静态变量，记录累计热量。
 * - 当heat小于0时会被重置为0。
 * - 当heat超过阈值时会被限制在阈值，并返回过载错误。
 * - 会调用set_app_Drive_accumulated_heat()设置累计热量。
 */
static inline bool AppDriveOverloadErrorCheck(void)
{
    kAppCheck.overload_heat_threshold_now = kAppCheck.i_rated_squared * get_app_Drive_overload_current_duration();
    kAppCheck.drive_heat_now += (kAppCheck.idq_squared_now - kAppCheck.i_rated_squared) * kAppCheck.dt_1ms;
    if (kAppCheck.drive_heat_now < 0)
    {
        kAppCheck.drive_heat_now = 0;
    }
    set_app_Drive_accumulated_heat(kAppCheck.drive_heat_now);

    if (kAppCheck.drive_heat_now >= kAppCheck.overload_heat_threshold_now)
    {
        kAppCheck.drive_heat_now = kAppCheck.overload_heat_threshold_now;
        return true;
    }
    return false;
}

/**
 * @brief 检查直流母线电压是否过高。
 * @return 如果检测到直流母线过压错误，返回 true；否则返回 false。
 */
static inline bool AppDCLinkOverVoltageErrorCheck(void)
{
    if (get_app_DC_link_circuit_voltage() > get_app_Bus_over_voltage_threshold())
    {
        return true;
    }
    return false;
}

/**
 * @brief 检查直流母线电压是否低于欠压阈值，并判断是否产生欠压错误。
 *
 * 此函数会持续检测直流母线电压，如果电压低于欠压阈值，则会累积低电压持续时间。
 * 当累计时间达到或超过 0.2 秒时，返回 true，表示发生欠压错误。
 * 如果电压恢复正常，则累计时间清零。
 *
 * @return 如果检测到直流母线欠压错误，返回 true；否则返回 false。
 */
static inline bool AppDCLinkUnderVoltageErrorCheck(void)
{
    static float time_count = 0;

    if (get_app_DC_link_circuit_voltage() < get_app_Bus_under_voltage_threshold())
    {
        time_count += kAppCheck.dt_1ms;
        if (time_count >= DC_BUS_UNDER_VOLTAGE_CHECK_TIME)
        {
            time_count = DC_BUS_UNDER_VOLTAGE_CHECK_TIME;
            return true;
        }
    }
    else
    {
        time_count = 0;
    }
    return false;
}

/**
 * @brief 检查驱动器是否因温度过高而产生故障。
 *
 * 此函数会持续检测驱动器温度是否超过高温故障阈值。
 * 如果温度超过阈值，并且持续时间超过设定的阈值时间，则返回true，表示发生过温故障。
 * 如果温度未超过阈值，则计时器重置为0。
 *
 * @return 如果检测到过温故障，返回true；否则返回false。
 */
static inline bool AppExcessTemperatureDriveErrorCheck(void)
{
    static float time_count = 0;

    if (kAppCheck.drive_temp_now > get_app_Drive_high_temperature_warning_threshold()) // 警告
    {
        kAppCheck.warning.bits.over_temperature_drive = true;
    }
    else
    {
        kAppCheck.warning.bits.over_temperature_drive = false;
    }

    if (kAppCheck.drive_temp_now > get_app_Drive_high_temperature_fault_threshold())
    {
        time_count += kAppCheck.dt_1ms;
        if (time_count >= get_app_Drive_temperature_threshold_time())
        {
            time_count = get_app_Drive_temperature_threshold_time();
            return true;
        }
    }
    else
    {
        time_count = 0;
    }
    return false;
}

/**
 * @brief 检查驱动器温度是否过低并产生错误。
 *
 * 此函数用于检测驱动器的温度是否低于设定的故障阈值，并在温度低于阈值持续一段设定时间后返回错误。
 * 如果温度恢复正常，则计时器会被重置。
 *
 * @return 如果检测到温度过低且持续时间超过阈值，返回true，否则返回false。
 */
static inline bool AppTooLowTemperatureDriveErrorCheck(void)
{
    static float time_count = 0;

    if (kAppCheck.drive_temp_now < get_app_Drive_low_temperature_warning_threshold()) // 警告
    {
        kAppCheck.warning.bits.under_temperature_drive = true;
    }
    else
    {
        kAppCheck.warning.bits.under_temperature_drive = false;
    }

    if (kAppCheck.drive_temp_now < get_app_Drive_low_temperature_fault_threshold())
    {
        time_count += kAppCheck.dt_1ms;
        if (time_count >= get_app_Drive_temperature_threshold_time())
        {
            time_count = get_app_Drive_temperature_threshold_time();
            return true;
        }
    }
    else
    {
        time_count = 0;
    }
    return false;
}

/**
 * @brief 检查当前速度是否超过超速阈值。
 *
 * 此函数获取当前速度和超速阈值，并判断当前速度（绝对值）是否超过超速阈值。
 *
 * @return 如果当前速度超过超速阈值，返回 true；否则返回 false。
 */
static inline bool AppOverSpeedErrorCheck(void)
{
    kAppCheck.motor_rpm_now = get_app_Motor_velocity_actual_value();
    if (MATH_ABS(kAppCheck.motor_rpm_now) > get_app_Overspeed_threshold())
    {
        return true;
    }
    return false;
}

/**
 * @brief 位置误差持续超过设定时间
 * @return 如果位置误差持续超过设定时间，返回true；否则返回false。
 */
static inline bool AppPositionFollowingErrorCheck(void)
{
    static float time_count = 0;

    // 处于使能状态且处于位置模式
    if ((axis->motor_ctl_sm_output.state != MOTOR_CTL_SM_STATE_ENABLE) ||
        (axis->motor_ctl_sm_config.mode != MOTOR_CTL_SM_MODE_POSITION))
    {
        return false;
    }

    kAppCheck.pos_error_now = get_app_Following_error_actual_value();
    if (MATH_ABS(kAppCheck.pos_error_now) > get_app_Following_error_window())
    {
        time_count += kAppCheck.dt_1ms;
        if (time_count >= get_app_Following_error_time_out())
        {
            time_count = get_app_Following_error_time_out();
            return true;
        }
    }
    else
    {
        time_count = 0;
    }
    return false;
}

/**
 * @brief 检查三相电流任意一相电流是否产生了过流错误。
 *
 * @return  ，返回 true；否则返回 false。
 */
static inline bool AppDriverOverCurrentErrorCheck(void)
{

    kAppCheck.iabc_now[0] = get_app_U_current_actual_value(); // 获取当前三相电流
    kAppCheck.iabc_now[1] = get_app_V_current_actual_value(); // 获取当前三相电流
    kAppCheck.iabc_now[2] = get_app_W_current_actual_value(); // 获取当前三相电流
    kAppCheck.over_current_threshold = get_app_Drive_overcurrent_threshold();

    if (MATH_ABS(kAppCheck.iabc_now[0]) > kAppCheck.over_current_threshold ||
        MATH_ABS(kAppCheck.iabc_now[1]) > kAppCheck.over_current_threshold ||
        MATH_ABS(kAppCheck.iabc_now[2]) > kAppCheck.over_current_threshold)
    {
        return true;
    }
    return false;
}

/**
 * @brief 检查CAN总线掉线错误
 *
 * 从接收到 第一条CAN消息开始 进行消息记录，默认0.5s没有接收到新的CAN消息则报错
 *
 * @return 掉线，返回 true；否则返回 false。
 */
static inline bool AppCanBusDisconnectionErrorCheck(void)
{
    static float time_count = 0;

    kAppCheck.can_mg_counts_now = bsp_get_can_mg_counts();

    if (0 == kAppCheck.can_mg_counts_now && 0 == kAppCheck.can_mg_counts_last) // 未接受到CAN消息
    {
        kAppCheck.can_mg_counts_last = kAppCheck.can_mg_counts_now;
        return false;
    }
    if (kAppCheck.can_mg_counts_last == kAppCheck.can_mg_counts_now) // 没有接收到 新的CAN消息 累计记录时间
    {
        time_count += kAppCheck.dt_1ms;
        if (time_count >= get_app_Can_timeout()) // 超时报错
        {
            time_count = get_app_Can_timeout();
            return true;
        }
    }
    else
    {
        time_count = 0.0f;
    }
    kAppCheck.can_mg_counts_last = kAppCheck.can_mg_counts_now;
    return false;
}

/**
 * @brief 电机温度过高检测
 *
 *
 * @return 过温，返回 true；否则返回 false。
 */
static inline bool AppExcessTemperatureMotorErrorCheck(void)
{
    if (kAppCheck.motor_temp_now > MOTOR_NTC_FAULT_C) // NTC警告
    {
        kAppCheck.warning.bits.motor_temperature_ntc = true;
        return false; //非正常温度值，不再检测错误
    }

    if (kAppCheck.motor_temp_now > get_app_Motor_high_temperature_warning_threshold()) // 警告
    {
        kAppCheck.warning.bits.over_temperature_motor = true;
    }
    else
    {
        kAppCheck.warning.bits.over_temperature_motor = false;
    }

    if (kAppCheck.motor_temp_now > get_app_Motor_high_temperature_fault_threshold()) // 错误
    {
        return true;
    }

    return false;
}

/**
 * @brief  电机温度过低检测
 *
 *
 *
 * @return 欠温，返回 true；否则返回 false。
 */
static inline bool AppTooLowTemperatureMotorErrorCheck(void)
{
    if (kAppCheck.motor_temp_now > MOTOR_NTC_FAULT_C) // NTC警告
    {
        kAppCheck.warning.bits.motor_temperature_ntc = true;
        return false; //非正常温度值，不再检测错误
    }

    if (kAppCheck.motor_temp_now < get_app_Motor_low_temperature_warning_threshold()) // 警告
    {
        kAppCheck.warning.bits.under_temperature_motor = true;
    }
    else
    {
        kAppCheck.warning.bits.under_temperature_motor = false;
    }

    if (kAppCheck.motor_temp_now < get_app_Motor_low_temperature_fault_threshold()) // 错误
    {
        return true;
    }

    return false;
}

/**
 * @brief 检查mcu是否因温度过高而产生故障。
 *
 * 此函数会持续检测mcu温度是否超过高温故障阈值。
 * 如果温度超过阈值，并且持续时间超过设定的阈值时间，则返回true，表示发生过温故障。
 * 如果温度未超过阈值，则计时器重置为0。
 *
 * @return 如果检测到过温故障，返回true；否则返回false。
 */
static inline bool AppExcessTemperatureMcuErrorCheck(void)
{
    static float time_count = 0;

    if (kAppCheck.mcu_temp_now > get_app_Mcu_high_temperature_warning_threshold()) // 警告
    {
        kAppCheck.warning.bits.over_temperature_mcu = true;
    }
    else
    {
        kAppCheck.warning.bits.over_temperature_mcu = false;
    }
    if (kAppCheck.mcu_temp_now > get_app_Mcu_high_temperature_fault_threshold())
    {
        time_count += kAppCheck.dt_1ms;
        if (time_count >= get_app_Mcu_temperature_threshold_time())
        {
            time_count = get_app_Mcu_temperature_threshold_time();
            return true;
        }
    }
    else
    {
        time_count = 0;
    }
    return false;
}

/**
 * @brief 检查mcu温度是否过低并产生错误。
 *
 * 此函数用于检测mcu的温度是否低于设定的故障阈值，并在温度低于阈值持续一段设定时间后返回错误。
 * 如果温度恢复正常，则计时器会被重置。
 *
 * @return 如果检测到温度过低且持续时间超过阈值，返回true，否则返回false。
 */
static inline bool AppTooLowTemperatureMcuErrorCheck(void)
{
    static float time_count = 0;

    if (kAppCheck.mcu_temp_now < get_app_Mcu_low_temperature_warning_threshold()) // 警告
    {
        kAppCheck.warning.bits.under_temperature_mcu = true;
    }
    else
    {
        kAppCheck.warning.bits.under_temperature_mcu = false;
    }

    if (kAppCheck.mcu_temp_now < get_app_Mcu_low_temperature_fault_threshold())
    {
        time_count += kAppCheck.dt_1ms;
        if (time_count >= get_app_Mcu_temperature_threshold_time())
        {
            time_count = get_app_Mcu_temperature_threshold_time();
            return true;
        }
    }
    else
    {
        time_count = 0;
    }
    return false;
}

#pragma endregion

#pragma region 状态检测函数定义
bool AppMotorEnableStateCheck(void)
{
    // 同步控制层的使能状态
    if (axis->motor_ctl_sm_output.state == MOTOR_CTL_SM_STATE_ENABLE)
    {
        kAppCheck.status.bits.motor_enable_state = true;
        return true;
    }
    kAppCheck.status.bits.motor_enable_state = false;
    return false;
}

/**
 * @brief 检查目标是否已到达状态
 *
 * 此函数用于判断当前速度是否低于设定的速度阈值，并在持续低于该阈值一段设定时间后，
 * 返回true表示目标已到达。否则返回false。若速度高于阈值，则计时器重置。
 *
 * @return 如果目标到达状态返回true，否则返回false。
 */
bool AppTargetReachedStateCheck(void)
{
    // 控制字暂停，所有模式均检测速度是否为0,更新目标到达状态
    kAppCheck.status.bits.target_reached = kAppCheck.status.bits.velocity_zero;

    return kAppCheck.status.bits.target_reached;
}

/**
 * @brief 检查速度是否为零状态
 *
 * 此函数用于判断当前速度是否低于设定的速度阈值，并在持续低于该阈值一段设定时间后，
 * 返回true表示速度为零。否则返回false。若速度高于阈值，则计时器重置。
 *
 * @return 如果速度为零状态返回true，否则返回false。
 */
bool AppVelocityZeroStateCheck(void)
{
    static float time_count = 0;

    if (MATH_ABS(kAppCheck.load_rpm_now) <= get_app_Velocity_threshold())
    {
        time_count += kAppCheck.dt_1ms;
        if (time_count >= get_app_Velocity_threshold_time())
        {
            time_count = get_app_Velocity_threshold_time();
            kAppCheck.status.bits.velocity_zero = true;
            return true;
        }
    }
    else
    {
        time_count = 0;
    }
    kAppCheck.status.bits.velocity_zero = false;
    return false;
}

/**
 * @brief 检测回零是否达到状态
 *
 * 回零状态为成功且使能状态下有效。
 *
 * @return 如果达到回零状态返回true，否则返回false。
 */
bool AppHomingAttainedStateCheck(void)
{
    if ((HOMING_STATE)get_app_Homing_state() == HOMING_STATE_SUCCEED && \
        get_app_Controlword() == APP_CTRL_ENABLE)
    {
        kAppCheck.status.bits.homing_attained = true;
    }
    else
    {
        kAppCheck.status.bits.homing_attained = false;
    }

    return kAppCheck.status.bits.homing_attained;
}

/**
 * @brief 检查位置是否达到目标状态
 *
 * 此函数用于判断当前位置是否与目标位置接近，并在持续接近一段时间后，
 * 返回true表示位置达到目标。否则返回false。若位置与目标位置相差超过设定的窗口值，
 * 则计时器重置。
 *
 * @return 如果位置达到目标状态返回true，否则返回false。
 */
bool AppPositionTargetReachedStateCheck(void)
{
    static float time_count = 0;

    kAppCheck.pos_diff_now = get_app_Target_position() - get_app_Position_actual_value();
    kAppCheck.pos_diff_now = MATH_ABS(kAppCheck.pos_diff_now);
    if (kAppCheck.pos_diff_now > 0x7FFFFFFF)
    {
        kAppCheck.pos_diff_now = 0x7FFFFFFF;
    }
    if (kAppCheck.pos_diff_now <= get_app_Position_window())
    {
        time_count += kAppCheck.dt;
        if (time_count >= get_app_Position_window_time())
        {
            time_count = get_app_Position_window_time();
            kAppCheck.status.bits.position_target_reached = true;
            return true;
        }
    }
    else
    {
        time_count = 0;
    }
    kAppCheck.status.bits.position_target_reached = false;
    return false;
}
void AppPositionTargetReachedStateClear(void)
{
    kAppCheck.status.bits.position_target_reached = false;
}

/**
 * @brief 检查速度是否达到目标状态
 *
 * 此函数用于判断当前速度是否与目标速度接近，并在持续接近一段时间后，
 * 返回true表示速度达到目标。否则返回false。若速度与目标速度相差超过设定的窗口值，
 * 则计时器重置。
 *
 * @return 如果速度达到目标状态返回true，否则返回false。
 */
bool AppVelocityTargetReachedStateCheck(void)
{
    static float time_count = 0;

    kAppCheck.vel_diff_now = get_app_Target_velocity() - get_app_Velocity_actual_value();
    if (MATH_ABS(kAppCheck.vel_diff_now) <= get_app_Velocity_window())
    {
        time_count += kAppCheck.dt;
        if (time_count >= get_app_Velocity_window_time())
        {
            time_count = get_app_Velocity_window_time();
            kAppCheck.status.bits.velocity_target_reached = true;
            return true;
        }
    }
    else
    {
        time_count = 0;
    }
    kAppCheck.status.bits.velocity_target_reached = false;
    return false;
}
void AppVelocityTargetReachedStateClear(void)
{
    kAppCheck.status.bits.velocity_target_reached = false;
}

/**
 * @brief 检查目标转矩是否达到状态
 *
 * 此函数用于判断规划的转矩是否到达
 *
 * @return 如果目标转矩达到状态返回true，否则返回false。
 */
bool AppTargetTorqueReachedStateCheck(void)
{
    kAppCheck.trq_diff_now = get_app_Target_torque() - get_app_Torque_demand_value();
    if (MATH_ABS(kAppCheck.trq_diff_now) <= MATH_FLOAT_EQUAL) // 判断目标转矩和指令规划转矩指令相等
    {
        kAppCheck.status.bits.target_torque_reached = true;
        return true;
    }
    kAppCheck.status.bits.target_torque_reached = false;
    return false;
}
void AppTargetTorqueReachedStateClear(void)
{
    kAppCheck.status.bits.target_torque_reached = false;
}

bool AppEncoderZeroCrossingStateCheck(void)
{
    kAppCheck.status.bits.encoder_zero_crossing_state = bsp_get_encoder_zero_crossing_state(ENCODER_ID_LOAD);
    return kAppCheck.status.bits.encoder_zero_crossing_state;
}

#pragma endregion

#pragma region 外部接口函数定义
uint32_t app_get_check_error_val(void)
{
    return kAppCheck.error.all;
}

uint32_t app_get_check_warning_val(void)
{
    return kAppCheck.warning.all;
}

uint32_t app_get_check_status_val(void)
{
    return kAppCheck.status.all;
}

uint32_t app_get_check_di_io_val(void)
{
    return kAppCheck.di_io.all;
}

CheckWarningVal* app_set_check_warning_val(void)
{
    return &kAppCheck.warning;
}

/**
 * @brief 应用错误状态检测初始化
 *
 *
 * @note
 */
void AppStatusScanInit(void)
{
    kAppCheck.scan_ring_num = MATH_ARRAY_SIZE(CheckTable);
    sys_get_bsp_error_state(&kAppCheck.p_bsp_error);
    kAppCheck.error_record_addr = get_app_Error_records_list_addr();
    kAppCheck.dt = axis->pmsm_config.tp_s;
    kAppCheck.dt_1ms = NRT_TASK_PERIOD_S;
    kAppCheck.i_rated_squared = DRIVER_RATED_CURRENT_A * DRIVER_RATED_CURRENT_A;
    kAppCheck.i_peak_squared_threshold = 0.81f * DRIVER_PEAK_CURRENT_A * DRIVER_PEAK_CURRENT_A;
}

/**
 * @brief 应用错误状态快速检测与更新
 *
 * 1. 若上次控制字为APP_CTRL_DISABLE且当前为APP_CTRL_CLEAR_ERROR，则清除所有错误标志。
 * 2. 遍历CheckErrorTable，调用各错误检测函数，检测到错误则设置对应bit。
 * 3. 发生错误,直接发送控制字失能
 *
 * @note 应周期性调用本函数以监测和更新错误状态。
 */
void AppStatusScanFast(void)
{
    kAppCheck.now_ctrl_word = get_app_Controlword();
    // 控制字发送0->3，清错
    if (kAppCheck.pre_ctrl_word == APP_CTRL_DISABLE &&
        (kAppCheck.now_ctrl_word == APP_CTRL_CLEAR_ERROR))
    {
        if (kAppCheck.p_bsp_error->bit_band.error_bus_voltage || \
            kAppCheck.p_bsp_error->bit_band.error_nfault) // 此2错误无法被清除  只能复位
        {
            ;;;
        }
        else
        {
            kAppCheck.error.all = 0;
            kAppCheck.p_bsp_error->code = 0;
        }
    }
    kAppCheck.pre_ctrl_word = kAppCheck.now_ctrl_word;

    // 遍历错误检测函数
    for (uint8_t i = 0; i < kAppCheck.scan_ring_num; i++)
    {
        if (CheckTable[i].scan_fast == true)
        {
            kAppCheck.error.all |= (CheckTable[i].check_func() << i); // 对应bit置1
        }
    }

    // 发生错误失能电机
    if (kAppCheck.error.all != 0)
    {
        // TODO：根据不同错误类型执行不同保护动作，目前统一失能
        set_app_Controlword(APP_CTRL_DISABLE);
    }

    AppMotorEnableStateCheck();
    set_app_Encoder_zero_crossing_state(AppEncoderZeroCrossingStateCheck());
}

/**
 * @brief 应用错误状态慢速检测与更新
 *
 * 1. 遍历CheckErrorTable，调用各错误检测函数，检测到错误则设置对应bit。
 * 2. 发生错误,直接发送控制字失能
 * 3. 记录错误并保存到Flash
 *
 * @note 应周期性调用本函数以监测和更新错误状态。
 */
void AppStatusScanSlow(void)
{
    // 部分通用检测数据更新
    kAppCheck.idq_now[0] = get_app_D_current_actual_value();
    kAppCheck.idq_now[1] = get_app_Current_actual_value();
    kAppCheck.idq_squared_now = kAppCheck.idq_now[0] * kAppCheck.idq_now[0] + kAppCheck.idq_now[1] * kAppCheck.idq_now[1];
    kAppCheck.drive_temp_now = get_app_Drive_temperature();
    kAppCheck.motor_temp_now = get_app_Motor_temperature();
    kAppCheck.mcu_temp_now = get_app_Mcu_temperature();
    kAppCheck.load_rpm_now = get_app_Velocity_actual_value();

    // 遍历错误检测函数
    for (uint8_t i = 0; i < kAppCheck.scan_ring_num; i++)
    {
        if (CheckTable[i].scan_fast == false)
        {
            kAppCheck.error.all |= (CheckTable[i].check_func() << i); // 对应bit置1
        }
    }

    // 扫描到 nFault 错误，设置到控制层
    if (kAppCheck.p_bsp_error->bit_band.error_nfault)
    {
        kAppCheck.error.bits.nfault_error = true;
        axis->motor_ctl_sm_output.state = MOTOR_CTL_SM_STATE_ERROR;
        axis->motor_ctl_sm_output.error = MOTOR_CTL_SM_NFAULT_ERROR;
    }

    // 发生错误失能电机
    if (kAppCheck.error.all != 0)
    {
        // TODO：根据不同错误类型执行不同保护动作，目前统一失能
        set_app_Controlword(APP_CTRL_DISABLE);

        // 低速进行错误记录存储兼容高速部分
        if (kAppCheck.error_record_addr[0] != kAppCheck.error.all) // 错误中，再新增其它错误再加入新记录
        {
            kAppCheck.error_record_latch_flag = false;
        }
        if (kAppCheck.error_record_latch_flag == false)
        {
            if (axis->motor_ctl_sm_output.state != MOTOR_CTL_SM_STATE_ENABLE && \
                get_app_Storage_status() != FLASH_STORE_STATUS_BUSY)    // 等待Flash空闲
            {
                // 数组FIFO，更新错误记录，低优先级更新避免重复记录错误
                for (uint8_t i = ERROR_RECORD_NUM - 1; i > 0; i--)
                {
                    kAppCheck.error_record_addr[i] = kAppCheck.error_record_addr[i - 1];
                }
                kAppCheck.error_record_addr[0] = kAppCheck.error.all;
                kAppCheck.error_record_latch_flag = true;
                set_app_Storage_cmd(FLASH_STORE_CMD_WRITE_ERROR);
            }
        }
    }
    else
    {
        kAppCheck.error_record_latch_flag = false;
    }

    // 检查速度是否为零状态
    AppVelocityZeroStateCheck();
    AppTargetReachedStateCheck();
}

/**
 * @brief 应用通用状态轮询检查函数  位置环调用
 *
 * 1. 遍历数字输入IO状态，更新对应bit。
 * 2. ...
 *
 * @note 应周期性调用本函数以监测和更新状态。
 */
void AppStatusCheck(void)
{
    // 遍历数字输入IO状态，更新对应bit。
    uint32_t di_io_status = 0;
    for (DIGITAL_INPUTS_IO_BIT io = DI_IO_MIN; io <= DI_IO_MAX; io++)
    {
        di_io_status |= (bsp_get_digital_input_state(io) << io);
        // 可根据需要在以下添加IO输入状态变化，处理触发事件等功能逻辑
    }
    kAppCheck.di_io.all = di_io_status;
}

/**
 * @brief 更新 LED 状态  1ms 周期调用
 * 正常运行 0.5s 闪烁一次 run led
 * 错误状态 error led 常亮  run led  0.1s 闪烁一次
 * @note  应周期性调用本函数以监测和更新 LED 状态。
 */
void AppLedStateUpdata1ms(void)
{
    static uint16_t run_led_times_count = 0; // 运行LED闪烁计数
    static uint16_t run_led_blink_period = LED_NORMAL_STATE_PERIOD; // 运行LED闪烁周期

    if (app_get_check_error_val() != 0) // 有错误
    {
        bsp_set_error_led_state(1); // 错误LED常亮
        run_led_blink_period = LED_ERROR_STATE_PERIOD;
    }
    else
    {
        bsp_set_error_led_state(0); // 错误LED常灭
        run_led_blink_period = LED_NORMAL_STATE_PERIOD;
    }

    // 运行LED闪烁逻辑
    if (run_led_times_count++ >= run_led_blink_period)
    {
        run_led_times_count = 0;        // 重置计数
        bsp_set_run_led_toggle(); // 翻转运行LED状态
    }
}

#pragma endregion
