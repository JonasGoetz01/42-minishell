/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 20:14:49 by pgrossma          #+#    #+#             */
/*   Updated: 2024/04/11 21:28:46 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_wait_for_processes(t_ast_node *node)
{
	// int		status;
	// pid_t	pid;
	(void)node;

	// status = 0;
	// pid = args->processes[args->process_len - 1]->pid;
	// waitpid(pid, &status, 0);
	while (wait(NULL) > 0)
		;
	// if (WIFEXITED(status))
	// 	return (WEXITSTATUS(status));
	// return (EXIT_FAILURE);
	return (0);
}
