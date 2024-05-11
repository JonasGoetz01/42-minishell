/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_util_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 10:34:07 by vscode            #+#    #+#             */
/*   Updated: 2024/05/11 16:04:23 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_expand_word(char *word, t_global *global);
int		ft_strlen_til_space(char *str);
void	single_word_no_quotes(t_token **current, t_global *global);
void	single_char_with_quotes(t_token **current, t_token **tokens);
void	single_char_no_next(t_token **current, t_global *global);

void	expand_variables_1_util(char *tmp, char *remind, char *remind2)
{
	if (tmp)
		free(tmp);
	if (remind)
		free(remind);
	if (remind2)
		free(remind2);
}

void	expand_variables_1_util_1(t_token **current, char **tmp3)
{
	*tmp3 = NULL;
	if ((*current)->be_value)
	{
		*tmp3 = ft_strjoin((*current)->be_value, (*current)->value);
		free((*current)->be_value);
		free((*current)->value);
	}
	if (tmp3)
		(*current)->be_value = *tmp3;
	else
		(*current)->be_value = (*current)->value;
}
