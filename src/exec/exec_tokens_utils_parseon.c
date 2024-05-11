/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tokens_utils_parseon.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 16:49:58 by pgrossma          #+#    #+#             */
/*   Updated: 2024/05/11 16:50:00 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	ft_parseon_less(t_ast_node *node, t_exec_flags *exec_flags)
{
	if (node->left)
	{
		node->left->fd_out[PIPE_READ] = node->fd_out[PIPE_READ];
		node->left->fd_out[PIPE_WRITE] = node->fd_out[PIPE_WRITE];
		node->left->file_out = node->file_out;
	}
	exec_flags->wait = false;
}

static void	ft_parseon_greater(t_ast_node *node, t_exec_flags *exec_flags)
{
	if (node->left)
	{
		node->left->fd_in[PIPE_READ] = node->fd_in[PIPE_READ];
		node->left->fd_in[PIPE_WRITE] = node->fd_in[PIPE_WRITE];
		node->left->file_out = node->file_out;
	}
	exec_flags->wait = false;
}

static void	ft_parseon_ambersand(t_ast_node *node)
{
	if (node->left)
	{
		node->left->fd_out[PIPE_READ] = node->fd_out[PIPE_READ];
		node->left->fd_out[PIPE_WRITE] = node->fd_out[PIPE_WRITE];
		node->left->file_out = node->file_out;
	}
	if (node->right)
	{
		node->right->fd_out[PIPE_READ] = node->fd_out[PIPE_READ];
		node->right->fd_out[PIPE_WRITE] = node->fd_out[PIPE_WRITE];
		node->right->file_out = node->file_out;
	}
}

void	ft_parseon_fds(t_ast_node *node, t_token_type type,
		t_exec_flags *exec_flags)
{
	if (type == TOKEN_LESS || type == TOKEN_DOUBLE_LESS)
		ft_parseon_less(node, exec_flags);
	else if (type == TOKEN_GREATER || type == TOKEN_DOUBLE_GREATER)
		ft_parseon_greater(node, exec_flags);
	else if (type == TOKEN_DOUBLE_AMPERSAND)
		ft_parseon_ambersand(node);
}
