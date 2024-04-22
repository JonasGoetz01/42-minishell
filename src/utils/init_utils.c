#include "../../inc/minishell.h"

static bool	ft_env_cpy(char **src, char ***dst)
{
	char	*name;
	char	*value;
	bool	result;

	while (*src)
	{
		name = ft_trim_to_equal(*src);
		value = ft_trim_from_equal(*src);
		if (!name || !value)
		{
			if (name)
				free(name);
			if (value)
				free(value);
			return (false);
		}
		result = ft_add_env_export(name, value, dst);
		free(name);
		free(value);
		if (!result)
			return (false);
		src++;
	}
	return (true);
}

void	ft_init_t_global(t_global *global, char **envv)
{
	global->envv = ft_arr_create_len(ft_arr_len(envv) + 1);
	if (!global->envv)
		exit(1);
	ft_arr_cpy(envv, global->envv);
	global->env_export = ft_arr_create();
	if (!global->env_export)
		exit(1);
	ft_env_cpy(global->envv, &global->env_export);
	global->exit_status = 0;
}
