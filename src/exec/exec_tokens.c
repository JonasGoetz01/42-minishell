#include "../../inc/minishell.h"

t_process	*ft_exec_cmd(t_token *token, t_ast_node *node, t_global *global)
{
	char		*cmd;
	char		**args;
	t_process	*process;

	cmd = token->value;
	args = ft_arr_create_len(2);
	// ToDo Error
	// if (!args)
	args[0] = ft_strdup(cmd);
	// ToDo Error
	// if (!args[0])
	token = token->next;
	while (token)
	{
		if (token->type == TOKEN_ARG)
			args = ft_arr_add(token->value, args);
		token = token->next;
	}
	process = ft_create_process(cmd, args, node);
	if (DEBUG)
		printf("executing %s: in %d out %d\n", process->cmd, process->pipe_fd_in[PIPE_READ], process->pipe_fd_out[PIPE_WRITE]);
	if (ft_verify_process(process, global))
	{
		ft_execute_process(process, global);
		ft_close_fd(&node->fd_in[PIPE_READ]);
		ft_close_fd(&node->fd_in[PIPE_WRITE]);
		ft_close_fd(&node->file_in);
		ft_close_fd(&node->file_out);
	}
	else
		printf("minishell: %s: command not found\n", process->cmd);
	node->exit_status = process->exit_status;
	return (process);
}

void	ft_execute_nodes(t_ast_node *node, bool wait, t_global *global)
{
	t_token			*token;
	t_token_type	type;
	int				fd_pipe[2];
	bool			next_wait;
	bool			exit_on_err;

	if (!node)
		return ;
	next_wait = wait;
	exit_on_err = false;
	token = node->token;
	while (token)
	{
		type = token->type;
		if (type == TOKEN_LESS || type == TOKEN_DOUBLE_LESS)
		{
			node->right->fd_in[PIPE_READ] = node->fd_in[PIPE_READ];
			node->right->fd_in[PIPE_WRITE] = node->fd_in[PIPE_WRITE];
			node->left->fd_out[PIPE_READ] = node->fd_out[PIPE_READ];
			node->left->fd_out[PIPE_WRITE] = node->fd_out[PIPE_WRITE];
		}
		else if (type == TOKEN_GREATER || type == TOKEN_DOUBLE_GREATER)
		{
			node->left->fd_in[PIPE_READ] = node->fd_in[PIPE_READ];
			node->left->fd_in[PIPE_WRITE] = node->fd_in[PIPE_WRITE];
		}
		if (type == TOKEN_LESS)
			ft_open_in_file(node);
		else if (type == TOKEN_GREATER)
			ft_open_out_file(node);
		else if (type == TOKEN_DOUBLE_GREATER)
			ft_open_out_append_file(node);
		else if(type == TOKEN_DOUBLE_LESS)
			ft_exec_here_doc(node);
		else if (type == TOKEN_DOUBLE_PIPE)
			wait = false;
		else if (type == TOKEN_DOUBLE_AMPERSAND)
		{
			wait = false;
			exit_on_err = true;
		}
		else if (type == TOKEN_PIPE)
		{
			if (pipe(fd_pipe) != 0)
			{
				printf("Handle Error pipe\n");
				return ;
			}
			node->left->fd_out[PIPE_WRITE] = fd_pipe[PIPE_WRITE];
			node->left->fd_out[PIPE_READ] = fd_pipe[PIPE_READ];
			node->right->fd_in[PIPE_READ] = fd_pipe[PIPE_READ];
			node->right->fd_in[PIPE_WRITE] = fd_pipe[PIPE_WRITE];
			node->left->fd_in[PIPE_READ] = node->fd_in[PIPE_READ];
			node->left->fd_in[PIPE_WRITE] = node->fd_in[PIPE_WRITE];
			node->right->fd_out[PIPE_READ] = node->fd_out[PIPE_READ];
			node->right->fd_out[PIPE_WRITE] = node->fd_out[PIPE_WRITE];
			next_wait = false;
		}
		else if (type == TOKEN_CMD && node->file_in != -2 && node->file_out != -2 && !node->process)
			node->process = ft_exec_cmd(token, node, global);
		else if (type == TOKEN_CMD && (node->file_in == -2 || node->file_out == -2) && !node->process)
			node->exit_status = 1;
		token = token->next;
	}
	ft_execute_nodes(node->left, next_wait, global);
	ft_set_right_exit_code(node, global);
	if (exit_on_err && global->exit_status >= 1)
		return ;
	if (type == TOKEN_DOUBLE_PIPE && global->exit_status == 0)
		return ;
	ft_execute_nodes(node->right, next_wait, global);
	if (wait)
		ft_wait_for_processes(node, global);
	ft_set_right_exit_code(node, global);
}

void	ft_exec_all(t_ast_node *node, t_global *global)
{
	ft_org_tokens(node);
	print_ast(&node, 0);
	ft_execute_nodes(node, true, global);
}
