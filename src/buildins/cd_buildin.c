#include "../../inc/minishell.h"

void	ft_cd_dir_rel(t_process *process)
{
	char	*cwd;
	char	*new_path;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_error_buildin(strerror(errno), process->args[1], process, 1);
		return ;
	}
	new_path = ft_strjoin(cwd, "/");
	free(cwd);
	if (!new_path)
		return ;
	cwd = ft_strjoin(new_path, process->args[1]);
	free(new_path);
	if (!cwd)
		return ;
	if (chdir(cwd) != 0)
		ft_error_buildin(strerror(errno), process->args[1], process, 1);
	free(cwd);
	return ;
}

void	ft_cd_buildin(t_process *process)
{
	char	*tmp;

	if (!process->args[1])
	{
		tmp = getenv("HOME");
		if (!tmp)
		{
			ft_error_buildin("HOME not set", NULL, process, 1);
			return ;
		}
	}
	else if (process->args[1][0] == '/' || process->args[1][0] == '.')
		tmp = process->args[1];
	else
	{
		ft_cd_dir_rel(process);
		return ;
	}
	if (chdir(tmp) != 0)
		ft_error_buildin(strerror(errno), process->args[1], process, 1);
}
