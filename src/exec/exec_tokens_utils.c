#include "../../inc/minishell.h"

static t_process	*ft_exec_cmd(t_token *token,
									t_ast_node *node, t_ast_node *ast, t_global *global)
{
	char		*cmd;
	char		**args;
	t_process	*process;

	cmd = token->value;
	args = ft_fill_args(token, cmd);
	process = ft_create_process(cmd, args, node, ast);
	if (process == NULL)
		return (NULL);
	if (DEBUG)
		printf("executing %s: in %d out %d\n", process->cmd,
			ft_get_fd(process->fd_in[PIPE_READ]),
			ft_get_fd(process->fd_out[PIPE_WRITE]));
	if (ft_verify_process(process, global))
	{
		ft_execute_process(process, global);
		ft_close_fd(node->fd_in[PIPE_READ]);
		ft_close_fd(node->fd_in[PIPE_WRITE]);
		ft_close_fd(node->file_in);
		ft_close_fd(node->file_out);
	}
	else
		ft_handle_verify_process_error(process);
	node->exit_status = process->exit_status;
	return (process);
}

static void	ft_parseon_fds(t_ast_node *node,
	t_token_type type, t_exec_flags *exec_flags)
{
	if (type == TOKEN_LESS || type == TOKEN_DOUBLE_LESS)
	{
		if (node->right)
		{
			node->right->fd_in[PIPE_READ] = node->fd_in[PIPE_READ];
			node->right->fd_in[PIPE_WRITE] = node->fd_in[PIPE_WRITE];
		}
		if (node->left)
		{
			node->left->fd_out[PIPE_READ] = node->fd_out[PIPE_READ];
			node->left->fd_out[PIPE_WRITE] = node->fd_out[PIPE_WRITE];
		}
		exec_flags->wait = false;
	}
	else if (type == TOKEN_GREATER || type == TOKEN_DOUBLE_GREATER)
	{
		if (node->left)
		{
			node->left->fd_in[PIPE_READ] = node->fd_in[PIPE_READ];
			node->left->fd_in[PIPE_WRITE] = node->fd_in[PIPE_WRITE];
			node->left->file_out = node->file_out;
		}
		exec_flags->wait = false;
	}
}

static bool	ft_handle_redirects(t_ast_node *node, t_global *global,
	t_token_type type, t_exec_flags *exec_flags)
{
	if (type == TOKEN_LESS)
		ft_open_in_file(node, global);
	else if (type == TOKEN_GREATER)
		ft_open_out_file(node, global);
	else if (type == TOKEN_DOUBLE_GREATER)
		ft_open_out_append_file(node, global);
	else if (type == TOKEN_DOUBLE_LESS)
		ft_exec_here_doc(node, exec_flags->ast, global);
	else if (type == TOKEN_DOUBLE_PIPE)
		exec_flags->wait = false;
	else if (type == TOKEN_DOUBLE_AMPERSAND)
	{
		exec_flags->wait = false;
		exec_flags->exit_on_err = true;
	}
	else
		return (false);
	return (true);
}

bool	ft_exec_tokens_loop(t_ast_node *node, t_token *token,
	t_exec_flags *exec_flags, t_global *global)
{
	while (token)
	{
		exec_flags->tok_typ = token->type;
		ft_parseon_fds(node, exec_flags->tok_typ, exec_flags);
		if (ft_handle_redirects(node, global, exec_flags->tok_typ, exec_flags))
			;
		else if (exec_flags->tok_typ == TOKEN_PIPE)
		{
			if (!ft_handle_pipe_token(node, global))
				return (false);
			exec_flags->next_wait = false;
		}
		else if (exec_flags->tok_typ == TOKEN_CMD && ft_get_fd(node->file_in) != -2
			&& ft_get_fd(node->file_out) != -2 && !node->process)
			node->process = ft_exec_cmd(token, node, exec_flags->ast, global);
		else if (exec_flags->tok_typ == TOKEN_CMD
			&& (ft_get_fd(node->file_in) == -2
				|| ft_get_fd(node->file_out) == -2)
			&& !node->process)
			node->exit_status = 1;
		token = token->next;
	}
	return (true);
}
