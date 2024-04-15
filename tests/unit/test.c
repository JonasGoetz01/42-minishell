#include "test.h"
#include <stdio.h>

TEST_COUNT(1);

int	main(void)
{
	INIT_TESTER();
	TEST("add", "Should add two numbers", {
		ASSERT_EQ(2 + 2, 4);
		ASSERT_EQ(2 + 3, 4);
	});
	TEST("sub", "Should substract two numbers", {
		ASSERT_EQ(2 - 2, 0);
		ASSERT_EQ(2 - 3, -1);
	});
	SUMMARIZE_TESTS();
	return (0);
}
