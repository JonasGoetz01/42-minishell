/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_buildin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 16:22:39 by vscode            #+#    #+#             */
/*   Updated: 2024/05/11 16:22:39 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_unset_buildin(t_process *process, t_global *global)
{
	size_t	ind;

	if (!process->args[1])
		return ;
	ind = 1;
	while (process->args[ind])
	{
		ft_unset_env(process->args[ind], global);
		ind++;
	}
}
