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
	int		start;
	int		end;
	char	*temp;

	current_token = tokens;
	in_single_quotes = 0;
	while (current_token != NULL)
	{
		if (current_token->type == TOKEN_SINGLE_QUOTE)
			in_single_quotes = !in_single_quotes;
		if (current_token->type == TOKEN_WORD && !in_single_quotes)
		{
			start = 0;
			while (current_token->value[start] != '$'
				&& current_token->value[start] != '\0')
				start++;
			if (current_token->value[start] == '\0')
				break ;
			end = start;
			if (current_token->value[end] == '$')
				end++;
			while (current_token->value[end] != '\0'
				&& current_token->value[end] != ' '
				&& current_token->value[end] != '?'
				&& current_token->value[end] != '$')
				end++;
			if (current_token->value[end] == ' '
				|| current_token->value[end] == '$')
				end--;
			temp = ft_strdup("");
			temp = ft_strjoin(temp, ft_substr(current_token->value, 0, start));
			temp = ft_strjoin(temp,
					ft_expand_word(ft_substr(current_token->value, start, end
							- start + 1), global));
			temp = ft_strjoin(temp, ft_strdup(&current_token->value[end + 1]));
			free(current_token->value);
			current_token->value = temp;
			if (start != end)
				ft_expand_tokens(tokens, global);
		}
		current_token = current_token->next;
	}
}

// @TODO
// void ft_expand_asterix(t_token *tokens)
