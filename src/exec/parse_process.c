#include "../../inc/minishell.h"

t_process	*ft_create_process(char *cmd, char **args, t_ast_node *node)
{
	t_process	*process;

	process = malloc(sizeof(t_process));
	process->is_buildin = false;
	process->cmd = cmd;
	process->args = args;
	process->pipe_fd_in[PIPE_READ] = node->fd_in[PIPE_READ];
	process->pipe_fd_in[PIPE_WRITE] = node->fd_in[PIPE_WRITE];
	process->pipe_fd_out[PIPE_READ] = node->fd_out[PIPE_READ];
	process->pipe_fd_out[PIPE_WRITE] = node->fd_out[PIPE_WRITE];
	process->pid = -1;
	process->exit_status = -1;
	return (process);
}

char	*ft_check_cmd_path(char **dirs, char *cmd, int ind)
{
	char	*cmd_path;
	char	*tmp;

	cmd_path = ft_strjoin(dirs[ind], "/");
	if (!cmd_path)
	{
		ft_arr_free((void **)dirs);
		// ft_exit_error(args, "malloc failed");
	}
	tmp = ft_strjoin(cmd_path, cmd);
	free(cmd_path);
	if (!tmp)
	{
		ft_arr_free((void **)dirs);
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
			ft_arr_free((void **)dirs);
			return (cmd_path);
		}
		ind++;
	}
	ft_arr_free((void **)dirs);
	return (NULL);
}

bool	ft_is_buildin_cmd(char *cmd)
{
	return (ft_strncmp(cmd, "echo", 5) == 0 ||
			ft_strncmp(cmd, "cd", 3) == 0 ||
			ft_strncmp(cmd, "pwd", 4) == 0 ||
			ft_strncmp(cmd, "export", 7) == 0 ||
			ft_strncmp(cmd, "unset", 6) == 0 ||
			ft_strncmp(cmd, "env", 4) == 0 ||
			ft_strncmp(cmd, "exit", 5) == 0);
}

bool	ft_verify_process(t_process *process)
{
	char	*new_cmd;

	if (ft_is_buildin_cmd(process->cmd))
	{
		process->is_buildin = true;
		return (true);
	}
	new_cmd = ft_get_cmd_path(process->cmd, getenv("PATH"));
	if (new_cmd)
	{
		free(process->cmd);
		process->cmd = new_cmd;
	}
	else
		process->exit_status = 127;
	return (new_cmd != NULL);
}
