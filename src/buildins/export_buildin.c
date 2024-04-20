#include "../../inc/minishell.h"

static void	ft_add_env(char *str, t_global *global)
{
	char	*name;
	char	*value;

	name = ft_trim_to_equal(str);
	if (!name)
		return ;
	if (ft_env_contains(name, global->env_export))
		return ;
	value = ft_trim_from_equal(str);
	ft_add_env_export(name, value, &global->env_export);
	ft_add_env_env(name, value, &global->envv);
	free(name);
	if (value)
		free(value);
}

void	ft_export_buildin(t_process *process, t_global *global)
{
	char	**export_env;
	size_t	ind;

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
	ind = 1;
	while (process->args[ind])
	{
		ft_add_env(process->args[ind], global);
		ind++;
	}
}
