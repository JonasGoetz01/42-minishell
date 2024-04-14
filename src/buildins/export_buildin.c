#include "../../inc/minishell.h"

void	ft_export_buildin(t_process *process, char ***envv)
{
	// char	*name;
	// char	*value;

	if (!process->args[1])
	{
		while (**envv)
		{
			printf("declare -x %s\n", **envv);
			(*envv)++;
		}
		return ;
	}
}
