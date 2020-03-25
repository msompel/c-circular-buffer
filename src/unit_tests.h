/* 
 *  Unit Tests
 *
 *  @author John E Maddox
 *
 *************************************************/
 
#ifndef UNIT_TESTS_H
#define UNIT_TESTS_H

#include <stdbool.h>

//  utest_group
//  - prints group name
//  - resets test counter
void utest_group (char* group);

/* ************************** */
/* ***** string asserts ***** */

//  utest_str_equal
//  - compares input and expect strings for equality
//  - uses strcmp
bool utest_str_equal (char* describe, char* input, char* expect);

//  utest_str_not_equal
//  - compares input and expect strings for inequality
//  - uses strcmp
bool utest_str_not_equal (char* describe, char* input, char* expect);

/* *************************** */
/* ***** integer asserts ***** */

//  utest_int_equal
//  - compares input and expect integers for equality
bool utest_int_equal (char* describe, int input, int expect);

//  utest_int_not_equal
//  - compares input and expect integers for inequality
bool utest_int_not_equal (char* describe, int input, int expect);

//  utest_int_greater_than
//  - asserts true if input is greater than expect
bool utest_int_greater (char* describe, int input, int expect);

//  utest_int_less_than
//  - asserts true if input is less than expect
bool utest_int_less (char* describe, int input, int expect);

/* *************************** */
/* ****** array asserts ****** */

//  utest_int_array_equal
//  - compares each array element for equality up to length
//  - does not compare array length or size
bool utest_int_array_equal (char* describe, int* input, int* expect, int length);

/* **************************** */
/* *** null pointer asserts *** */

//  utest_ptr_null
//  - asserts true if input is NULL
bool utest_ptr_null (char* describe, void* input);

//  utest_ptr_not_null
//  - asserts true if input is NOT NULL
bool utest_ptr_not_null (char* describe, void* input);

#endif // UNIT_TESTS_H
