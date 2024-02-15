/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgotz <jgotz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 18:47:15 by jgotz             #+#    #+#             */
/*   Updated: 2024/02/14 21:09:58 by jgotz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft/libft.h"
# include "colors.h"
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/select.h>
# include <unistd.h>

# define EXIT_ERROR 1

# include <readline/history.h>
# include <readline/readline.h>

typedef enum operation
{
	REDIRECT,
	PIPE
}					t_operation;

typedef struct s_node_data
{
	t_operation		op;
}					t_node_data;

typedef struct s_node
{
	t_node_data		data;
	struct s_node	*left;
	struct s_node	*right;
}					t_node;

int					show_prompt(char **envv);

char				*get_current_dir(void);

void				change_dir(char *path);

void				handle_sigint(int sig);

void				print_envs(char **envv);

#endif