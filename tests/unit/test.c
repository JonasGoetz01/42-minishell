#include "../../inc/minishell.h"
#include "helpers.h"
#include "test.h"
#include <stdio.h>

void	test_expand(void)
{
	// t_token	**tokens;
	// t_token	**tokens1;
}

void	test_combine_words_in_quotes(void)
{
	// t_token	**tokens;
	// t_token	**tokens1;
}

void	test_retokenize(void)
{
	t_token	**tokens;
	t_token	**tokens1;

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
}

void	test_tokenize(void)
{
	t_token	**tokens;
	t_token	**tokens1;

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
}

void	test_expand_tokens(void)
{
	t_token	**tokens;
	t_token	**tokens1;

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
}

void	test_expand_and_retokenize(void)
{
	t_token	**tokens;
	t_token	**tokens1;

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
}

void	test_rearrange_tokens(void)
{
	t_token	**tokens;
	t_token	**tokens1;

	TEST("rearrange_tokens", "one word", {
		tokens = create_token_list(1, TOKEN_WORD, "echo");
		ft_expand_tokens(*tokens, NULL);
		retokenize(tokens);
		tokens1 = create_token_list(1, TOKEN_WORD, "echo", TOKEN_WORD, " ",
				TOKEN_WORD, "hello");
		ASSERT_TOKENS_EQ(*tokens, *tokens1);
		free_token_list(tokens);
		free_token_list(tokens1);
	});
}

