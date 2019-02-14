#include "circularBuffer.h"

#define CIR_BUF_LEN 256
#define CIR_DATA_LEN 64

cirBuf_t cBuf[CIR_BUF_LEN];

int main (void) {
  cirBufInit((cirBuf_t*)&cBuf);
  
  return 0;
}
