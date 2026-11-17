#include "servo_can.h"

#include <string.h>

#include "bsp_api.h"
#include "bsp_can.h"
#include "data_param.h"
#include "master_cia402_callback.h"

#if !defined(USE_CANOPEN) && !defined(USE_ENCOS) && !defined(USE_CUSTOM)
#include "hpm_mcan_drv.h"   /* status_mcan_txfifo_full */
#endif

#if defined(USE_CANOPEN)
#include "board.h"
#include "hpm_clock_drv.h"
#include "hpm_gptmr_drv.h"
#include "SlaveOD.h"
#include "states.h"
#include "timer.h"
#endif
#if defined(USE_CAN_MAVLINK_HOST)
#include "mavlink_callback.h"
#include "motor_ctl_loop.h"
#endif

#define SERVO_CAN_DEFAULT_NODE_ID (0x15U)
#define SERVO_CAN_DEFAULT_BITRATE (1000000U)

#if defined(SERVO_CAN_SPLIT_REPLY) && (SERVO_CAN_SPLIT_REPLY == 1)
#define CIA402_REPLY_ID(request_id) ((request_id) | 0x400U)
#else
#define CIA402_REPLY_ID(request_id) (request_id)
#endif

static bool s_ready;
static volatile uint32_t s_node_id = SERVO_CAN_DEFAULT_NODE_ID;
static volatile uint32_t s_active_node_id = SERVO_CAN_DEFAULT_NODE_ID;
static uint32_t s_bitrate_hz = SERVO_CAN_DEFAULT_BITRATE;
static uint32_t s_active_bitrate_hz;
static hpm_stat_t s_last_error = status_success;
static volatile uint32_t s_rx_count;
static volatile uint32_t s_tx_count;
static volatile uint32_t s_tx_error_count;

#if !defined(USE_ENCOS)
/* 只有 FIFO0 的协议入口写这个计数。保持 0 表示尚未收到可处理的请求。 */
static void note_can_activity(void)
{
    s_rx_count++;
    if (s_rx_count == 0U)
    {
        s_rx_count = 1U;
    }
}
#endif

#if !defined(USE_CANOPEN) && !defined(USE_ENCOS) && !defined(USE_CUSTOM)
/*
 * 应答队列：RX 中断只做协议解析、同步执行 OD 回调和入队，实际发送放到前台
 * servo_can_poll()。索引由短临界区保护；生产者和消费者各只有一个。
 * 128 槽是当前功能的有界容量，不承诺超过它的突发不丢。
 */
#define CIA402_REPLY_QUEUE_SLOTS (128U)
#define CIA402_REPLY_QUEUE_MASK  (CIA402_REPLY_QUEUE_SLOTS - 1U)

typedef struct
{
    uint32_t id;             /* 收到请求时算好的应答 ID */
    uint8_t data[8];
} cia402_reply_t;

static cia402_reply_t s_reply_queue[CIA402_REPLY_QUEUE_SLOTS];
static volatile uint32_t s_reply_head;   /* 前台消费者 */
static volatile uint32_t s_reply_tail;   /* RX 中断生产者 */
static volatile uint32_t s_reply_drop_count;
static volatile uint32_t s_reply_highwater;

static uint32_t cia402_reply_pending(void)
{
    return s_reply_tail - s_reply_head;
}

/* 先确认有空位再执行 OD 回调；只有中断生产者写 tail，因此回调后一定还能入队。 */
static bool cia402_reply_queue_has_space(void)
{
    bool has_space;
    uint32_t irq_state = bsp_irq_save();

    has_space = (cia402_reply_pending() < CIA402_REPLY_QUEUE_SLOTS);
    bsp_irq_restore(irq_state);
    return has_space;
}

static void cia402_reply_queue_push(uint32_t id, const uint8_t *data)
{
    uint32_t irq_state = bsp_irq_save();
    uint32_t tail = s_reply_tail;
    cia402_reply_t *entry = &s_reply_queue[tail & CIA402_REPLY_QUEUE_MASK];
    uint32_t pending;

    entry->id = id;
    memcpy(entry->data, data, 8U);
    s_reply_tail = tail + 1U;
    pending = s_reply_tail - s_reply_head;
    if (pending > s_reply_highwater)
    {
        s_reply_highwater = pending;
    }
    bsp_irq_restore(irq_state);
}

