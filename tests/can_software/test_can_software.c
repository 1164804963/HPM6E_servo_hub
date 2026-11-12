#include "test_can_software.h"

#include "can_cia402.h"
#include "data_param.h"
#include "servo_can.h"
#include "servo_debug_can_policy.h"
#include "test_stubs.h"

#include <stdio.h>
#include <string.h>

static int s_fail;

#define CHECK(cond, msg) do { if (!(cond)) { printf("FAIL: %s (line %d)\r\n", msg, __LINE__); s_fail++; } } while (0)

static void reset_all(void)
{
    stub_reset();
    stub_od_value = 0U;
    stub_od_abort = 0U;
    stub_od_read_calls = 0;
    stub_od_write_calls = 0;
    stub_od_last_index = 0U;
    stub_od_last_subindex = 0U;
    stub_error_set_calls = 0;
    stub_error_clear_calls = 0;
    stub_app_controlword_calls = 0;
    stub_last_app_controlword = 0xFFFFU;
    stub_set_controlword_calls = 0;
    stub_last_set_controlword = 0xFFFFU;
}

static void test_codec(void)
{
    uint8_t req[8] = {0};
    uint8_t reply[8] = {0};
    uint32_t abort = 0U;
    can_cia402_result_t result;

    reset_all();

    req[0] = 0U; req[1] = 0x41U; req[2] = 0x60U; req[3] = 0U;
    stub_od_value = 0x12345678U;
    result = can_cia402_handle_request(req, 5U, reply, &abort);
    CHECK(result == CAN_CIA402_OK, "read 5-byte request");
    CHECK(stub_od_last_index == 0x6041U, "read index 0x6041");
    CHECK(reply[4] == 0x78U && reply[5] == 0x56U && reply[6] == 0x34U && reply[7] == 0x12U,
          "read reply little-endian");

    req[0] = 1U; req[1] = 0x40U; req[2] = 0x60U; req[3] = 0U; req[4] = 0x0FU;
    result = can_cia402_handle_request(req, 5U, reply, &abort);
    CHECK(result == CAN_CIA402_OK, "write 1-byte request");
    CHECK(stub_od_value == 0x0FU, "write 1-byte value");
    CHECK(stub_od_write_calls == 1, "write callback once for 1-byte");

    req[1] = 0x60U; req[2] = 0x60U; req[4] = 0x34U; req[5] = 0x12U;
    result = can_cia402_handle_request(req, 6U, reply, &abort);
    CHECK(result == CAN_CIA402_OK, "write 2-byte 0x6060 request");
    CHECK(stub_od_value == 0x1234U, "write 2-byte value");

    req[1] = 0x7AU; req[2] = 0x60U; req[3] = 0U;
    req[4] = 0U; req[5] = 0U; req[6] = 0U; req[7] = 0x80U;
    result = can_cia402_handle_request(req, 8U, reply, &abort);
    CHECK(result == CAN_CIA402_OK, "write 4-byte 0x607A request");
    CHECK(stub_od_value == 0x80000000U, "0x80 high-byte value");
    CHECK(reply[7] == 0x80U, "0x607A reply high byte");

    req[4] = 0xFFU; req[5] = 0xFFU; req[6] = 0xFFU; req[7] = 0xFFU;
    result = can_cia402_handle_request(req, 8U, reply, &abort);
    CHECK(result == CAN_CIA402_OK, "write 4-byte all-ones request");
    CHECK(stub_od_value == 0xFFFFFFFFU, "0xFFFFFFFF value");

    req[0] = 0U; req[1] = 0x60U; req[2] = 0x60U; req[3] = 0U;
    result = can_cia402_handle_request(req, 5U, reply, &abort);
    CHECK(result == CAN_CIA402_OK, "read 0x6060");
    CHECK(stub_od_last_index == 0x6060U, "read index 0x6060");

    reset_all();
    req[0] = 1U;
    for (uint8_t bad_len = 0U; bad_len <= 9U; bad_len++)
    {
        if ((bad_len == 0U) || (bad_len == 1U) || (bad_len == 2U) || (bad_len == 3U) ||
            (bad_len == 4U) || (bad_len == 7U) || (bad_len == 9U))
        {
            result = can_cia402_handle_request(req, bad_len, reply, &abort);
            CHECK(result == CAN_CIA402_INVALID, "invalid length rejected");
        }
    }
    CHECK(stub_od_read_calls == 0 && stub_od_write_calls == 0, "invalid length does not call OD");
    req[0] = 2U;
    result = can_cia402_handle_request(req, 5U, reply, &abort);
    CHECK(result == CAN_CIA402_INVALID, "invalid opcode rejected");
    req[0] = 1U;
    result = can_cia402_handle_request(0, 5U, reply, &abort);
    CHECK(result == CAN_CIA402_INVALID, "null request rejected");
    CHECK(stub_od_read_calls == 0 && stub_od_write_calls == 0, "invalid request never calls OD");
    result = can_cia402_handle_request(req, 5U, 0, &abort);
    CHECK(result == CAN_CIA402_INVALID, "null reply rejected");

    reset_all();
    stub_od_abort = 0x06010002U;
    memset(reply, 0xA5, sizeof(reply));
    req[0] = 1U; req[1] = 0x40U; req[2] = 0x60U; req[3] = 0U; req[4] = 1U;
    result = can_cia402_handle_request(req, 5U, reply, &abort);
    CHECK(result == CAN_CIA402_ABORT, "callback abort is not a reply");
    CHECK(abort == 0x06010002U, "abort code captured");
    for (uint32_t i = 0; i < sizeof(reply); i++)
    {
        CHECK(reply[i] == 0xA5U, "abort leaves reply buffer unchanged");
    }
    stub_od_abort = 0U;
}

