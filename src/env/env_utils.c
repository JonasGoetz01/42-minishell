/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 16:23:03 by vscode            #+#    #+#             */
/*   Updated: 2024/05/11 16:23:03 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_trim_to_equal(char *str)
{
	char	*find;
	size_t	ind_equal;

	find = ft_strchr(str, '=');
	if (!find)
		return (ft_strdup(str));
	ind_equal = find - str;
	find = ft_substr(str, 0, ind_equal);
	return (find);
}

char	*ft_trim_from_equal(char *str)
{
	char	*find;
	size_t	ind_equal;

	find = ft_strchr(str, '=');
	if (!find)
		return (NULL);
	ind_equal = find - str;
	find = ft_substr(str, ind_equal + 1, ft_strlen(str));
	return (find);
}

char	**ft_find_env(char *name, char **envv)
{
	char	*temp;

	while (*envv)
	{
		temp = ft_trim_to_equal(*envv);
		if (!temp)
			return (NULL);
		if (ft_strncmp(name, temp, ft_strlen(temp)) == 0)
		{
			free(temp);
			return (envv);
		}
		free(temp);
		envv++;
	}
	return (NULL);
}

ssize_t	ft_find_env_ind(char *name, char **envv)
{
	char	*temp;
	ssize_t	ind;

	ind = 0;
	while (envv[ind])
	{
		temp = ft_trim_to_equal(envv[ind]);
		if (!temp)
			return (-1);
		if (ft_strncmp(name, temp, ft_strlen(temp)) == 0)
		{
			free(temp);
			return (ind);
		}
		free(temp);
		ind++;
	}
	return (-1);
}
