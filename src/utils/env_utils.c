#include "../../inc/minishell.h"

char	*ft_trim_to_equal(char *str)
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

char	*ft_trim_from_equal(char *str)
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

bool	ft_env_contains(char *name, char **env)
{
	char	*find_temp;
	size_t	len_str;

	len_str = ft_strlen(name);
	while (*env)
	{
		find_temp = ft_trim_to_equal(*env);
		if (!find_temp)
			return (true);
		if (len_str == ft_strlen(find_temp) && ft_strncmp(find_temp, name, len_str + 1) == 0)
			return (free(find_temp), true);
		free(find_temp);
		env++;
	}
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

bool	ft_add_env_export(char *name, char *value, char ***envv)
{
	char	*temp;
	char	*str;

	temp = ft_strdup(name);
	if (!temp)
		return (false);
	if (!value)
		return (ft_add_env_arr(temp, envv));
	str = ft_strjoin(temp, "=\"");
	free(temp);
	if (!str)
		return (false);
	temp = ft_strjoin(str, value);
	free(str);
	if (!temp)
		return (false);
	str = ft_strjoin(temp, "\"");
	free(temp);
	if (!str)
		return (false);
	return (ft_add_env_arr(str, envv));
}

bool	ft_add_env_env(char *name, char *value, char ***envv)
{
	char	*temp;
	char	*str;

	if (!value)
		return false;
	temp = ft_strdup(name);
	if (!temp)
		return (false);
	str = ft_strjoin(temp, "=");
	free(temp);
	if (!str)
		return (false);
	temp = ft_strjoin(str, value);
	free(str);
	if (!temp)
		return (false);
	return (ft_add_env_arr(temp, envv));
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

bool	ft_replace_env_export(char *name, char *value, char **envv)
{
	char	*temp;
	char	*str;

	temp = ft_strdup(name);
	if (!temp)
		return (false);
	if (!value)
		return (ft_replace_env(name, temp, envv));
	str = ft_strjoin(temp, "=\"");
	free(temp);
	if (!str)
		return (false);
	temp = ft_strjoin(str, value);
	free(str);
	if (!temp)
		return (false);
	str = ft_strjoin(temp, "\"");
	free(temp);
	if (!str)
		return (false);
	return (ft_replace_env(name, str, envv));
}

bool	ft_replace_env_env(char *name, char *value, char **envv)
{
	char	*temp;
	char	*str;

	if (!value)
		return false;
	temp = ft_strdup(name);
	if (!temp)
		return (false);
	str = ft_strjoin(temp, "=");
	free(temp);
	if (!str)
		return (false);
	temp = ft_strjoin(str, value);
	free(str);
	if (!temp)
		return (false);
	return (ft_replace_env(name, temp, envv));
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
	ssize_t ind;

	if (ft_env_contains(name, global->env_export))
	{
		ind = ft_find_env_ind(name, global->env_export);
		if (!(ind == -1))
			global->env_export = ft_arr_rm(ind, global->env_export);
	}
	if (ft_env_contains(name, global->envv))
	{
		ind = ft_find_env_ind(name, global->envv);
		if (!(ind == -1))
			global->envv = ft_arr_rm(ind, global->envv);
	}
}

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

bool	ft_is_valid_identifier(char *str)
{
	char	*name;
	size_t	ind;

	name = ft_trim_to_equal(str);
	if (!name)
		return (false);
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (free(name), false);
	ind = 0;
	while (name[ind])
	{
		if (!ft_isalnum(name[ind]) && name[ind] != '_')
			return (free(name), false);
		ind++;
	}
	return (free(name), true);
}
