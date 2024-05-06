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