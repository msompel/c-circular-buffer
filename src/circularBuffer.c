#include "circularBuffer.h"
#include <stdint.h>
//#include <stdlib.h>


/* **************************** */
/* ***** public functions ***** */

void cBufInit (cBuf_t* buf, cData_t* data, uint32_t maxSize)
{
  buf->head = buf->tail = buf->curSize = 0;
  buf->maxSize = maxSize;
  buf->data = data;
  // QUESTION: are there advantages to using malloc here?
  //buf->data = (cData_t**)malloc(maxSize * sizeof(cData_t*));
}

cBufStatus_t cBufWrite (cBuf_t* buf, cData_t data)
{
  /* stop condition flags */
  if(buf->curSize >= buf->maxSize) { return CBUF_FULL; }

  /* data in to buffer */
  buf->data[buf->tail] = data;

  /* update trackers */
  buf->tail = (buf->tail + 1) % buf->maxSize;
  buf->curSize++;
  
  return CBUF_OK;
}

cBufStatus_t cBufRead (cBuf_t* buf, cData_t* data)
{
  /* stop condition flags */
  if(!buf->curSize) { return CBUF_EMPTY; }
    
  /* buffer to output */
  // QUESTION: should I use memcpy here?
  // should i use pointers instead?
  data->len = buf->data[buf->head].len;
  data->data = buf->data[buf->head].data;

  /* update trackers */
  buf->head = (buf->head + 1) % buf->maxSize;
  buf->curSize--;

  return CBUF_OK;
}
