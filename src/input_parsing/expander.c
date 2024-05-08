#include "../../inc/minishell.h"

char	*ft_expand_word(char *word, t_global *global)
{
	char	*env_value;

	if (word[0] == '$')
	{
		if (word[1] == '\0')
			return (word);
		if (word[1] == '?')
			return (ft_itoa(global->old_exit_status));
		else
		{
			env_value = ft_get_env(&word[1], global->envv);
			free(word);
			word = NULL;
			if (!env_value)
				return (ft_strdup(""));
			return (env_value);
		}
	}
	if (word[0] == '~')
	{
		if (word[1] == '\0' || word[1] == '/')
			return (ft_get_env("HOME", global->envv));
	}
	return (word);
}

// void	ft_expand_tokens(t_token *tokens, t_global *global)
// {
// 	t_token	*current_token;
// 	t_token	*tmp;
// 	t_token	*prev;
// 	int		in_single_quotes;
// 	int		in_double_quotes;
// 	int		start;
// 	int		end;
// 	char	*temp;
// 	int		finish;

// 	current_token = tokens;
// 	in_single_quotes = 0;
// 	in_double_quotes = 0;
// 	prev = NULL;
// 	while (current_token != NULL)
// 	{
// 		if (current_token->type == TOKEN_SINGLE_QUOTE)
// 		{
// 			in_single_quotes = !in_single_quotes;
// 			printf("in_single_quotes: %d changed at: %s\n", in_single_quotes,
// 				current_token->value);
// 		}
// 		if (current_token->type == TOKEN_DOUBLE_QUOTE)
// 		{
// 			in_double_quotes = !in_double_quotes;
// 			printf("in_double_quotes: %d changed at: %s\n", in_double_quotes,
// 				current_token->value);
// 		}
// 		if (current_token->type == TOKEN_WORD && !in_single_quotes)
// 		{
// 			while (current_token && current_token->value
// 				&& (ft_strchr(current_token->value, '$')
// 					|| (ft_strchr(current_token->value, '~')
// 						&& !in_double_quotes)))
// 			{
// 				if (ft_strlen(current_token->value) == 1
// 					&& current_token->value[0] == '$' && current_token->next
// 					&& current_token->next->type == TOKEN_DOUBLE_QUOTE
// 					&& !in_double_quotes)
// 				{
// 					printf("here\n");
// 					// Remove the dollar sign ('$')
// 					if (current_token->next->type == TOKEN_SINGLE_QUOTE
// 						&& ft_strlen(current_token->value) == 1)
// 					{
// 						in_single_quotes = !in_single_quotes;
// 						printf("in_single_quotes: %d changed at: %s\n",
// 							in_single_quotes, current_token->value);
// 					}
// 					if (current_token->next->type == TOKEN_DOUBLE_QUOTE
// 						&& ft_strlen(current_token->value) == 1)
// 					{
// 						in_double_quotes = !in_double_quotes;
// 						printf("in_double_quotes: %d changed at: %s\n",
// 							in_double_quotes, current_token->value);
// 					}
// 					tmp = current_token;
// 					current_token = current_token->next;
// 					free(tmp->value);
// 					free(tmp);
// 					tmp = NULL;
// 					if (!prev)
// 						tokens = current_token;
// 					else
// 						prev->next = current_token;
// 					break ;
// 				}
// 				else if (ft_strchr(current_token->value, '$')
// 					&& ft_strlen(current_token->value) > 1
// 					&& !ft_strchr(current_token->value, '~')
// 					&& !in_single_quotes)
// 				{
// 					if (ft_strlen(current_token->value) == 1
// 						&& (!current_token->next
// 							|| current_token->next->value[0] == ' '
// 							|| current_token->next->value[0] == '\0'))
// 					{
// 						if (current_token->next)
// 						{
// 							current_token = current_token->next;
// 							if (current_token->type == TOKEN_SINGLE_QUOTE)
// 							{
// 								in_single_quotes = !in_single_quotes;
// 								printf("in_single_quotes: %d changed at: %s\n",
// 									in_single_quotes, current_token->value);
// 							}
// 							if (current_token->type == TOKEN_DOUBLE_QUOTE)
// 							{
// 								in_double_quotes = !in_double_quotes;
// 								printf("in_double_quotes: %d changed at: %s\n",
// 									in_double_quotes, current_token->value);
// 							}
// 							continue ;
// 						}
// 						else
// 							break ;
// 					}
// 					start = ft_strchr(current_token->value, '$')
// 						- current_token->value;
// 					start++;
// 					end = start;
// 					while (current_token->value[end]
// 						&& (ft_isalnum(current_token->value[end])
// 							|| current_token->value[end] == '?'
// 							|| current_token->value[end] == '_'))
// 						end++;
// 					if (end - start == 0)
// 					{
// 						finish = 0;
// 						while (current_token && current_token->next
// 							&& ((current_token->type != TOKEN_WORD
// 									&& is_operator(*current_token))
// 								|| ft_strchr(current_token->value, '$') != NULL)
// 							&& !in_single_quotes)
// 						{
// 							prev = current_token;
// 							current_token = current_token->next;
// 							if (!current_token)
// 								break ;
// 							if (current_token->type == TOKEN_SINGLE_QUOTE)
// 							{
// 								in_single_quotes = !in_single_quotes;
// 								printf("in_single_quotes: %d changed at: %s\n",
// 									in_single_quotes, current_token->value);
// 							}
// 							if (current_token->type == TOKEN_DOUBLE_QUOTE)
// 							{
// 								in_double_quotes = !in_double_quotes;
// 								printf("in_double_quotes: %d changed at: %s\n",
// 									in_double_quotes, current_token->value);
// 							}
// 							finish = 1;
// 						}
// 						if (finish && current_token && current_token->next
// 							&& current_token->next->next && !in_single_quotes)
// 						{
// 							tmp = current_token->next->next;
// 							if (current_token->next->type == TOKEN_SINGLE_QUOTE)
// 							{
// 								in_single_quotes = !in_single_quotes;
// 								printf("in_single_quotes: %d changed at: %s\n",
// 									in_single_quotes, current_token->value);
// 							}
// 							if (current_token->next->type == TOKEN_DOUBLE_QUOTE)
// 							{
// 								in_double_quotes = !in_double_quotes;
// 								printf("in_double_quotes: %d changed at: %s\n",
// 									in_double_quotes, current_token->value);
// 							}
// 							free(current_token->next->value);
// 							free(current_token->next);
// 							current_token->next = NULL;
// 							current_token->next = tmp;
// 							finish = 0;
// 						}
// 						break ;
// 					}
// 					if (prev && prev->type == TOKEN_SINGLE_QUOTE)
// 					{
// 						in_single_quotes = !in_single_quotes;
// 						prev = current_token;
// 						current_token = current_token->next;
// 						continue ;
// 					}
// 					temp = ft_substr(current_token->value, 0, start - 1);
// 					temp = ft_strjoin(temp,
// 							ft_expand_word(ft_substr(current_token->value, start
// 									- 1, end - (start - 1)), global));
// 					temp = ft_strjoin(temp, &current_token->value[end]);
// 					free(current_token->value);
// 					current_token->value = ft_strdup(temp);
// 					if (current_token->value[0] == '\0')
// 						current_token->type = TOKEN_WORD;
// 					free(temp);
// 				}
// 				else if (ft_strchr(current_token->value, '~')
// 					&& !ft_strchr(current_token->value, '$')
// 					&& !in_single_quotes)
// 				{
// 					if (ft_strlen(current_token->value) == 1)
// 					{
// 						start = ft_strchr(current_token->value, '~')
// 							- current_token->value;
// 						temp = ft_substr(current_token->value, 0, start);
// 						temp = ft_strjoin(temp, ft_get_env("HOME",
// 									global->envv));
// 						temp = ft_strjoin(temp, &current_token->value[start
// 								+ 1]);
// 						free(current_token->value);
// 						current_token->value = ft_strdup(temp);
// 						if (current_token->value[0] == '\0')
// 							current_token->type = TOKEN_WORD;
// 						free(temp);
// 					}
// 					else
// 					{
// 						prev = current_token;
// 						current_token = current_token->next;
// 					}
// 				}
// 				else if (current_token)
// 				{
// 					prev = current_token;
// 					current_token = current_token->next;
// 				}
// 			}
// 		}
// 		if (current_token)
// 		{
// 			// if (current_token->type == TOKEN_SINGLE_QUOTE)
// 			// {
// 			// 	in_single_quotes = !in_single_quotes;
// 			// 	printf("in_single_quotes: %d changed at: %s\n",
// 			// 		in_single_quotes, current_token->value);
// 			// }
// 			// if (current_token->type == TOKEN_DOUBLE_QUOTE)
// 			// {
// 			// 	in_double_quotes = !in_double_quotes;
// 			// 	printf("in_double_quotes: %d changed at: %s\n",
// 			// 		in_double_quotes, current_token->value);
// 			// }
// 			prev = current_token;
// 			current_token = current_token->next;
// 		}
// 	}
// }

