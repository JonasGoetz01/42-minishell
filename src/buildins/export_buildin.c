#include "../../inc/minishell.h"

static void	ft_set_env(char *str, t_process *process, t_global *global)
{
	char	*name;
	char	*value;

	if (ft_is_valid_identifier(str))
	{
		name = ft_trim_to_equal(str);
		if (name == NULL)
			return ;
		value = ft_trim_from_equal(str);
		ft_set_env_env(name, value, &global->envv);
		ft_set_env_export(name, value, &global->env_export);
		free(name);
		if (value != NULL)
			free(value);
	}
	else
		ft_error_buildin_env(str, process);
}

void	ft_export_buildin(t_process *process, t_global *global)
{
	char	**export_env;
	size_t	ind;

	export_env = global->env_export;
	if (!process->args[1])
	{
		if (LINUX)
			ft_arr_sort(export_env);
		while (*export_env)
		{
			printf("declare -x %s\n", *export_env);
			export_env++;
		}
		return ;
	}
	ind = 1;
	while (process->args[ind])
	{
		ft_set_env(process->args[ind], process, global);
		ind++;
	}
}
