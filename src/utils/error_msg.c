#include "../../inc/minishell.h"

void	ft_print_error(const char *msg, const char *arg)
{
	ft_putstr_fd("minishell: ", 2);
	if (arg)
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
}

bool	ft_is_debug(t_global *global)
{
	return (DEBUG || (ft_get_env("DEBUG", global->envv) && ft_get_env("DEBUG",
				global->envv)[0] == '1'));
}
