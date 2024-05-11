/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_buildins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 16:22:20 by vscode            #+#    #+#             */
/*   Updated: 2024/05/11 16:22:20 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_error_buildin(const char *msg, const char *arg, t_process *process,
		int exit_status)
{
	process->exit_status = exit_status;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(process->cmd, 2);
	ft_putstr_fd(": ", 2);
	if (arg)
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
}

void	ft_error_buildin_env(const char *arg, t_process *process)
{
	char	*temp;
	char	*str;

	temp = ft_strjoin("\'", arg);
	if (!temp)
		return ;
	str = ft_strjoin(temp, "'");
	free(temp);
	if (!str)
		return ;
	ft_error_buildin("not a valid identifier", str, process, 1);
	free(str);
	process->exit_status = 1;
}
