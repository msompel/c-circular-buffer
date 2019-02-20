#include "circularBuffer.h"
#include "helpers.h"
#include <stdint.h>


/* ****************************** */
/* **** private declarations **** */

/*  shiftPos
 *  increments index, if max level is reached the index moves to zero
 */
static uint32_t shiftPos (uint32_t maxSize, uint32_t pos);


/* **************************** */
/* ***** public functions ***** */

void cBufInit (cBuf_t* buf, uint8_t* data, uint32_t maxSize)
{
  buf->head = buf->tail = buf->curSize = 0;
  buf->lock = OFF;
  buf->maxSize = maxSize;
  buf->data = data;
}

cBufStatus_t cBufWrite (cBuf_t* buf, uint8_t* data, uint32_t len)
{
  /* stop condition flags */
  if((buf->curSize + len) > buf->maxSize) { return CBUF_FULL; }
  
  buf->lock = ON;

  static uint32_t i;
  for(i=0; i<len; i++)
  {
    /* write data to buffer */
    buf->data[buf->tail] = data[i];

    /* update trackers */
    buf->tail = shiftPos(buf->maxSize, buf->tail);
    buf->curSize++;
  }

  buf->lock = OFF;

  return CBUF_OK;
}

cBufStatus_t cBufRead (cBuf_t* buf, uint8_t* data, uint32_t len)
{
  /* stop condition flags */
  if(!buf->curSize) { return CBUF_EMPTY; }
    
  /* set return size */
  static uint32_t rLen;
  rLen = (buf->curSize < len) ? buf->curSize : len;

  static uint32_t i;
  for(i=0; i<len; i++)
  {
    /* locks memory block that is being written to */
    while (buf->lock && (buf->head == buf->tail)) { }

    if(i < rLen)
    {
      /* read data from buffer */
      data[i] = buf->data[buf->head];

      /* update trackers */
      buf->head = shiftPos(buf->maxSize, buf->head);
      buf->curSize--;
    }
    else
    {
      /* fill unused data array space with zeros */
      data[i] = 0;
    }
  }
  return CBUF_OK;
}


/* ***************************** */
/* ***** private functions ***** */

static uint32_t shiftPos (uint32_t max, uint32_t pos)
{
  return (pos == max - 1) ? 0 : pos + 1;
}
