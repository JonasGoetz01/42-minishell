#include "../../inc/minishell.h"

void	ft_exec_cmd(t_token *token, char **envp)
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
	process = ft_create_process(cmd, args);
	if (ft_verify_process(process))
		ft_execute_process(process, envp);
	else
		printf("Command not found for %s\n", process->cmd);
}

void	ft_execute_nodes(t_ast_node *node, char **envp)
{
	t_token	*token;

	if (!node)
		return ;
	token = node->token;
	while (token)
	{
		if (token->type == TOKEN_CMD)
			ft_exec_cmd(token, envp);
		token = token->next;
	}
	ft_execute_nodes(node->left, envp);
	ft_execute_nodes(node->right, envp);
}

void	ft_exec_all(t_ast_node *node, char **envp)
{
	ft_org_tokens(node);
	ft_execute_nodes(node, envp);
}
