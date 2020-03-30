/* 
 *  Circular FiFo Buffer
 *  
 *  Thread safe, can handle multiple producers with the 
 *  option of blocking on writes (a flag is returned).
 *  
 *  - deque is always non-blocking, data is only available after 
 *    it is written.
 *  
 *  - enque will only allow one write operation at a time, under 
 *    single producer programs this will not be an issue. With 
 *    multiple producers, write overlaps return a flag. This 
 *    allows the producer to decide how to handle the collision.
 *   
 *  @author John E Maddox
 * 
***************************************************************/
 
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

// - allocates data and handle memory
// - max size: size of buffer
// - returns buffer handle
cbuf_handle_t* cbuf_init (size_t max_size);

// - returns current size of buffer
size_t cbuf_size (cbuf_handle_t* buf);

// - writes data to circular buffer
// - only writes data if there is enough space available in the buffer
// - returns flag if attempting to write data simultaneously
cbuf_status_t cbuf_enque (cbuf_handle_t* buf, uint8_t* data_in, size_t size_in);

// - writes data from buffer to data output
// - if buffer is empty, returns empty status flag
cbuf_status_t cbuf_deque (cbuf_handle_t* buf, uint8_t* data_out, size_t size_out);

// - clears buffer memory
// - resets buffer counters
void cbuf_reset (cbuf_handle_t* buf);

// - free data buffer memory
// - free handle pointer
// - set pointers to NULL
void cbuf_free (cbuf_handle_t** buf);


#endif // CIRCULAR_BUFFER_H
