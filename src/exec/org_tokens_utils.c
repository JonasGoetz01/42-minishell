/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   org_tokens_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 16:23:30 by vscode            #+#    #+#             */
/*   Updated: 2024/05/11 16:23:31 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	*ft_first_valid_token(t_token *token)
{
	while (token)
	{
		if (token->type == TOKEN_WORD)
		{
			if (token->value && token->value[0] == '\0')
			{
				if (token->next)
				{
					if (token->next->type == TOKEN_DOUBLE_QUOTE
						|| token->next->type == TOKEN_SINGLE_QUOTE)
						break ;
				}
			}
			else
				break ;
		}
		token = token->next;
	}
	return (token);
}
