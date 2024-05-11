/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retokenize_utils_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 10:05:18 by vscode            #+#    #+#             */
/*   Updated: 2024/05/11 16:09:09 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	skip_quote_content(t_token **current, t_token **temp);
void	skip_multiple_spaces(t_token **current, t_token **temp);

void	split_words_with_spaces_util_1(t_token **new_token, t_token **current,
		char ***split, int *i)
{
	if ((*split)[*i + 1] != NULL)
	{
		(*new_token) = create_token(TOKEN_SPACE, ft_strdup(" "));
		(*new_token)->next = (*current)->next;
		(*current)->next = (*new_token);
		(*current) = (*current)->next;
	}
}

void	split_words_with_spaces_util_2(t_token **current, bool *first_space,
		bool *last_space)
{
	if (!(*current) || !(*current)->value)
		return ;
	if ((*current)->value[0] == ' ')
		(*first_space) = true;
	else
		(*first_space) = false;
	if ((*current)->value[ft_strlen((*current)->value) - 1] == ' ')
		(*last_space) = true;
	else
		(*last_space) = false;
}
