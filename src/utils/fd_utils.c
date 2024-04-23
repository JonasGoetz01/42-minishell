#include "../../inc/minishell.h"

void	ft_close_fd(int *fd)
{
	if (!fd)
		return ;
	if (*fd != -1 && *fd != -2)
	{
		if (close(*fd) != 0)
			ft_print_error(strerror(errno), NULL);
		*fd = -1;
	}
}

static t_fd	*ft_init_t_fd(void)
{
	t_fd	*fd;

	fd = malloc(sizeof(t_fd));
	if (!fd)
		return (NULL);
	fd->fd_file = -1;
	fd->fd_pipe[PIPE_READ] = -1;
	fd->fd_pipe[PIPE_WRITE] = -1;
	fd->next = NULL;
	return (fd);
}

t_fd	*ft_add_t_fd(t_global *global)
{
	t_fd	*new_fd;
	t_fd	**next_fd;

	new_fd = ft_init_t_fd();
	if (!new_fd)
		return (NULL);
	if (!global->fds)
		global->fds = new_fd;
	else
	{
		next_fd = &global->fds->next;
		while (*next_fd)
			next_fd = &(*next_fd)->next;
		*next_fd = new_fd;
	}
	return (new_fd);
}

void	ft_close_fd_node(t_ast_node *node)
{
	ft_close_fd(node->file_in);
	ft_close_fd(node->fd_in[PIPE_READ]);
	ft_close_fd(node->fd_in[PIPE_WRITE]);
	ft_close_fd(node->fd_out[PIPE_READ]);
	ft_close_fd(node->fd_out[PIPE_WRITE]);
	ft_close_fd(node->file_out);
}

void	ft_close_all_fds(t_global *global)
{
	t_fd	*fds;
	t_fd	*tmp;

	fds = global->fds;
	while (fds)
	{
		ft_close_fd(&fds->fd_file);
		ft_close_fd(&fds->fd_pipe[PIPE_READ]);
		ft_close_fd(&fds->fd_pipe[PIPE_WRITE]);
		tmp = fds;
		fds = fds->next;
		free(tmp);
	}
	global->fds = NULL;
}

int	ft_get_fd(int *fd)
{
	if (fd)
		return (*fd);
	return (-1);
}
