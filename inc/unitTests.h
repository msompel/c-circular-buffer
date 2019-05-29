/* 
 *  Basic Unit Tests
 *
 *  @author John E Maddox
 *
 *************************************************/
 
#ifndef __UNIT_TESTS_H
#define __UNIT_TESTS_H

#include <stdint.h>

typedef enum 
{
  ASSERT_FALSE,
  ASSERT_TRUE
} assertState_t;


/*  assertGroup
 *  - prints group name
 *  - resets test counter
 */
void assertGroup (char* group);

/* ************************** */
/* ***** string asserts ***** */

/*  assertStrEqual
 *  - compares input and expect strings for equality
 *  - uses strcmp
 */
assertState_t assertStrEqual (char* describe, char* input, char* expect);

/*  assertStrEqual
 *  - compares input and expect strings for inequality
 *  - uses strcmp
 */
assertState_t assertStrNotEqual (char* describe, char* input, char* expect);


/* *************************** */
/* ***** integer asserts ***** */

/*  assertIntEqual
 *  - compares input and expect integers for equality
 */
assertState_t assertIntEqual (char* describe, int input, int expect);

/*  assertIntNotEqual
 *  - compares input and expect integers for inequality
 */
assertState_t assertIntNotEqual (char* describe, int input, int expect);

/*  assertIntGreaterThan
 *  - asserts true if input is greater than expect
 */
assertState_t assertIntGreaterThan (char* describe, int input, int expect);

/*  assertIntLessThan
 *  - asserts true if input is less than expect
 */
assertState_t assertIntLessThan (char* describe, int input, int expect);


/* *************************** */
/* ****** array asserts ****** */

/*  assertArrayElements
 *  - compares each array element for equality up to length
 *  - does not compare array length or size
 */
assertState_t assertArrayElements (char* describe, uint8_t* input, uint8_t* expect, uint16_t length);


/* **************************** */
/* *** null pointer asserts *** */

/*  assertPtrNull
 *  - asserts true if input is NULL
 */
assertState_t assertPtrNull (char* describe, void* input);

/*  assertPtrNotNull
 *  - asserts true if input is NOT NULL
 */
assertState_t assertPtrNotNull (char* describe, void* input);


#endif /* __UNIT_TESTS_H */
