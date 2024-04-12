#include "../../inc/minishell.h"

void	ft_exec_cmd(t_token *token, t_ast_node *node, char **envp)
{
	char	*cmd;
	char	**args;
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
		if (token->type != TOKEN_ARG)
			break ;
		args = ft_arr_add(token->value, args);
		token = token->next;
	}
	process = ft_create_process(cmd, args, node);
	if (ft_verify_process(process))
		ft_execute_process(process, envp);
	else
		printf("Command not found for %s\n", process->cmd);
}

void	ft_exec_pipes(t_ast_node *node, char **envp)
{
	t_token	*token;
	t_token_type	type;
	int		fd_pipe[2];

	if (!node)
		return ;
	token = node->token;
	type = 0;
	while (token)
	{
		type = token->type;
		if (token->type == TOKEN_PIPE)
		{
			if (pipe(fd_pipe) != 0)
				printf("Handle Error pipe\n");
			node->left->fd_out[PIPE_WRITE] = fd_pipe[PIPE_WRITE];
			node->left->fd_out[PIPE_READ] = fd_pipe[PIPE_READ];
			node->right->fd_in[PIPE_READ] = fd_pipe[PIPE_READ];
			node->right->fd_in[PIPE_WRITE] = fd_pipe[PIPE_WRITE];
		}
		else if (token->type == TOKEN_CMD)
			ft_exec_cmd(token, node, envp);
		// else
		// 	return ;
		token = token->next;
	}
	ft_exec_pipes(node->left, envp);
	ft_exec_pipes(node->right, envp);
	if (type == TOKEN_PIPE)
	{
		ft_close_fd(&node->left->fd_out);
		ft_close_fd(&node->right->fd_in);
	}
	else if (type == TOKEN_CMD)
	{

	}
}

void	ft_execute_nodes(t_ast_node *node, char **envp)
{
	t_token	*token;

	if (!node)
		return ;
	token = node->token;
	while (token)
	{
		if (token->type == TOKEN_PIPE)
		{
			ft_exec_pipes(node, envp);
		}
		// else if (token->type == TOKEN_CMD)
		// 	ft_exec_cmd(token, node, envp);
		token = token->next;
	}
	// ft_execute_nodes(node->left, envp);
	// ft_execute_nodes(node->right, envp);
}

void	ft_exec_all(t_ast_node *node, char **envp)
{
	ft_org_tokens(node);
	// ft_execute_nodes(node, envp);
	ft_exec_pipes(node, envp);
	// ft_wait_for_processes(node);
}
