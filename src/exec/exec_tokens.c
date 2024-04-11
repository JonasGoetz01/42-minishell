#include "../../inc/minishell.h"

void	ft_exec_cmd(t_token *token)
{
	char	*cmd;
	char	**args;
	// t_process	*process;

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
		printf("%s\n", token->value);
		args = ft_arr_add(token->value, args);
		token = token->next;
	}
	// process = ft_create_process(cmd, args);
	// ft_execute_process(process, NULL);
}

void	ft_execute_tokens(t_token *token)
{
	ft_org_tokens(token);
	print_tokens(token);
	while (token)
	{
		if (token->type == TOKEN_CMD)
			ft_exec_cmd(token);
		token = token->next;
	}
}
