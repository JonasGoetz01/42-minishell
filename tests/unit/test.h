#ifndef TEST_H
# define TEST_H

#include <stdio.h>
#include <stdlib.h>

static int totalTests = 0;
static int passedTests = 0;
static int failedTests = 0;

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
      exit(0); \
    } \
    else \
    { \
      printf("\x1b[31m[  FAILED  ] %d of %d failed\n\x1b[0m", failedTests, totalTests); \
      exit(1); \
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

#define ASSERT_STR_EQ(arg1, arg2) \
    do { \
        if (strcmp(arg1, arg2) == 0) { \
            printf("\x1b[32m[    OK    ] %s == %s\x1b[0m\n", arg1, arg2); \
            passedTests++;  \
        } else { \
            printf("\x1b[31m[    KO    ] %s == %s\x1b[0m\n", arg1, arg2); \
            failedTests++; \
        } \
    } while (0)

#define TOKEN_LENGTH(token) \
    ({ \
        int length = 0; \
        t_token *temp = token; \
        while (temp != NULL) { \
            length++; \
            temp = temp->next; \
        } \
        length; \
    })

#define ASSERT_TOKENS_EQ(arg1, arg2) \
    do { \
        int actual_length = TOKEN_LENGTH(arg1); \
        int expected_length = TOKEN_LENGTH(arg2); \
        if (actual_length != expected_length) { \
            printf("\x1b[31m[    KO    ] Token lists have different lengths\x1b[0m\n"); \
            printf("Actual token length: %d\n", actual_length); \
            printf("Expected token length: %d\n", expected_length); \
            printf("Actual tokens:\n"); \
            print_tokens(arg1); \
            printf("vs\n"); \
            printf("Expected output:\n"); \
            print_tokens(arg2); \
            failedTests++; \
        } else { \
            t_token *token1 = arg1; \
            t_token *token2 = arg2; \
            while (token1 != NULL && token2 != NULL) { \
                if (token1->type != token2->type || strcmp(token1->value, token2->value) != 0) { \
                    printf("\x1b[31m[    KO    ] Tokens are not equal\x1b[0m\n"); \
                    printf("Actual tokens:\n"); \
                    print_tokens(arg1); \
                    printf("vs\n"); \
                    printf("Expected output:\n"); \
                    print_tokens(arg2); \
                    failedTests++; \
                    break; \
                } \
                token1 = token1->next; \
                token2 = token2->next; \
            } \
            if (token1 == NULL && token2 == NULL) { \
                printf("\x1b[32m[    OK    ] Tokens are equal\x1b[0m\n"); \
                passedTests++; \
            } \
        } \
    } while (0)

#define ASSERT_AST_EQ(ast1, ast2) \
    do { \
        if (compare_ast(ast1, ast2)) { \
            printf("\x1b[32m[    OK    ] ASTs are identical\x1b[0m\n"); \
            passedTests++; \
        } else { \
            printf("\x1b[31m[    KO    ] ASTs are not identical\x1b[0m\n"); \
            printf("Actual AST:\n"); \
            print_ast(ast1, 0); \
            printf("vs\n"); \
            printf("Expected AST:\n"); \
            print_ast(ast2, 0); \
            failedTests++; \
        } \
    } while (0)

#endif
