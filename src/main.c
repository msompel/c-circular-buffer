#include "circularBuffer.h"
#include <stdio.h>

#define BUF_SIZE   10
#define WRITE_SIZE 5
#define READ_SIZE  6

#define TEST_LOOP 3

/* cBuf_t manages the circular buffer */
cBuf_t cBuf;

/* this is the array that will hold the buffer data, cBufInit sets up a pointer to this array inside cBuf_t */
uint8_t cData[BUF_SIZE];

/* data is returned to a fixed size variable */
uint8_t readData[READ_SIZE];

/* status of buffer */
cBufStatus_t status;


/*** Test variables ***/
static size_t i = 0;
char* testDataLoop[TEST_LOOP] = {
  "Data1",
  "Data2",
  "Data3"
};

/*** declarations ***/
void showBuffer (cBuf_t* buf, char* label);
void showStatus (cBufStatus_t status);


/*** main ***/
int main (void) {
  
  cBufInit(&cBuf, (uint8_t*)&cData, BUF_SIZE);

  /*  write to buffer
   *
   *  loops through the test data
   *  Our circular buffer is 10 bytes while our test data contains 3 blocks of 5 bytes (total of 15 bytes)
   *  This means we will fill our buffer up after two cycles, the third will return a full flag
   */
  for(i=0; i<TEST_LOOP; i++)
  {
    status = cBufWrite(&cBuf, (uint8_t*)testDataLoop[i], WRITE_SIZE);
    if (status == CBUF_OK)
    {
      showBuffer(&cBuf, "Write");
    }
    else
    {
     showStatus(status);
    }
  }

  /*  Read from buffer
   * 
   *  Using a loop, data is read from our buffer until a buffer empty flag is sent
   *  Our buffer is 10 bytes, but our read buffer is 6
   *  Because our buffer only holds a total of 10 bytes, we will see two outputs. One 6 and the next 4.
   *  When the buffer is empty, a flag will be returned
   */
  while(1)
  {
    status = cBufRead(&cBuf, (uint8_t*)&readData, READ_SIZE);
    if(status != CBUF_EMPTY)
    {
      showBuffer(&cBuf, "Read");
      printf("  OUTPUT: %s\r\n", readData);
    }
    else
    {
      showStatus(status);
      break;
    }
  }
  return 0;
}

void showBuffer (cBuf_t* buf, char* label)
{
  printf("%s [ Head: %02d Tail: %02d Size: %02d Buffer: \"%s\" ]\r\n", label, buf->head, buf->tail, buf->curSize, buf->data);
}

void showStatus (cBufStatus_t status)
{
  static char* statusTxt;
  switch (status)
  {
    case CBUF_OK:
      statusTxt = "Okay";
      break;
    case CBUF_EMPTY:
      statusTxt = "Empty";
      break;
    case CBUF_OVERFLOW:
      statusTxt = "Overflow";
      break;
  }
  printf("%s\r\n", statusTxt);
}
