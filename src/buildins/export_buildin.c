#include "../../inc/minishell.h"
#include <stdlib.h>

static void	ft_export_value(t_process *process, t_global *global)
{
	char	*find;
	char	*name;
	char	*value;
	size_t	ind_equal;
	char	**temp;

	if (ft_env_contains(process->args[1], global->env_export))
		{
			printf("return\n");
		return ;
		}
	temp = ft_arr_add(process->args[1], global->env_export);
	if (!temp)
		return ;
	global->env_export = temp;
	find = ft_strchr(process->args[1], '=');
	if (!find)
		return ;
	ind_equal = find - process->args[1];
	name = ft_substr(process->args[1], 0, ind_equal);
	if (!name)
		return ;
	if (ft_env_contains(name, global->env_export))
		return ;
	value = ft_substr(process->args[1], ind_equal + 1, ft_strlen(process->args[1]));
	if (!value)
	{
		free(name);
		return ;
	}
	setenv(name, value, 0);
	temp = ft_arr_add(process->args[1], global->envv);
	if (temp)
		global->envv = temp;
	free(name);
	free(value);
}

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
	ft_export_value(process, global);
}
