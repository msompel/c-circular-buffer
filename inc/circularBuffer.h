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
  uint8_t* buf;
  uint32_t len;
} cirData_t;

typedef struct
{
  uint32_t head;
  uint32_t tail;
  uint32_t que;
  uint8_t  lock;
  cirData_t* data;
} cirBuf_t;


/* ************************** */
/* **** public functions **** */

void cirBufInit (cirBuf_t* buf);


/* *********************** */
/* ** defined variables ** */



#endif /* __CIRCULAR_BUFFER_H */