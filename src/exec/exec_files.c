#include "../../inc/minishell.h"

void	ft_open_in_file(t_ast_node *node)
{
	char	*file_name;

	file_name = node->right->token->value;
	node->left->fd_in[PIPE_READ] = open(file_name, O_RDONLY);
}
