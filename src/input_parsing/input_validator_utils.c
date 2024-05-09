/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validator_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:42:12 by vscode            #+#    #+#             */
/*   Updated: 2024/05/09 16:38:55 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token_type	get_next_type(t_token *token);

bool	first_is_pipe_second_operator(t_token **prev, t_token **current,
		t_token **tokens)
{
	if ((!(*prev) && ((*current)->type == TOKEN_PIPE)) || ((*current) == *tokens
			&& next_is_operator((*current))))
	{
		while ((*current)->type == TOKEN_SPACE)
			(*current) = (*current)->next;
		if ((*current)->type == TOKEN_PIPE)
			return (true);
	}
	return (false);
}

bool	pipe_after_pipe(t_token *current)
{
	if (current->type == TOKEN_PIPE
		&& get_next_type(current->next) == TOKEN_PIPE)
		return (true);
	return (false);
}

bool	redirect_has_no_file(t_token *current)
{
	if ((current->type == TOKEN_GREATER
			|| current->type == TOKEN_DOUBLE_GREATER) && ((current->next
				&& next_is_operator(current->next))
			|| next_is_newline(current->next)))
		return (true);
	return (false);
}

bool	no_file_for_indirect(t_token *current)
{
	if (current->type == TOKEN_LESS && ((current->next
				&& next_is_operator(current->next))
			|| next_is_newline(current->next)))
		return (true);
	return (false);
}
