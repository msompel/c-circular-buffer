/* 
 *  Circular FiFo Buffer
 *
 *  @author John E Maddox
 *
 *************************************************/

#include "circularBuffer.h"
#include <stdlib.h>
#include <string.h>


/*  cBufInit
 *  size: size of data array
 */
cBufHandle_t* cBufInit (uint32_t _size)
{
  cBufHandle_t* handle = (cBufHandle_t*)malloc(sizeof(cBufHandle_t));
  handle->data = (uint8_t*)malloc(_size * sizeof(uint8_t));
  handle->maxSize = _size;

  /* start with a clean buffer */
  cBufReset(handle);

  return handle;
}

/*  cBufWrite
 *  - writes data to circular buffer
 *  - only writes data if there is enough space available in the buffer
 */
cBufStatus_t cBufWrite (cBufHandle_t* _buf, uint8_t* _dataIn, uint16_t _lenIn)
{
  /* stop condition flags */
  if((_buf->curSize + _lenIn) > _buf->maxSize) { return eCBufFull; }

  /* write buffer memory */
  uint16_t spaceTillEnd = _buf->maxSize - _buf->tail;

  if(_lenIn <= spaceTillEnd)
  {
    memcpy(&_buf->data[_buf->tail], &_dataIn[0], _lenIn);
  }
  else
  {
    /* wrap data to fit in buffer */
    memcpy(&_buf->data[_buf->tail], &_dataIn[0], spaceTillEnd);
    memcpy(&_buf->data[0], &_dataIn[spaceTillEnd], (_lenIn - spaceTillEnd));
  }

  /* update trackers */
  _buf->tail = (_buf->tail + _lenIn) % _buf->maxSize;
  _buf->curSize = _buf->curSize + _lenIn;
  
  return eCBufOk;
}

/*  cBufRead
 *  - writes data from buffer to data array
 *  - dynamically allocates output memory, use cBufFreeData to free memory
 */
cBufStatus_t cBufRead (cBufHandle_t* _buf, uint8_t* _dataOut, uint16_t _lenOut)
{
  /* stop condition flags */
  if(!_buf->curSize) { return eCBufEmpty; }

  /* find return length */
  uint16_t rtnLen = _lenOut;

  if(_buf->curSize < _lenOut)
  {
    rtnLen = _buf->curSize;

    /* add null terminator */
    _dataOut[rtnLen] = '\0';
  }

  /* find space remaining in buffer */
  uint32_t spaceTillEnd = _buf->maxSize - _buf->head;

  /* write output memory */
  if(rtnLen < spaceTillEnd)
  {
    memcpy(&_dataOut[0], &_buf->data[_buf->head], rtnLen);
  }
  else
  {
    memcpy(&_dataOut[0], &_buf->data[_buf->head], spaceTillEnd);
    memcpy(&_dataOut[spaceTillEnd], &_buf->data[0], (rtnLen - spaceTillEnd));
  }

  /* update trackers */
  _buf->head = (_buf->head + rtnLen) % _buf->maxSize;
  _buf->curSize = _buf->curSize - rtnLen;

  return eCBufOk;
}

/*  cBufReset
 *  - reset the buffer
 */
void cBufReset (cBufHandle_t* _buf)
{
  /* clean memory */
  int i;
  for (i=0; i < _buf->maxSize; ++i)
  {
    _buf->data[i] = '\0';
  }

  /* update trackers */
  _buf->head = _buf->tail = _buf->curSize = 0;
}

/*  cBufFree
 *  - free data buffer memory
 *  - free handle pointer
 */
void cBufFree (cBufHandle_t** _buf)
{
  free((*_buf)->data);
  (*_buf)->data = NULL;

  free(*_buf);
  *_buf = NULL;
}
