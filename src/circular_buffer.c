/* 
 *  Circular FiFo Buffer
 *  
 *  Thread safe, can handle multiple producers with the 
 *  option of blocking on writes.
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

#include "circular_buffer.h"
#include <stdlib.h>
#include <string.h>


cbuf_handle_t* cbuf_init (size_t max_size)
{
    cbuf_handle_t* handle = (cbuf_handle_t*)malloc(sizeof(cbuf_handle_t));
    handle->data = (uint8_t*)malloc(max_size * sizeof(uint8_t));
    handle->max_size = max_size;
    handle->is_locked = false;

    cbuf_reset(handle);

    return handle;
}

size_t cbuf_size (cbuf_handle_t* buf)
{
    return buf->cur_size;
}

cbuf_status_t cbuf_put (cbuf_handle_t* buf, uint8_t* data_in, size_t size_in)
{
    // NOTE: lock to prevent race conditions when 
    //       buffer has multiple producers.
    if (true == buf->is_locked) { return CBUF_LOCKED; }
    if ((buf->cur_size + size_in) > buf->max_size) { return CBUF_FULL; }

    buf->is_locked = true;

    size_t end_space = buf->max_size - buf->tail_idx;

    if (size_in <= end_space)
    {
        memcpy(&buf->data[buf->tail_idx], &data_in[0], size_in);
    }
    else
    {
        memcpy(&buf->data[buf->tail_idx], &data_in[0], end_space);
        memcpy(&buf->data[0], &data_in[end_space], (size_in - end_space));
    }

    // NOTE: updating tail_idx and cur_size after write operation
    //       prevents race conditions on read operations 
    buf->tail_idx = (buf->tail_idx + size_in) % buf->max_size;
    buf->cur_size = buf->cur_size + size_in;
    buf->is_locked = false;
       
    return CBUF_OK;
}

cbuf_status_t cbuf_get (cbuf_handle_t* buf, uint8_t* data_out, size_t size_out)
{
    if (!buf->cur_size) { return CBUF_EMPTY; }

    // set output size by comparing available data to requested data
    if (buf->cur_size < size_out)
    {
        size_out = buf->cur_size;
        data_out[size_out] = '\0';
    }

    size_t end_space = buf->max_size - buf->head_idx;

    if(size_out <= end_space)
    {
        memcpy(&data_out[0], &buf->data[buf->head_idx], size_out);
    }
    else
    {
        memcpy(&data_out[0], &buf->data[buf->head_idx], end_space);
        memcpy(&data_out[end_space], &buf->data[0], (size_out - end_space));
    }

    buf->head_idx = (buf->head_idx + size_out) % buf->max_size;
    buf->cur_size = buf->cur_size - size_out;

    return CBUF_OK;
}

void cbuf_reset (cbuf_handle_t* buf)
{
    for (size_t i=0; i < buf->max_size; ++i)
    {
        buf->data[i] = '\0';
    }

    buf->head_idx = buf->tail_idx = buf->cur_size = 0;
}

void cbuf_free (cbuf_handle_t** buf)
{
    free((*buf)->data);
    (*buf)->data = NULL;

    free(*buf);
    *buf = NULL;
}
