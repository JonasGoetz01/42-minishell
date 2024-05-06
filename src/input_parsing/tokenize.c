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

bool	handle_brackets(const char *input, int *i, t_token_type *type)
{
	if (input[*i] == '(')
		return (*type = TOKEN_BRACKET_L, true);
	else if (input[*i] == ')')
		return (*type = TOKEN_BRACKET_R, true);
	return (false);
}

bool	handle_greater_less(const char *input, int *i, t_token_type *type,
		char **value)
{
	if (input[*i] == '<')
	{
		if (input[*i + 1] == '<')
		{
			*type = TOKEN_DOUBLE_LESS;
			*value = ft_substr(input, *i, 2);
			(*i)++;
		}
		else
			*type = TOKEN_LESS;
		return (true);
	}
	else if (input[*i] == '>')
	{
		if (input[*i + 1] == '>')
		{
			*type = TOKEN_DOUBLE_GREATER;
			*value = ft_substr(input, *i, 2);
			(*i)++;
		}
		else
			*type = TOKEN_GREATER;
		return (true);
	}
	return (false);
}

bool	handle_pipe(const char *input, int *i, t_token_type *type, char **value)
{
	if (input[*i] == '|')
	{
		if (input[*i + 1] == '|')
		{
			*type = TOKEN_DOUBLE_PIPE;
			*value = ft_substr(input, *i, 2);
			(*i)++;
		}
		else
			*type = TOKEN_PIPE;
		return (true);
	}
	return (false);
}

bool	handle_and(const char *input, int *i, t_token_type *type, char **value)
{
	if (input[*i] == '&')
	{
		if (input[*i + 1] == '&')
		{
			*type = TOKEN_DOUBLE_AMPERSAND;
			*value = ft_substr(input, *i, 2);
			(*i)++;
		}
		else
			*type = TOKEN_AMPERSAND;
		return (true);
	}
	return (false);
}

void	handle_other_delimiters(char **value, const char *input, int *i,
		t_token_type *type)
{
	*value = ft_substr(input, *i, 1);
	if (handle_brackets(input, i, type))
		;
	else if (handle_greater_less(input, i, type, value))
		;
	else if (handle_pipe(input, i, type, value))
		;
	else if (handle_and(input, i, type, value))
		;
	else
		*type = TOKEN_WORD;
}

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
		if (ft_strchr("()<>|&\"' ", input[h.i]))
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
			handle_word(&(h.i), input, "()<>|&\"' ", tokens);
	}
	return (*tokens);
}
