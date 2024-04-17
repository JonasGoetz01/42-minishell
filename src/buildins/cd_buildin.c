#include "../../inc/minishell.h"

static void	ft_cd_dir_rel(t_process *process)
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

static char	*ft_cd_env(const char *env, t_process *process)
{
	char	*new_pwd;
	char	*err_msg;

	new_pwd = getenv(env);
	if (!new_pwd)
	{
		err_msg = ft_strjoin(env, " not set");
		ft_error_buildin(err_msg, NULL, process, 1);
		free(err_msg);
	}
	return (new_pwd);
}

static void	ft_set_oldpwd(t_global *global)
{
	char	*old_pwd;

	old_pwd = ft_strjoin("OLDPWD=", getenv("PWD"));
	ft_set_env(old_pwd, global);
	free(old_pwd);
}

void	ft_cd_buildin(t_process *process, t_global *global)
{
	char	*tmp;

	if (!process->args[1])
		tmp = ft_cd_env("HOME", process);
	else if (ft_strncmp(process->args[1], "-", 2) == 0)
	{
		tmp = ft_cd_env("OLDPWD", process);
		if (tmp)
			printf("%s\n", tmp);
	}
	else if (process->args[1][0] == '/' || process->args[1][0] == '.')
		tmp = process->args[1];
	else
	{
		ft_set_oldpwd(global);
		ft_cd_dir_rel(process);
		return ;
	}
	ft_set_oldpwd(global);
	if (!tmp)
		return ;
	if (chdir(tmp) != 0)
		ft_error_buildin(strerror(errno), process->args[1], process, 1);
}
