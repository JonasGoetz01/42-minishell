#include "../../inc/minishell.h"

bool	ft_is_last_pipe(t_ast_node *node)
{
	if (node->left && node->right)
	{
		return (ft_is_last_pipe(node));
	}

}
