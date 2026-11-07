#include "drv_nor_flash.h"

#include "bsp_nor_flash.h"

/* KVDB object */
static FLASHDB_STATUS fdb_err_code = FLASHDB_NO_ERR;
static struct fdb_kvdb kvdb = {0};
static struct fdb_default_kv default_kv;
static struct fdb_default_kv_node default_kv_table[FLASHDB_KEYS_NUM];

struct fal_flash_dev nor_flash0 =
{
    .name       = FAL_USING_NOR_FLASH_DEV_NAME,
    .addr       = GD25Q64_BASE_ADDR,
    .len        = GD25Q64_TOTAL_SIZE,
    .blk_size   = GD25Q64_SECTOR_SIZE,
    .ops        = {bsp_nor_flash_init, \
                   bsp_nor_flash_read, \
                   bsp_nor_flash_write, \
                   bsp_nor_flash_erase},
    .write_gran = FDB_WRITE_GRAN
};


// lock and unlock function for KVDB
static void lock(fdb_db_t db)
{
    __disable_irq();
}
static void unlock(fdb_db_t db)
{
    __enable_irq();
}

/**
  * @brief Flashdb初始化
  * @param void
  * @retval fdb_err_t
  * @note
  */
FLASHDB_STATUS flashdb_init(void)
{
    struct fdb_kv kv;
    struct fdb_blob blob;

    default_kv.kvs = default_kv_table;
    default_kv.num = FLASHDB_KEYS_NUM;

    /* set the lock and unlock function if you want */
    fdb_kvdb_control(&kvdb, FDB_KVDB_CTRL_SET_LOCK, (void *)lock);
    fdb_kvdb_control(&kvdb, FDB_KVDB_CTRL_SET_UNLOCK, (void *)unlock);

    /* Key-Value database initialization
         *
         *        &kvdb: database object
         *    "YuanHub": database name
         * "flashdb_kv": The flash partition name base on FAL. Please make sure it's in FAL partition table.
         *               Please change to YOUR partition name.
         *  &default_kv: The default KV nodes. It will auto add to KVDB when first initialize successfully.
         *         NULL: The user data if you need, now is empty.
         */
    fdb_err_code = (FLASHDB_STATUS)fdb_kvdb_init(&kvdb, "YuanHub", "flashdb_kv", &default_kv, NULL);
    if (fdb_err_code != FLASHDB_NO_ERR)
    {
        return fdb_err_code;
    }

    /* check if the default kv nodes are in the kvdb */
    for (uint8_t index = 0; index < default_kv.num; index++)
    {
        if (fdb_kv_get_obj(&kvdb, default_kv.kvs[index].key, &kv) == NULL)
        {
            fdb_err_code = (FLASHDB_STATUS)fdb_kv_set_blob(&kvdb, default_kv.kvs[index].key, \
            fdb_blob_make(&blob, default_kv.kvs[index].value, default_kv.kvs[index].value_len));
            if (fdb_err_code != FLASHDB_NO_ERR)
            {
                return fdb_err_code;
            }
        }
    }

    return fdb_err_code;
}
/**
  * @brief Flashdb数据读取
  * @param index: 目标数据键值索引
  * @retval fdb_err_t
  * @note
  */
FLASHDB_STATUS flashdb_read(FLASHDB_KEY_INDEX const index)
{
    struct fdb_blob blob;

    size_t read_size = fdb_kv_get_blob(&kvdb, default_kv_table[index].key, \
                                       fdb_blob_make(&blob, \
                                                     default_kv_table[index].value, \
                                                     default_kv_table[index].value_len));

    if (read_size != 0)
    {
        return FLASHDB_NO_ERR;
    }
    return FLASHDB_READ_ERR;
}

/**
  * @brief Flashdb数据写入
  * @param index: 目标数据键值索引
  * @retval fdb_err_t
  * @note
  */
FLASHDB_STATUS flashdb_write(FLASHDB_KEY_INDEX const index)
{
    struct fdb_blob blob;

    return (FLASHDB_STATUS)fdb_kv_set_blob(&kvdb, default_kv_table[index].key, \
                                           fdb_blob_make(&blob, \
                                                         default_kv_table[index].value, \
                                                         default_kv_table[index].value_len));
}

/**
  * @brief Flashdb注册键值
  * @param index: 目标数据键值索引
  * @param key: 目标数据键值
  * @param value: 目标数据地址
  * @param value_len: 目标数据长度
  * @retval fdb_err_t
  * @note
  */
FLASHDB_STATUS flashdb_key_register(FLASHDB_KEY_INDEX const index, char *key, void *value, size_t value_len)
{
    if (index > FLASHDB_KEY_INDEX_MAX)
    {
        return FLASHDB_WRITE_ERR;
    }
    default_kv_table[index].key = key;
    default_kv_table[index].value = value;
    default_kv_table[index].value_len = value_len;
    return FLASHDB_NO_ERR;
}

/**
  * @brief Flashdb数据删除
  * @param index: 目标数据键值索引
  * @retval FLASHDB_STATUS
  * @note
  */
FLASHDB_STATUS flashdb_key_delete(FLASHDB_KEY_INDEX const index)
{
    return (FLASHDB_STATUS)fdb_kv_del(&kvdb, default_kv_table[index].key);
}
