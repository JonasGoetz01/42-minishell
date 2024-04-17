#include "../../inc/minishell.h"

void	ft_unset_buildin(t_process *process, t_global *global)
{
	if(!process->args[1])
		return ;
	ft_unset_env(process->args[1], global);
}
