/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgotz <jgotz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 18:47:15 by jgotz             #+#    #+#             */
/*   Updated: 2024/03/09 12:50:34 by jgotz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft/libft.h"
# include "colors.h"
# include "stack.h"
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/select.h>
# include <unistd.h>

# define EXIT_ERROR 1

# include <readline/history.h>
# include <readline/readline.h>

typedef enum e_token_type
{
	TOKEN_NUMBER,
	TOKEN_PLUS,
	TOKEN_MINUS,
	TOKEN_MULT,
	TOKEN_DIV,
	TOKEN_BRACKET_L,
	TOKEN_BRACKET_R
}					t_token_type;

typedef struct s_token
{
	t_token_type	type;
	int				value;
}					t_token;

int					show_prompt(char **envv);

char				*get_current_dir(void);
void				change_dir(char *path);

void				handle_sigint(int sig);

void				print_envs(char **envv);
void				print_tokens(t_token *tokens, int numTokens);

t_token				*tokenize(const char *input, int *numTokens);
t_stack				*toPostFix(t_token *tokens, int numTokens);

#endif