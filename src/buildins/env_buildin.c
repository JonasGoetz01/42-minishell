#include "../../inc/minishell.h"

void	ft_env_buildin(char **envv)
{
	if (LINUX)
		ft_arr_sort(envv);
	while (*envv)
	{
		printf("%s\n", *envv);
		envv++;
	}
}
