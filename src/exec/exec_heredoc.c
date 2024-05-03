#include "../../inc/minishell.h"

static void	ft_error_heredoc(char *limiter)
{
	char	*msg;
	char	*tmp;

	tmp = ft_strjoin("here-document at line 1 delimited by end-of-file (wanted `", limiter);
	if (tmp == NULL)
		return ;
	msg = ft_strjoin(tmp, "')");
	if (msg == NULL)
		return (free(tmp));
	ft_print_error(msg, "warning");
}

static void	ft_read_here_doc(char *limiter, int fd_pipe[2])
{
	char	*line;
	char	*limiter_nl;

	limiter_nl = ft_strjoin(limiter, "\n");
	if (limiter_nl == NULL)
		return ;
	while (g_signal != SIGNAL_INT)
	{
		line = readline("> ");
		if (line == NULL)
		{
			ft_error_heredoc(limiter);
			break ;
		}
		if (ft_strncmp(line, limiter_nl, ft_strlen(limiter_nl)) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd_pipe[PIPE_WRITE]);
		free(line);
	}
	get_next_line(-1);
	free(limiter_nl);
}

static void ft_init_here_doc(char *limiter, int fd_pipe[2])
{
	struct sigaction	sa_heredoc;
	struct sigaction	sa_old;

	sa_heredoc.sa_handler = handle_sigint_heredoc;
	sigemptyset(&sa_heredoc.sa_mask);
	sa_heredoc.sa_flags = 0;
	sigaction(SIGINT, &sa_heredoc, &sa_old);
	ft_read_here_doc(limiter, fd_pipe);
	sigaction(SIGINT, &sa_old, NULL);
}

void	ft_exec_here_doc(t_ast_node *node, t_global *global)
{
	char	*limiter;
	int		fd_pipe[2];
	t_fd	*fd;

	limiter = ft_get_file_name(node);
	if (pipe(fd_pipe) != 0)
		return (ft_print_error(strerror(errno), NULL));
	ft_init_here_doc(limiter, fd_pipe);
	close(fd_pipe[PIPE_WRITE]);
	fd = ft_add_t_fd(global);
	if (!fd)
		return ;
	fd->fd_pipe[PIPE_READ] = fd_pipe[PIPE_READ];
	if (node->left)
	{
		if (!node->left->fd_in[PIPE_READ])
		{
			node->left->fd_in[PIPE_READ] = &fd->fd_pipe[PIPE_READ];
			return ;
		}
	}
	ft_close_fd(&fd->fd_pipe[PIPE_READ]);
}
