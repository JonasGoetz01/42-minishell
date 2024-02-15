/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgotz <jgotz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 21:25:18 by jgotz             #+#    #+#             */
/*   Updated: 2024/02/15 12:22:48 by jgotz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_strarrlen(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	**tokenize_input(char *input)
{
	char	**words;
	char	**tokens;
	int		i;

	words = ft_split(input, ' ');
	i = 0;
	tokens = (char **)malloc(sizeof(char *) * ft_strarrlen(words));
	while (words[i])
	{
		tokens[i] = ft_strdup("WORD");
	}
	free(words);
	return (tokens);
}

void	print_tokens(char *input)
{
	char	**tokens;

	tokens = tokenize_input(input);
}

//