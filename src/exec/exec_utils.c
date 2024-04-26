#include "../../inc/minishell.h"

char	*ft_get_file_name(t_ast_node *node)
{
	if (node->right)
	{
		if (node->right->token)
		{
			return (node->right->token->value);
		}
	}
	return (NULL);
}