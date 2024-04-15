#ifndef TEST_H
# define TEST_H

#include <stdio.h>
#include <stdlib.h>

// Define macros to keep track of test counts
#define TEST_COUNT(count) \
    static int totalTests = count; \
    static int passedTests = 0; \
    static int failedTests = 0;

#define GET_TOTAL_TESTS() totalTests
#define GET_PASSED_TESTS() passedTests
#define GET_FAILED_TESTS() failedTests

// Macro to initialize the tester and print a welcome message
#define INIT_TESTER() \
    TEST_COUNT(1); \
    printf("\x1b[34mStarting tests...\n\x1b[0m");

// Macro to summarize the tests
#define SUMMARIZE_TESTS() \
    totalTests = passedTests + failedTests; \
    if(failedTests == 0) \
    { \
      printf("\x1b[32m[  PASSED  ] %d of %d passed\n\x1b[0m", passedTests, totalTests); \
    } \
    else \
    { \
      printf("\x1b[31m[  FAILED  ] %d of %d failed\n\x1b[0m", failedTests, totalTests); \
    } \

#define TEST(function, description, body) \
    do { \
        printf("\x1b[32m[----------] %s.", function); \
        printf("%s\x1b[0m\n", description); \
        (body); \
        printf("\n");                      \
    } while (0)

#define ASSERT_EQ(arg1, arg2) \
    do { \
        if (arg1 == arg2) { \
            printf("\x1b[32m[    OK    ] %d == %d\x1b[0m\n", arg1, arg2); \
            passedTests++;  \
        } else { \
            printf("\x1b[31m[    KO    ] %d == %d\x1b[0m\n", arg1, arg2); \
            failedTests++; \
        } \
    } while (0)

#endif
