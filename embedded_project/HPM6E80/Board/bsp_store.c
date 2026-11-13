#include "bsp_api.h"
#include "servo_board.h"
#include "flashdb.h"
#include "fal.h"
#include "hpm_romapi.h"
#include "hpm_l1c_drv.h"
#include <string.h>
#include <stdio.h>

/* FlashDB owns CRC, append/commit states and interrupted-write recovery.
 * This port owns the reserved region, XIP-safe ROM calls and schema checks.
 * Called only before control starts or from the disabled foreground service. */
#define STORE_MAX_KEYS 4U
#define STORE_MAX_VALUE 3072U
#define STORE_MAGIC 0x31565053U /* SPV1; change schema when saved layouts change. */
#define STORE_SCHEMA 1U
typedef struct { const char *key; void *value; size_t len; } StoreItem;
typedef struct { uint32_t magic, schema, len; uint8_t data[STORE_MAX_VALUE]; } StoreBlob;
static StoreItem s_items[STORE_MAX_KEYS];
static StoreBlob s_blob;
static struct fdb_kvdb s_db;
static xpi_nor_config_t s_nor;
static bool s_ready, s_nor_ready, s_io_failed;
static uint32_t s_page[64]; /* ROM requires word-aligned RAM source. */

/* No flash code/constants may execute while the ROM makes XPI busy.
 * The whole caller masks interrupts so no control ISR can re-enable PWM. */
ATTR_RAMFUNC __attribute__((noinline))
static hpm_stat_t flash_configure(void)
{
    xpi_nor_config_option_t option;
    option.header.U = BOARD_APP_XPI_NOR_CFG_OPT_HDR;
    option.option0.U = BOARD_APP_XPI_NOR_CFG_OPT_OPT0;
    option.option1.U = BOARD_APP_XPI_NOR_CFG_OPT_OPT1;
    return rom_xpi_nor_auto_config(BOARD_APP_XPI_NOR_XPI_BASE, &s_nor, &option);
}
ATTR_RAMFUNC __attribute__((noinline))
static hpm_stat_t flash_program(uint32_t offset, uint32_t size)
{
    return rom_xpi_nor_program(BOARD_APP_XPI_NOR_XPI_BASE, xpi_xfer_channel_auto,
                              &s_nor, s_page, offset, size);
}
ATTR_RAMFUNC __attribute__((noinline))
static hpm_stat_t flash_erase(uint32_t offset)
{
    return rom_xpi_nor_erase_sector(BOARD_APP_XPI_NOR_XPI_BASE, xpi_xfer_channel_auto,
                                   &s_nor, offset);
}
static void invalidate(uint32_t offset, size_t size)
{
    uint32_t start = HPM_L1C_CACHELINE_ALIGN_DOWN(BOARD_FLASH_BASE_ADDRESS + SERVO_KV_OFFSET + offset);
    uint32_t end = HPM_L1C_CACHELINE_ALIGN_UP(BOARD_FLASH_BASE_ADDRESS + SERVO_KV_OFFSET + offset + size);
    l1c_dc_invalidate(start, end - start);
}
static bool valid_range(long off, size_t len)
{
    return s_nor_ready && off >= 0 && (size_t)off <= SERVO_KV_SIZE && len <= SERVO_KV_SIZE - (size_t)off;
}
static int nor_init(void)
{
    if (s_nor_ready) return 0;
    uint32_t size = 0, sector = 0, page = 0;
    uint32_t irq = bsp_irq_save();
    hpm_stat_t result = flash_configure();
    bsp_irq_restore(irq);
    if (result != status_success) return -1;
    if (rom_xpi_nor_get_property(BOARD_APP_XPI_NOR_XPI_BASE, &s_nor, xpi_nor_property_total_size, &size) != status_success ||
        rom_xpi_nor_get_property(BOARD_APP_XPI_NOR_XPI_BASE, &s_nor, xpi_nor_property_sector_size, &sector) != status_success ||
        rom_xpi_nor_get_property(BOARD_APP_XPI_NOR_XPI_BASE, &s_nor, xpi_nor_property_page_size, &page) != status_success ||
        size < SERVO_KV_OFFSET + SERVO_KV_SIZE || sector != SERVO_FLASH_SECTOR || page != sizeof(s_page)) return -1;
    s_nor_ready = true;
    printf("store: flash=%lu sector=%lu page=%lu KV=0x%lx+0x%lx\r\n",
           (unsigned long)size, (unsigned long)sector, (unsigned long)page,
           (unsigned long)SERVO_KV_OFFSET, (unsigned long)SERVO_KV_SIZE);
    return 0;
}
static int nor_read(long offset, uint8_t *buf, size_t size)
{
    if (!valid_range(offset, size)) { s_io_failed = true; return -1; }
    invalidate(offset, size);
    memcpy(buf, (const void *)(BOARD_FLASH_BASE_ADDRESS + SERVO_KV_OFFSET + offset), size);
    return (int)size;
}
static int nor_write(long offset, const uint8_t *buf, size_t size)
{
    if (s_io_failed || !valid_range(offset, size) || bsp_get_pwm_state()) { s_io_failed = true; return -1; }
    size_t done = 0;
    while (done < size)
    {
        size_t n = sizeof(s_page) - ((offset + done) % sizeof(s_page));
        if (n > size - done) n = size - done;
        memcpy(s_page, buf + done, n);
        hpm_stat_t result = flash_program(SERVO_KV_OFFSET + offset + done, n);
        invalidate(offset + done, n);
        if (result != status_success || memcmp((const void *)(BOARD_FLASH_BASE_ADDRESS + SERVO_KV_OFFSET + offset + done), buf + done, n))
        { s_io_failed = true; return -1; }
        done += n;
    }
    return (int)size;
}
static int nor_erase(long offset, size_t size)
{
    if (s_io_failed || !valid_range(offset, size) || offset % SERVO_FLASH_SECTOR || size % SERVO_FLASH_SECTOR || bsp_get_pwm_state())
    { s_io_failed = true; return -1; }
    for (size_t i = 0; i < size; i += SERVO_FLASH_SECTOR)
    {
        hpm_stat_t result = flash_erase(SERVO_KV_OFFSET + offset + i);
        invalidate(offset + i, SERVO_FLASH_SECTOR);
        if (result != status_success) { s_io_failed = true; return -1; }
        const uint32_t *p = (const uint32_t *)(BOARD_FLASH_BASE_ADDRESS + SERVO_KV_OFFSET + offset + i);
        for (size_t j = 0; j < SERVO_FLASH_SECTOR / 4; j++)
            if (p[j] != UINT32_MAX) { s_io_failed = true; return -1; }
    }
    return (int)size;
}
struct fal_flash_dev servo_nor = {
    .name = "servo_nor", .addr = BOARD_FLASH_BASE_ADDRESS + SERVO_KV_OFFSET,
    .len = SERVO_KV_SIZE, .blk_size = SERVO_FLASH_SECTOR,
    .ops = {nor_init, nor_read, nor_write, nor_erase}, .write_gran = 1
};

