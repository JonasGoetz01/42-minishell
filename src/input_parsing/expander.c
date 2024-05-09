/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 12:22:33 by vscode            #+#    #+#             */
/*   Updated: 2024/05/09 12:22:36 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_expand_word(char *word, t_global *global);
int		ft_strlen_til_space(char *str);
void	single_word_no_quotes(t_token **current, t_global *global);
void	single_char_with_quotes(t_token **current, t_token **tokens);
void	single_char_no_next(t_token **current, t_global *global);

void	single_char(t_token **current, t_token **tokens, t_global *global,
			t_expander_helper *h);
void	expand_tilde(t_token **current, t_global *global);
void	expand_variables_1(t_token **current, t_global *global, int i);
void	expand_variables_2(t_token **current, t_global *global, int i);
void	expand_variables(t_token **current, t_global *global);

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
	t_token				*current;
	t_expander_helper	h;

	current = tokens;
	h.in_single_quotes = false;
	h.in_double_quotes = false;
	while (current)
	{
		if (current->type == TOKEN_WORD && ft_strlen(current->value) == 1)
			single_char(&current, &tokens, global, &h);
		else if (current->type == TOKEN_WORD && !h.in_single_quotes
			&& !h.in_double_quotes && current->value[0] == '~'
			&& (current->value[1] == '\0' || current->value[1] == '/'))
			expand_tilde(&current, global);
		else if (current->type == TOKEN_WORD && ft_strlen(current->value) > 1
			&& !h.in_single_quotes && ft_strchr(current->value, '$')
			&& (current->value[ft_strchr(current->value, '$') - current->value
					+ 1] != '/'))
			expand_variables(&current, global);
		else
			update_quotes(&current, &h.in_single_quotes, &h.in_double_quotes);
		update_current(&current);
	}
}
