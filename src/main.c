#include "circularBuffer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE   2
#define TEST_WRITE 5
#define TEST_LOOP  10

/* cBuf_t manages the circular buffer */
cBuf_t cBuf;
cData_t cDataBuf[BUF_SIZE];


/*** Test variables ***/
char* testData[TEST_WRITE] = {
  "01 Data Test",
  "02 Data",
  "03 Hello, I'm data 0",
  "04 More data",
  "05 guess what? Data!!!"
};


/*** declarations ***/
void showBuffer (cBuf_t* buf, char* label);


/*** main ***/
int main (void) {
  
  cBufInit(&cBuf, (cData_t*)&cDataBuf, BUF_SIZE);

  /*  loops through test data */
  uint16_t i, j = 0;
  for(i=0; i<TEST_LOOP; i++)
  {
    /* write to buffer */
    if(j < TEST_WRITE)
    {
      cData_t input = { (uint8_t*)testData[j], strlen(testData[j]) };

      if(cBufWrite(&cBuf, input) != CBUF_FULL)
      {
        showBuffer(&cBuf, "W");
        j++;
      }
      else
      {
        printf("BUFFER FULL\r\n");
      }
    }
    
    /* read from buffer */
    if(i % 2 == 0)
    {
      cData_t output;

      if(cBufRead(&cBuf, &output) == CBUF_OK)
      {
        showBuffer(&cBuf, "R");
        printf("OUTPUT: %s (%d)\r\n", output.data, output.len);
      }
    }
  }
  return 0;
}

void showBuffer (cBuf_t* buf, char* label)
{
  printf("  %s [ Head: %02d Tail: %02d Size: %02d ]\r\n", label, buf->head, buf->tail, buf->curSize);

  uint32_t i = 0;
  for(i=0; i<buf->maxSize;i++)
  {
    if(buf->data[i].len)
    {
      printf("      [%d] %s\r\n", i, buf->data[i].data);
    }
  }
}
