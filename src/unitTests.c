#include "unitTests.h"
#include "ansiColors.h"
#include <stdio.h>
#include <string.h>


static int _testCount = 1;


/* ****************************** */
/* **** private declarations **** */

void _printResults (char* describe, assertState_t state);
void _printStrError (char* input, char* expect, assertState_t state);
void _printIntError (int input, int expect, assertState_t state);
void _printCharError (uint8_t input, uint8_t expect, assertState_t state);

/* ************************** */
/* **** public functions **** */

void assertGroup (char* group)
{
  _testCount = 1;
  printf(ANSI_MAGENTA "%s\n" ANSI_RESET, group);
}

/* ************************** */
/* ***** string asserts ***** */

assertState_t assertStrEqual (char* describe, char* input, char* expect)
{
  assertState_t state = strcmp(input, expect) == 0;

  _printResults(describe, state);

  _printStrError(input, expect, state);

  return state;
}

assertState_t assertStrNotEqual (char* describe, char* input, char* expect)
{
  assertState_t state = strcmp(input, expect) != 0;

  _printResults(describe, state);

  _printStrError(input, expect, state);

  return state;
}


/* *************************** */
/* ***** integer asserts ***** */

assertState_t assertIntEqual (char* describe, int input, int expect)
{
  assertState_t state = (input == expect);

  _printResults(describe, state);

  _printIntError(input, expect, state);

  return state;
}

assertState_t assertIntNotEqual (char* describe, int input, int expect)
{
  assertState_t state = (input != expect);

  _printResults(describe, state);

  _printIntError(input, expect, state);

  return state;
}

assertState_t assertIntGreaterThan (char* describe, int input, int expect)
{
  assertState_t state = (input > expect);

  _printResults(describe, state);

  _printIntError(input, expect, state);

  return state;
}

assertState_t assertIntLessThan (char* describe, int input, int expect)
{
  assertState_t state = (input < expect);

  _printResults(describe, state);

  _printIntError(input, expect, state);

  return state;
}

assertState_t assertArrayElements (char* describe, uint8_t* input, uint8_t* expect, uint16_t length)
{
  /* compare each element */
  for (int i=0; i<length; i++) {
    if (input[i] != expect[i]) {
      _printResults(describe, ASSERT_FALSE);
      _printCharError((uint8_t)input[i], (uint8_t)expect[i], ASSERT_FALSE);
      return ASSERT_FALSE;
    }
  }

  _printResults(describe, ASSERT_TRUE);
  return ASSERT_TRUE;
}


/* **************************** */
/* *** null pointer asserts *** */

assertState_t assertPtrNull (char* describe, void* input)
{
  assertState_t state = (input == NULL);

  _printResults(describe, state);

  return state;
}

assertState_t assertPtrNotNull (char* describe, void* input)
{
  assertState_t state = (input != NULL);

  _printResults(describe, state);

  return state;
}


/* ***************************** */
/* ***** private functions ***** */

void _printResults (char* describe, assertState_t state)
{
  char* results =  (state == ASSERT_TRUE) ? ANSI_GREEN "Passed!" : ANSI_RED "Failed :(";
  printf(ANSI_CYAN "  %d) %s: %s" ANSI_RESET "\n", _testCount, describe, results);
  _testCount++;
}

void _printStrError (char* input, char* expect, assertState_t state)
{
  if (state == ASSERT_FALSE)
  {
    printf(ANSI_YELLOW "      INPUT: \"%s\"\n     EXPECT: \"%s\"\n" ANSI_RESET, input, expect);
  }
}

void _printIntError (int input, int expect, assertState_t state)
{
if (state == ASSERT_FALSE)
  {
    printf(ANSI_YELLOW "      INPUT: \"%d\"\n     EXPECT: \"%d\"\n" ANSI_RESET, input, expect);
  }
}

void _printCharError (uint8_t input, uint8_t expect, assertState_t state)
{
if (state == ASSERT_FALSE)
  {
    printf(ANSI_YELLOW "      INPUT: \"%c\"\n     EXPECT: \"%c\"\n" ANSI_RESET, input, expect);
  }
}
