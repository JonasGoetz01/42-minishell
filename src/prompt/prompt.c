#include "../../inc/minishell.h"

void	process_input(char *input, char ***envv, t_global *global)
{
	t_token		*tokens;
	t_ast_node	*ast;

	// t_token		*root;
	// t_token		*stack;
	ast = NULL;
	if (DEBUG)
		printf("You entered: %s\n", input);
	setenv("PWD", getcwd(NULL, 0), 1);
	tokens = tokenize(input);
	ft_expand_tokens(tokens, global);
	if (DEBUG)
		print_tokens(tokens);
	remove_unused_spaces(&tokens);
	if (DEBUG)
		print_tokens(tokens);
	combine_words_in_quotes(&tokens);
	if (DEBUG)
		print_tokens(tokens);
	rearrange_tokens(&tokens);
	if (DEBUG)
		print_tokens(tokens);
	if (DEBUG)
		printf("---\n");
	// root = postfixFromTokens(tokens);
	// print_tokens(root);
	gen_ast(&ast, tokens);
	if (DEBUG)
		print_ast(&ast, 0);
	ft_exec_all(ast, envv, global);
	// print_tokens(tokens);
	// stack = postfixFromTokens(tokens);
	// print_tokens(stack);
	free(input);
}

char	*build_prompt(void)
{
	char	*prompt;

	prompt = ft_strdup("");
	prompt = ft_strjoin(prompt, KGRN); // Green color
	prompt = ft_strjoin(prompt, "👤 "); // User icon
	prompt = ft_strjoin(prompt, getenv("USER"));
	prompt = ft_strjoin(prompt, KNRM); // Reset color
	prompt = ft_strjoin(prompt, "@");
	prompt = ft_strjoin(prompt, KMAG); // Magenta color
	prompt = ft_strjoin(prompt, get_hostname());
	prompt = ft_strjoin(prompt, KNRM); // Reset color
	prompt = ft_strjoin(prompt, "\n");
	prompt = ft_strjoin(prompt, KBLU); // Blue color
	prompt = ft_strjoin(prompt, getcwd(NULL, 0));
	prompt = ft_strjoin(prompt, KGRN);  // Green color
	prompt = ft_strjoin(prompt, " ❯ "); // Arrow icon
	prompt = ft_strjoin(prompt, KNRM);  // Reset color
	return (prompt);
}

int	show_prompt(char ***envv, t_global *global)
{
	char	*input;
	char	*prompt;

	prompt = build_prompt();
	input = readline(prompt);
	if (!input)
		return (1);
	if (input[0] == '\0')
	{
		free(input);
		return (0);
	}
	add_history(input);
	if (validator(input))
	{
		printf("Invalid input\n");
		free(input);
		return (0);
	}
	process_input(input, envv, global);
	return (0);
}
