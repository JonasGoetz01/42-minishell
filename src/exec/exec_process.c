#include "../../inc/minishell.h"

static void	ft_exec_buildin(t_process *process, t_global *global)
{
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
	ft_exec_buildins(process, global);
	ft_close_fd(&process->pipe_fd_in[PIPE_READ]);
	ft_close_fd(&process->pipe_fd_in[PIPE_WRITE]);
	if (dup_STDIN != -1)
		dup2(dup_STDIN, STDIN_FILENO);
	ft_close_fd(&dup_STDIN);
	if (dup_STDOUT != -1)
		dup2(dup_STDOUT, STDOUT_FILENO);
	ft_close_fd(&dup_STDOUT);
}

void	ft_execute_process(t_process *process, t_global *global)
{
	if (process->is_buildin)
	{
		ft_exec_buildin(process, global);
		return ;
	}
	process->pid = fork();
	if (process->pid == -1)
		return ;
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
		execve(process->cmd, process->args, global->envv);
		exit(1);
	}
	ft_close_fd(&process->pipe_fd_in[PIPE_READ]);
	ft_close_fd(&process->pipe_fd_in[PIPE_WRITE]);
}

void	ft_wait_for_processes(t_ast_node *node, t_global *global)
{
	if (!node)
		return ;
	ft_wait_for_processes(node->right, global);
	if (node->process)
	{
		if (DEBUG)
			printf("waiting for %s...\n", node->process->cmd);
		if (!node->process->is_buildin)
			waitpid(node->process->pid, &node->process->exit_status, 0);
		global->exit_status = node->process->exit_status;
	}
	ft_wait_for_processes(node->left, global);
}
