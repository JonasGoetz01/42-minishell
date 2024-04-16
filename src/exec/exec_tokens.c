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
	if (ft_verify_process(process))
		ft_execute_process(process, global);
	else
		printf("minishell: %s: command not found\n", process->cmd);
	return (process);
}

void	ft_execute_nodes(t_ast_node *node, t_global *global)
{
	t_token	*token;
	int		fd_pipe[2];

	if (!node)
		return ;
	token = node->token;
	while (token)
	{
		if (token->type == TOKEN_LESS || token->type == TOKEN_GREATER || token->type == TOKEN_DOUBLE_GREATER)
		{
			node->right->fd_in[PIPE_READ] = node->fd_in[PIPE_READ];
			node->right->fd_in[PIPE_WRITE] = node->fd_in[PIPE_WRITE];
			node->left->fd_out[PIPE_READ] = node->fd_out[PIPE_READ];
			node->left->fd_out[PIPE_WRITE] = node->fd_out[PIPE_WRITE];
		}
		if (token->type == TOKEN_LESS)
			ft_open_in_file(node);
		else if (token->type == TOKEN_GREATER)
			ft_open_out_file(node);
		else if (token->type == TOKEN_DOUBLE_GREATER)
			ft_open_out_append_file(node);
		else if (token->type == TOKEN_PIPE)
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
		}
		else if (token->type == TOKEN_CMD && node->fd_in[PIPE_READ] != -2 && node->fd_out[PIPE_WRITE] != -2)
			node->process = ft_exec_cmd(token, node, global);
		token = token->next;
	}
	ft_execute_nodes(node->left, global);
	ft_execute_nodes(node->right, global);
	if (node->process)
	{
		if (!node->process->is_buildin)
			waitpid(node->process->pid, &node->process->exit_status, 0);
		global->exit_status = node->process->exit_status;
		ft_close_fd(&(node->process->pipe_fd_out[PIPE_WRITE]));
	}
}

void	ft_exec_all(t_ast_node *node, t_global *global)
{
	ft_org_tokens(node);
	if (DEBUG)
		print_ast(&node, 0);
	ft_execute_nodes(node, global);
}
