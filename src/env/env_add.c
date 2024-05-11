/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 16:22:43 by vscode            #+#    #+#             */
/*   Updated: 2024/05/11 16:22:44 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	ft_add_env_export(char *name, char *value, char ***envv)
{
	char	*temp;
	char	*str;

	temp = ft_strdup(name);
	if (!temp)
		return (false);
	if (!value)
		return (ft_arr_add(temp, envv));
	str = ft_strjoin(temp, "=\"");
	free(temp);
	if (!str)
		return (false);
	temp = ft_strjoin(str, value);
	free(str);
	if (!temp)
		return (false);
	str = ft_strjoin(temp, "\"");
	free(temp);
	if (str == NULL)
		return (false);
	return (ft_arr_add(str, envv));
}

bool	ft_add_env_env(char *name, char *value, char ***envv)
{
	char	*temp;
	char	*str;

	if (!value)
		return (false);
	temp = ft_strdup(name);
	if (!temp)
		return (false);
	str = ft_strjoin(temp, "=");
	free(temp);
	if (!str)
		return (false);
	temp = ft_strjoin(str, value);
	free(str);
	if (!temp)
		return (false);
	return (ft_arr_add(temp, envv));
}
