#include "../../inc/minishell.h"

t_token	*tokenize(const char *input)
{
	t_token			*tokens;
	const char		*delimiters = "()<>|&\"' ";
	char			*value;
	t_token_type	type;
	t_token			*new_token;
	int				i;
	int				tokenLen;

	tokens = NULL;
	i = 0;
	while (i < (int)ft_strlen(input) && input[i] != '\0')
	{
		if (ft_strchr(delimiters, input[i]))
		{
			value = ft_substr(input, i, 1);
			if (input[i] == '(')
				type = TOKEN_BRACKET_L;
			else if (input[i] == ')')
				type = TOKEN_BRACKET_R;
			else if (input[i] == '<')
			{
				if (input[i + 1] == '<')
				{
					type = TOKEN_DOUBLE_LESS;
					value = ft_substr(input, i, 2);
					i++;
				}
				else
					type = TOKEN_LESS;
			}
			else if (input[i] == '>')
			{
				if (input[i + 1] == '>')
				{
					type = TOKEN_DOUBLE_GREATER;
					value = ft_substr(input, i, 2);
					i++;
				}
				else
					type = TOKEN_GREATER;
			}
			else if (input[i] == '|')
			{
				if (input[i + 1] == '|')
				{
					type = TOKEN_DOUBLE_PIPE;
					value = ft_substr(input, i, 2);
					i++;
				}
				else
					type = TOKEN_PIPE;
			}
			else if (input[i] == '&')
			{
				if (input[i + 1] == '&')
				{
					type = TOKEN_DOUBLE_AMPERSAND;
					value = ft_substr(input, i, 2);
					i++;
				}
				else
					type = TOKEN_AMPERSAND;
			}
			else if (input[i] == '\"')
			{
				if (input[i + 1] == '\"')
				{
					i += 1;
					continue ;
				}
				type = TOKEN_DOUBLE_QUOTE;
				value = ft_substr(input, i, 1);
				new_token = create_token(type, value);
				append_token(&tokens, new_token);
				i++;
				tokenLen = token_length(input + i, "\"");
				value = ft_substr(input, i, tokenLen);
				new_token = create_token(TOKEN_WORD, value);
				append_token(&tokens, new_token);
				i += tokenLen;
				value = ft_substr(input, i, 1);
				type = TOKEN_DOUBLE_QUOTE;
			}
			else if (input[i] == '\'')
			{
				if (input[i + 1] == '\'')
				{
					i += 2;
					continue ;
				}
				type = TOKEN_SINGLE_QUOTE;
				value = ft_substr(input, i, 1);
				new_token = create_token(type, value);
				append_token(&tokens, new_token);
				i++;
				tokenLen = token_length(input + i, "\'");
				value = ft_substr(input, i, tokenLen);
				new_token = create_token(TOKEN_WORD, value);
				append_token(&tokens, new_token);
				i += tokenLen;
				value = ft_substr(input, i, 1);
				type = TOKEN_SINGLE_QUOTE;
			}
			else
				type = TOKEN_WORD;
			new_token = create_token(type, value);
			append_token(&tokens, new_token);
			i++;
		}
		else
		{
			tokenLen = token_length(input + i, delimiters);
			value = ft_substr(input, i, tokenLen);
			new_token = create_token(TOKEN_WORD, value);
			append_token(&tokens, new_token);
			i += tokenLen;
		}
	}
	return (tokens);
}
