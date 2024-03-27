/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 12:47:34 by jgotz             #+#    #+#             */
/*   Updated: 2024/03/27 15:36:17 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	ft_execute_process(t_cmd *cmd, t_process *process, char **envp)
{
	(void)cmd;
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
		if (ft_strlen(process->cmd) > 0)
			execve(process->cmd, process->args, envp);
		else
		{
			// ft_free_close(cmd);
			exit(127);
		}
	}
	return (true);
}

int	ft_wait_for_processes(t_cmd *cmd)
{
	int		status;
	pid_t	pid;

	status = 0;
	pid = cmd->processes[cmd->process_len - 1]->pid;
	waitpid(pid, &status, 0);
	while (wait(NULL) > 0)
		;
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_FAILURE);
}

char	*execute_command(const char *command)
{
	int		pipefd[2];
	char	*args[] = {(char *)command, NULL};
	char	*output;
	ssize_t	bytes_read;
	pid_t	pid;

	if (pipe(pipefd) == -1)
		return (NULL);
	pid = fork();
	if (pid == -1)
		return (NULL);
	else if (pid == 0)
	{
		close(pipefd[0]);
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			exit(EXIT_FAILURE);
		execve(command, args, NULL);
		exit(EXIT_FAILURE);
	}
	else
	{
		close(pipefd[1]);
		output = (char *)malloc(MAX_BUFFER_SIZE);
		if (output == NULL)
			return (NULL);
		memset(output, 0, MAX_BUFFER_SIZE);
		while ((bytes_read = read(pipefd[0], output, MAX_BUFFER_SIZE - 1)) > 0)
		{
		}
		if (bytes_read == -1)
		{
			free(output);
			return (NULL);
		}
		close(pipefd[0]);
		wait(NULL);
		return (output);
	}
}
