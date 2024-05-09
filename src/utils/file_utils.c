#include "../../inc/minishell.h"

bool	ft_is_directory(const char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) != 0)
		return (false);
	return (S_ISDIR(statbuf.st_mode));
}

t_token	*ft_get_file_token(t_ast_node *node)
{
	t_token	*token;

	if (node->right)
	{
		if (node->right->token)
		{
			token = node->right->token;
			while (token)
			{
				if (token->type == TOKEN_ARG)
					return (token);
				token = token->next;
			}
		}
	}
	return (NULL);
}

char	*ft_get_file_name(t_ast_node *node)
{
	t_token	*token;

	if (node->right)
	{
		if (node->right->token)
		{
			token = node->right->token;
			while (token)
			{
				if (token->type == TOKEN_ARG)
					return (token->value);
				token = token->next;
			}
		}
	}
	return (NULL);
}
