/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 19:03:35 by vscode            #+#    #+#             */
/*   Updated: 2024/05/09 08:17:31 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	handle_empty_double_quote(t_token **tokens);
void	handle_empty_single_quotes(t_token **tokens);
int		handle_dq(const char *input, t_token **tokens, t_tokenize_helper *h);
int		handle_single_quotes(const char *input, t_token **tokens,
			t_tokenize_helper *h);
bool	handle_spaces(const char *input, int *i, t_token **tokens);
bool	handle_brackets(const char *input, int *i, t_token_type *type);
bool	handle_greater_less(const char *input, int *i, t_token_type *type,
			char **value);
bool	handle_pipe(const char *input, int *i, t_token_type *type,
			char **value);
bool	handle_and(const char *input, int *i, t_token_type *type, char **value);
void	handle_other_delimiters(char **value, const char *input, int *i,
			t_token_type *type);

void	handle_word(int *i, const char *input, const char *delimiters,
		t_token **tokens)
{
	int		token_len;
	char	*value;
	t_token	*new_token;

	token_len = token_length(input + *i, delimiters);
	value = ft_substr(input, *i, token_len);
	new_token = create_token(TOKEN_WORD, value);
	append_token(tokens, new_token);
	(*i) += token_len;
}

bool	tokenize_util(const char *input, t_token **tokens, t_tokenize_helper *h)
{
	int	return_value;

	return_value = handle_single_quotes(input, tokens, h);
	if (return_value != 0)
	{
		if (return_value == 1)
			return (true);
	}
	else
	{
		if (handle_spaces(input, &(h->i), tokens))
			return (true);
		else
			handle_other_delimiters(&(h->value), input, &(h->i), &(h->type));
	}
	return (false);
}

t_token	*tokenize(const char *input, t_token **tokens, int rv)
{
	t_tokenize_helper	h;
	t_token				*new_token;

	h.i = 0;
	*tokens = NULL;
	while (h.i < (int)ft_strlen(input) && input[h.i] != '\0')
	{
		if (ft_strchr("()<>|&\"' \t", input[h.i]))
		{
			rv = handle_dq(input, tokens, &h);
			if (rv != 0)
			{
				if (rv == 1)
					continue ;
			}
			else if (tokenize_util(input, tokens, &h))
				continue ;
			new_token = create_token(h.type, h.value);
			append_token(tokens, new_token);
			h.i++;
		}
		else
			handle_word(&(h.i), input, "()<>|&\"' \t", tokens);
	}
	return (*tokens);
}
