#include "../../inc/minishell.h"

void	ft_error_buildin(const char *msg, const char *arg, t_process *process, int exit_status)
{
	process->exit_status = exit_status;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(process->args[0], 2);
	ft_putstr_fd(": ", 2);
	if (arg)
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
}
