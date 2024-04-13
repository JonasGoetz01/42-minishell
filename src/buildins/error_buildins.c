#include "../../inc/minishell.h"

void	ft_error_buildin(const char *msg, const char *arg, t_process *process, int exit_status)
{
	process->exit_status = exit_status;
	if (arg)
		printf("minishell: %s: %s: %s\n", process->cmd, arg, msg);
	else
		printf("minishell: %s: %s\n", process->cmd, msg);
}
