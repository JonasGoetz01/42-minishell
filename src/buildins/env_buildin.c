/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_buildin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 16:22:01 by vscode            #+#    #+#             */
/*   Updated: 2024/05/11 16:22:01 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_env_buildin(char **envv)
{
	if (LINUX)
		ft_arr_sort(envv);
	while (*envv)
	{
		printf("%s\n", *envv);
		envv++;
	}
}
