#include "unit_tests.h"
#include "circular_buffer.h"
#include "ansi_colors.h"
#include <stdint.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>


#define BUF_SIZE  32
#define THREAD_BUF_SIZE 5
#define THREAD_DATA_SIZE 75

cbuf_status_t status;
uint8_t output_buffer[128];

// thread setup
cbuf_handle_t *cbuf_thread;
uint8_t thread_data_in[THREAD_DATA_SIZE] = "Integrity check for threads, more data than buffer space.";
uint8_t thread_data_out[THREAD_DATA_SIZE];

void *input_thread (void *arg);
void *output_thread (void *arg);


int main (void) 
{
    cbuf_handle_t *cbuf = cbuf_init(BUF_SIZE);
    cbuf_thread = cbuf_init(THREAD_BUF_SIZE);

    /* **************** */
    /* ** Write Data ** */

    utest_group("Write to Buffer");

    // input greater than buffer
    status = cbuf_put(cbuf, (uint8_t*)"{ This data exceeds the buffer max size }", 41);
    utest_int_equal("Input greater than buffer should return CBUF_FULL", status, CBUF_FULL);

    // valid input
    status = cbuf_put(cbuf, (uint8_t*)"{{ First Input DATA }}", 22);
    utest_int_equal("Should return CBUF_OK when valid", status, CBUF_OK);
    utest_int_equal("Buffer size should equal size of input", cbuf_size(cbuf), 22);

    // valid input to fill buffer to max
    status = cbuf_put(cbuf, (uint8_t*)"{ Second }", 10);
    utest_int_equal("Buffer size should increase when writing", cbuf_size(cbuf), BUF_SIZE);

    // verify buffer full flag when inserting one more byte
    status = cbuf_put(cbuf, (uint8_t*)"OVER", 4);
    utest_int_equal("Writing to a full buffer should return CBUF_FULL", status, CBUF_FULL);

    /* *************** */
    /* ** Read Data ** */

    utest_group("Read from Buffer");

    // valid read output
    status = cbuf_get(cbuf, output_buffer, 22);
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

    status = cbuf_put(cbuf, (uint8_t*)"{ Wrap Input DATA. }", 20);
    utest_int_equal("Should return CBUF_OK when valid", status, CBUF_OK);
    utest_int_equal("Buffer size should equal size of input", cbuf_size(cbuf), 30);

    cbuf_get(cbuf, output_buffer, 30);
    utest_str_equal("Output string produces expected result", (char*)output_buffer, "{ Second }{ Wrap Input DATA. }");

    /*  Null Terminating string output 
     *  
     *  Because the buffer is usually going to be a fixed size,
     *  a null terminator needs to be sent when data is being read.
     *  This is especially important when the requested data length 
     *  is greater than the amount of data in the buffer.
     * 
     *  Buffer Size: 0
     *  Space Available: 32 (Buffer Max - Buffer Size)
    */

    utest_group("Verify output string null terminators");

    // input equal to buffer fills entire buffer
    cbuf_put(cbuf, (uint8_t*)"{ This data equals buffer size }", 32);
    cbuf_get(cbuf, output_buffer, 32);

    utest_str_equal("Filling buffer should not drop any data", (char*)output_buffer, "{ This data equals buffer size }");

    // input
    cbuf_put(cbuf, (uint8_t*)"{ Buffer Data }", 15);
    utest_int_equal("Buffer contains 15 bytes of data", cbuf_size(cbuf), 15);
    cbuf_get(cbuf, output_buffer, 25);

    utest_str_equal("Read length greater than the buffer should be null terminated", (char*)output_buffer, "{ Buffer Data }");

    /* ******************************* */
    /* ** Threads - Common Use Case ** */

    /*  This tests the ability of the buffer to sync data between
     *  threads, ensuring data can remain intact. The circular 
     *  buffer is limited so the inbound data will overflow. It is
     *  up to the consumer how to handle full buffers.
    */

    utest_group("Thread Test");

    pthread_t in_id;
    pthread_t out_id;

    pthread_create(&in_id, NULL, &input_thread, NULL);
    pthread_create(&out_id, NULL, &output_thread, NULL);

    pthread_join(in_id, NULL);
    pthread_join(out_id, NULL);

    utest_str_equal("Data syncs through threads", (char*)thread_data_out, (char*)thread_data_in);

    cbuf_free(&cbuf_thread);

    /* ************************* */
    /* ** data reset and free ** */

    utest_group("cbuf_reset()");

    cbuf_reset(cbuf);

    utest_int_equal("Buffer cur_size should be 0", cbuf_size(cbuf), 0);
    // NOTE: head and tail idx values are being accessed for testing 
    //       purposes and are not part of normal operation
    utest_int_equal("Buffer head should be 0", cbuf->head_idx, 0);
    utest_int_equal("Buffer tail should be 0", cbuf->tail_idx, 0);

    utest_group("cbuf_free()");

    cbuf_free(&cbuf);

    utest_ptr_null("Buffer handle is null", cbuf);

    return 0;
}

void *input_thread (void *arg)
{
    // FIXME: If I drop size_in below 4 the buffer locks up.
    //        I have not had an issue on running this on devices,
    //        probably because they are slower. My initial thought
    //        is that there is a race condition.
    static size_t size_in = 5;
    
    static size_t i = 0;
    static cbuf_status_t status;

    while (i < THREAD_DATA_SIZE)
    {
        status = cbuf_put(cbuf_thread, &thread_data_in[i], size_in);
        if (status == CBUF_OK)
        {
            i += size_in;
        }
    }
    pthread_exit(NULL);
}

void *output_thread (void *arg)
{
    static size_t i = 0;
    static cbuf_status_t status;

    while (i < THREAD_DATA_SIZE)
    {
        status = cbuf_get(cbuf_thread, &thread_data_out[i], 1);
        if (status == CBUF_OK)
        {
            i++;
        }
    }
    pthread_exit(NULL);
}
