#include "../../inc/minishell.h"

static char	*ft_trim_to_equal(char *str)
{
	char	*find;
	size_t	ind_equal;

	find = ft_strchr(str, '=');
	if (!find)
		return (ft_strdup(str));
	ind_equal = find - str;
	find = ft_substr(str, 0, ind_equal);
	return (find);
}

static char	*ft_trim_from_equal(char *str)
{
	char	*find;
	size_t	ind_equal;

	find = ft_strchr(str, '=');
	if (!find)
		return (NULL);
	ind_equal = find - str;
	find = ft_substr(str, ind_equal + 1, ft_strlen(str));
	return (find);
}

bool	ft_env_contains(char *str, char **env)
{
	char	*find_temp;
	size_t	len_str;

	str = ft_trim_to_equal(str);
	if (!str)
		return (true);
	len_str = ft_strlen(str);
	while (*env)
	{
		find_temp = ft_trim_to_equal(*env);
		if (!find_temp)
		{
			free(str);
			return (true);
		}
		if (len_str == ft_strlen(find_temp) && ft_strncmp(find_temp, str, len_str + 1) == 0)
		{
			free(find_temp);
			free(str);
			return (true);
		}
		free(find_temp);
		env++;
	}
	free(str);
	return (false);
}

static bool	ft_add_env_arr(char *str, char ***envv)
{
	char	**temp;

	temp = ft_arr_add(str, *envv);
	if (!temp)
		return (false);
	*envv = temp;
	return (true);
}

bool	ft_add_env(char *str, t_global *global)
{
	char	*name;
	char	*value;

	if (ft_env_contains(str, global->env_export))
		return (false);
	if (!ft_add_env_arr(str, &global->env_export))
		return (false);
	if (ft_strchr(str, '=') == NULL)
		return (true);
	if (!ft_add_env_arr(str, &global->envv))
		return (false);
	name = ft_trim_to_equal(str);
	value = ft_trim_from_equal(str);
	if (!name || !value)
		return (false);
	return (setenv(name, value, 0) == 0);
}

static char	**ft_find_env(char *name, char **envv)
{
	char	*temp;

	while (*envv)
	{
		temp = ft_trim_to_equal(*envv);
		if (!temp)
			return (NULL);
		if (ft_strncmp(name, temp, ft_strlen(temp)) == 0)
		{
			free(temp);
			return (envv);
		}
		free(temp);
		envv++;
	}
	return (NULL);
}

static ssize_t ft_find_env_ind(char *name, char **envv)
{
	char	*temp;
	ssize_t	ind;

	ind = 0;
	while (envv[ind])
	{
		temp = ft_trim_to_equal(envv[ind]);
		if (!temp)
			return (-1);
		if (ft_strncmp(name, temp, ft_strlen(temp)) == 0)
		{
			free(temp);
			return (ind);
		}
		free(temp);
		ind++;
	}
	return (-1);
}

static bool ft_replace_env(char *name, char *str, char **envv)
{
	char	**line;
	char	*old_line;

	line = ft_find_env(name, envv);
	if (!line)
		return (false);
	old_line = *line;
	*line = ft_strdup(str);
	if (!line)
	{
		*line = old_line;
		free(name);
		return (false);
	}
	free(old_line);
	return (true);
}

bool	ft_set_env(char *str, t_global *global)
{
	char	*name;
	char	*value;
	bool	result;

	if (!ft_env_contains(str, global->env_export))
		return (ft_add_env(str, global));
	name = ft_trim_to_equal(str);
	if (!ft_replace_env(name, str, global->env_export))
	{
		free(name);
		return (false);
	}
	if (ft_env_contains(name, global->envv))
	{
		if (!ft_replace_env(name, str, global->envv))
		{
			free(name);
			return (false);
		}
	}
	else
		ft_add_env_arr(str, &global->envv);
	value = ft_trim_from_equal(str);
	if (!name || !value)
		return (false);
	result = (setenv(name, value, 1) == 0);
	free(name);
	free(value);
	return (result);
}

void	ft_unset_env(char *str, t_global *global)
{
	ssize_t ind;
	char	*name;

	if (ft_env_contains(str, global->env_export))
	{
		ind = ft_find_env_ind(str, global->env_export);
		if (!(ind == -1))
			global->env_export = ft_arr_rm(ind, global->env_export);
	}
	if (ft_env_contains(str, global->envv))
	{
		ind = ft_find_env_ind(str, global->envv);
		if (!(ind == -1))
			global->envv = ft_arr_rm(ind, global->envv);
		name = ft_trim_to_equal(str);
		if (name)
			unsetenv(name);
	}
}
