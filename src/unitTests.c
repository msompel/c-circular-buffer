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

assertState_t assertIntArrayElements (char* describe, int* input, int* expect, int length)
{
  int errors[length][3];
  int errorCount = 0;
  int i;
  
  /* compare each element */
  for (i=0; i<length; i++) {
    if (input[i] != expect[i]) {
      errors[errorCount][0] = i;
      errors[errorCount][1] = input[i];
      errors[errorCount][2] = expect[i];
      errorCount++;
    }
  }

  if (errorCount)
  {
    _printResults(describe, eAssertFalse);
    for(i=0; i<errorCount; i++)
    {
      printf(ANSI_RED "     [%d]\n" ANSI_RESET, errors[i][0]);
      _printIntError(errors[i][1], errors[i][2], eAssertFalse);
    }
    return eAssertFalse;
  }

  _printResults(describe, eAssertTrue);
  return eAssertTrue;
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
  char* results =  (state == eAssertTrue) ? ANSI_GREEN "Passed!" : ANSI_RED "Failed :(";
  printf(ANSI_CYAN "  %d) %s: %s" ANSI_RESET "\n", _testCount, describe, results);
  _testCount++;
}

void _printStrError (char* input, char* expect, assertState_t state)
{
  if (state == eAssertFalse)
  {
    printf(ANSI_YELLOW "      INPUT:  \"%s\"\n      EXPECT: \"%s\"\n" ANSI_RESET, input, expect);
  }
}

void _printIntError (int input, int expect, assertState_t state)
{
if (state == eAssertFalse)
  {
    printf(ANSI_YELLOW "      INPUT:  \"%d\"\n      EXPECT: \"%d\"\n" ANSI_RESET, input, expect);
  }
}
