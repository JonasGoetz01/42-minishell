/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 16:24:32 by vscode            #+#    #+#             */
/*   Updated: 2024/05/11 16:24:33 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static bool	ft_env_cpy(char **src, char ***dst)
{
	char	*name;
	char	*value;
	bool	result;

	while (*src)
	{
		name = ft_trim_to_equal(*src);
		value = ft_trim_from_equal(*src);
		if (!name || !value)
		{
			if (name)
				free(name);
			if (value)
				free(value);
			return (false);
		}
		result = ft_add_env_export(name, value, dst);
		free(name);
		free(value);
		if (!result)
			return (false);
		src++;
	}
	return (true);
}

void	ft_increase_shlvl(t_global *global)
{
	int		shlvl;
	char	*var;
	char	*value;

	var = ft_get_env("SHLVL", global->envv);
	if (var == NULL)
		shlvl = 1;
	else
	{
		shlvl = ft_atoi(var);
		shlvl++;
		if (shlvl < 0)
			shlvl = 0;
		else if (shlvl >= 999)
		{
			shlvl = 1;
			ft_print_error("shell level (1000) too high, resetting to 1",
				"warning");
		}
	}
	value = ft_itoa(shlvl);
	ft_set_env_env("SHLVL", value, &global->envv);
	ft_set_env_export("SHLVL", value, &global->env_export);
	free(value);
	free(var);
}

void	ft_init_t_global(t_global *global, char **envv)
{
	global->should_exit = false;
	global->envv = ft_arr_create_len(ft_arr_len(envv) + 1);
	if (global->envv == NULL)
		exit(1);
	if (!ft_arr_cpy(envv, global->envv))
		return (free(global->envv), exit(1));
	global->env_export = ft_arr_create();
	if (!global->env_export)
		return (ft_arr_free((void **)global->envv), exit(1));
	if (!ft_env_cpy(global->envv, &global->env_export))
		return (free(global->envv), ft_arr_free((void **)global->envv),
			exit(1));
	ft_unset_env("_", global);
	global->exit_status = 0;
	global->old_exit_status = 0;
	global->fds = NULL;
	global->isatty = isatty(STDIN_FILENO);
}
