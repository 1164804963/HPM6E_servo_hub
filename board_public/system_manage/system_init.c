#include "system_init.h"

#include "app_brake_control.h"
#include "app_motion_precondition.h"
#include "app_scheduler.h"
#include "app_store_param.h"
#include "app_status_check.h"

extern Axis kAxis;
extern AxisDw kAxisDw;

SystemMessage_t sys_msg = {
    .first_time_enable_flag = true,
    .hardware_self_test_status = false,
    .bus_voltage_check_flag = VOLTAGE_STATUS_UNKNOWN,
    .bsp_error_code.code = 0,
    .current_calibration.start_flag = false,
    .current_calibration.result = CURRENT_CALIBRATION_STATUS_READY,
    .current_calibration.drift = {0, 0, 0}
};

void HalInit(void)
{
    sys_timer_init();
    AppParamInit();
    MotorCtrlInit();  //电机控制相关初始化
    AppInit();
    AppStatusScanInit();
    AppStoreInit();
    ScopeInit();
    AppBrakeControlInit();
    AppMotionPreConditionInit();
}

// 检测母线电压稳定
VOLTAGE_CHECK_STATUS BusVoltageCheck(void)
{
    static uint16_t check_timer[3] = {0, 0, 0}; // 检测计时器
    float bus_voltage = bsp_get_dc_bus_voltage();

    check_timer[0]++;    // 母线电压检测超时计时器
    if (bus_voltage < UNDER_VOLTAGE_PROTECTION_V)
    {
        check_timer[1] = 0; // 只要有一次欠压，正常电压计时器清零
        check_timer[2]++;   // 欠压计时器计时
    }
    else
    {
        check_timer[2] = 0; // 只要有一次正常电压，欠压计时器清零
        check_timer[1]++;   // 正常电压计时器计时
    }

    if (check_timer[2] >= HARDWARE_UNDER_BUS_VOLTAGE_CNT ||         // 欠压累计持续2s报错
        check_timer[0] >= HARDWARE_BUS_VOLTAGE_CHECK_OVERTIME_CNT)  // 检测超时3s报错
    {
        sys_msg.bus_voltage_check_flag = VOLTAGE_STATUS_ERROR;
        set_bsp_error_state(ERROR_BUS_VOLTAGE, ERROR_SET); // 设置母线电压错误
    }
    else if (check_timer[1] >= HARDWARE_NORMAL_BUS_VOLTAGE_CNT)     // 正常电压累计持续0.5s认为母线稳定正常
    {
        sys_msg.bus_voltage_check_flag = VOLTAGE_STATUS_NORMAL;
    }
    else
    {
        sys_msg.bus_voltage_check_flag = VOLTAGE_STATUS_UNKNOWN;
    }

    return sys_msg.bus_voltage_check_flag;
}

void HardwareSelfTestRun(void)
{
    static uint32_t position_irq_cnt = 0;
    static uint32_t motor_encoder_cnt = 0;     // 电机端编码器单圈值
    static uint32_t load_encoder_cnt = 0;      // 负载端编码器单圈值
    static int64_t motor_encoder_turns = 0;    // 电机端编码器多圈值
    static int64_t load_encoder_turns = 0;     // 负载端编码器多圈值

    position_irq_cnt++;

    // 检查编码器是否准备好
    if (bsp_get_encoder_state(ENCODER_ID_MOTOR) == true && \
        bsp_get_encoder_state(ENCODER_ID_LOAD) == true)
    {
        // 编码器已准备好，获取编码器数据并初始化电机控制状态
        motor_encoder_cnt = bsp_get_encoder_cnt(ENCODER_ID_MOTOR);
        load_encoder_cnt = bsp_get_encoder_cnt(ENCODER_ID_LOAD);
        motor_encoder_turns = bsp_get_encoder_turns(ENCODER_ID_MOTOR);
        load_encoder_turns = bsp_get_encoder_turns(ENCODER_ID_LOAD);

        MotorCtlSmStateInit(&kAxis, &kAxisDw, \
                            motor_encoder_turns, motor_encoder_cnt, \
                            load_encoder_turns, load_encoder_cnt);

        position_irq_cnt = 0;

        // 编码器准备好，设置硬件自检状态为true
        sys_msg.hardware_self_test_status = true;
    }
    else
    {
        // 编码器未准备好，检查是否超时
        if (position_irq_cnt >= HARDWARE_SELF_TEST_RUN_CNT)
        {
            // 超时处理：使用默认值初始化电机控制状态
            MotorCtlSmStateInit(&kAxis, &kAxisDw, 0, 0, 0, 0);

            // 设置编码器错误状态
            if (bsp_get_encoder_state(ENCODER_ID_MOTOR) == false)
            {
                sys_set_bsp_error_state(ERROR_ENCODER_MOTOR, ERROR_SET);
            }
            if (bsp_get_encoder_state(ENCODER_ID_LOAD) == false)
            {
                sys_set_bsp_error_state(ERROR_ENCODER_LOAD, ERROR_SET);
            }

            // 重置计数器
            position_irq_cnt = 0;
        }
        // 编码器未准备好，保持硬件自检状态为false
        sys_msg.hardware_self_test_status = false;
    }

    // 硬件自检也检测相关状态
    AppStatusScanFast();
}

