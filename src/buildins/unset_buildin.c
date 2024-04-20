#include "../../inc/minishell.h"

void	ft_unset_buildin(t_process *process, t_global *global)
{
	size_t	ind;

	if(!process->args[1])
		return ;
	ind = 1;
	while (process->args[ind])
	{
		ft_unset_env(process->args[ind], global);
		ind++;
	}
}