FLASHDB_STATUS bsp_flashdb_key_register(FLASHDB_KEY_INDEX index, char *key, void *value, size_t len)
{
    if (s_ready || (unsigned)index >= STORE_MAX_KEYS || !key || !value || !len ||
        len > STORE_MAX_VALUE || strlen(key) >= FDB_KV_NAME_MAX) return FLASHDB_INIT_FAILED;
    s_items[index] = (StoreItem){key, value, len};
    return FLASHDB_NO_ERR;
}
FLASHDB_STATUS bsp_flashdb_init(void)
{
    if (s_ready) return FLASHDB_NO_ERR;
    if (s_db.parent.init_ok) return FLASHDB_INIT_FAILED; /* Reset required after failed I/O. */
    if (bsp_get_pwm_state() || nor_init() != 0) return FLASHDB_INIT_FAILED;
    uint32_t irq = bsp_irq_save();
    s_io_failed = false;
    /* No automatic defaults: missing/deleted values keep the app's RAM defaults.
     * FlashDB formats blank sectors and recovers interrupted KV/GC states. */
    /* Refuse to format an unknown layout. A known FlashDB sector may be
     * recovered by FlashDB; an erased sector may be initialized. */
    for (uint32_t off = 0; off < SERVO_KV_SIZE; off += SERVO_FLASH_SECTOR)
    {
        uint32_t header[2];
        nor_read(off, (uint8_t *)header, sizeof(header));
        bool recognized = header[1] == 0x30424446U;
        if (!recognized && header[0] == UINT32_MAX && header[1] == UINT32_MAX)
        {
            recognized = true;
            const uint32_t *words = (const uint32_t *)(BOARD_FLASH_BASE_ADDRESS + SERVO_KV_OFFSET + off);
            invalidate(off, SERVO_FLASH_SECTOR);
            for (size_t i = 0; i < SERVO_FLASH_SECTOR / 4; i++)
                if (words[i] != UINT32_MAX) { recognized = false; break; }
        }
        if (!recognized)
        {
            bsp_irq_restore(irq);
            return FLASHDB_INIT_FAILED;
        }
    }
    struct fdb_default_kv defaults = {0};
    fdb_err_t result = fdb_kvdb_init(&s_db, "servo", "servo_kv", &defaults, NULL);
    s_ready = result == FDB_NO_ERR && !s_io_failed;
    bsp_irq_restore(irq);
    printf("store: init %s\r\n", s_ready ? "OK" : "FAILED");
    return s_ready ? FLASHDB_NO_ERR : FLASHDB_INIT_FAILED;
}
static bool valid_item(FLASHDB_KEY_INDEX index)
{
    return s_ready && (unsigned)index < STORE_MAX_KEYS && s_items[index].key;
}
FLASHDB_STATUS bsp_flashdb_read(FLASHDB_KEY_INDEX index)
{
    if (!valid_item(index)) return FLASHDB_READ_ERR;
    StoreItem *item = &s_items[index];
    struct fdb_blob blob;
    s_io_failed = false;
    struct fdb_kv kv;
    if (!fdb_kv_get_obj(&s_db, item->key, &kv))
        return s_io_failed ? FLASHDB_READ_ERR : FLASHDB_KEY_NOT_FOUND;
    if (!kv.crc_is_ok || kv.status != FDB_KV_WRITE || s_io_failed) return FLASHDB_READ_ERR;
    size_t n = fdb_kv_get_blob(&s_db, item->key, fdb_blob_make(&blob, &s_blob, sizeof(s_blob)));
    if (s_io_failed) return FLASHDB_READ_ERR;
    if (!n) return FLASHDB_KEY_NOT_FOUND;
    if (n != 12 + item->len || blob.saved.len != n || s_blob.magic != STORE_MAGIC ||
        s_blob.schema != STORE_SCHEMA || s_blob.len != item->len) return FLASHDB_READ_ERR;
    memcpy(item->value, s_blob.data, item->len);
    return FLASHDB_NO_ERR;
}
FLASHDB_STATUS bsp_flashdb_write(FLASHDB_KEY_INDEX index)
{
    if (!valid_item(index) || bsp_get_pwm_state()) return FLASHDB_WRITE_ERR;
    StoreItem *item = &s_items[index];
    s_blob.magic = STORE_MAGIC; s_blob.schema = STORE_SCHEMA; s_blob.len = item->len;
    memcpy(s_blob.data, item->value, item->len);
    struct fdb_blob blob;
    uint32_t irq = bsp_irq_save();
    s_io_failed = false;
    fdb_err_t result = fdb_kv_set_blob(&s_db, item->key, fdb_blob_make(&blob, &s_blob, 12 + item->len));
    bool ok = result == FDB_NO_ERR && !s_io_failed;
    if (s_io_failed) s_ready = false; /* Cached addresses are untrusted after a partial write. */
    bsp_irq_restore(irq);
    return ok ? FLASHDB_NO_ERR : FLASHDB_WRITE_ERR;
}
FLASHDB_STATUS bsp_flashdb_key_delete(FLASHDB_KEY_INDEX index)
{
    if (!valid_item(index) || bsp_get_pwm_state()) return FLASHDB_ERASE_ERR;
    uint32_t irq = bsp_irq_save();
    s_io_failed = false;
    fdb_err_t result = fdb_kv_del(&s_db, s_items[index].key);
    bool ok = (result == FDB_NO_ERR || result == FDB_KV_NAME_ERR) && !s_io_failed;
    if (s_io_failed) s_ready = false;
    bsp_irq_restore(irq);
    /* Deletion does not unregister the RAM destination; a later write is valid. */
    return ok ? FLASHDB_NO_ERR : FLASHDB_ERASE_ERR;
}
