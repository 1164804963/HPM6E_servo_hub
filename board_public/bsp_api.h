#ifndef BSP_API_H
#define BSP_API_H

#include "data_type_define.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define PWM_ENABLE      true
#define PWM_DISABLE     false

/**
 * @defgroup MotorControl 电机控制相关API
 * @{
 */
#pragma region 系统控制相关
/* 系统复位 */
void bsp_system_reset(void);
/* 全局中断使能 */
void bsp_system_global_irq_enable(void);
/* 全局中断禁用 */
void bsp_system_global_irq_disable(void);
#pragma endregion

#pragma region 硬件状态相关
/* 设置系统硬件错误状态 */
void sys_set_bsp_error_state(BSP_ERROR_CODE type, BSP_ERROR_OPERATION op);
/* 获取系统硬件错误状态地址 */
void sys_get_bsp_error_state(BspErrorCode_t* *p_bsp_error);
/* 获取系统硬件自检状态 */
bool sys_get_hardware_self_test_status(void);
/* 母线电压检测 */
VOLTAGE_CHECK_STATUS sys_bus_voltage_check(void);
/* 三相电流检测 */
void sys_current_calibration_step(void);
/* 获取系统三相电流检测状态 */
CURRENT_CALIBRATION_STATUS sys_get_current_calibration_status(void);
/* 获取UVW三相电流校准值 */
void sys_get_current_calibration_drift(uint16_t *drift);
/* 设置PWM输出状态 */
void bsp_set_pwm_state(bool state);
/* 更新PWM输出准备状态 */
void bsp_pwm_ready_state_updata(void);
/* 获取PWM输出状态 */
bool bsp_get_pwm_state(void);
/* 设置UVW三相电压 */
void bsp_set_phase_voltage(const float voltage[3]);
/* 获取UVW三相电流 */
void bsp_get_phase_current(float piabc[3]);
/* 读取母线电压 */
float bsp_get_dc_bus_voltage(void);
/* 读取母线电流 */
float bsp_get_dc_bus_current(void);
/* 读取电机当前温度 */
float bsp_get_motor_temp(void);
/* 读取mos当前温度 */
float bsp_get_mos_temperature(void);
/* 读取mcu温度 */
float bsp_get_mcu_temperature(void);
/* 读取用户ADC采样值 */
uint16_t bsp_get_user_adc1_val(void);
/* 计算抱闸PWM定时器配置值 */
void bsp_calc_brake_pwm_timer_param(bool is_pwm_adjust, float pwm_freq, float rated_voltage, \
                                    float release_action_voltage, float release_hold_voltage);
/* 设置抱闸PWM定时器配置值 */
void bsp_set_brake_pwm_timer_config(APP_BRAKE_STATE brake_state);
#pragma endregion

#pragma region 编码器相关
/* 编码器配置 */
void bsp_set_encoder_config(ENCODER_ID const enc_id, uint16_t const type, uint8_t const options, \
                            uint32_t const a_single_res, uint32_t const a_single_res_real, uint32_t const a_multi_res, \
                            uint32_t const b_single_res, uint32_t const b_single_res_real, uint32_t const b_multi_res);
/* 获取编码器状态 */
bool bsp_get_encoder_state(ENCODER_ID const enc_id);
/* 获取编码器单圈值 */
uint32_t bsp_get_encoder_cnt(ENCODER_ID const enc_id);
/* 获取编码器多圈值 */
int64_t bsp_get_encoder_turns(ENCODER_ID const enc_id);
/* 获取编码器类型 */
uint8_t bsp_get_encoder_type(ENCODER_ID enc_id);
/* 获取编码器过零点状态 */
bool bsp_get_encoder_zero_crossing_state(ENCODER_ID const enc_id);
#pragma endregion

#pragma region 通讯相关
/* 设置CAN ID */
void bsp_set_can_id(uint32_t can_id);
/* 获取当前 CAN ID */
uint32_t bsp_get_can_id(void);
/* 设置CAN 波特率 */
void bsp_set_can_baudrate(uint32_t baudrate);
/* 获取当前 CAN 波特率 */
uint32_t bsp_get_can_baudrate(void);
/* 获取当前 CAN 消息累计计数值 */
uint32_t bsp_get_can_mg_counts(void);
/* 设置CAN mavlink系统ID、组件ID */
void bsp_set_can_mav_id(uint8_t sys_id, uint8_t comp_id);
/* 获取CAN mavlink系统ID、组件ID */
void bsp_get_can_mav_id(uint8_t *sys_id, uint8_t *comp_id);
#pragma endregion

#pragma region 参数存储相关
/* FlashDB数据库初始化 */
FLASHDB_STATUS bsp_flashdb_init(void);
/* FlashDB数据库读取 */
FLASHDB_STATUS bsp_flashdb_read(FLASHDB_KEY_INDEX const index);
/* FlashDB数据库写入 */
FLASHDB_STATUS bsp_flashdb_write(FLASHDB_KEY_INDEX const index);
/* FlashDB数据库键值注册 */
FLASHDB_STATUS bsp_flashdb_key_register(FLASHDB_KEY_INDEX const index, char *key, void *value, size_t value_len);
/* FlashDB数据库键值删除 */
FLASHDB_STATUS bsp_flashdb_key_delete(FLASHDB_KEY_INDEX const index);
#pragma endregion

#pragma region 其它
/* 获取数字输入IO状态 */
bool bsp_get_digital_input_state(DIGITAL_INPUTS_IO_BIT const io);
/* 设置数字输出IO状态 */
void bsp_set_digital_output_state(DIGITAL_OUTPUTS_IO_BIT const io, bool state);
/* 系统阻塞us延时 */
void bsp_sys_blocking_delay_us(uint32_t us);
/* 系统阻塞ms延时 */
void bsp_sys_blocking_delay_ms(uint32_t ms);
/* 系统耗时记录开始 */
void bsp_set_timer_record_start(SYS_TIMER_RECORD_INDEX index);
/* 系统耗时记录结束 */
void bsp_set_timer_record_stop(SYS_TIMER_RECORD_INDEX index);
/* 获取系统代码区块执行耗时 */
float bsp_get_timer_duration_records_us(SYS_TIMER_RECORD_INDEX index);
/* 设置运行LED状态 */
void bsp_set_run_led_state(uint8_t state);
/* 设置运行LED状态翻转 */
void bsp_set_run_led_toggle(void);
/* 设置错误LED状态 */
void bsp_set_error_led_state(uint8_t state);
/* 设置错误LED状态翻转 */
void bsp_set_error_led_toggle(void);
/* 文件传输参数配置 */
void bsp_set_file_transfer_config(uint8_t file_type, uint32_t file_size, uint8_t file_dir);
/* 固件升级配置 */
void bsp_set_fw_upgrade_config(uint8_t fw_mode);
/* 固件升级写入 */
void bsp_set_fw_upgrade_write(uint16_t const index, uint16_t const length, void const *data);
/* 获取固件升级当前文件传输完成帧索引 */
uint32_t bsp_get_fw_file_index_complete(void);
/* 获取固件升级当前文件传输状态 */
APP_FILE_STATUS bsp_get_fw_file_status(void);
/* 获取固件升级当前步骤 */
int8_t bsp_get_fw_operating_steps(void);
/* 固件升级运行主函数 */
void bsp_run_fw_upgrade(void);
#pragma endregion

/** @} */ // end of MotorControl


#ifdef __cplusplus
}
#endif

#endif
