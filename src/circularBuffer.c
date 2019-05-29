#include "circularBuffer.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <stdio.h>


/* **************************** */
/* ***** public functions ***** */

void cBufInit (cBuf_t* buf, uint32_t maxSize)
{
  buf->head = buf->tail = buf->curSize = 0;
  buf->maxSize = maxSize;
  buf->data = (uint8_t*)malloc(maxSize);
}

cBufStatus_t cBufWrite (cBuf_t* buf, uint8_t* dataIn, uint16_t lenIn)
{
  /* stop condition flags */
  if((buf->curSize + lenIn) > buf->maxSize) { return CBUF_FULL; }

  /* write buffer memory */
  uint16_t spaceTillEnd = buf->maxSize - buf->tail;

  if(lenIn <= spaceTillEnd)
  {
    memcpy(&buf->data[buf->tail], &dataIn[0], lenIn);
  }
  else
  {
    /* wrap data to fit in buffer */
    memcpy(&buf->data[buf->tail], &dataIn[0], spaceTillEnd);
    memcpy(&buf->data[0], &dataIn[spaceTillEnd], (lenIn - spaceTillEnd));
  }

  /* update trackers */
  buf->tail = (buf->tail + lenIn) % buf->maxSize;
  buf->curSize = buf->curSize + lenIn;
  
  return CBUF_OK;
}

cBufStatus_t cBufRead (cBuf_t* buf, uint8_t* dataOut, uint16_t lenOut)
{
  /* stop condition flags */
  if(!buf->curSize) { return CBUF_EMPTY; }

  /* find return len */
  uint16_t rtnLen = (buf->curSize < lenOut) ? buf->curSize : lenOut;
  
  /* add null terminator */
  dataOut[rtnLen] = '\0';

  /* find space remaining in buffer */
  uint32_t spaceTillEnd = buf->maxSize - buf->head;

  /* write output memory */
  if(rtnLen < spaceTillEnd)
  {
    memcpy(&dataOut[0], &buf->data[buf->head], rtnLen);
  }
  else
  {
    memcpy(&dataOut[0], &buf->data[buf->head], spaceTillEnd);
    memcpy(&dataOut[spaceTillEnd], &buf->data[0], (rtnLen - spaceTillEnd));
  }

  /* update trackers */
  buf->head = (buf->head + rtnLen) % buf->maxSize;
  buf->curSize = buf->curSize - rtnLen;

  return CBUF_OK;
}

void cBufFree (cBuf_t* buf)
{
  free(buf->data);
  buf->data = NULL;
  buf->head = buf->tail = buf->curSize = buf->maxSize = 0;
}
