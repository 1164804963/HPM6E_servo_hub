#include "ringbuffer.h"

enum ringbuffer_state ringbuffer_status(struct ringbuffer *rb) {
    if (rb->read_index == rb->write_index) {
        if (rb->read_mirror == rb->write_mirror)
            return RINGBUFFER_EMPTY;
        else
            return RINGBUFFER_FULL;
    }
    return RINGBUFFER_HALFFULL;
}

void ringbuffer_init(struct ringbuffer *rb, uint8_t *pool, int16_t size) {
    rb->read_mirror = rb->read_index = 0;
    rb->write_mirror = rb->write_index = 0;

    rb->buffer_ptr = pool;
    rb->buffer_size = RB_ALIGN_DOWN(size, RB_ALIGN_SIZE);
}

uint16_t ringbuffer_put(struct ringbuffer *rb, const uint8_t *ptr, uint16_t length) {
    uint16_t size;

    size = ringbuffer_space_len(rb);

    if (size == 0) return 0;

    if (size < length) length = size;

    if (rb->buffer_size - rb->write_index > length) {
        memcpy(&rb->buffer_ptr[rb->write_index], ptr, length);
        rb->write_index += length;
        return length;
    }

    memcpy(&rb->buffer_ptr[rb->write_index], &ptr[0], rb->buffer_size - rb->write_index);
    memcpy(&rb->buffer_ptr[0], &ptr[rb->buffer_size - rb->write_index],
           length - (rb->buffer_size - rb->write_index));

    rb->write_mirror = ~rb->write_mirror;
    rb->write_index = length - (rb->buffer_size - rb->write_index);

    return length;
}

uint16_t ringbuffer_put_force(struct ringbuffer *rb, const uint8_t *ptr, uint16_t length) {
    uint16_t space_length;
    space_length = ringbuffer_space_len(rb);

    if (length > rb->buffer_size) {
        ptr = &ptr[length - rb->buffer_size];
        length = rb->buffer_size;
    }

    if (rb->buffer_size - rb->write_index > length) {
        memcpy(&rb->buffer_ptr[rb->write_index], ptr, length);
        rb->write_index += length;

        if (length > space_length) rb->read_index = rb->write_index;

        return length;
    }

    memcpy(&rb->buffer_ptr[rb->write_index], &ptr[0], rb->buffer_size - rb->write_index);
    memcpy(&rb->buffer_ptr[0], &ptr[rb->buffer_size - rb->write_index],
           length - (rb->buffer_size - rb->write_index));

    rb->write_mirror = ~rb->write_mirror;
    rb->write_index = length - (rb->buffer_size - rb->write_index);

    if (length > space_length) {
        rb->read_mirror = ~rb->read_mirror;
        rb->read_index = rb->write_index;
    }

    return length;
}

uint16_t ringbuffer_get(struct ringbuffer *rb, uint8_t *ptr, uint16_t length) {
    uint16_t size;

    size = ringbuffer_data_len(rb);

    if (size == 0) return 0;

    if (size < length) length = size;

    if (rb->buffer_size - rb->read_index > length) {
        memcpy(ptr, &rb->buffer_ptr[rb->read_index], length);
        rb->read_index += length;
        return length;
    }

    memcpy(&ptr[0], &rb->buffer_ptr[rb->read_index], rb->buffer_size - rb->read_index);
    memcpy(&ptr[rb->buffer_size - rb->read_index], &rb->buffer_ptr[0],
           length - (rb->buffer_size - rb->read_index));

    rb->read_mirror = ~rb->read_mirror;
    rb->read_index = length - (rb->buffer_size - rb->read_index);

    return length;
}


uint16_t ringbuffer_putchar(struct ringbuffer *rb, const uint8_t ch) {
    if (!ringbuffer_space_len(rb)) return 0;

    rb->buffer_ptr[rb->write_index] = ch;

    if (rb->write_index == rb->buffer_size - 1) {
        rb->write_mirror = ~rb->write_mirror;
        rb->write_index = 0;
    } else {
        rb->write_index++;
    }

    return 1;
}

