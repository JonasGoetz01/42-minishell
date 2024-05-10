/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rearrange_tokens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:40:23 by vscode            #+#    #+#             */
/*   Updated: 2024/05/10 09:28:54 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	bcw(t_token **token);
void	move_on(t_token **tokens, t_token **current, t_token **after_file);
void	skip_to_first_redirect(t_token **tokens, t_token **current);
int		count_words_after(t_token **c);
void	combine_words(t_token **c);
void	update_h(t_rearrange_helper *h);
void	ft_set_free_get_file(t_token **file, t_token **tmp);
void	ft_inner_loop_after_file(t_token **after_file);

bool	get_file(t_token **current, t_token **redirect, t_token **file,
		t_token **tmp)
{
	*redirect = *current;
	*file = *redirect;
	while ((*file)->next && (*file)->next->type == TOKEN_SPACE)
		(*file) = (*file)->next;
	if (!(*file)->next || is_operator(*(*file)->next))
		return (true);
	if ((*file)->next && ((*file)->next->type == TOKEN_SINGLE_QUOTE
			|| (*file)->next->type == TOKEN_DOUBLE_QUOTE))
		ft_set_free_get_file(file, tmp);
	else if ((*file)->next && (*file)->next->type == TOKEN_WORD)
		(*file) = (*file)->next;
	return (false);
}

bool	get_after_file(t_token **after_file, t_token **file)
{
	*after_file = *file;
	while ((*after_file)->next && (*after_file)->next->type != TOKEN_SPACE)
		(*after_file) = (*after_file)->next;
	while ((*after_file)->next && (*after_file)->next->type == TOKEN_SPACE)
	{
		ft_inner_loop_after_file(after_file);
	}
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

void	combine_words_util(t_token **current, t_token **tmp)
{
	char	*temp;

	if ((*current)->type == TOKEN_SPACE)
		temp = ft_strdup((*current)->next->value);
	else
		temp = ft_strjoin((*current)->value, (*current)->next->value);
	free((*current)->value);
	(*current)->value = temp;
	(*current)->type = TOKEN_WORD;
	(*tmp) = (*current)->next->next;
	free((*current)->next->value);
	if ((*current)->next->be_value)
		free((*current)->next->be_value);
	(*current)->next->be_value = NULL;
	free((*current)->next);
	(*current)->next = (*tmp);
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
	t_token				*tmp;

	tmp = NULL;
	h = &helper;
	h->current = *tokens;
	skip_to_first_redirect(tokens, &(h->current));
	if (h->current && (h->current->type == TOKEN_GREATER
			|| h->current->type == TOKEN_DOUBLE_GREATER
			|| h->current->type == TOKEN_DOUBLE_LESS))
	{
		prev_link_list(tokens);
		if (!bcw(&(h->current)) || count_words_after(&(h->current)) > 1)
		{
			combine_words(&(h->current));
			if (get_file(&(h->current), &(h->redirect), &(h->file), &tmp)
				|| get_after_file(&(h->after_file), &(h->file)))
				return ;
			get_end(&(h->end), &(h->before_end), &(h->after_file));
			move_on(tokens, &(h->current), &(h->after_file));
			update_h(h);
		}
	}
}
