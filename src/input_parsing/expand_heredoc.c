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
	bool	is_in_single_quotes;
	bool	is_in_double_quotes;

	is_in_single_quotes = false;
	is_in_double_quotes = false;
	if (node->right)
	{
		if (node->right->token)
		{
			token = node->right->token;
			while (token)
			{
				if (token->type == TOKEN_ARG)
					return (!(is_in_double_quotes || is_in_single_quotes));
				else if (token->type == TOKEN_SINGLE_QUOTE)
					is_in_single_quotes = !is_in_single_quotes;
				else if (token->type == TOKEN_DOUBLE_QUOTE)
					is_in_double_quotes = !is_in_double_quotes;
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

	tokens = tokenize(str);
	ft_expand_tokens(tokens, global);
	expanded = ft_combine_str(tokens);
	free_tokens(tokens);
	return (expanded);
}
