/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 16:23:06 by vscode            #+#    #+#             */
/*   Updated: 2024/05/11 16:23:07 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	ft_open_in_file(t_ast_node *node, t_global *global)
{
	char	*file_name;
	t_fd	*fd;

	file_name = ft_get_file_name(node);
	fd = ft_add_t_fd(global);
	if (!fd)
		return (false);
	if (file_name == NULL)
	{
		fd->fd_file = -1;
		errno = 11;
	}
	else
		fd->fd_file = open(file_name, O_RDONLY);
	if (fd->fd_file == -1)
	{
		ft_print_error(strerror(errno), file_name);
		fd->fd_file = -2;
	}
	if (node->left)
	{
		if (!node->left->file_in)
			return (node->left->file_in = &fd->fd_file, true);
	}
	return (ft_close_fd(&fd->fd_file), global->exit_status = 1, false);
}

bool	ft_open_out_file(t_ast_node *node, t_global *global)
{
	char	*file_name;
	t_fd	*fd;

	file_name = ft_get_file_name(node);
	fd = ft_add_t_fd(global);
	if (!fd)
		return (false);
	if (file_name == NULL)
	{
		fd->fd_file = -1;
		errno = 11;
	}
	else
		fd->fd_file = open(file_name, O_TRUNC | O_WRONLY | O_CREAT, 0644);
	if (fd->fd_file == -1)
	{
		ft_print_error(strerror(errno), file_name);
		fd->fd_file = -2;
	}
	if (node->left)
	{
		if (!node->left->file_out)
			return (node->left->file_out = &fd->fd_file, true);
	}
	return (ft_close_fd(&fd->fd_file), global->exit_status = 1, false);
}

bool	ft_open_out_append_file(t_ast_node *node, t_global *global)
{
	char	*file_name;
	t_fd	*fd;

	file_name = ft_get_file_name(node);
	fd = ft_add_t_fd(global);
	if (!fd)
		return (false);
	if (file_name == NULL)
	{
		fd->fd_file = -1;
		errno = 11;
	}
	else
		fd->fd_file = open(file_name, O_APPEND | O_WRONLY | O_CREAT, 0644);
	if (fd->fd_file == -1)
	{
		ft_print_error(strerror(errno), file_name);
		fd->fd_file = -2;
	}
	if (node->left)
	{
		if (!node->left->file_out)
			return (node->left->file_out = &fd->fd_file, true);
	}
	return (ft_close_fd(&fd->fd_file), global->exit_status = 1, false);
}
