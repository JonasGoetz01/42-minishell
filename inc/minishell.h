#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/history.h>
# include <readline/readline.h>
# include "../lib/libft/libft.h"
# include "colors.h"
# include "exec.h"
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/select.h>
# include <sys/wait.h>
# include <unistd.h>
# include <string.h>

# define EXIT_ERROR 1
# define DEBUG 1


# define MAX_BUFFER_SIZE 4096

typedef enum e_token_type
{
	TOKEN_WORD,
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
	TOKEN_CMD,
	TOKEN_ARG
}						t_token_type;

typedef struct s_token
{
	t_token_type		type;
	char				*value;
	struct s_token		*next;
}						t_token;

typedef struct s_stack_new
{
	t_token				*top;
}						t_stack;

typedef struct s_ast_node
{
	t_token				*token;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
	int					fd_out[2];
	int					fd_in[2];
	t_process			*process;
}						t_ast_node;

typedef struct s_global
{
	int					exit_status;
	char				**envv;
	char				**env_export;
}						t_global;

int						show_prompt(t_global *global);
void					ft_init_t_global(t_global *global, char **envv);

void					handle_sigint(int sig);
void					handle_sigquit(int sig);

void					ft_env_buildin(char **envv);
void					ft_pwd_buildin(t_process *process);
char					*get_hostname(void);
void					print_tokens(t_token *tokens);
void					print_tokens_value(t_token *tokens);
void					remove_unused_spaces(t_token **tokens);
char					*execute_command(const char *command);
bool					ft_is_buildin_cmd(char *cmd);
void					ft_exec_buildins(t_process *process, t_global *global);
void					ft_error_buildin(const char *msg, const char *arg,
							t_process *process, int exit_status);
void					ft_cd_buildin(t_process *process);
void					ft_echo_buildin(t_process *process);
void					ft_exit_buildin(t_process *process);
void					ft_export_buildin(t_process *process, t_global *global);
bool					ft_env_contains(char *str, char **env);

t_token					*tokenize(const char *input);

t_token					*postfixFromTokens(t_token *tokens);
int						precedence_node(t_ast_node *node);
int						precedence(t_token token);

int						validator(char *input);

t_token					*create_token(t_token_type type, char *value);
void					free_tokens(t_token *tokens);
void					append_token(t_token **head, t_token *new_token);
size_t					token_count(t_token *tokens);
void					ft_expand_tokens(t_token *tokens, t_global *global);

void					ft_close_fd(int *fd);
void					ft_close_fd_process(t_process *process);
void					ft_close_fd_node(t_ast_node *node);

void					ft_org_tokens(t_ast_node *token);
void					ft_execute_process(t_process *process, t_global *global);
void					ft_exec_all(t_ast_node *token, t_global *global);
t_process				*ft_create_process(char *cmd, char **args,
							t_ast_node *node);
bool					ft_verify_process(t_process *process);
int						ft_wait_for_processes(t_ast_node *node);

//----
t_stack					*create_stack(void);
void					stack_push(t_stack *stack, t_token token);
t_token					stack_pop(t_stack *stack);
t_token					stack_pop(t_stack *stack);
t_token					stack_peek(t_stack *stack);
int						stack_is_not_empty(t_stack *stack);

void					*ft_recalloc(void *ptr, size_t old_size,
							size_t new_size);

void					gen_ast(t_ast_node **root, t_token *tokens);
void					print_ast(t_ast_node **root, int level);

void					rearrange_tokens(t_token **tokens);

void					combine_words_in_quotes(t_token **tokens);

#endif
