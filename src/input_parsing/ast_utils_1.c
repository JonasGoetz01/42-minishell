/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 16:55:28 by vscode            #+#    #+#             */
/*   Updated: 2024/05/11 16:11:45 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	get_highest_token(t_token **highest_token, t_token **current_token);
void	create_ast(t_ast_node **ast, t_ast_node **root,
			t_token **highest_token);
void	skip_tokens(t_ast_node **ast, t_token **tokens,
			t_token **current_token);
bool	handle_highest_token(t_ast_node **ast, t_token **highest_token,
			t_token **tokens, t_token **current_token);
void	create_arms(t_token **right_arm, t_token **tokens,
			t_token **current_token, t_token **highest_token);

void	remove_bracktes_util(t_token **tokens, t_token **closing_bracket)
{
	prev_link_list(tokens);
	if ((*closing_bracket)->prev && (*closing_bracket)->next)
	{
		(*closing_bracket)->prev->next = (*closing_bracket)->next;
		free((*closing_bracket)->value);
		if ((*closing_bracket)->be_value)
			free((*closing_bracket)->be_value);
		free((*closing_bracket));
	}
	else if (!(*closing_bracket)->prev)
	{
		free_tokens(*tokens);
		*tokens = NULL;
	}
	else if (!(*closing_bracket)->next)
	{
		(*closing_bracket)->prev->next = NULL;
		free((*closing_bracket)->value);
		if ((*closing_bracket)->be_value)
			free((*closing_bracket)->be_value);
		free((*closing_bracket));
	}
}

void	free_open_bracket(t_token **opening_bracket, t_token **current)
{
	(*opening_bracket)->prev->next = *current;
	free((*opening_bracket)->value);
	if ((*opening_bracket)->be_value)
		free((*opening_bracket)->be_value);
	free((*opening_bracket));
}
