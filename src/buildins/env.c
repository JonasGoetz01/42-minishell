#include "../../inc/minishell.h"

void	print_envs(char **envv)
{
	while (*envv)
	{
		printf("%s\n", *envv);
		envv++;
	}
}

char	*get_env(char *env)
{
	return (getenv(env));
}
