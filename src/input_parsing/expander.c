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
	t_token	*tmp;
	t_token	*prev;
	int		in_single_quotes;
	int		in_double_quotes;
	int		start;
	int		end;
	char	*temp;
	int 	finish;

	current_token = tokens;
	in_single_quotes = 0;
	in_double_quotes = 0;
	prev = NULL;
	while (current_token != NULL)
	{
		if (current_token->type == TOKEN_SINGLE_QUOTE)
			in_single_quotes = !in_single_quotes;
		if (current_token->type == TOKEN_DOUBLE_QUOTE)
			in_double_quotes = !in_double_quotes;
		if (current_token->type == TOKEN_WORD && !in_single_quotes)
		{
			while (current_token && current_token->value && (ft_strchr(current_token->value, '$') || (ft_strchr(current_token->value, '~') && !in_double_quotes)))
			{
				if (ft_strlen(current_token->value) == 1 && (current_token->value[0] == '$') && (current_token->next && (current_token->next->value[0] == '\'' || current_token->next->value[0] == '\"')))
				{
					// Remove the dollar sign ('$')
					if (current_token->next->type == TOKEN_SINGLE_QUOTE && ft_strlen(current_token->value) == 1)
						in_single_quotes = !in_single_quotes;
					if (current_token->next->type == TOKEN_DOUBLE_QUOTE && ft_strlen(current_token->value) == 1)
						in_double_quotes = !in_double_quotes;
					tmp = current_token;
					current_token = current_token->next;
					free(tmp->value);
					free(tmp);
					if (!prev)
						tokens = current_token;
					else
						prev->next = current_token;
					break;
				}
				if (ft_strchr(current_token->value, '$') && ft_strlen(current_token->value) > 1 && !ft_strchr(current_token->value, '~') && !in_single_quotes)
				{
					if (ft_strlen(current_token->value) == 1 && (!current_token->next || current_token->next->value[0] == ' ' || current_token->next->value[0] == '\0'))
					{
						if (current_token->next)
						{
							current_token = current_token->next;
							continue ;
						}
						else
							break ;
					}
					start = ft_strchr(current_token->value, '$')
						- current_token->value;
					start++;
					end = start;
					while (current_token->value[end]
						&& (ft_isalnum(current_token->value[end]) 
						|| current_token->value[end] == '?' 
						|| current_token->value[end] == '_'))
						end++;
					if (end - start == 0)
					{
						finish = 0;
						while (current_token && current_token->next
							&& (current_token->type != TOKEN_WORD
								|| ft_strchr(current_token->value, '$') != NULL) && !in_single_quotes)
						{
							prev = current_token;
							current_token = current_token->next;
							if (!current_token)
								break ;
							if (current_token->type == TOKEN_SINGLE_QUOTE)
								in_single_quotes = !in_single_quotes;
							if (current_token->type == TOKEN_DOUBLE_QUOTE)
								in_double_quotes = !in_double_quotes;
							finish = 1;
						}
						if (finish && current_token && current_token->next && current_token->next->next && !in_single_quotes)
						{
							tmp = current_token->next->next;
							if (current_token->next->type == TOKEN_SINGLE_QUOTE)
								in_single_quotes = !in_single_quotes;
							if (current_token->next->type == TOKEN_DOUBLE_QUOTE)
								in_double_quotes = !in_double_quotes;
							free(current_token->next->value);
							free(current_token->next);
							current_token->next = tmp;
							finish = 0;
						}
						break ;
					}
					if (prev && prev->type == TOKEN_SINGLE_QUOTE)
					{
						in_single_quotes = !in_single_quotes;
						prev = current_token;
						current_token = current_token->next;
						continue;
					}
					temp = ft_substr(current_token->value, 0, start - 1);
					temp = ft_strjoin(temp,
							ft_expand_word(ft_substr(current_token->value, start
									- 1, end - (start - 1)), global));
					temp = ft_strjoin(temp, &current_token->value[end]);
					free(current_token->value);
					current_token->value = ft_strdup(temp);
					if (current_token->value[0] == '\0')
						current_token->type = TOKEN_WORD;
					free(temp);
				}
				if (ft_strchr(current_token->value, '~') && !ft_strchr(current_token->value, '$') && !in_single_quotes)
				{
					start = ft_strchr(current_token->value, '~')
						- current_token->value;
					temp = ft_substr(current_token->value, 0, start);
					temp = ft_strjoin(temp, ft_get_env("HOME", global->envv));
					temp = ft_strjoin(temp, &current_token->value[start + 1]);
					free(current_token->value);
					current_token->value = ft_strdup(temp);
					if (current_token->value[0] == '\0')
						current_token->type = TOKEN_WORD;
					free(temp);
				}
				if (ft_strlen(current_token->value) <= 1)
				{
					prev = current_token;
					current_token = current_token->next;
				}
			}
		}
		if (current_token)
		{
			prev = current_token;
			current_token = current_token->next;
		}
	}
	current_token = tokens;
	while (current_token != NULL)
	{
		if (current_token->next && current_token->next->type == TOKEN_WORD 
			&& ft_strlen(current_token->next->value) == 1 
			&& current_token->next->value[0] == '$' && ft_strlen(current_token->next->value) > 1)
		{
			if (!current_token->next->next)
				break ;
			temp = ft_expand_word(ft_strjoin("$", current_token->next->next->value), global) ;
			free(current_token->next->value);
			current_token->next->value = ft_strdup(temp);
			if (current_token->next->value[0] == '\0')
						current_token->type = TOKEN_WORD;
			// free(temp);
			tmp = current_token->next->next->next;
			if (current_token->next->type == TOKEN_SINGLE_QUOTE)
				in_single_quotes = !in_single_quotes;
			if (current_token->next->type == TOKEN_DOUBLE_QUOTE)
				in_double_quotes = !in_double_quotes;
			free(current_token->next->next->value);
			free(current_token->next->next);
			current_token->next->next = tmp;
		}
		prev = current_token;
		current_token = current_token->next;
	}
}

// @TODO
// void ft_expand_asterix(t_token *tokens)
