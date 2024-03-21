/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgotz <jgotz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 18:51:02 by jgotz             #+#    #+#             */
/*   Updated: 2024/03/21 14:01:39 by jgotz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void print_welcome_message()
{
	char *pastel_colors[] = {
        "\x1b[38;2;255;204;204m", // pastel red
        "\x1b[38;2;255;229;204m", // pastel orange
        "\x1b[38;2;255;242;204m", // pastel yellow
        "\x1b[38;2;204;255;204m", // pastel green
        "\x1b[38;2;204;255;255m", // pastel cyan
        "\x1b[38;2;204;204;255m", // pastel blue
        "\x1b[38;2;255;204;255m", // pastel magenta
    };

    printf("\x1b[2J");
	printf("%s", pastel_colors[0]);
	printf("%s\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t██████  ██████  ███████ ██   ██\n", pastel_colors[1]);
	printf("%s\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t██   ██ ██   ██ ██      ██   ██\n", pastel_colors[2]);
	printf("%s\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t██   ██ ██████  ███████ ███████\n", pastel_colors[3]);
	printf("%s\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t██   ██ ██           ██ ██   ██\n", pastel_colors[4]);
	printf("%s\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t██████  ██      ███████ ██   ██\n", pastel_colors[5]);
	printf("\x1b[0m");
	printf("\n\n");
	printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tDont panic shell\n");
	printf("\n");
	printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tpgrossma & jgotz\n");	
	printf("\n\n");
	
	fflush(stdout);
}

int	show_prompt(char **envv)
{
	char	*input;
	char	*prompt;
	char	**inputs;
	int		num_tokens;
	t_token	*tokens;
	t_token	*stack;

	num_tokens = 0;
    print_welcome_message();
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
