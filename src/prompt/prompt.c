/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgotz <jgotz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 18:51:02 by jgotz             #+#    #+#             */
/*   Updated: 2024/03/11 20:14:05 by jgotz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	show_prompt(char **envv)
{
	char	*input;
	char	*prompt;
	char	**inputs;
	int		num_tokens;
	t_token	*tokens;
	t_token	*stack;

	num_tokens = 0;
	prompt = ft_strjoin(get_current_dir(), KGRN);
	prompt = ft_strjoin(prompt, "❯ ");
	prompt = ft_strjoin(prompt, KNRM);
	input = readline(prompt);
	if (!input)
		return (1);
	add_history(input);
	if (validator(input))
	{
		printf("Invalid input\n");
		free(input);
		return (0);
	}
	printf("You entered: %s\n", input);
	setenv("PWD", get_current_dir(), 1);
	inputs = ft_split(input, ' ');
	if (ft_strncmp(inputs[0], "cd", 2) == 0)
		change_dir(inputs[1]);
	else if (ft_strncmp(inputs[0], "env", 3) == 0)
		print_envs(envv);
	tokens = tokenize(input);
	print_tokens(tokens);
	remove_unused_spaces(tokens);
	print_tokens(tokens);
	print_tokens_value(tokens);
	stack = postfixFromTokens(tokens);
	print_tokens(stack);
	free(input);
	return (0);
}
