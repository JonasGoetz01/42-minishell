#ifndef TEST_H
# define TEST_H

#define TEST(function, description, body) \
      do { \
           printf("%s\n", function);         \
           printf("%s\n", description);   \
           (body);                     \
      } while (0)

#define ASSERT_EQ(arg1, arg2) \
      do { \
           if (arg1 == arg2) \
           { \
            printf("OK\n"); \
           } \
           else \
           { \
            printf("KO\n"); \
            exit(1); \
           } \
      } while (0)


#endif