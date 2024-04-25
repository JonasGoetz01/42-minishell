#include "../../inc/minishell.h"

void	process_input(char *input, t_global *global)
{
	t_token		*tokens;
	t_ast_node	*ast;
	char		*cwd;

	ast = NULL;
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		ft_set_env_env("PWD", cwd, &global->envv);
		ft_set_env_export("PWD", cwd, &global->env_export);
		free(cwd);
	}
	tokens = tokenize(input);
	print_tokens(tokens);
	ft_expand_tokens(tokens, global);
	print_tokens(tokens);
	// remove_unused_spaces(&tokens);
	// print_tokens(tokens);
	retokenize(&tokens);
	print_tokens(tokens);
	if (input_validation(&tokens))
		return (free_token(&tokens), free(input));
	else if (DEBUG)
		printf("Input is valid\n");
	combine_words_in_quotes(&tokens);
	print_tokens(tokens);
	rearrange_tokens(&tokens);
	print_tokens(tokens);
	gen_ast(&ast, tokens);
	ft_exec_all(ast, global);
	free(input);
}

char	*build_prompt(t_global *global)
{
	char	*prompt;
	char	*temp;
	char	*reset_color;
	char	*username;

	prompt = ft_strdup("");
	reset_color = ft_strdup(KNRM);
	temp = ft_strjoin(prompt, KGRN);
	free(prompt);
	prompt = temp;
	temp = ft_strjoin(prompt, "👤 ");
	free(prompt);
	prompt = temp;
	username = ft_get_env("USER", global->envv);
	if (username == NULL)
	{
		temp = ft_strjoin(prompt, "user");
		free(prompt);
		prompt = temp;
	}
	else
	{
		temp = ft_strjoin(prompt, username);
		free(prompt);
		prompt = temp;
	}
	free(username);
	temp = ft_strjoin(prompt, reset_color);
	free(prompt);
	prompt = temp;
	temp = ft_strjoin(prompt, "@");
	free(prompt);
	prompt = temp;
	temp = ft_strjoin(prompt, KMAG);
	free(prompt);
	prompt = temp;
	temp = ft_strjoin(prompt, get_hostname());
	free(prompt);
	prompt = temp;
	temp = ft_strjoin(prompt, reset_color);
	free(prompt);
	prompt = temp;
	temp = ft_strjoin(prompt, "\n");
	free(prompt);
	prompt = temp;
	temp = ft_strjoin(prompt, KBLU);
	free(prompt);
	prompt = temp;
	temp = ft_strjoin(prompt, getcwd(NULL, 0));
	free(prompt);
	prompt = temp;
	temp = ft_strjoin(prompt, KGRN);
	free(prompt);
	prompt = temp;
	temp = ft_strjoin(prompt, " ❯ ");
	free(prompt);
	prompt = temp;
	temp = ft_strjoin(prompt, reset_color);
	free(prompt);
	free(reset_color);
	return (temp);
}

int	show_prompt(t_global *global)
{
	char	*input;
	char	*prompt;

	if (global->isatty)
	{
		prompt = build_prompt(global);
		input = readline(prompt);
		free(prompt);
	}
	else
	{
		input = get_next_line(fileno(stdin));
		input = ft_strtrim(input, "\n");
	}
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
	process_input(input, global);
	return (0);
}
