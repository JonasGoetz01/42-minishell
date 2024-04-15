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
		tokens = create_token_list(1, TOKEN_WORD, "ls");
		tokens1 = create_token_list(1, TOKEN_WORD, "ls");
		retokenize(tokens);
		ASSERT_TOKENS_EQ(*tokens, *tokens1);
		free_token_list(tokens);
		free_token_list(tokens1);
	});
	TEST("retokenize", "split into tree words", {
		tokens = create_token_list(1, TOKEN_WORD, "ls (");
		tokens1 = create_token_list(3, TOKEN_WORD, "ls", TOKEN_WORD, " ",
				TOKEN_WORD, "(");
		retokenize(tokens);
		ASSERT_TOKENS_EQ(*tokens, *tokens1);
		free_token_list(tokens);
		free_token_list(tokens1);
	});
	TEST("retokenize", "more complex lists", {
		tokens = create_token_list(1, TOKEN_WORD, "echo $HOME | wc -l");
		tokens1 = create_token_list(9, TOKEN_WORD, "echo", TOKEN_WORD, " ",
				TOKEN_WORD, "$HOME", TOKEN_WORD, " ", TOKEN_WORD, "|",
				TOKEN_WORD, " ", TOKEN_WORD, "wc", TOKEN_WORD, " ", TOKEN_WORD,
				"-l");
		retokenize(tokens);
		ASSERT_TOKENS_EQ(*tokens, *tokens1);
		free_token_list(tokens);
		free_token_list(tokens1);
	});
	TEST("retokenize", "empty", {
		tokens = create_token_list(1, TOKEN_WORD, "");
		tokens1 = create_token_list(1, TOKEN_WORD, "");
		retokenize(tokens);
		ASSERT_TOKENS_EQ(*tokens, *tokens1);
		free_token_list(tokens);
		free_token_list(tokens1);
	});
	//
	// ---- tokenize
	//
	TEST("tokenize", "simple command", {
		tokens = malloc(sizeof(t_token *));
		*tokens = tokenize("ls");
		tokens1 = create_token_list(1, TOKEN_WORD, "ls");
		ASSERT_TOKENS_EQ(*tokens, *tokens1);
		free_token_list(tokens);
		free_token_list(tokens1);
	});
	TEST("tokenize", "more words", {
		tokens = malloc(sizeof(t_token *));
		*tokens = tokenize("ls -l -a -lah");
		tokens1 = create_token_list(7, TOKEN_WORD, "ls", TOKEN_WORD, " ",
				TOKEN_WORD, "-l", TOKEN_WORD, " ", TOKEN_WORD, "-a", TOKEN_WORD,
				" ", TOKEN_WORD, "-lah");
		ASSERT_TOKENS_EQ(*tokens, *tokens1);
		free_token_list(tokens);
		free_token_list(tokens1);
	});
	TEST("tokenize", "pipes", {
		tokens = malloc(sizeof(t_token *));
		*tokens = tokenize("ls -lah | wc -l");
		tokens1 = create_token_list(9, TOKEN_WORD, "ls", TOKEN_WORD, " ",
				TOKEN_WORD, "-lah", TOKEN_WORD, " ", TOKEN_PIPE, "|",
				TOKEN_WORD, " ", TOKEN_WORD, "wc", TOKEN_WORD, " ", TOKEN_WORD,
				"-l");
		ASSERT_TOKENS_EQ(*tokens, *tokens1);
		free_token_list(tokens);
		free_token_list(tokens1);
	});
	TEST("tokenize", "multiple pipes", {
		tokens = malloc(sizeof(t_token *));
		*tokens = tokenize("ls -lah | wc -l | cat -e");
		tokens1 = create_token_list(15, TOKEN_WORD, "ls", TOKEN_WORD, " ",
				TOKEN_WORD, "-lah", TOKEN_WORD, " ", TOKEN_PIPE, "|",
				TOKEN_WORD, " ", TOKEN_WORD, "wc", TOKEN_WORD, " ", TOKEN_WORD,
				"-l", TOKEN_WORD, " ", TOKEN_PIPE, "|", TOKEN_WORD, " ",
				TOKEN_WORD, "cat", TOKEN_WORD, " ", TOKEN_WORD, "-e");
		ASSERT_TOKENS_EQ(*tokens, *tokens1);
		free_token_list(tokens);
		free_token_list(tokens1);
	});
	SUMMARIZE_TESTS();
	return (0);
}
