/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_util_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 10:34:07 by vscode            #+#    #+#             */
/*   Updated: 2024/05/12 09:35:46 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_expand_word(char *word, t_global *global);
int		ft_strlen_til_space(char *str);
void	single_word_no_quotes(t_token **current, t_global *global);
void	single_char_with_quotes(t_token **current, t_token **tokens);
void	single_char_no_next(t_token **current, t_global *global);
void	expand_variables_1_util(char **tmp, char **remind, char **remind2);
void	expand_variables_1_util_1(t_token **current, char **tmp3);

void	single_char(t_token **current, t_token **tokens, t_global *global,
		t_expander_helper *h)
{
	if ((*current)->type == TOKEN_WORD && !h->in_single_quotes
		&& (*current)->next && ((*current)->next->type != TOKEN_SINGLE_QUOTE
			&& (*current)->next->type != TOKEN_DOUBLE_QUOTE))
		single_word_no_quotes(current, global);
	else if ((*current)->type == TOKEN_WORD && !h->in_single_quotes
		&& !h->in_double_quotes && (*current)->next
		&& ((*current)->next->type == TOKEN_SINGLE_QUOTE
			|| (*current)->next->type == TOKEN_DOUBLE_QUOTE)
		&& (ft_strchr((*current)->value, '$') || ft_strchr((*current)->value,
				'~')))
		single_char_with_quotes(current, tokens);
	else if ((*current)->type == TOKEN_WORD && !h->in_single_quotes
		&& !h->in_double_quotes && !(*current)->next)
		single_char_no_next(current, global);
}

void	expand_tilde(t_token **current, t_global *global)
{
	char	*expanded_word;
	char	*sub;

	sub = ft_substr((*current)->value, 1, ft_strlen((*current)->value));
	expanded_word = ft_strjoin(ft_get_env("HOME", global->envv), sub);
	free(sub);
	if (expanded_word)
	{
		(*current)->be_value = (*current)->value;
		(*current)->value = expanded_word;
	}
}

void	expand_variables_1(t_token **current, t_global *global, int i)
{
	char	*remind;
	char	*remind2;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	remind = ft_substr((*current)->value, 0, i);
	remind2 = ft_substr((*current)->value, i
			+ ft_strlen_til_space(&(*current)->value[i]),
			ft_strlen((*current)->value));
	tmp3 = ft_substr(&(*current)->value[i], ft_strchr(&(*current)->value[i],
				'$') - &(*current)->value[i],
			ft_strlen_til_space(&(*current)->value[i]));
	tmp = ft_expand_word(tmp3, global);
	if (tmp)
	{
		expand_variables_1_util_1(current, &tmp3);
		tmp2 = ft_strjoin(tmp, remind2);
		(*current)->value = ft_strjoin(remind, tmp2);
		free(tmp2);
		free(tmp);
		tmp = NULL;
	}
	expand_variables_1_util(&tmp, &remind, &remind2);
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
		(*current)->be_value = (*current)->value;
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