/* Same sequence as Y01 fdcan_cia402_handle. Length is bytes, already converted from DLC. */
static void handle_cia402(const bsp_can_frame_t *rx)
{
    uint8_t is_write;
    uint16_t obj_index;
    uint8_t obj_subindex;
    uint32_t obj_data = 0U;
    uint32_t reply_id;
    uint8_t data_length;
    uint8_t tx_data[8];
    uint32_t od_result;

    if (rx->extended || rx->remote || (rx->id != s_active_node_id))
    {
        return;
    }

    if (rx->len < 5U)
    {
        return;
    }

    is_write = rx->data[0];
    obj_index = (uint16_t)((uint16_t)rx->data[1] | ((uint16_t)rx->data[2] << 8));
    obj_subindex = rx->data[3];
    data_length = (uint8_t)(rx->len - 4U);
    switch (data_length)
    {
    case 1U:
        obj_data = rx->data[4];
        break;
    case 2U:
        obj_data = (uint32_t)rx->data[4] | ((uint32_t)rx->data[5] << 8);
        break;
    case 4U:
        obj_data = (uint32_t)rx->data[4] |
                   ((uint32_t)rx->data[5] << 8) |
                   ((uint32_t)rx->data[6] << 16) |
                   ((uint32_t)rx->data[7] << 24);
        break;
    default:
        return;
    }

    if ((is_write != 0U) && (is_write != 1U))
    {
        return;
    }

    /* 长度和 opcode 已确认是本节点可处理的数据请求；OD 失败/队满仍算收到。 */
    note_can_activity();

    /* 应答 ID 在收到请求时确定；后续节点变化不改已排队帧的目标。 */
    reply_id = CIA402_REPLY_ID(rx->id);

    /* 队满时不执行 OD 回调：避免形成没有对应应答的部分动作，并明确计数。 */
    if (!cia402_reply_queue_has_space())
    {
        s_reply_drop_count++;
        s_tx_error_count++;
        return;
    }

    if (is_write == 1U)
    {
        od_result = master_cia402_write_callback(obj_index, obj_subindex, &obj_data);
    }
    else
    {
        od_result = master_cia402_read_callback(obj_index, obj_subindex, &obj_data);
    }

    if (od_result != 0U)
    {
        /* OD 回调失败：应答固定为 8 字节 abort 帧。 */
        tx_data[0] = 0x80U;
        tx_data[1] = (uint8_t)(obj_index & 0xFFU);
        tx_data[2] = (uint8_t)((obj_index >> 8) & 0xFFU);
        tx_data[3] = obj_subindex;
        tx_data[4] = (uint8_t)(od_result & 0xFFU);
        tx_data[5] = (uint8_t)((od_result >> 8) & 0xFFU);
        tx_data[6] = (uint8_t)((od_result >> 16) & 0xFFU);
        tx_data[7] = (uint8_t)((od_result >> 24) & 0xFFU);
    }
    else
    {
        tx_data[0] = is_write;
        tx_data[1] = (uint8_t)(obj_index & 0xFFU);
        tx_data[2] = (uint8_t)((obj_index >> 8) & 0xFFU);
        tx_data[3] = obj_subindex;
        tx_data[4] = (uint8_t)(obj_data & 0xFFU);
        tx_data[5] = (uint8_t)((obj_data >> 8) & 0xFFU);
        tx_data[6] = (uint8_t)((obj_data >> 16) & 0xFFU);
        tx_data[7] = (uint8_t)((obj_data >> 24) & 0xFFU);
    }

    cia402_reply_queue_push(reply_id, tx_data);
}
#endif

