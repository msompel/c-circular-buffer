#include "ansiColors.h"
#include "unitTests.h"
#include "circularBuffer.h"

#define BUF_SIZE  32

/* cBuf_t manages the circular buffer */
cBufStatus_t status;

uint8_t outputBuffer[128];

int main (void) 
{
  ansiInit();
  
  cBufHandle_t *cBuf = cBufInit(BUF_SIZE);

  /* ******************* */
  /* **** cBufWrite **** */

  assertGroup("cBufWrite()");

  /* input greater than buffer */
  status = cBufWrite(cBuf, (uint8_t*)"{ This data exceeds the buffer max size }", 41);
  assertIntEqual("Input greater than buffer should return eCBufFull", status, eCBufFull);

  /* valid input */
  status = cBufWrite(cBuf, (uint8_t*)"{ First Input DATA }", 20);
  assertIntEqual("Should return eCBufOk when valid", status, eCBufOk);
  assertIntEqual("Buffer size should equal size of input", cBuf->curSize, 20);

  /* valid input to fill buffer to max */
  status = cBufWrite(cBuf, (uint8_t*)"{ Second }", 10);
  assertIntEqual("Buffer size should increase when writing", cBuf->curSize, 30);

  /* verify buffer full flag when inserting one more byte */
  status = cBufWrite(cBuf, (uint8_t*)"OVER", 4);
  assertIntEqual("Writing to a full buffer should return eCBufFull", status, eCBufFull);


  /* ******************* */
  /* **** cBufRead **** */

  assertGroup("cBufRead()");

  /* valid read output */
  status = cBufRead(cBuf, outputBuffer, 20);
  assertIntEqual("Should return eCBufOk when valid", status, eCBufOk);
  assertIntEqual("Buffer size should decrease when reading", cBuf->curSize, 10);
  assertStrEqual("Output string produces expected result", (char*)outputBuffer, "{ First Input DATA }");
  

  /* *************************** */
  /* ** Data Integrity Checks ** */

  /*  End of buffer jumps to index 0 when there is free space
   *  
   *  When we write data that exceeds the available space at the end of the buffer, 
   *  and there is enough space at the begining of the buffer to hold the remaining data,
   *  the data should be written to the buffer in two chucks, one at the end and one at the beginning.
   * 
   *      Buffer Size: 10
   *  Space Available: 22 (Buffer Max - Buffer Size)
   */

  assertGroup("Verify Data Wrapping");

  status = cBufWrite(cBuf, (uint8_t*)"{ Wrap Input DATA. }", 20);
  assertIntEqual("Should return eCBufOk when valid", status, eCBufOk);
  assertIntEqual("Buffer size should equal size of input", cBuf->curSize, 30);

  cBufRead(cBuf, outputBuffer, 30);
  assertStrEqual("Output string produces expected result", (char*)outputBuffer, "{ Second }{ Wrap Input DATA. }");

  /*  Null Terminating string output 
   *  
   *  Because the buffer is usually going to be a fixed size,
   *  a null terminator needs to be sent when data is being read.
   *  This is expecially important when the requested data length is greater than the amount of data in the buffer.
   * 
   *      Buffer Size: 0
   *  Space Available: 32 (Buffer Max - Buffer Size)
   */

  assertGroup("Verify output string null terminators");

  /* input equal to buffer fills entire buffer */
  cBufWrite(cBuf, (uint8_t*)"{ This data equals buffer size }", 32);
  cBufRead(cBuf, outputBuffer, 32);

  assertStrEqual("Filling buffer should not drop any data", (char*)outputBuffer, "{ This data equals buffer size }");

  /* input */
  cBufWrite(cBuf, (uint8_t*)"{ Buffer Data }", 15);
  assertIntEqual("Buffer contains 15 bytes of data", cBuf->curSize, 15);
  cBufRead(cBuf, outputBuffer, 25);

  assertStrEqual("Read length greater than the buffer should be null terminated", (char*)outputBuffer, "{ Buffer Data }");
 

  /* ************************* */
  /* ** data reset and free ** */

  assertGroup("cBufReset()");

  cBufReset(cBuf);

  assertIntEqual("Buffer curSize should be 0", cBuf->curSize, 0);
  assertIntEqual("Buffer head should be 0", cBuf->head, 0);
  assertIntEqual("Buffer tail should be 0", cBuf->tail, 0);

  assertGroup("cBufFree()");

  cBufFree(&cBuf);

  assertPtrNull("Buffer handle is free", cBuf);

  return 0;
}