static void test_request_during_init(void)
{
    (void)servo_can_request_node_id(0x33U);
    (void)servo_can_request_bitrate(1000000U);
}

static void test_adapter(void)
{
    servo_can_status_t st;
    uint8_t req[8];
    uint8_t data[8];
    int init_calls;

    reset_all();
    stub_init_status = status_fail;
    CHECK(servo_can_init(0x24U, 500000U) == status_fail, "initial init failure reported");
    servo_can_get_status(&st);
    CHECK(!st.ready && st.node_id == 0x15U && st.bitrate_hz == 1000000U,
          "initial failure keeps last applied");
    CHECK(st.requested_node_id == 0x24U && st.requested_bitrate_hz == 500000U,
          "initial failure retains requested");

    reset_all();
    CHECK(servo_can_request_node_id(0x24U) == status_success, "request non-default node 0x24");
    CHECK(servo_can_request_bitrate(500000U) == status_success, "request non-default 500k");
    CHECK(servo_can_init(servo_can_requested_node_id(), servo_can_requested_bitrate()) == status_success,
          "startup from requested config");
    servo_can_get_status(&st);
    CHECK(st.ready && st.node_id == 0x24U && st.bitrate_hz == 500000U, "startup applied non-default config");

    memset(data, 0, sizeof(data));
    stub_queue_rx(0x16U, false, data, 5U);
    stub_queue_rx(0x24U, true, data, 5U);
    servo_can_poll();
    servo_can_get_status(&st);
    CHECK(st.invalid_count == 2U, "drop wrong ID and extended");

    req[0] = 0U; req[1] = 0x41U; req[2] = 0x60U; req[3] = 0U; req[4] = 0U;
    stub_od_value = 0x00000027U;
    stub_queue_rx(0x24U, false, req, 5U);
    servo_can_poll();
    servo_can_get_status(&st);
    CHECK(st.rx_count == 1U && st.tx_count == 1U, "read frame counted and replied");
    CHECK(stub_last_tx.id == 0x24U && stub_last_tx.len == 8U, "reply ID/8 bytes");
    CHECK(stub_last_tx.data[4] == 0x27U, "reply read value");

    stub_tx_busy = 1;
    req[0] = 1U; req[1] = 0x40U; req[2] = 0x60U; req[3] = 0U; req[4] = 0x0FU;
    stub_queue_rx(0x24U, false, req, 5U);
    servo_can_poll();
    CHECK(stub_od_write_calls == 1, "write callback once before busy retry");
    stub_queue_rx(0x24U, false, req, 5U);
    servo_can_poll();
    CHECK(stub_od_write_calls == 1, "do not consume while reply pending");
    stub_tx_busy = 0;
    servo_can_poll();
    CHECK(stub_od_write_calls == 2, "busy reply sent and next request consumed once");
    servo_can_poll();
    CHECK(stub_od_write_calls == 2, "no duplicate OD write for pending reply");

    init_calls = stub_init_calls;
    stub_set_tx_complete();
    stub_tx_pending_hw = true;
    CHECK(servo_can_request_bitrate(1000000U) == status_success, "request 1M while TX pending");
    servo_can_poll();
    CHECK(stub_init_calls == init_calls, "TX pending blocks reconfigure");
    stub_set_tx_complete();
    servo_can_poll();
    CHECK(stub_init_calls == init_calls + 1, "reconfigure after TX complete");
    servo_can_get_status(&st);
    CHECK(st.bitrate_hz == 1000000U, "new baud applied from snapshot");

    memset(data, 0, sizeof(data));
    for (int i = 0; i < 9; i++)
    {
        stub_queue_rx(0x24U, false, req, 5U);
    }
    int before = st.rx_count;
    servo_can_poll();
    servo_can_get_status(&st);
    CHECK((int)st.rx_count - before == 8, "poll frame budget is 8");

    reset_all();
    CHECK(servo_can_init(0x24U, 500000U) == status_success, "init for hardware pending test");
    stub_auto_complete = false;
    stub_tx_pending_hw = false;
    req[0] = 0U; req[1] = 0x41U; req[2] = 0x60U; req[3] = 0U;
    stub_queue_rx(0x24U, false, req, 5U);
    stub_queue_rx(0x24U, false, req, 5U);
    servo_can_poll();
    CHECK(stub_od_read_calls == 2, "two requests processed once each");
    CHECK(stub_tx_pending_hw, "first reply occupies hardware TX0");
    servo_can_poll();
    CHECK(stub_od_read_calls == 2, "no duplicate OD while software reply pending");
    stub_set_tx_complete();
    servo_can_poll();
    servo_can_get_status(&st);
    CHECK(st.tx_count == 2U, "both replies eventually queued");

    CHECK(servo_can_request_node_id(0x800U) == status_invalid_argument, "reject 12-bit node ID");
    CHECK(servo_can_request_bitrate(250000U) == status_invalid_argument, "reject unknown baud");

    reset_all();
    CHECK(servo_can_request_node_id(0x24U) == status_success, "snapshot request 0x24");
    CHECK(servo_can_request_bitrate(500000U) == status_success, "snapshot request 500k");
    stub_set_init_hook(test_request_during_init);
    CHECK(servo_can_init(0x24U, 500000U) == status_success, "init with snapshot");
    servo_can_get_status(&st);
    CHECK(st.node_id == 0x24U && st.bitrate_hz == 500000U, "hardware/applied use init snapshot");
    CHECK(stub_last_init_bitrate == 500000U, "hardware called with init snapshot");
    CHECK(st.requested_node_id == 0x33U && st.requested_bitrate_hz == 1000000U,
          "new request retained for next poll");
    stub_set_init_hook(0);
    servo_can_poll();
    servo_can_get_status(&st);
    CHECK(st.node_id == 0x33U && st.bitrate_hz == 1000000U, "next poll applies new requested config");
    CHECK(stub_last_init_bitrate == 1000000U, "next poll hardware uses new baud");

    reset_all();
    CHECK(servo_can_init(0x15U, 1000000U) == status_success, "init before failure test");
    stub_init_status = status_fail;
    CHECK(servo_can_request_bitrate(500000U) == status_success, "request bad reinit");
    servo_can_poll();
    servo_can_get_status(&st);
    CHECK(!st.ready && st.last_error == status_fail, "reinit failure reports not ready");
    CHECK(stub_error_set_calls > 0 && stub_app_controlword_calls > 0, "failure sets error and disables");
    stub_init_status = status_success;
    CHECK(servo_can_reset() == status_success, "explicit reset recovers");
    servo_can_get_status(&st);
    CHECK(st.ready && stub_error_clear_calls > 0, "reset clears init error");

    stub_tx_pending_hw = true;
    CHECK(servo_can_reset() == status_success, "reset drops pending TX");
    CHECK(!stub_tx_pending_hw, "reset stops hardware pending");
    CHECK(stub_last_set_controlword == 0U, "reset sends CiA402 Controlword 0");
    CHECK(stub_last_app_controlword == APP_CTRL_DISABLE, "reset sends APP_CTRL_DISABLE");
}