void servo_can_poll(void)
{
#if !defined(USE_CANOPEN) && !defined(USE_ENCOS) && !defined(USE_CUSTOM)
    uint32_t attempts;

    for (attempts = 0U; attempts < 8U; attempts++)
    {
        cia402_reply_t reply;
        hpm_stat_t status;
        uint32_t irq_state;

        irq_state = bsp_irq_save();
        if (s_reply_head == s_reply_tail)
        {
            bsp_irq_restore(irq_state);
            break;
        }
        reply = s_reply_queue[s_reply_head & CIA402_REPLY_QUEUE_MASK];
        bsp_irq_restore(irq_state);

        /* MCAN 提交窗口：SDK 在 HPM6E80 上是非阻塞写入（TXFIFO 满立即返回），
         * 这里只关一个很短的窗口，避免与使能透传时的 ISR 发送交错。 */
        irq_state = bsp_irq_save();
        status = bsp_can_send(reply.id, reply.data, 8U);
        bsp_irq_restore(irq_state);
        if (status == status_success)
        {
            irq_state = bsp_irq_save();
            s_reply_head++;
            s_tx_count++;
            bsp_irq_restore(irq_state);
            continue;
        }
        if (status == status_mcan_txfifo_full)
        {
            /* 硬件 TXFIFO 暂忙：保留队首，下次前台继续尝试，不计丢包。 */
            break;
        }

        /* 其他发送错误：丢弃这一帧并明确计数，避免队首永久阻塞。 */
        irq_state = bsp_irq_save();
        s_reply_head++;
        s_tx_error_count++;
        bsp_irq_restore(irq_state);
    }
#else
    /* CANopen/ENCOS/CUSTOM 保持原有发送路径，不经过应答队列。 */
#endif
}

#if defined(USE_CANOPEN)
/* SDO 服务端请求：只认实际配置的客户端->服务端 COB-ID，且 ccs 在 0..4。 */
static bool canopen_sdo_request_counts(const bsp_can_frame_t *rx)
{
    UNS16 offset;

    if ((rx->id < 0x580U) || (rx->id > 0x67FU) ||
        (SlaveOD_Data.firstIndex->SDO_SVR == 0U))
    {
        return false;
    }
    for (offset = SlaveOD_Data.firstIndex->SDO_SVR;
         offset <= SlaveOD_Data.lastIndex->SDO_SVR; offset++)
    {
        UNS32 cob_id = *(UNS32 *)SlaveOD_Data.objdict[offset].pSubindex[1].pObject;

        if (cob_id == rx->id)
        {
            return (rx->data[0] >> 5) <= 4U;
        }
    }
    return false;
}

/* RPDO 请求：COB-ID 与实际 0x1400 配置匹配，长度满足当前映射。 */
static bool canopen_rpdo_counts(const bsp_can_frame_t *rx)
{
    UNS16 offset;

    if ((rx->id < 0x180U) || (rx->id > 0x57FU) ||
        (SlaveOD_Data.firstIndex->PDO_RCV == 0U))
    {
        return false;
    }
    for (offset = SlaveOD_Data.firstIndex->PDO_RCV;
         offset <= SlaveOD_Data.lastIndex->PDO_RCV; offset++)
    {
        UNS16 map_offset;
        UNS8 map_count;
        UNS8 i;
        UNS32 bits = 0U;
        bool valid = true;

        if (*(UNS32 *)SlaveOD_Data.objdict[offset].pSubindex[1].pObject != rx->id)
        {
            continue;
        }
        map_offset = (UNS16)(SlaveOD_Data.firstIndex->PDO_RCV_MAP +
                             (offset - SlaveOD_Data.firstIndex->PDO_RCV));
        if (map_offset > SlaveOD_Data.lastIndex->PDO_RCV_MAP)
        {
            return false;
        }
        map_count = *(UNS8 *)SlaveOD_Data.objdict[map_offset].pSubindex[0].pObject;
        if ((map_count == 0U) ||
            (map_count >= SlaveOD_Data.objdict[map_offset].bSubCount))
        {
            return false;
        }
        for (i = 0U; i < map_count; i++)
        {
            UNS32 param = *(UNS32 *)SlaveOD_Data.objdict[map_offset].pSubindex[i + 1U].pObject;
            UNS8 size = (UNS8)(param & 0xFFU);

            if (size == 0U)
            {
                valid = false;
                break;
            }
            bits += size;
        }
        return valid && (bits <= 64U) &&
               (rx->len >= (uint8_t)((bits + 7U) / 8U)) && (rx->len <= 8U);
    }
    return false;
}

