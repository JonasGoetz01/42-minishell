#include "../../inc/minishell.h"

static size_t	ft_count_equals(char *str)
{
	size_t	count;

	if (str == NULL)
		return (0);
	count = 0;
	while (*str)
	{
		count++;
		str++;
	}
	return (count);
}

static void	ft_set_env(char *name, char *value, t_token *token, t_process *process, t_global *global)
{
	char	*trim_name;
	char	*trim_value;

	if (ft_count_equals(name) + ft_count_equals(value) > 1)
		return ;
	trim_name = ft_trim_to_equal(name);
	trim_value = NULL;
	if (trim_name == NULL)
		return ;
	if (ft_is_valid_identifier(trim_name))
	{
		if (value == NULL)
			value = ft_trim_from_equal(name);
		else
		{
			trim_value = ft_trim_from_equal(value);
			if (trim_value != NULL)
				value = trim_value;
		}
		ft_set_env_env(trim_name, value, &global->envv);
		ft_set_env_export(trim_name, value, &global->env_export);
	}
	else
		ft_error_buildin_env(token->value, process);
	free(trim_name);
	if (trim_value != NULL)
		free(trim_value);
}

static bool	ft_ignore_equals(t_token *token)
{
	if (ft_strncmp(token->value, "=", 2) == 0)
	{
		if (token->next)
			return (token->next->type == TOKEN_SINGLE_QUOTE || token->next->type == TOKEN_DOUBLE_QUOTE);
	}
	return (false);
}

static bool	ft_next_token_invalid(t_token *token)
{
	if (token->next)
	{
		token = token->next;
		return (token->type == TOKEN_SPACE);
	}
	return (true);
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
			if (!ft_ignore_equals(token))
			{
				if (name == NULL)
					name = token->value;
				else
					value = token->value;
			}
		}
		if (ft_next_token_invalid(token))
		{
			if (name != NULL)
				ft_set_env(name, value, token, process, global);
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
