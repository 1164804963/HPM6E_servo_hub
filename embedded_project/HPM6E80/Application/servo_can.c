#include "servo_can.h"

#include <string.h>

#include "bsp_api.h"
#include "bsp_can.h"
#include "app_status_check.h"
#include "data_param.h"
#include "master_cia402_callback.h"

#if !defined(USE_CANOPEN) && !defined(USE_ENCOS) && !defined(USE_CUSTOM)
#include "hpm_mcan_drv.h"   /* status_mcan_txfifo_full */
#elif IS_USE_CAN_PASSTHROUGH
#include "hpm_mcan_drv.h"   /* MAV 发送同样需要区分 status_mcan_txfifo_full */
#endif

#if defined(USE_CANOPEN)
#include "board.h"
#include "hpm_clock_drv.h"
#include "hpm_gptmr_drv.h"
#include "hpm_interrupt.h"
#include "SlaveOD.h"
#include "states.h"
#include "timer.h"
#include "pdo.h"
#include "lifegrd.h"
#include "objacces.h"
#endif
#if defined(USE_ENCOS)
#error "USE_ENCOS is unsupported: the ENCOS transport has no implementation"
#endif

#if defined(USE_CAN_MAVLINK_HOST)
#include "mavlink_callback.h"
#include "motor_ctl_loop.h"
#endif
#if IS_USE_CAN_PASSTHROUGH
#include "hpm_clock_drv.h"  /* clock_get_frequency: 200ms 超时换算 */
#endif

#define SERVO_CAN_DEFAULT_NODE_ID (0x15U)
#define SERVO_CAN_DEFAULT_BITRATE (1000000U)

#if defined(SERVO_CAN_SPLIT_REPLY) && (SERVO_CAN_SPLIT_REPLY == 1)
#define CIA402_REPLY_ID(request_id) ((request_id) | 0x400U)
#else
#define CIA402_REPLY_ID(request_id) (request_id)
#endif

static volatile bool s_ready;
static volatile uint32_t s_node_id = SERVO_CAN_DEFAULT_NODE_ID;
static volatile uint32_t s_active_node_id = SERVO_CAN_DEFAULT_NODE_ID;
static uint32_t s_bitrate_hz = SERVO_CAN_DEFAULT_BITRATE;
static uint32_t s_active_bitrate_hz;
static hpm_stat_t s_last_error = status_success;
static volatile uint32_t s_rx_count;
static volatile uint32_t s_tx_count;
static volatile uint32_t s_tx_error_count;

#if IS_USE_CAN_PASSTHROUGH
static void servo_can_mav_on_rx_frame(const bsp_can_frame_t *frame);
static void servo_can_mav_poll(void);
static void servo_can_mav_transport_reset(void);
static void servo_can_mav_status_fill(servo_can_status_t *status);

/* 初始化成功后锁定的 MAV 组件 ID; 运行期改 CAN ID 不改它。 */
static volatile uint8_t s_active_component = 21U;
#endif

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

    /* 只有同步模式的目标对象写入成功才通知上层刷新目标；应答顺序保持在后。 */
    if ((is_write == 1U) && (od_result == 0U) && (obj_subindex == 0U))
    {
        int8_t mode = get_app_Modes_of_operation();

        if (((obj_index == 0x607AU) && (mode == MOTOR_CTL_SM_MODE_CSP)) ||
            ((obj_index == 0x60FFU) && (mode == MOTOR_CTL_SM_MODE_CSV)) ||
            ((obj_index == 0x6071U) && (mode == MOTOR_CTL_SM_MODE_CST)))
        {
            set_app_Target_update_state(true);
        }
    }

    cia402_reply_queue_push(reply_id, tx_data);
}
#endif

#if defined(USE_CANOPEN)
static uint32_t canopen_stack_lock(void);
static void canopen_stack_unlock(uint32_t enabled);
static void canopen_consumer_fault_poll_locked(void);
#endif

void servo_can_poll(void)
{
#if IS_USE_CAN_PASSTHROUGH
    /* 透传: 先完成 MAV 重装, 再走各总线原有的前台发送, 避免普通应答饿死 MAV。 */
    servo_can_mav_poll();
#endif
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
#if defined(USE_CANOPEN)
    uint32_t lock_state = canopen_stack_lock();

    canopen_consumer_fault_poll_locked();
    canopen_stack_unlock(lock_state);
#else
    /* ENCOS/CUSTOM 保持原有发送路径，不经过应答队列。 */
#endif
#endif
}

#if defined(USE_CANOPEN)
/* CANopen 协议栈不可重入:RX 中断的 canDispatch() 与 GPTMR2 的 TimeDispatch()
 * 共用 OD 和定时器链表。这里只屏蔽可能进入协议栈的两个源,20kHz ADC 中断保持使能;
 * GPTMR2 与 1ms 节拍共用,只会延迟一次有界调用。 */
#define CANOPEN_LOCK_MCAN (1U << 1U)
#define CANOPEN_LOCK_TMR  (1U << 0U)

static uint32_t canopen_stack_lock(void)
{
    volatile uint32_t *enable = (volatile uint32_t *)(HPM_PLIC_BASE + HPM_PLIC_ENABLE_OFFSET +
        ((uint32_t)HPM_PLIC_TARGET_M_MODE << HPM_PLIC_ENABLE_SHIFT_PER_TARGET));
    uint32_t irq_state;
    uint32_t enabled;

    /* PLIC 没有读使能位的接口,按使能寄存器布局直接取位。 */
    irq_state = bsp_irq_save();
    enabled = ((enable[(uint32_t)BOARD_APP_CAN_IRQn >> 5U] >> ((uint32_t)BOARD_APP_CAN_IRQn & 31U)) & 1U) << 1U;
    enabled |= (enable[(uint32_t)BOARD_BLDC_TMR_IRQ >> 5U] >> ((uint32_t)BOARD_BLDC_TMR_IRQ & 31U)) & 1U;
    intc_m_disable_irq(BOARD_APP_CAN_IRQn);
    intc_m_disable_irq(BOARD_BLDC_TMR_IRQ);
    bsp_irq_restore(irq_state);
    return enabled;
}

