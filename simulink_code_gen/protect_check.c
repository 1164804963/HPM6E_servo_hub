/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: protect_check.c
 *
 * Code generated for Simulink model 'protect_check'.
 *
 * Simulink Coder version         : 9.9 (R2023a) 19-Nov-2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Not run
 */

#include "protect_check.h"
#include "rtwtypes.h"
#include "servo_hub_database_type.h"

/* Output and update for referenced model: 'protect_check' */
void protect_check(const real32_T rtu_iabc_now[3], const real32_T *rtu_dc_bus,
                   const real32_T *rtu_driver_temp, const int32_T
                   *rtu_pos_ctl_error, const real32_T *rtu_speed_now, const
                   MotorCtlSmConfig *rtu_config, uint32_T *rty_error)
{
    /* MATLAB Function: '<S1>/protect_check_fun' */
    /*  config.error_enable  保护可以根据配置关闭 开启 */
    /* MATLAB Function 'protect_check/protect_check_fun': '<S2>:1' */
    /* 电压保护 */
    /* '<S2>:1:8' if dc_bus < config.under_voltage_protection_V && bitget(config.error_enable, 1) == 1 */
    if ((*rtu_dc_bus < rtu_config->under_voltage_protection_V) &&
            ((rtu_config->error_enable & 1U) != 0U))
    {
        /* '<S2>:1:9' error = uint32(1); */
        *rty_error = 1U;

        /* '<S2>:1:13' if dc_bus > config.over_voltage_protection_V  && bitget(config.error_enable, 2) == 1 */
    }
    else if ((*rtu_dc_bus > rtu_config->over_voltage_protection_V) &&
             ((rtu_config->error_enable & 2U) != 0U))
    {
        /* '<S2>:1:14' error = uint32(2); */
        *rty_error = 2U;

        /* 过流保护 */
        /* '<S2>:1:20' if iabc_now(1) > config.over_current_protection_A  && bitget(config.error_enable, 7) == 1 */
    }
    else if ((rtu_iabc_now[0] > rtu_config->over_current_protection_A) &&
             ((rtu_config->error_enable & 64U) != 0U))
    {
        /* '<S2>:1:21' error = uint32(7); */
        *rty_error = 7U;

        /* '<S2>:1:24' if iabc_now(1) < -config.over_current_protection_A && bitget(config.error_enable, 7) == 1 */
    }
    else if ((rtu_iabc_now[0] < -rtu_config->over_current_protection_A) &&
             ((rtu_config->error_enable & 64U) != 0U))
    {
        /* '<S2>:1:25' error = uint32(7); */
        *rty_error = 7U;

        /* '<S2>:1:29' if iabc_now(2) > config.over_current_protection_A && bitget(config.error_enable, 7) == 1 */
    }
    else if ((rtu_iabc_now[1] > rtu_config->over_current_protection_A) &&
             ((rtu_config->error_enable & 64U) != 0U))
    {
        /* '<S2>:1:30' error = uint32(7); */
        *rty_error = 7U;

        /* '<S2>:1:33' if iabc_now(2) < -config.over_current_protection_A && bitget(config.error_enable, 7) == 1 */
    }
    else if ((rtu_iabc_now[1] < -rtu_config->over_current_protection_A) &&
             ((rtu_config->error_enable & 64U) != 0U))
    {
        /* '<S2>:1:34' error = uint32(7); */
        *rty_error = 7U;

        /* '<S2>:1:38' if iabc_now(3) > config.over_current_protection_A && bitget(config.error_enable, 7) == 1 */
    }
    else if ((rtu_iabc_now[2] > rtu_config->over_current_protection_A) &&
             ((rtu_config->error_enable & 64U) != 0U))
    {
        /* '<S2>:1:39' error = uint32(7); */
        *rty_error = 7U;

        /* '<S2>:1:42' if iabc_now(3) < -config.over_current_protection_A && bitget(config.error_enable, 7) == 1 */
    }
    else if ((rtu_iabc_now[2] < -rtu_config->over_current_protection_A) &&
             ((rtu_config->error_enable & 64U) != 0U))
    {
        /* '<S2>:1:43' error = uint32(7); */
        *rty_error = 7U;

        /* 温度保护 */
        /* '<S2>:1:48' if driver_temp < config.under_temperature_protection_d && bitget(config.error_enable, 4) == 1 */
    }
    else if ((*rtu_driver_temp < rtu_config->under_temperature_protection_d) &&
             ((rtu_config->error_enable & 8U) != 0U))
    {
        /* '<S2>:1:49' error = uint32(4); */
        *rty_error = 4U;

        /* '<S2>:1:52' if driver_temp > config.over_temperature_protection_d && bitget(config.error_enable, 5) == 1 */
    }
    else if ((*rtu_driver_temp > rtu_config->over_temperature_protection_d) &&
             ((rtu_config->error_enable & 16U) != 0U))
    {
        /* '<S2>:1:53' error = uint32(5); */
        *rty_error = 5U;
    }
    else
    {
        uint32_T tmp_0;

        /* 过速保护 */
        /* '<S2>:1:58' if speed_now > config.over_speed_protection_rad_s && bitget(config.error_enable, 3) == 1 */
        tmp_0 = rtu_config->error_enable & 4U;
        if ((*rtu_speed_now > rtu_config->over_speed_protection_rad_s) && (tmp_0
             != 0U))
        {
            /* '<S2>:1:59' error = uint32(3); */
            *rty_error = 3U;

            /* '<S2>:1:62' if speed_now < -config.over_speed_protection_rad_s && bitget(config.error_enable, 3) == 1 */
        }
        else if ((*rtu_speed_now < -rtu_config->over_speed_protection_rad_s) &&
                 (tmp_0 != 0U))
        {
            /* '<S2>:1:63' error = uint32(3); */
            *rty_error = 3U;

            /* 位置跟随误差保护 */
            /* '<S2>:1:69' if config.mode == 3 || config.mode == 4 */
        }
        else if ((rtu_config->mode == 3) || (rtu_config->mode == 4))
        {
            /* 位置模式下才会生效位置误差保护 */
            /* '<S2>:1:71' if pos_ctl_error > config.position_following_error_protection && bitget(config.error_enable, 6) == 1 */
            tmp_0 = rtu_config->error_enable & 32U;
            if ((*rtu_pos_ctl_error >
                    rtu_config->position_following_error_protection) && (tmp_0
                    != 0U))
            {
                /* '<S2>:1:72' error = uint32(6); */
                *rty_error = 6U;
            }
            else
            {
                int32_T tmp;

                /* '<S2>:1:75' if pos_ctl_error < -config.position_following_error_protection && bitget(config.error_enable, 6) == 1 */
                if (rtu_config->position_following_error_protection <=
                        MIN_int32_T)
                {
                    tmp = MAX_int32_T;
                }
                else
                {
                    tmp = -rtu_config->position_following_error_protection;
                }

                if ((*rtu_pos_ctl_error < tmp) && (tmp_0 != 0U))
                {
                    /* '<S2>:1:76' error = uint32(6); */
                    *rty_error = 6U;
                }
                else
                {
                    /* '<S2>:1:83' error = uint32(0); */
                    *rty_error = 0U;
                }
            }
        }
        else
        {
            /* '<S2>:1:83' error = uint32(0); */
            *rty_error = 0U;
        }
    }

    /* End of MATLAB Function: '<S1>/protect_check_fun' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
