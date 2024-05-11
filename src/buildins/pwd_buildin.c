/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_buildin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 16:22:32 by vscode            #+#    #+#             */
/*   Updated: 2024/05/11 16:22:32 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_pwd_buildin(t_process *process)
{
	char	*temp;

	temp = getcwd(NULL, 0);
	if (!temp)
	{
		ft_error_buildin(strerror(errno), NULL, process, 1);
		return ;
	}
	printf("%s\n", temp);
	free(temp);
}