uint16_t ringbuffer_putchar_force(struct ringbuffer *rb, const uint8_t ch) {
    enum ringbuffer_state old_state;

    old_state = ringbuffer_status(rb);

    rb->buffer_ptr[rb->write_index] = ch;

    if (rb->write_index == rb->buffer_size - 1) {
        rb->write_mirror = ~rb->write_mirror;
        rb->write_index = 0;
        if (old_state == RINGBUFFER_FULL) {
            rb->read_mirror = ~rb->read_mirror;
            rb->read_index = rb->write_index;
        }
    } else {
        rb->write_index++;
        if (old_state == RINGBUFFER_FULL) rb->read_index = rb->write_index;
    }

    return 1;
}

uint16_t ringbuffer_getchar(struct ringbuffer *rb, uint8_t *ch) {
    if (!ringbuffer_data_len(rb)) return 0;

    *ch = rb->buffer_ptr[rb->read_index];

    if (rb->read_index == rb->buffer_size - 1) {
        rb->read_mirror = ~rb->read_mirror;
        rb->read_index = 0;
    } else {
        rb->read_index++;
    }

    return 1;
}

uint16_t ringbuffer_data_len(struct ringbuffer *rb) {
    switch (ringbuffer_status(rb)) {
        case RINGBUFFER_EMPTY:
            return 0;
        case RINGBUFFER_FULL:
            return rb->buffer_size;
        case RINGBUFFER_HALFFULL:
        default:
            if (rb->write_index > rb->read_index)
                return rb->write_index - rb->read_index;
            else
                return rb->buffer_size - (rb->read_index - rb->write_index);
    };
}

void ringbuffer_reset(struct ringbuffer *rb) {
    rb->read_mirror = 0;
    rb->read_index = 0;
    rb->write_mirror = 0;
    rb->write_index = 0;
}


/*------------------------------------------------------------------------------
------
------    自己补充的功能
------
------------------------------------------------------------------------------*/
/*--------------------------------------
-	偏移一定位置进行读取，并且不改变原读取指针
--------------------------------------*/
uint16_t ringbuffer_get_offset(struct ringbuffer *rb, uint8_t *ptr, uint16_t offset_length,
                               uint16_t length) {
    uint16_t size;

    size = ringbuffer_data_len(rb);

    if (size == 0) return 0;

    /*	如果偏移位置后没有数据，则直接退出	*/
    if (size < offset_length) return 0;

    /* 如果没有足够的数据，则提取剩下的数据 */
    if (size < (length + offset_length)) { length = size - offset_length; }


    /* 如果末尾有足够的数据 */
    if (rb->buffer_size - (rb->read_index + offset_length) >= length) {
        memcpy(ptr, &rb->buffer_ptr[rb->read_index + offset_length], length);
        return length;
    }

    /* 如果末尾连偏移的量都不够 */
    if ((rb->buffer_size - rb->read_index) < offset_length) {
        memcpy(&ptr[0], &rb->buffer_ptr[offset_length - (rb->buffer_size - rb->read_index)],
               length);
        return length;
    }

    /* 如果末尾没有足够的数据 */
    if ((rb->buffer_size - rb->read_index) < (length + offset_length)) {
        memcpy(&ptr[0], &rb->buffer_ptr[rb->read_index + offset_length],
               rb->buffer_size - (rb->read_index + offset_length));
        memcpy(&ptr[rb->buffer_size - (rb->read_index + offset_length)], &rb->buffer_ptr[0],
               length - (rb->buffer_size - (rb->read_index + offset_length)));
        return length;
    }
    return 0;
}


