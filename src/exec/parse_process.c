/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 16:23:33 by vscode            #+#    #+#             */
/*   Updated: 2024/05/11 16:23:34 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_check_cmd_path(char **dirs, char *cmd, int ind)
{
	char	*cmd_path;
	char	*tmp;

	cmd_path = ft_strjoin(dirs[ind], "/");
	if (!cmd_path)
		return (NULL);
	tmp = ft_strjoin(cmd_path, cmd);
	free(cmd_path);
	if (!tmp)
		return (NULL);
	cmd_path = tmp;
	if (!ft_is_directory(cmd_path) && access(cmd_path, F_OK | X_OK) == 0)
		return (cmd_path);
	free(cmd_path);
	return (NULL);
}

static char	*ft_loop_check_path(char *cmd, char *path)
{
	char	**dirs;
	char	*cmd_path;
	size_t	ind;

	dirs = ft_split(path, ':');
	if (dirs == NULL)
		return (NULL);
	ind = 0;
	while (dirs[ind])
	{
		cmd_path = ft_check_cmd_path(dirs, cmd, ind++);
		if (cmd_path)
		{
			ft_arr_free((void **)dirs);
			return (cmd_path);
		}
	}
	ft_arr_free((void **)dirs);
	errno = 0;
	return (NULL);
}

char	*ft_get_cmd_path(char *cmd, char *path)
{
	if (ft_is_directory(cmd) && ft_strncmp(cmd, ".", 2) != 0 && ft_strncmp(cmd,
			"..", 3) != 0)
		return (errno = 21, NULL);
	if (access(cmd, F_OK | X_OK) == 0 && ft_strncmp(cmd, ".", 2) != 0
		&& ft_strncmp(cmd, "..", 3) != 0)
		return (ft_strdup(cmd));
	if (path == NULL || path[0] == 0 || ft_strncmp(cmd, "./", 2) == 0
		|| ft_strncmp(cmd, "../", 3) == 0 || ft_strnstr(cmd, "/",
			ft_strlen(cmd) != 0))
		return (NULL);
	return (ft_loop_check_path(cmd, path));
}

bool	ft_is_buildin_cmd(char *cmd)
{
	return (ft_strncmp(cmd, "echo", 5) == 0 || ft_strncmp(cmd, "cd", 3) == 0
		|| ft_strncmp(cmd, "pwd", 4) == 0 || ft_strncmp(cmd, "export", 7) == 0
		|| ft_strncmp(cmd, "unset", 6) == 0 || ft_strncmp(cmd, "env", 4) == 0
		|| ft_strncmp(cmd, "exit", 5) == 0);
}

bool	ft_verify_process(t_process *process, t_global *global)
{
	char	*new_cmd;
	char	*lc_cmd;
	char	*path;

	if (process->cmd == NULL || process->cmd[0] == '\0')
		return (false);
	if (ft_is_buildin_cmd(process->cmd))
	{
		process->type = PROCESS_BUILDIN;
		return (true);
	}
	lc_cmd = ft_strdup(process->cmd);
	if (!LINUX)
		ft_lower_str(lc_cmd);
	path = ft_get_env("PATH", global->envv);
	new_cmd = ft_get_cmd_path(lc_cmd, path);
	free(lc_cmd);
	if (path)
		free(path);
	if (new_cmd)
	{
		free(process->cmd);
		process->cmd = new_cmd;
	}
	return (new_cmd != NULL);
}
