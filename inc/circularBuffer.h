/* 
 *	Circular Buffer
 *
 *  @author John E Maddox
 *
 *************************************************/
 
#ifndef __CIRCULAR_BUFFER_H
#define __CIRCULAR_BUFFER_H

#include <stdint.h>


typedef struct
{
  uint8_t* data;
  uint32_t len;
} cData_t;

typedef struct
{
  uint32_t head;
  uint32_t tail;
  uint32_t curSize;
  uint32_t maxSize;
  uint8_t  lock;
  cData_t* buf;
} cBuf_t;


/* ************************** */
/* **** public functions **** */

void cBufInit (cBuf_t* buf, uint32_t bufLen, uint32_t dataLen);

void cBufWrite (cBuf_t* buf);

void cBufRead (cBuf_t* buf);

void cBufReset (cBuf_t* buf);


/* *********************** */
/* ** defined variables ** */



#endif /* __CIRCULAR_BUFFER_H */