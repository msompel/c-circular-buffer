#include "circularBuffer.h"
#include <stdint.h>

/* ***************************** */
/* ***** private variables ***** */



/* ****************************** */
/* **** private declarations **** */

static void cirPos (uint32_t* pos);

/* **************************** */
/* ***** public functions ***** */

void cirBufInit (cirBuf_t* buf) {
  printf(buf);
}


/* ***************************** */
/* ***** private functions ***** */

static void cirPos (uint32_t* pos)
{
  *pos = (*pos == COM_BUF_LEN - 1) ? 0 : *pos + 1;
}
