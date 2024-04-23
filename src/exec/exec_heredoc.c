#include "../../inc/minishell.h"

void	ft_exec_here_doc(t_ast_node *node, t_global *global)
{
	char	*line;
	char	*limiter;
	int		fd_pipe[2];

	limiter = node->right->token->value;
	if (pipe(fd_pipe) == -1)
		return (ft_print_error(strerror(errno), NULL));
	while (true)
	{
		ft_putstr_fd("> ", STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (ft_strncmp(line, limiter, ft_strlen(limiter) + 1) == 0)
		{
			free(line);
			get_next_line(-1);
			break ;
		}
		ft_putstr_fd(line, fd_pipe[PIPE_WRITE]);
		ft_putstr_fd("\n", fd_pipe[PIPE_WRITE]);
		free(line);
	}
	close(fd_pipe[PIPE_WRITE]);
	t_fd *fd = ft_add_t_fd(global);
	if (!fd)
		return ;
	fd->fd_pipe[PIPE_READ] = fd_pipe[PIPE_READ];
	node->left->fd_in[PIPE_READ] = &fd->fd_pipe[PIPE_READ];
}
