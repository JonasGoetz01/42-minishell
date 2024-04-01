/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 18:47:15 by jgotz             #+#    #+#             */
/*   Updated: 2024/04/01 13:37:36 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft/libft.h"
# include "colors.h"
# include "pipes.h"
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/select.h>
# include <unistd.h>
# include <stdbool.h>

# define EXIT_ERROR 1

# include <readline/history.h>
# include <readline/readline.h>

# define MAX_BUFFER_SIZE 4096

typedef enum e_token_type
{
	TOKEN_NUMBER,
	TOKEN_WORD,
	TOKEN_PLUS,
	TOKEN_MINUS,
	TOKEN_MULT,
	TOKEN_DIV,
	TOKEN_BRACKET_L,
	TOKEN_BRACKET_R,
	TOKEN_DOUBLE_LESS,
	TOKEN_LESS,
	TOKEN_GREATER,
	TOKEN_DOUBLE_GREATER,
	TOKEN_DOUBLE_PIPE,
	TOKEN_PIPE,
	TOKEN_AMPERSAND,
	TOKEN_DOUBLE_AMPERSAND,
	TOKEN_DOUBLE_QUOTE,
	TOKEN_SINGLE_QUOTE,
	TOKEN_SEMICOLON,
}						t_token_type;

typedef struct s_token
{
	t_token_type		type;
	char				*value;
	struct s_token		*next;
}						t_token;

typedef struct s_stack
{
	struct s_token		*array;
	size_t				capacity;
	size_t				size;
}						t_stack;

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
void					handle_sigquit(int sig);

void					print_envs(char **envv);
char					*get_env(char *env);
char					*get_hostname(void);
void					print_tokens(t_token *tokens);
void					print_tokens_value(t_token *tokens);
void					remove_unused_spaces(t_token **tokens);
char					*execute_command(const char *command);

t_token					*tokenize(const char *input);
t_stack					*toPostFix(t_token *tokens, int numTokens);
t_ast_node				*parse_tokens_to_ast(t_token *tokens);
void					print_ast_execution_order(t_ast_node *root);

t_token					*postfixFromTokens(t_token *tokens);
int						precedence_node(t_ast_node *node);
int						precedence(t_token token);

t_stack					*createStack(size_t capacity);
void					push(t_stack *stack, t_token token);
t_token					pop(t_stack *stack);
t_token					peek(const t_stack *stack);
void					freeStack(t_stack *stack);

int						validator(char *input);

t_token					*create_token(t_token_type type, char *value);
void					free_tokens(t_token *tokens);
void					append_token(t_token **head, t_token *new_token);
size_t					token_count(t_token *tokens);

void					ft_close_fd(int *fd);

#endif
