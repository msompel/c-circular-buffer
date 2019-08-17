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
} cBuf_t;


/* ************************** */
/* **** public functions **** */

/*  cBufInit
 *  buf:     the controller for the buffer
 *  data:    a pointer to the data buffer
 *  size: this is the size of the data array (ex. 1024)
 * 
 *  - sets default values
 *  - adds 
 */ 
void cBufInit (cBuf_t* _buf, uint8_t* _data, uint32_t _size);

/*  cBufWrite
 *  - writes data to circular buffer
 *  - only writes data if there is enough space available in the buffer
 */
cBufStatus_t cBufWrite (cBuf_t* _buf, uint8_t* _dataIn, uint16_t _lenIn);

/*  cBufRead
 *  - writes data from buffer to data array
 *  - dynamically allocates output memory, use cBufFreeData to free memory
 */
cBufStatus_t cBufRead (cBuf_t* _buf, uint8_t* _dataOut, uint16_t _lenOut);

/*  cBufFree
 *  - free data buffer memory
 */
void cBufEmpty (cBuf_t* _buf);

#endif /* __CIRCULAR_BUFFER_H */
