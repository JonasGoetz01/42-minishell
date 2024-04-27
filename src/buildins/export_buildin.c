#include "../../inc/minishell.h"

static void	ft_set_env(char *name, char *value, t_global *global)
{
	ft_set_env_env(name, value, &global->envv);
	ft_set_env_export(name, value, &global->env_export);
}

static void	ft_loop_args(t_process *process, t_global *global)
{
	t_token	*token;
	char	*name;
	char	*value;

	name = NULL;
	value = NULL;
	token = process->token;
	while (token)
	{
		if (token->type == TOKEN_ARG)
		{
			if (token->value[0] != '=')
			{
				if (name == NULL)
					name = token->value;
				else
					value = token->value;
			}
		}
		else if (token->type != TOKEN_SINGLE_QUOTE && token->type != TOKEN_DOUBLE_QUOTE)
		{
			if (name != NULL)
			{
				if (ft_is_valid_identifier(name))
					ft_set_env(name, value, global);
				else
					ft_error_buildin_env(token->value, process);
			}
			name = NULL;
			value = NULL;
		}
		token = token->next;
	}
}

void	ft_export_buildin(t_process *process, t_global *global)
{
	char	**export_env;

	export_env = global->env_export;
	if (!process->args[1])
	{
		while (*export_env)
		{
			printf("declare -x %s\n", *export_env);
			export_env++;
		}
		return ;
	}
	ft_loop_args(process, global);
}