// 三相电流校准
void CurrentCalibrationStep(void)
{
    static uint16_t cnt = 0;
    static uint32_t current_temp[3] = {0, 0, 0};
    const float uabc[3] = {0.0f};

    // 上电后第一次使能，电流校准
    if (sys_msg.first_time_enable_flag == true)
    {
        // 校准标志位
        if (sys_msg.current_calibration.result == CURRENT_CALIBRATION_STATUS_OK)  //校准成功直接退出
        {
            sys_msg.first_time_enable_flag = false;
            return;
        }

        if (sys_msg.bus_voltage_check_flag < 0) // 母线电压不稳定，电流不进行校准，不开波，报校准错误
        {
            sys_msg.current_calibration.result = CURRENT_CALIBRATION_STATUS_ERR_BUS_VOLTAGE;     // 3校准过程中母线电压不稳定错误
            set_bsp_error_state(ERROR_CURRENT_SAMPLE, ERROR_SET); // 设置电流采样错误
            bsp_set_pwm_state(PWM_DISABLE);               // 立刻关闭PWM,防止电流过大
            return;
        }

        if (sys_msg.current_calibration.start_flag == false)  // 启动电流校准 启动PWM 
        {
            sys_msg.current_calibration.start_flag = true;
            // 设置50%占空比，相间电压0V, 用于电流校准
            bsp_set_phase_voltage(uabc);
            bsp_set_pwm_state(PWM_ENABLE);

            // 发波后返回,等待稳定,下一个周期开始采样
            return;
        }

        if(bsp_get_pwm_state() != true)  //等待PWM使能完成
        {
            return;
        }

        // 电流校准过程中，需要判断当前采样值是否在误差允许范围内
        if ((UVW_CURRENT_U_CHANNEL > (UVW_CURRENT_MID_VAL * (1 + UVW_CURRENT_ERROR_RANGE))) ||
            (UVW_CURRENT_U_CHANNEL < (UVW_CURRENT_MID_VAL * (1 - UVW_CURRENT_ERROR_RANGE))) ||
            (UVW_CURRENT_V_CHANNEL > (UVW_CURRENT_MID_VAL * (1 + UVW_CURRENT_ERROR_RANGE))) ||
            (UVW_CURRENT_V_CHANNEL < (UVW_CURRENT_MID_VAL * (1 - UVW_CURRENT_ERROR_RANGE))) ||
            (UVW_CURRENT_W_CHANNEL > (UVW_CURRENT_MID_VAL * (1 + UVW_CURRENT_ERROR_RANGE))) ||
            (UVW_CURRENT_W_CHANNEL < (UVW_CURRENT_MID_VAL * (1 - UVW_CURRENT_ERROR_RANGE))))
        {
            cnt = 0;
            current_temp[0] = 0;
            current_temp[1] = 0;
            current_temp[2] = 0;

            sys_msg.current_calibration.result = CURRENT_CALIBRATION_STATUS_ERR_BIG_CURRENT;   // 2校准中心电流过大错误
            set_bsp_error_state(ERROR_CURRENT_SAMPLE, ERROR_SET); // 设置电流采样错误
            bsp_set_pwm_state(PWM_DISABLE);               // 立刻关闭PWM,防止电流过大
            return;
        }

        // 电流采样均值校准 1024次采样平均值
        cnt ++;
        current_temp[0] += UVW_CURRENT_U_CHANNEL;
        current_temp[1] += UVW_CURRENT_V_CHANNEL;
        current_temp[2] += UVW_CURRENT_W_CHANNEL;

        // 采样1024次取平均值
        if (cnt >= CURRENTCCALIBRATION_TIMES)
        {
            // 采样值右移10位,相当于除以1024
            sys_msg.current_calibration.drift[0] = current_temp[0] >> CURRENTCCALIBRATION_TIMES_SHIFT;
            sys_msg.current_calibration.drift[1] = current_temp[1] >> CURRENTCCALIBRATION_TIMES_SHIFT;
            sys_msg.current_calibration.drift[2] = current_temp[2] >> CURRENTCCALIBRATION_TIMES_SHIFT;

            cnt = 0;
            current_temp[0] = 0;
            current_temp[1] = 0;
            current_temp[2] = 0;

            sys_msg.current_calibration.result = CURRENT_CALIBRATION_STATUS_OK;
            sys_msg.first_time_enable_flag = false;
        }
    }
}