/* 按进入时的使能状态恢复,支持中断源原本就被关掉的嵌套场景。 */
static void canopen_stack_unlock(uint32_t enabled)
{
    uint32_t irq_state = bsp_irq_save();

    if ((enabled & CANOPEN_LOCK_MCAN) != 0U)
    {
        intc_m_enable_irq(BOARD_APP_CAN_IRQn);
    }
    else
    {
        intc_m_disable_irq(BOARD_APP_CAN_IRQn);
    }
    if ((enabled & CANOPEN_LOCK_TMR) != 0U)
    {
        intc_m_enable_irq(BOARD_BLDC_TMR_IRQ);
    }
    else
    {
        intc_m_disable_irq(BOARD_BLDC_TMR_IRQ);
    }
    bsp_irq_restore(irq_state);
}

#define CANOPEN_APPLIED_SLOTS (9U)
#define CANOPEN_HB_CONSUMER_SLOTS (1U) /* 实际字典 1016 只有一个消费者 */

typedef struct
{
    const indextable *table;
    UNS8 subindex;
    UNS32 value;
} canopen_applied_t;

static canopen_applied_t s_applied[CANOPEN_APPLIED_SLOTS];
static UNS8 s_applied_count;

static bool canopen_applied_is_pdo(UNS16 index)
{
    return ((index >= 0x1400U) && (index <= 0x1403U)) ||
           ((index >= 0x1800U) && (index <= 0x1803U));
}

static canopen_applied_t *canopen_applied_lookup(const indextable *table, UNS8 subindex)
{
    UNS8 i;

    for (i = 0U; i < s_applied_count; i++)
    {
        if ((s_applied[i].table == table) && (s_applied[i].subindex == subindex))
        {
            return &s_applied[i];
        }
    }
    return NULL;
}

static bool canopen_applied_pdo_conflict(const canopen_applied_t *own, UNS16 id)
{
    UNS8 i;

    for (i = 0U; i < s_applied_count; i++)
    {
        const canopen_applied_t *slot = &s_applied[i];

        if ((slot == own) || !canopen_applied_is_pdo(slot->table->index))
        {
            continue;
        }
        if (((slot->value & 0x80000000U) == 0U) && ((slot->value & 0x7FFU) == id))
        {
            return true;
        }
    }
    return false;
}

static bool canopen_applied_hb_conflict(UNS16 id)
{
    UNS8 i;

    for (i = 0U; i < s_applied_count; i++)
    {
        UNS32 value = s_applied[i].value;

        if ((s_applied[i].table->index != 0x1016U) || ((value & 0xFFFFU) == 0U))
        {
            continue;
        }
        if (id == (UNS16)(0x700U + ((value >> 16) & 0x7FU)))
        {
            return true;
        }
    }
    return false;
}

static bool canopen_applied_hb_pdo_conflict(UNS8 node)
{
    UNS8 i;

    for (i = 0U; i < s_applied_count; i++)
    {
        UNS32 value = s_applied[i].value;

        if (!canopen_applied_is_pdo(s_applied[i].table->index))
        {
            continue;
        }
        if (((value & 0x80000000U) == 0U) &&
            ((value & 0x7FFU) == (UNS32)(0x700U + node)))
        {
            return true;
        }
    }
    return false;
}

static bool canopen_sdo_cob_conflict(UNS16 id)
{
    UNS16 offset = SlaveOD_Data.firstIndex->SDO_SVR;

    if ((offset == 0U) || (offset > SlaveOD_Data.lastIndex->SDO_SVR) ||
        (SlaveOD_Data.objdict[offset].bSubCount <= 2U))
    {
        return false;
    }
    return (*(UNS32 *)SlaveOD_Data.objdict[offset].pSubindex[1].pObject == id) ||
           (*(UNS32 *)SlaveOD_Data.objdict[offset].pSubindex[2].pObject == id);
}

static bool canopen_pdo_value_valid(const canopen_applied_t *slot, UNS32 value)
{
    UNS32 allowed;
    UNS16 id;

    if ((slot->table->index >= 0x1400U) && (slot->table->index <= 0x1403U))
    {
        allowed = 0x800007FFU;
    }
    else if ((slot->table->index >= 0x1800U) && (slot->table->index <= 0x1803U))
    {
        allowed = 0xC00007FFU;
    }
    else
    {
        return false;
    }
    if ((value & ~allowed) != 0U)
    {
        return false;
    }
    if ((value & 0x80000000U) != 0U)
    {
        return true;
    }

    id = (UNS16)(value & 0x7FFU);
    if ((id == 0U) || (id == 0x080U) || (id == 0x100U))
    {
        return false;
    }
    if (id == (UNS16)(0x700U + *SlaveOD_Data.bDeviceNodeId))
    {
        return false;
    }
    if (canopen_sdo_cob_conflict(id) || canopen_applied_pdo_conflict(slot, id) ||
        canopen_applied_hb_conflict(id))
    {
        return false;
    }
    return true;
}

static bool canopen_hb_value_valid(UNS32 value)
{
    UNS16 time = (UNS16)(value & 0xFFFFU);
    UNS8 node = (UNS8)((value >> 16) & 0xFFU);

    if ((value & 0xFF000000U) != 0U)
    {
        return false;
    }
    if (time == 0U)
    {
        return true;
    }
    if ((node == 0U) || (node > 127U) || (node == *SlaveOD_Data.bDeviceNodeId))
    {
        return false;
    }
    return !canopen_applied_hb_pdo_conflict(node);
}

