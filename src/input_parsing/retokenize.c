/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retokenize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 10:05:18 by vscode            #+#    #+#             */
/*   Updated: 2024/05/11 10:53:22 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	skip_quote_content(t_token **current, t_token **temp);
void	skip_multiple_spaces(t_token **current, t_token **temp);

void	split_words_with_spaces_first_word(t_token **current, char ***split,
		int i, bool first_space)
{
	t_token	*new_token;

	free((*current)->value);
	if (!first_space)
		(*current)->value = (*split)[i];
	else
	{
		(*current)->value = ft_strdup(" ");
		new_token = create_token(TOKEN_WORD, (*split)[i]);
		new_token->next = (*current)->next;
		(*current)->next = new_token;
		(*current) = (*current)->next;
	}
}

void	split_words_with_spaces_next_words(t_token **current,
		t_token **new_token, char ***split, int i)
{
	(*new_token) = create_token(TOKEN_WORD, (*split)[i]);
	(*new_token)->next = (*current)->next;
	(*current)->next = (*new_token);
	(*current) = (*current)->next;
}

void	split_words_with_spaces(t_token **current, t_token **new_token,
		char ***split)
{
	int		i;
	bool	last_space;
	bool	first_space;

	if (!(*current) || !(*current)->value)
		return ;
	if ((*current)->value[0] == ' ')
		first_space = true;
	else
		first_space = false;
	if ((*current)->value[ft_strlen((*current)->value) - 1] == ' ')
		last_space = true;
	else
		last_space = false;
	if ((*current)->type == TOKEN_WORD && ft_strchr((*current)->value, ' '))
	{
		(*split) = ft_split((*current)->value, ' ');
		i = 0;
		while ((*split)[i])
		{
			if (i == 0)
				split_words_with_spaces_first_word(current, split, i,
					first_space);
			else
				split_words_with_spaces_next_words(current, new_token, split,
					i);
			if ((*split)[i + 1] != NULL)
			{
				(*new_token) = create_token(TOKEN_SPACE, ft_strdup(" "));
				(*new_token)->next = (*current)->next;
				(*current)->next = (*new_token);
				(*current) = (*current)->next;
			}
			i++;
		}
		if (last_space)
		{
			(*new_token) = create_token(TOKEN_SPACE, ft_strdup(" "));
			(*new_token)->next = (*current)->next;
			(*current)->next = (*new_token);
			(*current) = (*current)->next;
		}
		free(*split);
	}
}

void	retokenize(t_token **tokens)
{
	t_token	*current;
	t_token	*temp;
	t_token	*new_token;
	char	**split;

	current = *tokens;
	while (current)
	{
		skip_quote_content(&current, &temp);
		skip_multiple_spaces(&current, &temp);
		split_words_with_spaces(&current, &new_token, &split);
		if (current)
			current = current->next;
	}
}
