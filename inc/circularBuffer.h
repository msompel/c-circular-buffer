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
  uint32_t head;
  uint32_t tail;
  uint8_t  lock;
  uint32_t curSize;
  uint32_t maxSize;
  uint8_t* data;
} cBuf_t;


/* ************************** */
/* **** public functions **** */

/*  cBufInit
 *  buf:     the controller for the buffer
 *  data:    uint8_t static array (ex. uint8_t data[1024])
 *  maxSize: this is the size of the data array (ex. 1024)
 * 
 *  - sets default values
 *  - points buf->data to data array
 */ 
void cBufInit (cBuf_t* buf, uint8_t* data, uint32_t maxSize);

/*  cBufWrite
 *  - writes data to circular buffer one byte at a time
 *  - only writes data if there is enough space available in the buffer
 *  - sets lock to prevent reading and writing to same data block
 */
cBufStatus_t cBufWrite (cBuf_t* buf, uint8_t* data, uint32_t len);

/*  cBufRead
 *  - writes data from buffer to data array one byte at a time
 *  - fills empty space in data array with zeros
 *  - locks memory block that is being written to
 */
cBufStatus_t cBufRead (cBuf_t* buf, uint8_t* data, uint32_t len);

#endif /* __CIRCULAR_BUFFER_H */