static void test_debug_can_policy(void)
{
    uint8_t req[8] = {0U};

    req[1] = 0x41U;
    req[2] = 0x60U;
    req[3] = 0U;

    CHECK(servo_debug_can_is_read_only_request(false, 0x015U, 5U, req), "J8 5-byte read accepted");
    CHECK(servo_debug_can_is_read_only_request(false, 0x015U, 6U, req), "J8 6-byte read accepted");
    CHECK(servo_debug_can_is_read_only_request(false, 0x015U, 8U, req), "J8 8-byte read accepted");

    req[0] = 1U;
    CHECK(!servo_debug_can_is_read_only_request(false, 0x015U, 5U, req), "J8 write rejected");
    req[0] = 0U;

    CHECK(!servo_debug_can_is_read_only_request(true, 0x015U, 5U, req), "J8 extended rejected");
    CHECK(!servo_debug_can_is_read_only_request(false, 0x016U, 5U, req), "J8 wrong ID rejected");
    CHECK(!servo_debug_can_is_read_only_request(false, 0x015U, 4U, req), "J8 DLC 4 rejected");
    CHECK(!servo_debug_can_is_read_only_request(false, 0x015U, 7U, req), "J8 DLC 7 rejected");
    CHECK(!servo_debug_can_is_read_only_request(false, 0x015U, 5U, NULL), "J8 null data rejected");
}

int can_software_run(void)
{
    s_fail = 0;
    test_debug_can_policy();
    test_codec();
    test_adapter();
    if (s_fail == 0)
    {
        printf("TEST PASS\r\n");
        return 0;
    }
    printf("TEST FAIL: %d checks\r\n", s_fail);
    return 1;
}
