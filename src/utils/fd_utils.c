#include "../../inc/minishell.h"

void	ft_close_fd(int *fd)
{
	if (*fd != -1)
		close(*fd);
	*fd = -1;
}

void	ft_close_pipes(t_process *process)
{
	if (!process)
		return ;
	ft_close_fd(&process->pipe_fd_in[PIPE_READ]);
	ft_close_fd(&process->pipe_fd_in[PIPE_WRITE]);
	ft_close_fd(&process->pipe_fd_out[PIPE_READ]);
	ft_close_fd(&process->pipe_fd_out[PIPE_WRITE]);
}
