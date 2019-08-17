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
 *  maxSize: this is the size of the data array (ex. 1024)
 * 
 *  - sets default values
 *  - allocates memory for data buffer based on maxSize
 */ 
void cBufInit (cBuf_t* buf, uint32_t maxSize);

/*  cBufWrite
 *  - writes data to circular buffer
 *  - only writes data if there is enough space available in the buffer
 */
cBufStatus_t cBufWrite (cBuf_t* buf, uint8_t* dataIn, uint16_t lenIn);

/*  cBufRead
 *  - writes data from buffer to data array
 *  - dynamically allocates output memory, use cBufFreeData to free memory
 */
cBufStatus_t cBufRead (cBuf_t* buf, uint8_t* dataOut, uint16_t lenOut);

/*  cBufFree
 *  - free data buffer memory
 */
void cBufFree (cBuf_t* buf);

#endif /* __CIRCULAR_BUFFER_H */
