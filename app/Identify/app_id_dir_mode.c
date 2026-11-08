#include "app_id_dir_mode.h"
#include "motor_ctl_loop.h"

static Axis *const axis = &kAxis; // 引用电机对象实例化

static uint16_t s_wait_enable_ms = 0; // 使能建立等待计时（单位：位置环周期）
static uint8_t s_armed = 0;           // 1=本次进入后又看到过"非完成"状态，之后才认 FINISH

AppResult IdDirModeInit(void)
{
    set_app_Controlword(APP_CTRL_DISABLE); //上升沿使能，初始化置0

    /* 辨识电流用应用层"电机额定电流"，并留出余量避开 App 层峰值电流保护
     * （阈值 = 0.9 × 驱动器峰值，见 app_status_check.c）。
     *
     * 原来这里不设置，控制层沿用 pmsm_config.rated_current —— 那是额定电流的峰值
     * （= √2 × 额定），1.2A 电机就是 1.697A，直接越过 0.9×1.52=1.368A 的保护线，
     * 使能后 200ms 内必定被判过流强制失能，辨识永远完不成。
     * 现在辨识 APP 自己给电流，且控制层不再覆盖它（见 MotorCtlParamSetUpdata）。 */
    float i_id = get_app_Motor_rated_current();
    float i_limit = 0.81f * get_app_Motor_peak_current(); // 0.9 × 峰值再留 10% 余量
    if (i_id > i_limit)
    {
        i_id = i_limit;
    }
    if (i_id <= 0.0f)
    {
        i_id = i_limit;
    }
    axis->direction_id_config.id_tar_max_A = i_id;

    /* 清掉上一次辨识残留在输出里的结果：
     * direction_id 模型的 step_num/state_now 只有在"失能->使能"那一个上升沿
     * (ModeCheckInInit) 才会被 direction_id_Init() 复位，而输出的 state_now/direction
     * 是直接挂在轴对象上的。如果上一次辨识停在 3(完成)，重新进入辨识模式时如果
     * 使能沿没建立起来（上位机连写 0/-3/1 时 1kHz 任务看不到中间的 0），
     * 输出就会一直是 3，上位机会立刻显示"辨识成功"，实际电机根本没动。 */
    axis->direction_id_output.state_now = IDENTIFICATION_MODE_STATE_IDLE;
    axis->direction_id_output.direction = 0;
    axis->direction_id_output.elec_angle_tar_rad = 0.0f;

    s_wait_enable_ms = 0;
    s_armed = 0;

    return APP_RET_SUCCESS;
}

AppResult IdDirModeStart(void)
{
    return APP_RET_SUCCESS;
}

AppResult IdDirModeRun(void)
{
    // 辨识运行条件: 1. 使能指令生效 2. 抱闸状态为松闸
    if (get_app_Controlword() == APP_CTRL_ENABLE && get_app_Brake_state() == BRAKE_STATE_RELEASED)
    {
        s_wait_enable_ms = 0;

        if (get_app_Emergency_brake_requested())
        {
            // 触发急停，辨识失败 会自动失能电机
            set_app_Controlword(APP_CTRL_DISABLE);
            return APP_RET_FAIL;
        }

        if (axis->direction_id_output.state_now != IDENTIFICATION_MODE_STATE_FINISH)
        {
            s_armed = 1; // 看到过"运行中/收敛"状态，说明这次辨识真的启动了
        }

        if (axis->direction_id_output.state_now == IDENTIFICATION_MODE_STATE_FINISH && s_armed)
        {
            // 辨识完成 会自动失能电机；这里返回 SUCCESS，让 AppRun 正常结束并调用 Stop，
            // 上位机才能通过 APP 状态拿到"结束"，而不是一直停在"辨识中"。
            set_app_Controlword(APP_CTRL_DISABLE);
            return APP_RET_SUCCESS;
        }

        if (axis->direction_id_output.state_now == IDENTIFICATION_MODE_STATE_ERROR)
        {
            set_app_Controlword(APP_CTRL_DISABLE);
            return APP_RET_FAIL;
        }
    }
    else if (get_app_Controlword() != APP_CTRL_ENABLE)
    {
        /* 使能没建立起来（被保护强制失能 / 上位机撤销 / 桥臂没能放开）。
         * 给 1s 宽限让使能和松闸完成，超时仍不满足就报失败退出，
         * 避免 APP 永远停在 RUNNING、上位机一直显示"辨识中"只能手动停止。 */
        if (++s_wait_enable_ms > 1000U)
        {
            s_wait_enable_ms = 0;
            return APP_RET_FAIL;
        }
    }
    else
    {
        s_wait_enable_ms = 0; // 已使能、只是抱闸还没松到位
    }

    return APP_RET_RUNNING;
}

AppResult IdDirModeStop(void)
{
    s_wait_enable_ms = 0;
    s_armed = 0;
    return APP_RET_SUCCESS;
}
