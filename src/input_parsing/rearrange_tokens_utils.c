/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rearrange_tokens_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 09:57:31 by vscode            #+#    #+#             */
/*   Updated: 2024/05/10 09:11:02 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	combine_words_util(t_token **current, t_token **tmp);

bool	bcw(t_token **token)
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

void	combine_words(t_token **c)
{
	t_token	*current;
	t_token	*tmp;

	current = *c;
	while (current->next && current->next->type == TOKEN_SPACE)
		current = current->next;
	while (current->next && (!is_operator(*current->next)
			&& current->next->type != TOKEN_SPACE))
	{
		if (current->next && (current->next->type == TOKEN_DOUBLE_QUOTE
				|| current->next->type == TOKEN_SINGLE_QUOTE))
		{
			if (!current->next->next || (current->next->next
					&& current->next->next->type != TOKEN_DOUBLE_QUOTE
					&& current->next->next->type != TOKEN_SINGLE_QUOTE
					&& (current->next->next->type != TOKEN_WORD
						|| current->next->next->value[0] != '\0')))
			{
				tmp = current->next->next;
				free(current->next->value);
				if (current->next->be_value)
					free(current->next->be_value);
				current->next->be_value = NULL;
				free(current->next);
				current->next = tmp;
			}
			else
				current = current->next->next->next;
		}
		else if (current->type == TOKEN_SPACE)
			current = current->next;
		else if (current->next && current->next->type == TOKEN_WORD)
			combine_words_util(&current, &tmp);
	}
}

int	count_words_after(t_token **c)
{
	t_token	*current;
	int		num_words;

	current = *c;
	num_words = 0;
	while (current->next && current->next->type == TOKEN_SPACE)
		current = current->next;
	while (current->next && !is_operator(*current->next))
	{
		if (current->next->type == TOKEN_WORD)
			num_words++;
		current = current->next;
	}
	return (num_words);
}
