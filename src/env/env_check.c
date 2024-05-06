#include "../../inc/minishell.h"

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
		if (len_str == ft_strlen(find_temp)
			&& ft_strncmp(find_temp, name, len_str + 1) == 0)
			return (free(find_temp), true);
		free(find_temp);
		env++;
	}
	return (false);
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