bool get_first_time_enable_flag(void)
{
    return sys_msg.first_time_enable_flag;
}

void set_first_time_enable_flag(bool flag)
{
    sys_msg.first_time_enable_flag = flag; 
}

bool get_hardware_self_test_status(void)
{
    return sys_msg.hardware_self_test_status;
}

BspErrorCode_t* get_bsp_error_state(void)
{
    return &sys_msg.bsp_error_code;
}

void set_bsp_error_state(BSP_ERROR_CODE type, BSP_ERROR_OPERATION op)
{
    switch (type)
    {
    case ERROR_ENCODER_MOTOR:
        sys_msg.bsp_error_code.bit_band.error_encoder_motor = op;
        break;
    case ERROR_ENCODER_LOAD:
        sys_msg.bsp_error_code.bit_band.error_encoder_load = op;
        break;
    case ERROR_NFAULT:
        sys_msg.bsp_error_code.bit_band.error_nfault = op;
        break;
    case ERROR_BUS_CURRENT_OC:
        sys_msg.bsp_error_code.bit_band.error_bus_current_oc = op;
        break;
    case ERROR_BUS_OFFLINE:
        sys_msg.bsp_error_code.bit_band.error_bus_offline = op;
        break;
    case ERROR_FLASH_STORE:
        sys_msg.bsp_error_code.bit_band.error_flash_store = op;
        break;
    case ERROR_COMMS_INIT:
        sys_msg.bsp_error_code.bit_band.error_comms_init = op;
        break;
    case ERROR_DRV_INIT:
        sys_msg.bsp_error_code.bit_band.error_drv_init = op;
        break;
    case ERROR_BUS_VOLTAGE:
        sys_msg.bsp_error_code.bit_band.error_bus_voltage = op;
        break;
    case ERROR_CURRENT_SAMPLE:
        sys_msg.bsp_error_code.bit_band.error_current_sample = op;
        break;
    case ERROR_FIRMWARE:
        sys_msg.bsp_error_code.bit_band.error_firmware = op;
        break;
    case ERROR_LIMIT_SWITCH:
        sys_msg.bsp_error_code.bit_band.error_limit_switch = op;
        break;
    default:
        break;
    }
}

CURRENT_CALIBRATION_STATUS get_current_calibration_status(void)
{
    return sys_msg.current_calibration.result;
}

void get_current_calibration_drift(uint16_t *drift)
{
    drift[0] = sys_msg.current_calibration.drift[0];
    drift[1] = sys_msg.current_calibration.drift[1];
    drift[2] = sys_msg.current_calibration.drift[2];
}
