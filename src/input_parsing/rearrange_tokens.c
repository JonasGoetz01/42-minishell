/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rearrange_tokens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:40:23 by vscode            #+#    #+#             */
/*   Updated: 2024/05/05 18:40:36 by vscode           ###   ########.fr       */
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

bool	get_file(t_token **current, t_token **redirect, t_token **file)
{
	t_token	*tmp;

	*redirect = *current;
	*file = *redirect;
	while ((*file)->next && (*file)->next->type == TOKEN_SPACE)
		(*file) = (*file)->next;
	if (!(*file)->next || is_operator(*(*file)->next))
		return (true);
	if ((*file)->next && ((*file)->next->type == TOKEN_SINGLE_QUOTE
			|| (*file)->next->type == TOKEN_DOUBLE_QUOTE))
	{
		tmp = (*file)->next;
		(*file)->next = tmp->next;
		free(tmp->value);
		free(tmp);
		(*file)->next = NULL;
		(*file) = (*file)->next;
		tmp = (*file)->next;
		if (tmp->next)
			(*file)->next = tmp->next;
		else
			(*file)->next = NULL;
		free(tmp->value);
		free(tmp);
	}
	else if ((*file)->next && (*file)->next->type == TOKEN_WORD)
		(*file) = (*file)->next;
	return (false);
}

bool	get_after_file(t_token **after_file, t_token **file)
{
	*after_file = *file;
	while ((*after_file)->next && (*after_file)->next->type == TOKEN_SPACE)
		(*after_file) = (*after_file)->next;
	if (!(*after_file)->next || is_operator(*(*after_file)->next))
		return (true);
	if ((*after_file)->next)
		(*after_file) = (*after_file)->next;
	return (false);
}

void	get_end(t_token **end, t_token **before_end, t_token **after_file)
{
	*end = *after_file;
	while ((*end)->next && !is_operator(*(*end)->next))
		(*end) = (*end)->next;
	if ((*end)->next)
		(*before_end) = (*end)->prev;
	else
	{
		(*before_end) = (*end);
		(*end) = NULL;
	}
}

// sometimes the tokens need to be rearranged
// example 1:
// echo < file.txt hello ... => echo hello ... < file.txt
// example 2:
// echo < file.txt hello ... && test => echo hello ... < file.txt && test
// example 3:
// < file.txt echo hello ... => echo hello ... < file.txt
// example 4:
// < file.txt echo hello ... && test => echo hello ... < file.txt && test
//
// For testing
// echo 1 && < test.txt echo 2 && echo 3
// echo 1 && < test.txt echo 2 && < test1.txt echo 3
// < test.txt echo 1
void	rearrange_tokens(t_token **tokens)
{
	t_rearrange_helper	helper;
	t_rearrange_helper	*h;

	h = &helper;
	h->current = *tokens;
	skip_to_first_redirect(tokens, &(h->current));
	if (h->current && (h->current->type == TOKEN_GREATER
			|| h->current->type == TOKEN_DOUBLE_GREATER))
	{
		prev_link_list(tokens);
		if (!before_comes_word(&(h->current)))
		{
			if (get_file(&(h->current), &(h->redirect), &(h->file))
				|| get_after_file(&(h->after_file), &(h->file)))
				return ;
			get_end(&(h->end), &(h->before_end), &(h->after_file));
			move_on(tokens, &(h->current), &(h->after_file));
			h->before_end->next = h->redirect;
			h->redirect->next = h->file;
			h->file->next = h->end;
		}
	}
}
