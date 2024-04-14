#include "../../inc/minishell.h"

void	ft_export_buildin(t_process *process, t_global *global)
{
	// char	*name;
	// char	*value;
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
}
