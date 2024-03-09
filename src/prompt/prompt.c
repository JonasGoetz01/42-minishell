/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgotz <jgotz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 18:51:02 by jgotz             #+#    #+#             */
/*   Updated: 2024/03/09 14:28:30 by jgotz            ###   ########.fr       */
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
	int		postFixSize;

	prompt = ft_strjoin(get_current_dir(), KGRN);
	prompt = ft_strjoin(prompt, "❯ ");
	prompt = ft_strjoin(prompt, KNRM);
	input = readline(prompt);
	if (!input)
		return (1);
	add_history(input);
	printf("You entered: %s\n", input);
	setenv("PWD", get_current_dir(), 1);
	inputs = ft_split(input, ' ');
	if (ft_strncmp(inputs[0], "cd", 2) == 0)
		change_dir(inputs[1]);
	else if (ft_strncmp(inputs[0], "env", 3) == 0)
		print_envs(envv);
	tokens = tokenize(input, &num_tokens);
	print_tokens(tokens, num_tokens);
	stack = postfixFromTokens(tokens, num_tokens, &postFixSize);
	print_tokens(stack, postFixSize);
	free(input);
	return (0);
}