/* CANopen 计数资格：本节点可处理的经典入站请求，不代替协议栈校验。 */
static bool canopen_rx_counts(const bsp_can_frame_t *rx)
{
    uint8_t node = *SlaveOD_Data.bDeviceNodeId;

    /* CANopen FD 未实现，只覆盖 0..8 字节经典数据帧。 */
    if (rx->extended || rx->canfd || (rx->len > 8U))
    {
        return false;
    }
    if (rx->remote)
    {
        return (rx->id == (0x700U + node)) && (rx->len == 0U) &&
               (SlaveOD_Data.CurrentCommunicationState.csLifeGuard != 0);
    }
    if (rx->id == 0x000U)
    {
        return (rx->len == 2U) &&
               ((rx->data[1] == 0U) || (rx->data[1] == node)) &&
               (SlaveOD_Data.nodeState == Pre_operational ||
                SlaveOD_Data.nodeState == Operational ||
                SlaveOD_Data.nodeState == Stopped) &&
               ((rx->data[0] == 0x01U) || (rx->data[0] == 0x02U) ||
                (rx->data[0] == 0x80U) || (rx->data[0] == 0x81U) ||
                (rx->data[0] == 0x82U));
    }
    if (rx->id == 0x080U)
    {
        return (rx->len == 0U) &&
               (SlaveOD_Data.CurrentCommunicationState.csSYNC != 0);
    }
    if ((SlaveOD_Data.CurrentCommunicationState.csSDO != 0) &&
        (rx->len == 8U) && canopen_sdo_request_counts(rx))
    {
        return true;
    }
    return (SlaveOD_Data.CurrentCommunicationState.csPDO != 0) &&
           canopen_rpdo_counts(rx);
}

static void handle_canopen(const bsp_can_frame_t *rx)
{
    Message message;

    memset(&message, 0, sizeof(message));
    message.cob_id = (UNS16)rx->id;
    message.rtr = rx->remote ? 1U : 0U;
    message.len = (rx->len > 8U) ? 8U : rx->len;
    if (message.len > 0U)
    {
        memcpy(message.data, rx->data, message.len);
    }
    if (canopen_rx_counts(rx))
    {
        note_can_activity();
    }
    canDispatch(&SlaveOD_Data, &message);
    if ((message.cob_id == 0x080U) && (SlaveOD_Data.nodeState == Operational))
    {
        set_app_Target_update_state(true);
    }
}

/*
 * CanFestival 定时器契约（protocol/CANopen/src/timer.c、inc/hw_cm7/timerscfg.h）：
 *   TIMEVAL_MAX = 0xFFFF，单次等待最长 65.535 ms，因此不需要更宽的时间基准。
 *   setTimer(v)       从“当前时刻”起 v µs 后唤醒；SetAlarm 中途重装也保留同一 epoch。
 *   getElapsedTime()  返回“自上次 TimeDispatch 以来”的累计 µs，**只读不推进**——
 *                     SetAlarm 会连续调用它比较多个闹钟，推进会把同一段时间重复计入。
 *   截止中断里先把 epoch 设成“计划截止时刻”再 TimeDispatch，使 overrun 只包含中断延迟。
 *
 * 硬件：GPTMR2 通道 1 自由计数（100 MHz → 100 tick/µs），32 位计数器 42.9 s 回绕。
 * 软件维护一个 32 位 µs 时钟（71 min 回绕，差值按无符号取模），tick→µs 的余数
 * 累积在 s_tmr_us_rem 里，避免每次采样截断导致时钟偏慢。
 */
#define CANOPEN_TMR_CH (1U)

static uint32_t s_tmr_ticks_per_us;   /* 0 = 定时器未启动 */
static uint32_t s_tmr_tick_last;      /* 上次推进 µs 时钟时的硬件计数 */
static uint32_t s_tmr_us_now;         /* 自由运行 µs 时钟 */
static uint32_t s_tmr_us_rem;         /* 未满 1 µs 的 tick 余量 */
static uint32_t s_tmr_epoch_us;       /* 上次 TimeDispatch 的时间点 */
static uint32_t s_tmr_deadline_us;    /* 已装载的唤醒时刻 */