int	ft_strlen_til_space(char *str)
{
	int	i;

	i = 0;
	if (str && str[i] == '$')
		i++;
	while (str[i] && (str[i] != ' ' && str[i] != '\'' && str[i] != '\"'
			&& str[i] != '$'))
		i++;
	return (i);
}

void	ft_expand_tokens(t_token *tokens, t_global *global)
{
	t_token	*current;
	t_token	*temp;
	char	*tmp;
	char	*remind;
	char	*remind2;
	char	*expanded_word;
	bool	in_single_quotes;
	bool	in_double_quotes;
	int		i;

	current = tokens;
	temp = NULL;
	in_single_quotes = false;
	in_double_quotes = false;
	while (current)
	{
		if (current->type == TOKEN_WORD && ft_strlen(current->value) == 1)
		{
			if (current->type == TOKEN_WORD && !in_single_quotes
				&& current->next && (current->next->type != TOKEN_SINGLE_QUOTE
					&& current->next->type != TOKEN_DOUBLE_QUOTE))
			{
				expanded_word = ft_expand_word(current->value, global);
				if (expanded_word)
				{
					if (ft_strlen(expanded_word) != ft_strlen(current->value)
						|| ft_strncmp(expanded_word, current->value,
							ft_strlen(expanded_word)) != 0)
					{
						if (current->value)
							free(current->value);
						current->value = ft_strdup(expanded_word);
					}
				}
			}
			else if (current->type == TOKEN_WORD && !in_single_quotes
				&& !in_double_quotes && current->next
				&& (current->next->type == TOKEN_SINGLE_QUOTE
					|| current->next->type == TOKEN_DOUBLE_QUOTE))
			{
				prev_link_list(&tokens);
				current->prev->next = current->next;
				temp = current->next;
				free(current->value);
				free(current);
				prev_link_list(&tokens);
				current = temp;
			}
			else if (current->type == TOKEN_WORD && !in_single_quotes
				&& !in_double_quotes && !current->next)
			{
				expanded_word = ft_expand_word(current->value, global);
				if (expanded_word)
				{
					if (ft_strlen(expanded_word) != ft_strlen(current->value)
						|| ft_strncmp(expanded_word, current->value,
							ft_strlen(expanded_word)) != 0)
					{
						if (current->value)
							free(current->value);
						current->value = ft_strdup(expanded_word);
					}
				}
			}
		}
		else if (current->type == TOKEN_WORD && !in_single_quotes
			&& !in_double_quotes && current->value[0] == '~'
			&& (current->value[1] == '\0' || current->value[1] == '/'))
		{
			expanded_word = ft_strjoin(ft_get_env("HOME", global->envv),
					ft_substr(current->value, 1, ft_strlen(current->value)));
			if (expanded_word)
			{
				free(current->value);
				current->value = ft_strdup(expanded_word);
			}
		}
		else if (current->type == TOKEN_WORD && ft_strlen(current->value) > 1
			&& !in_single_quotes && ft_strchr(current->value, '$'))
		{
			while (ft_strchr(current->value, '$') && *(ft_strchr(current->value,
						'$') + 1) != '\0' && *(ft_strchr(current->value, '$')
					+ 1) != ' ')
			{
				i = 0;
				while (current->value && current->value[i] != '$')
					i++;
				if (ft_strchr(&current->value[i], '$'))
				{
					remind = ft_substr(current->value, 0, i);
					remind2 = ft_substr(current->value, i
							+ ft_strlen_til_space(&current->value[i]),
							ft_strlen(current->value));
					// printf("remind: %s\n", remind);
					// printf("remind2: %s\n", remind2);
					// printf("try to expand: %s\n", ft_substr(current->value,
					// i,
					// 		ft_strlen_til_space(&current->value[i])));
					tmp = ft_expand_word(ft_substr(&current->value[i],
								ft_strchr(&current->value[i], '$')
								- &current->value[i],
								ft_strlen_til_space(&current->value[i])),
							global);
					if (tmp)
					{
						free(current->value);
						current->value = ft_strjoin(remind, ft_strjoin(tmp,
									remind2));
						free(tmp);
					}
				}
				else
				{
					remind = ft_substr(current->value, 0, i);
					tmp = ft_expand_word(ft_substr(current->value, i,
								ft_strlen(current->value)), global);
					if (tmp)
					{
						free(current->value);
						current->value = ft_strjoin(remind, tmp);
						free(tmp);
					}
				}
			}
		}
		else if (current->type == TOKEN_SINGLE_QUOTE)
		{
			in_single_quotes = !in_single_quotes;
		}
		else if (current->type == TOKEN_DOUBLE_QUOTE)
		{
			in_double_quotes = !in_double_quotes;
		}
		current = current->next;
	}
}