void	test_remove_unused_spaces(void)
{
	t_token	**tokens;
	t_token	**tokens1;

	TEST("remove_unused_spaces", "one word", {
		tokens = create_token_list(1, TOKEN_WORD, "echo");
		remove_unused_spaces(tokens);
		tokens1 = create_token_list(1, TOKEN_WORD, "echo");
		ASSERT_TOKENS_EQ(*tokens, *tokens1);
		free_token_list(tokens);
		free_token_list(tokens1);
	});
	TEST("remove_unused_spaces", "multiple words", {
		tokens = create_token_list(3, TOKEN_WORD, "echo", TOKEN_WORD, " ",
				TOKEN_WORD, "hello");
		remove_unused_spaces(tokens);
		tokens1 = create_token_list(2, TOKEN_WORD, "echo", TOKEN_WORD, "hello");
		ASSERT_TOKENS_EQ(*tokens, *tokens1);
		free_token_list(tokens);
		free_token_list(tokens1);
	});
	TEST("remove_unused_spaces", "two spaces", {
		tokens = create_token_list(4, TOKEN_WORD, "echo", TOKEN_WORD, " ",
				TOKEN_WORD, " ", TOKEN_WORD, "hello");
		remove_unused_spaces(tokens);
		tokens1 = create_token_list(2, TOKEN_WORD, "echo", TOKEN_WORD, "hello");
		ASSERT_TOKENS_EQ(*tokens, *tokens1);
		free_token_list(tokens);
		free_token_list(tokens1);
	});
	TEST("remove_unused_spaces", "double quotes", {
		tokens = create_token_list(6, TOKEN_WORD, "echo", TOKEN_WORD, " ",
				TOKEN_DOUBLE_QUOTE, "\"", TOKEN_WORD, "hello", TOKEN_WORD, " ",
				TOKEN_DOUBLE_QUOTE, "\"");
		remove_unused_spaces(tokens);
		tokens1 = create_token_list(5, TOKEN_WORD, "echo", TOKEN_DOUBLE_QUOTE,
				"\"", TOKEN_WORD, "hello", TOKEN_WORD, " ", TOKEN_DOUBLE_QUOTE,
				"\"");
		ASSERT_TOKENS_EQ(*tokens, *tokens1);
		free_token_list(tokens);
		free_token_list(tokens1);
	});
	TEST("remove_unused_spaces", "multiple double quotes", {
		tokens = create_token_list(11, TOKEN_WORD, "echo", TOKEN_WORD, " ",
				TOKEN_DOUBLE_QUOTE, "\"", TOKEN_WORD, "hello", TOKEN_WORD, " ",
				TOKEN_DOUBLE_QUOTE, "\"", TOKEN_WORD, " ", TOKEN_DOUBLE_QUOTE,
				"\"", TOKEN_WORD, "hello", TOKEN_WORD, " ", TOKEN_DOUBLE_QUOTE,
				"\"");
		remove_unused_spaces(tokens);
		tokens1 = create_token_list(9, TOKEN_WORD, "echo", TOKEN_DOUBLE_QUOTE,
				"\"", TOKEN_WORD, "hello", TOKEN_WORD, " ", TOKEN_DOUBLE_QUOTE,
				"\"", TOKEN_DOUBLE_QUOTE, "\"", TOKEN_WORD, "hello", TOKEN_WORD,
				" ", TOKEN_DOUBLE_QUOTE, "\"");
		ASSERT_TOKENS_EQ(*tokens, *tokens1);
		free_token_list(tokens);
		free_token_list(tokens1);
	});
	TEST("remove_unused_spaces", "single quotes", {
		tokens = create_token_list(6, TOKEN_WORD, "echo", TOKEN_WORD, " ",
				TOKEN_SINGLE_QUOTE, "\'", TOKEN_WORD, "hello", TOKEN_WORD, " ",
				TOKEN_SINGLE_QUOTE, "\'");
		remove_unused_spaces(tokens);
		tokens1 = create_token_list(5, TOKEN_WORD, "echo", TOKEN_SINGLE_QUOTE,
				"\'", TOKEN_WORD, "hello", TOKEN_WORD, " ", TOKEN_SINGLE_QUOTE,
				"\'");
		ASSERT_TOKENS_EQ(*tokens, *tokens1);
		free_token_list(tokens);
		free_token_list(tokens1);
	});
	TEST("remove_unused_spaces", "multiple single quotes", {
		tokens = create_token_list(11, TOKEN_WORD, "echo", TOKEN_WORD, " ",
				TOKEN_SINGLE_QUOTE, "\'", TOKEN_WORD, "hello", TOKEN_WORD, " ",
				TOKEN_SINGLE_QUOTE, "\'", TOKEN_WORD, " ", TOKEN_SINGLE_QUOTE,
				"\'", TOKEN_WORD, "hello", TOKEN_WORD, " ", TOKEN_SINGLE_QUOTE,
				"\'");
		remove_unused_spaces(tokens);
		tokens1 = create_token_list(9, TOKEN_WORD, "echo", TOKEN_SINGLE_QUOTE,
				"\'", TOKEN_WORD, "hello", TOKEN_WORD, " ", TOKEN_SINGLE_QUOTE,
				"\'", TOKEN_SINGLE_QUOTE, "\'", TOKEN_WORD, "hello", TOKEN_WORD,
				" ", TOKEN_SINGLE_QUOTE, "\'");
		ASSERT_TOKENS_EQ(*tokens, *tokens1);
		free_token_list(tokens);
		free_token_list(tokens1);
	});
	TEST("remove_unused_spaces", "mixed quotes", {
		tokens = create_token_list(11, TOKEN_WORD, "echo", TOKEN_WORD, " ",
				TOKEN_SINGLE_QUOTE, "\'", TOKEN_WORD, "hello", TOKEN_WORD, " ",
				TOKEN_SINGLE_QUOTE, "\'", TOKEN_WORD, " ", TOKEN_DOUBLE_QUOTE,
				"\"", TOKEN_WORD, "hello", TOKEN_WORD, " ", TOKEN_DOUBLE_QUOTE,
				"\"");
		remove_unused_spaces(tokens);
		tokens1 = create_token_list(9, TOKEN_WORD, "echo", TOKEN_SINGLE_QUOTE,
				"\'", TOKEN_WORD, "hello", TOKEN_WORD, " ", TOKEN_SINGLE_QUOTE,
				"\'", TOKEN_DOUBLE_QUOTE, "\"", TOKEN_WORD, "hello", TOKEN_WORD,
				" ", TOKEN_DOUBLE_QUOTE, "\"");
		ASSERT_TOKENS_EQ(*tokens, *tokens1);
		free_token_list(tokens);
		free_token_list(tokens1);
	});
	TEST("remove_unused_spaces", "quotes in quotes", {
		tokens = create_token_list(10, TOKEN_WORD, "echo", TOKEN_WORD, " ",
				TOKEN_SINGLE_QUOTE, "\'", TOKEN_WORD, "hello", TOKEN_WORD, " ",
				TOKEN_DOUBLE_QUOTE, "\"", TOKEN_WORD, "world", TOKEN_WORD, " ",
				TOKEN_DOUBLE_QUOTE, "\"", TOKEN_SINGLE_QUOTE, "\'");
		remove_unused_spaces(tokens);
		tokens1 = create_token_list(9, TOKEN_WORD, "echo", TOKEN_SINGLE_QUOTE,
				"\'", TOKEN_WORD, "hello", TOKEN_WORD, " ", TOKEN_DOUBLE_QUOTE,
				"\"", TOKEN_WORD, "world", TOKEN_WORD, " ", TOKEN_DOUBLE_QUOTE,
				"\"", TOKEN_SINGLE_QUOTE, "\'");
		ASSERT_TOKENS_EQ(*tokens, *tokens1);
		free_token_list(tokens);
		free_token_list(tokens1);
		tokens = create_token_list(10, TOKEN_WORD, "echo", TOKEN_WORD, " ",
				TOKEN_DOUBLE_QUOTE, "\"", TOKEN_WORD, "hello", TOKEN_WORD, " ",
				TOKEN_SINGLE_QUOTE, "\'", TOKEN_WORD, "world", TOKEN_WORD, " ",
				TOKEN_SINGLE_QUOTE, "\'", TOKEN_DOUBLE_QUOTE, "\"");
		remove_unused_spaces(tokens);
		tokens1 = create_token_list(9, TOKEN_WORD, "echo", TOKEN_DOUBLE_QUOTE,
				"\"", TOKEN_WORD, "hello", TOKEN_WORD, " ", TOKEN_SINGLE_QUOTE,
				"\'", TOKEN_WORD, "world", TOKEN_WORD, " ", TOKEN_SINGLE_QUOTE,
				"\'", TOKEN_DOUBLE_QUOTE, "\"");
		ASSERT_TOKENS_EQ(*tokens, *tokens1);
		free_token_list(tokens);
		free_token_list(tokens1);
	});
}