/* 持锁调用：采样硬件计数并推进 µs 时钟。采样与状态更新必须在同一临界区。 */
static uint32_t canopen_timer_sample_locked(uint32_t *raw_out)
{
    uint32_t raw = gptmr_channel_get_counter(BOARD_BLDC_TMR_1MS, CANOPEN_TMR_CH,
                                             gptmr_counter_type_normal);
    uint32_t ticks = (uint32_t)(raw - s_tmr_tick_last) + s_tmr_us_rem;

    s_tmr_tick_last = raw;
    s_tmr_us_now += ticks / s_tmr_ticks_per_us;
    s_tmr_us_rem = ticks % s_tmr_ticks_per_us;
    if (raw_out != NULL)
    {
        *raw_out = raw;
    }
    return s_tmr_us_now;
}

/* 单次装载上限：剩余 µs 换算成 tick 后必须留在 32 位内（≈21 s @100 MHz）。
 * 更长的等待由 ISR 重新装载，不会丢截止点，也不需要专门的框架。 */
static uint32_t canopen_timer_max_arm_us(void)
{
    return 0x7FFFFFFFU / s_tmr_ticks_per_us;
}

/* 持锁调用：把比较值装到 s_tmr_deadline_us。 */
static void canopen_timer_arm_locked(uint32_t now_us, uint32_t raw_now)
{
    int32_t remain_us = (int32_t)(s_tmr_deadline_us - now_us);
    uint32_t wait_us;
    uint32_t ticks;

    if (remain_us <= 0)
    {
        ticks = 1U;                       /* 已到点：下一个 tick 进 ISR */
    }
    else
    {
        wait_us = (uint32_t)remain_us;
        if (wait_us > canopen_timer_max_arm_us())
        {
            wait_us = canopen_timer_max_arm_us();
        }
        ticks = wait_us * s_tmr_ticks_per_us;
    }
    /* 装载期间计数仍在走，零等待/极短等待可能在写比较值前已经到点。
     * 写后确认目标还在前方，否则给出 2 us 的装载余量再试，避免漏等一整圈。 */
    for (;;)
    {
        uint32_t target = raw_now + ticks;
        uint32_t raw_after;

        /* 驱动通常写 cmp-1；0/UINT32_MAX 特殊值最多使事件晚一个 tick。 */
        gptmr_update_cmp(BOARD_BLDC_TMR_1MS, CANOPEN_TMR_CH, 0, target + 1U);
        raw_after = gptmr_channel_get_counter(BOARD_BLDC_TMR_1MS, CANOPEN_TMR_CH,
                                             gptmr_counter_type_normal);
        if ((int32_t)(raw_after - target) < 0)
        {
            break;
        }
        (void)canopen_timer_sample_locked(&raw_now);
        ticks = 2U * s_tmr_ticks_per_us;
    }
}

