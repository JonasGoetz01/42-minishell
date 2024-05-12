/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validator_utils_1.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:40:35 by vscode            #+#    #+#             */
/*   Updated: 2024/05/12 10:45:32 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool			first_is_pipe_second_operator(t_token **prev, t_token **current,
					t_token **tokens);
bool			pipe_after_pipe(t_token *current);
bool			redirect_has_no_file(t_token *current);
bool			no_file_for_indirect(t_token *current);
bool			ft_no_lim_heredoc(t_token *current);
t_token_type	get_next_type(t_token *token);

bool	operator_has_no_right_side(t_token *current)
{
	if ((current->type == TOKEN_PIPE || current->type == TOKEN_DOUBLE_PIPE
			|| current->type == TOKEN_DOUBLE_AMPERSAND) && ((current->next
				&& next_is_operator(current->next))
			|| next_is_newline(current->next)))
		return (true);
	return (false);
}

bool	empty_bracket(t_token *current)
{
	if (current->type == TOKEN_BRACKET_L)
	{
		while (current)
		{
			if (is_operator(*current) || current->type == TOKEN_SPACE)
				return (false);
			else if (current->type == TOKEN_BRACKET_R)
				return (true);
			current = current->next;
		}
	}
	else
		return (false);
	return (true);
}

bool	open_bracket_after_closing(t_token *current)
{
	if (current->type == TOKEN_BRACKET_R)
	{
		current = current->next;
		while (current && current->type == TOKEN_SPACE)
			current = current->next;
		if (current && current->type == TOKEN_BRACKET_L)
			return (true);
	}
	return (false);
}

bool	check_invalids(t_token **tokens, t_token **prev, t_token **current)
{
	if (first_is_pipe_second_operator(prev, current, tokens)
		|| pipe_after_pipe(*current) || ((*current == *tokens)
			&& (get_next_type(*current) == TOKEN_PIPE))
		|| redirect_has_no_file(*current) || no_file_for_indirect(*current)
		|| ft_no_lim_heredoc(*current) || operator_has_no_right_side(*current)
		|| empty_bracket(*current) || open_bracket_after_closing(*current))
		return (true);
	return (false);
}
