#include "../../inc/minishell.h"

bool	ft_handle_pipe_token(t_ast_node *node, t_global *global)
{
	int		fd_pipe[2];
	t_fd	*fd;

	if (pipe(fd_pipe) != 0)
	{
		ft_print_error(strerror(errno), "pipe");
		return (false);
	}
	fd = ft_add_t_fd(global);
	if (!fd)
		return (false);
	fd->fd_pipe[PIPE_READ] = fd_pipe[PIPE_READ];
	fd->fd_pipe[PIPE_WRITE] = fd_pipe[PIPE_WRITE];
	if (node->left == NULL || node->right == NULL)
		return (false);
	node->left->fd_out[PIPE_WRITE] = &fd->fd_pipe[PIPE_WRITE];
	node->left->fd_out[PIPE_READ] = &fd->fd_pipe[PIPE_READ];
	node->right->fd_in[PIPE_READ] = &fd->fd_pipe[PIPE_READ];
	node->right->fd_in[PIPE_WRITE] = &fd->fd_pipe[PIPE_WRITE];
	node->left->fd_in[PIPE_READ] = node->fd_in[PIPE_READ];
	node->left->fd_in[PIPE_WRITE] = node->fd_in[PIPE_WRITE];
	node->right->fd_out[PIPE_READ] = node->fd_out[PIPE_READ];
	node->right->fd_out[PIPE_WRITE] = node->fd_out[PIPE_WRITE];
	return (true);
}
