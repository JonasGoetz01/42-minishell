/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   org_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 13:32:52 by pgrossma          #+#    #+#             */
/*   Updated: 2024/04/03 14:51:10 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_org_tokens(t_token *token)
{
	while (token)
	{
		if (token->type == TOKEN_WORD)
		{
			token->type = TOKEN_CMD;
			token = token->next;
			while (token && token->type == TOKEN_WORD)
			{
				token->type = TOKEN_ARG;
				token = token->next;
			}
		}
		else
			token = token->next;
	}
}
