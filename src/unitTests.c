#include "unitTests.h"
#include "ansiColors.h"
#include <stdio.h>
#include <string.h>


static int testCount = 1;


/* ****************************** */
/* **** private declarations **** */

void printResults (char* _describe, assertState_t _state);
void printStrError (char* _input, char* _expect, assertState_t _state);
void printIntError (int _input, int _expect, assertState_t _state);


/* ************************** */
/* **** public functions **** */

void assertGroup (char* _group)
{
  testCount = 1;
  printf(ANSI_MAGENTA "%s\n" ANSI_RESET, _group);
}

/* ************************** */
/* ***** string asserts ***** */

assertState_t assertStrEqual (char* _describe, char* _input, char* _expect)
{
  assertState_t state = strcmp(_input, _expect) == 0;

  printResults(_describe, state);

  printStrError(_input, _expect, state);

  return state;
}

assertState_t assertStrNotEqual (char* _describe, char* _input, char* _expect)
{
  assertState_t state = strcmp(_input, _expect) != 0;

  printResults(_describe, state);

  printStrError(_input, _expect, state);

  return state;
}


/* *************************** */
/* ***** integer asserts ***** */

assertState_t assertIntEqual (char* _describe, int _input, int _expect)
{
  assertState_t state = (_input == _expect);

  printResults(_describe, state);

  printIntError(_input, _expect, state);

  return state;
}

assertState_t assertIntNotEqual (char* _describe, int _input, int _expect)
{
  assertState_t state = (_input != _expect);

  printResults(_describe, state);

  printIntError(_input, _expect, state);

  return state;
}

assertState_t assertIntGreaterThan (char* _describe, int _input, int _expect)
{
  assertState_t state = (_input > _expect);

  printResults(_describe, state);

  printIntError(_input, _expect, state);

  return state;
}

assertState_t assertIntLessThan (char* _describe, int _input, int _expect)
{
  assertState_t state = (_input < _expect);

  printResults(_describe, state);

  printIntError(_input, _expect, state);

  return state;
}

assertState_t assertIntArrayElements (char* _describe, int* _input, int* _expect, int _length)
{
  int errors[_length][3];
  int errorCount = 0;
  int i;
  
  /* compare each element */
  for (i=0; i<_length; i++)
  {
    if (_input[i] != _expect[i])
    {
      errors[errorCount][0] = i;
      errors[errorCount][1] = _input[i];
      errors[errorCount][2] = _expect[i];
      errorCount++;
    }
  }

  if (errorCount)
  {
    printResults(_describe, eAssertFalse);
    for(i=0; i<errorCount; i++)
    {
      printf(ANSI_RED "     [%d]\n" ANSI_RESET, errors[i][0]);
      printIntError(errors[i][1], errors[i][2], eAssertFalse);
    }
    return eAssertFalse;
  }

  printResults(_describe, eAssertTrue);
  return eAssertTrue;
}


/* **************************** */
/* *** null pointer asserts *** */

assertState_t assertPtrNull (char* _describe, void* _input)
{
  assertState_t state = (_input == NULL);

  printResults(_describe, state);

  return state;
}

assertState_t assertPtrNotNull (char* _describe, void* _input)
{
  assertState_t state = (_input != NULL);

  printResults(_describe, state);

  return state;
}


/* ***************************** */
/* ***** private functions ***** */

void printResults (char* _describe, assertState_t _state)
{
  char* results =  (_state == eAssertTrue) ? ANSI_GREEN "Passed!" : ANSI_RED "Failed :(";
  printf(ANSI_CYAN "  %d) %s: %s" ANSI_RESET "\n", testCount, _describe, results);
  testCount++;
}

void printStrError (char* _input, char* _expect, assertState_t _state)
{
  if (_state == eAssertFalse)
  {
    printf(ANSI_YELLOW "      INPUT:  \"%s\"\n      EXPECT: \"%s\"\n" ANSI_RESET, _input, _expect);
  }
}

void printIntError (int _input, int _expect, assertState_t _state)
{
if (_state == eAssertFalse)
  {
    printf(ANSI_YELLOW "      INPUT:  \"%d\"\n      EXPECT: \"%d\"\n" ANSI_RESET, _input, _expect);
  }
}
