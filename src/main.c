#include "circularBuffer.h"

#define CIR_BUF_LEN 256
#define CIR_DATA_LEN 64

cBuf_t cBuf;

int main (void) {
  cBufInit(&cBuf, CIR_BUF_LEN, CIR_DATA_LEN);
  
  return 0;
}
