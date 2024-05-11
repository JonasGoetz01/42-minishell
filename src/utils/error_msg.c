/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 16:24:22 by vscode            #+#    #+#             */
/*   Updated: 2024/05/11 16:24:23 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
