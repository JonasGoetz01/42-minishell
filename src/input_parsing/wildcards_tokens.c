#include "../../inc/minishell.h"

static void	ft_expand_wildcard_token(t_token *token)
{
	char	**files;
	size_t	ind;
	char	*tmp;
	t_token	*last_token;

	files = ft_expand_wildcard(token->value);
	if (files == NULL)
		return ;
	ind = 0;
	if (files[ind])
	{
		tmp = ft_strdup(files[ind]);
		if (tmp == NULL)
			return (ft_arr_free((void **) files));
		free(token->value);
		token->value = tmp;
		ind++;
	}
	while (files[ind])
	{
		tmp = ft_strdup(files[ind]);
		if (tmp == NULL)
			return (ft_arr_free((void **) files));
		last_token = token->next;
		token->next = create_token(TOKEN_SPACE, NULL);
		token = token->next;
		token->next = create_token(TOKEN_WORD, tmp);
		token = token->next;
		token->next = last_token;
		ind++;
	}
}

void	ft_expand_wildcards(t_token *token)
{
	while (token)
	{
		if (token->type == TOKEN_WORD)
		{
			if (ft_strnstr(token->value, "*", ft_strlen(token->value)) != 0)
				ft_expand_wildcard_token(token);
		}
		token = token->next;
	}
}
