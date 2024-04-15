#include "../../inc/minishell.h"

void	ft_export_buildin(t_process *process, t_global *global)
{
	char	**export_env;

	export_env = global->env_export;
	if (!process->args[1])
	{
		while (*export_env)
		{
			printf("declare -x %s\n", *export_env);
			export_env++;
		}
		return ;
	}
	ft_add_env(process->args[1], global);
}
