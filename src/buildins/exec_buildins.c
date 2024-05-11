/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_buildins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 16:22:04 by vscode            #+#    #+#             */
/*   Updated: 2024/05/11 16:22:05 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_exec_buildins(t_process *process, t_global *global)
{
	if (ft_strncmp(process->cmd, "echo", 5) == 0)
		ft_echo_buildin(process);
	else if (ft_strncmp(process->cmd, "cd", 3) == 0)
		ft_cd_buildin(process, global);
	else if (ft_strncmp(process->cmd, "pwd", 4) == 0)
		ft_pwd_buildin(process);
	else if (ft_strncmp(process->cmd, "export", 7) == 0)
		ft_export_buildin(process, global);
	else if (ft_strncmp(process->cmd, "unset", 6) == 0)
		ft_unset_buildin(process, global);
	else if (ft_strncmp(process->cmd, "env", 4) == 0)
		ft_env_buildin(global->envv);
	else if (ft_strncmp(process->cmd, "exit", 5) == 0)
		ft_exit_buildin(process, global);
	if (process->exit_status == -1)
		process->exit_status = 0;
}
