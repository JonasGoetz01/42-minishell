/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 16:24:19 by vscode            #+#    #+#             */
/*   Updated: 2024/05/11 16:24:20 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	ft_free_process(t_process *process)
{
	if (process == NULL)
		return ;
	free(process->cmd);
	ft_arr_free((void **)process->args);
	free(process);
}

void	ft_free_nodes(t_ast_node *node)
{
	if (node == NULL)
		return ;
	ft_free_nodes(node->left);
	ft_free_nodes(node->right);
	ft_free_process(node->process);
	free_tokens(node->token);
	free(node);
}

void	ft_free_global(t_global *global)
{
	ft_arr_free((void **)global->envv);
	ft_arr_free((void **)global->env_export);
}
