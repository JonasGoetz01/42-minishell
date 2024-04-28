#include "../../inc/minishell.h"

char	*ft_get_file_name(t_ast_node *node)
{
	if (node->right)
	{
		if (node->right->token)
		{
			return (node->right->token->value);
		}
	}
	return (NULL);
}

static char	**ft_init_args_arr(char *cmd)
{
	char	**args;

	args = ft_arr_create_len(2);
	if (args == NULL)
		return (NULL);
	args[0] = ft_strdup(cmd);
	if (args[0] == NULL)
	{
		ft_arr_free((void **) args);
		return (NULL);
	}
	return (args);
}

char	**ft_fill_args(t_token *token, char *cmd)
{
	char	**args;
	char	*tmp;

	args = ft_init_args_arr(cmd);
	if (args == NULL)
		return (NULL);
	token = token->next;
	while (token)
	{
		if (token->type == TOKEN_ARG)
		{
			tmp = ft_strdup(token->value);
			if (tmp == NULL)
				return (ft_arr_free((void **) args), NULL);
			if (!ft_arr_add(tmp, &args))
			{
				ft_arr_free((void **) args);
				return (NULL);
			}
		}
		token = token->next;
	}
	return (args);
}

void	ft_handle_verify_process_error(t_process *process)
{
	if (errno != 0)
	{
		ft_print_error(strerror(errno), process->cmd);
		if (errno != 21 && errno != 13)
			process->exit_status = 127;
		else
			process->exit_status = 126;
	}
	else
	{
		ft_print_error("command not found", process->cmd);
		process->exit_status = 127;
	}
}
