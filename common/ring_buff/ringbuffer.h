#ifndef __ringbuffer_H
#define __ringbuffer_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <string.h>

#define RB_ALIGN_SIZE 4
#define RB_ALIGN_DOWN(size, align) ((size) & ~((align)-1))

typedef struct ringbuffer {
    uint8_t *buffer_ptr;
    uint16_t read_mirror : 1;
    uint16_t read_index : 15;
    uint16_t write_mirror : 1;
    uint16_t write_index : 15;
    int16_t buffer_size;  // max size 32KB
} ToolModuleRingBuffer;

enum ringbuffer_state {
    RINGBUFFER_EMPTY,
    RINGBUFFER_FULL,
    RINGBUFFER_HALFFULL,
};

void ringbuffer_init(struct ringbuffer *rb, uint8_t *pool, int16_t size);
void ringbuffer_reset(struct ringbuffer *rb);
uint16_t ringbuffer_put(struct ringbuffer *rb, const uint8_t *ptr, uint16_t length);
uint16_t ringbuffer_put_force(struct ringbuffer *rb, const uint8_t *ptr, uint16_t length);
uint16_t ringbuffer_putchar(struct ringbuffer *rb, const uint8_t ch);
uint16_t ringbuffer_putchar_force(struct ringbuffer *rb, const uint8_t ch);
uint16_t ringbuffer_get(struct ringbuffer *rb, uint8_t *ptr, uint16_t length);
uint16_t ringbuffer_getchar(struct ringbuffer *rb, uint8_t *ch);
uint16_t ringbuffer_data_len(struct ringbuffer *rb);


uint16_t ringbuffer_get_offset(struct ringbuffer *rb, uint8_t *ptr, uint16_t offset_length,
                               uint16_t length);
uint16_t ringbuffer_put_overlayable(struct ringbuffer *rb, const uint8_t *ptr, uint16_t length);
uint16_t ringbuffer_put_no_rw_offset(struct ringbuffer *rb, const uint8_t *ptr, uint16_t length);
uint16_t ringbuffer_set_read_index(struct ringbuffer *rb, uint16_t new_index, uint16_t new_mirror);
uint16_t ringbuffer_get_read_index(struct ringbuffer *rb, uint16_t *actual_index,
                                   uint16_t *actual_mirror);
uint16_t ringbuffer_set_write_index(struct ringbuffer *rb, uint16_t new_index, uint16_t new_mirror);
uint16_t ringbuffer_get_write_index(struct ringbuffer *rb, uint16_t *actual_index,
                                    uint16_t *actual_mirror);
uint16_t ringbuffer_get_write_index_offset(struct ringbuffer *rb, uint16_t offset_index,
                                           uint16_t *actual_index, uint16_t *actual_mirror);

#ifdef RB_USING_HEAP
#define MMEMORY_ALLOC malloc
#define MMEMORY_FREE free
struct ringbuffer *ringbuffer_create(uint16_t size);
void ringbuffer_destroy(struct ringbuffer *rb);
#endif

inline uint16_t ringbuffer_get_size(struct ringbuffer *rb) {
    return rb->buffer_size;
}

#define ringbuffer_space_len(rb) ((rb)->buffer_size - ringbuffer_data_len(rb))


#ifdef __cplusplus
}
#endif

#endif