void servo_canopen_timer_start(void)
{
    gptmr_channel_config_t config;
    uint32_t hz = clock_get_frequency(BOARD_BLDC_TMR_CLOCK);
    uint32_t irq_state;

    s_tmr_ticks_per_us = hz / 1000000U;
    if (s_tmr_ticks_per_us == 0U)
    {
        return;
    }

    gptmr_channel_get_default_config(BOARD_BLDC_TMR_1MS, &config);
    /* 自由计数：32 位计数器回绕由 µs 时钟吸收；cmp 先给满量程表示"不比较"。 */
    config.cmp[0] = 0xFFFFFFFFU;
    config.cmp[1] = 0U;
    config.reload = 0xFFFFFFFFU;
    config.debug_mode = 0;
    gptmr_enable_irq(BOARD_BLDC_TMR_1MS, GPTMR_CH_CMP_IRQ_MASK(CANOPEN_TMR_CH, 0));
    gptmr_channel_config(BOARD_BLDC_TMR_1MS, CANOPEN_TMR_CH, &config, true);
    gptmr_clear_status(BOARD_BLDC_TMR_1MS, GPTMR_CH_CMP_IRQ_MASK(CANOPEN_TMR_CH, 0));

    irq_state = bsp_irq_save();
    s_tmr_tick_last = gptmr_channel_get_counter(BOARD_BLDC_TMR_1MS, CANOPEN_TMR_CH,
                                                gptmr_counter_type_normal);
    s_tmr_us_now = 0U;
    s_tmr_us_rem = 0U;
    s_tmr_epoch_us = 0U;
    /* CanFestival 的 total_sleep_time 初值就是 TIMEVAL_MAX。第一段没有任何
     * 闹钟时也必须有一次唤醒，否则 "首个闹钟 > TIMEVAL_MAX" 永远装不上。 */
    s_tmr_deadline_us = (uint32_t)TIMEVAL_MAX;
    canopen_timer_arm_locked(s_tmr_us_now, s_tmr_tick_last);
    bsp_irq_restore(irq_state);
}

void servo_canopen_timer_isr(void)
{
    uint32_t irq_state;
    uint32_t raw_now;
    uint32_t now;

    if (!gptmr_check_status(BOARD_BLDC_TMR_1MS, GPTMR_CH_CMP_IRQ_MASK(CANOPEN_TMR_CH, 0)))
    {
        return;
    }
    gptmr_clear_status(BOARD_BLDC_TMR_1MS, GPTMR_CH_CMP_IRQ_MASK(CANOPEN_TMR_CH, 0));

    irq_state = bsp_irq_save();
    now = canopen_timer_sample_locked(&raw_now);
    if ((int32_t)(now - s_tmr_deadline_us) < 0)
    {
        /* 比较值量化提前 1 tick 触发，或上次只装了分段上限：按剩余时间重装。 */
        canopen_timer_arm_locked(now, raw_now);
        bsp_irq_restore(irq_state);
        return;
    }
    /* 截止时刻作为新 epoch：TimeDispatch 里的 getElapsedTime 只返回中断延迟。 */
    s_tmr_epoch_us = s_tmr_deadline_us;
    bsp_irq_restore(irq_state);

    TimeDispatch();
}

void setTimer(TIMEVAL value)
{
    uint32_t irq_state;
    uint32_t raw_now;
    uint32_t now;

    if (s_tmr_ticks_per_us == 0U)
    {
        return;
    }

    irq_state = bsp_irq_save();
    now = canopen_timer_sample_locked(&raw_now);
    s_tmr_deadline_us = now + (uint32_t)value;   /* value <= TIMEVAL_MAX */
    canopen_timer_arm_locked(now, raw_now);
    bsp_irq_restore(irq_state);
}

TIMEVAL getElapsedTime(void)
{
    uint32_t irq_state;
    uint32_t elapsed_us;

    if (s_tmr_ticks_per_us == 0U)
    {
        return 0U;
    }

    irq_state = bsp_irq_save();
    (void)canopen_timer_sample_locked(NULL);
    /* 只读：epoch 只由截止中断推进，SetAlarm 连续调用不会消耗时间。 */
    elapsed_us = s_tmr_us_now - s_tmr_epoch_us;
    bsp_irq_restore(irq_state);
    return elapsed_us;
}

unsigned char canSend(CAN_PORT notused, Message *message)
{
    (void)notused;
    if (message == NULL)
    {
        return 0U;
    }
    if (bsp_can_send_classic(message->cob_id, false, message->rtr != 0U,
                             message->data, message->len) != status_success)
    {
        return 0U;
    }
    return 1U;
}
#elif defined(USE_ENCOS)
/* Y01 fdcan_encos_handle is an empty placeholder. */
static void handle_encos(const bsp_can_frame_t *rx)
{
    (void)rx;
}
#elif defined(USE_CUSTOM)
static void handle_custom(const bsp_can_frame_t *rx)
{
    if (!rx->remote && (rx->len <= (rx->canfd ? 64U : 8U)))
    {
        note_can_activity();
    }
    if (rx->canfd)
    {
        (void)bsp_can_send_fd(s_node_id, rx->extended, rx->bitrate_switch, rx->data, rx->len);
    }
    else
    {
        (void)bsp_can_send_classic(s_node_id, rx->extended, false, rx->data, rx->len);
    }
}
#endif

