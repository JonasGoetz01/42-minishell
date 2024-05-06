#include "../../inc/minishell.h"

char	*ft_get_env(char *name, char **envv)
{
	char	*value;
	char	**find;

	if (!ft_env_contains(name, envv))
		return (NULL);
	find = ft_find_env(name, envv);
	if (!find)
		return (NULL);
	value = ft_trim_from_equal(*find);
	return (value);
}

bool	ft_set_env_export(char *name, char *value, char ***envv)
{
	if (!ft_env_contains(name, *envv))
		return (ft_add_env_export(name, value, envv));
	return (ft_replace_env_export(name, value, *envv));
}

bool	ft_set_env_env(char *name, char *value, char ***envv)
{
	if (!ft_env_contains(name, *envv))
		return (ft_add_env_env(name, value, envv));
	return (ft_replace_env_env(name, value, *envv));
}

void	ft_unset_env(char *name, t_global *global)
{
	ssize_t	ind;

	if (ft_env_contains(name, global->env_export))
	{
		ind = ft_find_env_ind(name, global->env_export);
		if (!(ind == -1))
		{
			if (!ft_arr_rm(ind, &global->env_export))
				return ;
		}
	}
	if (ft_env_contains(name, global->envv))
	{
		ind = ft_find_env_ind(name, global->envv);
		if (!(ind == -1))
		{
			if (!ft_arr_rm(ind, &global->envv))
				return ;
		}
	}
}
