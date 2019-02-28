#include "circularBuffer.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>


/* **************************** */
/* ***** public functions ***** */

void cBufInit (cBuf_t* buf, uint32_t maxSize)
{
  buf->head = buf->tail = buf->curSize = 0;
  buf->maxSize = maxSize;
  buf->data = (uint8_t*)malloc(maxSize);
  // TODO: add memory cleanup function
}

cBufStatus_t cBufWrite (cBuf_t* buf, cData_t* data)
{
  /* stop condition flags */
  if((buf->curSize + data->len) >= buf->maxSize) { return CBUF_FULL; }

  /* data in to buffer */
  memcpy(&buf->data[buf->tail], &data->data[0], data->len);

  /* update trackers */
  buf->tail = (buf->tail + data->len) % buf->maxSize;
  buf->curSize = buf->curSize + data->len;
  
  return CBUF_OK;
}

cBufStatus_t cBufRead (cBuf_t* buf, cData_t* data, uint32_t len)
{
  /* stop condition flags */
  if(!buf->curSize) { return CBUF_EMPTY; }

  // TODO: use data.len and buf.CurSize to determine return size
  /* find return len */
  rLen = ()
    
  /* buffer to output */
  // what if memory needed wraps?
  //memcpy(&data->data[0], &buf->data[buf->head], data->len);

  /* update trackers */
  buf->head = (buf->head + data->len) % buf->maxSize;
  buf->curSize = buf->curSize - data->len;

  return CBUF_OK;
}
