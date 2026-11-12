#include "can_cia402.h"

#include "master_cia402_callback.h"

#define CAN_CIA402_ABORT_OK (0U)

can_cia402_result_t can_cia402_handle_request(const uint8_t *request,
                                              uint8_t request_len,
                                              uint8_t reply[CAN_CIA402_REPLY_SIZE],
                                              uint32_t *abort_code)
{
    uint8_t op;
    uint16_t index;
    uint8_t subindex;
    uint32_t value = 0U;
    uint32_t abort = 0U;
    uint8_t value_len;

    if ((request == 0) || (reply == 0))
    {
        return CAN_CIA402_INVALID;
    }
    if ((request_len != 5U) && (request_len != 6U) && (request_len != 8U))
    {
        return CAN_CIA402_INVALID;
    }

    op = request[0];
    if ((op != 0U) && (op != 1U))
    {
        return CAN_CIA402_INVALID;
    }

    index = (uint16_t)((uint16_t)request[1] | ((uint16_t)request[2] << 8U));
    subindex = request[3];
    value_len = (uint8_t)(request_len - 4U);

    if (value_len == 1U)
    {
        value = request[4];
    }
    else if (value_len == 2U)
    {
        value = (uint32_t)request[4] | ((uint32_t)request[5] << 8U);
    }
    else if (value_len == 4U)
    {
        value = (uint32_t)request[4] |
                ((uint32_t)request[5] << 8U) |
                ((uint32_t)request[6] << 16U) |
                ((uint32_t)request[7] << 24U);
    }
    else
    {
        return CAN_CIA402_INVALID;
    }

    if (op == 1U)
    {
        abort = master_cia402_write_callback(index, subindex, &value);
    }
    else
    {
        value = 0U;
        abort = master_cia402_read_callback(index, subindex, &value);
    }

    if (abort_code != 0)
    {
        *abort_code = abort;
    }
    if (abort != CAN_CIA402_ABORT_OK)
    {
        return CAN_CIA402_ABORT;
    }

    reply[0] = op;
    reply[1] = request[1];
    reply[2] = request[2];
    reply[3] = subindex;
    reply[4] = (uint8_t)(value & 0xFFU);
    reply[5] = (uint8_t)((value >> 8U) & 0xFFU);
    reply[6] = (uint8_t)((value >> 16U) & 0xFFU);
    reply[7] = (uint8_t)((value >> 24U) & 0xFFU);

    return CAN_CIA402_OK;
}
