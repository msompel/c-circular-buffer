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
}

cBufStatus_t cBufWrite (cBuf_t* buf, cData_t* data)
{
  /* stop condition flags */
  if((buf->curSize + data->len) >= buf->maxSize) { return CBUF_FULL; }

  /* write buffer memory */
  uint32_t rem = buf->maxSize - buf->tail;
  if(data->len < rem)
  {
    memcpy(&buf->data[buf->tail], &data->data[0], data->len);
  }
  else
  {
    /* wrap data to fit in buffer */
    memcpy(&buf->data[buf->tail], &data->data[0], rem);
    memcpy(&buf->data[0], &data->data[rem], (data->len - rem));
  }

  /* update trackers */
  buf->tail = (buf->tail + data->len) % buf->maxSize;
  buf->curSize = buf->curSize + data->len;
  
  return CBUF_OK;
}

cBufStatus_t cBufRead (cBuf_t* buf, cData_t* data, uint16_t len)
{
  /* stop condition flags */
  if(!buf->curSize) { return CBUF_EMPTY; }

  /* find return len */
  uint32_t rLen = (buf->curSize < len) ? buf->curSize : len;

  /* allocate output memory */
  data->data = (uint8_t*)malloc(rLen);
  data->len = rLen;

  /* write output memory */
  uint32_t rem = buf->maxSize - buf->head;
  if(rLen < rem)
  {
    memcpy(&data->data[0], &buf->data[buf->head], rLen);
  }
  else
  {
    memcpy(&data->data[0], &buf->data[buf->head], rem);
    memcpy(&data->data[rem], &buf->data[0], (rLen - rem));
  }

  /* update trackers */
  buf->head = (buf->head + rLen) % buf->maxSize;
  buf->curSize = buf->curSize - rLen;

  return CBUF_OK;
}

void cBufFreeData (cData_t* data)
{
  free(data->data);
}

void cBufFree (cBuf_t* buf)
{
  buf->head = buf->tail = buf->curSize = 0;
  free(buf->data);
}
