#ifndef SERVO_DEBUG_CAN_POLICY_H
#define SERVO_DEBUG_CAN_POLICY_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#define SERVO_DEBUG_CAN_NODE_ID   (0x015U)
#define SERVO_DEBUG_CAN_BITRATE_HZ (1000000U)

/* J8 debug port is read-only: standard ID 0x015, DLC 5/6/8, op=0 only. */
static inline bool servo_debug_can_is_read_only_request(bool extended,
                                                        uint32_t id,
                                                        uint8_t len,
                                                        const uint8_t *data)
{
    if (extended || (id != SERVO_DEBUG_CAN_NODE_ID)) {
        return false;
    }
    if ((len != 5U) && (len != 6U) && (len != 8U)) {
        return false;
    }
    if (data == NULL) {
        return false;
    }
    return data[0] == 0U;
}

#endif /* SERVO_DEBUG_CAN_POLICY_H */
