#include "../../inc/minishell.h"

char	*ft_expand_word(char *word, t_global *global)
{
	char	*env_value;

	if (word[0] == '$')
	{
		if (word[1] == '\0')
			return (word);
		if (word[1] == '?')
			return (ft_itoa(global->exit_status));
		else
		{
			env_value = ft_get_env(&word[1], global->envv);
			free(word);
			if (!env_value)
				return (ft_strdup(""));
			return (env_value);
		}
	}
	return (word);
}

void	ft_expand_tokens(t_token *tokens, t_global *global)
{
	t_token	*current_token;
	int		in_single_quotes;

	current_token = tokens;
	in_single_quotes = 0;
	while (current_token != NULL)
	{
		if (current_token->type == TOKEN_SINGLE_QUOTE)
			in_single_quotes = !in_single_quotes;
		if (current_token->type == TOKEN_WORD && !in_single_quotes)
			current_token->value = ft_expand_word(current_token->value, global);
		current_token = current_token->next;
	}
}

// @TODO
// void ft_expand_asterix(t_token *tokens)
