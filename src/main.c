#include "unit_tests.h"
#include "circular_buffer.h"
#include <stdint.h>

#define BUF_SIZE  32

cbuf_status_t status;

uint8_t output_buffer[128];

int main (void) 
{
    cbuf_handle_t *cbuf = cbuf_init(BUF_SIZE);

    /* **************** */
    /* ** Write Data ** */

    utest_group("Write to Buffer");

    // input greater than buffer
    status = cbuf_write(cbuf, (uint8_t*)"{ This data exceeds the buffer max size }", 41);
    utest_int_equal("Input greater than buffer should return CBUF_FULL", status, CBUF_FULL);

    // valid input
    status = cbuf_write(cbuf, (uint8_t*)"{{ First Input DATA }}", 22);
    utest_int_equal("Should return CBUF_OK when valid", status, CBUF_OK);
    utest_int_equal("Buffer size should equal size of input", cbuf_size(cbuf), 22);

    // valid input to fill buffer to max
    status = cbuf_write(cbuf, (uint8_t*)"{ Second }", 10);
    utest_int_equal("Buffer size should increase when writing", cbuf_size(cbuf), BUF_SIZE);

    // verify buffer full flag when inserting one more byte
    status = cbuf_write(cbuf, (uint8_t*)"OVER", 4);
    utest_int_equal("Writing to a full buffer should return CBUF_FULL", status, CBUF_FULL);

    /* *************** */
    /* ** Read Data ** */

    utest_group("Read from Buffer");

    // valid read output
    status = cbuf_read(cbuf, output_buffer, 22);
    utest_int_equal("Should return CBUF_OK when valid", status, CBUF_OK);
    utest_int_equal("Buffer size should decrease when reading", cbuf_size(cbuf), 10);
    utest_str_equal("Output string produces expected result", (char*)output_buffer, "{{ First Input DATA }}");
    

    /* *************************** */
    /* ** Data Integrity Checks ** */

    /*  End of buffer jumps to index 0 when there is free space
    *  
    *  When we write data that exceeds the available space at the end of the buffer, 
    *  and there is enough space at the begining of the buffer to hold the remaining data,
    *  the data should be written to the buffer in two chucks, one at the end and one at the beginning.
    * 
    *  Buffer Size: 10
    *  Space Available: 22 (Buffer Max - Buffer Size)
    */

    utest_group("Verify Data Wrapping");

    status = cbuf_write(cbuf, (uint8_t*)"{ Wrap Input DATA. }", 20);
    utest_int_equal("Should return CBUF_OK when valid", status, CBUF_OK);
    utest_int_equal("Buffer size should equal size of input", cbuf_size(cbuf), 30);

    cbuf_read(cbuf, output_buffer, 30);
    utest_str_equal("Output string produces expected result", (char*)output_buffer, "{ Second }{ Wrap Input DATA. }");

    /*  Null Terminating string output 
    *  
    *  Because the buffer is usually going to be a fixed size,
    *  a null terminator needs to be sent when data is being read.
    *  This is especially important when the requested data length is greater than the amount of data in the buffer.
    * 
    *  Buffer Size: 0
    *  Space Available: 32 (Buffer Max - Buffer Size)
    */

    utest_group("Verify output string null terminators");

    // input equal to buffer fills entire buffer
    cbuf_write(cbuf, (uint8_t*)"{ This data equals buffer size }", 32);
    cbuf_read(cbuf, output_buffer, 32);

    utest_str_equal("Filling buffer should not drop any data", (char*)output_buffer, "{ This data equals buffer size }");

    // input
    cbuf_write(cbuf, (uint8_t*)"{ Buffer Data }", 15);
    utest_int_equal("Buffer contains 15 bytes of data", cbuf_size(cbuf), 15);
    cbuf_read(cbuf, output_buffer, 25);

    utest_str_equal("Read length greater than the buffer should be null terminated", (char*)output_buffer, "{ Buffer Data }");
  

    /* ************************* */
    /* ** data reset and free ** */

    utest_group("cbuf_reset()");

    cbuf_reset(cbuf);

    utest_int_equal("Buffer cur_size should be 0", cbuf_size(cbuf), 0);
    // NOTE: these values are being accessed for testing purposes and are not part of normal operation
    utest_int_equal("Buffer head should be 0", cbuf->head_idx, 0);
    utest_int_equal("Buffer tail should be 0", cbuf->tail_idx, 0);

    utest_group("cbuf_free()");

    cbuf_free(&cbuf);

    utest_ptr_null("Buffer handle is free", cbuf);

    return 0;
}
