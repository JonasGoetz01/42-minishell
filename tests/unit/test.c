#include "../../inc/minishell.h"
#include "helpers.h"
#include "test.h"
#include <stdio.h>

int	main(void)
{
	t_token	**tokens;
	t_token	**tokens1;

	INIT_TESTER();
	TEST("retokenize", "no changes needed", {
		tokens = create_token_list(1, "ls");
		tokens1 = create_token_list(1, "ls");
		retokenize(tokens);
		ASSERT_TOKENS_EQ(*tokens, *tokens1);
		free_token_list(tokens);
		free_token_list(tokens1);
	});
	TEST("retokenize", "split into tree words", {
		tokens = create_token_list(1, "ls (");
		tokens1 = create_token_list(3, "ls", " ", "(");
		retokenize(tokens);
		ASSERT_TOKENS_EQ(*tokens, *tokens1);
		free_token_list(tokens);
		free_token_list(tokens1);
	});
	TEST("retokenize", "more complex lists", {
		tokens = create_token_list(1, "echo $HOME | wc -l");
		tokens1 = create_token_list(8, "echo", " ", "$HOME", " ", "|", " ",
				"wc", " ");
		retokenize(tokens);
		ASSERT_TOKENS_EQ(*tokens, *tokens1);
		free_token_list(tokens);
		free_token_list(tokens1);
	});
	TEST("retokenize", "empty", {
		tokens = create_token_list(1, "");
		tokens1 = create_token_list(1, "");
		retokenize(tokens);
		ASSERT_TOKENS_EQ(*tokens, *tokens1);
		free_token_list(tokens);
		free_token_list(tokens1);
	});
	SUMMARIZE_TESTS();
	return (0);
}
