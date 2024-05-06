#include "../../inc/minishell.h"

bool	ft_replace_env(char *name, char *str, char **envv)
{
	char	**line;
	char	*old_line;

	line = ft_find_env(name, envv);
	if (!line)
		return (false);
	old_line = *line;
	*line = str;
	if (!line)
	{
		*line = old_line;
		return (false);
	}
	free(old_line);
	return (true);
}

bool	ft_replace_env_export(char *name, char *value, char **envv)
{
	char	*temp;
	char	*str;

	if (value == NULL)
		return (false);
	temp = ft_strdup(name);
	if (!temp)
		return (false);
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

	if (value == NULL)
		return (false);
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
