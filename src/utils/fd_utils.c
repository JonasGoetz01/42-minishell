/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 15:27:53 by pgrossma          #+#    #+#             */
/*   Updated: 2024/04/01 13:38:56 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
