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
	TEST("retokenize", "no changes needed multiple words", {
		tokens = create_token_list(1, TOKEN_WORD, "echo", TOKEN_WORD, " ",
				TOKEN_WORD, "HELLO", TOKEN_WORD, " ", TOKEN_WORD, "WORLD");
		tokens1 = create_token_list(1, TOKEN_WORD, "echo", TOKEN_WORD, " ",
				TOKEN_WORD, "HELLO", TOKEN_WORD, " ", TOKEN_WORD, "WORLD");
		retokenize(tokens);
		ASSERT_TOKENS_EQ(*tokens, *tokens1);
		free_token_list(tokens);
		free_token_list(tokens1);
	});
	TEST("retokenize", "split into tree words", {
		tokens = create_token_list(1, TOKEN_WORD, "ls (");
		tokens1 = create_token_list(2, TOKEN_WORD, "ls", TOKEN_WORD, "(");
		retokenize(tokens);
		ASSERT_TOKENS_EQ(*tokens, *tokens1);
		free_token_list(tokens);
		free_token_list(tokens1);
	});
	TEST("retokenize", "more complex lists", {
		tokens = create_token_list(1, TOKEN_WORD, "echo $HOME | wc -l");
		tokens1 = create_token_list(5, TOKEN_WORD, "echo", TOKEN_WORD, "$HOME",
				TOKEN_WORD, "|", TOKEN_WORD, "wc", TOKEN_WORD, "-l");
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
	TEST("tokenize", "redirects", {
		tokens = malloc(sizeof(t_token *));
		*tokens = tokenize("ls -lah > file");
		tokens1 = create_token_list(7, TOKEN_WORD, "ls", TOKEN_WORD, " ",
				TOKEN_WORD, "-lah", TOKEN_WORD, " ", TOKEN_GREATER, ">",
				TOKEN_WORD, " ", TOKEN_WORD, "file");
		ASSERT_TOKENS_EQ(*tokens, *tokens1);
		free_token_list(tokens);
		free_token_list(tokens1);
	});
	TEST("tokenize", "multiple redirects", {
		tokens = malloc(sizeof(t_token *));
		*tokens = tokenize("ls -lah > file > file2");
		tokens1 = create_token_list(11, TOKEN_WORD, "ls", TOKEN_WORD, " ",
				TOKEN_WORD, "-lah", TOKEN_WORD, " ", TOKEN_GREATER, ">",
				TOKEN_WORD, " ", TOKEN_WORD, "file", TOKEN_WORD, " ",
				TOKEN_GREATER, ">", TOKEN_WORD, " ", TOKEN_WORD, "file2");
		ASSERT_TOKENS_EQ(*tokens, *tokens1);
		free_token_list(tokens);
		free_token_list(tokens1);
	});
	TEST("tokenize", "indirect", {
		tokens = malloc(sizeof(t_token *));
		*tokens = tokenize("ls -lah < file");
		tokens1 = create_token_list(7, TOKEN_WORD, "ls", TOKEN_WORD, " ",
				TOKEN_WORD, "-lah", TOKEN_WORD, " ", TOKEN_LESS, "<",
				TOKEN_WORD, " ", TOKEN_WORD, "file");
		ASSERT_TOKENS_EQ(*tokens, *tokens1);
		free_token_list(tokens);
		free_token_list(tokens1);
	});
	TEST("tokenize", "multiple indirect", {
		tokens = malloc(sizeof(t_token *));
		*tokens = tokenize("ls -lah < file < file2");
		tokens1 = create_token_list(11, TOKEN_WORD, "ls", TOKEN_WORD, " ",
				TOKEN_WORD, "-lah", TOKEN_WORD, " ", TOKEN_LESS, "<",
				TOKEN_WORD, " ", TOKEN_WORD, "file", TOKEN_WORD, " ",
				TOKEN_LESS, "<", TOKEN_WORD, " ", TOKEN_WORD, "file2");
		ASSERT_TOKENS_EQ(*tokens, *tokens1);
		free_token_list(tokens);
		free_token_list(tokens1);
	});
	TEST("tokenize", "parentheses", {
		tokens = malloc(sizeof(t_token *));
		*tokens = tokenize("(ls -lah)");
		tokens1 = create_token_list(5, TOKEN_BRACKET_L, "(", TOKEN_WORD, "ls",
				TOKEN_WORD, " ", TOKEN_WORD, "-lah", TOKEN_BRACKET_R, ")");
		ASSERT_TOKENS_EQ(*tokens, *tokens1);
		free_token_list(tokens);
		free_token_list(tokens1);
	});
	TEST("tokenize", "logical AND", {
		tokens = malloc(sizeof(t_token *));
		*tokens = tokenize("ls && pwd");
		tokens1 = create_token_list(5, TOKEN_WORD, "ls", TOKEN_WORD, " ",
				TOKEN_DOUBLE_AMPERSAND, "&&", TOKEN_WORD, " ", TOKEN_WORD,
				"pwd");
		ASSERT_TOKENS_EQ(*tokens, *tokens1);
		free_token_list(tokens);
		free_token_list(tokens1);
	});
	TEST("tokenize", "logical OR", {
		tokens = malloc(sizeof(t_token *));
		*tokens = tokenize("ls || pwd");
		tokens1 = create_token_list(5, TOKEN_WORD, "ls", TOKEN_WORD, " ",
				TOKEN_DOUBLE_PIPE, "||", TOKEN_WORD, " ", TOKEN_WORD, "pwd");
		ASSERT_TOKENS_EQ(*tokens, *tokens1);
		free_token_list(tokens);
		free_token_list(tokens1);
	});
	TEST("tokenize", "mixed operators 1", {
		tokens = malloc(sizeof(t_token *));
		*tokens = tokenize("ls -lah && (pwd || echo)");
		tokens1 = create_token_list(13, TOKEN_WORD, "ls", TOKEN_WORD, " ",
				TOKEN_WORD, "-lah", TOKEN_WORD, " ", TOKEN_DOUBLE_AMPERSAND,
				"&&", TOKEN_WORD, " ", TOKEN_BRACKET_L, "(", TOKEN_WORD, "pwd",
				TOKEN_WORD, " ", TOKEN_DOUBLE_PIPE, "||", TOKEN_WORD, " ",
				TOKEN_WORD, "echo", TOKEN_BRACKET_R, ")");
		ASSERT_TOKENS_EQ(*tokens, *tokens1);
		free_token_list(tokens);
		free_token_list(tokens1);
	});
	TEST("tokenize", "mixed operators 2", {
		tokens = malloc(sizeof(t_token *));
		*tokens = tokenize("(ls || pwd) && echo");
		tokens1 = create_token_list(11, TOKEN_BRACKET_L, "(", TOKEN_WORD, "ls",
				TOKEN_WORD, " ", TOKEN_DOUBLE_PIPE, "||", TOKEN_WORD, " ",
				TOKEN_WORD, "pwd", TOKEN_BRACKET_R, ")", TOKEN_WORD, " ",
				TOKEN_DOUBLE_AMPERSAND, "&&", TOKEN_WORD, " ", TOKEN_WORD,
				"echo");
		ASSERT_TOKENS_EQ(*tokens, *tokens1);
		free_token_list(tokens);
		free_token_list(tokens1);
	});
	TEST("tokenize", "mixed operators 3", {
		tokens = malloc(sizeof(t_token *));
		*tokens = tokenize("(ls && pwd) || echo");
		tokens1 = create_token_list(11, TOKEN_BRACKET_L, "(", TOKEN_WORD, "ls",
				TOKEN_WORD, " ", TOKEN_DOUBLE_AMPERSAND, "&&", TOKEN_WORD, " ",
				TOKEN_WORD, "pwd", TOKEN_BRACKET_R, ")", TOKEN_WORD, " ",
				TOKEN_DOUBLE_PIPE, "||", TOKEN_WORD, " ", TOKEN_WORD, "echo");
		ASSERT_TOKENS_EQ(*tokens, *tokens1);
		free_token_list(tokens);
		free_token_list(tokens1);
	});
	TEST("expand_tokens", "simple command", {
		tokens = create_token_list(1, TOKEN_WORD, "ls");
		ft_expand_tokens(*tokens, NULL);
		tokens1 = create_token_list(1, TOKEN_WORD, "ls");
		ASSERT_TOKENS_EQ(*tokens, *tokens1);
		free_token_list(tokens);
		free_token_list(tokens1);
	});
	TEST("expand_tokens", "multiple words", {
		tokens = create_token_list(3, TOKEN_WORD, "echo", TOKEN_WORD, " ",
				TOKEN_WORD, "world");
		ft_expand_tokens(*tokens, NULL);
		tokens1 = create_token_list(3, TOKEN_WORD, "echo", TOKEN_WORD, " ",
				TOKEN_WORD, "world");
		ASSERT_TOKENS_EQ(*tokens, *tokens1);
		free_token_list(tokens);
		free_token_list(tokens1);
	});
	TEST("expand_tokens", "simple variable", {
		tokens = create_token_list(1, TOKEN_WORD, "$HOME");
		ft_expand_tokens(*tokens, NULL);
		tokens1 = create_token_list(1, TOKEN_WORD, getenv("HOME"));
		ASSERT_TOKENS_EQ(*tokens, *tokens1);
		free_token_list(tokens);
		free_token_list(tokens1);
	});
	TEST("expand and retokenize", "simple variable", {
		tokens = create_token_list(1, TOKEN_WORD, "$HOME");
		ft_expand_tokens(*tokens, NULL);
		retokenize(tokens);
		tokens1 = create_token_list(1, TOKEN_WORD, getenv("HOME"));
		ASSERT_TOKENS_EQ(*tokens, *tokens1);
		free_token_list(tokens);
		free_token_list(tokens1);
	});
	TEST("expand and retokenize", "multiple words", {
		tokens = create_token_list(3, TOKEN_WORD, "echo", TOKEN_WORD, " ",
				TOKEN_WORD, "hello");
		ft_expand_tokens(*tokens, NULL);
		retokenize(tokens);
		tokens1 = create_token_list(3, TOKEN_WORD, "echo", TOKEN_WORD, " ",
				TOKEN_WORD, "hello");
		ASSERT_TOKENS_EQ(*tokens, *tokens1);
		free_token_list(tokens);
		free_token_list(tokens1);
	});
	SUMMARIZE_TESTS();
	return (0);
}
