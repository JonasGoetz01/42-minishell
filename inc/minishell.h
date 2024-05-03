#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft/libft.h"
# include "colors.h"
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/select.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <unistd.h>

# ifndef DEBUG
// !!!change in makefile!!!
#  define DEBUG 1
# endif
# define LINUX 1

# include <readline/history.h>
# include <readline/readline.h>

# define MAX_BUFFER_SIZE 4096

# define PIPE_READ 0
# define PIPE_WRITE 1

typedef enum e_g_signal
{
	SIGNAL_NONE,
	SIGNAL_INT
}				t_g_signal;

extern t_g_signal	g_signal;

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
	TOKEN_ARG,
	TOKEN_SPACE,
	TOKEN_IGNORE
}						t_token_type;

typedef struct s_token
{
	t_token_type		type;
	char				*value;
	struct s_token		*next;
	struct s_token		*prev;
}						t_token;

typedef struct s_fd
{
	int			fd_file;
	int			fd_pipe[2];
	struct s_fd	*next;
}				t_fd;

typedef enum e_process_type
{
	PROCESS_BUILDIN,
	PROCESS_BUILDIN_FORK,
	PROCESS_FORK
}						t_process_type;

typedef struct s_process
{
	t_process_type		type;
	int					*file_in;
	int					*fd_out[2];
	int					*fd_in[2];
	int					*file_out;
	char				*cmd;
	char				**args;
	pid_t				pid;
	int					exit_status;
	struct s_ast_node	*ast;
}						t_process;

typedef struct s_stack_new
{
	t_token				*top;
}						t_stack;

typedef struct s_ast_node
{
	t_token				*token;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
	int					*file_in;
	int					*(fd_out[2]);
	int					*(fd_in[2]);
	int					*file_out;
	int					exit_status;
	t_process			*process;
}						t_ast_node;

typedef struct s_global
{
	bool				should_exit;
	int					exit_status;
	char				**envv;
	char				**env_export;
	t_fd				*fds;
	bool				isatty;
}						t_global;

typedef struct s_exec_flags
{
	bool				wait;
	bool				next_wait;
	bool				exit_on_err;
	t_token_type		tok_typ;
	t_ast_node			*ast;
}						t_exec_flags;


int						show_prompt(t_global *global);
void					ft_init_t_global(t_global *global, char **envv);

void					handle_sigint(int sig);
void					handle_exec(int sig);
void					handle_sigint_heredoc(int sig);

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
void					ft_error_buildin_env(const char *arg,
							t_process *process);
void					ft_cd_buildin(t_process *process, t_global *global);
void					ft_echo_buildin(t_process *process);
void					ft_exit_buildin(t_process *process, t_global *global);
void					ft_export_buildin(t_process *process, t_global *global);
void					ft_unset_buildin(t_process *process, t_global *global);
bool					ft_env_contains(char *name, char **env);
bool					ft_set_env_export(char *name, char *value,
							char ***envv);
bool					ft_set_env_env(char *name, char *value, char ***envv);
bool					ft_add_env_export(char *name, char *value,
							char ***envv);
bool					ft_add_env_env(char *name, char *value, char ***envv);
void					ft_unset_env(char *name, t_global *global);
char					*ft_get_env(char *name, char **envv);
char					*ft_trim_to_equal(char *str);
char					*ft_trim_from_equal(char *str);
bool					ft_is_valid_identifier(char *str);
char					*ft_get_file_name(t_ast_node *node);
char					**ft_fill_args(t_token *token, char *cmd);
void					ft_handle_verify_process_error(t_process *process);
bool					ft_exec_tokens_loop(t_ast_node *node, t_token *token,
							t_exec_flags *exec_flags, t_global *global);
int						ft_wait_pid(pid_t pid);

t_token					*tokenize(const char *input);

t_token					*postfixFromTokens(t_token *tokens);
int						precedence_node(t_ast_node *node);
int						precedence(t_token token);

int						validator(char *input);

t_token					*create_token(t_token_type type, char *value);
void					free_tokens(t_token *tokens);
void					append_token(t_token **head, t_token *new_token);
size_t					token_count(t_token *tokens);
int						token_length(const char *input, const char *delimiters);
void					ft_expand_tokens(t_token *tokens, t_global *global);
void					ft_open_in_file(t_ast_node *node, t_global *global);
void					ft_open_out_file(t_ast_node *node, t_global *global);
void					ft_open_out_append_file(t_ast_node *node,
							t_global *global);
void					ft_exec_here_doc(t_ast_node *node, t_ast_node *ast, t_global *global);
void					ft_wait_for_processes(t_ast_node *node,
							t_global *global);
void					ft_set_right_exit_code(t_ast_node *node,
							t_global *global);
bool					ft_handle_pipe_token(t_ast_node *node,
							t_global *global);

void					ft_close_fd(int *fd);
void					ft_close_fd_node(t_ast_node *node);
void					ft_close_all_fds(t_global *global);
t_fd					*ft_add_t_fd(t_global *global);
int						ft_get_fd(int *fd);

void					ft_org_tokens(t_ast_node *token);
void					ft_execute_process(t_process *process,
							t_global *global);
void					ft_exec_all(t_ast_node *token, t_global *global);
t_process				*ft_create_process(char *cmd, char **args,
							t_ast_node *node, t_ast_node *ast);
bool					ft_verify_process(t_process *process, t_global *global);
bool					ft_exec_buildin_in_fork(t_process *process);
void					ft_execute_child_process(t_process *process, t_global *global);

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

int						input_validation(t_token **tokens);

void					retokenize(t_token **tokens);

void					ft_print_error(const char *msg, const char *arg);

void					free_token(t_token **tokens);

bool					ft_is_directory(const char *path);
int						isOperator(t_token token);

bool					next_is_operator(t_token *token);
bool					next_is_word(t_token *token);
bool					next_is_newline(t_token *token);
bool					next_is_quotes(t_token *token);
bool					next_is_brackets(t_token *token);

void					ft_free_nodes(t_ast_node *node);
void					ft_free_global(t_global *global);
void					prev_link_list(t_token **tokens);

#endif
