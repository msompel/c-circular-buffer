/* 
 *  Circular FiFo Buffer
 *
 *  @author John E Maddox
 *
 *************************************************/
 
#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <stdint.h>
#include <stddef.h>


typedef enum
{
    CBUF_OK,
    CBUF_EMPTY,
    CBUF_FULL
} cbuf_status_t;

typedef struct
{
    size_t head_idx;
    size_t tail_idx;
    size_t cur_size;
    size_t max_size;
    uint8_t* data;
} cbuf_handle_t;

// cbuf_init
// max size: size of buffer
cbuf_handle_t* cbuf_init (size_t max_size);

// cbuf_size
// returns current size of buffer
size_t cbuf_size (cbuf_handle_t* buf);

// cbuf_write
// - writes data to circular buffer
// - only writes data if there is enough space available in the buffer
cbuf_status_t cbuf_write (cbuf_handle_t* buf, uint8_t* data_in, size_t size_in);

// cbuf_read
// - writes data from buffer to data output
// - if buffer is empty, returns empty status flag
cbuf_status_t cbuf_read (cbuf_handle_t* buf, uint8_t* data_out, size_t size_out);

// cbuf_reset
// - reset the buffer
void cbuf_reset (cbuf_handle_t* buf);

// cbuf_free
// - free data buffer memory
// - free handle pointer
void cbuf_free (cbuf_handle_t** buf);


#endif // CIRCULAR_BUFFER_H