static UNS32 canopen_config_write_cb(CO_Data *d, const indextable *table, UNS8 subindex)
{
    canopen_applied_t *slot = canopen_applied_lookup(table, subindex);
    UNS32 value;

    if (slot == NULL)
    {
        return OD_SUCCESSFUL;
    }

    value = *(UNS32 *)table->pSubindex[subindex].pObject;
    if (table->index == 0x1016U)
    {
        if (!canopen_hb_value_valid(value))
        {
            *(UNS32 *)table->pSubindex[subindex].pObject = slot->value;
            return OD_VALUE_RANGE_EXCEEDED;
        }
        slot->value = value;
        heartbeatStop(d);
        if ((value & 0xFFFFU) != 0U)
        {
            d->NMTable[(UNS8)((value >> 16) & 0xFFU)] = Unknown_state;
        }
        if (d->CurrentCommunicationState.csLifeGuard)
        {
            heartbeatInit(d);
        }
        return OD_SUCCESSFUL;
    }

    if (!canopen_pdo_value_valid(slot, value))
    {
        *(UNS32 *)table->pSubindex[subindex].pObject = slot->value;
        return OD_VALUE_RANGE_EXCEEDED;
    }
    slot->value = value;
    return OD_SUCCESSFUL;
}

static bool canopen_applied_add(UNS16 index, UNS8 subindex)
{
    UNS32 error;
    const indextable *table;
    canopen_applied_t *slot;

    if (s_applied_count >= CANOPEN_APPLIED_SLOTS)
    {
        return false;
    }
    table = SlaveOD_Data.scanIndexOD(&SlaveOD_Data, index, &error);
    if ((error != OD_SUCCESSFUL) || (table == NULL) || (subindex >= table->bSubCount))
    {
        return false;
    }
    slot = &s_applied[s_applied_count];
    slot->table = table;
    slot->subindex = subindex;
    slot->value = *(UNS32 *)table->pSubindex[subindex].pObject;
    if (RegisterSetODentryCallBack(&SlaveOD_Data, index, subindex,
                                   &canopen_config_write_cb) != OD_SUCCESSFUL)
    {
        return false;
    }
    s_applied_count++;
    return true;
}

static bool canopen_applied_init(void)
{
    UNS16 index;

    s_applied_count = 0U;
    if (*SlaveOD_Data.ConsumerHeartbeatCount != CANOPEN_HB_CONSUMER_SLOTS) return false;
    if (!canopen_applied_add(0x1016U, 1U))
    {
        return false;
    }
    for (index = 0x1400U; index <= 0x1403U; index++)
    {
        if (!canopen_applied_add(index, 1U))
        {
            return false;
        }
    }
    for (index = 0x1800U; index <= 0x1803U; index++)
    {
        if (!canopen_applied_add(index, 1U))
        {
            return false;
        }
    }
    return s_applied_count == CANOPEN_APPLIED_SLOTS;
}

static void canopen_applied_refresh(void)
{
    UNS8 i;

    for (i = 0U; i < s_applied_count; i++)
    {
        s_applied[i].value = *(UNS32 *)s_applied[i].table->pSubindex[s_applied[i].subindex].pObject;
    }
}

static void canopen_heartbeat_error(CO_Data *d, UNS8 node)
{
    (void)d;
    (void)node;
    AppSetCanBusPeerLost(true);
}

static void canopen_consumer_fault_poll_locked(void)
{
    UNS8 count = *SlaveOD_Data.ConsumerHeartbeatCount;
    bool lost = false;
    UNS8 i;
    if (count > CANOPEN_HB_CONSUMER_SLOTS) count = CANOPEN_HB_CONSUMER_SLOTS;
    for (i = 0U; i < count; i++)
    {
        UNS32 entry = SlaveOD_Data.ConsumerHeartbeatEntries[i];
        UNS8 node = (UNS8)((entry >> 16) & 0xFFU);
        if (((entry & 0xFFFFU) != 0U) && (node >= 1U) && (node <= 127U) &&
            (SlaveOD_Data.NMTable[node] == Disconnected)) lost = true;
    }
    AppSetCanBusPeerLost(lost);
}

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

static bool canopen_nmt_request(const bsp_can_frame_t *rx)
{
    uint8_t node = *SlaveOD_Data.bDeviceNodeId;

    return !rx->remote && (rx->id == 0x000U) && (rx->len == 2U) &&
           ((rx->data[1] == 0U) || (rx->data[1] == node)) &&
           ((SlaveOD_Data.nodeState == Pre_operational) ||
            (SlaveOD_Data.nodeState == Operational) ||
            (SlaveOD_Data.nodeState == Stopped)) &&
           ((rx->data[0] == 0x01U) || (rx->data[0] == 0x02U) ||
            (rx->data[0] == 0x80U) || (rx->data[0] == 0x81U) ||
            (rx->data[0] == 0x82U));
}

static bool canopen_sync_request(const bsp_can_frame_t *rx)
{
    return !rx->remote && (rx->id == 0x080U) && (rx->len == 0U) &&
           (SlaveOD_Data.CurrentCommunicationState.csSYNC != 0);
}

static bool canopen_guard_request(const bsp_can_frame_t *rx)
{
    return rx->remote && (rx->id == (0x700U + *SlaveOD_Data.bDeviceNodeId)) &&
           (rx->len == 0U) &&
           (SlaveOD_Data.CurrentCommunicationState.csLifeGuard != 0);
}

