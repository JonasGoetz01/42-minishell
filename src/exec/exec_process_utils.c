#include "../../inc/minishell.h"

void	ft_execute_child_process(t_process *process, t_global *global)
{
	int	exit_code;

	if (ft_get_fd(process->file_in) != -1)
		dup2(ft_get_fd(process->file_in), STDIN_FILENO);
	else if (ft_get_fd(process->fd_in[PIPE_READ]) != -1)
		dup2(ft_get_fd(process->fd_in[PIPE_READ]), STDIN_FILENO);
	if (ft_get_fd(process->file_out) != -1)
		dup2(ft_get_fd(process->file_out), STDOUT_FILENO);
	else if (ft_get_fd(process->fd_out[PIPE_WRITE]) != -1)
		dup2(ft_get_fd(process->fd_out[PIPE_WRITE]), STDOUT_FILENO);
	ft_close_all_fds(global);
	if (process->type == PROCESS_BUILDIN_FORK)
	{
		ft_exec_buildins(process, global);
		exit_code = process->exit_status;
		ft_free_nodes(process->ast);
		ft_free_global(global);
		exit(exit_code);
	}
	else
	{
		execve(process->cmd, process->args, global->envv);
		ft_print_error(strerror(errno), process->cmd);
		exit(1);
	}
}

int	ft_wait_pid(pid_t pid)
{
	int	status;

	if (waitpid(pid, &status, 0 | WUNTRACED) == -1)
		return (-1);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (WTERMSIG(status) + 128);
	return (-1);
}
