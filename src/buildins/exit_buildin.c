#include "../../inc/minishell.h"

void	ft_exit_buildin(t_process *process)
{
	size_t	ind;
	char	*arg1;

	arg1 = process->args[1];
	if (!arg1)
		exit(1);
	if (process->args[2])
	{
		ft_error_buildin("too many arguments", NULL, process, 1);
		return ;
	}
	ind = 0;
	if (arg1[ind] == '+' || arg1[ind] == '-')
		ind++;
	while (arg1[ind])
	{
		if (!ft_isdigit(arg1[ind]))
		{
			ft_error_buildin("numeric argument required", arg1, process, 1);
			exit(1);
		}
		ind++;
	}
	exit(ft_atoi(arg1));
}
