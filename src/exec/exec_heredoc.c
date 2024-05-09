#include "../../inc/minishell.h"

static bool	ft_process_line(char *line, bool should_expand,
							t_heredoc *heredoc, t_global *global)
{
	char	*expanded;

	if (ft_strncmp(line, heredoc->lim,
			ft_strlen(heredoc->lim) + 1) == 0)
		return (false);
	expanded = NULL;
	if (should_expand)
	{
		expanded = ft_expand_heredoc(line, global);
		if (expanded)
			line = expanded;
	}
	ft_putstr_fd(line, heredoc->fd_pipe[PIPE_WRITE]);
	ft_putchar_fd('\n', heredoc->fd_pipe[PIPE_WRITE]);
	if (expanded)
		free(expanded);
	return (true);
}

static void	ft_read_here_doc(t_heredoc *heredoc, bool should_expand,
								t_global *global)
{
	char	*line;
	char	**lines;
	size_t	ind;
	bool	stop;

	stop = false;
	while (stop == false)
	{
		line = ft_test_compatible_readline(global);
		if (line == NULL)
			return (ft_error_heredoc(heredoc->lim));
		lines = ft_split(line, '\n');
		if (lines == NULL)
			return (free(line));
		ind = 0;
		while (lines[ind])
		{
			stop = !ft_process_line(lines[ind], should_expand, heredoc, global);
			if (stop)
				break ;
			ind++;
		}
		free(line);
		ft_arr_free((void **) lines);
	}
}

static void	ft_child_here_doc(t_heredoc *heredoc, bool should_expand,
	t_ast_node *ast, t_global *global)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	ft_read_here_doc(heredoc, should_expand, global);
	close(heredoc->fd_pipe[PIPE_WRITE]);
	close(heredoc->fd_pipe[PIPE_READ]);
	ft_close_all_fds(global);
	ft_free_nodes(ast);
	ft_free_global(global);
	exit(EXIT_SUCCESS);
}

static void	ft_init_here_doc(t_heredoc *heredoc, bool should_expand,
	t_ast_node *ast, t_global *global)
{
	pid_t	pid;
	int		exit_code;

	signal(SIGINT, handle_sigint_heredoc);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid == -1)
		return ;
	else if (pid == 0)
		ft_child_here_doc(heredoc, should_expand, ast, global);
	else
	{
		exit_code = ft_wait_pid(pid);
		if (exit_code > 128)
			global->exit_status = exit_code;
	}
	signal(SIGINT, handle_exec);
	signal(SIGQUIT, handle_exec);
}

void	ft_exec_here_doc(t_ast_node *node, t_ast_node *ast, t_global *global)
{
	t_fd		*fd;
	t_heredoc	heredoc;

	heredoc.lim = ft_get_limiter(node);
	if (heredoc.lim == NULL)
		return ;
	if (pipe(heredoc.fd_pipe) != 0)
		return (ft_print_error(strerror(errno), NULL));
	ft_init_here_doc(&heredoc, ft_should_expand_heredoc(node), ast, global);
	close(heredoc.fd_pipe[PIPE_WRITE]);
	fd = ft_add_t_fd(global);
	if (!fd)
		return ;
	fd->fd_pipe[PIPE_READ] = heredoc.fd_pipe[PIPE_READ];
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
