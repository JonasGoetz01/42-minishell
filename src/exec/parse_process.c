/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 13:46:37 by pgrossma          #+#    #+#             */
/*   Updated: 2024/04/01 18:22:51 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_process	ft_create_process(char *cmd, char **args, int *pipe_fd_in, int *pipe_fd_out)
{
	t_process	process;

	process.cmd = cmd;
	process.args = args;
	process.pipe_fd_in[PIPE_READ] = -1;
	process.pipe_fd_in[PIPE_WRITE] = -1;
	process.pipe_fd_out[PIPE_READ] = -1;
	process.pipe_fd_out[PIPE_WRITE] = -1;
	process.pid = -1;
	return (process);
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

bool	ft_verify_process(t_process *process)
{
	process->cmd = ft_get_cmd_path(process->cmd, get_env("PATH"));
	return (process->cmd != NULL);
}
