/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rearrange_tokens_utils_1.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 09:57:31 by vscode            #+#    #+#             */
/*   Updated: 2024/05/11 16:10:00 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	combine_words_util(t_token **current, t_token **tmp);

void	combine_words_util1(t_token **current, t_token **tmp)
{
	(*tmp) = (*current)->next->next;
	free((*current)->next->value);
	if ((*current)->next->be_value)
		free((*current)->next->be_value);
	(*current)->next->be_value = NULL;
	free((*current)->next);
	(*current)->next = (*tmp);
}

void	combine_words_util_2(t_token **current, t_token **tmp)
{
	if ((*current)->type == TOKEN_SPACE)
		(*current) = (*current)->next;
	else if ((*current)->next && (*current)->next->type == TOKEN_WORD)
		combine_words_util(&(*current), &(*tmp));
}
