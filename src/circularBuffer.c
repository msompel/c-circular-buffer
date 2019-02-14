#include "circularBuffer.h"
#include "helpers.h"
#include <stdint.h>


/* ***************************** */
/* ***** private variables ***** */



/* ****************************** */
/* **** private declarations **** */

static void cBufDefaults (cBuf_t* buf);

static void cBufPos (cBuf_t* buf, uint32_t* pos);

/* **************************** */
/* ***** public functions ***** */

void cBufInit (cBuf_t* buf, uint32_t bufSize, uint32_t dataSize)
{
  cBufDefaults(buf);
  buf->maxSize = bufSize;

  /* memory allocation */
  
}

void cBufWrite (cBuf_t* buf)
{

}

void cBufRead (cBuf_t* buf)
{

}

void cBufReset (cBuf_t* buf)
{
  cBufDefaults(buf);

}


/* ***************************** */
/* ***** private functions ***** */

static void cBufDefaults (cBuf_t* buf)
{
  buf->head = buf->tail = buf->curSize = 0;
  buf->lock = OFF;
}

static void cBufPos (cBuf_t* buf, uint32_t* pos)
{
  *pos = (*pos == buf->maxSize - 1) ? 0 : *pos + 1;
}
