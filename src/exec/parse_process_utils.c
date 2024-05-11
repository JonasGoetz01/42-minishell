/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_process_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 16:23:37 by vscode            #+#    #+#             */
/*   Updated: 2024/05/11 16:23:37 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_process	*ft_create_process(char *cmd, char **args, t_ast_node *node,
		t_ast_node *ast)
{
	t_process	*process;

	process = malloc(sizeof(t_process));
	if (process == NULL)
		return (NULL);
	process->type = PROCESS_FORK;
	process->cmd = ft_strdup(cmd);
	process->args = args;
	process->file_in = node->file_in;
	process->fd_in[PIPE_READ] = node->fd_in[PIPE_READ];
	process->fd_in[PIPE_WRITE] = node->fd_in[PIPE_WRITE];
	process->fd_out[PIPE_READ] = node->fd_out[PIPE_READ];
	process->fd_out[PIPE_WRITE] = node->fd_out[PIPE_WRITE];
	process->file_out = node->file_out;
	process->pid = -1;
	process->exit_status = -1;
	process->ast = ast;
	return (process);
}
