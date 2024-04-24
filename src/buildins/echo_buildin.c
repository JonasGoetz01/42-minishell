#include "../../inc/minishell.h"

static bool	ft_is_new_line(t_process *process, size_t *ind)
{
	bool	new_line;
	size_t	ind_arg;

	new_line = true;
	while (true)
	{
		if (process->args[*ind] == NULL)
			break ;
		if (ft_strncmp(process->args[*ind], "-n", 3) == 0)
			new_line = false;
		else if (ft_strncmp(process->args[*ind], "-n", 2) == 0)
		{
			ind_arg = 2;
			while (process->args[*ind][ind_arg] == 'n')
				ind_arg++;
			if (process->args[*ind][ind_arg] == 0)
				new_line = false;
			else
				break ;
		}
		else
			break ;
		(*ind)++;
	}
	return (new_line);
}

void	ft_echo_buildin(t_process *process)
{
	bool	new_line;
	size_t	ind;

	ind = 1;
	new_line = ft_is_new_line(process, &ind);
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
