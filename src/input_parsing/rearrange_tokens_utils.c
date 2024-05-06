/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rearrange_tokens_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 09:57:31 by vscode            #+#    #+#             */
/*   Updated: 2024/05/06 09:57:32 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	before_comes_word(t_token **token)
{
	t_token	*current;

	current = *token;
	if (current->prev == NULL)
		return (false);
	while (current->prev != NULL)
	{
		if (current->prev->type == TOKEN_WORD)
			return (true);
		current = current->prev;
	}
	return (false);
}

void	move_on(t_token **tokens, t_token **current, t_token **after_file)
{
	prev_link_list(tokens);
	if ((*current)->prev)
	{
		(*current) = (*current)->prev;
		(*current)->next = (*after_file);
	}
	else
	{
		(*current) = *tokens;
		*tokens = (*after_file);
	}
	prev_link_list(tokens);
}

void	skip_to_first_redirect(t_token **tokens, t_token **current)
{
	prev_link_list(tokens);
	while ((*current) != NULL && !((*current)->type == TOKEN_LESS
			|| (*current)->type == TOKEN_DOUBLE_LESS
			|| (*current)->type == TOKEN_GREATER
			|| (*current)->type == TOKEN_DOUBLE_GREATER))
	{
		(*current) = (*current)->next;
	}
}
