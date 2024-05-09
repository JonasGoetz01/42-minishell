/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 19:07:28 by vscode            #+#    #+#             */
/*   Updated: 2024/05/09 12:37:10 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*ft_combine_str(t_token *token)
{
	char	*str;
	char	*tmp;

	str = NULL;
	while (token)
	{
		if (str == NULL)
		{
			str = ft_strdup(token->value);
			if (str == NULL)
				return (NULL);
		}
		else
		{
			tmp = ft_strjoin(str, token->value);
			if (tmp == NULL)
				return (free(str), NULL);
			free(str);
			str = tmp;
		}
		token = token->next;
	}
	return (str);
}

bool	ft_should_expand_heredoc(t_ast_node *node)
{
	t_token	*token;

	if (node->right)
	{
		if (node->right->token)
		{
			token = node->right->token;
			while (token)
			{
				if (token->type == TOKEN_SINGLE_QUOTE
					|| token->type == TOKEN_DOUBLE_QUOTE)
					return (false);
				token = token->next;
			}
		}
	}
	return (true);
}

char	*ft_expand_heredoc(char *str, t_global *global)
{
	t_token	*tokens;
	char	*expanded;

	tokens = tokenize(str, &tokens, 0);
	ft_expand_tokens(tokens, global);
	expanded = ft_combine_str(tokens);
	free_tokens(tokens);
	return (expanded);
}