static bool canopen_sdo_request_admitted(const bsp_can_frame_t *rx)
{
    UNS16 offset;

    if (rx->remote || (SlaveOD_Data.CurrentCommunicationState.csSDO == 0) ||
        (SlaveOD_Data.firstIndex->SDO_SVR == 0U))
    {
        return false;
    }
    for (offset = SlaveOD_Data.firstIndex->SDO_SVR;
         offset <= SlaveOD_Data.lastIndex->SDO_SVR; offset++)
    {
        if (*(UNS32 *)SlaveOD_Data.objdict[offset].pSubindex[1].pObject == rx->id)
        {
            return true;
        }
    }
    return false;
}

static bool canopen_heartbeat_request(const bsp_can_frame_t *rx)
{
    UNS8 count = *SlaveOD_Data.ConsumerHeartbeatCount;
    UNS8 node;
    UNS8 i;
    UNS8 state;

    if (rx->remote || (rx->id < 0x701U) || (rx->id > 0x77FU) || (rx->len != 1U) ||
        (SlaveOD_Data.CurrentCommunicationState.csLifeGuard == 0))
    {
        return false;
    }
    state = (UNS8)(rx->data[0] & 0x7FU);
    if ((state != (UNS8)Initialisation) && (state != (UNS8)Stopped) &&
        (state != (UNS8)Operational) && (state != (UNS8)Pre_operational))
    {
        return false;
    }
    if (count > CANOPEN_HB_CONSUMER_SLOTS)
    {
        count = CANOPEN_HB_CONSUMER_SLOTS;
    }
    node = (UNS8)(rx->id - 0x700U);
    for (i = 0U; i < count; i++)
    {
        UNS32 entry = SlaveOD_Data.ConsumerHeartbeatEntries[i];

        if (((entry & 0xFFFFU) != 0U) && (node == (UNS8)((entry >> 16) & 0xFFU)))
        {
            return true;
        }
    }
    return false;
}

static bool canopen_emcy_request(const bsp_can_frame_t *rx)
{
    return !rx->remote && (rx->id >= 0x081U) && (rx->id <= 0xFFU) &&
           (rx->len == 8U) &&
           (SlaveOD_Data.CurrentCommunicationState.csEmergency != 0);
}

static bool canopen_rpdo_addressed(const bsp_can_frame_t *rx)
{
    UNS16 offset;
    if (rx->remote || (SlaveOD_Data.firstIndex->PDO_RCV == 0U)) return false;
    for (offset = SlaveOD_Data.firstIndex->PDO_RCV; offset <= SlaveOD_Data.lastIndex->PDO_RCV; offset++)
        if (*(UNS32 *)SlaveOD_Data.objdict[offset].pSubindex[1].pObject == rx->id) return true;
    return false;
}

static bool canopen_tpdo_rtr(const bsp_can_frame_t *rx)
{
    UNS16 offset;

    if (!rx->remote || (rx->len != 0U) || (SlaveOD_Data.firstIndex->PDO_TRS == 0U) ||
        (SlaveOD_Data.CurrentCommunicationState.csPDO == 0))
    {
        return false;
    }
    for (offset = SlaveOD_Data.firstIndex->PDO_TRS;
         offset <= SlaveOD_Data.lastIndex->PDO_TRS; offset++)
    {
        UNS32 cob_id = *(UNS32 *)SlaveOD_Data.objdict[offset].pSubindex[1].pObject;

        if ((cob_id & 0x80000000U) != 0U)
        {
            continue;
        }
        if ((cob_id & 0x40000000U) != 0U) /* 1: RTR not allowed */
        {
            continue;
        }
        if ((cob_id & 0x7FFU) == rx->id)
        {
            UNS8 type = *(UNS8 *)SlaveOD_Data.objdict[offset].pSubindex[2].pObject;
            /* Match proceedPDO: synchronous cyclic TPDOs ignore RTR. */
            return (type == TRANS_RTR) || (type == TRANS_RTR_SYNC) ||
                   (type == TRANS_EVENT_PROFILE) || (type == TRANS_EVENT_SPECIFIC);
        }
    }
    return false;
}

/* RPDO 请求：COB-ID 与实际 0x1400 配置匹配，长度满足当前映射。 */
static bool canopen_rpdo_counts(const bsp_can_frame_t *rx)
{
    UNS16 offset;

    if (rx->remote || (SlaveOD_Data.firstIndex->PDO_RCV == 0U))
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
        UNS32 cob_id = *(UNS32 *)SlaveOD_Data.objdict[offset].pSubindex[1].pObject;
        bool valid = true;

        if (((cob_id & 0x80000000U) != 0U) || ((cob_id & 0x7FFU) != rx->id))
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
    if (rx->extended || rx->canfd || (rx->len > 8U))
    {
        return false;
    }
    if (rx->remote)
    {
        return canopen_guard_request(rx) || canopen_tpdo_rtr(rx);
    }
    return canopen_nmt_request(rx) || canopen_sync_request(rx) ||
           ((SlaveOD_Data.CurrentCommunicationState.csSDO != 0) &&
            (rx->len == 8U) && canopen_sdo_request_counts(rx)) ||
           ((SlaveOD_Data.CurrentCommunicationState.csPDO != 0) &&
            canopen_rpdo_counts(rx));
}

