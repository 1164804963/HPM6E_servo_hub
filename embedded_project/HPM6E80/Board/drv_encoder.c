#include "drv_encoder.h"

#include "encoder_mt6816.h"
#include "servo_board.h"

#define TWO_PI_F (6.28318530718f)

/* 中值滤波深度：MT6816 每隔 1ms 读一次，偶尔会读到跨越内部更新边界的跳变值
 * （实测转动时出现 ~600 count 的孤立尖峰，而 300rpm 时每帧只该变 82 count）。
 * 这些尖峰直接把速度观测器带飞，所以取相邻 3 帧的中值把它们滤掉。 */
#define ENC_FILTER_DEPTH    (3U)

static bool s_encoder_ready;
static uint32_t s_sample_fail_cnt;

static uint16_t s_hist[ENC_FILTER_DEPTH];
static uint32_t s_hist_cnt;
static uint16_t s_filtered_raw;

bool drv_encoder_init(void)
{
    s_encoder_ready = encoder_mt6816_init();
    s_hist_cnt = 0U;
    s_filtered_raw = 0U;
    return s_encoder_ready;
}

/* 单圈计数差值，处理 0/16384 回绕。 */
static int32_t enc_delta16(uint16_t now, uint16_t ref)
{
    int32_t d = (int32_t)now - (int32_t)ref;

    if (d > (int32_t)(PMSM_MOTOR_ENC_LINE_P_N / 2U))
    {
        d -= (int32_t)PMSM_MOTOR_ENC_LINE_P_N;
    }
    else if (d < -(int32_t)(PMSM_MOTOR_ENC_LINE_P_N / 2U))
    {
        d += (int32_t)PMSM_MOTOR_ENC_LINE_P_N;
    }
    return d;
}

void drv_encoder_sample(void)
{
    uint16_t raw;

    if (!s_encoder_ready)
    {
        return;
    }
    /* 单帧失败不清状态：缓存保留上一次有效角度，连续失效由上层保护处理。
     * 失败次数累计出来，用来判断编码器线是不是被功率级干扰了。 */
    if (!encoder_mt6816_sample())
    {
        s_sample_fail_cnt++;
        return;
    }
    if (!encoder_mt6816_get_cached_raw(&raw))
    {
        return;
    }

    s_hist[0] = s_hist[1];
    s_hist[1] = s_hist[2];
    s_hist[2] = raw;
    if (++s_hist_cnt < ENC_FILTER_DEPTH)
    {
        s_filtered_raw = raw;
        return;
    }

    /* 三帧取中值：把两端相对中间帧的偏移算出来，中间帧加上"居中的那个偏移"就是中值。 */
    int32_t d_old = enc_delta16(s_hist[0], s_hist[1]);
    int32_t d_new = enc_delta16(s_hist[2], s_hist[1]);
    int32_t median_off;

    if (((d_old >= 0) && (d_new <= 0)) || ((d_old <= 0) && (d_new >= 0)))
    {
        median_off = 0;                        /* 中间帧本来就在两者之间 */
    }
    else if (d_old > 0)
    {
        median_off = (d_old < d_new) ? d_old : d_new;
    }
    else
    {
        median_off = (d_old > d_new) ? d_old : d_new;
    }
    s_filtered_raw = (uint16_t)(((int32_t)s_hist[1] + median_off) & (int32_t)(PMSM_MOTOR_ENC_LINE_P_N - 1U));
}

uint32_t drv_encoder_get_fail_count(void)
{
    return s_sample_fail_cnt;
}

uint32_t drv_encoder_get_cnt(ENCODER_ID id)
{
    if (id != ENCODER_ID_MOTOR || !s_encoder_ready)
    {
        return 0U;
    }
    return (uint32_t)s_filtered_raw;
}

int64_t drv_encoder_get_turns(ENCODER_ID id)
{
    float abs_theta;

    if (id != ENCODER_ID_MOTOR || !s_encoder_ready)
    {
        return 0;
    }
    if (!encoder_mt6816_get_cached_abs_theta_rad(&abs_theta))
    {
        return 0;
    }
    /* 多圈角以重置点为原点，正值/负值都可能，直接截断取整圈数。 */
    return (int64_t)(abs_theta / TWO_PI_F);
}

bool drv_encoder_get_state(ENCODER_ID id)
{
    return (id == ENCODER_ID_MOTOR) && s_encoder_ready && encoder_mt6816_feedback_ok();
}

uint8_t drv_encoder_get_type(ENCODER_ID id)
{
    return (id == ENCODER_ID_MOTOR) ? ENCODER_TYPE_ABS_SPI_MT68XX : ENCODER_TYPE_NONE;
}
