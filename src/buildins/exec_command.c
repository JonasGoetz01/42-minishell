#include "../../inc/minishell.h"

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
