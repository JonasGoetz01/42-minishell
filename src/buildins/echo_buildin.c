#include "../../inc/minishell.h"

void	ft_echo_buildin(t_process *process)
{
	bool	new_line;
	size_t	ind;

	if (process->args[1])
		new_line = (ft_strncmp(process->args[1], "-n", 3) != 0);
	else
		new_line = true;
	ind = 1;
	if (!new_line)
		ind++;
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
