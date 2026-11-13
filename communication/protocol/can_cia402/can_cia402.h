#ifndef CAN_CIA402_H
#define CAN_CIA402_H

#include <stdint.h>

#define CAN_CIA402_REPLY_SIZE (8U)

typedef enum
{
    CAN_CIA402_OK = 0,
    CAN_CIA402_INVALID,
    CAN_CIA402_ABORT,
} can_cia402_result_t;

typedef enum
{
    CAN_CIA402_ACCESS_MASTER = 0, /* J9 / CANopen master, writes need BUS */
    CAN_CIA402_ACCESS_DEBUG_HOST, /* J8 debug port, writes need HOST */
} can_cia402_access_t;

/*
 * Request: [op, index LE16, subindex, value LE (1/2/4 bytes)]
 * op 0 = read, op 1 = write. Total request length is 5, 6 or 8.
 * Reply is always 8 bytes: [op, index LE16, subindex, value LE32].
 * Callback abort is not converted into a reply.
 */
can_cia402_result_t can_cia402_handle_request(const uint8_t *request,
                                              uint8_t request_len,
                                              uint8_t reply[CAN_CIA402_REPLY_SIZE],
                                              uint32_t *abort_code);
can_cia402_result_t can_cia402_handle_request_for(can_cia402_access_t access,
                                                  const uint8_t *request,
                                                  uint8_t request_len,
                                                  uint8_t reply[CAN_CIA402_REPLY_SIZE],
                                                  uint32_t *abort_code);

#endif /* CAN_CIA402_H */
