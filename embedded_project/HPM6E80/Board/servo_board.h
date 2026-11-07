#ifndef SERVO_BOARD_H
#define SERVO_BOARD_H

// HPM6EMotorV20 板级定义：把 SDK 板级包（boards/hpm6e00YZ）和本板伺服参数接起来。
// 约定：本工程的硬件细节只出现在 embedded_project/HPM6E80/ 下，portable 层只看到 bsp_api.h。

#include "board.h"              // SDK 板级包：时钟、引脚、BOARD_BLDC_* 硬件宏
#include "servo_system_cfg.h"

/* 本板补充的模拟通道：SDK 板级包只定义了 U/V/W，母线与温度是本工程加的。
 * VBUS_VOL = PF31 = ADC3.CH7（200K/10K 分压，21:1）；NTC1 = PF8 = ADC3.CH? 见 board.c。 */
#define BOARD_BLDC_ADC_VBUS_CH   (7U)

#ifdef __cplusplus
extern "C" {
#endif

/* 运行期硬件状态。bsp_api.c 与中断写，上层只读。 */
typedef struct
{
    volatile uint16_t adc_u_raw;        /* PF28 I_U   原始计数 */
    volatile uint16_t adc_v_raw;        /* PF29 I_V */
    volatile uint16_t adc_w_raw;        /* PF30 I_W，与 U 同一颗 ADC 的第 2 个预转换槽 */
    volatile uint16_t adc_vbus_raw;     /* PF31 VBUS_VOL */
    volatile uint16_t adc_temp_raw;     /* PF8  NTC1(MCP9700) */
    float uvw_current[3];               /* 换算后的相电流 A */
    float uvw_target_voltage[3];        /* 上层下发的三相电压指令 V */
    float dc_bus_voltage_val;           /* 母线电压 V */
    float motor_temp_val;               /* 电机温度 ℃ */
    volatile bool pwm_en_state;         /* PWM 已放开 */
    volatile bool pwm_ready_state;      /* PWM 输出已稳定，可参与使能判定 */
    uint32_t pwm_state_cnt;             /* PWM 放开后的位置环周期计数 */
    volatile uint32_t ctrl_tick;        /* 20kHz 控制节拍计数，供看门狗判活 */
} BspData;

extern BspData kBspData;

/* board.c：时钟、引脚、PWM/ADC/TRGM、20kHz 与 1ms 节拍。开节拍前调用。 */
void board_init_servo(void);

/* 启动 20kHz 控制节拍。必须在 MotorCtrlInit()/AppInit() 之后调用。 */
void board_start_ctrl_tick(void);

/* PWM 输出闸门。false 时六路强制输出，桥臂不跟随比较值。 */
void board_set_pwm_enable(bool enable);
bool board_get_pwm_state(void);

/* 20kHz 控制节拍计数，供上层判活。 */
uint32_t board_get_ctrl_tick(void);

/* 当前 PWM 的 reload 值（= PWM 时钟 / 20kHz - 1），占空比换算要用。 */
uint32_t board_get_pwm_reload(void);

/* 调试心跳：置 true 后 1ms 与 20kHz 中断各每秒打一个标记，用来判断中断是否还活着。 */
extern volatile bool board_heartbeat_on;

#ifdef __cplusplus
}
#endif

#endif // SERVO_BOARD_H
