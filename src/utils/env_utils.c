#include "../../inc/minishell.h"

bool	ft_env_contains(char *str, char **env)
{
	char	*find;
	size_t	ind_equal;

	while (*env)
	{
		find = ft_strchr(*env, '=');
		if (find)
			ind_equal = find - *env - 1;
		else
			ind_equal = ft_strlen(str);
		printf("%s\n", str);
		if (ft_strncmp(*env, str, ind_equal) == 0)
			return (true);
		env++;
	}
	return (false);
}