static void handle_canopen(const bsp_can_frame_t *rx)
{
    Message message;
    uint32_t lock_state;
    bool sync_request;

    if (rx->extended || rx->canfd || (rx->len > 8U))
    {
        return;
    }
    memset(&message, 0, sizeof(message));
    message.cob_id = (UNS16)rx->id;
    message.rtr = rx->remote ? 1U : 0U;
    message.len = (rx->len > 8U) ? 8U : rx->len;
    if (message.len > 0U)
    {
        memcpy(message.data, rx->data, message.len);
    }
    /* 计数资格和 canDispatch 共用 OD;TimeDispatch 也会改 OD,所以放在同一临界区。 */
    lock_state = canopen_stack_lock();
    if (canopen_rx_counts(rx))
    {
        note_can_activity();
    }
    sync_request = canopen_sync_request(rx);
    if (canopen_rpdo_addressed(rx))
    {
        if ((SlaveOD_Data.CurrentCommunicationState.csPDO != 0) && canopen_rpdo_counts(rx))
            (void)proceedPDO(&SlaveOD_Data, &message);
    }
    else if (canopen_tpdo_rtr(rx))
    {
        (void)proceedPDO(&SlaveOD_Data, &message);
    }
    else if (canopen_nmt_request(rx) || sync_request || canopen_guard_request(rx) ||
             canopen_sdo_request_admitted(rx) || canopen_heartbeat_request(rx) ||
             canopen_emcy_request(rx))
    {
        canDispatch(&SlaveOD_Data, &message);
        if (sync_request && (SlaveOD_Data.nodeState == Operational))
            set_app_Target_update_state(true);
    }
    canopen_applied_refresh();
    canopen_consumer_fault_poll_locked();
    canopen_stack_unlock(lock_state);
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
    uint32_t lock_state;
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

    /* 与 RX 中断里的 canDispatch 串行;只延迟本 1ms 节拍的一次有界调用。 */
    lock_state = canopen_stack_lock();
    TimeDispatch();
    canopen_applied_refresh();
    canopen_stack_unlock(lock_state);
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
    /* 未初始化或重初始化期间直接丢弃。 */
    if ((frame == 0) || !s_ready)
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

    /* 重初始化期间先拒绝 RX 帧,避免进入尚未建好的协议栈。 */
    s_ready = false;
    s_node_id = node_id;
    s_bitrate_hz = bitrate_hz;
    s_rx_count = 0U;
    s_tx_count = 0U;
    s_tx_error_count = 0U;
    s_active_bitrate_hz = 0U;
#if IS_USE_CAN_PASSTHROUGH
    servo_can_mav_transport_reset();
#endif
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

#if defined(BOARD_SERVO_HPM6E80) && IS_USE_CAN_PASSTHROUGH
    /* 透传节点号同时是 MAV 组件 ID, 只允许 1..255; 初始化前就拒绝。 */
    if ((node_id == 0U) || (node_id > 255U))
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
        uint32_t lock_state;

        servo_canopen_timer_start();
        /* 状态切换会创建定时器/生成报文,必须与 canDispatch/TimeDispatch 串行。 */
        lock_state = canopen_stack_lock();
        SlaveOD_Data.heartbeatError = canopen_heartbeat_error;
        setNodeId(&SlaveOD_Data, (UNS8)s_node_id);
        setState(&SlaveOD_Data, Initialisation);
        setState(&SlaveOD_Data, Operational);
        if (!canopen_applied_init())
        {
            status = status_fail;
        }
        canopen_stack_unlock(lock_state);
    }
