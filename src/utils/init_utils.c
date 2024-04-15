#include "../../inc/minishell.h"

void	ft_init_t_global(t_global *global, char **envv)
{
	global->envv = ft_arr_create_len(ft_arr_len(envv) + 1);
	if (!global->envv)
		exit(1);
	ft_arr_cpy(envv, global->envv);
	global->env_export = ft_arr_create_len(ft_arr_len(envv) + 1);
	if (!global->env_export)
		exit(1);
	ft_arr_cpy(envv, global->env_export);
}
