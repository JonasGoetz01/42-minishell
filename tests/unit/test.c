#include "../../inc/minishell.h"
#include "test.h"

int	main(void)
{
	printf("Testing...!\n");
	TEST("Add", "Should add two numbers", {
		ASSERT_EQ(2 + 2, 4);
		ASSERT_EQ(2 + 3, 4);
	});

	return (0);
}