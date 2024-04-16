#include "../../inc/minishell.h"

void	ft_open_in_file(t_ast_node *node)
{
	char	*file_name;
	int		fd;

	file_name = node->right->token->value;
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		ft_print_error(strerror(errno), file_name);
		fd = -2;
	}
	node->left->fd_in[PIPE_READ] = fd;
}
