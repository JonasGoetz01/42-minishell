#include "../../inc/minishell.h"

static int	ft_exec_buildin(t_process *process, char **envp)
{
	int	exit_code;
	int	dup_STDIN;
	int	dup_STDOUT;

	dup_STDIN = -1;
	dup_STDOUT = -1;
	if (process->pipe_fd_in[PIPE_READ] != -1)
	{
		dup_STDIN = dup(STDIN_FILENO);
		dup2(process->pipe_fd_in[PIPE_READ], STDIN_FILENO);
	}
	if (process->pipe_fd_out[PIPE_WRITE] != -1)
	{
		dup_STDOUT = dup(STDOUT_FILENO);
		dup2(process->pipe_fd_out[PIPE_WRITE], STDOUT_FILENO);
	}
	exit_code = ft_exec_buildins(process, envp);
	ft_close_fd(&process->pipe_fd_in[PIPE_READ]);
	ft_close_fd(&process->pipe_fd_in[PIPE_WRITE]);
	if (dup_STDIN != -1)
		dup2(dup_STDIN, STDIN_FILENO);
	ft_close_fd(&dup_STDIN);
	if (dup_STDOUT != -1)
		dup2(dup_STDOUT, STDOUT_FILENO);
	ft_close_fd(&dup_STDOUT);
	return (exit_code);
}

int	ft_execute_process(t_process *process, char **envp)
{
	if (process->is_buildin)
		return (ft_exec_buildin(process, envp));
	process->pid = fork();
	if (process->pid == -1)
		return (false);
	if (process->pid == 0)
	{
		if (process->pipe_fd_in[PIPE_READ] != -1)
			dup2(process->pipe_fd_in[PIPE_READ], STDIN_FILENO);
		ft_close_fd(&process->pipe_fd_in[PIPE_READ]);
		ft_close_fd(&process->pipe_fd_in[PIPE_WRITE]);
		if (process->pipe_fd_out[PIPE_WRITE] != -1)
			dup2(process->pipe_fd_out[PIPE_WRITE], STDOUT_FILENO);
		ft_close_fd(&process->pipe_fd_out[PIPE_READ]);
		ft_close_fd(&process->pipe_fd_out[PIPE_WRITE]);
		execve(process->cmd, process->args, envp);
		exit(1);
	}
	ft_close_fd(&process->pipe_fd_in[PIPE_READ]);
	ft_close_fd(&process->pipe_fd_in[PIPE_WRITE]);
	return (0);
}
