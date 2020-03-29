/* 
 *  Circular FiFo Buffer
 *
 *  Thread safe, can handle multiple producers with the possibility of blocking on writes.
 * 
 *  - dequeue is always non-blocking, data is only available after it is written.
 * 
 *  - enqueue will only allow one write operation at a time, under single producer
 *    programs this will not be an issue. With multiple producers, write overlaps return
 *    a flag. This allows the producer to decide how to handle the collision.
 * 
 *  @author John E Maddox
 * 
*******************************************************************************************/
 
#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>


typedef enum
{
    CBUF_OK,
    CBUF_EMPTY,
    CBUF_LOCKED,
    CBUF_FULL
} cbuf_status_t;

typedef struct
{
    size_t head_idx;
    size_t tail_idx;
    size_t cur_size;
    size_t max_size;
    bool   is_locked;
    uint8_t* data;
} cbuf_handle_t;

// cbuf_init
// max size: size of buffer
cbuf_handle_t* cbuf_init (size_t max_size);

// cbuf_size
// returns current size of buffer
size_t cbuf_size (cbuf_handle_t* buf);

// cbuf_enque
// - writes data to circular buffer
// - only writes data if there is enough space available in the buffer
// - returns flag if attempting to write data simultaneously
cbuf_status_t cbuf_enque (cbuf_handle_t* buf, uint8_t* data_in, size_t size_in);

// cbuf_deque
// - writes data from buffer to data output
// - if buffer is empty, returns empty status flag
cbuf_status_t cbuf_deque (cbuf_handle_t* buf, uint8_t* data_out, size_t size_out);

// cbuf_reset
// - reset the buffer
void cbuf_reset (cbuf_handle_t* buf);

// cbuf_free
// - free data buffer memory
// - free handle pointer
void cbuf_free (cbuf_handle_t** buf);


#endif // CIRCULAR_BUFFER_H
