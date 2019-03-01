#include "circularBuffer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE   32
#define RTN_SIZE   15
#define TEST_WRITE 5
#define TEST_LOOP  20

/* cBuf_t manages the circular buffer */
cBuf_t cBuf;

/*** Test variables ***/
char* testData[TEST_WRITE] = {
  "{ 01 Data }",
  "{ 02 Data Test }",
  "{ 03 Data Data Data }",
  "{ 04 End with zero } -> 0",
  "{ 05 This is data. }"
};

uint16_t testDataPos = 0;
uint8_t  testDataOut[128];


/*** declarations ***/
void showBuffer (cBuf_t* buf, char* label);


/*** main ***/
int main (void) {
  
  cBufInit(&cBuf, BUF_SIZE);

  cData_t input, output;

  /*  loops through test data */
  uint16_t i, j = 0;
  for(i=0; i<TEST_LOOP; i++)
  {
    /* write to buffer */
    if(j < TEST_WRITE)
    {
      input.data = (uint8_t*)testData[j];
      input.len = strlen(testData[j]);

      if(cBufWrite(&cBuf, &input) != CBUF_FULL)
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
    if(cBufRead(&cBuf, &output, RTN_SIZE) == CBUF_OK)
    {
      showBuffer(&cBuf, "R");
      memcpy(&testDataOut[testDataPos], &output.data[0], output.len);
      testDataPos = testDataPos + output.len;
      cBufFreeData (&output);
    }

  }

  /* free memory */
  cBufFree(&cBuf);
  showBuffer(&cBuf, "F");

  /* print results */
  printf("\r\nOUTPUT:\r\n\"%.*s\"\r\n", testDataPos, testDataOut);

  return 0;
}

void showBuffer (cBuf_t* buf, char* label)
{
  printf("  %s [ Head: %02d Tail: %02d Size: %02d ]\r\n", label, buf->head, buf->tail, buf->curSize);
}
