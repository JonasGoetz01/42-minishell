/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 19:03:52 by vscode            #+#    #+#             */
/*   Updated: 2024/05/11 16:06:37 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	handle_brackets(const char *input, int *i, t_token_type *type);
bool	handle_greater_less_util(const char *input, int *i, t_token_type *type,
			char **value);
bool	handle_greater_less(const char *input, int *i, t_token_type *type,
			char **value);
bool	handle_pipe(const char *input, int *i, t_token_type *type,
			char **value);
bool	handle_and(const char *input, int *i, t_token_type *type, char **value);

void	handle_other_delimiters(char **value, const char *input, int *i,
		t_token_type *type)
{
	*value = ft_substr(input, *i, 1);
	if (handle_brackets(input, i, type))
	{
		free(*value);
		*value = NULL;
	}
	else if (handle_greater_less(input, i, type, value))
		;
	else if (handle_pipe(input, i, type, value))
		;
	else if (handle_and(input, i, type, value))
		;
	else
	{
		*type = TOKEN_WORD;
		free(*value);
	}
}
