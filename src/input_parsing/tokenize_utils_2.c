/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 19:03:49 by vscode            #+#    #+#             */
/*   Updated: 2024/05/06 19:03:50 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	handle_empty_double_quote(t_token **tokens)
{
	t_token_type	type;
	char			*value;
	t_token			*new_token;

	type = TOKEN_DOUBLE_QUOTE;
	value = ft_strdup("\"");
	new_token = create_token(type, value);
	append_token(tokens, new_token);
	type = TOKEN_WORD;
	value = ft_strdup("");
	new_token = create_token(type, value);
	append_token(tokens, new_token);
	type = TOKEN_DOUBLE_QUOTE;
	value = ft_strdup("\"");
	new_token = create_token(type, value);
	append_token(tokens, new_token);
}

void	handle_empty_single_quotes(t_token **tokens)
{
	t_token_type	type;
	char			*value;
	t_token			*new_token;

	type = TOKEN_SINGLE_QUOTE;
	value = ft_strdup("\'");
	new_token = create_token(type, value);
	append_token(tokens, new_token);
	type = TOKEN_WORD;
	value = ft_strdup("");
	new_token = create_token(type, value);
	append_token(tokens, new_token);
	type = TOKEN_SINGLE_QUOTE;
	value = ft_strdup("\'");
	new_token = create_token(type, value);
	append_token(tokens, new_token);
}

int	handle_dq(const char *input, t_token **tokens, t_tokenize_helper *h)
{
	t_token	*new_token;
	int		token_len;

	if (input[h->i] == '\"')
	{
		if (input[(h->i) + 1] == '\"')
			return (handle_empty_double_quote(tokens), (h->i) += 2, 1);
		h->type = TOKEN_DOUBLE_QUOTE;
		h->value = ft_strdup("\"");
		new_token = create_token(h->type, h->value);
		append_token(tokens, new_token);
		(h->i)++;
		token_len = token_length(input + (h->i), "\"");
		h->value = ft_substr(input, h->i, token_len);
		new_token = create_token(TOKEN_WORD, h->value);
		append_token(tokens, new_token);
		(h->i) += token_len;
		h->value = ft_strdup("\"");
		h->type = TOKEN_DOUBLE_QUOTE;
		return (2);
	}
	return (0);
}

int	handle_single_quotes(const char *input, t_token **tokens,
		t_tokenize_helper *h)
{
	t_token	*new_token;
	int		token_len;

	if (input[h->i] == '\'')
	{
		if (input[h->i + 1] == '\'')
			return (handle_empty_single_quotes(tokens), (h->i) += 2, 1);
		h->type = TOKEN_SINGLE_QUOTE;
		h->value = ft_substr(input, h->i, 1);
		new_token = create_token(h->type, h->value);
		append_token(tokens, new_token);
		(h->i)++;
		token_len = token_length(input + h->i, "\'");
		h->value = ft_substr(input, h->i, token_len);
		new_token = create_token(TOKEN_WORD, h->value);
		append_token(tokens, new_token);
		h->i += token_len;
		h->value = ft_substr(input, h->i, 1);
		h->type = TOKEN_SINGLE_QUOTE;
		return (2);
	}
	return (0);
}

bool	handle_spaces(const char *input, int *i, t_token **tokens)
{
	t_token			*new_token;
	t_token_type	type;
	char			*value;

	if (input[*i] == ' ')
	{
		type = TOKEN_SPACE;
		value = ft_substr(input, *i, 1);
		new_token = create_token(type, value);
		append_token(tokens, new_token);
		(*i)++;
		return (true);
	}
	return (false);
}
