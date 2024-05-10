/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rearrange_tokens_utils_2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 09:57:31 by vscode            #+#    #+#             */
/*   Updated: 2024/05/10 09:30:37 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	update_h(t_rearrange_helper *h)
{
	h->before_end->next = h->redirect;
	h->redirect->next = h->file;
	h->file->next = h->end;
}

void	ft_set_free_get_file(t_token **file, t_token **tmp)
{
	(*tmp) = (*file)->next;
	(*file)->next = (*tmp)->next;
	free((*tmp)->value);
	if ((*tmp)->be_value)
		free((*tmp)->be_value);
	(*tmp)->be_value = NULL;
	free((*tmp));
	(*file) = (*file)->next;
	(*tmp) = (*file)->next;
	if ((*tmp)->next)
		(*file)->next = (*tmp)->next;
	else
		(*file)->next = NULL;
	free((*tmp)->value);
	if ((*tmp)->be_value)
		free((*tmp)->be_value);
	(*tmp)->be_value = NULL;
	free((*tmp));
	(*tmp) = NULL;
}

void	ft_inner_loop_after_file(t_token **after_file)
{
	t_token	*tmp;

	if ((*after_file)->next->type == TOKEN_SPACE)
	{
		tmp = (*after_file)->next;
		if ((*after_file)->next->next)
		{
			(*after_file)->next = (*after_file)->next->next;
			(*after_file) = (*after_file)->next;
		}
		else
			(*after_file)->next = NULL;
		free(tmp->value);
		if (tmp->be_value)
			free(tmp->be_value);
		free(tmp);
	}
}