void bsp_can_on_rx(const bsp_can_frame_t *frame)
{
    if (frame == 0)
    {
        return;
    }
#if defined(USE_CANOPEN)
    handle_canopen(frame);
#elif defined(USE_ENCOS)
    handle_encos(frame);
#elif defined(USE_CUSTOM)
    handle_custom(frame);
#else
    handle_cia402(frame);
#endif
}

hpm_stat_t servo_can_init(uint32_t node_id, uint32_t bitrate_hz)
{
    hpm_stat_t status;

    s_node_id = node_id;
    s_bitrate_hz = bitrate_hz;
    s_rx_count = 0U;
    s_tx_count = 0U;
    s_tx_error_count = 0U;
    s_active_bitrate_hz = 0U;
#if !defined(USE_CANOPEN) && !defined(USE_ENCOS) && !defined(USE_CUSTOM)
    s_reply_head = 0U;
    s_reply_tail = 0U;
    s_reply_drop_count = 0U;
    s_reply_highwater = 0U;
#endif

#if !defined(USE_CANOPEN) && !defined(USE_ENCOS) && !defined(USE_CUSTOM)
#if defined(SERVO_CAN_SPLIT_REPLY) && (SERVO_CAN_SPLIT_REPLY == 1)
    if (node_id > 0x3FFU)
#else
    if (node_id > 0x7FFU)
#endif
    {
        s_last_error = status_invalid_argument;
        s_ready = false;
        return status_invalid_argument;
    }
#endif

    status = bsp_can_init(node_id, bitrate_hz);
#if defined(USE_CANOPEN)
    if (status == status_success)
    {
        servo_canopen_timer_start();
        setNodeId(&SlaveOD_Data, (UNS8)s_node_id);
        setState(&SlaveOD_Data, Initialisation);
        setState(&SlaveOD_Data, Operational);
    }
#endif
    s_last_error = status;
    s_ready = (status == status_success);
    if (s_ready)
    {
        s_active_node_id = node_id;
        s_active_bitrate_hz = bitrate_hz;
    }
    return status;
}

void servo_can_get_status(servo_can_status_t *status)
{
    if (status == 0)
    {
        return;
    }

    status->ready = s_ready;
    status->node_id = s_node_id;
    status->active_node_id = s_active_node_id;
    status->bitrate_hz = s_bitrate_hz;
    status->active_bitrate_hz = s_active_bitrate_hz;
    status->last_error = s_last_error;
    status->rx_count = s_rx_count;
    status->tx_count = s_tx_count;
    status->tx_error_count = s_tx_error_count;
    status->overflow_count = bsp_can_overflow_count();
    status->busoff_count = bsp_can_busoff_count();
#if !defined(USE_CANOPEN) && !defined(USE_ENCOS) && !defined(USE_CUSTOM)
    {
        uint32_t irq_state = bsp_irq_save();

        status->reply_pending = cia402_reply_pending();
        status->reply_drop_count = s_reply_drop_count;
        status->reply_highwater = s_reply_highwater;
        bsp_irq_restore(irq_state);
    }
    status->reply_id = s_ready ? CIA402_REPLY_ID(s_active_node_id) : 0U;
#if defined(SERVO_CAN_SPLIT_REPLY) && (SERVO_CAN_SPLIT_REPLY == 1)
    status->split_reply = true;
    status->legacy_same_id = false;
#else
    status->split_reply = false;
    status->legacy_same_id = true;
#endif
#else
    status->reply_id = 0U;
    status->split_reply = false;
    status->legacy_same_id = false;
    status->reply_pending = 0U;
    status->reply_drop_count = 0U;
    status->reply_highwater = 0U;
#endif
}

/* Node ID is used on the next frame. Baudrate is stored until the next init. */
bool bsp_can_port_is_ready(bool debug_port)
{
    (void)debug_port;
    return s_ready;
}

