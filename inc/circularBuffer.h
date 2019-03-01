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
  CBUF_OK    = 0x00U,
  CBUF_EMPTY = 0x01U,
  CBUF_FULL  = 0x02U
} cBufStatus_t;

typedef struct
{
  uint8_t* data;
  uint16_t len;
} cData_t;

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
cBufStatus_t cBufWrite (cBuf_t* buf, cData_t* data);

/*  cBufRead
 *  - writes data from buffer to data array
 *  - dynamically allocates output memory, use cBufFreeData to free memory
 */
cBufStatus_t cBufRead (cBuf_t* buf, cData_t* data, uint16_t len);

/*  cBufFreeData
 *  - free output memory
 */
void cBufFreeData (cData_t* data);

/*  cBufFree
 *  - free data buffer memory
 */
void cBufFree (cBuf_t* buf);

#endif /* __CIRCULAR_BUFFER_H */