#endif
    s_last_error = status;
    if (status == status_success)
    {
        s_active_node_id = node_id;
        s_active_bitrate_hz = bitrate_hz;
#if IS_USE_CAN_PASSTHROUGH
        /* 身份和硬件过滤都源自这次成功初始化, 运行期不再改动。 */
        s_active_component = (uint8_t)(node_id & 0xFFU);
#endif
        __asm__ volatile ("" ::: "memory");
        s_ready = true;
    }
    else
    {
        s_ready = false;
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
#if IS_USE_CAN_PASSTHROUGH
    servo_can_mav_status_fill(status);
#else
    status->mav_tx_pending = 0U;
    status->mav_tx_dropped = 0U;
    status->mav_rx_pending = 0U;
    status->mav_rx_dropped = 0U;
    status->mav_active_comp_id = 0U;
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

/* ---- A15: CAN 上的 MAVLink 分片传输 (线格式沿用旧约定, 只加 4+4 固定缓冲) ---- */
#define MAV_CAN_TX_SLOTS       4U      /* 4 个整包发送槽, 每槽 280 字节 */
#define MAV_CAN_RX_CTX_COUNT   4U      /* 4 个并行重装上下文, 每上下文 280 字节 */
#define MAV_CAN_PACKET_MAX     280U
#define MAV_CAN_FRAME_MAX      64U

#define MAV_CTX_FREE           0U
#define MAV_CTX_ACTIVE         1U
#define MAV_CTX_READY          2U

/* 传输键: 只去掉 CNT(3..5) 和 MORE(2), 其余位不同就不算同一路传输。
 * 旧线格式里没有源物理 ID, 同一键的并发传输会被当成一路, 这里约定同一时刻
 * 一个键只有一路传输。 */
#define MAV_CAN_KEY_MASK       (~((uint32_t)((7U << CAN_POS_CNT_OF_TX) | (1U << CAN_POS_FLAG_END))))

typedef struct
{
    volatile uint8_t state;
    uint8_t  magic;            /* 0xFD = MAVLink v2, 0xFE = v1 */
    uint8_t  incompat_flags;
    uint8_t  frag_next;        /* 下一片应有的 CNT */
    uint16_t expected_len;     /* 0 = 头部还没到齐 */
    uint16_t have_len;
    uint32_t key;
    uint32_t last_mcycle;
    uint32_t order;            /* 完成顺序, 前台按它处理 */
    uint8_t  buf[MAV_CAN_PACKET_MAX];
} mav_can_rx_ctx_t;

typedef struct
{
    uint16_t len;
    uint16_t sent;
    uint8_t  frag;             /* 下一片的 CNT */
    uint8_t  sys_id;
    uint8_t  comp_id;
    uint8_t  priority;
    uint8_t  channel;
    uint8_t  seq;              /* 入队时快照的传输序号 */
    uint8_t  data[MAV_CAN_PACKET_MAX];
} mav_can_tx_job_t;

static mav_can_rx_ctx_t s_mav_rx[MAV_CAN_RX_CTX_COUNT];
static mav_can_tx_job_t s_mav_tx[MAV_CAN_TX_SLOTS];
static uint32_t s_mav_rx_order;
static uint32_t s_mav_rx_dropped;
static uint32_t s_mav_tx_dropped;
static uint32_t s_mav_timeout_cycles;
static uint8_t s_mav_tx_head;
static uint8_t s_mav_tx_tail;
static volatile uint8_t s_mav_tx_count;

static uint32_t mav_read_mcycle(void)
{
    uint32_t value;

    __asm volatile ("csrr %0, mcycle" : "=r" (value));
    return value;
}

static void mav_can_rx_drop(uint8_t idx)
{
    s_mav_rx[idx].state = MAV_CTX_FREE;
    s_mav_rx[idx].have_len = 0U;
    s_mav_rx[idx].expected_len = 0U;
    s_mav_rx[idx].frag_next = 0U;
    s_mav_rx_dropped++;
}

/* 超时只清未完成的上下文; 完整待取的包不能因为超时被丢掉。 */
static void mav_can_rx_expire(void)
{
    uint32_t now = mav_read_mcycle();
    uint8_t i;

    for (i = 0U; i < MAV_CAN_RX_CTX_COUNT; i++)
    {
        if (s_mav_rx[i].state != MAV_CTX_ACTIVE)
        {
            continue;
        }
        if ((uint32_t)(now - s_mav_rx[i].last_mcycle) > s_mav_timeout_cycles)
        {
            mav_can_rx_drop(i);
        }
    }
}

/* 返回 true 表示已拿到合法 expected_len; *invalid 表示内容已确定不合法。 */
static bool mav_can_parse_header(mav_can_rx_ctx_t *ctx, bool *invalid)
{
    uint8_t magic;
    uint32_t expected;

    *invalid = false;
    if (ctx->have_len < 2U)
    {
        return false;
    }
    magic = ctx->buf[0];
    if (magic == 0xFDU)
    {
        if (ctx->have_len < 3U)
        {
            return false;   /* incompat_flags 还没到 */
        }
        if ((ctx->buf[2] & (uint8_t)~0x01U) != 0U)
        {
            *invalid = true;    /* 未知的 v2 incompat 标志 */
            return false;
        }
        expected = 12U + (uint32_t)ctx->buf[1] + (((ctx->buf[2] & 0x01U) != 0U) ? 13U : 0U);
    }
    else if (magic == 0xFEU)
    {
        expected = 8U + (uint32_t)ctx->buf[1];
    }
    else
    {
        *invalid = true;
        return false;
    }
    if (expected > MAV_CAN_PACKET_MAX)
    {
        *invalid = true;
        return false;
    }
    ctx->magic = magic;
    ctx->incompat_flags = (magic == 0xFDU) ? ctx->buf[2] : 0U;
    ctx->expected_len = (uint16_t)expected;
    return true;
}

static void servo_can_mav_transport_reset(void)
{
    uint32_t irq_state = bsp_irq_save();
    uint8_t i;

    for (i = 0U; i < MAV_CAN_RX_CTX_COUNT; i++)
    {
        s_mav_rx[i].state = MAV_CTX_FREE;
        s_mav_rx[i].magic = 0U;
        s_mav_rx[i].incompat_flags = 0U;
        s_mav_rx[i].frag_next = 0U;
        s_mav_rx[i].expected_len = 0U;
        s_mav_rx[i].have_len = 0U;
        s_mav_rx[i].key = 0U;
        s_mav_rx[i].last_mcycle = 0U;
        s_mav_rx[i].order = 0U;
    }
    for (i = 0U; i < MAV_CAN_TX_SLOTS; i++)
    {
        s_mav_tx[i].len = 0U;
        s_mav_tx[i].sent = 0U;
        s_mav_tx[i].frag = 0U;
    }
    s_mav_tx_head = 0U;
    s_mav_tx_tail = 0U;
    s_mav_tx_count = 0U;
    s_mav_rx_order = 0U;
    s_mav_rx_dropped = 0U;
    s_mav_tx_dropped = 0U;
    s_mav_seq = 0U;
    /* 200ms 超时: 主频 / 5, 运行期用无符号差值比较, 回绕安全。 */
    s_mav_timeout_cycles = clock_get_frequency(clock_cpu0) / 5U;
    bsp_irq_restore(irq_state);
}

static void servo_can_mav_on_rx_frame(const bsp_can_frame_t *frame)
{
    uint32_t id;
    uint32_t key;
    uint8_t cnt;
    uint8_t more;
    uint8_t idx;
    uint8_t n;
    mav_can_rx_ctx_t *ctx;

    if ((frame == 0) || !s_ready)
    {
        return;
    }
    /* 只接受扩展帧的数据帧, BRS 输入约定保持和原来一致。 */
    if (!frame->extended || frame->remote || frame->bitrate_switch)
    {
        s_mav_rx_dropped++;
        return;
    }
    if ((frame->len == 0U) || (frame->len > MAV_CAN_FRAME_MAX) || (!frame->canfd && frame->len > 8U))
    {
        s_mav_rx_dropped++;
        return;
    }
    id = frame->id;
    if ((id & 0x03U) != 0U)
    {
        s_mav_rx_dropped++;
        return;     /* 未知线格式版本 */
    }

    cnt = (uint8_t)((id >> CAN_POS_CNT_OF_TX) & 0x07U);
    more = (uint8_t)((id >> CAN_POS_FLAG_END) & 0x01U);
    key = id & MAV_CAN_KEY_MASK;

    mav_can_rx_expire();

    idx = 0xFFU;
    for (n = 0U; n < MAV_CAN_RX_CTX_COUNT; n++)
    {
        if ((s_mav_rx[n].state != MAV_CTX_FREE) && (s_mav_rx[n].key == key))
        {
            idx = n;
            break;
        }
    }

    if ((more != 0U) && (cnt == 7U))
    {
        if ((idx != 0xFFU) && s_mav_rx[idx].state == MAV_CTX_ACTIVE) mav_can_rx_drop(idx);
        else s_mav_rx_dropped++;
        return;
    }
    if (cnt == 0U)
    {
        if ((idx != 0xFFU) && (s_mav_rx[idx].state == MAV_CTX_READY))
        {
            s_mav_rx_dropped++;     /* 上一包还没被前台取走: 拒绝新传输 */
            return;
        }
        if ((idx != 0xFFU) && (s_mav_rx[idx].state == MAV_CTX_ACTIVE))
        {
            if (more != 0U)
            {
                /* 同键的两路长传输无法区分后续片，拒绝双方而不尝试拼接。 */
                mav_can_rx_drop(idx);
                s_mav_rx_dropped++;
                return;
            }
            s_mav_rx_dropped++; /* 完整的单片新包可以安全替换旧半包。 */
        }
        else
        {
            idx = 0xFFU;
            for (n = 0U; n < MAV_CAN_RX_CTX_COUNT; n++)
            {
                if (s_mav_rx[n].state == MAV_CTX_FREE)
                {
                    idx = n;
                    break;
                }
            }
            if (idx == 0xFFU)
            {
                s_mav_rx_dropped++; /* 4 路都在用 */
                return;
            }
        }
        ctx = &s_mav_rx[idx];
        ctx->key = key;
        ctx->state = MAV_CTX_ACTIVE;
        ctx->have_len = 0U;
        ctx->expected_len = 0U;
        ctx->magic = 0U;
        ctx->incompat_flags = 0U;
        ctx->frag_next = 1U;
    }
    else
    {
        if (idx == 0xFFU)
        {
            s_mav_rx_dropped++;     /* 没有对应的起始片 */
            return;
        }
        ctx = &s_mav_rx[idx];
        if (ctx->state != MAV_CTX_ACTIVE)
        {
            s_mav_rx_dropped++;  /* 不能让迟到的片取消已经完整待处理的包。 */
            return;
        }
        if (ctx->frag_next != cnt)
        {
            mav_can_rx_drop(idx);
            return;
        }
        ctx->frag_next = (uint8_t)(cnt + 1U);
    }

    /* 一边接收一边确定长度；末片的零填充不占包缓冲，280字节包也可补齐DLC。 */
    for (n = 0U; n < frame->len; n++)
    {
        if ((ctx->expected_len != 0U) && (ctx->have_len == ctx->expected_len))
        {
            if ((more != 0U) || frame->data[n] != 0U) {mav_can_rx_drop(idx);return;}
            continue;
        }
        if (ctx->have_len >= MAV_CAN_PACKET_MAX) {mav_can_rx_drop(idx);return;}
        ctx->buf[ctx->have_len++] = frame->data[n];
        if (ctx->expected_len == 0U)
        {
            bool invalid = false;
            (void)mav_can_parse_header(ctx, &invalid);
            if (invalid) {mav_can_rx_drop(idx);return;}
        }
    }
    ctx->last_mcycle = mav_read_mcycle();

    if (more != 0U)
    {
        if ((ctx->expected_len != 0U) && (ctx->have_len >= ctx->expected_len))
        {
            mav_can_rx_drop(idx);   /* 非末片已完整 */
        }
        return;
    }

    if ((ctx->expected_len == 0U) || (ctx->have_len != ctx->expected_len))
    {
        mav_can_rx_drop(idx);       /* 截断或长度不符 */
        return;
    }

    ctx->state = MAV_CTX_READY;
    s_mav_rx_order++;
    if (s_mav_rx_order == 0U)
    {
        s_mav_rx_order++;
    }
    ctx->order = s_mav_rx_order;
}

static void servo_can_mav_tx_poll(void)
{
    uint8_t frags = 0U;

    while (frags < 8U)
    {
        uint32_t irq_state;
        mav_can_tx_job_t *job;
        hpm_stat_t status;
        uint32_t id;
        uint8_t chunk;
        uint8_t more;

        irq_state = bsp_irq_save();
        if (s_mav_tx_count == 0U)
        {
            bsp_irq_restore(irq_state);
            break;
        }
        job = &s_mav_tx[s_mav_tx_head];
        chunk = (uint8_t)(((uint32_t)(job->len - job->sent) > 64U) ? 64U : (uint32_t)(job->len - job->sent));
        more = ((uint16_t)(job->sent + chunk) < job->len) ? 1U : 0U;

        id = ((uint32_t)job->priority & 0x07U) << CAN_POS_PRIORITY;
        id |= (1UL & 0x1FU) << CAN_POS_SYSID;     /* CAN-MAV 固定 sys=1 */
        id |= ((uint32_t)job->comp_id & 0xFFU) << CAN_POS_COMPID;
        id |= ((uint32_t)job->seq & 0x1FU) << CAN_POS_TRANS_SEQ;
        id |= ((uint32_t)job->frag & 0x07U) << CAN_POS_CNT_OF_TX;
        id |= ((uint32_t)more & 0x01U) << CAN_POS_FLAG_END;
        status = bsp_can_send_fd(id, true, (job->channel != CANFD_DEBUG), &job->data[job->sent], chunk);

        if (status == status_success)
        {
            s_tx_count++;
            job->sent = (uint16_t)(job->sent + chunk);
            job->frag++;
            if (job->sent >= job->len)
            {
                /* 整包的最后一片已提交: 摘掉任务头。 */
                s_mav_tx_head = (uint8_t)((s_mav_tx_head + 1U) % MAV_CAN_TX_SLOTS);
                s_mav_tx_count--;
            }
            bsp_irq_restore(irq_state);
            frags++;
            continue;
        }
        if (status == status_mcan_txfifo_full)
        {
            /* 硬件 TXFIFO 满: 保留这一片原样, 下次 poll 再试, 不计错。 */
            bsp_irq_restore(irq_state);
            break;
        }

        /* 其他错误: 丢掉整包并计一次错, 避免任务头永久阻塞。 */
        s_mav_tx_dropped++;
        s_tx_error_count++;
        s_mav_tx_head = (uint8_t)((s_mav_tx_head + 1U) % MAV_CAN_TX_SLOTS);
        s_mav_tx_count--;
        bsp_irq_restore(irq_state);
        frags++;
    }
}

static void servo_can_mav_poll(void)
{
    uint8_t processed = 0U;

    if (!s_ready) return;
    /* 按完成顺序取包, 不是按分配顺序。 */
    while (processed < MAV_CAN_RX_CTX_COUNT)
    {
        uint8_t picked = 0xFFU;
        uint8_t n;
        uint8_t local[MAV_CAN_PACKET_MAX];
        uint16_t local_len;
        uint32_t irq_state = bsp_irq_save();

        mav_can_rx_expire();
        for (n = 0U; n < MAV_CAN_RX_CTX_COUNT; n++)
        {
            if (s_mav_rx[n].state != MAV_CTX_READY)
            {
                continue;
            }
            if ((picked == 0xFFU) || ((int32_t)(s_mav_rx[n].order - s_mav_rx[picked].order) < 0))
            {
                picked = n;
            }
        }
        if (picked == 0xFFU)
        {
            bsp_irq_restore(irq_state);
            break;
        }
        local_len = s_mav_rx[picked].have_len;
        memcpy(local, s_mav_rx[picked].buf, local_len);
        s_mav_rx[picked].state = MAV_CTX_FREE;
        s_mav_rx[picked].have_len = 0U;
        s_mav_rx[picked].expected_len = 0U;
        bsp_irq_restore(irq_state);

        /* 在真正拥有 COMM_0 状态的应用模块内重置并解析整包。 */
        MavlinkRecvPacketCallback(&kAxis, &kAxisDw, local, local_len);
        processed++;
    }

    servo_can_mav_tx_poll();
}

static void servo_can_mav_status_fill(servo_can_status_t *status)
{
    uint32_t irq_state = bsp_irq_save();
    uint32_t rx_pending = 0U;
    uint8_t n;

    for (n = 0U; n < MAV_CAN_RX_CTX_COUNT; n++)
    {
        if (s_mav_rx[n].state == MAV_CTX_READY)
        {
            rx_pending++;
        }
    }
    status->mav_tx_pending = s_mav_tx_count;
    status->mav_tx_dropped = s_mav_tx_dropped;
    status->mav_rx_pending = rx_pending;
    status->mav_rx_dropped = s_mav_rx_dropped;
    status->mav_active_comp_id = s_active_component;
    bsp_irq_restore(irq_state);
}

void bsp_can_on_rx_fifo1(const bsp_can_frame_t *frame)
{
#if IS_USE_CAN_PASSTHROUGH
    /* 透传: ISR 只做无堆重装, 完整包的解析留给 servo_can_poll 前台。 */
    servo_can_mav_on_rx_frame(frame);
#else
    if ((frame == 0) || frame->bitrate_switch)
    {
        return;
    }
    MavlinkRecvCallback(&kAxis, &kAxisDw, (uint8_t *)frame->data, frame->len);
#endif
}

static uint8_t mav_enqueue_packet(const uint8_t *data, uint32_t len, uint8_t sys_id, uint8_t comp_id,
                                  uint8_t priority, uint8_t channel)
{
    uint32_t irq_state;
    uint8_t slot;

    if (!s_ready || (data == 0) || (len == 0U) || (len > MAV_CAN_PACKET_MAX))
    {
        irq_state = bsp_irq_save();
        s_mav_tx_dropped++;
        s_tx_error_count++;
        bsp_irq_restore(irq_state);
        return 1U;
    }

    irq_state = bsp_irq_save();
    if (s_mav_tx_count >= MAV_CAN_TX_SLOTS)
    {
        /* 队列满: 整包丢弃并计数, 不假装已经上总线。 */
        s_mav_tx_dropped++;
        s_tx_error_count++;
        bsp_irq_restore(irq_state);
        return 1U;
    }

    slot = s_mav_tx_tail;
    memcpy(s_mav_tx[slot].data, data, len);
    s_mav_tx[slot].len = (uint16_t)len;
    s_mav_tx[slot].sent = 0U;
    s_mav_tx[slot].frag = 0U;
    s_mav_tx[slot].sys_id = sys_id;
    s_mav_tx[slot].comp_id = comp_id;
    s_mav_tx[slot].priority = (uint8_t)(priority & 0x07U);
    s_mav_tx[slot].channel = channel;
    /* 传输序号在入队时锁定, 只有整包被接收才前进。 */
    s_mav_tx[slot].seq = s_mav_seq;
    s_mav_seq = (uint8_t)((s_mav_seq + 1U) & 0x1FU);
    s_mav_tx_tail = (uint8_t)((s_mav_tx_tail + 1U) % MAV_CAN_TX_SLOTS);
    s_mav_tx_count++;
    bsp_irq_restore(irq_state);
    return 0U;
}

void servo_can_mavlink_send(uint8_t *pdata, uint32_t len)
{
    (void)mav_enqueue_packet(pdata, len, 1U, s_active_component, 1U, CANFD_MESSAGE);
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
#if IS_USE_CAN_PASSTHROUGH
        /* 返回本次初始化锁定的身份, 不跟随运行期的 CAN ID 修改。 */
        *comp_id = s_active_component;
#else
        *comp_id = (uint8_t)(s_node_id & 0xFFU);
#endif
    }
}
#endif
