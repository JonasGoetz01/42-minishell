#include "../../inc/minishell.h"

void	ft_export_buildin(t_process *process, char **envp)
{
	char	*name;
	char	*value;

	if (!process->args[1])
	{
		while (*envp)
		{
			printf("declare -x %s\n", *envp);
			envp++;
		}
		return ;
	}
}