void	test_gen_ast(void)
{
	t_token		**tokens;
	t_ast_node	*ast;

	// t_ast_node	**ast1;
	// t_token		**tokens1;
	// TEST("gen_ast", "simple command", {
	// 	ast = NULL;
	// 	ast1 = NULL;
	// 	tokens = create_token_list(1, TOKEN_WORD, "ls");
	// 	gen_ast(&ast, *tokens);
	// 	tokens1 = create_token_list(1, TOKEN_WORD, "ls");
	// 	ast1 = create_ast(*tokens);
	// 	ASSERT_AST_EQ(ast, ast1);
	// 	free_token_list(tokens);
	// 	free_token_list(tokens1);
	// 	free_ast(ast);
	// 	free_ast(ast1);
	// });
	// TEST("gen_ast", "simple command with flags", {
	// 	ast = NULL;
	// 	ast1 = NULL;
	// 	tokens = create_token_list(2, TOKEN_WORD, "ls", TOKEN_WORD, "-lah");
	// 	gen_ast(&ast, *tokens);
	// 	tokens1 = create_token_list(2, TOKEN_WORD, "ls", TOKEN_WORD, "-lah");
	// 	ast1 = create_ast(*tokens);
	// 	ASSERT_AST_EQ(ast, ast1);
	// 	free_token_list(tokens);
	// 	free_token_list(tokens1);
	// 	free_ast(ast);
	// 	free_ast(ast1);
	// });
	TEST("gen_ast", "simple command with flags and pipes", {
		tokens = create_token_list(1, TOKEN_WORD, "echo");
		// remove_unused_spaces(tokens);
		// print_tokens(*tokens);
		// gen_ast(&ast, *tokens);
		ast = create_ast(create_token_list(1, TOKEN_PIPE, "|"));
		// add_left(ast1, *create_token_list(2, TOKEN_WORD, "ls", TOKEN_WORD,
		// 		"-lah"));
		// add_right(ast1, *create_token_list(1, TOKEN_WORD, "lwc", TOKEN_WORD,
		// 		"-ll"));
		print_ast(&ast, 1);
		// print_ast(ast1, 2);
		// ASSERT_AST_EQ(ast, ast1);
		// free_token_list(tokens);
		// free_ast(*ast);
		// free_ast(*ast1);
	});
}

int	main(void)
{
	test_expand();
	test_combine_words_in_quotes();
	test_retokenize();
	test_tokenize();
	test_expand_tokens();
	test_expand_and_retokenize();
	test_rearrange_tokens();
	test_remove_unused_spaces();
	test_gen_ast();
	SUMMARIZE_TESTS();
	return (0);
}