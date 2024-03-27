/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 20:47:06 by jgotz             #+#    #+#             */
/*   Updated: 2024/03/27 15:06:53 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_envs(char **envv)
{
	while (*envv)
	{
		printf("%s\n", *envv);
		envv++;
	}
}

char	*get_env(char *env)
{
	return (getenv(env));
}

char	*ft_check_cmd_path(char **dirs, char *cmd, int ind)
{
	char	*cmd_path;
	char	*tmp;

	cmd_path = ft_strjoin(dirs[ind], "/");
	if (!cmd_path)
	{
		ft_free_array((void **) dirs);
		// ft_exit_error(args, "malloc failed");
	}
	tmp = ft_strjoin(cmd_path, cmd);
	free(cmd_path);
	if (!tmp)
	{
		ft_free_array((void **) dirs);
		// ft_exit_error(args, "malloc failed");
	}
	cmd_path = tmp;
	if (access(cmd_path, F_OK | X_OK) == 0)
		return (cmd_path);
	free(cmd_path);
	return (NULL);
}

char	*ft_get_cmd_path(char *cmd, char *path)
{
	char	**dirs;
	char	*cmd_path;
	int		ind;

	if (access(cmd, F_OK | X_OK) == 0)
		return (ft_strdup(cmd));
	dirs = ft_split(path, ':');
	ind = 0;
	while (dirs[ind])
	{
		cmd_path = ft_check_cmd_path(dirs, cmd, ind);
		if (cmd_path)
		{
			ft_free_array((void **) dirs);
			return (cmd_path);
		}
		ind++;
	}
	ft_free_array((void **) dirs);
	return (NULL);
}
