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
    if ((buf->cur_size + size_in) > buf->max_size) { return CBUF_FULL; }

    size_t end_space = buf->max_size - buf->tail_idx;

    if (size_in < end_space)
    {
        memcpy(&buf->data[buf->tail_idx], &data_in[0], size_in);
    }
    else
    {
        memcpy(&buf->data[buf->tail_idx], &data_in[0], end_space);
        memcpy(&buf->data[0], &data_in[end_space], (size_in - end_space));
    }

    buf->tail_idx = (buf->tail_idx + size_in) % buf->max_size;
    buf->cur_size = buf->cur_size + size_in;
       
    return CBUF_OK;
}

cbuf_status_t cbuf_read (cbuf_handle_t* buf, uint8_t* data_out, size_t size_out)
{
    if (!buf->cur_size) { return CBUF_EMPTY; }

   
    if (buf->cur_size < size_out)
    {
        size_out = buf->cur_size;
        data_out[size_out] = '\0';
    }

    size_t end_space = buf->max_size - buf->head_idx;

    if(size_out < end_space)
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
