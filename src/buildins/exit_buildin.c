#include "../../inc/minishell.h"

void	ft_exit_buildin(t_process *process)
{
	size_t	ind;
	char	*arg1;

	arg1 = process->args[1];
	if (isatty(fileno(stdin)))
		ft_putstr_fd("exit\n", 1);
	if (!arg1)
		exit(0);
	ind = 0;
	if (arg1[ind] == '+' || arg1[ind] == '-')
		ind++;
	while (arg1[ind])
	{
		if (!ft_isdigit(arg1[ind]))
		{
			ft_error_buildin("numeric argument required", arg1, process, 2);
			exit(2);
		}
		ind++;
	}
	if (process->args[2])
	{
		ft_error_buildin("too many arguments", NULL, process, 1);
		return ;
	}
	if (arg1[0] == 0)
	{
		ft_error_buildin("numeric argument required", arg1, process, 2);
		exit(2);
	}
	exit(ft_atoi(arg1));
}
