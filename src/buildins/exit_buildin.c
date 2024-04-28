#include "../../inc/minishell.h"

static void	ft_start_exit(int exit_status, t_process *process, t_global *global)
{
	global->should_exit = true;
	global->exit_status = exit_status;
	process->exit_status = exit_status;
}

static bool	ft_con_num(char *arg1)
{
	size_t	ind;

	ind = 0;
	if (arg1[ind] == '+' || arg1[ind] == '-')
		ind++;
	while (arg1[ind])
	{
		if (!ft_isdigit(arg1[ind]))
			return (true);
		ind++;
	}
	return (false);
}

void	ft_exit_buildin(t_process *process, t_global *global)
{
	char	*arg1;

	arg1 = process->args[1];
	if (global->isatty)
		ft_putstr_fd("exit\n", 1);
	if (!arg1)
		ft_start_exit(0, process, global);
	else if (ft_con_num(arg1))
	{
		ft_error_buildin("numeric argument required", arg1, process, 2);
		ft_start_exit(2, process, global);
	}
	else if (process->args[2])
		ft_error_buildin("too many arguments", NULL, process, 1);
	else if (arg1[0] == 0)
	{
		ft_error_buildin("numeric argument required", arg1, process, 2);
		ft_start_exit(2, process, global);
	}
	else
		ft_start_exit(ft_atoi(arg1), process, global);
}
