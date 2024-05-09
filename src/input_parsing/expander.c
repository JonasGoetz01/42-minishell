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

int	ft_strlen_til_space(char *str)
{
	int	i;

	i = 0;
	if (str && str[i] == '$')
		i++;
	while (str[i] && (str[i] != ' ' && str[i] != '\'' && str[i] != '\"'
			&& str[i] != '$' && str[i] != ':' && str[i] != '.'
			&& str[i] != '/'))
		i++;
	return (i);
}

void	single_word_no_quotes(t_token **current, t_global *global)
{
	char	*expanded_word;

	expanded_word = ft_expand_word((*current)->value, global);
	if (expanded_word)
	{
		if (ft_strlen(expanded_word) != ft_strlen((*current)->value)
			|| ft_strncmp(expanded_word, (*current)->value,
				ft_strlen(expanded_word)) != 0)
		{
			if ((*current)->value)
				free((*current)->value);
			(*current)->value = ft_strdup(expanded_word);
		}
	}
}

void	single_char_with_quotes(t_token **current, t_token **tokens)
{
	t_token	*temp;

	prev_link_list(tokens);
	if (!(*current)->prev)
		*tokens = (*current)->next;
	else if ((*current)->prev)
		(*current)->prev->next = (*current)->next;
	temp = (*current)->next;
	free((*current)->value);
	free((*current));
	prev_link_list(tokens);
	(*current) = temp->prev;
}

void	single_char_no_next(t_token **current, t_global *global)
{
	char	*expanded_word;

	expanded_word = ft_expand_word((*current)->value, global);
	if (expanded_word)
	{
		if (ft_strlen(expanded_word) != ft_strlen((*current)->value)
			|| ft_strncmp(expanded_word, (*current)->value,
				ft_strlen(expanded_word)) != 0)
		{
			if ((*current)->value)
				free((*current)->value);
			(*current)->value = ft_strdup(expanded_word);
		}
	}
}

void	single_char(t_token **current, t_token **tokens, t_global *global,
		bool *in_single_quotes, bool *in_double_quotes)
{
	if ((*current)->type == TOKEN_WORD && !*in_single_quotes && (*current)->next
		&& ((*current)->next->type != TOKEN_SINGLE_QUOTE
			&& (*current)->next->type != TOKEN_DOUBLE_QUOTE))
		single_word_no_quotes(current, global);
	else if ((*current)->type == TOKEN_WORD && !*in_single_quotes
		&& !*in_double_quotes && (*current)->next
		&& ((*current)->next->type == TOKEN_SINGLE_QUOTE
			|| (*current)->next->type == TOKEN_DOUBLE_QUOTE)
		&& (ft_strchr((*current)->value, '$') || ft_strchr((*current)->value,
				'~')))
		single_char_with_quotes(current, tokens);
	else if ((*current)->type == TOKEN_WORD && !*in_single_quotes
		&& !*in_double_quotes && !(*current)->next)
		single_char_no_next(current, global);
}

void	expand_tilde(t_token **current, t_global *global)
{
	char	*expanded_word;

	expanded_word = ft_strjoin(ft_get_env("HOME", global->envv),
			ft_substr((*current)->value, 1, ft_strlen((*current)->value)));
	if (expanded_word)
	{
		free((*current)->value);
		(*current)->value = ft_strdup(expanded_word);
	}
}

void	expand_variables_1(t_token **current, t_global *global, int i)
{
	char	*remind;
	char	*remind2;
	char	*tmp;

	remind = ft_substr((*current)->value, 0, i);
	remind2 = ft_substr((*current)->value, i
			+ ft_strlen_til_space(&(*current)->value[i]),
			ft_strlen((*current)->value));
	tmp = ft_expand_word(ft_substr(&(*current)->value[i],
				ft_strchr(&(*current)->value[i], '$') - &(*current)->value[i],
				ft_strlen_til_space(&(*current)->value[i])), global);
	if (tmp)
	{
		free((*current)->value);
		(*current)->value = ft_strjoin(remind, ft_strjoin(tmp, remind2));
		free(tmp);
	}
}

void	expand_variables_2(t_token **current, t_global *global, int i)
{
	char	*remind;
	char	*tmp;

	remind = ft_substr((*current)->value, 0, i);
	tmp = ft_expand_word(ft_substr((*current)->value, i,
				ft_strlen((*current)->value)), global);
	if (tmp)
	{
		free((*current)->value);
		(*current)->value = ft_strjoin(remind, tmp);
		free(tmp);
	}
}

void	expand_variables(t_token **current, t_global *global)
{
	int	i;

	while (ft_strchr((*current)->value, '$') && *(ft_strchr((*current)->value,
				'$') + 1) != '\0' && *(ft_strchr((*current)->value, '$')
			+ 1) != ' ')
	{
		i = 0;
		while ((*current)->value && (*current)->value[i] != '$')
			i++;
		if (ft_strchr(&(*current)->value[i], '$'))
			expand_variables_1(current, global, i);
		else
			expand_variables_2(current, global, i);
	}
}

void	update_quotes(t_token **current, bool *in_single_quotes,
		bool *in_double_quotes)
{
	if ((*current)->type == TOKEN_SINGLE_QUOTE)
		*in_single_quotes = !*in_single_quotes;
	else if ((*current)->type == TOKEN_DOUBLE_QUOTE)
		*in_double_quotes = !*in_double_quotes;
}

void	update_current(t_token **current)
{
	if ((*current))
		*current = (*current)->next;
}

void	ft_expand_tokens(t_token *tokens, t_global *global)
{
	t_token	*current;
	bool	in_single_quotes;
	bool	in_double_quotes;

	current = tokens;
	in_single_quotes = false;
	in_double_quotes = false;
	while (current)
	{
		if (current->type == TOKEN_WORD && ft_strlen(current->value) == 1)
			single_char(&current, &tokens, global, &in_single_quotes,
				&in_double_quotes);
		else if (current->type == TOKEN_WORD && !in_single_quotes
			&& !in_double_quotes && current->value[0] == '~'
			&& (current->value[1] == '\0' || current->value[1] == '/'))
			expand_tilde(&current, global);
		else if (current->type == TOKEN_WORD && ft_strlen(current->value) > 1
			&& !in_single_quotes && ft_strchr(current->value, '$')
			&& (current->value[ft_strchr(current->value, '$') - current->value
				+ 1] != '/'))
			expand_variables(&current, global);
		else
			update_quotes(&current, &in_single_quotes, &in_double_quotes);
		update_current(&current);
	}
}