void bsp_set_can_id(uint32_t can_id)
{
    s_node_id = can_id;
#if !defined(USE_CANOPEN)
    /* CAN_CIA402: node ID is compared on every frame, so the next frame uses the new ID.
     * 已排队的应答保留接收时算出的 ID，不随这次修改重定向。 */
    s_active_node_id = can_id;
#endif
}

uint32_t bsp_get_can_id(void)
{
    return s_node_id;
}

void bsp_set_can_baudrate(uint32_t baudrate)
{
    s_bitrate_hz = baudrate;
}

uint32_t bsp_get_can_baudrate(void)
{
    return s_bitrate_hz;
}

uint32_t bsp_get_can_mg_counts(void)
{
    return s_rx_count;
}

#if IS_USE_CAN_PASSTHROUGH
#define CAN_POS_PRIORITY  26
#define CAN_POS_SYSID     21
#define CAN_POS_COMPID    13
#define CAN_POS_FLAG_CAST 11
#define CAN_POS_TRANS_SEQ 6
#define CAN_POS_CNT_OF_TX 3
#define CAN_POS_FLAG_END  2
#define CAN_POS_VERSION   0
#define CANFD_MESSAGE     1U
#define CANFD_DEBUG       2U

static uint8_t s_mav_seq;

void bsp_can_on_rx_fifo1(const bsp_can_frame_t *frame)
{
    if ((frame == 0) || frame->bitrate_switch)
    {
        return;
    }
    MavlinkRecvCallback(&kAxis, &kAxisDw, (uint8_t *)frame->data, frame->len);
}

static uint8_t mav_send_packet(uint8_t *data, uint16_t len, uint8_t sys_id, uint8_t comp_id,
                               uint8_t priority, uint8_t channel)
{
    uint32_t id_base = 0U;
    uint16_t sent = 0U;
    uint8_t count = 0U;

    id_base |= ((uint32_t)priority & 0x07U) << CAN_POS_PRIORITY;
    id_base |= ((uint32_t)sys_id & 0x1FU) << CAN_POS_SYSID;
    id_base |= ((uint32_t)comp_id & 0xFFU) << CAN_POS_COMPID;
    id_base |= (0U << CAN_POS_FLAG_CAST);

    while (sent < len)
    {
        uint8_t chunk = (uint8_t)((len - sent) > 64U ? 64U : (len - sent));
        uint8_t flag_end = ((uint16_t)(sent + chunk) < len) ? 1U : 0U;
        uint32_t id = id_base;
        bool brs = (channel != CANFD_DEBUG);

        id |= ((uint32_t)s_mav_seq & 0x1FU) << CAN_POS_TRANS_SEQ;
        id |= ((uint32_t)count & 0x07U) << CAN_POS_CNT_OF_TX;
        id |= ((uint32_t)flag_end & 0x01U) << CAN_POS_FLAG_END;
        if (bsp_can_send_fd(id, true, brs, data + sent, chunk) != status_success)
        {
            return 1U;
        }
        sent = (uint16_t)(sent + chunk);
        count++;
        if (count > 7U)
        {
            break;
        }
    }
    s_mav_seq = (uint8_t)((s_mav_seq + 1U) & 0x1FU);
    return 0U;
}

void servo_can_mavlink_send(uint8_t *pdata, uint32_t len)
{
    if ((pdata == 0) || (len > 0xFFFFU))
    {
        return;
    }
    (void)mav_send_packet(pdata, (uint16_t)len, get_app_Sys_id(), get_app_Comp_id(), 1U, CANFD_MESSAGE);
}

/* Y01 maps the CAN node to the MAVLink component id and ignores a direct mav-id write. */
void bsp_set_can_mav_id(uint8_t sys_id, uint8_t comp_id)
{
    (void)sys_id;
    (void)comp_id;
}

void bsp_get_can_mav_id(uint8_t *sys_id, uint8_t *comp_id)
{
    if (sys_id != 0)
    {
        *sys_id = 1U;
    }
    if (comp_id != 0)
    {
        *comp_id = (uint8_t)(s_node_id & 0xFFU);
    }
}
#endif
