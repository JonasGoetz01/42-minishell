#include "../../inc/minishell.h"

void	ft_env_buildin(char **envv)
{
	while (*envv)
	{
		printf("%s\n", *envv);
		envv++;
	}
}
