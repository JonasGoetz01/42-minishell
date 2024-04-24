#include "../../inc/minishell.h"

static char	*ft_get_file_name(t_ast_node *node)
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

void	ft_open_in_file(t_ast_node *node, t_global *global)
{
	char	*file_name;
	t_fd	*fd;

	file_name = ft_get_file_name(node);
	fd = ft_add_t_fd(global);
	if (!fd)
		return ;
	fd->fd_file = open(file_name, O_RDONLY);
	if (fd->fd_file == -1)
	{
		ft_print_error(strerror(errno), file_name);
		fd->fd_file = -2;
	}
	if (!node->left->file_in)
		node->left->file_in = &fd->fd_file;
	else
		ft_close_fd(&fd->fd_file);
}

void	ft_open_out_file(t_ast_node *node, t_global *global)
{
	char	*file_name;
	t_fd	*fd;

	file_name = ft_get_file_name(node);
	fd = ft_add_t_fd(global);
	if (!fd)
		return ;
	fd->fd_file = open(file_name, O_TRUNC | O_WRONLY | O_CREAT, 0644);
	if (fd->fd_file == -1)
	{
		ft_print_error(strerror(errno), file_name);
		fd->fd_file = -2;
	}
	if (!node->left->file_out)
		node->left->file_out = &fd->fd_file;
	else
		ft_close_fd(&fd->fd_file);
}

void	ft_open_out_append_file(t_ast_node *node, t_global *global)
{
	char	*file_name;
	t_fd	*fd;

	file_name = ft_get_file_name(node);
	fd = ft_add_t_fd(global);
	if (!fd)
		return ;
	fd->fd_file = open(file_name, O_APPEND | O_WRONLY | O_CREAT, 0644);
	if (fd->fd_file == -1)
	{
		ft_print_error(strerror(errno), file_name);
		fd->fd_file = -2;
	}
	if (!node->left->file_out)
		node->left->file_out = &fd->fd_file;
	else
		ft_close_fd(&fd->fd_file);
}
