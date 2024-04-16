#include "../../inc/minishell.h"

void	ft_exec_here_doc(t_ast_node *node)
{
	char	*line;
	char	*limiter;
	int		fd_pipe[2];

	limiter = node->right->token->value;
	if (pipe(fd_pipe) == -1)
	{
		ft_print_error(strerror(errno), NULL);
		return ;
	}
	while (true)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd_pipe[PIPE_WRITE]);
		ft_putstr_fd("\n", fd_pipe[PIPE_WRITE]);
		free(line);
	}
	close(fd_pipe[PIPE_WRITE]);
	node->left->fd_in[PIPE_READ] = fd_pipe[PIPE_READ];
}