/*--------------------------------------
-	循环写入数据，可以超过一个循环的写
，但是不能一次写超过一个buffer的数据
--------------------------------------*/
uint16_t ringbuffer_put_overlayable(struct ringbuffer *rb, const uint8_t *ptr, uint16_t length) {
    if (rb->buffer_size < length) return 0;

    if (rb->buffer_size - rb->write_index > length) {
        memcpy(&rb->buffer_ptr[rb->write_index], ptr, length);
        rb->write_index += length;
        return length;
    }

    memcpy(&rb->buffer_ptr[rb->write_index], &ptr[0], rb->buffer_size - rb->write_index);
    memcpy(&rb->buffer_ptr[0], &ptr[rb->buffer_size - rb->write_index],
           length - (rb->buffer_size - rb->write_index));

    rb->write_mirror = ~rb->write_mirror;
    rb->write_index = length - (rb->buffer_size - rb->write_index);

    return length;
}

/*--------------------------------------
-	覆盖写入数据，但是不造成write和read
指针的偏移
--------------------------------------*/
uint16_t ringbuffer_put_no_rw_offset(struct ringbuffer *rb, const uint8_t *ptr, uint16_t length) {
    if (rb->buffer_size < length) return 0;

    if (rb->buffer_size - rb->write_index > length) {
        memcpy(&rb->buffer_ptr[rb->write_index], ptr, length);
        return length;
    }

    memcpy(&rb->buffer_ptr[rb->write_index], &ptr[0], rb->buffer_size - rb->write_index);
    memcpy(&rb->buffer_ptr[0], &ptr[rb->buffer_size - rb->write_index],
           length - (rb->buffer_size - rb->write_index));

    return length;
}


/*--------------------------------------
-	根据需要设置read_index位置
--------------------------------------*/
uint16_t ringbuffer_set_read_index(struct ringbuffer *rb, uint16_t new_index, uint16_t new_mirror) {
    rb->read_index = new_index;
    rb->read_mirror = new_mirror;
    return 0;
}

/*--------------------------------------
-	根据需要获取read_index位置
--------------------------------------*/
uint16_t ringbuffer_get_read_index(struct ringbuffer *rb, uint16_t *actual_index,
                                   uint16_t *actual_mirror) {
    *actual_index = rb->read_index;
    *actual_mirror = rb->read_mirror;
    return 0;
}

/*--------------------------------------
-	根据需要设置write_index位置
--------------------------------------*/
uint16_t ringbuffer_set_write_index(struct ringbuffer *rb, uint16_t new_index,
                                    uint16_t new_mirror) {
    rb->write_index = new_index;
    rb->write_mirror = new_mirror;
    return 0;
}

/*--------------------------------------
-	根据需要获取read_index位置
--------------------------------------*/
uint16_t ringbuffer_get_write_index(struct ringbuffer *rb, uint16_t *actual_index,
                                    uint16_t *actual_mirror) {
    *actual_index = rb->write_index;
    *actual_mirror = rb->write_mirror;
    return 0;
}

/*--------------------------------------
-	根据write_index的位置，获取向前偏移后的位置
--------------------------------------*/
uint16_t ringbuffer_get_write_index_offset(struct ringbuffer *rb, uint16_t offset_index,
                                           uint16_t *actual_index, uint16_t *actual_mirror) {
    if (offset_index <= rb->write_index) {
        *actual_index = rb->write_index - offset_index;
        *actual_mirror = rb->write_mirror;
        return 0;
    } else {
        *actual_index = rb->buffer_size - (offset_index - rb->write_index);
        *actual_mirror = ~(rb->write_mirror);
        return 0;
    }
}


#ifdef RB_USING_HEAP
struct ringbuffer *ringbuffer_create(uint16_t size) {
    struct ringbuffer *rb;
    uint8_t *pool;

    size = RB_ALIGN_DOWN(size, RB_ALIGN_SIZE);

    rb = (struct rt_ringbuffer *)MMEMORY_ALLOC(sizeof(struct ringbuffer));
    if (rb == NULL) goto exit;

    pool = (uint8_t *)MMEMORY_ALLOC(size);
    if (pool == NULL) {
        MMEMORY_FREE(rb);
        rb = NULL;
        goto exit;
    }
    ringbuffer_init(rb, pool, size);

exit:
    return rb;
}

void ringbuffer_destroy(struct ringbuffer *rb) {
    MMEMORY_FREE(rb->buffer_ptr);
    MMEMORY_FREE(rb);
}

#endif
