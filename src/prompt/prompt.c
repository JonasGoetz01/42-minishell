/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgotz <jgotz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 18:51:02 by jgotz             #+#    #+#             */
/*   Updated: 2024/02/14 19:01:50 by jgotz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	show_prompt(void)
{
	char	*input;
	char	*promt;
	char	**inputs;

	promt = ft_strjoin(get_current_dir(), "> ");
	input = readline(promt);
	if (!input)
	{
		printf("\nExiting...\n");
		return (1);
	}
	add_history(input);
	printf("You entered: %s\n", input);
	inputs = ft_split(input, ' ');
	if (ft_strncmp(inputs[0], "cd", 2) == 0)
	{
		change_dir(inputs[1]);
	}
	free(input);
	return (0);
}
