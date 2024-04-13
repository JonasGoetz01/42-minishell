#include "../../inc/minishell.h"

void	ft_cd_dir_rel(t_process *process)
{
	(void) process;
	return ;
}

void	ft_cd_buildin(t_process *process)
{
	char	*tmp;

	if (!process->args[1])
	{
		tmp = getenv("HOME");
		if (!tmp)
		{
			ft_error_buildin("HOME not set", NULL, process, 1);
			return ;
		}
	}
	else if (process->args[1][0] == '/')
		tmp = process->args[0];
	else
	{
		ft_cd_dir_rel(process);
		return ;
	}
	if (chdir(tmp) != 0)
		ft_error_buildin("No such file or directory", process->args[1], process, 1);
}
