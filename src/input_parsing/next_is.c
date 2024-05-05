/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_is.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:45:24 by vscode            #+#    #+#             */
/*   Updated: 2024/05/05 17:51:24 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	next_is_operator(t_token *token)
{
	t_token	*current;

	current = token;
	while (current && current->type == TOKEN_SPACE)
		current = current->next;
	if (current && is_operator(*current))
		return (true);
	return (false);
}

bool	next_is_word(t_token *token)
{
	t_token	*current;

	current = token;
	while (current && current->type == TOKEN_SPACE)
		current = current->next;
	if (current && current->type == TOKEN_WORD)
		return (true);
	return (false);
}

// check if all remining tokens are spaces
bool	next_is_newline(t_token *token)
{
	t_token	*current;

	current = token;
	while (current && current->type == TOKEN_SPACE)
		current = current->next;
	if (current)
		return (false);
	return (true);
}

bool	next_is_quotes(t_token *token)
{
	t_token	*current;

	current = token;
	while (current && current->type == TOKEN_SPACE)
		current = current->next;
	if (current && (current->type == TOKEN_SINGLE_QUOTE
			|| current->type == TOKEN_DOUBLE_QUOTE))
		return (true);
	return (false);
}

bool	next_is_brackets(t_token *token)
{
	t_token	*current;

	current = token;
	while (current && current->type == TOKEN_SPACE)
		current = current->next;
	{
		if (current->type == TOKEN_BRACKET_L
			|| current->type == TOKEN_BRACKET_R)
			return (true);
	}
	return (false);
}
