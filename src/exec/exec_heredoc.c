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
	free(msg);
}

static void	ft_read_here_doc(char *limiter, int fd_pipe[2])
{
	char	*line;

	while (true)
	{
		line = readline("> ");
		if (line == NULL)
		{
			ft_error_heredoc(limiter);
			break ;
		}
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd_pipe[PIPE_WRITE]);
		ft_putchar_fd('\n', fd_pipe[PIPE_WRITE]);
		free(line);
	}
}

static void ft_init_here_doc(char *limiter, int fd_pipe[2], t_ast_node *ast, t_global *global)
{
	pid_t	pid;
	int		exit_code;

	signal(SIGINT, handle_sigint_heredoc);
	pid = fork();
	if (pid == -1)
		return ;
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		ft_read_here_doc(limiter, fd_pipe);
		close(fd_pipe[PIPE_WRITE]);
		close(fd_pipe[PIPE_READ]);
		ft_close_all_fds(global);
		ft_free_nodes(ast);
		ft_free_global(global);
		exit(EXIT_SUCCESS);
	}
	else
	{
		exit_code = ft_wait_pid(pid);
		if (exit_code > 128)
			global->exit_status = exit_code;
	}
}

void	ft_exec_here_doc(t_ast_node *node, t_ast_node *ast, t_global *global)
{
	char	*limiter;
	int		fd_pipe[2];
	t_fd	*fd;

	limiter = ft_get_file_name(node);
	if (pipe(fd_pipe) != 0)
		return (ft_print_error(strerror(errno), NULL));
	ft_init_here_doc(limiter, fd_pipe, ast, global);
	close(fd_pipe[PIPE_WRITE]);
	fd = ft_add_t_fd(global);
	if (!fd)
		return ;
	fd->fd_pipe[PIPE_READ] = fd_pipe[PIPE_READ];
	if (node->left && global->exit_status != 130)
	{
		if (!node->left->fd_in[PIPE_READ])
		{
			node->left->fd_in[PIPE_READ] = &fd->fd_pipe[PIPE_READ];
			return ;
		}
	}
	ft_close_fd(&fd->fd_pipe[PIPE_READ]);
}
