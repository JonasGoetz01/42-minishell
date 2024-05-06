/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retokenize_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 10:05:18 by vscode            #+#    #+#             */
/*   Updated: 2024/05/06 10:34:04 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	skip_quote_content(t_token **current, t_token **temp)
{
	if ((*current)->type == TOKEN_SINGLE_QUOTE
		|| (*current)->type == TOKEN_DOUBLE_QUOTE)
	{
		(*temp) = (*current);
		while ((*current)->next && (*current)->next->type != (*temp)->type)
			(*current) = (*current)->next;
		if ((*current)->next)
			(*current) = (*current)->next;
	}
}

void	skip_multiple_spaces(t_token **current, t_token **temp)
{
	if ((*current)->type == TOKEN_SPACE && (*current)->next
		&& (*current)->next->type == TOKEN_SPACE)
	{
		(*temp) = (*current)->next;
		(*current)->next = (*temp)->next;
		free((*temp)->value);
		free((*temp));
		(*temp) = NULL;
	}
}
