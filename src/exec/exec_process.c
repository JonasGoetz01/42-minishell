#include "../../inc/minishell.h"

static void	ft_buildin_dup(t_process *process, int *dup_stdin, int *dup_stdout)
{
	if (ft_get_fd(process->file_in) != -1)
	{
		*dup_stdin = dup(STDIN_FILENO);
		dup2(ft_get_fd(process->file_in), STDIN_FILENO);
	}
	if (ft_get_fd(process->file_out) != -1)
	{
		*dup_stdout = dup(STDOUT_FILENO);
		dup2(ft_get_fd(process->file_out), STDOUT_FILENO);
	}
}

static void	ft_exec_buildin(t_process *process, t_global *global)
{
	int	dup_stdin;
	int	dup_stdout;

	dup_stdin = -1;
	dup_stdout = -1;
	ft_buildin_dup(process, &dup_stdin, &dup_stdout);
	ft_exec_buildins(process, global);
	if (dup_stdin != -1)
		dup2(dup_stdin, STDIN_FILENO);
	ft_close_fd(&dup_stdin);
	if (dup_stdout != -1)
		dup2(dup_stdout, STDOUT_FILENO);
	ft_close_fd(&dup_stdout);
}

void	ft_execute_process(t_process *process, t_global *global)
{
	int	exit_code;

	if (ft_exec_buildin_in_fork(process))
		return (ft_exec_buildin(process, global));
	process->pid = fork();
	if (process->pid == -1)
		return (ft_print_error(strerror(errno), process->cmd));
	if (process->pid == 0)
	{
		if (ft_get_fd(process->file_in) != -1)
			dup2(ft_get_fd(process->file_in), STDIN_FILENO);
		else if (ft_get_fd(process->fd_in[PIPE_READ]) != -1)
			dup2(ft_get_fd(process->fd_in[PIPE_READ]), STDIN_FILENO);
		if (ft_get_fd(process->file_out) != -1)
			dup2(ft_get_fd(process->file_out), STDOUT_FILENO);
		else if (ft_get_fd(process->fd_out[PIPE_WRITE]) != -1)
			dup2(ft_get_fd(process->fd_out[PIPE_WRITE]), STDOUT_FILENO);
		ft_close_all_fds(global);
		if (process->is_buildin)
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
}

void	ft_wait_for_processes(t_ast_node *node, t_global *global)
{
	int	exit_status;

	if (!node)
		return ;
	ft_wait_for_processes(node->right, global);
	if (node->process)
	{
		if (DEBUG)
			printf("waiting for %s...\n", node->process->cmd);
		if (ft_exec_buildin_in_fork(node->process))
		{
			if (waitpid(node->process->pid, &exit_status, 0 | WUNTRACED) != -1)
				node->exit_status = WEXITSTATUS(exit_status);
		}
	}
	if (node->exit_status != -1)
		global->exit_status = node->exit_status;
	ft_wait_for_processes(node->left, global);
}

void	ft_set_right_exit_code(t_ast_node *node, t_global *global)
{
	if (!node)
		return ;
	if (node->process || node->exit_status != -1)
		global->exit_status = node->exit_status;
	ft_set_right_exit_code(node->left, global);
	ft_set_right_exit_code(node->right, global);
}
