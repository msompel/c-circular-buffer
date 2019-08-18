
/* 
 *  Basic Unit Tests
 *
 *  @author John E Maddox
 *
 *************************************************/
 
#ifndef __UNIT_TESTS_H
#define __UNIT_TESTS_H

typedef enum 
{
  eAssertFalse,
  eAssertTrue,
  endOfAssertState
} assertState_t;


/*  assertGroup
 *  - prints group name
 *  - resets test counter
 */
void assertGroup (char* _group);

/* ************************** */
/* ***** string asserts ***** */

/*  assertStrEqual
 *  - compares input and expect strings for equality
 *  - uses strcmp
 */
assertState_t assertStrEqual (char* _describe, char* _input, char* _expect);

/*  assertStrEqual
 *  - compares input and expect strings for inequality
 *  - uses strcmp
 */
assertState_t assertStrNotEqual (char* _describe, char* _input, char* _expect);


/* *************************** */
/* ***** integer asserts ***** */

/*  assertIntEqual
 *  - compares input and expect integers for equality
 */
assertState_t assertIntEqual (char* _describe, int _input, int _expect);

/*  assertIntNotEqual
 *  - compares input and expect integers for inequality
 */
assertState_t assertIntNotEqual (char* _describe, int _input, int _expect);

/*  assertIntGreaterThan
 *  - asserts true if input is greater than expect
 */
assertState_t assertIntGreaterThan (char* _describe, int _input, int _expect);

/*  assertIntLessThan
 *  - asserts true if input is less than expect
 */
assertState_t assertIntLessThan (char* _describe, int _input, int _expect);


/* *************************** */
/* ****** array asserts ****** */

/*  assertIntArrayElements
 *  - compares each array element for equality up to length
 *  - does not compare array length or size
 */
assertState_t assertIntArrayElements (char* _describe, int* _input, int* _expect, int _length);


/* **************************** */
/* *** null pointer asserts *** */

/*  assertPtrNull
 *  - asserts true if input is NULL
 */
assertState_t assertPtrNull (char* _describe, void* _input);

/*  assertPtrNotNull
 *  - asserts true if input is NOT NULL
 */
assertState_t assertPtrNotNull (char* _describe, void* _input);


#endif /* __UNIT_TESTS_H */
