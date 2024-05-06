/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_tokens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 19:07:16 by vscode            #+#    #+#             */
/*   Updated: 2024/05/06 19:07:16 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	ft_fill_tokens(t_token *token, t_token *last_token, char **files,
		char *tmp)
{
	size_t	ind;

	ind = 0;
	if (files[ind])
	{
		tmp = ft_strdup(files[ind]);
		if (tmp == NULL)
			return (ft_arr_free((void **)files));
		free(token->value);
		token->value = tmp;
		ind++;
	}
	while (files[ind])
	{
		tmp = ft_strdup(files[ind]);
		if (tmp == NULL)
			return (ft_arr_free((void **)files));
		last_token = token->next;
		token->next = create_token(TOKEN_SPACE, NULL);
		token = token->next;
		token->next = create_token(TOKEN_WORD, tmp);
		token = token->next;
		token->next = last_token;
		ind++;
	}
}

static void	ft_expand_wildcard_token(t_token *token)
{
	char	**files;

	files = ft_expand_wildcard(token->value);
	if (files == NULL)
		return ;
	ft_fill_tokens(token, NULL, files, NULL);
}

void	ft_expand_wildcards(t_token *token)
{
	bool	in_single_quotes;
	bool	in_double_quotes;

	in_single_quotes = false;
	in_double_quotes = false;
	while (token)
	{
		if (token->type == TOKEN_SINGLE_QUOTE)
			in_single_quotes = !in_single_quotes;
		if (token->type == TOKEN_DOUBLE_QUOTE)
			in_double_quotes = !in_double_quotes;
		if (token->type == TOKEN_WORD)
		{
			if (ft_strnstr(token->value, "*", ft_strlen(token->value)) != 0
				&& in_single_quotes == false && in_double_quotes == false)
				ft_expand_wildcard_token(token);
		}
		token = token->next;
	}
}
