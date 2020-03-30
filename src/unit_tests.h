/* 
 *  Unit Tests
 * 
 *  Basic unit testing focusing on integers, c strings, and 
 *  pointers.
 *
 *  @author John E Maddox
 *
***************************************************************/
 
#ifndef UNIT_TESTS_H
#define UNIT_TESTS_H

#include <stdbool.h>
#include <stddef.h>

// - prints group name
// - resets test counter
void utest_group (char* group);

/* ************************** */
/* ***** string asserts ***** */

// - compares input and expect strings for equality
// - uses strcmp for comparison
// - returns true if equal
bool utest_str_equal (char* describe, char* input, char* expect);

// - compares input and expect strings for inequality
// - uses strcmp for comparison
// - returns true if not equal
bool utest_str_not_equal (char* describe, char* input, char* expect);

/* *************************** */
/* ***** integer asserts ***** */

// - compares input and expect integers for equality
// - returns true if equal
bool utest_int_equal (char* describe, int input, int expect);

// - compares input and expect integers for inequality
// - returns true if not equal
bool utest_int_not_equal (char* describe, int input, int expect);

// - check for an input value greater than expect
// - returns true if input is greater than expect
bool utest_int_greater (char* describe, int input, int expect);

// - check for an input value less than expect
// - returns true if input is less than expect
bool utest_int_less (char* describe, int input, int expect);

/* *************************** */
/* ****** array asserts ****** */

// - compares each array element for equality up to length
// - does not compare array length or size
// - returns true if elements are equal
bool utest_int_array_equal (char* describe, int* input, int* expect, size_t length);

/* **************************** */
/* *** null pointer asserts *** */

// - tests for NULL pointer input
// - this is useful for tear down checks
// - returns true if input is NULL
bool utest_ptr_null (char* describe, void* input);

// - tests for NOT NULL pointer input
// - useful for checking generic assignments
// - returns true if input is NOT NULL
bool utest_ptr_not_null (char* describe, void* input);

#endif // UNIT_TESTS_H
