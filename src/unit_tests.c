#include "unit_tests.h"
#include "ansi_colors.h"
#include <stdio.h>
#include <string.h>


static size_t test_count = 1;

static void print_results (char* describe, bool state);
static void print_str_error (char* input, char* expect, bool state);
static void print_int_error (int input, int expect, bool state);


void utest_group (char* group)
{
    test_count = 1;
    printf(ANSI_MAGENTA "%s\n" ANSI_RESET, group);
}

/* ************************** */
/* ***** string asserts ***** */

bool utest_str_equal (char* describe, char* input, char* expect)
{
    bool state = strcmp(input, expect) == 0;

    print_results(describe, state);
    print_str_error(input, expect, state);

    return state;
}

bool utest_str_not_equal (char* describe, char* input, char* expect)
{
    bool state = strcmp(input, expect) != 0;

    print_results(describe, state);
    print_str_error(input, expect, state);

    return state;
}

/* *************************** */
/* ***** integer asserts ***** */

bool utest_int_equal (char* describe, int input, int expect)
{
    bool state = (input == expect);

    print_results(describe, state);
    print_int_error(input, expect, state);

    return state;
}

bool utest_int_not_equal (char* describe, int input, int expect)
{
    bool state = (input != expect);

    print_results(describe, state);
    print_int_error(input, expect, state);

    return state;
}

bool utest_int_greater (char* describe, int input, int expect)
{
    bool state = (input > expect);

    print_results(describe, state);
    print_int_error(input, expect, state);

    return state;
}

bool utest_int_less (char* describe, int input, int expect)
{
    bool state = (input < expect);

    print_results(describe, state);
    print_int_error(input, expect, state);

    return state;
}

bool utest_int_array_equal (char* describe, int* input, int* expect, size_t length)
{
    int errors[length][3];
    size_t error_count = 0;
    size_t i;
  
    // compare array elements
    for (i=0; i<length; i++)
    {
        if (input[i] != expect[i])
        {
            errors[error_count][0] = i;
            errors[error_count][1] = input[i];
            errors[error_count][2] = expect[i];
            error_count++;
        }
    }

    if (error_count)
    {
        print_results(describe, false);
        for(i=0; i<error_count; i++)
        {
            printf("\t[%d]\n", errors[i][0]);
            print_int_error(errors[i][1], errors[i][2], false);
        }
        return false;
    }

    print_results(describe, true);
    return true;
}

/* **************************** */
/* *** null pointer asserts *** */

bool utest_ptr_null (char* describe, void* input)
{
    bool state = (input == NULL);

    print_results(describe, state);

    return state;
}

bool utest_ptr_not_null (char* describe, void* input)
{
    bool state = (input != NULL);

    print_results(describe, state);

    return state;
}

/* *************************** */
/* **** private functions **** */

static void print_results (char* describe, bool state)
{
    char* results =  (state) ? ANSI_GREEN "Passed!" : ANSI_RED "Failed :(";
    printf(ANSI_CYAN "  %zu) %s: %s" ANSI_RESET "\n", test_count, describe, results);
    test_count++;
}

static void print_str_error (char* input, char* expect, bool state)
{
    if (!state)
    {
        printf(ANSI_YELLOW "\tINPUT:  \"%s\"\n\tEXPECT: \"%s\"\n" ANSI_RESET, input, expect);
    }
}

static void print_int_error (int input, int expect, bool state)
{
    if (!state)
    {
        printf(ANSI_YELLOW "\tINPUT:  \"%d\"\n\tEXPECT: \"%d\"\n" ANSI_RESET, input, expect);
    }
}
