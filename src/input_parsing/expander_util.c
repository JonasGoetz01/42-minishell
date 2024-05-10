/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 10:34:04 by vscode            #+#    #+#             */
/*   Updated: 2024/05/10 19:03:20 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_expand_word(char *word, t_global *global)
{
	char	*env_value;

	if (word[0] == '$')
	{
		if (word[1] == '\0')
			return (word);
		if (word[1] == '?')
			return (free(word), ft_itoa(global->old_exit_status));
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
	if ((*current)->be_value)
		free((*current)->be_value);
	(*current)->be_value = NULL;
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
			// if ((*current)->value)
			// 	free((*current)->value);
			(*current)->be_value = (*current)->value;
			(*current)->value = ft_strdup(expanded_word);
		}
	}
}
