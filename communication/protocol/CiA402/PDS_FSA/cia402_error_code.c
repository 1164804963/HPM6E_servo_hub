#include "cia402_error_code.h"
#include "Cia402_ObjectDictionary_Variable.h"
#include "app_status_check.h"
// 失能自由停机
void FreeToRotateErrorHandle(void)
{
    // axis->motor_ctl_sm_input.motor_enable = 0; //控制状态机：失能
}

// 中断运行时，检查错误代码
void Cia402ErrorCodeScan(void)
{
    CheckErrorCode_t check_error_val = (CheckErrorCode_t)app_get_check_error_val();
    // 无错误不检查
    if (check_error_val.all)
    {
        //free_to_rotate_error_handle();
        // 按照错误优先级顺序检查每个错误位
        if (check_error_val.bits.drive_overload) {
            set_Error_code(Load_error_error);
            return;
        }
        if (check_error_val.bits.drive_peak_current_overload) {
            set_Error_code(Driver_peak_current_overload_error);
            return;
        }
        if (check_error_val.bits.drive_over_current_error) {
            set_Error_code(Continuous_over_current_output_No_2_error);
            return;
        }
        if (check_error_val.bits.dc_bus_over_voltage) {
            set_Error_code(DC_link_over_voltage_error);
            return;
        }
        if (check_error_val.bits.dc_bus_under_voltage) {
            set_Error_code(DC_link_under_voltage_error);
            return;
        }
        if (check_error_val.bits.over_temperature_drive) {
            set_Error_code(Excess_temperature_device_error);
            return;
        }
        if (check_error_val.bits.under_temperature_drive) {
            set_Error_code(Too_low_temperature_device_error);
            return;
        }
        if (check_error_val.bits.over_temperature_motor) {
            set_Error_code(Motor_blocked_error);
            return;
        }
        if (check_error_val.bits.under_temperature_motor) {
            set_Error_code(Under_temperature_motor_error);
            return;
        }
        if (check_error_val.bits.over_temperature_mcu) {
            set_Error_code(Excess_temperature_drive_error);
            return;
        }
        if (check_error_val.bits.under_temperature_mcu) {
            set_Error_code(Too_low_temperature_drive_error);
            return;
        }
        if (check_error_val.bits.over_speed) {
            set_Error_code(Velocity_speed_controller_error);
            return;
        }
        if (check_error_val.bits.position_following_error) {
            set_Error_code(Following_error_error);
            return;
        }
        if (check_error_val.bits.motor_encoder_error) {
            set_Error_code(Incremental_sensor_1_fault_error);
            return;
        }
        if (check_error_val.bits.load_encoder_error) {
            set_Error_code(Incremental_sensor_2_fault_error);
            return;
        }
        if (check_error_val.bits.flash_store_error) {
            set_Error_code(Non_volatile_data_memory_error);
            return;
        }
        if (check_error_val.bits.nfault_error) {
            set_Error_code(Drv_nfault_error);
            return;
        }
        if (check_error_val.bits.drv_init_error) {
            set_Error_code(Drv_init_error);
            return;
        }
        if (check_error_val.bits.current_sample_error) {
            set_Error_code(Current_sample_error);
            return;
        }
        if (check_error_val.bits.drive_bus_voltage_error) {
            set_Error_code(Drive_bus_voltage_error);
            return;
        }
        if (check_error_val.bits.can_bus_disconnection_error) {
            set_Error_code(Can_bus_disconnection_error);
            return;
        }
        if (check_error_val.bits.external_inhibit_input_detected) {
            set_Error_code(External_inhibit_input_detected_error);
            return;
        }
    }
    else
    {
        set_Error_code(0);
    }
}
