#include "../../inc/minishell.h"

void	ft_echo_buildin(t_process *process)
{
	bool	new_line;
	size_t	ind;

	ind = 1;
	new_line = true;
	while (true)
	{
		if (process->args[ind] == NULL)
			break ;
		if (ft_strncmp(process->args[ind], "-n", 3) == 0)
			new_line = false;
		else
			break ;
		ind++;
	}
	while (process->args[ind])
	{
		printf("%s", process->args[ind]);
		if (process->args[ind + 1])
			printf(" ");
		ind++;
	}
	if (new_line)
		printf("\n");
}
