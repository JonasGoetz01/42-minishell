/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 19:03:52 by vscode            #+#    #+#             */
/*   Updated: 2024/05/11 10:52:16 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	handle_brackets(const char *input, int *i, t_token_type *type)
{
	if (input[*i] == '(')
		return (*type = TOKEN_BRACKET_L, true);
	else if (input[*i] == ')')
		return (*type = TOKEN_BRACKET_R, true);
	return (false);
}

bool	handle_greater_less(const char *input, int *i, t_token_type *type,
		char **value)
{
	if (input[*i] == '<')
	{
		if (input[*i + 1] == '<')
		{
			*type = TOKEN_DOUBLE_LESS;
			free(*value);
			*value = ft_substr(input, *i, 2);
			(*i)++;
		}
		else
			*type = TOKEN_LESS;
		return (true);
	}
	else if (input[*i] == '>')
	{
		if (input[*i + 1] == '>')
		{
			*type = TOKEN_DOUBLE_GREATER;
			free(*value);
			*value = ft_substr(input, *i, 2);
			(*i)++;
		}
		else
			*type = TOKEN_GREATER;
		return (true);
	}
	return (false);
}

bool	handle_pipe(const char *input, int *i, t_token_type *type, char **value)
{
	if (input[*i] == '|')
	{
		if (input[*i + 1] == '|')
		{
			*type = TOKEN_DOUBLE_PIPE;
			free(*value);
			*value = ft_substr(input, *i, 2);
			(*i)++;
		}
		else
			*type = TOKEN_PIPE;
		return (true);
	}
	return (false);
}

bool	handle_and(const char *input, int *i, t_token_type *type, char **value)
{
	if (input[*i] == '&')
	{
		if (input[*i + 1] == '&')
		{
			*type = TOKEN_DOUBLE_AMPERSAND;
			free(*value);
			*value = ft_strdup("&&");
			(*i)++;
		}
		else
			*type = TOKEN_AMPERSAND;
		return (true);
	}
	return (false);
}

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
