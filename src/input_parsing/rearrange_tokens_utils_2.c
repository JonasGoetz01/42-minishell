/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rearrange_tokens_utils_2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 09:57:31 by vscode            #+#    #+#             */
/*   Updated: 2024/05/09 17:34:24 by pgrossma         ###   ########.fr       */
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
	free((*tmp));
	(*file) = (*file)->next;
	(*tmp) = (*file)->next;
	if ((*tmp)->next)
		(*file)->next = (*tmp)->next;
	free((*tmp)->value);
	free((*tmp));
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
		free(tmp);
	}
}
