/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgotz <jgotz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 18:47:15 by jgotz             #+#    #+#             */
/*   Updated: 2024/02/22 12:51:32 by jgotz            ###   ########.fr       */
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

// typedef enum operation
// {
// 	REDIRECT,
// 	PIPE
// }					t_operation;

// typedef struct s_node_data
// {
// 	t_operation		op;
// }					t_node_data;

// typedef struct s_node
// {
// 	t_node_data		data;
// 	struct s_node	*left;
// 	struct s_node	*right;
// }					t_node;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT
}						t_token_type;

typedef struct s_token
{
	t_token_type		type;
	char				*value;
}						t_token;

typedef struct s_ast_node
{
	t_token_type		type;
	char				*value;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}						t_ast_node;

int						show_prompt(char **envv);

char					*get_current_dir(void);

void					change_dir(char *path);

void					handle_sigint(int sig);

void					print_envs(char **envv);

void					print_tokens(char *input);

t_token					*tokenize(const char *input, int *numTokens);
t_ast_node				*buildAST(t_token *tokens, int numTokens, int *depth);
void					printAST(t_ast_node *root, int depth);

#endif