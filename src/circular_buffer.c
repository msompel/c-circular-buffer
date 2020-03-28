/* 
 *  Circular FiFo Buffer
 *
 *  @author John E Maddox
 *
 *************************************************/

#include "circular_buffer.h"
#include <stdlib.h>
#include <string.h>


cbuf_handle_t* cbuf_init (size_t max_size)
{
    cbuf_handle_t* handle = (cbuf_handle_t*)malloc(sizeof(cbuf_handle_t));
    handle->data = (uint8_t*)malloc(max_size * sizeof(uint8_t));
    handle->max_size = max_size;

    cbuf_reset(handle);

    return handle;
}

size_t cbuf_size (cbuf_handle_t* buf)
{
    return buf->cur_size;
}

cbuf_status_t cbuf_write (cbuf_handle_t* buf, uint8_t* data_in, size_t size_in)
{
    // stop condition flags
    if((buf->cur_size + size_in) > buf->max_size) { return CBUF_FULL; }

    // write buffer memory
    size_t space_till_end = buf->max_size - buf->tail_idx;

    if(size_in <= space_till_end)
    {
        memcpy(&buf->data[buf->tail_idx], &data_in[0], size_in);
    }
    else
    {
        // wrap data to fit in buffer
        memcpy(&buf->data[buf->tail_idx], &data_in[0], space_till_end);
        memcpy(&buf->data[0], &data_in[space_till_end], (size_in - space_till_end));
    }

    // update trackers
    buf->tail_idx = (buf->tail_idx + size_in) % buf->max_size;
    buf->cur_size = buf->cur_size + size_in;
    
    return CBUF_OK;
}

cbuf_status_t cbuf_read (cbuf_handle_t* buf, uint8_t* data_out, size_t size_out)
{
    // stop condition flags
    if(!buf->cur_size) { return CBUF_EMPTY; }

    // find return length
    size_t size_return = size_out;

    if(buf->cur_size < size_out)
    {
        size_return = buf->cur_size;

        // add null terminator
        data_out[size_return] = '\0';
    }

    // find space remaining in buffer
    size_t space_till_end = buf->max_size - buf->head_idx;

    // write output memory
    if(size_return < space_till_end)
    {
        memcpy(&data_out[0], &buf->data[buf->head_idx], size_return);
    }
    else
    {
        memcpy(&data_out[0], &buf->data[buf->head_idx], space_till_end);
        memcpy(&data_out[space_till_end], &buf->data[0], (size_return - space_till_end));
    }

    // update trackers
    buf->head_idx = (buf->head_idx + size_return) % buf->max_size;
    buf->cur_size = buf->cur_size - size_return;

    return CBUF_OK;
}

void cbuf_reset (cbuf_handle_t* buf)
{
    // clean memory
    int i;
    for (i=0; i < buf->max_size; ++i)
    {
        buf->data[i] = '\0';
    }

    // update trackers
    buf->head_idx = buf->tail_idx = buf->cur_size = 0;
}

void cbuf_free (cbuf_handle_t** buf)
{
    free((*buf)->data);
    (*buf)->data = NULL;

    free(*buf);
    *buf = NULL;
}

/* *************************** */
/* **** private functions **** */

