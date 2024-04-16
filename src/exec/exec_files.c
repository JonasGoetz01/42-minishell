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

void	ft_open_out_file(t_ast_node *node)
{
	char	*file_name;
	int		fd;

	file_name = node->right->token->value;
	fd = open(file_name, O_TRUNC | O_WRONLY | O_CREAT, 0644);
	if (fd == -1)
	{
		ft_print_error(strerror(errno), file_name);
		fd = -2;
	}
	node->left->fd_out[PIPE_WRITE] = fd;
}

void	ft_open_out_append_file(t_ast_node *node)
{
	char	*file_name;
	int		fd;

	file_name = node->right->token->value;
	fd = open(file_name, O_APPEND | O_WRONLY | O_CREAT, 0644);
	if (fd == -1)
	{
		ft_print_error(strerror(errno), file_name);
		fd = -2;
	}
	node->left->fd_out[PIPE_WRITE] = fd;
}
