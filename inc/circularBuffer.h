/* 
 *  Circular FiFo Buffer
 *
 *  @author John E Maddox
 *
 *************************************************/
 
#ifndef __CIRCULAR_BUFFER_H
#define __CIRCULAR_BUFFER_H

#include <stdint.h>

typedef enum
{
  eCBufOk,
  eCBufEmpty,
  eCBufFull,
  endOfCBufStatus
} cBufStatus_t;

typedef struct
{
  uint32_t head;
  uint32_t tail;
  uint32_t curSize;
  uint32_t maxSize;
  uint8_t* data;
} cBufHandle_t;


cBufHandle_t* cBufInit (uint32_t _size);

cBufStatus_t cBufWrite (cBufHandle_t* _buf, uint8_t* _dataIn, uint16_t _lenIn);

cBufStatus_t cBufRead (cBufHandle_t* _buf, uint8_t* _dataOut, uint16_t _lenOut);

void cBufReset (cBufHandle_t* _buf);

void cBufFree (cBufHandle_t** _buf);


#endif /* __CIRCULAR_BUFFER_H */
