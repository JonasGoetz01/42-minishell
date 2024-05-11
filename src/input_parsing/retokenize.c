/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retokenize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 10:05:18 by vscode            #+#    #+#             */
/*   Updated: 2024/05/11 16:09:23 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	skip_quote_content(t_token **current, t_token **temp);
void	skip_multiple_spaces(t_token **current, t_token **temp);
void	split_words_with_spaces_util_1(t_token **new_token, t_token **current,
			char ***split, int *i);
void	split_words_with_spaces_util_2(t_token **current, bool *first_space,
			bool *last_space);

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

void	split_words_with_spaces_util(bool *last_space, t_token **new_token,
		t_token **current)
{
	if (last_space)
	{
		(*new_token) = create_token(TOKEN_SPACE, ft_strdup(" "));
		(*new_token)->next = (*current)->next;
		(*current)->next = (*new_token);
		(*current) = (*current)->next;
	}
}

void	split_words_with_spaces(t_token **current, t_token **new_token,
		char ***split)
{
	int		i;
	bool	last_space;
	bool	first_space;

	split_words_with_spaces_util_2(current, &first_space, &last_space);
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
			split_words_with_spaces_util_1(new_token, current, split, &i);
			i++;
		}
		split_words_with_spaces_util(&last_space, new_token, current);
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
