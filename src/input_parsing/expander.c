#include "../../inc/minishell.h"

char	*ft_expand_word(char *word)
{
	char	*env_value;

	if (word[0] == '$')
	{
		if (word[1] == '\0')
			return (word);
		if (word[1] == '?')
			return (ft_itoa(0));
		else
		{
			env_value = get_env(&word[1]);
			free(word);
			if (!env_value)
				return (ft_strdup(""));
			return (ft_strdup(env_value));
		}
	}
	return (word);
}

void	ft_expand_tokens(t_token *tokens)
{
	t_token	*current_token;

	current_token = tokens;
	while (current_token != NULL)
	{
		if (current_token->type == TOKEN_WORD)
			current_token->value = ft_expand_word(current_token->value);
		current_token = current_token->next;
	}
}

// @TODO
// void ft_expand_asterix(t_token *tokens)
